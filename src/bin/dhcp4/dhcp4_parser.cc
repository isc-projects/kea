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
      case 152: // value
      case 156: // map_value
      case 194: // socket_type
      case 203: // db_type
      case 411: // ncr_protocol_value
      case 419: // replace_client_name_value
        value.move< ElementPtr > (that.value);
        break;

      case 138: // "boolean"
        value.move< bool > (that.value);
        break;

      case 137: // "floating point"
        value.move< double > (that.value);
        break;

      case 136: // "integer"
        value.move< int64_t > (that.value);
        break;

      case 135: // "constant string"
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
      case 152: // value
      case 156: // map_value
      case 194: // socket_type
      case 203: // db_type
      case 411: // ncr_protocol_value
      case 419: // replace_client_name_value
        value.copy< ElementPtr > (that.value);
        break;

      case 138: // "boolean"
        value.copy< bool > (that.value);
        break;

      case 137: // "floating point"
        value.copy< double > (that.value);
        break;

      case 136: // "integer"
        value.copy< int64_t > (that.value);
        break;

      case 135: // "constant string"
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
            case 135: // "constant string"

#line 210 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< std::string > (); }
#line 362 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 136: // "integer"

#line 210 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< int64_t > (); }
#line 369 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 137: // "floating point"

#line 210 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< double > (); }
#line 376 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 138: // "boolean"

#line 210 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< bool > (); }
#line 383 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 152: // value

#line 210 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 390 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 156: // map_value

#line 210 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 397 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 194: // socket_type

#line 210 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 404 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 203: // db_type

#line 210 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 411 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 411: // ncr_protocol_value

#line 210 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 418 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 419: // replace_client_name_value

#line 210 "dhcp4_parser.yy" // lalr1.cc:636
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
      case 152: // value
      case 156: // map_value
      case 194: // socket_type
      case 203: // db_type
      case 411: // ncr_protocol_value
      case 419: // replace_client_name_value
        yylhs.value.build< ElementPtr > ();
        break;

      case 138: // "boolean"
        yylhs.value.build< bool > ();
        break;

      case 137: // "floating point"
        yylhs.value.build< double > ();
        break;

      case 136: // "integer"
        yylhs.value.build< int64_t > ();
        break;

      case 135: // "constant string"
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
#line 219 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.NO_KEYWORD; }
#line 670 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 4:
#line 220 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.CONFIG; }
#line 676 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 6:
#line 221 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.DHCP4; }
#line 682 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 8:
#line 222 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.INTERFACES_CONFIG; }
#line 688 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 10:
#line 223 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.SUBNET4; }
#line 694 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 12:
#line 224 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.POOLS; }
#line 700 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 14:
#line 225 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.RESERVATIONS; }
#line 706 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 16:
#line 226 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.OPTION_DEF; }
#line 712 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 18:
#line 227 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.OPTION_DATA; }
#line 718 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 20:
#line 228 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.HOOKS_LIBRARIES; }
#line 724 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 22:
#line 229 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.DHCP_DDNS; }
#line 730 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 24:
#line 237 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 736 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 25:
#line 238 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as< double > (), ctx.loc2pos(yystack_[0].location))); }
#line 742 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 26:
#line 239 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 748 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 27:
#line 240 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 754 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 28:
#line 241 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 760 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 29:
#line 242 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 766 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 30:
#line 243 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 772 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 31:
#line 246 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as< ElementPtr > ());
}
#line 781 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 32:
#line 251 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 792 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 33:
#line 256 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 802 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 34:
#line 262 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 808 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 37:
#line 269 "dhcp4_parser.yy" // lalr1.cc:859
    {
                  // map containing a single entry
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 817 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 38:
#line 273 "dhcp4_parser.yy" // lalr1.cc:859
    {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 827 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 39:
#line 280 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 836 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 40:
#line 283 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // list parsing complete. Put any sanity checking here
}
#line 844 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 43:
#line 291 "dhcp4_parser.yy" // lalr1.cc:859
    {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 853 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 44:
#line 295 "dhcp4_parser.yy" // lalr1.cc:859
    {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 862 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 45:
#line 302 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // List parsing about to start
}
#line 870 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 46:
#line 304 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // list parsing complete. Put any sanity checking here
    //ctx.stack_.pop_back();
}
#line 879 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 49:
#line 313 "dhcp4_parser.yy" // lalr1.cc:859
    {
                          ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 888 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 50:
#line 317 "dhcp4_parser.yy" // lalr1.cc:859
    {
                          ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 897 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 51:
#line 328 "dhcp4_parser.yy" // lalr1.cc:859
    {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as< std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 908 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 52:
#line 338 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 919 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 53:
#line 343 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 929 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 61:
#line 362 "dhcp4_parser.yy" // lalr1.cc:859
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
#line 369 "dhcp4_parser.yy" // lalr1.cc:859
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
#line 379 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the Dhcp4 map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 964 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 64:
#line 383 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 972 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 88:
#line 416 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 981 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 89:
#line 421 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 990 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 90:
#line 426 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 999 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 91:
#line 431 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr dpp(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 1008 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 92:
#line 436 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr echo(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("echo-client-id", echo);
}
#line 1017 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 93:
#line 441 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr match(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("match-client-id", match);
}
#line 1026 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 94:
#line 447 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces-config", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.INTERFACES_CONFIG);
}
#line 1037 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 95:
#line 452 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1046 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 100:
#line 465 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1056 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 101:
#line 469 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1064 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 102:
#line 473 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1075 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 103:
#line 478 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1084 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 104:
#line 483 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.DHCP_SOCKET_TYPE);
}
#line 1092 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 105:
#line 485 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("dhcp-socket-type", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1101 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 106:
#line 490 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("raw", ctx.loc2pos(yystack_[0].location))); }
#line 1107 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 107:
#line 491 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("udp", ctx.loc2pos(yystack_[0].location))); }
#line 1113 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 108:
#line 494 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lease-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.LEASE_DATABASE);
}
#line 1124 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 109:
#line 499 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1133 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 110:
#line 504 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1144 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 111:
#line 509 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1153 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 127:
#line 533 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.DATABASE_TYPE);
}
#line 1161 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 128:
#line 535 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("type", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1170 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 129:
#line 540 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("memfile", ctx.loc2pos(yystack_[0].location))); }
#line 1176 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 130:
#line 541 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("mysql", ctx.loc2pos(yystack_[0].location))); }
#line 1182 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 131:
#line 542 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("postgresql", ctx.loc2pos(yystack_[0].location))); }
#line 1188 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 132:
#line 543 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("cql", ctx.loc2pos(yystack_[0].location))); }
#line 1194 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 133:
#line 546 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1202 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 134:
#line 548 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr user(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1212 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 135:
#line 554 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1220 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 136:
#line 556 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr pwd(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 1230 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 137:
#line 562 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1238 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 138:
#line 564 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr h(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 1248 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 139:
#line 570 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr p(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", p);
}
#line 1257 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 140:
#line 575 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1265 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 141:
#line 577 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1275 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 142:
#line 583 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 1284 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 143:
#line 588 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 1293 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 144:
#line 593 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 1302 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 145:
#line 598 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("connect-timeout", n);
}
#line 1311 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 146:
#line 603 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1319 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 147:
#line 605 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr cp(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("contact-points", cp);
    ctx.leave();
}
#line 1329 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 148:
#line 611 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1337 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 149:
#line 613 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr ks(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("keyspace", ks);
    ctx.leave();
}
#line 1347 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 150:
#line 620 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 1358 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 151:
#line 625 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1367 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 159:
#line 641 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1376 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 160:
#line 646 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 1385 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 161:
#line 651 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr circuit(new StringElement("circuit-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(circuit);
}
#line 1394 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 162:
#line 656 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr client(new StringElement("client-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(client);
}
#line 1403 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 163:
#line 661 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr flex_id(new StringElement("flex-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(flex_id);
}
#line 1412 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 164:
#line 666 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 1423 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 165:
#line 671 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1432 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 170:
#line 684 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1442 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 171:
#line 688 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1450 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 172:
#line 692 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1460 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 173:
#line 696 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1468 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 179:
#line 709 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1476 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 180:
#line 711 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr lib(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 1486 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 181:
#line 717 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1494 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 182:
#line 719 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1503 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 183:
#line 725 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.EXPIRED_LEASES_PROCESSING);
}
#line 1514 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 184:
#line 730 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1523 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 193:
#line 747 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 1532 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 194:
#line 752 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 1541 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 195:
#line 757 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 1550 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 196:
#line 762 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 1559 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 197:
#line 767 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 1568 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 198:
#line 772 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 1577 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 199:
#line 780 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet4", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET4);
}
#line 1588 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 200:
#line 785 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1597 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 205:
#line 805 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1607 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 206:
#line 809 "dhcp4_parser.yy" // lalr1.cc:859
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
#line 1630 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 207:
#line 828 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the subnet4 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1640 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 208:
#line 832 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1648 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 231:
#line 864 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1656 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 232:
#line 866 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr subnet(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 1666 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 233:
#line 872 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1674 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 234:
#line 874 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface", iface);
    ctx.leave();
}
#line 1684 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 235:
#line 880 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1692 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 236:
#line 882 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface-id", iface);
    ctx.leave();
}
#line 1702 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 237:
#line 888 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1710 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 238:
#line 890 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-subnet", iface);
    ctx.leave();
}
#line 1720 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 239:
#line 896 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1728 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 240:
#line 898 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 1738 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 241:
#line 904 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1746 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 242:
#line 906 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface-id", iface);
    ctx.leave();
}
#line 1756 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 243:
#line 912 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.CLIENT_CLASS);
}
#line 1764 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 244:
#line 914 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr cls(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 1774 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 245:
#line 920 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1782 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 246:
#line 922 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr rm(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservation-mode", rm);
    ctx.leave();
}
#line 1792 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 247:
#line 928 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr id(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 1801 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 248:
#line 933 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr rc(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rapid-commit", rc);
}
#line 1810 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 249:
#line 942 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 1821 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 250:
#line 947 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1830 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 255:
#line 964 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1840 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 256:
#line 968 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1848 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 257:
#line 975 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1858 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 258:
#line 979 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1866 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 272:
#line 1005 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr code(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 1875 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 274:
#line 1012 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1883 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 275:
#line 1014 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 1893 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 276:
#line 1020 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1901 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 277:
#line 1022 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 1911 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 278:
#line 1028 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1919 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 279:
#line 1030 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr space(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 1929 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 281:
#line 1038 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1937 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 282:
#line 1040 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr encap(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 1947 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 283:
#line 1046 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr array(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 1956 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 284:
#line 1055 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 1967 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 285:
#line 1060 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1976 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 290:
#line 1079 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1986 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 291:
#line 1083 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1994 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 292:
#line 1090 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2004 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 293:
#line 1094 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 2012 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 305:
#line 1123 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2020 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 306:
#line 1125 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr data(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 2030 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 309:
#line 1135 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr space(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", space);
}
#line 2039 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 310:
#line 1143 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 2050 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 311:
#line 1148 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2059 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 316:
#line 1163 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2069 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 317:
#line 1167 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2077 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 318:
#line 1171 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2087 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 319:
#line 1175 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 2095 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 326:
#line 1189 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2103 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 327:
#line 1191 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr pool(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 2113 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 328:
#line 1197 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2121 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 329:
#line 1199 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("user-context", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2130 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 330:
#line 1207 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 2141 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 331:
#line 1212 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2150 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 336:
#line 1225 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2160 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 337:
#line 1229 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2168 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 338:
#line 1233 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2178 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 339:
#line 1237 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 2186 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 357:
#line 1265 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2194 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 358:
#line 1267 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr next_server(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("next-server", next_server);
    ctx.leave();
}
#line 2204 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 359:
#line 1273 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2212 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 360:
#line 1275 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr srv(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-hostname", srv);
    ctx.leave();
}
#line 2222 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 361:
#line 1281 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2230 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 362:
#line 1283 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr bootfile(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("boot-file-name", bootfile);
    ctx.leave();
}
#line 2240 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 363:
#line 1289 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2248 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 364:
#line 1291 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr addr(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", addr);
    ctx.leave();
}
#line 2258 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 365:
#line 1297 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2266 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 366:
#line 1299 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr d(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 2276 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 367:
#line 1305 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2284 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 368:
#line 1307 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 2294 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 369:
#line 1313 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2302 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 370:
#line 1315 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-id", hw);
    ctx.leave();
}
#line 2312 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 371:
#line 1321 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2320 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 372:
#line 1323 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("circuit-id", hw);
    ctx.leave();
}
#line 2330 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 373:
#line 1329 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2338 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 374:
#line 1331 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flex-id", hw);
    ctx.leave();
}
#line 2348 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 375:
#line 1337 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2356 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 376:
#line 1339 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr host(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 2366 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 377:
#line 1345 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2377 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 378:
#line 1350 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2386 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 379:
#line 1358 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 2397 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 380:
#line 1363 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2406 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 381:
#line 1368 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2414 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 382:
#line 1370 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr ip(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", ip);
    ctx.leave();
}
#line 2424 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 383:
#line 1379 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 2435 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 384:
#line 1384 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2444 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 387:
#line 1393 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2454 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 388:
#line 1397 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2462 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 401:
#line 1420 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2470 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 402:
#line 1422 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr test(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 2480 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 403:
#line 1432 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 2489 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 404:
#line 1439 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 2500 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 405:
#line 1444 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2509 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 410:
#line 1457 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2517 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 411:
#line 1459 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr stype(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 2527 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 412:
#line 1465 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2535 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 413:
#line 1467 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 2545 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 414:
#line 1475 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 2556 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 415:
#line 1480 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2565 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 416:
#line 1485 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2575 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 417:
#line 1489 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 2583 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 435:
#line 1514 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 2592 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 436:
#line 1519 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2600 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 437:
#line 1521 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("qualifying-suffix", s);
    ctx.leave();
}
#line 2610 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 438:
#line 1527 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2618 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 439:
#line 1529 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 2628 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 440:
#line 1535 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 2637 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 441:
#line 1540 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2645 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 442:
#line 1542 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 2655 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 443:
#line 1548 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 2664 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 444:
#line 1553 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 2673 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 445:
#line 1558 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 2681 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 446:
#line 1560 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2690 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 447:
#line 1566 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 2696 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 448:
#line 1567 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 2702 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 449:
#line 1570 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NCR_FORMAT);
}
#line 2710 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 450:
#line 1572 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 2720 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 451:
#line 1578 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-include-fqdn", b);
}
#line 2729 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 452:
#line 1583 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-no-update", b);
}
#line 2738 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 453:
#line 1588 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-client-update", b);
}
#line 2747 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 454:
#line 1593 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 2755 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 455:
#line 1595 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("replace-client-name", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2764 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 456:
#line 1601 "dhcp4_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("when-present", ctx.loc2pos(yystack_[0].location))); 
      }
