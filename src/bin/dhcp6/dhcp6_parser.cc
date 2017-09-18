// A Bison parser, made by GNU Bison 3.0.4.

// Skeleton implementation for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015 Free Software Foundation, Inc.

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
#define yylex   parser6_lex

// First part of user declarations.

#line 39 "dhcp6_parser.cc" // lalr1.cc:404

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

#include "dhcp6_parser.h"

// User implementation prologue.

#line 53 "dhcp6_parser.cc" // lalr1.cc:412
// Unqualified %code blocks.
#line 34 "dhcp6_parser.yy" // lalr1.cc:413

#include <dhcp6/parser_context.h>

#line 59 "dhcp6_parser.cc" // lalr1.cc:413


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
#if PARSER6_DEBUG

// A pseudo ostream that takes yydebug_ into account.
# define YYCDEBUG if (yydebug_) (*yycdebug_)

# define YY_SYMBOL_PRINT(Title, Symbol)         \
  do {                                          \
    if (yydebug_)                               \
    {                                           \
      *yycdebug_ << Title << ' ';               \
      yy_print_ (*yycdebug_, Symbol);           \
      *yycdebug_ << std::endl;                  \
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
# define YY_SYMBOL_PRINT(Title, Symbol)  YYUSE(Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void>(0)
# define YY_STACK_PRINT()                static_cast<void>(0)

#endif // !PARSER6_DEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)

#line 14 "dhcp6_parser.yy" // lalr1.cc:479
namespace isc { namespace dhcp {
#line 145 "dhcp6_parser.cc" // lalr1.cc:479

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


  /*---------------.
  | Symbol types.  |
  `---------------*/



  // by_state.
  inline
  Dhcp6Parser::by_state::by_state ()
    : state (empty_state)
  {}

  inline
  Dhcp6Parser::by_state::by_state (const by_state& other)
    : state (other.state)
  {}

  inline
  void
  Dhcp6Parser::by_state::clear ()
  {
    state = empty_state;
  }

  inline
  void
  Dhcp6Parser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  inline
  Dhcp6Parser::by_state::by_state (state_type s)
    : state (s)
  {}

  inline
  Dhcp6Parser::symbol_number_type
  Dhcp6Parser::by_state::type_get () const
  {
    if (state == empty_state)
      return empty_symbol;
    else
      return yystos_[state];
  }

  inline
  Dhcp6Parser::stack_symbol_type::stack_symbol_type ()
  {}


  inline
  Dhcp6Parser::stack_symbol_type::stack_symbol_type (state_type s, symbol_type& that)
    : super_type (s, that.location)
  {
      switch (that.type_get ())
    {
      case 170: // value
      case 174: // map_value
      case 218: // db_type
      case 294: // hr_mode
      case 425: // duid_type
      case 458: // ncr_protocol_value
      case 466: // replace_client_name_value
        value.move< ElementPtr > (that.value);
        break;

      case 154: // "boolean"
        value.move< bool > (that.value);
        break;

      case 153: // "floating point"
        value.move< double > (that.value);
        break;

      case 152: // "integer"
        value.move< int64_t > (that.value);
        break;

      case 151: // "constant string"
        value.move< std::string > (that.value);
        break;

      default:
        break;
    }

    // that is emptied.
    that.type = empty_symbol;
  }

  inline
  Dhcp6Parser::stack_symbol_type&
  Dhcp6Parser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
      switch (that.type_get ())
    {
      case 170: // value
      case 174: // map_value
      case 218: // db_type
      case 294: // hr_mode
      case 425: // duid_type
      case 458: // ncr_protocol_value
      case 466: // replace_client_name_value
        value.copy< ElementPtr > (that.value);
        break;

      case 154: // "boolean"
        value.copy< bool > (that.value);
        break;

      case 153: // "floating point"
        value.copy< double > (that.value);
        break;

      case 152: // "integer"
        value.copy< int64_t > (that.value);
        break;

      case 151: // "constant string"
        value.copy< std::string > (that.value);
        break;

      default:
        break;
    }

    location = that.location;
    return *this;
  }


  template <typename Base>
  inline
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
    // Avoid a (spurious) G++ 4.8 warning about "array subscript is
    // below array bounds".
    if (yysym.empty ())
      std::abort ();
    yyo << (yytype < yyntokens_ ? "token" : "nterm")
        << ' ' << yytname_[yytype] << " ("
        << yysym.location << ": ";
    switch (yytype)
    {
            case 151: // "constant string"

#line 227 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< std::string > (); }
#line 364 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 152: // "integer"

#line 227 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< int64_t > (); }
#line 371 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 153: // "floating point"

#line 227 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< double > (); }
#line 378 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 154: // "boolean"

#line 227 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< bool > (); }
#line 385 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 170: // value

#line 227 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 392 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 174: // map_value

#line 227 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 399 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 218: // db_type

#line 227 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 406 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 294: // hr_mode

#line 227 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 413 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 425: // duid_type

#line 227 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 420 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 458: // ncr_protocol_value

#line 227 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 427 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 466: // replace_client_name_value

#line 227 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 434 "dhcp6_parser.cc" // lalr1.cc:636
        break;


      default:
        break;
    }
    yyo << ')';
  }
#endif

  inline
  void
  Dhcp6Parser::yypush_ (const char* m, state_type s, symbol_type& sym)
  {
    stack_symbol_type t (s, sym);
    yypush_ (m, t);
  }

  inline
  void
  Dhcp6Parser::yypush_ (const char* m, stack_symbol_type& s)
  {
    if (m)
      YY_SYMBOL_PRINT (m, s);
    yystack_.push (s);
  }

  inline
  void
  Dhcp6Parser::yypop_ (unsigned int n)
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

  inline Dhcp6Parser::state_type
  Dhcp6Parser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - yyntokens_] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - yyntokens_];
  }

  inline bool
  Dhcp6Parser::yy_pact_value_is_default_ (int yyvalue)
  {
    return yyvalue == yypact_ninf_;
  }

  inline bool
  Dhcp6Parser::yy_table_value_is_error_ (int yyvalue)
  {
    return yyvalue == yytable_ninf_;
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

    // FIXME: This shoud be completely indented.  It is not yet to
    // avoid gratuitous conflicts when merging into the master branch.
    try
      {
    YYCDEBUG << "Starting parse" << std::endl;


    /* Initialize the stack.  The initial state will be set in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystack_.clear ();
    yypush_ (YY_NULLPTR, 0, yyla);

    // A new symbol was pushed on the stack.
  yynewstate:
    YYCDEBUG << "Entering state " << yystack_[0].state << std::endl;

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
        try
          {
            symbol_type yylookahead (yylex (ctx));
            yyla.move (yylookahead);
          }
        catch (const syntax_error& yyexc)
          {
            error (yyexc);
            goto yyerrlab1;
          }
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
      yylhs.state = yy_lr_goto_state_(yystack_[yylen].state, yyr1_[yyn]);
      /* Variants are always initialized to an empty instance of the
         correct type. The default '$$ = $1' action is NOT applied
         when using variants.  */
        switch (yyr1_[yyn])
    {
      case 170: // value
      case 174: // map_value
      case 218: // db_type
      case 294: // hr_mode
      case 425: // duid_type
      case 458: // ncr_protocol_value
      case 466: // replace_client_name_value
        yylhs.value.build< ElementPtr > ();
        break;

      case 154: // "boolean"
        yylhs.value.build< bool > ();
        break;

      case 153: // "floating point"
        yylhs.value.build< double > ();
        break;

      case 152: // "integer"
        yylhs.value.build< int64_t > ();
        break;

      case 151: // "constant string"
        yylhs.value.build< std::string > ();
        break;

      default:
        break;
    }


      // Compute the default @$.
      {
        slice<stack_symbol_type, stack_type> slice (yystack_, yylen);
        YYLLOC_DEFAULT (yylhs.location, slice, yylen);
      }

      // Perform the reduction.
      YY_REDUCE_PRINT (yyn);
      try
        {
          switch (yyn)
            {
  case 2:
#line 236 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.NO_KEYWORD; }
#line 680 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 4:
#line 237 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.CONFIG; }
#line 686 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 6:
#line 238 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.DHCP6; }
#line 692 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 8:
#line 239 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.INTERFACES_CONFIG; }
#line 698 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 10:
#line 240 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.SUBNET6; }
#line 704 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 12:
#line 241 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.POOLS; }
#line 710 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 14:
#line 242 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.PD_POOLS; }
#line 716 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 16:
#line 243 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.RESERVATIONS; }
#line 722 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 18:
#line 244 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.DHCP6; }
#line 728 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 20:
#line 245 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.OPTION_DEF; }
#line 734 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 22:
#line 246 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.OPTION_DATA; }
#line 740 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 24:
#line 247 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.HOOKS_LIBRARIES; }
#line 746 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 26:
#line 248 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.DHCP_DDNS; }
#line 752 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 28:
#line 256 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 758 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 29:
#line 257 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as< double > (), ctx.loc2pos(yystack_[0].location))); }
#line 764 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 30:
#line 258 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 770 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 31:
#line 259 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 776 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 32:
#line 260 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 782 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 33:
#line 261 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 788 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 34:
#line 262 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 794 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 35:
#line 265 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as< ElementPtr > ());
}
#line 803 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 36:
#line 270 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 814 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 37:
#line 275 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 824 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 38:
#line 281 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 830 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 41:
#line 288 "dhcp6_parser.yy" // lalr1.cc:859
    {
                  // map containing a single entry
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 839 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 42:
#line 292 "dhcp6_parser.yy" // lalr1.cc:859
    {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 849 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 43:
#line 299 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 858 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 44:
#line 302 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // list parsing complete. Put any sanity checking here
}
#line 866 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 47:
#line 310 "dhcp6_parser.yy" // lalr1.cc:859
    {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 875 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 48:
#line 314 "dhcp6_parser.yy" // lalr1.cc:859
    {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 884 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 49:
#line 321 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // List parsing about to start
}
#line 892 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 50:
#line 323 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // list parsing complete. Put any sanity checking here
    //ctx.stack_.pop_back();
}
#line 901 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 53:
#line 332 "dhcp6_parser.yy" // lalr1.cc:859
    {
                          ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 910 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 54:
#line 336 "dhcp6_parser.yy" // lalr1.cc:859
    {
                          ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 919 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 55:
#line 347 "dhcp6_parser.yy" // lalr1.cc:859
    {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as< std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 930 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 56:
#line 357 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 941 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 57:
#line 362 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.

    // Dhcp6 is required
    ctx.require("Dhcp6", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
}
#line 954 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 66:
#line 385 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Dhcp6", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP6);
}
#line 967 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 67:
#line 392 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // No global parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 977 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 68:
#line 400 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the Dhcp6 map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 987 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 69:
#line 404 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // No global parameter is required
    // parsing completed
}
#line 996 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 95:
#line 440 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("preferred-lifetime", prf);
}
#line 1005 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 96:
#line 445 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 1014 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 97:
#line 450 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 1023 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 98:
#line 455 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 1032 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 99:
#line 460 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr dpp(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 1041 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 100:
#line 465 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces-config", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.INTERFACES_CONFIG);
}
#line 1052 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 101:
#line 470 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // No interfaces config param is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1062 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 102:
#line 476 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1072 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 103:
#line 480 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // No interfaces config param is required
    // parsing completed
}
#line 1081 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 108:
#line 493 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1092 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 109:
#line 498 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1101 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 110:
#line 503 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("re-detect", b);
}
#line 1110 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 111:
#line 509 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lease-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.LEASE_DATABASE);
}
#line 1121 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 112:
#line 514 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1132 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 113:
#line 521 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1143 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 114:
#line 526 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1154 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 130:
#line 552 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.DATABASE_TYPE);
}
#line 1162 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 131:
#line 554 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("type", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1171 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 132:
#line 559 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("memfile", ctx.loc2pos(yystack_[0].location))); }
#line 1177 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 133:
#line 560 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("mysql", ctx.loc2pos(yystack_[0].location))); }
#line 1183 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 134:
#line 561 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("postgresql", ctx.loc2pos(yystack_[0].location))); }
#line 1189 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 135:
#line 562 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("cql", ctx.loc2pos(yystack_[0].location))); }
#line 1195 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 136:
#line 565 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1203 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 137:
#line 567 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr user(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1213 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 138:
#line 573 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1221 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 139:
#line 575 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr pwd(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 1231 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 140:
#line 581 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1239 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 141:
#line 583 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr h(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 1249 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 142:
#line 589 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr p(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", p);
}
#line 1258 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 143:
#line 594 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1266 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 144:
#line 596 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1276 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 145:
#line 602 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 1285 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 146:
#line 607 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 1294 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 147:
#line 612 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 1303 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 148:
#line 617 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("connect-timeout", n);
}
#line 1312 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 149:
#line 622 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1320 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 150:
#line 624 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr cp(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("contact-points", cp);
    ctx.leave();
}
#line 1330 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 151:
#line 630 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1338 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 152:
#line 632 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr ks(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("keyspace", ks);
    ctx.leave();
}
#line 1348 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 153:
#line 639 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("mac-sources", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.MAC_SOURCES);
}
#line 1359 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 154:
#line 644 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1368 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 159:
#line 657 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1377 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 160:
#line 662 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr duid(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1386 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 161:
#line 667 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 1397 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 162:
#line 672 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1406 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 168:
#line 686 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 1415 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 169:
#line 691 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr flex_id(new StringElement("flex-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(flex_id);
}
#line 1424 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 170:
#line 698 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay-supplied-options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1435 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 171:
#line 703 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1444 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 172:
#line 708 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 1455 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 173:
#line 713 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1464 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 178:
#line 726 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1474 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 179:
#line 730 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1484 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 180:
#line 736 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1494 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 181:
#line 740 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 1504 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 187:
#line 755 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1512 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 188:
#line 757 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr lib(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 1522 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 189:
#line 763 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1530 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 190:
#line 765 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1539 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 191:
#line 771 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.EXPIRED_LEASES_PROCESSING);
}
#line 1550 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 192:
#line 776 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // No expired lease parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1560 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 201:
#line 794 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 1569 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 202:
#line 799 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 1578 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 203:
#line 804 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 1587 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 204:
#line 809 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 1596 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 205:
#line 814 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 1605 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 206:
#line 819 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 1614 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 207:
#line 827 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet6", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET6);
}
#line 1625 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 208:
#line 832 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1634 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 213:
#line 852 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1644 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 214:
#line 856 "dhcp6_parser.yy" // lalr1.cc:859
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
#line 1670 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 215:
#line 878 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the subnet6 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1680 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 216:
#line 882 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The subnet subnet6 parameter is required
    ctx.require("subnet", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 1690 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 237:
#line 914 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1698 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 238:
#line 916 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr subnet(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 1708 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 239:
#line 922 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1716 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 240:
#line 924 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 1726 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 241:
#line 930 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1734 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 242:
#line 932 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface-id", iface);
    ctx.leave();
}
#line 1744 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 243:
#line 938 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.CLIENT_CLASS);
}
#line 1752 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 244:
#line 940 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr cls(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 1762 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 245:
#line 946 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.RESERVATION_MODE);
}
#line 1770 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 246:
#line 948 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("reservation-mode", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1779 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 247:
#line 953 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("disabled", ctx.loc2pos(yystack_[0].location))); }
#line 1785 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 248:
#line 954 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("out-of-pool", ctx.loc2pos(yystack_[0].location))); }
#line 1791 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 249:
#line 955 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("all", ctx.loc2pos(yystack_[0].location))); }
#line 1797 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 250:
#line 958 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr id(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 1806 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 251:
#line 963 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr rc(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rapid-commit", rc);
}
#line 1815 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 252:
#line 971 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("shared-networks", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SHARED_NETWORK);
}
#line 1826 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 253:
#line 976 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1835 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 258:
#line 991 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1845 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 259:
#line 995 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1853 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 276:
#line 1023 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 1864 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 277:
#line 1028 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1873 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 278:
#line 1036 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1882 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 279:
#line 1039 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1890 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 284:
#line 1055 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1900 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 285:
#line 1059 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1912 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 286:
#line 1070 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1922 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 287:
#line 1074 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 1934 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 301:
#line 1104 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr code(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 1943 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 303:
#line 1111 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1951 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 304:
#line 1113 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 1961 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 305:
#line 1119 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1969 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 306:
#line 1121 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 1979 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 307:
#line 1127 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1987 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 308:
#line 1129 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr space(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 1997 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 310:
#line 1137 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2005 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 311:
#line 1139 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr encap(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 2015 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 312:
#line 1145 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr array(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 2024 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 313:
#line 1154 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 2035 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 314:
#line 1159 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2044 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 319:
#line 1178 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2054 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 320:
#line 1182 "dhcp6_parser.yy" // lalr1.cc:859
    {
    /// @todo: the code or name parameters are required.
    ctx.stack_.pop_back();
}
#line 2063 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 321:
#line 1190 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2073 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 322:
#line 1194 "dhcp6_parser.yy" // lalr1.cc:859
    {
    /// @todo: the code or name parameters are required.
    // parsing completed
}
#line 2082 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 335:
#line 1225 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2090 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 336:
#line 1227 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr data(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 2100 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 339:
#line 1237 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr space(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", space);
}
#line 2109 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 340:
#line 1242 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr persist(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-send", persist);
}
#line 2118 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 341:
#line 1250 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 2129 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 342:
#line 1255 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2138 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 347:
#line 1270 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2148 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 348:
#line 1274 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2158 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 349:
#line 1280 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2168 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 350:
#line 1284 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
}
#line 2177 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 357:
#line 1299 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2185 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 358:
#line 1301 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr pool(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 2195 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 359:
#line 1307 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2203 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 360:
#line 1309 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("user-context", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2212 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 361:
#line 1317 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pd-pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.PD_POOLS);
}
#line 2223 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 362:
#line 1322 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2232 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 367:
#line 1337 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2242 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 368:
#line 1341 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The prefix, prefix len and delegated len parameters are required.
    ctx.require("prefix", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("prefix-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("delegated-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2254 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 369:
#line 1349 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the pd-pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2264 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 370:
#line 1353 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The prefix, prefix len and delegated len parameters are required.
    ctx.require("prefix", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("prefix-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("delegated-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2276 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 381:
#line 1375 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2284 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 382:
#line 1377 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix", prf);
    ctx.leave();
}
#line 2294 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 383:
#line 1383 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix-len", prf);
}
#line 2303 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 384:
#line 1388 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2311 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 385:
#line 1390 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix", prf);
    ctx.leave();
}
#line 2321 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 386:
#line 1396 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix-len", prf);
}
#line 2330 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 387:
#line 1401 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr deleg(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("delegated-len", deleg);
}
#line 2339 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 388:
#line 1409 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 2350 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 389:
#line 1414 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2359 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 394:
#line 1427 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2369 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 395:
#line 1431 "dhcp6_parser.yy" // lalr1.cc:859
    {
    /// @todo: an identifier parameter is required.
    ctx.stack_.pop_back();
}
#line 2378 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 396:
#line 1436 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2388 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 397:
#line 1440 "dhcp6_parser.yy" // lalr1.cc:859
    {
    /// @todo: an identifier parameter is required.
    // parsing completed
}
#line 2397 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 411:
#line 1465 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-addresses", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2408 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 412:
#line 1470 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2417 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 413:
#line 1475 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefixes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2428 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 414:
#line 1480 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2437 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 415:
#line 1485 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2445 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 416:
#line 1487 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr d(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 2455 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 417:
#line 1493 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2463 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 418:
#line 1495 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 2473 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 419:
#line 1501 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2481 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 420:
#line 1503 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr host(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 2491 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 421:
#line 1509 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2499 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 422:
#line 1511 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flex-id", hw);
    ctx.leave();
}
#line 2509 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 423:
#line 1517 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2520 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 424:
#line 1522 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2529 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 425:
#line 1530 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 2540 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 426:
#line 1535 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2549 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 427:
#line 1540 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2557 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 428:
#line 1542 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr ip(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", ip);
    ctx.leave();
}
#line 2567 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 429:
#line 1551 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 2578 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 430:
#line 1556 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2587 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 433:
#line 1565 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2597 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 434:
#line 1569 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The name client class parameter is required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2607 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 444:
#line 1591 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2615 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 445:
#line 1593 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr test(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 2625 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 446:
#line 1602 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-id", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SERVER_ID);
}
#line 2636 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 447:
#line 1607 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The type parameter is required.
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2647 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 457:
#line 1627 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.DUID_TYPE);
}
#line 2655 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 458:
#line 1629 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("type", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2664 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 459:
#line 1634 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("LLT", ctx.loc2pos(yystack_[0].location))); }
#line 2670 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 460:
#line 1635 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("EN", ctx.loc2pos(yystack_[0].location))); }
#line 2676 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 461:
#line 1636 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("LL", ctx.loc2pos(yystack_[0].location))); }
#line 2682 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 462:
#line 1639 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr htype(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("htype", htype);
}
#line 2691 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 463:
#line 1644 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2699 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 464:
#line 1646 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr id(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("identifier", id);
    ctx.leave();
}
#line 2709 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 465:
#line 1652 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("time", time);
}
#line 2718 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 466:
#line 1657 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enterprise-id", time);
}
#line 2727 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 467:
#line 1664 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 2736 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 468:
#line 1671 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 2747 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 469:
#line 1676 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2756 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 474:
#line 1689 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2764 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 475:
#line 1691 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr stype(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 2774 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 476:
#line 1697 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2782 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 477:
#line 1699 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 2792 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 478:
#line 1707 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 2803 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 479:
#line 1712 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2814 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 480:
#line 1719 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2824 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 481:
#line 1723 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2834 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 499:
#line 1750 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 2843 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 500:
#line 1755 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2851 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 501:
#line 1757 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("qualifying-suffix", s);
    ctx.leave();
}
#line 2861 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 502:
#line 1763 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2869 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 503:
#line 1765 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 2879 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 504:
#line 1771 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 2888 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 505:
#line 1776 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2896 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 506:
#line 1778 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 2906 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 507:
#line 1784 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 2915 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 508:
#line 1789 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 2924 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 509:
#line 1794 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 2932 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 510:
#line 1796 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2941 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 511:
#line 1802 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 2947 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 512:
#line 1803 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 2953 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 513:
#line 1806 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NCR_FORMAT);
}
#line 2961 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 514:
#line 1808 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 2971 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 515:
#line 1814 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-include-fqdn", b);
}
#line 2980 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 516:
#line 1819 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-no-update", b);
}
#line 2989 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 517:
#line 1824 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-client-update", b);
}
#line 2998 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 518:
#line 1829 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 3006 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 519:
#line 1831 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("replace-client-name", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3015 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 520:
#line 1837 "dhcp6_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("when-present", ctx.loc2pos(yystack_[0].location))); 
      }
