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

  case 110:
#line 496 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1092 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 111:
#line 501 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1101 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 112:
#line 506 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("re-detect", b);
}
#line 1110 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 113:
#line 512 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lease-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.LEASE_DATABASE);
}
#line 1121 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 114:
#line 517 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1132 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 115:
#line 524 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1143 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 116:
#line 529 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1154 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 132:
#line 555 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.DATABASE_TYPE);
}
#line 1162 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 133:
#line 557 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("type", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1171 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 134:
#line 562 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("memfile", ctx.loc2pos(yystack_[0].location))); }
#line 1177 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 135:
#line 563 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("mysql", ctx.loc2pos(yystack_[0].location))); }
#line 1183 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 136:
#line 564 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("postgresql", ctx.loc2pos(yystack_[0].location))); }
#line 1189 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 137:
#line 565 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("cql", ctx.loc2pos(yystack_[0].location))); }
#line 1195 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 138:
#line 568 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1203 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 139:
#line 570 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr user(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1213 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 140:
#line 576 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1221 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 141:
#line 578 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr pwd(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 1231 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 142:
#line 584 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1239 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 143:
#line 586 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr h(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 1249 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 144:
#line 592 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr p(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", p);
}
#line 1258 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 145:
#line 597 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1266 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 146:
#line 599 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1276 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 147:
#line 605 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 1285 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 148:
#line 610 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 1294 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 149:
#line 615 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 1303 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 150:
#line 620 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("connect-timeout", n);
}
#line 1312 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 151:
#line 625 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1320 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 152:
#line 627 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr cp(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("contact-points", cp);
    ctx.leave();
}
#line 1330 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 153:
#line 633 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1338 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 154:
#line 635 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr ks(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("keyspace", ks);
    ctx.leave();
}
#line 1348 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 155:
#line 642 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("mac-sources", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.MAC_SOURCES);
}
#line 1359 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 156:
#line 647 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1368 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 161:
#line 660 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1377 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 162:
#line 665 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr duid(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1386 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 163:
#line 670 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 1397 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 164:
#line 675 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1406 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 170:
#line 689 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 1415 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 171:
#line 694 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr flex_id(new StringElement("flex-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(flex_id);
}
#line 1424 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 172:
#line 701 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay-supplied-options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1435 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 173:
#line 706 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1444 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 174:
#line 711 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 1455 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 175:
#line 716 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1464 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 180:
#line 729 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1474 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 181:
#line 733 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1484 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 182:
#line 739 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1494 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 183:
#line 743 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 1504 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 189:
#line 758 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1512 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 190:
#line 760 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr lib(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 1522 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 191:
#line 766 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1530 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 192:
#line 768 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1539 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 193:
#line 774 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.EXPIRED_LEASES_PROCESSING);
}
#line 1550 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 194:
#line 779 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // No expired lease parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1560 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 203:
#line 797 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 1569 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 204:
#line 802 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 1578 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 205:
#line 807 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 1587 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 206:
#line 812 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 1596 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 207:
#line 817 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 1605 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 208:
#line 822 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 1614 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 209:
#line 830 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet6", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET6);
}
#line 1625 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 210:
#line 835 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1634 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 215:
#line 855 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1644 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 216:
#line 859 "dhcp6_parser.yy" // lalr1.cc:859
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

  case 217:
#line 881 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the subnet6 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1680 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 218:
#line 885 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The subnet subnet6 parameter is required
    ctx.require("subnet", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 1690 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 240:
#line 918 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1698 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 241:
#line 920 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr subnet(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 1708 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 242:
#line 926 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1716 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 243:
#line 928 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 1726 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 244:
#line 934 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1734 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 245:
#line 936 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface-id", iface);
    ctx.leave();
}
#line 1744 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 246:
#line 942 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.CLIENT_CLASS);
}
#line 1752 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 247:
#line 944 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr cls(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 1762 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 248:
#line 950 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.RESERVATION_MODE);
}
#line 1770 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 249:
#line 952 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("reservation-mode", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1779 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 250:
#line 957 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("disabled", ctx.loc2pos(yystack_[0].location))); }
#line 1785 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 251:
#line 958 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("out-of-pool", ctx.loc2pos(yystack_[0].location))); }
#line 1791 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 252:
#line 959 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("all", ctx.loc2pos(yystack_[0].location))); }
#line 1797 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 253:
#line 962 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr id(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 1806 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 254:
#line 967 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr rc(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rapid-commit", rc);
}
#line 1815 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 255:
#line 975 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("shared-networks", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SHARED_NETWORK);
}
#line 1826 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 256:
#line 980 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1835 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 261:
#line 995 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1845 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 262:
#line 999 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1853 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 281:
#line 1029 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 1864 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 282:
#line 1034 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1873 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 283:
#line 1042 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1882 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 284:
#line 1045 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1890 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 289:
#line 1061 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1900 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 290:
#line 1065 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1912 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 291:
#line 1076 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1922 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 292:
#line 1080 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 1934 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 308:
#line 1112 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr code(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 1943 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 310:
#line 1119 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1951 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 311:
#line 1121 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 1961 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 312:
#line 1127 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1969 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 313:
#line 1129 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 1979 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 314:
#line 1135 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1987 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 315:
#line 1137 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr space(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 1997 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 317:
#line 1145 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2005 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 318:
#line 1147 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr encap(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 2015 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 319:
#line 1153 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr array(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 2024 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 320:
#line 1162 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 2035 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 321:
#line 1167 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2044 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 326:
#line 1186 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2054 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 327:
#line 1190 "dhcp6_parser.yy" // lalr1.cc:859
    {
    /// @todo: the code or name parameters are required.
    ctx.stack_.pop_back();
}
#line 2063 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 328:
#line 1198 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2073 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 329:
#line 1202 "dhcp6_parser.yy" // lalr1.cc:859
    {
    /// @todo: the code or name parameters are required.
    // parsing completed
}
#line 2082 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 344:
#line 1235 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2090 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 345:
#line 1237 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr data(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 2100 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 348:
#line 1247 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr space(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", space);
}
#line 2109 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 349:
#line 1252 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr persist(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-send", persist);
}
#line 2118 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 350:
#line 1260 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 2129 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 351:
#line 1265 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2138 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 356:
#line 1280 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2148 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 357:
#line 1284 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2158 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 358:
#line 1290 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2168 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 359:
#line 1294 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
}
#line 2177 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 367:
#line 1310 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2185 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 368:
#line 1312 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr pool(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 2195 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 369:
#line 1318 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2203 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 370:
#line 1320 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->combine_set("user-context", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2212 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 371:
#line 1325 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2220 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 372:
#line 1327 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr e(new MapElement(ctx.loc2pos(yystack_[3].location)));
    e->set("comment", yystack_[0].value.as< ElementPtr > ());
    ctx.stack_.back()->combine_set("user-context", e);
    ctx.leave();
}
#line 2231 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 373:
#line 1337 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pd-pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.PD_POOLS);
}
#line 2242 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 374:
#line 1342 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2251 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 379:
#line 1357 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2261 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 380:
#line 1361 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The prefix, prefix len and delegated len parameters are required.
    ctx.require("prefix", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("prefix-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("delegated-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2273 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 381:
#line 1369 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the pd-pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2283 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 382:
#line 1373 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The prefix, prefix len and delegated len parameters are required.
    ctx.require("prefix", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("prefix-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("delegated-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2295 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 394:
#line 1396 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2303 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 395:
#line 1398 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix", prf);
    ctx.leave();
}
#line 2313 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 396:
#line 1404 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix-len", prf);
}
#line 2322 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 397:
#line 1409 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2330 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 398:
#line 1411 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix", prf);
    ctx.leave();
}
#line 2340 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 399:
#line 1417 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix-len", prf);
}
#line 2349 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 400:
#line 1422 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr deleg(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("delegated-len", deleg);
}
#line 2358 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 401:
#line 1430 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 2369 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 402:
#line 1435 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2378 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 407:
#line 1448 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2388 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 408:
#line 1452 "dhcp6_parser.yy" // lalr1.cc:859
    {
    /// @todo: an identifier parameter is required.
    ctx.stack_.pop_back();
}
#line 2397 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 409:
#line 1457 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2407 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 410:
#line 1461 "dhcp6_parser.yy" // lalr1.cc:859
    {
    /// @todo: an identifier parameter is required.
    // parsing completed
}
#line 2416 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 424:
#line 1486 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-addresses", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2427 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 425:
#line 1491 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2436 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 426:
#line 1496 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefixes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2447 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 427:
#line 1501 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2456 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 428:
#line 1506 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2464 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 429:
#line 1508 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr d(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 2474 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 430:
#line 1514 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2482 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 431:
#line 1516 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 2492 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 432:
#line 1522 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2500 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 433:
#line 1524 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr host(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 2510 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 434:
#line 1530 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2518 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 435:
#line 1532 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flex-id", hw);
    ctx.leave();
}
#line 2528 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 436:
#line 1538 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2539 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 437:
#line 1543 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2548 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 438:
#line 1551 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 2559 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 439:
#line 1556 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2568 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 440:
#line 1561 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2576 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 441:
#line 1563 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr ip(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", ip);
    ctx.leave();
}
#line 2586 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 442:
#line 1572 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 2597 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 443:
#line 1577 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2606 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 446:
#line 1586 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2616 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 447:
#line 1590 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The name client class parameter is required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2626 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 459:
#line 1614 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2634 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 460:
#line 1616 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr test(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 2644 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 461:
#line 1625 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-id", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SERVER_ID);
}
#line 2655 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 462:
#line 1630 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The type parameter is required.
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2666 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 472:
#line 1650 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.DUID_TYPE);
}
#line 2674 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 473:
#line 1652 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("type", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2683 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 474:
#line 1657 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("LLT", ctx.loc2pos(yystack_[0].location))); }
#line 2689 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 475:
#line 1658 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("EN", ctx.loc2pos(yystack_[0].location))); }
#line 2695 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 476:
#line 1659 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("LL", ctx.loc2pos(yystack_[0].location))); }
#line 2701 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 477:
#line 1662 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr htype(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("htype", htype);
}
#line 2710 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 478:
#line 1667 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2718 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 479:
#line 1669 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr id(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("identifier", id);
    ctx.leave();
}
#line 2728 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 480:
#line 1675 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("time", time);
}
#line 2737 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 481:
#line 1680 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enterprise-id", time);
}
#line 2746 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 482:
#line 1687 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 2755 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 483:
#line 1694 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 2766 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 484:
#line 1699 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2775 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 489:
#line 1712 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2783 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 490:
#line 1714 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr stype(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 2793 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 491:
#line 1720 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2801 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 492:
#line 1722 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 2811 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 493:
#line 1730 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 2822 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 494:
#line 1735 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2833 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 495:
#line 1742 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2843 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 496:
#line 1746 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2853 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 514:
#line 1773 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 2862 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 515:
#line 1778 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2870 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 516:
#line 1780 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("qualifying-suffix", s);
    ctx.leave();
}
#line 2880 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 517:
#line 1786 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2888 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 518:
#line 1788 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 2898 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 519:
#line 1794 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 2907 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 520:
#line 1799 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2915 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 521:
#line 1801 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 2925 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 522:
#line 1807 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 2934 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 523:
#line 1812 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 2943 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 524:
#line 1817 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 2951 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 525:
#line 1819 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2960 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 526:
#line 1825 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 2966 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 527:
#line 1826 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 2972 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 528:
#line 1829 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NCR_FORMAT);
}
#line 2980 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 529:
#line 1831 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 2990 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 530:
#line 1837 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-include-fqdn", b);
}
#line 2999 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 531:
#line 1842 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-no-update", b);
}
#line 3008 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 532:
#line 1847 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-client-update", b);
}
#line 3017 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 533:
#line 1852 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 3025 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 534:
#line 1854 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("replace-client-name", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3034 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 535:
#line 1860 "dhcp6_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("when-present", ctx.loc2pos(yystack_[0].location))); 
      }
