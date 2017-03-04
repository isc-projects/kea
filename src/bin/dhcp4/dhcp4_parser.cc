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
#define yylex   parser4_lex

// First part of user declarations.

#line 39 "dhcp4_parser.cc" // lalr1.cc:404

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

#include "dhcp4_parser.h"

// User implementation prologue.

#line 53 "dhcp4_parser.cc" // lalr1.cc:412
// Unqualified %code blocks.
#line 34 "dhcp4_parser.yy" // lalr1.cc:413

#include <dhcp4/parser_context.h>

#line 59 "dhcp4_parser.cc" // lalr1.cc:413


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
#if PARSER4_DEBUG

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

#else // !PARSER4_DEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YYUSE(Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void>(0)
# define YY_STACK_PRINT()                static_cast<void>(0)

#endif // !PARSER4_DEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)

#line 14 "dhcp4_parser.yy" // lalr1.cc:479
namespace isc { namespace dhcp {
#line 145 "dhcp4_parser.cc" // lalr1.cc:479

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
  inline
  Dhcp4Parser::by_state::by_state ()
    : state (empty_state)
  {}

  inline
  Dhcp4Parser::by_state::by_state (const by_state& other)
    : state (other.state)
  {}

  inline
  void
  Dhcp4Parser::by_state::clear ()
  {
    state = empty_state;
  }

  inline
  void
  Dhcp4Parser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  inline
  Dhcp4Parser::by_state::by_state (state_type s)
    : state (s)
  {}

  inline
  Dhcp4Parser::symbol_number_type
  Dhcp4Parser::by_state::type_get () const
  {
    if (state == empty_state)
      return empty_symbol;
    else
      return yystos_[state];
  }

  inline
  Dhcp4Parser::stack_symbol_type::stack_symbol_type ()
  {}


  inline
  Dhcp4Parser::stack_symbol_type::stack_symbol_type (state_type s, symbol_type& that)
    : super_type (s, that.location)
  {
      switch (that.type_get ())
    {
      case 148: // value
      case 152: // map_value
      case 190: // socket_type
      case 199: // db_type
      case 404: // ncr_protocol_value
      case 412: // replace_client_name_value
        value.move< ElementPtr > (that.value);
        break;

      case 134: // "boolean"
        value.move< bool > (that.value);
        break;

      case 133: // "floating point"
        value.move< double > (that.value);
        break;

      case 132: // "integer"
        value.move< int64_t > (that.value);
        break;

      case 131: // "constant string"
        value.move< std::string > (that.value);
        break;

      default:
        break;
    }

    // that is emptied.
    that.type = empty_symbol;
  }

  inline
  Dhcp4Parser::stack_symbol_type&
  Dhcp4Parser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
      switch (that.type_get ())
    {
      case 148: // value
      case 152: // map_value
      case 190: // socket_type
      case 199: // db_type
      case 404: // ncr_protocol_value
      case 412: // replace_client_name_value
        value.copy< ElementPtr > (that.value);
        break;

      case 134: // "boolean"
        value.copy< bool > (that.value);
        break;

      case 133: // "floating point"
        value.copy< double > (that.value);
        break;

      case 132: // "integer"
        value.copy< int64_t > (that.value);
        break;

      case 131: // "constant string"
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
            case 131: // "constant string"

#line 206 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< std::string > (); }
#line 362 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 132: // "integer"

#line 206 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< int64_t > (); }
#line 369 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 133: // "floating point"

#line 206 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< double > (); }
#line 376 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 134: // "boolean"

#line 206 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< bool > (); }
#line 383 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 148: // value

#line 206 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 390 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 152: // map_value

#line 206 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 397 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 190: // socket_type

#line 206 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 404 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 199: // db_type

#line 206 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 411 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 404: // ncr_protocol_value

#line 206 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 418 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 412: // replace_client_name_value

#line 206 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 425 "dhcp4_parser.cc" // lalr1.cc:636
        break;


      default:
        break;
    }
    yyo << ')';
  }
#endif

  inline
  void
  Dhcp4Parser::yypush_ (const char* m, state_type s, symbol_type& sym)
  {
    stack_symbol_type t (s, sym);
    yypush_ (m, t);
  }

  inline
  void
  Dhcp4Parser::yypush_ (const char* m, stack_symbol_type& s)
  {
    if (m)
      YY_SYMBOL_PRINT (m, s);
    yystack_.push (s);
  }

  inline
  void
  Dhcp4Parser::yypop_ (unsigned int n)
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