#line 3023 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 521:
#line 1840 "dhcp6_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location)));
      }
#line 3031 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 522:
#line 1843 "dhcp6_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("always", ctx.loc2pos(yystack_[0].location)));
      }
#line 3039 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 523:
#line 1846 "dhcp6_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("when-not-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 3047 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 524:
#line 1849 "dhcp6_parser.yy" // lalr1.cc:859
    {
      error(yystack_[0].location, "boolean values for the replace-client-name are "
                "no longer supported");
      }
#line 3056 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 525:
#line 1855 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3064 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 526:
#line 1857 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("generated-prefix", s);
    ctx.leave();
}
#line 3074 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 527:
#line 1865 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3082 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 528:
#line 1867 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("Dhcp4", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3091 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 529:
#line 1872 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3099 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 530:
#line 1874 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("DhcpDdns", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3108 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 531:
#line 1879 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3116 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 532:
#line 1881 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("Control-agent", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3125 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 533:
#line 1892 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Logging", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.LOGGING);
}
#line 3136 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 534:
#line 1897 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3145 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 538:
#line 1914 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 3156 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 539:
#line 1919 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3165 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 542:
#line 1931 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 3175 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 543:
#line 1935 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 3183 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 551:
#line 1950 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr dl(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 3192 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 552:
#line 1955 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3200 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 553:
#line 1957 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 3210 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 554:
#line 1963 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 3221 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 555:
#line 1968 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3230 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 558:
#line 1977 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3240 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 559:
#line 1981 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 3248 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 566:
#line 1995 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3256 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 567:
#line 1997 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 3266 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 568:
#line 2003 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr flush(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 3275 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 569:
#line 2008 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr maxsize(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 3284 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 570:
#line 2013 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr maxver(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 3293 "dhcp6_parser.cc" // lalr1.cc:859
    break;