#line 2772 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 457:
#line 1604 "dhcp4_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location)));
      }
#line 2780 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 458:
#line 1607 "dhcp4_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("always", ctx.loc2pos(yystack_[0].location)));
      }
#line 2788 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 459:
#line 1610 "dhcp4_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("when-not-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 2796 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 460:
#line 1613 "dhcp4_parser.yy" // lalr1.cc:859
    {
      error(yystack_[0].location, "boolean values for the replace-client-name are "
                "no longer supported");
      }
#line 2805 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 461:
#line 1619 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2813 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 462:
#line 1621 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("generated-prefix", s);
    ctx.leave();
}
#line 2823 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 463:
#line 1629 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2831 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 464:
#line 1631 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("Dhcp6", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2840 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 465:
#line 1636 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2848 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 466:
#line 1638 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("DhcpDdns", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2857 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 467:
#line 1648 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Logging", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.LOGGING);
}
#line 2868 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 468:
#line 1653 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2877 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 472:
#line 1670 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 2888 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 473:
#line 1675 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2897 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 476:
#line 1687 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 2907 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 477:
#line 1691 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2915 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 485:
#line 1706 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr dl(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 2924 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 486:
#line 1711 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2932 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 487:
#line 1713 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 2942 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 488:
#line 1719 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 2953 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 489:
#line 1724 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2962 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 492:
#line 1733 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2972 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 493:
#line 1737 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2980 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 500:
#line 1751 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2988 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 501:
#line 1753 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 2998 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 502:
#line 1759 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr flush(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 3007 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 503:
#line 1764 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr maxsize(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 3016 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 504:
#line 1769 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr maxver(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 3025 "dhcp4_parser.cc" // lalr1.cc:859
    break;


