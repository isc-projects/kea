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
      case 171: // value
      case 175: // map_value
      case 219: // db_type
      case 295: // hr_mode
      case 428: // duid_type
      case 461: // ncr_protocol_value
      case 469: // replace_client_name_value
        value.move< ElementPtr > (that.value);
        break;

      case 155: // "boolean"
        value.move< bool > (that.value);
        break;

      case 154: // "floating point"
        value.move< double > (that.value);
        break;

      case 153: // "integer"
        value.move< int64_t > (that.value);
        break;

      case 152: // "constant string"
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
      case 171: // value
      case 175: // map_value
      case 219: // db_type
      case 295: // hr_mode
      case 428: // duid_type
      case 461: // ncr_protocol_value
      case 469: // replace_client_name_value
        value.copy< ElementPtr > (that.value);
        break;

      case 155: // "boolean"
        value.copy< bool > (that.value);
        break;

      case 154: // "floating point"
        value.copy< double > (that.value);
        break;

      case 153: // "integer"
        value.copy< int64_t > (that.value);
        break;

      case 152: // "constant string"
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
            case 152: // "constant string"

#line 228 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< std::string > (); }
#line 364 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 153: // "integer"

#line 228 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< int64_t > (); }
#line 371 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 154: // "floating point"

#line 228 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< double > (); }
#line 378 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 155: // "boolean"

#line 228 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< bool > (); }
#line 385 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 171: // value

#line 228 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 392 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 175: // map_value

#line 228 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 399 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 219: // db_type

#line 228 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 406 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 295: // hr_mode

#line 228 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 413 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 428: // duid_type

#line 228 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 420 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 461: // ncr_protocol_value

#line 228 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 427 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 469: // replace_client_name_value

#line 228 "dhcp6_parser.yy" // lalr1.cc:636
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
      case 171: // value
      case 175: // map_value
      case 219: // db_type
      case 295: // hr_mode
      case 428: // duid_type
      case 461: // ncr_protocol_value
      case 469: // replace_client_name_value
        yylhs.value.build< ElementPtr > ();
        break;

      case 155: // "boolean"
        yylhs.value.build< bool > ();
        break;

      case 154: // "floating point"
        yylhs.value.build< double > ();
        break;

      case 153: // "integer"
        yylhs.value.build< int64_t > ();
        break;

      case 152: // "constant string"
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
#line 237 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.NO_KEYWORD; }
#line 680 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 4:
#line 238 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.CONFIG; }
#line 686 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 6:
#line 239 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.DHCP6; }
#line 692 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 8:
#line 240 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.INTERFACES_CONFIG; }
#line 698 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 10:
#line 241 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.SUBNET6; }
#line 704 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 12:
#line 242 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.POOLS; }
#line 710 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 14:
#line 243 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.PD_POOLS; }
#line 716 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 16:
#line 244 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.RESERVATIONS; }
#line 722 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 18:
#line 245 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.DHCP6; }
#line 728 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 20:
#line 246 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.OPTION_DEF; }
#line 734 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 22:
#line 247 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.OPTION_DATA; }
#line 740 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 24:
#line 248 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.HOOKS_LIBRARIES; }
#line 746 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 26:
#line 249 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.DHCP_DDNS; }
#line 752 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 28:
#line 257 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 758 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 29:
#line 258 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as< double > (), ctx.loc2pos(yystack_[0].location))); }
#line 764 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 30:
#line 259 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 770 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 31:
#line 260 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 776 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 32:
#line 261 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 782 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 33:
#line 262 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 788 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 34:
#line 263 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 794 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 35:
#line 266 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as< ElementPtr > ());
}
#line 803 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 36:
#line 271 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 814 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 37:
#line 276 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 824 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 38:
#line 282 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 830 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 41:
#line 289 "dhcp6_parser.yy" // lalr1.cc:859
    {
                  // map containing a single entry
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 839 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 42:
#line 293 "dhcp6_parser.yy" // lalr1.cc:859
    {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 849 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 43:
#line 300 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 858 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 44:
#line 303 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // list parsing complete. Put any sanity checking here
}
#line 866 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 47:
#line 311 "dhcp6_parser.yy" // lalr1.cc:859
    {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 875 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 48:
#line 315 "dhcp6_parser.yy" // lalr1.cc:859
    {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 884 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 49:
#line 322 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // List parsing about to start
}
#line 892 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 50:
#line 324 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // list parsing complete. Put any sanity checking here
    //ctx.stack_.pop_back();
}
#line 901 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 53:
#line 333 "dhcp6_parser.yy" // lalr1.cc:859
    {
                          ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 910 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 54:
#line 337 "dhcp6_parser.yy" // lalr1.cc:859
    {
                          ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 919 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 55:
#line 348 "dhcp6_parser.yy" // lalr1.cc:859
    {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as< std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 930 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 56:
#line 358 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 941 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 57:
#line 363 "dhcp6_parser.yy" // lalr1.cc:859
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
#line 386 "dhcp6_parser.yy" // lalr1.cc:859
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
#line 393 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // No global parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 977 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 68:
#line 401 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the Dhcp6 map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 987 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 69:
#line 405 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // No global parameter is required
    // parsing completed
}
#line 996 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 95:
#line 441 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("preferred-lifetime", prf);
}
#line 1005 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 96:
#line 446 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 1014 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 97:
#line 451 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 1023 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 98:
#line 456 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 1032 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 99:
#line 461 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr dpp(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 1041 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 100:
#line 466 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces-config", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.INTERFACES_CONFIG);
}
#line 1052 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 101:
#line 471 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // No interfaces config param is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1062 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 102:
#line 477 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1072 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 103:
#line 481 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // No interfaces config param is required
    // parsing completed
}
#line 1081 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 108:
#line 494 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1092 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 109:
#line 499 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1101 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 110:
#line 504 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("re-detect", b);
}
#line 1110 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 111:
#line 510 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lease-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.LEASE_DATABASE);
}
#line 1121 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 112:
#line 515 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1132 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 113:
#line 522 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1143 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 114:
#line 527 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1154 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 130:
#line 553 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.DATABASE_TYPE);
}
#line 1162 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 131:
#line 555 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("type", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1171 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 132:
#line 560 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("memfile", ctx.loc2pos(yystack_[0].location))); }
#line 1177 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 133:
#line 561 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("mysql", ctx.loc2pos(yystack_[0].location))); }
#line 1183 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 134:
#line 562 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("postgresql", ctx.loc2pos(yystack_[0].location))); }
#line 1189 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 135:
#line 563 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("cql", ctx.loc2pos(yystack_[0].location))); }
#line 1195 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 136:
#line 566 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1203 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 137:
#line 568 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr user(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1213 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 138:
#line 574 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1221 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 139:
#line 576 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr pwd(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 1231 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 140:
#line 582 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1239 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 141:
#line 584 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr h(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 1249 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 142:
#line 590 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr p(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", p);
}
#line 1258 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 143:
#line 595 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1266 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 144:
#line 597 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1276 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 145:
#line 603 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 1285 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 146:
#line 608 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 1294 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 147:
#line 613 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 1303 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 148:
#line 618 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("connect-timeout", n);
}
#line 1312 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 149:
#line 623 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1320 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 150:
#line 625 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr cp(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("contact-points", cp);
    ctx.leave();
}
#line 1330 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 151:
#line 631 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1338 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 152:
#line 633 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr ks(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("keyspace", ks);
    ctx.leave();
}
#line 1348 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 153:
#line 640 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("mac-sources", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.MAC_SOURCES);
}
#line 1359 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 154:
#line 645 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1368 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 159:
#line 658 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1377 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 160:
#line 663 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr duid(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1386 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 161:
#line 668 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 1397 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 162:
#line 673 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1406 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 168:
#line 687 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 1415 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 169:
#line 692 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr flex_id(new StringElement("flex-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(flex_id);
}
#line 1424 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 170:
#line 699 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay-supplied-options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1435 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 171:
#line 704 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1444 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 172:
#line 709 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 1455 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 173:
#line 714 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1464 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 178:
#line 727 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1474 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 179:
#line 731 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1484 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 180:
#line 737 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1494 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 181:
#line 741 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 1504 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 187:
#line 756 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1512 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 188:
#line 758 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr lib(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 1522 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 189:
#line 764 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1530 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 190:
#line 766 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1539 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 191:
#line 772 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.EXPIRED_LEASES_PROCESSING);
}
#line 1550 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 192:
#line 777 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // No expired lease parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1560 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 201:
#line 795 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 1569 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 202:
#line 800 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 1578 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 203:
#line 805 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 1587 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 204:
#line 810 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 1596 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 205:
#line 815 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 1605 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 206:
#line 820 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 1614 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 207:
#line 828 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet6", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET6);
}
#line 1625 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 208:
#line 833 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1634 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 213:
#line 853 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1644 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 214:
#line 857 "dhcp6_parser.yy" // lalr1.cc:859
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
#line 879 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the subnet6 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1680 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 216:
#line 883 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The subnet subnet6 parameter is required
    ctx.require("subnet", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 1690 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 238:
#line 916 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1698 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 239:
#line 918 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr subnet(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 1708 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 240:
#line 924 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1716 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 241:
#line 926 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 1726 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 242:
#line 932 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1734 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 243:
#line 934 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface-id", iface);
    ctx.leave();
}
#line 1744 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 244:
#line 940 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.CLIENT_CLASS);
}
#line 1752 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 245:
#line 942 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr cls(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 1762 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 246:
#line 948 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.RESERVATION_MODE);
}
#line 1770 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 247:
#line 950 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("reservation-mode", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1779 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 248:
#line 955 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("disabled", ctx.loc2pos(yystack_[0].location))); }
#line 1785 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 249:
#line 956 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("out-of-pool", ctx.loc2pos(yystack_[0].location))); }
#line 1791 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 250:
#line 957 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("all", ctx.loc2pos(yystack_[0].location))); }
#line 1797 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 251:
#line 960 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr id(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 1806 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 252:
#line 965 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr rc(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rapid-commit", rc);
}
#line 1815 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 253:
#line 973 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("shared-networks", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SHARED_NETWORK);
}
#line 1826 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 254:
#line 978 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1835 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 259:
#line 993 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1845 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 260:
#line 997 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1853 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 277:
#line 1025 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 1864 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 278:
#line 1030 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1873 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 279:
#line 1038 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1882 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 280:
#line 1041 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1890 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 285:
#line 1057 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1900 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 286:
#line 1061 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1912 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 287:
#line 1072 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1922 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 288:
#line 1076 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 1934 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 302:
#line 1106 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr code(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 1943 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 304:
#line 1113 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1951 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 305:
#line 1115 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 1961 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 306:
#line 1121 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1969 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 307:
#line 1123 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 1979 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 308:
#line 1129 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1987 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 309:
#line 1131 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr space(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 1997 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 311:
#line 1139 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2005 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 312:
#line 1141 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr encap(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 2015 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 313:
#line 1147 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr array(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 2024 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 314:
#line 1156 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 2035 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 315:
#line 1161 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2044 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 320:
#line 1180 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2054 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 321:
#line 1184 "dhcp6_parser.yy" // lalr1.cc:859
    {
    /// @todo: the code or name parameters are required.
    ctx.stack_.pop_back();
}
#line 2063 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 322:
#line 1192 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2073 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 323:
#line 1196 "dhcp6_parser.yy" // lalr1.cc:859
    {
    /// @todo: the code or name parameters are required.
    // parsing completed
}
#line 2082 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 336:
#line 1227 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2090 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 337:
#line 1229 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr data(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 2100 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 340:
#line 1239 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr space(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", space);
}
#line 2109 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 341:
#line 1244 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr persist(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-send", persist);
}
#line 2118 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 342:
#line 1252 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 2129 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 343:
#line 1257 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2138 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 348:
#line 1272 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2148 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 349:
#line 1276 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2158 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 350:
#line 1282 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2168 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 351:
#line 1286 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
}
#line 2177 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 359:
#line 1302 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2185 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 360:
#line 1304 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr pool(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 2195 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 361:
#line 1310 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2203 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 362:
#line 1312 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->combine_set("user-context", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2212 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 363:
#line 1317 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2220 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 364:
#line 1319 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr e(new MapElement(ctx.loc2pos(yystack_[3].location)));
    e->set("comment", yystack_[0].value.as< ElementPtr > ());
    ctx.stack_.back()->combine_set("user-context", e);
    ctx.leave();
}
#line 2231 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 365:
#line 1329 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pd-pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.PD_POOLS);
}
#line 2242 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 366:
#line 1334 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2251 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 371:
#line 1349 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2261 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 372:
#line 1353 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The prefix, prefix len and delegated len parameters are required.
    ctx.require("prefix", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("prefix-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("delegated-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2273 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 373:
#line 1361 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the pd-pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2283 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 374:
#line 1365 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The prefix, prefix len and delegated len parameters are required.
    ctx.require("prefix", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("prefix-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("delegated-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2295 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 386:
#line 1388 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2303 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 387:
#line 1390 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix", prf);
    ctx.leave();
}
#line 2313 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 388:
#line 1396 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix-len", prf);
}
#line 2322 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 389:
#line 1401 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2330 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 390:
#line 1403 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix", prf);
    ctx.leave();
}
#line 2340 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 391:
#line 1409 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix-len", prf);
}
#line 2349 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 392:
#line 1414 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr deleg(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("delegated-len", deleg);
}
#line 2358 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 393:
#line 1422 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 2369 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 394:
#line 1427 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2378 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 399:
#line 1440 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2388 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 400:
#line 1444 "dhcp6_parser.yy" // lalr1.cc:859
    {
    /// @todo: an identifier parameter is required.
    ctx.stack_.pop_back();
}
#line 2397 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 401:
#line 1449 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2407 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 402:
#line 1453 "dhcp6_parser.yy" // lalr1.cc:859
    {
    /// @todo: an identifier parameter is required.
    // parsing completed
}
#line 2416 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 416:
#line 1478 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-addresses", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2427 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 417:
#line 1483 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2436 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 418:
#line 1488 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefixes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2447 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 419:
#line 1493 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2456 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 420:
#line 1498 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2464 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 421:
#line 1500 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr d(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 2474 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 422:
#line 1506 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2482 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 423:
#line 1508 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 2492 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 424:
#line 1514 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2500 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 425:
#line 1516 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr host(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 2510 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 426:
#line 1522 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2518 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 427:
#line 1524 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flex-id", hw);
    ctx.leave();
}
#line 2528 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 428:
#line 1530 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2539 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 429:
#line 1535 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2548 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 430:
#line 1543 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 2559 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 431:
#line 1548 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2568 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 432:
#line 1553 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2576 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 433:
#line 1555 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr ip(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", ip);
    ctx.leave();
}
#line 2586 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 434:
#line 1564 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 2597 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 435:
#line 1569 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2606 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 438:
#line 1578 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2616 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 439:
#line 1582 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The name client class parameter is required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2626 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 449:
#line 1604 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2634 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 450:
#line 1606 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr test(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 2644 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 451:
#line 1615 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-id", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SERVER_ID);
}
#line 2655 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 452:
#line 1620 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The type parameter is required.
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2666 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 462:
#line 1640 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.DUID_TYPE);
}
#line 2674 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 463:
#line 1642 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("type", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2683 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 464:
#line 1647 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("LLT", ctx.loc2pos(yystack_[0].location))); }
#line 2689 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 465:
#line 1648 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("EN", ctx.loc2pos(yystack_[0].location))); }
#line 2695 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 466:
#line 1649 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("LL", ctx.loc2pos(yystack_[0].location))); }
#line 2701 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 467:
#line 1652 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr htype(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("htype", htype);
}
#line 2710 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 468:
#line 1657 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2718 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 469:
#line 1659 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr id(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("identifier", id);
    ctx.leave();
}
#line 2728 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 470:
#line 1665 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("time", time);
}
#line 2737 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 471:
#line 1670 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enterprise-id", time);
}
#line 2746 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 472:
#line 1677 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 2755 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 473:
#line 1684 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 2766 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 474:
#line 1689 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2775 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 479:
#line 1702 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2783 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 480:
#line 1704 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr stype(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 2793 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 481:
#line 1710 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2801 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 482:
#line 1712 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 2811 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 483:
#line 1720 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 2822 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 484:
#line 1725 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2833 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 485:
#line 1732 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2843 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 486:
#line 1736 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2853 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 504:
#line 1763 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 2862 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 505:
#line 1768 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2870 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 506:
#line 1770 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("qualifying-suffix", s);
    ctx.leave();
}
#line 2880 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 507:
#line 1776 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2888 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 508:
#line 1778 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 2898 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 509:
#line 1784 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 2907 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 510:
#line 1789 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2915 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 511:
#line 1791 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 2925 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 512:
#line 1797 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 2934 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 513:
#line 1802 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 2943 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 514:
#line 1807 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 2951 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 515:
#line 1809 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2960 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 516:
#line 1815 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 2966 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 517:
#line 1816 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 2972 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 518:
#line 1819 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NCR_FORMAT);
}
#line 2980 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 519:
#line 1821 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 2990 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 520:
#line 1827 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-include-fqdn", b);
}
#line 2999 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 521:
#line 1832 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-no-update", b);
}
#line 3008 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 522:
#line 1837 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-client-update", b);
}
#line 3017 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 523:
#line 1842 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 3025 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 524:
#line 1844 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("replace-client-name", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3034 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 525:
#line 1850 "dhcp6_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("when-present", ctx.loc2pos(yystack_[0].location))); 
      }
