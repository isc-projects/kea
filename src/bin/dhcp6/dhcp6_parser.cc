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
      case 156: // value
      case 160: // map_value
      case 201: // db_type
      case 389: // duid_type
      case 422: // ncr_protocol_value
      case 431: // replace_client_name_value
        value.move< ElementPtr > (that.value);
        break;

      case 141: // "boolean"
        value.move< bool > (that.value);
        break;

      case 140: // "floating point"
        value.move< double > (that.value);
        break;

      case 139: // "integer"
        value.move< int64_t > (that.value);
        break;

      case 138: // "constant string"
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
      case 156: // value
      case 160: // map_value
      case 201: // db_type
      case 389: // duid_type
      case 422: // ncr_protocol_value
      case 431: // replace_client_name_value
        value.copy< ElementPtr > (that.value);
        break;

      case 141: // "boolean"
        value.copy< bool > (that.value);
        break;

      case 140: // "floating point"
        value.copy< double > (that.value);
        break;

      case 139: // "integer"
        value.copy< int64_t > (that.value);
        break;

      case 138: // "constant string"
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
            case 138: // "constant string"

#line 213 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< std::string > (); }
#line 362 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 139: // "integer"

#line 213 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< int64_t > (); }
#line 369 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 140: // "floating point"

#line 213 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< double > (); }
#line 376 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 141: // "boolean"

#line 213 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< bool > (); }
#line 383 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 156: // value

#line 213 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 390 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 160: // map_value

#line 213 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 397 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 201: // db_type

#line 213 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 404 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 389: // duid_type

#line 213 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 411 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 422: // ncr_protocol_value

#line 213 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 418 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 431: // replace_client_name_value

#line 213 "dhcp6_parser.yy" // lalr1.cc:636
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
      case 156: // value
      case 160: // map_value
      case 201: // db_type
      case 389: // duid_type
      case 422: // ncr_protocol_value
      case 431: // replace_client_name_value
        yylhs.value.build< ElementPtr > ();
        break;

      case 141: // "boolean"
        yylhs.value.build< bool > ();
        break;

      case 140: // "floating point"
        yylhs.value.build< double > ();
        break;

      case 139: // "integer"
        yylhs.value.build< int64_t > ();
        break;

      case 138: // "constant string"
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
#line 222 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.NO_KEYWORD; }
#line 670 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 4:
#line 223 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.CONFIG; }
#line 676 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 6:
#line 224 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.DHCP6; }
#line 682 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 8:
#line 225 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.INTERFACES_CONFIG; }
#line 688 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 10:
#line 226 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.SUBNET6; }
#line 694 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 12:
#line 227 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.POOLS; }
#line 700 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 14:
#line 228 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.PD_POOLS; }
#line 706 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 16:
#line 229 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.RESERVATIONS; }
#line 712 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 18:
#line 230 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.OPTION_DEF; }
#line 718 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 20:
#line 231 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.OPTION_DATA; }
#line 724 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 22:
#line 232 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.HOOKS_LIBRARIES; }
#line 730 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 24:
#line 233 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.DHCP_DDNS; }
#line 736 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 26:
#line 241 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 742 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 27:
#line 242 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as< double > (), ctx.loc2pos(yystack_[0].location))); }
#line 748 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 28:
#line 243 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 754 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 29:
#line 244 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 760 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 30:
#line 245 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 766 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 31:
#line 246 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 772 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 32:
#line 247 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 778 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 33:
#line 250 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as< ElementPtr > ());
}
#line 787 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 34:
#line 255 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 798 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 35:
#line 260 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 808 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 36:
#line 266 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 814 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 39:
#line 273 "dhcp6_parser.yy" // lalr1.cc:859
    {
                  // map containing a single entry
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 823 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 40:
#line 277 "dhcp6_parser.yy" // lalr1.cc:859
    {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 833 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 41:
#line 284 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 842 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 42:
#line 287 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // list parsing complete. Put any sanity checking here
}
#line 850 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 45:
#line 295 "dhcp6_parser.yy" // lalr1.cc:859
    {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 859 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 46:
#line 299 "dhcp6_parser.yy" // lalr1.cc:859
    {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 868 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 47:
#line 306 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // List parsing about to start
}
#line 876 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 48:
#line 308 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // list parsing complete. Put any sanity checking here
    //ctx.stack_.pop_back();
}
#line 885 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 51:
#line 317 "dhcp6_parser.yy" // lalr1.cc:859
    {
                          ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 894 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 52:
#line 321 "dhcp6_parser.yy" // lalr1.cc:859
    {
                          ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 903 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 53:
#line 332 "dhcp6_parser.yy" // lalr1.cc:859
    {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as< std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 914 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 54:
#line 342 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 925 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 55:
#line 347 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 935 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 63:
#line 366 "dhcp6_parser.yy" // lalr1.cc:859
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
#line 373 "dhcp6_parser.yy" // lalr1.cc:859
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
#line 383 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the Dhcp6 map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 970 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 66:
#line 387 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 978 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 91:
#line 421 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("preferred-lifetime", prf);
}
#line 987 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 92:
#line 426 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 996 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 93:
#line 431 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 1005 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 94:
#line 436 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 1014 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 95:
#line 441 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr dpp(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 1023 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 96:
#line 446 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces-config", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.INTERFACES_CONFIG);
}
#line 1034 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 97:
#line 451 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1043 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 98:
#line 456 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1053 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 99:
#line 460 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1061 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 100:
#line 464 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1072 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 101:
#line 469 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1081 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 102:
#line 474 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lease-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.LEASE_DATABASE);
}
#line 1092 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 103:
#line 479 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1101 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 104:
#line 484 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1112 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 105:
#line 489 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1121 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 119:
#line 511 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.DATABASE_TYPE);
}
#line 1129 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 120:
#line 513 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("type", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1138 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 121:
#line 518 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("memfile", ctx.loc2pos(yystack_[0].location))); }
#line 1144 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 122:
#line 519 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("mysql", ctx.loc2pos(yystack_[0].location))); }
#line 1150 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 123:
#line 520 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("postgresql", ctx.loc2pos(yystack_[0].location))); }
#line 1156 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 124:
#line 521 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("cql", ctx.loc2pos(yystack_[0].location))); }
#line 1162 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 125:
#line 524 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1170 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 126:
#line 526 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr user(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1180 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 127:
#line 532 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1188 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 128:
#line 534 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr pwd(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 1198 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 129:
#line 540 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1206 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 130:
#line 542 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr h(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 1216 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 131:
#line 548 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr p(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", p);
}
#line 1225 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 132:
#line 553 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1233 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 133:
#line 555 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1243 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 134:
#line 561 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 1252 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 135:
#line 566 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 1261 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 136:
#line 571 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 1270 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 137:
#line 576 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("connect-timeout", n);
}
#line 1279 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 138:
#line 581 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("mac-sources", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.MAC_SOURCES);
}
#line 1290 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 139:
#line 586 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1299 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 144:
#line 599 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1308 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 145:
#line 604 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr duid(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1317 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 146:
#line 609 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 1328 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 147:
#line 614 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1337 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 152:
#line 627 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 1346 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 153:
#line 634 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay-supplied-options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1357 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 154:
#line 639 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1366 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 155:
#line 644 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 1377 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 156:
#line 649 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1386 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 161:
#line 662 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1396 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 162:
#line 666 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1404 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 163:
#line 670 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1414 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 164:
#line 674 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1422 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 170:
#line 687 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1430 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 171:
#line 689 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr lib(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 1440 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 172:
#line 695 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1448 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 173:
#line 697 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1457 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 174:
#line 703 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.EXPIRED_LEASES_PROCESSING);
}
#line 1468 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 175:
#line 708 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1477 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 184:
#line 725 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 1486 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 185:
#line 730 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 1495 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 186:
#line 735 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 1504 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 187:
#line 740 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 1513 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 188:
#line 745 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 1522 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 189:
#line 750 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 1531 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 190:
#line 758 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet6", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET6);
}
#line 1542 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 191:
#line 763 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1551 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 196:
#line 783 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1561 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 197:
#line 787 "dhcp6_parser.yy" // lalr1.cc:859
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
#line 1584 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 198:
#line 806 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the subnet6 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1594 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 199:
#line 810 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1602 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 219:
#line 839 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1610 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 220:
#line 841 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr subnet(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 1620 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 221:
#line 847 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1628 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 222:
#line 849 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 1638 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 223:
#line 855 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1646 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 224:
#line 857 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface-id", iface);
    ctx.leave();
}
#line 1656 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 225:
#line 863 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.CLIENT_CLASS);
}
#line 1664 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 226:
#line 865 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr cls(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 1674 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 227:
#line 871 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1682 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 228:
#line 873 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr rm(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservation-mode", rm);
    ctx.leave();
}
#line 1692 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 229:
#line 879 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr id(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 1701 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 230:
#line 884 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr rc(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rapid-commit", rc);
}
#line 1710 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 231:
#line 893 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 1721 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 232:
#line 898 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1730 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 237:
#line 915 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1740 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 238:
#line 919 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1748 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 239:
#line 926 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1758 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 240:
#line 930 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1766 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 254:
#line 956 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr code(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 1775 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 256:
#line 963 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1783 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 257:
#line 965 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 1793 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 258:
#line 971 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1801 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 259:
#line 973 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 1811 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 260:
#line 979 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1819 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 261:
#line 981 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr space(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 1829 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 263:
#line 989 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1837 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 264:
#line 991 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr encap(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 1847 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 265:
#line 997 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr array(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 1856 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 266:
#line 1006 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 1867 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 267:
#line 1011 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1876 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 272:
#line 1030 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1886 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 273:
#line 1034 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1894 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 274:
#line 1041 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1904 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 275:
#line 1045 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1912 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 287:
#line 1074 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1920 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 288:
#line 1076 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr data(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 1930 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 291:
#line 1086 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr space(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", space);
}
#line 1939 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 292:
#line 1094 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 1950 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 293:
#line 1099 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1959 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 298:
#line 1114 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1969 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 299:
#line 1118 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1977 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 300:
#line 1122 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1987 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 301:
#line 1126 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1995 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 308:
#line 1140 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2003 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 309:
#line 1142 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr pool(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 2013 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 310:
#line 1148 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2021 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 311:
#line 1150 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("user-context", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2030 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 312:
#line 1158 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pd-pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.PD_POOLS);
}
#line 2041 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 313:
#line 1163 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2050 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 318:
#line 1178 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2060 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 319:
#line 1182 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2068 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 320:
#line 1186 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the pd-pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2078 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 321:
#line 1190 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 2086 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 332:
#line 1208 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2094 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 333:
#line 1210 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix", prf);
    ctx.leave();
}
#line 2104 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 334:
#line 1216 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix-len", prf);
}
#line 2113 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 335:
#line 1221 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2121 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 336:
#line 1223 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix", prf);
    ctx.leave();
}
#line 2131 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 337:
#line 1229 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix-len", prf);
}
#line 2140 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 338:
#line 1234 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr deleg(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("delegated-len", deleg);
}
#line 2149 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 339:
#line 1242 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 2160 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 340:
#line 1247 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2169 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 345:
#line 1260 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2179 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 346:
#line 1264 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2187 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 347:
#line 1268 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2197 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 348:
#line 1272 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 2205 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 361:
#line 1295 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-addresses", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2216 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 362:
#line 1300 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2225 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 363:
#line 1305 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefixes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2236 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 364:
#line 1310 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2245 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 365:
#line 1315 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2253 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 366:
#line 1317 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr d(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 2263 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 367:
#line 1323 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2271 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 368:
#line 1325 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 2281 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 369:
#line 1331 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2289 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 370:
#line 1333 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr host(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 2299 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 371:
#line 1339 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2310 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 372:
#line 1344 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2319 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 373:
#line 1352 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 2330 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 374:
#line 1357 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2339 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 375:
#line 1362 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2347 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 376:
#line 1364 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr ip(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", ip);
    ctx.leave();
}
#line 2357 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 377:
#line 1373 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 2368 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 378:
#line 1378 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2377 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 381:
#line 1387 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2387 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 382:
#line 1391 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2395 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 392:
#line 1411 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2403 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 393:
#line 1413 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr test(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 2413 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 394:
#line 1422 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-id", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SERVER_ID);
}
#line 2424 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 395:
#line 1427 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2433 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 405:
#line 1445 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.DUID_TYPE);
}
#line 2441 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 406:
#line 1447 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("type", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2450 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 407:
#line 1452 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("LLT", ctx.loc2pos(yystack_[0].location))); }
#line 2456 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 408:
#line 1453 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("EN", ctx.loc2pos(yystack_[0].location))); }
#line 2462 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 409:
#line 1454 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("LL", ctx.loc2pos(yystack_[0].location))); }
#line 2468 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 410:
#line 1457 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr htype(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("htype", htype);
}
#line 2477 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 411:
#line 1462 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2485 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 412:
#line 1464 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr id(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("identifier", id);
    ctx.leave();
}
#line 2495 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 413:
#line 1470 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("time", time);
}
#line 2504 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 414:
#line 1475 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enterprise-id", time);
}
#line 2513 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 415:
#line 1482 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 2522 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 416:
#line 1489 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 2533 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 417:
#line 1494 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2542 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 422:
#line 1507 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2550 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 423:
#line 1509 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr stype(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 2560 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 424:
#line 1515 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2568 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 425:
#line 1517 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 2578 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 426:
#line 1525 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 2589 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 427:
#line 1530 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2598 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 428:
#line 1535 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2608 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 429:
#line 1539 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 2616 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 448:
#line 1565 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 2625 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 449:
#line 1570 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2633 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 450:
#line 1572 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("qualifying-suffix", s);
    ctx.leave();
}
#line 2643 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 451:
#line 1578 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2651 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 452:
#line 1580 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 2661 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 453:
#line 1586 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 2670 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 454:
#line 1591 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2678 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 455:
#line 1593 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 2688 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 456:
#line 1599 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 2697 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 457:
#line 1604 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 2706 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 458:
#line 1609 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 2714 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 459:
#line 1611 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2723 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 460:
#line 1617 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 2729 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 461:
#line 1618 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 2735 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 462:
#line 1621 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NCR_FORMAT);
}
#line 2743 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 463:
#line 1623 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 2753 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 464:
#line 1629 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-include-fqdn", b);
}
#line 2762 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 465:
#line 1634 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("allow-client-update",  b);
}
#line 2771 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 466:
#line 1639 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-no-update", b);
}
#line 2780 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 467:
#line 1644 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-client-update", b);
}
#line 2789 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 468:
#line 1649 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 2797 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 469:
#line 1651 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("replace-client-name", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2806 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 470:
#line 1657 "dhcp6_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("when-present", ctx.loc2pos(yystack_[0].location))); 
      }