#line 3029 "dhcp4_parser.cc" // lalr1.cc:859
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


  const short int Dhcp4Parser::yypact_ninf_ = -473;

  const signed char Dhcp4Parser::yytable_ninf_ = -1;

  const short int
  Dhcp4Parser::yypact_[] =
  {
      92,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,
    -473,  -473,    34,    19,    31,    36,   108,   116,   127,   134,
     143,   152,   175,   182,  -473,  -473,  -473,  -473,  -473,  -473,
    -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,
    -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,
    -473,  -473,  -473,  -473,  -473,  -473,    19,   -94,    17,    80,
     168,    18,    -7,   113,    16,   -19,   -35,   229,  -473,    53,
      69,    79,    84,   188,  -473,  -473,  -473,  -473,   189,  -473,
      52,  -473,  -473,  -473,  -473,  -473,  -473,   196,   202,  -473,
    -473,  -473,   210,   241,   259,   260,  -473,  -473,  -473,  -473,
    -473,  -473,  -473,   262,  -473,  -473,  -473,    65,  -473,  -473,
    -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,
    -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,
    -473,    81,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,
    -473,  -473,  -473,   263,   265,  -473,  -473,  -473,  -473,  -473,
    -473,  -473,  -473,  -473,    82,  -473,  -473,  -473,  -473,  -473,
    -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,
    -473,  -473,  -473,  -473,  -473,    85,  -473,  -473,  -473,  -473,
    -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,
    -473,   231,   268,  -473,  -473,  -473,  -473,  -473,  -473,  -473,
    -473,  -473,  -473,  -473,  -473,  -473,  -473,   269,  -473,  -473,
    -473,   270,  -473,  -473,   267,   274,  -473,  -473,  -473,  -473,
    -473,  -473,  -473,  -473,  -473,  -473,  -473,   276,  -473,  -473,
    -473,  -473,   273,   275,  -473,  -473,  -473,  -473,  -473,  -473,
    -473,  -473,  -473,   139,  -473,  -473,  -473,   280,  -473,  -473,
     281,  -473,   283,   287,  -473,  -473,   288,   289,   290,  -473,
    -473,  -473,   140,  -473,  -473,  -473,  -473,  -473,  -473,  -473,
    -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,    19,
      19,  -473,   160,   296,   297,   299,   300,  -473,    17,  -473,
     301,   169,   170,   302,   305,   306,   176,   178,   179,   180,
     313,   314,   315,   316,   332,   333,   334,   203,   336,   337,
      80,  -473,   338,   339,   168,  -473,    28,   340,   341,   342,
     343,   344,   345,   348,   217,   216,   351,   352,   353,   354,
      18,  -473,   355,   356,    -7,  -473,   357,   358,   359,   361,
     362,   363,   364,   365,   366,   367,  -473,   113,   368,   369,
     238,   371,   372,   373,   240,  -473,    16,   375,   242,  -473,
     -19,   377,   378,   172,  -473,   246,   379,   381,   250,   383,
     252,   253,   386,   387,   254,   255,   256,   391,   392,   229,
    -473,  -473,  -473,   393,   394,   395,    19,    19,  -473,   396,
    -473,  -473,   264,   397,   398,  -473,  -473,  -473,  -473,   401,
     402,   403,   404,   405,   406,   407,  -473,   408,   409,  -473,
     412,   245,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,
     390,   410,  -473,  -473,  -473,   277,   284,   285,   413,   286,
     293,   295,  -473,  -473,   298,   303,   417,   416,  -473,   304,
     418,  -473,   307,   308,   412,   310,   312,   317,   318,   319,
     320,   322,  -473,   323,   325,  -473,   326,   327,   328,  -473,
    -473,   329,  -473,  -473,   330,    19,  -473,  -473,   331,   335,
    -473,   346,  -473,  -473,    22,   292,  -473,  -473,  -473,    26,
     347,  -473,    19,    80,   321,  -473,  -473,   168,  -473,    76,
      76,   427,   429,   430,   126,    35,   433,    91,   171,   229,
    -473,  -473,  -473,  -473,  -473,   420,  -473,    28,  -473,  -473,
    -473,   441,  -473,  -473,  -473,  -473,  -473,   443,   374,  -473,
    -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,
    -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,
    -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,
    -473,  -473,  -473,  -473,  -473,   141,  -473,   159,  -473,  -473,
     162,  -473,  -473,  -473,  -473,   463,   464,   465,   467,   468,
    -473,  -473,  -473,   163,  -473,  -473,  -473,  -473,  -473,  -473,
    -473,  -473,  -473,  -473,  -473,  -473,  -473,   199,  -473,   469,
     470,  -473,  -473,   471,   473,  -473,  -473,   472,   476,  -473,
    -473,  -473,  -473,  -473,  -473,   111,  -473,  -473,  -473,  -473,
    -473,  -473,  -473,   235,  -473,   474,   480,  -473,   481,   482,
     483,   484,   485,   486,   200,  -473,  -473,  -473,  -473,  -473,
    -473,  -473,  -473,  -473,   201,  -473,  -473,  -473,   224,   349,
     360,  -473,  -473,   487,   488,  -473,  -473,   490,   489,  -473,
    -473,   466,  -473,   493,   321,  -473,  -473,   494,   495,   496,
     497,   370,   376,   380,   382,   385,   498,   499,    76,  -473,
    -473,    18,  -473,   427,    16,  -473,   429,   -19,  -473,   430,
     126,  -473,    35,  -473,   -35,  -473,   433,   388,   389,   399,
     400,   411,   414,    91,  -473,   500,   501,   171,  -473,  -473,
    -473,   502,   491,  -473,    -7,  -473,   441,   113,  -473,   443,
     503,  -473,   504,  -473,   230,   384,   419,   421,  -473,  -473,
    -473,  -473,  -473,   422,   423,  -473,   225,  -473,   505,  -473,
     507,  -473,  -473,  -473,   226,  -473,  -473,  -473,  -473,  -473,
    -473,  -473,  -473,   424,   425,  -473,  -473,   426,   228,  -473,
     509,  -473,   428,   511,  -473,  -473,  -473,  -473,  -473,  -473,
    -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,
    -473,  -473,  -473,  -473,  -473,   243,  -473,    77,   511,  -473,
    -473,   506,  -473,  -473,  -473,   232,  -473,  -473,  -473,  -473,
    -473,   508,   415,   518,    77,  -473,   521,  -473,   431,  -473,
     516,  -473,  -473,   244,  -473,   -67,   516,  -473,  -473,   523,
     524,   525,   234,  -473,  -473,  -473,  -473,  -473,  -473,   526,
     432,   435,   436,   -67,  -473,   434,  -473,  -473,  -473,  -473,
    -473
  };

  const unsigned short int
  Dhcp4Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     1,    39,    32,    28,    27,    24,
      25,    26,    31,     3,    29,    30,    52,     5,    63,     7,
     100,     9,   207,    11,   318,    13,   338,    15,   257,    17,
     292,    19,   172,    21,   416,    23,    41,    35,     0,     0,
       0,     0,     0,   340,   259,   294,     0,     0,    43,     0,
      42,     0,     0,    36,    61,   467,   463,   465,     0,    60,
       0,    54,    56,    58,    59,    57,    94,     0,     0,   357,
     108,   110,     0,     0,     0,     0,   199,   249,   284,   150,
     383,   164,   183,     0,   404,   414,    87,     0,    65,    67,
      68,    69,    70,    84,    85,    72,    73,    74,    75,    79,
      80,    71,    77,    78,    86,    76,    81,    82,    83,   102,
     104,     0,    96,    98,    99,   387,   233,   235,   237,   310,
     231,   239,   241,     0,     0,   245,   243,   330,   379,   230,
     211,   212,   213,   225,     0,   209,   216,   227,   228,   229,
     217,   218,   221,   223,   219,   220,   214,   215,   222,   226,
     224,   326,   328,   325,   323,     0,   320,   322,   324,   359,
     361,   377,   365,   367,   371,   369,   375,   373,   363,   356,
     352,     0,   341,   342,   353,   354,   355,   349,   344,   350,
     346,   347,   348,   351,   345,   274,   140,     0,   278,   276,
     281,     0,   270,   271,     0,   260,   261,   263,   273,   264,
     265,   266,   280,   267,   268,   269,   305,     0,   303,   304,
     307,   308,     0,   295,   296,   298,   299,   300,   301,   302,
     179,   181,   176,     0,   174,   177,   178,     0,   436,   438,
       0,   441,     0,     0,   445,   449,     0,     0,     0,   454,
     461,   434,     0,   418,   420,   421,   422,   423,   424,   425,
     426,   427,   428,   429,   430,   431,   432,   433,    40,     0,
       0,    33,     0,     0,     0,     0,     0,    51,     0,    53,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    64,     0,     0,     0,   101,   389,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   208,     0,     0,     0,   319,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   339,     0,     0,     0,
       0,     0,     0,     0,     0,   258,     0,     0,     0,   293,
       0,     0,     0,     0,   173,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     417,    44,    37,     0,     0,     0,     0,     0,    55,     0,
      92,    93,     0,     0,     0,    88,    89,    90,    91,     0,
       0,     0,     0,     0,     0,     0,   403,     0,     0,    66,
       0,     0,    97,   401,   399,   400,   395,   396,   397,   398,
       0,   390,   391,   393,   394,     0,     0,     0,     0,     0,
       0,     0,   247,   248,     0,     0,     0,     0,   210,     0,
       0,   321,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   343,     0,     0,   272,     0,     0,     0,   283,
     262,     0,   309,   297,     0,     0,   175,   435,     0,     0,
     440,     0,   443,   444,     0,     0,   451,   452,   453,     0,
       0,   419,     0,     0,     0,   464,   466,     0,   358,     0,
       0,   201,   251,   286,     0,     0,   166,     0,     0,     0,
      45,   103,   106,   107,   105,     0,   388,     0,   234,   236,
     238,   312,   232,   240,   242,   246,   244,   332,     0,   327,
      34,   329,   360,   362,   378,   366,   368,   372,   370,   376,
     374,   364,   275,   141,   279,   277,   282,   306,   180,   182,
     437,   439,   442,   447,   448,   446,   450,   456,   457,   458,
     459,   460,   455,   462,    38,     0,   472,     0,   469,   471,
       0,   127,   133,   135,   137,     0,     0,     0,     0,     0,
     146,   148,   126,     0,   112,   114,   115,   116,   117,   118,
     119,   120,   121,   122,   123,   124,   125,     0,   205,     0,
     202,   203,   255,     0,   252,   253,   290,     0,   287,   288,
     159,   160,   161,   162,   163,     0,   152,   154,   155,   156,
     157,   158,   385,     0,   170,     0,   167,   168,     0,     0,
       0,     0,     0,     0,     0,   185,   187,   188,   189,   190,
     191,   192,   410,   412,     0,   406,   408,   409,     0,    47,
       0,   392,   316,     0,   313,   314,   336,     0,   333,   334,
     381,     0,    62,     0,     0,   468,    95,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   109,
     111,     0,   200,     0,   259,   250,     0,   294,   285,     0,
       0,   151,     0,   384,     0,   165,     0,     0,     0,     0,
       0,     0,     0,     0,   184,     0,     0,     0,   405,   415,
      49,     0,    48,   402,     0,   311,     0,   340,   331,     0,
       0,   380,     0,   470,     0,     0,     0,     0,   139,   142,
     143,   144,   145,     0,     0,   113,     0,   204,     0,   254,
       0,   289,   153,   386,     0,   169,   193,   194,   195,   196,
     197,   198,   186,     0,     0,   407,    46,     0,     0,   315,
       0,   335,     0,     0,   129,   130,   131,   132,   128,   134,
     136,   138,   147,   149,   206,   256,   291,   171,   411,   413,
      50,   317,   337,   382,   476,     0,   474,     0,     0,   473,
     488,     0,   486,   484,   480,     0,   478,   482,   483,   481,
     475,     0,     0,     0,     0,   477,     0,   485,     0,   479,
       0,   487,   492,     0,   490,     0,     0,   489,   500,     0,
       0,     0,     0,   494,   496,   497,   498,   499,   491,     0,
       0,     0,     0,     0,   493,     0,   502,   503,   504,   495,
     501
  };

  const short int
  Dhcp4Parser::yypgoto_[] =
  {
    -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,
    -473,  -473,  -473,   -36,  -473,    71,  -473,  -473,  -473,  -473,
    -473,  -473,  -473,  -473,    87,  -473,  -473,  -473,   -58,  -473,
    -473,  -473,   249,  -473,  -473,  -473,  -473,    49,   223,   -60,
     -44,   -42,  -473,  -473,   -40,  -473,  -473,    47,   227,  -473,
    -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,
      48,  -129,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,
    -473,  -473,   -63,  -473,  -473,  -473,  -473,  -473,  -473,  -473,
    -473,  -473,  -473,  -473,  -473,  -140,  -473,  -473,  -473,  -473,
    -473,  -473,  -473,  -473,  -473,  -144,  -473,  -473,  -473,  -141,
     181,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -148,  -473,
    -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -127,
    -473,  -473,  -473,  -123,   219,  -473,  -473,  -473,  -473,  -473,
    -473,  -473,  -473,  -473,  -473,  -473,  -473,  -472,  -473,  -473,
    -473,  -473,  -473,  -473,  -473,  -473,  -473,  -124,  -473,  -473,
    -473,  -121,  -473,   206,  -473,   -49,  -473,  -473,  -473,  -473,
    -473,   -47,  -473,  -473,  -473,  -473,  -473,   -51,  -473,  -473,
    -473,  -115,  -473,  -473,  -473,  -122,  -473,   205,  -473,  -473,
    -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -139,  -473,
    -473,  -473,  -136,   239,  -473,  -473,  -473,  -473,  -473,  -473,
    -473,  -473,  -135,  -473,  -473,  -473,  -132,  -473,   233,   -48,
    -473,  -302,  -473,  -294,  -473,  -473,  -473,  -473,  -473,  -473,
    -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,
    -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,
    -473,    70,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -119,
    -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,    83,   197,
    -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,
    -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,
    -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,
     -75,  -473,  -473,  -473,  -197,  -473,  -473,  -211,  -473,  -473,
    -473,  -473,  -473,  -473,  -222,  -473,  -473,  -238,  -473,  -473,
    -473,  -473,  -473
  };

  const short int
  Dhcp4Parser::yydefgoto_[] =
  {
      -1,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    32,    33,    34,    57,   521,    72,    73,
      35,    56,    69,    70,   501,   639,   701,   702,   106,    37,
      58,    80,    81,    82,   283,    39,    59,   107,   108,   109,
     110,   111,   112,   113,   114,   115,   290,   131,   132,    41,
      60,   133,   312,   134,   313,   504,   116,   294,   117,   295,
     573,   574,   575,   657,   758,   576,   658,   577,   659,   578,
     660,   579,   213,   349,   581,   582,   583,   584,   585,   666,
     586,   667,   118,   303,   605,   606,   607,   608,   609,   610,
     611,   119,   305,   615,   616,   617,   684,    53,    66,   243,
     244,   245,   361,   246,   362,   120,   306,   624,   625,   626,
     627,   628,   629,   630,   631,   121,   300,   589,   590,   591,
     671,    43,    61,   154,   155,   156,   321,   157,   317,   158,
     318,   159,   319,   160,   322,   161,   323,   162,   327,   163,
     326,   164,   165,   122,   301,   593,   594,   595,   674,    49,
      64,   214,   215,   216,   217,   218,   219,   220,   348,   221,
     352,   222,   351,   223,   224,   353,   225,   123,   302,   597,
     598,   599,   677,    51,    65,   232,   233,   234,   235,   236,
     357,   237,   238,   239,   167,   320,   643,   644,   645,   704,
      45,    62,   175,   176,   177,   332,   178,   333,   168,   328,
     647,   648,   649,   707,    47,    63,   191,   192,   193,   124,
     293,   195,   336,   196,   337,   197,   345,   198,   339,   199,
     340,   200,   342,   201,   341,   202,   344,   203,   343,   204,
     338,   170,   329,   651,   710,   125,   304,   613,   316,   420,
     421,   422,   423,   424,   505,   126,   127,   308,   634,   635,
     636,   695,   637,   696,   128,   309,    55,    67,   262,   263,
     264,   265,   366,   266,   367,   267,   268,   369,   269,   270,
     271,   372,   545,   272,   373,   273,   274,   275,   276,   377,
     552,   277,   378,    83,   285,    84,   286,    85,   284,   557,
     558,   559,   653,   775,   776,   777,   785,   786,   787,   788,
     793,   789,   791,   803,   804,   805,   812,   813,   814,   819,
     815,   816,   817
  };

  const unsigned short int
  Dhcp4Parser::yytable_[] =
  {
      79,   150,   229,   149,   173,   189,   212,   228,   242,   261,
     166,   174,   190,   169,   418,   194,   230,   151,   231,   152,
      68,   153,   419,   612,    25,   135,    26,    74,    27,   206,
     226,   207,   208,   227,    24,    88,    89,   543,    36,   205,
      98,    71,   135,    38,   240,   241,    89,   179,   180,   808,
     171,   172,   809,   810,   811,   288,    92,    93,    94,   278,
     289,   136,   137,   138,   206,    98,   207,   208,   310,   209,
     210,   211,   279,   311,   139,    98,   206,   140,   141,   142,
     143,   144,   145,   280,   314,   330,   146,   147,   334,   315,
     331,    86,   281,   335,   148,   413,    87,    88,    89,   561,
      78,    90,    91,   146,   562,   563,   564,   565,   566,   567,
     568,   569,   570,   571,   680,    40,    78,   681,    92,    93,
      94,    95,    96,    42,   206,   206,    97,    98,    78,   544,
      75,    89,   179,   180,    44,   547,   548,   549,   550,    76,
      77,    46,   363,   379,   310,    99,   100,   364,   380,   652,
      48,    78,    78,    78,    28,    29,    30,    31,   101,    50,
      98,   102,   654,    78,   551,   314,   668,   655,   103,   104,
     656,   669,   105,   618,   619,   620,   621,   622,   623,   181,
     129,   130,    52,   182,   183,   184,   185,   186,   187,    54,
     188,   282,   780,   287,   781,   782,   600,   601,   602,   603,
     291,   604,   668,   693,   697,   418,   292,   670,   694,   698,
     733,    78,    78,   419,   296,    78,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,   379,   330,   363,
      79,   334,   699,   764,   767,   794,   771,   823,   682,   346,
     795,   683,   824,   381,   382,   297,   778,   806,    78,   779,
     807,   240,   241,   415,   754,   755,   756,   757,   414,   502,
     503,   632,   633,   298,   299,   416,   307,   324,   417,   325,
     150,   347,   149,   350,   354,   355,   173,   356,   360,   166,
     358,   359,   169,   174,   365,   368,   151,   370,   152,   189,
     153,   371,   374,   375,   376,   383,   190,   229,   212,   194,
     384,   385,   228,   386,   387,   389,   392,   390,   391,   393,
     394,   230,   395,   231,   396,   397,   398,   399,   400,   401,
     402,   261,   247,   248,   249,   250,   251,   252,   253,   254,
     255,   256,   257,   258,   259,   260,   403,   404,   405,   406,
     407,   408,   410,   411,   425,   426,   427,   428,   429,   430,
     485,   486,   431,   432,   433,   434,   435,   436,   437,   439,
     440,   442,   443,   444,    78,   445,   446,   447,   448,   449,
     450,   451,   453,   454,   455,   456,   457,   458,   459,   461,
     462,   464,   465,   468,   467,   469,   470,   471,   472,   473,
     474,   475,   476,   477,   478,   479,   480,   482,   506,   488,
     546,   483,   484,   487,   489,   490,   491,   492,   493,   494,
     495,   496,   508,   507,   497,   498,   499,   500,   511,   509,
     510,   512,   517,   518,   640,    26,   580,   580,   513,   539,
     514,   572,   572,   515,   588,   556,   592,   596,   516,   519,
     614,   261,   522,   523,   415,   525,   554,   526,   642,   414,
     646,   650,   527,   528,   529,   530,   416,   531,   532,   417,
     533,   534,   535,   536,   537,   538,   540,   661,   662,   663,
     541,   664,   665,   673,   711,   672,   676,   675,   678,   679,
     685,   542,   553,   686,   700,   687,   688,   689,   690,   691,
     692,   706,   709,   705,   747,   703,   708,   712,   714,   715,
     716,   717,   723,   724,   743,   744,   718,   752,   746,   753,
     792,   520,   796,   765,   719,   766,   720,   772,   774,   759,
     721,   722,   798,   802,   736,   737,   800,   820,   821,   822,
     825,   524,   555,   409,   560,   738,   739,   388,   587,   725,
     732,   412,   735,   734,   466,   742,   727,   740,   726,   438,
     741,   797,   729,   728,   760,   730,   761,   762,   763,   768,
     769,   770,   460,   773,   731,   463,   801,   749,   748,   830,
     826,   827,   828,   441,   751,   750,   481,   641,   745,   713,
     452,   790,   638,   799,   818,   829,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   580,     0,     0,     0,     0,
     572,   150,     0,   149,   229,     0,   212,     0,     0,   228,
     166,     0,     0,   169,     0,     0,   242,   151,   230,   152,
     231,   153,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   173,     0,     0,   189,
       0,     0,     0,   174,     0,     0,   190,     0,     0,   194,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   784,     0,     0,     0,     0,   783,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   784,     0,     0,     0,     0,   783
  };

  const short int
  Dhcp4Parser::yycheck_[] =
  {
      58,    61,    65,    61,    62,    63,    64,    65,    66,    67,
      61,    62,    63,    61,   316,    63,    65,    61,    65,    61,
      56,    61,   316,   495,     5,     7,     7,    10,     9,    48,
      49,    50,    51,    52,     0,    17,    18,    15,     7,    23,
      47,   135,     7,     7,    79,    80,    18,    19,    20,   116,
      57,    58,   119,   120,   121,     3,    38,    39,    40,     6,
       8,    43,    44,    45,    48,    47,    50,    51,     3,    53,
      54,    55,     3,     8,    56,    47,    48,    59,    60,    61,
      62,    63,    64,     4,     3,     3,    68,    69,     3,     8,
       8,    11,     8,     8,    76,    67,    16,    17,    18,    23,
     135,    21,    22,    68,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,     3,     7,   135,     6,    38,    39,
      40,    41,    42,     7,    48,    48,    46,    47,   135,   107,
     113,    18,    19,    20,     7,   109,   110,   111,   112,   122,
     123,     7,     3,     3,     3,    65,    66,     8,     8,     8,
       7,   135,   135,   135,   135,   136,   137,   138,    78,     7,
      47,    81,     3,   135,   138,     3,     3,     8,    88,    89,
       8,     8,    92,    82,    83,    84,    85,    86,    87,    66,
      12,    13,     7,    70,    71,    72,    73,    74,    75,     7,
      77,     3,   115,     4,   117,   118,    70,    71,    72,    73,
       4,    75,     3,     3,     3,   507,     4,     8,     8,     8,
     682,   135,   135,   507,     4,   135,   124,   125,   126,   127,
     128,   129,   130,   131,   132,   133,   134,     3,     3,     3,
     288,     3,     8,     8,     8,     3,     8,     3,     3,     8,
       8,     6,     8,   279,   280,     4,     3,     3,   135,     6,
       6,    79,    80,   316,    24,    25,    26,    27,   316,    14,
      15,    90,    91,     4,     4,   316,     4,     4,   316,     4,
     330,     3,   330,     4,     4,     8,   334,     3,     3,   330,
       4,     8,   330,   334,     4,     4,   330,     4,   330,   347,
     330,     4,     4,     4,     4,   135,   347,   360,   356,   347,
       4,     4,   360,     4,     4,     4,     4,   138,   138,     4,
       4,   360,   136,   360,   136,   136,   136,     4,     4,     4,
       4,   379,    93,    94,    95,    96,    97,    98,    99,   100,
     101,   102,   103,   104,   105,   106,     4,     4,     4,   136,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
     386,   387,     4,   136,   138,     4,     4,     4,     4,     4,
       4,     4,     4,     4,   135,     4,     4,     4,     4,     4,
       4,     4,     4,     4,   136,     4,     4,     4,   138,     4,
     138,     4,     4,     4,   138,     4,   136,     4,   136,   136,
       4,     4,   138,   138,   138,     4,     4,     4,     8,   135,
     108,     7,     7,     7,     7,     7,     5,     5,     5,     5,
       5,     5,   135,     3,     7,     7,     7,     5,     5,   135,
     135,   135,     5,     7,     4,     7,   489,   490,   135,   465,
     135,   489,   490,   135,     7,   114,     7,     7,   135,   135,
       7,   499,   135,   135,   507,   135,   482,   135,     7,   507,
       7,    77,   135,   135,   135,   135,   507,   135,   135,   507,
     135,   135,   135,   135,   135,   135,   135,     4,     4,     4,
     135,     4,     4,     3,     8,     6,     3,     6,     6,     3,
       6,   135,   135,     3,   135,     4,     4,     4,     4,     4,
       4,     3,     3,     6,     3,   135,     6,     4,     4,     4,
       4,     4,     4,     4,     4,     4,   136,     4,     6,     5,
       4,   440,     4,     8,   138,     8,   136,     8,     7,   135,
     138,   136,     4,     7,   136,   136,     5,     4,     4,     4,
       4,   444,   483,   310,   487,   136,   136,   288,   490,   668,
     680,   314,   686,   684,   363,   693,   673,   136,   671,   330,
     136,   136,   676,   674,   135,   677,   135,   135,   135,   135,
     135,   135,   356,   135,   679,   360,   135,   706,   704,   135,
     138,   136,   136,   334,   709,   707,   379,   507,   697,   654,
     347,   778,   499,   794,   806,   823,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   668,    -1,    -1,    -1,    -1,
     668,   671,    -1,   671,   677,    -1,   674,    -1,    -1,   677,
     671,    -1,    -1,   671,    -1,    -1,   684,   671,   677,   671,
     677,   671,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   704,    -1,    -1,   707,
      -1,    -1,    -1,   704,    -1,    -1,   707,    -1,    -1,   707,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   777,    -1,    -1,    -1,    -1,   777,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   794,    -1,    -1,    -1,    -1,   794
  };

  const unsigned short int
  Dhcp4Parser::yystos_[] =
  {
       0,   124,   125,   126,   127,   128,   129,   130,   131,   132,
     133,   134,   140,   141,   142,   143,   144,   145,   146,   147,
     148,   149,   150,   151,     0,     5,     7,     9,   135,   136,
     137,   138,   152,   153,   154,   159,     7,   168,     7,   174,
       7,   188,     7,   260,     7,   329,     7,   343,     7,   288,
       7,   312,     7,   236,     7,   395,   160,   155,   169,   175,
     189,   261,   330,   344,   289,   313,   237,   396,   152,   161,
     162,   135,   157,   158,    10,   113,   122,   123,   135,   167,
     170,   171,   172,   422,   424,   426,    11,    16,    17,    18,
      21,    22,    38,    39,    40,    41,    42,    46,    47,    65,
      66,    78,    81,    88,    89,    92,   167,   176,   177,   178,
     179,   180,   181,   182,   183,   184,   195,   197,   221,   230,
     244,   254,   282,   306,   348,   374,   384,   385,   393,    12,
      13,   186,   187,   190,   192,     7,    43,    44,    45,    56,
      59,    60,    61,    62,    63,    64,    68,    69,    76,   167,
     178,   179,   180,   183,   262,   263,   264,   266,   268,   270,
     272,   274,   276,   278,   280,   281,   306,   323,   337,   348,
     370,    57,    58,   167,   306,   331,   332,   333,   335,    19,
      20,    66,    70,    71,    72,    73,    74,    75,    77,   167,
     306,   345,   346,   347,   348,   350,   352,   354,   356,   358,
     360,   362,   364,   366,   368,    23,    48,    50,    51,    53,
      54,    55,   167,   211,   290,   291,   292,   293,   294,   295,
     296,   298,   300,   302,   303,   305,    49,    52,   167,   211,
     294,   300,   314,   315,   316,   317,   318,   320,   321,   322,
      79,    80,   167,   238,   239,   240,   242,    93,    94,    95,
      96,    97,    98,    99,   100,   101,   102,   103,   104,   105,
     106,   167,   397,   398,   399,   400,   402,   404,   405,   407,
     408,   409,   412,   414,   415,   416,   417,   420,     6,     3,
       4,     8,     3,   173,   427,   423,   425,     4,     3,     8,
     185,     4,     4,   349,   196,   198,     4,     4,     4,     4,
     255,   283,   307,   222,   375,   231,   245,     4,   386,   394,
       3,     8,   191,   193,     3,     8,   377,   267,   269,   271,
     324,   265,   273,   275,     4,     4,   279,   277,   338,   371,
       3,     8,   334,   336,     3,     8,   351,   353,   369,   357,
     359,   363,   361,   367,   365,   355,     8,     3,   297,   212,
       4,   301,   299,   304,     4,     8,     3,   319,     4,     8,
       3,   241,   243,     3,     8,     4,   401,   403,     4,   406,
       4,     4,   410,   413,     4,     4,     4,   418,   421,     3,
       8,   152,   152,   135,     4,     4,     4,     4,   171,     4,
     138,   138,     4,     4,     4,   136,   136,   136,   136,     4,
       4,     4,     4,     4,     4,     4,   136,     4,     4,   177,
       4,     4,   187,    67,   167,   211,   306,   348,   350,   352,
     378,   379,   380,   381,   382,     4,     4,     4,     4,     4,
       4,     4,   136,   138,     4,     4,     4,     4,   263,     4,
       4,   332,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,   347,     4,     4,   136,     4,     4,     4,   138,
     292,     4,   138,   316,     4,     4,   239,   138,     4,     4,
     136,     4,   136,   136,     4,     4,   138,   138,   138,     4,
       4,   398,     4,     7,     7,   152,   152,     7,   135,     7,
       7,     5,     5,     5,     5,     5,     5,     7,     7,     7,
       5,   163,    14,    15,   194,   383,     8,     3,   135,   135,
     135,     5,   135,   135,   135,   135,   135,     5,     7,   135,
     154,   156,   135,   135,   163,   135,   135,   135,   135,   135,
     135,   135,   135,   135,   135,   135,   135,   135,   135,   152,
     135,   135,   135,    15,   107,   411,   108,   109,   110,   111,
     112,   138,   419,   135,   152,   176,   114,   428,   429,   430,
     186,    23,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,   167,   199,   200,   201,   204,   206,   208,   210,
     211,   213,   214,   215,   216,   217,   219,   199,     7,   256,
     257,   258,     7,   284,   285,   286,     7,   308,   309,   310,
      70,    71,    72,    73,    75,   223,   224,   225,   226,   227,
     228,   229,   276,   376,     7,   232,   233,   234,    82,    83,
      84,    85,    86,    87,   246,   247,   248,   249,   250,   251,
     252,   253,    90,    91,   387,   388,   389,   391,   397,   164,
       4,   380,     7,   325,   326,   327,     7,   339,   340,   341,
      77,   372,     8,   431,     3,     8,     8,   202,   205,   207,
     209,     4,     4,     4,     4,     4,   218,   220,     3,     8,
       8,   259,     6,     3,   287,     6,     3,   311,     6,     3,
       3,     6,     3,     6,   235,     6,     3,     4,     4,     4,
       4,     4,     4,     3,     8,   390,   392,     3,     8,     8,
     135,   165,   166,   135,   328,     6,     3,   342,     6,     3,
     373,     8,     4,   429,     4,     4,     4,     4,   136,   138,
     136,   138,   136,     4,     4,   200,   262,   258,   290,   286,
     314,   310,   224,   276,   238,   234,   136,   136,   136,   136,
     136,   136,   247,     4,     4,   388,     6,     3,   331,   327,
     345,   341,     4,     5,    24,    25,    26,    27,   203,   135,
     135,   135,   135,   135,     8,     8,     8,     8,   135,   135,
     135,     8,     8,   135,     7,   432,   433,   434,     3,     6,
     115,   117,   118,   167,   211,   435,   436,   437,   438,   440,
     433,   441,     4,   439,     3,     8,     4,   136,     4,   436,
       5,   135,     7,   442,   443,   444,     3,     6,   116,   119,
     120,   121,   445,   446,   447,   449,   450,   451,   443,   448,
       4,     4,     4,     3,     8,     4,   138,   136,   136,   446,
     135
  };

  const unsigned short int
  Dhcp4Parser::yyr1_[] =
  {
       0,   139,   141,   140,   142,   140,   143,   140,   144,   140,
     145,   140,   146,   140,   147,   140,   148,   140,   149,   140,
     150,   140,   151,   140,   152,   152,   152,   152,   152,   152,
     152,   153,   155,   154,   156,   157,   157,   158,   158,   160,
     159,   161,   161,   162,   162,   164,   163,   165,   165,   166,
     166,   167,   169,   168,   170,   170,   171,   171,   171,   171,
     171,   173,   172,   175,   174,   176,   176,   177,   177,   177,
     177,   177,   177,   177,   177,   177,   177,   177,   177,   177,
     177,   177,   177,   177,   177,   177,   177,   177,   178,   179,
     180,   181,   182,   183,   185,   184,   186,   186,   187,   187,
     189,   188,   191,   190,   193,   192,   194,   194,   196,   195,
     198,   197,   199,   199,   200,   200,   200,   200,   200,   200,
     200,   200,   200,   200,   200,   200,   200,   202,   201,   203,
     203,   203,   203,   205,   204,   207,   206,   209,   208,   210,
     212,   211,   213,   214,   215,   216,   218,   217,   220,   219,
     222,   221,   223,   223,   224,   224,   224,   224,   224,   225,
     226,   227,   228,   229,   231,   230,   232,   232,   233,   233,
     235,   234,   237,   236,   238,   238,   238,   239,   239,   241,
     240,   243,   242,   245,   244,   246,   246,   247,   247,   247,
     247,   247,   247,   248,   249,   250,   251,   252,   253,   255,
     254,   256,   256,   257,   257,   259,   258,   261,   260,   262,
     262,   263,   263,   263,   263,   263,   263,   263,   263,   263,
     263,   263,   263,   263,   263,   263,   263,   263,   263,   263,
     263,   265,   264,   267,   266,   269,   268,   271,   270,   273,
     272,   275,   274,   277,   276,   279,   278,   280,   281,   283,
     282,   284,   284,   285,   285,   287,   286,   289,   288,   290,
     290,   291,   291,   292,   292,   292,   292,   292,   292,   292,
     292,   293,   294,   295,   297,   296,   299,   298,   301,   300,
     302,   304,   303,   305,   307,   306,   308,   308,   309,   309,
     311,   310,   313,   312,   314,   314,   315,   315,   316,   316,
     316,   316,   316,   316,   317,   319,   318,   320,   321,   322,
     324,   323,   325,   325,   326,   326,   328,   327,   330,   329,
     331,   331,   332,   332,   332,   332,   334,   333,   336,   335,
     338,   337,   339,   339,   340,   340,   342,   341,   344,   343,
     345,   345,   346,   346,   347,   347,   347,   347,   347,   347,
     347,   347,   347,   347,   347,   347,   347,   349,   348,   351,
     350,   353,   352,   355,   354,   357,   356,   359,   358,   361,
     360,   363,   362,   365,   364,   367,   366,   369,   368,   371,
     370,   373,   372,   375,   374,   376,   376,   377,   276,   378,
     378,   379,   379,   380,   380,   380,   380,   380,   380,   380,
     381,   383,   382,   384,   386,   385,   387,   387,   388,   388,
     390,   389,   392,   391,   394,   393,   396,   395,   397,   397,
     398,   398,   398,   398,   398,   398,   398,   398,   398,   398,
     398,   398,   398,   398,   398,   399,   401,   400,   403,   402,
     404,   406,   405,   407,   408,   410,   409,   411,   411,   413,
     412,   414,   415,   416,   418,   417,   419,   419,   419,   419,
     419,   421,   420,   423,   422,   425,   424,   427,   426,   428,
     428,   429,   431,   430,   432,   432,   434,   433,   435,   435,
     436,   436,   436,   436,   436,   437,   439,   438,   441,   440,
     442,   442,   444,   443,   445,   445,   446,   446,   446,   446,
     448,   447,   449,   450,   451
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
       1,     1,     1,     1,     0,     6,     0,     1,     1,     3,
       0,     4,     0,     4,     1,     3,     1,     1,     1,     0,
       4,     0,     4,     0,     6,     1,     3,     1,     1,     1,
       1,     1,     1,     3,     3,     3,     3,     3,     3,     0,
       6,     0,     1,     1,     3,     0,     4,     0,     4,     1,
       3,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     4,     3,     3,     0,
       6,     0,     1,     1,     3,     0,     4,     0,     4,     0,
       1,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     3,     1,     0,     4,     0,     4,     0,     4,
       1,     0,     4,     3,     0,     6,     0,     1,     1,     3,
       0,     4,     0,     4,     0,     1,     1,     3,     1,     1,
       1,     1,     1,     1,     1,     0,     4,     1,     1,     3,
       0,     6,     0,     1,     1,     3,     0,     4,     0,     4,
       1,     3,     1,     1,     1,     1,     0,     4,     0,     4,
       0,     6,     0,     1,     1,     3,     0,     4,     0,     4,
       0,     1,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       6,     0,     4,     0,     6,     1,     3,     0,     4,     0,
       1,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     0,     4,     3,     0,     6,     1,     3,     1,     1,
       0,     4,     0,     4,     0,     6,     0,     4,     1,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     3,     0,     4,     0,     4,
       3,     0,     4,     3,     3,     0,     4,     1,     1,     0,
       4,     3,     3,     3,     0,     4,     1,     1,     1,     1,
       1,     0,     4,     0,     4,     0,     4,     0,     6,     1,
       3,     1,     0,     6,     1,     3,     0,     4,     1,     3,
       1,     1,     1,     1,     1,     3,     0,     4,     0,     6,
       1,     3,     0,     4,     1,     3,     1,     1,     1,     1,
       0,     4,     3,     3,     3
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
  "\"hostname\"", "\"flex-id\"", "\"relay\"", "\"ip-address\"",
  "\"hooks-libraries\"", "\"library\"", "\"parameters\"",
  "\"expired-leases-processing\"", "\"reclaim-timer-wait-time\"",
  "\"flush-reclaimed-timer-wait-time\"", "\"hold-reclaimed-time\"",
  "\"max-reclaim-leases\"", "\"max-reclaim-time\"",
  "\"unwarned-reclaim-cycles\"", "\"dhcp4o6-port\"", "\"control-socket\"",
  "\"socket-type\"", "\"socket-name\"", "\"dhcp-ddns\"",
  "\"enable-updates\"", "\"qualifying-suffix\"", "\"server-ip\"",
  "\"server-port\"", "\"sender-ip\"", "\"sender-port\"",
  "\"max-queue-size\"", "\"ncr-protocol\"", "\"ncr-format\"",
  "\"always-include-fqdn\"", "\"override-no-update\"",
  "\"override-client-update\"", "\"replace-client-name\"",
  "\"generated-prefix\"", "\"tcp\"", "\"JSON\"", "\"when-present\"",
  "\"never\"", "\"always\"", "\"when-not-present\"", "\"Logging\"",
  "\"loggers\"", "\"output_options\"", "\"output\"", "\"debuglevel\"",
  "\"severity\"", "\"flush\"", "\"maxsize\"", "\"maxver\"", "\"Dhcp6\"",
  "\"DhcpDdns\"", "TOPLEVEL_JSON", "TOPLEVEL_DHCP4", "SUB_DHCP4",
  "SUB_INTERFACES4", "SUB_SUBNET4", "SUB_POOL4", "SUB_RESERVATION",
  "SUB_OPTION_DEF", "SUB_OPTION_DATA", "SUB_HOOKS_LIBRARY",
  "SUB_DHCP_DDNS", "\"constant string\"", "\"integer\"",
  "\"floating point\"", "\"boolean\"", "$accept", "start", "$@1", "$@2",
  "$@3", "$@4", "$@5", "$@6", "$@7", "$@8", "$@9", "$@10", "$@11", "value",
  "sub_json", "map2", "$@12", "map_value", "map_content", "not_empty_map",
  "list_generic", "$@13", "list_content", "not_empty_list", "list_strings",
  "$@14", "list_strings_content", "not_empty_list_strings",
  "unknown_map_entry", "syntax_map", "$@15", "global_objects",
  "global_object", "dhcp4_object", "$@16", "sub_dhcp4", "$@17",
  "global_params", "global_param", "valid_lifetime", "renew_timer",
  "rebind_timer", "decline_probation_period", "echo_client_id",
  "match_client_id", "interfaces_config", "$@18",
  "interfaces_config_params", "interfaces_config_param", "sub_interfaces4",
  "$@19", "interfaces_list", "$@20", "dhcp_socket_type", "$@21",
  "socket_type", "lease_database", "$@22", "hosts_database", "$@23",
  "database_map_params", "database_map_param", "database_type", "$@24",
  "db_type", "user", "$@25", "password", "$@26", "host", "$@27", "port",
  "name", "$@28", "persist", "lfc_interval", "readonly", "connect_timeout",
  "contact_points", "$@29", "keyspace", "$@30",
  "host_reservation_identifiers", "$@31",
  "host_reservation_identifiers_list", "host_reservation_identifier",
  "duid_id", "hw_address_id", "circuit_id", "client_id", "flex_id",
  "hooks_libraries", "$@32", "hooks_libraries_list",
  "not_empty_hooks_libraries_list", "hooks_library", "$@33",
  "sub_hooks_library", "$@34", "hooks_params", "hooks_param", "library",
  "$@35", "parameters", "$@36", "expired_leases_processing", "$@37",
  "expired_leases_params", "expired_leases_param",
  "reclaim_timer_wait_time", "flush_reclaimed_timer_wait_time",
  "hold_reclaimed_time", "max_reclaim_leases", "max_reclaim_time",
  "unwarned_reclaim_cycles", "subnet4_list", "$@38",
  "subnet4_list_content", "not_empty_subnet4_list", "subnet4", "$@39",
  "sub_subnet4", "$@40", "subnet4_params", "subnet4_param", "subnet",
  "$@41", "subnet_4o6_interface", "$@42", "subnet_4o6_interface_id",
  "$@43", "subnet_4o6_subnet", "$@44", "interface", "$@45", "interface_id",
  "$@46", "client_class", "$@47", "reservation_mode", "$@48", "id",
  "rapid_commit", "option_def_list", "$@49", "option_def_list_content",
  "not_empty_option_def_list", "option_def_entry", "$@50",
  "sub_option_def", "$@51", "option_def_params",
  "not_empty_option_def_params", "option_def_param", "option_def_name",
  "code", "option_def_code", "option_def_type", "$@52",
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
  "$@75", "flex_id_value", "$@76", "hostname", "$@77",
  "reservation_client_classes", "$@78", "relay", "$@79", "relay_map",
  "$@80", "client_classes", "$@81", "client_classes_list", "$@82",
  "client_class_params", "not_empty_client_class_params",
  "client_class_param", "client_class_name", "client_class_test", "$@83",
  "dhcp4o6_port", "control_socket", "$@84", "control_socket_params",
  "control_socket_param", "control_socket_type", "$@85",
  "control_socket_name", "$@86", "dhcp_ddns", "$@87", "sub_dhcp_ddns",
  "$@88", "dhcp_ddns_params", "dhcp_ddns_param", "enable_updates",
  "qualifying_suffix", "$@89", "server_ip", "$@90", "server_port",
  "sender_ip", "$@91", "sender_port", "max_queue_size", "ncr_protocol",
  "$@92", "ncr_protocol_value", "ncr_format", "$@93",
  "always_include_fqdn", "override_no_update", "override_client_update",
  "replace_client_name", "$@94", "replace_client_name_value",
  "generated_prefix", "$@95", "dhcp6_json_object", "$@96",
  "dhcpddns_json_object", "$@97", "logging_object", "$@98",
  "logging_params", "logging_param", "loggers", "$@99", "loggers_entries",
  "logger_entry", "$@100", "logger_params", "logger_param", "debuglevel",
  "severity", "$@101", "output_options_list", "$@102",
  "output_options_list_content", "output_entry", "$@103",
  "output_params_list", "output_params", "output", "$@104", "flush",
  "maxsize", "maxver", YY_NULLPTR
  };