#line 3042 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 526:
#line 1853 "dhcp6_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location)));
      }
#line 3050 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 527:
#line 1856 "dhcp6_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("always", ctx.loc2pos(yystack_[0].location)));
      }
#line 3058 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 528:
#line 1859 "dhcp6_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("when-not-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 3066 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 529:
#line 1862 "dhcp6_parser.yy" // lalr1.cc:859
    {
      error(yystack_[0].location, "boolean values for the replace-client-name are "
                "no longer supported");
      }
#line 3075 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 530:
#line 1868 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3083 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 531:
#line 1870 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("generated-prefix", s);
    ctx.leave();
}
#line 3093 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 532:
#line 1878 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3101 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 533:
#line 1880 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("Dhcp4", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3110 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 534:
#line 1885 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3118 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 535:
#line 1887 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("DhcpDdns", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3127 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 536:
#line 1892 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3135 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 537:
#line 1894 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("Control-agent", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3144 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 538:
#line 1905 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Logging", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.LOGGING);
}
#line 3155 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 539:
#line 1910 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3164 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 543:
#line 1927 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 3175 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 544:
#line 1932 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3184 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 547:
#line 1944 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 3194 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 548:
#line 1948 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 3202 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 556:
#line 1963 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr dl(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 3211 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 557:
#line 1968 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3219 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 558:
#line 1970 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 3229 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 559:
#line 1976 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 3240 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 560:
#line 1981 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3249 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 563:
#line 1990 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3259 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 564:
#line 1994 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 3267 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 571:
#line 2008 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3275 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 572:
#line 2010 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 3285 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 573:
#line 2016 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr flush(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 3294 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 574:
#line 2021 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr maxsize(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 3303 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 575:
#line 2026 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr maxver(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 3312 "dhcp6_parser.cc" // lalr1.cc:859
    break;