#line 2814 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 471:
#line 1660 "dhcp6_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location)));
      }
#line 2822 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 472:
#line 1663 "dhcp6_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("always", ctx.loc2pos(yystack_[0].location)));
      }
#line 2830 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 473:
#line 1666 "dhcp6_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("when-not-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 2838 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 474:
#line 1669 "dhcp6_parser.yy" // lalr1.cc:859
    {
      error(yystack_[0].location, "boolean values for the replace-client-name are "
                "no longer supported");
      }
#line 2847 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 475:
#line 1675 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2855 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 476:
#line 1677 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("generated-prefix", s);
    ctx.leave();
}
#line 2865 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 477:
#line 1685 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2873 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 478:
#line 1687 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("Dhcp4", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2882 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 479:
#line 1692 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2890 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 480:
#line 1694 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("DhcpDdns", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2899 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 481:
#line 1704 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Logging", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.LOGGING);
}
#line 2910 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 482:
#line 1709 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2919 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 486:
#line 1726 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 2930 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 487:
#line 1731 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2939 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 490:
#line 1743 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 2949 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 491:
#line 1747 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2957 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 499:
#line 1762 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr dl(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 2966 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 500:
#line 1766 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2974 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 501:
#line 1768 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 2984 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 502:
#line 1774 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 2995 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 503:
#line 1779 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3004 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 506:
#line 1788 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3014 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 507:
#line 1792 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 3022 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 510:
#line 1800 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3030 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 511:
#line 1802 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 3040 "dhcp6_parser.cc" // lalr1.cc:859
    break;


