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
      case 201: // db_type
      case 406: // ncr_protocol_value
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
      case 201: // db_type
      case 406: // ncr_protocol_value
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

      case 201: // db_type

#line 207 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 411 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 406: // ncr_protocol_value

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
      case 201: // db_type
      case 406: // ncr_protocol_value
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

  case 101:
#line 463 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1056 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 102:
#line 467 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1064 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 103:
#line 471 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1075 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 104:
#line 476 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1084 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 105:
#line 481 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.DHCP_SOCKET_TYPE);
}
#line 1092 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 106:
#line 483 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("dhcp-socket-type", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1101 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 107:
#line 488 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("raw", ctx.loc2pos(yystack_[0].location))); }
#line 1107 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 108:
#line 489 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("udp", ctx.loc2pos(yystack_[0].location))); }
#line 1113 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 109:
#line 492 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("re-detect", b);
}
#line 1122 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 110:
#line 498 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lease-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.LEASE_DATABASE);
}
#line 1133 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 111:
#line 503 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1142 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 112:
#line 508 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1153 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 113:
#line 513 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1162 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 129:
#line 537 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.DATABASE_TYPE);
}
#line 1170 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 130:
#line 539 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("type", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1179 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 131:
#line 544 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("memfile", ctx.loc2pos(yystack_[0].location))); }
#line 1185 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 132:
#line 545 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("mysql", ctx.loc2pos(yystack_[0].location))); }
#line 1191 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 133:
#line 546 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("postgresql", ctx.loc2pos(yystack_[0].location))); }
#line 1197 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 134:
#line 547 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("cql", ctx.loc2pos(yystack_[0].location))); }
#line 1203 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 135:
#line 550 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1211 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 136:
#line 552 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr user(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1221 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 137:
#line 558 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1229 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 138:
#line 560 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr pwd(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 1239 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 139:
#line 566 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1247 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 140:
#line 568 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr h(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 1257 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 141:
#line 574 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr p(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", p);
}
#line 1266 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 142:
#line 579 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1274 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 143:
#line 581 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1284 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 144:
#line 587 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 1293 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 145:
#line 592 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 1302 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 146:
#line 597 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 1311 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 147:
#line 602 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("connect-timeout", n);
}
#line 1320 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 148:
#line 607 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1328 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 149:
#line 609 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr cp(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("contact-points", cp);
    ctx.leave();
}
#line 1338 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 150:
#line 615 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1346 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 151:
#line 617 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr ks(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("keyspace", ks);
    ctx.leave();
}
#line 1356 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 152:
#line 624 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 1367 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 153:
#line 629 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1376 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 160:
#line 644 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1385 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 161:
#line 649 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 1394 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 162:
#line 654 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr circuit(new StringElement("circuit-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(circuit);
}
#line 1403 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 163:
#line 659 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr client(new StringElement("client-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(client);
}
#line 1412 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 164:
#line 664 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 1423 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 165:
#line 669 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1432 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 170:
#line 682 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1442 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 171:
#line 686 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1450 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 172:
#line 690 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1460 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 173:
#line 694 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1468 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 179:
#line 707 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1476 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 180:
#line 709 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr lib(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 1486 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 181:
#line 715 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1494 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 182:
#line 717 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1503 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 183:
#line 723 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.EXPIRED_LEASES_PROCESSING);
}
#line 1514 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 184:
#line 728 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1523 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 193:
#line 745 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 1532 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 194:
#line 750 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 1541 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 195:
#line 755 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 1550 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 196:
#line 760 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 1559 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 197:
#line 765 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 1568 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 198:
#line 770 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 1577 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 199:
#line 778 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet4", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET4);
}
#line 1588 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 200:
#line 783 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1597 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 205:
#line 803 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1607 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 206:
#line 807 "dhcp4_parser.yy" // lalr1.cc:859
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
#line 826 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the subnet4 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1640 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 208:
#line 830 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1648 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 231:
#line 862 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1656 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 232:
#line 864 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr subnet(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 1666 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 233:
#line 870 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1674 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 234:
#line 872 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface", iface);
    ctx.leave();
}
#line 1684 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 235:
#line 878 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1692 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 236:
#line 880 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface-id", iface);
    ctx.leave();
}
#line 1702 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 237:
#line 886 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1710 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 238:
#line 888 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-subnet", iface);
    ctx.leave();
}
#line 1720 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 239:
#line 894 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1728 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 240:
#line 896 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 1738 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 241:
#line 902 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1746 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 242:
#line 904 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface-id", iface);
    ctx.leave();
}
#line 1756 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 243:
#line 910 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.CLIENT_CLASS);
}
#line 1764 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 244:
#line 912 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr cls(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 1774 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 245:
#line 918 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1782 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 246:
#line 920 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr rm(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservation-mode", rm);
    ctx.leave();
}
#line 1792 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 247:
#line 926 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr id(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 1801 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 248:
#line 931 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr rc(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rapid-commit", rc);
}
#line 1810 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 249:
#line 940 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 1821 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 250:
#line 945 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1830 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 255:
#line 962 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1840 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 256:
#line 966 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1848 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 257:
#line 973 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1858 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 258:
#line 977 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1866 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 272:
#line 1003 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr code(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 1875 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 274:
#line 1010 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1883 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 275:
#line 1012 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 1893 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 276:
#line 1018 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1901 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 277:
#line 1020 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 1911 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 278:
#line 1026 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1919 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 279:
#line 1028 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr space(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 1929 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 281:
#line 1036 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1937 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 282:
#line 1038 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr encap(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 1947 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 283:
#line 1044 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr array(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 1956 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 284:
#line 1053 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 1967 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 285:
#line 1058 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1976 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 290:
#line 1077 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1986 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 291:
#line 1081 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1994 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 292:
#line 1088 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2004 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 293:
#line 1092 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 2012 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 305:
#line 1121 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2020 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 306:
#line 1123 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr data(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 2030 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 309:
#line 1133 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr space(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", space);
}
#line 2039 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 310:
#line 1141 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 2050 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 311:
#line 1146 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2059 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 316:
#line 1161 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2069 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 317:
#line 1165 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2077 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 318:
#line 1169 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2087 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 319:
#line 1173 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 2095 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 326:
#line 1187 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2103 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 327:
#line 1189 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr pool(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 2113 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 328:
#line 1195 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2121 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 329:
#line 1197 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("user-context", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2130 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 330:
#line 1205 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 2141 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 331:
#line 1210 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2150 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 336:
#line 1223 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2160 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 337:
#line 1227 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2168 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 338:
#line 1231 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2178 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 339:
#line 1235 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 2186 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 356:
#line 1262 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2194 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 357:
#line 1264 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr next_server(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("next-server", next_server);
    ctx.leave();
}
#line 2204 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 358:
#line 1270 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2212 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 359:
#line 1272 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr srv(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-hostname", srv);
    ctx.leave();
}
#line 2222 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 360:
#line 1278 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2230 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 361:
#line 1280 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr bootfile(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("boot-file-name", bootfile);
    ctx.leave();
}
#line 2240 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 362:
#line 1286 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2248 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 363:
#line 1288 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr addr(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", addr);
    ctx.leave();
}
#line 2258 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 364:
#line 1294 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2266 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 365:
#line 1296 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr d(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 2276 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 366:
#line 1302 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2284 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 367:
#line 1304 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 2294 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 368:
#line 1310 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2302 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 369:
#line 1312 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-id", hw);
    ctx.leave();
}
#line 2312 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 370:
#line 1318 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2320 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 371:
#line 1320 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("circuit-id", hw);
    ctx.leave();
}
#line 2330 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 372:
#line 1327 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2338 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 373:
#line 1329 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr host(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 2348 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 374:
#line 1335 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2359 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 375:
#line 1340 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2368 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 376:
#line 1348 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 2379 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 377:
#line 1353 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2388 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 378:
#line 1358 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2396 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 379:
#line 1360 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr ip(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", ip);
    ctx.leave();
}
#line 2406 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 380:
#line 1369 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 2417 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 381:
#line 1374 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2426 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 384:
#line 1383 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2436 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 385:
#line 1387 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2444 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 398:
#line 1410 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2452 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 399:
#line 1412 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr test(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 2462 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 400:
#line 1422 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 2471 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 401:
#line 1429 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 2482 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 402:
#line 1434 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2491 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 407:
#line 1447 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2499 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 408:
#line 1449 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr stype(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 2509 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 409:
#line 1455 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2517 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 410:
#line 1457 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 2527 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 411:
#line 1465 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 2538 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 412:
#line 1470 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2547 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 413:
#line 1475 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2557 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 414:
#line 1479 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 2565 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 432:
#line 1504 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 2574 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 433:
#line 1509 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2582 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 434:
#line 1511 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("qualifying-suffix", s);
    ctx.leave();
}
#line 2592 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 435:
#line 1517 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2600 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 436:
#line 1519 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 2610 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 437:
#line 1525 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 2619 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 438:
#line 1530 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2627 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 439:
#line 1532 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 2637 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 440:
#line 1538 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 2646 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 441:
#line 1543 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 2655 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 442:
#line 1548 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 2663 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 443:
#line 1550 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2672 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 444:
#line 1556 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 2678 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 445:
#line 1557 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 2684 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 446:
#line 1560 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NCR_FORMAT);
}
#line 2692 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 447:
#line 1562 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 2702 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 448:
#line 1568 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-include-fqdn", b);
}
#line 2711 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 449:
#line 1573 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-no-update", b);
}
#line 2720 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 450:
#line 1578 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-client-update", b);
}
#line 2729 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 451:
#line 1583 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 2737 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 452:
#line 1585 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("replace-client-name", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2746 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 453:
#line 1591 "dhcp4_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("when-present", ctx.loc2pos(yystack_[0].location))); 
      }
