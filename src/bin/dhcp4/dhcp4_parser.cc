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
      case 149: // value
      case 153: // map_value
      case 191: // socket_type
      case 200: // db_type
      case 405: // ncr_protocol_value
      case 414: // replace_client_name_value
        value.move< ElementPtr > (that.value);
        break;

      case 135: // "boolean"
        value.move< bool > (that.value);
        break;

      case 134: // "floating point"
        value.move< double > (that.value);
        break;

      case 133: // "integer"
        value.move< int64_t > (that.value);
        break;

      case 132: // "constant string"
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
      case 149: // value
      case 153: // map_value
      case 191: // socket_type
      case 200: // db_type
      case 405: // ncr_protocol_value
      case 414: // replace_client_name_value
        value.copy< ElementPtr > (that.value);
        break;

      case 135: // "boolean"
        value.copy< bool > (that.value);
        break;

      case 134: // "floating point"
        value.copy< double > (that.value);
        break;

      case 133: // "integer"
        value.copy< int64_t > (that.value);
        break;

      case 132: // "constant string"
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
            case 132: // "constant string"

#line 207 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< std::string > (); }
#line 362 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 133: // "integer"

#line 207 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< int64_t > (); }
#line 369 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 134: // "floating point"

#line 207 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< double > (); }
#line 376 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 135: // "boolean"

#line 207 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< bool > (); }
#line 383 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 149: // value

#line 207 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 390 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 153: // map_value

#line 207 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 397 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 191: // socket_type

#line 207 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 404 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 200: // db_type

#line 207 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 411 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 405: // ncr_protocol_value

#line 207 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 418 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 414: // replace_client_name_value