#line 3044 "dhcp6_parser.cc" // lalr1.cc:859
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


  const short int Dhcp6Parser::yypact_ninf_ = -490;

  const signed char Dhcp6Parser::yytable_ninf_ = -1;

  const short int
  Dhcp6Parser::yypact_[] =
  {
      81,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,
    -490,  -490,  -490,    98,    19,    41,    95,   114,   118,   120,
     161,   226,   230,   247,   251,   265,  -490,  -490,  -490,  -490,
    -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,
    -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,
    -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,
      19,    57,    17,    31,   215,    23,    37,    68,    62,    32,
     100,   -42,   143,  -490,   268,   231,   272,   269,   276,  -490,
    -490,  -490,  -490,   290,  -490,   102,  -490,  -490,  -490,  -490,
    -490,  -490,  -490,  -490,   291,   293,   294,   295,   297,  -490,
    -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,   298,
    -490,  -490,  -490,   146,  -490,  -490,  -490,  -490,  -490,  -490,
    -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,
    -490,  -490,  -490,  -490,  -490,  -490,  -490,   302,  -490,  -490,
    -490,  -490,  -490,  -490,   299,   307,  -490,  -490,  -490,  -490,
    -490,  -490,  -490,  -490,  -490,   148,  -490,  -490,  -490,  -490,
    -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,
    -490,  -490,  -490,   159,  -490,  -490,  -490,  -490,   308,  -490,
     309,   310,  -490,  -490,  -490,   175,  -490,  -490,  -490,  -490,
    -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,
     311,   277,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,
    -490,   312,  -490,  -490,  -490,   313,  -490,  -490,   314,   303,
    -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,
    -490,   316,  -490,  -490,  -490,  -490,   315,   318,  -490,  -490,
    -490,  -490,  -490,  -490,  -490,  -490,  -490,   177,  -490,  -490,
    -490,   321,  -490,  -490,   322,  -490,   323,   324,  -490,  -490,
     325,   326,   327,   328,  -490,  -490,  -490,   181,  -490,  -490,
    -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,
    -490,  -490,  -490,  -490,  -490,    19,    19,  -490,   180,   329,
     330,   331,   332,  -490,    17,  -490,   333,   334,   335,   176,
     201,   202,   203,   204,   340,   341,   342,   343,   344,   345,
     346,   347,   348,   349,   216,   350,   352,    31,  -490,   353,
    -490,    48,   354,   355,   356,   357,   358,   224,   223,   361,
     362,   363,   364,    23,  -490,   365,   366,    37,  -490,   367,
     233,   369,   235,   236,    68,  -490,   372,   373,   374,   375,
     376,   377,  -490,    62,   378,   379,   245,   381,   382,   383,
     248,  -490,    32,   384,   250,  -490,   100,   386,   388,    11,
    -490,   255,   389,   390,   256,   393,   259,   260,   398,   399,
     263,   264,   266,   267,   402,   405,   143,  -490,  -490,  -490,
     406,   404,   407,    19,    19,  -490,   408,   409,   410,  -490,
    -490,  -490,  -490,  -490,   413,   414,   415,   416,   417,   418,
     419,   420,   421,   422,  -490,   425,   426,  -490,   431,  -490,
    -490,  -490,  -490,   429,   423,  -490,  -490,  -490,   433,   434,
     274,   275,   289,  -490,  -490,   304,   306,   435,   438,  -490,
     317,   439,  -490,   319,  -490,   320,  -490,  -490,  -490,   431,
     431,   431,   336,   338,   339,  -490,   351,   359,  -490,   360,
     368,   370,  -490,  -490,   371,  -490,  -490,   380,    19,  -490,
    -490,   385,   387,  -490,   391,  -490,  -490,     1,   337,  -490,
    -490,  -490,  -490,    49,   392,  -490,    19,    31,   394,  -490,
    -490,   215,    14,    14,   440,   442,   444,   -37,    19,    65,
      36,   446,    66,    84,    83,   143,  -490,  -490,   450,  -490,
      48,   449,   452,  -490,  -490,  -490,  -490,  -490,   453,   395,
    -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,
    -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,
    -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,
    -490,  -490,  -490,  -490,   184,  -490,   185,  -490,  -490,   455,
    -490,  -490,  -490,  -490,   457,   460,   461,   462,   464,  -490,
     188,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,
    -490,  -490,   191,  -490,   463,   467,  -490,  -490,   465,   469,
    -490,  -490,   472,   470,  -490,  -490,  -490,    43,  -490,  -490,
    -490,   473,  -490,  -490,   103,  -490,  -490,  -490,   147,  -490,
     474,   478,  -490,   479,   480,   481,   482,   483,   484,   195,
    -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,   486,
     487,   488,  -490,  -490,   218,  -490,  -490,  -490,  -490,  -490,
    -490,  -490,  -490,   220,  -490,  -490,  -490,   221,   396,   397,
    -490,  -490,   476,   491,  -490,  -490,   489,   493,  -490,  -490,
     494,   496,  -490,  -490,   495,  -490,   497,   394,  -490,  -490,
     498,   500,   501,   503,   400,   401,   411,   403,   412,    14,
    -490,  -490,    23,  -490,   440,    32,  -490,   442,   100,  -490,
     444,   -37,  -490,  -490,    65,  -490,    36,  -490,   -42,  -490,
     446,   424,   427,   428,   430,   432,   436,    66,  -490,   506,
     507,   437,   441,   443,    84,  -490,   508,   510,    83,  -490,
    -490,  -490,   509,   513,  -490,    37,  -490,   449,    68,  -490,
     452,    62,  -490,   453,   515,  -490,   512,  -490,   249,   445,
     447,   448,  -490,  -490,  -490,  -490,  -490,  -490,   227,  -490,
     514,  -490,   516,  -490,  -490,  -490,  -490,   228,  -490,  -490,
    -490,  -490,  -490,  -490,  -490,  -490,   -29,   451,  -490,  -490,
    -490,  -490,   454,   456,  -490,  -490,   458,   252,  -490,   253,
    -490,   518,  -490,   459,   520,  -490,  -490,  -490,  -490,  -490,
    -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,
    -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,
     198,  -490,    59,   520,  -490,  -490,   517,  -490,  -490,  -490,
     254,  -490,  -490,  -490,  -490,  -490,   524,   466,   527,    59,
    -490,   528,  -490,   468,  -490,   525,  -490,  -490,   199,  -490,
     477,   525,  -490,  -490,   261,  -490,  -490,   532,   477,  -490,
     471,  -490,  -490
  };

  const unsigned short int
  Dhcp6Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,    24,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     1,    41,    34,    30,
      29,    26,    27,    28,    33,     3,    31,    32,    54,     5,
      65,     7,    98,     9,   198,    11,   300,    13,   320,    15,
     347,    17,   239,    19,   274,    21,   163,    23,   428,    25,
      43,    37,     0,     0,     0,     0,     0,     0,   349,   241,
     276,     0,     0,    45,     0,    44,     0,     0,    38,    63,
     481,   477,   479,     0,    62,     0,    56,    58,    60,    61,
      59,    96,   102,   104,     0,     0,     0,     0,     0,   190,
     231,   266,   138,   153,   146,   377,   155,   174,   394,     0,
     416,   426,    90,     0,    67,    69,    70,    71,    72,    73,
      75,    76,    77,    78,    80,    79,    84,    85,    74,    82,
      83,    81,    86,    87,    88,    89,   100,     0,   381,   292,
     312,   219,   221,   223,     0,     0,   227,   225,   339,   373,
     218,   202,   203,   204,   205,     0,   200,   209,   210,   211,
     214,   216,   212,   213,   206,   207,   208,   215,   217,   308,
     310,   307,   305,     0,   302,   304,   306,   332,     0,   335,
       0,     0,   331,   327,   330,     0,   322,   324,   325,   328,
     329,   326,   371,   361,   363,   365,   367,   369,   360,   359,
       0,   350,   351,   355,   356,   353,   357,   358,   354,   256,
     132,     0,   260,   258,   263,     0,   252,   253,     0,   242,
     243,   245,   255,   246,   247,   248,   262,   249,   250,   251,
     287,     0,   285,   286,   289,   290,     0,   277,   278,   280,
     281,   282,   283,   284,   170,   172,   167,     0,   165,   168,
     169,     0,   449,   451,     0,   454,     0,     0,   458,   462,
       0,     0,     0,     0,   468,   475,   447,     0,   430,   432,
     433,   434,   435,   436,   437,   438,   439,   440,   441,   442,
     443,   444,   445,   446,    42,     0,     0,    35,     0,     0,
       0,     0,     0,    53,     0,    55,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    66,     0,
      99,   383,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   199,     0,     0,     0,   301,     0,
       0,     0,     0,     0,     0,   321,     0,     0,     0,     0,
       0,     0,   348,     0,     0,     0,     0,     0,     0,     0,
       0,   240,     0,     0,     0,   275,     0,     0,     0,     0,
     164,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   429,    46,    39,
       0,     0,     0,     0,     0,    57,     0,     0,     0,    91,
      92,    93,    94,    95,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   415,     0,     0,    68,     0,   392,
     390,   391,   389,     0,   384,   385,   387,   388,     0,     0,
       0,     0,     0,   229,   230,     0,     0,     0,     0,   201,
       0,     0,   303,     0,   334,     0,   337,   338,   323,     0,
       0,     0,     0,     0,     0,   352,     0,     0,   254,     0,
       0,     0,   265,   244,     0,   291,   279,     0,     0,   166,
     448,     0,     0,   453,     0,   456,   457,     0,     0,   464,
     465,   466,   467,     0,     0,   431,     0,     0,     0,   478,
     480,     0,     0,     0,   192,   233,   268,     0,    43,     0,
       0,   157,     0,     0,     0,     0,    47,   101,     0,   382,
       0,   294,   314,   220,   222,   224,   228,   226,   341,     0,
     309,    36,   311,   333,   336,   372,   362,   364,   366,   368,
     370,   257,   133,   261,   259,   264,   288,   171,   173,   450,
     452,   455,   460,   461,   459,   463,   470,   471,   472,   473,
     474,   469,   476,    40,     0,   486,     0,   483,   485,     0,
     119,   125,   127,   129,     0,     0,     0,     0,     0,   118,
       0,   106,   108,   109,   110,   111,   112,   113,   114,   115,
     116,   117,     0,   196,     0,   193,   194,   237,     0,   234,
     235,   272,     0,   269,   270,   144,   145,     0,   140,   142,
     143,     0,   152,   150,     0,   148,   151,   379,     0,   161,
       0,   158,   159,     0,     0,     0,     0,     0,     0,     0,
     176,   178,   179,   180,   181,   182,   183,   405,   411,     0,
       0,     0,   404,   403,     0,   396,   398,   401,   399,   400,
     402,   422,   424,     0,   418,   420,   421,     0,    49,     0,
     386,   298,     0,   295,   296,   318,     0,   315,   316,   345,
       0,   342,   343,   375,     0,    64,     0,     0,   482,    97,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     103,   105,     0,   191,     0,   241,   232,     0,   276,   267,
       0,     0,   139,   154,     0,   147,     0,   378,     0,   156,
       0,     0,     0,     0,     0,     0,     0,     0,   175,     0,
       0,     0,     0,     0,     0,   395,     0,     0,     0,   417,
     427,    51,     0,    50,   393,     0,   293,     0,     0,   313,
       0,   349,   340,     0,     0,   374,     0,   484,     0,     0,
       0,     0,   131,   134,   135,   136,   137,   107,     0,   195,
       0,   236,     0,   271,   141,   149,   380,     0,   160,   184,
     185,   186,   187,   188,   189,   177,     0,     0,   410,   413,
     414,   397,     0,     0,   419,    48,     0,     0,   297,     0,
     317,     0,   344,     0,     0,   121,   122,   123,   124,   120,
     126,   128,   130,   197,   238,   273,   162,   407,   408,   409,
     406,   412,   423,   425,    52,   299,   319,   346,   376,   490,
       0,   488,     0,     0,   487,   502,     0,   500,   498,   494,
       0,   492,   496,   497,   495,   489,     0,     0,     0,     0,
     491,     0,   499,     0,   493,     0,   501,   506,     0,   504,
       0,     0,   503,   510,     0,   508,   505,     0,     0,   507,
       0,   509,   511
  };

  const short int
  Dhcp6Parser::yypgoto_[] =
  {
    -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,
    -490,  -490,  -490,  -490,     7,  -490,    79,  -490,  -490,  -490,
    -490,  -490,  -490,    39,  -490,  -163,  -490,  -490,  -490,   -62,
    -490,  -490,  -490,   244,  -490,  -490,  -490,  -490,    53,   229,
     -63,   -50,   -49,   -43,  -490,  -490,  -490,  -490,  -490,    50,
    -490,  -490,  -490,  -490,  -490,    52,  -136,  -490,  -490,  -490,
    -490,  -490,  -490,  -490,  -490,  -490,  -490,   -58,  -490,  -489,
    -490,  -490,  -490,  -490,  -490,  -490,  -144,  -474,  -490,  -490,
    -490,  -490,  -146,  -490,  -490,  -490,  -490,  -490,  -490,  -490,
    -151,  -490,  -490,  -490,  -145,   183,  -490,  -490,  -490,  -490,
    -490,  -490,  -490,  -153,  -490,  -490,  -490,  -490,  -490,  -490,
    -490,  -490,  -490,  -490,  -129,  -490,  -490,  -490,  -126,   225,
    -490,  -490,  -490,  -490,  -490,  -490,  -477,  -490,  -490,  -490,
    -490,  -490,  -490,  -490,  -490,  -490,  -130,  -490,  -490,  -490,
    -125,  -490,   197,  -490,   -59,  -490,  -490,  -490,  -490,  -490,
     -57,  -490,  -490,  -490,  -490,  -490,   -48,  -490,  -490,  -490,
    -128,  -490,  -490,  -490,  -127,  -490,   206,  -490,  -490,  -490,
    -490,  -490,  -490,  -490,  -490,  -490,  -490,  -162,  -490,  -490,
    -490,  -161,   237,  -490,  -490,   -66,  -490,  -490,  -490,  -490,
    -490,  -160,  -490,  -490,  -490,  -155,   234,  -490,  -490,  -490,
    -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -165,  -490,
    -490,  -490,  -154,  -490,   238,  -490,  -490,  -490,  -490,  -490,
    -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,
    -490,  -490,  -490,  -490,  -490,  -490,  -490,    69,  -490,  -490,
    -490,  -490,  -490,  -490,  -133,  -490,  -490,  -490,  -490,  -490,
    -490,  -490,  -490,  -490,  -490,  -490,  -490,  -134,  -490,  -490,
    -490,  -490,  -490,  -490,  -490,  -490,    82,   207,  -490,  -490,
    -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,
    -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,
    -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,   -79,
    -490,  -490,  -490,  -223,  -490,  -490,  -234,  -490,  -490,  -490,
    -490,  -490,  -490,  -242,  -490,  -490,  -248,  -490
  };

  const short int
  Dhcp6Parser::yydefgoto_[] =
  {
      -1,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    73,    35,    36,    61,   522,    77,
      78,    37,    60,    74,    75,   507,   648,   722,   723,   112,
      39,    62,    85,    86,    87,   289,    41,    63,   113,   114,
     115,   116,   117,   118,   119,   120,   296,    43,    64,   137,
     319,   121,   297,   122,   298,   570,   571,   572,   670,   789,
     573,   671,   574,   672,   575,   673,   576,   217,   355,   578,
     579,   580,   581,   123,   307,   597,   598,   599,   600,   124,
     309,   604,   605,   606,   125,   308,   126,   311,   610,   611,
     612,   698,    57,    71,   247,   248,   249,   367,   250,   368,
     127,   312,   619,   620,   621,   622,   623,   624,   625,   626,
     128,   304,   584,   585,   586,   682,    45,    65,   155,   156,
     157,   324,   158,   325,   159,   326,   160,   330,   161,   329,
     162,   163,   129,   305,   588,   589,   590,   685,    53,    69,
     218,   219,   220,   221,   222,   223,   224,   354,   225,   358,
     226,   357,   227,   228,   359,   229,   130,   306,   592,   593,
     594,   688,    55,    70,   236,   237,   238,   239,   240,   363,
     241,   242,   243,   165,   322,   652,   653,   654,   725,    47,
      66,   173,   174,   175,   335,   176,   336,   166,   323,   656,
     657,   658,   728,    49,    67,   185,   186,   187,   339,   188,
     189,   341,   190,   191,   167,   331,   660,   661,   662,   731,
      51,    68,   200,   201,   202,   203,   347,   204,   348,   205,
     349,   206,   350,   207,   351,   208,   346,   168,   332,   664,
     734,   131,   310,   608,   321,   423,   424,   425,   426,   427,
     508,   132,   313,   634,   635,   636,   709,   800,   637,   638,
     710,   639,   640,   133,   134,   315,   643,   644,   645,   716,
     646,   717,   135,   316,    59,    72,   267,   268,   269,   270,
     372,   271,   373,   272,   273,   375,   274,   275,   276,   378,
     544,   277,   379,   278,   279,   280,   281,   282,   384,   551,
     283,   385,    88,   291,    89,   292,    90,   290,   556,   557,
     558,   666,   810,   811,   812,   820,   821,   822,   823,   828,
     824,   826,   838,   839,   840,   844,   845,   847
  };

  const unsigned short int
  Dhcp6Parser::yytable_[] =
  {
      84,   184,   151,   150,   171,   182,   198,   216,   232,   246,
     266,   234,   233,   235,   633,   152,   153,   164,   172,   183,
     199,    34,   154,   607,    27,   603,    28,    79,    29,   560,
     138,   595,   244,   245,   561,   562,   563,   564,   565,   566,
     567,   568,    91,   138,    92,    93,   691,   209,    38,   692,
     210,    94,    95,    96,    97,   797,   798,   799,   101,    94,
      95,    96,    97,    98,    99,   100,   101,   139,   210,   140,
     211,   212,   101,   213,   214,   215,   141,   142,   143,   144,
     145,   146,   169,   101,   210,   244,   245,   147,   148,   170,
     102,   103,   104,   105,   149,   210,    83,   101,    26,   627,
     147,   596,    40,   101,   106,   294,   694,   107,   565,   695,
     295,   419,   542,   543,   108,   177,   178,   179,   180,   181,
     170,    42,   109,   110,   192,    44,   111,    46,   193,   194,
     195,   196,   197,   595,   602,    80,   210,   230,   211,   212,
     231,    81,    82,   613,   614,   615,   616,   617,   618,   317,
     696,   333,    83,   697,   318,    83,   334,    30,    31,    32,
      33,    83,   337,   546,   547,   548,   549,   338,    48,    83,
      83,   628,   629,   630,   631,    83,   641,   642,   344,   815,
     369,   816,   817,   345,   386,   370,    83,   317,   667,   387,
     550,   679,   665,   668,   679,    76,   680,    83,   707,   681,
      83,   813,   841,   708,   814,   842,    83,     1,     2,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,   756,
     603,   714,    83,   718,   386,   633,   715,   136,   719,   720,
     333,   369,    84,    50,   285,   793,   796,    52,    83,   251,
     252,   253,   254,   255,   256,   257,   258,   259,   260,   261,
     262,   263,   264,   265,    54,   337,   344,   829,    56,   420,
     805,   806,   830,   421,   848,   785,   786,   787,   788,   849,
     151,   150,    58,   422,   284,   171,   286,   287,   184,   288,
     353,    83,   182,   152,   153,   164,   525,   526,   527,   172,
     154,   198,   388,   389,   293,   299,   183,   300,   301,   302,
     216,   303,   314,   327,   232,   199,   362,   234,   233,   235,
     320,   328,   340,   342,   343,   399,   356,   360,   390,   352,
     364,   366,   361,   365,   266,   371,   374,   376,   377,   380,
     381,   382,   383,   391,   392,   393,   394,   396,   397,   398,
     400,   401,   402,   403,   404,   405,   406,   407,   408,   409,
     410,   411,   412,   413,   415,   414,   416,   418,   428,   429,
     430,   431,   432,   433,   434,   435,   436,   437,   438,   440,
     441,   443,   444,   445,   446,   447,   449,   450,   451,   452,
     453,   454,   456,   457,   458,   459,   460,   461,   464,   462,
     467,   465,   468,   471,   472,   473,   470,   474,   475,   476,
     489,   490,   477,   478,   479,   480,   483,   481,   482,   484,
     486,   487,   513,   514,   488,   491,   492,   493,   494,   495,
     496,   497,   498,   499,   500,   501,   510,   515,   502,   503,
     569,   569,   504,   505,   577,   577,   506,   509,   511,   512,
     518,   632,   516,   266,   517,   519,    28,   583,   420,   587,
     545,   591,   421,   609,   649,   520,   651,   523,   524,   655,
     659,   674,   422,   669,   675,   676,   677,   663,   678,   683,
     684,   686,   687,   690,   528,   538,   529,   530,   689,   693,
     699,   700,   726,   701,   702,   703,   704,   705,   706,   531,
     711,   712,   713,   553,   727,   729,   730,   532,   533,   733,
     732,   736,   738,   735,   739,   740,   534,   741,   535,   536,
     766,   767,   772,   555,   773,   775,   776,   784,   537,   783,
     521,   827,   794,   539,   795,   540,   807,   809,   831,   541,
     552,   833,   837,   835,   721,   724,   850,   601,   395,   742,
     554,   559,   743,   747,   745,   582,   417,   754,   755,   758,
     744,   746,   469,   757,   765,   749,   748,   751,   439,   463,
     750,   752,   753,   759,   777,   778,   760,   761,   782,   762,
     780,   763,   466,   779,   442,   764,   768,   781,   448,   650,
     769,   771,   770,   790,   774,   791,   792,   647,   737,   801,
     825,   455,   802,   485,   803,   834,   804,   808,   843,   846,
     851,     0,     0,     0,     0,   832,   836,     0,     0,   852,
       0,     0,     0,     0,     0,     0,     0,   569,     0,   151,
     150,   577,     0,   216,     0,     0,   232,     0,     0,   234,
     233,   235,   152,   153,   164,     0,   246,     0,     0,   154,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   632,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   184,   171,     0,     0,   182,     0,     0,   198,
       0,     0,     0,     0,     0,     0,     0,   172,     0,     0,
     183,     0,     0,   199,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     818,     0,     0,     0,   819,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   818,     0,     0,
       0,   819
  };

  const short int
  Dhcp6Parser::yycheck_[] =
  {
      62,    67,    65,    65,    66,    67,    68,    69,    70,    71,
      72,    70,    70,    70,   503,    65,    65,    65,    66,    67,
      68,    14,    65,   500,     5,   499,     7,    10,     9,    15,
       7,    68,    74,    75,    20,    21,    22,    23,    24,    25,
      26,    27,    11,     7,    13,    14,     3,    15,     7,     6,
      36,    28,    29,    30,    31,    84,    85,    86,    35,    28,
      29,    30,    31,    32,    33,    34,    35,    44,    36,    46,
      38,    39,    35,    41,    42,    43,    53,    54,    55,    56,
      57,    58,    45,    35,    36,    74,    75,    64,    65,    52,
      59,    60,    61,    62,    71,    36,   138,    35,     0,    15,
      64,   138,     7,    35,    73,     3,     3,    76,    24,     6,
       8,    63,   111,   112,    83,    47,    48,    49,    50,    51,
      52,     7,    91,    92,    62,     7,    95,     7,    66,    67,
      68,    69,    70,    68,    69,   118,    36,    37,    38,    39,
      40,   124,   125,    77,    78,    79,    80,    81,    82,     3,
       3,     3,   138,     6,     8,   138,     8,   138,   139,   140,
     141,   138,     3,   114,   115,   116,   117,     8,     7,   138,
     138,    87,    88,    89,    90,   138,    93,    94,     3,   120,
       3,   122,   123,     8,     3,     8,   138,     3,     3,     8,
     141,     3,     8,     8,     3,   138,     8,   138,     3,     8,
     138,     3,     3,     8,     6,     6,   138,   126,   127,   128,
     129,   130,   131,   132,   133,   134,   135,   136,   137,   696,
     694,     3,   138,     3,     3,   714,     8,    12,     8,     8,
       3,     3,   294,     7,     3,     8,     8,     7,   138,    96,
      97,    98,    99,   100,   101,   102,   103,   104,   105,   106,
     107,   108,   109,   110,     7,     3,     3,     3,     7,   321,
       8,     8,     8,   321,     3,    16,    17,    18,    19,     8,
     333,   333,     7,   321,     6,   337,     4,     8,   344,     3,
       3,   138,   344,   333,   333,   333,   449,   450,   451,   337,
     333,   353,   285,   286,     4,     4,   344,     4,     4,     4,
     362,     4,     4,     4,   366,   353,     3,   366,   366,   366,
       8,     4,     4,     4,     4,   139,     4,     4,   138,     8,
       4,     3,     8,     8,   386,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
     139,   139,   139,   139,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,   139,     4,     4,     4,     4,
       4,     4,     4,   139,   141,     4,     4,     4,     4,     4,
       4,     4,   139,     4,   139,   139,     4,     4,     4,     4,
       4,     4,     4,     4,   139,     4,     4,     4,     4,   141,
       4,   141,     4,     4,     4,   139,   141,     4,   139,   139,
     393,   394,     4,     4,   141,   141,     4,   141,   141,     4,
       4,     7,   138,   138,     7,     7,     7,     7,     5,     5,
       5,     5,     5,     5,     5,     5,     3,   138,     7,     7,
     492,   493,     7,     7,   492,   493,     5,     8,     5,     5,
       5,   503,   138,   505,   138,     7,     7,     7,   510,     7,
     113,     7,   510,     7,     4,   138,     7,   138,   138,     7,
       7,     4,   510,     8,     4,     4,     4,    72,     4,     6,
       3,     6,     3,     3,   138,   468,   138,   138,     6,     6,
       6,     3,     6,     4,     4,     4,     4,     4,     4,   138,
       4,     4,     4,   486,     3,     6,     3,   138,   138,     3,
       6,     4,     4,     8,     4,     4,   138,     4,   138,   138,
       4,     4,     4,   119,     4,     6,     3,     5,   138,     4,
     441,     4,     8,   138,     8,   138,     8,     7,     4,   138,
     138,     4,     7,     5,   138,   138,     4,   498,   294,   139,
     487,   491,   141,   679,   141,   493,   317,   691,   694,   700,
     139,   139,   369,   698,   707,   684,   682,   687,   333,   362,
     685,   688,   690,   139,   725,   727,   139,   139,   733,   139,
     730,   139,   366,   728,   337,   139,   139,   731,   344,   510,
     139,   714,   139,   138,   718,   138,   138,   505,   667,   138,
     813,   353,   138,   386,   138,   829,   138,   138,   121,   841,
     848,    -1,    -1,    -1,    -1,   139,   138,    -1,    -1,   138,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   679,    -1,   682,
     682,   679,    -1,   685,    -1,    -1,   688,    -1,    -1,   688,
     688,   688,   682,   682,   682,    -1,   698,    -1,    -1,   682,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   714,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   728,   725,    -1,    -1,   728,    -1,    -1,   731,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   725,    -1,    -1,
     728,    -1,    -1,   731,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     812,    -1,    -1,    -1,   812,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   829,    -1,    -1,
      -1,   829
  };

  const unsigned short int
  Dhcp6Parser::yystos_[] =
  {
       0,   126,   127,   128,   129,   130,   131,   132,   133,   134,
     135,   136,   137,   143,   144,   145,   146,   147,   148,   149,
     150,   151,   152,   153,   154,   155,     0,     5,     7,     9,
     138,   139,   140,   141,   156,   157,   158,   163,     7,   172,
       7,   178,     7,   189,     7,   258,     7,   321,     7,   335,
       7,   352,     7,   280,     7,   304,     7,   234,     7,   406,
     164,   159,   173,   179,   190,   259,   322,   336,   353,   281,
     305,   235,   407,   156,   165,   166,   138,   161,   162,    10,
     118,   124,   125,   138,   171,   174,   175,   176,   434,   436,
     438,    11,    13,    14,    28,    29,    30,    31,    32,    33,
      34,    35,    59,    60,    61,    62,    73,    76,    83,    91,
      92,    95,   171,   180,   181,   182,   183,   184,   185,   186,
     187,   193,   195,   215,   221,   226,   228,   242,   252,   274,
     298,   373,   383,   395,   396,   404,    12,   191,     7,    44,
      46,    53,    54,    55,    56,    57,    58,    64,    65,    71,
     171,   182,   183,   184,   185,   260,   261,   262,   264,   266,
     268,   270,   272,   273,   298,   315,   329,   346,   369,    45,
      52,   171,   298,   323,   324,   325,   327,    47,    48,    49,
      50,    51,   171,   298,   327,   337,   338,   339,   341,   342,
     344,   345,    62,    66,    67,    68,    69,    70,   171,   298,
     354,   355,   356,   357,   359,   361,   363,   365,   367,    15,
      36,    38,    39,    41,    42,    43,   171,   209,   282,   283,
     284,   285,   286,   287,   288,   290,   292,   294,   295,   297,
      37,    40,   171,   209,   286,   292,   306,   307,   308,   309,
     310,   312,   313,   314,    74,    75,   171,   236,   237,   238,
     240,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   171,   408,   409,   410,
     411,   413,   415,   416,   418,   419,   420,   423,   425,   426,
     427,   428,   429,   432,     6,     3,     4,     8,     3,   177,
     439,   435,   437,     4,     3,     8,   188,   194,   196,     4,
       4,     4,     4,     4,   253,   275,   299,   216,   227,   222,
     374,   229,   243,   384,     4,   397,   405,     3,     8,   192,
       8,   376,   316,   330,   263,   265,   267,     4,     4,   271,
     269,   347,   370,     3,     8,   326,   328,     3,     8,   340,
       4,   343,     4,     4,     3,     8,   368,   358,   360,   362,
     364,   366,     8,     3,   289,   210,     4,   293,   291,   296,
       4,     8,     3,   311,     4,     8,     3,   239,   241,     3,
       8,     4,   412,   414,     4,   417,     4,     4,   421,   424,
       4,     4,     4,     4,   430,   433,     3,     8,   156,   156,
     138,     4,     4,     4,     4,   175,     4,     4,     4,   139,
     139,   139,   139,   139,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,   139,     4,     4,   181,     4,    63,
     171,   209,   298,   377,   378,   379,   380,   381,     4,     4,
       4,     4,     4,   139,   141,     4,     4,     4,     4,   261,
       4,     4,   324,     4,   139,     4,   139,   139,   338,     4,
       4,     4,     4,     4,     4,   356,     4,     4,   139,     4,
       4,     4,   141,   284,     4,   141,   308,     4,     4,   237,
     141,     4,     4,   139,     4,   139,   139,     4,     4,   141,
     141,   141,   141,     4,     4,   409,     4,     7,     7,   156,
     156,     7,     7,     7,     5,     5,     5,     5,     5,     5,
       5,     5,     7,     7,     7,     7,     5,   167,   382,     8,
       3,     5,     5,   138,   138,   138,   138,   138,     5,     7,
     138,   158,   160,   138,   138,   167,   167,   167,   138,   138,
     138,   138,   138,   138,   138,   138,   138,   138,   156,   138,
     138,   138,   111,   112,   422,   113,   114,   115,   116,   117,
     141,   431,   138,   156,   180,   119,   440,   441,   442,   191,
      15,    20,    21,    22,    23,    24,    25,    26,    27,   171,
     197,   198,   199,   202,   204,   206,   208,   209,   211,   212,
     213,   214,   197,     7,   254,   255,   256,     7,   276,   277,
     278,     7,   300,   301,   302,    68,   138,   217,   218,   219,
     220,   165,    69,   219,   223,   224,   225,   268,   375,     7,
     230,   231,   232,    77,    78,    79,    80,    81,    82,   244,
     245,   246,   247,   248,   249,   250,   251,    15,    87,    88,
      89,    90,   171,   211,   385,   386,   387,   390,   391,   393,
     394,    93,    94,   398,   399,   400,   402,   408,   168,     4,
     379,     7,   317,   318,   319,     7,   331,   332,   333,     7,
     348,   349,   350,    72,   371,     8,   443,     3,     8,     8,
     200,   203,   205,   207,     4,     4,     4,     4,     4,     3,
       8,     8,   257,     6,     3,   279,     6,     3,   303,     6,
       3,     3,     6,     6,     3,     6,     3,     6,   233,     6,
       3,     4,     4,     4,     4,     4,     4,     3,     8,   388,
     392,     4,     4,     4,     3,     8,   401,   403,     3,     8,
       8,   138,   169,   170,   138,   320,     6,     3,   334,     6,
       3,   351,     6,     3,   372,     8,     4,   441,     4,     4,
       4,     4,   139,   141,   139,   141,   139,   198,   260,   256,
     282,   278,   306,   302,   218,   224,   268,   236,   232,   139,
     139,   139,   139,   139,   139,   245,     4,     4,   139,   139,
     139,   386,     4,     4,   399,     6,     3,   323,   319,   337,
     333,   354,   350,     4,     5,    16,    17,    18,    19,   201,
     138,   138,   138,     8,     8,     8,     8,    84,    85,    86,
     389,   138,   138,   138,   138,     8,     8,     8,   138,     7,
     444,   445,   446,     3,     6,   120,   122,   123,   171,   209,
     447,   448,   449,   450,   452,   445,   453,     4,   451,     3,
       8,     4,   139,     4,   448,     5,   138,     7,   454,   455,
     456,     3,     6,   121,   457,   458,   455,   459,     3,     8,
       4,   458,   138
  };

  const unsigned short int
  Dhcp6Parser::yyr1_[] =
  {
       0,   142,   144,   143,   145,   143,   146,   143,   147,   143,
     148,   143,   149,   143,   150,   143,   151,   143,   152,   143,
     153,   143,   154,   143,   155,   143,   156,   156,   156,   156,
     156,   156,   156,   157,   159,   158,   160,   161,   161,   162,
     162,   164,   163,   165,   165,   166,   166,   168,   167,   169,
     169,   170,   170,   171,   173,   172,   174,   174,   175,   175,
     175,   175,   175,   177,   176,   179,   178,   180,   180,   181,
     181,   181,   181,   181,   181,   181,   181,   181,   181,   181,
     181,   181,   181,   181,   181,   181,   181,   181,   181,   181,
     181,   182,   183,   184,   185,   186,   188,   187,   190,   189,
     192,   191,   194,   193,   196,   195,   197,   197,   198,   198,
     198,   198,   198,   198,   198,   198,   198,   198,   198,   200,
     199,   201,   201,   201,   201,   203,   202,   205,   204,   207,
     206,   208,   210,   209,   211,   212,   213,   214,   216,   215,
     217,   217,   218,   218,   219,   220,   222,   221,   223,   223,
     224,   224,   225,   227,   226,   229,   228,   230,   230,   231,
     231,   233,   232,   235,   234,   236,   236,   236,   237,   237,
     239,   238,   241,   240,   243,   242,   244,   244,   245,   245,
     245,   245,   245,   245,   246,   247,   248,   249,   250,   251,
     253,   252,   254,   254,   255,   255,   257,   256,   259,   258,
     260,   260,   261,   261,   261,   261,   261,   261,   261,   261,
     261,   261,   261,   261,   261,   261,   261,   261,   261,   263,
     262,   265,   264,   267,   266,   269,   268,   271,   270,   272,
     273,   275,   274,   276,   276,   277,   277,   279,   278,   281,
     280,   282,   282,   283,   283,   284,   284,   284,   284,   284,
     284,   284,   284,   285,   286,   287,   289,   288,   291,   290,
     293,   292,   294,   296,   295,   297,   299,   298,   300,   300,
     301,   301,   303,   302,   305,   304,   306,   306,   307,   307,
     308,   308,   308,   308,   308,   308,   309,   311,   310,   312,
     313,   314,   316,   315,   317,   317,   318,   318,   320,   319,
     322,   321,   323,   323,   324,   324,   324,   324,   326,   325,
     328,   327,   330,   329,   331,   331,   332,   332,   334,   333,
     336,   335,   337,   337,   338,   338,   338,   338,   338,   338,
     338,   338,   340,   339,   341,   343,   342,   344,   345,   347,
     346,   348,   348,   349,   349,   351,   350,   353,   352,   354,
     354,   355,   355,   356,   356,   356,   356,   356,   356,   356,
     356,   358,   357,   360,   359,   362,   361,   364,   363,   366,
     365,   368,   367,   370,   369,   372,   371,   374,   373,   375,
     375,   376,   268,   377,   377,   378,   378,   379,   379,   379,
     379,   380,   382,   381,   384,   383,   385,   385,   386,   386,
     386,   386,   386,   386,   386,   388,   387,   389,   389,   389,
     390,   392,   391,   393,   394,   395,   397,   396,   398,   398,
     399,   399,   401,   400,   403,   402,   405,   404,   407,   406,
     408,   408,   409,   409,   409,   409,   409,   409,   409,   409,
     409,   409,   409,   409,   409,   409,   409,   409,   410,   412,
     411,   414,   413,   415,   417,   416,   418,   419,   421,   420,
     422,   422,   424,   423,   425,   426,   427,   428,   430,   429,
     431,   431,   431,   431,   431,   433,   432,   435,   434,   437,
     436,   439,   438,   440,   440,   441,   443,   442,   444,   444,
     446,   445,   447,   447,   448,   448,   448,   448,   448,   449,
     451,   450,   453,   452,   454,   454,   456,   455,   457,   457,
     459,   458
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
       1,     1,     1,     1,     1,     1,     1,     1,     1,     0,
       4,     1,     1,     1,     1,     0,     4,     0,     4,     0,
       4,     3,     0,     4,     3,     3,     3,     3,     0,     6,
       1,     3,     1,     1,     1,     1,     0,     6,     1,     3,
       1,     1,     1,     0,     6,     0,     6,     0,     1,     1,
       3,     0,     4,     0,     4,     1,     3,     1,     1,     1,
       0,     4,     0,     4,     0,     6,     1,     3,     1,     1,
       1,     1,     1,     1,     3,     3,     3,     3,     3,     3,
       0,     6,     0,     1,     1,     3,     0,     4,     0,     4,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     4,     3,
       3,     0,     6,     0,     1,     1,     3,     0,     4,     0,
       4,     0,     1,     1,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     3,     1,     0,     4,     0,     4,
       0,     4,     1,     0,     4,     3,     0,     6,     0,     1,
       1,     3,     0,     4,     0,     4,     0,     1,     1,     3,
       1,     1,     1,     1,     1,     1,     1,     0,     4,     1,
       1,     3,     0,     6,     0,     1,     1,     3,     0,     4,
       0,     4,     1,     3,     1,     1,     1,     1,     0,     4,
       0,     4,     0,     6,     0,     1,     1,     3,     0,     4,
       0,     4,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     0,     4,     3,     0,     4,     3,     3,     0,
       6,     0,     1,     1,     3,     0,     4,     0,     4,     0,
       1,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     6,     0,     4,     0,     6,     1,
       3,     0,     4,     0,     1,     1,     3,     1,     1,     1,
       1,     1,     0,     4,     0,     6,     1,     3,     1,     1,
       1,     1,     1,     1,     1,     0,     4,     1,     1,     1,
       3,     0,     4,     3,     3,     3,     0,     6,     1,     3,
       1,     1,     0,     4,     0,     4,     0,     6,     0,     4,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     3,     0,
       4,     0,     4,     3,     0,     4,     3,     3,     0,     4,
       1,     1,     0,     4,     3,     3,     3,     3,     0,     4,
       1,     1,     1,     1,     1,     0,     4,     0,     4,     0,
       4,     0,     6,     1,     3,     1,     0,     6,     1,     3,
       0,     4,     1,     3,     1,     1,     1,     1,     1,     3,
       0,     4,     0,     6,     1,     3,     0,     4,     1,     3,
       0,     4
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
  "\"connect-timeout\"", "\"preferred-lifetime\"", "\"valid-lifetime\"",
  "\"renew-timer\"", "\"rebind-timer\"", "\"decline-probation-period\"",
  "\"subnet6\"", "\"option-def\"", "\"option-data\"", "\"name\"",
  "\"data\"", "\"code\"", "\"space\"", "\"csv-format\"",
  "\"record-types\"", "\"encapsulate\"", "\"array\"", "\"pools\"",
  "\"pool\"", "\"pd-pools\"", "\"prefix\"", "\"prefix-len\"",
  "\"excluded-prefix\"", "\"excluded-prefix-len\"", "\"delegated-len\"",
  "\"user-context\"", "\"subnet\"", "\"interface\"", "\"interface-id\"",
  "\"id\"", "\"rapid-commit\"", "\"reservation-mode\"", "\"mac-sources\"",
  "\"relay-supplied-options\"", "\"host-reservation-identifiers\"",
  "\"client-classes\"", "\"test\"", "\"client-class\"", "\"reservations\"",
  "\"ip-addresses\"", "\"prefixes\"", "\"duid\"", "\"hw-address\"",
  "\"hostname\"", "\"relay\"", "\"ip-address\"", "\"hooks-libraries\"",
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
  "\"always-include-fqdn\"", "\"allow-client-update\"",
  "\"override-no-update\"", "\"override-client-update\"",
  "\"replace-client-name\"", "\"generated-prefix\"", "\"UDP\"", "\"TCP\"",
  "\"JSON\"", "\"when-present\"", "\"never\"", "\"always\"",
  "\"when-not-present\"", "\"Logging\"", "\"loggers\"",
  "\"output_options\"", "\"output\"", "\"debuglevel\"", "\"severity\"",
  "\"Dhcp4\"", "\"DhcpDdns\"", "TOPLEVEL_JSON", "TOPLEVEL_DHCP6",
  "SUB_DHCP6", "SUB_INTERFACES6", "SUB_SUBNET6", "SUB_POOL6",
  "SUB_PD_POOL", "SUB_RESERVATION", "SUB_OPTION_DEF", "SUB_OPTION_DATA",
  "SUB_HOOKS_LIBRARY", "SUB_DHCP_DDNS", "\"constant string\"",
  "\"integer\"", "\"floating point\"", "\"boolean\"", "$accept", "start",
  "$@1", "$@2", "$@3", "$@4", "$@5", "$@6", "$@7", "$@8", "$@9", "$@10",
  "$@11", "$@12", "value", "sub_json", "map2", "$@13", "map_value",
  "map_content", "not_empty_map", "list_generic", "$@14", "list_content",
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
  "mac_sources", "$@29", "mac_sources_list", "mac_sources_value",
  "duid_id", "string_id", "host_reservation_identifiers", "$@30",
  "host_reservation_identifiers_list", "host_reservation_identifier",
  "hw_address_id", "relay_supplied_options", "$@31", "hooks_libraries",
  "$@32", "hooks_libraries_list", "not_empty_hooks_libraries_list",
  "hooks_library", "$@33", "sub_hooks_library", "$@34", "hooks_params",
  "hooks_param", "library", "$@35", "parameters", "$@36",
  "expired_leases_processing", "$@37", "expired_leases_params",
  "expired_leases_param", "reclaim_timer_wait_time",
  "flush_reclaimed_timer_wait_time", "hold_reclaimed_time",
  "max_reclaim_leases", "max_reclaim_time", "unwarned_reclaim_cycles",
  "subnet6_list", "$@38", "subnet6_list_content", "not_empty_subnet6_list",
  "subnet6", "$@39", "sub_subnet6", "$@40", "subnet6_params",
  "subnet6_param", "subnet", "$@41", "interface", "$@42", "interface_id",
  "$@43", "client_class", "$@44", "reservation_mode", "$@45", "id",
  "rapid_commit", "option_def_list", "$@46", "option_def_list_content",
  "not_empty_option_def_list", "option_def_entry", "$@47",
  "sub_option_def", "$@48", "option_def_params",
  "not_empty_option_def_params", "option_def_param", "option_def_name",
  "code", "option_def_code", "option_def_type", "$@49",
  "option_def_record_types", "$@50", "space", "$@51", "option_def_space",
  "option_def_encapsulate", "$@52", "option_def_array", "option_data_list",
  "$@53", "option_data_list_content", "not_empty_option_data_list",
  "option_data_entry", "$@54", "sub_option_data", "$@55",
  "option_data_params", "not_empty_option_data_params",
  "option_data_param", "option_data_name", "option_data_data", "$@56",
  "option_data_code", "option_data_space", "option_data_csv_format",
  "pools_list", "$@57", "pools_list_content", "not_empty_pools_list",
  "pool_list_entry", "$@58", "sub_pool6", "$@59", "pool_params",
  "pool_param", "pool_entry", "$@60", "user_context", "$@61",
  "pd_pools_list", "$@62", "pd_pools_list_content",
  "not_empty_pd_pools_list", "pd_pool_entry", "$@63", "sub_pd_pool",
  "$@64", "pd_pool_params", "pd_pool_param", "pd_prefix", "$@65",
  "pd_prefix_len", "excluded_prefix", "$@66", "excluded_prefix_len",
  "pd_delegated_len", "reservations", "$@67", "reservations_list",
  "not_empty_reservations_list", "reservation", "$@68", "sub_reservation",
  "$@69", "reservation_params", "not_empty_reservation_params",
  "reservation_param", "ip_addresses", "$@70", "prefixes", "$@71", "duid",
  "$@72", "hw_address", "$@73", "hostname", "$@74",
  "reservation_client_classes", "$@75", "relay", "$@76", "relay_map",
  "$@77", "client_classes", "$@78", "client_classes_list", "$@79",
  "client_class_params", "not_empty_client_class_params",
  "client_class_param", "client_class_name", "client_class_test", "$@80",
  "server_id", "$@81", "server_id_params", "server_id_param",
  "server_id_type", "$@82", "duid_type", "htype", "identifier", "$@83",
  "time", "enterprise_id", "dhcp4o6_port", "control_socket", "$@84",
  "control_socket_params", "control_socket_param", "socket_type", "$@85",
  "socket_name", "$@86", "dhcp_ddns", "$@87", "sub_dhcp_ddns", "$@88",
  "dhcp_ddns_params", "dhcp_ddns_param", "enable_updates",
  "qualifying_suffix", "$@89", "server_ip", "$@90", "server_port",
  "sender_ip", "$@91", "sender_port", "max_queue_size", "ncr_protocol",
  "$@92", "ncr_protocol_value", "ncr_format", "$@93",
  "always_include_fqdn", "allow_client_update", "override_no_update",
  "override_client_update", "replace_client_name", "$@94",
  "replace_client_name_value", "generated_prefix", "$@95",
  "dhcp4_json_object", "$@96", "dhcpddns_json_object", "$@97",
  "logging_object", "$@98", "logging_params", "logging_param", "loggers",
  "$@99", "loggers_entries", "logger_entry", "$@100", "logger_params",
  "logger_param", "debuglevel", "severity", "$@101", "output_options_list",
  "$@102", "output_options_list_content", "output_entry", "$@103",
  "output_params", "output_param", "$@104", YY_NULLPTR
  };

