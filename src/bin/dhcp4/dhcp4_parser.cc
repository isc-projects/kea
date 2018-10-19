// A Bison parser, made by GNU Bison 3.1.

// Skeleton implementation for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015, 2018 Free Software Foundation, Inc.

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

// Take the name prefix into account.
#define yylex   parser4_lex

// First part of user declarations.

#line 39 "dhcp4_parser.cc" // lalr1.cc:407

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

#include "dhcp4_parser.h"

// User implementation prologue.

#line 53 "dhcp4_parser.cc" // lalr1.cc:415
// Unqualified %code blocks.
#line 34 "dhcp4_parser.yy" // lalr1.cc:416

#include <dhcp4/parser_context.h>

#line 59 "dhcp4_parser.cc" // lalr1.cc:416


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
    while (/*CONSTCOND*/ false)
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

#line 14 "dhcp4_parser.yy" // lalr1.cc:491
namespace isc { namespace dhcp {
#line 154 "dhcp4_parser.cc" // lalr1.cc:491

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
        std::string yyr = "";
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
              // Fall through.
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


  /*---------------.
  | Symbol types.  |
  `---------------*/



  // by_state.
  Dhcp4Parser::by_state::by_state ()
    : state (empty_state)
  {}

  Dhcp4Parser::by_state::by_state (const by_state& other)
    : state (other.state)
  {}

  void
  Dhcp4Parser::by_state::clear ()
  {
    state = empty_state;
  }

  void
  Dhcp4Parser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  Dhcp4Parser::by_state::by_state (state_type s)
    : state (s)
  {}

  Dhcp4Parser::symbol_number_type
  Dhcp4Parser::by_state::type_get () const
  {
    if (state == empty_state)
      return empty_symbol;
    else
      return yystos_[state];
  }

  Dhcp4Parser::stack_symbol_type::stack_symbol_type ()
  {}

  Dhcp4Parser::stack_symbol_type::stack_symbol_type (const stack_symbol_type& that)
    : super_type (that.state, that.location)
  {
    switch (that.type_get ())
    {
      case 185: // value
      case 189: // map_value
      case 230: // socket_type
      case 233: // outbound_interface_value
      case 255: // db_type
      case 337: // hr_mode
      case 484: // ncr_protocol_value
      case 492: // replace_client_name_value
        value.copy< ElementPtr > (that.value);
        break;

      case 168: // "boolean"
        value.copy< bool > (that.value);
        break;

      case 167: // "floating point"
        value.copy< double > (that.value);
        break;

      case 166: // "integer"
        value.copy< int64_t > (that.value);
        break;

      case 165: // "constant string"
        value.copy< std::string > (that.value);
        break;

      default:
        break;
    }

  }

  Dhcp4Parser::stack_symbol_type::stack_symbol_type (state_type s, symbol_type& that)
    : super_type (s, that.location)
  {
    switch (that.type_get ())
    {
      case 185: // value
      case 189: // map_value
      case 230: // socket_type
      case 233: // outbound_interface_value
      case 255: // db_type
      case 337: // hr_mode
      case 484: // ncr_protocol_value
      case 492: // replace_client_name_value
        value.move< ElementPtr > (that.value);
        break;

      case 168: // "boolean"
        value.move< bool > (that.value);
        break;

      case 167: // "floating point"
        value.move< double > (that.value);
        break;

      case 166: // "integer"
        value.move< int64_t > (that.value);
        break;

      case 165: // "constant string"
        value.move< std::string > (that.value);
        break;

      default:
        break;
    }

    // that is emptied.
    that.type = empty_symbol;
  }

  Dhcp4Parser::stack_symbol_type&
  Dhcp4Parser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
    switch (that.type_get ())
    {
      case 185: // value
      case 189: // map_value
      case 230: // socket_type
      case 233: // outbound_interface_value
      case 255: // db_type
      case 337: // hr_mode
      case 484: // ncr_protocol_value
      case 492: // replace_client_name_value
        value.copy< ElementPtr > (that.value);
        break;

      case 168: // "boolean"
        value.copy< bool > (that.value);
        break;

      case 167: // "floating point"
        value.copy< double > (that.value);
        break;

      case 166: // "integer"
        value.copy< int64_t > (that.value);
        break;

      case 165: // "constant string"
        value.copy< std::string > (that.value);
        break;

      default:
        break;
    }

    location = that.location;
    return *this;
  }


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
    // Avoid a (spurious) G++ 4.8 warning about "array subscript is
    // below array bounds".
    if (yysym.empty ())
      std::abort ();
    yyo << (yytype < yyntokens_ ? "token" : "nterm")
        << ' ' << yytname_[yytype] << " ("
        << yysym.location << ": ";
    switch (yytype)
    {
            case 165: // "constant string"

#line 244 "dhcp4_parser.yy" // lalr1.cc:644
        { yyoutput << yysym.value.template as< std::string > (); }
#line 402 "dhcp4_parser.cc" // lalr1.cc:644
        break;

      case 166: // "integer"

#line 244 "dhcp4_parser.yy" // lalr1.cc:644
        { yyoutput << yysym.value.template as< int64_t > (); }
#line 409 "dhcp4_parser.cc" // lalr1.cc:644
        break;

      case 167: // "floating point"

#line 244 "dhcp4_parser.yy" // lalr1.cc:644
        { yyoutput << yysym.value.template as< double > (); }
#line 416 "dhcp4_parser.cc" // lalr1.cc:644
        break;

      case 168: // "boolean"

#line 244 "dhcp4_parser.yy" // lalr1.cc:644
        { yyoutput << yysym.value.template as< bool > (); }
#line 423 "dhcp4_parser.cc" // lalr1.cc:644
        break;

      case 185: // value

#line 244 "dhcp4_parser.yy" // lalr1.cc:644
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 430 "dhcp4_parser.cc" // lalr1.cc:644
        break;

      case 189: // map_value

#line 244 "dhcp4_parser.yy" // lalr1.cc:644
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 437 "dhcp4_parser.cc" // lalr1.cc:644
        break;

      case 230: // socket_type

#line 244 "dhcp4_parser.yy" // lalr1.cc:644
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 444 "dhcp4_parser.cc" // lalr1.cc:644
        break;

      case 233: // outbound_interface_value

#line 244 "dhcp4_parser.yy" // lalr1.cc:644
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 451 "dhcp4_parser.cc" // lalr1.cc:644
        break;

      case 255: // db_type

#line 244 "dhcp4_parser.yy" // lalr1.cc:644
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 458 "dhcp4_parser.cc" // lalr1.cc:644
        break;

      case 337: // hr_mode

#line 244 "dhcp4_parser.yy" // lalr1.cc:644
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 465 "dhcp4_parser.cc" // lalr1.cc:644
        break;

      case 484: // ncr_protocol_value

#line 244 "dhcp4_parser.yy" // lalr1.cc:644
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 472 "dhcp4_parser.cc" // lalr1.cc:644
        break;

      case 492: // replace_client_name_value

#line 244 "dhcp4_parser.yy" // lalr1.cc:644
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 479 "dhcp4_parser.cc" // lalr1.cc:644
        break;


      default:
        break;
    }
    yyo << ')';
  }
#endif

  void
  Dhcp4Parser::yypush_ (const char* m, state_type s, symbol_type& sym)
  {
    stack_symbol_type t (s, sym);
    yypush_ (m, t);
  }

  void
  Dhcp4Parser::yypush_ (const char* m, stack_symbol_type& s)
  {
    if (m)
      YY_SYMBOL_PRINT (m, s);
    yystack_.push (s);
  }

  void
  Dhcp4Parser::yypop_ (unsigned n)
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
    yypush_ (YY_NULLPTR, 0, yyla);

    // A new symbol was pushed on the stack.
  yynewstate:
    YYCDEBUG << "Entering state " << yystack_[0].state << '\n';

    // Accept?
    if (yystack_[0].state == yyfinal_)
      goto yyacceptlab;

    goto yybackup;

    // Backup.
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
    yypush_ ("Shifting", yyn, yyla);
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
  | yyreduce -- Do a reduction.  |
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
      case 185: // value
      case 189: // map_value
      case 230: // socket_type
      case 233: // outbound_interface_value
      case 255: // db_type
      case 337: // hr_mode
      case 484: // ncr_protocol_value
      case 492: // replace_client_name_value
        yylhs.value.build< ElementPtr > ();
        break;

      case 168: // "boolean"
        yylhs.value.build< bool > ();
        break;

      case 167: // "floating point"
        yylhs.value.build< double > ();
        break;

      case 166: // "integer"
        yylhs.value.build< int64_t > ();
        break;

      case 165: // "constant string"
        yylhs.value.build< std::string > ();
        break;

      default:
        break;
    }


      // Default location.
      {
        slice<stack_symbol_type, stack_type> slice (yystack_, yylen);
        YYLLOC_DEFAULT (yylhs.location, slice, yylen);
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
#line 253 "dhcp4_parser.yy" // lalr1.cc:870
    { ctx.ctx_ = ctx.NO_KEYWORD; }
#line 729 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 4:
#line 254 "dhcp4_parser.yy" // lalr1.cc:870
    { ctx.ctx_ = ctx.CONFIG; }
#line 735 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 6:
#line 255 "dhcp4_parser.yy" // lalr1.cc:870
    { ctx.ctx_ = ctx.DHCP4; }
#line 741 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 8:
#line 256 "dhcp4_parser.yy" // lalr1.cc:870
    { ctx.ctx_ = ctx.INTERFACES_CONFIG; }
#line 747 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 10:
#line 257 "dhcp4_parser.yy" // lalr1.cc:870
    { ctx.ctx_ = ctx.SUBNET4; }
#line 753 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 12:
#line 258 "dhcp4_parser.yy" // lalr1.cc:870
    { ctx.ctx_ = ctx.POOLS; }
#line 759 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 14:
#line 259 "dhcp4_parser.yy" // lalr1.cc:870
    { ctx.ctx_ = ctx.RESERVATIONS; }
#line 765 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 16:
#line 260 "dhcp4_parser.yy" // lalr1.cc:870
    { ctx.ctx_ = ctx.DHCP4; }
#line 771 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 18:
#line 261 "dhcp4_parser.yy" // lalr1.cc:870
    { ctx.ctx_ = ctx.OPTION_DEF; }
#line 777 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 20:
#line 262 "dhcp4_parser.yy" // lalr1.cc:870
    { ctx.ctx_ = ctx.OPTION_DATA; }
#line 783 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 22:
#line 263 "dhcp4_parser.yy" // lalr1.cc:870
    { ctx.ctx_ = ctx.HOOKS_LIBRARIES; }
#line 789 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 24:
#line 264 "dhcp4_parser.yy" // lalr1.cc:870
    { ctx.ctx_ = ctx.DHCP_DDNS; }
#line 795 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 26:
#line 265 "dhcp4_parser.yy" // lalr1.cc:870
    { ctx.ctx_ = ctx.LOGGING; }
#line 801 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 28:
#line 266 "dhcp4_parser.yy" // lalr1.cc:870
    { ctx.ctx_ = ctx.CONFIG_CONTROL; }
#line 807 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 30:
#line 274 "dhcp4_parser.yy" // lalr1.cc:870
    { yylhs.value.as< ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 813 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 31:
#line 275 "dhcp4_parser.yy" // lalr1.cc:870
    { yylhs.value.as< ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as< double > (), ctx.loc2pos(yystack_[0].location))); }