#line 207 "dhcp4_parser.yy" // lalr1.cc:636
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
      case 149: // value
      case 153: // map_value
      case 191: // socket_type
      case 200: // db_type
      case 405: // ncr_protocol_value
      case 414: // replace_client_name_value
        yylhs.value.build< ElementPtr > ();
        break;

      case 135: // "boolean"
        yylhs.value.build< bool > ();
        break;

      case 134: // "floating point"
        yylhs.value.build< double > ();
        break;

      case 133: // "integer"
        yylhs.value.build< int64_t > ();
        break;

      case 132: // "constant string"
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
#line 216 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.NO_KEYWORD; }
#line 670 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 4:
#line 217 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.CONFIG; }
#line 676 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 6:
#line 218 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.DHCP4; }
#line 682 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 8:
#line 219 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.INTERFACES_CONFIG; }
#line 688 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 10:
#line 220 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.SUBNET4; }
#line 694 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 12:
#line 221 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.POOLS; }
#line 700 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 14:
#line 222 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.RESERVATIONS; }
#line 706 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 16:
#line 223 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.OPTION_DEF; }
#line 712 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 18:
#line 224 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.OPTION_DATA; }
#line 718 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 20:
#line 225 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.HOOKS_LIBRARIES; }
#line 724 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 22:
#line 226 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.DHCP_DDNS; }
#line 730 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 24:
#line 234 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 736 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 25:
#line 235 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as< double > (), ctx.loc2pos(yystack_[0].location))); }
#line 742 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 26:
#line 236 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 748 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 27:
#line 237 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 754 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 28:
#line 238 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 760 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 29:
#line 239 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 766 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 30:
#line 240 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 772 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 31:
#line 243 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as< ElementPtr > ());
}
#line 781 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 32:
#line 248 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 792 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 33:
#line 253 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 802 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 34:
#line 259 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 808 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 37:
#line 266 "dhcp4_parser.yy" // lalr1.cc:859
    {
                  // map containing a single entry
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 817 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 38:
#line 270 "dhcp4_parser.yy" // lalr1.cc:859
    {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 827 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 39:
#line 277 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 836 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 40:
#line 280 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // list parsing complete. Put any sanity checking here
}
#line 844 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 43:
#line 288 "dhcp4_parser.yy" // lalr1.cc:859
    {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 853 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 44:
#line 292 "dhcp4_parser.yy" // lalr1.cc:859
    {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 862 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 45:
#line 299 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // List parsing about to start
}
#line 870 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 46:
#line 301 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // list parsing complete. Put any sanity checking here
    //ctx.stack_.pop_back();
}
#line 879 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 49:
#line 310 "dhcp4_parser.yy" // lalr1.cc:859
    {
                          ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 888 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 50:
#line 314 "dhcp4_parser.yy" // lalr1.cc:859
    {
                          ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 897 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 51:
#line 325 "dhcp4_parser.yy" // lalr1.cc:859
    {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as< std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 908 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 52:
#line 335 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 919 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 53:
#line 340 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 929 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 61:
#line 359 "dhcp4_parser.yy" // lalr1.cc:859
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
#line 366 "dhcp4_parser.yy" // lalr1.cc:859
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
#line 376 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the Dhcp4 map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 964 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 64:
#line 380 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 972 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 88:
#line 413 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 981 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 89:
#line 418 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 990 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 90:
#line 423 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 999 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 91:
#line 428 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr dpp(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 1008 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 92:
#line 433 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr echo(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("echo-client-id", echo);
}
#line 1017 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 93:
#line 438 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr match(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("match-client-id", match);
}
#line 1026 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 94:
#line 444 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces-config", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.INTERFACES_CONFIG);
}
#line 1037 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 95:
#line 449 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1046 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 100:
#line 462 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1056 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 101:
#line 466 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1064 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 102:
#line 470 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1075 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 103:
#line 475 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1084 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 104:
#line 480 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.DHCP_SOCKET_TYPE);
}
#line 1092 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 105:
#line 482 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("dhcp-socket-type", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1101 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 106:
#line 487 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("raw", ctx.loc2pos(yystack_[0].location))); }
#line 1107 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 107:
#line 488 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("udp", ctx.loc2pos(yystack_[0].location))); }
#line 1113 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 108:
#line 491 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lease-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.LEASE_DATABASE);
}
#line 1124 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 109:
#line 496 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1133 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 110:
#line 501 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1144 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 111:
#line 506 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1153 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 127:
#line 530 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.DATABASE_TYPE);
}
#line 1161 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 128:
#line 532 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("type", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1170 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 129:
#line 537 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("memfile", ctx.loc2pos(yystack_[0].location))); }
#line 1176 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 130:
#line 538 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("mysql", ctx.loc2pos(yystack_[0].location))); }
#line 1182 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 131:
#line 539 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("postgresql", ctx.loc2pos(yystack_[0].location))); }
#line 1188 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 132:
#line 540 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("cql", ctx.loc2pos(yystack_[0].location))); }
#line 1194 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 133:
#line 543 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1202 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 134:
#line 545 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr user(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1212 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 135:
#line 551 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1220 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 136:
#line 553 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr pwd(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 1230 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 137:
#line 559 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1238 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 138:
#line 561 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr h(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 1248 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 139:
#line 567 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr p(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", p);
}
#line 1257 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 140:
#line 572 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1265 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 141:
#line 574 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1275 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 142:
#line 580 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 1284 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 143:
#line 585 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 1293 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 144:
#line 590 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 1302 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 145:
#line 595 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("connect-timeout", n);
}
#line 1311 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 146:
#line 600 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1319 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 147:
#line 602 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr cp(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("contact-points", cp);
    ctx.leave();
}
#line 1329 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 148:
#line 608 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1337 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 149:
#line 610 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr ks(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("keyspace", ks);
    ctx.leave();
}
#line 1347 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 150:
#line 617 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 1358 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 151:
#line 622 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1367 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 158:
#line 637 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1376 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 159:
#line 642 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 1385 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 160:
#line 647 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr circuit(new StringElement("circuit-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(circuit);
}
#line 1394 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 161:
#line 652 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr client(new StringElement("client-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(client);
}
#line 1403 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 162:
#line 657 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 1414 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 163:
#line 662 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1423 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 168:
#line 675 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1433 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 169:
#line 679 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1441 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 170:
#line 683 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1451 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 171:
#line 687 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1459 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 177:
#line 700 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1467 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 178:
#line 702 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr lib(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 1477 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 179:
#line 708 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1485 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 180:
#line 710 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1494 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 181:
#line 716 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.EXPIRED_LEASES_PROCESSING);
}
#line 1505 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 182:
#line 721 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1514 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 191:
#line 738 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 1523 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 192:
#line 743 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 1532 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 193:
#line 748 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 1541 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 194:
#line 753 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 1550 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 195:
#line 758 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 1559 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 196:
#line 763 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 1568 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 197:
#line 771 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet4", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET4);
}
#line 1579 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 198:
#line 776 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1588 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 203:
#line 796 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1598 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 204:
#line 800 "dhcp4_parser.yy" // lalr1.cc:859
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
#line 819 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the subnet4 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1631 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 206:
#line 823 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1639 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 229:
#line 855 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1647 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 230:
#line 857 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr subnet(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 1657 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 231:
#line 863 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1665 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 232:
#line 865 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface", iface);
    ctx.leave();
}
#line 1675 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 233:
#line 871 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1683 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 234:
#line 873 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface-id", iface);
    ctx.leave();
}
#line 1693 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 235:
#line 879 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1701 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 236:
#line 881 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-subnet", iface);
    ctx.leave();
}
#line 1711 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 237:
#line 887 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1719 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 238:
#line 889 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 1729 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 239:
#line 895 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1737 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 240:
#line 897 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface-id", iface);
    ctx.leave();
}
#line 1747 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 241:
#line 903 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.CLIENT_CLASS);
}
#line 1755 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 242:
#line 905 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr cls(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 1765 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 243:
#line 911 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1773 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 244:
#line 913 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr rm(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservation-mode", rm);
    ctx.leave();
}
#line 1783 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 245:
#line 919 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr id(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 1792 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 246:
#line 924 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr rc(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rapid-commit", rc);
}
#line 1801 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 247:
#line 933 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 1812 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 248:
#line 938 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1821 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 253:
#line 955 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1831 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 254:
#line 959 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1839 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 255:
#line 966 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1849 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 256:
#line 970 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1857 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 270:
#line 996 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr code(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 1866 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 272:
#line 1003 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1874 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 273:
#line 1005 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 1884 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 274:
#line 1011 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1892 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 275:
#line 1013 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 1902 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 276:
#line 1019 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1910 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 277:
#line 1021 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr space(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 1920 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 279:
#line 1029 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1928 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 280:
#line 1031 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr encap(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 1938 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 281:
#line 1037 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr array(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 1947 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 282:
#line 1046 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 1958 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 283:
#line 1051 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1967 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 288:
#line 1070 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1977 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 289:
#line 1074 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1985 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 290:
#line 1081 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1995 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 291:
#line 1085 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 2003 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 303:
#line 1114 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2011 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 304:
#line 1116 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr data(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 2021 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 307:
#line 1126 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr space(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", space);
}
#line 2030 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 308:
#line 1134 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 2041 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 309:
#line 1139 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2050 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 314:
#line 1154 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2060 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 315:
#line 1158 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2068 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 316:
#line 1162 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2078 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 317:
#line 1166 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 2086 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 324:
#line 1180 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2094 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 325:
#line 1182 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr pool(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 2104 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 326:
#line 1188 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2112 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 327:
#line 1190 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("user-context", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2121 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 328:
#line 1198 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 2132 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 329:
#line 1203 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2141 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 334:
#line 1216 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2151 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 335:
#line 1220 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2159 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 336:
#line 1224 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2169 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 337:
#line 1228 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 2177 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 354:
#line 1255 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2185 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 355:
#line 1257 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr next_server(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("next-server", next_server);
    ctx.leave();
}
#line 2195 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 356:
#line 1263 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2203 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 357:
#line 1265 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr srv(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-hostname", srv);
    ctx.leave();
}
#line 2213 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 358:
#line 1271 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2221 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 359:
#line 1273 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr bootfile(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("boot-file-name", bootfile);
    ctx.leave();
}
#line 2231 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 360:
#line 1279 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2239 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 361:
#line 1281 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr addr(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", addr);
    ctx.leave();
}
#line 2249 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 362:
#line 1287 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2257 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 363:
#line 1289 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr d(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 2267 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 364:
#line 1295 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2275 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 365:
#line 1297 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 2285 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 366:
#line 1303 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2293 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 367:
#line 1305 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-id", hw);
    ctx.leave();
}
#line 2303 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 368:
#line 1311 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2311 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 369:
#line 1313 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("circuit-id", hw);
    ctx.leave();
}
#line 2321 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 370:
#line 1320 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2329 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 371:
#line 1322 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr host(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 2339 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 372:
#line 1328 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2350 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 373:
#line 1333 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2359 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 374:
#line 1341 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 2370 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 375:
#line 1346 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2379 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 376:
#line 1351 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2387 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 377:
#line 1353 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr ip(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", ip);
    ctx.leave();
}
#line 2397 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 378:
#line 1362 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 2408 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 379:
#line 1367 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2417 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 382:
#line 1376 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2427 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 383:
#line 1380 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2435 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 396:
#line 1403 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2443 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 397:
#line 1405 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr test(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 2453 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 398:
#line 1415 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 2462 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 399:
#line 1422 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 2473 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 400:
#line 1427 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2482 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 405:
#line 1440 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2490 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 406:
#line 1442 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr stype(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 2500 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 407:
#line 1448 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2508 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 408:
#line 1450 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 2518 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 409:
#line 1458 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 2529 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 410:
#line 1463 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2538 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 411:
#line 1468 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2548 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 412:
#line 1472 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 2556 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 431:
#line 1498 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 2565 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 432:
#line 1503 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2573 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 433:
#line 1505 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("qualifying-suffix", s);
    ctx.leave();
}
#line 2583 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 434:
#line 1511 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2591 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 435:
#line 1513 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 2601 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 436:
#line 1519 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 2610 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 437:
#line 1524 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2618 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 438:
#line 1526 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 2628 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 439:
#line 1532 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 2637 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 440:
#line 1537 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 2646 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 441:
#line 1542 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 2654 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 442:
#line 1544 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2663 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 443:
#line 1550 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 2669 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 444:
#line 1551 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 2675 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 445:
#line 1554 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NCR_FORMAT);
}
#line 2683 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 446:
#line 1556 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 2693 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 447:
#line 1562 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-include-fqdn", b);
}
#line 2702 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 448:
#line 1567 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("allow-client-update",  b);
}
#line 2711 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 449:
#line 1572 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-no-update", b);
}
#line 2720 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 450:
#line 1577 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-client-update", b);
}
#line 2729 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 451:
#line 1582 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 2737 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 452:
#line 1584 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("replace-client-name", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2746 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 453:
#line 1590 "dhcp4_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("when-present", ctx.loc2pos(yystack_[0].location))); 
      }