  inline Dhcp4Parser::state_type
  Dhcp4Parser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - yyntokens_] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - yyntokens_];
  }

  inline bool
  Dhcp4Parser::yy_pact_value_is_default_ (int yyvalue)
  {
    return yyvalue == yypact_ninf_;
  }

  inline bool
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
      case 148: // value
      case 152: // map_value
      case 190: // socket_type
      case 199: // db_type
      case 404: // ncr_protocol_value
      case 412: // replace_client_name_value
        yylhs.value.build< ElementPtr > ();
        break;

      case 134: // "boolean"
        yylhs.value.build< bool > ();
        break;

      case 133: // "floating point"
        yylhs.value.build< double > ();
        break;

      case 132: // "integer"
        yylhs.value.build< int64_t > ();
        break;

      case 131: // "constant string"
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
#line 215 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.NO_KEYWORD; }
#line 670 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 4:
#line 216 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.CONFIG; }
#line 676 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 6:
#line 217 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.DHCP4; }
#line 682 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 8:
#line 218 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.INTERFACES_CONFIG; }
#line 688 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 10:
#line 219 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.SUBNET4; }
#line 694 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 12:
#line 220 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.POOLS; }
#line 700 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 14:
#line 221 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.RESERVATIONS; }
#line 706 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 16:
#line 222 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.OPTION_DEF; }
#line 712 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 18:
#line 223 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.OPTION_DATA; }
#line 718 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 20:
#line 224 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.HOOKS_LIBRARIES; }
#line 724 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 22:
#line 225 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.DHCP_DDNS; }
#line 730 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 24:
#line 233 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 736 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 25:
#line 234 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as< double > (), ctx.loc2pos(yystack_[0].location))); }
#line 742 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 26:
#line 235 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 748 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 27:
#line 236 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 754 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 28:
#line 237 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 760 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 29:
#line 238 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 766 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 30:
#line 239 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 772 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 31:
#line 242 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as< ElementPtr > ());
}
#line 781 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 32:
#line 247 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 792 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 33:
#line 252 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 802 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 34:
#line 258 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 808 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 37:
#line 265 "dhcp4_parser.yy" // lalr1.cc:859
    {
                  // map containing a single entry
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 817 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 38:
#line 269 "dhcp4_parser.yy" // lalr1.cc:859
    {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 827 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 39:
#line 276 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 836 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 40:
#line 279 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // list parsing complete. Put any sanity checking here
}
#line 844 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 43:
#line 287 "dhcp4_parser.yy" // lalr1.cc:859
    {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 853 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 44:
#line 291 "dhcp4_parser.yy" // lalr1.cc:859
    {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 862 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 45:
#line 298 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // List parsing about to start
}
#line 870 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 46:
#line 300 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // list parsing complete. Put any sanity checking here
    //ctx.stack_.pop_back();
}
#line 879 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 49:
#line 309 "dhcp4_parser.yy" // lalr1.cc:859
    {
                          ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 888 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 50:
#line 313 "dhcp4_parser.yy" // lalr1.cc:859
    {
                          ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 897 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 51:
#line 324 "dhcp4_parser.yy" // lalr1.cc:859
    {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as< std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 908 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 52:
#line 334 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 919 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 53:
#line 339 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 929 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 61:
#line 358 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Dhcp4", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP4);
}
#line 942 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 62:
#line 365 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 954 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 63:
#line 375 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the Dhcp4 map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 964 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 64:
#line 379 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 972 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 88:
#line 412 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 981 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 89:
#line 417 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 990 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 90:
#line 422 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 999 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 91:
#line 427 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr dpp(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 1008 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 92:
#line 432 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr echo(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("echo-client-id", echo);
}
#line 1017 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 93:
#line 437 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr match(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("match-client-id", match);
}
#line 1026 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 94:
#line 443 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces-config", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.INTERFACES_CONFIG);
}
#line 1037 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 95:
#line 448 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1046 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 100:
#line 461 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1056 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 101:
#line 465 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1064 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 102:
#line 469 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1075 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 103:
#line 474 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1084 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 104:
#line 479 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.DHCP_SOCKET_TYPE);
}
#line 1092 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 105:
#line 481 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("dhcp-socket-type", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1101 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 106:
#line 486 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("raw", ctx.loc2pos(yystack_[0].location))); }
#line 1107 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 107:
#line 487 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("udp", ctx.loc2pos(yystack_[0].location))); }
#line 1113 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 108:
#line 490 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lease-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.LEASE_DATABASE);
}
#line 1124 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 109:
#line 495 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1133 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 110:
#line 500 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1144 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 111:
#line 505 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1153 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 127:
#line 529 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.DATABASE_TYPE);
}
#line 1161 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 128:
#line 531 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("type", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1170 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 129:
#line 536 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("memfile", ctx.loc2pos(yystack_[0].location))); }
#line 1176 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 130:
#line 537 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("mysql", ctx.loc2pos(yystack_[0].location))); }
#line 1182 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 131:
#line 538 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("postgresql", ctx.loc2pos(yystack_[0].location))); }
#line 1188 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 132:
#line 539 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("cql", ctx.loc2pos(yystack_[0].location))); }
#line 1194 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 133:
#line 542 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1202 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 134:
#line 544 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr user(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1212 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 135:
#line 550 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1220 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 136:
#line 552 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr pwd(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 1230 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 137:
#line 558 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1238 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 138:
#line 560 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr h(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 1248 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 139:
#line 566 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr p(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", p);
}
#line 1257 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 140:
#line 571 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1265 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 141:
#line 573 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1275 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 142:
#line 579 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 1284 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 143:
#line 584 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 1293 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 144:
#line 589 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 1302 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 145:
#line 594 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("connect-timeout", n);
}
#line 1311 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 146:
#line 599 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1319 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 147:
#line 601 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr cp(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("contact-points", cp);
    ctx.leave();
}
#line 1329 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 148:
#line 607 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1337 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 149:
#line 609 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr ks(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("keyspace", ks);
    ctx.leave();
}
#line 1347 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 150:
#line 616 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 1358 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 151:
#line 621 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1367 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 158:
#line 636 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1376 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 159:
#line 641 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 1385 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 160:
#line 646 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr circuit(new StringElement("circuit-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(circuit);
}
#line 1394 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 161:
#line 651 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr client(new StringElement("client-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(client);
}
#line 1403 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 162:
#line 656 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 1414 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 163:
#line 661 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1423 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 168:
#line 674 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1433 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 169:
#line 678 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1441 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 170:
#line 682 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1451 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 171:
#line 686 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1459 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 177:
#line 699 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1467 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 178:
#line 701 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr lib(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 1477 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 179:
#line 707 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1485 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 180:
#line 709 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1494 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 181:
#line 715 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.EXPIRED_LEASES_PROCESSING);
}
#line 1505 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 182:
#line 720 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1514 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 191:
#line 737 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 1523 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 192:
#line 742 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 1532 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 193:
#line 747 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 1541 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 194:
#line 752 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 1550 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 195:
#line 757 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 1559 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 196:
#line 762 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 1568 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 197:
#line 770 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet4", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET4);
}
#line 1579 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 198:
#line 775 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1588 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 203:
#line 795 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1598 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 204:
#line 799 "dhcp4_parser.yy" // lalr1.cc:859
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
    ctx.stack_.pop_back();
}
#line 1621 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 205:
#line 818 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the subnet4 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1631 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 206:
#line 822 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1639 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 229:
#line 854 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1647 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 230:
#line 856 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr subnet(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 1657 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 231:
#line 862 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1665 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 232:
#line 864 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface", iface);
    ctx.leave();
}
#line 1675 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 233:
#line 870 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1683 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 234:
#line 872 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface-id", iface);
    ctx.leave();
}
#line 1693 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 235:
#line 878 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1701 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 236:
#line 880 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-subnet", iface);
    ctx.leave();
}
#line 1711 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 237:
#line 886 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1719 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 238:
#line 888 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 1729 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 239:
#line 894 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1737 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 240:
#line 896 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface-id", iface);
    ctx.leave();
}
#line 1747 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 241:
#line 902 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.CLIENT_CLASS);
}
#line 1755 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 242:
#line 904 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr cls(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 1765 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 243:
#line 910 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1773 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 244:
#line 912 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr rm(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservation-mode", rm);
    ctx.leave();
}
#line 1783 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 245:
#line 918 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr id(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 1792 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 246:
#line 923 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr rc(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rapid-commit", rc);
}
#line 1801 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 247:
#line 932 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 1812 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 248:
#line 937 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1821 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 253:
#line 954 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1831 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 254:
#line 958 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1839 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 255:
#line 965 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1849 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 256:
#line 969 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1857 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 270:
#line 995 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr code(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 1866 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 272:
#line 1002 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1874 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 273:
#line 1004 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 1884 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 274:
#line 1010 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1892 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 275:
#line 1012 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 1902 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 276:
#line 1018 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1910 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 277:
#line 1020 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr space(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 1920 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 279:
#line 1028 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1928 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 280:
#line 1030 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr encap(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 1938 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 281:
#line 1036 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr array(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 1947 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 282:
#line 1045 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 1958 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 283:
#line 1050 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1967 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 288:
#line 1069 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1977 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 289:
#line 1073 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1985 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 290:
#line 1080 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1995 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 291:
#line 1084 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 2003 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 303:
#line 1113 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2011 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 304:
#line 1115 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr data(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 2021 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 307:
#line 1125 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr space(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", space);
}
#line 2030 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 308:
#line 1133 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 2041 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 309:
#line 1138 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2050 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 314:
#line 1153 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2060 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 315:
#line 1157 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2068 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 316:
#line 1161 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2078 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 317:
#line 1165 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 2086 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 324:
#line 1179 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2094 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 325:
#line 1181 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr pool(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 2104 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 326:
#line 1187 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2112 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 327:
#line 1189 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("user-context", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2121 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 328:
#line 1197 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 2132 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 329:
#line 1202 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2141 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 334:
#line 1215 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2151 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 335:
#line 1219 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2159 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 336:
#line 1223 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2169 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 337:
#line 1227 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 2177 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 354:
#line 1254 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2185 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 355:
#line 1256 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr next_server(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("next-server", next_server);
    ctx.leave();
}
#line 2195 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 356:
#line 1262 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2203 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 357:
#line 1264 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr srv(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-hostname", srv);
    ctx.leave();
}
#line 2213 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 358:
#line 1270 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2221 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 359:
#line 1272 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr bootfile(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("boot-file-name", bootfile);
    ctx.leave();
}
#line 2231 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 360:
#line 1278 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2239 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 361:
#line 1280 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr addr(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", addr);
    ctx.leave();
}
#line 2249 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 362:
#line 1286 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2257 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 363:
#line 1288 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr d(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 2267 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 364:
#line 1294 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2275 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 365:
#line 1296 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 2285 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 366:
#line 1302 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2293 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 367:
#line 1304 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-id", hw);
    ctx.leave();
}
#line 2303 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 368:
#line 1310 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2311 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 369:
#line 1312 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("circuit-id", hw);
    ctx.leave();
}
#line 2321 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 370:
#line 1319 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2329 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 371:
#line 1321 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr host(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 2339 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 372:
#line 1327 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2350 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 373:
#line 1332 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2359 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 374:
#line 1340 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 2370 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 375:
#line 1345 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2379 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 376:
#line 1350 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2387 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 377:
#line 1352 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr ip(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", ip);
    ctx.leave();
}
#line 2397 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 378:
#line 1361 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 2408 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 379:
#line 1366 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2417 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 382:
#line 1375 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2427 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 383:
#line 1379 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2435 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 396:
#line 1402 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2443 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 397:
#line 1404 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr test(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 2453 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 398:
#line 1414 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 2462 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 399:
#line 1421 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 2473 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 400:
#line 1426 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2482 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 405:
#line 1439 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2490 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 406:
#line 1441 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr stype(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 2500 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 407:
#line 1447 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2508 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 408:
#line 1449 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 2518 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 409:
#line 1457 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 2529 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 410:
#line 1462 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2538 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 411:
#line 1467 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2548 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 412:
#line 1471 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 2556 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 430:
#line 1496 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 2565 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 431:
#line 1501 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2573 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 432:
#line 1503 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("qualifying-suffix", s);
    ctx.leave();
}
#line 2583 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 433:
#line 1509 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2591 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 434:
#line 1511 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 2601 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 435:
#line 1517 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 2610 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 436:
#line 1522 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2618 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 437:
#line 1524 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 2628 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 438:
#line 1530 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 2637 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 439:
#line 1535 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 2646 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 440:
#line 1540 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 2654 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 441:
#line 1542 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2663 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 442:
#line 1548 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 2669 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 443:
#line 1549 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 2675 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 444:
#line 1552 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NCR_FORMAT);
}
#line 2683 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 445:
#line 1554 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 2693 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 446:
#line 1560 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-include-fqdn", b);
}
#line 2702 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 447:
#line 1565 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-no-update", b);
}
#line 2711 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 448:
#line 1570 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-client-update", b);
}
#line 2720 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 449:
#line 1575 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 2728 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 450:
#line 1577 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("replace-client-name", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2737 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 451:
#line 1583 "dhcp4_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("when-present", ctx.loc2pos(yystack_[0].location))); 
      }
#line 2745 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 452:
#line 1586 "dhcp4_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location)));
      }
#line 2753 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 453:
#line 1589 "dhcp4_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("always", ctx.loc2pos(yystack_[0].location)));
      }
#line 2761 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 454:
#line 1592 "dhcp4_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("when-not-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 2769 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 455:
#line 1595 "dhcp4_parser.yy" // lalr1.cc:859
    {
      error(yystack_[0].location, "boolean values for the replace-client-name are "
                "no longer supported");
      }
