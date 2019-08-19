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
      case 177: // value
      case 181: // map_value
      case 219: // socket_type
      case 222: // outbound_interface_value
      case 238: // db_type
      case 323: // hr_mode
      case 471: // ncr_protocol_value
      case 479: // replace_client_name_value
        value.YY_MOVE_OR_COPY< ElementPtr > (YY_MOVE (that.value));
        break;

      case 161: // "boolean"
        value.YY_MOVE_OR_COPY< bool > (YY_MOVE (that.value));
        break;

      case 160: // "floating point"
        value.YY_MOVE_OR_COPY< double > (YY_MOVE (that.value));
        break;

      case 159: // "integer"
        value.YY_MOVE_OR_COPY< int64_t > (YY_MOVE (that.value));
        break;

      case 158: // "constant string"
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
      case 177: // value
      case 181: // map_value
      case 219: // socket_type
      case 222: // outbound_interface_value
      case 238: // db_type
      case 323: // hr_mode
      case 471: // ncr_protocol_value
      case 479: // replace_client_name_value
        value.move< ElementPtr > (YY_MOVE (that.value));
        break;

      case 161: // "boolean"
        value.move< bool > (YY_MOVE (that.value));
        break;

      case 160: // "floating point"
        value.move< double > (YY_MOVE (that.value));
        break;

      case 159: // "integer"
        value.move< int64_t > (YY_MOVE (that.value));
        break;

      case 158: // "constant string"
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
      case 177: // value
      case 181: // map_value
      case 219: // socket_type
      case 222: // outbound_interface_value
      case 238: // db_type
      case 323: // hr_mode
      case 471: // ncr_protocol_value
      case 479: // replace_client_name_value
        value.move< ElementPtr > (that.value);
        break;

      case 161: // "boolean"
        value.move< bool > (that.value);
        break;

      case 160: // "floating point"
        value.move< double > (that.value);
        break;

      case 159: // "integer"
        value.move< int64_t > (that.value);
        break;

      case 158: // "constant string"
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
      case 158: // "constant string"
#line 236 "dhcp4_parser.yy"
        { yyoutput << yysym.value.template as < std::string > (); }
#line 408 "dhcp4_parser.cc"
        break;

      case 159: // "integer"
#line 236 "dhcp4_parser.yy"
        { yyoutput << yysym.value.template as < int64_t > (); }
#line 414 "dhcp4_parser.cc"
        break;

      case 160: // "floating point"
#line 236 "dhcp4_parser.yy"
        { yyoutput << yysym.value.template as < double > (); }
#line 420 "dhcp4_parser.cc"
        break;

      case 161: // "boolean"
#line 236 "dhcp4_parser.yy"
        { yyoutput << yysym.value.template as < bool > (); }
#line 426 "dhcp4_parser.cc"
        break;

      case 177: // value
