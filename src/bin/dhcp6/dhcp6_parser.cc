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
      case 157: // value
      case 161: // map_value
      case 202: // db_type
      case 394: // duid_type
      case 427: // ncr_protocol_value
      case 435: // replace_client_name_value
        value.move< ElementPtr > (that.value);
        break;

      case 142: // "boolean"
        value.move< bool > (that.value);
        break;

      case 141: // "floating point"
        value.move< double > (that.value);
        break;

      case 140: // "integer"
        value.move< int64_t > (that.value);
        break;

      case 139: // "constant string"
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
      case 157: // value
      case 161: // map_value
      case 202: // db_type
      case 394: // duid_type
      case 427: // ncr_protocol_value
      case 435: // replace_client_name_value
        value.copy< ElementPtr > (that.value);
        break;

      case 142: // "boolean"
        value.copy< bool > (that.value);
        break;

      case 141: // "floating point"
        value.copy< double > (that.value);
        break;

      case 140: // "integer"
        value.copy< int64_t > (that.value);
        break;

      case 139: // "constant string"
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
            case 139: // "constant string"

#line 214 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< std::string > (); }
#line 362 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 140: // "integer"

#line 214 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< int64_t > (); }
#line 369 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 141: // "floating point"

#line 214 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< double > (); }
#line 376 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 142: // "boolean"

#line 214 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< bool > (); }
#line 383 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 157: // value

#line 214 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 390 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 161: // map_value

#line 214 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 397 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 202: // db_type

#line 214 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 404 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 394: // duid_type

#line 214 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 411 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 427: // ncr_protocol_value

#line 214 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 418 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 435: // replace_client_name_value

#line 214 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 425 "dhcp6_parser.cc" // lalr1.cc:636
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
      case 157: // value
      case 161: // map_value
      case 202: // db_type
      case 394: // duid_type
      case 427: // ncr_protocol_value
      case 435: // replace_client_name_value
        yylhs.value.build< ElementPtr > ();
        break;

      case 142: // "boolean"
        yylhs.value.build< bool > ();
        break;

      case 141: // "floating point"
        yylhs.value.build< double > ();
        break;

      case 140: // "integer"
        yylhs.value.build< int64_t > ();
        break;

      case 139: // "constant string"
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
#line 223 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.NO_KEYWORD; }
#line 670 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 4:
#line 224 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.CONFIG; }
#line 676 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 6:
#line 225 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.DHCP6; }
#line 682 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 8:
#line 226 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.INTERFACES_CONFIG; }
#line 688 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 10:
#line 227 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.SUBNET6; }
#line 694 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 12:
#line 228 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.POOLS; }
#line 700 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 14:
#line 229 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.PD_POOLS; }
#line 706 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 16:
#line 230 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.RESERVATIONS; }
#line 712 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 18:
#line 231 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.OPTION_DEF; }
#line 718 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 20:
#line 232 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.OPTION_DATA; }
#line 724 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 22:
#line 233 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.HOOKS_LIBRARIES; }
#line 730 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 24:
#line 234 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.DHCP_DDNS; }
#line 736 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 26:
#line 242 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 742 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 27:
#line 243 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as< double > (), ctx.loc2pos(yystack_[0].location))); }
#line 748 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 28:
#line 244 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 754 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 29:
#line 245 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 760 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 30:
#line 246 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 766 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 31:
#line 247 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 772 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 32:
#line 248 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 778 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 33:
#line 251 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as< ElementPtr > ());
}
#line 787 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 34:
#line 256 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 798 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 35:
#line 261 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 808 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 36:
#line 267 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 814 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 39:
#line 274 "dhcp6_parser.yy" // lalr1.cc:859
    {
                  // map containing a single entry
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 823 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 40:
#line 278 "dhcp6_parser.yy" // lalr1.cc:859
    {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 833 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 41:
#line 285 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 842 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 42:
#line 288 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // list parsing complete. Put any sanity checking here
}
#line 850 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 45:
#line 296 "dhcp6_parser.yy" // lalr1.cc:859
    {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 859 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 46:
#line 300 "dhcp6_parser.yy" // lalr1.cc:859
    {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 868 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 47:
#line 307 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // List parsing about to start
}
#line 876 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 48:
#line 309 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // list parsing complete. Put any sanity checking here
    //ctx.stack_.pop_back();
}
#line 885 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 51:
#line 318 "dhcp6_parser.yy" // lalr1.cc:859
    {
                          ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 894 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 52:
#line 322 "dhcp6_parser.yy" // lalr1.cc:859
    {
                          ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 903 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 53:
#line 333 "dhcp6_parser.yy" // lalr1.cc:859
    {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as< std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 914 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 54:
#line 343 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 925 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 55:
#line 348 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 935 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 63:
#line 367 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Dhcp6", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP6);
}
#line 948 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 64:
#line 374 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 960 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 65:
#line 384 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the Dhcp6 map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 970 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 66:
#line 388 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 978 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 91:
#line 422 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("preferred-lifetime", prf);
}
#line 987 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 92:
#line 427 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 996 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 93:
#line 432 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 1005 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 94:
#line 437 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 1014 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 95:
#line 442 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr dpp(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 1023 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 96:
#line 447 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces-config", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.INTERFACES_CONFIG);
}
#line 1034 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 97:
#line 452 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1043 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 98:
#line 457 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1053 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 99:
#line 461 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1061 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 100:
#line 465 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1072 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 101:
#line 470 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1081 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 102:
#line 475 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lease-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.LEASE_DATABASE);
}
#line 1092 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 103:
#line 480 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1101 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 104:
#line 485 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1112 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 105:
#line 490 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1121 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 121:
#line 514 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.DATABASE_TYPE);
}
#line 1129 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 122:
#line 516 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("type", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1138 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 123:
#line 521 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("memfile", ctx.loc2pos(yystack_[0].location))); }
#line 1144 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 124:
#line 522 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("mysql", ctx.loc2pos(yystack_[0].location))); }
#line 1150 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 125:
#line 523 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("postgresql", ctx.loc2pos(yystack_[0].location))); }
#line 1156 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 126:
#line 524 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("cql", ctx.loc2pos(yystack_[0].location))); }
#line 1162 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 127:
#line 527 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1170 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 128:
#line 529 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr user(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1180 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 129:
#line 535 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1188 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 130:
#line 537 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr pwd(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 1198 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 131:
#line 543 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1206 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 132:
#line 545 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr h(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 1216 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 133:
#line 551 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr p(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", p);
}
#line 1225 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 134:
#line 556 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1233 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 135:
#line 558 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1243 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 136:
#line 564 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 1252 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 137:
#line 569 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 1261 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 138:
#line 574 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 1270 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 139:
#line 579 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("connect-timeout", n);
}
#line 1279 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 140:
#line 584 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1287 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 141:
#line 586 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr cp(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("contact-points", cp);
    ctx.leave();
}
#line 1297 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 142:
#line 592 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1305 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 143:
#line 594 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr ks(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("keyspace", ks);
    ctx.leave();
}
#line 1315 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 144:
#line 601 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("mac-sources", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.MAC_SOURCES);
}
#line 1326 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 145:
#line 606 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1335 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 150:
#line 619 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1344 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 151:
#line 624 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr duid(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1353 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 152:
#line 629 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 1364 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 153:
#line 634 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1373 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 158:
#line 647 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 1382 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 159:
#line 654 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay-supplied-options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1393 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 160:
#line 659 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1402 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 161:
#line 664 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 1413 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 162:
#line 669 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1422 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 167:
#line 682 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1432 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 168:
#line 686 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1440 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 169:
#line 690 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1450 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 170:
#line 694 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1458 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 176:
#line 707 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1466 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 177:
#line 709 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr lib(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 1476 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 178:
#line 715 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1484 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 179:
#line 717 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1493 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 180:
#line 723 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.EXPIRED_LEASES_PROCESSING);
}
#line 1504 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 181:
#line 728 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1513 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 190:
#line 745 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 1522 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 191:
#line 750 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 1531 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 192:
#line 755 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 1540 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 193:
#line 760 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 1549 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 194:
#line 765 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 1558 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 195:
#line 770 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 1567 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 196:
#line 778 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet6", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET6);
}
#line 1578 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 197:
#line 783 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1587 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 202:
#line 803 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1597 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 203:
#line 807 "dhcp6_parser.yy" // lalr1.cc:859
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
    ctx.stack_.pop_back();
}
#line 1620 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 204:
#line 826 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the subnet6 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1630 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 205:
#line 830 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1638 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 225:
#line 859 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1646 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 226:
#line 861 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr subnet(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 1656 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 227:
#line 867 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1664 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 228:
#line 869 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 1674 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 229:
#line 875 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1682 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 230:
#line 877 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface-id", iface);
    ctx.leave();
}
#line 1692 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 231:
#line 883 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.CLIENT_CLASS);
}
#line 1700 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 232:
#line 885 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr cls(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 1710 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 233:
#line 891 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1718 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 234:
#line 893 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr rm(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservation-mode", rm);
    ctx.leave();
}
#line 1728 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 235:
#line 899 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr id(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 1737 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 236:
#line 904 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr rc(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rapid-commit", rc);
}
#line 1746 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 237:
#line 913 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 1757 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 238:
#line 918 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1766 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 243:
#line 935 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1776 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 244:
#line 939 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1784 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 245:
#line 946 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1794 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 246:
#line 950 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1802 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 260:
#line 976 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr code(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 1811 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 262:
#line 983 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1819 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 263:
#line 985 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 1829 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 264:
#line 991 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1837 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 265:
#line 993 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 1847 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 266:
#line 999 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1855 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 267:
#line 1001 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr space(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 1865 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 269:
#line 1009 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1873 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 270:
#line 1011 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr encap(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 1883 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 271:
#line 1017 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr array(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 1892 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 272:
#line 1026 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 1903 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 273:
#line 1031 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1912 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 278:
#line 1050 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1922 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 279:
#line 1054 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1930 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 280:
#line 1061 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1940 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 281:
#line 1065 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1948 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 293:
#line 1094 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1956 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 294:
#line 1096 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr data(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 1966 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 297:
#line 1106 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr space(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", space);
}
#line 1975 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 298:
#line 1114 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 1986 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 299:
#line 1119 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1995 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 304:
#line 1134 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2005 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 305:
#line 1138 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2013 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 306:
#line 1142 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2023 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 307:
#line 1146 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 2031 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 314:
#line 1160 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2039 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 315:
#line 1162 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr pool(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 2049 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 316:
#line 1168 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2057 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 317:
#line 1170 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("user-context", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2066 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 318:
#line 1178 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pd-pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.PD_POOLS);
}
#line 2077 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 319:
#line 1183 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2086 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 324:
#line 1198 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2096 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 325:
#line 1202 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2104 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 326:
#line 1206 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the pd-pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2114 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 327:
#line 1210 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 2122 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 338:
#line 1228 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2130 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 339:
#line 1230 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix", prf);
    ctx.leave();
}
#line 2140 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 340:
#line 1236 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix-len", prf);
}
#line 2149 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 341:
#line 1241 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2157 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 342:
#line 1243 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix", prf);
    ctx.leave();
}
#line 2167 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 343:
#line 1249 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix-len", prf);
}
#line 2176 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 344:
#line 1254 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr deleg(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("delegated-len", deleg);
}
#line 2185 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 345:
#line 1262 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 2196 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 346:
#line 1267 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2205 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 351:
#line 1280 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2215 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 352:
#line 1284 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2223 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 353:
#line 1288 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2233 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 354:
#line 1292 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 2241 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 367:
#line 1315 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-addresses", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2252 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 368:
#line 1320 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2261 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 369:
#line 1325 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefixes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2272 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 370:
#line 1330 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2281 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 371:
#line 1335 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2289 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 372:
#line 1337 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr d(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 2299 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 373:
#line 1343 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2307 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 374:
#line 1345 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 2317 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 375:
#line 1351 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2325 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 376:
#line 1353 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr host(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 2335 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 377:
#line 1359 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2346 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 378:
#line 1364 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2355 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 379:
#line 1372 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 2366 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 380:
#line 1377 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2375 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 381:
#line 1382 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2383 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 382:
#line 1384 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr ip(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", ip);
    ctx.leave();
}
#line 2393 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 383:
#line 1393 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 2404 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 384:
#line 1398 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2413 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 387:
#line 1407 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2423 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 388:
#line 1411 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2431 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 398:
#line 1431 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2439 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 399:
#line 1433 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr test(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 2449 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 400:
#line 1442 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-id", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SERVER_ID);
}
#line 2460 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 401:
#line 1447 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2469 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 411:
#line 1465 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.DUID_TYPE);
}
#line 2477 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 412:
#line 1467 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("type", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2486 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 413:
#line 1472 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("LLT", ctx.loc2pos(yystack_[0].location))); }
#line 2492 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 414:
#line 1473 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("EN", ctx.loc2pos(yystack_[0].location))); }
#line 2498 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 415:
#line 1474 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("LL", ctx.loc2pos(yystack_[0].location))); }
#line 2504 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 416:
#line 1477 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr htype(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("htype", htype);
}
#line 2513 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 417:
#line 1482 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2521 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 418:
#line 1484 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr id(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("identifier", id);
    ctx.leave();
}
#line 2531 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 419:
#line 1490 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("time", time);
}
#line 2540 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 420:
#line 1495 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enterprise-id", time);
}
#line 2549 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 421:
#line 1502 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 2558 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 422:
#line 1509 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 2569 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 423:
#line 1514 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2578 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 428:
#line 1527 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2586 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 429:
#line 1529 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr stype(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 2596 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 430:
#line 1535 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2604 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 431:
#line 1537 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 2614 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 432:
#line 1545 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 2625 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 433:
#line 1550 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2634 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 434:
#line 1555 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2644 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 435:
#line 1559 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 2652 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 453:
#line 1584 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 2661 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 454:
#line 1589 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2669 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 455:
#line 1591 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("qualifying-suffix", s);
    ctx.leave();
}
#line 2679 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 456:
#line 1597 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2687 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 457:
#line 1599 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 2697 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 458:
#line 1605 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 2706 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 459:
#line 1610 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2714 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 460:
#line 1612 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 2724 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 461:
#line 1618 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 2733 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 462:
#line 1623 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 2742 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 463:
#line 1628 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 2750 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 464:
#line 1630 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2759 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 465:
#line 1636 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 2765 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 466:
#line 1637 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 2771 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 467:
#line 1640 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NCR_FORMAT);
}
#line 2779 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 468:
#line 1642 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 2789 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 469:
#line 1648 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-include-fqdn", b);
}
#line 2798 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 470:
#line 1653 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-no-update", b);
}
#line 2807 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 471:
#line 1658 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-client-update", b);
}
#line 2816 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 472:
#line 1663 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 2824 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 473:
#line 1665 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("replace-client-name", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2833 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 474:
#line 1671 "dhcp6_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("when-present", ctx.loc2pos(yystack_[0].location))); 
      }