#line 2754 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 454:
#line 1593 "dhcp4_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location)));
      }
#line 2762 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 455:
#line 1596 "dhcp4_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("always", ctx.loc2pos(yystack_[0].location)));
      }
#line 2770 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 456:
#line 1599 "dhcp4_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("when-not-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 2778 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 457:
#line 1602 "dhcp4_parser.yy" // lalr1.cc:859
    {
      error(yystack_[0].location, "boolean values for the replace-client-name are "
                "no longer supported");
      }
#line 2787 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 458:
#line 1608 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2795 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 459:
#line 1610 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("generated-prefix", s);
    ctx.leave();
}
#line 2805 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 460:
#line 1618 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2813 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 461:
#line 1620 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("Dhcp6", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2822 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 462:
#line 1625 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2830 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 463:
#line 1627 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("DhcpDdns", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2839 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 464:
#line 1637 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Logging", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.LOGGING);
}
#line 2850 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 465:
#line 1642 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2859 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 469:
#line 1659 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 2870 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 470:
#line 1664 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2879 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 473:
#line 1676 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 2889 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 474:
#line 1680 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2897 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 482:
#line 1695 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr dl(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 2906 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 483:
#line 1700 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2914 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 484:
#line 1702 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 2924 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 485:
#line 1708 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 2935 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 486:
#line 1713 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2944 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 489:
#line 1722 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2954 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 490:
#line 1726 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2962 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 493:
#line 1734 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2970 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 494:
#line 1736 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 2980 "dhcp4_parser.cc" // lalr1.cc:859
    break;