#if PARSER6_DEBUG
  const unsigned short int
  Dhcp6Parser::yyrline_[] =
  {
       0,   222,   222,   222,   223,   223,   224,   224,   225,   225,
     226,   226,   227,   227,   228,   228,   229,   229,   230,   230,
     231,   231,   232,   232,   233,   233,   241,   242,   243,   244,
     245,   246,   247,   250,   255,   255,   266,   269,   270,   273,
     277,   284,   284,   291,   292,   295,   299,   306,   306,   313,
     314,   317,   321,   332,   342,   342,   354,   355,   359,   360,
     361,   362,   363,   366,   366,   383,   383,   391,   392,   397,
     398,   399,   400,   401,   402,   403,   404,   405,   406,   407,
     408,   409,   410,   411,   412,   413,   414,   415,   416,   417,
     418,   421,   426,   431,   436,   441,   446,   446,   456,   456,
     464,   464,   474,   474,   484,   484,   494,   495,   498,   499,
     500,   501,   502,   503,   504,   505,   506,   507,   508,   511,
     511,   518,   519,   520,   521,   524,   524,   532,   532,   540,
     540,   548,   553,   553,   561,   566,   571,   576,   581,   581,
     591,   592,   595,   596,   599,   604,   609,   609,   619,   620,
     623,   624,   627,   634,   634,   644,   644,   654,   655,   658,
     659,   662,   662,   670,   670,   678,   679,   680,   683,   684,
     687,   687,   695,   695,   703,   703,   713,   714,   717,   718,
     719,   720,   721,   722,   725,   730,   735,   740,   745,   750,
     758,   758,   771,   772,   775,   776,   783,   783,   806,   806,
     815,   816,   820,   821,   822,   823,   824,   825,   826,   827,
     828,   829,   830,   831,   832,   833,   834,   835,   836,   839,
     839,   847,   847,   855,   855,   863,   863,   871,   871,   879,
     884,   893,   893,   905,   906,   909,   910,   915,   915,   926,
     926,   936,   937,   940,   941,   944,   945,   946,   947,   948,
     949,   950,   951,   954,   956,   961,   963,   963,   971,   971,
     979,   979,   987,   989,   989,   997,  1006,  1006,  1018,  1019,
    1024,  1025,  1030,  1030,  1041,  1041,  1052,  1053,  1058,  1059,
    1064,  1065,  1066,  1067,  1068,  1069,  1072,  1074,  1074,  1082,
    1084,  1086,  1094,  1094,  1106,  1107,  1110,  1111,  1114,  1114,
    1122,  1122,  1130,  1131,  1134,  1135,  1136,  1137,  1140,  1140,
    1148,  1148,  1158,  1158,  1170,  1171,  1174,  1175,  1178,  1178,
    1186,  1186,  1194,  1195,  1198,  1199,  1200,  1201,  1202,  1203,
    1204,  1205,  1208,  1208,  1216,  1221,  1221,  1229,  1234,  1242,
    1242,  1252,  1253,  1256,  1257,  1260,  1260,  1268,  1268,  1276,
    1277,  1280,  1281,  1285,  1286,  1287,  1288,  1289,  1290,  1291,
    1292,  1295,  1295,  1305,  1305,  1315,  1315,  1323,  1323,  1331,
    1331,  1339,  1339,  1352,  1352,  1362,  1362,  1373,  1373,  1383,
    1384,  1387,  1387,  1395,  1396,  1399,  1400,  1403,  1404,  1405,
    1406,  1409,  1411,  1411,  1422,  1422,  1432,  1433,  1436,  1437,
    1438,  1439,  1440,  1441,  1442,  1445,  1445,  1452,  1453,  1454,
    1457,  1462,  1462,  1470,  1475,  1482,  1489,  1489,  1499,  1500,
    1503,  1504,  1507,  1507,  1515,  1515,  1525,  1525,  1535,  1535,
    1543,  1544,  1547,  1548,  1549,  1550,  1551,  1552,  1553,  1554,
    1555,  1556,  1557,  1558,  1559,  1560,  1561,  1562,  1565,  1570,
    1570,  1578,  1578,  1586,  1591,  1591,  1599,  1604,  1609,  1609,
    1617,  1618,  1621,  1621,  1629,  1634,  1639,  1644,  1649,  1649,
    1657,  1660,  1663,  1666,  1669,  1675,  1675,  1685,  1685,  1692,
    1692,  1704,  1704,  1717,  1718,  1722,  1726,  1726,  1738,  1739,
    1743,  1743,  1751,  1752,  1755,  1756,  1757,  1758,  1759,  1762,
    1766,  1766,  1774,  1774,  1784,  1785,  1788,  1788,  1796,  1797,
    1800,  1800
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
#line 4144 "dhcp6_parser.cc" // lalr1.cc:1167
#line 1808 "dhcp6_parser.yy" // lalr1.cc:1168


void
isc::dhcp::Dhcp6Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