#line 2841 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 475:
#line 1674 "dhcp6_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location)));
      }
#line 2849 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 476:
#line 1677 "dhcp6_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("always", ctx.loc2pos(yystack_[0].location)));
      }
#line 2857 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 477:
#line 1680 "dhcp6_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("when-not-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 2865 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 478:
#line 1683 "dhcp6_parser.yy" // lalr1.cc:859
    {
      error(yystack_[0].location, "boolean values for the replace-client-name are "
                "no longer supported");
      }
#line 2874 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 479:
#line 1689 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2882 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 480:
#line 1691 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("generated-prefix", s);
    ctx.leave();
}
#line 2892 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 481:
#line 1699 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2900 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 482:
#line 1701 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("Dhcp4", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2909 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 483:
#line 1706 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2917 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 484:
#line 1708 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("DhcpDdns", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2926 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 485:
#line 1718 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Logging", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.LOGGING);
}
#line 2937 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 486:
#line 1723 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2946 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 490:
#line 1740 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 2957 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 491:
#line 1745 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2966 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 494:
#line 1757 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 2976 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 495:
#line 1761 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2984 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 503:
#line 1776 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr dl(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 2993 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 504:
#line 1781 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3001 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 505:
#line 1783 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 3011 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 506:
#line 1789 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 3022 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 507:
#line 1794 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3031 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 510:
#line 1803 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3041 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 511:
#line 1807 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 3049 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 514:
#line 1815 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3057 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 515:
#line 1817 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 3067 "dhcp6_parser.cc" // lalr1.cc:859
    break;