#line 236 "dhcp4_parser.yy"
        { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 432 "dhcp4_parser.cc"
        break;

      case 181: // map_value
#line 236 "dhcp4_parser.yy"
        { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 438 "dhcp4_parser.cc"
        break;

      case 219: // socket_type
#line 236 "dhcp4_parser.yy"
        { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 444 "dhcp4_parser.cc"
        break;

      case 222: // outbound_interface_value
#line 236 "dhcp4_parser.yy"
        { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 450 "dhcp4_parser.cc"
        break;

      case 238: // db_type
#line 236 "dhcp4_parser.yy"
        { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 456 "dhcp4_parser.cc"
        break;

      case 323: // hr_mode
#line 236 "dhcp4_parser.yy"
        { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 462 "dhcp4_parser.cc"
        break;

      case 471: // ncr_protocol_value
#line 236 "dhcp4_parser.yy"
        { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 468 "dhcp4_parser.cc"
        break;

      case 479: // replace_client_name_value
#line 236 "dhcp4_parser.yy"
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
      case 177: // value
      case 181: // map_value
      case 219: // socket_type
      case 222: // outbound_interface_value
      case 238: // db_type
      case 323: // hr_mode
      case 471: // ncr_protocol_value
      case 479: // replace_client_name_value
        yylhs.value.emplace< ElementPtr > ();
        break;

      case 161: // "boolean"
        yylhs.value.emplace< bool > ();
        break;

      case 160: // "floating point"
        yylhs.value.emplace< double > ();
        break;

      case 159: // "integer"
        yylhs.value.emplace< int64_t > ();
        break;

      case 158: // "constant string"
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
#line 245 "dhcp4_parser.yy"
    { ctx.ctx_ = ctx.NO_KEYWORD; }
#line 741 "dhcp4_parser.cc"
    break;

  case 4:
#line 246 "dhcp4_parser.yy"
    { ctx.ctx_ = ctx.CONFIG; }
#line 747 "dhcp4_parser.cc"
    break;

  case 6:
#line 247 "dhcp4_parser.yy"
    { ctx.ctx_ = ctx.DHCP4; }
#line 753 "dhcp4_parser.cc"
    break;

  case 8:
#line 248 "dhcp4_parser.yy"
    { ctx.ctx_ = ctx.INTERFACES_CONFIG; }
#line 759 "dhcp4_parser.cc"
    break;

  case 10:
#line 249 "dhcp4_parser.yy"
    { ctx.ctx_ = ctx.SUBNET4; }
#line 765 "dhcp4_parser.cc"
    break;

  case 12:
#line 250 "dhcp4_parser.yy"
    { ctx.ctx_ = ctx.POOLS; }
#line 771 "dhcp4_parser.cc"
    break;

  case 14:
#line 251 "dhcp4_parser.yy"
    { ctx.ctx_ = ctx.RESERVATIONS; }
#line 777 "dhcp4_parser.cc"
    break;

  case 16:
#line 252 "dhcp4_parser.yy"
    { ctx.ctx_ = ctx.DHCP4; }
#line 783 "dhcp4_parser.cc"
    break;

  case 18:
#line 253 "dhcp4_parser.yy"
    { ctx.ctx_ = ctx.OPTION_DEF; }
#line 789 "dhcp4_parser.cc"
    break;

  case 20:
#line 254 "dhcp4_parser.yy"
    { ctx.ctx_ = ctx.OPTION_DATA; }
#line 795 "dhcp4_parser.cc"
    break;

  case 22:
#line 255 "dhcp4_parser.yy"
    { ctx.ctx_ = ctx.HOOKS_LIBRARIES; }
#line 801 "dhcp4_parser.cc"
    break;

  case 24:
#line 256 "dhcp4_parser.yy"
    { ctx.ctx_ = ctx.DHCP_DDNS; }
#line 807 "dhcp4_parser.cc"
    break;

  case 26:
#line 257 "dhcp4_parser.yy"
    { ctx.ctx_ = ctx.LOGGING; }
#line 813 "dhcp4_parser.cc"
    break;

  case 28:
#line 265 "dhcp4_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 819 "dhcp4_parser.cc"
    break;

  case 29:
#line 266 "dhcp4_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location))); }
#line 825 "dhcp4_parser.cc"
    break;

  case 30:
#line 267 "dhcp4_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 831 "dhcp4_parser.cc"
    break;

  case 31:
#line 268 "dhcp4_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 837 "dhcp4_parser.cc"
    break;

  case 32:
#line 269 "dhcp4_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 843 "dhcp4_parser.cc"
    break;

  case 33:
#line 270 "dhcp4_parser.yy"
    { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 849 "dhcp4_parser.cc"
    break;

  case 34:
#line 271 "dhcp4_parser.yy"
    { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 855 "dhcp4_parser.cc"
    break;

  case 35:
#line 274 "dhcp4_parser.yy"
    {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as < ElementPtr > ());
}
#line 864 "dhcp4_parser.cc"
    break;

  case 36:
#line 279 "dhcp4_parser.yy"
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 875 "dhcp4_parser.cc"
    break;

  case 37:
#line 284 "dhcp4_parser.yy"
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 885 "dhcp4_parser.cc"
    break;

  case 38:
#line 290 "dhcp4_parser.yy"
    { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 891 "dhcp4_parser.cc"
    break;

  case 41:
#line 297 "dhcp4_parser.yy"
    {
                  // map containing a single entry
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 900 "dhcp4_parser.cc"
    break;

  case 42:
#line 301 "dhcp4_parser.yy"
    {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 910 "dhcp4_parser.cc"
    break;

  case 43:
#line 308 "dhcp4_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 919 "dhcp4_parser.cc"
    break;

  case 44:
#line 311 "dhcp4_parser.yy"
    {
    // list parsing complete. Put any sanity checking here
}
#line 927 "dhcp4_parser.cc"
    break;

  case 47:
#line 319 "dhcp4_parser.yy"
    {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 936 "dhcp4_parser.cc"
    break;

  case 48:
#line 323 "dhcp4_parser.yy"
    {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 945 "dhcp4_parser.cc"
    break;

  case 49:
#line 330 "dhcp4_parser.yy"
    {
    // List parsing about to start
}
#line 953 "dhcp4_parser.cc"
    break;

  case 50:
#line 332 "dhcp4_parser.yy"
    {
    // list parsing complete. Put any sanity checking here
    //ctx.stack_.pop_back();
}
#line 962 "dhcp4_parser.cc"
    break;

  case 53:
#line 341 "dhcp4_parser.yy"
    {
                          ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 971 "dhcp4_parser.cc"
    break;

  case 54:
#line 345 "dhcp4_parser.yy"
    {
                          ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 980 "dhcp4_parser.cc"
    break;

  case 55:
#line 356 "dhcp4_parser.yy"
    {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as < std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 991 "dhcp4_parser.cc"
    break;

  case 56:
#line 366 "dhcp4_parser.yy"
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1002 "dhcp4_parser.cc"
    break;

  case 57:
#line 371 "dhcp4_parser.yy"
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.

    // Dhcp4 is required
    ctx.require("Dhcp4", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
}
#line 1015 "dhcp4_parser.cc"
    break;

  case 66:
#line 395 "dhcp4_parser.yy"
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Dhcp4", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP4);
}
#line 1028 "dhcp4_parser.cc"
    break;

  case 67:
#line 402 "dhcp4_parser.yy"
    {
    // No global parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1038 "dhcp4_parser.cc"
    break;

  case 68:
#line 410 "dhcp4_parser.yy"
    {
    // Parse the Dhcp4 map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1048 "dhcp4_parser.cc"
    break;

  case 69:
#line 414 "dhcp4_parser.yy"
    {
    // No global parameter is required
    // parsing completed
}
#line 1057 "dhcp4_parser.cc"
    break;

  case 99:
#line 454 "dhcp4_parser.yy"
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 1066 "dhcp4_parser.cc"
    break;

  case 100:
#line 459 "dhcp4_parser.yy"
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 1075 "dhcp4_parser.cc"
    break;

  case 101:
#line 464 "dhcp4_parser.yy"
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 1084 "dhcp4_parser.cc"
    break;

  case 102:
#line 469 "dhcp4_parser.yy"
    {
    ElementPtr dpp(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 1093 "dhcp4_parser.cc"
    break;

  case 103:
#line 474 "dhcp4_parser.yy"
    {
    ElementPtr echo(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("echo-client-id", echo);
}
#line 1102 "dhcp4_parser.cc"
    break;

  case 104:
#line 479 "dhcp4_parser.yy"
    {
    ElementPtr match(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("match-client-id", match);
}
#line 1111 "dhcp4_parser.cc"
    break;

  case 105:
#line 485 "dhcp4_parser.yy"
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces-config", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.INTERFACES_CONFIG);
}
#line 1122 "dhcp4_parser.cc"
    break;

  case 106:
#line 490 "dhcp4_parser.yy"
    {
    // No interfaces config param is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1132 "dhcp4_parser.cc"
    break;

  case 116:
#line 509 "dhcp4_parser.yy"
    {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1142 "dhcp4_parser.cc"
    break;

  case 117:
#line 513 "dhcp4_parser.yy"
    {
    // No interfaces config param is required
    // parsing completed
}
#line 1151 "dhcp4_parser.cc"
    break;

  case 118:
#line 518 "dhcp4_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1162 "dhcp4_parser.cc"
    break;

  case 119:
#line 523 "dhcp4_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1171 "dhcp4_parser.cc"
    break;

  case 120:
#line 528 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.DHCP_SOCKET_TYPE);
}
#line 1179 "dhcp4_parser.cc"
    break;

  case 121:
#line 530 "dhcp4_parser.yy"
    {
    ctx.stack_.back()->set("dhcp-socket-type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1188 "dhcp4_parser.cc"
    break;

  case 122:
#line 535 "dhcp4_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("raw", ctx.loc2pos(yystack_[0].location))); }
#line 1194 "dhcp4_parser.cc"
    break;

  case 123:
#line 536 "dhcp4_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("udp", ctx.loc2pos(yystack_[0].location))); }
#line 1200 "dhcp4_parser.cc"
    break;

  case 124:
#line 539 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.OUTBOUND_INTERFACE);
}
#line 1208 "dhcp4_parser.cc"
    break;

  case 125:
#line 541 "dhcp4_parser.yy"
    {
    ctx.stack_.back()->set("outbound-interface", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1217 "dhcp4_parser.cc"
    break;

  case 126:
#line 546 "dhcp4_parser.yy"
    {
    yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("same-as-inbound", ctx.loc2pos(yystack_[0].location)));
}
#line 1225 "dhcp4_parser.cc"
    break;

  case 127:
#line 548 "dhcp4_parser.yy"
    {
    yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("use-routing", ctx.loc2pos(yystack_[0].location)));
    }
#line 1233 "dhcp4_parser.cc"
    break;

  case 128:
#line 552 "dhcp4_parser.yy"
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("re-detect", b);
}
#line 1242 "dhcp4_parser.cc"
    break;

  case 129:
#line 558 "dhcp4_parser.yy"
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lease-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.LEASE_DATABASE);
}
#line 1253 "dhcp4_parser.cc"
    break;

  case 130:
#line 563 "dhcp4_parser.yy"
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1264 "dhcp4_parser.cc"
    break;

  case 131:
#line 570 "dhcp4_parser.yy"
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1275 "dhcp4_parser.cc"
    break;

  case 132:
#line 575 "dhcp4_parser.yy"
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1286 "dhcp4_parser.cc"
    break;

  case 133:
#line 582 "dhcp4_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1297 "dhcp4_parser.cc"
    break;

  case 134:
#line 587 "dhcp4_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1306 "dhcp4_parser.cc"
    break;

  case 139:
#line 600 "dhcp4_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1316 "dhcp4_parser.cc"
    break;

  case 140:
#line 604 "dhcp4_parser.yy"
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1326 "dhcp4_parser.cc"
    break;

  case 162:
#line 635 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.DATABASE_TYPE);
}
#line 1334 "dhcp4_parser.cc"
    break;

  case 163:
#line 637 "dhcp4_parser.yy"
    {
    ctx.stack_.back()->set("type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1343 "dhcp4_parser.cc"
    break;

  case 164:
#line 642 "dhcp4_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("memfile", ctx.loc2pos(yystack_[0].location))); }
#line 1349 "dhcp4_parser.cc"
    break;

  case 165:
#line 643 "dhcp4_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("mysql", ctx.loc2pos(yystack_[0].location))); }
#line 1355 "dhcp4_parser.cc"
    break;

  case 166:
#line 644 "dhcp4_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("postgresql", ctx.loc2pos(yystack_[0].location))); }
#line 1361 "dhcp4_parser.cc"
    break;

  case 167:
#line 645 "dhcp4_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("cql", ctx.loc2pos(yystack_[0].location))); }
#line 1367 "dhcp4_parser.cc"
    break;

  case 168:
#line 648 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1375 "dhcp4_parser.cc"
    break;

  case 169:
#line 650 "dhcp4_parser.yy"
    {
    ElementPtr user(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1385 "dhcp4_parser.cc"
    break;

  case 170:
#line 656 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1393 "dhcp4_parser.cc"
    break;

  case 171:
#line 658 "dhcp4_parser.yy"
    {
    ElementPtr pwd(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 1403 "dhcp4_parser.cc"
    break;

  case 172:
#line 664 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1411 "dhcp4_parser.cc"
    break;

  case 173:
#line 666 "dhcp4_parser.yy"
    {
    ElementPtr h(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 1421 "dhcp4_parser.cc"
    break;

  case 174:
#line 672 "dhcp4_parser.yy"
    {
    ElementPtr p(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", p);
}
#line 1430 "dhcp4_parser.cc"
    break;

  case 175:
#line 677 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1438 "dhcp4_parser.cc"
    break;

  case 176:
#line 679 "dhcp4_parser.yy"
    {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1448 "dhcp4_parser.cc"
    break;

  case 177:
#line 685 "dhcp4_parser.yy"
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 1457 "dhcp4_parser.cc"
    break;

  case 178:
#line 690 "dhcp4_parser.yy"
    {
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 1466 "dhcp4_parser.cc"
    break;

  case 179:
#line 695 "dhcp4_parser.yy"
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 1475 "dhcp4_parser.cc"
    break;

  case 180:
#line 700 "dhcp4_parser.yy"
    {
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("connect-timeout", n);
}
#line 1484 "dhcp4_parser.cc"
    break;

  case 181:
#line 705 "dhcp4_parser.yy"
    {
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("request-timeout", n);
}
#line 1493 "dhcp4_parser.cc"
    break;

  case 182:
#line 710 "dhcp4_parser.yy"
    {
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-keepalive", n);
}
#line 1502 "dhcp4_parser.cc"
    break;

  case 183:
#line 715 "dhcp4_parser.yy"
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-nodelay", n);
}
#line 1511 "dhcp4_parser.cc"
    break;

  case 184:
#line 720 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1519 "dhcp4_parser.cc"
    break;

  case 185:
#line 722 "dhcp4_parser.yy"
    {
    ElementPtr cp(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("contact-points", cp);
    ctx.leave();
}
#line 1529 "dhcp4_parser.cc"
    break;

  case 186:
#line 728 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1537 "dhcp4_parser.cc"
    break;

  case 187:
#line 730 "dhcp4_parser.yy"
    {
    ElementPtr ks(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("keyspace", ks);
    ctx.leave();
}
#line 1547 "dhcp4_parser.cc"
    break;

  case 188:
#line 736 "dhcp4_parser.yy"
    {
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reconnect-tries", n);
}
#line 1556 "dhcp4_parser.cc"
    break;

  case 189:
#line 741 "dhcp4_parser.yy"
    {
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reconnect-wait-time", n);
}
#line 1565 "dhcp4_parser.cc"
    break;

  case 190:
#line 746 "dhcp4_parser.yy"
    {
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-row-errors", n);
}
#line 1574 "dhcp4_parser.cc"
    break;

  case 191:
#line 751 "dhcp4_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 1585 "dhcp4_parser.cc"
    break;

  case 192:
#line 756 "dhcp4_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1594 "dhcp4_parser.cc"
    break;

  case 200:
#line 772 "dhcp4_parser.yy"
    {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1603 "dhcp4_parser.cc"
    break;

  case 201:
#line 777 "dhcp4_parser.yy"
    {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 1612 "dhcp4_parser.cc"
    break;

  case 202:
#line 782 "dhcp4_parser.yy"
    {
    ElementPtr circuit(new StringElement("circuit-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(circuit);
}
#line 1621 "dhcp4_parser.cc"
    break;

  case 203:
#line 787 "dhcp4_parser.yy"
    {
    ElementPtr client(new StringElement("client-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(client);
}
#line 1630 "dhcp4_parser.cc"
    break;

  case 204:
#line 792 "dhcp4_parser.yy"
    {
    ElementPtr flex_id(new StringElement("flex-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(flex_id);
}
#line 1639 "dhcp4_parser.cc"
    break;

  case 205:
#line 797 "dhcp4_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 1650 "dhcp4_parser.cc"
    break;

  case 206:
#line 802 "dhcp4_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1659 "dhcp4_parser.cc"
    break;

  case 211:
#line 815 "dhcp4_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1669 "dhcp4_parser.cc"
    break;

  case 212:
#line 819 "dhcp4_parser.yy"
    {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1679 "dhcp4_parser.cc"
    break;

  case 213:
#line 825 "dhcp4_parser.yy"
    {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1689 "dhcp4_parser.cc"
    break;

  case 214:
#line 829 "dhcp4_parser.yy"
    {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 1699 "dhcp4_parser.cc"
    break;

  case 220:
#line 844 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1707 "dhcp4_parser.cc"
    break;

  case 221:
#line 846 "dhcp4_parser.yy"
    {
    ElementPtr lib(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 1717 "dhcp4_parser.cc"
    break;

  case 222:
#line 852 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1725 "dhcp4_parser.cc"
    break;

  case 223:
#line 854 "dhcp4_parser.yy"
    {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1734 "dhcp4_parser.cc"
    break;

  case 224:
#line 860 "dhcp4_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.EXPIRED_LEASES_PROCESSING);
}
#line 1745 "dhcp4_parser.cc"
    break;

  case 225:
#line 865 "dhcp4_parser.yy"
    {
    // No expired lease parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1755 "dhcp4_parser.cc"
    break;

  case 234:
#line 883 "dhcp4_parser.yy"
    {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 1764 "dhcp4_parser.cc"
    break;

  case 235:
#line 888 "dhcp4_parser.yy"
    {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 1773 "dhcp4_parser.cc"
    break;

  case 236:
#line 893 "dhcp4_parser.yy"
    {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 1782 "dhcp4_parser.cc"
    break;

  case 237:
#line 898 "dhcp4_parser.yy"
    {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 1791 "dhcp4_parser.cc"
    break;

  case 238:
#line 903 "dhcp4_parser.yy"
    {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 1800 "dhcp4_parser.cc"
    break;

  case 239:
#line 908 "dhcp4_parser.yy"
    {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 1809 "dhcp4_parser.cc"
    break;

  case 240:
#line 916 "dhcp4_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet4", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET4);
}
#line 1820 "dhcp4_parser.cc"
    break;

  case 241:
#line 921 "dhcp4_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1829 "dhcp4_parser.cc"
    break;

  case 246:
#line 941 "dhcp4_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1839 "dhcp4_parser.cc"
    break;

  case 247:
#line 945 "dhcp4_parser.yy"
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
#line 1865 "dhcp4_parser.cc"
    break;

  case 248:
#line 967 "dhcp4_parser.yy"
    {
    // Parse the subnet4 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1875 "dhcp4_parser.cc"
    break;

  case 249:
#line 971 "dhcp4_parser.yy"
    {
    // The subnet subnet4 parameter is required
    ctx.require("subnet", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 1885 "dhcp4_parser.cc"
    break;

  case 277:
#line 1010 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1893 "dhcp4_parser.cc"
    break;

  case 278:
#line 1012 "dhcp4_parser.yy"
    {
    ElementPtr subnet(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 1903 "dhcp4_parser.cc"
    break;

  case 279:
#line 1018 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1911 "dhcp4_parser.cc"
    break;

  case 280:
#line 1020 "dhcp4_parser.yy"
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface", iface);
    ctx.leave();
}
#line 1921 "dhcp4_parser.cc"
    break;

  case 281:
#line 1026 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1929 "dhcp4_parser.cc"
    break;

  case 282:
#line 1028 "dhcp4_parser.yy"
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface-id", iface);
    ctx.leave();
}
#line 1939 "dhcp4_parser.cc"
    break;

  case 283:
#line 1034 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1947 "dhcp4_parser.cc"
    break;

  case 284:
#line 1036 "dhcp4_parser.yy"
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-subnet", iface);
    ctx.leave();
}
#line 1957 "dhcp4_parser.cc"
    break;

  case 285:
#line 1042 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1965 "dhcp4_parser.cc"
    break;

  case 286:
#line 1044 "dhcp4_parser.yy"
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 1975 "dhcp4_parser.cc"
    break;

  case 287:
#line 1050 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1983 "dhcp4_parser.cc"
    break;

  case 288:
#line 1052 "dhcp4_parser.yy"
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface-id", iface);
    ctx.leave();
}
#line 1993 "dhcp4_parser.cc"
    break;

  case 289:
#line 1058 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2001 "dhcp4_parser.cc"
    break;

  case 290:
#line 1060 "dhcp4_parser.yy"
    {
    ElementPtr cls(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 2011 "dhcp4_parser.cc"
    break;

  case 291:
#line 1066 "dhcp4_parser.yy"
    {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("require-client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2022 "dhcp4_parser.cc"
    break;

  case 292:
#line 1071 "dhcp4_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2031 "dhcp4_parser.cc"
    break;

  case 293:
#line 1076 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.RESERVATION_MODE);
}
#line 2039 "dhcp4_parser.cc"
    break;

  case 294:
#line 1078 "dhcp4_parser.yy"
    {
    ctx.stack_.back()->set("reservation-mode", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2048 "dhcp4_parser.cc"
    break;

  case 295:
#line 1083 "dhcp4_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("disabled", ctx.loc2pos(yystack_[0].location))); }
#line 2054 "dhcp4_parser.cc"
    break;

  case 296:
#line 1084 "dhcp4_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("out-of-pool", ctx.loc2pos(yystack_[0].location))); }
#line 2060 "dhcp4_parser.cc"
    break;

  case 297:
#line 1085 "dhcp4_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("all", ctx.loc2pos(yystack_[0].location))); }
#line 2066 "dhcp4_parser.cc"
    break;

  case 298:
#line 1088 "dhcp4_parser.yy"
    {
    ElementPtr id(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 2075 "dhcp4_parser.cc"
    break;

  case 299:
#line 1093 "dhcp4_parser.yy"
    {
    ElementPtr rc(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rapid-commit", rc);
}
#line 2084 "dhcp4_parser.cc"
    break;

  case 300:
#line 1100 "dhcp4_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("shared-networks", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SHARED_NETWORK);
}
#line 2095 "dhcp4_parser.cc"
    break;

  case 301:
#line 1105 "dhcp4_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2104 "dhcp4_parser.cc"
    break;

  case 306:
#line 1120 "dhcp4_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2114 "dhcp4_parser.cc"
    break;

  case 307:
#line 1124 "dhcp4_parser.yy"
    {
    ctx.stack_.pop_back();
}
#line 2122 "dhcp4_parser.cc"
    break;

  case 328:
#line 1156 "dhcp4_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 2133 "dhcp4_parser.cc"
    break;

  case 329:
#line 1161 "dhcp4_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2142 "dhcp4_parser.cc"
    break;

  case 330:
#line 1169 "dhcp4_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2151 "dhcp4_parser.cc"
    break;

  case 331:
#line 1172 "dhcp4_parser.yy"
    {
    // parsing completed
}
#line 2159 "dhcp4_parser.cc"
    break;

  case 336:
#line 1188 "dhcp4_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2169 "dhcp4_parser.cc"
    break;

  case 337:
#line 1192 "dhcp4_parser.yy"
    {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2181 "dhcp4_parser.cc"
    break;

  case 338:
#line 1203 "dhcp4_parser.yy"
    {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2191 "dhcp4_parser.cc"
    break;

  case 339:
#line 1207 "dhcp4_parser.yy"
    {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2203 "dhcp4_parser.cc"
    break;

  case 355:
#line 1239 "dhcp4_parser.yy"
    {
    ElementPtr code(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 2212 "dhcp4_parser.cc"
    break;

  case 357:
#line 1246 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2220 "dhcp4_parser.cc"
    break;

  case 358:
#line 1248 "dhcp4_parser.yy"
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 2230 "dhcp4_parser.cc"
    break;

  case 359:
#line 1254 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2238 "dhcp4_parser.cc"
    break;

  case 360:
#line 1256 "dhcp4_parser.yy"
    {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 2248 "dhcp4_parser.cc"
    break;

  case 361:
#line 1262 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2256 "dhcp4_parser.cc"
    break;

  case 362:
#line 1264 "dhcp4_parser.yy"
    {
    ElementPtr space(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 2266 "dhcp4_parser.cc"
    break;

  case 364:
#line 1272 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2274 "dhcp4_parser.cc"
    break;

  case 365:
#line 1274 "dhcp4_parser.yy"
    {
    ElementPtr encap(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 2284 "dhcp4_parser.cc"
    break;

  case 366:
#line 1280 "dhcp4_parser.yy"
    {
    ElementPtr array(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 2293 "dhcp4_parser.cc"
    break;

  case 367:
#line 1289 "dhcp4_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 2304 "dhcp4_parser.cc"
    break;

  case 368:
#line 1294 "dhcp4_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2313 "dhcp4_parser.cc"
    break;

  case 373:
#line 1313 "dhcp4_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2323 "dhcp4_parser.cc"
    break;

  case 374:
#line 1317 "dhcp4_parser.yy"
    {
    /// @todo: the code or name parameters are required.
    ctx.stack_.pop_back();
}
#line 2332 "dhcp4_parser.cc"
    break;

  case 375:
#line 1325 "dhcp4_parser.yy"
    {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2342 "dhcp4_parser.cc"
    break;

  case 376:
#line 1329 "dhcp4_parser.yy"
    {
    /// @todo: the code or name parameters are required.
    // parsing completed
}
#line 2351 "dhcp4_parser.cc"
    break;

  case 391:
#line 1362 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2359 "dhcp4_parser.cc"
    break;

  case 392:
#line 1364 "dhcp4_parser.yy"
    {
    ElementPtr data(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 2369 "dhcp4_parser.cc"
    break;

  case 395:
#line 1374 "dhcp4_parser.yy"
    {
    ElementPtr space(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", space);
}
#line 2378 "dhcp4_parser.cc"
    break;

  case 396:
#line 1379 "dhcp4_parser.yy"
    {
    ElementPtr persist(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-send", persist);
}
#line 2387 "dhcp4_parser.cc"
    break;

  case 397:
#line 1387 "dhcp4_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 2398 "dhcp4_parser.cc"
    break;

  case 398:
#line 1392 "dhcp4_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2407 "dhcp4_parser.cc"
    break;

  case 403:
#line 1407 "dhcp4_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2417 "dhcp4_parser.cc"
    break;

  case 404:
#line 1411 "dhcp4_parser.yy"
    {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2427 "dhcp4_parser.cc"
    break;

  case 405:
#line 1417 "dhcp4_parser.yy"
    {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2437 "dhcp4_parser.cc"
    break;

  case 406:
#line 1421 "dhcp4_parser.yy"
    {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2447 "dhcp4_parser.cc"
    break;

  case 416:
#line 1440 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2455 "dhcp4_parser.cc"
    break;

  case 417:
#line 1442 "dhcp4_parser.yy"
    {
    ElementPtr pool(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 2465 "dhcp4_parser.cc"
    break;

  case 418:
#line 1448 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2473 "dhcp4_parser.cc"
    break;

  case 419:
#line 1450 "dhcp4_parser.yy"
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
#line 2500 "dhcp4_parser.cc"
    break;

  case 420:
#line 1473 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2508 "dhcp4_parser.cc"
    break;

  case 421:
#line 1475 "dhcp4_parser.yy"
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
#line 2537 "dhcp4_parser.cc"
    break;

  case 422:
#line 1503 "dhcp4_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 2548 "dhcp4_parser.cc"
    break;

  case 423:
#line 1508 "dhcp4_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2557 "dhcp4_parser.cc"
    break;

  case 428:
#line 1521 "dhcp4_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2567 "dhcp4_parser.cc"
    break;

  case 429:
#line 1525 "dhcp4_parser.yy"
    {
    /// @todo: an identifier parameter is required.
    ctx.stack_.pop_back();
}
#line 2576 "dhcp4_parser.cc"
    break;

  case 430:
#line 1530 "dhcp4_parser.yy"
    {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2586 "dhcp4_parser.cc"
    break;

  case 431:
#line 1534 "dhcp4_parser.yy"
    {
    /// @todo: an identifier parameter is required.
    // parsing completed
}
#line 2595 "dhcp4_parser.cc"
    break;

  case 451:
#line 1565 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2603 "dhcp4_parser.cc"
    break;

  case 452:
#line 1567 "dhcp4_parser.yy"
    {
    ElementPtr next_server(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("next-server", next_server);
    ctx.leave();
}
#line 2613 "dhcp4_parser.cc"
    break;

  case 453:
#line 1573 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2621 "dhcp4_parser.cc"
    break;

  case 454:
#line 1575 "dhcp4_parser.yy"
    {
    ElementPtr srv(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-hostname", srv);
    ctx.leave();
}
#line 2631 "dhcp4_parser.cc"
    break;

  case 455:
#line 1581 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2639 "dhcp4_parser.cc"
    break;

  case 456:
#line 1583 "dhcp4_parser.yy"
    {
    ElementPtr bootfile(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("boot-file-name", bootfile);
    ctx.leave();
}
#line 2649 "dhcp4_parser.cc"
    break;

  case 457:
#line 1589 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2657 "dhcp4_parser.cc"
    break;

  case 458:
#line 1591 "dhcp4_parser.yy"
    {
    ElementPtr addr(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", addr);
    ctx.leave();
}
#line 2667 "dhcp4_parser.cc"
    break;

  case 459:
#line 1597 "dhcp4_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-addresses", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2678 "dhcp4_parser.cc"
    break;

  case 460:
#line 1602 "dhcp4_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2687 "dhcp4_parser.cc"
    break;

  case 461:
#line 1607 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2695 "dhcp4_parser.cc"
    break;

  case 462:
#line 1609 "dhcp4_parser.yy"
    {
    ElementPtr d(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 2705 "dhcp4_parser.cc"
    break;

  case 463:
#line 1615 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2713 "dhcp4_parser.cc"
    break;

  case 464:
#line 1617 "dhcp4_parser.yy"
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 2723 "dhcp4_parser.cc"
    break;

  case 465:
#line 1623 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2731 "dhcp4_parser.cc"
    break;

  case 466:
#line 1625 "dhcp4_parser.yy"
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-id", hw);
    ctx.leave();
}
#line 2741 "dhcp4_parser.cc"
    break;

  case 467:
#line 1631 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2749 "dhcp4_parser.cc"
    break;

  case 468:
#line 1633 "dhcp4_parser.yy"
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("circuit-id", hw);
    ctx.leave();
}
#line 2759 "dhcp4_parser.cc"
    break;

  case 469:
#line 1639 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2767 "dhcp4_parser.cc"
    break;

  case 470:
#line 1641 "dhcp4_parser.yy"
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flex-id", hw);
    ctx.leave();
}
#line 2777 "dhcp4_parser.cc"
    break;

  case 471:
#line 1647 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2785 "dhcp4_parser.cc"
    break;

  case 472:
#line 1649 "dhcp4_parser.yy"
    {
    ElementPtr host(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 2795 "dhcp4_parser.cc"
    break;

  case 473:
#line 1655 "dhcp4_parser.yy"
    {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2806 "dhcp4_parser.cc"
    break;

  case 474:
#line 1660 "dhcp4_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2815 "dhcp4_parser.cc"
    break;

  case 475:
#line 1668 "dhcp4_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 2826 "dhcp4_parser.cc"
    break;

  case 476:
#line 1673 "dhcp4_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2835 "dhcp4_parser.cc"
    break;

  case 479:
#line 1685 "dhcp4_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 2846 "dhcp4_parser.cc"
    break;

  case 480:
#line 1690 "dhcp4_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2855 "dhcp4_parser.cc"
    break;

  case 483:
#line 1699 "dhcp4_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2865 "dhcp4_parser.cc"
    break;

  case 484:
#line 1703 "dhcp4_parser.yy"
    {
    // The name client class parameter is required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2875 "dhcp4_parser.cc"
    break;

  case 501:
#line 1732 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2883 "dhcp4_parser.cc"
    break;

  case 502:
#line 1734 "dhcp4_parser.yy"
    {
    ElementPtr test(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 2893 "dhcp4_parser.cc"
    break;

  case 503:
#line 1740 "dhcp4_parser.yy"
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("only-if-required", b);
}
#line 2902 "dhcp4_parser.cc"
    break;

  case 504:
#line 1749 "dhcp4_parser.yy"
    {
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 2911 "dhcp4_parser.cc"
    break;

  case 505:
#line 1756 "dhcp4_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 2922 "dhcp4_parser.cc"
    break;

  case 506:
#line 1761 "dhcp4_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2931 "dhcp4_parser.cc"
    break;

  case 514:
#line 1777 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2939 "dhcp4_parser.cc"
    break;

  case 515:
#line 1779 "dhcp4_parser.yy"
    {
    ElementPtr stype(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 2949 "dhcp4_parser.cc"
    break;

  case 516:
#line 1785 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2957 "dhcp4_parser.cc"
    break;

  case 517:
#line 1787 "dhcp4_parser.yy"
    {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 2967 "dhcp4_parser.cc"
    break;

  case 518:
#line 1795 "dhcp4_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 2978 "dhcp4_parser.cc"
    break;

  case 519:
#line 1800 "dhcp4_parser.yy"
    {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2989 "dhcp4_parser.cc"
    break;

  case 520:
#line 1807 "dhcp4_parser.yy"
    {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2999 "dhcp4_parser.cc"
    break;

  case 521:
#line 1811 "dhcp4_parser.yy"
    {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3009 "dhcp4_parser.cc"
    break;

  case 541:
#line 1840 "dhcp4_parser.yy"
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 3018 "dhcp4_parser.cc"
    break;

  case 542:
#line 1845 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3026 "dhcp4_parser.cc"
    break;

  case 543:
#line 1847 "dhcp4_parser.yy"
    {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("qualifying-suffix", s);
    ctx.leave();
}
#line 3036 "dhcp4_parser.cc"
    break;

  case 544:
#line 1853 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3044 "dhcp4_parser.cc"
    break;

  case 545:
#line 1855 "dhcp4_parser.yy"
    {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 3054 "dhcp4_parser.cc"
    break;

  case 546:
#line 1861 "dhcp4_parser.yy"
    {
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 3063 "dhcp4_parser.cc"
    break;

  case 547:
#line 1866 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3071 "dhcp4_parser.cc"
    break;

  case 548:
#line 1868 "dhcp4_parser.yy"
    {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 3081 "dhcp4_parser.cc"
    break;

  case 549:
#line 1874 "dhcp4_parser.yy"
    {
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 3090 "dhcp4_parser.cc"
    break;

  case 550:
#line 1879 "dhcp4_parser.yy"
    {
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 3099 "dhcp4_parser.cc"
    break;

  case 551:
#line 1884 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 3107 "dhcp4_parser.cc"
    break;

  case 552:
#line 1886 "dhcp4_parser.yy"
    {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3116 "dhcp4_parser.cc"
    break;

  case 553:
#line 1892 "dhcp4_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 3122 "dhcp4_parser.cc"
    break;

  case 554:
#line 1893 "dhcp4_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 3128 "dhcp4_parser.cc"
    break;

  case 555:
#line 1896 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NCR_FORMAT);
}
#line 3136 "dhcp4_parser.cc"
    break;

  case 556:
#line 1898 "dhcp4_parser.yy"
    {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 3146 "dhcp4_parser.cc"
    break;

  case 557:
#line 1904 "dhcp4_parser.yy"
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-include-fqdn", b);
}
#line 3155 "dhcp4_parser.cc"
    break;

  case 558:
#line 1909 "dhcp4_parser.yy"
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-no-update", b);
}
#line 3164 "dhcp4_parser.cc"
    break;

  case 559:
#line 1914 "dhcp4_parser.yy"
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-client-update", b);
}
#line 3173 "dhcp4_parser.cc"
    break;

  case 560:
#line 1919 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 3181 "dhcp4_parser.cc"
    break;

  case 561:
#line 1921 "dhcp4_parser.yy"
    {
    ctx.stack_.back()->set("replace-client-name", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3190 "dhcp4_parser.cc"
    break;

  case 562:
#line 1927 "dhcp4_parser.yy"
    {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("when-present", ctx.loc2pos(yystack_[0].location))); 
      }
#line 3198 "dhcp4_parser.cc"
    break;

  case 563:
#line 1930 "dhcp4_parser.yy"
    {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location)));
      }
#line 3206 "dhcp4_parser.cc"
    break;

  case 564:
#line 1933 "dhcp4_parser.yy"
    {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("always", ctx.loc2pos(yystack_[0].location)));
      }
#line 3214 "dhcp4_parser.cc"
    break;

  case 565:
#line 1936 "dhcp4_parser.yy"
    {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("when-not-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 3222 "dhcp4_parser.cc"
    break;

  case 566:
#line 1939 "dhcp4_parser.yy"
    {
      error(yystack_[0].location, "boolean values for the replace-client-name are "
                "no longer supported");
      }
#line 3231 "dhcp4_parser.cc"
    break;

  case 567:
#line 1945 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3239 "dhcp4_parser.cc"
    break;

  case 568:
#line 1947 "dhcp4_parser.yy"
    {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("generated-prefix", s);
    ctx.leave();
}
#line 3249 "dhcp4_parser.cc"
    break;

  case 569:
#line 1955 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3257 "dhcp4_parser.cc"
    break;

  case 570:
#line 1957 "dhcp4_parser.yy"
    {
    ctx.stack_.back()->set("Dhcp6", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3266 "dhcp4_parser.cc"
    break;

  case 571:
#line 1962 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3274 "dhcp4_parser.cc"
    break;

  case 572:
#line 1964 "dhcp4_parser.yy"
    {
    ctx.stack_.back()->set("DhcpDdns", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3283 "dhcp4_parser.cc"
    break;

  case 573:
#line 1969 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3291 "dhcp4_parser.cc"
    break;

  case 574:
#line 1971 "dhcp4_parser.yy"
    {
    ctx.stack_.back()->set("Control-agent", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3300 "dhcp4_parser.cc"
    break;

  case 575:
#line 1981 "dhcp4_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Logging", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.LOGGING);
}
#line 3311 "dhcp4_parser.cc"
    break;

  case 576:
#line 1986 "dhcp4_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3320 "dhcp4_parser.cc"
    break;

  case 577:
#line 1991 "dhcp4_parser.yy"
    {
    // Parse the Logging map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3330 "dhcp4_parser.cc"
    break;

  case 578:
#line 1995 "dhcp4_parser.yy"
    {
    // parsing completed
}
#line 3338 "dhcp4_parser.cc"
    break;

  case 582:
#line 2011 "dhcp4_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 3349 "dhcp4_parser.cc"
    break;

  case 583:
#line 2016 "dhcp4_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3358 "dhcp4_parser.cc"
    break;

  case 586:
#line 2028 "dhcp4_parser.yy"
    {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 3368 "dhcp4_parser.cc"
    break;

  case 587:
#line 2032 "dhcp4_parser.yy"
    {
    ctx.stack_.pop_back();
}
#line 3376 "dhcp4_parser.cc"
    break;

  case 597:
#line 2049 "dhcp4_parser.yy"
    {
    ElementPtr dl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 3385 "dhcp4_parser.cc"
    break;

  case 598:
#line 2054 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3393 "dhcp4_parser.cc"
    break;

  case 599:
#line 2056 "dhcp4_parser.yy"
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 3403 "dhcp4_parser.cc"
    break;

  case 600:
#line 2062 "dhcp4_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 3414 "dhcp4_parser.cc"
    break;

  case 601:
#line 2067 "dhcp4_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3423 "dhcp4_parser.cc"
    break;

  case 604:
#line 2076 "dhcp4_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3433 "dhcp4_parser.cc"
    break;

  case 605:
#line 2080 "dhcp4_parser.yy"
    {
    ctx.stack_.pop_back();
}
#line 3441 "dhcp4_parser.cc"
    break;

  case 612:
#line 2094 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3449 "dhcp4_parser.cc"
    break;

  case 613:
#line 2096 "dhcp4_parser.yy"
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 3459 "dhcp4_parser.cc"
    break;

  case 614:
#line 2102 "dhcp4_parser.yy"
    {
    ElementPtr flush(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 3468 "dhcp4_parser.cc"
    break;

  case 615:
#line 2107 "dhcp4_parser.yy"
    {
    ElementPtr maxsize(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 3477 "dhcp4_parser.cc"
    break;

  case 616:
#line 2112 "dhcp4_parser.yy"
    {
    ElementPtr maxver(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 3486 "dhcp4_parser.cc"
    break;


#line 3490 "dhcp4_parser.cc"

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


  const short Dhcp4Parser::yypact_ninf_ = -755;

  const signed char Dhcp4Parser::yytable_ninf_ = -1;

  const short
  Dhcp4Parser::yypact_[] =
  {
     274,  -755,  -755,  -755,  -755,  -755,  -755,  -755,  -755,  -755,
    -755,  -755,  -755,  -755,    33,    22,    54,    56,    66,    70,
      82,    92,   152,   162,   179,   220,   224,   230,  -755,  -755,
    -755,  -755,  -755,  -755,  -755,  -755,  -755,  -755,  -755,  -755,
    -755,  -755,  -755,  -755,  -755,  -755,  -755,  -755,  -755,  -755,
    -755,  -755,  -755,  -755,  -755,  -755,  -755,  -755,  -755,  -755,
    -755,  -755,  -755,  -755,    22,   -83,    20,    59,    43,   174,
      35,   415,    93,    29,   143,    -2,   163,    55,  -755,   186,
     250,   268,   263,   270,  -755,  -755,  -755,  -755,  -755,   299,
    -755,    45,  -755,  -755,  -755,  -755,  -755,  -755,  -755,   306,
     312,  -755,  -755,  -755,  -755,  -755,  -755,   313,   314,   315,
     318,  -755,  -755,  -755,  -755,  -755,  -755,  -755,  -755,  -755,
    -755,   319,  -755,  -755,  -755,    46,  -755,  -755,  -755,  -755,
    -755,  -755,  -755,  -755,  -755,  -755,  -755,  -755,  -755,  -755,
    -755,  -755,  -755,  -755,  -755,  -755,  -755,  -755,  -755,  -755,
    -755,  -755,  -755,  -755,  -755,  -755,   321,  -755,    61,  -755,
    -755,  -755,  -755,  -755,  -755,  -755,  -755,  -755,  -755,  -755,
    -755,  -755,  -755,   322,   324,  -755,  -755,  -755,  -755,  -755,
    -755,  -755,  -755,  -755,  -755,    68,  -755,  -755,  -755,  -755,
    -755,  -755,  -755,  -755,  -755,  -755,  -755,  -755,  -755,  -755,
    -755,  -755,  -755,  -755,  -755,  -755,  -755,  -755,  -755,  -755,
    -755,  -755,    84,  -755,  -755,  -755,  -755,  -755,  -755,  -755,
    -755,  -755,  -755,  -755,  -755,  -755,  -755,  -755,  -755,   323,
     304,  -755,  -755,  -755,  -755,  -755,  -755,  -755,  -755,  -755,
    -755,  -755,  -755,   325,  -755,  -755,   326,  -755,  -755,  -755,
     330,  -755,  -755,   327,   334,  -755,  -755,  -755,  -755,  -755,
    -755,  -755,  -755,  -755,  -755,  -755,  -755,  -755,   337,   338,
    -755,  -755,  -755,  -755,   335,   342,  -755,  -755,  -755,  -755,
    -755,  -755,  -755,  -755,  -755,  -755,  -755,  -755,   110,  -755,
    -755,  -755,   343,  -755,  -755,   345,  -755,   348,   350,  -755,
    -755,   351,   357,   358,  -755,  -755,  -755,  -755,  -755,   125,
    -755,  -755,  -755,  -755,  -755,  -755,  -755,  -755,  -755,  -755,
    -755,  -755,  -755,  -755,  -755,  -755,   137,  -755,  -755,  -755,
      22,    22,  -755,   171,   362,   364,   365,   367,   369,  -755,
      20,  -755,   370,   214,   215,   373,   378,   379,   382,   385,
     387,   187,   235,   236,   237,   396,   398,   399,   401,   402,
     407,   408,   409,   428,   429,   239,   430,   431,    59,  -755,
     432,   436,   437,   281,    43,  -755,   442,   444,   445,   446,
     447,   450,   451,   298,   295,   454,   455,   456,   457,   458,
     174,  -755,   459,    35,  -755,   460,   463,   465,   466,   467,
     470,   471,   472,  -755,   415,  -755,   475,   476,   329,   480,
     481,   486,   331,  -755,    29,   487,   332,   336,  -755,   143,
     491,   492,    21,  -755,   374,   495,   499,   372,   530,   377,
     380,   533,   534,   381,   383,   384,   536,   539,   163,  -755,
     542,    55,  -755,  -755,  -755,   543,   541,   544,    22,    22,
      22,  -755,   546,  -755,  -755,   391,   392,   397,   547,   549,
     552,  -755,  -755,  -755,  -755,   553,   554,   555,   556,   557,
     404,   558,   560,   561,   562,  -755,   563,   564,  -755,   567,
     185,   191,  -755,  -755,   410,   416,   417,   571,   419,   420,
     421,  -755,  -755,   139,   567,   422,   576,   575,  -755,   425,
    -755,   567,   426,   427,   433,   434,   435,   438,   439,  -755,
     440,   441,  -755,   443,   448,   449,  -755,  -755,   452,  -755,
    -755,  -755,   453,    22,  -755,  -755,   461,   462,  -755,   464,
    -755,  -755,    17,   474,  -755,  -755,  -755,    -6,   468,  -755,
     581,  -755,    22,    59,    55,  -755,  -755,  -755,    43,  -755,
    -755,  -755,   482,   482,   580,   582,   583,   587,   588,  -755,
    -755,  -755,   150,   593,   596,   161,    64,   163,  -755,  -755,
    -755,  -755,  -755,  -755,  -755,  -755,  -755,  -755,  -755,   597,
    -755,  -755,  -755,  -755,  -755,  -755,  -755,  -755,  -755,   598,
     160,  -755,  -755,  -755,  -755,  -755,  -755,  -755,  -755,  -755,
    -755,  -755,  -755,  -755,  -755,  -755,  -755,  -755,  -755,  -755,
    -755,  -755,  -755,  -755,  -755,  -755,  -755,  -755,  -755,  -755,
    -755,  -755,   601,  -755,   140,   146,   169,  -755,  -755,  -755,
    -755,   584,   605,   608,   609,   610,  -755,  -755,   611,   612,
     613,   614,   617,   619,  -755,   176,  -755,  -755,  -755,  -755,
    -755,  -755,  -755,  -755,  -755,  -755,  -755,  -755,  -755,  -755,
    -755,  -755,  -755,  -755,  -755,   182,  -755,   618,   622,  -755,
    -755,   621,   625,  -755,  -755,   623,   627,  -755,  -755,   626,
     628,  -755,  -755,   629,   630,  -755,  -755,  -755,  -755,  -755,
    -755,    44,  -755,  -755,  -755,  -755,  -755,  -755,  -755,   126,
    -755,  -755,   631,   633,  -755,   634,   635,   637,   638,   639,
     640,   208,  -755,  -755,  -755,  -755,  -755,  -755,  -755,  -755,
    -755,  -755,  -755,  -755,   218,  -755,  -755,  -755,   251,   488,
    -755,   641,   642,  -755,  -755,   643,   645,  -755,  -755,  -755,
    -755,   559,  -755,   155,  -755,  -755,  -755,  -755,   646,   647,
     648,   649,   496,   473,   497,   493,   498,   654,   655,   501,
     502,   503,   504,   505,   506,   482,  -755,  -755,   482,  -755,
     580,   174,  -755,   582,    29,  -755,   583,   143,  -755,   587,
     394,  -755,   588,   150,  -755,    80,   593,  -755,    -2,  -755,
     596,   508,   509,   510,   511,   512,   513,   161,  -755,   660,
     669,    64,  -755,  -755,  -755,   668,   672,    35,  -755,   597,
     415,  -755,   598,   673,  -755,    75,   601,  -755,   283,   518,
     520,   521,  -755,  -755,  -755,  -755,  -755,   522,   523,  -755,
    -755,  -755,  -755,  -755,  -755,  -755,   252,  -755,   267,  -755,
     674,  -755,   675,  -755,  -755,  -755,  -755,  -755,  -755,  -755,
    -755,  -755,  -755,  -755,  -755,   290,  -755,  -755,  -755,  -755,
    -755,  -755,  -755,  -755,  -755,  -755,  -755,   680,  -755,  -755,
    -755,  -755,  -755,  -755,  -755,  -755,  -755,   677,   683,  -755,
    -755,  -755,  -755,  -755,   291,  -755,  -755,  -755,  -755,  -755,
    -755,  -755,  -755,   529,   531,  -755,  -755,   532,   297,  -755,
     684,  -755,   567,  -755,   687,  -755,  -755,  -755,  -755,  -755,
     301,  -755,  -755,  -755,  -755,  -755,  -755,  -755,  -755,  -755,
    -755,  -755,  -755,  -755,  -755,  -755,  -755,  -755,  -755,  -755,
     394,  -755,   689,   527,  -755,    80,  -755,  -755,  -755,  -755,
    -755,  -755,  -755,   690,   537,   691,    75,  -755,  -755,   540,
    -755,  -755,   692,  -755,   545,  -755,  -755,   693,  -755,  -755,
     167,  -755,   156,   693,  -755,  -755,   695,   697,   698,   303,
    -755,  -755,  -755,  -755,  -755,  -755,   700,   548,   551,   568,
     156,  -755,   570,  -755,  -755,  -755,  -755,  -755
  };

  const unsigned short
  Dhcp4Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,    24,    26,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     1,    43,
      36,    32,    31,    28,    29,    30,    35,     3,    33,    34,
      56,     5,    68,     7,   116,     9,   248,    11,   405,    13,
     430,    15,   330,    17,   338,    19,   375,    21,   213,    23,
     520,    25,   577,    27,    45,    39,     0,     0,     0,     0,
       0,   432,     0,   340,   377,     0,     0,     0,    47,     0,
      46,     0,     0,    40,    66,   575,   569,   571,   573,     0,
      65,     0,    58,    60,    62,    63,    64,    61,   105,     0,
       0,   451,   453,   455,   129,   131,   133,     0,     0,     0,
       0,   240,   328,   367,   300,   418,   420,   191,   479,   205,
     224,     0,   505,   518,    98,     0,    70,    72,    73,    74,
      75,    91,    92,    78,    79,    80,    81,    82,    86,    87,
      76,    77,    84,    85,    96,    97,    93,    94,    95,    83,
      88,    89,    90,   118,   120,   124,     0,   115,     0,   107,
     109,   110,   111,   112,   113,   114,   279,   281,   283,   397,
     277,   285,   287,     0,     0,   293,   291,   289,   422,   475,
     276,   252,   253,   254,   267,     0,   250,   257,   271,   272,
     273,   258,   259,   262,   263,   265,   260,   261,   255,   256,
     274,   275,   264,   268,   269,   270,   266,   416,   415,   411,
     412,   410,     0,   407,   409,   413,   414,   473,   461,   463,
     467,   465,   471,   469,   457,   450,   444,   448,   449,     0,
     433,   434,   445,   446,   447,   441,   436,   442,   438,   439,
     440,   443,   437,     0,   357,   175,     0,   361,   359,   364,
       0,   353,   354,     0,   341,   342,   344,   356,   345,   346,
     347,   363,   348,   349,   350,   351,   352,   391,     0,     0,
     389,   390,   393,   394,     0,   378,   379,   381,   382,   383,
     384,   385,   386,   387,   388,   220,   222,   217,     0,   215,
     218,   219,     0,   542,   544,     0,   547,     0,     0,   551,
     555,     0,     0,     0,   560,   567,   540,   538,   539,     0,
     522,   524,   525,   526,   527,   528,   529,   530,   531,   532,
     533,   534,   535,   536,   537,   582,     0,   579,   581,    44,
       0,     0,    37,     0,     0,     0,     0,     0,     0,    55,
       0,    57,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    69,
       0,     0,     0,     0,     0,   117,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   249,     0,     0,   406,     0,     0,     0,     0,     0,
       0,     0,     0,   431,     0,   331,     0,     0,     0,     0,
       0,     0,     0,   339,     0,     0,     0,     0,   376,     0,
       0,     0,     0,   214,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   521,
       0,     0,   578,    48,    41,     0,     0,     0,     0,     0,
       0,    59,     0,   103,   104,     0,     0,     0,     0,     0,
       0,    99,   100,   101,   102,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   504,     0,     0,    71,     0,
       0,     0,   128,   108,     0,     0,     0,     0,     0,     0,
       0,   298,   299,     0,     0,     0,     0,     0,   251,     0,
     408,     0,     0,     0,     0,     0,     0,     0,     0,   435,
       0,     0,   355,     0,     0,     0,   366,   343,     0,   395,
     396,   380,     0,     0,   216,   541,     0,     0,   546,     0,
     549,   550,     0,     0,   557,   558,   559,     0,     0,   523,
       0,   580,     0,     0,     0,   570,   572,   574,     0,   452,
     454,   456,     0,     0,   135,   242,   332,   369,   302,    38,
     419,   421,     0,     0,   207,     0,     0,     0,    49,   119,
     122,   123,   121,   126,   127,   125,   280,   282,   284,   399,
     278,   286,   288,   295,   296,   297,   294,   292,   290,   424,
       0,   417,   474,   462,   464,   468,   466,   472,   470,   458,
     358,   176,   362,   360,   365,   392,   221,   223,   543,   545,
     548,   553,   554,   552,   556,   562,   563,   564,   565,   566,
     561,   568,     0,    42,     0,     0,     0,   162,   168,   170,
     172,     0,     0,     0,     0,     0,   184,   186,     0,     0,
       0,     0,     0,     0,   161,     0,   141,   143,   144,   145,
     146,   147,   148,   149,   150,   151,   152,   156,   157,   158,
     153,   159,   154,   155,   160,     0,   139,     0,   136,   137,
     246,     0,   243,   244,   336,     0,   333,   334,   373,     0,
     370,   371,   306,     0,   303,   304,   200,   201,   202,   203,
     204,     0,   193,   195,   196,   197,   198,   199,   483,     0,
     481,   211,     0,   208,   209,     0,     0,     0,     0,     0,
       0,     0,   226,   228,   229,   230,   231,   232,   233,   514,
     516,   513,   511,   512,     0,   507,   509,   510,     0,    51,
     403,     0,   400,   401,   428,     0,   425,   426,   459,   477,
     478,     0,   586,     0,   584,    67,   576,   106,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   130,   132,     0,   134,
       0,     0,   241,     0,   340,   329,     0,   377,   368,     0,
       0,   301,     0,     0,   192,   485,     0,   480,     0,   206,
       0,     0,     0,     0,     0,     0,     0,     0,   225,     0,
       0,     0,   506,   519,    53,     0,    52,     0,   398,     0,
     432,   423,     0,     0,   476,     0,     0,   583,     0,     0,
       0,     0,   174,   177,   178,   179,   180,     0,     0,   188,
     189,   181,   182,   183,   190,   142,     0,   138,     0,   245,
       0,   335,     0,   372,   327,   324,   313,   314,   316,   310,
     311,   312,   322,   323,   321,     0,   308,   315,   325,   326,
     317,   318,   319,   320,   305,   194,   501,     0,   499,   500,
     492,   493,   497,   498,   494,   495,   496,     0,   486,   487,
     489,   490,   491,   482,     0,   210,   234,   235,   236,   237,
     238,   239,   227,     0,     0,   508,    50,     0,     0,   402,
       0,   427,     0,   600,     0,   598,   596,   590,   594,   595,
       0,   588,   592,   593,   591,   585,   164,   165,   166,   167,
     163,   169,   171,   173,   185,   187,   140,   247,   337,   374,
       0,   307,     0,     0,   484,     0,   212,   515,   517,    54,
     404,   429,   460,     0,     0,     0,     0,   587,   309,     0,
     503,   488,     0,   597,     0,   589,   502,     0,   599,   604,
       0,   602,     0,     0,   601,   612,     0,     0,     0,     0,
     606,   608,   609,   610,   611,   603,     0,     0,     0,     0,
       0,   605,     0,   614,   615,   616,   607,   613
  };

  const short
  Dhcp4Parser::yypgoto_[] =
  {
    -755,  -755,  -755,  -755,  -755,  -755,  -755,  -755,  -755,  -755,
    -755,  -755,  -755,  -755,  -755,   -40,  -755,   238,  -755,  -755,
    -755,  -755,  -755,  -755,  -755,  -755,  -488,  -755,  -755,  -755,
     -66,  -755,  -755,  -755,   366,  -755,  -755,  -755,  -755,   170,
     344,   -23,   -11,    -9,  -755,  -755,     9,  -755,  -755,   168,
     355,  -755,  -755,  -755,  -755,  -755,  -755,  -755,  -755,  -755,
    -755,  -755,  -755,  -755,  -755,  -755,  -755,  -755,  -755,  -755,
     -52,  -755,  -532,   -35,  -755,  -755,  -755,  -755,  -755,  -755,
    -755,  -755,  -755,  -755,   -22,  -755,  -755,  -755,  -755,  -755,
    -755,  -755,  -755,  -755,  -755,  -755,  -755,  -755,  -755,  -755,
    -755,  -755,  -755,   -51,  -755,  -755,  -755,  -755,  -755,  -755,
    -755,  -755,  -755,   -57,  -755,  -755,  -755,   -38,   320,  -755,
    -755,  -755,  -755,  -755,  -755,  -755,   -31,  -755,  -755,  -755,
    -755,  -755,  -755,  -754,  -755,  -755,  -755,   -37,  -755,  -755,
    -755,    -1,   388,  -755,  -755,  -755,  -755,  -755,  -755,  -755,
    -755,  -742,  -755,  -755,  -755,   -42,  -755,    -5,  -755,  -739,
    -755,  -755,  -755,  -755,  -755,  -755,  -755,  -755,   -10,  -755,
    -755,  -151,   -61,  -755,  -755,  -755,  -755,  -755,    10,  -755,
    -755,  -755,    11,  -755,   376,  -755,   -62,  -755,  -755,  -755,
    -755,  -755,   -56,  -755,  -755,  -755,  -755,  -755,    -3,  -755,
    -755,  -755,     8,  -755,  -755,  -755,    14,  -755,   375,  -755,
    -755,  -755,  -755,  -755,  -755,  -755,  -755,  -755,  -755,  -755,
     -17,  -755,  -755,  -755,   -12,   403,  -755,  -755,   -54,  -755,
     -34,  -755,  -755,  -755,  -755,  -755,   -15,  -755,  -755,  -755,
      -7,  -755,   395,   -46,  -755,   -26,  -755,     3,  -755,   210,
    -755,  -755,  -755,  -755,  -755,  -755,  -755,  -755,  -755,  -755,
    -755,  -755,  -755,  -755,  -755,  -755,  -755,  -736,  -755,  -755,
    -755,  -755,  -755,    12,  -755,  -755,  -755,  -134,  -755,  -755,
    -755,  -755,  -755,  -755,  -755,  -755,     4,  -755,  -755,  -755,
    -755,  -755,  -755,  -755,  -755,   241,   368,  -755,  -755,  -755,
    -755,  -755,  -755,  -755,  -755,  -755,  -755,  -755,  -755,  -755,
    -755,  -755,  -755,  -755,  -755,  -755,  -755,  -755,  -755,  -755,
    -755,  -755,  -755,  -755,  -755,  -755,  -755,  -755,  -755,  -755,
     265,   371,  -755,  -755,  -755,     0,  -755,  -755,  -136,  -755,
    -755,  -755,  -755,  -755,  -755,  -152,  -755,  -755,  -166,  -755,
    -755,  -755,  -755,  -755
  };

  const short
  Dhcp4Parser::yydefgoto_[] =
  {
      -1,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    36,    37,    38,    65,   560,
      82,    83,    39,    64,    79,    80,   569,   729,   805,   806,
     644,    41,    66,    91,    92,    93,   334,    43,    67,   125,
     126,   127,   128,   129,   130,   131,   132,   133,   342,   158,
     159,    45,    68,   160,   370,   161,   371,   572,   162,   372,
     575,   163,   134,   348,   135,   349,   136,   350,   667,   668,
     669,   768,   645,   646,   647,   748,   920,   648,   749,   649,
     750,   650,   751,   651,   652,   407,   653,   654,   655,   656,
     657,   658,   659,   660,   757,   661,   758,   662,   663,   664,
     137,   361,   691,   692,   693,   694,   695,   696,   697,   138,
     363,   702,   703,   704,   788,    59,    75,   288,   289,   290,
     420,   291,   421,   139,   364,   711,   712,   713,   714,   715,
     716,   717,   718,   140,   355,   671,   672,   673,   771,    47,
      69,   185,   186,   187,   380,   188,   376,   189,   377,   190,
     378,   191,   381,   192,   382,   193,   387,   194,   386,   195,
     385,   586,   196,   197,   141,   358,   683,   684,   685,   780,
     855,   856,   142,   356,    53,    72,   675,   676,   677,   774,
      55,    73,   253,   254,   255,   256,   257,   258,   259,   406,
     260,   410,   261,   409,   262,   263,   411,   264,   143,   357,
     679,   680,   681,   777,    57,    74,   274,   275,   276,   277,
     278,   415,   279,   280,   281,   282,   199,   379,   731,   732,
     733,   807,    49,    70,   212,   213,   214,   392,   144,   359,
     145,   360,   202,   388,   735,   736,   737,   810,    51,    71,
     229,   230,   231,   146,   345,   147,   346,   148,   347,   235,
     402,   740,   813,   236,   396,   237,   397,   238,   399,   239,
     398,   240,   401,   241,   400,   242,   395,   206,   389,   741,
     149,   362,   699,   700,   785,   877,   878,   879,   880,   881,
     932,   882,   150,   151,   366,   724,   725,   726,   799,   727,
     800,   152,   367,    61,    76,   309,   310,   311,   312,   425,
     313,   426,   314,   315,   428,   316,   317,   318,   431,   613,
     319,   432,   320,   321,   322,   323,   436,   620,   324,   437,
      94,   336,    95,   337,    96,   338,    97,   335,    63,    77,
     326,   327,   328,   440,   743,   744,   815,   910,   911,   912,
     913,   945,   914,   943,   960,   961,   962,   969,   970,   971,
     976,   972,   973,   974
  };

  const unsigned short
  Dhcp4Parser::yytable_[] =
  {
      90,   124,   157,   180,   208,   225,   587,   251,   270,   287,
     306,   243,   272,   592,   164,   200,   215,   227,   273,   265,
     283,   665,   307,   203,    78,   232,   850,    29,   209,    30,
      84,    31,   611,    28,   165,   201,   216,   228,   851,   266,
     284,   854,   308,   204,   863,   233,   181,   783,   340,   368,
     784,   252,   271,   341,   369,   153,   154,   244,   182,   155,
     183,    40,   156,    42,   374,   210,   198,   211,   226,   375,
      98,   390,   205,    44,   234,    81,   391,    46,   184,    99,
     100,   101,   102,   103,   104,   105,   106,   393,   245,    48,
     246,   247,   394,   113,   248,   249,   250,   285,   286,    50,
     115,   116,   101,   102,   103,   207,   115,   116,   107,   108,
     109,   110,   111,   422,   115,   116,   112,   113,   423,   176,
     285,   286,   177,   615,   616,   617,   618,   114,   438,   786,
     115,   116,   787,   439,   245,   115,   116,   112,   113,   245,
     441,   117,   118,   368,   612,   442,   115,   116,   745,   441,
     112,   115,   116,    85,   746,   619,    89,   119,   816,    52,
     120,   817,    86,    87,    88,   866,   867,   121,   122,    54,
     963,   123,   374,   964,   719,   720,   850,   747,    89,   765,
      32,    33,    34,    35,   766,   765,    56,    89,   851,   325,
     767,   854,   329,    89,   863,   100,   101,   102,   103,   570,
     571,    89,   245,   267,   246,   247,   268,   269,   573,   574,
     903,   797,   904,   905,   115,   116,   798,    89,   583,   584,
     585,   801,    89,   107,   108,   109,   802,    58,   166,   167,
     168,    60,   113,    89,   115,   116,   836,    62,    89,   686,
     687,   688,   689,   169,   690,   115,   116,   170,   171,   172,
     173,   174,   175,   330,   438,   765,   224,   738,   176,   803,
     926,   177,   178,   705,   706,   707,   708,   709,   710,   179,
     390,   332,   331,   333,    90,   927,   292,   293,   294,   295,
     296,   297,   298,   299,   300,   301,   302,   303,   304,   305,
     443,   444,   965,   930,   422,   966,   967,   968,   931,   936,
     393,    89,   124,   339,   946,   940,   980,   404,   157,   947,
     343,   981,   916,   917,   918,   919,   344,   351,   352,   353,
     164,    89,   354,   365,   180,   373,   383,   208,   384,   445,
     408,   403,    89,   405,   412,   413,   200,   414,   225,   215,
     165,   416,   417,   418,   203,   419,   461,   424,   251,   427,
     227,   209,   429,   270,   430,   433,   201,   272,   232,   216,
     265,   434,   435,   273,   204,   283,   446,   181,   447,   448,
     228,   449,   306,   450,   452,   453,   454,   455,   233,   182,
     266,   183,   456,   457,   307,   284,   458,   198,   210,   459,
     211,   460,   252,   205,   462,   463,   464,   271,   475,   184,
     465,   226,   466,   467,   308,   468,   469,   234,   545,   546,
     547,   470,   471,   472,   942,   100,   101,   102,   103,     1,
       2,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,   473,   474,   476,   477,   479,   101,   102,   103,
     480,   481,   482,   107,   108,   109,   484,   111,   485,   486,
     487,   488,   113,   245,   489,   490,   492,   491,   493,   494,
     495,   496,   497,   499,   501,   115,   116,   502,   171,   503,
     504,   505,   175,   113,   506,   507,   508,   124,   176,   510,
     511,   177,   157,   607,   513,   514,   115,   116,   512,   179,
     515,   518,   516,   519,   164,   522,   523,   520,   217,   526,
     721,   306,   623,   527,   218,   219,   220,   221,   222,   223,
     627,   224,   722,   307,   165,   628,   629,   630,   631,   632,
     633,   634,   635,   636,   637,   638,   639,   640,   641,   642,
     643,   528,   723,   308,   529,   525,   530,   532,   533,   531,
     537,   245,   534,   538,   535,   536,   540,   542,   543,   549,
     550,   544,    89,   548,   552,   551,   553,   554,   555,   556,
     557,   558,   561,   562,    30,   563,   564,   814,   576,   565,
     566,   567,   568,    89,   577,   578,   579,   580,   581,   582,
     588,   589,   590,   591,   593,   594,   622,   666,   752,   670,
     674,   595,   596,   597,   678,   682,   598,   599,   600,   601,
     698,   602,   614,   701,   730,   734,   603,   604,   742,   753,
     605,   606,   754,   755,   756,   759,   760,   761,   762,   608,
     609,   763,   610,   764,   769,   770,   621,   772,   773,   775,
     776,   779,   778,   782,   823,   781,   790,   789,   791,   792,
      89,   793,   794,   795,   796,   809,   804,   808,   812,   811,
     818,   819,   820,   821,   825,   822,   824,   826,   827,   828,
     829,   830,   831,   832,   893,   834,   833,   886,   887,   888,
     889,   890,   891,   894,   896,   897,   921,   902,   922,   923,
     924,   925,   928,   929,   933,   934,   935,   937,   950,   938,
     939,   944,   941,   949,   952,   954,   953,   957,   956,   977,
     959,   978,   979,   958,   982,   180,   451,   559,   251,   983,
     984,   270,   478,   624,   844,   272,   626,   200,   837,   868,
     265,   273,   287,   283,   870,   203,   858,   985,   987,   483,
     835,   872,   865,   885,   860,   721,   839,   201,   852,   874,
     266,   208,   524,   284,   225,   204,   859,   722,   181,   906,
     884,   873,   252,   215,   861,   271,   227,   845,   849,   875,
     182,   908,   183,   869,   232,   209,   892,   723,   198,   846,
     838,   847,   864,   216,   205,   853,   228,   857,   498,   948,
     184,   909,   871,   862,   233,   840,   841,   843,   876,   848,
     517,   842,   899,   907,   521,   898,   500,   901,   883,   509,
     739,   951,   210,   900,   211,   895,   539,   226,   728,   625,
     955,   975,   541,   234,   986,     0,   915,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   844,     0,     0,     0,     0,   868,
       0,     0,     0,     0,   870,     0,   858,     0,     0,     0,
     906,   872,     0,     0,   860,     0,     0,     0,   852,   874,
       0,     0,   908,     0,     0,     0,   859,     0,     0,     0,
       0,   873,     0,     0,   861,     0,     0,   845,   849,   875,
       0,     0,   909,   869,     0,     0,     0,     0,     0,   846,
       0,   847,     0,     0,   907,   853,     0,   857,     0,     0,
       0,     0,   871,   862,     0,     0,     0,     0,   876,   848
  };

  const short
  Dhcp4Parser::yycheck_[] =
  {
      66,    67,    68,    69,    70,    71,   494,    73,    74,    75,
      76,    72,    74,   501,    68,    69,    70,    71,    74,    73,
      74,   553,    76,    69,    64,    71,   780,     5,    70,     7,
      10,     9,    15,     0,    68,    69,    70,    71,   780,    73,
      74,   780,    76,    69,   780,    71,    69,     3,     3,     3,
       6,    73,    74,     8,     8,    12,    13,    28,    69,    16,
      69,     7,    19,     7,     3,    70,    69,    70,    71,     8,
      11,     3,    69,     7,    71,   158,     8,     7,    69,    20,
      21,    22,    23,    24,    25,    26,    27,     3,    59,     7,
      61,    62,     8,    58,    65,    66,    67,    99,   100,     7,
      71,    72,    22,    23,    24,    70,    71,    72,    49,    50,
      51,    52,    53,     3,    71,    72,    57,    58,     8,    84,
      99,   100,    87,   129,   130,   131,   132,    68,     3,     3,
      71,    72,     6,     8,    59,    71,    72,    57,    58,    59,
       3,    82,    83,     3,   127,     8,    71,    72,     8,     3,
      57,    71,    72,   133,     8,   161,   158,    98,     3,     7,
     101,     6,   142,   143,   144,    85,    86,   108,   109,     7,
       3,   112,     3,     6,   110,   111,   930,     8,   158,     3,
     158,   159,   160,   161,     8,     3,     7,   158,   930,   134,
       8,   930,     6,   158,   930,    21,    22,    23,    24,    14,
      15,   158,    59,    60,    61,    62,    63,    64,    17,    18,
     135,     3,   137,   138,    71,    72,     8,   158,    79,    80,
      81,     3,   158,    49,    50,    51,     8,     7,    54,    55,
      56,     7,    58,   158,    71,    72,   768,     7,   158,    89,
      90,    91,    92,    69,    94,    71,    72,    73,    74,    75,
      76,    77,    78,     3,     3,     3,    96,    97,    84,     8,
       8,    87,    88,   102,   103,   104,   105,   106,   107,    95,
       3,     8,     4,     3,   340,     8,   113,   114,   115,   116,
     117,   118,   119,   120,   121,   122,   123,   124,   125,   126,
     330,   331,   136,     3,     3,   139,   140,   141,     8,     8,
       3,   158,   368,     4,     3,     8,     3,     3,   374,     8,
       4,     8,    29,    30,    31,    32,     4,     4,     4,     4,
     374,   158,     4,     4,   390,     4,     4,   393,     4,   158,
       4,     8,   158,     8,     4,     8,   390,     3,   404,   393,
     374,     4,     4,     8,   390,     3,   159,     4,   414,     4,
     404,   393,     4,   419,     4,     4,   390,   419,   404,   393,
     414,     4,     4,   419,   390,   419,     4,   390,     4,     4,
     404,     4,   438,     4,     4,   161,   161,     4,   404,   390,
     414,   390,     4,     4,   438,   419,     4,   390,   393,     4,
     393,     4,   414,   390,   159,   159,   159,   419,   159,   390,
       4,   404,     4,     4,   438,     4,     4,   404,   448,   449,
     450,     4,     4,     4,   902,    21,    22,    23,    24,   145,
     146,   147,   148,   149,   150,   151,   152,   153,   154,   155,
     156,   157,     4,     4,     4,     4,     4,    22,    23,    24,
       4,     4,   161,    49,    50,    51,     4,    53,     4,     4,
       4,     4,    58,    59,     4,     4,   161,   159,     4,     4,
       4,     4,     4,     4,     4,    71,    72,     4,    74,     4,
       4,     4,    78,    58,     4,     4,     4,   543,    84,     4,
       4,    87,   548,   523,     4,     4,    71,    72,   159,    95,
       4,     4,   161,   161,   548,     4,     4,   161,    83,     4,
     566,   567,   542,     4,    89,    90,    91,    92,    93,    94,
      28,    96,   566,   567,   548,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      48,   159,   566,   567,     4,   161,   159,     4,     4,   159,
       4,    59,   161,     4,   161,   161,     4,     4,     7,   158,
     158,     7,   158,     7,     7,   158,     7,     5,     5,     5,
       5,     5,   158,     5,     7,     5,     5,     8,   158,     7,
       7,     7,     5,   158,   158,   158,     5,   158,   158,   158,
     158,     5,     7,   158,   158,   158,     5,     7,     4,     7,
       7,   158,   158,   158,     7,     7,   158,   158,   158,   158,
       7,   158,   128,     7,     7,     7,   158,   158,     7,     4,
     158,   158,     4,     4,     4,     4,     4,     4,     4,   158,
     158,     4,   158,     4,     6,     3,   158,     6,     3,     6,
       3,     3,     6,     3,   161,     6,     3,     6,     4,     4,
     158,     4,     4,     4,     4,     3,   158,     6,     3,     6,
       4,     4,     4,     4,   161,   159,   159,   159,     4,     4,
     159,   159,   159,   159,     4,   159,   161,   159,   159,   159,
     159,   159,   159,     4,     6,     3,   158,     4,   158,   158,
     158,   158,     8,     8,     4,     8,     3,   158,   161,   158,
     158,     4,     8,     4,     4,     4,   159,     5,   158,     4,
       7,     4,     4,   158,     4,   771,   340,   469,   774,   161,
     159,   777,   368,   543,   780,   777,   548,   771,   770,   785,
     774,   777,   788,   777,   785,   771,   780,   159,   158,   374,
     765,   785,   783,   790,   780,   801,   773,   771,   780,   785,
     774,   807,   422,   777,   810,   771,   780,   801,   771,   815,
     788,   785,   774,   807,   780,   777,   810,   780,   780,   785,
     771,   815,   771,   785,   810,   807,   797,   801,   771,   780,
     771,   780,   782,   807,   771,   780,   810,   780,   390,   930,
     771,   815,   785,   780,   810,   774,   776,   779,   785,   780,
     414,   777,   809,   815,   419,   807,   393,   812,   786,   404,
     590,   935,   807,   810,   807,   801,   438,   810,   567,   544,
     946,   963,   441,   810,   980,    -1,   816,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   930,    -1,    -1,    -1,    -1,   935,
      -1,    -1,    -1,    -1,   935,    -1,   930,    -1,    -1,    -1,
     946,   935,    -1,    -1,   930,    -1,    -1,    -1,   930,   935,
      -1,    -1,   946,    -1,    -1,    -1,   930,    -1,    -1,    -1,
      -1,   935,    -1,    -1,   930,    -1,    -1,   930,   930,   935,
      -1,    -1,   946,   935,    -1,    -1,    -1,    -1,    -1,   930,
      -1,   930,    -1,    -1,   946,   930,    -1,   930,    -1,    -1,
      -1,    -1,   935,   930,    -1,    -1,    -1,    -1,   935,   930
  };

  const unsigned short
  Dhcp4Parser::yystos_[] =
  {
       0,   145,   146,   147,   148,   149,   150,   151,   152,   153,
     154,   155,   156,   157,   163,   164,   165,   166,   167,   168,
     169,   170,   171,   172,   173,   174,   175,   176,     0,     5,
       7,     9,   158,   159,   160,   161,   177,   178,   179,   184,
       7,   193,     7,   199,     7,   213,     7,   301,     7,   384,
       7,   400,     7,   336,     7,   342,     7,   366,     7,   277,
       7,   455,     7,   490,   185,   180,   194,   200,   214,   302,
     385,   401,   337,   343,   367,   278,   456,   491,   177,   186,
     187,   158,   182,   183,    10,   133,   142,   143,   144,   158,
     192,   195,   196,   197,   482,   484,   486,   488,    11,    20,
      21,    22,    23,    24,    25,    26,    27,    49,    50,    51,
      52,    53,    57,    58,    68,    71,    72,    82,    83,    98,
     101,   108,   109,   112,   192,   201,   202,   203,   204,   205,
     206,   207,   208,   209,   224,   226,   228,   262,   271,   285,
     295,   326,   334,   360,   390,   392,   405,   407,   409,   432,
     444,   445,   453,    12,    13,    16,    19,   192,   211,   212,
     215,   217,   220,   223,   390,   392,    54,    55,    56,    69,
      73,    74,    75,    76,    77,    78,    84,    87,    88,    95,
     192,   203,   204,   205,   208,   303,   304,   305,   307,   309,
     311,   313,   315,   317,   319,   321,   324,   325,   360,   378,
     390,   392,   394,   405,   407,   409,   429,    70,   192,   317,
     319,   360,   386,   387,   388,   390,   392,    83,    89,    90,
      91,    92,    93,    94,    96,   192,   360,   390,   392,   402,
     403,   404,   405,   407,   409,   411,   415,   417,   419,   421,
     423,   425,   427,   334,    28,    59,    61,    62,    65,    66,
      67,   192,   246,   344,   345,   346,   347,   348,   349,   350,
     352,   354,   356,   357,   359,   390,   392,    60,    63,    64,
     192,   246,   348,   354,   368,   369,   370,   371,   372,   374,
     375,   376,   377,   390,   392,    99,   100,   192,   279,   280,
     281,   283,   113,   114,   115,   116,   117,   118,   119,   120,
     121,   122,   123,   124,   125,   126,   192,   390,   392,   457,
     458,   459,   460,   462,   464,   465,   467,   468,   469,   472,
     474,   475,   476,   477,   480,   134,   492,   493,   494,     6,
       3,     4,     8,     3,   198,   489,   483,   485,   487,     4,
       3,     8,   210,     4,     4,   406,   408,   410,   225,   227,
     229,     4,     4,     4,     4,   296,   335,   361,   327,   391,
     393,   263,   433,   272,   286,     4,   446,   454,     3,     8,
     216,   218,   221,     4,     3,     8,   308,   310,   312,   379,
     306,   314,   316,     4,     4,   322,   320,   318,   395,   430,
       3,     8,   389,     3,     8,   428,   416,   418,   422,   420,
     426,   424,   412,     8,     3,     8,   351,   247,     4,   355,
     353,   358,     4,     8,     3,   373,     4,     4,     8,     3,
     282,   284,     3,     8,     4,   461,   463,     4,   466,     4,
       4,   470,   473,     4,     4,     4,   478,   481,     3,     8,
     495,     3,     8,   177,   177,   158,     4,     4,     4,     4,
       4,   196,     4,   161,   161,     4,     4,     4,     4,     4,
       4,   159,   159,   159,   159,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,   159,     4,     4,   202,     4,
       4,     4,   161,   212,     4,     4,     4,     4,     4,     4,
       4,   159,   161,     4,     4,     4,     4,     4,   304,     4,
     387,     4,     4,     4,     4,     4,     4,     4,     4,   404,
       4,     4,   159,     4,     4,     4,   161,   346,     4,   161,
     161,   370,     4,     4,   280,   161,     4,     4,   159,     4,
     159,   159,     4,     4,   161,   161,   161,     4,     4,   458,
       4,   493,     4,     7,     7,   177,   177,   177,     7,   158,
     158,   158,     7,     7,     5,     5,     5,     5,     5,   179,
     181,   158,     5,     5,     5,     7,     7,     7,     5,   188,
      14,    15,   219,    17,    18,   222,   158,   158,   158,     5,
     158,   158,   158,    79,    80,    81,   323,   188,   158,     5,
       7,   158,   188,   158,   158,   158,   158,   158,   158,   158,
     158,   158,   158,   158,   158,   158,   158,   177,   158,   158,
     158,    15,   127,   471,   128,   129,   130,   131,   132,   161,
     479,   158,     5,   177,   201,   492,   211,    28,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,   192,   234,   235,   236,   239,   241,
     243,   245,   246,   248,   249,   250,   251,   252,   253,   254,
     255,   257,   259,   260,   261,   234,     7,   230,   231,   232,
       7,   297,   298,   299,     7,   338,   339,   340,     7,   362,
     363,   364,     7,   328,   329,   330,    89,    90,    91,    92,
      94,   264,   265,   266,   267,   268,   269,   270,     7,   434,
     435,     7,   273,   274,   275,   102,   103,   104,   105,   106,
     107,   287,   288,   289,   290,   291,   292,   293,   294,   110,
     111,   192,   390,   392,   447,   448,   449,   451,   457,   189,
       7,   380,   381,   382,     7,   396,   397,   398,    97,   411,
     413,   431,     7,   496,   497,     8,     8,     8,   237,   240,
     242,   244,     4,     4,     4,     4,     4,   256,   258,     4,
       4,     4,     4,     4,     4,     3,     8,     8,   233,     6,
       3,   300,     6,     3,   341,     6,     3,   365,     6,     3,
     331,     6,     3,     3,     6,   436,     3,     6,   276,     6,
       3,     4,     4,     4,     4,     4,     4,     3,     8,   450,
     452,     3,     8,     8,   158,   190,   191,   383,     6,     3,
     399,     6,     3,   414,     8,   498,     3,     6,     4,     4,
       4,     4,   159,   161,   159,   161,   159,     4,     4,   159,
     159,   159,   159,   161,   159,   235,   234,   232,   303,   299,
     344,   340,   368,   364,   192,   203,   204,   205,   208,   246,
     295,   313,   317,   319,   321,   332,   333,   360,   390,   392,
     405,   407,   409,   429,   330,   265,    85,    86,   192,   246,
     334,   360,   390,   392,   405,   407,   409,   437,   438,   439,
     440,   441,   443,   435,   279,   275,   159,   159,   159,   159,
     159,   159,   288,     4,     4,   448,     6,     3,   386,   382,
     402,   398,     4,   135,   137,   138,   192,   246,   390,   392,
     499,   500,   501,   502,   504,   497,    29,    30,    31,    32,
     238,   158,   158,   158,   158,   158,     8,     8,     8,     8,
       3,     8,   442,     4,     8,     3,     8,   158,   158,   158,
       8,     8,   188,   505,     4,   503,     3,     8,   333,     4,
     161,   439,     4,   159,     4,   500,   158,     5,   158,     7,
     506,   507,   508,     3,     6,   136,   139,   140,   141,   509,
     510,   511,   513,   514,   515,   507,   512,     4,     4,     4,
       3,     8,     4,   161,   159,   159,   510,   158
  };

  const unsigned short
  Dhcp4Parser::yyr1_[] =
  {
       0,   162,   164,   163,   165,   163,   166,   163,   167,   163,
     168,   163,   169,   163,   170,   163,   171,   163,   172,   163,
     173,   163,   174,   163,   175,   163,   176,   163,   177,   177,
     177,   177,   177,   177,   177,   178,   180,   179,   181,   182,
     182,   183,   183,   185,   184,   186,   186,   187,   187,   189,
     188,   190,   190,   191,   191,   192,   194,   193,   195,   195,
     196,   196,   196,   196,   196,   196,   198,   197,   200,   199,
     201,   201,   202,   202,   202,   202,   202,   202,   202,   202,
     202,   202,   202,   202,   202,   202,   202,   202,   202,   202,
     202,   202,   202,   202,   202,   202,   202,   202,   202,   203,
     204,   205,   206,   207,   208,   210,   209,   211,   211,   212,
     212,   212,   212,   212,   212,   212,   214,   213,   216,   215,
     218,   217,   219,   219,   221,   220,   222,   222,   223,   225,
     224,   227,   226,   229,   228,   230,   230,   231,   231,   233,
     232,   234,   234,   235,   235,   235,   235,   235,   235,   235,
     235,   235,   235,   235,   235,   235,   235,   235,   235,   235,
     235,   235,   237,   236,   238,   238,   238,   238,   240,   239,
     242,   241,   244,   243,   245,   247,   246,   248,   249,   250,
     251,   252,   253,   254,   256,   255,   258,   257,   259,   260,
     261,   263,   262,   264,   264,   265,   265,   265,   265,   265,
     266,   267,   268,   269,   270,   272,   271,   273,   273,   274,
     274,   276,   275,   278,   277,   279,   279,   279,   280,   280,
     282,   281,   284,   283,   286,   285,   287,   287,   288,   288,
     288,   288,   288,   288,   289,   290,   291,   292,   293,   294,
     296,   295,   297,   297,   298,   298,   300,   299,   302,   301,
     303,   303,   304,   304,   304,   304,   304,   304,   304,   304,
     304,   304,   304,   304,   304,   304,   304,   304,   304,   304,
     304,   304,   304,   304,   304,   304,   304,   306,   305,   308,
     307,   310,   309,   312,   311,   314,   313,   316,   315,   318,
     317,   320,   319,   322,   321,   323,   323,   323,   324,   325,
     327,   326,   328,   328,   329,   329,   331,   330,   332,   332,
     333,   333,   333,   333,   333,   333,   333,   333,   333,   333,
     333,   333,   333,   333,   333,   333,   333,   333,   335,   334,
     337,   336,   338,   338,   339,   339,   341,   340,   343,   342,
     344,   344,   345,   345,   346,   346,   346,   346,   346,   346,
     346,   346,   346,   346,   347,   348,   349,   351,   350,   353,
     352,   355,   354,   356,   358,   357,   359,   361,   360,   362,
     362,   363,   363,   365,   364,   367,   366,   368,   368,   369,
     369,   370,   370,   370,   370,   370,   370,   370,   370,   370,
     371,   373,   372,   374,   375,   376,   377,   379,   378,   380,
     380,   381,   381,   383,   382,   385,   384,   386,   386,   387,
     387,   387,   387,   387,   387,   387,   389,   388,   391,   390,
     393,   392,   395,   394,   396,   396,   397,   397,   399,   398,
     401,   400,   402,   402,   403,   403,   404,   404,   404,   404,
     404,   404,   404,   404,   404,   404,   404,   404,   404,   404,
     404,   406,   405,   408,   407,   410,   409,   412,   411,   414,
     413,   416,   415,   418,   417,   420,   419,   422,   421,   424,
     423,   426,   425,   428,   427,   430,   429,   431,   431,   433,
     432,   434,   434,   436,   435,   437,   437,   438,   438,   439,
     439,   439,   439,   439,   439,   439,   439,   439,   439,   439,
     440,   442,   441,   443,   444,   446,   445,   447,   447,   448,
     448,   448,   448,   448,   450,   449,   452,   451,   454,   453,
     456,   455,   457,   457,   458,   458,   458,   458,   458,   458,
     458,   458,   458,   458,   458,   458,   458,   458,   458,   458,
     458,   459,   461,   460,   463,   462,   464,   466,   465,   467,
     468,   470,   469,   471,   471,   473,   472,   474,   475,   476,
     478,   477,   479,   479,   479,   479,   479,   481,   480,   483,
     482,   485,   484,   487,   486,   489,   488,   491,   490,   492,
     492,   493,   495,   494,   496,   496,   498,   497,   499,   499,
     500,   500,   500,   500,   500,   500,   500,   501,   503,   502,
     505,   504,   506,   506,   508,   507,   509,   509,   510,   510,
     510,   510,   512,   511,   513,   514,   515
  };

  const unsigned char
  Dhcp4Parser::yyr2_[] =
  {
       0,     2,     0,     3,     0,     3,     0,     3,     0,     3,
       0,     3,     0,     3,     0,     3,     0,     3,     0,     3,
       0,     3,     0,     3,     0,     3,     0,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     0,     4,     1,     0,
       1,     3,     5,     0,     4,     0,     1,     1,     3,     0,
       4,     0,     1,     1,     3,     2,     0,     4,     1,     3,
       1,     1,     1,     1,     1,     1,     0,     6,     0,     4,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     3,
       3,     3,     3,     3,     3,     0,     6,     1,     3,     1,
       1,     1,     1,     1,     1,     1,     0,     4,     0,     4,
       0,     4,     1,     1,     0,     4,     1,     1,     3,     0,
       6,     0,     6,     0,     6,     0,     1,     1,     3,     0,
       4,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     0,     4,     1,     1,     1,     1,     0,     4,
       0,     4,     0,     4,     3,     0,     4,     3,     3,     3,
       3,     3,     3,     3,     0,     4,     0,     4,     3,     3,
       3,     0,     6,     1,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     0,     6,     0,     1,     1,
       3,     0,     4,     0,     4,     1,     3,     1,     1,     1,
       0,     4,     0,     4,     0,     6,     1,     3,     1,     1,
       1,     1,     1,     1,     3,     3,     3,     3,     3,     3,
       0,     6,     0,     1,     1,     3,     0,     4,     0,     4,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     4,     1,     1,     1,     3,     3,
       0,     6,     0,     1,     1,     3,     0,     4,     1,     3,
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
       0,     4,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     3,     0,     4,     0,     4,     3,     0,     4,     3,
       3,     0,     4,     1,     1,     0,     4,     3,     3,     3,
       0,     4,     1,     1,     1,     1,     1,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     6,     0,     4,     1,
       3,     1,     0,     6,     1,     3,     0,     4,     1,     3,
       1,     1,     1,     1,     1,     1,     1,     3,     0,     4,
       0,     6,     1,     3,     0,     4,     1,     3,     1,     1,
       1,     1,     0,     4,     3,     3,     3
  };



  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a yyntokens_, nonterminals.
  const char*
  const Dhcp4Parser::yytname_[] =
  {
  "\"end of file\"", "error", "$undefined", "\",\"", "\":\"", "\"[\"",
  "\"]\"", "\"{\"", "\"}\"", "\"null\"", "\"Dhcp4\"",
  "\"interfaces-config\"", "\"interfaces\"", "\"dhcp-socket-type\"",
  "\"raw\"", "\"udp\"", "\"outbound-interface\"", "\"same-as-inbound\"",
  "\"use-routing\"", "\"re-detect\"", "\"echo-client-id\"",
  "\"match-client-id\"", "\"next-server\"", "\"server-hostname\"",
  "\"boot-file-name\"", "\"lease-database\"", "\"hosts-database\"",
  "\"hosts-databases\"", "\"type\"", "\"memfile\"", "\"mysql\"",
  "\"postgresql\"", "\"cql\"", "\"user\"", "\"password\"", "\"host\"",
  "\"port\"", "\"persist\"", "\"lfc-interval\"", "\"readonly\"",
  "\"connect-timeout\"", "\"contact-points\"", "\"keyspace\"",
  "\"max-reconnect-tries\"", "\"reconnect-wait-time\"",
  "\"request-timeout\"", "\"tcp-keepalive\"", "\"tcp-nodelay\"",
  "\"max-row-errors\"", "\"valid-lifetime\"", "\"renew-timer\"",
  "\"rebind-timer\"", "\"decline-probation-period\"", "\"subnet4\"",
  "\"4o6-interface\"", "\"4o6-interface-id\"", "\"4o6-subnet\"",
  "\"option-def\"", "\"option-data\"", "\"name\"", "\"data\"", "\"code\"",
  "\"space\"", "\"csv-format\"", "\"always-send\"", "\"record-types\"",
  "\"encapsulate\"", "\"array\"", "\"shared-networks\"", "\"pools\"",
  "\"pool\"", "\"user-context\"", "\"comment\"", "\"subnet\"",
  "\"interface\"", "\"interface-id\"", "\"id\"", "\"rapid-commit\"",
  "\"reservation-mode\"", "\"disabled\"", "\"out-of-pool\"", "\"all\"",
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
  "\"socket-name\"", "\"dhcp-ddns\"", "\"enable-updates\"",
  "\"qualifying-suffix\"", "\"server-ip\"", "\"server-port\"",
  "\"sender-ip\"", "\"sender-port\"", "\"max-queue-size\"",
  "\"ncr-protocol\"", "\"ncr-format\"", "\"always-include-fqdn\"",
  "\"override-no-update\"", "\"override-client-update\"",
  "\"replace-client-name\"", "\"generated-prefix\"", "\"tcp\"", "\"JSON\"",
  "\"when-present\"", "\"never\"", "\"always\"", "\"when-not-present\"",
  "\"Logging\"", "\"loggers\"", "\"output_options\"", "\"output\"",
  "\"debuglevel\"", "\"severity\"", "\"flush\"", "\"maxsize\"",
  "\"maxver\"", "\"Dhcp6\"", "\"DhcpDdns\"", "\"Control-agent\"",
  "TOPLEVEL_JSON", "TOPLEVEL_DHCP4", "SUB_DHCP4", "SUB_INTERFACES4",
  "SUB_SUBNET4", "SUB_POOL4", "SUB_RESERVATION", "SUB_OPTION_DEFS",
  "SUB_OPTION_DEF", "SUB_OPTION_DATA", "SUB_HOOKS_LIBRARY",
  "SUB_DHCP_DDNS", "SUB_LOGGING", "\"constant string\"", "\"integer\"",
  "\"floating point\"", "\"boolean\"", "$accept", "start", "$@1", "$@2",
  "$@3", "$@4", "$@5", "$@6", "$@7", "$@8", "$@9", "$@10", "$@11", "$@12",
  "$@13", "value", "sub_json", "map2", "$@14", "map_value", "map_content",
  "not_empty_map", "list_generic", "$@15", "list_content",
  "not_empty_list", "list_strings", "$@16", "list_strings_content",
  "not_empty_list_strings", "unknown_map_entry", "syntax_map", "$@17",
  "global_objects", "global_object", "dhcp4_object", "$@18", "sub_dhcp4",
  "$@19", "global_params", "global_param", "valid_lifetime", "renew_timer",
  "rebind_timer", "decline_probation_period", "echo_client_id",
  "match_client_id", "interfaces_config", "$@20",
  "interfaces_config_params", "interfaces_config_param", "sub_interfaces4",
  "$@21", "interfaces_list", "$@22", "dhcp_socket_type", "$@23",
  "socket_type", "outbound_interface", "$@24", "outbound_interface_value",
  "re_detect", "lease_database", "$@25", "hosts_database", "$@26",
  "hosts_databases", "$@27", "database_list", "not_empty_database_list",
  "database", "$@28", "database_map_params", "database_map_param",
  "database_type", "$@29", "db_type", "user", "$@30", "password", "$@31",
  "host", "$@32", "port", "name", "$@33", "persist", "lfc_interval",
  "readonly", "connect_timeout", "request_timeout", "tcp_keepalive",
  "tcp_nodelay", "contact_points", "$@34", "keyspace", "$@35",
  "max_reconnect_tries", "reconnect_wait_time", "max_row_errors",
  "host_reservation_identifiers", "$@36",
  "host_reservation_identifiers_list", "host_reservation_identifier",
  "duid_id", "hw_address_id", "circuit_id", "client_id", "flex_id",
  "hooks_libraries", "$@37", "hooks_libraries_list",
  "not_empty_hooks_libraries_list", "hooks_library", "$@38",
  "sub_hooks_library", "$@39", "hooks_params", "hooks_param", "library",
  "$@40", "parameters", "$@41", "expired_leases_processing", "$@42",
  "expired_leases_params", "expired_leases_param",
  "reclaim_timer_wait_time", "flush_reclaimed_timer_wait_time",
  "hold_reclaimed_time", "max_reclaim_leases", "max_reclaim_time",
  "unwarned_reclaim_cycles", "subnet4_list", "$@43",
  "subnet4_list_content", "not_empty_subnet4_list", "subnet4", "$@44",
  "sub_subnet4", "$@45", "subnet4_params", "subnet4_param", "subnet",
  "$@46", "subnet_4o6_interface", "$@47", "subnet_4o6_interface_id",
  "$@48", "subnet_4o6_subnet", "$@49", "interface", "$@50", "interface_id",
  "$@51", "client_class", "$@52", "require_client_classes", "$@53",
  "reservation_mode", "$@54", "hr_mode", "id", "rapid_commit",
  "shared_networks", "$@55", "shared_networks_content",
  "shared_networks_list", "shared_network", "$@56",
  "shared_network_params", "shared_network_param", "option_def_list",
  "$@57", "sub_option_def_list", "$@58", "option_def_list_content",
  "not_empty_option_def_list", "option_def_entry", "$@59",
  "sub_option_def", "$@60", "option_def_params",
  "not_empty_option_def_params", "option_def_param", "option_def_name",
  "code", "option_def_code", "option_def_type", "$@61",
  "option_def_record_types", "$@62", "space", "$@63", "option_def_space",
  "option_def_encapsulate", "$@64", "option_def_array", "option_data_list",
  "$@65", "option_data_list_content", "not_empty_option_data_list",
  "option_data_entry", "$@66", "sub_option_data", "$@67",
  "option_data_params", "not_empty_option_data_params",
  "option_data_param", "option_data_name", "option_data_data", "$@68",
  "option_data_code", "option_data_space", "option_data_csv_format",
  "option_data_always_send", "pools_list", "$@69", "pools_list_content",
  "not_empty_pools_list", "pool_list_entry", "$@70", "sub_pool4", "$@71",
  "pool_params", "pool_param", "pool_entry", "$@72", "user_context",
  "$@73", "comment", "$@74", "reservations", "$@75", "reservations_list",
  "not_empty_reservations_list", "reservation", "$@76", "sub_reservation",
  "$@77", "reservation_params", "not_empty_reservation_params",
  "reservation_param", "next_server", "$@78", "server_hostname", "$@79",
  "boot_file_name", "$@80", "ip_address", "$@81", "ip_addresses", "$@82",
  "duid", "$@83", "hw_address", "$@84", "client_id_value", "$@85",
  "circuit_id_value", "$@86", "flex_id_value", "$@87", "hostname", "$@88",
  "reservation_client_classes", "$@89", "relay", "$@90", "relay_map",
  "client_classes", "$@91", "client_classes_list", "client_class_entry",
  "$@92", "client_class_params", "not_empty_client_class_params",
  "client_class_param", "client_class_name", "client_class_test", "$@93",
  "only_if_required", "dhcp4o6_port", "control_socket", "$@94",
  "control_socket_params", "control_socket_param", "control_socket_type",
  "$@95", "control_socket_name", "$@96", "dhcp_ddns", "$@97",
  "sub_dhcp_ddns", "$@98", "dhcp_ddns_params", "dhcp_ddns_param",
  "enable_updates", "qualifying_suffix", "$@99", "server_ip", "$@100",
  "server_port", "sender_ip", "$@101", "sender_port", "max_queue_size",
  "ncr_protocol", "$@102", "ncr_protocol_value", "ncr_format", "$@103",
  "always_include_fqdn", "override_no_update", "override_client_update",
  "replace_client_name", "$@104", "replace_client_name_value",
  "generated_prefix", "$@105", "dhcp6_json_object", "$@106",
  "dhcpddns_json_object", "$@107", "control_agent_json_object", "$@108",
  "logging_object", "$@109", "sub_logging", "$@110", "logging_params",
  "logging_param", "loggers", "$@111", "loggers_entries", "logger_entry",
  "$@112", "logger_params", "logger_param", "debuglevel", "severity",
  "$@113", "output_options_list", "$@114", "output_options_list_content",
  "output_entry", "$@115", "output_params_list", "output_params", "output",
  "$@116", "flush", "maxsize", "maxver", YY_NULLPTR
  };

#if PARSER4_DEBUG
  const unsigned short
  Dhcp4Parser::yyrline_[] =
  {
       0,   245,   245,   245,   246,   246,   247,   247,   248,   248,
     249,   249,   250,   250,   251,   251,   252,   252,   253,   253,
     254,   254,   255,   255,   256,   256,   257,   257,   265,   266,
     267,   268,   269,   270,   271,   274,   279,   279,   290,   293,
     294,   297,   301,   308,   308,   315,   316,   319,   323,   330,
     330,   337,   338,   341,   345,   356,   366,   366,   382,   383,
     387,   388,   389,   390,   391,   392,   395,   395,   410,   410,
     419,   420,   425,   426,   427,   428,   429,   430,   431,   432,
     433,   434,   435,   436,   437,   438,   439,   440,   441,   442,
     443,   444,   445,   446,   447,   448,   449,   450,   451,   454,
     459,   464,   469,   474,   479,   485,   485,   496,   497,   500,
     501,   502,   503,   504,   505,   506,   509,   509,   518,   518,
     528,   528,   535,   536,   539,   539,   546,   548,   552,   558,
     558,   570,   570,   582,   582,   592,   593,   596,   597,   600,
     600,   610,   611,   614,   615,   616,   617,   618,   619,   620,
     621,   622,   623,   624,   625,   626,   627,   628,   629,   630,
     631,   632,   635,   635,   642,   643,   644,   645,   648,   648,
     656,   656,   664,   664,   672,   677,   677,   685,   690,   695,
     700,   705,   710,   715,   720,   720,   728,   728,   736,   741,
     746,   751,   751,   761,   762,   765,   766,   767,   768,   769,
     772,   777,   782,   787,   792,   797,   797,   807,   808,   811,
     812,   815,   815,   825,   825,   835,   836,   837,   840,   841,
     844,   844,   852,   852,   860,   860,   871,   872,   875,   876,
     877,   878,   879,   880,   883,   888,   893,   898,   903,   908,
     916,   916,   929,   930,   933,   934,   941,   941,   967,   967,
     978,   979,   983,   984,   985,   986,   987,   988,   989,   990,
     991,   992,   993,   994,   995,   996,   997,   998,   999,  1000,
    1001,  1002,  1003,  1004,  1005,  1006,  1007,  1010,  1010,  1018,
    1018,  1026,  1026,  1034,  1034,  1042,  1042,  1050,  1050,  1058,
    1058,  1066,  1066,  1076,  1076,  1083,  1084,  1085,  1088,  1093,
    1100,  1100,  1111,  1112,  1116,  1117,  1120,  1120,  1128,  1129,
    1132,  1133,  1134,  1135,  1136,  1137,  1138,  1139,  1140,  1141,
    1142,  1143,  1144,  1145,  1146,  1147,  1148,  1149,  1156,  1156,
    1169,  1169,  1178,  1179,  1182,  1183,  1188,  1188,  1203,  1203,
    1217,  1218,  1221,  1222,  1225,  1226,  1227,  1228,  1229,  1230,
    1231,  1232,  1233,  1234,  1237,  1239,  1244,  1246,  1246,  1254,
    1254,  1262,  1262,  1270,  1272,  1272,  1280,  1289,  1289,  1301,
    1302,  1307,  1308,  1313,  1313,  1325,  1325,  1337,  1338,  1343,
    1344,  1349,  1350,  1351,  1352,  1353,  1354,  1355,  1356,  1357,
    1360,  1362,  1362,  1370,  1372,  1374,  1379,  1387,  1387,  1399,
    1400,  1403,  1404,  1407,  1407,  1417,  1417,  1427,  1428,  1431,
    1432,  1433,  1434,  1435,  1436,  1437,  1440,  1440,  1448,  1448,
    1473,  1473,  1503,  1503,  1513,  1514,  1517,  1518,  1521,  1521,
    1530,  1530,  1539,  1540,  1543,  1544,  1548,  1549,  1550,  1551,
    1552,  1553,  1554,  1555,  1556,  1557,  1558,  1559,  1560,  1561,
    1562,  1565,  1565,  1573,  1573,  1581,  1581,  1589,  1589,  1597,
    1597,  1607,  1607,  1615,  1615,  1623,  1623,  1631,  1631,  1639,
    1639,  1647,  1647,  1655,  1655,  1668,  1668,  1678,  1679,  1685,
    1685,  1695,  1696,  1699,  1699,  1709,  1710,  1713,  1714,  1717,
    1718,  1719,  1720,  1721,  1722,  1723,  1724,  1725,  1726,  1727,
    1730,  1732,  1732,  1740,  1749,  1756,  1756,  1766,  1767,  1770,
    1771,  1772,  1773,  1774,  1777,  1777,  1785,  1785,  1795,  1795,
    1807,  1807,  1817,  1818,  1821,  1822,  1823,  1824,  1825,  1826,
    1827,  1828,  1829,  1830,  1831,  1832,  1833,  1834,  1835,  1836,
    1837,  1840,  1845,  1845,  1853,  1853,  1861,  1866,  1866,  1874,
    1879,  1884,  1884,  1892,  1893,  1896,  1896,  1904,  1909,  1914,
    1919,  1919,  1927,  1930,  1933,  1936,  1939,  1945,  1945,  1955,
    1955,  1962,  1962,  1969,  1969,  1981,  1981,  1991,  1991,  2002,
    2003,  2007,  2011,  2011,  2023,  2024,  2028,  2028,  2036,  2037,
    2040,  2041,  2042,  2043,  2044,  2045,  2046,  2049,  2054,  2054,
    2062,  2062,  2072,  2073,  2076,  2076,  2084,  2085,  2088,  2089,
    2090,  2091,  2094,  2094,  2102,  2107,  2112
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
#line 4730 "dhcp4_parser.cc"

#line 2117 "dhcp4_parser.yy"


void
isc::dhcp::Dhcp4Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