#line 3042 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 536:
#line 1863 "dhcp6_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location)));
      }
#line 3050 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 537:
#line 1866 "dhcp6_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("always", ctx.loc2pos(yystack_[0].location)));
      }
#line 3058 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 538:
#line 1869 "dhcp6_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("when-not-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 3066 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 539:
#line 1872 "dhcp6_parser.yy" // lalr1.cc:859
    {
      error(yystack_[0].location, "boolean values for the replace-client-name are "
                "no longer supported");
      }
#line 3075 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 540:
#line 1878 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3083 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 541:
#line 1880 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("generated-prefix", s);
    ctx.leave();
}
#line 3093 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 542:
#line 1888 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3101 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 543:
#line 1890 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("Dhcp4", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3110 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 544:
#line 1895 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3118 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 545:
#line 1897 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("DhcpDdns", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3127 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 546:
#line 1902 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3135 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 547:
#line 1904 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("Control-agent", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3144 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 548:
#line 1915 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Logging", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.LOGGING);
}
#line 3155 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 549:
#line 1920 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3164 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 553:
#line 1937 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 3175 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 554:
#line 1942 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3184 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 557:
#line 1954 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 3194 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 558:
#line 1958 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 3202 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 566:
#line 1973 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr dl(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 3211 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 567:
#line 1978 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3219 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 568:
#line 1980 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 3229 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 569:
#line 1986 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 3240 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 570:
#line 1991 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3249 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 573:
#line 2000 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3259 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 574:
#line 2004 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 3267 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 581:
#line 2018 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3275 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 582:
#line 2020 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 3285 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 583:
#line 2026 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr flush(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 3294 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 584:
#line 2031 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr maxsize(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 3303 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 585:
#line 2036 "dhcp6_parser.yy" // lalr1.cc:859
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


  const short int Dhcp6Parser::yypact_ninf_ = -712;

  const signed char Dhcp6Parser::yytable_ninf_ = -1;

  const short int
  Dhcp6Parser::yypact_[] =
  {
     242,  -712,  -712,  -712,  -712,  -712,  -712,  -712,  -712,  -712,
    -712,  -712,  -712,  -712,    31,    21,    30,    39,    45,    73,
      94,    98,   109,   120,   128,   131,   135,   142,  -712,  -712,
    -712,  -712,  -712,  -712,  -712,  -712,  -712,  -712,  -712,  -712,
    -712,  -712,  -712,  -712,  -712,  -712,  -712,  -712,  -712,  -712,
    -712,  -712,  -712,  -712,  -712,  -712,  -712,  -712,  -712,  -712,
    -712,  -712,  -712,  -712,    21,   -29,    10,   149,   184,    25,
     174,    15,   123,   153,    87,   204,   -30,   261,  -712,   134,
     208,   203,   207,   221,  -712,  -712,  -712,  -712,  -712,   222,
    -712,    92,  -712,  -712,  -712,  -712,  -712,  -712,  -712,  -712,
    -712,   224,   230,   237,   245,   251,  -712,  -712,  -712,  -712,
    -712,  -712,  -712,  -712,  -712,  -712,  -712,  -712,  -712,   255,
    -712,  -712,  -712,    99,  -712,  -712,  -712,  -712,  -712,  -712,
    -712,  -712,  -712,  -712,  -712,  -712,  -712,  -712,  -712,  -712,
    -712,  -712,  -712,  -712,  -712,  -712,  -712,  -712,  -712,  -712,
     266,   101,  -712,  -712,  -712,  -712,  -712,  -712,  -712,  -712,
    -712,   272,   301,  -712,  -712,  -712,  -712,  -712,  -712,  -712,
    -712,  -712,   116,  -712,  -712,  -712,  -712,  -712,  -712,  -712,
    -712,  -712,  -712,  -712,  -712,  -712,  -712,  -712,  -712,  -712,
    -712,   122,  -712,  -712,  -712,  -712,  -712,   321,  -712,   325,
     338,  -712,  -712,  -712,  -712,   133,  -712,  -712,  -712,  -712,
    -712,  -712,  -712,  -712,  -712,  -712,  -712,  -712,  -712,  -712,
    -712,   299,   284,  -712,  -712,  -712,  -712,  -712,  -712,  -712,
    -712,   345,  -712,  -712,   342,  -712,  -712,  -712,   400,  -712,
    -712,   397,   306,  -712,  -712,  -712,  -712,  -712,  -712,  -712,
    -712,  -712,  -712,  -712,  -712,  -712,   402,   403,  -712,  -712,
    -712,  -712,   401,   405,  -712,  -712,  -712,  -712,  -712,  -712,
    -712,  -712,  -712,  -712,  -712,  -712,   205,  -712,  -712,  -712,
     406,  -712,  -712,   407,  -712,   408,   410,  -712,  -712,   411,
     412,   413,  -712,  -712,  -712,   206,  -712,  -712,  -712,  -712,
    -712,  -712,  -712,  -712,  -712,  -712,  -712,  -712,  -712,  -712,
    -712,  -712,    21,    21,  -712,   267,   414,   416,   417,   418,
     419,  -712,    10,  -712,   420,   421,   422,   276,   277,   278,
     281,   287,   423,   424,   428,   429,   431,   435,   437,   438,
     439,   440,   441,   442,   443,   295,   445,   446,   149,  -712,
     447,   298,   184,  -712,   132,   450,   451,   452,   453,   454,
     307,   308,   455,   460,   461,   462,    25,  -712,   463,   174,
    -712,   464,   318,   468,   322,   323,    15,  -712,   469,   470,
     473,   474,   475,   476,   477,  -712,   123,  -712,   478,   481,
     334,   484,   485,   486,   337,  -712,    87,   489,   339,   340,
    -712,   204,   492,   493,   279,  -712,   343,   495,   496,   348,
     498,   350,   351,   502,   503,   353,   354,   355,   507,   508,
     261,  -712,  -712,  -712,   509,   510,   511,    21,    21,    21,
    -712,   512,   514,   516,  -712,  -712,  -712,  -712,  -712,   519,
     520,   521,   522,    21,   523,   525,   526,   527,   528,   529,
     531,   532,  -712,   533,   534,  -712,   530,  -712,  -712,  -712,
    -712,  -712,  -712,  -712,  -712,   506,   513,  -712,  -712,  -712,
     537,   538,   363,   375,   392,  -712,  -712,   231,   393,   541,
     540,  -712,   396,  -712,   398,  -712,   399,  -712,  -712,  -712,
     530,   530,   530,   404,   409,   415,   425,  -712,   426,   427,
    -712,   430,   432,   433,  -712,  -712,   434,  -712,  -712,  -712,
     436,    21,  -712,  -712,   444,   448,  -712,   449,  -712,  -712,
     195,   458,  -712,  -712,  -712,   -81,   456,  -712,    21,   149,
     459,  -712,  -712,  -712,   184,   129,   129,   542,   545,   546,
    -712,  -712,  -712,   547,   -44,    21,   280,    20,   548,   175,
      13,   292,   261,  -712,  -712,   553,  -712,   132,   551,   552,
    -712,  -712,  -712,  -712,  -712,  -712,  -712,  -712,   555,   482,
    -712,  -712,  -712,  -712,  -712,  -712,  -712,  -712,  -712,  -712,
    -712,  -712,  -712,  -712,  -712,  -712,  -712,  -712,  -712,  -712,
    -712,  -712,  -712,  -712,  -712,  -712,  -712,  -712,  -712,  -712,
    -712,  -712,  -712,   219,  -712,   249,  -712,  -712,   250,  -712,
    -712,  -712,  -712,   556,   559,   561,   562,   564,  -712,  -712,
    -712,   265,  -712,  -712,  -712,  -712,  -712,  -712,  -712,  -712,
    -712,  -712,  -712,  -712,  -712,   271,  -712,   563,   567,  -712,
    -712,   565,   569,  -712,  -712,   568,   570,  -712,  -712,   575,
     572,  -712,  -712,  -712,   163,  -712,  -712,  -712,   577,  -712,
    -712,  -712,   333,  -712,  -712,  -712,  -712,   344,  -712,   583,
     573,  -712,   586,   587,   588,   589,   590,   591,   274,  -712,
    -712,  -712,  -712,  -712,  -712,  -712,  -712,  -712,   593,   594,
     595,  -712,  -712,   275,  -712,  -712,  -712,  -712,  -712,  -712,
    -712,  -712,   282,  -712,  -712,  -712,   283,   457,   465,  -712,
    -712,   596,   600,  -712,  -712,   598,   602,  -712,  -712,   601,
     603,  -712,  -712,   604,  -712,   606,   459,  -712,  -712,   607,
     609,   610,   611,   466,   467,   471,   472,   479,   612,   614,
     129,  -712,  -712,    25,  -712,   542,    87,  -712,   545,   204,
    -712,   546,    58,  -712,   547,   -44,  -712,  -712,   280,  -712,
      20,  -712,   -30,  -712,   548,   480,   483,   487,   488,   490,
     491,   175,  -712,   616,   617,   494,   497,   499,    13,  -712,
     619,   621,   292,  -712,  -712,  -712,   620,   625,  -712,   174,
    -712,   551,    15,  -712,   552,   123,  -712,   555,   626,  -712,
     624,  -712,    59,   501,   504,   505,  -712,  -712,  -712,  -712,
    -712,   515,   517,  -712,   286,  -712,   623,  -712,   627,  -712,
    -712,  -712,  -712,  -712,  -712,  -712,  -712,  -712,  -712,  -712,
    -712,  -712,   290,  -712,  -712,  -712,  -712,  -712,  -712,  -712,
    -712,  -712,   303,  -712,  -712,  -712,  -712,  -712,  -712,  -712,
    -712,   304,   518,  -712,  -712,  -712,  -712,   535,   549,  -712,
    -712,   550,   305,  -712,   320,  -712,   629,  -712,   554,   631,
    -712,  -712,  -712,  -712,  -712,  -712,  -712,  -712,  -712,  -712,
    -712,  -712,  -712,    58,  -712,  -712,  -712,  -712,  -712,  -712,
    -712,  -712,  -712,  -712,  -712,  -712,  -712,  -712,  -712,   356,
    -712,  -712,   140,   631,  -712,  -712,   630,  -712,  -712,  -712,
     329,  -712,  -712,  -712,  -712,  -712,   635,   539,   638,   140,
    -712,   640,  -712,   557,  -712,   639,  -712,  -712,   391,  -712,
     103,   639,  -712,  -712,   644,   645,   647,   335,  -712,  -712,
    -712,  -712,  -712,  -712,   650,   500,   560,   566,   103,  -712,
     558,  -712,  -712,  -712,  -712,  -712
  };

  const unsigned short int
  Dhcp6Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,    24,    26,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     1,    43,
      36,    32,    31,    28,    29,    30,    35,     3,    33,    34,
      56,     5,    68,     7,   104,     9,   217,    11,   358,    13,
     381,    15,   409,    17,   283,    19,   291,    21,   328,    23,
     182,    25,   495,    27,    45,    39,     0,     0,     0,     0,
       0,     0,   411,     0,   293,   330,     0,     0,    47,     0,
      46,     0,     0,    40,    66,   548,   542,   544,   546,     0,
      65,     0,    58,    60,    62,    63,    64,    61,   102,   113,
     115,     0,     0,     0,     0,     0,   209,   281,   320,   369,
     371,   255,   155,   172,   163,   442,   174,   193,   461,     0,
     483,   493,    96,     0,    70,    72,    73,    74,    75,    76,
      79,    80,    81,    82,    84,    83,    88,    89,    77,    78,
      86,    87,    94,    95,    85,    90,    91,    92,    93,   110,
       0,     0,   106,   108,   109,   446,   350,   373,   240,   242,
     244,     0,     0,   248,   246,   401,   438,   239,   221,   222,
     223,   224,     0,   219,   228,   229,   230,   233,   235,   231,
     232,   225,   226,   237,   238,   227,   234,   236,   367,   366,
     363,     0,   360,   362,   364,   365,   394,     0,   397,     0,
       0,   393,   388,   391,   392,     0,   383,   385,   386,   389,
     390,   387,   436,   424,   426,   428,   430,   432,   434,   423,
     422,     0,   412,   413,   417,   418,   415,   419,   420,   421,
     416,     0,   310,   145,     0,   314,   312,   317,     0,   306,
     307,     0,   294,   295,   297,   309,   298,   299,   300,   316,
     301,   302,   303,   304,   305,   344,     0,     0,   342,   343,
     346,   347,     0,   331,   332,   334,   335,   336,   337,   338,
     339,   340,   341,   189,   191,   186,     0,   184,   187,   188,
       0,   515,   517,     0,   520,     0,     0,   524,   528,     0,
       0,     0,   533,   540,   513,     0,   497,   499,   500,   501,
     502,   503,   504,   505,   506,   507,   508,   509,   510,   511,
     512,    44,     0,     0,    37,     0,     0,     0,     0,     0,
       0,    55,     0,    57,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    69,
       0,     0,     0,   105,   448,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   218,     0,     0,
     359,     0,     0,     0,     0,     0,     0,   382,     0,     0,
       0,     0,     0,     0,     0,   410,     0,   284,     0,     0,
       0,     0,     0,     0,     0,   292,     0,     0,     0,     0,
     329,     0,     0,     0,     0,   183,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   496,    48,    41,     0,     0,     0,     0,     0,     0,
      59,     0,     0,     0,    97,    98,    99,   100,   101,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   482,     0,     0,    71,     0,   112,   107,   459,
     457,   458,   454,   455,   456,     0,   449,   450,   452,   453,
       0,     0,     0,     0,     0,   253,   254,     0,     0,     0,
       0,   220,     0,   361,     0,   396,     0,   399,   400,   384,
       0,     0,     0,     0,     0,     0,     0,   414,     0,     0,
     308,     0,     0,     0,   319,   296,     0,   348,   349,   333,
       0,     0,   185,   514,     0,     0,   519,     0,   522,   523,
       0,     0,   530,   531,   532,     0,     0,   498,     0,     0,
       0,   543,   545,   547,     0,     0,     0,   211,   285,   322,
      38,   370,   372,   257,     0,    45,     0,     0,   176,     0,
       0,     0,     0,    49,   111,     0,   447,     0,   352,   375,
     241,   243,   245,   250,   251,   252,   249,   247,   403,     0,
     368,   395,   398,   437,   425,   427,   429,   431,   433,   435,
     311,   146,   315,   313,   318,   345,   190,   192,   516,   518,
     521,   526,   527,   525,   529,   535,   536,   537,   538,   539,
     534,   541,    42,     0,   553,     0,   550,   552,     0,   132,
     138,   140,   142,     0,     0,     0,     0,     0,   151,   153,
     131,     0,   117,   119,   120,   121,   122,   123,   124,   125,
     126,   127,   128,   129,   130,     0,   215,     0,   212,   213,
     289,     0,   286,   287,   326,     0,   323,   324,   261,     0,
     258,   259,   161,   162,     0,   157,   159,   160,     0,   170,
     171,   167,     0,   165,   168,   169,   444,     0,   180,     0,
     177,   178,     0,     0,     0,     0,     0,     0,     0,   195,
     197,   198,   199,   200,   201,   202,   472,   478,     0,     0,
       0,   471,   470,     0,   463,   465,   468,   466,   467,   469,
     489,   491,     0,   485,   487,   488,     0,    51,     0,   451,
     356,     0,   353,   354,   379,     0,   376,   377,   407,     0,
     404,   405,   440,     0,    67,     0,     0,   549,   103,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   114,   116,     0,   210,     0,   293,   282,     0,   330,
     321,     0,     0,   256,     0,     0,   156,   173,     0,   164,
       0,   443,     0,   175,     0,     0,     0,     0,     0,     0,
       0,     0,   194,     0,     0,     0,     0,     0,     0,   462,
       0,     0,     0,   484,   494,    53,     0,    52,   460,     0,
     351,     0,     0,   374,     0,   411,   402,     0,     0,   439,
       0,   551,     0,     0,     0,     0,   144,   147,   148,   149,
     150,     0,     0,   118,     0,   214,     0,   288,     0,   325,
     280,   275,   277,   269,   270,   265,   266,   267,   268,   274,
     273,   276,     0,   263,   271,   278,   279,   272,   260,   158,
     166,   445,     0,   179,   203,   204,   205,   206,   207,   208,
     196,     0,     0,   477,   480,   481,   464,     0,     0,   486,
      50,     0,     0,   355,     0,   378,     0,   406,     0,     0,
     134,   135,   136,   137,   133,   139,   141,   143,   152,   154,
     216,   290,   327,     0,   262,   181,   474,   475,   476,   473,
     479,   490,   492,    54,   357,   380,   408,   441,   557,     0,
     555,   264,     0,     0,   554,   569,     0,   567,   565,   561,
       0,   559,   563,   564,   562,   556,     0,     0,     0,     0,
     558,     0,   566,     0,   560,     0,   568,   573,     0,   571,
       0,     0,   570,   581,     0,     0,     0,     0,   575,   577,
     578,   579,   580,   572,     0,     0,     0,     0,     0,   574,
       0,   583,   584,   585,   576,   582
  };

  const short int
  Dhcp6Parser::yypgoto_[] =
  {
    -712,  -712,  -712,  -712,  -712,  -712,  -712,  -712,  -712,  -712,
    -712,  -712,  -712,  -712,  -712,     9,  -712,   216,  -712,  -712,
    -712,  -712,  -712,  -712,   114,  -712,   -89,  -712,  -712,  -712,
     -66,  -712,  -712,  -712,   341,  -712,  -712,  -712,  -712,   136,
     312,   -67,   -62,   -54,   -48,  -712,  -712,  -712,  -712,  -712,
     127,   310,  -712,  -712,  -712,  -712,  -712,  -712,  -712,   137,
     -76,  -712,  -712,  -712,  -712,  -712,  -712,  -712,  -712,  -712,
    -712,   -74,  -712,  -538,  -712,  -712,  -712,  -712,  -712,  -712,
    -712,  -712,  -712,  -712,   -87,  -533,  -712,  -712,  -712,  -712,
     -86,  -712,  -712,  -712,  -712,  -712,  -712,  -712,  -712,   -93,
    -712,  -712,  -712,   -83,   289,  -712,  -712,  -712,  -712,  -712,
    -712,  -712,   -68,  -712,  -712,  -712,  -712,  -712,  -712,  -711,
    -712,  -712,  -712,   -63,  -712,  -712,  -712,   -59,   349,  -712,
    -712,  -705,  -712,  -692,  -712,  -531,  -712,  -691,  -712,  -712,
    -712,  -690,  -712,  -712,  -712,  -712,   -49,  -712,  -712,  -176,
     643,  -712,  -712,  -712,  -712,  -712,   -28,  -712,  -712,  -712,
     -25,  -712,   328,  -712,   -61,  -712,  -712,  -712,  -712,  -712,
     -50,  -712,  -712,  -712,  -712,  -712,   -21,  -712,  -712,  -712,
     -33,  -712,  -712,  -712,   -24,  -712,   326,  -712,  -712,  -712,
    -712,  -712,  -712,  -712,  -712,  -712,  -712,  -712,   -58,  -712,
    -712,  -712,   -57,   359,  -712,  -712,   -52,  -712,   -35,  -712,
    -712,  -712,  -712,  -712,   -64,  -712,  -712,  -712,   -56,   358,
    -712,  -712,  -712,  -712,  -712,  -712,  -712,  -712,  -712,  -712,
    -712,   -55,  -712,  -712,  -712,   -60,  -712,   352,  -712,  -712,
    -712,  -712,  -712,  -712,  -712,  -712,  -712,  -712,  -712,  -712,
    -712,  -712,  -688,  -712,  -712,  -712,  -712,  -712,  -712,  -712,
    -712,  -712,   182,  -712,  -712,  -712,  -712,  -712,  -712,   -37,
    -712,  -712,  -712,  -712,  -712,  -712,  -712,  -712,  -712,  -712,
    -712,  -712,   -39,  -712,  -712,  -712,  -712,  -712,  -712,  -712,
    -712,   192,   327,  -712,  -712,  -712,  -712,  -712,  -712,  -712,
    -712,  -712,  -712,  -712,  -712,  -712,  -712,  -712,  -712,  -712,
    -712,  -712,  -712,  -712,  -712,  -712,  -712,  -712,  -712,  -712,
    -712,  -712,  -712,  -712,  -712,    19,  -712,  -712,  -712,  -157,
    -712,  -712,  -171,  -712,  -712,  -712,  -712,  -712,  -712,  -182,
    -712,  -712,  -198,  -712,  -712,  -712,  -712,  -712
  };

  const short int
  Dhcp6Parser::yydefgoto_[] =
  {
      -1,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    78,    37,    38,    65,   541,
      82,    83,    39,    64,    79,    80,   554,   707,   786,   787,
     122,    41,    66,    91,    92,    93,   316,    43,    67,   123,
     124,   125,   126,   127,   128,   129,   130,   324,    45,    68,
     151,   152,   153,   350,   154,   131,   325,   132,   326,   621,
     622,   623,   729,   874,   624,   730,   625,   731,   626,   732,
     627,   240,   389,   629,   630,   631,   632,   633,   738,   634,
     739,   133,   338,   654,   655,   656,   657,   134,   340,   662,
     663,   664,   665,   135,   339,   136,   342,   669,   670,   671,
     762,    61,    76,   276,   277,   278,   402,   279,   403,   137,
     343,   678,   679,   680,   681,   682,   683,   684,   685,   138,
     332,   637,   638,   639,   743,    47,    69,   172,   173,   174,
     357,   175,   358,   176,   359,   177,   363,   178,   362,   566,
     179,   180,   139,   337,   649,   650,   651,   752,   832,   833,
     140,   333,    55,    73,   641,   642,   643,   746,    57,    74,
     241,   242,   243,   244,   245,   246,   247,   388,   248,   392,
     249,   391,   250,   251,   393,   252,   141,   334,   645,   646,
     647,   749,    59,    75,   262,   263,   264,   265,   266,   397,
     267,   268,   269,   270,   182,   355,   711,   712,   713,   789,
      49,    70,   191,   192,   193,   368,   142,   335,   143,   336,
     185,   356,   715,   716,   717,   792,    51,    71,   205,   206,
     207,   371,   208,   209,   373,   210,   211,   186,   364,   719,
     720,   721,   795,    53,    72,   221,   222,   223,   224,   379,
     225,   380,   226,   381,   227,   382,   228,   383,   229,   384,
     230,   378,   187,   365,   723,   798,   144,   341,   667,   354,
     465,   466,   467,   468,   469,   555,   145,   344,   693,   694,
     695,   773,   889,   696,   697,   774,   698,   699,   146,   147,
     346,   702,   703,   704,   780,   705,   781,   148,   347,    63,
      77,   295,   296,   297,   298,   407,   299,   408,   300,   301,
     410,   302,   303,   304,   413,   593,   305,   414,   306,   307,
     308,   309,   418,   600,   310,   419,    94,   318,    95,   319,
      96,   320,    97,   317,   605,   606,   607,   725,   899,   900,
     902,   910,   911,   912,   913,   918,   914,   916,   928,   929,
     930,   937,   938,   939,   944,   940,   941,   942
  };

  const unsigned short int
  Dhcp6Parser::yytable_[] =
  {
      90,   259,   168,   167,   189,   201,   219,   169,   239,   258,
     275,   294,   692,   661,   260,   170,   666,   183,   194,   203,
      84,   171,   253,   271,    36,   261,    29,   155,    30,   686,
      31,    28,   155,   652,   184,   195,   204,    40,   614,   254,
     272,   826,   595,   596,   597,   598,    42,   827,   181,   190,
     202,   220,    44,   108,   273,   274,   101,   102,   103,   104,
     828,   830,   831,   108,   837,   155,   196,   197,   198,   199,
     200,   109,   110,   156,   599,   157,   870,   871,   872,   873,
      46,   109,   110,   158,   159,   160,   161,   162,   163,   101,
     102,   103,   104,   164,   106,   322,   108,   233,   164,   165,
     323,    48,   348,   232,   352,    50,   166,   349,   653,   353,
     687,   688,   689,   690,   109,   110,    52,   159,   160,   366,
     162,   163,    89,    81,   367,   369,   233,    54,   234,   235,
     370,   164,   236,   237,   238,    56,   376,    85,    58,   166,
     311,   377,    60,   109,   110,   609,    86,    87,    88,    62,
     610,   611,   612,   613,   614,   615,   616,   617,   618,   619,
      98,   108,    89,    99,   100,    89,   755,    89,   233,   756,
     108,   233,   826,    32,    33,    34,    35,    89,   827,   233,
     101,   102,   103,   104,   105,   106,   107,   108,   109,   110,
     107,   828,   830,   831,   212,   837,   149,   150,   213,   214,
     215,   216,   217,   218,   459,   109,   110,   313,   404,   420,
      89,   312,   108,   405,   421,   314,   111,   112,   113,   114,
     115,   829,   348,   188,   315,   661,   321,   724,   327,   841,
     109,   110,   116,   933,   328,   117,   934,   935,   936,    89,
     692,   329,   118,   233,   255,   234,   235,   256,   257,   330,
     119,   120,   726,   352,   121,   331,    90,   727,   728,   345,
     109,   110,   672,   673,   674,   675,   676,   677,   740,   905,
     351,   906,   907,   741,   740,    89,   360,   771,   778,   742,
     461,    89,   772,   779,    89,   782,   420,   386,   460,   366,
     783,   784,    89,   883,   880,   563,   564,   565,   884,   168,
     167,    89,   463,   189,   169,   361,   404,   385,   369,   396,
     201,   885,   170,   894,   183,   591,   592,   194,   171,   464,
     219,   422,   423,   376,   203,   372,    89,   259,   895,   374,
     239,   184,   919,   462,   195,   258,   758,   920,   948,   759,
     260,   204,   375,   949,   253,   181,   390,   760,   190,   271,
     761,   261,   829,   387,   294,   202,    89,   652,   659,   903,
     660,   254,   904,   273,   274,   220,   272,   280,   281,   282,
     283,   284,   285,   286,   287,   288,   289,   290,   291,   292,
     293,     1,     2,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,   931,   700,   701,   932,   886,   887,
     888,   573,   574,   575,   394,   395,   398,   399,   401,   400,
     406,   409,   411,    89,   412,   415,   416,   417,   425,   424,
     426,   427,   428,   429,   431,   432,   433,   439,   440,   434,
     435,   436,   441,   442,   437,   443,   531,   532,   533,   444,
     438,   445,   446,   447,   448,   449,   450,   451,   452,   453,
     454,   456,   542,   457,   470,   471,   472,   473,   474,   477,
     475,   628,   628,   476,   478,   479,   480,   482,   484,   620,
     620,   485,   486,   490,   491,   487,   488,   492,   493,   494,
     495,   496,   498,   461,   691,   499,   294,   500,   501,   502,
     503,   460,   504,   506,   507,   508,   510,   511,   513,   514,
     515,   516,   517,   518,   519,   463,   520,   521,   522,   523,
     524,   525,   526,   528,   556,   560,   557,   529,   530,   534,
     587,   535,   464,   536,   537,   538,   539,   561,   543,    30,
     544,   545,   546,   547,   548,   553,   462,   602,   549,   550,
     551,   552,   558,   559,   562,   567,   568,   569,   570,   636,
     571,   572,   640,   644,   648,   668,   576,   708,   710,   714,
     733,   577,   718,   734,   722,   735,   736,   578,   737,   744,
     745,   747,   748,   751,   750,   754,   764,   579,   580,   581,
     594,   753,   582,   757,   583,   584,   585,   604,   586,   763,
     765,   766,   767,   768,   769,   770,   588,   775,   776,   777,
     589,   590,   790,   791,   793,   794,   797,   796,   601,   785,
     800,   802,   799,   803,   804,   805,   811,   788,   812,   806,
     851,   852,   807,   857,   808,   858,   860,   809,   861,   869,
     868,   881,   810,   844,   917,   882,   845,   896,   898,   921,
     846,   847,   923,   848,   849,   925,   927,   853,   945,   946,
     854,   947,   855,   875,   950,   951,   876,   877,   540,   658,
     455,   608,   458,   430,   813,   603,   628,   878,   839,   879,
     890,   843,   840,   635,   620,   259,   168,   167,   825,   842,
     239,   169,   815,   258,   814,   821,   820,   891,   260,   170,
     822,   183,   922,   512,   253,   171,   275,   271,   823,   261,
     835,   892,   893,   850,   824,   838,   897,   901,   184,   926,
     955,   254,   691,   952,   272,   481,   231,   836,   819,   953,
     817,   816,   181,   189,   505,   818,   201,   509,   483,   219,
     865,   834,   862,   863,   489,   866,   864,   194,   497,   709,
     203,   856,   867,   859,   706,   801,   915,   527,   924,   943,
     954,     0,     0,     0,   195,     0,     0,   204,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   190,     0,
       0,   202,     0,     0,   220,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   825,
       0,     0,     0,     0,     0,     0,   821,   820,     0,     0,
       0,   822,     0,     0,     0,     0,     0,     0,   909,   823,
       0,   835,     0,     0,     0,   824,   908,     0,     0,     0,
       0,     0,     0,     0,     0,   909,     0,     0,   836,     0,
       0,     0,     0,   908,     0,     0,     0,     0,     0,     0,
       0,     0,   834
  };

  const short int
  Dhcp6Parser::yycheck_[] =
  {
      66,    75,    69,    69,    70,    71,    72,    69,    74,    75,
      76,    77,   550,   546,    75,    69,   547,    69,    70,    71,
      10,    69,    74,    75,    15,    75,     5,     7,     7,    16,
       9,     0,     7,    77,    69,    70,    71,     7,    25,    74,
      75,   752,   123,   124,   125,   126,     7,   752,    69,    70,
      71,    72,     7,    38,    84,    85,    31,    32,    33,    34,
     752,   752,   752,    38,   752,     7,    51,    52,    53,    54,
      55,    56,    57,    48,   155,    50,    17,    18,    19,    20,
       7,    56,    57,    58,    59,    60,    61,    62,    63,    31,
      32,    33,    34,    73,    36,     3,    38,    39,    73,    74,
       8,     7,     3,    16,     3,     7,    81,     8,   152,     8,
      97,    98,    99,   100,    56,    57,     7,    59,    60,     3,
      62,    63,   152,   152,     8,     3,    39,     7,    41,    42,
       8,    73,    45,    46,    47,     7,     3,   127,     7,    81,
       6,     8,     7,    56,    57,    16,   136,   137,   138,     7,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      11,    38,   152,    14,    15,   152,     3,   152,    39,     6,
      38,    39,   883,   152,   153,   154,   155,   152,   883,    39,
      31,    32,    33,    34,    35,    36,    37,    38,    56,    57,
      37,   883,   883,   883,    71,   883,    12,    13,    75,    76,
      77,    78,    79,    80,    72,    56,    57,     4,     3,     3,
     152,     3,    38,     8,     8,     8,    67,    68,    69,    70,
      71,   752,     3,    49,     3,   758,     4,     8,     4,   760,
      56,    57,    83,   130,     4,    86,   133,   134,   135,   152,
     778,     4,    93,    39,    40,    41,    42,    43,    44,     4,
     101,   102,     3,     3,   105,     4,   322,     8,     8,     4,
      56,    57,    87,    88,    89,    90,    91,    92,     3,   129,
       4,   131,   132,     8,     3,   152,     4,     3,     3,     8,
     354,   152,     8,     8,   152,     3,     3,     3,   354,     3,
       8,     8,   152,     3,     8,    64,    65,    66,     8,   366,
     366,   152,   354,   369,   366,     4,     3,     8,     3,     3,
     376,     8,   366,     8,   366,   120,   121,   369,   366,   354,
     386,   312,   313,     3,   376,     4,   152,   401,     8,     4,
     396,   366,     3,   354,   369,   401,     3,     8,     3,     6,
     401,   376,     4,     8,   396,   366,     4,     3,   369,   401,
       6,   401,   883,     8,   420,   376,   152,    77,    78,     3,
      80,   396,     6,    84,    85,   386,   401,   106,   107,   108,
     109,   110,   111,   112,   113,   114,   115,   116,   117,   118,
     119,   139,   140,   141,   142,   143,   144,   145,   146,   147,
     148,   149,   150,   151,     3,   103,   104,     6,    94,    95,
      96,   490,   491,   492,     4,     8,     4,     4,     3,     8,
       4,     4,     4,   152,     4,     4,     4,     4,     4,   152,
       4,     4,     4,     4,     4,     4,     4,     4,     4,   153,
     153,   153,     4,     4,   153,     4,   427,   428,   429,     4,
     153,     4,     4,     4,     4,     4,     4,     4,   153,     4,
       4,     4,   443,   155,     4,     4,     4,     4,     4,     4,
     153,   535,   536,   155,     4,     4,     4,     4,     4,   535,
     536,   153,     4,     4,     4,   153,   153,     4,     4,     4,
       4,     4,     4,   557,   550,     4,   552,   153,     4,     4,
       4,   557,   155,     4,   155,   155,     4,     4,   155,     4,
       4,   153,     4,   153,   153,   557,     4,     4,   155,   155,
     155,     4,     4,     4,     8,   152,     3,     7,     7,     7,
     511,     7,   557,     7,     5,     5,     5,   152,     5,     7,
       5,     5,     5,     5,     5,     5,   557,   528,     7,     7,
       7,     7,     5,     5,   152,   152,     5,     7,   152,     7,
     152,   152,     7,     7,     7,     7,   152,     4,     7,     7,
       4,   152,     7,     4,    82,     4,     4,   152,     4,     6,
       3,     6,     3,     3,     6,     3,     3,   152,   152,   152,
     122,     6,   152,     6,   152,   152,   152,   128,   152,     6,
       4,     4,     4,     4,     4,     4,   152,     4,     4,     4,
     152,   152,     6,     3,     6,     3,     3,     6,   152,   152,
       4,     4,     8,     4,     4,     4,     4,   152,     4,   153,
       4,     4,   155,     4,   153,     4,     6,   155,     3,     5,
       4,     8,   153,   153,     4,     8,   153,     8,     7,     4,
     153,   153,     4,   153,   153,     5,     7,   153,     4,     4,
     153,     4,   153,   152,     4,   155,   152,   152,   442,   545,
     348,   534,   352,   322,   740,   529,   740,   152,   755,   152,
     152,   764,   758,   536,   740,   749,   743,   743,   752,   762,
     746,   743,   745,   749,   743,   752,   752,   152,   749,   743,
     752,   743,   153,   404,   746,   743,   762,   749,   752,   749,
     752,   152,   152,   771,   752,   754,   152,   883,   743,   152,
     152,   746,   778,   153,   749,   366,    73,   752,   751,   153,
     748,   746,   743,   789,   396,   749,   792,   401,   369,   795,
     794,   752,   789,   791,   376,   795,   792,   789,   386,   557,
     792,   778,   797,   782,   552,   726,   903,   420,   919,   931,
     948,    -1,    -1,    -1,   789,    -1,    -1,   792,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   789,    -1,
      -1,   792,    -1,    -1,   795,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   883,
      -1,    -1,    -1,    -1,    -1,    -1,   883,   883,    -1,    -1,
      -1,   883,    -1,    -1,    -1,    -1,    -1,    -1,   902,   883,
      -1,   883,    -1,    -1,    -1,   883,   902,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   919,    -1,    -1,   883,    -1,
      -1,    -1,    -1,   919,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   883
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
      13,   206,   207,   208,   210,     7,    48,    50,    58,    59,
      60,    61,    62,    63,    73,    74,    81,   186,   197,   198,
     199,   200,   283,   284,   285,   287,   289,   291,   293,   296,
     297,   332,   350,   362,   364,   366,   383,   408,    49,   186,
     332,   358,   359,   360,   362,   364,    51,    52,    53,    54,
      55,   186,   332,   362,   364,   374,   375,   376,   378,   379,
     381,   382,    71,    75,    76,    77,    78,    79,    80,   186,
     332,   391,   392,   393,   394,   396,   398,   400,   402,   404,
     406,   306,    16,    39,    41,    42,    45,    46,    47,   186,
     227,   316,   317,   318,   319,   320,   321,   322,   324,   326,
     328,   329,   331,   362,   364,    40,    43,    44,   186,   227,
     320,   326,   340,   341,   342,   343,   344,   346,   347,   348,
     349,   362,   364,    84,    85,   186,   259,   260,   261,   263,
     106,   107,   108,   109,   110,   111,   112,   113,   114,   115,
     116,   117,   118,   119,   186,   447,   448,   449,   450,   452,
     454,   455,   457,   458,   459,   462,   464,   465,   466,   467,
     470,     6,     3,     4,     8,     3,   192,   479,   473,   475,
     477,     4,     3,     8,   203,   212,   214,     4,     4,     4,
       4,     4,   276,   307,   333,   363,   365,   299,   238,   250,
     244,   413,   252,   266,   423,     4,   436,   444,     3,     8,
     209,     4,     3,     8,   415,   351,   367,   286,   288,   290,
       4,     4,   294,   292,   384,   409,     3,     8,   361,     3,
       8,   377,     4,   380,     4,     4,     3,     8,   407,   395,
     397,   399,   401,   403,   405,     8,     3,     8,   323,   228,
       4,   327,   325,   330,     4,     8,     3,   345,     4,     4,
       8,     3,   262,   264,     3,     8,     4,   451,   453,     4,
     456,     4,     4,   460,   463,     4,     4,     4,   468,   471,
       3,     8,   171,   171,   152,     4,     4,     4,     4,     4,
     190,     4,     4,     4,   153,   153,   153,   153,   153,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,   153,     4,     4,   196,     4,   155,   207,    72,
     186,   227,   332,   362,   364,   416,   417,   418,   419,   420,
       4,     4,     4,     4,     4,   153,   155,     4,     4,     4,
       4,   284,     4,   359,     4,   153,     4,   153,   153,   375,
       4,     4,     4,     4,     4,     4,     4,   393,     4,     4,
     153,     4,     4,     4,   155,   318,     4,   155,   155,   342,
       4,     4,   260,   155,     4,     4,   153,     4,   153,   153,
       4,     4,   155,   155,   155,     4,     4,   448,     4,     7,
       7,   171,   171,   171,     7,     7,     7,     5,     5,     5,
     173,   175,   171,     5,     5,     5,     5,     5,     5,     7,
       7,     7,     7,     5,   182,   421,     8,     3,     5,     5,
     152,   152,   152,    64,    65,    66,   295,   152,     5,     7,
     152,   152,   152,   182,   182,   182,   152,   152,   152,   152,
     152,   152,   152,   152,   152,   152,   152,   171,   152,   152,
     152,   120,   121,   461,   122,   123,   124,   125,   126,   155,
     469,   152,   171,   195,   128,   480,   481,   482,   206,    16,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
     186,   215,   216,   217,   220,   222,   224,   226,   227,   229,
     230,   231,   232,   233,   235,   215,     7,   277,   278,   279,
       7,   310,   311,   312,     7,   334,   335,   336,     7,   300,
     301,   302,    77,   152,   239,   240,   241,   242,   180,    78,
      80,   241,   245,   246,   247,   248,   291,   414,     7,   253,
     254,   255,    87,    88,    89,    90,    91,    92,   267,   268,
     269,   270,   271,   272,   273,   274,    16,    97,    98,    99,
     100,   186,   229,   424,   425,   426,   429,   430,   432,   433,
     103,   104,   437,   438,   439,   441,   447,   183,     4,   418,
       7,   352,   353,   354,     7,   368,   369,   370,     7,   385,
     386,   387,    82,   410,     8,   483,     3,     8,     8,   218,
     221,   223,   225,     4,     4,     4,     4,     4,   234,   236,
       3,     8,     8,   280,     6,     3,   313,     6,     3,   337,
       6,     3,   303,     6,     3,     3,     6,     6,     3,     6,
       3,     6,   256,     6,     3,     4,     4,     4,     4,     4,
       4,     3,     8,   427,   431,     4,     4,     4,     3,     8,
     440,   442,     3,     8,     8,   152,   184,   185,   152,   355,
       6,     3,   371,     6,     3,   388,     6,     3,   411,     8,
       4,   481,     4,     4,     4,     4,   153,   155,   153,   155,
     153,     4,     4,   216,   283,   279,   316,   312,   340,   336,
     186,   197,   198,   199,   200,   227,   275,   287,   289,   291,
     293,   297,   304,   305,   332,   362,   364,   408,   302,   240,
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
     196,   196,   196,   196,   196,   196,   196,   197,   198,   199,
     200,   201,   203,   202,   205,   204,   206,   206,   207,   207,
     209,   208,   210,   212,   211,   214,   213,   215,   215,   216,
     216,   216,   216,   216,   216,   216,   216,   216,   216,   216,
     216,   216,   218,   217,   219,   219,   219,   219,   221,   220,
     223,   222,   225,   224,   226,   228,   227,   229,   230,   231,
     232,   234,   233,   236,   235,   238,   237,   239,   239,   240,
     240,   241,   242,   244,   243,   245,   245,   246,   246,   246,
     247,   248,   250,   249,   252,   251,   253,   253,   254,   254,
     256,   255,   258,   257,   259,   259,   259,   260,   260,   262,
     261,   264,   263,   266,   265,   267,   267,   268,   268,   268,
     268,   268,   268,   269,   270,   271,   272,   273,   274,   276,
     275,   277,   277,   278,   278,   280,   279,   282,   281,   283,
     283,   284,   284,   284,   284,   284,   284,   284,   284,   284,
     284,   284,   284,   284,   284,   284,   284,   284,   284,   284,
     286,   285,   288,   287,   290,   289,   292,   291,   294,   293,
     295,   295,   295,   296,   297,   299,   298,   300,   300,   301,
     301,   303,   302,   304,   304,   305,   305,   305,   305,   305,
     305,   305,   305,   305,   305,   305,   305,   305,   305,   305,
     305,   307,   306,   309,   308,   310,   310,   311,   311,   313,
     312,   315,   314,   316,   316,   317,   317,   318,   318,   318,
     318,   318,   318,   318,   318,   318,   318,   319,   320,   321,
     323,   322,   325,   324,   327,   326,   328,   330,   329,   331,
     333,   332,   334,   334,   335,   335,   337,   336,   339,   338,
     340,   340,   341,   341,   342,   342,   342,   342,   342,   342,
     342,   342,   342,   343,   345,   344,   346,   347,   348,   349,
     351,   350,   352,   352,   353,   353,   355,   354,   357,   356,
     358,   358,   359,   359,   359,   359,   359,   361,   360,   363,
     362,   365,   364,   367,   366,   368,   368,   369,   369,   371,
     370,   373,   372,   374,   374,   375,   375,   375,   375,   375,
     375,   375,   375,   375,   377,   376,   378,   380,   379,   381,
     382,   384,   383,   385,   385,   386,   386,   388,   387,   390,
     389,   391,   391,   392,   392,   393,   393,   393,   393,   393,
     393,   393,   393,   393,   395,   394,   397,   396,   399,   398,
     401,   400,   403,   402,   405,   404,   407,   406,   409,   408,
     411,   410,   413,   412,   414,   414,   415,   291,   416,   416,
     417,   417,   418,   418,   418,   418,   418,   418,   419,   421,
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
       1,     1,     1,     1,     1,     1,     1,     3,     3,     3,
       3,     3,     0,     6,     0,     4,     1,     3,     1,     1,
       0,     4,     3,     0,     6,     0,     6,     1,     3,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     0,     4,     1,     1,     1,     1,     0,     4,
       0,     4,     0,     4,     3,     0,     4,     3,     3,     3,
       3,     0,     4,     0,     4,     0,     6,     1,     3,     1,
       1,     1,     1,     0,     6,     1,     3,     1,     1,     1,
       1,     1,     0,     6,     0,     6,     0,     1,     1,     3,
       0,     4,     0,     4,     1,     3,     1,     1,     1,     0,
       4,     0,     4,     0,     6,     1,     3,     1,     1,     1,
       1,     1,     1,     3,     3,     3,     3,     3,     3,     0,
       6,     0,     1,     1,     3,     0,     4,     0,     4,     1,
       3,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       0,     4,     0,     4,     0,     4,     0,     4,     0,     4,
       1,     1,     1,     3,     3,     0,     6,     0,     1,     1,
       3,     0,     4,     1,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     0,     6,     0,     4,     0,     1,     1,     3,     0,
       4,     0,     4,     0,     1,     1,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     3,     1,
       0,     4,     0,     4,     0,     4,     1,     0,     4,     3,
       0,     6,     0,     1,     1,     3,     0,     4,     0,     4,
       0,     1,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     0,     4,     1,     1,     3,     3,
       0,     6,     0,     1,     1,     3,     0,     4,     0,     4,
       1,     3,     1,     1,     1,     1,     1,     0,     4,     0,
       4,     0,     4,     0,     6,     0,     1,     1,     3,     0,
       4,     0,     4,     1,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     0,     4,     3,     0,     4,     3,
       3,     0,     6,     0,     1,     1,     3,     0,     4,     0,
       4,     0,     1,     1,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     0,     4,     0,     4,     0,     4,
       0,     4,     0,     4,     0,     4,     0,     4,     0,     6,
       0,     4,     0,     6,     1,     3,     0,     4,     0,     1,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     0,
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
     434,   435,   436,   437,   438,   439,   440,   443,   448,   453,
     458,   463,   468,   468,   479,   479,   488,   489,   492,   493,
     496,   496,   506,   512,   512,   524,   524,   536,   537,   540,
     541,   542,   543,   544,   545,   546,   547,   548,   549,   550,
     551,   552,   555,   555,   562,   563,   564,   565,   568,   568,
     576,   576,   584,   584,   592,   597,   597,   605,   610,   615,
     620,   625,   625,   633,   633,   642,   642,   652,   653,   656,
     657,   660,   665,   670,   670,   680,   681,   684,   685,   686,
     689,   694,   701,   701,   711,   711,   721,   722,   725,   726,
     729,   729,   739,   739,   749,   750,   751,   754,   755,   758,
     758,   766,   766,   774,   774,   785,   786,   789,   790,   791,
     792,   793,   794,   797,   802,   807,   812,   817,   822,   830,
     830,   843,   844,   847,   848,   855,   855,   881,   881,   892,
     893,   897,   898,   899,   900,   901,   902,   903,   904,   905,
     906,   907,   908,   909,   910,   911,   912,   913,   914,   915,
     918,   918,   926,   926,   934,   934,   942,   942,   950,   950,
     957,   958,   959,   962,   967,   975,   975,   986,   987,   991,
     992,   995,   995,  1003,  1004,  1007,  1008,  1009,  1010,  1011,
    1012,  1013,  1014,  1015,  1016,  1017,  1018,  1019,  1020,  1021,
    1022,  1029,  1029,  1042,  1042,  1051,  1052,  1055,  1056,  1061,
    1061,  1076,  1076,  1090,  1091,  1094,  1095,  1098,  1099,  1100,
    1101,  1102,  1103,  1104,  1105,  1106,  1107,  1110,  1112,  1117,
    1119,  1119,  1127,  1127,  1135,  1135,  1143,  1145,  1145,  1153,
    1162,  1162,  1174,  1175,  1180,  1181,  1186,  1186,  1198,  1198,
    1210,  1211,  1216,  1217,  1222,  1223,  1224,  1225,  1226,  1227,
    1228,  1229,  1230,  1233,  1235,  1235,  1243,  1245,  1247,  1252,
    1260,  1260,  1272,  1273,  1276,  1277,  1280,  1280,  1290,  1290,
    1299,  1300,  1303,  1304,  1305,  1306,  1307,  1310,  1310,  1318,
    1318,  1325,  1325,  1337,  1337,  1349,  1350,  1353,  1354,  1357,
    1357,  1369,  1369,  1381,  1382,  1385,  1386,  1387,  1388,  1389,
    1390,  1391,  1392,  1393,  1396,  1396,  1404,  1409,  1409,  1417,
    1422,  1430,  1430,  1440,  1441,  1444,  1445,  1448,  1448,  1457,
    1457,  1466,  1467,  1470,  1471,  1475,  1476,  1477,  1478,  1479,
    1480,  1481,  1482,  1483,  1486,  1486,  1496,  1496,  1506,  1506,
    1514,  1514,  1522,  1522,  1530,  1530,  1538,  1538,  1551,  1551,
    1561,  1561,  1572,  1572,  1582,  1583,  1586,  1586,  1596,  1597,
    1600,  1601,  1604,  1605,  1606,  1607,  1608,  1609,  1612,  1614,
    1614,  1625,  1625,  1637,  1638,  1641,  1642,  1643,  1644,  1645,
    1646,  1647,  1650,  1650,  1657,  1658,  1659,  1662,  1667,  1667,
    1675,  1680,  1687,  1694,  1694,  1704,  1705,  1708,  1709,  1712,
    1712,  1720,  1720,  1730,  1730,  1742,  1742,  1752,  1753,  1756,
    1757,  1758,  1759,  1760,  1761,  1762,  1763,  1764,  1765,  1766,
    1767,  1768,  1769,  1770,  1773,  1778,  1778,  1786,  1786,  1794,
    1799,  1799,  1807,  1812,  1817,  1817,  1825,  1826,  1829,  1829,
    1837,  1842,  1847,  1852,  1852,  1860,  1863,  1866,  1869,  1872,
    1878,  1878,  1888,  1888,  1895,  1895,  1902,  1902,  1915,  1915,
    1928,  1929,  1933,  1937,  1937,  1949,  1950,  1954,  1954,  1962,
    1963,  1966,  1967,  1968,  1969,  1970,  1973,  1978,  1978,  1986,
    1986,  1996,  1997,  2000,  2000,  2008,  2009,  2012,  2013,  2014,
    2015,  2018,  2018,  2026,  2031,  2036
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
#line 4503 "dhcp6_parser.cc" // lalr1.cc:1167
#line 2041 "dhcp6_parser.yy" // lalr1.cc:1168


void
isc::dhcp::Dhcp6Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