#line 3071 "dhcp6_parser.cc" // lalr1.cc:859
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


  const short int Dhcp6Parser::yypact_ninf_ = -486;

  const signed char Dhcp6Parser::yytable_ninf_ = -1;

  const short int
  Dhcp6Parser::yypact_[] =
  {
      63,  -486,  -486,  -486,  -486,  -486,  -486,  -486,  -486,  -486,
    -486,  -486,  -486,    50,    19,    67,   116,   122,   131,   137,
     148,   150,   195,   196,   213,   214,  -486,  -486,  -486,  -486,
    -486,  -486,  -486,  -486,  -486,  -486,  -486,  -486,  -486,  -486,
    -486,  -486,  -486,  -486,  -486,  -486,  -486,  -486,  -486,  -486,
    -486,  -486,  -486,  -486,  -486,  -486,  -486,  -486,  -486,  -486,
      19,   -51,    17,    31,    92,    23,    -8,    48,   104,    32,
      -5,   -28,   107,  -486,   259,   249,   254,   276,   269,  -486,
    -486,  -486,  -486,   281,  -486,    83,  -486,  -486,  -486,  -486,
    -486,  -486,  -486,  -486,   282,   288,   289,   291,   293,  -486,
    -486,  -486,  -486,  -486,  -486,  -486,  -486,  -486,  -486,   295,
    -486,  -486,  -486,   118,  -486,  -486,  -486,  -486,  -486,  -486,
    -486,  -486,  -486,  -486,  -486,  -486,  -486,  -486,  -486,  -486,
    -486,  -486,  -486,  -486,  -486,  -486,  -486,   296,  -486,  -486,
    -486,  -486,  -486,  -486,   297,   308,  -486,  -486,  -486,  -486,
    -486,  -486,  -486,  -486,  -486,   119,  -486,  -486,  -486,  -486,
    -486,  -486,  -486,  -486,  -486,  -486,  -486,  -486,  -486,  -486,
    -486,  -486,  -486,   127,  -486,  -486,  -486,  -486,   309,  -486,
     310,   311,  -486,  -486,  -486,   129,  -486,  -486,  -486,  -486,
    -486,  -486,  -486,  -486,  -486,  -486,  -486,  -486,  -486,  -486,
     312,   313,  -486,  -486,  -486,  -486,  -486,  -486,  -486,  -486,
    -486,   314,  -486,  -486,  -486,   315,  -486,  -486,   316,   319,
    -486,  -486,  -486,  -486,  -486,  -486,  -486,  -486,  -486,  -486,
    -486,   321,  -486,  -486,  -486,  -486,   318,   320,  -486,  -486,
    -486,  -486,  -486,  -486,  -486,  -486,  -486,   161,  -486,  -486,
    -486,   323,  -486,  -486,   324,  -486,   325,   326,  -486,  -486,
     327,   328,   329,  -486,  -486,  -486,   216,  -486,  -486,  -486,
    -486,  -486,  -486,  -486,  -486,  -486,  -486,  -486,  -486,  -486,
    -486,  -486,  -486,    19,    19,  -486,   157,   330,   331,   332,
     333,  -486,    17,  -486,   334,   335,   336,   160,   177,   201,
     202,   203,   340,   341,   342,   343,   344,   345,   346,   347,
     348,   349,   215,   350,   352,    31,  -486,   353,  -486,    -6,
     354,   355,   356,   357,   358,   223,   222,   361,   362,   363,
     364,    23,  -486,   365,   366,    -8,  -486,   367,   234,   368,
     235,   237,    48,  -486,   369,   372,   374,   375,   376,   377,
    -486,   104,   378,   379,   244,   381,   382,   383,   247,  -486,
      32,   384,   250,  -486,    -5,   386,   387,   -36,  -486,   251,
     390,   391,   261,   392,   262,   263,   395,   396,   265,   266,
     267,   400,   401,   107,  -486,  -486,  -486,   402,   403,   404,
      19,    19,  -486,   405,   406,   407,  -486,  -486,  -486,  -486,
    -486,   410,   411,   412,   413,   414,   415,   416,   417,   418,
     421,  -486,   422,   425,  -486,   419,  -486,  -486,  -486,  -486,
     426,   420,  -486,  -486,  -486,   428,   430,   299,   301,   302,
    -486,  -486,   303,   304,   431,   438,  -486,   307,   440,  -486,
     317,  -486,   322,  -486,  -486,  -486,   419,   419,   419,   337,
     338,   339,  -486,   351,   359,  -486,   360,   370,   371,  -486,
    -486,   373,  -486,  -486,   380,    19,  -486,  -486,   385,   388,
    -486,   389,  -486,  -486,   -55,   393,  -486,  -486,  -486,    -3,
     394,  -486,    19,    31,   397,  -486,  -486,    92,   125,   125,
     442,   443,   444,   -32,    19,    95,    44,   445,    98,    28,
     179,   107,  -486,  -486,   449,  -486,    -6,   447,   448,  -486,
    -486,  -486,  -486,  -486,   450,   399,  -486,  -486,  -486,  -486,
    -486,  -486,  -486,  -486,  -486,  -486,  -486,  -486,  -486,  -486,
    -486,  -486,  -486,  -486,  -486,  -486,  -486,  -486,  -486,  -486,
    -486,  -486,  -486,  -486,  -486,  -486,  -486,  -486,  -486,  -486,
     219,  -486,   220,  -486,  -486,   451,  -486,  -486,  -486,  -486,
     456,   458,   459,   460,   461,  -486,  -486,  -486,   226,  -486,
    -486,  -486,  -486,  -486,  -486,  -486,  -486,  -486,  -486,  -486,
    -486,  -486,   229,  -486,   462,   463,  -486,  -486,   464,   466,
    -486,  -486,   465,   471,  -486,  -486,  -486,    81,  -486,  -486,
    -486,   469,  -486,  -486,   102,  -486,  -486,  -486,   256,  -486,
     473,   477,  -486,   478,   479,   480,   481,   482,   483,   230,
    -486,  -486,  -486,  -486,  -486,  -486,  -486,  -486,  -486,   484,
     487,   488,  -486,  -486,   232,  -486,  -486,  -486,  -486,  -486,
    -486,  -486,  -486,   233,  -486,  -486,  -486,   236,   398,   408,
    -486,  -486,   475,   490,  -486,  -486,   489,   491,  -486,  -486,
     494,   493,  -486,  -486,   495,  -486,   497,   397,  -486,  -486,
     498,   500,   501,   502,   409,   423,   424,   427,   432,   504,
     507,   125,  -486,  -486,    23,  -486,   442,    32,  -486,   443,
      -5,  -486,   444,   -32,  -486,  -486,    95,  -486,    44,  -486,
     -28,  -486,   445,   433,   434,   435,   436,   437,   439,    98,
    -486,   509,   510,   441,   446,   452,    28,  -486,   511,   512,
     179,  -486,  -486,  -486,   514,   515,  -486,    -8,  -486,   447,
      48,  -486,   448,   104,  -486,   450,   517,  -486,   492,  -486,
     292,   429,   454,   455,  -486,  -486,  -486,  -486,  -486,   457,
     467,  -486,   239,  -486,   518,  -486,   521,  -486,  -486,  -486,
    -486,   242,  -486,  -486,  -486,  -486,  -486,  -486,  -486,  -486,
      97,   468,  -486,  -486,  -486,  -486,   470,   472,  -486,  -486,
     474,   245,  -486,   246,  -486,   522,  -486,   476,   516,  -486,
    -486,  -486,  -486,  -486,  -486,  -486,  -486,  -486,  -486,  -486,
    -486,  -486,  -486,  -486,  -486,  -486,  -486,  -486,  -486,  -486,
    -486,  -486,  -486,  -486,  -486,  -486,   260,  -486,    65,   516,
    -486,  -486,   527,  -486,  -486,  -486,   248,  -486,  -486,  -486,
    -486,  -486,   528,   486,   530,    65,  -486,   520,  -486,   485,
    -486,   529,  -486,  -486,   264,  -486,   496,   529,  -486,  -486,
     252,  -486,  -486,   531,   496,  -486,   503,  -486,  -486
  };

  const unsigned short int
  Dhcp6Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,    24,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     1,    41,    34,    30,
      29,    26,    27,    28,    33,     3,    31,    32,    54,     5,
      65,     7,    98,     9,   204,    11,   306,    13,   326,    15,
     353,    17,   245,    19,   280,    21,   169,    23,   434,    25,
      43,    37,     0,     0,     0,     0,     0,     0,   355,   247,
     282,     0,     0,    45,     0,    44,     0,     0,    38,    63,
     485,   481,   483,     0,    62,     0,    56,    58,    60,    61,
      59,    96,   102,   104,     0,     0,     0,     0,     0,   196,
     237,   272,   144,   159,   152,   383,   161,   180,   400,     0,
     422,   432,    90,     0,    67,    69,    70,    71,    72,    73,
      75,    76,    77,    78,    80,    79,    84,    85,    74,    82,
      83,    81,    86,    87,    88,    89,   100,     0,   387,   298,
     318,   225,   227,   229,     0,     0,   233,   231,   345,   379,
     224,   208,   209,   210,   211,     0,   206,   215,   216,   217,
     220,   222,   218,   219,   212,   213,   214,   221,   223,   314,
     316,   313,   311,     0,   308,   310,   312,   338,     0,   341,
       0,     0,   337,   333,   336,     0,   328,   330,   331,   334,
     335,   332,   377,   367,   369,   371,   373,   375,   366,   365,
       0,   356,   357,   361,   362,   359,   363,   364,   360,   262,
     134,     0,   266,   264,   269,     0,   258,   259,     0,   248,
     249,   251,   261,   252,   253,   254,   268,   255,   256,   257,
     293,     0,   291,   292,   295,   296,     0,   283,   284,   286,
     287,   288,   289,   290,   176,   178,   173,     0,   171,   174,
     175,     0,   454,   456,     0,   459,     0,     0,   463,   467,
       0,     0,     0,   472,   479,   452,     0,   436,   438,   439,
     440,   441,   442,   443,   444,   445,   446,   447,   448,   449,
     450,   451,    42,     0,     0,    35,     0,     0,     0,     0,
       0,    53,     0,    55,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    66,     0,    99,   389,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   205,     0,     0,     0,   307,     0,     0,     0,
       0,     0,     0,   327,     0,     0,     0,     0,     0,     0,
     354,     0,     0,     0,     0,     0,     0,     0,     0,   246,
       0,     0,     0,   281,     0,     0,     0,     0,   170,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   435,    46,    39,     0,     0,     0,
       0,     0,    57,     0,     0,     0,    91,    92,    93,    94,
      95,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   421,     0,     0,    68,     0,   398,   396,   397,   395,
       0,   390,   391,   393,   394,     0,     0,     0,     0,     0,
     235,   236,     0,     0,     0,     0,   207,     0,     0,   309,
       0,   340,     0,   343,   344,   329,     0,     0,     0,     0,
       0,     0,   358,     0,     0,   260,     0,     0,     0,   271,
     250,     0,   297,   285,     0,     0,   172,   453,     0,     0,
     458,     0,   461,   462,     0,     0,   469,   470,   471,     0,
       0,   437,     0,     0,     0,   482,   484,     0,     0,     0,
     198,   239,   274,     0,    43,     0,     0,   163,     0,     0,
       0,     0,    47,   101,     0,   388,     0,   300,   320,   226,
     228,   230,   234,   232,   347,     0,   315,    36,   317,   339,
     342,   378,   368,   370,   372,   374,   376,   263,   135,   267,
     265,   270,   294,   177,   179,   455,   457,   460,   465,   466,
     464,   468,   474,   475,   476,   477,   478,   473,   480,    40,
       0,   490,     0,   487,   489,     0,   121,   127,   129,   131,
       0,     0,     0,     0,     0,   140,   142,   120,     0,   106,
     108,   109,   110,   111,   112,   113,   114,   115,   116,   117,
     118,   119,     0,   202,     0,   199,   200,   243,     0,   240,
     241,   278,     0,   275,   276,   150,   151,     0,   146,   148,
     149,     0,   158,   156,     0,   154,   157,   385,     0,   167,
       0,   164,   165,     0,     0,     0,     0,     0,     0,     0,
     182,   184,   185,   186,   187,   188,   189,   411,   417,     0,
       0,     0,   410,   409,     0,   402,   404,   407,   405,   406,
     408,   428,   430,     0,   424,   426,   427,     0,    49,     0,
     392,   304,     0,   301,   302,   324,     0,   321,   322,   351,
       0,   348,   349,   381,     0,    64,     0,     0,   486,    97,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   103,   105,     0,   197,     0,   247,   238,     0,
     282,   273,     0,     0,   145,   160,     0,   153,     0,   384,
       0,   162,     0,     0,     0,     0,     0,     0,     0,     0,
     181,     0,     0,     0,     0,     0,     0,   401,     0,     0,
       0,   423,   433,    51,     0,    50,   399,     0,   299,     0,
       0,   319,     0,   355,   346,     0,     0,   380,     0,   488,
       0,     0,     0,     0,   133,   136,   137,   138,   139,     0,
       0,   107,     0,   201,     0,   242,     0,   277,   147,   155,
     386,     0,   166,   190,   191,   192,   193,   194,   195,   183,
       0,     0,   416,   419,   420,   403,     0,     0,   425,    48,
       0,     0,   303,     0,   323,     0,   350,     0,     0,   123,
     124,   125,   126,   122,   128,   130,   132,   141,   143,   203,
     244,   279,   168,   413,   414,   415,   412,   418,   429,   431,
      52,   305,   325,   352,   382,   494,     0,   492,     0,     0,
     491,   506,     0,   504,   502,   498,     0,   496,   500,   501,
     499,   493,     0,     0,     0,     0,   495,     0,   503,     0,
     497,     0,   505,   510,     0,   508,     0,     0,   507,   514,
       0,   512,   509,     0,     0,   511,     0,   513,   515
  };

  const short int
  Dhcp6Parser::yypgoto_[] =
  {
    -486,  -486,  -486,  -486,  -486,  -486,  -486,  -486,  -486,  -486,
    -486,  -486,  -486,  -486,     7,  -486,    29,  -486,  -486,  -486,
    -486,  -486,  -486,    45,  -486,  -169,  -486,  -486,  -486,   -62,
    -486,  -486,  -486,   253,  -486,  -486,  -486,  -486,    39,   225,
     -63,   -50,   -49,   -43,  -486,  -486,  -486,  -486,  -486,    51,
    -486,  -486,  -486,  -486,  -486,    52,  -139,  -486,  -486,  -486,
    -486,  -486,  -486,  -486,  -486,  -486,  -486,   -58,  -486,  -485,
    -486,  -486,  -486,  -486,  -486,  -486,  -486,  -486,  -486,  -486,
    -150,  -470,  -486,  -486,  -486,  -486,  -152,  -486,  -486,  -486,
    -486,  -486,  -486,  -486,  -156,  -486,  -486,  -486,  -149,   181,
    -486,  -486,  -486,  -486,  -486,  -486,  -486,  -159,  -486,  -486,
    -486,  -486,  -486,  -486,  -486,  -486,  -486,  -486,  -134,  -486,
    -486,  -486,  -131,   224,  -486,  -486,  -486,  -486,  -486,  -486,
    -473,  -486,  -486,  -486,  -486,  -486,  -486,  -486,  -486,  -486,
    -135,  -486,  -486,  -486,  -130,  -486,   198,  -486,   -59,  -486,
    -486,  -486,  -486,  -486,   -57,  -486,  -486,  -486,  -486,  -486,
     -48,  -486,  -486,  -486,  -136,  -486,  -486,  -486,  -129,  -486,
     199,  -486,  -486,  -486,  -486,  -486,  -486,  -486,  -486,  -486,
    -486,  -170,  -486,  -486,  -486,  -167,   227,  -486,  -486,   -66,
    -486,  -486,  -486,  -486,  -486,  -166,  -486,  -486,  -486,  -163,
     228,  -486,  -486,  -486,  -486,  -486,  -486,  -486,  -486,  -486,
    -486,  -486,  -164,  -486,  -486,  -486,  -155,  -486,   231,  -486,
    -486,  -486,  -486,  -486,  -486,  -486,  -486,  -486,  -486,  -486,
    -486,  -486,  -486,  -486,  -486,  -486,  -486,  -486,  -486,  -486,
    -486,    74,  -486,  -486,  -486,  -486,  -486,  -486,  -133,  -486,
    -486,  -486,  -486,  -486,  -486,  -486,  -486,  -486,  -486,  -486,
    -486,  -132,  -486,  -486,  -486,  -486,  -486,  -486,  -486,  -486,
      84,   204,  -486,  -486,  -486,  -486,  -486,  -486,  -486,  -486,
    -486,  -486,  -486,  -486,  -486,  -486,  -486,  -486,  -486,  -486,
    -486,  -486,  -486,  -486,  -486,  -486,  -486,  -486,  -486,  -486,
    -486,  -486,   -83,  -486,  -486,  -486,  -230,  -486,  -486,  -245,
    -486,  -486,  -486,  -486,  -486,  -486,  -256,  -486,  -486,  -259,
    -486
  };

  const short int
  Dhcp6Parser::yydefgoto_[] =
  {
      -1,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    73,    35,    36,    61,   518,    77,
      78,    37,    60,    74,    75,   503,   648,   724,   725,   112,
      39,    62,    85,    86,    87,   287,    41,    63,   113,   114,
     115,   116,   117,   118,   119,   120,   294,    43,    64,   137,
     317,   121,   295,   122,   296,   568,   569,   570,   670,   793,
     571,   671,   572,   672,   573,   673,   574,   217,   353,   576,
     577,   578,   579,   580,   679,   581,   680,   123,   305,   597,
     598,   599,   600,   124,   307,   604,   605,   606,   125,   306,
     126,   309,   610,   611,   612,   700,    57,    71,   247,   248,
     249,   365,   250,   366,   127,   310,   619,   620,   621,   622,
     623,   624,   625,   626,   128,   302,   584,   585,   586,   684,
      45,    65,   155,   156,   157,   322,   158,   323,   159,   324,
     160,   328,   161,   327,   162,   163,   129,   303,   588,   589,
     590,   687,    53,    69,   218,   219,   220,   221,   222,   223,
     224,   352,   225,   356,   226,   355,   227,   228,   357,   229,
     130,   304,   592,   593,   594,   690,    55,    70,   236,   237,
     238,   239,   240,   361,   241,   242,   243,   165,   320,   652,
     653,   654,   727,    47,    66,   173,   174,   175,   333,   176,
     334,   166,   321,   656,   657,   658,   730,    49,    67,   185,
     186,   187,   337,   188,   189,   339,   190,   191,   167,   329,
     660,   661,   662,   733,    51,    68,   200,   201,   202,   203,
     345,   204,   346,   205,   347,   206,   348,   207,   349,   208,
     344,   168,   330,   664,   736,   131,   308,   608,   319,   420,
     421,   422,   423,   424,   504,   132,   311,   634,   635,   636,
     711,   806,   637,   638,   712,   639,   640,   133,   134,   313,
     643,   644,   645,   718,   646,   719,   135,   314,    59,    72,
     266,   267,   268,   269,   370,   270,   371,   271,   272,   373,
     273,   274,   275,   376,   540,   276,   377,   277,   278,   279,
     280,   381,   547,   281,   382,    88,   289,    89,   290,    90,
     288,   552,   553,   554,   666,   816,   817,   818,   826,   827,
     828,   829,   834,   830,   832,   844,   845,   846,   850,   851,
     853
  };

  const unsigned short int
  Dhcp6Parser::yytable_[] =
  {
      84,   184,   151,   150,   171,   182,   198,   216,   232,   246,
     265,   234,   233,   235,   633,   152,   153,   164,   172,   183,
     199,    34,   154,   607,    27,   603,    28,    79,    29,   101,
     138,   101,   210,   210,   230,   211,   212,   231,   595,   169,
     244,   245,    91,   627,    92,    93,   170,   209,   244,   245,
      26,   138,   561,    94,    95,    96,    97,   538,   539,   416,
     101,    94,    95,    96,    97,    98,    99,   100,   101,   139,
     210,   140,   211,   212,    38,   213,   214,   215,   141,   142,
     143,   144,   145,   146,   693,   101,   292,   694,    76,   147,
     148,   293,   102,   103,   104,   105,   149,   177,   178,   179,
     180,   181,   170,   210,   136,   696,   106,   596,   697,   107,
     147,    83,   542,   543,   544,   545,   108,   628,   629,   630,
     631,   315,   331,    40,   109,   110,   316,   332,   111,    42,
     335,    83,   342,    83,    83,   336,    80,   343,    44,   546,
     556,   101,    81,    82,    46,   557,   558,   559,   560,   561,
     562,   563,   564,   565,   566,    48,    83,    50,    30,    31,
      32,    33,    83,   210,   367,   595,   602,    83,   192,   368,
      83,    83,   193,   194,   195,   196,   197,   613,   614,   615,
     616,   617,   618,   803,   804,   805,   821,    83,   822,   823,
       1,     2,     3,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    52,    54,    83,   251,   252,   253,   254,   255,
     256,   257,   258,   259,   260,   261,   262,   263,   264,   383,
      56,    58,   315,   667,   384,   760,   603,   665,   668,   681,
      84,   633,   681,   709,   682,   716,   720,   683,   710,   383,
     717,   721,   331,    83,   722,   367,    83,   799,   335,   342,
     802,   835,   283,   811,   812,   854,   836,   417,   284,   698,
     855,   418,   699,   819,    83,   282,   820,   847,   151,   150,
     848,   419,   286,   171,   641,   642,   184,   521,   522,   523,
     182,   152,   153,   164,   285,   291,   297,   172,   154,   198,
     385,   386,   298,   299,   183,   300,   387,   301,   216,   312,
     396,   325,   232,   199,   318,   234,   233,   235,   789,   790,
     791,   792,   326,   338,   340,   341,   351,   397,   354,   358,
     350,   265,   360,   364,   359,   362,   363,   369,   372,   374,
     375,   378,   379,   380,   388,   389,   390,   391,   393,   394,
     395,   398,   399,   400,   401,   402,   403,   404,   405,   406,
     407,   408,   409,   410,   412,   411,   413,   415,   425,   426,
     427,   428,   429,   430,   431,   432,   433,   434,   435,   437,
     438,   440,   442,   446,   441,   443,   447,   444,   448,   449,
     450,   451,   453,   454,   455,   456,   457,   458,   461,   459,
     464,   465,   462,   467,   468,   469,   471,   485,   486,   474,
     475,   470,   472,   473,   479,   480,   482,   476,   477,   478,
     483,   484,   487,   488,   489,   490,   491,   492,   493,   494,
     495,   496,   497,   506,   502,   498,   567,   567,   499,   500,
     575,   575,   501,   507,   505,   508,   514,   632,   509,   265,
     510,   511,   512,   513,   417,   515,   516,    28,   418,   583,
     587,   591,   609,   649,   651,   655,   519,   659,   419,   669,
     674,   520,   675,   676,   677,   678,   686,   517,   685,   689,
     688,   691,   534,   663,   692,   695,   524,   525,   526,   701,
     702,   728,   703,   704,   705,   706,   707,   708,   713,   549,
     527,   714,   715,   729,   732,   731,   735,   788,   528,   529,
     734,   738,   740,   737,   741,   742,   743,   541,   749,   530,
     531,   750,   532,   770,   771,   776,   777,   551,   780,   533,
     779,   787,   550,   815,   535,   841,   800,   536,   537,   801,
     813,   833,   837,   548,   839,   856,   843,   723,   555,   601,
     414,   582,   751,   758,   759,   392,   762,   726,   466,   744,
     769,   761,   753,   752,   755,   436,   757,   754,   460,   782,
     781,   756,   439,   463,   746,   745,   784,   783,   794,   747,
     445,   786,   748,   763,   764,   765,   766,   767,   785,   768,
     650,   772,   452,   775,   739,   647,   773,   481,   778,   831,
     840,   852,   774,   795,   796,   857,   797,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   798,   807,     0,   808,
       0,   809,     0,   810,     0,   814,     0,     0,   849,   567,
       0,   151,   150,   575,   842,   216,   838,     0,   232,     0,
       0,   234,   233,   235,   152,   153,   164,     0,   246,     0,
       0,   154,   858,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   632,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   184,   171,     0,     0,   182,     0,
       0,   198,     0,     0,     0,     0,     0,     0,     0,   172,
       0,     0,   183,     0,     0,   199,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   824,     0,     0,     0,
     825,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   824,     0,     0,     0,   825
  };

  const short int
  Dhcp6Parser::yycheck_[] =
  {
      62,    67,    65,    65,    66,    67,    68,    69,    70,    71,
      72,    70,    70,    70,   499,    65,    65,    65,    66,    67,
      68,    14,    65,   496,     5,   495,     7,    10,     9,    37,
       7,    37,    38,    38,    39,    40,    41,    42,    70,    47,
      76,    77,    11,    15,    13,    14,    54,    15,    76,    77,
       0,     7,    24,    30,    31,    32,    33,   112,   113,    65,
      37,    30,    31,    32,    33,    34,    35,    36,    37,    46,
      38,    48,    40,    41,     7,    43,    44,    45,    55,    56,
      57,    58,    59,    60,     3,    37,     3,     6,   139,    66,
      67,     8,    61,    62,    63,    64,    73,    49,    50,    51,
      52,    53,    54,    38,    12,     3,    75,   139,     6,    78,
      66,   139,   115,   116,   117,   118,    85,    89,    90,    91,
      92,     3,     3,     7,    93,    94,     8,     8,    97,     7,
       3,   139,     3,   139,   139,     8,   119,     8,     7,   142,
      15,    37,   125,   126,     7,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,     7,   139,     7,   139,   140,
     141,   142,   139,    38,     3,    70,    71,   139,    64,     8,
     139,   139,    68,    69,    70,    71,    72,    79,    80,    81,
      82,    83,    84,    86,    87,    88,   121,   139,   123,   124,
     127,   128,   129,   130,   131,   132,   133,   134,   135,   136,
     137,   138,     7,     7,   139,    98,    99,   100,   101,   102,
     103,   104,   105,   106,   107,   108,   109,   110,   111,     3,
       7,     7,     3,     3,     8,   698,   696,     8,     8,     3,
     292,   716,     3,     3,     8,     3,     3,     8,     8,     3,
       8,     8,     3,   139,     8,     3,   139,     8,     3,     3,
       8,     3,     3,     8,     8,     3,     8,   319,     4,     3,
       8,   319,     6,     3,   139,     6,     6,     3,   331,   331,
       6,   319,     3,   335,    95,    96,   342,   446,   447,   448,
     342,   331,   331,   331,     8,     4,     4,   335,   331,   351,
     283,   284,     4,     4,   342,     4,   139,     4,   360,     4,
     140,     4,   364,   351,     8,   364,   364,   364,    16,    17,
      18,    19,     4,     4,     4,     4,     3,   140,     4,     4,
       8,   383,     3,     3,     8,     4,     8,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,   140,   140,   140,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,   140,     4,     4,     4,     4,
       4,     4,     4,   140,   142,     4,     4,     4,     4,     4,
       4,     4,     4,     4,   140,   140,     4,   140,     4,     4,
       4,     4,     4,     4,   140,     4,     4,     4,     4,   142,
       4,     4,   142,   142,     4,     4,     4,   390,   391,     4,
       4,   140,   140,   140,     4,     4,     4,   142,   142,   142,
       7,     7,     7,     7,     7,     5,     5,     5,     5,     5,
       5,     5,     5,     3,     5,     7,   488,   489,     7,     7,
     488,   489,     7,     5,     8,     5,     5,   499,   139,   501,
     139,   139,   139,   139,   506,     7,   139,     7,   506,     7,
       7,     7,     7,     4,     7,     7,   139,     7,   506,     8,
       4,   139,     4,     4,     4,     4,     3,   438,     6,     3,
       6,     6,   465,    74,     3,     6,   139,   139,   139,     6,
       3,     6,     4,     4,     4,     4,     4,     4,     4,   482,
     139,     4,     4,     3,     3,     6,     3,     5,   139,   139,
       6,     4,     4,     8,     4,     4,     4,   114,     4,   139,
     139,     4,   139,     4,     4,     4,     4,   120,     3,   139,
       6,     4,   483,     7,   139,     5,     8,   139,   139,     8,
       8,     4,     4,   139,     4,     4,     7,   139,   487,   494,
     315,   489,   681,   693,   696,   292,   702,   139,   367,   140,
     709,   700,   686,   684,   689,   331,   692,   687,   360,   729,
     727,   690,   335,   364,   140,   142,   732,   730,   139,   142,
     342,   735,   140,   140,   140,   140,   140,   140,   733,   140,
     506,   140,   351,   716,   667,   501,   140,   383,   720,   819,
     835,   847,   140,   139,   139,   854,   139,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   139,   139,    -1,   139,
      -1,   139,    -1,   139,    -1,   139,    -1,    -1,   122,   681,
      -1,   684,   684,   681,   139,   687,   140,    -1,   690,    -1,
      -1,   690,   690,   690,   684,   684,   684,    -1,   700,    -1,
      -1,   684,   139,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   716,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   730,   727,    -1,    -1,   730,    -1,
      -1,   733,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   727,
      -1,    -1,   730,    -1,    -1,   733,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   818,    -1,    -1,    -1,
     818,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   835,    -1,    -1,    -1,   835
  };

  const unsigned short int
  Dhcp6Parser::yystos_[] =
  {
       0,   127,   128,   129,   130,   131,   132,   133,   134,   135,
     136,   137,   138,   144,   145,   146,   147,   148,   149,   150,
     151,   152,   153,   154,   155,   156,     0,     5,     7,     9,
     139,   140,   141,   142,   157,   158,   159,   164,     7,   173,
       7,   179,     7,   190,     7,   263,     7,   326,     7,   340,
       7,   357,     7,   285,     7,   309,     7,   239,     7,   411,
     165,   160,   174,   180,   191,   264,   327,   341,   358,   286,
     310,   240,   412,   157,   166,   167,   139,   162,   163,    10,
     119,   125,   126,   139,   172,   175,   176,   177,   438,   440,
     442,    11,    13,    14,    30,    31,    32,    33,    34,    35,
      36,    37,    61,    62,    63,    64,    75,    78,    85,    93,
      94,    97,   172,   181,   182,   183,   184,   185,   186,   187,
     188,   194,   196,   220,   226,   231,   233,   247,   257,   279,
     303,   378,   388,   400,   401,   409,    12,   192,     7,    46,
      48,    55,    56,    57,    58,    59,    60,    66,    67,    73,
     172,   183,   184,   185,   186,   265,   266,   267,   269,   271,
     273,   275,   277,   278,   303,   320,   334,   351,   374,    47,
      54,   172,   303,   328,   329,   330,   332,    49,    50,    51,
      52,    53,   172,   303,   332,   342,   343,   344,   346,   347,
     349,   350,    64,    68,    69,    70,    71,    72,   172,   303,
     359,   360,   361,   362,   364,   366,   368,   370,   372,    15,
      38,    40,    41,    43,    44,    45,   172,   210,   287,   288,
     289,   290,   291,   292,   293,   295,   297,   299,   300,   302,
      39,    42,   172,   210,   291,   297,   311,   312,   313,   314,
     315,   317,   318,   319,    76,    77,   172,   241,   242,   243,
     245,    98,    99,   100,   101,   102,   103,   104,   105,   106,
     107,   108,   109,   110,   111,   172,   413,   414,   415,   416,
     418,   420,   421,   423,   424,   425,   428,   430,   431,   432,
     433,   436,     6,     3,     4,     8,     3,   178,   443,   439,
     441,     4,     3,     8,   189,   195,   197,     4,     4,     4,
       4,     4,   258,   280,   304,   221,   232,   227,   379,   234,
     248,   389,     4,   402,   410,     3,     8,   193,     8,   381,
     321,   335,   268,   270,   272,     4,     4,   276,   274,   352,
     375,     3,     8,   331,   333,     3,     8,   345,     4,   348,
       4,     4,     3,     8,   373,   363,   365,   367,   369,   371,
       8,     3,   294,   211,     4,   298,   296,   301,     4,     8,
       3,   316,     4,     8,     3,   244,   246,     3,     8,     4,
     417,   419,     4,   422,     4,     4,   426,   429,     4,     4,
       4,   434,   437,     3,     8,   157,   157,   139,     4,     4,
       4,     4,   176,     4,     4,     4,   140,   140,   140,   140,
     140,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,   140,     4,     4,   182,     4,    65,   172,   210,   303,
     382,   383,   384,   385,   386,     4,     4,     4,     4,     4,
     140,   142,     4,     4,     4,     4,   266,     4,     4,   329,
       4,   140,     4,   140,   140,   343,     4,     4,     4,     4,
       4,     4,   361,     4,     4,   140,     4,     4,     4,   142,
     289,     4,   142,   313,     4,     4,   242,   142,     4,     4,
     140,     4,   140,   140,     4,     4,   142,   142,   142,     4,
       4,   414,     4,     7,     7,   157,   157,     7,     7,     7,
       5,     5,     5,     5,     5,     5,     5,     5,     7,     7,
       7,     7,     5,   168,   387,     8,     3,     5,     5,   139,
     139,   139,   139,   139,     5,     7,   139,   159,   161,   139,
     139,   168,   168,   168,   139,   139,   139,   139,   139,   139,
     139,   139,   139,   139,   157,   139,   139,   139,   112,   113,
     427,   114,   115,   116,   117,   118,   142,   435,   139,   157,
     181,   120,   444,   445,   446,   192,    15,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,   172,   198,   199,
     200,   203,   205,   207,   209,   210,   212,   213,   214,   215,
     216,   218,   198,     7,   259,   260,   261,     7,   281,   282,
     283,     7,   305,   306,   307,    70,   139,   222,   223,   224,
     225,   166,    71,   224,   228,   229,   230,   273,   380,     7,
     235,   236,   237,    79,    80,    81,    82,    83,    84,   249,
     250,   251,   252,   253,   254,   255,   256,    15,    89,    90,
      91,    92,   172,   212,   390,   391,   392,   395,   396,   398,
     399,    95,    96,   403,   404,   405,   407,   413,   169,     4,
     384,     7,   322,   323,   324,     7,   336,   337,   338,     7,
     353,   354,   355,    74,   376,     8,   447,     3,     8,     8,
     201,   204,   206,   208,     4,     4,     4,     4,     4,   217,
     219,     3,     8,     8,   262,     6,     3,   284,     6,     3,
     308,     6,     3,     3,     6,     6,     3,     6,     3,     6,
     238,     6,     3,     4,     4,     4,     4,     4,     4,     3,
       8,   393,   397,     4,     4,     4,     3,     8,   406,   408,
       3,     8,     8,   139,   170,   171,   139,   325,     6,     3,
     339,     6,     3,   356,     6,     3,   377,     8,     4,   445,
       4,     4,     4,     4,   140,   142,   140,   142,   140,     4,
       4,   199,   265,   261,   287,   283,   311,   307,   223,   229,
     273,   241,   237,   140,   140,   140,   140,   140,   140,   250,
       4,     4,   140,   140,   140,   391,     4,     4,   404,     6,
       3,   328,   324,   342,   338,   359,   355,     4,     5,    16,
      17,    18,    19,   202,   139,   139,   139,   139,   139,     8,
       8,     8,     8,    86,    87,    88,   394,   139,   139,   139,
     139,     8,     8,     8,   139,     7,   448,   449,   450,     3,
       6,   121,   123,   124,   172,   210,   451,   452,   453,   454,
     456,   449,   457,     4,   455,     3,     8,     4,   140,     4,
     452,     5,   139,     7,   458,   459,   460,     3,     6,   122,
     461,   462,   459,   463,     3,     8,     4,   462,   139
  };

  const unsigned short int
  Dhcp6Parser::yyr1_[] =
  {
       0,   143,   145,   144,   146,   144,   147,   144,   148,   144,
     149,   144,   150,   144,   151,   144,   152,   144,   153,   144,
     154,   144,   155,   144,   156,   144,   157,   157,   157,   157,
     157,   157,   157,   158,   160,   159,   161,   162,   162,   163,
     163,   165,   164,   166,   166,   167,   167,   169,   168,   170,
     170,   171,   171,   172,   174,   173,   175,   175,   176,   176,
     176,   176,   176,   178,   177,   180,   179,   181,   181,   182,
     182,   182,   182,   182,   182,   182,   182,   182,   182,   182,
     182,   182,   182,   182,   182,   182,   182,   182,   182,   182,
     182,   183,   184,   185,   186,   187,   189,   188,   191,   190,
     193,   192,   195,   194,   197,   196,   198,   198,   199,   199,
     199,   199,   199,   199,   199,   199,   199,   199,   199,   199,
     199,   201,   200,   202,   202,   202,   202,   204,   203,   206,
     205,   208,   207,   209,   211,   210,   212,   213,   214,   215,
     217,   216,   219,   218,   221,   220,   222,   222,   223,   223,
     224,   225,   227,   226,   228,   228,   229,   229,   230,   232,
     231,   234,   233,   235,   235,   236,   236,   238,   237,   240,
     239,   241,   241,   241,   242,   242,   244,   243,   246,   245,
     248,   247,   249,   249,   250,   250,   250,   250,   250,   250,
     251,   252,   253,   254,   255,   256,   258,   257,   259,   259,
     260,   260,   262,   261,   264,   263,   265,   265,   266,   266,
     266,   266,   266,   266,   266,   266,   266,   266,   266,   266,
     266,   266,   266,   266,   266,   268,   267,   270,   269,   272,
     271,   274,   273,   276,   275,   277,   278,   280,   279,   281,
     281,   282,   282,   284,   283,   286,   285,   287,   287,   288,
     288,   289,   289,   289,   289,   289,   289,   289,   289,   290,
     291,   292,   294,   293,   296,   295,   298,   297,   299,   301,
     300,   302,   304,   303,   305,   305,   306,   306,   308,   307,
     310,   309,   311,   311,   312,   312,   313,   313,   313,   313,
     313,   313,   314,   316,   315,   317,   318,   319,   321,   320,
     322,   322,   323,   323,   325,   324,   327,   326,   328,   328,
     329,   329,   329,   329,   331,   330,   333,   332,   335,   334,
     336,   336,   337,   337,   339,   338,   341,   340,   342,   342,
     343,   343,   343,   343,   343,   343,   343,   343,   345,   344,
     346,   348,   347,   349,   350,   352,   351,   353,   353,   354,
     354,   356,   355,   358,   357,   359,   359,   360,   360,   361,
     361,   361,   361,   361,   361,   361,   361,   363,   362,   365,
     364,   367,   366,   369,   368,   371,   370,   373,   372,   375,
     374,   377,   376,   379,   378,   380,   380,   381,   273,   382,
     382,   383,   383,   384,   384,   384,   384,   385,   387,   386,
     389,   388,   390,   390,   391,   391,   391,   391,   391,   391,
     391,   393,   392,   394,   394,   394,   395,   397,   396,   398,
     399,   400,   402,   401,   403,   403,   404,   404,   406,   405,
     408,   407,   410,   409,   412,   411,   413,   413,   414,   414,
     414,   414,   414,   414,   414,   414,   414,   414,   414,   414,
     414,   414,   414,   415,   417,   416,   419,   418,   420,   422,
     421,   423,   424,   426,   425,   427,   427,   429,   428,   430,
     431,   432,   434,   433,   435,   435,   435,   435,   435,   437,
     436,   439,   438,   441,   440,   443,   442,   444,   444,   445,
     447,   446,   448,   448,   450,   449,   451,   451,   452,   452,
     452,   452,   452,   453,   455,   454,   457,   456,   458,   458,
     460,   459,   461,   461,   463,   462
  };

  const unsigned char
  Dhcp6Parser::yyr2_[] =
  {
       0,     2,     0,     3,     0,     3,     0,     3,     0,     3,
       0,     3,     0,     3,     0,     3,     0,     3,     0,     3,
       0,     3,     0,     3,     0,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     0,     4,     1,     0,     1,     3,
       5,     0,     4,     0,     1,     1,     3,     0,     4,     0,
       1,     1,     3,     2,     0,     4,     1,     3,     1,     1,
       1,     1,     1,     0,     6,     0,     4,     1,     3,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     3,     3,     3,     3,     3,     0,     6,     0,     4,
       0,     4,     0,     6,     0,     6,     1,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     0,     4,     1,     1,     1,     1,     0,     4,     0,
       4,     0,     4,     3,     0,     4,     3,     3,     3,     3,
       0,     4,     0,     4,     0,     6,     1,     3,     1,     1,
       1,     1,     0,     6,     1,     3,     1,     1,     1,     0,
       6,     0,     6,     0,     1,     1,     3,     0,     4,     0,
       4,     1,     3,     1,     1,     1,     0,     4,     0,     4,
       0,     6,     1,     3,     1,     1,     1,     1,     1,     1,
       3,     3,     3,     3,     3,     3,     0,     6,     0,     1,
       1,     3,     0,     4,     0,     4,     1,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     4,     3,     3,     0,     6,     0,
       1,     1,     3,     0,     4,     0,     4,     0,     1,     1,
       3,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       3,     1,     0,     4,     0,     4,     0,     4,     1,     0,
       4,     3,     0,     6,     0,     1,     1,     3,     0,     4,
       0,     4,     0,     1,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     0,     4,     1,     1,     3,     0,     6,
       0,     1,     1,     3,     0,     4,     0,     4,     1,     3,
       1,     1,     1,     1,     0,     4,     0,     4,     0,     6,
       0,     1,     1,     3,     0,     4,     0,     4,     1,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     0,     4,
       3,     0,     4,     3,     3,     0,     6,     0,     1,     1,
       3,     0,     4,     0,     4,     0,     1,     1,     3,     1,
       1,     1,     1,     1,     1,     1,     1,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       6,     0,     4,     0,     6,     1,     3,     0,     4,     0,
       1,     1,     3,     1,     1,     1,     1,     1,     0,     4,
       0,     6,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     0,     4,     1,     1,     1,     3,     0,     4,     3,
       3,     3,     0,     6,     1,     3,     1,     1,     0,     4,
       0,     4,     0,     6,     0,     4,     1,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     3,     0,     4,     0,     4,     3,     0,
       4,     3,     3,     0,     4,     1,     1,     0,     4,     3,
       3,     3,     0,     4,     1,     1,     1,     1,     1,     0,
       4,     0,     4,     0,     4,     0,     6,     1,     3,     1,
       0,     6,     1,     3,     0,     4,     1,     3,     1,     1,
       1,     1,     1,     3,     0,     4,     0,     6,     1,     3,
       0,     4,     1,     3,     0,     4
  };



  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a yyntokens_, nonterminals.
  const char*
  const Dhcp6Parser::yytname_[] =
  {
  "\"end of file\"", "error", "$undefined", "\",\"", "\":\"", "\"[\"",
  "\"]\"", "\"{\"", "\"}\"", "\"null\"", "\"Dhcp6\"",
  "\"interfaces-config\"", "\"interfaces\"", "\"lease-database\"",
  "\"hosts-database\"", "\"type\"", "\"memfile\"", "\"mysql\"",
  "\"postgresql\"", "\"cql\"", "\"user\"", "\"password\"", "\"host\"",
  "\"port\"", "\"persist\"", "\"lfc-interval\"", "\"readonly\"",
  "\"connect-timeout\"", "\"contact-points\"", "\"keyspace\"",
  "\"preferred-lifetime\"", "\"valid-lifetime\"", "\"renew-timer\"",
  "\"rebind-timer\"", "\"decline-probation-period\"", "\"subnet6\"",
  "\"option-def\"", "\"option-data\"", "\"name\"", "\"data\"", "\"code\"",
  "\"space\"", "\"csv-format\"", "\"record-types\"", "\"encapsulate\"",
  "\"array\"", "\"pools\"", "\"pool\"", "\"pd-pools\"", "\"prefix\"",
  "\"prefix-len\"", "\"excluded-prefix\"", "\"excluded-prefix-len\"",
  "\"delegated-len\"", "\"user-context\"", "\"subnet\"", "\"interface\"",
  "\"interface-id\"", "\"id\"", "\"rapid-commit\"", "\"reservation-mode\"",
  "\"mac-sources\"", "\"relay-supplied-options\"",
  "\"host-reservation-identifiers\"", "\"client-classes\"", "\"test\"",
  "\"client-class\"", "\"reservations\"", "\"ip-addresses\"",
  "\"prefixes\"", "\"duid\"", "\"hw-address\"", "\"hostname\"",
  "\"relay\"", "\"ip-address\"", "\"hooks-libraries\"", "\"library\"",
  "\"parameters\"", "\"expired-leases-processing\"",
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
  "\"debuglevel\"", "\"severity\"", "\"Dhcp4\"", "\"DhcpDdns\"",
  "TOPLEVEL_JSON", "TOPLEVEL_DHCP6", "SUB_DHCP6", "SUB_INTERFACES6",
  "SUB_SUBNET6", "SUB_POOL6", "SUB_PD_POOL", "SUB_RESERVATION",
  "SUB_OPTION_DEF", "SUB_OPTION_DATA", "SUB_HOOKS_LIBRARY",
  "SUB_DHCP_DDNS", "\"constant string\"", "\"integer\"",
  "\"floating point\"", "\"boolean\"", "$accept", "start", "$@1", "$@2",
  "$@3", "$@4", "$@5", "$@6", "$@7", "$@8", "$@9", "$@10", "$@11", "$@12",
  "value", "sub_json", "map2", "$@13", "map_value", "map_content",
  "not_empty_map", "list_generic", "$@14", "list_content",
  "not_empty_list", "list_strings", "$@15", "list_strings_content",
  "not_empty_list_strings", "unknown_map_entry", "syntax_map", "$@16",
  "global_objects", "global_object", "dhcp6_object", "$@17", "sub_dhcp6",
  "$@18", "global_params", "global_param", "preferred_lifetime",
  "valid_lifetime", "renew_timer", "rebind_timer",
  "decline_probation_period", "interfaces_config", "$@19",
  "sub_interfaces6", "$@20", "interface_config_map", "$@21",
  "lease_database", "$@22", "hosts_database", "$@23",
  "database_map_params", "database_map_param", "database_type", "$@24",
  "db_type", "user", "$@25", "password", "$@26", "host", "$@27", "port",
  "name", "$@28", "persist", "lfc_interval", "readonly", "connect_timeout",
  "contact_points", "$@29", "keyspace", "$@30", "mac_sources", "$@31",
  "mac_sources_list", "mac_sources_value", "duid_id", "string_id",
  "host_reservation_identifiers", "$@32",
  "host_reservation_identifiers_list", "host_reservation_identifier",
  "hw_address_id", "relay_supplied_options", "$@33", "hooks_libraries",
  "$@34", "hooks_libraries_list", "not_empty_hooks_libraries_list",
  "hooks_library", "$@35", "sub_hooks_library", "$@36", "hooks_params",
  "hooks_param", "library", "$@37", "parameters", "$@38",
  "expired_leases_processing", "$@39", "expired_leases_params",
  "expired_leases_param", "reclaim_timer_wait_time",
  "flush_reclaimed_timer_wait_time", "hold_reclaimed_time",
  "max_reclaim_leases", "max_reclaim_time", "unwarned_reclaim_cycles",
  "subnet6_list", "$@40", "subnet6_list_content", "not_empty_subnet6_list",
  "subnet6", "$@41", "sub_subnet6", "$@42", "subnet6_params",
  "subnet6_param", "subnet", "$@43", "interface", "$@44", "interface_id",
  "$@45", "client_class", "$@46", "reservation_mode", "$@47", "id",
  "rapid_commit", "option_def_list", "$@48", "option_def_list_content",
  "not_empty_option_def_list", "option_def_entry", "$@49",
  "sub_option_def", "$@50", "option_def_params",
  "not_empty_option_def_params", "option_def_param", "option_def_name",
  "code", "option_def_code", "option_def_type", "$@51",
  "option_def_record_types", "$@52", "space", "$@53", "option_def_space",
  "option_def_encapsulate", "$@54", "option_def_array", "option_data_list",
  "$@55", "option_data_list_content", "not_empty_option_data_list",
  "option_data_entry", "$@56", "sub_option_data", "$@57",
  "option_data_params", "not_empty_option_data_params",
  "option_data_param", "option_data_name", "option_data_data", "$@58",
  "option_data_code", "option_data_space", "option_data_csv_format",
  "pools_list", "$@59", "pools_list_content", "not_empty_pools_list",
  "pool_list_entry", "$@60", "sub_pool6", "$@61", "pool_params",
  "pool_param", "pool_entry", "$@62", "user_context", "$@63",
  "pd_pools_list", "$@64", "pd_pools_list_content",
  "not_empty_pd_pools_list", "pd_pool_entry", "$@65", "sub_pd_pool",
  "$@66", "pd_pool_params", "pd_pool_param", "pd_prefix", "$@67",
  "pd_prefix_len", "excluded_prefix", "$@68", "excluded_prefix_len",
  "pd_delegated_len", "reservations", "$@69", "reservations_list",
  "not_empty_reservations_list", "reservation", "$@70", "sub_reservation",
  "$@71", "reservation_params", "not_empty_reservation_params",
  "reservation_param", "ip_addresses", "$@72", "prefixes", "$@73", "duid",
  "$@74", "hw_address", "$@75", "hostname", "$@76",
  "reservation_client_classes", "$@77", "relay", "$@78", "relay_map",
  "$@79", "client_classes", "$@80", "client_classes_list", "$@81",
  "client_class_params", "not_empty_client_class_params",
  "client_class_param", "client_class_name", "client_class_test", "$@82",
  "server_id", "$@83", "server_id_params", "server_id_param",
  "server_id_type", "$@84", "duid_type", "htype", "identifier", "$@85",
  "time", "enterprise_id", "dhcp4o6_port", "control_socket", "$@86",
  "control_socket_params", "control_socket_param", "socket_type", "$@87",
  "socket_name", "$@88", "dhcp_ddns", "$@89", "sub_dhcp_ddns", "$@90",
  "dhcp_ddns_params", "dhcp_ddns_param", "enable_updates",
  "qualifying_suffix", "$@91", "server_ip", "$@92", "server_port",
  "sender_ip", "$@93", "sender_port", "max_queue_size", "ncr_protocol",
  "$@94", "ncr_protocol_value", "ncr_format", "$@95",
  "always_include_fqdn", "override_no_update", "override_client_update",
  "replace_client_name", "$@96", "replace_client_name_value",
  "generated_prefix", "$@97", "dhcp4_json_object", "$@98",
  "dhcpddns_json_object", "$@99", "logging_object", "$@100",
  "logging_params", "logging_param", "loggers", "$@101", "loggers_entries",
  "logger_entry", "$@102", "logger_params", "logger_param", "debuglevel",
  "severity", "$@103", "output_options_list", "$@104",
  "output_options_list_content", "output_entry", "$@105", "output_params",
  "output_param", "$@106", YY_NULLPTR
  };

