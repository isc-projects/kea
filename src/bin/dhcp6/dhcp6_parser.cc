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

  case 97:
#line 443 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("preferred-lifetime", prf);
}
#line 1005 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 98:
#line 448 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 1014 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 99:
#line 453 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 1023 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 100:
#line 458 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 1032 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 101:
#line 463 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr dpp(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 1041 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 102:
#line 468 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces-config", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.INTERFACES_CONFIG);
}
#line 1052 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 103:
#line 473 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // No interfaces config param is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1062 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 104:
#line 479 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1072 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 105:
#line 483 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // No interfaces config param is required
    // parsing completed
}
#line 1081 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 113:
#line 499 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1092 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 114:
#line 504 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1101 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 115:
#line 509 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("re-detect", b);
}
#line 1110 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 116:
#line 515 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lease-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.LEASE_DATABASE);
}
#line 1121 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 117:
#line 520 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1132 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 118:
#line 527 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1143 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 119:
#line 532 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1154 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 137:
#line 560 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.DATABASE_TYPE);
}
#line 1162 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 138:
#line 562 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("type", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1171 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 139:
#line 567 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("memfile", ctx.loc2pos(yystack_[0].location))); }
#line 1177 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 140:
#line 568 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("mysql", ctx.loc2pos(yystack_[0].location))); }
#line 1183 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 141:
#line 569 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("postgresql", ctx.loc2pos(yystack_[0].location))); }
#line 1189 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 142:
#line 570 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("cql", ctx.loc2pos(yystack_[0].location))); }
#line 1195 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 143:
#line 573 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1203 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 144:
#line 575 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr user(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1213 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 145:
#line 581 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1221 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 146:
#line 583 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr pwd(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 1231 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 147:
#line 589 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1239 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 148:
#line 591 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr h(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 1249 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 149:
#line 597 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr p(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", p);
}
#line 1258 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 150:
#line 602 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1266 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 151:
#line 604 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1276 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 152:
#line 610 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 1285 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 153:
#line 615 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 1294 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 154:
#line 620 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 1303 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 155:
#line 625 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("connect-timeout", n);
}
#line 1312 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 156:
#line 630 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1320 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 157:
#line 632 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr cp(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("contact-points", cp);
    ctx.leave();
}
#line 1330 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 158:
#line 638 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1338 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 159:
#line 640 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr ks(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("keyspace", ks);
    ctx.leave();
}
#line 1348 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 160:
#line 647 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("mac-sources", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.MAC_SOURCES);
}
#line 1359 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 161:
#line 652 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1368 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 166:
#line 665 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1377 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 167:
#line 670 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr duid(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1386 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 168:
#line 675 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 1397 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 169:
#line 680 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1406 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 175:
#line 694 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 1415 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 176:
#line 699 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr flex_id(new StringElement("flex-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(flex_id);
}
#line 1424 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 177:
#line 706 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay-supplied-options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1435 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 178:
#line 711 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1444 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 179:
#line 716 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 1455 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 180:
#line 721 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1464 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 185:
#line 734 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1474 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 186:
#line 738 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1484 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 187:
#line 744 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1494 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 188:
#line 748 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 1504 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 194:
#line 763 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1512 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 195:
#line 765 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr lib(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 1522 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 196:
#line 771 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1530 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 197:
#line 773 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1539 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 198:
#line 779 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.EXPIRED_LEASES_PROCESSING);
}
#line 1550 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 199:
#line 784 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // No expired lease parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1560 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 208:
#line 802 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 1569 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 209:
#line 807 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 1578 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 210:
#line 812 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 1587 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 211:
#line 817 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 1596 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 212:
#line 822 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 1605 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 213:
#line 827 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 1614 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 214:
#line 835 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet6", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET6);
}
#line 1625 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 215:
#line 840 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1634 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 220:
#line 860 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1644 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 221:
#line 864 "dhcp6_parser.yy" // lalr1.cc:859
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

  case 222:
#line 886 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the subnet6 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1680 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 223:
#line 890 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The subnet subnet6 parameter is required
    ctx.require("subnet", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 1690 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 245:
#line 923 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1698 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 246:
#line 925 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr subnet(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 1708 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 247:
#line 931 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1716 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 248:
#line 933 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 1726 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 249:
#line 939 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1734 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 250:
#line 941 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface-id", iface);
    ctx.leave();
}
#line 1744 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 251:
#line 947 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.CLIENT_CLASS);
}
#line 1752 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 252:
#line 949 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr cls(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 1762 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 253:
#line 955 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.RESERVATION_MODE);
}
#line 1770 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 254:
#line 957 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("reservation-mode", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1779 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 255:
#line 962 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("disabled", ctx.loc2pos(yystack_[0].location))); }
#line 1785 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 256:
#line 963 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("out-of-pool", ctx.loc2pos(yystack_[0].location))); }
#line 1791 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 257:
#line 964 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("all", ctx.loc2pos(yystack_[0].location))); }
#line 1797 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 258:
#line 967 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr id(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 1806 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 259:
#line 972 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr rc(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rapid-commit", rc);
}
#line 1815 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 260:
#line 980 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("shared-networks", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SHARED_NETWORK);
}
#line 1826 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 261:
#line 985 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1835 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 266:
#line 1000 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1845 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 267:
#line 1004 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1853 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 286:
#line 1034 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 1864 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 287:
#line 1039 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1873 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 288:
#line 1047 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1882 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 289:
#line 1050 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1890 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 294:
#line 1066 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1900 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 295:
#line 1070 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1912 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 296:
#line 1081 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1922 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 297:
#line 1085 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 1934 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 313:
#line 1117 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr code(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 1943 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 315:
#line 1124 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1951 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 316:
#line 1126 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 1961 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 317:
#line 1132 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1969 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 318:
#line 1134 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 1979 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 319:
#line 1140 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1987 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 320:
#line 1142 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr space(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 1997 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 322:
#line 1150 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2005 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 323:
#line 1152 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr encap(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 2015 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 324:
#line 1158 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr array(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 2024 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 325:
#line 1167 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 2035 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 326:
#line 1172 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2044 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 331:
#line 1191 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2054 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 332:
#line 1195 "dhcp6_parser.yy" // lalr1.cc:859
    {
    /// @todo: the code or name parameters are required.
    ctx.stack_.pop_back();
}
#line 2063 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 333:
#line 1203 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2073 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 334:
#line 1207 "dhcp6_parser.yy" // lalr1.cc:859
    {
    /// @todo: the code or name parameters are required.
    // parsing completed
}
#line 2082 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 349:
#line 1240 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2090 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 350:
#line 1242 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr data(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 2100 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 353:
#line 1252 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr space(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", space);
}
#line 2109 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 354:
#line 1257 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr persist(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-send", persist);
}
#line 2118 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 355:
#line 1265 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 2129 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 356:
#line 1270 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2138 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 361:
#line 1285 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2148 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 362:
#line 1289 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2158 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 363:
#line 1295 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2168 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 364:
#line 1299 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
}
#line 2177 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 372:
#line 1315 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2185 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 373:
#line 1317 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr pool(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 2195 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 374:
#line 1323 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2203 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 375:
#line 1325 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->combine_set("user-context", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2212 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 376:
#line 1330 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2220 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 377:
#line 1332 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr e(new MapElement(ctx.loc2pos(yystack_[3].location)));
    e->set("comment", yystack_[0].value.as< ElementPtr > ());
    ctx.stack_.back()->combine_set("user-context", e);
    ctx.leave();
}
#line 2231 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 378:
#line 1342 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pd-pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.PD_POOLS);
}
#line 2242 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 379:
#line 1347 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2251 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 384:
#line 1362 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2261 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 385:
#line 1366 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The prefix, prefix len and delegated len parameters are required.
    ctx.require("prefix", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("prefix-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("delegated-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2273 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 386:
#line 1374 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the pd-pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2283 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 387:
#line 1378 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The prefix, prefix len and delegated len parameters are required.
    ctx.require("prefix", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("prefix-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("delegated-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2295 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 399:
#line 1401 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2303 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 400:
#line 1403 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix", prf);
    ctx.leave();
}
#line 2313 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 401:
#line 1409 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix-len", prf);
}
#line 2322 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 402:
#line 1414 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2330 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 403:
#line 1416 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix", prf);
    ctx.leave();
}
#line 2340 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 404:
#line 1422 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix-len", prf);
}
#line 2349 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 405:
#line 1427 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr deleg(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("delegated-len", deleg);
}
#line 2358 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 406:
#line 1435 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 2369 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 407:
#line 1440 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2378 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 412:
#line 1453 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2388 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 413:
#line 1457 "dhcp6_parser.yy" // lalr1.cc:859
    {
    /// @todo: an identifier parameter is required.
    ctx.stack_.pop_back();
}
#line 2397 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 414:
#line 1462 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2407 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 415:
#line 1466 "dhcp6_parser.yy" // lalr1.cc:859
    {
    /// @todo: an identifier parameter is required.
    // parsing completed
}
#line 2416 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 431:
#line 1493 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-addresses", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2427 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 432:
#line 1498 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2436 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 433:
#line 1503 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefixes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2447 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 434:
#line 1508 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2456 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 435:
#line 1513 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2464 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 436:
#line 1515 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr d(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 2474 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 437:
#line 1521 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2482 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 438:
#line 1523 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 2492 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 439:
#line 1529 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2500 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 440:
#line 1531 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr host(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 2510 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 441:
#line 1537 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2518 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 442:
#line 1539 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flex-id", hw);
    ctx.leave();
}
#line 2528 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 443:
#line 1545 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2539 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 444:
#line 1550 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2548 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 445:
#line 1558 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 2559 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 446:
#line 1563 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2568 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 447:
#line 1568 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2576 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 448:
#line 1570 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr ip(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", ip);
    ctx.leave();
}
#line 2586 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 449:
#line 1579 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 2597 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 450:
#line 1584 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2606 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 453:
#line 1593 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2616 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 454:
#line 1597 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The name client class parameter is required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2626 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 466:
#line 1621 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2634 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 467:
#line 1623 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr test(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 2644 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 468:
#line 1632 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-id", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SERVER_ID);
}
#line 2655 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 469:
#line 1637 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The type parameter is required.
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2666 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 481:
#line 1659 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.DUID_TYPE);
}
#line 2674 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 482:
#line 1661 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("type", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2683 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 483:
#line 1666 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("LLT", ctx.loc2pos(yystack_[0].location))); }
#line 2689 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 484:
#line 1667 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("EN", ctx.loc2pos(yystack_[0].location))); }
#line 2695 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 485:
#line 1668 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("LL", ctx.loc2pos(yystack_[0].location))); }
#line 2701 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 486:
#line 1671 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr htype(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("htype", htype);
}
#line 2710 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 487:
#line 1676 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2718 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 488:
#line 1678 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr id(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("identifier", id);
    ctx.leave();
}
#line 2728 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 489:
#line 1684 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("time", time);
}
#line 2737 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 490:
#line 1689 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enterprise-id", time);
}
#line 2746 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 491:
#line 1696 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 2755 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 492:
#line 1703 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 2766 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 493:
#line 1708 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2775 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 498:
#line 1721 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2783 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 499:
#line 1723 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr stype(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 2793 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 500:
#line 1729 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2801 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 501:
#line 1731 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 2811 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 502:
#line 1739 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 2822 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 503:
#line 1744 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2833 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 504:
#line 1751 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2843 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 505:
#line 1755 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2853 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 525:
#line 1784 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 2862 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 526:
#line 1789 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2870 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 527:
#line 1791 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("qualifying-suffix", s);
    ctx.leave();
}
#line 2880 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 528:
#line 1797 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2888 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 529:
#line 1799 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 2898 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 530:
#line 1805 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 2907 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 531:
#line 1810 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2915 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 532:
#line 1812 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 2925 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 533:
#line 1818 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 2934 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 534:
#line 1823 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 2943 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 535:
#line 1828 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 2951 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 536:
#line 1830 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2960 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 537:
#line 1836 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 2966 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 538:
#line 1837 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 2972 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 539:
#line 1840 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NCR_FORMAT);
}
#line 2980 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 540:
#line 1842 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 2990 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 541:
#line 1848 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-include-fqdn", b);
}
#line 2999 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 542:
#line 1853 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-no-update", b);
}
#line 3008 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 543:
#line 1858 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-client-update", b);
}
#line 3017 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 544:
#line 1863 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 3025 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 545:
#line 1865 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("replace-client-name", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3034 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 546:
#line 1871 "dhcp6_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("when-present", ctx.loc2pos(yystack_[0].location))); 
      }