#line 3297 "dhcp6_parser.cc" // lalr1.cc:859
            default:
              break;
            }
        }
      catch (const syntax_error& yyexc)
        {
          error (yyexc);
          YYERROR;
        }
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
    yyerror_range[1].location = yystack_[yylen - 1].location;
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
    catch (...)
      {
        YYCDEBUG << "Exception caught: cleaning lookahead and stack"
                 << std::endl;
        // Do not try to display the values of the reclaimed symbols,
        // as their printer might throw an exception.
        if (!yyla.empty ())
          yy_destroy_ (YY_NULLPTR, yyla);

        while (1 < yystack_.size ())
          {
            yy_destroy_ (YY_NULLPTR, yystack_[0]);
            yypop_ ();
          }
        throw;
      }
  }

  void
  Dhcp6Parser::error (const syntax_error& yyexc)
  {
    error (yyexc.location, yyexc.what());
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
        YYCASE_(0, YY_("syntax error"));
        YYCASE_(1, YY_("syntax error, unexpected %s"));
        YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
        YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
        YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
        YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
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


  const short int Dhcp6Parser::yypact_ninf_ = -707;

  const signed char Dhcp6Parser::yytable_ninf_ = -1;

  const short int
  Dhcp6Parser::yypact_[] =
  {
     211,  -707,  -707,  -707,  -707,  -707,  -707,  -707,  -707,  -707,
    -707,  -707,  -707,  -707,    45,    23,    61,    76,    86,   116,
     124,   126,   166,   177,   187,   204,   227,   238,  -707,  -707,
    -707,  -707,  -707,  -707,  -707,  -707,  -707,  -707,  -707,  -707,
    -707,  -707,  -707,  -707,  -707,  -707,  -707,  -707,  -707,  -707,
    -707,  -707,  -707,  -707,  -707,  -707,  -707,  -707,  -707,  -707,
    -707,  -707,  -707,  -707,    23,   120,    14,   121,   135,    16,
      73,    63,    67,   246,    53,   189,   -13,   143,  -707,   281,
     297,   304,   302,   309,  -707,  -707,  -707,  -707,  -707,   314,
    -707,    59,  -707,  -707,  -707,  -707,  -707,  -707,  -707,  -707,
    -707,   318,   319,   337,   338,   343,  -707,  -707,  -707,  -707,
    -707,  -707,  -707,  -707,  -707,  -707,  -707,   358,  -707,  -707,
    -707,    82,  -707,  -707,  -707,  -707,  -707,  -707,  -707,  -707,
    -707,  -707,  -707,  -707,  -707,  -707,  -707,  -707,  -707,  -707,
    -707,  -707,  -707,  -707,  -707,  -707,   359,    94,  -707,  -707,
    -707,  -707,  -707,  -707,  -707,  -707,  -707,  -707,   360,   361,
    -707,  -707,  -707,  -707,  -707,  -707,  -707,  -707,  -707,   100,
    -707,  -707,  -707,  -707,  -707,  -707,  -707,  -707,  -707,  -707,
    -707,  -707,  -707,  -707,  -707,  -707,  -707,   131,  -707,  -707,
    -707,  -707,   362,  -707,   363,   364,  -707,  -707,  -707,   158,
    -707,  -707,  -707,  -707,  -707,  -707,  -707,  -707,  -707,  -707,
    -707,  -707,  -707,  -707,  -707,   365,   366,  -707,  -707,  -707,
    -707,  -707,  -707,  -707,  -707,   367,  -707,  -707,   368,  -707,
    -707,  -707,   370,  -707,  -707,   369,   373,  -707,  -707,  -707,
    -707,  -707,  -707,  -707,  -707,  -707,  -707,  -707,   374,   375,
    -707,  -707,  -707,  -707,   372,   378,  -707,  -707,  -707,  -707,
    -707,  -707,  -707,  -707,  -707,  -707,   160,  -707,  -707,  -707,
     379,  -707,  -707,   380,  -707,   381,   382,  -707,  -707,   383,
     384,   385,  -707,  -707,  -707,   194,  -707,  -707,  -707,  -707,
    -707,  -707,  -707,  -707,  -707,  -707,  -707,  -707,  -707,  -707,
    -707,  -707,    23,    23,  -707,   219,   386,   387,   388,   389,
     390,  -707,    14,  -707,   391,   392,   393,   230,   247,   248,
     249,   250,   394,   399,   400,   401,   402,   403,   404,   405,
     406,   407,   408,   261,   410,   411,   121,  -707,   412,   217,
     135,  -707,    20,   413,   414,   415,   416,   417,   418,   272,
     269,   421,   422,   423,   427,    16,  -707,   428,    73,  -707,
     429,   282,   431,   284,   285,    63,  -707,   434,   435,   436,
     437,   438,   439,   440,  -707,    67,  -707,   441,   442,   298,
     445,   447,   448,   299,  -707,    53,   450,   303,   305,  -707,
     189,   454,   456,   -23,  -707,   307,   458,   459,   312,   461,
     316,   320,   466,   467,   321,   322,   323,   469,   474,   143,
    -707,  -707,  -707,   475,   473,   476,    23,    23,    23,  -707,
     477,   478,   480,  -707,  -707,  -707,  -707,  -707,   483,   484,
     485,   486,   487,   488,   489,   490,   491,   492,   493,  -707,
     494,   495,  -707,   498,  -707,  -707,  -707,  -707,  -707,  -707,
     496,   479,  -707,  -707,  -707,   500,   501,   503,   330,   346,
     347,  -707,  -707,   271,   356,   506,   505,  -707,   357,  -707,
     371,  -707,   376,  -707,  -707,  -707,   498,   498,   498,   377,
     395,   396,   397,  -707,   398,   409,  -707,   419,   420,   424,
    -707,  -707,   425,  -707,  -707,  -707,   426,    23,  -707,  -707,
     430,   432,  -707,   433,  -707,  -707,    -7,   443,  -707,  -707,
    -707,    85,   444,  -707,    23,   121,   446,  -707,  -707,  -707,
     135,    13,    13,   507,   508,   509,   510,   -30,    23,    93,
      58,   511,   176,    28,   229,   143,  -707,  -707,   515,  -707,
      20,   513,   514,  -707,  -707,  -707,  -707,  -707,  -707,  -707,
    -707,  -707,  -707,   516,   449,  -707,  -707,  -707,  -707,  -707,
    -707,  -707,  -707,  -707,  -707,  -707,  -707,  -707,  -707,  -707,
    -707,  -707,  -707,  -707,  -707,  -707,  -707,  -707,  -707,  -707,
    -707,  -707,  -707,  -707,  -707,  -707,  -707,  -707,   197,  -707,
     209,  -707,  -707,   212,  -707,  -707,  -707,  -707,   520,   521,
     525,   527,   528,  -707,  -707,  -707,   232,  -707,  -707,  -707,
    -707,  -707,  -707,  -707,  -707,  -707,  -707,  -707,  -707,  -707,
     234,  -707,   529,   530,  -707,  -707,   531,   533,  -707,  -707,
     532,   536,  -707,  -707,   534,   538,  -707,  -707,  -707,   195,
    -707,  -707,  -707,   537,  -707,  -707,  -707,   220,  -707,  -707,
    -707,  -707,   235,  -707,   539,   541,  -707,   546,   547,   548,
     549,   550,   551,   266,  -707,  -707,  -707,  -707,  -707,  -707,
    -707,  -707,  -707,   552,   553,   554,  -707,  -707,   267,  -707,
    -707,  -707,  -707,  -707,  -707,  -707,  -707,   270,  -707,  -707,
    -707,   274,   451,   452,  -707,  -707,   555,   556,  -707,  -707,
     557,   559,  -707,  -707,   560,   562,  -707,  -707,   526,  -707,
     563,   446,  -707,  -707,   564,   565,   568,   570,   453,   455,
     460,   457,   462,   574,   575,    13,  -707,  -707,    16,  -707,
     507,    53,  -707,   508,   189,  -707,   509,    48,  -707,   510,
     -30,  -707,  -707,    93,  -707,    58,  -707,   -13,  -707,   511,
     463,   464,   465,   468,   470,   471,   176,  -707,   576,   578,
     472,   481,   482,    28,  -707,   581,   582,   229,  -707,  -707,
    -707,   583,   584,  -707,    73,  -707,   513,    63,  -707,   514,
      67,  -707,   516,   586,  -707,   587,  -707,   308,   497,   499,
     502,  -707,  -707,  -707,  -707,  -707,   504,   518,  -707,   276,
    -707,   580,  -707,   585,  -707,  -707,  -707,  -707,  -707,  -707,
    -707,  -707,  -707,  -707,  -707,  -707,  -707,   277,  -707,  -707,
    -707,  -707,  -707,  -707,  -707,   278,  -707,  -707,  -707,  -707,
    -707,  -707,  -707,  -707,   244,   519,  -707,  -707,  -707,  -707,
     535,   540,  -707,  -707,   542,   287,  -707,   288,  -707,   588,
    -707,   543,   590,  -707,  -707,  -707,  -707,  -707,  -707,  -707,
    -707,  -707,  -707,  -707,  -707,  -707,    48,  -707,  -707,  -707,
    -707,  -707,  -707,  -707,  -707,  -707,  -707,  -707,  -707,  -707,
    -707,  -707,   241,  -707,  -707,    65,   590,  -707,  -707,   594,
    -707,  -707,  -707,   294,  -707,  -707,  -707,  -707,  -707,   595,
     512,   596,    65,  -707,   589,  -707,   544,  -707,   597,  -707,
    -707,   327,  -707,    49,   597,  -707,  -707,   602,   603,   604,
     295,  -707,  -707,  -707,  -707,  -707,  -707,   606,   522,   558,
     561,    49,  -707,   545,  -707,  -707,  -707,  -707,  -707
  };

  const unsigned short int
  Dhcp6Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,    24,    26,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     1,    43,
      36,    32,    31,    28,    29,    30,    35,     3,    33,    34,
      56,     5,    68,     7,   102,     9,   215,    11,   349,    13,
     369,    15,   396,    17,   278,    19,   286,    21,   321,    23,
     180,    25,   480,    27,    45,    39,     0,     0,     0,     0,
       0,     0,   398,     0,   288,   323,     0,     0,    47,     0,
      46,     0,     0,    40,    66,   533,   527,   529,   531,     0,
      65,     0,    58,    60,    62,    63,    64,    61,   100,   111,
     113,     0,     0,     0,     0,     0,   207,   276,   313,   252,
     153,   170,   161,   429,   172,   191,   446,     0,   468,   478,
      94,     0,    70,    72,    73,    74,    75,    76,    79,    80,
      81,    82,    84,    83,    88,    89,    77,    78,    86,    87,
      85,    90,    91,    92,    93,   108,     0,     0,   104,   106,
     107,   433,   341,   361,   359,   237,   239,   241,     0,     0,
     245,   243,   388,   425,   236,   219,   220,   221,   222,     0,
     217,   226,   227,   228,   231,   233,   229,   230,   223,   224,
     235,   225,   232,   234,   357,   356,   354,     0,   351,   353,
     355,   381,     0,   384,     0,     0,   380,   376,   379,     0,
     371,   373,   374,   377,   378,   375,   423,   411,   413,   415,
     417,   419,   421,   410,   409,     0,   399,   400,   404,   405,
     402,   406,   407,   408,   403,     0,   303,   143,     0,   307,
     305,   310,     0,   299,   300,     0,   289,   290,   292,   302,
     293,   294,   295,   309,   296,   297,   298,   335,     0,     0,
     333,   334,   337,   338,     0,   324,   325,   327,   328,   329,
     330,   331,   332,   187,   189,   184,     0,   182,   185,   186,
       0,   500,   502,     0,   505,     0,     0,   509,   513,     0,
       0,     0,   518,   525,   498,     0,   482,   484,   485,   486,
     487,   488,   489,   490,   491,   492,   493,   494,   495,   496,
     497,    44,     0,     0,    37,     0,     0,     0,     0,     0,
       0,    55,     0,    57,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    69,     0,     0,
       0,   103,   435,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   216,     0,     0,   350,
       0,     0,     0,     0,     0,     0,   370,     0,     0,     0,
       0,     0,     0,     0,   397,     0,   279,     0,     0,     0,
       0,     0,     0,     0,   287,     0,     0,     0,     0,   322,
       0,     0,     0,     0,   181,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     481,    48,    41,     0,     0,     0,     0,     0,     0,    59,
       0,     0,     0,    95,    96,    97,    98,    99,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   467,
       0,     0,    71,     0,   110,   105,   444,   442,   443,   441,
       0,   436,   437,   439,   440,     0,     0,     0,     0,     0,
       0,   250,   251,     0,     0,     0,     0,   218,     0,   352,
       0,   383,     0,   386,   387,   372,     0,     0,     0,     0,
       0,     0,     0,   401,     0,     0,   301,     0,     0,     0,
     312,   291,     0,   339,   340,   326,     0,     0,   183,   499,
       0,     0,   504,     0,   507,   508,     0,     0,   515,   516,
     517,     0,     0,   483,     0,     0,     0,   528,   530,   532,
       0,     0,     0,   209,   280,   315,   254,     0,    45,     0,
       0,   174,     0,     0,     0,     0,    49,   109,     0,   434,
       0,   343,   363,    38,   360,   238,   240,   242,   247,   248,
     249,   246,   244,   390,     0,   358,   382,   385,   424,   412,
     414,   416,   418,   420,   422,   304,   144,   308,   306,   311,
     336,   188,   190,   501,   503,   506,   511,   512,   510,   514,
     520,   521,   522,   523,   524,   519,   526,    42,     0,   538,
       0,   535,   537,     0,   130,   136,   138,   140,     0,     0,
       0,     0,     0,   149,   151,   129,     0,   115,   117,   118,
     119,   120,   121,   122,   123,   124,   125,   126,   127,   128,
       0,   213,     0,   210,   211,   284,     0,   281,   282,   319,
       0,   316,   317,   258,     0,   255,   256,   159,   160,     0,
     155,   157,   158,     0,   168,   169,   165,     0,   163,   166,
     167,   431,     0,   178,     0,   175,   176,     0,     0,     0,
       0,     0,     0,     0,   193,   195,   196,   197,   198,   199,
     200,   457,   463,     0,     0,     0,   456,   455,     0,   448,
     450,   453,   451,   452,   454,   474,   476,     0,   470,   472,
     473,     0,    51,     0,   438,   347,     0,   344,   345,   367,
       0,   364,   365,   394,     0,   391,   392,   427,     0,    67,
       0,     0,   534,   101,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   112,   114,     0,   208,
       0,   288,   277,     0,   323,   314,     0,     0,   253,     0,
       0,   154,   171,     0,   162,     0,   430,     0,   173,     0,
       0,     0,     0,     0,     0,     0,     0,   192,     0,     0,
       0,     0,     0,     0,   447,     0,     0,     0,   469,   479,
      53,     0,    52,   445,     0,   342,     0,     0,   362,     0,
     398,   389,     0,     0,   426,     0,   536,     0,     0,     0,
       0,   142,   145,   146,   147,   148,     0,     0,   116,     0,
     212,     0,   283,     0,   318,   275,   272,   274,   266,   267,
     262,   263,   264,   265,   271,   270,   273,     0,   260,   268,
     269,   257,   156,   164,   432,     0,   177,   201,   202,   203,
     204,   205,   206,   194,     0,     0,   462,   465,   466,   449,
       0,     0,   471,    50,     0,     0,   346,     0,   366,     0,
     393,     0,     0,   132,   133,   134,   135,   131,   137,   139,
     141,   150,   152,   214,   285,   320,     0,   259,   179,   459,
     460,   461,   458,   464,   475,   477,    54,   348,   368,   395,
     428,   542,     0,   540,   261,     0,     0,   539,   554,     0,
     552,   550,   546,     0,   544,   548,   549,   547,   541,     0,
       0,     0,     0,   543,     0,   551,     0,   545,     0,   553,
     558,     0,   556,     0,     0,   555,   566,     0,     0,     0,
       0,   560,   562,   563,   564,   565,   557,     0,     0,     0,
       0,     0,   559,     0,   568,   569,   570,   561,   567
  };

  const short int
  Dhcp6Parser::yypgoto_[] =
  {
    -707,  -707,  -707,  -707,  -707,  -707,  -707,  -707,  -707,  -707,
    -707,  -707,  -707,  -707,  -707,    12,  -707,    56,  -707,  -707,
    -707,  -707,  -707,  -707,    90,  -707,  -132,  -707,  -707,  -707,
     -66,  -707,  -707,  -707,   279,  -707,  -707,  -707,  -707,    27,
     265,   -62,   -50,   -49,   -48,  -707,  -707,  -707,  -707,  -707,
      99,   273,  -707,  -707,  -707,  -707,  -707,  -707,  -707,   103,
    -104,  -707,  -707,  -707,  -707,  -707,  -707,  -707,  -707,  -707,
    -707,   -74,  -707,  -520,  -707,  -707,  -707,  -707,  -707,  -707,
    -707,  -707,  -707,  -707,  -114,  -507,  -707,  -707,  -707,  -707,
    -116,  -707,  -707,  -707,  -707,  -707,  -707,  -707,  -707,  -121,
    -707,  -707,  -707,  -118,   237,  -707,  -707,  -707,  -707,  -707,
    -707,  -707,  -125,  -707,  -707,  -707,  -707,  -707,  -707,  -706,
    -707,  -707,  -707,   -98,  -707,  -707,  -707,   -93,   283,  -707,
    -707,  -704,  -707,  -686,  -707,  -518,  -707,  -681,  -707,  -707,
    -707,  -680,  -707,  -707,  -707,  -707,  -103,  -707,  -707,  -229,
     566,  -707,  -707,  -707,  -707,  -707,   -92,  -707,  -707,  -707,
     -91,  -707,   257,  -707,   -73,  -707,  -707,  -707,  -707,  -707,
     -61,  -707,  -707,  -707,  -707,  -707,   -54,  -707,  -707,  -707,
     -90,  -707,  -707,  -707,   -89,  -707,   253,  -707,  -707,  -707,
    -707,  -707,  -707,  -707,  -707,  -707,  -707,  -707,  -129,  -707,
    -707,  -707,  -130,   291,  -707,  -707,   -45,  -707,  -707,  -707,
    -707,  -707,  -127,  -707,  -707,  -707,  -123,   292,  -707,  -707,
    -707,  -707,  -707,  -707,  -707,  -707,  -707,  -707,  -707,  -126,
    -707,  -707,  -707,  -122,  -707,   310,  -707,  -707,  -707,  -707,
    -707,  -707,  -707,  -707,  -707,  -707,  -707,  -707,  -707,  -707,
    -674,  -707,  -707,  -707,  -707,  -707,  -707,  -707,  -707,  -707,
     127,  -707,  -707,  -707,  -707,  -707,  -707,   -86,  -707,  -707,
    -707,  -707,  -707,  -707,  -707,  -707,  -707,  -707,  -707,  -707,
     -95,  -707,  -707,  -707,  -707,  -707,  -707,  -707,  -707,   147,
     275,  -707,  -707,  -707,  -707,  -707,  -707,  -707,  -707,  -707,
    -707,  -707,  -707,  -707,  -707,  -707,  -707,  -707,  -707,  -707,
    -707,  -707,  -707,  -707,  -707,  -707,  -707,  -707,  -707,  -707,
    -707,  -707,  -707,   -21,  -707,  -707,  -707,  -194,  -707,  -707,
    -204,  -707,  -707,  -707,  -707,  -707,  -707,  -215,  -707,  -707,
    -231,  -707,  -707,  -707,  -707,  -707
  };

  const short int
  Dhcp6Parser::yydefgoto_[] =
  {
      -1,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    78,    37,    38,    65,   544,
      82,    83,    39,    64,    79,    80,   537,   692,   771,   772,
     120,    41,    66,    91,    92,    93,   306,    43,    67,   121,
     122,   123,   124,   125,   126,   127,   128,   314,    45,    68,
     147,   148,   149,   338,   150,   129,   315,   130,   316,   606,
     607,   608,   714,   857,   609,   715,   610,   716,   611,   717,
     612,   234,   378,   614,   615,   616,   617,   618,   723,   619,
     724,   131,   326,   639,   640,   641,   642,   132,   328,   647,
     648,   649,   650,   133,   327,   134,   330,   654,   655,   656,
     747,    61,    76,   266,   267,   268,   391,   269,   392,   135,
     331,   663,   664,   665,   666,   667,   668,   669,   670,   136,
     322,   622,   623,   624,   728,    47,    69,   169,   170,   171,
     346,   172,   347,   173,   348,   174,   352,   175,   351,   551,
     176,   177,   137,   325,   634,   635,   636,   737,   817,   818,
     138,   323,    55,    73,   626,   627,   628,   731,    57,    74,
     235,   236,   237,   238,   239,   240,   241,   377,   242,   381,
     243,   380,   244,   245,   382,   246,   139,   324,   630,   631,
     632,   734,    59,    75,   254,   255,   256,   257,   258,   386,
     259,   260,   261,   262,   179,   343,   696,   697,   698,   774,
      49,    70,   187,   188,   189,   357,   180,   345,   181,   344,
     700,   701,   702,   777,    51,    71,   199,   200,   201,   360,
     202,   203,   362,   204,   205,   182,   353,   704,   705,   706,
     780,    53,    72,   215,   216,   217,   218,   368,   219,   369,
     220,   370,   221,   371,   222,   372,   223,   373,   224,   367,
     183,   354,   708,   783,   140,   329,   652,   342,   450,   451,
     452,   453,   454,   538,   141,   332,   678,   679,   680,   758,
     872,   681,   682,   759,   683,   684,   142,   143,   334,   687,
     688,   689,   765,   690,   766,   144,   335,    63,    77,   285,
     286,   287,   288,   396,   289,   397,   290,   291,   399,   292,
     293,   294,   402,   578,   295,   403,   296,   297,   298,   299,
     407,   585,   300,   408,    94,   308,    95,   309,    96,   310,
      97,   307,   590,   591,   592,   710,   882,   883,   885,   893,
     894,   895,   896,   901,   897,   899,   911,   912,   913,   920,
     921,   922,   927,   923,   924,   925
  };

  const unsigned short int
  Dhcp6Parser::yytable_[] =
  {
      90,   251,   252,   164,   185,   196,   213,   165,   233,   250,
     265,   284,   651,   677,   253,   178,   186,   197,   214,   166,
     167,   168,   646,   151,    84,   190,   198,    36,    29,   594,
      30,   811,    31,   812,   595,   596,   597,   598,   599,   600,
     601,   602,   603,   604,   671,    28,   637,   101,   102,   103,
     104,   813,   227,   599,   108,   151,   815,   816,   108,   227,
     263,   264,   312,   820,   152,   151,   153,   313,    40,   226,
     263,   264,   154,   155,   156,   157,   158,   159,   160,   101,
     102,   103,   104,    42,   106,   336,   108,   227,   161,   162,
     337,   446,   227,    44,   228,   229,   163,   340,   230,   231,
     232,   108,   341,   355,   227,   108,   156,   157,   356,   159,
     160,   108,   576,   577,   191,   192,   193,   194,   195,   154,
     161,   638,   184,    46,   672,   673,   674,   675,   163,   154,
     161,    48,    98,    50,   358,    99,   100,   206,    89,   359,
      85,   207,   208,   209,   210,   211,   212,   145,   146,    86,
      87,    88,   101,   102,   103,   104,   105,   106,   107,   108,
     811,   365,   812,   393,    89,    89,   366,    89,   394,   637,
     644,    89,   645,    52,    32,    33,    34,    35,   916,    89,
     813,   917,   918,   919,    54,   815,   816,   109,   110,   111,
     112,   113,   820,   888,    56,   889,   890,   409,   740,    89,
     336,   741,   410,   114,    89,   709,   115,   580,   581,   582,
     583,    58,   711,   116,    89,   340,    89,   712,    89,   814,
     713,   117,   118,   743,    89,   119,   744,   824,   227,   247,
     228,   229,   248,   249,    60,   725,   646,   725,   745,   584,
     726,   746,   727,   677,   886,    62,    90,   887,   270,   271,
     272,   273,   274,   275,   276,   277,   278,   279,   280,   281,
     282,   283,   657,   658,   659,   660,   661,   662,   448,   756,
     763,    81,    89,   767,   757,   764,   447,   409,   768,   355,
     866,   393,   769,   107,   863,   867,   868,   301,   449,   164,
     358,   365,   185,   165,    89,   877,   878,   902,   931,   196,
     302,   178,   903,   932,   186,   166,   167,   168,   303,   213,
     304,   197,   305,   190,   411,   412,   251,   252,   311,   233,
     198,   214,   317,   318,   250,   853,   854,   855,   856,   253,
     914,   685,   686,   915,   548,   549,   550,   869,   870,   871,
      89,   319,   320,   284,   558,   559,   560,   321,   814,     1,
       2,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,   333,   339,   349,   350,   361,   363,   364,   375,
     413,   444,   379,   374,   383,   376,   385,   384,   387,   388,
     389,   390,   423,   395,   398,   400,   401,   404,   405,   406,
     414,   415,   416,   417,   418,   420,   421,   422,   428,   424,
     425,   426,   427,   429,   430,   431,   432,   433,   434,   435,
     436,   437,   438,   439,   440,   441,   443,   455,   456,   457,
     458,   459,   460,   462,   461,   463,   464,   465,   517,   518,
     519,   466,   468,   470,   471,   472,   473,   474,   476,   477,
     478,   479,   480,   481,   482,   484,   485,   613,   613,   487,
     486,   488,   489,   490,   492,   605,   605,   493,   496,   494,
     497,   499,   500,   501,   502,   503,   448,   676,   504,   284,
     506,   507,   505,   511,   447,   508,   509,   510,   512,   514,
     515,   545,   540,   516,   520,   521,   449,   522,   523,   524,
     525,   526,   527,   528,   529,   530,   531,   546,   547,   532,
     533,   534,   535,   536,   539,   541,   542,   552,   555,   572,
      30,   553,   554,   543,   621,   625,   629,   633,   653,   693,
     695,   699,   556,   703,   718,   719,   587,   557,   561,   720,
     707,   721,   722,   730,   784,   729,   733,   732,   735,   736,
     738,   739,   588,   742,   749,   748,   562,   563,   564,   565,
     750,   751,   752,   753,   754,   755,   760,   761,   762,   776,
     566,   775,   779,   778,   579,   782,   781,   785,   787,   788,
     567,   568,   789,   589,   790,   569,   570,   571,   796,   797,
     834,   573,   835,   574,   575,   840,   841,   844,   864,   843,
     851,   419,   852,   865,   908,   586,   879,   881,   900,   904,
     906,   442,   770,   773,   910,   791,   928,   929,   930,   792,
     933,   794,   793,   445,   795,   827,   828,   829,   643,   593,
     830,   798,   831,   832,   836,   620,   822,   823,   826,   825,
     498,   833,   800,   837,   838,   799,   821,   884,   467,   225,
     801,   802,   491,   495,   845,   803,   804,   846,   858,   469,
     859,   613,   848,   860,   847,   861,   850,   475,   849,   605,
     251,   252,   164,   810,   905,   233,   165,   694,   250,   862,
     873,   805,   842,   253,   178,   806,   934,   839,   166,   167,
     168,   265,   691,   819,   513,   483,   874,   807,   808,   809,
     786,   875,   898,   876,   880,   909,   938,   676,   907,   926,
     937,     0,     0,     0,     0,     0,     0,     0,   185,     0,
     935,   196,     0,   936,   213,     0,     0,     0,     0,     0,
     186,     0,     0,   197,     0,     0,   214,     0,     0,   190,
       0,     0,   198,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   810,     0,     0,     0,     0,     0,     0,     0,
     805,     0,     0,     0,   806,     0,     0,     0,     0,     0,
       0,   892,   819,     0,     0,     0,   807,   808,   809,   891,
       0,     0,     0,     0,     0,     0,     0,     0,   892,     0,
       0,     0,     0,     0,     0,     0,   891
  };

  const short int
  Dhcp6Parser::yycheck_[] =
  {
      66,    75,    75,    69,    70,    71,    72,    69,    74,    75,
      76,    77,   530,   533,    75,    69,    70,    71,    72,    69,
      69,    69,   529,     7,    10,    70,    71,    15,     5,    16,
       7,   737,     9,   737,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    16,     0,    76,    31,    32,    33,
      34,   737,    39,    25,    38,     7,   737,   737,    38,    39,
      83,    84,     3,   737,    48,     7,    50,     8,     7,    16,
      83,    84,    56,    57,    58,    59,    60,    61,    62,    31,
      32,    33,    34,     7,    36,     3,    38,    39,    72,    73,
       8,    71,    39,     7,    41,    42,    80,     3,    45,    46,
      47,    38,     8,     3,    39,    38,    58,    59,     8,    61,
      62,    38,   119,   120,    51,    52,    53,    54,    55,    56,
      72,   151,    49,     7,    96,    97,    98,    99,    80,    56,
      72,     7,    11,     7,     3,    14,    15,    70,   151,     8,
     126,    74,    75,    76,    77,    78,    79,    12,    13,   135,
     136,   137,    31,    32,    33,    34,    35,    36,    37,    38,
     866,     3,   866,     3,   151,   151,     8,   151,     8,    76,
      77,   151,    79,     7,   151,   152,   153,   154,   129,   151,
     866,   132,   133,   134,     7,   866,   866,    66,    67,    68,
      69,    70,   866,   128,     7,   130,   131,     3,     3,   151,
       3,     6,     8,    82,   151,     8,    85,   122,   123,   124,
     125,     7,     3,    92,   151,     3,   151,     8,   151,   737,
       8,   100,   101,     3,   151,   104,     6,   745,    39,    40,
      41,    42,    43,    44,     7,     3,   743,     3,     3,   154,
       8,     6,     8,   763,     3,     7,   312,     6,   105,   106,
     107,   108,   109,   110,   111,   112,   113,   114,   115,   116,
     117,   118,    86,    87,    88,    89,    90,    91,   342,     3,
       3,   151,   151,     3,     8,     8,   342,     3,     8,     3,
       3,     3,     8,    37,     8,     8,     8,     6,   342,   355,
       3,     3,   358,   355,   151,     8,     8,     3,     3,   365,
       3,   355,     8,     8,   358,   355,   355,   355,     4,   375,
       8,   365,     3,   358,   302,   303,   390,   390,     4,   385,
     365,   375,     4,     4,   390,    17,    18,    19,    20,   390,
       3,   102,   103,     6,    63,    64,    65,    93,    94,    95,
     151,     4,     4,   409,   476,   477,   478,     4,   866,   138,
     139,   140,   141,   142,   143,   144,   145,   146,   147,   148,
     149,   150,     4,     4,     4,     4,     4,     4,     4,     3,
     151,   154,     4,     8,     4,     8,     3,     8,     4,     4,
       8,     3,   152,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,   152,
     152,   152,   152,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,   152,     4,     4,     4,     4,     4,     4,
       4,     4,     4,   154,   152,     4,     4,     4,   416,   417,
     418,     4,     4,     4,   152,     4,   152,   152,     4,     4,
       4,     4,     4,     4,     4,     4,     4,   521,   522,     4,
     152,     4,     4,   154,     4,   521,   522,   154,     4,   154,
       4,   154,     4,     4,   152,     4,   540,   533,   152,   535,
       4,     4,   152,     4,   540,   154,   154,   154,     4,     4,
       7,   151,     3,     7,     7,     7,   540,     7,     5,     5,
       5,     5,     5,     5,     5,     5,     5,   151,   151,     7,
       7,     7,     7,     5,     8,     5,     5,   151,   151,   497,
       7,     5,     7,   457,     7,     7,     7,     7,     7,     4,
       7,     7,   151,     7,     4,     4,   514,   151,   151,     4,
      81,     4,     4,     3,     8,     6,     3,     6,     6,     3,
       6,     3,   515,     6,     3,     6,   151,   151,   151,   151,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     3,
     151,     6,     3,     6,   121,     3,     6,     4,     4,     4,
     151,   151,     4,   127,     4,   151,   151,   151,     4,     4,
       4,   151,     4,   151,   151,     4,     4,     3,     8,     6,
       4,   312,     5,     8,     5,   151,     8,     7,     4,     4,
       4,   336,   151,   151,     7,   152,     4,     4,     4,   154,
       4,   154,   152,   340,   152,   152,   152,   152,   528,   520,
     152,   725,   152,   152,   152,   522,   740,   743,   749,   747,
     393,   756,   730,   152,   152,   728,   739,   866,   355,    73,
     731,   733,   385,   390,   774,   734,   736,   776,   151,   358,
     151,   725,   779,   151,   777,   151,   782,   365,   780,   725,
     734,   734,   728,   737,   152,   731,   728,   540,   734,   151,
     151,   737,   767,   734,   728,   737,   154,   763,   728,   728,
     728,   747,   535,   737,   409,   375,   151,   737,   737,   737,
     711,   151,   886,   151,   151,   151,   151,   763,   902,   914,
     931,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   774,    -1,
     152,   777,    -1,   152,   780,    -1,    -1,    -1,    -1,    -1,
     774,    -1,    -1,   777,    -1,    -1,   780,    -1,    -1,   774,
      -1,    -1,   777,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   866,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     866,    -1,    -1,    -1,   866,    -1,    -1,    -1,    -1,    -1,
      -1,   885,   866,    -1,    -1,    -1,   866,   866,   866,   885,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   902,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   902
  };

  const unsigned short int
  Dhcp6Parser::yystos_[] =
  {
       0,   138,   139,   140,   141,   142,   143,   144,   145,   146,
     147,   148,   149,   150,   156,   157,   158,   159,   160,   161,
     162,   163,   164,   165,   166,   167,   168,   169,     0,     5,
       7,     9,   151,   152,   153,   154,   170,   171,   172,   177,
       7,   186,     7,   192,     7,   203,     7,   280,     7,   355,
       7,   369,     7,   386,     7,   307,     7,   313,     7,   337,
       7,   256,     7,   442,   178,   173,   187,   193,   204,   281,
     356,   370,   387,   308,   314,   338,   257,   443,   170,   179,
     180,   151,   175,   176,    10,   126,   135,   136,   137,   151,
     185,   188,   189,   190,   469,   471,   473,   475,    11,    14,
      15,    31,    32,    33,    34,    35,    36,    37,    38,    66,
      67,    68,    69,    70,    82,    85,    92,   100,   101,   104,
     185,   194,   195,   196,   197,   198,   199,   200,   201,   210,
     212,   236,   242,   248,   250,   264,   274,   297,   305,   331,
     409,   419,   431,   432,   440,    12,    13,   205,   206,   207,
     209,     7,    48,    50,    56,    57,    58,    59,    60,    61,
      62,    72,    73,    80,   185,   196,   197,   198,   199,   282,
     283,   284,   286,   288,   290,   292,   295,   296,   331,   349,
     361,   363,   380,   405,    49,   185,   331,   357,   358,   359,
     361,    51,    52,    53,    54,    55,   185,   331,   361,   371,
     372,   373,   375,   376,   378,   379,    70,    74,    75,    76,
      77,    78,    79,   185,   331,   388,   389,   390,   391,   393,
     395,   397,   399,   401,   403,   305,    16,    39,    41,    42,
      45,    46,    47,   185,   226,   315,   316,   317,   318,   319,
     320,   321,   323,   325,   327,   328,   330,    40,    43,    44,
     185,   226,   319,   325,   339,   340,   341,   342,   343,   345,
     346,   347,   348,    83,    84,   185,   258,   259,   260,   262,
     105,   106,   107,   108,   109,   110,   111,   112,   113,   114,
     115,   116,   117,   118,   185,   444,   445,   446,   447,   449,
     451,   452,   454,   455,   456,   459,   461,   462,   463,   464,
     467,     6,     3,     4,     8,     3,   191,   476,   470,   472,
     474,     4,     3,     8,   202,   211,   213,     4,     4,     4,
       4,     4,   275,   306,   332,   298,   237,   249,   243,   410,
     251,   265,   420,     4,   433,   441,     3,     8,   208,     4,
       3,     8,   412,   350,   364,   362,   285,   287,   289,     4,
       4,   293,   291,   381,   406,     3,     8,   360,     3,     8,
     374,     4,   377,     4,     4,     3,     8,   404,   392,   394,
     396,   398,   400,   402,     8,     3,     8,   322,   227,     4,
     326,   324,   329,     4,     8,     3,   344,     4,     4,     8,
       3,   261,   263,     3,     8,     4,   448,   450,     4,   453,
       4,     4,   457,   460,     4,     4,     4,   465,   468,     3,
       8,   170,   170,   151,     4,     4,     4,     4,     4,   189,
       4,     4,     4,   152,   152,   152,   152,   152,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,   152,
       4,     4,   195,     4,   154,   206,    71,   185,   226,   331,
     413,   414,   415,   416,   417,     4,     4,     4,     4,     4,
       4,   152,   154,     4,     4,     4,     4,   283,     4,   358,
       4,   152,     4,   152,   152,   372,     4,     4,     4,     4,
       4,     4,     4,   390,     4,     4,   152,     4,     4,     4,
     154,   317,     4,   154,   154,   341,     4,     4,   259,   154,
       4,     4,   152,     4,   152,   152,     4,     4,   154,   154,
     154,     4,     4,   445,     4,     7,     7,   170,   170,   170,
       7,     7,     7,     5,     5,     5,     5,     5,     5,     5,
       5,     5,     7,     7,     7,     7,     5,   181,   418,     8,
       3,     5,     5,   172,   174,   151,   151,   151,    63,    64,
      65,   294,   151,     5,     7,   151,   151,   151,   181,   181,
     181,   151,   151,   151,   151,   151,   151,   151,   151,   151,
     151,   151,   170,   151,   151,   151,   119,   120,   458,   121,
     122,   123,   124,   125,   154,   466,   151,   170,   194,   127,
     477,   478,   479,   205,    16,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,   185,   214,   215,   216,   219,
     221,   223,   225,   226,   228,   229,   230,   231,   232,   234,
     214,     7,   276,   277,   278,     7,   309,   310,   311,     7,
     333,   334,   335,     7,   299,   300,   301,    76,   151,   238,
     239,   240,   241,   179,    77,    79,   240,   244,   245,   246,
     247,   290,   411,     7,   252,   253,   254,    86,    87,    88,
      89,    90,    91,   266,   267,   268,   269,   270,   271,   272,
     273,    16,    96,    97,    98,    99,   185,   228,   421,   422,
     423,   426,   427,   429,   430,   102,   103,   434,   435,   436,
     438,   444,   182,     4,   415,     7,   351,   352,   353,     7,
     365,   366,   367,     7,   382,   383,   384,    81,   407,     8,
     480,     3,     8,     8,   217,   220,   222,   224,     4,     4,
       4,     4,     4,   233,   235,     3,     8,     8,   279,     6,
       3,   312,     6,     3,   336,     6,     3,   302,     6,     3,
       3,     6,     6,     3,     6,     3,     6,   255,     6,     3,
       4,     4,     4,     4,     4,     4,     3,     8,   424,   428,
       4,     4,     4,     3,     8,   437,   439,     3,     8,     8,
     151,   183,   184,   151,   354,     6,     3,   368,     6,     3,
     385,     6,     3,   408,     8,     4,   478,     4,     4,     4,
       4,   152,   154,   152,   154,   152,     4,     4,   215,   282,
     278,   315,   311,   339,   335,   185,   196,   197,   198,   199,
     226,   274,   286,   288,   290,   292,   296,   303,   304,   331,
     405,   301,   239,   245,   290,   258,   254,   152,   152,   152,
     152,   152,   152,   267,     4,     4,   152,   152,   152,   422,
       4,     4,   435,     6,     3,   357,   353,   371,   367,   388,
     384,     4,     5,    17,    18,    19,    20,   218,   151,   151,
     151,   151,   151,     8,     8,     8,     3,     8,     8,    93,
      94,    95,   425,   151,   151,   151,   151,     8,     8,     8,
     151,     7,   481,   482,   304,   483,     3,     6,   128,   130,
     131,   185,   226,   484,   485,   486,   487,   489,   482,   490,
       4,   488,     3,     8,     4,   152,     4,   485,     5,   151,
       7,   491,   492,   493,     3,     6,   129,   132,   133,   134,
     494,   495,   496,   498,   499,   500,   492,   497,     4,     4,
       4,     3,     8,     4,   154,   152,   152,   495,   151
  };

  const unsigned short int
  Dhcp6Parser::yyr1_[] =
  {
       0,   155,   157,   156,   158,   156,   159,   156,   160,   156,
     161,   156,   162,   156,   163,   156,   164,   156,   165,   156,
     166,   156,   167,   156,   168,   156,   169,   156,   170,   170,
     170,   170,   170,   170,   170,   171,   173,   172,   174,   175,
     175,   176,   176,   178,   177,   179,   179,   180,   180,   182,
     181,   183,   183,   184,   184,   185,   187,   186,   188,   188,
     189,   189,   189,   189,   189,   189,   191,   190,   193,   192,
     194,   194,   195,   195,   195,   195,   195,   195,   195,   195,
     195,   195,   195,   195,   195,   195,   195,   195,   195,   195,
     195,   195,   195,   195,   195,   196,   197,   198,   199,   200,
     202,   201,   204,   203,   205,   205,   206,   206,   208,   207,
     209,   211,   210,   213,   212,   214,   214,   215,   215,   215,
     215,   215,   215,   215,   215,   215,   215,   215,   215,   215,
     217,   216,   218,   218,   218,   218,   220,   219,   222,   221,
     224,   223,   225,   227,   226,   228,   229,   230,   231,   233,
     232,   235,   234,   237,   236,   238,   238,   239,   239,   240,
     241,   243,   242,   244,   244,   245,   245,   245,   246,   247,
     249,   248,   251,   250,   252,   252,   253,   253,   255,   254,
     257,   256,   258,   258,   258,   259,   259,   261,   260,   263,
     262,   265,   264,   266,   266,   267,   267,   267,   267,   267,
     267,   268,   269,   270,   271,   272,   273,   275,   274,   276,
     276,   277,   277,   279,   278,   281,   280,   282,   282,   283,
     283,   283,   283,   283,   283,   283,   283,   283,   283,   283,
     283,   283,   283,   283,   283,   283,   283,   285,   284,   287,
     286,   289,   288,   291,   290,   293,   292,   294,   294,   294,
     295,   296,   298,   297,   299,   299,   300,   300,   302,   301,
     303,   303,   304,   304,   304,   304,   304,   304,   304,   304,
     304,   304,   304,   304,   304,   304,   306,   305,   308,   307,
     309,   309,   310,   310,   312,   311,   314,   313,   315,   315,
     316,   316,   317,   317,   317,   317,   317,   317,   317,   317,
     318,   319,   320,   322,   321,   324,   323,   326,   325,   327,
     329,   328,   330,   332,   331,   333,   333,   334,   334,   336,
     335,   338,   337,   339,   339,   340,   340,   341,   341,   341,
     341,   341,   341,   341,   342,   344,   343,   345,   346,   347,
     348,   350,   349,   351,   351,   352,   352,   354,   353,   356,
     355,   357,   357,   358,   358,   358,   358,   360,   359,   362,
     361,   364,   363,   365,   365,   366,   366,   368,   367,   370,
     369,   371,   371,   372,   372,   372,   372,   372,   372,   372,
     372,   374,   373,   375,   377,   376,   378,   379,   381,   380,
     382,   382,   383,   383,   385,   384,   387,   386,   388,   388,
     389,   389,   390,   390,   390,   390,   390,   390,   390,   390,
     390,   392,   391,   394,   393,   396,   395,   398,   397,   400,
     399,   402,   401,   404,   403,   406,   405,   408,   407,   410,
     409,   411,   411,   412,   290,   413,   413,   414,   414,   415,
     415,   415,   415,   416,   418,   417,   420,   419,   421,   421,
     422,   422,   422,   422,   422,   422,   422,   424,   423,   425,
     425,   425,   426,   428,   427,   429,   430,   431,   433,   432,
     434,   434,   435,   435,   437,   436,   439,   438,   441,   440,
     443,   442,   444,   444,   445,   445,   445,   445,   445,   445,
     445,   445,   445,   445,   445,   445,   445,   445,   445,   446,
     448,   447,   450,   449,   451,   453,   452,   454,   455,   457,
     456,   458,   458,   460,   459,   461,   462,   463,   465,   464,
     466,   466,   466,   466,   466,   468,   467,   470,   469,   472,
     471,   474,   473,   476,   475,   477,   477,   478,   480,   479,
     481,   481,   483,   482,   484,   484,   485,   485,   485,   485,
     485,   486,   488,   487,   490,   489,   491,   491,   493,   492,
     494,   494,   495,   495,   495,   495,   497,   496,   498,   499,
     500
  };

  const unsigned char
  Dhcp6Parser::yyr2_[] =
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
       1,     1,     1,     1,     1,     3,     3,     3,     3,     3,
       0,     6,     0,     4,     1,     3,     1,     1,     0,     4,
       3,     0,     6,     0,     6,     1,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       0,     4,     1,     1,     1,     1,     0,     4,     0,     4,
       0,     4,     3,     0,     4,     3,     3,     3,     3,     0,
       4,     0,     4,     0,     6,     1,     3,     1,     1,     1,
       1,     0,     6,     1,     3,     1,     1,     1,     1,     1,
       0,     6,     0,     6,     0,     1,     1,     3,     0,     4,
       0,     4,     1,     3,     1,     1,     1,     0,     4,     0,
       4,     0,     6,     1,     3,     1,     1,     1,     1,     1,
       1,     3,     3,     3,     3,     3,     3,     0,     6,     0,
       1,     1,     3,     0,     4,     0,     4,     1,     3,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     4,     1,     1,     1,
       3,     3,     0,     6,     0,     1,     1,     3,     0,     4,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     0,     6,     0,     4,
       0,     1,     1,     3,     0,     4,     0,     4,     0,     1,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     3,     1,     0,     4,     0,     4,     0,     4,     1,
       0,     4,     3,     0,     6,     0,     1,     1,     3,     0,
       4,     0,     4,     0,     1,     1,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     0,     4,     1,     1,     3,
       3,     0,     6,     0,     1,     1,     3,     0,     4,     0,
       4,     1,     3,     1,     1,     1,     1,     0,     4,     0,
       4,     0,     6,     0,     1,     1,     3,     0,     4,     0,
       4,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     0,     4,     3,     0,     4,     3,     3,     0,     6,
       0,     1,     1,     3,     0,     4,     0,     4,     0,     1,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     6,     0,     4,     0,
       6,     1,     3,     0,     4,     0,     1,     1,     3,     1,
       1,     1,     1,     1,     0,     4,     0,     6,     1,     3,
       1,     1,     1,     1,     1,     1,     1,     0,     4,     1,
       1,     1,     3,     0,     4,     3,     3,     3,     0,     6,
       1,     3,     1,     1,     0,     4,     0,     4,     0,     6,
       0,     4,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     3,
       0,     4,     0,     4,     3,     0,     4,     3,     3,     0,
       4,     1,     1,     0,     4,     3,     3,     3,     0,     4,
       1,     1,     1,     1,     1,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     6,     1,     3,     1,     0,     6,
       1,     3,     0,     4,     1,     3,     1,     1,     1,     1,
       1,     3,     0,     4,     0,     6,     1,     3,     0,     4,
       1,     3,     1,     1,     1,     1,     0,     4,     3,     3,
       3
  };



  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a yyntokens_, nonterminals.
  const char*
  const Dhcp6Parser::yytname_[] =
  {
  "\"end of file\"", "error", "$undefined", "\",\"", "\":\"", "\"[\"",
  "\"]\"", "\"{\"", "\"}\"", "\"null\"", "\"Dhcp6\"",
  "\"interfaces-config\"", "\"interfaces\"", "\"re-detect\"",
  "\"lease-database\"", "\"hosts-database\"", "\"type\"", "\"memfile\"",
  "\"mysql\"", "\"postgresql\"", "\"cql\"", "\"user\"", "\"password\"",
  "\"host\"", "\"port\"", "\"persist\"", "\"lfc-interval\"",
  "\"readonly\"", "\"connect-timeout\"", "\"contact-points\"",
  "\"keyspace\"", "\"preferred-lifetime\"", "\"valid-lifetime\"",
  "\"renew-timer\"", "\"rebind-timer\"", "\"decline-probation-period\"",
  "\"subnet6\"", "\"option-def\"", "\"option-data\"", "\"name\"",
  "\"data\"", "\"code\"", "\"space\"", "\"csv-format\"", "\"always-send\"",
  "\"record-types\"", "\"encapsulate\"", "\"array\"", "\"pools\"",
  "\"pool\"", "\"pd-pools\"", "\"prefix\"", "\"prefix-len\"",
  "\"excluded-prefix\"", "\"excluded-prefix-len\"", "\"delegated-len\"",
  "\"user-context\"", "\"subnet\"", "\"interface\"", "\"interface-id\"",
  "\"id\"", "\"rapid-commit\"", "\"reservation-mode\"", "\"disabled\"",
  "\"out-of-pool\"", "\"all\"", "\"shared-networks\"", "\"mac-sources\"",
  "\"relay-supplied-options\"", "\"host-reservation-identifiers\"",
  "\"client-classes\"", "\"test\"", "\"client-class\"", "\"reservations\"",
  "\"ip-addresses\"", "\"prefixes\"", "\"duid\"", "\"hw-address\"",
  "\"hostname\"", "\"flex-id\"", "\"relay\"", "\"ip-address\"",
  "\"hooks-libraries\"", "\"library\"", "\"parameters\"",
  "\"expired-leases-processing\"", "\"reclaim-timer-wait-time\"",
  "\"flush-reclaimed-timer-wait-time\"", "\"hold-reclaimed-time\"",
  "\"max-reclaim-leases\"", "\"max-reclaim-time\"",
  "\"unwarned-reclaim-cycles\"", "\"server-id\"", "\"LLT\"", "\"EN\"",
  "\"LL\"", "\"identifier\"", "\"htype\"", "\"time\"", "\"enterprise-id\"",
  "\"dhcp4o6-port\"", "\"control-socket\"", "\"socket-type\"",
  "\"socket-name\"", "\"dhcp-ddns\"", "\"enable-updates\"",
  "\"qualifying-suffix\"", "\"server-ip\"", "\"server-port\"",
  "\"sender-ip\"", "\"sender-port\"", "\"max-queue-size\"",
  "\"ncr-protocol\"", "\"ncr-format\"", "\"always-include-fqdn\"",
  "\"override-no-update\"", "\"override-client-update\"",
  "\"replace-client-name\"", "\"generated-prefix\"", "\"UDP\"", "\"TCP\"",
  "\"JSON\"", "\"when-present\"", "\"never\"", "\"always\"",
  "\"when-not-present\"", "\"Logging\"", "\"loggers\"",
  "\"output_options\"", "\"output\"", "\"debuglevel\"", "\"severity\"",
  "\"flush\"", "\"maxsize\"", "\"maxver\"", "\"Dhcp4\"", "\"DhcpDdns\"",
  "\"Control-agent\"", "TOPLEVEL_JSON", "TOPLEVEL_DHCP6", "SUB_DHCP6",
  "SUB_INTERFACES6", "SUB_SUBNET6", "SUB_POOL6", "SUB_PD_POOL",
  "SUB_RESERVATION", "SUB_OPTION_DEFS", "SUB_OPTION_DEF",
  "SUB_OPTION_DATA", "SUB_HOOKS_LIBRARY", "SUB_DHCP_DDNS",
  "\"constant string\"", "\"integer\"", "\"floating point\"",
  "\"boolean\"", "$accept", "start", "$@1", "$@2", "$@3", "$@4", "$@5",
  "$@6", "$@7", "$@8", "$@9", "$@10", "$@11", "$@12", "$@13", "value",
  "sub_json", "map2", "$@14", "map_value", "map_content", "not_empty_map",
  "list_generic", "$@15", "list_content", "not_empty_list", "list_strings",
  "$@16", "list_strings_content", "not_empty_list_strings",
  "unknown_map_entry", "syntax_map", "$@17", "global_objects",
  "global_object", "dhcp6_object", "$@18", "sub_dhcp6", "$@19",
  "global_params", "global_param", "preferred_lifetime", "valid_lifetime",
  "renew_timer", "rebind_timer", "decline_probation_period",
  "interfaces_config", "$@20", "sub_interfaces6", "$@21",
  "interfaces_config_params", "interfaces_config_param", "interfaces_list",
  "$@22", "re_detect", "lease_database", "$@23", "hosts_database", "$@24",
  "database_map_params", "database_map_param", "database_type", "$@25",
  "db_type", "user", "$@26", "password", "$@27", "host", "$@28", "port",
  "name", "$@29", "persist", "lfc_interval", "readonly", "connect_timeout",
  "contact_points", "$@30", "keyspace", "$@31", "mac_sources", "$@32",
  "mac_sources_list", "mac_sources_value", "duid_id", "string_id",
  "host_reservation_identifiers", "$@33",
  "host_reservation_identifiers_list", "host_reservation_identifier",
  "hw_address_id", "flex_id", "relay_supplied_options", "$@34",
  "hooks_libraries", "$@35", "hooks_libraries_list",
  "not_empty_hooks_libraries_list", "hooks_library", "$@36",
  "sub_hooks_library", "$@37", "hooks_params", "hooks_param", "library",
  "$@38", "parameters", "$@39", "expired_leases_processing", "$@40",
  "expired_leases_params", "expired_leases_param",
  "reclaim_timer_wait_time", "flush_reclaimed_timer_wait_time",
  "hold_reclaimed_time", "max_reclaim_leases", "max_reclaim_time",
  "unwarned_reclaim_cycles", "subnet6_list", "$@41",
  "subnet6_list_content", "not_empty_subnet6_list", "subnet6", "$@42",
  "sub_subnet6", "$@43", "subnet6_params", "subnet6_param", "subnet",
  "$@44", "interface", "$@45", "interface_id", "$@46", "client_class",
  "$@47", "reservation_mode", "$@48", "hr_mode", "id", "rapid_commit",
  "shared_networks", "$@49", "shared_networks_content",
  "shared_networks_list", "shared_network", "$@50",
  "shared_network_params", "shared_network_param", "option_def_list",
  "$@51", "sub_option_def_list", "$@52", "option_def_list_content",
  "not_empty_option_def_list", "option_def_entry", "$@53",
  "sub_option_def", "$@54", "option_def_params",
  "not_empty_option_def_params", "option_def_param", "option_def_name",
  "code", "option_def_code", "option_def_type", "$@55",
  "option_def_record_types", "$@56", "space", "$@57", "option_def_space",
  "option_def_encapsulate", "$@58", "option_def_array", "option_data_list",
  "$@59", "option_data_list_content", "not_empty_option_data_list",
  "option_data_entry", "$@60", "sub_option_data", "$@61",
  "option_data_params", "not_empty_option_data_params",
  "option_data_param", "option_data_name", "option_data_data", "$@62",
  "option_data_code", "option_data_space", "option_data_csv_format",
  "option_data_always_send", "pools_list", "$@63", "pools_list_content",
  "not_empty_pools_list", "pool_list_entry", "$@64", "sub_pool6", "$@65",
  "pool_params", "pool_param", "pool_entry", "$@66", "user_context",
  "$@67", "pd_pools_list", "$@68", "pd_pools_list_content",
  "not_empty_pd_pools_list", "pd_pool_entry", "$@69", "sub_pd_pool",
  "$@70", "pd_pool_params", "pd_pool_param", "pd_prefix", "$@71",
  "pd_prefix_len", "excluded_prefix", "$@72", "excluded_prefix_len",
  "pd_delegated_len", "reservations", "$@73", "reservations_list",
  "not_empty_reservations_list", "reservation", "$@74", "sub_reservation",
  "$@75", "reservation_params", "not_empty_reservation_params",
  "reservation_param", "ip_addresses", "$@76", "prefixes", "$@77", "duid",
  "$@78", "hw_address", "$@79", "hostname", "$@80", "flex_id_value",
  "$@81", "reservation_client_classes", "$@82", "relay", "$@83",
  "relay_map", "$@84", "client_classes", "$@85", "client_classes_list",
  "$@86", "client_class_params", "not_empty_client_class_params",
  "client_class_param", "client_class_name", "client_class_test", "$@87",
  "server_id", "$@88", "server_id_params", "server_id_param",
  "server_id_type", "$@89", "duid_type", "htype", "identifier", "$@90",
  "time", "enterprise_id", "dhcp4o6_port", "control_socket", "$@91",
  "control_socket_params", "control_socket_param", "socket_type", "$@92",
  "socket_name", "$@93", "dhcp_ddns", "$@94", "sub_dhcp_ddns", "$@95",
  "dhcp_ddns_params", "dhcp_ddns_param", "enable_updates",
  "qualifying_suffix", "$@96", "server_ip", "$@97", "server_port",
  "sender_ip", "$@98", "sender_port", "max_queue_size", "ncr_protocol",
  "$@99", "ncr_protocol_value", "ncr_format", "$@100",
  "always_include_fqdn", "override_no_update", "override_client_update",
  "replace_client_name", "$@101", "replace_client_name_value",
  "generated_prefix", "$@102", "dhcp4_json_object", "$@103",
  "dhcpddns_json_object", "$@104", "control_agent_json_object", "$@105",
  "logging_object", "$@106", "logging_params", "logging_param", "loggers",
  "$@107", "loggers_entries", "logger_entry", "$@108", "logger_params",
  "logger_param", "debuglevel", "severity", "$@109", "output_options_list",
  "$@110", "output_options_list_content", "output_entry", "$@111",
  "output_params_list", "output_params", "output", "$@112", "flush",
  "maxsize", "maxver", YY_NULLPTR
  };