#line 3316 "dhcp6_parser.cc" // lalr1.cc:859
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


  const short int Dhcp6Parser::yypact_ninf_ = -705;

  const signed char Dhcp6Parser::yytable_ninf_ = -1;

  const short int
  Dhcp6Parser::yypact_[] =
  {
     234,  -705,  -705,  -705,  -705,  -705,  -705,  -705,  -705,  -705,
    -705,  -705,  -705,  -705,    43,    22,    48,    62,    87,   106,
     117,   166,   175,   198,   205,   227,   229,   231,  -705,  -705,
    -705,  -705,  -705,  -705,  -705,  -705,  -705,  -705,  -705,  -705,
    -705,  -705,  -705,  -705,  -705,  -705,  -705,  -705,  -705,  -705,
    -705,  -705,  -705,  -705,  -705,  -705,  -705,  -705,  -705,  -705,
    -705,  -705,  -705,  -705,    22,   -75,    20,   130,    50,    26,
      74,    -6,    58,    44,    63,   110,   -46,   253,  -705,    95,
     140,   155,   240,   254,  -705,  -705,  -705,  -705,  -705,   263,
    -705,    53,  -705,  -705,  -705,  -705,  -705,  -705,  -705,  -705,
    -705,   273,   291,   309,   313,   318,  -705,  -705,  -705,  -705,
    -705,  -705,  -705,  -705,  -705,  -705,  -705,   319,  -705,  -705,
    -705,    70,  -705,  -705,  -705,  -705,  -705,  -705,  -705,  -705,
    -705,  -705,  -705,  -705,  -705,  -705,  -705,  -705,  -705,  -705,
    -705,  -705,  -705,  -705,  -705,  -705,   328,    72,  -705,  -705,
    -705,  -705,  -705,  -705,  -705,  -705,  -705,  -705,  -705,   329,
     331,  -705,  -705,  -705,  -705,  -705,  -705,  -705,  -705,  -705,
     112,  -705,  -705,  -705,  -705,  -705,  -705,  -705,  -705,  -705,
    -705,  -705,  -705,  -705,  -705,  -705,  -705,  -705,  -705,   152,
    -705,  -705,  -705,  -705,  -705,   338,  -705,   343,   345,  -705,
    -705,  -705,  -705,   200,  -705,  -705,  -705,  -705,  -705,  -705,
    -705,  -705,  -705,  -705,  -705,  -705,  -705,  -705,  -705,   248,
     284,  -705,  -705,  -705,  -705,  -705,  -705,  -705,  -705,   267,
    -705,  -705,   346,  -705,  -705,  -705,   347,  -705,  -705,   344,
     350,  -705,  -705,  -705,  -705,  -705,  -705,  -705,  -705,  -705,
    -705,  -705,   351,   352,  -705,  -705,  -705,  -705,   349,   383,
    -705,  -705,  -705,  -705,  -705,  -705,  -705,  -705,  -705,  -705,
     206,  -705,  -705,  -705,   384,  -705,  -705,   385,  -705,   386,
     387,  -705,  -705,   388,   389,   390,  -705,  -705,  -705,   222,
    -705,  -705,  -705,  -705,  -705,  -705,  -705,  -705,  -705,  -705,
    -705,  -705,  -705,  -705,  -705,  -705,    22,    22,  -705,   202,
     391,   392,   393,   394,   395,  -705,    20,  -705,   396,   397,
     398,   250,   256,   257,   259,   260,   400,   402,   403,   404,
     407,   410,   411,   412,   413,   414,   415,   269,   416,   417,
     130,  -705,   419,   232,    50,  -705,    -4,   420,   421,   422,
     423,   424,   425,   426,   279,   276,   429,   433,   434,   435,
      26,  -705,   436,    74,  -705,   437,   289,   439,   292,   294,
      -6,  -705,   440,   442,   444,   445,   446,   447,   448,  -705,
      58,  -705,   451,   452,   304,   454,   455,   456,   308,  -705,
      63,   460,   310,   311,  -705,   110,   463,   464,    32,  -705,
     314,   466,   467,   321,   473,   326,   330,   474,   477,   327,
     332,   333,   480,   481,   253,  -705,  -705,  -705,   482,   483,
     484,    22,    22,    22,  -705,   486,   487,   488,  -705,  -705,
    -705,  -705,  -705,   491,   492,   493,   494,   495,   496,   497,
     498,   499,   500,   501,  -705,   502,   503,  -705,   506,  -705,
    -705,  -705,  -705,  -705,  -705,   504,   510,  -705,  -705,  -705,
     509,   512,   508,    22,   337,   353,   354,  -705,  -705,   272,
     366,   514,   513,  -705,   369,  -705,   370,  -705,   371,  -705,
    -705,  -705,   506,   506,   506,   372,   373,   374,   375,  -705,
     376,   377,  -705,   378,   379,   380,  -705,  -705,   382,  -705,
    -705,  -705,   399,    22,  -705,  -705,   401,   405,  -705,   406,
    -705,  -705,   187,   418,  -705,  -705,  -705,    94,   408,  -705,
      22,   130,   409,  -705,  -705,  -705,    50,   163,   163,   528,
     529,   531,   532,   -41,    22,   144,    30,   534,   153,    28,
      92,   253,  -705,  -705,   538,  -705,    -4,   536,   537,  -705,
    -705,  -705,  -705,  -705,  -705,  -705,  -705,  -705,  -705,  -705,
     539,   465,  -705,  -705,  -705,  -705,  -705,  -705,  -705,  -705,
    -705,  -705,  -705,  -705,  -705,  -705,  -705,  -705,  -705,  -705,
    -705,  -705,  -705,  -705,  -705,  -705,  -705,  -705,  -705,  -705,
    -705,  -705,  -705,  -705,  -705,   225,  -705,   243,  -705,  -705,
     244,  -705,  -705,  -705,  -705,   541,   544,   545,   546,   548,
    -705,  -705,  -705,   251,  -705,  -705,  -705,  -705,  -705,  -705,
    -705,  -705,  -705,  -705,  -705,  -705,  -705,   252,  -705,   549,
     551,  -705,  -705,   550,   556,  -705,  -705,   555,   559,  -705,
    -705,   557,   561,  -705,  -705,  -705,   136,  -705,  -705,  -705,
     560,  -705,  -705,  -705,   285,  -705,  -705,  -705,  -705,   293,
    -705,   562,   564,  -705,   565,   566,   567,   568,   569,   570,
     255,  -705,  -705,  -705,  -705,  -705,  -705,  -705,  -705,  -705,
     571,   572,   573,  -705,  -705,   258,  -705,  -705,  -705,  -705,
    -705,  -705,  -705,  -705,   261,  -705,  -705,  -705,   262,   427,
     428,  -705,  -705,   575,   579,  -705,  -705,   577,   581,  -705,
    -705,   580,   582,  -705,  -705,   583,  -705,   574,   409,  -705,
    -705,   584,   585,   586,   588,   441,   432,   443,   438,   449,
     591,   593,   163,  -705,  -705,    26,  -705,   528,    63,  -705,
     529,   110,  -705,   531,    59,  -705,   532,   -41,  -705,  -705,
     144,  -705,    30,  -705,   -46,  -705,   534,   450,   453,   457,
     458,   459,   461,   153,  -705,   594,   595,   462,   468,   469,
      28,  -705,   596,   597,    92,  -705,  -705,  -705,   598,   602,
    -705,    74,  -705,   536,    -6,  -705,   537,    58,  -705,   539,
     603,  -705,   604,  -705,   283,   471,   472,   475,  -705,  -705,
    -705,  -705,  -705,   476,   478,  -705,   265,  -705,   600,  -705,
     605,  -705,  -705,  -705,  -705,  -705,  -705,  -705,  -705,  -705,
    -705,  -705,  -705,  -705,   268,  -705,  -705,  -705,  -705,  -705,
    -705,  -705,   271,  -705,  -705,  -705,  -705,  -705,  -705,  -705,
    -705,   245,   479,  -705,  -705,  -705,  -705,   485,   489,  -705,
    -705,   490,   275,  -705,   278,  -705,   608,  -705,   505,   558,
    -705,  -705,  -705,  -705,  -705,  -705,  -705,  -705,  -705,  -705,
    -705,  -705,  -705,    59,  -705,  -705,  -705,  -705,  -705,  -705,
    -705,  -705,  -705,  -705,  -705,  -705,  -705,  -705,  -705,   324,
    -705,  -705,    75,   558,  -705,  -705,   613,  -705,  -705,  -705,
     281,  -705,  -705,  -705,  -705,  -705,   614,   507,   615,    75,
    -705,   620,  -705,   511,  -705,   619,  -705,  -705,   325,  -705,
     -63,   619,  -705,  -705,   616,   625,   628,   282,  -705,  -705,
    -705,  -705,  -705,  -705,   629,   516,   521,   523,   -63,  -705,
     527,  -705,  -705,  -705,  -705,  -705
  };

  const unsigned short int
  Dhcp6Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,    24,    26,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     1,    43,
      36,    32,    31,    28,    29,    30,    35,     3,    33,    34,
      56,     5,    68,     7,   102,     9,   215,    11,   350,    13,
     373,    15,   401,    17,   279,    19,   287,    21,   322,    23,
     180,    25,   485,    27,    45,    39,     0,     0,     0,     0,
       0,     0,   403,     0,   289,   324,     0,     0,    47,     0,
      46,     0,     0,    40,    66,   538,   532,   534,   536,     0,
      65,     0,    58,    60,    62,    63,    64,    61,   100,   111,
     113,     0,     0,     0,     0,     0,   207,   277,   314,   253,
     153,   170,   161,   434,   172,   191,   451,     0,   473,   483,
      94,     0,    70,    72,    73,    74,    75,    76,    79,    80,
      81,    82,    84,    83,    88,    89,    77,    78,    86,    87,
      85,    90,    91,    92,    93,   108,     0,     0,   104,   106,
     107,   438,   342,   365,   361,   363,   238,   240,   242,     0,
       0,   246,   244,   393,   430,   237,   219,   220,   221,   222,
       0,   217,   226,   227,   228,   231,   233,   229,   230,   223,
     224,   235,   236,   225,   232,   234,   359,   358,   355,     0,
     352,   354,   356,   357,   386,     0,   389,     0,     0,   385,
     380,   383,   384,     0,   375,   377,   378,   381,   382,   379,
     428,   416,   418,   420,   422,   424,   426,   415,   414,     0,
     404,   405,   409,   410,   407,   411,   412,   413,   408,     0,
     304,   143,     0,   308,   306,   311,     0,   300,   301,     0,
     290,   291,   293,   303,   294,   295,   296,   310,   297,   298,
     299,   336,     0,     0,   334,   335,   338,   339,     0,   325,
     326,   328,   329,   330,   331,   332,   333,   187,   189,   184,
       0,   182,   185,   186,     0,   505,   507,     0,   510,     0,
       0,   514,   518,     0,     0,     0,   523,   530,   503,     0,
     487,   489,   490,   491,   492,   493,   494,   495,   496,   497,
     498,   499,   500,   501,   502,    44,     0,     0,    37,     0,
       0,     0,     0,     0,     0,    55,     0,    57,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    69,     0,     0,     0,   103,   440,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   216,     0,     0,   351,     0,     0,     0,     0,     0,
       0,   374,     0,     0,     0,     0,     0,     0,     0,   402,
       0,   280,     0,     0,     0,     0,     0,     0,     0,   288,
       0,     0,     0,     0,   323,     0,     0,     0,     0,   181,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   486,    48,    41,     0,     0,
       0,     0,     0,     0,    59,     0,     0,     0,    95,    96,
      97,    98,    99,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   472,     0,     0,    71,     0,   110,
     105,   449,   447,   448,   446,     0,   441,   442,   444,   445,
       0,     0,     0,     0,     0,     0,     0,   251,   252,     0,
       0,     0,     0,   218,     0,   353,     0,   388,     0,   391,
     392,   376,     0,     0,     0,     0,     0,     0,     0,   406,
       0,     0,   302,     0,     0,     0,   313,   292,     0,   340,
     341,   327,     0,     0,   183,   504,     0,     0,   509,     0,
     512,   513,     0,     0,   520,   521,   522,     0,     0,   488,
       0,     0,     0,   533,   535,   537,     0,     0,     0,   209,
     281,   316,   255,     0,    45,     0,     0,   174,     0,     0,
       0,     0,    49,   109,     0,   439,     0,   344,   367,    38,
     362,   364,   239,   241,   243,   248,   249,   250,   247,   245,
     395,     0,   360,   387,   390,   429,   417,   419,   421,   423,
     425,   427,   305,   144,   309,   307,   312,   337,   188,   190,
     506,   508,   511,   516,   517,   515,   519,   525,   526,   527,
     528,   529,   524,   531,    42,     0,   543,     0,   540,   542,
       0,   130,   136,   138,   140,     0,     0,     0,     0,     0,
     149,   151,   129,     0,   115,   117,   118,   119,   120,   121,
     122,   123,   124,   125,   126,   127,   128,     0,   213,     0,
     210,   211,   285,     0,   282,   283,   320,     0,   317,   318,
     259,     0,   256,   257,   159,   160,     0,   155,   157,   158,
       0,   168,   169,   165,     0,   163,   166,   167,   436,     0,
     178,     0,   175,   176,     0,     0,     0,     0,     0,     0,
       0,   193,   195,   196,   197,   198,   199,   200,   462,   468,
       0,     0,     0,   461,   460,     0,   453,   455,   458,   456,
     457,   459,   479,   481,     0,   475,   477,   478,     0,    51,
       0,   443,   348,     0,   345,   346,   371,     0,   368,   369,
     399,     0,   396,   397,   432,     0,    67,     0,     0,   539,
     101,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   112,   114,     0,   208,     0,   289,   278,
       0,   324,   315,     0,     0,   254,     0,     0,   154,   171,
       0,   162,     0,   435,     0,   173,     0,     0,     0,     0,
       0,     0,     0,     0,   192,     0,     0,     0,     0,     0,
       0,   452,     0,     0,     0,   474,   484,    53,     0,    52,
     450,     0,   343,     0,     0,   366,     0,   403,   394,     0,
       0,   431,     0,   541,     0,     0,     0,     0,   142,   145,
     146,   147,   148,     0,     0,   116,     0,   212,     0,   284,
       0,   319,   276,   273,   275,   267,   268,   263,   264,   265,
     266,   272,   271,   274,     0,   261,   269,   270,   258,   156,
     164,   437,     0,   177,   201,   202,   203,   204,   205,   206,
     194,     0,     0,   467,   470,   471,   454,     0,     0,   476,
      50,     0,     0,   347,     0,   370,     0,   398,     0,     0,
     132,   133,   134,   135,   131,   137,   139,   141,   150,   152,
     214,   286,   321,     0,   260,   179,   464,   465,   466,   463,
     469,   480,   482,    54,   349,   372,   400,   433,   547,     0,
     545,   262,     0,     0,   544,   559,     0,   557,   555,   551,
       0,   549,   553,   554,   552,   546,     0,     0,     0,     0,
     548,     0,   556,     0,   550,     0,   558,   563,     0,   561,
       0,     0,   560,   571,     0,     0,     0,     0,   565,   567,
     568,   569,   570,   562,     0,     0,     0,     0,     0,   564,
       0,   573,   574,   575,   566,   572
  };

  const short int
  Dhcp6Parser::yypgoto_[] =
  {
    -705,  -705,  -705,  -705,  -705,  -705,  -705,  -705,  -705,  -705,
    -705,  -705,  -705,  -705,  -705,    13,  -705,   172,  -705,  -705,
    -705,  -705,  -705,  -705,   101,  -705,  -138,  -705,  -705,  -705,
     -66,  -705,  -705,  -705,   320,  -705,  -705,  -705,  -705,   118,
     298,   -67,   -62,   -50,   -49,  -705,  -705,  -705,  -705,  -705,
     114,   299,  -705,  -705,  -705,  -705,  -705,  -705,  -705,   116,
     -87,  -705,  -705,  -705,  -705,  -705,  -705,  -705,  -705,  -705,
    -705,   -74,  -705,  -517,  -705,  -705,  -705,  -705,  -705,  -705,
    -705,  -705,  -705,  -705,  -101,  -511,  -705,  -705,  -705,  -705,
    -103,  -705,  -705,  -705,  -705,  -705,  -705,  -705,  -705,  -108,
    -705,  -705,  -705,  -105,   264,  -705,  -705,  -705,  -705,  -705,
    -705,  -705,  -113,  -705,  -705,  -705,  -705,  -705,  -705,  -704,
    -705,  -705,  -705,   -86,  -705,  -705,  -705,   -83,   295,  -705,
    -705,  -703,  -705,  -702,  -705,  -515,  -705,  -692,  -705,  -705,
    -705,  -690,  -705,  -705,  -705,  -705,   -93,  -705,  -705,  -219,
     592,  -705,  -705,  -705,  -705,  -705,   -84,  -705,  -705,  -705,
     -79,  -705,   274,  -705,   -61,  -705,  -705,  -705,  -705,  -705,
     -52,  -705,  -705,  -705,  -705,  -705,   -54,  -705,  -705,  -705,
     -82,  -705,  -705,  -705,   -57,  -705,   288,  -705,  -705,  -705,
    -705,  -705,  -705,  -705,  -705,  -705,  -705,  -705,   -96,  -705,
    -705,  -705,   -90,   334,  -705,  -705,   -58,  -705,   -45,  -705,
    -705,  -705,  -705,  -705,   -94,  -705,  -705,  -705,   -91,   335,
    -705,  -705,  -705,  -705,  -705,  -705,  -705,  -705,  -705,  -705,
    -705,   -89,  -705,  -705,  -705,   -88,  -705,   316,  -705,  -705,
    -705,  -705,  -705,  -705,  -705,  -705,  -705,  -705,  -705,  -705,
    -705,  -705,  -679,  -705,  -705,  -705,  -705,  -705,  -705,  -705,
    -705,  -705,   156,  -705,  -705,  -705,  -705,  -705,  -705,   -72,
    -705,  -705,  -705,  -705,  -705,  -705,  -705,  -705,  -705,  -705,
    -705,  -705,   -73,  -705,  -705,  -705,  -705,  -705,  -705,  -705,
    -705,   162,   296,  -705,  -705,  -705,  -705,  -705,  -705,  -705,
    -705,  -705,  -705,  -705,  -705,  -705,  -705,  -705,  -705,  -705,
    -705,  -705,  -705,  -705,  -705,  -705,  -705,  -705,  -705,  -705,
    -705,  -705,  -705,  -705,  -705,   -12,  -705,  -705,  -705,  -186,
    -705,  -705,  -201,  -705,  -705,  -705,  -705,  -705,  -705,  -212,
    -705,  -705,  -227,  -705,  -705,  -705,  -705,  -705
  };

  const short int
  Dhcp6Parser::yydefgoto_[] =
  {
      -1,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    78,    37,    38,    65,   550,
      82,    83,    39,    64,    79,    80,   543,   699,   778,   779,
     120,    41,    66,    91,    92,    93,   310,    43,    67,   121,
     122,   123,   124,   125,   126,   127,   128,   318,    45,    68,
     147,   148,   149,   342,   150,   129,   319,   130,   320,   613,
     614,   615,   721,   864,   616,   722,   617,   723,   618,   724,
     619,   238,   383,   621,   622,   623,   624,   625,   730,   626,
     731,   131,   330,   646,   647,   648,   649,   132,   332,   654,
     655,   656,   657,   133,   331,   134,   334,   661,   662,   663,
     754,    61,    76,   270,   271,   272,   396,   273,   397,   135,
     335,   670,   671,   672,   673,   674,   675,   676,   677,   136,
     326,   629,   630,   631,   735,    47,    69,   170,   171,   172,
     351,   173,   352,   174,   353,   175,   357,   176,   356,   558,
     177,   178,   137,   329,   641,   642,   643,   744,   824,   825,
     138,   327,    55,    73,   633,   634,   635,   738,    57,    74,
     239,   240,   241,   242,   243,   244,   245,   382,   246,   386,
     247,   385,   248,   249,   387,   250,   139,   328,   637,   638,
     639,   741,    59,    75,   258,   259,   260,   261,   262,   391,
     263,   264,   265,   266,   180,   347,   703,   704,   705,   781,
      49,    70,   189,   190,   191,   362,   181,   349,   182,   350,
     183,   348,   707,   708,   709,   784,    51,    71,   203,   204,
     205,   365,   206,   207,   367,   208,   209,   184,   358,   711,
     712,   713,   787,    53,    72,   219,   220,   221,   222,   373,
     223,   374,   224,   375,   225,   376,   226,   377,   227,   378,
     228,   372,   185,   359,   715,   790,   140,   333,   659,   346,
     455,   456,   457,   458,   459,   544,   141,   336,   685,   686,
     687,   765,   879,   688,   689,   766,   690,   691,   142,   143,
     338,   694,   695,   696,   772,   697,   773,   144,   339,    63,
      77,   289,   290,   291,   292,   401,   293,   402,   294,   295,
     404,   296,   297,   298,   407,   585,   299,   408,   300,   301,
     302,   303,   412,   592,   304,   413,    94,   312,    95,   313,
      96,   314,    97,   311,   597,   598,   599,   717,   889,   890,
     892,   900,   901,   902,   903,   908,   904,   906,   918,   919,
     920,   927,   928,   929,   934,   930,   931,   932
  };

  const unsigned short int
  Dhcp6Parser::yytable_[] =
  {
      90,   255,   166,   165,   187,   199,   217,   167,   237,   254,
     269,   288,   192,   201,   256,   179,   188,   200,   218,   168,
     169,   658,   684,   257,   653,   193,   202,    29,    36,    30,
      84,    31,   108,   151,   108,   231,   644,   151,   267,   268,
     818,   819,   820,    28,   678,   194,   195,   196,   197,   198,
     154,   155,   822,   606,   823,    40,   316,   101,   102,   103,
     104,   317,   145,   146,   108,   827,   151,   923,   451,    42,
     924,   925,   926,   340,   152,   344,   153,    81,   341,   230,
     345,   107,   154,   155,   156,   157,   158,   159,   160,   161,
     101,   102,   103,   104,    44,   106,   108,   108,   231,   162,
     163,   305,   231,   162,   232,   233,    89,   164,   234,   235,
     236,   645,   108,    46,   231,   360,   267,   268,   157,   158,
     361,   160,   161,   186,    48,   679,   680,   681,   682,   210,
     154,   155,   162,   211,   212,   213,   214,   215,   216,   747,
     164,    98,   748,   306,    99,   100,    89,    85,    89,   231,
     251,   232,   233,   252,   253,   363,    86,    87,    88,   307,
     364,   101,   102,   103,   104,   105,   106,   107,   108,   818,
     819,   820,    89,    50,    32,    33,    34,    35,    89,   601,
      89,   822,    52,   823,   602,   603,   604,   605,   606,   607,
     608,   609,   610,   611,   827,   692,   693,   109,   110,   111,
     112,   113,   231,   370,   895,    54,   896,   897,   371,   398,
      89,    89,    56,   114,   399,    89,   115,   587,   588,   589,
     590,   644,   651,   116,   652,   414,    89,    89,   340,   821,
     415,   117,   118,   716,    58,   119,    60,   831,    62,   653,
     664,   665,   666,   667,   668,   669,   718,   344,   308,   591,
      90,   719,   720,   684,   732,   732,   379,   309,   763,   733,
     734,   770,    89,   764,   774,   414,   771,   315,   360,   775,
     776,   873,   453,   870,   398,   381,   874,   321,   363,   875,
     452,   370,    89,   884,   909,   938,   885,   380,   750,   910,
     939,   751,   454,   166,   165,   322,   752,   187,   167,   753,
     860,   861,   862,   863,   199,   192,   179,   583,   584,   188,
     168,   169,   201,   323,   217,    89,   200,   324,   193,   416,
     417,   255,   325,   337,   237,   202,   218,   893,   921,   254,
     894,   922,   343,   354,   256,   355,   555,   556,   557,   876,
     877,   878,   366,   257,   565,   566,   567,   368,   288,   369,
     384,   388,   389,   390,   418,   392,   393,   394,   821,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,     1,     2,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,   395,   449,   400,   403,
     405,   406,   409,   410,   411,   419,   420,   421,   422,   423,
     425,   426,   427,   428,   433,    89,   434,   435,   436,   429,
     430,   437,   431,   432,   438,   439,   440,   441,   442,   443,
     445,   446,   444,   448,   460,   461,   462,   463,   464,   465,
     466,   468,   467,   469,   523,   524,   525,   470,   471,   472,
     474,   476,   477,   478,   482,   479,   483,   480,   484,   485,
     486,   487,   488,   620,   620,   490,   491,   492,   493,   494,
     495,   612,   612,   496,   498,   499,   500,   502,   503,   505,
     506,   507,   453,   683,   508,   288,   551,   509,   512,   510,
     452,   513,   514,   511,   517,   518,   520,   515,   516,   552,
     521,   522,   454,   526,   527,   528,   529,   530,   531,   532,
     533,   534,   535,   536,   537,   553,   554,   538,   539,   540,
     541,   542,   545,   546,   547,    30,   579,   548,   559,   560,
     561,   562,   563,   564,   568,   569,   570,   571,   572,   573,
     574,   575,   576,   594,   577,   628,   632,   596,   636,   640,
     586,   660,   700,   702,   706,   725,   710,   714,   726,   727,
     728,   578,   729,   580,   737,   736,   739,   581,   582,   740,
     593,   742,   743,   745,   746,   888,   749,   756,   755,   757,
     758,   759,   760,   761,   762,   767,   768,   769,   792,   777,
     780,   782,   783,   785,   786,   789,   788,   799,   794,   795,
     796,   791,   797,   801,   798,   803,   800,   804,   841,   842,
     847,   848,   802,   834,   850,   851,   835,   858,   871,   859,
     836,   837,   838,   872,   839,   843,   886,   907,   911,   913,
     935,   844,   845,   865,   866,   915,   917,   867,   868,   936,
     869,   880,   937,   940,   549,   650,   424,   881,   447,   595,
     600,   882,   883,   450,   627,   805,   829,   830,   833,   832,
     840,   807,   806,   828,   891,   473,   809,   887,   620,   808,
     912,   811,   504,   916,   497,   229,   612,   255,   166,   165,
     817,   941,   237,   167,   942,   254,   943,   813,   812,   945,
     256,   179,   814,   501,   810,   168,   169,   853,   269,   257,
     826,   852,   855,   854,   815,   816,   489,   475,   846,   856,
     857,   849,   701,   698,   683,   481,   793,   905,   914,   933,
     519,   944,     0,     0,     0,   187,     0,     0,   199,     0,
       0,   217,     0,   192,     0,     0,   201,   188,     0,     0,
     200,     0,     0,   218,     0,     0,   193,     0,     0,   202,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   817,
       0,     0,     0,     0,     0,     0,   813,   812,     0,     0,
       0,   814,     0,     0,     0,     0,     0,     0,   899,   826,
       0,     0,     0,   815,   816,     0,   898,     0,     0,     0,
       0,     0,     0,     0,     0,   899,     0,     0,     0,     0,
       0,     0,     0,   898
  };

  const short int
  Dhcp6Parser::yycheck_[] =
  {
      66,    75,    69,    69,    70,    71,    72,    69,    74,    75,
      76,    77,    70,    71,    75,    69,    70,    71,    72,    69,
      69,   536,   539,    75,   535,    70,    71,     5,    15,     7,
      10,     9,    38,     7,    38,    39,    77,     7,    84,    85,
     744,   744,   744,     0,    16,    51,    52,    53,    54,    55,
      56,    57,   744,    25,   744,     7,     3,    31,    32,    33,
      34,     8,    12,    13,    38,   744,     7,   130,    72,     7,
     133,   134,   135,     3,    48,     3,    50,   152,     8,    16,
       8,    37,    56,    57,    58,    59,    60,    61,    62,    63,
      31,    32,    33,    34,     7,    36,    38,    38,    39,    73,
      74,     6,    39,    73,    41,    42,   152,    81,    45,    46,
      47,   152,    38,     7,    39,     3,    84,    85,    59,    60,
       8,    62,    63,    49,     7,    97,    98,    99,   100,    71,
      56,    57,    73,    75,    76,    77,    78,    79,    80,     3,
      81,    11,     6,     3,    14,    15,   152,   127,   152,    39,
      40,    41,    42,    43,    44,     3,   136,   137,   138,     4,
       8,    31,    32,    33,    34,    35,    36,    37,    38,   873,
     873,   873,   152,     7,   152,   153,   154,   155,   152,    16,
     152,   873,     7,   873,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,   873,   103,   104,    67,    68,    69,
      70,    71,    39,     3,   129,     7,   131,   132,     8,     3,
     152,   152,     7,    83,     8,   152,    86,   123,   124,   125,
     126,    77,    78,    93,    80,     3,   152,   152,     3,   744,
       8,   101,   102,     8,     7,   105,     7,   752,     7,   750,
      87,    88,    89,    90,    91,    92,     3,     3,     8,   155,
     316,     8,     8,   770,     3,     3,     8,     3,     3,     8,
       8,     3,   152,     8,     3,     3,     8,     4,     3,     8,
       8,     3,   346,     8,     3,     8,     8,     4,     3,     8,
     346,     3,   152,     8,     3,     3,     8,     3,     3,     8,
       8,     6,   346,   360,   360,     4,     3,   363,   360,     6,
      17,    18,    19,    20,   370,   363,   360,   120,   121,   363,
     360,   360,   370,     4,   380,   152,   370,     4,   363,   306,
     307,   395,     4,     4,   390,   370,   380,     3,     3,   395,
       6,     6,     4,     4,   395,     4,    64,    65,    66,    94,
      95,    96,     4,   395,   482,   483,   484,     4,   414,     4,
       4,     4,     8,     3,   152,     4,     4,     8,   873,   106,
     107,   108,   109,   110,   111,   112,   113,   114,   115,   116,
     117,   118,   119,   139,   140,   141,   142,   143,   144,   145,
     146,   147,   148,   149,   150,   151,     3,   155,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,   153,     4,   152,     4,     4,     4,   153,
     153,     4,   153,   153,     4,     4,     4,     4,     4,     4,
       4,     4,   153,     4,     4,     4,     4,     4,     4,     4,
       4,   155,   153,     4,   421,   422,   423,     4,     4,     4,
       4,     4,   153,     4,     4,   153,     4,   153,     4,     4,
       4,     4,     4,   527,   528,     4,     4,   153,     4,     4,
       4,   527,   528,   155,     4,   155,   155,     4,     4,   155,
       4,     4,   546,   539,   153,   541,   463,     4,     4,   153,
     546,     4,   155,   153,     4,     4,     4,   155,   155,   152,
       7,     7,   546,     7,     7,     7,     5,     5,     5,     5,
       5,     5,     5,     5,     5,   152,   152,     7,     7,     7,
       7,     5,     8,     3,     5,     7,   503,     5,   152,     5,
       7,   152,   152,   152,   152,   152,   152,   152,   152,   152,
     152,   152,   152,   520,   152,     7,     7,   128,     7,     7,
     122,     7,     4,     7,     7,     4,     7,    82,     4,     4,
       4,   152,     4,   152,     3,     6,     6,   152,   152,     3,
     152,     6,     3,     6,     3,     7,     6,     3,     6,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,   152,
     152,     6,     3,     6,     3,     3,     6,   155,     4,     4,
       4,     8,     4,   155,   153,     4,   153,     4,     4,     4,
       4,     4,   153,   153,     6,     3,   153,     4,     8,     5,
     153,   153,   153,     8,   153,   153,     8,     4,     4,     4,
       4,   153,   153,   152,   152,     5,     7,   152,   152,     4,
     152,   152,     4,     4,   462,   534,   316,   152,   340,   521,
     526,   152,   152,   344,   528,   732,   747,   750,   756,   754,
     763,   737,   735,   746,   873,   360,   740,   152,   732,   738,
     153,   743,   398,   152,   390,    73,   732,   741,   735,   735,
     744,   155,   738,   735,   153,   741,   153,   744,   744,   152,
     741,   735,   744,   395,   741,   735,   735,   783,   754,   741,
     744,   781,   786,   784,   744,   744,   380,   363,   770,   787,
     789,   774,   546,   541,   770,   370,   718,   893,   909,   921,
     414,   938,    -1,    -1,    -1,   781,    -1,    -1,   784,    -1,
      -1,   787,    -1,   781,    -1,    -1,   784,   781,    -1,    -1,
     784,    -1,    -1,   787,    -1,    -1,   781,    -1,    -1,   784,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   873,
      -1,    -1,    -1,    -1,    -1,    -1,   873,   873,    -1,    -1,
      -1,   873,    -1,    -1,    -1,    -1,    -1,    -1,   892,   873,
      -1,    -1,    -1,   873,   873,    -1,   892,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   909,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   909
  };

  const unsigned short int
  Dhcp6Parser::yystos_[] =
  {
       0,   139,   140,   141,   142,   143,   144,   145,   146,   147,
     148,   149,   150,   151,   157,   158,   159,   160,   161,   162,
     163,   164,   165,   166,   167,   168,   169,   170,     0,     5,
       7,     9,   152,   153,   154,   155,   171,   172,   173,   178,
       7,   187,     7,   193,     7,   204,     7,   281,     7,   356,
       7,   372,     7,   389,     7,   308,     7,   314,     7,   338,
       7,   257,     7,   445,   179,   174,   188,   194,   205,   282,
     357,   373,   390,   309,   315,   339,   258,   446,   171,   180,
     181,   152,   176,   177,    10,   127,   136,   137,   138,   152,
     186,   189,   190,   191,   472,   474,   476,   478,    11,    14,
      15,    31,    32,    33,    34,    35,    36,    37,    38,    67,
      68,    69,    70,    71,    83,    86,    93,   101,   102,   105,
     186,   195,   196,   197,   198,   199,   200,   201,   202,   211,
     213,   237,   243,   249,   251,   265,   275,   298,   306,   332,
     412,   422,   434,   435,   443,    12,    13,   206,   207,   208,
     210,     7,    48,    50,    56,    57,    58,    59,    60,    61,
      62,    63,    73,    74,    81,   186,   197,   198,   199,   200,
     283,   284,   285,   287,   289,   291,   293,   296,   297,   332,
     350,   362,   364,   366,   383,   408,    49,   186,   332,   358,
     359,   360,   362,   364,    51,    52,    53,    54,    55,   186,
     332,   362,   364,   374,   375,   376,   378,   379,   381,   382,
      71,    75,    76,    77,    78,    79,    80,   186,   332,   391,
     392,   393,   394,   396,   398,   400,   402,   404,   406,   306,
      16,    39,    41,    42,    45,    46,    47,   186,   227,   316,
     317,   318,   319,   320,   321,   322,   324,   326,   328,   329,
     331,    40,    43,    44,   186,   227,   320,   326,   340,   341,
     342,   343,   344,   346,   347,   348,   349,    84,    85,   186,
     259,   260,   261,   263,   106,   107,   108,   109,   110,   111,
     112,   113,   114,   115,   116,   117,   118,   119,   186,   447,
     448,   449,   450,   452,   454,   455,   457,   458,   459,   462,
     464,   465,   466,   467,   470,     6,     3,     4,     8,     3,
     192,   479,   473,   475,   477,     4,     3,     8,   203,   212,
     214,     4,     4,     4,     4,     4,   276,   307,   333,   299,
     238,   250,   244,   413,   252,   266,   423,     4,   436,   444,
       3,     8,   209,     4,     3,     8,   415,   351,   367,   363,
     365,   286,   288,   290,     4,     4,   294,   292,   384,   409,
       3,     8,   361,     3,     8,   377,     4,   380,     4,     4,
       3,     8,   407,   395,   397,   399,   401,   403,   405,     8,
       3,     8,   323,   228,     4,   327,   325,   330,     4,     8,
       3,   345,     4,     4,     8,     3,   262,   264,     3,     8,
       4,   451,   453,     4,   456,     4,     4,   460,   463,     4,
       4,     4,   468,   471,     3,     8,   171,   171,   152,     4,
       4,     4,     4,     4,   190,     4,     4,     4,   153,   153,
     153,   153,   153,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,   153,     4,     4,   196,     4,   155,
     207,    72,   186,   227,   332,   416,   417,   418,   419,   420,
       4,     4,     4,     4,     4,     4,     4,   153,   155,     4,
       4,     4,     4,   284,     4,   359,     4,   153,     4,   153,
     153,   375,     4,     4,     4,     4,     4,     4,     4,   393,
       4,     4,   153,     4,     4,     4,   155,   318,     4,   155,
     155,   342,     4,     4,   260,   155,     4,     4,   153,     4,
     153,   153,     4,     4,   155,   155,   155,     4,     4,   448,
       4,     7,     7,   171,   171,   171,     7,     7,     7,     5,
       5,     5,     5,     5,     5,     5,     5,     5,     7,     7,
       7,     7,     5,   182,   421,     8,     3,     5,     5,   173,
     175,   171,   152,   152,   152,    64,    65,    66,   295,   152,
       5,     7,   152,   152,   152,   182,   182,   182,   152,   152,
     152,   152,   152,   152,   152,   152,   152,   152,   152,   171,
     152,   152,   152,   120,   121,   461,   122,   123,   124,   125,
     126,   155,   469,   152,   171,   195,   128,   480,   481,   482,
     206,    16,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,   186,   215,   216,   217,   220,   222,   224,   226,
     227,   229,   230,   231,   232,   233,   235,   215,     7,   277,
     278,   279,     7,   310,   311,   312,     7,   334,   335,   336,
       7,   300,   301,   302,    77,   152,   239,   240,   241,   242,
     180,    78,    80,   241,   245,   246,   247,   248,   291,   414,
       7,   253,   254,   255,    87,    88,    89,    90,    91,    92,
     267,   268,   269,   270,   271,   272,   273,   274,    16,    97,
      98,    99,   100,   186,   229,   424,   425,   426,   429,   430,
     432,   433,   103,   104,   437,   438,   439,   441,   447,   183,
       4,   418,     7,   352,   353,   354,     7,   368,   369,   370,
       7,   385,   386,   387,    82,   410,     8,   483,     3,     8,
       8,   218,   221,   223,   225,     4,     4,     4,     4,     4,
     234,   236,     3,     8,     8,   280,     6,     3,   313,     6,
       3,   337,     6,     3,   303,     6,     3,     3,     6,     6,
       3,     6,     3,     6,   256,     6,     3,     4,     4,     4,
       4,     4,     4,     3,     8,   427,   431,     4,     4,     4,
       3,     8,   440,   442,     3,     8,     8,   152,   184,   185,
     152,   355,     6,     3,   371,     6,     3,   388,     6,     3,
     411,     8,     4,   481,     4,     4,     4,     4,   153,   155,
     153,   155,   153,     4,     4,   216,   283,   279,   316,   312,
     340,   336,   186,   197,   198,   199,   200,   227,   275,   287,
     289,   291,   293,   297,   304,   305,   332,   408,   302,   240,
     246,   291,   259,   255,   153,   153,   153,   153,   153,   153,
     268,     4,     4,   153,   153,   153,   425,     4,     4,   438,
       6,     3,   358,   354,   374,   370,   391,   387,     4,     5,
      17,    18,    19,    20,   219,   152,   152,   152,   152,   152,
       8,     8,     8,     3,     8,     8,    94,    95,    96,   428,
     152,   152,   152,   152,     8,     8,     8,   152,     7,   484,
     485,   305,   486,     3,     6,   129,   131,   132,   186,   227,
     487,   488,   489,   490,   492,   485,   493,     4,   491,     3,
       8,     4,   153,     4,   488,     5,   152,     7,   494,   495,
     496,     3,     6,   130,   133,   134,   135,   497,   498,   499,
     501,   502,   503,   495,   500,     4,     4,     4,     3,     8,
       4,   155,   153,   153,   498,   152
  };

  const unsigned short int
  Dhcp6Parser::yyr1_[] =
  {
       0,   156,   158,   157,   159,   157,   160,   157,   161,   157,
     162,   157,   163,   157,   164,   157,   165,   157,   166,   157,
     167,   157,   168,   157,   169,   157,   170,   157,   171,   171,
     171,   171,   171,   171,   171,   172,   174,   173,   175,   176,
     176,   177,   177,   179,   178,   180,   180,   181,   181,   183,
     182,   184,   184,   185,   185,   186,   188,   187,   189,   189,
     190,   190,   190,   190,   190,   190,   192,   191,   194,   193,
     195,   195,   196,   196,   196,   196,   196,   196,   196,   196,
     196,   196,   196,   196,   196,   196,   196,   196,   196,   196,
     196,   196,   196,   196,   196,   197,   198,   199,   200,   201,
     203,   202,   205,   204,   206,   206,   207,   207,   209,   208,
     210,   212,   211,   214,   213,   215,   215,   216,   216,   216,
     216,   216,   216,   216,   216,   216,   216,   216,   216,   216,
     218,   217,   219,   219,   219,   219,   221,   220,   223,   222,
     225,   224,   226,   228,   227,   229,   230,   231,   232,   234,
     233,   236,   235,   238,   237,   239,   239,   240,   240,   241,
     242,   244,   243,   245,   245,   246,   246,   246,   247,   248,
     250,   249,   252,   251,   253,   253,   254,   254,   256,   255,
     258,   257,   259,   259,   259,   260,   260,   262,   261,   264,
     263,   266,   265,   267,   267,   268,   268,   268,   268,   268,
     268,   269,   270,   271,   272,   273,   274,   276,   275,   277,
     277,   278,   278,   280,   279,   282,   281,   283,   283,   284,
     284,   284,   284,   284,   284,   284,   284,   284,   284,   284,
     284,   284,   284,   284,   284,   284,   284,   284,   286,   285,
     288,   287,   290,   289,   292,   291,   294,   293,   295,   295,
     295,   296,   297,   299,   298,   300,   300,   301,   301,   303,
     302,   304,   304,   305,   305,   305,   305,   305,   305,   305,
     305,   305,   305,   305,   305,   305,   305,   307,   306,   309,
     308,   310,   310,   311,   311,   313,   312,   315,   314,   316,
     316,   317,   317,   318,   318,   318,   318,   318,   318,   318,
     318,   319,   320,   321,   323,   322,   325,   324,   327,   326,
     328,   330,   329,   331,   333,   332,   334,   334,   335,   335,
     337,   336,   339,   338,   340,   340,   341,   341,   342,   342,
     342,   342,   342,   342,   342,   343,   345,   344,   346,   347,
     348,   349,   351,   350,   352,   352,   353,   353,   355,   354,
     357,   356,   358,   358,   359,   359,   359,   359,   359,   361,
     360,   363,   362,   365,   364,   367,   366,   368,   368,   369,
     369,   371,   370,   373,   372,   374,   374,   375,   375,   375,
     375,   375,   375,   375,   375,   375,   377,   376,   378,   380,
     379,   381,   382,   384,   383,   385,   385,   386,   386,   388,
     387,   390,   389,   391,   391,   392,   392,   393,   393,   393,
     393,   393,   393,   393,   393,   393,   395,   394,   397,   396,
     399,   398,   401,   400,   403,   402,   405,   404,   407,   406,
     409,   408,   411,   410,   413,   412,   414,   414,   415,   291,
     416,   416,   417,   417,   418,   418,   418,   418,   419,   421,
     420,   423,   422,   424,   424,   425,   425,   425,   425,   425,
     425,   425,   427,   426,   428,   428,   428,   429,   431,   430,
     432,   433,   434,   436,   435,   437,   437,   438,   438,   440,
     439,   442,   441,   444,   443,   446,   445,   447,   447,   448,
     448,   448,   448,   448,   448,   448,   448,   448,   448,   448,
     448,   448,   448,   448,   449,   451,   450,   453,   452,   454,
     456,   455,   457,   458,   460,   459,   461,   461,   463,   462,
     464,   465,   466,   468,   467,   469,   469,   469,   469,   469,
     471,   470,   473,   472,   475,   474,   477,   476,   479,   478,
     480,   480,   481,   483,   482,   484,   484,   486,   485,   487,
     487,   488,   488,   488,   488,   488,   489,   491,   490,   493,
     492,   494,   494,   496,   495,   497,   497,   498,   498,   498,
     498,   500,   499,   501,   502,   503
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
       1,     1,     1,     1,     1,     1,     1,     1,     0,     4,
       0,     4,     0,     4,     0,     4,     0,     4,     1,     1,
       1,     3,     3,     0,     6,     0,     1,     1,     3,     0,
       4,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     0,     6,     0,
       4,     0,     1,     1,     3,     0,     4,     0,     4,     0,
       1,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     3,     1,     0,     4,     0,     4,     0,     4,
       1,     0,     4,     3,     0,     6,     0,     1,     1,     3,
       0,     4,     0,     4,     0,     1,     1,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     0,     4,     1,     1,
       3,     3,     0,     6,     0,     1,     1,     3,     0,     4,
       0,     4,     1,     3,     1,     1,     1,     1,     1,     0,
       4,     0,     4,     0,     4,     0,     6,     0,     1,     1,
       3,     0,     4,     0,     4,     1,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     0,     4,     3,     0,
       4,     3,     3,     0,     6,     0,     1,     1,     3,     0,
       4,     0,     4,     0,     1,     1,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     0,     4,     0,     4,
       0,     4,     0,     4,     0,     4,     0,     4,     0,     4,
       0,     6,     0,     4,     0,     6,     1,     3,     0,     4,
       0,     1,     1,     3,     1,     1,     1,     1,     1,     0,
       4,     0,     6,     1,     3,     1,     1,     1,     1,     1,
       1,     1,     0,     4,     1,     1,     1,     3,     0,     4,
       3,     3,     3,     0,     6,     1,     3,     1,     1,     0,
       4,     0,     4,     0,     6,     0,     4,     1,     3,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     3,     0,     4,     0,     4,     3,
       0,     4,     3,     3,     0,     4,     1,     1,     0,     4,
       3,     3,     3,     0,     4,     1,     1,     1,     1,     1,
       0,     4,     0,     4,     0,     4,     0,     4,     0,     6,
       1,     3,     1,     0,     6,     1,     3,     0,     4,     1,
       3,     1,     1,     1,     1,     1,     3,     0,     4,     0,
       6,     1,     3,     0,     4,     1,     3,     1,     1,     1,
       1,     0,     4,     3,     3,     3
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
  "\"user-context\"", "\"comment\"", "\"subnet\"", "\"interface\"",
  "\"interface-id\"", "\"id\"", "\"rapid-commit\"", "\"reservation-mode\"",
  "\"disabled\"", "\"out-of-pool\"", "\"all\"", "\"shared-networks\"",
  "\"mac-sources\"", "\"relay-supplied-options\"",
  "\"host-reservation-identifiers\"", "\"client-classes\"", "\"test\"",
  "\"client-class\"", "\"reservations\"", "\"ip-addresses\"",
  "\"prefixes\"", "\"duid\"", "\"hw-address\"", "\"hostname\"",
  "\"flex-id\"", "\"relay\"", "\"ip-address\"", "\"hooks-libraries\"",
  "\"library\"", "\"parameters\"", "\"expired-leases-processing\"",
  "\"reclaim-timer-wait-time\"", "\"flush-reclaimed-timer-wait-time\"",
  "\"hold-reclaimed-time\"", "\"max-reclaim-leases\"",
  "\"max-reclaim-time\"", "\"unwarned-reclaim-cycles\"", "\"server-id\"",
  "\"LLT\"", "\"EN\"", "\"LL\"", "\"identifier\"", "\"htype\"", "\"time\"",
  "\"enterprise-id\"", "\"dhcp4o6-port\"", "\"control-socket\"",
  "\"socket-type\"", "\"socket-name\"", "\"dhcp-ddns\"",
  "\"enable-updates\"", "\"qualifying-suffix\"", "\"server-ip\"",
  "\"server-port\"", "\"sender-ip\"", "\"sender-port\"",
  "\"max-queue-size\"", "\"ncr-protocol\"", "\"ncr-format\"",
  "\"always-include-fqdn\"", "\"override-no-update\"",
  "\"override-client-update\"", "\"replace-client-name\"",
  "\"generated-prefix\"", "\"UDP\"", "\"TCP\"", "\"JSON\"",
  "\"when-present\"", "\"never\"", "\"always\"", "\"when-not-present\"",
  "\"Logging\"", "\"loggers\"", "\"output_options\"", "\"output\"",
  "\"debuglevel\"", "\"severity\"", "\"flush\"", "\"maxsize\"",
  "\"maxver\"", "\"Dhcp4\"", "\"DhcpDdns\"", "\"Control-agent\"",
  "TOPLEVEL_JSON", "TOPLEVEL_DHCP6", "SUB_DHCP6", "SUB_INTERFACES6",
  "SUB_SUBNET6", "SUB_POOL6", "SUB_PD_POOL", "SUB_RESERVATION",
  "SUB_OPTION_DEFS", "SUB_OPTION_DEF", "SUB_OPTION_DATA",
  "SUB_HOOKS_LIBRARY", "SUB_DHCP_DDNS", "\"constant string\"",
  "\"integer\"", "\"floating point\"", "\"boolean\"", "$accept", "start",
  "$@1", "$@2", "$@3", "$@4", "$@5", "$@6", "$@7", "$@8", "$@9", "$@10",
  "$@11", "$@12", "$@13", "value", "sub_json", "map2", "$@14", "map_value",
  "map_content", "not_empty_map", "list_generic", "$@15", "list_content",
  "not_empty_list", "list_strings", "$@16", "list_strings_content",
  "not_empty_list_strings", "unknown_map_entry", "syntax_map", "$@17",
  "global_objects", "global_object", "dhcp6_object", "$@18", "sub_dhcp6",
  "$@19", "global_params", "global_param", "preferred_lifetime",
  "valid_lifetime", "renew_timer", "rebind_timer",
  "decline_probation_period", "interfaces_config", "$@20",
  "sub_interfaces6", "$@21", "interfaces_config_params",
  "interfaces_config_param", "interfaces_list", "$@22", "re_detect",
  "lease_database", "$@23", "hosts_database", "$@24",
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
  "$@67", "comment", "$@68", "pd_pools_list", "$@69",
  "pd_pools_list_content", "not_empty_pd_pools_list", "pd_pool_entry",
  "$@70", "sub_pd_pool", "$@71", "pd_pool_params", "pd_pool_param",
  "pd_prefix", "$@72", "pd_prefix_len", "excluded_prefix", "$@73",
  "excluded_prefix_len", "pd_delegated_len", "reservations", "$@74",
  "reservations_list", "not_empty_reservations_list", "reservation",
  "$@75", "sub_reservation", "$@76", "reservation_params",
  "not_empty_reservation_params", "reservation_param", "ip_addresses",
  "$@77", "prefixes", "$@78", "duid", "$@79", "hw_address", "$@80",
  "hostname", "$@81", "flex_id_value", "$@82",
  "reservation_client_classes", "$@83", "relay", "$@84", "relay_map",
  "$@85", "client_classes", "$@86", "client_classes_list", "$@87",
  "client_class_params", "not_empty_client_class_params",
  "client_class_param", "client_class_name", "client_class_test", "$@88",
  "server_id", "$@89", "server_id_params", "server_id_param",
  "server_id_type", "$@90", "duid_type", "htype", "identifier", "$@91",
  "time", "enterprise_id", "dhcp4o6_port", "control_socket", "$@92",
  "control_socket_params", "control_socket_param", "socket_type", "$@93",
  "socket_name", "$@94", "dhcp_ddns", "$@95", "sub_dhcp_ddns", "$@96",
  "dhcp_ddns_params", "dhcp_ddns_param", "enable_updates",
  "qualifying_suffix", "$@97", "server_ip", "$@98", "server_port",
  "sender_ip", "$@99", "sender_port", "max_queue_size", "ncr_protocol",
  "$@100", "ncr_protocol_value", "ncr_format", "$@101",
  "always_include_fqdn", "override_no_update", "override_client_update",
  "replace_client_name", "$@102", "replace_client_name_value",
  "generated_prefix", "$@103", "dhcp4_json_object", "$@104",
  "dhcpddns_json_object", "$@105", "control_agent_json_object", "$@106",
  "logging_object", "$@107", "logging_params", "logging_param", "loggers",
  "$@108", "loggers_entries", "logger_entry", "$@109", "logger_params",
  "logger_param", "debuglevel", "severity", "$@110", "output_options_list",
  "$@111", "output_options_list_content", "output_entry", "$@112",
  "output_params_list", "output_params", "output", "$@113", "flush",
  "maxsize", "maxver", YY_NULLPTR
  };