#line 3042 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 547:
#line 1874 "dhcp6_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location)));
      }
#line 3050 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 548:
#line 1877 "dhcp6_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("always", ctx.loc2pos(yystack_[0].location)));
      }
#line 3058 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 549:
#line 1880 "dhcp6_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("when-not-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 3066 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 550:
#line 1883 "dhcp6_parser.yy" // lalr1.cc:859
    {
      error(yystack_[0].location, "boolean values for the replace-client-name are "
                "no longer supported");
      }
#line 3075 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 551:
#line 1889 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3083 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 552:
#line 1891 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("generated-prefix", s);
    ctx.leave();
}
#line 3093 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 553:
#line 1899 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3101 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 554:
#line 1901 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("Dhcp4", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3110 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 555:
#line 1906 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3118 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 556:
#line 1908 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("DhcpDdns", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3127 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 557:
#line 1913 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3135 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 558:
#line 1915 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("Control-agent", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3144 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 559:
#line 1926 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Logging", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.LOGGING);
}
#line 3155 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 560:
#line 1931 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3164 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 564:
#line 1948 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 3175 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 565:
#line 1953 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3184 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 568:
#line 1965 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 3194 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 569:
#line 1969 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 3202 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 579:
#line 1986 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr dl(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 3211 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 580:
#line 1991 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3219 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 581:
#line 1993 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 3229 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 582:
#line 1999 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 3240 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 583:
#line 2004 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3249 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 586:
#line 2013 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3259 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 587:
#line 2017 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 3267 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 594:
#line 2031 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3275 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 595:
#line 2033 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 3285 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 596:
#line 2039 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr flush(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 3294 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 597:
#line 2044 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr maxsize(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 3303 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 598:
#line 2049 "dhcp6_parser.yy" // lalr1.cc:859
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


  const short int Dhcp6Parser::yypact_ninf_ = -729;

  const signed char Dhcp6Parser::yytable_ninf_ = -1;

  const short int
  Dhcp6Parser::yypact_[] =
  {
     264,  -729,  -729,  -729,  -729,  -729,  -729,  -729,  -729,  -729,
    -729,  -729,  -729,  -729,    25,    15,    20,    22,    69,    71,
      73,    77,    94,   110,   117,   193,   199,   221,  -729,  -729,
    -729,  -729,  -729,  -729,  -729,  -729,  -729,  -729,  -729,  -729,
    -729,  -729,  -729,  -729,  -729,  -729,  -729,  -729,  -729,  -729,
    -729,  -729,  -729,  -729,  -729,  -729,  -729,  -729,  -729,  -729,
    -729,  -729,  -729,  -729,    15,   -15,    13,   121,    29,    33,
     164,   142,   315,   203,    12,   227,   -10,   340,  -729,   270,
     275,   296,   298,   305,  -729,  -729,  -729,  -729,  -729,   316,
    -729,    74,  -729,  -729,  -729,  -729,  -729,  -729,  -729,  -729,
    -729,   320,   328,   329,   335,   336,  -729,  -729,  -729,  -729,
    -729,  -729,  -729,  -729,  -729,  -729,  -729,  -729,  -729,   337,
    -729,  -729,  -729,   100,  -729,  -729,  -729,  -729,  -729,  -729,
    -729,  -729,  -729,  -729,  -729,  -729,  -729,  -729,  -729,  -729,
    -729,  -729,  -729,  -729,  -729,  -729,  -729,  -729,  -729,  -729,
     343,  -729,   113,  -729,  -729,  -729,  -729,  -729,  -729,  -729,
    -729,  -729,  -729,  -729,   345,   358,  -729,  -729,  -729,  -729,
    -729,  -729,  -729,  -729,  -729,   130,  -729,  -729,  -729,  -729,
    -729,  -729,  -729,  -729,  -729,  -729,  -729,  -729,  -729,  -729,
    -729,  -729,  -729,  -729,   140,  -729,  -729,  -729,  -729,  -729,
     362,  -729,   365,   369,  -729,  -729,  -729,  -729,   216,  -729,
    -729,  -729,  -729,  -729,  -729,  -729,  -729,  -729,  -729,  -729,
    -729,  -729,  -729,  -729,  -729,  -729,   367,   373,  -729,  -729,
    -729,  -729,  -729,  -729,  -729,  -729,   372,  -729,  -729,   377,
    -729,  -729,  -729,   378,  -729,  -729,   379,   382,  -729,  -729,
    -729,  -729,  -729,  -729,  -729,  -729,  -729,  -729,  -729,  -729,
    -729,   384,   396,  -729,  -729,  -729,  -729,   409,   417,  -729,
    -729,  -729,  -729,  -729,  -729,  -729,  -729,  -729,  -729,  -729,
    -729,   224,  -729,  -729,  -729,   418,  -729,  -729,   419,  -729,
     420,   421,  -729,  -729,   425,   426,   427,  -729,  -729,  -729,
    -729,  -729,   228,  -729,  -729,  -729,  -729,  -729,  -729,  -729,
    -729,  -729,  -729,  -729,  -729,  -729,  -729,  -729,  -729,    15,
      15,  -729,   280,   429,   430,   431,   432,   433,  -729,    13,
    -729,   434,   436,   437,   268,   290,   291,   292,   307,   457,
     458,   459,   460,   461,   462,   464,   465,   466,   467,   468,
     469,   470,   325,   475,   478,   121,  -729,   479,   330,    29,
    -729,   173,   480,   482,   483,   484,   485,   341,   342,   486,
     491,   492,   495,    33,  -729,   496,   164,  -729,   497,   353,
     503,   355,   356,   142,  -729,   507,   508,   509,   510,   511,
     516,   518,  -729,   315,  -729,   519,   520,   375,   521,   525,
     526,   376,  -729,    12,   529,   380,   381,  -729,   227,   533,
     534,   132,  -729,   385,   537,   538,   390,   540,   392,   393,
     543,   544,   394,   395,   397,   547,   549,   340,  -729,  -729,
    -729,   550,   551,   552,    15,    15,    15,  -729,   553,   554,
     555,  -729,  -729,  -729,  -729,  -729,   558,   559,   560,   561,
      15,   562,   564,   565,   566,   567,   568,   569,   570,  -729,
     571,   572,  -729,   575,  -729,  -729,  -729,  -729,  -729,  -729,
    -729,  -729,   548,   563,  -729,  -729,  -729,   576,   577,   405,
     422,   423,  -729,  -729,    80,   435,   578,   579,  -729,   438,
    -729,   439,  -729,   440,  -729,  -729,  -729,   575,   575,   575,
     441,   442,   443,   444,  -729,   445,   446,  -729,   447,   448,
     449,  -729,  -729,   450,  -729,  -729,  -729,   451,    15,  -729,
    -729,   452,   453,  -729,   454,  -729,  -729,   138,   463,  -729,
    -729,  -729,   -14,   455,  -729,    15,   121,   456,  -729,  -729,
    -729,    29,   225,   225,   581,   582,   601,  -729,  -729,  -729,
     602,   -39,    15,   321,    14,   603,    84,    63,   185,   340,
    -729,  -729,   607,  -729,   173,   605,   606,  -729,  -729,  -729,
    -729,  -729,  -729,  -729,  -729,   608,   532,  -729,  -729,  -729,
    -729,  -729,  -729,  -729,  -729,  -729,  -729,  -729,  -729,  -729,
    -729,  -729,  -729,  -729,  -729,  -729,  -729,  -729,  -729,  -729,
    -729,  -729,  -729,  -729,  -729,  -729,  -729,  -729,  -729,  -729,
     231,  -729,   234,  -729,  -729,   235,  -729,  -729,  -729,  -729,
     612,   613,   614,   615,   616,  -729,  -729,  -729,   253,  -729,
    -729,  -729,  -729,  -729,  -729,  -729,  -729,  -729,  -729,  -729,
    -729,  -729,  -729,  -729,   254,  -729,   617,   618,  -729,  -729,
     619,   621,  -729,  -729,   620,   624,  -729,  -729,   622,   626,
    -729,  -729,  -729,   112,  -729,  -729,  -729,   625,  -729,  -729,
    -729,   124,  -729,  -729,  -729,  -729,   128,  -729,   627,   629,
    -729,   630,   631,   632,   633,   634,   635,   257,  -729,  -729,
    -729,  -729,  -729,  -729,  -729,  -729,  -729,   636,   637,   638,
    -729,  -729,  -729,  -729,   269,  -729,  -729,  -729,  -729,  -729,
    -729,  -729,  -729,   271,  -729,  -729,  -729,   272,   493,   494,
    -729,  -729,   641,   640,  -729,  -729,   642,   646,  -729,  -729,
     644,   648,  -729,  -729,   645,  -729,   650,   456,  -729,  -729,
     651,   652,   653,   654,   477,   489,   499,   504,   512,   656,
     657,   225,  -729,  -729,    33,  -729,   581,    12,  -729,   582,
     227,  -729,   601,    66,  -729,   602,   -39,  -729,  -729,   321,
    -729,    14,  -729,   -10,  -729,   603,   513,   514,   515,   517,
     522,   523,    84,  -729,   658,   659,   524,   527,   528,    63,
    -729,   660,   665,   185,  -729,  -729,  -729,   666,   668,  -729,
     164,  -729,   605,   142,  -729,   606,   315,  -729,   608,   669,
    -729,   673,  -729,   311,   530,   531,   535,  -729,  -729,  -729,
    -729,  -729,   541,   584,  -729,   282,  -729,   671,  -729,   676,
    -729,  -729,  -729,  -729,  -729,  -729,  -729,  -729,  -729,  -729,
    -729,  -729,  -729,   283,  -729,  -729,  -729,  -729,  -729,  -729,
    -729,  -729,  -729,   284,  -729,  -729,  -729,  -729,  -729,  -729,
    -729,  -729,    88,   587,  -729,  -729,  -729,  -729,   589,   590,
    -729,  -729,   591,   293,  -729,   294,  -729,   682,  -729,   592,
     667,  -729,  -729,  -729,  -729,  -729,  -729,  -729,  -729,  -729,
    -729,  -729,  -729,  -729,    66,  -729,  -729,  -729,  -729,  -729,
    -729,  -729,  -729,  -729,  -729,  -729,  -729,  -729,  -729,  -729,
     351,  -729,  -729,   287,   667,  -729,  -729,   688,  -729,  -729,
    -729,  -729,  -729,   295,  -729,  -729,  -729,  -729,  -729,   692,
     557,   700,   287,  -729,   701,  -729,   594,  -729,   698,  -729,
    -729,   357,  -729,    75,   698,  -729,  -729,   710,   711,   713,
     301,  -729,  -729,  -729,  -729,  -729,  -729,   714,   573,   574,
     580,    75,  -729,   595,  -729,  -729,  -729,  -729,  -729
  };

  const unsigned short int
  Dhcp6Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,    24,    26,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     1,    43,
      36,    32,    31,    28,    29,    30,    35,     3,    33,    34,
      56,     5,    68,     7,   104,     9,   222,    11,   363,    13,
     386,    15,   414,    17,   288,    19,   296,    21,   333,    23,
     187,    25,   504,    27,    45,    39,     0,     0,     0,     0,
       0,     0,   416,     0,   298,   335,     0,     0,    47,     0,
      46,     0,     0,    40,    66,   559,   553,   555,   557,     0,
      65,     0,    58,    60,    62,    63,    64,    61,   102,   116,
     118,     0,     0,     0,     0,     0,   214,   286,   325,   374,
     376,   260,   160,   177,   168,   449,   179,   198,   468,     0,
     492,   502,    96,     0,    70,    72,    73,    74,    75,    76,
      79,    80,    81,    82,    84,    83,    88,    89,    77,    78,
      86,    87,    94,    95,    85,    90,    91,    92,    93,   113,
       0,   112,     0,   106,   108,   109,   110,   111,   453,   355,
     378,   245,   247,   249,     0,     0,   253,   251,   406,   445,
     244,   226,   227,   228,   229,     0,   224,   233,   234,   235,
     238,   240,   236,   237,   230,   231,   242,   243,   232,   239,
     241,   372,   371,   368,     0,   365,   367,   369,   370,   399,
       0,   402,     0,     0,   398,   393,   396,   397,     0,   388,
     390,   391,   394,   395,   392,   443,   431,   433,   435,   437,
     439,   441,   430,   427,   428,   429,     0,   417,   418,   422,
     423,   420,   424,   425,   426,   421,     0,   315,   150,     0,
     319,   317,   322,     0,   311,   312,     0,   299,   300,   302,
     314,   303,   304,   305,   321,   306,   307,   308,   309,   310,
     349,     0,     0,   347,   348,   351,   352,     0,   336,   337,
     339,   340,   341,   342,   343,   344,   345,   346,   194,   196,
     191,     0,   189,   192,   193,     0,   526,   528,     0,   531,
       0,     0,   535,   539,     0,     0,     0,   544,   551,   524,
     522,   523,     0,   506,   508,   509,   510,   511,   512,   513,
     514,   515,   516,   517,   518,   519,   520,   521,    44,     0,
       0,    37,     0,     0,     0,     0,     0,     0,    55,     0,
      57,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    69,     0,     0,     0,
     105,   455,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   223,     0,     0,   364,     0,     0,
       0,     0,     0,     0,   387,     0,     0,     0,     0,     0,
       0,     0,   415,     0,   289,     0,     0,     0,     0,     0,
       0,     0,   297,     0,     0,     0,     0,   334,     0,     0,
       0,     0,   188,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   505,    48,
      41,     0,     0,     0,     0,     0,     0,    59,     0,     0,
       0,    97,    98,    99,   100,   101,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   491,
       0,     0,    71,     0,   115,   107,   466,   464,   465,   461,
     462,   463,     0,   456,   457,   459,   460,     0,     0,     0,
       0,     0,   258,   259,     0,     0,     0,     0,   225,     0,
     366,     0,   401,     0,   404,   405,   389,     0,     0,     0,
       0,     0,     0,     0,   419,     0,     0,   313,     0,     0,
       0,   324,   301,     0,   353,   354,   338,     0,     0,   190,
     525,     0,     0,   530,     0,   533,   534,     0,     0,   541,
     542,   543,     0,     0,   507,     0,     0,     0,   554,   556,
     558,     0,     0,     0,   216,   290,   327,    38,   375,   377,
     262,     0,    45,     0,     0,   181,     0,     0,     0,     0,
      49,   114,     0,   454,     0,   357,   380,   246,   248,   250,
     255,   256,   257,   254,   252,   408,     0,   373,   400,   403,
     444,   432,   434,   436,   438,   440,   442,   316,   151,   320,
     318,   323,   350,   195,   197,   527,   529,   532,   537,   538,
     536,   540,   546,   547,   548,   549,   550,   545,   552,    42,
       0,   564,     0,   561,   563,     0,   137,   143,   145,   147,
       0,     0,     0,     0,     0,   156,   158,   136,     0,   120,
     122,   123,   124,   125,   126,   127,   128,   129,   130,   131,
     132,   133,   134,   135,     0,   220,     0,   217,   218,   294,
       0,   291,   292,   331,     0,   328,   329,   266,     0,   263,
     264,   166,   167,     0,   162,   164,   165,     0,   175,   176,
     172,     0,   170,   173,   174,   451,     0,   185,     0,   182,
     183,     0,     0,     0,     0,     0,     0,     0,   200,   202,
     203,   204,   205,   206,   207,   481,   487,     0,     0,     0,
     480,   477,   478,   479,     0,   470,   472,   475,   473,   474,
     476,   498,   500,     0,   494,   496,   497,     0,    51,     0,
     458,   361,     0,   358,   359,   384,     0,   381,   382,   412,
       0,   409,   410,   447,     0,    67,     0,     0,   560,   103,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   117,   119,     0,   215,     0,   298,   287,     0,
     335,   326,     0,     0,   261,     0,     0,   161,   178,     0,
     169,     0,   450,     0,   180,     0,     0,     0,     0,     0,
       0,     0,     0,   199,     0,     0,     0,     0,     0,     0,
     469,     0,     0,     0,   493,   503,    53,     0,    52,   467,
       0,   356,     0,     0,   379,     0,   416,   407,     0,     0,
     446,     0,   562,     0,     0,     0,     0,   149,   152,   153,
     154,   155,     0,     0,   121,     0,   219,     0,   293,     0,
     330,   285,   280,   282,   274,   275,   270,   271,   272,   273,
     279,   278,   281,     0,   268,   276,   283,   284,   277,   265,
     163,   171,   452,     0,   184,   208,   209,   210,   211,   212,
     213,   201,     0,     0,   486,   489,   490,   471,     0,     0,
     495,    50,     0,     0,   360,     0,   383,     0,   411,     0,
       0,   139,   140,   141,   142,   138,   144,   146,   148,   157,
     159,   221,   295,   332,     0,   267,   186,   483,   484,   485,
     482,   488,   499,   501,    54,   362,   385,   413,   448,   568,
       0,   566,   269,     0,     0,   565,   582,     0,   580,   578,
     572,   576,   577,     0,   570,   574,   575,   573,   567,     0,
       0,     0,     0,   569,     0,   579,     0,   571,     0,   581,
     586,     0,   584,     0,     0,   583,   594,     0,     0,     0,
       0,   588,   590,   591,   592,   593,   585,     0,     0,     0,
       0,     0,   587,     0,   596,   597,   598,   589,   595
  };

  const short int
  Dhcp6Parser::yypgoto_[] =
  {
    -729,  -729,  -729,  -729,  -729,  -729,  -729,  -729,  -729,  -729,
    -729,  -729,  -729,  -729,  -729,    -8,  -729,   281,  -729,  -729,
    -729,  -729,  -729,  -729,    70,  -729,  -184,  -729,  -729,  -729,
     -66,  -729,  -729,  -729,   391,  -729,  -729,  -729,  -729,   188,
     366,   -68,   -55,   -54,   -51,  -729,  -729,  -729,  -729,  -729,
     190,   389,  -729,  -729,  -729,  -729,  -729,  -729,  -729,   206,
      -1,  -729,  -729,  -729,  -729,  -729,  -729,  -729,  -729,  -729,
    -729,   -62,  -729,  -545,  -729,  -729,  -729,  -729,  -729,  -729,
    -729,  -729,  -729,  -729,   -13,  -534,  -729,  -729,  -729,  -729,
     -17,  -729,  -729,  -729,  -729,  -729,  -729,  -729,  -729,   -20,
    -729,  -729,  -729,   -16,   347,  -729,  -729,  -729,  -729,  -729,
    -729,  -729,   -26,  -729,  -729,  -729,  -729,  -729,  -729,  -728,
    -729,  -729,  -729,     3,  -729,  -729,  -729,     6,   388,  -729,
    -729,  -715,  -729,  -708,  -729,  -538,  -729,  -707,  -729,  -729,
    -729,  -693,  -729,  -729,  -729,  -729,    -2,  -729,  -729,  -128,
     694,  -729,  -729,  -729,  -729,  -729,    10,  -729,  -729,  -729,
      16,  -729,   368,  -729,   -58,  -729,  -729,  -729,  -729,  -729,
     -49,  -729,  -729,  -729,  -729,  -729,    -9,  -729,  -729,  -729,
       8,  -729,  -729,  -729,    17,  -729,   364,  -729,  -729,  -729,
    -729,  -729,  -729,  -729,  -729,  -729,  -729,  -729,   -28,  -729,
    -729,  -729,   -24,   403,  -729,  -729,   -38,  -729,   -25,  -729,
    -729,  -729,  -729,  -729,   -23,  -729,  -729,  -729,   -19,   400,
    -729,  -729,  -729,  -729,  -729,  -729,  -729,  -729,  -729,  -729,
    -729,   -22,  -729,  -729,  -729,   -21,  -729,   387,  -729,  -729,
    -729,  -729,  -729,  -729,  -729,  -729,  -729,  -729,  -729,  -729,
    -729,  -729,  -691,  -729,  -729,  -729,  -729,  -729,  -729,  -729,
    -729,  -729,   223,  -729,  -729,  -729,  -729,  -729,  -729,     0,
    -729,  -729,  -729,  -729,  -729,  -729,  -729,  -729,  -729,  -729,
    -729,  -729,    -5,  -729,  -729,  -729,  -729,  -729,  -729,  -729,
    -729,   233,   363,  -729,  -729,  -729,  -729,  -729,  -729,  -729,
    -729,  -729,  -729,  -729,  -729,  -729,  -729,  -729,  -729,  -729,
    -729,  -729,  -729,  -729,  -729,  -729,  -729,  -729,  -729,  -729,
    -729,  -729,  -729,  -729,  -729,    56,  -729,  -729,  -729,  -119,
    -729,  -729,  -136,  -729,  -729,  -729,  -729,  -729,  -729,  -146,
    -729,  -729,  -162,  -729,  -729,  -729,  -729,  -729
  };

  const short int
  Dhcp6Parser::yydefgoto_[] =
  {
      -1,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    78,    37,    38,    65,   548,
      82,    83,    39,    64,    79,    80,   561,   718,   797,   798,
     122,    41,    66,    91,    92,    93,   323,    43,    67,   123,
     124,   125,   126,   127,   128,   129,   130,   331,    45,    68,
     152,   153,   154,   357,   155,   131,   332,   132,   333,   628,
     629,   630,   740,   885,   631,   741,   632,   742,   633,   743,
     634,   245,   396,   636,   637,   638,   639,   640,   749,   641,
     750,   133,   345,   663,   664,   665,   666,   134,   347,   671,
     672,   673,   674,   135,   346,   136,   349,   678,   679,   680,
     773,    61,    76,   281,   282,   283,   409,   284,   410,   137,
     350,   687,   688,   689,   690,   691,   692,   693,   694,   138,
     339,   646,   647,   648,   754,    47,    69,   175,   176,   177,
     364,   178,   365,   179,   366,   180,   370,   181,   369,   573,
     182,   183,   139,   344,   658,   659,   660,   763,   843,   844,
     140,   340,    55,    73,   650,   651,   652,   757,    57,    74,
     246,   247,   248,   249,   250,   251,   252,   395,   253,   399,
     254,   398,   255,   256,   400,   257,   141,   341,   654,   655,
     656,   760,    59,    75,   267,   268,   269,   270,   271,   404,
     272,   273,   274,   275,   185,   362,   722,   723,   724,   800,
      49,    70,   194,   195,   196,   375,   142,   342,   143,   343,
     188,   363,   726,   727,   728,   803,    51,    71,   208,   209,
     210,   378,   211,   212,   380,   213,   214,   189,   371,   730,
     731,   732,   806,    53,    72,   226,   227,   228,   229,   386,
     230,   387,   231,   388,   232,   389,   233,   390,   234,   391,
     235,   385,   190,   372,   734,   809,   144,   348,   676,   361,
     472,   473,   474,   475,   476,   562,   145,   351,   704,   705,
     706,   784,   900,   707,   708,   785,   709,   710,   146,   147,
     353,   713,   714,   715,   791,   716,   792,   148,   354,    63,
      77,   302,   303,   304,   305,   414,   306,   415,   307,   308,
     417,   309,   310,   311,   420,   600,   312,   421,   313,   314,
     315,   316,   425,   607,   317,   426,    94,   325,    95,   326,
      96,   327,    97,   324,   612,   613,   614,   736,   910,   911,
     913,   923,   924,   925,   926,   931,   927,   929,   941,   942,
     943,   950,   951,   952,   957,   953,   954,   955
  };

  const unsigned short int
  Dhcp6Parser::yytable_[] =
  {
      90,   171,   151,   170,   192,   204,   222,    36,   244,   263,
     280,   299,   701,   264,   172,   173,   675,   265,   174,   670,
      29,   158,    30,    84,    31,    28,   266,    40,   237,    42,
     156,   186,   197,   206,   224,   837,   258,   276,   661,   300,
     158,   149,   150,   157,   187,   198,   207,   225,   838,   259,
     277,   238,   301,   239,   240,   839,   841,   241,   242,   243,
     184,   193,   205,   223,   101,   102,   103,   104,   109,   110,
     842,   108,   848,   158,   278,   279,    44,   329,    46,   695,
      48,   159,   330,   160,    50,   109,   110,   167,   621,   109,
     110,   161,   162,   163,   164,   165,   166,   101,   102,   103,
     104,    52,   106,   355,   108,   238,   167,   168,   356,   602,
     603,   604,   605,   662,   169,   766,   359,    54,   767,   109,
     110,   360,   109,   110,    56,   162,   163,   769,   165,   166,
     770,   771,    98,   373,   772,    99,   100,    81,   374,   167,
      85,   606,    89,   376,   570,   571,   572,   169,   377,    86,
      87,    88,   101,   102,   103,   104,   105,   106,   107,   108,
     696,   697,   698,   699,    89,    89,   837,    32,    33,    34,
      35,   681,   682,   683,   684,   685,   686,   109,   110,   838,
     108,    89,   897,   898,   899,    89,   839,   841,   111,   112,
     113,   114,   115,   199,   200,   201,   202,   203,   109,   110,
      58,   842,   108,   848,   116,   946,    60,   117,   947,   948,
     949,   108,   238,   191,   118,    89,   278,   279,    89,   383,
     109,   110,   119,   120,   384,   840,   121,   411,    62,   109,
     110,   427,   412,   852,   355,   670,   428,   737,   359,   735,
     107,   616,   738,   739,   701,   466,   617,   618,   619,   620,
     621,   622,   623,   624,   625,   626,   751,   751,   598,   599,
     782,   752,   753,    90,   238,   783,   238,   260,   239,   240,
     261,   262,   789,    89,   793,   427,   318,   790,   319,   794,
     795,   109,   110,   109,   110,   373,   894,   411,   711,   712,
     891,   895,   896,   151,    89,   467,   376,   383,   932,   468,
     320,   905,   906,   933,   961,   171,   321,   170,   322,   962,
     192,   429,   430,   580,   581,   582,    89,   204,   172,   173,
     328,   156,   174,   470,   334,    89,   238,   222,   881,   882,
     883,   884,   335,   336,   157,   186,   471,   244,   197,   337,
     338,   352,   263,   109,   110,   206,   264,   358,   187,   367,
     265,   198,   469,   108,   914,   224,   840,   915,   207,   266,
     944,   299,   368,   945,   184,   258,   379,   193,   225,   381,
     276,   109,   110,   382,   205,   392,   393,    89,   259,    89,
     394,   397,   401,   277,   223,   403,   215,   402,   405,   300,
     216,   217,   218,   219,   220,   221,   109,   110,   661,   668,
     406,   669,   301,     1,     2,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,   916,   407,   917,   918,
     408,   441,   413,   416,   418,   419,   538,   539,   540,   422,
     423,   424,   431,   432,   433,   434,   435,   436,   438,    89,
     439,   440,   549,   442,   443,   444,   285,   286,   287,   288,
     289,   290,   291,   292,   293,   294,   295,   296,   297,   298,
     445,   446,   447,   448,   449,   450,   451,    89,   452,   453,
     454,   455,   456,   457,   458,   151,   627,   627,   459,   460,
     635,   635,   461,   463,   477,   464,   478,   479,   480,   481,
     484,   700,    89,   299,   482,   485,   486,   483,   467,   487,
     489,   491,   468,   156,   642,   642,   492,   493,   494,   495,
     594,   497,   498,   499,   500,   501,   157,   643,   643,   702,
     502,   300,   503,   505,   506,   508,   470,   609,   507,   509,
     510,   511,   703,   513,   301,   514,   515,   517,   518,   471,
     520,   521,   522,   523,   524,   525,   526,   527,   528,   529,
     530,   532,   531,   533,   535,   469,   563,   567,   536,   537,
     541,   542,   543,   544,   545,   546,   564,   550,    30,   551,
     552,   553,   554,   555,   568,   569,   556,   557,   558,   559,
     560,   565,   566,   575,   611,   601,   576,   574,   645,   649,
     577,   578,   579,   583,   584,   585,   586,   587,   588,   589,
     590,   591,   592,   593,   595,   596,   597,   608,   653,   657,
     677,   719,   721,   725,   733,   729,   744,   745,   746,   747,
     748,   756,   667,   755,   759,   758,   761,   762,   764,   765,
     817,   768,   775,   774,   776,   777,   778,   779,   780,   781,
     786,   787,   788,   802,   818,   796,   799,   801,   804,   805,
     807,   808,   819,   810,   811,   813,   814,   815,   816,   820,
     822,   823,   862,   863,   868,   821,   855,   856,   857,   869,
     858,   872,   871,   879,   909,   859,   860,   864,   880,   892,
     865,   866,   886,   887,   893,   627,   171,   888,   170,   635,
     907,   244,   930,   889,   263,   832,   934,   831,   264,   172,
     173,   836,   265,   174,   936,   940,   938,   280,   833,   834,
     935,   266,   835,   642,   958,   959,   186,   960,   963,   258,
     437,   462,   276,   700,   610,   846,   643,   965,   964,   187,
     547,   615,   259,   966,   192,   277,   890,   204,   847,   901,
     222,   902,   903,   904,   908,   184,   939,   968,   465,   644,
     824,   702,   851,   850,   845,   854,   861,   853,   519,   826,
     825,   488,   197,   849,   703,   206,   912,   236,   224,   828,
     830,   512,   516,   827,   874,   198,   873,   829,   207,   490,
     504,   225,   876,   496,   875,   877,   878,   720,   870,   867,
     534,   193,   717,   812,   205,   928,   937,   223,   956,   967,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   832,     0,   831,     0,
       0,     0,   836,     0,     0,     0,     0,     0,     0,   833,
     834,     0,     0,   835,     0,     0,     0,   919,     0,     0,
       0,   920,     0,     0,     0,     0,   846,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   919,     0,     0,   847,
     920,     0,     0,     0,     0,   921,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   845,     0,     0,   922,     0,
       0,     0,     0,     0,   921,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   922
  };

  const short int
  Dhcp6Parser::yycheck_[] =
  {
      66,    69,    68,    69,    70,    71,    72,    15,    74,    75,
      76,    77,   557,    75,    69,    69,   554,    75,    69,   553,
       5,     7,     7,    10,     9,     0,    75,     7,    16,     7,
      68,    69,    70,    71,    72,   763,    74,    75,    77,    77,
       7,    12,    13,    68,    69,    70,    71,    72,   763,    74,
      75,    39,    77,    41,    42,   763,   763,    45,    46,    47,
      69,    70,    71,    72,    31,    32,    33,    34,    56,    57,
     763,    38,   763,     7,    84,    85,     7,     3,     7,    16,
       7,    48,     8,    50,     7,    56,    57,    73,    25,    56,
      57,    58,    59,    60,    61,    62,    63,    31,    32,    33,
      34,     7,    36,     3,    38,    39,    73,    74,     8,   123,
     124,   125,   126,   152,    81,     3,     3,     7,     6,    56,
      57,     8,    56,    57,     7,    59,    60,     3,    62,    63,
       6,     3,    11,     3,     6,    14,    15,   152,     8,    73,
     127,   155,   152,     3,    64,    65,    66,    81,     8,   136,
     137,   138,    31,    32,    33,    34,    35,    36,    37,    38,
      97,    98,    99,   100,   152,   152,   894,   152,   153,   154,
     155,    87,    88,    89,    90,    91,    92,    56,    57,   894,
      38,   152,    94,    95,    96,   152,   894,   894,    67,    68,
      69,    70,    71,    51,    52,    53,    54,    55,    56,    57,
       7,   894,    38,   894,    83,   130,     7,    86,   133,   134,
     135,    38,    39,    49,    93,   152,    84,    85,   152,     3,
      56,    57,   101,   102,     8,   763,   105,     3,     7,    56,
      57,     3,     8,   771,     3,   769,     8,     3,     3,     8,
      37,    16,     8,     8,   789,    72,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,     3,     3,   120,   121,
       3,     8,     8,   329,    39,     8,    39,    40,    41,    42,
      43,    44,     3,   152,     3,     3,     6,     8,     3,     8,
       8,    56,    57,    56,    57,     3,     3,     3,   103,   104,
       8,     8,     8,   359,   152,   361,     3,     3,     3,   361,
       4,     8,     8,     8,     3,   373,     8,   373,     3,     8,
     376,   319,   320,   497,   498,   499,   152,   383,   373,   373,
       4,   359,   373,   361,     4,   152,    39,   393,    17,    18,
      19,    20,     4,     4,   359,   373,   361,   403,   376,     4,
       4,     4,   408,    56,    57,   383,   408,     4,   373,     4,
     408,   376,   361,    38,     3,   393,   894,     6,   383,   408,
       3,   427,     4,     6,   373,   403,     4,   376,   393,     4,
     408,    56,    57,     4,   383,     8,     3,   152,   403,   152,
       8,     4,     4,   408,   393,     3,    71,     8,     4,   427,
      75,    76,    77,    78,    79,    80,    56,    57,    77,    78,
       4,    80,   427,   139,   140,   141,   142,   143,   144,   145,
     146,   147,   148,   149,   150,   151,   129,     8,   131,   132,
       3,   153,     4,     4,     4,     4,   434,   435,   436,     4,
       4,     4,   152,     4,     4,     4,     4,     4,     4,   152,
       4,     4,   450,   153,   153,   153,   106,   107,   108,   109,
     110,   111,   112,   113,   114,   115,   116,   117,   118,   119,
     153,     4,     4,     4,     4,     4,     4,   152,     4,     4,
       4,     4,     4,     4,     4,   541,   542,   543,   153,     4,
     542,   543,     4,     4,     4,   155,     4,     4,     4,     4,
       4,   557,   152,   559,   153,     4,     4,   155,   564,     4,
       4,     4,   564,   541,   542,   543,   153,     4,   153,   153,
     518,     4,     4,     4,     4,     4,   541,   542,   543,   557,
       4,   559,     4,     4,     4,     4,   564,   535,   153,     4,
       4,   155,   557,     4,   559,   155,   155,     4,     4,   564,
     155,     4,     4,   153,     4,   153,   153,     4,     4,   155,
     155,     4,   155,     4,     4,   564,     8,   152,     7,     7,
       7,     7,     7,     5,     5,     5,     3,     5,     7,     5,
       5,     5,     5,     5,   152,   152,     7,     7,     7,     7,
       5,     5,     5,     5,   128,   122,     7,   152,     7,     7,
     152,   152,   152,   152,   152,   152,   152,   152,   152,   152,
     152,   152,   152,   152,   152,   152,   152,   152,     7,     7,
       7,     4,     7,     7,    82,     7,     4,     4,     4,     4,
       4,     3,   552,     6,     3,     6,     6,     3,     6,     3,
     153,     6,     3,     6,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     3,   155,   152,   152,     6,     6,     3,
       6,     3,   153,     8,     4,     4,     4,     4,     4,   155,
       4,     4,     4,     4,     4,   153,   153,   153,   153,     4,
     153,     3,     6,     4,     7,   153,   153,   153,     5,     8,
     153,   153,   152,   152,     8,   751,   754,   152,   754,   751,
       8,   757,     4,   152,   760,   763,     4,   763,   760,   754,
     754,   763,   760,   754,     4,     7,     5,   773,   763,   763,
     153,   760,   763,   751,     4,     4,   754,     4,     4,   757,
     329,   355,   760,   789,   536,   763,   751,   153,   155,   754,
     449,   541,   757,   153,   800,   760,   152,   803,   763,   152,
     806,   152,   152,   152,   152,   754,   152,   152,   359,   543,
     751,   789,   769,   766,   763,   775,   782,   773,   411,   756,
     754,   373,   800,   765,   789,   803,   894,    73,   806,   759,
     762,   403,   408,   757,   802,   800,   800,   760,   803,   376,
     393,   806,   805,   383,   803,   806,   808,   564,   793,   789,
     427,   800,   559,   737,   803,   914,   932,   806,   944,   961,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   894,    -1,   894,    -1,
      -1,    -1,   894,    -1,    -1,    -1,    -1,    -1,    -1,   894,
     894,    -1,    -1,   894,    -1,    -1,    -1,   913,    -1,    -1,
      -1,   913,    -1,    -1,    -1,    -1,   894,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   932,    -1,    -1,   894,
     932,    -1,    -1,    -1,    -1,   913,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   894,    -1,    -1,   913,    -1,
      -1,    -1,    -1,    -1,   932,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   932
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
      15,    31,    32,    33,    34,    35,    36,    37,    38,    56,
      57,    67,    68,    69,    70,    71,    83,    86,    93,   101,
     102,   105,   186,   195,   196,   197,   198,   199,   200,   201,
     202,   211,   213,   237,   243,   249,   251,   265,   275,   298,
     306,   332,   362,   364,   412,   422,   434,   435,   443,    12,
      13,   186,   206,   207,   208,   210,   362,   364,     7,    48,
      50,    58,    59,    60,    61,    62,    63,    73,    74,    81,
     186,   197,   198,   199,   200,   283,   284,   285,   287,   289,
     291,   293,   296,   297,   332,   350,   362,   364,   366,   383,
     408,    49,   186,   332,   358,   359,   360,   362,   364,    51,
      52,    53,    54,    55,   186,   332,   362,   364,   374,   375,
     376,   378,   379,   381,   382,    71,    75,    76,    77,    78,
      79,    80,   186,   332,   362,   364,   391,   392,   393,   394,
     396,   398,   400,   402,   404,   406,   306,    16,    39,    41,
      42,    45,    46,    47,   186,   227,   316,   317,   318,   319,
     320,   321,   322,   324,   326,   328,   329,   331,   362,   364,
      40,    43,    44,   186,   227,   320,   326,   340,   341,   342,
     343,   344,   346,   347,   348,   349,   362,   364,    84,    85,
     186,   259,   260,   261,   263,   106,   107,   108,   109,   110,
     111,   112,   113,   114,   115,   116,   117,   118,   119,   186,
     362,   364,   447,   448,   449,   450,   452,   454,   455,   457,
     458,   459,   462,   464,   465,   466,   467,   470,     6,     3,
       4,     8,     3,   192,   479,   473,   475,   477,     4,     3,
       8,   203,   212,   214,     4,     4,     4,     4,     4,   276,
     307,   333,   363,   365,   299,   238,   250,   244,   413,   252,
     266,   423,     4,   436,   444,     3,     8,   209,     4,     3,
       8,   415,   351,   367,   286,   288,   290,     4,     4,   294,
     292,   384,   409,     3,     8,   361,     3,     8,   377,     4,
     380,     4,     4,     3,     8,   407,   395,   397,   399,   401,
     403,   405,     8,     3,     8,   323,   228,     4,   327,   325,
     330,     4,     8,     3,   345,     4,     4,     8,     3,   262,
     264,     3,     8,     4,   451,   453,     4,   456,     4,     4,
     460,   463,     4,     4,     4,   468,   471,     3,     8,   171,
     171,   152,     4,     4,     4,     4,     4,   190,     4,     4,
       4,   153,   153,   153,   153,   153,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,   153,
       4,     4,   196,     4,   155,   207,    72,   186,   227,   332,
     362,   364,   416,   417,   418,   419,   420,     4,     4,     4,
       4,     4,   153,   155,     4,     4,     4,     4,   284,     4,
     359,     4,   153,     4,   153,   153,   375,     4,     4,     4,
       4,     4,     4,     4,   393,     4,     4,   153,     4,     4,
       4,   155,   318,     4,   155,   155,   342,     4,     4,   260,
     155,     4,     4,   153,     4,   153,   153,     4,     4,   155,
     155,   155,     4,     4,   448,     4,     7,     7,   171,   171,
     171,     7,     7,     7,     5,     5,     5,   173,   175,   171,
       5,     5,     5,     5,     5,     5,     7,     7,     7,     7,
       5,   182,   421,     8,     3,     5,     5,   152,   152,   152,
      64,    65,    66,   295,   152,     5,     7,   152,   152,   152,
     182,   182,   182,   152,   152,   152,   152,   152,   152,   152,
     152,   152,   152,   152,   171,   152,   152,   152,   120,   121,
     461,   122,   123,   124,   125,   126,   155,   469,   152,   171,
     195,   128,   480,   481,   482,   206,    16,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,   186,   215,   216,
     217,   220,   222,   224,   226,   227,   229,   230,   231,   232,
     233,   235,   362,   364,   215,     7,   277,   278,   279,     7,
     310,   311,   312,     7,   334,   335,   336,     7,   300,   301,
     302,    77,   152,   239,   240,   241,   242,   180,    78,    80,
     241,   245,   246,   247,   248,   291,   414,     7,   253,   254,
     255,    87,    88,    89,    90,    91,    92,   267,   268,   269,
     270,   271,   272,   273,   274,    16,    97,    98,    99,   100,
     186,   229,   362,   364,   424,   425,   426,   429,   430,   432,
     433,   103,   104,   437,   438,   439,   441,   447,   183,     4,
     418,     7,   352,   353,   354,     7,   368,   369,   370,     7,
     385,   386,   387,    82,   410,     8,   483,     3,     8,     8,
     218,   221,   223,   225,     4,     4,     4,     4,     4,   234,
     236,     3,     8,     8,   280,     6,     3,   313,     6,     3,
     337,     6,     3,   303,     6,     3,     3,     6,     6,     3,
       6,     3,     6,   256,     6,     3,     4,     4,     4,     4,
       4,     4,     3,     8,   427,   431,     4,     4,     4,     3,
       8,   440,   442,     3,     8,     8,   152,   184,   185,   152,
     355,     6,     3,   371,     6,     3,   388,     6,     3,   411,
       8,     4,   481,     4,     4,     4,     4,   153,   155,   153,
     155,   153,     4,     4,   216,   283,   279,   316,   312,   340,
     336,   186,   197,   198,   199,   200,   227,   275,   287,   289,
     291,   293,   297,   304,   305,   332,   362,   364,   408,   302,
     240,   246,   291,   259,   255,   153,   153,   153,   153,   153,
     153,   268,     4,     4,   153,   153,   153,   425,     4,     4,
     438,     6,     3,   358,   354,   374,   370,   391,   387,     4,
       5,    17,    18,    19,    20,   219,   152,   152,   152,   152,
     152,     8,     8,     8,     3,     8,     8,    94,    95,    96,
     428,   152,   152,   152,   152,     8,     8,     8,   152,     7,
     484,   485,   305,   486,     3,     6,   129,   131,   132,   186,
     227,   362,   364,   487,   488,   489,   490,   492,   485,   493,
       4,   491,     3,     8,     4,   153,     4,   488,     5,   152,
       7,   494,   495,   496,     3,     6,   130,   133,   134,   135,
     497,   498,   499,   501,   502,   503,   495,   500,     4,     4,
       4,     3,     8,     4,   155,   153,   153,   498,   152
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
     196,   196,   196,   196,   196,   196,   196,   197,   198,   199,
     200,   201,   203,   202,   205,   204,   206,   206,   207,   207,
     207,   207,   207,   209,   208,   210,   212,   211,   214,   213,
     215,   215,   216,   216,   216,   216,   216,   216,   216,   216,
     216,   216,   216,   216,   216,   216,   216,   218,   217,   219,
     219,   219,   219,   221,   220,   223,   222,   225,   224,   226,
     228,   227,   229,   230,   231,   232,   234,   233,   236,   235,
     238,   237,   239,   239,   240,   240,   241,   242,   244,   243,
     245,   245,   246,   246,   246,   247,   248,   250,   249,   252,
     251,   253,   253,   254,   254,   256,   255,   258,   257,   259,
     259,   259,   260,   260,   262,   261,   264,   263,   266,   265,
     267,   267,   268,   268,   268,   268,   268,   268,   269,   270,
     271,   272,   273,   274,   276,   275,   277,   277,   278,   278,
     280,   279,   282,   281,   283,   283,   284,   284,   284,   284,
     284,   284,   284,   284,   284,   284,   284,   284,   284,   284,
     284,   284,   284,   284,   284,   286,   285,   288,   287,   290,
     289,   292,   291,   294,   293,   295,   295,   295,   296,   297,
     299,   298,   300,   300,   301,   301,   303,   302,   304,   304,
     305,   305,   305,   305,   305,   305,   305,   305,   305,   305,
     305,   305,   305,   305,   305,   305,   307,   306,   309,   308,
     310,   310,   311,   311,   313,   312,   315,   314,   316,   316,
     317,   317,   318,   318,   318,   318,   318,   318,   318,   318,
     318,   318,   319,   320,   321,   323,   322,   325,   324,   327,
     326,   328,   330,   329,   331,   333,   332,   334,   334,   335,
     335,   337,   336,   339,   338,   340,   340,   341,   341,   342,
     342,   342,   342,   342,   342,   342,   342,   342,   343,   345,
     344,   346,   347,   348,   349,   351,   350,   352,   352,   353,
     353,   355,   354,   357,   356,   358,   358,   359,   359,   359,
     359,   359,   361,   360,   363,   362,   365,   364,   367,   366,
     368,   368,   369,   369,   371,   370,   373,   372,   374,   374,
     375,   375,   375,   375,   375,   375,   375,   375,   375,   377,
     376,   378,   380,   379,   381,   382,   384,   383,   385,   385,
     386,   386,   388,   387,   390,   389,   391,   391,   392,   392,
     393,   393,   393,   393,   393,   393,   393,   393,   393,   393,
     393,   395,   394,   397,   396,   399,   398,   401,   400,   403,
     402,   405,   404,   407,   406,   409,   408,   411,   410,   413,
     412,   414,   414,   415,   291,   416,   416,   417,   417,   418,
     418,   418,   418,   418,   418,   419,   421,   420,   423,   422,
     424,   424,   425,   425,   425,   425,   425,   425,   425,   425,
     425,   427,   426,   428,   428,   428,   429,   431,   430,   432,
     433,   434,   436,   435,   437,   437,   438,   438,   440,   439,
     442,   441,   444,   443,   446,   445,   447,   447,   448,   448,
     448,   448,   448,   448,   448,   448,   448,   448,   448,   448,
     448,   448,   448,   448,   448,   449,   451,   450,   453,   452,
     454,   456,   455,   457,   458,   460,   459,   461,   461,   463,
     462,   464,   465,   466,   468,   467,   469,   469,   469,   469,
     469,   471,   470,   473,   472,   475,   474,   477,   476,   479,
     478,   480,   480,   481,   483,   482,   484,   484,   486,   485,
     487,   487,   488,   488,   488,   488,   488,   488,   488,   489,
     491,   490,   493,   492,   494,   494,   496,   495,   497,   497,
     498,   498,   498,   498,   500,   499,   501,   502,   503
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
       1,     1,     1,     1,     1,     1,     1,     3,     3,     3,
       3,     3,     0,     6,     0,     4,     1,     3,     1,     1,
       1,     1,     1,     0,     4,     3,     0,     6,     0,     6,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     0,     4,     1,
       1,     1,     1,     0,     4,     0,     4,     0,     4,     3,
       0,     4,     3,     3,     3,     3,     0,     4,     0,     4,
       0,     6,     1,     3,     1,     1,     1,     1,     0,     6,
       1,     3,     1,     1,     1,     1,     1,     0,     6,     0,
       6,     0,     1,     1,     3,     0,     4,     0,     4,     1,
       3,     1,     1,     1,     0,     4,     0,     4,     0,     6,
       1,     3,     1,     1,     1,     1,     1,     1,     3,     3,
       3,     3,     3,     3,     0,     6,     0,     1,     1,     3,
       0,     4,     0,     4,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     4,     1,     1,     1,     3,     3,
       0,     6,     0,     1,     1,     3,     0,     4,     1,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     0,     6,     0,     4,
       0,     1,     1,     3,     0,     4,     0,     4,     0,     1,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     3,     1,     0,     4,     0,     4,     0,
       4,     1,     0,     4,     3,     0,     6,     0,     1,     1,
       3,     0,     4,     0,     4,     0,     1,     1,     3,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     0,
       4,     1,     1,     3,     3,     0,     6,     0,     1,     1,
       3,     0,     4,     0,     4,     1,     3,     1,     1,     1,
       1,     1,     0,     4,     0,     4,     0,     4,     0,     6,
       0,     1,     1,     3,     0,     4,     0,     4,     1,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     0,
       4,     3,     0,     4,     3,     3,     0,     6,     0,     1,
       1,     3,     0,     4,     0,     4,     0,     1,     1,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     6,     0,     4,     0,
       6,     1,     3,     0,     4,     0,     1,     1,     3,     1,
       1,     1,     1,     1,     1,     1,     0,     4,     0,     6,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     0,     4,     1,     1,     1,     3,     0,     4,     3,
       3,     3,     0,     6,     1,     3,     1,     1,     0,     4,
       0,     4,     0,     6,     0,     4,     1,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     3,     0,     4,     0,     4,
       3,     0,     4,     3,     3,     0,     4,     1,     1,     0,
       4,     3,     3,     3,     0,     4,     1,     1,     1,     1,
       1,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       6,     1,     3,     1,     0,     6,     1,     3,     0,     4,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     3,
       0,     4,     0,     6,     1,     3,     0,     4,     1,     3,
       1,     1,     1,     1,     0,     4,     3,     3,     3
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
     434,   435,   436,   437,   438,   439,   440,   443,   448,   453,
     458,   463,   468,   468,   479,   479,   488,   489,   492,   493,
     494,   495,   496,   499,   499,   509,   515,   515,   527,   527,
     539,   540,   543,   544,   545,   546,   547,   548,   549,   550,
     551,   552,   553,   554,   555,   556,   557,   560,   560,   567,
     568,   569,   570,   573,   573,   581,   581,   589,   589,   597,
     602,   602,   610,   615,   620,   625,   630,   630,   638,   638,
     647,   647,   657,   658,   661,   662,   665,   670,   675,   675,
     685,   686,   689,   690,   691,   694,   699,   706,   706,   716,
     716,   726,   727,   730,   731,   734,   734,   744,   744,   754,
     755,   756,   759,   760,   763,   763,   771,   771,   779,   779,
     790,   791,   794,   795,   796,   797,   798,   799,   802,   807,
     812,   817,   822,   827,   835,   835,   848,   849,   852,   853,
     860,   860,   886,   886,   897,   898,   902,   903,   904,   905,
     906,   907,   908,   909,   910,   911,   912,   913,   914,   915,
     916,   917,   918,   919,   920,   923,   923,   931,   931,   939,
     939,   947,   947,   955,   955,   962,   963,   964,   967,   972,
     980,   980,   991,   992,   996,   997,  1000,  1000,  1008,  1009,
    1012,  1013,  1014,  1015,  1016,  1017,  1018,  1019,  1020,  1021,
    1022,  1023,  1024,  1025,  1026,  1027,  1034,  1034,  1047,  1047,
    1056,  1057,  1060,  1061,  1066,  1066,  1081,  1081,  1095,  1096,
    1099,  1100,  1103,  1104,  1105,  1106,  1107,  1108,  1109,  1110,
    1111,  1112,  1115,  1117,  1122,  1124,  1124,  1132,  1132,  1140,
    1140,  1148,  1150,  1150,  1158,  1167,  1167,  1179,  1180,  1185,
    1186,  1191,  1191,  1203,  1203,  1215,  1216,  1221,  1222,  1227,
    1228,  1229,  1230,  1231,  1232,  1233,  1234,  1235,  1238,  1240,
    1240,  1248,  1250,  1252,  1257,  1265,  1265,  1277,  1278,  1281,
    1282,  1285,  1285,  1295,  1295,  1304,  1305,  1308,  1309,  1310,
    1311,  1312,  1315,  1315,  1323,  1323,  1330,  1330,  1342,  1342,
    1354,  1355,  1358,  1359,  1362,  1362,  1374,  1374,  1386,  1387,
    1390,  1391,  1392,  1393,  1394,  1395,  1396,  1397,  1398,  1401,
    1401,  1409,  1414,  1414,  1422,  1427,  1435,  1435,  1445,  1446,
    1449,  1450,  1453,  1453,  1462,  1462,  1471,  1472,  1475,  1476,
    1480,  1481,  1482,  1483,  1484,  1485,  1486,  1487,  1488,  1489,
    1490,  1493,  1493,  1503,  1503,  1513,  1513,  1521,  1521,  1529,
    1529,  1537,  1537,  1545,  1545,  1558,  1558,  1568,  1568,  1579,
    1579,  1589,  1590,  1593,  1593,  1603,  1604,  1607,  1608,  1611,
    1612,  1613,  1614,  1615,  1616,  1619,  1621,  1621,  1632,  1632,
    1644,  1645,  1648,  1649,  1650,  1651,  1652,  1653,  1654,  1655,
    1656,  1659,  1659,  1666,  1667,  1668,  1671,  1676,  1676,  1684,
    1689,  1696,  1703,  1703,  1713,  1714,  1717,  1718,  1721,  1721,
    1729,  1729,  1739,  1739,  1751,  1751,  1761,  1762,  1765,  1766,
    1767,  1768,  1769,  1770,  1771,  1772,  1773,  1774,  1775,  1776,
    1777,  1778,  1779,  1780,  1781,  1784,  1789,  1789,  1797,  1797,
    1805,  1810,  1810,  1818,  1823,  1828,  1828,  1836,  1837,  1840,
    1840,  1848,  1853,  1858,  1863,  1863,  1871,  1874,  1877,  1880,
    1883,  1889,  1889,  1899,  1899,  1906,  1906,  1913,  1913,  1926,
    1926,  1939,  1940,  1944,  1948,  1948,  1960,  1961,  1965,  1965,
    1973,  1974,  1977,  1978,  1979,  1980,  1981,  1982,  1983,  1986,
    1991,  1991,  1999,  1999,  2009,  2010,  2013,  2013,  2021,  2022,
    2025,  2026,  2027,  2028,  2031,  2031,  2039,  2044,  2049
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
#line 4517 "dhcp6_parser.cc" // lalr1.cc:1167
#line 2054 "dhcp6_parser.yy" // lalr1.cc:1168


void
isc::dhcp::Dhcp6Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