#if PARSER6_DEBUG
  const unsigned short int
  Dhcp6Parser::yyrline_[] =
  {
       0,   223,   223,   223,   224,   224,   225,   225,   226,   226,
     227,   227,   228,   228,   229,   229,   230,   230,   231,   231,
     232,   232,   233,   233,   234,   234,   242,   243,   244,   245,
     246,   247,   248,   251,   256,   256,   267,   270,   271,   274,
     278,   285,   285,   292,   293,   296,   300,   307,   307,   314,
     315,   318,   322,   333,   343,   343,   355,   356,   360,   361,
     362,   363,   364,   367,   367,   384,   384,   392,   393,   398,
     399,   400,   401,   402,   403,   404,   405,   406,   407,   408,
     409,   410,   411,   412,   413,   414,   415,   416,   417,   418,
     419,   422,   427,   432,   437,   442,   447,   447,   457,   457,
     465,   465,   475,   475,   485,   485,   495,   496,   499,   500,
     501,   502,   503,   504,   505,   506,   507,   508,   509,   510,
     511,   514,   514,   521,   522,   523,   524,   527,   527,   535,
     535,   543,   543,   551,   556,   556,   564,   569,   574,   579,
     584,   584,   592,   592,   601,   601,   611,   612,   615,   616,
     619,   624,   629,   629,   639,   640,   643,   644,   647,   654,
     654,   664,   664,   674,   675,   678,   679,   682,   682,   690,
     690,   698,   699,   700,   703,   704,   707,   707,   715,   715,
     723,   723,   733,   734,   737,   738,   739,   740,   741,   742,
     745,   750,   755,   760,   765,   770,   778,   778,   791,   792,
     795,   796,   803,   803,   826,   826,   835,   836,   840,   841,
     842,   843,   844,   845,   846,   847,   848,   849,   850,   851,
     852,   853,   854,   855,   856,   859,   859,   867,   867,   875,
     875,   883,   883,   891,   891,   899,   904,   913,   913,   925,
     926,   929,   930,   935,   935,   946,   946,   956,   957,   960,
     961,   964,   965,   966,   967,   968,   969,   970,   971,   974,
     976,   981,   983,   983,   991,   991,   999,   999,  1007,  1009,
    1009,  1017,  1026,  1026,  1038,  1039,  1044,  1045,  1050,  1050,
    1061,  1061,  1072,  1073,  1078,  1079,  1084,  1085,  1086,  1087,
    1088,  1089,  1092,  1094,  1094,  1102,  1104,  1106,  1114,  1114,
    1126,  1127,  1130,  1131,  1134,  1134,  1142,  1142,  1150,  1151,
    1154,  1155,  1156,  1157,  1160,  1160,  1168,  1168,  1178,  1178,
    1190,  1191,  1194,  1195,  1198,  1198,  1206,  1206,  1214,  1215,
    1218,  1219,  1220,  1221,  1222,  1223,  1224,  1225,  1228,  1228,
    1236,  1241,  1241,  1249,  1254,  1262,  1262,  1272,  1273,  1276,
    1277,  1280,  1280,  1288,  1288,  1296,  1297,  1300,  1301,  1305,
    1306,  1307,  1308,  1309,  1310,  1311,  1312,  1315,  1315,  1325,
    1325,  1335,  1335,  1343,  1343,  1351,  1351,  1359,  1359,  1372,
    1372,  1382,  1382,  1393,  1393,  1403,  1404,  1407,  1407,  1415,
    1416,  1419,  1420,  1423,  1424,  1425,  1426,  1429,  1431,  1431,
    1442,  1442,  1452,  1453,  1456,  1457,  1458,  1459,  1460,  1461,
    1462,  1465,  1465,  1472,  1473,  1474,  1477,  1482,  1482,  1490,
    1495,  1502,  1509,  1509,  1519,  1520,  1523,  1524,  1527,  1527,
    1535,  1535,  1545,  1545,  1555,  1555,  1563,  1564,  1567,  1568,
    1569,  1570,  1571,  1572,  1573,  1574,  1575,  1576,  1577,  1578,
    1579,  1580,  1581,  1584,  1589,  1589,  1597,  1597,  1605,  1610,
    1610,  1618,  1623,  1628,  1628,  1636,  1637,  1640,  1640,  1648,
    1653,  1658,  1663,  1663,  1671,  1674,  1677,  1680,  1683,  1689,
    1689,  1699,  1699,  1706,  1706,  1718,  1718,  1731,  1732,  1736,
    1740,  1740,  1752,  1753,  1757,  1757,  1765,  1766,  1769,  1770,
    1771,  1772,  1773,  1776,  1781,  1781,  1789,  1789,  1799,  1800,
    1803,  1803,  1811,  1812,  1815,  1815
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
#line 4175 "dhcp6_parser.cc" // lalr1.cc:1167
#line 1823 "dhcp6_parser.yy" // lalr1.cc:1168


void
isc::dhcp::Dhcp6Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