#line 2984 "dhcp4_parser.cc" // lalr1.cc:859
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
      62,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,
    -473,  -473,    32,    19,    59,    81,   124,   140,   165,   173,
     222,   244,   249,   250,  -473,  -473,  -473,  -473,  -473,  -473,
    -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,
    -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,
    -473,  -473,  -473,  -473,  -473,  -473,    19,   -90,    17,    29,
     196,    18,   -14,    72,    49,    74,   -25,   120,  -473,    42,
      70,   123,   131,   193,  -473,  -473,  -473,  -473,   137,  -473,
      31,  -473,  -473,  -473,  -473,  -473,  -473,   259,   260,  -473,
    -473,  -473,   263,   265,   267,   269,  -473,  -473,  -473,  -473,
    -473,  -473,  -473,   270,  -473,  -473,  -473,    52,  -473,  -473,
    -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,
    -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,
    -473,    56,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,
    -473,  -473,  -473,   271,   273,  -473,  -473,  -473,  -473,  -473,
    -473,  -473,  -473,  -473,    93,  -473,  -473,  -473,  -473,  -473,
    -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,
    -473,  -473,  -473,  -473,  -473,   102,  -473,  -473,  -473,  -473,
    -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,
     272,   275,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,
    -473,  -473,  -473,  -473,  -473,   277,  -473,  -473,  -473,   280,
    -473,  -473,   279,   282,  -473,  -473,  -473,  -473,  -473,  -473,
    -473,  -473,  -473,  -473,  -473,   285,  -473,  -473,  -473,  -473,
     284,   290,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,
    -473,   125,  -473,  -473,  -473,   295,  -473,  -473,   296,  -473,
     302,   303,  -473,  -473,   304,   305,   307,   309,  -473,  -473,
    -473,   126,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,
    -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,    19,
      19,  -473,   162,   310,   311,   312,   313,  -473,    17,  -473,
     314,   184,   185,   318,   319,   320,   194,   197,   198,   200,
     321,   322,   324,   325,   328,   330,   331,   203,   333,   334,
      29,  -473,   335,   336,   196,  -473,    65,   337,   338,   339,
     342,   343,   344,   345,   217,   216,   348,   349,   350,   351,
      18,  -473,   352,   353,   -14,  -473,   354,   355,   356,   357,
     358,   359,   360,   361,   362,  -473,    72,   363,   364,   241,
     365,   366,   367,   242,  -473,    49,   368,   243,  -473,    74,
     369,   371,    36,  -473,   245,   372,   375,   248,   378,   251,
     252,   379,   382,   253,   254,   255,   256,   383,   388,   120,
    -473,  -473,  -473,   389,   387,   390,    19,    19,  -473,   391,
    -473,  -473,   264,   392,   393,  -473,  -473,  -473,  -473,   396,
     397,   398,   399,   400,   401,   402,  -473,   403,   404,  -473,
     407,    16,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,
     405,   411,  -473,  -473,  -473,   276,   283,   286,   412,   287,
     288,   289,  -473,  -473,   291,   292,   420,   409,  -473,   297,
     421,  -473,   298,   301,   407,   306,   315,   316,   323,   326,
     329,  -473,   332,   340,  -473,   341,   346,   347,  -473,  -473,
     370,  -473,  -473,   373,    19,  -473,  -473,   374,   376,  -473,
     377,  -473,  -473,    14,   299,  -473,  -473,  -473,  -473,    66,
     380,  -473,    19,    29,   281,  -473,  -473,   196,  -473,   134,
     134,   427,   428,   429,   189,    30,   430,   150,   138,   120,
    -473,  -473,  -473,  -473,  -473,   435,  -473,    65,  -473,  -473,
    -473,   436,  -473,  -473,  -473,  -473,  -473,   438,   381,  -473,
    -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,
    -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,
    -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,
    -473,  -473,  -473,  -473,   132,  -473,   152,  -473,  -473,   171,
    -473,  -473,  -473,  -473,   442,   446,   447,   448,   449,  -473,
    -473,  -473,   191,  -473,  -473,  -473,  -473,  -473,  -473,  -473,
    -473,  -473,  -473,  -473,  -473,  -473,   192,  -473,   454,   439,
    -473,  -473,   456,   451,  -473,  -473,   457,   462,  -473,  -473,
    -473,  -473,  -473,    35,  -473,  -473,  -473,  -473,  -473,  -473,
      46,  -473,   460,   464,  -473,   465,   466,   467,   470,   471,
     472,   195,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,
    -473,   236,  -473,  -473,  -473,   237,   384,   385,  -473,  -473,
     474,   478,  -473,  -473,   476,   480,  -473,  -473,   469,  -473,
     481,   281,  -473,  -473,   482,   483,   484,   485,   386,   394,
     395,   406,   410,   486,   487,   134,  -473,  -473,    18,  -473,
     427,    49,  -473,   428,    74,  -473,   429,   189,  -473,    30,
    -473,   -25,  -473,   430,   413,   414,   415,   416,   417,   418,
     150,  -473,   488,   489,   138,  -473,  -473,  -473,   490,   491,
    -473,   -14,  -473,   436,    72,  -473,   438,   493,  -473,   463,
    -473,   278,   408,   422,   423,  -473,  -473,  -473,  -473,  -473,
     424,   425,  -473,   238,  -473,   492,  -473,   495,  -473,  -473,
    -473,   239,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,
     426,   431,  -473,  -473,   432,   240,  -473,   496,  -473,   433,
     477,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,
    -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,
    -473,  -473,   105,  -473,    41,   477,  -473,  -473,   494,  -473,
    -473,  -473,   246,  -473,  -473,  -473,  -473,  -473,   497,   419,
     503,    41,  -473,   505,  -473,   434,  -473,   504,  -473,  -473,
     199,  -473,   437,   504,  -473,  -473,   247,  -473,  -473,   509,
     437,  -473,   440,  -473,  -473
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
      42,     0,     0,    36,    61,   464,   460,   462,     0,    60,
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
     174,     0,   172,   175,   176,     0,   432,   434,     0,   437,
       0,     0,   441,   445,     0,     0,     0,     0,   451,   458,
     430,     0,   413,   415,   416,   417,   418,   419,   420,   421,
     422,   423,   424,   425,   426,   427,   428,   429,    40,     0,
       0,    33,     0,     0,     0,     0,     0,    51,     0,    53,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    64,     0,     0,     0,   101,   384,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   206,     0,     0,     0,   317,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   337,     0,     0,     0,     0,
       0,     0,     0,     0,   256,     0,     0,     0,   291,     0,
       0,     0,     0,   171,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     412,    44,    37,     0,     0,     0,     0,     0,    55,     0,
      92,    93,     0,     0,     0,    88,    89,    90,    91,     0,
       0,     0,     0,     0,     0,     0,   398,     0,     0,    66,
       0,     0,    97,   396,   394,   395,   390,   391,   392,   393,
       0,   385,   386,   388,   389,     0,     0,     0,     0,     0,
       0,     0,   245,   246,     0,     0,     0,     0,   208,     0,
       0,   319,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   341,     0,     0,   270,     0,     0,     0,   281,   260,
       0,   307,   295,     0,     0,   173,   431,     0,     0,   436,
       0,   439,   440,     0,     0,   447,   448,   449,   450,     0,
       0,   414,     0,     0,     0,   461,   463,     0,   355,     0,
       0,   199,   249,   284,     0,     0,   164,     0,     0,     0,
      45,   103,   106,   107,   105,     0,   383,     0,   232,   234,
     236,   310,   230,   238,   240,   244,   242,   330,     0,   325,
      34,   327,   357,   359,   373,   363,   365,   369,   367,   371,
     361,   273,   141,   277,   275,   280,   304,   178,   180,   433,
     435,   438,   443,   444,   442,   446,   453,   454,   455,   456,
     457,   452,   459,    38,     0,   469,     0,   466,   468,     0,
     127,   133,   135,   137,     0,     0,     0,     0,     0,   146,
     148,   126,     0,   112,   114,   115,   116,   117,   118,   119,
     120,   121,   122,   123,   124,   125,     0,   203,     0,   200,
     201,   253,     0,   250,   251,   288,     0,   285,   286,   158,
     159,   160,   161,     0,   152,   154,   155,   156,   157,   380,
       0,   168,     0,   165,   166,     0,     0,     0,     0,     0,
       0,     0,   183,   185,   186,   187,   188,   189,   190,   405,
     407,     0,   401,   403,   404,     0,    47,     0,   387,   314,
       0,   311,   312,   334,     0,   331,   332,   376,     0,    62,
       0,     0,   465,    95,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   109,   111,     0,   198,
       0,   257,   248,     0,   292,   283,     0,     0,   151,     0,
     379,     0,   163,     0,     0,     0,     0,     0,     0,     0,
       0,   182,     0,     0,     0,   400,   410,    49,     0,    48,
     397,     0,   309,     0,   338,   329,     0,     0,   375,     0,
     467,     0,     0,     0,     0,   139,   142,   143,   144,   145,
       0,     0,   113,     0,   202,     0,   252,     0,   287,   153,
     381,     0,   167,   191,   192,   193,   194,   195,   196,   184,
       0,     0,   402,    46,     0,     0,   313,     0,   333,     0,
       0,   129,   130,   131,   132,   128,   134,   136,   138,   147,
     149,   204,   254,   289,   169,   406,   408,    50,   315,   335,
     377,   473,     0,   471,     0,     0,   470,   485,     0,   483,
     481,   477,     0,   475,   479,   480,   478,   472,     0,     0,
       0,     0,   474,     0,   482,     0,   476,     0,   484,   489,
       0,   487,     0,     0,   486,   493,     0,   491,   488,     0,
       0,   490,     0,   492,   494
  };

  const short int
  Dhcp4Parser::yypgoto_[] =
  {
    -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,
    -473,  -473,  -473,   -42,  -473,    55,  -473,  -473,  -473,  -473,
    -473,  -473,  -473,  -473,    71,  -473,  -473,  -473,   -58,  -473,
    -473,  -473,   211,  -473,  -473,  -473,  -473,    37,   204,   -60,
     -44,   -40,  -473,  -473,   -39,  -473,  -473,    34,   208,  -473,
    -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,
      28,  -142,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,
    -473,  -473,   -63,  -473,  -473,  -473,  -473,  -473,  -473,  -473,
    -473,  -473,  -473,  -473,  -473,  -153,  -473,  -473,  -473,  -473,
    -473,  -473,  -473,  -473,  -158,  -473,  -473,  -473,  -155,   168,
    -473,  -473,  -473,  -473,  -473,  -473,  -473,  -163,  -473,  -473,
    -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -139,  -473,
    -473,  -473,  -136,   205,  -473,  -473,  -473,  -473,  -473,  -473,
    -473,  -473,  -473,  -473,  -473,  -473,  -472,  -473,  -473,  -473,
    -473,  -473,  -473,  -473,  -473,  -473,  -140,  -473,  -473,  -473,
    -137,  -473,   181,  -473,   -49,  -473,  -473,  -473,  -473,  -473,
     -47,  -473,  -473,  -473,  -473,  -473,   -51,  -473,  -473,  -473,
    -138,  -473,  -473,  -473,  -135,  -473,   178,  -473,  -473,  -473,
    -473,  -473,  -473,  -473,  -473,  -473,  -473,  -161,  -473,  -473,
    -473,  -157,   225,  -473,  -473,  -473,  -473,  -473,  -473,  -473,
    -473,  -146,  -473,  -473,  -473,  -159,  -473,   215,   -48,  -473,
    -297,  -473,  -296,  -473,  -473,  -473,  -473,  -473,  -473,  -473,
    -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,
    -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,    60,  -473,
    -473,  -473,  -473,  -473,  -473,  -473,  -132,  -473,  -473,  -473,
    -473,  -473,  -473,  -473,  -473,    69,   190,  -473,  -473,  -473,
    -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,
    -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,
    -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,   -81,  -473,
    -473,  -473,  -204,  -473,  -473,  -218,  -473,  -473,  -473,  -473,
    -473,  -473,  -229,  -473,  -473,  -235,  -473
  };

  const short int
  Dhcp4Parser::yydefgoto_[] =
  {
      -1,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    32,    33,    34,    57,   521,    72,    73,
      35,    56,    69,    70,   501,   636,   698,   699,   106,    37,
      58,    80,    81,    82,   283,    39,    59,   107,   108,   109,
     110,   111,   112,   113,   114,   115,   290,   131,   132,    41,
      60,   133,   312,   134,   313,   504,   116,   294,   117,   295,
     572,   573,   574,   654,   755,   575,   655,   576,   656,   577,
     657,   578,   211,   348,   580,   581,   582,   583,   584,   663,
     585,   664,   118,   303,   603,   604,   605,   606,   607,   608,
     119,   305,   612,   613,   614,   681,    53,    66,   241,   242,
     243,   360,   244,   361,   120,   306,   621,   622,   623,   624,
     625,   626,   627,   628,   121,   300,   588,   589,   590,   668,
      43,    61,   154,   155,   156,   321,   157,   317,   158,   318,
     159,   319,   160,   322,   161,   323,   162,   327,   163,   326,
     164,   165,   122,   301,   592,   593,   594,   671,    49,    64,
     212,   213,   214,   215,   216,   217,   218,   347,   219,   351,
     220,   350,   221,   222,   352,   223,   123,   302,   596,   597,
     598,   674,    51,    65,   230,   231,   232,   233,   234,   356,
     235,   236,   237,   167,   320,   640,   641,   642,   701,    45,
      62,   175,   176,   177,   332,   178,   333,   168,   328,   644,
     645,   646,   704,    47,    63,   190,   191,   192,   124,   293,
     194,   336,   195,   337,   196,   344,   197,   339,   198,   340,
     199,   342,   200,   341,   201,   343,   202,   338,   170,   329,
     648,   707,   125,   304,   610,   316,   420,   421,   422,   423,
     424,   505,   126,   127,   308,   631,   632,   633,   692,   634,
     693,   128,   309,    55,    67,   261,   262,   263,   264,   365,
     265,   366,   266,   267,   368,   268,   269,   270,   371,   544,
     271,   372,   272,   273,   274,   275,   276,   377,   551,   277,
     378,    83,   285,    84,   286,    85,   284,   556,   557,   558,
     650,   772,   773,   774,   782,   783,   784,   785,   790,   786,
     788,   800,   801,   802,   806,   807,   809
  };

  const unsigned short int
  Dhcp4Parser::yytable_[] =
  {
      79,   150,   227,   149,   173,   188,   210,   226,   240,   260,
     166,   174,   189,   169,    68,   193,   228,   151,   229,   418,
     419,   152,   153,   609,    25,   135,    26,    74,    27,   542,
     502,   503,    24,    98,   288,    88,    89,   135,   677,   289,
      86,   678,    71,   171,   172,    87,    88,    89,   278,   679,
      90,    91,   680,   238,   239,   310,    92,    93,    94,   314,
     311,   136,   137,   138,   315,    98,    36,    92,    93,    94,
      95,    96,   203,   279,   139,    97,    98,   140,   141,   142,
     143,   144,   145,    89,   179,   180,   146,   147,    38,   204,
      89,   179,   180,   148,    99,   100,   330,   204,   146,   205,
     206,   331,   207,   208,   209,   334,   101,    78,   775,   102,
     335,   776,    98,   204,   238,   239,   103,   104,    78,    98,
     105,   543,   204,   224,   205,   206,   225,   280,   362,   379,
      75,    40,   413,   363,   380,   310,    76,    77,   181,   281,
     649,   287,   182,   183,   184,   185,   186,    42,   187,    78,
      78,    28,    29,    30,    31,   651,   777,   560,   778,   779,
     652,    78,   561,   562,   563,   564,   565,   566,   567,   568,
     569,   570,    44,    78,   314,   546,   547,   548,   549,   653,
      46,    78,   204,     1,     2,     3,     4,     5,     6,     7,
       8,     9,    10,    11,   665,   665,   282,    78,   690,   666,
     667,   550,   803,   691,    78,   804,    78,   730,   129,   130,
     418,   419,   245,   246,   247,   248,   249,   250,   251,   252,
     253,   254,   255,   256,   257,   258,   259,   629,   630,    48,
      79,   615,   616,   617,   618,   619,   620,   381,   382,   694,
     379,   330,   362,   334,   695,   696,   761,   764,   768,   791,
     810,    50,    78,   415,   792,   811,    52,    54,   414,   599,
     600,   601,   602,   291,   292,   416,    78,   296,   417,   297,
     150,   298,   149,   299,   307,   324,   173,   325,   346,   166,
     345,   349,   169,   174,   353,   355,   151,   354,   188,   357,
     152,   153,   358,   359,   383,   189,   227,   210,   193,   364,
     367,   226,   751,   752,   753,   754,   369,   370,   373,   374,
     228,   375,   229,   376,   384,   385,   386,   387,   389,   390,
     391,   260,   392,   393,   394,   399,   400,   395,   401,   402,
     396,   397,   403,   398,   404,   405,   406,   407,   408,   410,
     411,   425,   426,   427,   485,   486,   428,   429,   430,   431,
     432,   433,   434,   435,   436,   437,   439,   440,   442,   443,
     444,   445,   446,   447,   448,   449,   450,   452,   453,   455,
     456,   457,   460,   463,   454,   464,   467,   458,   461,   468,
     466,   469,   470,   473,   471,   472,   474,   479,   475,   476,
     477,   478,   480,   482,   483,   555,   488,   484,   487,   489,
     490,   491,   492,   493,   494,   495,   496,   545,   508,   497,
     498,   499,   500,   506,   507,   509,   518,   511,   510,   512,
     513,   514,   538,   515,   516,   517,   579,   579,    26,   519,
     522,   571,   571,   523,   587,   591,   595,   611,   525,   637,
     553,   260,   670,   639,   415,   643,   658,   526,   527,   414,
     659,   660,   661,   662,   673,   528,   416,   647,   529,   417,
     669,   530,   672,   675,   531,   676,   682,   683,   750,   684,
     685,   686,   532,   533,   687,   688,   689,   708,   534,   535,
     702,   703,   705,   706,   771,   709,   711,   712,   713,   714,
     720,   721,   740,   741,   744,   520,   743,   749,   789,   388,
     762,   793,   536,   763,   769,   537,   539,   795,   540,   541,
     797,   799,   552,   812,   409,   524,   697,   700,   586,   715,
     554,   559,   412,   722,   729,   732,   731,   739,   717,   716,
     465,   724,   723,   726,   725,   438,   459,   462,   728,   727,
     756,   718,   746,   719,   745,   747,   733,   734,   735,   736,
     737,   738,   794,   805,   757,   758,   759,   760,   765,   441,
     748,   451,   742,   766,   767,   770,   798,   638,   635,   481,
     710,   787,   814,   796,   808,   813,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   579,     0,     0,     0,     0,   571,   150,     0,
     149,   227,     0,   210,     0,     0,   226,   166,     0,     0,
     169,     0,     0,   240,   151,   228,     0,   229,   152,   153,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   173,     0,     0,   188,     0,     0,     0,
     174,     0,     0,   189,     0,     0,   193,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   781,     0,     0,     0,     0,   780,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   781,     0,
       0,     0,     0,   780
  };

  const short int
  Dhcp4Parser::yycheck_[] =
  {
      58,    61,    65,    61,    62,    63,    64,    65,    66,    67,
      61,    62,    63,    61,    56,    63,    65,    61,    65,   316,
     316,    61,    61,   495,     5,     7,     7,    10,     9,    15,
      14,    15,     0,    47,     3,    17,    18,     7,     3,     8,
      11,     6,   132,    57,    58,    16,    17,    18,     6,     3,
      21,    22,     6,    78,    79,     3,    38,    39,    40,     3,
       8,    43,    44,    45,     8,    47,     7,    38,    39,    40,
      41,    42,    23,     3,    56,    46,    47,    59,    60,    61,
      62,    63,    64,    18,    19,    20,    68,    69,     7,    48,
      18,    19,    20,    75,    65,    66,     3,    48,    68,    50,
      51,     8,    53,    54,    55,     3,    77,   132,     3,    80,
       8,     6,    47,    48,    78,    79,    87,    88,   132,    47,
      91,   107,    48,    49,    50,    51,    52,     4,     3,     3,
     113,     7,    67,     8,     8,     3,   119,   120,    66,     8,
       8,     4,    70,    71,    72,    73,    74,     7,    76,   132,
     132,   132,   133,   134,   135,     3,   115,    23,   117,   118,
       8,   132,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,     7,   132,     3,   109,   110,   111,   112,     8,
       7,   132,    48,   121,   122,   123,   124,   125,   126,   127,
     128,   129,   130,   131,     3,     3,     3,   132,     3,     8,
       8,   135,     3,     8,   132,     6,   132,   679,    12,    13,
     507,   507,    92,    93,    94,    95,    96,    97,    98,    99,
     100,   101,   102,   103,   104,   105,   106,    89,    90,     7,
     288,    81,    82,    83,    84,    85,    86,   279,   280,     3,
       3,     3,     3,     3,     8,     8,     8,     8,     8,     3,
       3,     7,   132,   316,     8,     8,     7,     7,   316,    70,
      71,    72,    73,     4,     4,   316,   132,     4,   316,     4,
     330,     4,   330,     4,     4,     4,   334,     4,     3,   330,
       8,     4,   330,   334,     4,     3,   330,     8,   346,     4,
     330,   330,     8,     3,   132,   346,   359,   355,   346,     4,
       4,   359,    24,    25,    26,    27,     4,     4,     4,     4,
     359,     4,   359,     4,     4,     4,     4,     4,     4,   135,
     135,   379,     4,     4,     4,     4,     4,   133,     4,     4,
     133,   133,     4,   133,     4,     4,   133,     4,     4,     4,
       4,     4,     4,     4,   386,   387,     4,     4,     4,     4,
     133,   135,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,   133,     4,     4,   135,   135,     4,
     135,   133,     4,     4,   133,   133,     4,     4,   135,   135,
     135,   135,     4,     4,     7,   114,   132,     7,     7,     7,
       7,     5,     5,     5,     5,     5,     5,   108,   132,     7,
       7,     7,     5,     8,     3,   132,     7,     5,   132,   132,
     132,   132,   464,   132,   132,     5,   489,   490,     7,   132,
     132,   489,   490,   132,     7,     7,     7,     7,   132,     4,
     482,   499,     3,     7,   507,     7,     4,   132,   132,   507,
       4,     4,     4,     4,     3,   132,   507,    76,   132,   507,
       6,   132,     6,     6,   132,     3,     6,     3,     5,     4,
       4,     4,   132,   132,     4,     4,     4,     8,   132,   132,
       6,     3,     6,     3,     7,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     3,   440,     6,     4,     4,   288,
       8,     4,   132,     8,     8,   132,   132,     4,   132,   132,
       5,     7,   132,     4,   310,   444,   132,   132,   490,   133,
     483,   487,   314,   665,   677,   683,   681,   690,   133,   135,
     362,   670,   668,   673,   671,   330,   355,   359,   676,   674,
     132,   135,   703,   133,   701,   704,   133,   133,   133,   133,
     133,   133,   133,   116,   132,   132,   132,   132,   132,   334,
     706,   346,   694,   132,   132,   132,   132,   507,   499,   379,
     651,   775,   132,   791,   803,   810,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   665,    -1,    -1,    -1,    -1,   665,   668,    -1,
     668,   674,    -1,   671,    -1,    -1,   674,   668,    -1,    -1,
     668,    -1,    -1,   681,   668,   674,    -1,   674,   668,   668,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   701,    -1,    -1,   704,    -1,    -1,    -1,
     701,    -1,    -1,   704,    -1,    -1,   704,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   774,    -1,    -1,    -1,    -1,   774,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   791,    -1,
      -1,    -1,    -1,   791
  };

  const unsigned short int
  Dhcp4Parser::yystos_[] =
  {
       0,   121,   122,   123,   124,   125,   126,   127,   128,   129,
     130,   131,   137,   138,   139,   140,   141,   142,   143,   144,
     145,   146,   147,   148,     0,     5,     7,     9,   132,   133,
     134,   135,   149,   150,   151,   156,     7,   165,     7,   171,
       7,   185,     7,   256,     7,   325,     7,   339,     7,   284,
       7,   308,     7,   232,     7,   389,   157,   152,   166,   172,
     186,   257,   326,   340,   285,   309,   233,   390,   149,   158,
     159,   132,   154,   155,    10,   113,   119,   120,   132,   164,
     167,   168,   169,   417,   419,   421,    11,    16,    17,    18,
      21,    22,    38,    39,    40,    41,    42,    46,    47,    65,
      66,    77,    80,    87,    88,    91,   164,   173,   174,   175,
     176,   177,   178,   179,   180,   181,   192,   194,   218,   226,
     240,   250,   278,   302,   344,   368,   378,   379,   387,    12,
      13,   183,   184,   187,   189,     7,    43,    44,    45,    56,
      59,    60,    61,    62,    63,    64,    68,    69,    75,   164,
     175,   176,   177,   180,   258,   259,   260,   262,   264,   266,
     268,   270,   272,   274,   276,   277,   302,   319,   333,   344,
     364,    57,    58,   164,   302,   327,   328,   329,   331,    19,
      20,    66,    70,    71,    72,    73,    74,    76,   164,   302,
     341,   342,   343,   344,   346,   348,   350,   352,   354,   356,
     358,   360,   362,    23,    48,    50,    51,    53,    54,    55,
     164,   208,   286,   287,   288,   289,   290,   291,   292,   294,
     296,   298,   299,   301,    49,    52,   164,   208,   290,   296,
     310,   311,   312,   313,   314,   316,   317,   318,    78,    79,
     164,   234,   235,   236,   238,    92,    93,    94,    95,    96,
      97,    98,    99,   100,   101,   102,   103,   104,   105,   106,
     164,   391,   392,   393,   394,   396,   398,   399,   401,   402,
     403,   406,   408,   409,   410,   411,   412,   415,     6,     3,
       4,     8,     3,   170,   422,   418,   420,     4,     3,     8,
     182,     4,     4,   345,   193,   195,     4,     4,     4,     4,
     251,   279,   303,   219,   369,   227,   241,     4,   380,   388,
       3,     8,   188,   190,     3,     8,   371,   263,   265,   267,
     320,   261,   269,   271,     4,     4,   275,   273,   334,   365,
       3,     8,   330,   332,     3,     8,   347,   349,   363,   353,
     355,   359,   357,   361,   351,     8,     3,   293,   209,     4,
     297,   295,   300,     4,     8,     3,   315,     4,     8,     3,
     237,   239,     3,     8,     4,   395,   397,     4,   400,     4,
       4,   404,   407,     4,     4,     4,     4,   413,   416,     3,
       8,   149,   149,   132,     4,     4,     4,     4,   168,     4,
     135,   135,     4,     4,     4,   133,   133,   133,   133,     4,
       4,     4,     4,     4,     4,     4,   133,     4,     4,   174,
       4,     4,   184,    67,   164,   208,   302,   344,   346,   348,
     372,   373,   374,   375,   376,     4,     4,     4,     4,     4,
       4,     4,   133,   135,     4,     4,     4,     4,   259,     4,
       4,   328,     4,     4,     4,     4,     4,     4,     4,     4,
       4,   343,     4,     4,   133,     4,     4,     4,   135,   288,
       4,   135,   312,     4,     4,   235,   135,     4,     4,   133,
       4,   133,   133,     4,     4,   135,   135,   135,   135,     4,
       4,   392,     4,     7,     7,   149,   149,     7,   132,     7,
       7,     5,     5,     5,     5,     5,     5,     7,     7,     7,
       5,   160,    14,    15,   191,   377,     8,     3,   132,   132,
     132,     5,   132,   132,   132,   132,   132,     5,     7,   132,
     151,   153,   132,   132,   160,   132,   132,   132,   132,   132,
     132,   132,   132,   132,   132,   132,   132,   132,   149,   132,
     132,   132,    15,   107,   405,   108,   109,   110,   111,   112,
     135,   414,   132,   149,   173,   114,   423,   424,   425,   183,
      23,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      37,   164,   196,   197,   198,   201,   203,   205,   207,   208,
     210,   211,   212,   213,   214,   216,   196,     7,   252,   253,
     254,     7,   280,   281,   282,     7,   304,   305,   306,    70,
      71,    72,    73,   220,   221,   222,   223,   224,   225,   272,
     370,     7,   228,   229,   230,    81,    82,    83,    84,    85,
      86,   242,   243,   244,   245,   246,   247,   248,   249,    89,
      90,   381,   382,   383,   385,   391,   161,     4,   374,     7,
     321,   322,   323,     7,   335,   336,   337,    76,   366,     8,
     426,     3,     8,     8,   199,   202,   204,   206,     4,     4,
       4,     4,     4,   215,   217,     3,     8,     8,   255,     6,
       3,   283,     6,     3,   307,     6,     3,     3,     6,     3,
       6,   231,     6,     3,     4,     4,     4,     4,     4,     4,
       3,     8,   384,   386,     3,     8,     8,   132,   162,   163,
     132,   324,     6,     3,   338,     6,     3,   367,     8,     4,
     424,     4,     4,     4,     4,   133,   135,   133,   135,   133,
       4,     4,   197,   258,   254,   286,   282,   310,   306,   221,
     272,   234,   230,   133,   133,   133,   133,   133,   133,   243,
       4,     4,   382,     6,     3,   327,   323,   341,   337,     4,
       5,    24,    25,    26,    27,   200,   132,   132,   132,   132,
     132,     8,     8,     8,     8,   132,   132,   132,     8,     8,
     132,     7,   427,   428,   429,     3,     6,   115,   117,   118,
     164,   208,   430,   431,   432,   433,   435,   428,   436,     4,
     434,     3,     8,     4,   133,     4,   431,     5,   132,     7,
     437,   438,   439,     3,     6,   116,   440,   441,   438,   442,
       3,     8,     4,   441,   132
  };

  const unsigned short int
  Dhcp4Parser::yyr1_[] =
  {
       0,   136,   138,   137,   139,   137,   140,   137,   141,   137,
     142,   137,   143,   137,   144,   137,   145,   137,   146,   137,
     147,   137,   148,   137,   149,   149,   149,   149,   149,   149,
     149,   150,   152,   151,   153,   154,   154,   155,   155,   157,
     156,   158,   158,   159,   159,   161,   160,   162,   162,   163,
     163,   164,   166,   165,   167,   167,   168,   168,   168,   168,
     168,   170,   169,   172,   171,   173,   173,   174,   174,   174,
     174,   174,   174,   174,   174,   174,   174,   174,   174,   174,
     174,   174,   174,   174,   174,   174,   174,   174,   175,   176,
     177,   178,   179,   180,   182,   181,   183,   183,   184,   184,
     186,   185,   188,   187,   190,   189,   191,   191,   193,   192,
     195,   194,   196,   196,   197,   197,   197,   197,   197,   197,
     197,   197,   197,   197,   197,   197,   197,   199,   198,   200,
     200,   200,   200,   202,   201,   204,   203,   206,   205,   207,
     209,   208,   210,   211,   212,   213,   215,   214,   217,   216,
     219,   218,   220,   220,   221,   221,   221,   221,   222,   223,
     224,   225,   227,   226,   228,   228,   229,   229,   231,   230,
     233,   232,   234,   234,   234,   235,   235,   237,   236,   239,
     238,   241,   240,   242,   242,   243,   243,   243,   243,   243,
     243,   244,   245,   246,   247,   248,   249,   251,   250,   252,
     252,   253,   253,   255,   254,   257,   256,   258,   258,   259,
     259,   259,   259,   259,   259,   259,   259,   259,   259,   259,
     259,   259,   259,   259,   259,   259,   259,   259,   259,   261,
     260,   263,   262,   265,   264,   267,   266,   269,   268,   271,
     270,   273,   272,   275,   274,   276,   277,   279,   278,   280,
     280,   281,   281,   283,   282,   285,   284,   286,   286,   287,
     287,   288,   288,   288,   288,   288,   288,   288,   288,   289,
     290,   291,   293,   292,   295,   294,   297,   296,   298,   300,
     299,   301,   303,   302,   304,   304,   305,   305,   307,   306,
     309,   308,   310,   310,   311,   311,   312,   312,   312,   312,
     312,   312,   313,   315,   314,   316,   317,   318,   320,   319,
     321,   321,   322,   322,   324,   323,   326,   325,   327,   327,
     328,   328,   328,   328,   330,   329,   332,   331,   334,   333,
     335,   335,   336,   336,   338,   337,   340,   339,   341,   341,
     342,   342,   343,   343,   343,   343,   343,   343,   343,   343,
     343,   343,   343,   343,   345,   344,   347,   346,   349,   348,
     351,   350,   353,   352,   355,   354,   357,   356,   359,   358,
     361,   360,   363,   362,   365,   364,   367,   366,   369,   368,
     370,   370,   371,   272,   372,   372,   373,   373,   374,   374,
     374,   374,   374,   374,   374,   375,   377,   376,   378,   380,
     379,   381,   381,   382,   382,   384,   383,   386,   385,   388,
     387,   390,   389,   391,   391,   392,   392,   392,   392,   392,
     392,   392,   392,   392,   392,   392,   392,   392,   392,   392,
     392,   393,   395,   394,   397,   396,   398,   400,   399,   401,
     402,   404,   403,   405,   405,   407,   406,   408,   409,   410,
     411,   413,   412,   414,   414,   414,   414,   414,   416,   415,
     418,   417,   420,   419,   422,   421,   423,   423,   424,   426,
     425,   427,   427,   429,   428,   430,   430,   431,   431,   431,
     431,   431,   432,   434,   433,   436,   435,   437,   437,   439,
     438,   440,   440,   442,   441
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
       1,     3,     0,     4,     0,     4,     3,     0,     4,     3,
       3,     0,     4,     1,     1,     0,     4,     3,     3,     3,
       3,     0,     4,     1,     1,     1,     1,     1,     0,     4,
       0,     4,     0,     4,     0,     6,     1,     3,     1,     0,
       6,     1,     3,     0,     4,     1,     3,     1,     1,     1,
       1,     1,     3,     0,     4,     0,     6,     1,     3,     0,
       4,     1,     3,     0,     4
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
  "\"allow-client-update\"", "\"override-no-update\"",
  "\"override-client-update\"", "\"replace-client-name\"",
  "\"generated-prefix\"", "\"tcp\"", "\"JSON\"", "\"when-present\"",
  "\"never\"", "\"always\"", "\"when-not-present\"", "\"Logging\"",
  "\"loggers\"", "\"output_options\"", "\"output\"", "\"debuglevel\"",
  "\"severity\"", "\"Dhcp6\"", "\"DhcpDdns\"", "TOPLEVEL_JSON",
  "TOPLEVEL_DHCP4", "SUB_DHCP4", "SUB_INTERFACES4", "SUB_SUBNET4",
  "SUB_POOL4", "SUB_RESERVATION", "SUB_OPTION_DEF", "SUB_OPTION_DATA",
  "SUB_HOOKS_LIBRARY", "SUB_DHCP_DDNS", "\"constant string\"",
  "\"integer\"", "\"floating point\"", "\"boolean\"", "$accept", "start",
  "$@1", "$@2", "$@3", "$@4", "$@5", "$@6", "$@7", "$@8", "$@9", "$@10",
  "$@11", "value", "sub_json", "map2", "$@12", "map_value", "map_content",
  "not_empty_map", "list_generic", "$@13", "list_content",
  "not_empty_list", "list_strings", "$@14", "list_strings_content",
  "not_empty_list_strings", "unknown_map_entry", "syntax_map", "$@15",
  "global_objects", "global_object", "dhcp4_object", "$@16", "sub_dhcp4",
  "$@17", "global_params", "global_param", "valid_lifetime", "renew_timer",
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
  "always_include_fqdn", "allow_client_update", "override_no_update",
  "override_client_update", "replace_client_name", "$@93",
  "replace_client_name_value", "generated_prefix", "$@94",
  "dhcp6_json_object", "$@95", "dhcpddns_json_object", "$@96",
  "logging_object", "$@97", "logging_params", "logging_param", "loggers",
  "$@98", "loggers_entries", "logger_entry", "$@99", "logger_params",
  "logger_param", "debuglevel", "severity", "$@100", "output_options_list",
  "$@101", "output_options_list_content", "output_entry", "$@102",
  "output_params", "output_param", "$@103", YY_NULLPTR
  };