#line 2778 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 456:
#line 1601 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2786 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 457:
#line 1603 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("generated-prefix", s);
    ctx.leave();
}
#line 2796 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 458:
#line 1611 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2804 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 459:
#line 1613 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("Dhcp6", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2813 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 460:
#line 1618 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2821 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 461:
#line 1620 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("DhcpDdns", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2830 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 462:
#line 1630 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Logging", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.LOGGING);
}
#line 2841 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 463:
#line 1635 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2850 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 467:
#line 1652 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 2861 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 468:
#line 1657 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2870 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 471:
#line 1669 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 2880 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 472:
#line 1673 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2888 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 480:
#line 1688 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr dl(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 2897 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 481:
#line 1693 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2905 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 482:
#line 1695 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 2915 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 483:
#line 1701 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 2926 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 484:
#line 1706 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2935 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 487:
#line 1715 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2945 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 488:
#line 1719 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2953 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 491:
#line 1727 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2961 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 492:
#line 1729 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 2971 "dhcp4_parser.cc" // lalr1.cc:859
    break;


#line 2975 "dhcp4_parser.cc" // lalr1.cc:859
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
  Dhcp4Parser::error (const syntax_error& yyexc)
  {
    error (yyexc.location, yyexc.what());
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


  const short int Dhcp4Parser::yypact_ninf_ = -469;

  const signed char Dhcp4Parser::yytable_ninf_ = -1;

  const short int
  Dhcp4Parser::yypact_[] =
  {
     117,  -469,  -469,  -469,  -469,  -469,  -469,  -469,  -469,  -469,
    -469,  -469,    66,    19,    81,    85,    94,   139,   150,   165,
     172,   184,   193,   199,  -469,  -469,  -469,  -469,  -469,  -469,
    -469,  -469,  -469,  -469,  -469,  -469,  -469,  -469,  -469,  -469,
    -469,  -469,  -469,  -469,  -469,  -469,  -469,  -469,  -469,  -469,
    -469,  -469,  -469,  -469,  -469,  -469,    19,   -79,    17,    29,
      20,    18,   -16,    71,    49,    74,   -35,   118,  -469,   132,
      70,   127,   195,   137,  -469,  -469,  -469,  -469,   248,  -469,
      26,  -469,  -469,  -469,  -469,  -469,  -469,   250,   253,  -469,
    -469,  -469,   258,   261,   263,   265,  -469,  -469,  -469,  -469,
    -469,  -469,  -469,   269,  -469,  -469,  -469,    45,  -469,  -469,
    -469,  -469,  -469,  -469,  -469,  -469,  -469,  -469,  -469,  -469,
    -469,  -469,  -469,  -469,  -469,  -469,  -469,  -469,  -469,  -469,
    -469,    46,  -469,  -469,  -469,  -469,  -469,  -469,  -469,  -469,
    -469,  -469,  -469,   271,   272,  -469,  -469,  -469,  -469,  -469,
    -469,  -469,  -469,  -469,    52,  -469,  -469,  -469,  -469,  -469,
    -469,  -469,  -469,  -469,  -469,  -469,  -469,  -469,  -469,  -469,
    -469,  -469,  -469,  -469,  -469,    56,  -469,  -469,  -469,  -469,
    -469,  -469,  -469,  -469,  -469,  -469,  -469,  -469,  -469,  -469,
     270,   279,  -469,  -469,  -469,  -469,  -469,  -469,  -469,  -469,
    -469,  -469,  -469,  -469,  -469,   275,  -469,  -469,  -469,   281,
    -469,  -469,   282,   280,  -469,  -469,  -469,  -469,  -469,  -469,
    -469,  -469,  -469,  -469,  -469,   283,  -469,  -469,  -469,  -469,
     284,   288,  -469,  -469,  -469,  -469,  -469,  -469,  -469,  -469,
    -469,   111,  -469,  -469,  -469,   293,  -469,  -469,   294,  -469,
     300,   301,  -469,  -469,   302,   303,   305,  -469,  -469,  -469,
     125,  -469,  -469,  -469,  -469,  -469,  -469,  -469,  -469,  -469,
    -469,  -469,  -469,  -469,  -469,  -469,  -469,    19,    19,  -469,
     180,   308,   309,   310,   311,  -469,    17,  -469,   312,   183,
     185,   316,   317,   318,   191,   192,   194,   197,   321,   323,
     324,   326,   327,   328,   329,   202,   331,   332,    29,  -469,
     333,   334,    20,  -469,    65,   335,   336,   339,   340,   341,
     342,   343,   216,   215,   346,   347,   348,   349,    18,  -469,
     350,   351,   -16,  -469,   352,   353,   354,   355,   356,   357,
     358,   359,   360,  -469,    71,   361,   362,   235,   364,   365,
     366,   237,  -469,    49,   368,   239,  -469,    74,   370,   371,
     155,  -469,   242,   373,   374,   249,   375,   251,   252,   376,
     378,   254,   255,   256,   381,   382,   118,  -469,  -469,  -469,
     383,   384,   385,    19,    19,  -469,   386,  -469,  -469,   264,
     387,   389,  -469,  -469,  -469,  -469,   392,   393,   394,   395,
     396,   397,   398,  -469,   399,   400,  -469,   403,    24,  -469,
    -469,  -469,  -469,  -469,  -469,  -469,  -469,   401,   407,  -469,
    -469,  -469,   273,   285,   286,   406,   287,   289,   290,  -469,
    -469,   295,   298,   408,   405,  -469,   299,   417,  -469,   304,
     307,   403,   313,   315,   319,   320,   322,   325,  -469,   330,
     337,  -469,   338,   344,   345,  -469,  -469,   363,  -469,  -469,
     367,    19,  -469,  -469,   369,   372,  -469,   377,  -469,  -469,
      15,   296,  -469,  -469,  -469,    67,   379,  -469,    19,    29,
     380,  -469,  -469,    20,  -469,   133,   133,   418,   424,   425,
     188,    30,   426,   101,   182,   118,  -469,  -469,  -469,  -469,
    -469,   410,  -469,    65,  -469,  -469,  -469,   427,  -469,  -469,
    -469,  -469,  -469,   432,   388,  -469,  -469,  -469,  -469,  -469,
    -469,  -469,  -469,  -469,  -469,  -469,  -469,  -469,  -469,  -469,
    -469,  -469,  -469,  -469,  -469,  -469,  -469,  -469,  -469,  -469,
    -469,  -469,  -469,  -469,  -469,  -469,  -469,  -469,  -469,  -469,
     131,  -469,   151,  -469,  -469,   186,  -469,  -469,  -469,  -469,
     411,   437,   438,   439,   443,  -469,  -469,  -469,   187,  -469,
    -469,  -469,  -469,  -469,  -469,  -469,  -469,  -469,  -469,  -469,
    -469,  -469,   189,  -469,   442,   446,  -469,  -469,   448,   454,
    -469,  -469,   452,   456,  -469,  -469,  -469,  -469,  -469,   104,
    -469,  -469,  -469,  -469,  -469,  -469,   105,  -469,   457,   459,
    -469,   461,   462,   463,   466,   467,   468,   190,  -469,  -469,
    -469,  -469,  -469,  -469,  -469,  -469,  -469,   196,  -469,  -469,
    -469,   221,   390,   391,  -469,  -469,   471,   470,  -469,  -469,
     472,   476,  -469,  -469,   473,  -469,   478,   380,  -469,  -469,
     479,   480,   481,   482,   402,   404,   409,   412,   413,   483,
     484,   133,  -469,  -469,    18,  -469,   418,    49,  -469,   424,
      74,  -469,   425,   188,  -469,    30,  -469,   -35,  -469,   426,
     415,   416,   419,   420,   421,   422,   101,  -469,   485,   486,
     182,  -469,  -469,  -469,   474,   488,  -469,   -16,  -469,   427,
      71,  -469,   432,   491,  -469,   455,  -469,   276,   428,   429,
     430,  -469,  -469,  -469,  -469,  -469,   431,   433,  -469,   222,
    -469,   489,  -469,   493,  -469,  -469,  -469,   223,  -469,  -469,
    -469,  -469,  -469,  -469,  -469,  -469,   434,   435,  -469,  -469,
     436,   224,  -469,   494,  -469,   440,   492,  -469,  -469,  -469,
    -469,  -469,  -469,  -469,  -469,  -469,  -469,  -469,  -469,  -469,
    -469,  -469,  -469,  -469,  -469,  -469,  -469,  -469,   124,  -469,
      57,   492,  -469,  -469,   500,  -469,  -469,  -469,   245,  -469,
    -469,  -469,  -469,  -469,   501,   423,   502,    57,  -469,   469,
    -469,   441,  -469,   504,  -469,  -469,   152,  -469,   414,   504,
    -469,  -469,   247,  -469,  -469,   503,   414,  -469,   444,  -469,
    -469
  };

  const unsigned short int
  Dhcp4Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     1,    39,    32,    28,    27,    24,
      25,    26,    31,     3,    29,    30,    52,     5,    63,     7,
     100,     9,   205,    11,   316,    13,   336,    15,   255,    17,
     290,    19,   170,    21,   411,    23,    41,    35,     0,     0,
       0,     0,     0,   338,   257,   292,     0,     0,    43,     0,
      42,     0,     0,    36,    61,   462,   458,   460,     0,    60,
       0,    54,    56,    58,    59,    57,    94,     0,     0,   354,
     108,   110,     0,     0,     0,     0,   197,   247,   282,   150,
     378,   162,   181,     0,   399,   409,    87,     0,    65,    67,
      68,    69,    70,    84,    85,    72,    73,    74,    75,    79,
      80,    71,    77,    78,    86,    76,    81,    82,    83,   102,
     104,     0,    96,    98,    99,   382,   231,   233,   235,   308,
     229,   237,   239,     0,     0,   243,   241,   328,   374,   228,
     209,   210,   211,   223,     0,   207,   214,   225,   226,   227,
     215,   216,   219,   221,   217,   218,   212,   213,   220,   224,
     222,   324,   326,   323,   321,     0,   318,   320,   322,   356,
     358,   372,   362,   364,   368,   366,   370,   360,   353,   349,
       0,   339,   340,   350,   351,   352,   346,   342,   347,   344,
     345,   348,   343,   272,   140,     0,   276,   274,   279,     0,
     268,   269,     0,   258,   259,   261,   271,   262,   263,   264,
     278,   265,   266,   267,   303,     0,   301,   302,   305,   306,
       0,   293,   294,   296,   297,   298,   299,   300,   177,   179,
     174,     0,   172,   175,   176,     0,   431,   433,     0,   436,
       0,     0,   440,   444,     0,     0,     0,   449,   456,   429,
       0,   413,   415,   416,   417,   418,   419,   420,   421,   422,
     423,   424,   425,   426,   427,   428,    40,     0,     0,    33,
       0,     0,     0,     0,     0,    51,     0,    53,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    64,
       0,     0,     0,   101,   384,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   206,
       0,     0,     0,   317,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   337,     0,     0,     0,     0,     0,     0,
       0,     0,   256,     0,     0,     0,   291,     0,     0,     0,
       0,   171,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   412,    44,    37,
       0,     0,     0,     0,     0,    55,     0,    92,    93,     0,
       0,     0,    88,    89,    90,    91,     0,     0,     0,     0,
       0,     0,     0,   398,     0,     0,    66,     0,     0,    97,
     396,   394,   395,   390,   391,   392,   393,     0,   385,   386,
     388,   389,     0,     0,     0,     0,     0,     0,     0,   245,
     246,     0,     0,     0,     0,   208,     0,     0,   319,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   341,     0,
       0,   270,     0,     0,     0,   281,   260,     0,   307,   295,
       0,     0,   173,   430,     0,     0,   435,     0,   438,   439,
       0,     0,   446,   447,   448,     0,     0,   414,     0,     0,
       0,   459,   461,     0,   355,     0,     0,   199,   249,   284,
       0,     0,   164,     0,     0,     0,    45,   103,   106,   107,
     105,     0,   383,     0,   232,   234,   236,   310,   230,   238,
     240,   244,   242,   330,     0,   325,    34,   327,   357,   359,
     373,   363,   365,   369,   367,   371,   361,   273,   141,   277,
     275,   280,   304,   178,   180,   432,   434,   437,   442,   443,
     441,   445,   451,   452,   453,   454,   455,   450,   457,    38,
       0,   467,     0,   464,   466,     0,   127,   133,   135,   137,
       0,     0,     0,     0,     0,   146,   148,   126,     0,   112,
     114,   115,   116,   117,   118,   119,   120,   121,   122,   123,
     124,   125,     0,   203,     0,   200,   201,   253,     0,   250,
     251,   288,     0,   285,   286,   158,   159,   160,   161,     0,
     152,   154,   155,   156,   157,   380,     0,   168,     0,   165,
     166,     0,     0,     0,     0,     0,     0,     0,   183,   185,
     186,   187,   188,   189,   190,   405,   407,     0,   401,   403,
     404,     0,    47,     0,   387,   314,     0,   311,   312,   334,
       0,   331,   332,   376,     0,    62,     0,     0,   463,    95,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   109,   111,     0,   198,     0,   257,   248,     0,
     292,   283,     0,     0,   151,     0,   379,     0,   163,     0,
       0,     0,     0,     0,     0,     0,     0,   182,     0,     0,
       0,   400,   410,    49,     0,    48,   397,     0,   309,     0,
     338,   329,     0,     0,   375,     0,   465,     0,     0,     0,
       0,   139,   142,   143,   144,   145,     0,     0,   113,     0,
     202,     0,   252,     0,   287,   153,   381,     0,   167,   191,
     192,   193,   194,   195,   196,   184,     0,     0,   402,    46,
       0,     0,   313,     0,   333,     0,     0,   129,   130,   131,
     132,   128,   134,   136,   138,   147,   149,   204,   254,   289,
     169,   406,   408,    50,   315,   335,   377,   471,     0,   469,
       0,     0,   468,   483,     0,   481,   479,   475,     0,   473,
     477,   478,   476,   470,     0,     0,     0,     0,   472,     0,
     480,     0,   474,     0,   482,   487,     0,   485,     0,     0,
     484,   491,     0,   489,   486,     0,     0,   488,     0,   490,
     492
  };

  const short int
  Dhcp4Parser::yypgoto_[] =
  {
    -469,  -469,  -469,  -469,  -469,  -469,  -469,  -469,  -469,  -469,
    -469,  -469,  -469,   -42,  -469,    55,  -469,  -469,  -469,  -469,
    -469,  -469,  -469,  -469,    68,  -469,  -469,  -469,   -58,  -469,
    -469,  -469,   210,  -469,  -469,  -469,  -469,    33,   205,   -60,
     -44,   -40,  -469,  -469,   -39,  -469,  -469,    31,   203,  -469,
    -469,  -469,  -469,  -469,  -469,  -469,  -469,  -469,  -469,  -469,
      32,  -145,  -469,  -469,  -469,  -469,  -469,  -469,  -469,  -469,
    -469,  -469,   -63,  -469,  -469,  -469,  -469,  -469,  -469,  -469,
    -469,  -469,  -469,  -469,  -469,  -156,  -469,  -469,  -469,  -469,
    -469,  -469,  -469,  -469,  -160,  -469,  -469,  -469,  -157,   163,
    -469,  -469,  -469,  -469,  -469,  -469,  -469,  -162,  -469,  -469,
    -469,  -469,  -469,  -469,  -469,  -469,  -469,  -469,  -141,  -469,
    -469,  -469,  -138,   200,  -469,  -469,  -469,  -469,  -469,  -469,
    -469,  -469,  -469,  -469,  -469,  -469,  -468,  -469,  -469,  -469,
    -469,  -469,  -469,  -469,  -469,  -469,  -142,  -469,  -469,  -469,
    -137,  -469,   178,  -469,   -49,  -469,  -469,  -469,  -469,  -469,
     -47,  -469,  -469,  -469,  -469,  -469,   -51,  -469,  -469,  -469,
    -140,  -469,  -469,  -469,  -135,  -469,   176,  -469,  -469,  -469,
    -469,  -469,  -469,  -469,  -469,  -469,  -469,  -163,  -469,  -469,
    -469,  -158,   208,  -469,  -469,  -469,  -469,  -469,  -469,  -469,
    -469,  -165,  -469,  -469,  -469,  -151,  -469,   198,   -48,  -469,
    -295,  -469,  -294,  -469,  -469,  -469,  -469,  -469,  -469,  -469,
    -469,  -469,  -469,  -469,  -469,  -469,  -469,  -469,  -469,  -469,
    -469,  -469,  -469,  -469,  -469,  -469,  -469,  -469,    40,  -469,
    -469,  -469,  -469,  -469,  -469,  -469,  -146,  -469,  -469,  -469,
    -469,  -469,  -469,  -469,  -469,    61,   174,  -469,  -469,  -469,
    -469,  -469,  -469,  -469,  -469,  -469,  -469,  -469,  -469,  -469,
    -469,  -469,  -469,  -469,  -469,  -469,  -469,  -469,  -469,  -469,
    -469,  -469,  -469,  -469,  -469,  -469,  -469,   -90,  -469,  -469,
    -469,  -213,  -469,  -469,  -224,  -469,  -469,  -469,  -469,  -469,
    -469,  -231,  -469,  -469,  -237,  -469
  };

  const short int
  Dhcp4Parser::yydefgoto_[] =
  {
      -1,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    32,    33,    34,    57,   517,    72,    73,
      35,    56,    69,    70,   497,   632,   694,   695,   106,    37,
      58,    80,    81,    82,   281,    39,    59,   107,   108,   109,
     110,   111,   112,   113,   114,   115,   288,   131,   132,    41,
      60,   133,   310,   134,   311,   500,   116,   292,   117,   293,
     568,   569,   570,   650,   751,   571,   651,   572,   652,   573,
     653,   574,   211,   346,   576,   577,   578,   579,   580,   659,
     581,   660,   118,   301,   599,   600,   601,   602,   603,   604,
     119,   303,   608,   609,   610,   677,    53,    66,   241,   242,
     243,   358,   244,   359,   120,   304,   617,   618,   619,   620,
     621,   622,   623,   624,   121,   298,   584,   585,   586,   664,
      43,    61,   154,   155,   156,   319,   157,   315,   158,   316,
     159,   317,   160,   320,   161,   321,   162,   325,   163,   324,
     164,   165,   122,   299,   588,   589,   590,   667,    49,    64,
     212,   213,   214,   215,   216,   217,   218,   345,   219,   349,
     220,   348,   221,   222,   350,   223,   123,   300,   592,   593,
     594,   670,    51,    65,   230,   231,   232,   233,   234,   354,
     235,   236,   237,   167,   318,   636,   637,   638,   697,    45,
      62,   175,   176,   177,   330,   178,   331,   168,   326,   640,
     641,   642,   700,    47,    63,   190,   191,   192,   124,   291,
     194,   334,   195,   335,   196,   342,   197,   337,   198,   338,
     199,   340,   200,   339,   201,   341,   202,   336,   170,   327,
     644,   703,   125,   302,   606,   314,   417,   418,   419,   420,
     421,   501,   126,   127,   306,   627,   628,   629,   688,   630,
     689,   128,   307,    55,    67,   260,   261,   262,   263,   363,
     264,   364,   265,   266,   366,   267,   268,   269,   369,   540,
     270,   370,   271,   272,   273,   274,   374,   547,   275,   375,
      83,   283,    84,   284,    85,   282,   552,   553,   554,   646,
     768,   769,   770,   778,   779,   780,   781,   786,   782,   784,
     796,   797,   798,   802,   803,   805
  };

  const unsigned short int
  Dhcp4Parser::yytable_[] =
  {
      79,   150,   227,   149,   173,   188,   210,   226,   240,   259,
     166,   174,   189,   169,    68,   193,   228,   151,   229,   415,
     416,   152,   153,   605,    25,   135,    26,    74,    27,   286,
     538,    98,   129,   130,   287,    88,    89,   135,   498,   499,
      86,   171,   172,   238,   239,    87,    88,    89,   308,   312,
      90,    91,    71,   309,   313,   328,    92,    93,    94,   332,
     329,   136,   137,   138,   333,    98,    24,    92,    93,    94,
      95,    96,   203,   277,   139,    97,    98,   140,   141,   142,
     143,   144,   145,    89,   179,   180,   146,   147,    36,    89,
     179,   180,    38,   148,    99,   100,    78,   204,   146,   205,
     206,    40,   207,   208,   209,   204,   101,   673,   675,   102,
     674,   676,    98,   204,   360,    78,   103,   104,    98,   361,
     105,   539,   204,   224,   205,   206,   225,   771,   376,    75,
     772,   278,   410,   377,   308,    76,    77,   181,   276,   645,
     280,   182,   183,   184,   185,   186,    42,   187,    78,    78,
      28,    29,    30,    31,   647,   799,   556,    44,   800,   648,
      78,   557,   558,   559,   560,   561,   562,   563,   564,   565,
     566,   773,    46,   774,   775,   542,   543,   544,   545,    48,
      78,   204,   611,   612,   613,   614,   615,   616,    78,   312,
     661,    50,   661,   686,   649,   662,    78,   663,   687,   690,
      52,   546,    78,   279,   691,    78,    54,   726,   415,   416,
     245,   246,   247,   248,   249,   250,   251,   252,   253,   254,
     255,   256,   257,   258,   376,   328,   360,   332,    79,   692,
     757,   760,   764,   238,   239,   378,   379,     1,     2,     3,
       4,     5,     6,     7,     8,     9,    10,    11,   787,    78,
     806,   412,   285,   788,   289,   807,   411,   290,   595,   596,
     597,   598,   294,   413,    78,   295,   414,   296,   150,   297,
     149,   625,   626,   305,   173,   322,   323,   166,   343,   347,
     169,   174,   344,   353,   151,   351,   188,   355,   152,   153,
     352,   357,   356,   189,   227,   210,   193,   362,   365,   226,
     747,   748,   749,   750,   367,   368,   371,   372,   228,   373,
     229,   380,   381,   382,   383,   384,   386,   387,   259,   388,
     389,   390,   391,   392,   393,   396,   394,   397,   398,   395,
     399,   400,   401,   402,   403,   404,   405,   407,   408,   422,
     423,   481,   482,   424,   425,   426,   427,   428,   429,   430,
     431,   432,   433,   434,   436,   437,   439,   440,   441,   442,
     443,   444,   445,   446,   447,   449,   450,   451,   452,   453,
     454,   455,   457,   458,   460,   461,   463,   464,   465,   467,
     470,   466,   471,   468,   469,   475,   476,   478,   472,   473,
     474,   479,   480,   483,   485,   484,   486,   487,   488,   489,
     490,   491,   492,   541,   504,   493,   494,   495,   496,   502,
     503,   507,   514,   513,   633,   654,   505,   506,   508,   534,
     509,   510,   575,   575,    26,   583,   511,   567,   567,   512,
     515,   587,   591,   607,   635,   518,   549,   259,   519,   639,
     412,   655,   656,   657,   521,   411,   522,   658,   665,   666,
     523,   524,   413,   525,   668,   414,   526,   669,   671,   672,
     746,   527,   679,   678,   643,   680,   681,   682,   528,   529,
     683,   684,   685,   699,   793,   530,   531,   698,   701,   702,
     739,   704,   705,   707,   708,   709,   710,   716,   717,   736,
     737,   740,   516,   551,   532,   745,   385,   758,   533,   767,
     535,   759,   765,   536,   785,   789,   791,   808,   537,   520,
     548,   795,   550,   406,   555,   409,   718,   725,   582,   728,
     727,   693,   696,   462,   735,   720,   719,   722,   435,   801,
     721,   456,   724,   459,   711,   723,   742,   744,   712,   741,
     438,   713,   448,   634,   738,   715,   714,   729,   730,   743,
     477,   731,   732,   733,   734,   790,   631,   706,   783,   752,
     753,   754,   755,   792,   756,   761,   762,   763,   804,   809,
       0,   766,   794,     0,     0,   810,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   575,     0,
       0,     0,     0,   567,   150,     0,   149,   227,     0,   210,
       0,     0,   226,   166,     0,     0,   169,     0,     0,   240,
     151,   228,     0,   229,   152,   153,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   173,
       0,     0,   188,     0,     0,     0,   174,     0,     0,   189,
       0,     0,   193,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   777,     0,     0,
       0,     0,   776,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   777,     0,     0,     0,     0,   776
  };

  const short int
  Dhcp4Parser::yycheck_[] =
  {
      58,    61,    65,    61,    62,    63,    64,    65,    66,    67,
      61,    62,    63,    61,    56,    63,    65,    61,    65,   314,
     314,    61,    61,   491,     5,     7,     7,    10,     9,     3,
      15,    47,    12,    13,     8,    17,    18,     7,    14,    15,
      11,    57,    58,    78,    79,    16,    17,    18,     3,     3,
      21,    22,   131,     8,     8,     3,    38,    39,    40,     3,
       8,    43,    44,    45,     8,    47,     0,    38,    39,    40,
      41,    42,    23,     3,    56,    46,    47,    59,    60,    61,
      62,    63,    64,    18,    19,    20,    68,    69,     7,    18,
      19,    20,     7,    75,    65,    66,   131,    48,    68,    50,
      51,     7,    53,    54,    55,    48,    77,     3,     3,    80,
       6,     6,    47,    48,     3,   131,    87,    88,    47,     8,
      91,   106,    48,    49,    50,    51,    52,     3,     3,   112,
       6,     4,    67,     8,     3,   118,   119,    66,     6,     8,
       3,    70,    71,    72,    73,    74,     7,    76,   131,   131,
     131,   132,   133,   134,     3,     3,    23,     7,     6,     8,
     131,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      37,   114,     7,   116,   117,   108,   109,   110,   111,     7,
     131,    48,    81,    82,    83,    84,    85,    86,   131,     3,
       3,     7,     3,     3,     8,     8,   131,     8,     8,     3,
       7,   134,   131,     8,     8,   131,     7,   675,   503,   503,
      92,    93,    94,    95,    96,    97,    98,    99,   100,   101,
     102,   103,   104,   105,     3,     3,     3,     3,   286,     8,
       8,     8,     8,    78,    79,   277,   278,   120,   121,   122,
     123,   124,   125,   126,   127,   128,   129,   130,     3,   131,
       3,   314,     4,     8,     4,     8,   314,     4,    70,    71,
      72,    73,     4,   314,   131,     4,   314,     4,   328,     4,
     328,    89,    90,     4,   332,     4,     4,   328,     8,     4,
     328,   332,     3,     3,   328,     4,   344,     4,   328,   328,
       8,     3,     8,   344,   357,   353,   344,     4,     4,   357,
      24,    25,    26,    27,     4,     4,     4,     4,   357,     4,
     357,   131,     4,     4,     4,     4,     4,   134,   376,   134,
       4,     4,     4,   132,   132,     4,   132,     4,     4,   132,
       4,     4,     4,     4,   132,     4,     4,     4,     4,     4,
       4,   383,   384,     4,     4,     4,     4,     4,   132,   134,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,   132,     4,     4,
       4,   134,     4,   134,     4,     4,   134,     4,     4,     4,
       4,   132,     4,   132,   132,     4,     4,     4,   134,   134,
     134,     7,     7,     7,     7,   131,     7,     5,     5,     5,
       5,     5,     5,   107,   131,     7,     7,     7,     5,     8,
       3,     5,     7,     5,     4,     4,   131,   131,   131,   461,
     131,   131,   485,   486,     7,     7,   131,   485,   486,   131,
     131,     7,     7,     7,     7,   131,   478,   495,   131,     7,
     503,     4,     4,     4,   131,   503,   131,     4,     6,     3,
     131,   131,   503,   131,     6,   503,   131,     3,     6,     3,
       5,   131,     3,     6,    76,     4,     4,     4,   131,   131,
       4,     4,     4,     3,     5,   131,   131,     6,     6,     3,
       6,     8,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     3,   437,   113,   131,     4,   286,     8,   131,     7,
     131,     8,     8,   131,     4,     4,     4,     4,   131,   441,
     131,     7,   479,   308,   483,   312,   661,   673,   486,   679,
     677,   131,   131,   360,   686,   666,   664,   669,   328,   115,
     667,   353,   672,   357,   132,   670,   699,   702,   134,   697,
     332,   132,   344,   503,   690,   132,   134,   132,   132,   700,
     376,   132,   132,   132,   132,   132,   495,   647,   771,   131,
     131,   131,   131,   787,   131,   131,   131,   131,   799,   806,
      -1,   131,   131,    -1,    -1,   131,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   661,    -1,
      -1,    -1,    -1,   661,   664,    -1,   664,   670,    -1,   667,
      -1,    -1,   670,   664,    -1,    -1,   664,    -1,    -1,   677,
     664,   670,    -1,   670,   664,   664,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   697,
      -1,    -1,   700,    -1,    -1,    -1,   697,    -1,    -1,   700,
      -1,    -1,   700,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   770,    -1,    -1,
      -1,    -1,   770,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   787,    -1,    -1,    -1,    -1,   787
  };

  const unsigned short int
  Dhcp4Parser::yystos_[] =
  {
       0,   120,   121,   122,   123,   124,   125,   126,   127,   128,
     129,   130,   136,   137,   138,   139,   140,   141,   142,   143,
     144,   145,   146,   147,     0,     5,     7,     9,   131,   132,
     133,   134,   148,   149,   150,   155,     7,   164,     7,   170,
       7,   184,     7,   255,     7,   324,     7,   338,     7,   283,
       7,   307,     7,   231,     7,   388,   156,   151,   165,   171,
     185,   256,   325,   339,   284,   308,   232,   389,   148,   157,
     158,   131,   153,   154,    10,   112,   118,   119,   131,   163,
     166,   167,   168,   415,   417,   419,    11,    16,    17,    18,
      21,    22,    38,    39,    40,    41,    42,    46,    47,    65,
      66,    77,    80,    87,    88,    91,   163,   172,   173,   174,
     175,   176,   177,   178,   179,   180,   191,   193,   217,   225,
     239,   249,   277,   301,   343,   367,   377,   378,   386,    12,
      13,   182,   183,   186,   188,     7,    43,    44,    45,    56,
      59,    60,    61,    62,    63,    64,    68,    69,    75,   163,
     174,   175,   176,   179,   257,   258,   259,   261,   263,   265,
     267,   269,   271,   273,   275,   276,   301,   318,   332,   343,
     363,    57,    58,   163,   301,   326,   327,   328,   330,    19,
      20,    66,    70,    71,    72,    73,    74,    76,   163,   301,
     340,   341,   342,   343,   345,   347,   349,   351,   353,   355,
     357,   359,   361,    23,    48,    50,    51,    53,    54,    55,
     163,   207,   285,   286,   287,   288,   289,   290,   291,   293,
     295,   297,   298,   300,    49,    52,   163,   207,   289,   295,
     309,   310,   311,   312,   313,   315,   316,   317,    78,    79,
     163,   233,   234,   235,   237,    92,    93,    94,    95,    96,
      97,    98,    99,   100,   101,   102,   103,   104,   105,   163,
     390,   391,   392,   393,   395,   397,   398,   400,   401,   402,
     405,   407,   408,   409,   410,   413,     6,     3,     4,     8,
       3,   169,   420,   416,   418,     4,     3,     8,   181,     4,
       4,   344,   192,   194,     4,     4,     4,     4,   250,   278,
     302,   218,   368,   226,   240,     4,   379,   387,     3,     8,
     187,   189,     3,     8,   370,   262,   264,   266,   319,   260,
     268,   270,     4,     4,   274,   272,   333,   364,     3,     8,
     329,   331,     3,     8,   346,   348,   362,   352,   354,   358,
     356,   360,   350,     8,     3,   292,   208,     4,   296,   294,
     299,     4,     8,     3,   314,     4,     8,     3,   236,   238,
       3,     8,     4,   394,   396,     4,   399,     4,     4,   403,
     406,     4,     4,     4,   411,   414,     3,     8,   148,   148,
     131,     4,     4,     4,     4,   167,     4,   134,   134,     4,
       4,     4,   132,   132,   132,   132,     4,     4,     4,     4,
       4,     4,     4,   132,     4,     4,   173,     4,     4,   183,
      67,   163,   207,   301,   343,   345,   347,   371,   372,   373,
     374,   375,     4,     4,     4,     4,     4,     4,     4,   132,
     134,     4,     4,     4,     4,   258,     4,     4,   327,     4,
       4,     4,     4,     4,     4,     4,     4,     4,   342,     4,
       4,   132,     4,     4,     4,   134,   287,     4,   134,   311,
       4,     4,   234,   134,     4,     4,   132,     4,   132,   132,
       4,     4,   134,   134,   134,     4,     4,   391,     4,     7,
       7,   148,   148,     7,   131,     7,     7,     5,     5,     5,
       5,     5,     5,     7,     7,     7,     5,   159,    14,    15,
     190,   376,     8,     3,   131,   131,   131,     5,   131,   131,
     131,   131,   131,     5,     7,   131,   150,   152,   131,   131,
     159,   131,   131,   131,   131,   131,   131,   131,   131,   131,
     131,   131,   131,   131,   148,   131,   131,   131,    15,   106,
     404,   107,   108,   109,   110,   111,   134,   412,   131,   148,
     172,   113,   421,   422,   423,   182,    23,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,   163,   195,   196,
     197,   200,   202,   204,   206,   207,   209,   210,   211,   212,
     213,   215,   195,     7,   251,   252,   253,     7,   279,   280,
     281,     7,   303,   304,   305,    70,    71,    72,    73,   219,
     220,   221,   222,   223,   224,   271,   369,     7,   227,   228,
     229,    81,    82,    83,    84,    85,    86,   241,   242,   243,
     244,   245,   246,   247,   248,    89,    90,   380,   381,   382,
     384,   390,   160,     4,   373,     7,   320,   321,   322,     7,
     334,   335,   336,    76,   365,     8,   424,     3,     8,     8,
     198,   201,   203,   205,     4,     4,     4,     4,     4,   214,
     216,     3,     8,     8,   254,     6,     3,   282,     6,     3,
     306,     6,     3,     3,     6,     3,     6,   230,     6,     3,
       4,     4,     4,     4,     4,     4,     3,     8,   383,   385,
       3,     8,     8,   131,   161,   162,   131,   323,     6,     3,
     337,     6,     3,   366,     8,     4,   422,     4,     4,     4,
       4,   132,   134,   132,   134,   132,     4,     4,   196,   257,
     253,   285,   281,   309,   305,   220,   271,   233,   229,   132,
     132,   132,   132,   132,   132,   242,     4,     4,   381,     6,
       3,   326,   322,   340,   336,     4,     5,    24,    25,    26,
      27,   199,   131,   131,   131,   131,   131,     8,     8,     8,
       8,   131,   131,   131,     8,     8,   131,     7,   425,   426,
     427,     3,     6,   114,   116,   117,   163,   207,   428,   429,
     430,   431,   433,   426,   434,     4,   432,     3,     8,     4,
     132,     4,   429,     5,   131,     7,   435,   436,   437,     3,
       6,   115,   438,   439,   436,   440,     3,     8,     4,   439,
     131
  };

  const unsigned short int
  Dhcp4Parser::yyr1_[] =
  {
       0,   135,   137,   136,   138,   136,   139,   136,   140,   136,
     141,   136,   142,   136,   143,   136,   144,   136,   145,   136,
     146,   136,   147,   136,   148,   148,   148,   148,   148,   148,
     148,   149,   151,   150,   152,   153,   153,   154,   154,   156,
     155,   157,   157,   158,   158,   160,   159,   161,   161,   162,
     162,   163,   165,   164,   166,   166,   167,   167,   167,   167,
     167,   169,   168,   171,   170,   172,   172,   173,   173,   173,
     173,   173,   173,   173,   173,   173,   173,   173,   173,   173,
     173,   173,   173,   173,   173,   173,   173,   173,   174,   175,
     176,   177,   178,   179,   181,   180,   182,   182,   183,   183,
     185,   184,   187,   186,   189,   188,   190,   190,   192,   191,
     194,   193,   195,   195,   196,   196,   196,   196,   196,   196,
     196,   196,   196,   196,   196,   196,   196,   198,   197,   199,
     199,   199,   199,   201,   200,   203,   202,   205,   204,   206,
     208,   207,   209,   210,   211,   212,   214,   213,   216,   215,
     218,   217,   219,   219,   220,   220,   220,   220,   221,   222,
     223,   224,   226,   225,   227,   227,   228,   228,   230,   229,
     232,   231,   233,   233,   233,   234,   234,   236,   235,   238,
     237,   240,   239,   241,   241,   242,   242,   242,   242,   242,
     242,   243,   244,   245,   246,   247,   248,   250,   249,   251,
     251,   252,   252,   254,   253,   256,   255,   257,   257,   258,
     258,   258,   258,   258,   258,   258,   258,   258,   258,   258,
     258,   258,   258,   258,   258,   258,   258,   258,   258,   260,
     259,   262,   261,   264,   263,   266,   265,   268,   267,   270,
     269,   272,   271,   274,   273,   275,   276,   278,   277,   279,
     279,   280,   280,   282,   281,   284,   283,   285,   285,   286,
     286,   287,   287,   287,   287,   287,   287,   287,   287,   288,
     289,   290,   292,   291,   294,   293,   296,   295,   297,   299,
     298,   300,   302,   301,   303,   303,   304,   304,   306,   305,
     308,   307,   309,   309,   310,   310,   311,   311,   311,   311,
     311,   311,   312,   314,   313,   315,   316,   317,   319,   318,
     320,   320,   321,   321,   323,   322,   325,   324,   326,   326,
     327,   327,   327,   327,   329,   328,   331,   330,   333,   332,
     334,   334,   335,   335,   337,   336,   339,   338,   340,   340,
     341,   341,   342,   342,   342,   342,   342,   342,   342,   342,
     342,   342,   342,   342,   344,   343,   346,   345,   348,   347,
     350,   349,   352,   351,   354,   353,   356,   355,   358,   357,
     360,   359,   362,   361,   364,   363,   366,   365,   368,   367,
     369,   369,   370,   271,   371,   371,   372,   372,   373,   373,
     373,   373,   373,   373,   373,   374,   376,   375,   377,   379,
     378,   380,   380,   381,   381,   383,   382,   385,   384,   387,
     386,   389,   388,   390,   390,   391,   391,   391,   391,   391,
     391,   391,   391,   391,   391,   391,   391,   391,   391,   391,
     392,   394,   393,   396,   395,   397,   399,   398,   400,   401,
     403,   402,   404,   404,   406,   405,   407,   408,   409,   411,
     410,   412,   412,   412,   412,   412,   414,   413,   416,   415,
     418,   417,   420,   419,   421,   421,   422,   424,   423,   425,
     425,   427,   426,   428,   428,   429,   429,   429,   429,   429,
     430,   432,   431,   434,   433,   435,   435,   437,   436,   438,
     438,   440,   439
  };

  const unsigned char
  Dhcp4Parser::yyr2_[] =
  {
       0,     2,     0,     3,     0,     3,     0,     3,     0,     3,
       0,     3,     0,     3,     0,     3,     0,     3,     0,     3,
       0,     3,     0,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     0,     4,     1,     0,     1,     3,     5,     0,
       4,     0,     1,     1,     3,     0,     4,     0,     1,     1,
       3,     2,     0,     4,     1,     3,     1,     1,     1,     1,
       1,     0,     6,     0,     4,     1,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     3,     3,
       3,     3,     3,     3,     0,     6,     1,     3,     1,     1,
       0,     4,     0,     4,     0,     4,     1,     1,     0,     6,
       0,     6,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     0,     4,     1,
       1,     1,     1,     0,     4,     0,     4,     0,     4,     3,
       0,     4,     3,     3,     3,     3,     0,     4,     0,     4,
       0,     6,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     0,     6,     0,     1,     1,     3,     0,     4,
       0,     4,     1,     3,     1,     1,     1,     0,     4,     0,
       4,     0,     6,     1,     3,     1,     1,     1,     1,     1,
       1,     3,     3,     3,     3,     3,     3,     0,     6,     0,
       1,     1,     3,     0,     4,     0,     4,     1,     3,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     4,     3,     3,     0,     6,     0,
       1,     1,     3,     0,     4,     0,     4,     0,     1,     1,
       3,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       3,     1,     0,     4,     0,     4,     0,     4,     1,     0,
       4,     3,     0,     6,     0,     1,     1,     3,     0,     4,
       0,     4,     0,     1,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     0,     4,     1,     1,     3,     0,     6,
       0,     1,     1,     3,     0,     4,     0,     4,     1,     3,
       1,     1,     1,     1,     0,     4,     0,     4,     0,     6,
       0,     1,     1,     3,     0,     4,     0,     4,     0,     1,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     0,     4,     0,     4,     0,     4,
       0,     4,     0,     4,     0,     4,     0,     4,     0,     4,
       0,     4,     0,     4,     0,     6,     0,     4,     0,     6,
       1,     3,     0,     4,     0,     1,     1,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     0,     4,     3,     0,
       6,     1,     3,     1,     1,     0,     4,     0,     4,     0,
       6,     0,     4,     1,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       3,     0,     4,     0,     4,     3,     0,     4,     3,     3,
       0,     4,     1,     1,     0,     4,     3,     3,     3,     0,
       4,     1,     1,     1,     1,     1,     0,     4,     0,     4,
       0,     4,     0,     6,     1,     3,     1,     0,     6,     1,
       3,     0,     4,     1,     3,     1,     1,     1,     1,     1,
       3,     0,     4,     0,     6,     1,     3,     0,     4,     1,
       3,     0,     4
  };



  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a yyntokens_, nonterminals.
  const char*
  const Dhcp4Parser::yytname_[] =
  {
  "\"end of file\"", "error", "$undefined", "\",\"", "\":\"", "\"[\"",
  "\"]\"", "\"{\"", "\"}\"", "\"null\"", "\"Dhcp4\"",
  "\"interfaces-config\"", "\"interfaces\"", "\"dhcp-socket-type\"",
  "\"raw\"", "\"udp\"", "\"echo-client-id\"", "\"match-client-id\"",
  "\"next-server\"", "\"server-hostname\"", "\"boot-file-name\"",
  "\"lease-database\"", "\"hosts-database\"", "\"type\"", "\"memfile\"",
  "\"mysql\"", "\"postgresql\"", "\"cql\"", "\"user\"", "\"password\"",
  "\"host\"", "\"port\"", "\"persist\"", "\"lfc-interval\"",
  "\"readonly\"", "\"connect-timeout\"", "\"contact-points\"",
  "\"keyspace\"", "\"valid-lifetime\"", "\"renew-timer\"",
  "\"rebind-timer\"", "\"decline-probation-period\"", "\"subnet4\"",
  "\"4o6-interface\"", "\"4o6-interface-id\"", "\"4o6-subnet\"",
  "\"option-def\"", "\"option-data\"", "\"name\"", "\"data\"", "\"code\"",
  "\"space\"", "\"csv-format\"", "\"record-types\"", "\"encapsulate\"",
  "\"array\"", "\"pools\"", "\"pool\"", "\"user-context\"", "\"subnet\"",
  "\"interface\"", "\"interface-id\"", "\"id\"", "\"rapid-commit\"",
  "\"reservation-mode\"", "\"host-reservation-identifiers\"",
  "\"client-classes\"", "\"test\"", "\"client-class\"", "\"reservations\"",
  "\"duid\"", "\"hw-address\"", "\"circuit-id\"", "\"client-id\"",
  "\"hostname\"", "\"relay\"", "\"ip-address\"", "\"hooks-libraries\"",
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
  "\"debuglevel\"", "\"severity\"", "\"Dhcp6\"", "\"DhcpDdns\"",
  "TOPLEVEL_JSON", "TOPLEVEL_DHCP4", "SUB_DHCP4", "SUB_INTERFACES4",
  "SUB_SUBNET4", "SUB_POOL4", "SUB_RESERVATION", "SUB_OPTION_DEF",
  "SUB_OPTION_DATA", "SUB_HOOKS_LIBRARY", "SUB_DHCP_DDNS",
  "\"constant string\"", "\"integer\"", "\"floating point\"",
  "\"boolean\"", "$accept", "start", "$@1", "$@2", "$@3", "$@4", "$@5",
  "$@6", "$@7", "$@8", "$@9", "$@10", "$@11", "value", "sub_json", "map2",
  "$@12", "map_value", "map_content", "not_empty_map", "list_generic",
  "$@13", "list_content", "not_empty_list", "list_strings", "$@14",
  "list_strings_content", "not_empty_list_strings", "unknown_map_entry",
  "syntax_map", "$@15", "global_objects", "global_object", "dhcp4_object",
  "$@16", "sub_dhcp4", "$@17", "global_params", "global_param",
  "valid_lifetime", "renew_timer", "rebind_timer",
  "decline_probation_period", "echo_client_id", "match_client_id",
  "interfaces_config", "$@18", "interfaces_config_params",
  "interfaces_config_param", "sub_interfaces4", "$@19", "interfaces_list",
  "$@20", "dhcp_socket_type", "$@21", "socket_type", "lease_database",
  "$@22", "hosts_database", "$@23", "database_map_params",
  "database_map_param", "database_type", "$@24", "db_type", "user", "$@25",
  "password", "$@26", "host", "$@27", "port", "name", "$@28", "persist",
  "lfc_interval", "readonly", "connect_timeout", "contact_points", "$@29",
  "keyspace", "$@30", "host_reservation_identifiers", "$@31",
  "host_reservation_identifiers_list", "host_reservation_identifier",
  "duid_id", "hw_address_id", "circuit_id", "client_id", "hooks_libraries",
  "$@32", "hooks_libraries_list", "not_empty_hooks_libraries_list",
  "hooks_library", "$@33", "sub_hooks_library", "$@34", "hooks_params",
  "hooks_param", "library", "$@35", "parameters", "$@36",
  "expired_leases_processing", "$@37", "expired_leases_params",
  "expired_leases_param", "reclaim_timer_wait_time",
  "flush_reclaimed_timer_wait_time", "hold_reclaimed_time",
  "max_reclaim_leases", "max_reclaim_time", "unwarned_reclaim_cycles",
  "subnet4_list", "$@38", "subnet4_list_content", "not_empty_subnet4_list",
  "subnet4", "$@39", "sub_subnet4", "$@40", "subnet4_params",
  "subnet4_param", "subnet", "$@41", "subnet_4o6_interface", "$@42",
  "subnet_4o6_interface_id", "$@43", "subnet_4o6_subnet", "$@44",
  "interface", "$@45", "interface_id", "$@46", "client_class", "$@47",
  "reservation_mode", "$@48", "id", "rapid_commit", "option_def_list",
  "$@49", "option_def_list_content", "not_empty_option_def_list",
  "option_def_entry", "$@50", "sub_option_def", "$@51",
  "option_def_params", "not_empty_option_def_params", "option_def_param",
  "option_def_name", "code", "option_def_code", "option_def_type", "$@52",
  "option_def_record_types", "$@53", "space", "$@54", "option_def_space",
  "option_def_encapsulate", "$@55", "option_def_array", "option_data_list",
  "$@56", "option_data_list_content", "not_empty_option_data_list",
  "option_data_entry", "$@57", "sub_option_data", "$@58",
  "option_data_params", "not_empty_option_data_params",
  "option_data_param", "option_data_name", "option_data_data", "$@59",
  "option_data_code", "option_data_space", "option_data_csv_format",
  "pools_list", "$@60", "pools_list_content", "not_empty_pools_list",
  "pool_list_entry", "$@61", "sub_pool4", "$@62", "pool_params",
  "pool_param", "pool_entry", "$@63", "user_context", "$@64",
  "reservations", "$@65", "reservations_list",
  "not_empty_reservations_list", "reservation", "$@66", "sub_reservation",
  "$@67", "reservation_params", "not_empty_reservation_params",
  "reservation_param", "next_server", "$@68", "server_hostname", "$@69",
  "boot_file_name", "$@70", "ip_address", "$@71", "duid", "$@72",
  "hw_address", "$@73", "client_id_value", "$@74", "circuit_id_value",
  "$@75", "hostname", "$@76", "reservation_client_classes", "$@77",
  "relay", "$@78", "relay_map", "$@79", "client_classes", "$@80",
  "client_classes_list", "$@81", "client_class_params",
  "not_empty_client_class_params", "client_class_param",
  "client_class_name", "client_class_test", "$@82", "dhcp4o6_port",
  "control_socket", "$@83", "control_socket_params",
  "control_socket_param", "control_socket_type", "$@84",
  "control_socket_name", "$@85", "dhcp_ddns", "$@86", "sub_dhcp_ddns",
  "$@87", "dhcp_ddns_params", "dhcp_ddns_param", "enable_updates",
  "qualifying_suffix", "$@88", "server_ip", "$@89", "server_port",
  "sender_ip", "$@90", "sender_port", "max_queue_size", "ncr_protocol",
  "$@91", "ncr_protocol_value", "ncr_format", "$@92",
  "always_include_fqdn", "override_no_update", "override_client_update",
  "replace_client_name", "$@93", "replace_client_name_value",
  "generated_prefix", "$@94", "dhcp6_json_object", "$@95",
  "dhcpddns_json_object", "$@96", "logging_object", "$@97",
  "logging_params", "logging_param", "loggers", "$@98", "loggers_entries",
  "logger_entry", "$@99", "logger_params", "logger_param", "debuglevel",
  "severity", "$@100", "output_options_list", "$@101",
  "output_options_list_content", "output_entry", "$@102", "output_params",
  "output_param", "$@103", YY_NULLPTR
  };