#if PARSER4_DEBUG
  const unsigned short int
  Dhcp4Parser::yyrline_[] =
  {
       0,   219,   219,   219,   220,   220,   221,   221,   222,   222,
     223,   223,   224,   224,   225,   225,   226,   226,   227,   227,
     228,   228,   229,   229,   237,   238,   239,   240,   241,   242,
     243,   246,   251,   251,   262,   265,   266,   269,   273,   280,
     280,   287,   288,   291,   295,   302,   302,   309,   310,   313,
     317,   328,   338,   338,   350,   351,   355,   356,   357,   358,
     359,   362,   362,   379,   379,   387,   388,   393,   394,   395,
     396,   397,   398,   399,   400,   401,   402,   403,   404,   405,
     406,   407,   408,   409,   410,   411,   412,   413,   416,   421,
     426,   431,   436,   441,   447,   447,   457,   458,   461,   462,
     465,   465,   473,   473,   483,   483,   490,   491,   494,   494,
     504,   504,   514,   515,   518,   519,   520,   521,   522,   523,
     524,   525,   526,   527,   528,   529,   530,   533,   533,   540,
     541,   542,   543,   546,   546,   554,   554,   562,   562,   570,
     575,   575,   583,   588,   593,   598,   603,   603,   611,   611,
     620,   620,   630,   631,   634,   635,   636,   637,   638,   641,
     646,   651,   656,   661,   666,   666,   676,   677,   680,   681,
     684,   684,   692,   692,   700,   701,   702,   705,   706,   709,
     709,   717,   717,   725,   725,   735,   736,   739,   740,   741,
     742,   743,   744,   747,   752,   757,   762,   767,   772,   780,
     780,   793,   794,   797,   798,   805,   805,   828,   828,   837,
     838,   842,   843,   844,   845,   846,   847,   848,   849,   850,
     851,   852,   853,   854,   855,   856,   857,   858,   859,   860,
     861,   864,   864,   872,   872,   880,   880,   888,   888,   896,
     896,   904,   904,   912,   912,   920,   920,   928,   933,   942,
     942,   954,   955,   958,   959,   964,   964,   975,   975,   985,
     986,   989,   990,   993,   994,   995,   996,   997,   998,   999,
    1000,  1003,  1005,  1010,  1012,  1012,  1020,  1020,  1028,  1028,
    1036,  1038,  1038,  1046,  1055,  1055,  1067,  1068,  1073,  1074,
    1079,  1079,  1090,  1090,  1101,  1102,  1107,  1108,  1113,  1114,
    1115,  1116,  1117,  1118,  1121,  1123,  1123,  1131,  1133,  1135,
    1143,  1143,  1155,  1156,  1159,  1160,  1163,  1163,  1171,  1171,
    1179,  1180,  1183,  1184,  1185,  1186,  1189,  1189,  1197,  1197,
    1207,  1207,  1217,  1218,  1221,  1222,  1225,  1225,  1233,  1233,
    1241,  1242,  1245,  1246,  1250,  1251,  1252,  1253,  1254,  1255,
    1256,  1257,  1258,  1259,  1260,  1261,  1262,  1265,  1265,  1273,
    1273,  1281,  1281,  1289,  1289,  1297,  1297,  1305,  1305,  1313,
    1313,  1321,  1321,  1329,  1329,  1337,  1337,  1345,  1345,  1358,
    1358,  1368,  1368,  1379,  1379,  1389,  1390,  1393,  1393,  1401,
    1402,  1405,  1406,  1409,  1410,  1411,  1412,  1413,  1414,  1415,
    1418,  1420,  1420,  1432,  1439,  1439,  1449,  1450,  1453,  1454,
    1457,  1457,  1465,  1465,  1475,  1475,  1485,  1485,  1493,  1494,
    1497,  1498,  1499,  1500,  1501,  1502,  1503,  1504,  1505,  1506,
    1507,  1508,  1509,  1510,  1511,  1514,  1519,  1519,  1527,  1527,
    1535,  1540,  1540,  1548,  1553,  1558,  1558,  1566,  1567,  1570,
    1570,  1578,  1583,  1588,  1593,  1593,  1601,  1604,  1607,  1610,
    1613,  1619,  1619,  1629,  1629,  1636,  1636,  1648,  1648,  1661,
    1662,  1666,  1670,  1670,  1682,  1683,  1687,  1687,  1695,  1696,
    1699,  1700,  1701,  1702,  1703,  1706,  1711,  1711,  1719,  1719,
    1729,  1730,  1733,  1733,  1741,  1742,  1745,  1746,  1747,  1748,
    1751,  1751,  1759,  1764,  1769
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
#line 4112 "dhcp4_parser.cc" // lalr1.cc:1167
#line 1774 "dhcp4_parser.yy" // lalr1.cc:1168


void
isc::dhcp::Dhcp4Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