#if PARSER6_DEBUG
  const unsigned short int
  Dhcp6Parser::yyrline_[] =
  {
       0,   236,   236,   236,   237,   237,   238,   238,   239,   239,
     240,   240,   241,   241,   242,   242,   243,   243,   244,   244,
     245,   245,   246,   246,   247,   247,   248,   248,   256,   257,
     258,   259,   260,   261,   262,   265,   270,   270,   281,   284,
     285,   288,   292,   299,   299,   306,   307,   310,   314,   321,
     321,   328,   329,   332,   336,   347,   357,   357,   372,   373,
     377,   378,   379,   380,   381,   382,   385,   385,   400,   400,
     409,   410,   415,   416,   417,   418,   419,   420,   421,   422,
     423,   424,   425,   426,   427,   428,   429,   430,   431,   432,
     433,   434,   435,   436,   437,   440,   445,   450,   455,   460,
     465,   465,   476,   476,   485,   486,   489,   490,   493,   493,
     503,   509,   509,   521,   521,   533,   534,   537,   538,   539,
     540,   541,   542,   543,   544,   545,   546,   547,   548,   549,
     552,   552,   559,   560,   561,   562,   565,   565,   573,   573,
     581,   581,   589,   594,   594,   602,   607,   612,   617,   622,
     622,   630,   630,   639,   639,   649,   650,   653,   654,   657,
     662,   667,   667,   677,   678,   681,   682,   683,   686,   691,
     698,   698,   708,   708,   718,   719,   722,   723,   726,   726,
     736,   736,   746,   747,   748,   751,   752,   755,   755,   763,
     763,   771,   771,   782,   783,   786,   787,   788,   789,   790,
     791,   794,   799,   804,   809,   814,   819,   827,   827,   840,
     841,   844,   845,   852,   852,   878,   878,   889,   890,   894,
     895,   896,   897,   898,   899,   900,   901,   902,   903,   904,
     905,   906,   907,   908,   909,   910,   911,   914,   914,   922,
     922,   930,   930,   938,   938,   946,   946,   953,   954,   955,
     958,   963,   971,   971,   982,   983,   987,   988,   991,   991,
     999,  1000,  1003,  1004,  1005,  1006,  1007,  1008,  1009,  1010,
    1011,  1012,  1013,  1014,  1015,  1016,  1023,  1023,  1036,  1036,
    1045,  1046,  1049,  1050,  1055,  1055,  1070,  1070,  1084,  1085,
    1088,  1089,  1092,  1093,  1094,  1095,  1096,  1097,  1098,  1099,
    1102,  1104,  1109,  1111,  1111,  1119,  1119,  1127,  1127,  1135,
    1137,  1137,  1145,  1154,  1154,  1166,  1167,  1172,  1173,  1178,
    1178,  1190,  1190,  1202,  1203,  1208,  1209,  1214,  1215,  1216,
    1217,  1218,  1219,  1220,  1223,  1225,  1225,  1233,  1235,  1237,
    1242,  1250,  1250,  1262,  1263,  1266,  1267,  1270,  1270,  1280,
    1280,  1289,  1290,  1293,  1294,  1295,  1296,  1299,  1299,  1307,
    1307,  1317,  1317,  1329,  1330,  1333,  1334,  1337,  1337,  1349,
    1349,  1361,  1362,  1365,  1366,  1367,  1368,  1369,  1370,  1371,
    1372,  1375,  1375,  1383,  1388,  1388,  1396,  1401,  1409,  1409,
    1419,  1420,  1423,  1424,  1427,  1427,  1436,  1436,  1445,  1446,
    1449,  1450,  1454,  1455,  1456,  1457,  1458,  1459,  1460,  1461,
    1462,  1465,  1465,  1475,  1475,  1485,  1485,  1493,  1493,  1501,
    1501,  1509,  1509,  1517,  1517,  1530,  1530,  1540,  1540,  1551,
    1551,  1561,  1562,  1565,  1565,  1575,  1576,  1579,  1580,  1583,
    1584,  1585,  1586,  1589,  1591,  1591,  1602,  1602,  1614,  1615,
    1618,  1619,  1620,  1621,  1622,  1623,  1624,  1627,  1627,  1634,
    1635,  1636,  1639,  1644,  1644,  1652,  1657,  1664,  1671,  1671,
    1681,  1682,  1685,  1686,  1689,  1689,  1697,  1697,  1707,  1707,
    1719,  1719,  1729,  1730,  1733,  1734,  1735,  1736,  1737,  1738,
    1739,  1740,  1741,  1742,  1743,  1744,  1745,  1746,  1747,  1750,
    1755,  1755,  1763,  1763,  1771,  1776,  1776,  1784,  1789,  1794,
    1794,  1802,  1803,  1806,  1806,  1814,  1819,  1824,  1829,  1829,
    1837,  1840,  1843,  1846,  1849,  1855,  1855,  1865,  1865,  1872,
    1872,  1879,  1879,  1892,  1892,  1905,  1906,  1910,  1914,  1914,
    1926,  1927,  1931,  1931,  1939,  1940,  1943,  1944,  1945,  1946,
    1947,  1950,  1955,  1955,  1963,  1963,  1973,  1974,  1977,  1977,
    1985,  1986,  1989,  1990,  1991,  1992,  1995,  1995,  2003,  2008,
    2013
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
    *yycdebug_ << std::endl;
  }

  // Report on the debug stream that the rule \a yyrule is going to be reduced.
  void
  Dhcp6Parser::yy_reduce_print_ (int yyrule)
  {
    unsigned int yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    // Print the symbols being reduced, and their result.
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
               << " (line " << yylno << "):" << std::endl;
    // The symbols being reduced.
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
                       yystack_[(yynrhs) - (yyi + 1)]);
  }
#endif // PARSER6_DEBUG


#line 14 "dhcp6_parser.yy" // lalr1.cc:1167
} } // isc::dhcp
#line 4467 "dhcp6_parser.cc" // lalr1.cc:1167
#line 2018 "dhcp6_parser.yy" // lalr1.cc:1168


void
isc::dhcp::Dhcp6Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