#if PARSER4_DEBUG
  const unsigned short int
  Dhcp4Parser::yyrline_[] =
  {
       0,   216,   216,   216,   217,   217,   218,   218,   219,   219,
     220,   220,   221,   221,   222,   222,   223,   223,   224,   224,
     225,   225,   226,   226,   234,   235,   236,   237,   238,   239,
     240,   243,   248,   248,   259,   262,   263,   266,   270,   277,
     277,   284,   285,   288,   292,   299,   299,   306,   307,   310,
     314,   325,   335,   335,   347,   348,   352,   353,   354,   355,
     356,   359,   359,   376,   376,   384,   385,   390,   391,   392,
     393,   394,   395,   396,   397,   398,   399,   400,   401,   402,
     403,   404,   405,   406,   407,   408,   409,   410,   413,   418,
     423,   428,   433,   438,   444,   444,   454,   455,   458,   459,
     462,   462,   470,   470,   480,   480,   487,   488,   491,   491,
     501,   501,   511,   512,   515,   516,   517,   518,   519,   520,
     521,   522,   523,   524,   525,   526,   527,   530,   530,   537,
     538,   539,   540,   543,   543,   551,   551,   559,   559,   567,
     572,   572,   580,   585,   590,   595,   600,   600,   608,   608,
     617,   617,   627,   628,   631,   632,   633,   634,   637,   642,
     647,   652,   657,   657,   667,   668,   671,   672,   675,   675,
     683,   683,   691,   692,   693,   696,   697,   700,   700,   708,
     708,   716,   716,   726,   727,   730,   731,   732,   733,   734,
     735,   738,   743,   748,   753,   758,   763,   771,   771,   784,
     785,   788,   789,   796,   796,   819,   819,   828,   829,   833,
     834,   835,   836,   837,   838,   839,   840,   841,   842,   843,
     844,   845,   846,   847,   848,   849,   850,   851,   852,   855,
     855,   863,   863,   871,   871,   879,   879,   887,   887,   895,
     895,   903,   903,   911,   911,   919,   924,   933,   933,   945,
     946,   949,   950,   955,   955,   966,   966,   976,   977,   980,
     981,   984,   985,   986,   987,   988,   989,   990,   991,   994,
     996,  1001,  1003,  1003,  1011,  1011,  1019,  1019,  1027,  1029,
    1029,  1037,  1046,  1046,  1058,  1059,  1064,  1065,  1070,  1070,
    1081,  1081,  1092,  1093,  1098,  1099,  1104,  1105,  1106,  1107,
    1108,  1109,  1112,  1114,  1114,  1122,  1124,  1126,  1134,  1134,
    1146,  1147,  1150,  1151,  1154,  1154,  1162,  1162,  1170,  1171,
    1174,  1175,  1176,  1177,  1180,  1180,  1188,  1188,  1198,  1198,
    1208,  1209,  1212,  1213,  1216,  1216,  1224,  1224,  1232,  1233,
    1236,  1237,  1241,  1242,  1243,  1244,  1245,  1246,  1247,  1248,
    1249,  1250,  1251,  1252,  1255,  1255,  1263,  1263,  1271,  1271,
    1279,  1279,  1287,  1287,  1295,  1295,  1303,  1303,  1311,  1311,
    1320,  1320,  1328,  1328,  1341,  1341,  1351,  1351,  1362,  1362,
    1372,  1373,  1376,  1376,  1384,  1385,  1388,  1389,  1392,  1393,
    1394,  1395,  1396,  1397,  1398,  1401,  1403,  1403,  1415,  1422,
    1422,  1432,  1433,  1436,  1437,  1440,  1440,  1448,  1448,  1458,
    1458,  1468,  1468,  1476,  1477,  1480,  1481,  1482,  1483,  1484,
    1485,  1486,  1487,  1488,  1489,  1490,  1491,  1492,  1493,  1494,
    1495,  1498,  1503,  1503,  1511,  1511,  1519,  1524,  1524,  1532,
    1537,  1542,  1542,  1550,  1551,  1554,  1554,  1562,  1567,  1572,
    1577,  1582,  1582,  1590,  1593,  1596,  1599,  1602,  1608,  1608,
    1618,  1618,  1625,  1625,  1637,  1637,  1650,  1651,  1655,  1659,
    1659,  1671,  1672,  1676,  1676,  1684,  1685,  1688,  1689,  1690,
    1691,  1692,  1695,  1700,  1700,  1708,  1708,  1718,  1719,  1722,
    1722,  1730,  1731,  1734,  1734
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
#line 4053 "dhcp4_parser.cc" // lalr1.cc:1167
#line 1742 "dhcp4_parser.yy" // lalr1.cc:1168


void
isc::dhcp::Dhcp4Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