#if PARSER6_DEBUG
  const unsigned short int
  Dhcp6Parser::yyrline_[] =
  {
       0,   237,   237,   237,   238,   238,   239,   239,   240,   240,
     241,   241,   242,   242,   243,   243,   244,   244,   245,   245,
     246,   246,   247,   247,   248,   248,   249,   249,   257,   258,
     259,   260,   261,   262,   263,   266,   271,   271,   282,   285,
     286,   289,   293,   300,   300,   307,   308,   311,   315,   322,
     322,   329,   330,   333,   337,   348,   358,   358,   373,   374,
     378,   379,   380,   381,   382,   383,   386,   386,   401,   401,
     410,   411,   416,   417,   418,   419,   420,   421,   422,   423,
     424,   425,   426,   427,   428,   429,   430,   431,   432,   433,
     434,   435,   436,   437,   438,   441,   446,   451,   456,   461,
     466,   466,   477,   477,   486,   487,   490,   491,   494,   494,
     504,   510,   510,   522,   522,   534,   535,   538,   539,   540,
     541,   542,   543,   544,   545,   546,   547,   548,   549,   550,
     553,   553,   560,   561,   562,   563,   566,   566,   574,   574,
     582,   582,   590,   595,   595,   603,   608,   613,   618,   623,
     623,   631,   631,   640,   640,   650,   651,   654,   655,   658,
     663,   668,   668,   678,   679,   682,   683,   684,   687,   692,
     699,   699,   709,   709,   719,   720,   723,   724,   727,   727,
     737,   737,   747,   748,   749,   752,   753,   756,   756,   764,
     764,   772,   772,   783,   784,   787,   788,   789,   790,   791,
     792,   795,   800,   805,   810,   815,   820,   828,   828,   841,
     842,   845,   846,   853,   853,   879,   879,   890,   891,   895,
     896,   897,   898,   899,   900,   901,   902,   903,   904,   905,
     906,   907,   908,   909,   910,   911,   912,   913,   916,   916,
     924,   924,   932,   932,   940,   940,   948,   948,   955,   956,
     957,   960,   965,   973,   973,   984,   985,   989,   990,   993,
     993,  1001,  1002,  1005,  1006,  1007,  1008,  1009,  1010,  1011,
    1012,  1013,  1014,  1015,  1016,  1017,  1018,  1025,  1025,  1038,
    1038,  1047,  1048,  1051,  1052,  1057,  1057,  1072,  1072,  1086,
    1087,  1090,  1091,  1094,  1095,  1096,  1097,  1098,  1099,  1100,
    1101,  1104,  1106,  1111,  1113,  1113,  1121,  1121,  1129,  1129,
    1137,  1139,  1139,  1147,  1156,  1156,  1168,  1169,  1174,  1175,
    1180,  1180,  1192,  1192,  1204,  1205,  1210,  1211,  1216,  1217,
    1218,  1219,  1220,  1221,  1222,  1225,  1227,  1227,  1235,  1237,
    1239,  1244,  1252,  1252,  1264,  1265,  1268,  1269,  1272,  1272,
    1282,  1282,  1291,  1292,  1295,  1296,  1297,  1298,  1299,  1302,
    1302,  1310,  1310,  1317,  1317,  1329,  1329,  1341,  1342,  1345,
    1346,  1349,  1349,  1361,  1361,  1373,  1374,  1377,  1378,  1379,
    1380,  1381,  1382,  1383,  1384,  1385,  1388,  1388,  1396,  1401,
    1401,  1409,  1414,  1422,  1422,  1432,  1433,  1436,  1437,  1440,
    1440,  1449,  1449,  1458,  1459,  1462,  1463,  1467,  1468,  1469,
    1470,  1471,  1472,  1473,  1474,  1475,  1478,  1478,  1488,  1488,
    1498,  1498,  1506,  1506,  1514,  1514,  1522,  1522,  1530,  1530,
    1543,  1543,  1553,  1553,  1564,  1564,  1574,  1575,  1578,  1578,
    1588,  1589,  1592,  1593,  1596,  1597,  1598,  1599,  1602,  1604,
    1604,  1615,  1615,  1627,  1628,  1631,  1632,  1633,  1634,  1635,
    1636,  1637,  1640,  1640,  1647,  1648,  1649,  1652,  1657,  1657,
    1665,  1670,  1677,  1684,  1684,  1694,  1695,  1698,  1699,  1702,
    1702,  1710,  1710,  1720,  1720,  1732,  1732,  1742,  1743,  1746,
    1747,  1748,  1749,  1750,  1751,  1752,  1753,  1754,  1755,  1756,
    1757,  1758,  1759,  1760,  1763,  1768,  1768,  1776,  1776,  1784,
    1789,  1789,  1797,  1802,  1807,  1807,  1815,  1816,  1819,  1819,
    1827,  1832,  1837,  1842,  1842,  1850,  1853,  1856,  1859,  1862,
    1868,  1868,  1878,  1878,  1885,  1885,  1892,  1892,  1905,  1905,
    1918,  1919,  1923,  1927,  1927,  1939,  1940,  1944,  1944,  1952,
    1953,  1956,  1957,  1958,  1959,  1960,  1963,  1968,  1968,  1976,
    1976,  1986,  1987,  1990,  1990,  1998,  1999,  2002,  2003,  2004,
    2005,  2008,  2008,  2016,  2021,  2026
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
#line 4493 "dhcp6_parser.cc" // lalr1.cc:1167
#line 2031 "dhcp6_parser.yy" // lalr1.cc:1168


void
isc::dhcp::Dhcp6Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