#line 819 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 32:
#line 276 "dhcp4_parser.yy" // lalr1.cc:870
    { yylhs.value.as< ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 825 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 33:
#line 277 "dhcp4_parser.yy" // lalr1.cc:870
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 831 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 34:
#line 278 "dhcp4_parser.yy" // lalr1.cc:870
    { yylhs.value.as< ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 837 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 35:
#line 279 "dhcp4_parser.yy" // lalr1.cc:870
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 843 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 36:
#line 280 "dhcp4_parser.yy" // lalr1.cc:870
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 849 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 37:
#line 283 "dhcp4_parser.yy" // lalr1.cc:870
    {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as< ElementPtr > ());
}
#line 858 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 38:
#line 288 "dhcp4_parser.yy" // lalr1.cc:870
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 869 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 39:
#line 293 "dhcp4_parser.yy" // lalr1.cc:870
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 879 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 40:
#line 299 "dhcp4_parser.yy" // lalr1.cc:870
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 885 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 43:
#line 306 "dhcp4_parser.yy" // lalr1.cc:870
    {
                  // map containing a single entry
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 894 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 44:
#line 310 "dhcp4_parser.yy" // lalr1.cc:870
    {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 904 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 45:
#line 317 "dhcp4_parser.yy" // lalr1.cc:870
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 913 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 46:
#line 320 "dhcp4_parser.yy" // lalr1.cc:870
    {
    // list parsing complete. Put any sanity checking here
}
#line 921 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 49:
#line 328 "dhcp4_parser.yy" // lalr1.cc:870
    {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 930 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 50:
#line 332 "dhcp4_parser.yy" // lalr1.cc:870
    {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 939 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 51:
#line 339 "dhcp4_parser.yy" // lalr1.cc:870
    {
    // List parsing about to start
}
#line 947 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 52:
#line 341 "dhcp4_parser.yy" // lalr1.cc:870
    {
    // list parsing complete. Put any sanity checking here
    //ctx.stack_.pop_back();
}
#line 956 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 55:
#line 350 "dhcp4_parser.yy" // lalr1.cc:870
    {
                          ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 965 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 56:
#line 354 "dhcp4_parser.yy" // lalr1.cc:870
    {
                          ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 974 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 57:
#line 365 "dhcp4_parser.yy" // lalr1.cc:870
    {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as< std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 985 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 58:
#line 375 "dhcp4_parser.yy" // lalr1.cc:870
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 996 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 59:
#line 380 "dhcp4_parser.yy" // lalr1.cc:870
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.

    // Dhcp4 is required
    ctx.require("Dhcp4", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
}
#line 1009 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 68:
#line 404 "dhcp4_parser.yy" // lalr1.cc:870
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Dhcp4", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP4);
}
#line 1022 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 69:
#line 411 "dhcp4_parser.yy" // lalr1.cc:870
    {
    // No global parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1032 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 70:
#line 419 "dhcp4_parser.yy" // lalr1.cc:870
    {
    // Parse the Dhcp4 map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1042 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 71:
#line 423 "dhcp4_parser.yy" // lalr1.cc:870
    {
    // No global parameter is required
    // parsing completed
}
#line 1051 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 106:
#line 468 "dhcp4_parser.yy" // lalr1.cc:870
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 1060 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 107:
#line 473 "dhcp4_parser.yy" // lalr1.cc:870
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 1069 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 108:
#line 478 "dhcp4_parser.yy" // lalr1.cc:870
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 1078 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 109:
#line 483 "dhcp4_parser.yy" // lalr1.cc:870
    {
    ElementPtr dpp(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 1087 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 110:
#line 488 "dhcp4_parser.yy" // lalr1.cc:870
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1095 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 111:
#line 490 "dhcp4_parser.yy" // lalr1.cc:870
    {
    ElementPtr stag(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-tag", stag);
    ctx.leave();
}
#line 1105 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 112:
#line 496 "dhcp4_parser.yy" // lalr1.cc:870
    {
    ElementPtr echo(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("echo-client-id", echo);
}
#line 1114 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 113:
#line 501 "dhcp4_parser.yy" // lalr1.cc:870
    {
    ElementPtr match(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("match-client-id", match);
}
#line 1123 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 114:
#line 506 "dhcp4_parser.yy" // lalr1.cc:870
    {
    ElementPtr prf(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("authoritative", prf);
}
#line 1132 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 115:
#line 512 "dhcp4_parser.yy" // lalr1.cc:870
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces-config", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.INTERFACES_CONFIG);
}
#line 1143 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 116:
#line 517 "dhcp4_parser.yy" // lalr1.cc:870
    {
    // No interfaces config param is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1153 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 126:
#line 536 "dhcp4_parser.yy" // lalr1.cc:870
    {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1163 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 127:
#line 540 "dhcp4_parser.yy" // lalr1.cc:870
    {
    // No interfaces config param is required
    // parsing completed
}
#line 1172 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 128:
#line 545 "dhcp4_parser.yy" // lalr1.cc:870
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1183 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 129:
#line 550 "dhcp4_parser.yy" // lalr1.cc:870
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1192 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 130:
#line 555 "dhcp4_parser.yy" // lalr1.cc:870
    {
    ctx.enter(ctx.DHCP_SOCKET_TYPE);
}
#line 1200 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 131:
#line 557 "dhcp4_parser.yy" // lalr1.cc:870
    {
    ctx.stack_.back()->set("dhcp-socket-type", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1209 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 132:
#line 562 "dhcp4_parser.yy" // lalr1.cc:870
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("raw", ctx.loc2pos(yystack_[0].location))); }
#line 1215 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 133:
#line 563 "dhcp4_parser.yy" // lalr1.cc:870
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("udp", ctx.loc2pos(yystack_[0].location))); }
#line 1221 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 134:
#line 566 "dhcp4_parser.yy" // lalr1.cc:870
    {
    ctx.enter(ctx.OUTBOUND_INTERFACE);
}
#line 1229 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 135:
#line 568 "dhcp4_parser.yy" // lalr1.cc:870
    {
    ctx.stack_.back()->set("outbound-interface", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1238 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 136:
#line 573 "dhcp4_parser.yy" // lalr1.cc:870
    {
    yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("same-as-inbound", ctx.loc2pos(yystack_[0].location)));
}
#line 1246 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 137:
#line 575 "dhcp4_parser.yy" // lalr1.cc:870
    {
    yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("use-routing", ctx.loc2pos(yystack_[0].location)));
    }
#line 1254 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 138:
#line 579 "dhcp4_parser.yy" // lalr1.cc:870
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("re-detect", b);
}
#line 1263 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 139:
#line 585 "dhcp4_parser.yy" // lalr1.cc:870
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lease-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.LEASE_DATABASE);
}
#line 1274 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 140:
#line 590 "dhcp4_parser.yy" // lalr1.cc:870
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1285 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 141:
#line 597 "dhcp4_parser.yy" // lalr1.cc:870
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sanity-checks", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SANITY_CHECKS);
}
#line 1296 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 142:
#line 602 "dhcp4_parser.yy" // lalr1.cc:870
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1305 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 146:
#line 612 "dhcp4_parser.yy" // lalr1.cc:870
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1313 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 147:
#line 614 "dhcp4_parser.yy" // lalr1.cc:870
    {

    if ( (string(yystack_[0].value.as< std::string > ()) == "none") ||
         (string(yystack_[0].value.as< std::string > ()) == "warn") ||
         (string(yystack_[0].value.as< std::string > ()) == "fix") ||
         (string(yystack_[0].value.as< std::string > ()) == "fix-del") ||
         (string(yystack_[0].value.as< std::string > ()) == "del")) {
        ElementPtr user(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
        ctx.stack_.back()->set("lease-checks", user);
        ctx.leave();
    } else {
        error(yystack_[0].location, "Unsupported 'lease-checks value: " + string(yystack_[0].value.as< std::string > ()) +
              ", supported values are: none, warn, fix, fix-del, del");
    }
}
#line 1333 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 148:
#line 630 "dhcp4_parser.yy" // lalr1.cc:870
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1344 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 149:
#line 635 "dhcp4_parser.yy" // lalr1.cc:870
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1355 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 150:
#line 642 "dhcp4_parser.yy" // lalr1.cc:870
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1366 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 151:
#line 647 "dhcp4_parser.yy" // lalr1.cc:870
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1375 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 156:
#line 660 "dhcp4_parser.yy" // lalr1.cc:870
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1385 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 157:
#line 664 "dhcp4_parser.yy" // lalr1.cc:870
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1395 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 178:
#line 694 "dhcp4_parser.yy" // lalr1.cc:870
    {
    ctx.enter(ctx.DATABASE_TYPE);
}
#line 1403 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 179:
#line 696 "dhcp4_parser.yy" // lalr1.cc:870
    {
    ctx.stack_.back()->set("type", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1412 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 180:
#line 701 "dhcp4_parser.yy" // lalr1.cc:870
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("memfile", ctx.loc2pos(yystack_[0].location))); }
#line 1418 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 181:
#line 702 "dhcp4_parser.yy" // lalr1.cc:870
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("mysql", ctx.loc2pos(yystack_[0].location))); }
#line 1424 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 182:
#line 703 "dhcp4_parser.yy" // lalr1.cc:870
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("postgresql", ctx.loc2pos(yystack_[0].location))); }
#line 1430 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 183:
#line 704 "dhcp4_parser.yy" // lalr1.cc:870
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("cql", ctx.loc2pos(yystack_[0].location))); }
#line 1436 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 184:
#line 707 "dhcp4_parser.yy" // lalr1.cc:870
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1444 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 185:
#line 709 "dhcp4_parser.yy" // lalr1.cc:870
    {
    ElementPtr user(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1454 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 186:
#line 715 "dhcp4_parser.yy" // lalr1.cc:870
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1462 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 187:
#line 717 "dhcp4_parser.yy" // lalr1.cc:870
    {
    ElementPtr pwd(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 1472 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 188:
#line 723 "dhcp4_parser.yy" // lalr1.cc:870
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1480 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 189:
#line 725 "dhcp4_parser.yy" // lalr1.cc:870
    {
    ElementPtr h(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 1490 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 190:
#line 731 "dhcp4_parser.yy" // lalr1.cc:870
    {
    ElementPtr p(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", p);
}
#line 1499 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 191:
#line 736 "dhcp4_parser.yy" // lalr1.cc:870
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1507 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 192:
#line 738 "dhcp4_parser.yy" // lalr1.cc:870
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1517 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 193:
#line 744 "dhcp4_parser.yy" // lalr1.cc:870
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 1526 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 194:
#line 749 "dhcp4_parser.yy" // lalr1.cc:870
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 1535 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 195:
#line 754 "dhcp4_parser.yy" // lalr1.cc:870
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 1544 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 196:
#line 759 "dhcp4_parser.yy" // lalr1.cc:870
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("connect-timeout", n);
}
#line 1553 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 197:
#line 764 "dhcp4_parser.yy" // lalr1.cc:870
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("request-timeout", n);
}
#line 1562 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 198:
#line 769 "dhcp4_parser.yy" // lalr1.cc:870
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-keepalive", n);
}
#line 1571 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 199:
#line 774 "dhcp4_parser.yy" // lalr1.cc:870
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-nodelay", n);
}
#line 1580 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 200:
#line 779 "dhcp4_parser.yy" // lalr1.cc:870
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1588 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 201:
#line 781 "dhcp4_parser.yy" // lalr1.cc:870
    {
    ElementPtr cp(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("contact-points", cp);
    ctx.leave();
}
#line 1598 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 202:
#line 787 "dhcp4_parser.yy" // lalr1.cc:870
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1606 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 203:
#line 789 "dhcp4_parser.yy" // lalr1.cc:870
    {
    ElementPtr ks(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("keyspace", ks);
    ctx.leave();
}
#line 1616 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 204:
#line 795 "dhcp4_parser.yy" // lalr1.cc:870
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reconnect-tries", n);
}
#line 1625 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 205:
#line 800 "dhcp4_parser.yy" // lalr1.cc:870
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reconnect-wait-time", n);
}
#line 1634 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 206:
#line 805 "dhcp4_parser.yy" // lalr1.cc:870
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 1645 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 207:
#line 810 "dhcp4_parser.yy" // lalr1.cc:870
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1654 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 215:
#line 826 "dhcp4_parser.yy" // lalr1.cc:870
    {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1663 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 216:
#line 831 "dhcp4_parser.yy" // lalr1.cc:870
    {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 1672 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 217:
#line 836 "dhcp4_parser.yy" // lalr1.cc:870
    {
    ElementPtr circuit(new StringElement("circuit-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(circuit);
}
#line 1681 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 218:
#line 841 "dhcp4_parser.yy" // lalr1.cc:870
    {
    ElementPtr client(new StringElement("client-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(client);
}
#line 1690 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 219:
#line 846 "dhcp4_parser.yy" // lalr1.cc:870
    {
    ElementPtr flex_id(new StringElement("flex-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(flex_id);
}
#line 1699 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 220:
#line 851 "dhcp4_parser.yy" // lalr1.cc:870
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 1710 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 221:
#line 856 "dhcp4_parser.yy" // lalr1.cc:870
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1719 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 226:
#line 869 "dhcp4_parser.yy" // lalr1.cc:870
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1729 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 227:
#line 873 "dhcp4_parser.yy" // lalr1.cc:870
    {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1739 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 228:
#line 879 "dhcp4_parser.yy" // lalr1.cc:870
    {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1749 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 229:
#line 883 "dhcp4_parser.yy" // lalr1.cc:870
    {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 1759 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 235:
#line 898 "dhcp4_parser.yy" // lalr1.cc:870
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1767 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 236:
#line 900 "dhcp4_parser.yy" // lalr1.cc:870
    {
    ElementPtr lib(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 1777 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 237:
#line 906 "dhcp4_parser.yy" // lalr1.cc:870
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1785 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 238:
#line 908 "dhcp4_parser.yy" // lalr1.cc:870
    {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1794 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 239:
#line 914 "dhcp4_parser.yy" // lalr1.cc:870
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.EXPIRED_LEASES_PROCESSING);
}
#line 1805 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 240:
#line 919 "dhcp4_parser.yy" // lalr1.cc:870
    {
    // No expired lease parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1815 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 249:
#line 937 "dhcp4_parser.yy" // lalr1.cc:870
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 1824 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 250:
#line 942 "dhcp4_parser.yy" // lalr1.cc:870
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 1833 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 251:
#line 947 "dhcp4_parser.yy" // lalr1.cc:870
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 1842 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 252:
#line 952 "dhcp4_parser.yy" // lalr1.cc:870
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 1851 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 253:
#line 957 "dhcp4_parser.yy" // lalr1.cc:870
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 1860 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 254:
#line 962 "dhcp4_parser.yy" // lalr1.cc:870
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 1869 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 255:
#line 970 "dhcp4_parser.yy" // lalr1.cc:870
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet4", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET4);
}
#line 1880 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 256:
#line 975 "dhcp4_parser.yy" // lalr1.cc:870
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1889 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 261:
#line 995 "dhcp4_parser.yy" // lalr1.cc:870
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1899 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 262:
#line 999 "dhcp4_parser.yy" // lalr1.cc:870
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
#line 1925 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 263:
#line 1021 "dhcp4_parser.yy" // lalr1.cc:870
    {
    // Parse the subnet4 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1935 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 264:
#line 1025 "dhcp4_parser.yy" // lalr1.cc:870
    {
    // The subnet subnet4 parameter is required
    ctx.require("subnet", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 1945 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 291:
#line 1063 "dhcp4_parser.yy" // lalr1.cc:870
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1953 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 292:
#line 1065 "dhcp4_parser.yy" // lalr1.cc:870
    {
    ElementPtr subnet(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 1963 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 293:
#line 1071 "dhcp4_parser.yy" // lalr1.cc:870
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1971 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 294:
#line 1073 "dhcp4_parser.yy" // lalr1.cc:870
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface", iface);
    ctx.leave();
}
#line 1981 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 295:
#line 1079 "dhcp4_parser.yy" // lalr1.cc:870
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1989 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 296:
#line 1081 "dhcp4_parser.yy" // lalr1.cc:870
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface-id", iface);
    ctx.leave();
}
#line 1999 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 297:
#line 1087 "dhcp4_parser.yy" // lalr1.cc:870
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2007 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 298:
#line 1089 "dhcp4_parser.yy" // lalr1.cc:870
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-subnet", iface);
    ctx.leave();
}
#line 2017 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 299:
#line 1095 "dhcp4_parser.yy" // lalr1.cc:870
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2025 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 300:
#line 1097 "dhcp4_parser.yy" // lalr1.cc:870
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 2035 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 301:
#line 1103 "dhcp4_parser.yy" // lalr1.cc:870
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2043 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 302:
#line 1105 "dhcp4_parser.yy" // lalr1.cc:870
    {
    ElementPtr cls(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 2053 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 303:
#line 1111 "dhcp4_parser.yy" // lalr1.cc:870
    {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("require-client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2064 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 304:
#line 1116 "dhcp4_parser.yy" // lalr1.cc:870
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2073 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 305:
#line 1121 "dhcp4_parser.yy" // lalr1.cc:870
    {
    ctx.enter(ctx.RESERVATION_MODE);
}
#line 2081 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 306:
#line 1123 "dhcp4_parser.yy" // lalr1.cc:870
    {
    ctx.stack_.back()->set("reservation-mode", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2090 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 307:
#line 1128 "dhcp4_parser.yy" // lalr1.cc:870
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("disabled", ctx.loc2pos(yystack_[0].location))); }
#line 2096 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 308:
#line 1129 "dhcp4_parser.yy" // lalr1.cc:870
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("out-of-pool", ctx.loc2pos(yystack_[0].location))); }
#line 2102 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 309:
#line 1130 "dhcp4_parser.yy" // lalr1.cc:870
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("global", ctx.loc2pos(yystack_[0].location))); }
#line 2108 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 310:
#line 1131 "dhcp4_parser.yy" // lalr1.cc:870
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("all", ctx.loc2pos(yystack_[0].location))); }
#line 2114 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 311:
#line 1134 "dhcp4_parser.yy" // lalr1.cc:870
    {
    ElementPtr id(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 2123 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 312:
#line 1141 "dhcp4_parser.yy" // lalr1.cc:870
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("shared-networks", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SHARED_NETWORK);
}
#line 2134 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 313:
#line 1146 "dhcp4_parser.yy" // lalr1.cc:870
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2143 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 318:
#line 1161 "dhcp4_parser.yy" // lalr1.cc:870
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2153 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 319:
#line 1165 "dhcp4_parser.yy" // lalr1.cc:870
    {
    ctx.stack_.pop_back();
}
#line 2161 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 341:
#line 1198 "dhcp4_parser.yy" // lalr1.cc:870
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 2172 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 342:
#line 1203 "dhcp4_parser.yy" // lalr1.cc:870
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2181 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 343:
#line 1211 "dhcp4_parser.yy" // lalr1.cc:870
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2190 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 344:
#line 1214 "dhcp4_parser.yy" // lalr1.cc:870
    {
    // parsing completed
}
#line 2198 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 349:
#line 1230 "dhcp4_parser.yy" // lalr1.cc:870
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2208 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 350:
#line 1234 "dhcp4_parser.yy" // lalr1.cc:870
    {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2220 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 351:
#line 1245 "dhcp4_parser.yy" // lalr1.cc:870
    {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2230 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 352:
#line 1249 "dhcp4_parser.yy" // lalr1.cc:870
    {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2242 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 368:
#line 1281 "dhcp4_parser.yy" // lalr1.cc:870
    {
    ElementPtr code(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 2251 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 370:
#line 1288 "dhcp4_parser.yy" // lalr1.cc:870
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2259 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 371:
#line 1290 "dhcp4_parser.yy" // lalr1.cc:870
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 2269 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 372:
#line 1296 "dhcp4_parser.yy" // lalr1.cc:870
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2277 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 373:
#line 1298 "dhcp4_parser.yy" // lalr1.cc:870
    {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 2287 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 374:
#line 1304 "dhcp4_parser.yy" // lalr1.cc:870
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2295 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 375:
#line 1306 "dhcp4_parser.yy" // lalr1.cc:870
    {
    ElementPtr space(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 2305 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 377:
#line 1314 "dhcp4_parser.yy" // lalr1.cc:870
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2313 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 378:
#line 1316 "dhcp4_parser.yy" // lalr1.cc:870
    {
    ElementPtr encap(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 2323 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 379:
#line 1322 "dhcp4_parser.yy" // lalr1.cc:870
    {
    ElementPtr array(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 2332 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 380:
#line 1331 "dhcp4_parser.yy" // lalr1.cc:870
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 2343 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 381:
#line 1336 "dhcp4_parser.yy" // lalr1.cc:870
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2352 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 386:
#line 1355 "dhcp4_parser.yy" // lalr1.cc:870
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2362 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 387:
#line 1359 "dhcp4_parser.yy" // lalr1.cc:870
    {
    /// @todo: the code or name parameters are required.
    ctx.stack_.pop_back();
}
#line 2371 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 388:
#line 1367 "dhcp4_parser.yy" // lalr1.cc:870
    {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2381 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 389:
#line 1371 "dhcp4_parser.yy" // lalr1.cc:870
    {
    /// @todo: the code or name parameters are required.
    // parsing completed
}
#line 2390 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 404:
#line 1404 "dhcp4_parser.yy" // lalr1.cc:870
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2398 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 405:
#line 1406 "dhcp4_parser.yy" // lalr1.cc:870
    {
    ElementPtr data(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 2408 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 408:
#line 1416 "dhcp4_parser.yy" // lalr1.cc:870
    {
    ElementPtr space(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", space);
}
#line 2417 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 409:
#line 1421 "dhcp4_parser.yy" // lalr1.cc:870
    {
    ElementPtr persist(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-send", persist);
}
#line 2426 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 410:
#line 1429 "dhcp4_parser.yy" // lalr1.cc:870
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 2437 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 411:
#line 1434 "dhcp4_parser.yy" // lalr1.cc:870
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2446 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 416:
#line 1449 "dhcp4_parser.yy" // lalr1.cc:870
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2456 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 417:
#line 1453 "dhcp4_parser.yy" // lalr1.cc:870
    {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2466 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 418:
#line 1459 "dhcp4_parser.yy" // lalr1.cc:870
    {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2476 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 419:
#line 1463 "dhcp4_parser.yy" // lalr1.cc:870
    {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2486 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 429:
#line 1482 "dhcp4_parser.yy" // lalr1.cc:870
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2494 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 430:
#line 1484 "dhcp4_parser.yy" // lalr1.cc:870
    {
    ElementPtr pool(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 2504 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 431:
#line 1490 "dhcp4_parser.yy" // lalr1.cc:870
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2512 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 432:
#line 1492 "dhcp4_parser.yy" // lalr1.cc:870
    {
    ElementPtr parent = ctx.stack_.back();
    ElementPtr user_context = yystack_[0].value.as< ElementPtr > ();
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
#line 2539 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 433:
#line 1515 "dhcp4_parser.yy" // lalr1.cc:870
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2547 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 434:
#line 1517 "dhcp4_parser.yy" // lalr1.cc:870
    {
    ElementPtr parent = ctx.stack_.back();
    ElementPtr user_context(new MapElement(ctx.loc2pos(yystack_[3].location)));
    ElementPtr comment(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
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
#line 2576 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 435:
#line 1545 "dhcp4_parser.yy" // lalr1.cc:870
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 2587 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 436:
#line 1550 "dhcp4_parser.yy" // lalr1.cc:870
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2596 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 441:
#line 1563 "dhcp4_parser.yy" // lalr1.cc:870
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2606 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 442:
#line 1567 "dhcp4_parser.yy" // lalr1.cc:870
    {
    /// @todo: an identifier parameter is required.
    ctx.stack_.pop_back();
}
#line 2615 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 443:
#line 1572 "dhcp4_parser.yy" // lalr1.cc:870
    {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2625 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 444:
#line 1576 "dhcp4_parser.yy" // lalr1.cc:870
    {
    /// @todo: an identifier parameter is required.
    // parsing completed
}
#line 2634 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 464:
#line 1607 "dhcp4_parser.yy" // lalr1.cc:870
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2642 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 465:
#line 1609 "dhcp4_parser.yy" // lalr1.cc:870
    {
    ElementPtr next_server(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("next-server", next_server);
    ctx.leave();
}
#line 2652 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 466:
#line 1615 "dhcp4_parser.yy" // lalr1.cc:870
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2660 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 467:
#line 1617 "dhcp4_parser.yy" // lalr1.cc:870
    {
    ElementPtr srv(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-hostname", srv);
    ctx.leave();
}
#line 2670 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 468:
#line 1623 "dhcp4_parser.yy" // lalr1.cc:870
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2678 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 469:
#line 1625 "dhcp4_parser.yy" // lalr1.cc:870
    {
    ElementPtr bootfile(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("boot-file-name", bootfile);
    ctx.leave();
}
#line 2688 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 470:
#line 1631 "dhcp4_parser.yy" // lalr1.cc:870
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2696 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 471:
#line 1633 "dhcp4_parser.yy" // lalr1.cc:870
    {
    ElementPtr addr(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", addr);
    ctx.leave();
}
#line 2706 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 472:
#line 1639 "dhcp4_parser.yy" // lalr1.cc:870
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-addresses", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2717 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 473:
#line 1644 "dhcp4_parser.yy" // lalr1.cc:870
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2726 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 474:
#line 1649 "dhcp4_parser.yy" // lalr1.cc:870
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2734 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 475:
#line 1651 "dhcp4_parser.yy" // lalr1.cc:870
    {
    ElementPtr d(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 2744 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 476:
#line 1657 "dhcp4_parser.yy" // lalr1.cc:870
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2752 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 477:
#line 1659 "dhcp4_parser.yy" // lalr1.cc:870
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 2762 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 478:
#line 1665 "dhcp4_parser.yy" // lalr1.cc:870
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2770 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 479:
#line 1667 "dhcp4_parser.yy" // lalr1.cc:870
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-id", hw);
    ctx.leave();
}
#line 2780 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 480:
#line 1673 "dhcp4_parser.yy" // lalr1.cc:870
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2788 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 481:
#line 1675 "dhcp4_parser.yy" // lalr1.cc:870
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("circuit-id", hw);
    ctx.leave();
}
#line 2798 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 482:
#line 1681 "dhcp4_parser.yy" // lalr1.cc:870
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2806 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 483:
#line 1683 "dhcp4_parser.yy" // lalr1.cc:870
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flex-id", hw);
    ctx.leave();
}
#line 2816 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 484:
#line 1689 "dhcp4_parser.yy" // lalr1.cc:870
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2824 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 485:
#line 1691 "dhcp4_parser.yy" // lalr1.cc:870
    {
    ElementPtr host(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 2834 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 486:
#line 1697 "dhcp4_parser.yy" // lalr1.cc:870
    {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2845 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 487:
#line 1702 "dhcp4_parser.yy" // lalr1.cc:870
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2854 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 488:
#line 1710 "dhcp4_parser.yy" // lalr1.cc:870
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 2865 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 489:
#line 1715 "dhcp4_parser.yy" // lalr1.cc:870
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2874 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 492:
#line 1727 "dhcp4_parser.yy" // lalr1.cc:870
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 2885 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 493:
#line 1732 "dhcp4_parser.yy" // lalr1.cc:870
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2894 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 496:
#line 1741 "dhcp4_parser.yy" // lalr1.cc:870
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2904 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 497:
#line 1745 "dhcp4_parser.yy" // lalr1.cc:870
    {
    // The name client class parameter is required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2914 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 514:
#line 1774 "dhcp4_parser.yy" // lalr1.cc:870
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2922 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 515:
#line 1776 "dhcp4_parser.yy" // lalr1.cc:870
    {
    ElementPtr test(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 2932 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 516:
#line 1782 "dhcp4_parser.yy" // lalr1.cc:870
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("only-if-required", b);
}
#line 2941 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 517:
#line 1791 "dhcp4_parser.yy" // lalr1.cc:870
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 2950 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 518:
#line 1798 "dhcp4_parser.yy" // lalr1.cc:870
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 2961 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 519:
#line 1803 "dhcp4_parser.yy" // lalr1.cc:870
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2970 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 527:
#line 1819 "dhcp4_parser.yy" // lalr1.cc:870
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2978 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 528:
#line 1821 "dhcp4_parser.yy" // lalr1.cc:870
    {
    ElementPtr stype(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 2988 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 529:
#line 1827 "dhcp4_parser.yy" // lalr1.cc:870
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2996 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 530:
#line 1829 "dhcp4_parser.yy" // lalr1.cc:870
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 3006 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 531:
#line 1837 "dhcp4_parser.yy" // lalr1.cc:870
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 3017 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 532:
#line 1842 "dhcp4_parser.yy" // lalr1.cc:870
    {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3028 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 533:
#line 1849 "dhcp4_parser.yy" // lalr1.cc:870
    {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3038 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 534:
#line 1853 "dhcp4_parser.yy" // lalr1.cc:870
    {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3048 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 556:
#line 1884 "dhcp4_parser.yy" // lalr1.cc:870
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 3057 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 557:
#line 1889 "dhcp4_parser.yy" // lalr1.cc:870
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3065 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 558:
#line 1891 "dhcp4_parser.yy" // lalr1.cc:870
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("qualifying-suffix", s);
    ctx.leave();
}
#line 3075 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 559:
#line 1897 "dhcp4_parser.yy" // lalr1.cc:870
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3083 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 560:
#line 1899 "dhcp4_parser.yy" // lalr1.cc:870
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 3093 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 561:
#line 1905 "dhcp4_parser.yy" // lalr1.cc:870
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 3102 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 562:
#line 1910 "dhcp4_parser.yy" // lalr1.cc:870
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3110 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 563:
#line 1912 "dhcp4_parser.yy" // lalr1.cc:870
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 3120 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 564:
#line 1918 "dhcp4_parser.yy" // lalr1.cc:870
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 3129 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 565:
#line 1923 "dhcp4_parser.yy" // lalr1.cc:870
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 3138 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 566:
#line 1928 "dhcp4_parser.yy" // lalr1.cc:870
    {
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 3146 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 567:
#line 1930 "dhcp4_parser.yy" // lalr1.cc:870
    {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3155 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 568:
#line 1936 "dhcp4_parser.yy" // lalr1.cc:870
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 3161 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 569:
#line 1937 "dhcp4_parser.yy" // lalr1.cc:870
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 3167 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 570:
#line 1940 "dhcp4_parser.yy" // lalr1.cc:870
    {
    ctx.enter(ctx.NCR_FORMAT);
}
#line 3175 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 571:
#line 1942 "dhcp4_parser.yy" // lalr1.cc:870
    {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 3185 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 572:
#line 1948 "dhcp4_parser.yy" // lalr1.cc:870
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-include-fqdn", b);
}
#line 3194 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 573:
#line 1953 "dhcp4_parser.yy" // lalr1.cc:870
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-no-update", b);
}
#line 3203 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 574:
#line 1958 "dhcp4_parser.yy" // lalr1.cc:870
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-client-update", b);
}
#line 3212 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 575:
#line 1963 "dhcp4_parser.yy" // lalr1.cc:870
    {
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 3220 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 576:
#line 1965 "dhcp4_parser.yy" // lalr1.cc:870
    {
    ctx.stack_.back()->set("replace-client-name", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3229 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 577:
#line 1971 "dhcp4_parser.yy" // lalr1.cc:870
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("when-present", ctx.loc2pos(yystack_[0].location))); 
      }
#line 3237 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 578:
#line 1974 "dhcp4_parser.yy" // lalr1.cc:870
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location)));
      }
#line 3245 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 579:
#line 1977 "dhcp4_parser.yy" // lalr1.cc:870
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("always", ctx.loc2pos(yystack_[0].location)));
      }
#line 3253 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 580:
#line 1980 "dhcp4_parser.yy" // lalr1.cc:870
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("when-not-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 3261 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 581:
#line 1983 "dhcp4_parser.yy" // lalr1.cc:870
    {
      error(yystack_[0].location, "boolean values for the replace-client-name are "
                "no longer supported");
      }
#line 3270 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 582:
#line 1989 "dhcp4_parser.yy" // lalr1.cc:870
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3278 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 583:
#line 1991 "dhcp4_parser.yy" // lalr1.cc:870
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("generated-prefix", s);
    ctx.leave();
}
#line 3288 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 584:
#line 1997 "dhcp4_parser.yy" // lalr1.cc:870
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3296 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 585:
#line 1999 "dhcp4_parser.yy" // lalr1.cc:870
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-set", s);
    ctx.leave();
}
#line 3306 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 586:
#line 2005 "dhcp4_parser.yy" // lalr1.cc:870
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3314 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 587:
#line 2007 "dhcp4_parser.yy" // lalr1.cc:870
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-replacement", s);
    ctx.leave();
}
#line 3324 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 588:
#line 2016 "dhcp4_parser.yy" // lalr1.cc:870
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3332 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 589:
#line 2018 "dhcp4_parser.yy" // lalr1.cc:870
    {
    ctx.stack_.back()->set("Dhcp6", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3341 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 590:
#line 2023 "dhcp4_parser.yy" // lalr1.cc:870
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3349 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 591:
#line 2025 "dhcp4_parser.yy" // lalr1.cc:870
    {
    ctx.stack_.back()->set("DhcpDdns", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3358 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 592:
#line 2030 "dhcp4_parser.yy" // lalr1.cc:870
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3366 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 593:
#line 2032 "dhcp4_parser.yy" // lalr1.cc:870
    {
    ctx.stack_.back()->set("Control-agent", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3375 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 594:
#line 2037 "dhcp4_parser.yy" // lalr1.cc:870
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3385 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 595:
#line 2041 "dhcp4_parser.yy" // lalr1.cc:870
    {
    ctx.stack_.pop_back();
}
#line 3393 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 596:
#line 2046 "dhcp4_parser.yy" // lalr1.cc:870
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-control", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.CONFIG_CONTROL);
}
#line 3404 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 597:
#line 2051 "dhcp4_parser.yy" // lalr1.cc:870
    {
    // No config control params are required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3414 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 598:
#line 2057 "dhcp4_parser.yy" // lalr1.cc:870
    {
    // Parse the config-control map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3424 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 599:
#line 2061 "dhcp4_parser.yy" // lalr1.cc:870
    {
    // No config_control params are required
    // parsing completed
}
#line 3433 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 604:
#line 2076 "dhcp4_parser.yy" // lalr1.cc:870
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CONFIG_DATABASE);
}
#line 3444 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 605:
#line 2081 "dhcp4_parser.yy" // lalr1.cc:870
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3453 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 606:
#line 2091 "dhcp4_parser.yy" // lalr1.cc:870
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Logging", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.LOGGING);
}
#line 3464 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 607:
#line 2096 "dhcp4_parser.yy" // lalr1.cc:870
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3473 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 608:
#line 2101 "dhcp4_parser.yy" // lalr1.cc:870
    {
    // Parse the Logging map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3483 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 609:
#line 2105 "dhcp4_parser.yy" // lalr1.cc:870
    {
    // parsing completed
}
#line 3491 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 613:
#line 2121 "dhcp4_parser.yy" // lalr1.cc:870
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 3502 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 614:
#line 2126 "dhcp4_parser.yy" // lalr1.cc:870
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3511 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 617:
#line 2138 "dhcp4_parser.yy" // lalr1.cc:870
    {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 3521 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 618:
#line 2142 "dhcp4_parser.yy" // lalr1.cc:870
    {
    ctx.stack_.pop_back();
}
#line 3529 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 628:
#line 2159 "dhcp4_parser.yy" // lalr1.cc:870
    {
    ElementPtr dl(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 3538 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 629:
#line 2164 "dhcp4_parser.yy" // lalr1.cc:870
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3546 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 630:
#line 2166 "dhcp4_parser.yy" // lalr1.cc:870
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 3556 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 631:
#line 2172 "dhcp4_parser.yy" // lalr1.cc:870
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 3567 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 632:
#line 2177 "dhcp4_parser.yy" // lalr1.cc:870
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3576 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 635:
#line 2186 "dhcp4_parser.yy" // lalr1.cc:870
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3586 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 636:
#line 2190 "dhcp4_parser.yy" // lalr1.cc:870
    {
    ctx.stack_.pop_back();
}
#line 3594 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 643:
#line 2204 "dhcp4_parser.yy" // lalr1.cc:870
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3602 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 644:
#line 2206 "dhcp4_parser.yy" // lalr1.cc:870
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 3612 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 645:
#line 2212 "dhcp4_parser.yy" // lalr1.cc:870
    {
    ElementPtr flush(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 3621 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 646:
#line 2217 "dhcp4_parser.yy" // lalr1.cc:870
    {
    ElementPtr maxsize(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 3630 "dhcp4_parser.cc" // lalr1.cc:870
    break;

  case 647:
#line 2222 "dhcp4_parser.yy" // lalr1.cc:870
    {
    ElementPtr maxver(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 3639 "dhcp4_parser.cc" // lalr1.cc:870
    break;


#line 3643 "dhcp4_parser.cc" // lalr1.cc:870
            default:
              break;
            }
        }
#if YY_EXCEPTIONS
      catch (const syntax_error& yyexc)
        {
          error (yyexc);
          YYERROR;
        }
#endif // YY_EXCEPTIONS
      YY_SYMBOL_PRINT ("-> $$ =", yylhs);
      yypop_ (yylen);
      yylen = 0;
      YY_STACK_PRINT ();

      // Shift the result of the reduction.
      yypush_ (YY_NULLPTR, yylhs);
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

    /* Pacify compilers like GCC when the user code never invokes
       YYERROR and the label yyerrorlab therefore never appears in user
       code.  */
    if (false)
      goto yyerrorlab;
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
      yypush_ ("Shifting", error_token);
    }
    goto yynewstate;

    // Accept.
  yyacceptlab:
    yyresult = 0;
    goto yyreturn;

    // Abort.
  yyabortlab:
    yyresult = 1;
    goto yyreturn;

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


  const short Dhcp4Parser::yypact_ninf_ = -799;

  const signed char Dhcp4Parser::yytable_ninf_ = -1;

  const short
  Dhcp4Parser::yypact_[] =
  {
     400,  -799,  -799,  -799,  -799,  -799,  -799,  -799,  -799,  -799,
    -799,  -799,  -799,  -799,  -799,    45,    24,    40,    52,    64,
      79,    93,    97,   117,   180,   187,   191,   197,   220,   222,
    -799,  -799,  -799,  -799,  -799,  -799,  -799,  -799,  -799,  -799,
    -799,  -799,  -799,  -799,  -799,  -799,  -799,  -799,  -799,  -799,
    -799,  -799,  -799,  -799,  -799,  -799,  -799,  -799,  -799,  -799,
    -799,  -799,  -799,  -799,  -799,  -799,  -799,  -799,    24,  -127,
      34,    65,    84,   183,    38,   223,    -1,   403,   157,   -40,
     364,     7,    11,  -799,   233,    85,   254,   248,   266,  -799,
    -799,  -799,  -799,  -799,   277,  -799,    46,  -799,  -799,  -799,
    -799,  -799,  -799,  -799,  -799,  -799,  -799,   291,   299,   309,
    -799,  -799,  -799,  -799,  -799,  -799,   322,   341,   345,   350,
    -799,  -799,  -799,  -799,  -799,  -799,  -799,  -799,  -799,  -799,
    -799,  -799,   351,  -799,  -799,  -799,    50,  -799,  -799,  -799,
    -799,  -799,  -799,  -799,  -799,  -799,  -799,  -799,  -799,  -799,
    -799,  -799,  -799,  -799,  -799,  -799,  -799,  -799,  -799,  -799,
    -799,  -799,  -799,  -799,  -799,  -799,  -799,  -799,  -799,  -799,
    -799,  -799,   353,  -799,    57,  -799,  -799,  -799,  -799,  -799,
    -799,  -799,  -799,  -799,  -799,  -799,  -799,  -799,   356,  -799,
    -799,  -799,  -799,  -799,  -799,  -799,  -799,  -799,  -799,    71,
    -799,  -799,  -799,  -799,  -799,  -799,  -799,  -799,  -799,  -799,
    -799,  -799,  -799,  -799,  -799,  -799,  -799,  -799,  -799,  -799,
    -799,  -799,  -799,  -799,    77,  -799,  -799,  -799,  -799,  -799,
    -799,  -799,  -799,  -799,  -799,  -799,  -799,  -799,  -799,  -799,
    -799,   326,   334,  -799,  -799,  -799,  -799,  -799,  -799,  -799,
    -799,  -799,  -799,  -799,  -799,   354,  -799,  -799,   357,  -799,
    -799,  -799,   360,  -799,  -799,   366,   362,  -799,  -799,  -799,
    -799,  -799,  -799,  -799,  -799,  -799,  -799,  -799,  -799,  -799,
     368,   371,  -799,  -799,  -799,  -799,   370,   378,  -799,  -799,
    -799,  -799,  -799,  -799,  -799,  -799,  -799,  -799,  -799,  -799,
     109,  -799,  -799,  -799,   380,  -799,  -799,   382,  -799,   383,
     385,  -799,  -799,   387,   388,   391,  -799,  -799,  -799,  -799,
    -799,  -799,  -799,   140,  -799,  -799,  -799,  -799,  -799,  -799,
    -799,  -799,  -799,  -799,  -799,  -799,  -799,  -799,  -799,  -799,
    -799,  -799,   146,  -799,  -799,  -799,  -799,   147,  -799,  -799,
    -799,    24,    24,  -799,    76,   393,   394,   397,   398,   405,
    -799,    34,  -799,    11,   407,   411,   415,   236,   255,   256,
     416,   421,   423,   425,   426,   427,   216,   271,   272,   273,
     428,   438,   439,   440,   442,   443,   444,   461,   462,   464,
     467,   468,   311,   474,   491,    65,  -799,   492,   493,   494,
     331,    84,  -799,   496,   499,   500,   501,   502,   503,   342,
     506,   508,   509,   510,   183,  -799,   511,    38,  -799,   513,
     514,   515,   516,   519,   520,   521,   522,  -799,   223,  -799,
     523,   526,   365,   528,   529,   531,   372,  -799,   403,   532,
     373,   374,  -799,   157,   535,   539,    36,  -799,   376,   541,
     542,   381,   561,   401,   406,   562,   567,   408,   410,   413,
     569,   570,   571,   575,   364,  -799,   576,     7,  -799,   578,
      11,  -799,  -799,  -799,   579,   577,   580,    24,    24,    24,
    -799,   171,   581,   582,   583,  -799,  -799,  -799,   420,   429,
     430,   584,   585,   588,  -799,  -799,  -799,  -799,   431,   592,
     593,   594,   595,   596,   436,   597,   599,   600,   601,   602,
    -799,   603,   604,  -799,   607,   238,   292,  -799,  -799,   448,
     449,   450,   611,   452,   453,  -799,    81,   607,   454,   613,
    -799,   456,  -799,   607,   457,   458,   459,   460,   463,   465,
     466,  -799,   469,   470,  -799,   471,   472,   473,  -799,  -799,
     475,  -799,  -799,  -799,   476,    24,  -799,  -799,   477,   478,
    -799,   479,  -799,  -799,    31,   495,  -799,  -799,  -799,   -52,
     480,   481,   482,  -799,   621,  -799,   624,  -799,    24,    65,
       7,  -799,  -799,  -799,  -799,    11,    84,   563,  -799,  -799,
    -799,   412,   412,   625,  -799,   626,   632,   641,   642,  -799,
    -799,  -799,   120,   643,   644,   645,    26,    54,   364,  -799,
    -799,  -799,  -799,  -799,  -799,  -799,  -799,  -799,  -799,  -799,
     646,  -799,  -799,  -799,  -799,  -799,  -799,  -799,  -799,  -799,
     252,  -799,  -799,  -799,  -799,  -799,  -799,  -799,  -799,  -799,
    -799,  -799,  -799,  -799,  -799,  -799,  -799,  -799,  -799,  -799,
    -799,  -799,  -799,  -799,  -799,  -799,  -799,  -799,  -799,  -799,
    -799,  -799,  -799,  -799,   647,   625,  -799,   172,   193,   199,
     237,  -799,   245,  -799,  -799,  -799,  -799,  -799,  -799,   651,
     652,   653,   654,   655,  -799,  -799,   656,   657,   658,   659,
     660,  -799,   280,  -799,  -799,  -799,  -799,  -799,  -799,  -799,
    -799,  -799,  -799,  -799,  -799,  -799,  -799,  -799,  -799,  -799,
    -799,   281,  -799,   661,   605,  -799,  -799,   662,   663,  -799,
    -799,   664,   666,  -799,  -799,   665,   669,  -799,  -799,   667,
     671,  -799,  -799,  -799,  -799,  -799,  -799,   150,  -799,  -799,
    -799,  -799,  -799,  -799,  -799,   182,  -799,  -799,   670,   672,
    -799,  -799,   673,   674,  -799,   676,   677,   678,   679,   680,
     681,   282,  -799,  -799,  -799,  -799,  -799,  -799,  -799,  -799,
    -799,  -799,  -799,  -799,   284,  -799,  -799,  -799,   290,   524,
    -799,   682,   675,  -799,  -799,  -799,  -799,   683,  -799,   214,
    -799,   684,  -799,  -799,  -799,  -799,   688,   563,  -799,   689,
     690,   691,   692,   441,   497,   533,   518,   534,   693,   694,
     536,   537,   538,   540,   543,   412,  -799,  -799,   412,  -799,
     625,   183,  -799,   626,   403,  -799,   632,   157,  -799,   641,
     251,  -799,   642,   120,  -799,    82,   643,  -799,   223,  -799,
     644,   -40,  -799,   645,   544,   546,   547,   548,   549,   550,
      26,  -799,   697,   701,    54,  -799,  -799,  -799,   702,   704,
      38,  -799,   646,   705,  -799,   129,   647,  -799,  -799,   552,
    -799,   231,   553,   554,   555,  -799,  -799,  -799,  -799,  -799,
     556,   557,  -799,  -799,  -799,  -799,  -799,  -799,   293,  -799,
     294,  -799,   715,  -799,   716,  -799,  -799,  -799,  -799,  -799,
    -799,  -799,  -799,  -799,  -799,  -799,  -799,  -799,   321,  -799,
    -799,  -799,  -799,  -799,  -799,  -799,  -799,  -799,  -799,  -799,
     721,  -799,  -799,  -799,  -799,  -799,  -799,  -799,  -799,  -799,
     718,   724,  -799,  -799,  -799,  -799,  -799,   720,  -799,   330,
    -799,  -799,  -799,  -799,  -799,  -799,  -799,  -799,   564,   565,
    -799,  -799,   566,   332,  -799,   607,  -799,   728,  -799,  -799,
    -799,  -799,  -799,   333,  -799,  -799,  -799,  -799,  -799,  -799,
    -799,  -799,  -799,  -799,  -799,  -799,  -799,  -799,  -799,  -799,
    -799,  -799,  -799,  -799,   251,  -799,   729,   568,  -799,    82,
    -799,  -799,  -799,  -799,  -799,  -799,  -799,   730,   572,   731,
     129,  -799,  -799,   574,  -799,  -799,   732,  -799,   587,  -799,
    -799,   733,  -799,  -799,   225,  -799,   -39,   733,  -799,  -799,
     737,   738,   739,   343,  -799,  -799,  -799,  -799,  -799,  -799,
     740,   590,   589,   598,   -39,  -799,   591,  -799,  -799,  -799,
    -799,  -799
  };

  const unsigned short
  Dhcp4Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,    24,    26,    28,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       1,    45,    38,    34,    33,    30,    31,    32,    37,     3,
      35,    36,    58,     5,    70,     7,   126,     9,   263,    11,
     418,    13,   443,    15,   343,    17,   351,    19,   388,    21,
     228,    23,   533,    25,   608,    27,   598,    29,    47,    41,
       0,     0,     0,     0,     0,   445,     0,   353,   390,     0,
       0,     0,     0,    49,     0,    48,     0,     0,    42,    68,
     606,   588,   590,   592,     0,    67,     0,    60,    62,    64,
      65,    66,    63,   594,   596,   115,   141,     0,     0,     0,
     464,   466,   468,   139,   148,   150,     0,     0,     0,     0,
     110,   255,   341,   380,   312,   431,   433,   206,   492,   435,
     220,   239,     0,   518,   531,   105,     0,    72,    74,    75,
      76,    77,   104,    93,    94,    95,    80,    81,   101,    82,
      83,    84,    88,    89,    78,    79,    86,    87,    99,   100,
     102,    96,    97,    98,    85,    90,    91,    92,   103,   128,
     130,   134,     0,   125,     0,   117,   119,   120,   121,   122,
     123,   124,   293,   295,   297,   410,   291,   299,     0,   305,
     303,   301,   488,   290,   267,   268,   269,   280,   281,     0,
     265,   272,   285,   286,   287,   273,   275,   276,   278,   274,
     270,   271,   288,   289,   277,   282,   283,   284,   279,   429,
     428,   424,   425,   423,     0,   420,   422,   426,   427,   486,
     474,   476,   480,   478,   484,   482,   470,   463,   457,   461,
     462,     0,   446,   447,   458,   459,   460,   454,   449,   455,
     451,   452,   453,   456,   450,     0,   370,   191,     0,   374,
     372,   377,     0,   366,   367,     0,   354,   355,   357,   369,
     358,   359,   360,   376,   361,   362,   363,   364,   365,   404,
       0,     0,   402,   403,   406,   407,     0,   391,   392,   394,
     395,   396,   397,   398,   399,   400,   401,   235,   237,   232,
       0,   230,   233,   234,     0,   557,   559,     0,   562,     0,
       0,   566,   570,     0,     0,     0,   575,   582,   584,   586,
     555,   553,   554,     0,   535,   537,   538,   539,   540,   541,
     542,   543,   544,   545,   546,   547,   548,   549,   550,   551,
     552,   613,     0,   610,   612,   604,   603,     0,   600,   602,
      46,     0,     0,    39,     0,     0,     0,     0,     0,     0,
      57,     0,    59,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    71,     0,     0,     0,
       0,     0,   127,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   264,     0,     0,   419,     0,
       0,     0,     0,     0,     0,     0,     0,   444,     0,   344,
       0,     0,     0,     0,     0,     0,     0,   352,     0,     0,
       0,     0,   389,     0,     0,     0,     0,   229,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   534,     0,     0,   609,     0,
       0,   599,    50,    43,     0,     0,     0,     0,     0,     0,
      61,     0,     0,     0,     0,   112,   113,   114,     0,     0,
       0,     0,     0,     0,   106,   107,   108,   109,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     517,     0,     0,    73,     0,     0,     0,   138,   118,     0,
       0,     0,     0,     0,     0,   311,     0,     0,     0,     0,
     266,     0,   421,     0,     0,     0,     0,     0,     0,     0,
       0,   448,     0,     0,   368,     0,     0,     0,   379,   356,
       0,   408,   409,   393,     0,     0,   231,   556,     0,     0,
     561,     0,   564,   565,     0,     0,   572,   573,   574,     0,
       0,     0,     0,   536,     0,   611,     0,   601,     0,     0,
       0,   589,   591,   593,   595,     0,     0,     0,   465,   467,
     469,     0,     0,   152,   111,   257,   345,   382,   314,    40,
     432,   434,     0,     0,   437,   222,     0,     0,     0,    51,
     129,   132,   133,   131,   136,   137,   135,   294,   296,   298,
     412,   292,   300,   307,   308,   309,   310,   306,   304,   302,
       0,   430,   487,   475,   477,   481,   479,   485,   483,   471,
     371,   192,   375,   373,   378,   405,   236,   238,   558,   560,
     563,   568,   569,   567,   571,   577,   578,   579,   580,   581,
     576,   583,   585,   587,     0,   152,    44,     0,     0,     0,
       0,   146,     0,   143,   145,   178,   184,   186,   188,     0,
       0,     0,     0,     0,   200,   202,     0,     0,     0,     0,
       0,   177,     0,   158,   160,   161,   162,   163,   164,   165,
     166,   167,   168,   169,   173,   174,   175,   170,   176,   171,
     172,     0,   156,     0,   153,   154,   261,     0,   258,   259,
     349,     0,   346,   347,   386,     0,   383,   384,   318,     0,
     315,   316,   215,   216,   217,   218,   219,     0,   208,   210,
     211,   212,   213,   214,   496,     0,   494,   441,     0,   438,
     439,   226,     0,   223,   224,     0,     0,     0,     0,     0,
       0,     0,   241,   243,   244,   245,   246,   247,   248,   527,
     529,   526,   524,   525,     0,   520,   522,   523,     0,    53,
     416,     0,   413,   414,   472,   490,   491,     0,   617,     0,
     615,     0,    69,   607,   597,   116,     0,     0,   142,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   140,   149,     0,   151,
       0,     0,   256,     0,   353,   342,     0,   390,   381,     0,
       0,   313,     0,     0,   207,   498,     0,   493,   445,   436,
       0,     0,   221,     0,     0,     0,     0,     0,     0,     0,
       0,   240,     0,     0,     0,   519,   532,    55,     0,    54,
       0,   411,     0,     0,   489,     0,     0,   614,   605,     0,
     144,     0,     0,     0,     0,   190,   193,   194,   195,   196,
       0,     0,   204,   205,   197,   198,   199,   159,     0,   155,
       0,   260,     0,   348,     0,   385,   340,   337,   325,   326,
     328,   329,   322,   323,   324,   335,   336,   334,     0,   320,
     327,   338,   339,   330,   331,   332,   333,   317,   209,   514,
       0,   512,   513,   505,   506,   510,   511,   507,   508,   509,
       0,   499,   500,   502,   503,   504,   495,     0,   440,     0,
     225,   249,   250,   251,   252,   253,   254,   242,     0,     0,
     521,    52,     0,     0,   415,     0,   631,     0,   629,   627,
     621,   625,   626,     0,   619,   623,   624,   622,   616,   147,
     180,   181,   182,   183,   179,   185,   187,   189,   201,   203,
     157,   262,   350,   387,     0,   319,     0,     0,   497,     0,
     442,   227,   528,   530,    56,   417,   473,     0,     0,     0,
       0,   618,   321,     0,   516,   501,     0,   628,     0,   620,
     515,     0,   630,   635,     0,   633,     0,     0,   632,   643,
       0,     0,     0,     0,   637,   639,   640,   641,   642,   634,
       0,     0,     0,     0,     0,   636,     0,   645,   646,   647,
     638,   644
  };

  const short
  Dhcp4Parser::yypgoto_[] =
  {
    -799,  -799,  -799,  -799,  -799,  -799,  -799,  -799,  -799,  -799,
    -799,  -799,  -799,  -799,  -799,  -799,   -44,  -799,   184,  -799,
    -799,  -799,  -799,  -799,  -799,  -799,  -799,  -506,  -799,  -799,
    -799,   -70,  -799,  -799,  -799,   386,  -799,  -799,  -799,  -799,
     167,   355,   -48,   -45,   -43,  -799,  -799,  -799,  -799,   -11,
       4,  -799,  -799,   163,   352,  -799,  -799,  -799,  -799,  -799,
    -799,  -799,  -799,  -799,  -799,  -799,  -799,  -799,  -799,  -799,
    -799,   -35,  -799,  -799,  -799,  -799,  -799,  -799,    94,  -799,
     -41,  -799,  -586,   -34,  -799,  -799,  -799,  -799,  -799,  -799,
    -799,  -799,  -799,  -799,   -26,  -799,  -799,  -799,  -799,  -799,
    -799,  -799,  -799,  -799,  -799,  -799,  -799,  -799,  -799,  -799,
    -799,  -799,   -42,  -799,  -799,  -799,  -799,  -799,  -799,  -799,
    -799,  -799,   -68,  -799,  -799,  -799,   -53,   347,  -799,  -799,
    -799,  -799,  -799,  -799,  -799,   -56,  -799,  -799,  -799,  -799,
    -799,  -799,  -798,  -799,  -799,  -799,   -15,  -799,  -799,  -799,
     -22,   399,  -799,  -799,  -799,  -799,  -799,  -799,  -799,  -799,
    -789,  -799,   -24,  -799,    -4,  -799,  -787,  -799,  -799,  -799,
    -799,  -799,  -799,  -799,   -27,  -799,  -799,  -173,   -65,  -799,
    -799,  -799,  -799,  -799,    -8,  -799,  -799,  -799,     9,  -799,
     402,  -799,   -66,  -799,  -799,  -799,  -799,  -799,   -60,  -799,
    -799,  -799,  -799,  -799,   -18,  -799,  -799,  -799,     8,  -799,
    -799,  -799,    14,  -799,   404,  -799,  -799,  -799,  -799,  -799,
    -799,  -799,  -799,  -799,  -799,  -799,   -19,  -799,  -799,  -799,
     -16,   432,  -799,  -799,   -58,  -799,   -38,  -799,   -47,  -799,
    -799,  -799,     5,  -799,  -799,  -799,    10,  -799,   418,    -7,
    -799,    -6,  -799,     0,  -799,   221,  -799,  -799,  -799,  -799,
    -799,  -799,  -799,  -799,  -799,  -799,  -799,  -799,  -799,  -799,
    -799,  -799,  -799,  -784,  -799,  -799,  -799,  -799,  -799,    16,
    -799,  -799,  -799,  -139,  -799,  -799,  -799,  -799,  -799,  -799,
    -799,  -799,     1,  -799,  -799,  -799,  -799,  -799,  -799,  -799,
    -799,   246,   389,  -799,  -799,  -799,  -799,  -799,  -799,  -799,
    -799,  -799,  -799,  -799,  -799,  -799,  -799,  -799,  -799,  -799,
    -799,  -799,  -799,  -799,  -799,  -799,  -799,  -799,  -799,  -799,
    -799,  -799,  -799,  -799,  -799,  -799,  -799,  -799,  -799,  -799,
    -799,  -350,   390,  -799,  -799,  -799,  -799,  -799,  -799,   278,
     392,  -799,  -799,  -799,    -9,  -799,  -799,  -138,  -799,  -799,
    -799,  -799,  -799,  -799,  -156,  -799,  -799,  -171,  -799,  -799,
    -799,  -799,  -799
  };

  const short
  Dhcp4Parser::yydefgoto_[] =
  {
      -1,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    38,    39,    40,    69,
     600,    87,    88,    41,    68,    84,    85,   610,   779,   858,
     859,   346,    43,    70,    96,    97,    98,   355,    45,    71,
     136,   137,   138,   139,   140,   141,   142,   380,   143,   144,
     145,   146,   365,   174,   175,    47,    72,   176,   397,   177,
     398,   613,   178,   399,   616,   179,   147,   373,   148,   366,
     672,   673,   674,   796,   149,   374,   150,   375,   713,   714,
     715,   818,   692,   693,   694,   799,   974,   695,   800,   696,
     801,   697,   802,   698,   699,   431,   700,   701,   702,   703,
     704,   705,   706,   707,   808,   708,   809,   709,   710,   151,
     387,   737,   738,   739,   740,   741,   742,   743,   152,   390,
     752,   753,   754,   841,    61,    79,   300,   301,   302,   444,
     303,   445,   153,   391,   761,   762,   763,   764,   765,   766,
     767,   768,   154,   381,   717,   718,   719,   821,    49,    73,
     199,   200,   201,   407,   202,   403,   203,   404,   204,   405,
     205,   408,   206,   412,   207,   411,   208,   410,   627,   209,
     155,   384,   729,   730,   731,   830,   908,   909,   156,   382,
      55,    76,   721,   722,   723,   824,    57,    77,   265,   266,
     267,   268,   269,   270,   271,   430,   272,   434,   273,   433,
     274,   275,   435,   276,   157,   383,   725,   726,   727,   827,
      59,    78,   286,   287,   288,   289,   290,   439,   291,   292,
     293,   294,   211,   406,   781,   782,   783,   860,    51,    74,
     224,   225,   226,   416,   158,   385,   159,   386,   160,   389,
     748,   749,   750,   838,    53,    75,   241,   242,   243,   161,
     370,   162,   371,   163,   372,   247,   426,   786,   863,   248,
     420,   249,   421,   250,   423,   251,   422,   252,   425,   253,
     424,   254,   419,   218,   413,   787,   164,   388,   745,   746,
     835,   930,   931,   932,   933,   934,   986,   935,   165,   166,
     393,   774,   775,   776,   852,   777,   853,   167,   394,    63,
      80,   323,   324,   325,   326,   449,   327,   450,   328,   329,
     452,   330,   331,   332,   455,   653,   333,   456,   334,   335,
     336,   337,   460,   660,   338,   461,   339,   462,   340,   463,
      99,   357,   100,   358,   101,   359,   168,   363,   364,    67,
      82,   347,   348,   349,   469,   102,   356,    65,    81,   342,
     343,   344,   466,   789,   790,   865,   963,   964,   965,   966,
     999,   967,   997,  1014,  1015,  1016,  1023,  1024,  1025,  1030,
    1026,  1027,  1028
  };

  const unsigned short
  Dhcp4Parser::yytable_[] =
  {
      95,   135,   173,   193,   220,   237,   711,   263,   282,   299,
     320,   255,   284,   481,   180,   212,   227,   239,   285,   277,
     295,   628,   321,   345,    83,   194,   214,   632,   195,    31,
     196,    32,   903,    33,   181,   213,   228,   240,    86,   278,
     296,   904,   322,   907,    89,    30,   916,    42,   651,   361,
     221,   264,   283,   395,   362,   210,   223,   238,   396,    44,
     401,   122,   197,   297,   298,   402,   215,   216,   244,   245,
     222,    46,   103,   217,   414,   246,   104,   198,   105,   415,
     417,   655,   656,   657,   658,   418,    48,   106,   351,   107,
     108,   109,   110,   111,   112,   113,   114,   115,   169,   170,
      50,   123,   171,  1019,    52,   172,  1020,  1021,  1022,   110,
     111,   112,   446,   219,   125,   126,   659,   447,   116,   117,
     118,   119,   120,   121,    54,    94,   190,   122,   123,   191,
     125,   126,   755,   756,   757,   758,   759,   760,   124,   297,
     298,   125,   126,   464,   122,   123,   257,   341,   465,   467,
     470,   127,   128,   833,   468,   471,   834,   129,   125,   126,
     125,   126,   652,   623,   624,   625,   626,   130,   769,   770,
     131,   919,   920,    90,   470,   395,    94,   132,   133,   584,
     792,   134,    91,    92,    93,   836,   903,    56,   837,    34,
      35,    36,    37,   257,    58,   904,   467,   907,    60,    94,
     916,   793,   470,    94,    62,   125,   126,   794,   108,   109,
     110,   111,   112,   732,   733,   734,   735,   866,   736,    94,
     867,   257,   279,   258,   259,   280,   281,    64,  1017,    66,
      94,  1018,   888,   125,   126,   669,   116,   117,   118,   350,
     401,   474,   182,   183,   184,   795,   123,    94,   797,    94,
     110,   111,   112,   798,   611,   612,   353,   185,   352,   125,
     126,   186,   187,   188,   189,   970,   971,   972,   973,   354,
     956,   190,   957,   958,   191,   129,   108,   109,   110,   111,
     112,   360,   192,   815,   815,   850,   123,   854,   816,   817,
     851,    95,   855,   464,    94,   367,   815,   414,   856,   125,
     126,   980,   981,   368,   116,   117,   118,   472,   473,   121,
     229,   614,   615,   369,   123,   257,   230,   231,   232,   233,
     234,   235,    94,   236,   984,   135,   376,   125,   126,   985,
     187,   173,   189,   446,   427,   417,  1000,   428,   991,   190,
     995,  1001,   191,   180,   193,   377,  1034,   220,    94,   378,
     192,  1035,   236,   784,   379,   392,   212,   400,   237,   227,
     409,   432,   429,   181,   436,   438,   194,   214,   263,   195,
     239,   196,   440,   282,   437,   441,   213,   284,   442,   228,
     277,   443,   494,   285,   448,   295,   451,   453,    94,   454,
     240,   457,   458,   221,   320,   459,   210,   475,   476,   223,
     278,   477,   478,   197,   485,   296,   321,   215,   216,   479,
     238,   482,   264,   222,   217,   483,    94,   283,   198,   484,
     488,   244,   245,   486,   487,   489,   322,   490,   246,   491,
     492,   493,   498,   581,   582,   583,   256,   495,   496,   497,
     125,   126,   499,   500,   501,   675,   502,   503,   504,   996,
     676,   677,   678,   679,   680,   681,   682,   683,   684,   685,
     686,   687,   688,   689,   690,   505,   506,   257,   507,   258,
     259,   508,   509,   260,   261,   262,   257,   510,   511,   125,
     126,   304,   305,   306,   307,   308,   309,   310,   311,   312,
     313,   314,   315,   316,   317,   512,   514,   515,   516,   517,
     519,   318,   319,   520,   521,   522,   523,   524,   525,   135,
     526,   647,   527,   528,   529,   531,   173,   533,   534,   535,
     536,   691,   691,   537,   538,   539,   540,   542,   180,    94,
     543,   544,   545,   546,   666,   547,   550,   771,   320,   554,
     548,   551,   552,   555,   557,   558,   559,   560,   181,   772,
     321,     1,     2,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,   561,   564,   562,    94,   773,
     322,   565,   563,   569,   570,   571,   566,    94,   567,   572,
     574,   568,   576,   578,   579,   588,   671,   580,   585,   586,
     587,   591,   592,   593,   589,   590,   594,   595,   596,   597,
     598,   601,   602,    32,   603,   604,   605,   875,   820,   606,
     607,   608,   609,   617,   618,   619,   620,   621,   622,   629,
     630,   631,   633,   634,   635,   636,   664,   654,   637,   665,
     638,   639,   712,   716,   640,   641,   642,   643,   644,   720,
     645,   646,   648,   649,   650,   661,   662,   663,   724,   728,
     744,   747,   751,   780,   788,   803,   804,   805,   806,   807,
     810,   811,   812,   813,   814,   876,   823,   819,   822,   826,
     825,   828,   829,   831,   832,   840,   839,   843,   862,   842,
     844,   845,   846,   847,   848,   849,   878,   599,   861,   857,
     868,   864,   869,   871,   872,   873,   874,   880,   881,   877,
     879,   948,   882,   883,   884,   949,   885,   952,   951,   955,
     941,   886,   942,   943,   944,   945,   946,   969,   975,   976,
     977,   978,   979,   982,   983,   987,   988,   989,   990,   992,
     993,   994,   998,  1003,  1006,  1008,  1004,  1011,  1007,  1010,
    1013,  1031,  1032,  1033,  1036,   691,   667,   480,   691,   670,
     513,   193,  1012,   518,   263,  1038,  1041,   282,  1037,   791,
     896,   284,   870,   212,  1039,   921,   277,   285,   237,   295,
     923,   299,   911,   194,   214,   940,   195,   925,   196,   889,
     239,   887,   897,   213,   771,   898,   278,   899,   939,   296,
     220,   918,   912,   556,   947,   959,   772,   926,   264,   890,
     240,   283,   227,   210,   902,   917,   905,   961,   891,   922,
     197,  1002,   910,   530,   215,   216,   773,   924,   893,   900,
     238,   217,   228,   913,   914,   198,   906,   962,   927,   928,
     915,   244,   245,   892,   901,   929,   221,   895,   246,   960,
     549,   894,   223,   954,   953,   938,   541,   553,   937,   532,
    1005,   785,   936,   573,   778,   950,   222,   968,   668,   575,
     577,  1029,  1009,  1040,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   896,     0,     0,     0,     0,   921,
       0,     0,     0,     0,   923,     0,   911,     0,     0,     0,
     959,   925,     0,     0,     0,     0,   897,     0,     0,   898,
       0,   899,   961,     0,     0,     0,   912,     0,     0,     0,
       0,   926,     0,     0,     0,     0,     0,     0,   902,     0,
     905,     0,   962,   922,     0,     0,   910,     0,     0,     0,
       0,   924,     0,   900,   960,     0,     0,   913,   914,     0,
     906,     0,   927,   928,   915,     0,     0,     0,   901,   929
  };

  const short
  Dhcp4Parser::yycheck_[] =
  {
      70,    71,    72,    73,    74,    75,   592,    77,    78,    79,
      80,    76,    78,   363,    72,    73,    74,    75,    78,    77,
      78,   527,    80,    12,    68,    73,    73,   533,    73,     5,
      73,     7,   830,     9,    72,    73,    74,    75,   165,    77,
      78,   830,    80,   830,    10,     0,   830,     7,    17,     3,
      74,    77,    78,     3,     8,    73,    74,    75,     8,     7,
       3,    62,    73,   103,   104,     8,    73,    73,    75,    75,
      74,     7,     7,    73,     3,    75,    11,    73,    13,     8,
       3,   133,   134,   135,   136,     8,     7,    22,     3,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    14,    15,
       7,    63,    18,   142,     7,    21,   145,   146,   147,    27,
      28,    29,     3,    75,    76,    77,   168,     8,    53,    54,
      55,    56,    57,    58,     7,   165,    88,    62,    63,    91,
      76,    77,   106,   107,   108,   109,   110,   111,    73,   103,
     104,    76,    77,     3,    62,    63,    64,   140,     8,     3,
       3,    86,    87,     3,     8,     8,     6,    92,    76,    77,
      76,    77,   131,    82,    83,    84,    85,   102,   114,   115,
     105,    89,    90,   139,     3,     3,   165,   112,   113,     8,
       8,   116,   148,   149,   150,     3,   984,     7,     6,   165,
     166,   167,   168,    64,     7,   984,     3,   984,     7,   165,
     984,     8,     3,   165,     7,    76,    77,     8,    25,    26,
      27,    28,    29,    93,    94,    95,    96,     3,    98,   165,
       6,    64,    65,    66,    67,    68,    69,     7,     3,     7,
     165,     6,   818,    76,    77,   585,    53,    54,    55,     6,
       3,   165,    59,    60,    61,     8,    63,   165,     3,   165,
      27,    28,    29,     8,    16,    17,     8,    74,     4,    76,
      77,    78,    79,    80,    81,    34,    35,    36,    37,     3,
     141,    88,   143,   144,    91,    92,    25,    26,    27,    28,
      29,     4,    99,     3,     3,     3,    63,     3,     8,     8,
       8,   361,     8,     3,   165,     4,     3,     3,     8,    76,
      77,     8,     8,     4,    53,    54,    55,   351,   352,    58,
      87,    19,    20,     4,    63,    64,    93,    94,    95,    96,
      97,    98,   165,   100,     3,   395,     4,    76,    77,     8,
      79,   401,    81,     3,     8,     3,     3,     3,     8,    88,
       8,     8,    91,   401,   414,     4,     3,   417,   165,     4,
      99,     8,   100,   101,     4,     4,   414,     4,   428,   417,
       4,     4,     8,   401,     4,     3,   414,   414,   438,   414,
     428,   414,     4,   443,     8,     4,   414,   443,     8,   417,
     438,     3,   166,   443,     4,   443,     4,     4,   165,     4,
     428,     4,     4,   417,   464,     4,   414,     4,     4,   417,
     438,     4,     4,   414,   168,   443,   464,   414,   414,     4,
     428,     4,   438,   417,   414,     4,   165,   443,   414,     4,
       4,   428,   428,   168,   168,     4,   464,     4,   428,     4,
       4,     4,     4,   477,   478,   479,    33,   166,   166,   166,
      76,    77,     4,     4,     4,    33,     4,     4,     4,   955,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    50,    51,    52,     4,     4,    64,     4,    66,
      67,     4,     4,    70,    71,    72,    64,   166,     4,    76,
      77,   117,   118,   119,   120,   121,   122,   123,   124,   125,
     126,   127,   128,   129,   130,     4,     4,     4,     4,   168,
       4,   137,   138,     4,     4,     4,     4,     4,   166,   579,
       4,   555,     4,     4,     4,     4,   586,     4,     4,     4,
       4,   591,   592,     4,     4,     4,     4,     4,   586,   165,
       4,   166,     4,     4,   578,     4,     4,   607,   608,     4,
     168,   168,   168,     4,   168,     4,     4,   166,   586,   607,
     608,   151,   152,   153,   154,   155,   156,   157,   158,   159,
     160,   161,   162,   163,   164,     4,     4,   166,   165,   607,
     608,     4,   166,     4,     4,     4,   168,   165,   168,     4,
       4,   168,     4,     4,     7,   165,    23,     7,     7,     7,
       7,     7,     7,     5,   165,   165,   165,     5,     5,     5,
       5,   165,     5,     7,     5,     5,     5,   166,     3,     7,
       7,     7,     5,   165,   165,   165,     5,   165,   165,   165,
       7,   165,   165,   165,   165,   165,     5,   132,   165,     5,
     165,   165,     7,     7,   165,   165,   165,   165,   165,     7,
     165,   165,   165,   165,   165,   165,   165,   165,     7,     7,
       7,     7,     7,     7,     7,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,   168,     3,     6,     6,     3,
       6,     6,     3,     6,     3,     3,     6,     3,     3,     6,
       4,     4,     4,     4,     4,     4,   168,   503,     6,   165,
       6,     8,     4,     4,     4,     4,     4,     4,     4,   166,
     166,     4,   166,   166,   166,     4,   166,     3,     6,     4,
     166,   168,   166,   166,   166,   166,   166,   165,   165,   165,
     165,   165,   165,     8,     8,     4,     8,     3,     8,   165,
     165,   165,     4,     4,     4,     4,   168,     5,   166,   165,
       7,     4,     4,     4,     4,   815,   579,   361,   818,   586,
     395,   821,   165,   401,   824,   166,   165,   827,   168,   665,
     830,   827,   797,   821,   166,   835,   824,   827,   838,   827,
     835,   841,   830,   821,   821,   843,   821,   835,   821,   820,
     838,   815,   830,   821,   854,   830,   824,   830,   841,   827,
     860,   833,   830,   446,   850,   865,   854,   835,   824,   821,
     838,   827,   860,   821,   830,   832,   830,   865,   823,   835,
     821,   984,   830,   414,   821,   821,   854,   835,   826,   830,
     838,   821,   860,   830,   830,   821,   830,   865,   835,   835,
     830,   838,   838,   824,   830,   835,   860,   829,   838,   865,
     438,   827,   860,   862,   860,   840,   428,   443,   838,   417,
     989,   630,   836,   464,   608,   854,   860,   866,   580,   467,
     470,  1017,  1000,  1034,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   984,    -1,    -1,    -1,    -1,   989,
      -1,    -1,    -1,    -1,   989,    -1,   984,    -1,    -1,    -1,
    1000,   989,    -1,    -1,    -1,    -1,   984,    -1,    -1,   984,
      -1,   984,  1000,    -1,    -1,    -1,   984,    -1,    -1,    -1,
      -1,   989,    -1,    -1,    -1,    -1,    -1,    -1,   984,    -1,
     984,    -1,  1000,   989,    -1,    -1,   984,    -1,    -1,    -1,
      -1,   989,    -1,   984,  1000,    -1,    -1,   984,   984,    -1,
     984,    -1,   989,   989,   984,    -1,    -1,    -1,   984,   989
  };

  const unsigned short
  Dhcp4Parser::yystos_[] =
  {
       0,   151,   152,   153,   154,   155,   156,   157,   158,   159,
     160,   161,   162,   163,   164,   170,   171,   172,   173,   174,
     175,   176,   177,   178,   179,   180,   181,   182,   183,   184,
       0,     5,     7,     9,   165,   166,   167,   168,   185,   186,
     187,   192,     7,   201,     7,   207,     7,   224,     7,   317,
       7,   397,     7,   413,     7,   349,     7,   355,     7,   379,
       7,   293,     7,   468,     7,   516,     7,   508,   193,   188,
     202,   208,   225,   318,   398,   414,   350,   356,   380,   294,
     469,   517,   509,   185,   194,   195,   165,   190,   191,    10,
     139,   148,   149,   150,   165,   200,   203,   204,   205,   499,
     501,   503,   514,     7,    11,    13,    22,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    53,    54,    55,    56,
      57,    58,    62,    63,    73,    76,    77,    86,    87,    92,
     102,   105,   112,   113,   116,   200,   209,   210,   211,   212,
     213,   214,   215,   217,   218,   219,   220,   235,   237,   243,
     245,   278,   287,   301,   311,   339,   347,   373,   403,   405,
     407,   418,   420,   422,   445,   457,   458,   466,   505,    14,
      15,    18,    21,   200,   222,   223,   226,   228,   231,   234,
     403,   405,    59,    60,    61,    74,    78,    79,    80,    81,
      88,    91,    99,   200,   211,   212,   213,   218,   219,   319,
     320,   321,   323,   325,   327,   329,   331,   333,   335,   338,
     373,   391,   403,   405,   407,   418,   420,   422,   442,    75,
     200,   331,   333,   373,   399,   400,   401,   403,   405,    87,
      93,    94,    95,    96,    97,    98,   100,   200,   373,   403,
     405,   415,   416,   417,   418,   420,   422,   424,   428,   430,
     432,   434,   436,   438,   440,   347,    33,    64,    66,    67,
      70,    71,    72,   200,   263,   357,   358,   359,   360,   361,
     362,   363,   365,   367,   369,   370,   372,   403,   405,    65,
      68,    69,   200,   263,   361,   367,   381,   382,   383,   384,
     385,   387,   388,   389,   390,   403,   405,   103,   104,   200,
     295,   296,   297,   299,   117,   118,   119,   120,   121,   122,
     123,   124,   125,   126,   127,   128,   129,   130,   137,   138,
     200,   403,   405,   470,   471,   472,   473,   475,   477,   478,
     480,   481,   482,   485,   487,   488,   489,   490,   493,   495,
     497,   140,   518,   519,   520,    12,   200,   510,   511,   512,
       6,     3,     4,     8,     3,   206,   515,   500,   502,   504,
       4,     3,     8,   506,   507,   221,   238,     4,     4,     4,
     419,   421,   423,   236,   244,   246,     4,     4,     4,     4,
     216,   312,   348,   374,   340,   404,   406,   279,   446,   408,
     288,   302,     4,   459,   467,     3,     8,   227,   229,   232,
       4,     3,     8,   324,   326,   328,   392,   322,   330,     4,
     336,   334,   332,   443,     3,     8,   402,     3,     8,   441,
     429,   431,   435,   433,   439,   437,   425,     8,     3,     8,
     364,   264,     4,   368,   366,   371,     4,     8,     3,   386,
       4,     4,     8,     3,   298,   300,     3,     8,     4,   474,
     476,     4,   479,     4,     4,   483,   486,     4,     4,     4,
     491,   494,   496,   498,     3,     8,   521,     3,     8,   513,
       3,     8,   185,   185,   165,     4,     4,     4,     4,     4,
     204,   510,     4,     4,     4,   168,   168,   168,     4,     4,
       4,     4,     4,     4,   166,   166,   166,   166,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
     166,     4,     4,   210,     4,     4,     4,   168,   223,     4,
       4,     4,     4,     4,     4,   166,     4,     4,     4,     4,
     320,     4,   400,     4,     4,     4,     4,     4,     4,     4,
       4,   417,     4,     4,   166,     4,     4,     4,   168,   359,
       4,   168,   168,   383,     4,     4,   296,   168,     4,     4,
     166,     4,   166,   166,     4,     4,   168,   168,   168,     4,
       4,     4,     4,   471,     4,   519,     4,   511,     4,     7,
       7,   185,   185,   185,     8,     7,     7,     7,   165,   165,
     165,     7,     7,     5,   165,     5,     5,     5,     5,   187,
     189,   165,     5,     5,     5,     5,     7,     7,     7,     5,
     196,    16,    17,   230,    19,    20,   233,   165,   165,   165,
       5,   165,   165,    82,    83,    84,    85,   337,   196,   165,
       7,   165,   196,   165,   165,   165,   165,   165,   165,   165,
     165,   165,   165,   165,   165,   165,   165,   185,   165,   165,
     165,    17,   131,   484,   132,   133,   134,   135,   136,   168,
     492,   165,   165,   165,     5,     5,   185,   209,   518,   510,
     222,    23,   239,   240,   241,    33,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    48,    49,    50,    51,
      52,   200,   251,   252,   253,   256,   258,   260,   262,   263,
     265,   266,   267,   268,   269,   270,   271,   272,   274,   276,
     277,   251,     7,   247,   248,   249,     7,   313,   314,   315,
       7,   351,   352,   353,     7,   375,   376,   377,     7,   341,
     342,   343,    93,    94,    95,    96,    98,   280,   281,   282,
     283,   284,   285,   286,     7,   447,   448,     7,   409,   410,
     411,     7,   289,   290,   291,   106,   107,   108,   109,   110,
     111,   303,   304,   305,   306,   307,   308,   309,   310,   114,
     115,   200,   403,   405,   460,   461,   462,   464,   470,   197,
       7,   393,   394,   395,   101,   424,   426,   444,     7,   522,
     523,   247,     8,     8,     8,     8,   242,     3,     8,   254,
     257,   259,   261,     4,     4,     4,     4,     4,   273,   275,
       4,     4,     4,     4,     4,     3,     8,     8,   250,     6,
       3,   316,     6,     3,   354,     6,     3,   378,     6,     3,
     344,     6,     3,     3,     6,   449,     3,     6,   412,     6,
       3,   292,     6,     3,     4,     4,     4,     4,     4,     4,
       3,     8,   463,   465,     3,     8,     8,   165,   198,   199,
     396,     6,     3,   427,     8,   524,     3,     6,     6,     4,
     240,     4,     4,     4,     4,   166,   168,   166,   168,   166,
       4,     4,   166,   166,   166,   166,   168,   252,   251,   249,
     319,   315,   357,   353,   381,   377,   200,   211,   212,   213,
     218,   219,   263,   311,   329,   331,   333,   335,   345,   346,
     373,   403,   405,   418,   420,   422,   442,   343,   281,    89,
      90,   200,   263,   347,   373,   403,   405,   418,   420,   422,
     450,   451,   452,   453,   454,   456,   448,   415,   411,   295,
     291,   166,   166,   166,   166,   166,   166,   304,     4,     4,
     461,     6,     3,   399,   395,     4,   141,   143,   144,   200,
     263,   403,   405,   525,   526,   527,   528,   530,   523,   165,
      34,    35,    36,    37,   255,   165,   165,   165,   165,   165,
       8,     8,     8,     8,     3,     8,   455,     4,     8,     3,
       8,     8,   165,   165,   165,     8,   196,   531,     4,   529,
       3,     8,   346,     4,   168,   452,     4,   166,     4,   526,
     165,     5,   165,     7,   532,   533,   534,     3,     6,   142,
     145,   146,   147,   535,   536,   537,   539,   540,   541,   533,
     538,     4,     4,     4,     3,     8,     4,   168,   166,   166,
     536,   165
  };

  const unsigned short
  Dhcp4Parser::yyr1_[] =
  {
       0,   169,   171,   170,   172,   170,   173,   170,   174,   170,
     175,   170,   176,   170,   177,   170,   178,   170,   179,   170,
     180,   170,   181,   170,   182,   170,   183,   170,   184,   170,
     185,   185,   185,   185,   185,   185,   185,   186,   188,   187,
     189,   190,   190,   191,   191,   193,   192,   194,   194,   195,
     195,   197,   196,   198,   198,   199,   199,   200,   202,   201,
     203,   203,   204,   204,   204,   204,   204,   204,   206,   205,
     208,   207,   209,   209,   210,   210,   210,   210,   210,   210,
     210,   210,   210,   210,   210,   210,   210,   210,   210,   210,
     210,   210,   210,   210,   210,   210,   210,   210,   210,   210,
     210,   210,   210,   210,   210,   210,   211,   212,   213,   214,
     216,   215,   217,   218,   219,   221,   220,   222,   222,   223,
     223,   223,   223,   223,   223,   223,   225,   224,   227,   226,
     229,   228,   230,   230,   232,   231,   233,   233,   234,   236,
     235,   238,   237,   239,   239,   240,   242,   241,   244,   243,
     246,   245,   247,   247,   248,   248,   250,   249,   251,   251,
     252,   252,   252,   252,   252,   252,   252,   252,   252,   252,
     252,   252,   252,   252,   252,   252,   252,   252,   254,   253,
     255,   255,   255,   255,   257,   256,   259,   258,   261,   260,
     262,   264,   263,   265,   266,   267,   268,   269,   270,   271,
     273,   272,   275,   274,   276,   277,   279,   278,   280,   280,
     281,   281,   281,   281,   281,   282,   283,   284,   285,   286,
     288,   287,   289,   289,   290,   290,   292,   291,   294,   293,
     295,   295,   295,   296,   296,   298,   297,   300,   299,   302,
     301,   303,   303,   304,   304,   304,   304,   304,   304,   305,
     306,   307,   308,   309,   310,   312,   311,   313,   313,   314,
     314,   316,   315,   318,   317,   319,   319,   320,   320,   320,
     320,   320,   320,   320,   320,   320,   320,   320,   320,   320,
     320,   320,   320,   320,   320,   320,   320,   320,   320,   320,
     320,   322,   321,   324,   323,   326,   325,   328,   327,   330,
     329,   332,   331,   334,   333,   336,   335,   337,   337,   337,
     337,   338,   340,   339,   341,   341,   342,   342,   344,   343,
     345,   345,   346,   346,   346,   346,   346,   346,   346,   346,
     346,   346,   346,   346,   346,   346,   346,   346,   346,   346,
     346,   348,   347,   350,   349,   351,   351,   352,   352,   354,
     353,   356,   355,   357,   357,   358,   358,   359,   359,   359,
     359,   359,   359,   359,   359,   359,   359,   360,   361,   362,
     364,   363,   366,   365,   368,   367,   369,   371,   370,   372,
     374,   373,   375,   375,   376,   376,   378,   377,   380,   379,
     381,   381,   382,   382,   383,   383,   383,   383,   383,   383,
     383,   383,   383,   384,   386,   385,   387,   388,   389,   390,
     392,   391,   393,   393,   394,   394,   396,   395,   398,   397,
     399,   399,   400,   400,   400,   400,   400,   400,   400,   402,
     401,   404,   403,   406,   405,   408,   407,   409,   409,   410,
     410,   412,   411,   414,   413,   415,   415,   416,   416,   417,
     417,   417,   417,   417,   417,   417,   417,   417,   417,   417,
     417,   417,   417,   417,   419,   418,   421,   420,   423,   422,
     425,   424,   427,   426,   429,   428,   431,   430,   433,   432,
     435,   434,   437,   436,   439,   438,   441,   440,   443,   442,
     444,   444,   446,   445,   447,   447,   449,   448,   450,   450,
     451,   451,   452,   452,   452,   452,   452,   452,   452,   452,
     452,   452,   452,   453,   455,   454,   456,   457,   459,   458,
     460,   460,   461,   461,   461,   461,   461,   463,   462,   465,
     464,   467,   466,   469,   468,   470,   470,   471,   471,   471,
     471,   471,   471,   471,   471,   471,   471,   471,   471,   471,
     471,   471,   471,   471,   471,   471,   472,   474,   473,   476,
     475,   477,   479,   478,   480,   481,   483,   482,   484,   484,
     486,   485,   487,   488,   489,   491,   490,   492,   492,   492,
     492,   492,   494,   493,   496,   495,   498,   497,   500,   499,
     502,   501,   504,   503,   506,   505,   507,   505,   509,   508,
     510,   510,   511,   511,   513,   512,   515,   514,   517,   516,
     518,   518,   519,   521,   520,   522,   522,   524,   523,   525,
     525,   526,   526,   526,   526,   526,   526,   526,   527,   529,
     528,   531,   530,   532,   532,   534,   533,   535,   535,   536,
     536,   536,   536,   538,   537,   539,   540,   541
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
       1,     1,     1,     1,     1,     1,     3,     3,     3,     3,
       0,     4,     3,     3,     3,     0,     6,     1,     3,     1,
       1,     1,     1,     1,     1,     1,     0,     4,     0,     4,
       0,     4,     1,     1,     0,     4,     1,     1,     3,     0,
       6,     0,     6,     1,     3,     1,     0,     4,     0,     6,
       0,     6,     0,     1,     1,     3,     0,     4,     1,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     0,     4,
       1,     1,     1,     1,     0,     4,     0,     4,     0,     4,
       3,     0,     4,     3,     3,     3,     3,     3,     3,     3,
       0,     4,     0,     4,     3,     3,     0,     6,     1,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       0,     6,     0,     1,     1,     3,     0,     4,     0,     4,
       1,     3,     1,     1,     1,     0,     4,     0,     4,     0,
       6,     1,     3,     1,     1,     1,     1,     1,     1,     3,
       3,     3,     3,     3,     3,     0,     6,     0,     1,     1,
       3,     0,     4,     0,     4,     1,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     4,     1,     1,     1,
       1,     3,     0,     6,     0,     1,     1,     3,     0,     4,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     1,
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
       3,     0,     4,     0,     4,     0,     1,     1,     3,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     0,     4,     0,     4,     0,     4,
       0,     4,     0,     4,     0,     4,     0,     4,     0,     4,
       0,     4,     0,     4,     0,     4,     0,     4,     0,     6,
       1,     1,     0,     6,     1,     3,     0,     4,     0,     1,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     0,     4,     3,     3,     0,     6,
       1,     3,     1,     1,     1,     1,     1,     0,     4,     0,
       4,     0,     6,     0,     4,     1,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     3,     0,     4,     0,
       4,     3,     0,     4,     3,     3,     0,     4,     1,     1,
       0,     4,     3,     3,     3,     0,     4,     1,     1,     1,
       1,     1,     0,     4,     0,     4,     0,     4,     0,     4,
       0,     4,     0,     4,     0,     4,     0,     6,     0,     4,
       1,     3,     1,     1,     0,     6,     0,     6,     0,     4,
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
  "\"config-databases\"", "\"interfaces-config\"", "\"interfaces\"",
  "\"dhcp-socket-type\"", "\"raw\"", "\"udp\"", "\"outbound-interface\"",
  "\"same-as-inbound\"", "\"use-routing\"", "\"re-detect\"",
  "\"sanity-checks\"", "\"lease-checks\"", "\"echo-client-id\"",
  "\"match-client-id\"", "\"authoritative\"", "\"next-server\"",
  "\"server-hostname\"", "\"boot-file-name\"", "\"lease-database\"",
  "\"hosts-database\"", "\"hosts-databases\"", "\"type\"", "\"memfile\"",
  "\"mysql\"", "\"postgresql\"", "\"cql\"", "\"user\"", "\"password\"",
  "\"host\"", "\"port\"", "\"persist\"", "\"lfc-interval\"",
  "\"readonly\"", "\"connect-timeout\"", "\"contact-points\"",
  "\"keyspace\"", "\"max-reconnect-tries\"", "\"reconnect-wait-time\"",
  "\"request-timeout\"", "\"tcp-keepalive\"", "\"tcp-nodelay\"",
  "\"valid-lifetime\"", "\"renew-timer\"", "\"rebind-timer\"",
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
  "\"socket-name\"", "\"dhcp-ddns\"", "\"enable-updates\"",
  "\"qualifying-suffix\"", "\"server-ip\"", "\"server-port\"",
  "\"sender-ip\"", "\"sender-port\"", "\"max-queue-size\"",
  "\"ncr-protocol\"", "\"ncr-format\"", "\"always-include-fqdn\"",
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
  "$@20", "global_params", "global_param", "valid_lifetime", "renew_timer",
  "rebind_timer", "decline_probation_period", "server_tag", "$@21",
  "echo_client_id", "match_client_id", "authoritative",
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
  "max_reconnect_tries", "reconnect_wait_time",
  "host_reservation_identifiers", "$@40",
  "host_reservation_identifiers_list", "host_reservation_identifier",
  "duid_id", "hw_address_id", "circuit_id", "client_id", "flex_id",
  "hooks_libraries", "$@41", "hooks_libraries_list",
  "not_empty_hooks_libraries_list", "hooks_library", "$@42",
  "sub_hooks_library", "$@43", "hooks_params", "hooks_param", "library",
  "$@44", "parameters", "$@45", "expired_leases_processing", "$@46",
  "expired_leases_params", "expired_leases_param",
  "reclaim_timer_wait_time", "flush_reclaimed_timer_wait_time",
  "hold_reclaimed_time", "max_reclaim_leases", "max_reclaim_time",
  "unwarned_reclaim_cycles", "subnet4_list", "$@47",
  "subnet4_list_content", "not_empty_subnet4_list", "subnet4", "$@48",
  "sub_subnet4", "$@49", "subnet4_params", "subnet4_param", "subnet",
  "$@50", "subnet_4o6_interface", "$@51", "subnet_4o6_interface_id",
  "$@52", "subnet_4o6_subnet", "$@53", "interface", "$@54", "client_class",
  "$@55", "require_client_classes", "$@56", "reservation_mode", "$@57",
  "hr_mode", "id", "shared_networks", "$@58", "shared_networks_content",
  "shared_networks_list", "shared_network", "$@59",
  "shared_network_params", "shared_network_param", "option_def_list",
  "$@60", "sub_option_def_list", "$@61", "option_def_list_content",
  "not_empty_option_def_list", "option_def_entry", "$@62",
  "sub_option_def", "$@63", "option_def_params",
  "not_empty_option_def_params", "option_def_param", "option_def_name",
  "code", "option_def_code", "option_def_type", "$@64",
  "option_def_record_types", "$@65", "space", "$@66", "option_def_space",
  "option_def_encapsulate", "$@67", "option_def_array", "option_data_list",
  "$@68", "option_data_list_content", "not_empty_option_data_list",
  "option_data_entry", "$@69", "sub_option_data", "$@70",
  "option_data_params", "not_empty_option_data_params",
  "option_data_param", "option_data_name", "option_data_data", "$@71",
  "option_data_code", "option_data_space", "option_data_csv_format",
  "option_data_always_send", "pools_list", "$@72", "pools_list_content",
  "not_empty_pools_list", "pool_list_entry", "$@73", "sub_pool4", "$@74",
  "pool_params", "pool_param", "pool_entry", "$@75", "user_context",
  "$@76", "comment", "$@77", "reservations", "$@78", "reservations_list",
  "not_empty_reservations_list", "reservation", "$@79", "sub_reservation",
  "$@80", "reservation_params", "not_empty_reservation_params",
  "reservation_param", "next_server", "$@81", "server_hostname", "$@82",
  "boot_file_name", "$@83", "ip_address", "$@84", "ip_addresses", "$@85",
  "duid", "$@86", "hw_address", "$@87", "client_id_value", "$@88",
  "circuit_id_value", "$@89", "flex_id_value", "$@90", "hostname", "$@91",
  "reservation_client_classes", "$@92", "relay", "$@93", "relay_map",
  "client_classes", "$@94", "client_classes_list", "client_class_entry",
  "$@95", "client_class_params", "not_empty_client_class_params",
  "client_class_param", "client_class_name", "client_class_test", "$@96",
  "only_if_required", "dhcp4o6_port", "control_socket", "$@97",
  "control_socket_params", "control_socket_param", "control_socket_type",
  "$@98", "control_socket_name", "$@99", "dhcp_ddns", "$@100",
  "sub_dhcp_ddns", "$@101", "dhcp_ddns_params", "dhcp_ddns_param",
  "enable_updates", "qualifying_suffix", "$@102", "server_ip", "$@103",
  "server_port", "sender_ip", "$@104", "sender_port", "max_queue_size",
  "ncr_protocol", "$@105", "ncr_protocol_value", "ncr_format", "$@106",
  "always_include_fqdn", "override_no_update", "override_client_update",
  "replace_client_name", "$@107", "replace_client_name_value",
  "generated_prefix", "$@108", "hostname_char_set", "$@109",
  "hostname_char_replacement", "$@110", "dhcp6_json_object", "$@111",
  "dhcpddns_json_object", "$@112", "control_agent_json_object", "$@113",
  "config_control", "$@114", "$@115", "sub_config_control", "$@116",
  "config_control_params", "config_control_param", "config_databases",
  "$@117", "logging_object", "$@118", "sub_logging", "$@119",
  "logging_params", "logging_param", "loggers", "$@120", "loggers_entries",
  "logger_entry", "$@121", "logger_params", "logger_param", "debuglevel",
  "severity", "$@122", "output_options_list", "$@123",
  "output_options_list_content", "output_entry", "$@124",
  "output_params_list", "output_params", "output", "$@125", "flush",
  "maxsize", "maxver", YY_NULLPTR
  };

#if PARSER4_DEBUG
  const unsigned short
  Dhcp4Parser::yyrline_[] =
  {
       0,   253,   253,   253,   254,   254,   255,   255,   256,   256,
     257,   257,   258,   258,   259,   259,   260,   260,   261,   261,
     262,   262,   263,   263,   264,   264,   265,   265,   266,   266,
     274,   275,   276,   277,   278,   279,   280,   283,   288,   288,
     299,   302,   303,   306,   310,   317,   317,   324,   325,   328,
     332,   339,   339,   346,   347,   350,   354,   365,   375,   375,
     391,   392,   396,   397,   398,   399,   400,   401,   404,   404,
     419,   419,   428,   429,   434,   435,   436,   437,   438,   439,
     440,   441,   442,   443,   444,   445,   446,   447,   448,   449,
     450,   451,   452,   453,   454,   455,   456,   457,   458,   459,
     460,   461,   462,   463,   464,   465,   468,   473,   478,   483,
     488,   488,   496,   501,   506,   512,   512,   523,   524,   527,
     528,   529,   530,   531,   532,   533,   536,   536,   545,   545,
     555,   555,   562,   563,   566,   566,   573,   575,   579,   585,
     585,   597,   597,   607,   608,   610,   612,   612,   630,   630,
     642,   642,   652,   653,   656,   657,   660,   660,   670,   671,
     674,   675,   676,   677,   678,   679,   680,   681,   682,   683,
     684,   685,   686,   687,   688,   689,   690,   691,   694,   694,
     701,   702,   703,   704,   707,   707,   715,   715,   723,   723,
     731,   736,   736,   744,   749,   754,   759,   764,   769,   774,
     779,   779,   787,   787,   795,   800,   805,   805,   815,   816,
     819,   820,   821,   822,   823,   826,   831,   836,   841,   846,
     851,   851,   861,   862,   865,   866,   869,   869,   879,   879,
     889,   890,   891,   894,   895,   898,   898,   906,   906,   914,
     914,   925,   926,   929,   930,   931,   932,   933,   934,   937,
     942,   947,   952,   957,   962,   970,   970,   983,   984,   987,
     988,   995,   995,  1021,  1021,  1032,  1033,  1037,  1038,  1039,
    1040,  1041,  1042,  1043,  1044,  1045,  1046,  1047,  1048,  1049,
    1050,  1051,  1052,  1053,  1054,  1055,  1056,  1057,  1058,  1059,
    1060,  1063,  1063,  1071,  1071,  1079,  1079,  1087,  1087,  1095,
    1095,  1103,  1103,  1111,  1111,  1121,  1121,  1128,  1129,  1130,
    1131,  1134,  1141,  1141,  1152,  1153,  1157,  1158,  1161,  1161,
    1169,  1170,  1173,  1174,  1175,  1176,  1177,  1178,  1179,  1180,
    1181,  1182,  1183,  1184,  1185,  1186,  1187,  1188,  1189,  1190,
    1191,  1198,  1198,  1211,  1211,  1220,  1221,  1224,  1225,  1230,
    1230,  1245,  1245,  1259,  1260,  1263,  1264,  1267,  1268,  1269,
    1270,  1271,  1272,  1273,  1274,  1275,  1276,  1279,  1281,  1286,
    1288,  1288,  1296,  1296,  1304,  1304,  1312,  1314,  1314,  1322,
    1331,  1331,  1343,  1344,  1349,  1350,  1355,  1355,  1367,  1367,
    1379,  1380,  1385,  1386,  1391,  1392,  1393,  1394,  1395,  1396,
    1397,  1398,  1399,  1402,  1404,  1404,  1412,  1414,  1416,  1421,
    1429,  1429,  1441,  1442,  1445,  1446,  1449,  1449,  1459,  1459,
    1469,  1470,  1473,  1474,  1475,  1476,  1477,  1478,  1479,  1482,
    1482,  1490,  1490,  1515,  1515,  1545,  1545,  1555,  1556,  1559,
    1560,  1563,  1563,  1572,  1572,  1581,  1582,  1585,  1586,  1590,
    1591,  1592,  1593,  1594,  1595,  1596,  1597,  1598,  1599,  1600,
    1601,  1602,  1603,  1604,  1607,  1607,  1615,  1615,  1623,  1623,
    1631,  1631,  1639,  1639,  1649,  1649,  1657,  1657,  1665,  1665,
    1673,  1673,  1681,  1681,  1689,  1689,  1697,  1697,  1710,  1710,
    1720,  1721,  1727,  1727,  1737,  1738,  1741,  1741,  1751,  1752,
    1755,  1756,  1759,  1760,  1761,  1762,  1763,  1764,  1765,  1766,
    1767,  1768,  1769,  1772,  1774,  1774,  1782,  1791,  1798,  1798,
    1808,  1809,  1812,  1813,  1814,  1815,  1816,  1819,  1819,  1827,
    1827,  1837,  1837,  1849,  1849,  1859,  1860,  1863,  1864,  1865,
    1866,  1867,  1868,  1869,  1870,  1871,  1872,  1873,  1874,  1875,
    1876,  1877,  1878,  1879,  1880,  1881,  1884,  1889,  1889,  1897,
    1897,  1905,  1910,  1910,  1918,  1923,  1928,  1928,  1936,  1937,
    1940,  1940,  1948,  1953,  1958,  1963,  1963,  1971,  1974,  1977,
    1980,  1983,  1989,  1989,  1997,  1997,  2005,  2005,  2016,  2016,
    2023,  2023,  2030,  2030,  2037,  2037,  2046,  2046,  2057,  2057,
    2067,  2068,  2072,  2073,  2076,  2076,  2091,  2091,  2101,  2101,
    2112,  2113,  2117,  2121,  2121,  2133,  2134,  2138,  2138,  2146,
    2147,  2150,  2151,  2152,  2153,  2154,  2155,  2156,  2159,  2164,
    2164,  2172,  2172,  2182,  2183,  2186,  2186,  2194,  2195,  2198,
    2199,  2200,  2201,  2204,  2204,  2212,  2217,  2222
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


#line 14 "dhcp4_parser.yy" // lalr1.cc:1181
} } // isc::dhcp
#line 4918 "dhcp4_parser.cc" // lalr1.cc:1181
#line 2227 "dhcp4_parser.yy" // lalr1.cc:1182


void
isc::dhcp::Dhcp4Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