#line 2754 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 454:
#line 1594 "dhcp4_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location)));
      }
#line 2762 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 455:
#line 1597 "dhcp4_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("always", ctx.loc2pos(yystack_[0].location)));
      }
#line 2770 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 456:
#line 1600 "dhcp4_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("when-not-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 2778 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 457:
#line 1603 "dhcp4_parser.yy" // lalr1.cc:859
    {
      error(yystack_[0].location, "boolean values for the replace-client-name are "
                "no longer supported");
      }
#line 2787 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 458:
#line 1609 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2795 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 459:
#line 1611 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("generated-prefix", s);
    ctx.leave();
}
#line 2805 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 460:
#line 1619 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2813 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 461:
#line 1621 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("Dhcp6", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2822 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 462:
#line 1626 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2830 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 463:
#line 1628 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("DhcpDdns", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2839 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 464:
#line 1638 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Logging", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.LOGGING);
}
#line 2850 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 465:
#line 1643 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2859 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 469:
#line 1660 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 2870 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 470:
#line 1665 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2879 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 473:
#line 1677 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 2889 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 474:
#line 1681 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2897 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 482:
#line 1696 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr dl(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 2906 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 483:
#line 1701 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2914 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 484:
#line 1703 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 2924 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 485:
#line 1709 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 2935 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 486:
#line 1714 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2944 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 489:
#line 1723 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2954 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 490:
#line 1727 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2962 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 493:
#line 1735 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2970 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 494:
#line 1737 "dhcp4_parser.yy" // lalr1.cc:859
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
     201,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,
    -473,  -473,    32,    19,    38,    58,    60,    82,    86,    92,
     113,   134,   140,   151,  -473,  -473,  -473,  -473,  -473,  -473,
    -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,
    -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,
    -473,  -473,  -473,  -473,  -473,  -473,    19,   -89,    17,    29,
      96,    18,   -17,    71,    49,    74,   -30,   118,  -473,    68,
     129,   135,   165,   177,  -473,  -473,  -473,  -473,   204,  -473,
      26,  -473,  -473,  -473,  -473,  -473,  -473,   235,   247,  -473,
    -473,  -473,   254,   258,   259,   260,  -473,  -473,  -473,  -473,
    -473,  -473,  -473,   263,  -473,  -473,  -473,    30,  -473,  -473,
    -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,
    -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,
    -473,   264,    36,  -473,  -473,  -473,  -473,  -473,  -473,  -473,
    -473,  -473,  -473,  -473,  -473,   266,   268,  -473,  -473,  -473,
    -473,  -473,  -473,  -473,  -473,  -473,    52,  -473,  -473,  -473,
    -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,
    -473,  -473,  -473,  -473,  -473,  -473,  -473,    53,  -473,  -473,
    -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,
    -473,  -473,   184,   222,  -473,  -473,  -473,  -473,  -473,  -473,
    -473,  -473,  -473,  -473,  -473,  -473,  -473,   270,  -473,  -473,
    -473,   271,  -473,  -473,   245,   273,  -473,  -473,  -473,  -473,
    -473,  -473,  -473,  -473,  -473,  -473,  -473,   274,  -473,  -473,
    -473,  -473,   277,   276,  -473,  -473,  -473,  -473,  -473,  -473,
    -473,  -473,  -473,   108,  -473,  -473,  -473,   278,  -473,  -473,
     282,  -473,   284,   286,  -473,  -473,   289,   290,   291,  -473,
    -473,  -473,   126,  -473,  -473,  -473,  -473,  -473,  -473,  -473,
    -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,    19,
      19,  -473,   149,   296,   297,   299,   300,  -473,    17,  -473,
     301,   172,   173,   302,   305,   306,   179,   181,   182,   183,
     313,   314,   315,   316,   329,   330,   331,   203,   333,   334,
      29,  -473,   335,   336,   206,    96,  -473,    65,   338,   339,
     342,   343,   344,   345,   346,   218,   217,   349,   350,   351,
     352,    18,  -473,   353,   354,   -17,  -473,   355,   356,   357,
     358,   359,   360,   361,   362,   363,  -473,    71,   364,   365,
     237,   367,   368,   369,   239,  -473,    49,   371,   241,  -473,
      74,   373,   374,   -26,  -473,   244,   376,   377,   250,   378,
     251,   252,   382,   383,   253,   255,   256,   385,   388,   118,
    -473,  -473,  -473,   389,   387,   390,    19,    19,  -473,   391,
    -473,  -473,   267,   393,   394,  -473,  -473,  -473,  -473,   397,
     398,   399,   400,   401,   402,   403,  -473,   404,   405,  -473,
     408,   242,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,
    -473,   406,   392,  -473,  -473,  -473,   283,   285,   287,   411,
     288,   292,   293,  -473,  -473,   298,   303,   413,   414,  -473,
     304,   415,  -473,   307,   310,   408,   311,   318,   319,   320,
     321,   322,  -473,   323,   325,  -473,   326,   328,   332,  -473,
    -473,   337,  -473,  -473,   340,    19,  -473,  -473,   341,   347,
    -473,   348,  -473,  -473,    15,   366,  -473,  -473,  -473,    67,
     370,  -473,    19,    29,   294,  -473,  -473,    96,  -473,   133,
     133,   421,   422,   426,   171,    28,   427,   101,   170,   118,
    -473,  -473,  -473,  -473,  -473,   433,  -473,    65,  -473,  -473,
    -473,   431,  -473,  -473,  -473,  -473,  -473,   438,   384,  -473,
    -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,
    -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,
    -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,
    -473,  -473,  -473,  -473,   132,  -473,   152,  -473,  -473,   187,
    -473,  -473,  -473,  -473,   442,   443,   444,   458,   459,  -473,
    -473,  -473,   188,  -473,  -473,  -473,  -473,  -473,  -473,  -473,
    -473,  -473,  -473,  -473,  -473,  -473,   190,  -473,   460,   462,
    -473,  -473,   461,   465,  -473,  -473,   464,   468,  -473,  -473,
    -473,  -473,  -473,   125,  -473,  -473,  -473,  -473,  -473,  -473,
     153,  -473,   469,   473,  -473,   474,   477,   478,   479,   480,
     481,   191,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,
    -473,   197,  -473,  -473,  -473,   223,   372,   375,  -473,  -473,
     471,   483,  -473,  -473,   482,   484,  -473,  -473,   485,  -473,
     486,   294,  -473,  -473,   487,   488,   490,   491,   379,   261,
     380,   381,   386,   492,   493,   133,  -473,  -473,    18,  -473,
     421,    49,  -473,   422,    74,  -473,   426,   171,  -473,    28,
    -473,   -30,  -473,   427,   395,   396,   407,   409,   410,   412,
     101,  -473,   494,   495,   170,  -473,  -473,  -473,   497,   498,
    -473,   -17,  -473,   431,    71,  -473,   438,   496,  -473,   500,
    -473,   221,   416,   417,   418,  -473,  -473,  -473,  -473,  -473,
     419,   420,  -473,   224,  -473,   501,  -473,   502,  -473,  -473,
    -473,   225,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,
     423,   424,  -473,  -473,   425,   226,  -473,   503,  -473,   428,
     499,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,
    -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,
    -473,  -473,   198,  -473,    57,   499,  -473,  -473,   504,  -473,
    -473,  -473,   232,  -473,  -473,  -473,  -473,  -473,   510,   429,
     511,    57,  -473,   512,  -473,   432,  -473,   513,  -473,  -473,
     249,  -473,   430,   513,  -473,  -473,   233,  -473,  -473,   514,
     430,  -473,   434,  -473,  -473
  };

  const unsigned short int
  Dhcp4Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     1,    39,    32,    28,    27,    24,
      25,    26,    31,     3,    29,    30,    52,     5,    63,     7,
     101,     9,   207,    11,   318,    13,   338,    15,   257,    17,
     292,    19,   172,    21,   413,    23,    41,    35,     0,     0,
       0,     0,     0,   340,   259,   294,     0,     0,    43,     0,
      42,     0,     0,    36,    61,   464,   460,   462,     0,    60,
       0,    54,    56,    58,    59,    57,    94,     0,     0,   356,
     110,   112,     0,     0,     0,     0,   199,   249,   284,   152,
     380,   164,   183,     0,   401,   411,    87,     0,    65,    67,
      68,    69,    70,    84,    85,    72,    73,    74,    75,    79,
      80,    71,    77,    78,    86,    76,    81,    82,    83,   103,
     105,     0,     0,    96,    98,    99,   100,   384,   233,   235,
     237,   310,   231,   239,   241,     0,     0,   245,   243,   330,
     376,   230,   211,   212,   213,   225,     0,   209,   216,   227,
     228,   229,   217,   218,   221,   223,   219,   220,   214,   215,
     222,   226,   224,   326,   328,   325,   323,     0,   320,   322,
     324,   358,   360,   374,   364,   366,   370,   368,   372,   362,
     355,   351,     0,   341,   342,   352,   353,   354,   348,   344,
     349,   346,   347,   350,   345,   274,   142,     0,   278,   276,
     281,     0,   270,   271,     0,   260,   261,   263,   273,   264,
     265,   266,   280,   267,   268,   269,   305,     0,   303,   304,
     307,   308,     0,   295,   296,   298,   299,   300,   301,   302,
     179,   181,   176,     0,   174,   177,   178,     0,   433,   435,
       0,   438,     0,     0,   442,   446,     0,     0,     0,   451,
     458,   431,     0,   415,   417,   418,   419,   420,   421,   422,
     423,   424,   425,   426,   427,   428,   429,   430,    40,     0,
       0,    33,     0,     0,     0,     0,     0,    51,     0,    53,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    64,     0,     0,     0,     0,   102,   386,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   208,     0,     0,     0,   319,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   339,     0,     0,     0,
       0,     0,     0,     0,     0,   258,     0,     0,     0,   293,
       0,     0,     0,     0,   173,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     414,    44,    37,     0,     0,     0,     0,     0,    55,     0,
      92,    93,     0,     0,     0,    88,    89,    90,    91,     0,
       0,     0,     0,     0,     0,     0,   400,     0,     0,    66,
       0,     0,   109,    97,   398,   396,   397,   392,   393,   394,
     395,     0,   387,   388,   390,   391,     0,     0,     0,     0,
       0,     0,     0,   247,   248,     0,     0,     0,     0,   210,
       0,     0,   321,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   343,     0,     0,   272,     0,     0,     0,   283,
     262,     0,   309,   297,     0,     0,   175,   432,     0,     0,
     437,     0,   440,   441,     0,     0,   448,   449,   450,     0,
       0,   416,     0,     0,     0,   461,   463,     0,   357,     0,
       0,   201,   251,   286,     0,     0,   166,     0,     0,     0,
      45,   104,   107,   108,   106,     0,   385,     0,   234,   236,
     238,   312,   232,   240,   242,   246,   244,   332,     0,   327,
      34,   329,   359,   361,   375,   365,   367,   371,   369,   373,
     363,   275,   143,   279,   277,   282,   306,   180,   182,   434,
     436,   439,   444,   445,   443,   447,   453,   454,   455,   456,
     457,   452,   459,    38,     0,   469,     0,   466,   468,     0,
     129,   135,   137,   139,     0,     0,     0,     0,     0,   148,
     150,   128,     0,   114,   116,   117,   118,   119,   120,   121,
     122,   123,   124,   125,   126,   127,     0,   205,     0,   202,
     203,   255,     0,   252,   253,   290,     0,   287,   288,   160,
     161,   162,   163,     0,   154,   156,   157,   158,   159,   382,
       0,   170,     0,   167,   168,     0,     0,     0,     0,     0,
       0,     0,   185,   187,   188,   189,   190,   191,   192,   407,
     409,     0,   403,   405,   406,     0,    47,     0,   389,   316,
       0,   313,   314,   336,     0,   333,   334,   378,     0,    62,
       0,     0,   465,    95,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   111,   113,     0,   200,
       0,   259,   250,     0,   294,   285,     0,     0,   153,     0,
     381,     0,   165,     0,     0,     0,     0,     0,     0,     0,
       0,   184,     0,     0,     0,   402,   412,    49,     0,    48,
     399,     0,   311,     0,   340,   331,     0,     0,   377,     0,
     467,     0,     0,     0,     0,   141,   144,   145,   146,   147,
       0,     0,   115,     0,   204,     0,   254,     0,   289,   155,
     383,     0,   169,   193,   194,   195,   196,   197,   198,   186,
       0,     0,   404,    46,     0,     0,   315,     0,   335,     0,
       0,   131,   132,   133,   134,   130,   136,   138,   140,   149,
     151,   206,   256,   291,   171,   408,   410,    50,   317,   337,
     379,   473,     0,   471,     0,     0,   470,   485,     0,   483,
     481,   477,     0,   475,   479,   480,   478,   472,     0,     0,
       0,     0,   474,     0,   482,     0,   476,     0,   484,   489,
       0,   487,     0,     0,   486,   493,     0,   491,   488,     0,
       0,   490,     0,   492,   494
  };

  const short int
  Dhcp4Parser::yypgoto_[] =
  {
    -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,
    -473,  -473,  -473,   -42,  -473,   -32,  -473,  -473,  -473,  -473,
    -473,  -473,  -473,  -473,    44,  -473,  -473,  -473,   -58,  -473,
    -473,  -473,   234,  -473,  -473,  -473,  -473,    40,   211,   -60,
     -44,   -40,  -473,  -473,   -39,  -473,  -473,    37,   210,  -473,
    -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,
    -473,    41,  -139,  -473,  -473,  -473,  -473,  -473,  -473,  -473,
    -473,  -473,  -473,   -63,  -473,  -473,  -473,  -473,  -473,  -473,
    -473,  -473,  -473,  -473,  -473,  -473,  -150,  -473,  -473,  -473,
    -473,  -473,  -473,  -473,  -473,  -153,  -473,  -473,  -473,  -149,
     174,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -157,  -473,
    -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -136,
    -473,  -473,  -473,  -133,   205,  -473,  -473,  -473,  -473,  -473,
    -473,  -473,  -473,  -473,  -473,  -473,  -473,  -472,  -473,  -473,
    -473,  -473,  -473,  -473,  -473,  -473,  -473,  -135,  -473,  -473,
    -473,  -132,  -473,   185,  -473,   -49,  -473,  -473,  -473,  -473,
    -473,   -47,  -473,  -473,  -473,  -473,  -473,   -51,  -473,  -473,
    -473,  -129,  -473,  -473,  -473,  -130,  -473,   193,  -473,  -473,
    -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -145,  -473,
    -473,  -473,  -147,   228,  -473,  -473,  -473,  -473,  -473,  -473,
    -473,  -473,  -141,  -473,  -473,  -473,  -143,  -473,   212,   -48,
    -473,  -298,  -473,  -297,  -473,  -473,  -473,  -473,  -473,  -473,
    -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,
    -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,    61,
    -473,  -473,  -473,  -473,  -473,  -473,  -473,  -127,  -473,  -473,
    -473,  -473,  -473,  -473,  -473,  -473,    70,   192,  -473,  -473,
    -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,
    -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,
    -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,   -81,  -473,
    -473,  -473,  -203,  -473,  -473,  -218,  -473,  -473,  -473,  -473,
    -473,  -473,  -229,  -473,  -473,  -235,  -473
  };

  const short int
  Dhcp4Parser::yydefgoto_[] =
  {
      -1,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    32,    33,    34,    57,   521,    72,    73,
      35,    56,    69,    70,   501,   636,   698,   699,   106,    37,
      58,    80,    81,    82,   283,    39,    59,   107,   108,   109,
     110,   111,   112,   113,   114,   115,   290,   132,   133,    41,
      60,   134,   312,   135,   313,   504,   136,   116,   294,   117,
     295,   572,   573,   574,   654,   755,   575,   655,   576,   656,
     577,   657,   578,   213,   349,   580,   581,   582,   583,   584,
     663,   585,   664,   118,   303,   603,   604,   605,   606,   607,
     608,   119,   305,   612,   613,   614,   681,    53,    66,   243,
     244,   245,   361,   246,   362,   120,   306,   621,   622,   623,
     624,   625,   626,   627,   628,   121,   300,   588,   589,   590,
     668,    43,    61,   156,   157,   158,   322,   159,   318,   160,
     319,   161,   320,   162,   323,   163,   324,   164,   328,   165,
     327,   166,   167,   122,   301,   592,   593,   594,   671,    49,
      64,   214,   215,   216,   217,   218,   219,   220,   348,   221,
     352,   222,   351,   223,   224,   353,   225,   123,   302,   596,
     597,   598,   674,    51,    65,   232,   233,   234,   235,   236,
     357,   237,   238,   239,   169,   321,   640,   641,   642,   701,
      45,    62,   177,   178,   179,   333,   180,   334,   170,   329,
     644,   645,   646,   704,    47,    63,   192,   193,   194,   124,
     293,   196,   337,   197,   338,   198,   345,   199,   340,   200,
     341,   201,   343,   202,   342,   203,   344,   204,   339,   172,
     330,   648,   707,   125,   304,   610,   317,   421,   422,   423,
     424,   425,   505,   126,   127,   308,   631,   632,   633,   692,
     634,   693,   128,   309,    55,    67,   262,   263,   264,   265,
     366,   266,   367,   267,   268,   369,   269,   270,   271,   372,
     544,   272,   373,   273,   274,   275,   276,   377,   551,   277,
     378,    83,   285,    84,   286,    85,   284,   556,   557,   558,
     650,   772,   773,   774,   782,   783,   784,   785,   790,   786,
     788,   800,   801,   802,   806,   807,   809
  };

  const unsigned short int
  Dhcp4Parser::yytable_[] =
  {
      79,   152,   229,   151,   175,   190,   212,   228,   242,   261,
     168,   176,   191,   171,    68,   195,   230,   153,   231,   419,
     420,   154,   155,   609,    25,   137,    26,    74,    27,   288,
     542,    98,    24,   310,   289,   137,    88,    89,   311,   315,
      86,   173,   174,    71,   316,    36,    87,    88,    89,   240,
     241,    90,    91,   240,   241,   331,   335,    92,    93,    94,
     332,   336,   138,   139,   140,    38,    98,    40,    92,    93,
      94,    95,    96,   205,   278,   141,    97,    98,   142,   143,
     144,   145,   146,   147,    89,   181,   182,   148,   149,    42,
      89,   181,   182,    44,   150,    99,   100,   148,   206,    46,
     207,   208,    78,   209,   210,   211,   206,   101,   129,   130,
     102,   363,   131,    98,   206,    78,   364,   103,   104,    98,
      48,   105,   543,   206,   226,   207,   208,   227,   677,   379,
      75,   678,   279,   414,   380,   310,    76,    77,   183,   280,
     649,    50,   184,   185,   186,   187,   188,    52,   189,    78,
      78,    28,    29,    30,    31,   651,   679,   560,    54,   680,
     652,    78,   561,   562,   563,   564,   565,   566,   567,   568,
     569,   570,   777,   281,   778,   779,   546,   547,   548,   549,
     282,    78,   206,   615,   616,   617,   618,   619,   620,    78,
     315,   665,   346,   665,   690,   653,   666,    78,   667,   691,
     694,   775,   550,    78,   776,   695,    78,   730,   287,   419,
     420,   247,   248,   249,   250,   251,   252,   253,   254,   255,
     256,   257,   258,   259,   260,   347,   379,   331,   363,   335,
      79,   696,   761,   764,   768,   791,   810,   381,   382,   291,
     792,   811,   599,   600,   601,   602,   751,   752,   753,   754,
      78,   292,   803,   355,   416,   804,   502,   503,   296,   415,
     629,   630,   297,   298,   299,    78,   417,   307,   314,   418,
     325,   152,   326,   151,   350,   354,   356,   175,   358,   360,
     168,   383,   365,   171,   176,   359,   368,   153,   370,   190,
     371,   154,   155,   374,   375,   376,   191,   229,   212,   195,
     384,   385,   228,   386,   387,   389,   392,   390,   391,   393,
     394,   230,   395,   231,   396,   397,   398,   399,   400,   401,
     402,   261,     1,     2,     3,     4,     5,     6,     7,     8,
       9,    10,    11,   403,   404,   405,   406,   407,   408,   410,
     411,   412,   426,   427,   485,   486,   428,   429,   430,   431,
     432,   433,   434,   435,   436,   437,   438,   440,   441,   443,
     444,   445,   446,   447,   448,   449,   450,   451,   453,   454,
     455,   456,   457,   458,   459,   461,   462,   464,   465,   467,
     468,   469,   471,   470,   472,   473,   474,   475,   476,   479,
     477,   478,   480,   482,   483,   507,   716,   484,   487,   488,
     489,   490,   491,   492,   493,   494,   495,   496,   555,   520,
     497,   498,   499,   500,   506,   508,   511,   509,   517,   510,
     512,   518,    26,   538,   513,   514,   579,   579,   587,   591,
     515,   571,   571,   595,   611,   516,   519,   637,   639,   522,
     553,   261,   523,   525,   416,   643,   658,   659,   660,   415,
     526,   527,   528,   529,   530,   531,   417,   532,   533,   418,
     534,   647,   661,   662,   535,   670,   669,   672,   673,   536,
     675,   676,   537,   539,   545,   682,   683,   702,   684,   540,
     541,   685,   686,   687,   688,   689,   703,   706,   705,   524,
     709,   711,   712,   708,   713,   714,   720,   721,   740,   741,
     749,   744,   552,   743,   697,   750,   771,   700,   789,   762,
     763,   769,   715,   717,   793,   795,   718,   797,   812,   719,
     799,   409,   388,   554,   559,   413,   722,   729,   733,   734,
     732,   586,   731,   739,   724,   723,   439,   466,   726,   725,
     735,   460,   736,   737,   727,   738,   805,   728,   756,   757,
     758,   759,   760,   463,   745,   765,   766,   767,   746,   452,
     770,   747,   794,   442,   798,   748,   814,   742,   638,   635,
     710,   481,   787,   796,   808,   813,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   579,     0,     0,     0,     0,   571,   152,     0,
     151,   229,     0,   212,     0,     0,   228,   168,     0,     0,
     171,     0,     0,   242,   153,   230,     0,   231,   154,   155,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   175,     0,     0,   190,     0,     0,     0,
     176,     0,     0,   191,     0,     0,   195,     0,     0,     0,
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
      61,    62,    63,    61,    56,    63,    65,    61,    65,   317,
     317,    61,    61,   495,     5,     7,     7,    10,     9,     3,
      15,    48,     0,     3,     8,     7,    18,    19,     8,     3,
      11,    58,    59,   132,     8,     7,    17,    18,    19,    79,
      80,    22,    23,    79,    80,     3,     3,    39,    40,    41,
       8,     8,    44,    45,    46,     7,    48,     7,    39,    40,
      41,    42,    43,    24,     6,    57,    47,    48,    60,    61,
      62,    63,    64,    65,    19,    20,    21,    69,    70,     7,
      19,    20,    21,     7,    76,    66,    67,    69,    49,     7,
      51,    52,   132,    54,    55,    56,    49,    78,    12,    13,
      81,     3,    16,    48,    49,   132,     8,    88,    89,    48,
       7,    92,   107,    49,    50,    51,    52,    53,     3,     3,
     113,     6,     3,    68,     8,     3,   119,   120,    67,     4,
       8,     7,    71,    72,    73,    74,    75,     7,    77,   132,
     132,   132,   133,   134,   135,     3,     3,    24,     7,     6,
       8,   132,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,   115,     8,   117,   118,   109,   110,   111,   112,
       3,   132,    49,    82,    83,    84,    85,    86,    87,   132,
       3,     3,     8,     3,     3,     8,     8,   132,     8,     8,
       3,     3,   135,   132,     6,     8,   132,   679,     4,   507,
     507,    93,    94,    95,    96,    97,    98,    99,   100,   101,
     102,   103,   104,   105,   106,     3,     3,     3,     3,     3,
     288,     8,     8,     8,     8,     3,     3,   279,   280,     4,
       8,     8,    71,    72,    73,    74,    25,    26,    27,    28,
     132,     4,     3,     8,   317,     6,    14,    15,     4,   317,
      90,    91,     4,     4,     4,   132,   317,     4,     4,   317,
       4,   331,     4,   331,     4,     4,     3,   335,     4,     3,
     331,   132,     4,   331,   335,     8,     4,   331,     4,   347,
       4,   331,   331,     4,     4,     4,   347,   360,   356,   347,
       4,     4,   360,     4,     4,     4,     4,   135,   135,     4,
       4,   360,   133,   360,   133,   133,   133,     4,     4,     4,
       4,   379,   121,   122,   123,   124,   125,   126,   127,   128,
     129,   130,   131,     4,     4,     4,   133,     4,     4,     4,
       4,   135,     4,     4,   386,   387,     4,     4,     4,     4,
       4,   133,   135,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
     133,     4,     4,     4,   135,     4,   135,     4,     4,   135,
       4,     4,     4,   133,   133,   133,     4,     4,   135,     4,
     135,   135,     4,     4,     7,     3,   135,     7,     7,   132,
       7,     7,     5,     5,     5,     5,     5,     5,   114,   441,
       7,     7,     7,     5,     8,   132,     5,   132,     5,   132,
     132,     7,     7,   465,   132,   132,   489,   490,     7,     7,
     132,   489,   490,     7,     7,   132,   132,     4,     7,   132,
     482,   499,   132,   132,   507,     7,     4,     4,     4,   507,
     132,   132,   132,   132,   132,   132,   507,   132,   132,   507,
     132,    77,     4,     4,   132,     3,     6,     6,     3,   132,
       6,     3,   132,   132,   108,     6,     3,     6,     4,   132,
     132,     4,     4,     4,     4,     4,     3,     3,     6,   445,
       4,     4,     4,     8,     4,     4,     4,     4,     4,     4,
       4,     3,   132,     6,   132,     5,     7,   132,     4,     8,
       8,     8,   133,   133,     4,     4,   135,     5,     4,   133,
       7,   310,   288,   483,   487,   315,   665,   677,   133,   133,
     683,   490,   681,   690,   670,   668,   331,   363,   673,   671,
     133,   356,   133,   133,   674,   133,   116,   676,   132,   132,
     132,   132,   132,   360,   701,   132,   132,   132,   703,   347,
     132,   704,   133,   335,   132,   706,   132,   694,   507,   499,
     651,   379,   775,   791,   803,   810,    -1,    -1,    -1,    -1,
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
       7,   185,     7,   257,     7,   326,     7,   340,     7,   285,
       7,   309,     7,   233,     7,   390,   157,   152,   166,   172,
     186,   258,   327,   341,   286,   310,   234,   391,   149,   158,
     159,   132,   154,   155,    10,   113,   119,   120,   132,   164,
     167,   168,   169,   417,   419,   421,    11,    17,    18,    19,
      22,    23,    39,    40,    41,    42,    43,    47,    48,    66,
      67,    78,    81,    88,    89,    92,   164,   173,   174,   175,
     176,   177,   178,   179,   180,   181,   193,   195,   219,   227,
     241,   251,   279,   303,   345,   369,   379,   380,   388,    12,
      13,    16,   183,   184,   187,   189,   192,     7,    44,    45,
      46,    57,    60,    61,    62,    63,    64,    65,    69,    70,
      76,   164,   175,   176,   177,   180,   259,   260,   261,   263,
     265,   267,   269,   271,   273,   275,   277,   278,   303,   320,
     334,   345,   365,    58,    59,   164,   303,   328,   329,   330,
     332,    20,    21,    67,    71,    72,    73,    74,    75,    77,
     164,   303,   342,   343,   344,   345,   347,   349,   351,   353,
     355,   357,   359,   361,   363,    24,    49,    51,    52,    54,
      55,    56,   164,   209,   287,   288,   289,   290,   291,   292,
     293,   295,   297,   299,   300,   302,    50,    53,   164,   209,
     291,   297,   311,   312,   313,   314,   315,   317,   318,   319,
      79,    80,   164,   235,   236,   237,   239,    93,    94,    95,
      96,    97,    98,    99,   100,   101,   102,   103,   104,   105,
     106,   164,   392,   393,   394,   395,   397,   399,   400,   402,
     403,   404,   407,   409,   410,   411,   412,   415,     6,     3,
       4,     8,     3,   170,   422,   418,   420,     4,     3,     8,
     182,     4,     4,   346,   194,   196,     4,     4,     4,     4,
     252,   280,   304,   220,   370,   228,   242,     4,   381,   389,
       3,     8,   188,   190,     4,     3,     8,   372,   264,   266,
     268,   321,   262,   270,   272,     4,     4,   276,   274,   335,
     366,     3,     8,   331,   333,     3,     8,   348,   350,   364,
     354,   356,   360,   358,   362,   352,     8,     3,   294,   210,
       4,   298,   296,   301,     4,     8,     3,   316,     4,     8,
       3,   238,   240,     3,     8,     4,   396,   398,     4,   401,
       4,     4,   405,   408,     4,     4,     4,   413,   416,     3,
       8,   149,   149,   132,     4,     4,     4,     4,   168,     4,
     135,   135,     4,     4,     4,   133,   133,   133,   133,     4,
       4,     4,     4,     4,     4,     4,   133,     4,     4,   174,
       4,     4,   135,   184,    68,   164,   209,   303,   345,   347,
     349,   373,   374,   375,   376,   377,     4,     4,     4,     4,
       4,     4,     4,   133,   135,     4,     4,     4,     4,   260,
       4,     4,   329,     4,     4,     4,     4,     4,     4,     4,
       4,     4,   344,     4,     4,   133,     4,     4,     4,   135,
     289,     4,   135,   313,     4,     4,   236,   135,     4,     4,
     133,     4,   133,   133,     4,     4,   135,   135,   135,     4,
       4,   393,     4,     7,     7,   149,   149,     7,   132,     7,
       7,     5,     5,     5,     5,     5,     5,     7,     7,     7,
       5,   160,    14,    15,   191,   378,     8,     3,   132,   132,
     132,     5,   132,   132,   132,   132,   132,     5,     7,   132,
     151,   153,   132,   132,   160,   132,   132,   132,   132,   132,
     132,   132,   132,   132,   132,   132,   132,   132,   149,   132,
     132,   132,    15,   107,   406,   108,   109,   110,   111,   112,
     135,   414,   132,   149,   173,   114,   423,   424,   425,   183,
      24,    29,    30,    31,    32,    33,    34,    35,    36,    37,
      38,   164,   197,   198,   199,   202,   204,   206,   208,   209,
     211,   212,   213,   214,   215,   217,   197,     7,   253,   254,
     255,     7,   281,   282,   283,     7,   305,   306,   307,    71,
      72,    73,    74,   221,   222,   223,   224,   225,   226,   273,
     371,     7,   229,   230,   231,    82,    83,    84,    85,    86,
      87,   243,   244,   245,   246,   247,   248,   249,   250,    90,
      91,   382,   383,   384,   386,   392,   161,     4,   375,     7,
     322,   323,   324,     7,   336,   337,   338,    77,   367,     8,
     426,     3,     8,     8,   200,   203,   205,   207,     4,     4,
       4,     4,     4,   216,   218,     3,     8,     8,   256,     6,
       3,   284,     6,     3,   308,     6,     3,     3,     6,     3,
       6,   232,     6,     3,     4,     4,     4,     4,     4,     4,
       3,     8,   385,   387,     3,     8,     8,   132,   162,   163,
     132,   325,     6,     3,   339,     6,     3,   368,     8,     4,
     424,     4,     4,     4,     4,   133,   135,   133,   135,   133,
       4,     4,   198,   259,   255,   287,   283,   311,   307,   222,
     273,   235,   231,   133,   133,   133,   133,   133,   133,   244,
       4,     4,   383,     6,     3,   328,   324,   342,   338,     4,
       5,    25,    26,    27,    28,   201,   132,   132,   132,   132,
     132,     8,     8,     8,     8,   132,   132,   132,     8,     8,
     132,     7,   427,   428,   429,     3,     6,   115,   117,   118,
     164,   209,   430,   431,   432,   433,   435,   428,   436,     4,
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
     184,   186,   185,   188,   187,   190,   189,   191,   191,   192,
     194,   193,   196,   195,   197,   197,   198,   198,   198,   198,
     198,   198,   198,   198,   198,   198,   198,   198,   198,   200,
     199,   201,   201,   201,   201,   203,   202,   205,   204,   207,
     206,   208,   210,   209,   211,   212,   213,   214,   216,   215,
     218,   217,   220,   219,   221,   221,   222,   222,   222,   222,
     223,   224,   225,   226,   228,   227,   229,   229,   230,   230,
     232,   231,   234,   233,   235,   235,   235,   236,   236,   238,
     237,   240,   239,   242,   241,   243,   243,   244,   244,   244,
     244,   244,   244,   245,   246,   247,   248,   249,   250,   252,
     251,   253,   253,   254,   254,   256,   255,   258,   257,   259,
     259,   260,   260,   260,   260,   260,   260,   260,   260,   260,
     260,   260,   260,   260,   260,   260,   260,   260,   260,   260,
     260,   262,   261,   264,   263,   266,   265,   268,   267,   270,
     269,   272,   271,   274,   273,   276,   275,   277,   278,   280,
     279,   281,   281,   282,   282,   284,   283,   286,   285,   287,
     287,   288,   288,   289,   289,   289,   289,   289,   289,   289,
     289,   290,   291,   292,   294,   293,   296,   295,   298,   297,
     299,   301,   300,   302,   304,   303,   305,   305,   306,   306,
     308,   307,   310,   309,   311,   311,   312,   312,   313,   313,
     313,   313,   313,   313,   314,   316,   315,   317,   318,   319,
     321,   320,   322,   322,   323,   323,   325,   324,   327,   326,
     328,   328,   329,   329,   329,   329,   331,   330,   333,   332,
     335,   334,   336,   336,   337,   337,   339,   338,   341,   340,
     342,   342,   343,   343,   344,   344,   344,   344,   344,   344,
     344,   344,   344,   344,   344,   344,   346,   345,   348,   347,
     350,   349,   352,   351,   354,   353,   356,   355,   358,   357,
     360,   359,   362,   361,   364,   363,   366,   365,   368,   367,
     370,   369,   371,   371,   372,   273,   373,   373,   374,   374,
     375,   375,   375,   375,   375,   375,   375,   376,   378,   377,
     379,   381,   380,   382,   382,   383,   383,   385,   384,   387,
     386,   389,   388,   391,   390,   392,   392,   393,   393,   393,
     393,   393,   393,   393,   393,   393,   393,   393,   393,   393,
     393,   393,   394,   396,   395,   398,   397,   399,   401,   400,
     402,   403,   405,   404,   406,   406,   408,   407,   409,   410,
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
       1,     0,     4,     0,     4,     0,     4,     1,     1,     3,
       0,     6,     0,     6,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     0,
       4,     1,     1,     1,     1,     0,     4,     0,     4,     0,
       4,     3,     0,     4,     3,     3,     3,     3,     0,     4,
       0,     4,     0,     6,     1,     3,     1,     1,     1,     1,
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
       1,     1,     1,     1,     1,     1,     0,     4,     0,     4,
       0,     4,     0,     4,     0,     4,     0,     4,     0,     4,
       0,     4,     0,     4,     0,     4,     0,     6,     0,     4,
       0,     6,     1,     3,     0,     4,     0,     1,     1,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     0,     4,
       3,     0,     6,     1,     3,     1,     1,     0,     4,     0,
       4,     0,     6,     0,     4,     1,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     3,     0,     4,     0,     4,     3,     0,     4,
       3,     3,     0,     4,     1,     1,     0,     4,     3,     3,
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
  "\"raw\"", "\"udp\"", "\"re-detect\"", "\"echo-client-id\"",
  "\"match-client-id\"", "\"next-server\"", "\"server-hostname\"",
  "\"boot-file-name\"", "\"lease-database\"", "\"hosts-database\"",
  "\"type\"", "\"memfile\"", "\"mysql\"", "\"postgresql\"", "\"cql\"",
  "\"user\"", "\"password\"", "\"host\"", "\"port\"", "\"persist\"",
  "\"lfc-interval\"", "\"readonly\"", "\"connect-timeout\"",
  "\"contact-points\"", "\"keyspace\"", "\"valid-lifetime\"",
  "\"renew-timer\"", "\"rebind-timer\"", "\"decline-probation-period\"",
  "\"subnet4\"", "\"4o6-interface\"", "\"4o6-interface-id\"",
  "\"4o6-subnet\"", "\"option-def\"", "\"option-data\"", "\"name\"",
  "\"data\"", "\"code\"", "\"space\"", "\"csv-format\"",
  "\"record-types\"", "\"encapsulate\"", "\"array\"", "\"pools\"",
  "\"pool\"", "\"user-context\"", "\"subnet\"", "\"interface\"",
  "\"interface-id\"", "\"id\"", "\"rapid-commit\"", "\"reservation-mode\"",
  "\"host-reservation-identifiers\"", "\"client-classes\"", "\"test\"",
  "\"client-class\"", "\"reservations\"", "\"duid\"", "\"hw-address\"",
  "\"circuit-id\"", "\"client-id\"", "\"hostname\"", "\"relay\"",
  "\"ip-address\"", "\"hooks-libraries\"", "\"library\"", "\"parameters\"",
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
  "socket_type", "re_detect", "lease_database", "$@22", "hosts_database",
  "$@23", "database_map_params", "database_map_param", "database_type",
  "$@24", "db_type", "user", "$@25", "password", "$@26", "host", "$@27",
  "port", "name", "$@28", "persist", "lfc_interval", "readonly",
  "connect_timeout", "contact_points", "$@29", "keyspace", "$@30",
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
     460,   463,   463,   471,   471,   481,   481,   488,   489,   492,
     498,   498,   508,   508,   518,   519,   522,   523,   524,   525,
     526,   527,   528,   529,   530,   531,   532,   533,   534,   537,
     537,   544,   545,   546,   547,   550,   550,   558,   558,   566,
     566,   574,   579,   579,   587,   592,   597,   602,   607,   607,
     615,   615,   624,   624,   634,   635,   638,   639,   640,   641,
     644,   649,   654,   659,   664,   664,   674,   675,   678,   679,
     682,   682,   690,   690,   698,   699,   700,   703,   704,   707,
     707,   715,   715,   723,   723,   733,   734,   737,   738,   739,
     740,   741,   742,   745,   750,   755,   760,   765,   770,   778,
     778,   791,   792,   795,   796,   803,   803,   826,   826,   835,
     836,   840,   841,   842,   843,   844,   845,   846,   847,   848,
     849,   850,   851,   852,   853,   854,   855,   856,   857,   858,
     859,   862,   862,   870,   870,   878,   878,   886,   886,   894,
     894,   902,   902,   910,   910,   918,   918,   926,   931,   940,
     940,   952,   953,   956,   957,   962,   962,   973,   973,   983,
     984,   987,   988,   991,   992,   993,   994,   995,   996,   997,
     998,  1001,  1003,  1008,  1010,  1010,  1018,  1018,  1026,  1026,
    1034,  1036,  1036,  1044,  1053,  1053,  1065,  1066,  1071,  1072,
    1077,  1077,  1088,  1088,  1099,  1100,  1105,  1106,  1111,  1112,
    1113,  1114,  1115,  1116,  1119,  1121,  1121,  1129,  1131,  1133,
    1141,  1141,  1153,  1154,  1157,  1158,  1161,  1161,  1169,  1169,
    1177,  1178,  1181,  1182,  1183,  1184,  1187,  1187,  1195,  1195,
    1205,  1205,  1215,  1216,  1219,  1220,  1223,  1223,  1231,  1231,
    1239,  1240,  1243,  1244,  1248,  1249,  1250,  1251,  1252,  1253,
    1254,  1255,  1256,  1257,  1258,  1259,  1262,  1262,  1270,  1270,
    1278,  1278,  1286,  1286,  1294,  1294,  1302,  1302,  1310,  1310,
    1318,  1318,  1327,  1327,  1335,  1335,  1348,  1348,  1358,  1358,
    1369,  1369,  1379,  1380,  1383,  1383,  1391,  1392,  1395,  1396,
    1399,  1400,  1401,  1402,  1403,  1404,  1405,  1408,  1410,  1410,
    1422,  1429,  1429,  1439,  1440,  1443,  1444,  1447,  1447,  1455,
    1455,  1465,  1465,  1475,  1475,  1483,  1484,  1487,  1488,  1489,
    1490,  1491,  1492,  1493,  1494,  1495,  1496,  1497,  1498,  1499,
    1500,  1501,  1504,  1509,  1509,  1517,  1517,  1525,  1530,  1530,
    1538,  1543,  1548,  1548,  1556,  1557,  1560,  1560,  1568,  1573,
    1578,  1583,  1583,  1591,  1594,  1597,  1600,  1603,  1609,  1609,
    1619,  1619,  1626,  1626,  1638,  1638,  1651,  1652,  1656,  1660,
    1660,  1672,  1673,  1677,  1677,  1685,  1686,  1689,  1690,  1691,
    1692,  1693,  1696,  1701,  1701,  1709,  1709,  1719,  1720,  1723,
    1723,  1731,  1732,  1735,  1735
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
#line 1743 "dhcp4_parser.yy" // lalr1.cc:1168


void
isc::dhcp::Dhcp4Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