#if PARSER4_DEBUG
  const unsigned short int
  Dhcp4Parser::yyrline_[] =
  {
       0,   215,   215,   215,   216,   216,   217,   217,   218,   218,
     219,   219,   220,   220,   221,   221,   222,   222,   223,   223,
     224,   224,   225,   225,   233,   234,   235,   236,   237,   238,
     239,   242,   247,   247,   258,   261,   262,   265,   269,   276,
     276,   283,   284,   287,   291,   298,   298,   305,   306,   309,
     313,   324,   334,   334,   346,   347,   351,   352,   353,   354,
     355,   358,   358,   375,   375,   383,   384,   389,   390,   391,
     392,   393,   394,   395,   396,   397,   398,   399,   400,   401,
     402,   403,   404,   405,   406,   407,   408,   409,   412,   417,
     422,   427,   432,   437,   443,   443,   453,   454,   457,   458,
     461,   461,   469,   469,   479,   479,   486,   487,   490,   490,
     500,   500,   510,   511,   514,   515,   516,   517,   518,   519,
     520,   521,   522,   523,   524,   525,   526,   529,   529,   536,
     537,   538,   539,   542,   542,   550,   550,   558,   558,   566,
     571,   571,   579,   584,   589,   594,   599,   599,   607,   607,
     616,   616,   626,   627,   630,   631,   632,   633,   636,   641,
     646,   651,   656,   656,   666,   667,   670,   671,   674,   674,
     682,   682,   690,   691,   692,   695,   696,   699,   699,   707,
     707,   715,   715,   725,   726,   729,   730,   731,   732,   733,
     734,   737,   742,   747,   752,   757,   762,   770,   770,   783,
     784,   787,   788,   795,   795,   818,   818,   827,   828,   832,
     833,   834,   835,   836,   837,   838,   839,   840,   841,   842,
     843,   844,   845,   846,   847,   848,   849,   850,   851,   854,
     854,   862,   862,   870,   870,   878,   878,   886,   886,   894,
     894,   902,   902,   910,   910,   918,   923,   932,   932,   944,
     945,   948,   949,   954,   954,   965,   965,   975,   976,   979,
     980,   983,   984,   985,   986,   987,   988,   989,   990,   993,
     995,  1000,  1002,  1002,  1010,  1010,  1018,  1018,  1026,  1028,
    1028,  1036,  1045,  1045,  1057,  1058,  1063,  1064,  1069,  1069,
    1080,  1080,  1091,  1092,  1097,  1098,  1103,  1104,  1105,  1106,
    1107,  1108,  1111,  1113,  1113,  1121,  1123,  1125,  1133,  1133,
    1145,  1146,  1149,  1150,  1153,  1153,  1161,  1161,  1169,  1170,
    1173,  1174,  1175,  1176,  1179,  1179,  1187,  1187,  1197,  1197,
    1207,  1208,  1211,  1212,  1215,  1215,  1223,  1223,  1231,  1232,
    1235,  1236,  1240,  1241,  1242,  1243,  1244,  1245,  1246,  1247,
    1248,  1249,  1250,  1251,  1254,  1254,  1262,  1262,  1270,  1270,
    1278,  1278,  1286,  1286,  1294,  1294,  1302,  1302,  1310,  1310,
    1319,  1319,  1327,  1327,  1340,  1340,  1350,  1350,  1361,  1361,
    1371,  1372,  1375,  1375,  1383,  1384,  1387,  1388,  1391,  1392,
    1393,  1394,  1395,  1396,  1397,  1400,  1402,  1402,  1414,  1421,
    1421,  1431,  1432,  1435,  1436,  1439,  1439,  1447,  1447,  1457,
    1457,  1467,  1467,  1475,  1476,  1479,  1480,  1481,  1482,  1483,
    1484,  1485,  1486,  1487,  1488,  1489,  1490,  1491,  1492,  1493,
    1496,  1501,  1501,  1509,  1509,  1517,  1522,  1522,  1530,  1535,
    1540,  1540,  1548,  1549,  1552,  1552,  1560,  1565,  1570,  1575,
    1575,  1583,  1586,  1589,  1592,  1595,  1601,  1601,  1611,  1611,
    1618,  1618,  1630,  1630,  1643,  1644,  1648,  1652,  1652,  1664,
    1665,  1669,  1669,  1677,  1678,  1681,  1682,  1683,  1684,  1685,
    1688,  1693,  1693,  1701,  1701,  1711,  1712,  1715,  1715,  1723,
    1724,  1727,  1727
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
    *yycdebug_ << std::endl;
  }

  // Report on the debug stream that the rule \a yyrule is going to be reduced.
  void
  Dhcp4Parser::yy_reduce_print_ (int yyrule)
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
#endif // PARSER4_DEBUG


#line 14 "dhcp4_parser.yy" // lalr1.cc:1167
} } // isc::dhcp
#line 4041 "dhcp4_parser.cc" // lalr1.cc:1167
#line 1735 "dhcp4_parser.yy" // lalr1.cc:1168


void
isc::dhcp::Dhcp4Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
