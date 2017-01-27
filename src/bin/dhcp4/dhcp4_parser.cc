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
      case 147: // value
      case 151: // map_value
      case 189: // socket_type
      case 198: // db_type
      case 399: // ncr_protocol_value
      case 408: // replace_client_name_value
        value.move< ElementPtr > (that.value);
        break;

      case 133: // "boolean"
        value.move< bool > (that.value);
        break;

      case 132: // "floating point"
        value.move< double > (that.value);
        break;

      case 131: // "integer"
        value.move< int64_t > (that.value);
        break;

      case 130: // "constant string"
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
      case 147: // value
      case 151: // map_value
      case 189: // socket_type
      case 198: // db_type
      case 399: // ncr_protocol_value
      case 408: // replace_client_name_value
        value.copy< ElementPtr > (that.value);
        break;

      case 133: // "boolean"
        value.copy< bool > (that.value);
        break;

      case 132: // "floating point"
        value.copy< double > (that.value);
        break;

      case 131: // "integer"
        value.copy< int64_t > (that.value);
        break;

      case 130: // "constant string"
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
            case 130: // "constant string"

#line 205 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< std::string > (); }
#line 362 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 131: // "integer"

#line 205 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< int64_t > (); }
#line 369 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 132: // "floating point"

#line 205 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< double > (); }
#line 376 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 133: // "boolean"

#line 205 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< bool > (); }
#line 383 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 147: // value

#line 205 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 390 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 151: // map_value

#line 205 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 397 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 189: // socket_type

#line 205 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 404 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 198: // db_type

#line 205 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 411 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 399: // ncr_protocol_value

#line 205 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 418 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 408: // replace_client_name_value

#line 205 "dhcp4_parser.yy" // lalr1.cc:636
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
      case 147: // value
      case 151: // map_value
      case 189: // socket_type
      case 198: // db_type
      case 399: // ncr_protocol_value
      case 408: // replace_client_name_value
        yylhs.value.build< ElementPtr > ();
        break;

      case 133: // "boolean"
        yylhs.value.build< bool > ();
        break;

      case 132: // "floating point"
        yylhs.value.build< double > ();
        break;

      case 131: // "integer"
        yylhs.value.build< int64_t > ();
        break;

      case 130: // "constant string"
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
#line 214 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.NO_KEYWORD; }
#line 670 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 4:
#line 215 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.CONFIG; }
#line 676 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 6:
#line 216 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.DHCP4; }
#line 682 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 8:
#line 217 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.INTERFACES_CONFIG; }
#line 688 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 10:
#line 218 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.SUBNET4; }
#line 694 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 12:
#line 219 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.POOLS; }
#line 700 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 14:
#line 220 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.RESERVATIONS; }
#line 706 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 16:
#line 221 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.OPTION_DEF; }
#line 712 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 18:
#line 222 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.OPTION_DATA; }
#line 718 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 20:
#line 223 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.HOOKS_LIBRARIES; }
#line 724 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 22:
#line 224 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.DHCP_DDNS; }
#line 730 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 24:
#line 232 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 736 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 25:
#line 233 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as< double > (), ctx.loc2pos(yystack_[0].location))); }
#line 742 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 26:
#line 234 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 748 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 27:
#line 235 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 754 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 28:
#line 236 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 760 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 29:
#line 237 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 766 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 30:
#line 238 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 772 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 31:
#line 241 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as< ElementPtr > ());
}
#line 781 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 32:
#line 246 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 792 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 33:
#line 251 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 802 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 34:
#line 257 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 808 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 37:
#line 264 "dhcp4_parser.yy" // lalr1.cc:859
    {
                  // map containing a single entry
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 817 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 38:
#line 268 "dhcp4_parser.yy" // lalr1.cc:859
    {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 827 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 39:
#line 275 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 836 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 40:
#line 278 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // list parsing complete. Put any sanity checking here
}
#line 844 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 43:
#line 286 "dhcp4_parser.yy" // lalr1.cc:859
    {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 853 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 44:
#line 290 "dhcp4_parser.yy" // lalr1.cc:859
    {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 862 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 45:
#line 297 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // List parsing about to start
}
#line 870 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 46:
#line 299 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // list parsing complete. Put any sanity checking here
    //ctx.stack_.pop_back();
}
#line 879 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 49:
#line 308 "dhcp4_parser.yy" // lalr1.cc:859
    {
                          ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 888 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 50:
#line 312 "dhcp4_parser.yy" // lalr1.cc:859
    {
                          ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 897 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 51:
#line 323 "dhcp4_parser.yy" // lalr1.cc:859
    {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as< std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 908 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 52:
#line 333 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 919 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 53:
#line 338 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 929 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 61:
#line 357 "dhcp4_parser.yy" // lalr1.cc:859
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
#line 364 "dhcp4_parser.yy" // lalr1.cc:859
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
#line 374 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the Dhcp4 map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 964 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 64:
#line 378 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 972 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 88:
#line 411 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 981 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 89:
#line 416 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 990 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 90:
#line 421 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 999 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 91:
#line 426 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr dpp(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 1008 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 92:
#line 431 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr echo(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("echo-client-id", echo);
}
#line 1017 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 93:
#line 436 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr match(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("match-client-id", match);
}
#line 1026 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 94:
#line 442 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces-config", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.INTERFACES_CONFIG);
}
#line 1037 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 95:
#line 447 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1046 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 100:
#line 460 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1056 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 101:
#line 464 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1064 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 102:
#line 468 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1075 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 103:
#line 473 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1084 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 104:
#line 478 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.DHCP_SOCKET_TYPE);
}
#line 1092 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 105:
#line 480 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("dhcp-socket-type", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1101 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 106:
#line 485 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("raw", ctx.loc2pos(yystack_[0].location))); }
#line 1107 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 107:
#line 486 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("udp", ctx.loc2pos(yystack_[0].location))); }
#line 1113 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 108:
#line 489 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lease-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.LEASE_DATABASE);
}
#line 1124 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 109:
#line 494 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1133 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 110:
#line 499 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1144 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 111:
#line 504 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1153 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 125:
#line 526 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.DATABASE_TYPE);
}
#line 1161 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 126:
#line 528 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("type", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1170 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 127:
#line 533 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("memfile", ctx.loc2pos(yystack_[0].location))); }
#line 1176 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 128:
#line 534 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("mysql", ctx.loc2pos(yystack_[0].location))); }
#line 1182 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 129:
#line 535 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("postgresql", ctx.loc2pos(yystack_[0].location))); }
#line 1188 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 130:
#line 536 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("cql", ctx.loc2pos(yystack_[0].location))); }
#line 1194 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 131:
#line 539 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1202 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 132:
#line 541 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr user(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1212 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 133:
#line 547 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1220 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 134:
#line 549 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr pwd(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 1230 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 135:
#line 555 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1238 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 136:
#line 557 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr h(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 1248 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 137:
#line 563 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr p(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", p);
}
#line 1257 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 138:
#line 568 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1265 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 139:
#line 570 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1275 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 140:
#line 576 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 1284 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 141:
#line 581 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 1293 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 142:
#line 586 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 1302 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 143:
#line 591 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("connect-timeout", n);
}
#line 1311 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 144:
#line 596 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 1322 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 145:
#line 601 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1331 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 152:
#line 616 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1340 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 153:
#line 621 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 1349 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 154:
#line 626 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr circuit(new StringElement("circuit-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(circuit);
}
#line 1358 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 155:
#line 631 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr client(new StringElement("client-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(client);
}
#line 1367 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 156:
#line 636 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 1378 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 157:
#line 641 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1387 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 162:
#line 654 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1397 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 163:
#line 658 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1405 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 164:
#line 662 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1415 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 165:
#line 666 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1423 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 171:
#line 679 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1431 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 172:
#line 681 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr lib(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 1441 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 173:
#line 687 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1449 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 174:
#line 689 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1458 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 175:
#line 695 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.EXPIRED_LEASES_PROCESSING);
}
#line 1469 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 176:
#line 700 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1478 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 185:
#line 717 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 1487 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 186:
#line 722 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 1496 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 187:
#line 727 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 1505 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 188:
#line 732 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 1514 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 189:
#line 737 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 1523 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 190:
#line 742 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 1532 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 191:
#line 750 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet4", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET4);
}
#line 1543 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 192:
#line 755 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1552 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 197:
#line 775 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1562 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 198:
#line 779 "dhcp4_parser.yy" // lalr1.cc:859
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
#line 1585 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 199:
#line 798 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the subnet4 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1595 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 200:
#line 802 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1603 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 223:
#line 834 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1611 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 224:
#line 836 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr subnet(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 1621 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 225:
#line 842 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1629 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 226:
#line 844 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface", iface);
    ctx.leave();
}
#line 1639 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 227:
#line 850 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1647 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 228:
#line 852 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface-id", iface);
    ctx.leave();
}
#line 1657 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 229:
#line 858 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1665 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 230:
#line 860 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-subnet", iface);
    ctx.leave();
}
#line 1675 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 231:
#line 866 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1683 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 232:
#line 868 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 1693 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 233:
#line 874 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1701 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 234:
#line 876 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface-id", iface);
    ctx.leave();
}
#line 1711 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 235:
#line 882 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.CLIENT_CLASS);
}
#line 1719 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 236:
#line 884 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr cls(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 1729 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 237:
#line 890 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1737 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 238:
#line 892 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr rm(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservation-mode", rm);
    ctx.leave();
}
#line 1747 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 239:
#line 898 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr id(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 1756 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 240:
#line 903 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr rc(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rapid-commit", rc);
}
#line 1765 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 241:
#line 912 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 1776 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 242:
#line 917 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1785 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 247:
#line 934 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1795 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 248:
#line 938 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1803 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 249:
#line 945 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1813 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 250:
#line 949 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1821 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 264:
#line 975 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr code(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 1830 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 266:
#line 982 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1838 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 267:
#line 984 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 1848 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 268:
#line 990 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1856 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 269:
#line 992 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 1866 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 270:
#line 998 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1874 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 271:
#line 1000 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr space(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 1884 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 273:
#line 1008 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1892 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 274:
#line 1010 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr encap(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 1902 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 275:
#line 1016 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr array(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 1911 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 276:
#line 1025 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 1922 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 277:
#line 1030 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1931 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 282:
#line 1049 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1941 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 283:
#line 1053 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1949 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 284:
#line 1060 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1959 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 285:
#line 1064 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1967 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 297:
#line 1093 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1975 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 298:
#line 1095 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr data(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 1985 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 301:
#line 1105 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr space(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", space);
}
#line 1994 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 302:
#line 1113 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 2005 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 303:
#line 1118 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2014 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 308:
#line 1133 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2024 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 309:
#line 1137 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2032 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 310:
#line 1141 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2042 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 311:
#line 1145 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 2050 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 318:
#line 1159 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2058 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 319:
#line 1161 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr pool(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 2068 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 320:
#line 1167 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2076 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 321:
#line 1169 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("user-context", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2085 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 322:
#line 1177 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 2096 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 323:
#line 1182 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2105 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 328:
#line 1195 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2115 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 329:
#line 1199 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2123 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 330:
#line 1203 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2133 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 331:
#line 1207 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 2141 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 348:
#line 1234 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2149 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 349:
#line 1236 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr next_server(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("next-server", next_server);
    ctx.leave();
}
#line 2159 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 350:
#line 1242 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2167 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 351:
#line 1244 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr srv(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-hostname", srv);
    ctx.leave();
}
#line 2177 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 352:
#line 1250 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2185 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 353:
#line 1252 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr bootfile(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("boot-file-name", bootfile);
    ctx.leave();
}
#line 2195 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 354:
#line 1258 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2203 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 355:
#line 1260 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr addr(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", addr);
    ctx.leave();
}
#line 2213 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 356:
#line 1266 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2221 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 357:
#line 1268 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr d(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 2231 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 358:
#line 1274 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2239 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 359:
#line 1276 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 2249 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 360:
#line 1282 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2257 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 361:
#line 1284 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-id", hw);
    ctx.leave();
}
#line 2267 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 362:
#line 1290 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2275 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 363:
#line 1292 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("circuit-id", hw);
    ctx.leave();
}
#line 2285 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 364:
#line 1299 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2293 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 365:
#line 1301 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr host(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 2303 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 366:
#line 1307 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2314 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 367:
#line 1312 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2323 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 368:
#line 1320 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 2334 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 369:
#line 1325 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2343 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 370:
#line 1330 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2351 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 371:
#line 1332 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr ip(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", ip);
    ctx.leave();
}
#line 2361 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 372:
#line 1341 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 2372 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 373:
#line 1346 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2381 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 376:
#line 1355 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2391 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 377:
#line 1359 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2399 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 390:
#line 1382 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2407 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 391:
#line 1384 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr test(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 2417 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 392:
#line 1394 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 2426 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 393:
#line 1401 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 2437 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 394:
#line 1406 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2446 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 399:
#line 1419 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2454 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 400:
#line 1421 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr stype(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 2464 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 401:
#line 1427 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2472 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 402:
#line 1429 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 2482 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 403:
#line 1437 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 2493 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 404:
#line 1442 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2502 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 405:
#line 1447 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2512 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 406:
#line 1451 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 2520 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 425:
#line 1477 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 2529 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 426:
#line 1482 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2537 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 427:
#line 1484 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("qualifying-suffix", s);
    ctx.leave();
}
#line 2547 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 428:
#line 1490 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2555 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 429:
#line 1492 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 2565 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 430:
#line 1498 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 2574 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 431:
#line 1503 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2582 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 432:
#line 1505 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 2592 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 433:
#line 1511 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 2601 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 434:
#line 1516 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 2610 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 435:
#line 1521 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 2618 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 436:
#line 1523 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2627 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 437:
#line 1529 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 2633 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 438:
#line 1530 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 2639 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 439:
#line 1533 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NCR_FORMAT);
}
#line 2647 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 440:
#line 1535 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 2657 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 441:
#line 1541 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-include-fqdn", b);
}
#line 2666 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 442:
#line 1546 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("allow-client-update",  b);
}
#line 2675 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 443:
#line 1551 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-no-update", b);
}
#line 2684 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 444:
#line 1556 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-client-update", b);
}
#line 2693 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 445:
#line 1561 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 2701 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 446:
#line 1563 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("replace-client-name", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2710 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 447:
#line 1569 "dhcp4_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("when-present", ctx.loc2pos(yystack_[0].location))); 
      }
#line 2718 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 448:
#line 1572 "dhcp4_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location)));
      }
#line 2726 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 449:
#line 1575 "dhcp4_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("always", ctx.loc2pos(yystack_[0].location)));
      }
#line 2734 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 450:
#line 1578 "dhcp4_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("when-not-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 2742 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 451:
#line 1581 "dhcp4_parser.yy" // lalr1.cc:859
    {
      error(yystack_[0].location, "boolean values for the replace-client-name are "
                "no longer supported");
      }
#line 2751 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 452:
#line 1587 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2759 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 453:
#line 1589 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("generated-prefix", s);
    ctx.leave();
}
#line 2769 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 454:
#line 1597 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2777 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 455:
#line 1599 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("Dhcp6", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2786 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 456:
#line 1604 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2794 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 457:
#line 1606 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("DhcpDdns", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2803 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 458:
#line 1616 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Logging", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.LOGGING);
}
#line 2814 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 459:
#line 1621 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2823 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 463:
#line 1638 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 2834 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 464:
#line 1643 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2843 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 467:
#line 1655 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 2853 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 468:
#line 1659 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2861 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 476:
#line 1674 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr dl(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 2870 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 477:
#line 1678 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2878 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 478:
#line 1680 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 2888 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 479:
#line 1686 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 2899 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 480:
#line 1691 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2908 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 483:
#line 1700 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2918 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 484:
#line 1704 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2926 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 487:
#line 1712 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2934 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 488:
#line 1714 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 2944 "dhcp4_parser.cc" // lalr1.cc:859
    break;


#line 2948 "dhcp4_parser.cc" // lalr1.cc:859
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
      60,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,
    -473,  -473,    32,    19,    42,    51,    55,    57,    83,    98,
      99,   116,   126,   149,  -473,  -473,  -473,  -473,  -473,  -473,
    -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,
    -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,
    -473,  -473,  -473,  -473,  -473,  -473,    19,    38,    17,    29,
      25,    18,   -14,    68,    78,    62,   -33,   122,  -473,    77,
     173,   189,   169,   200,  -473,  -473,  -473,  -473,   203,  -473,
      31,  -473,  -473,  -473,  -473,  -473,  -473,   241,   245,  -473,
    -473,  -473,   246,   247,   255,   267,  -473,  -473,  -473,  -473,
    -473,  -473,  -473,   269,  -473,  -473,  -473,    45,  -473,  -473,
    -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,
    -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,
    -473,    49,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,
    -473,  -473,  -473,   270,   271,  -473,  -473,  -473,  -473,  -473,
    -473,  -473,  -473,  -473,   117,  -473,  -473,  -473,  -473,  -473,
    -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,
    -473,  -473,  -473,  -473,  -473,   150,  -473,  -473,  -473,  -473,
    -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,
     259,   274,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,
    -473,  -473,  -473,  -473,  -473,   276,  -473,  -473,  -473,   277,
    -473,  -473,   279,   275,  -473,  -473,  -473,  -473,  -473,  -473,
    -473,  -473,  -473,  -473,  -473,   280,  -473,  -473,  -473,  -473,
     281,   282,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,
    -473,   187,  -473,  -473,  -473,   288,  -473,  -473,   289,  -473,
     290,   295,  -473,  -473,   296,   302,   303,   304,  -473,  -473,
    -473,   188,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,
    -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,    19,
      19,  -473,   179,   307,   309,   310,   311,  -473,    17,  -473,
     312,   184,   185,   315,   316,   318,   192,   193,   195,   196,
     321,   324,   325,   326,   327,   328,   329,   204,   330,   332,
      29,  -473,   333,   334,    25,  -473,    76,   335,   336,   337,
     338,   339,   342,   343,   217,   216,   346,   347,   348,   349,
      18,  -473,   350,   351,   -14,  -473,   352,   353,   354,   355,
     356,   357,   358,   359,   360,  -473,    68,   361,   362,   237,
     363,   365,   366,   242,  -473,    78,   367,   243,  -473,    62,
     368,   369,    -6,  -473,   244,   370,   374,   248,   376,   250,
     251,   379,   380,   252,   253,   254,   256,   384,   386,   122,
    -473,  -473,  -473,   387,   385,   388,    19,    19,  -473,   389,
    -473,  -473,   264,   390,   391,  -473,  -473,  -473,  -473,   394,
     395,   396,   397,   398,   399,   400,  -473,   401,   402,  -473,
     405,    67,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,
     403,   409,  -473,  -473,  -473,   283,   284,   285,   411,   287,
     291,   293,  -473,  -473,   294,   298,   413,   412,  -473,   299,
     418,  -473,   300,   305,   405,   306,   308,   313,   317,   320,
     322,  -473,   323,   331,  -473,   340,   341,   344,  -473,  -473,
     345,  -473,  -473,   364,    19,  -473,  -473,   371,   372,  -473,
     373,  -473,  -473,    14,   314,  -473,  -473,  -473,  -473,    36,
     375,  -473,    19,    29,   377,  -473,  -473,    25,  -473,   132,
     132,   426,   427,   430,   186,    23,   432,    91,    11,   122,
    -473,  -473,  -473,  -473,  -473,   438,  -473,    76,  -473,  -473,
    -473,   439,  -473,  -473,  -473,  -473,  -473,   441,   319,  -473,
    -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,
    -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,
    -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,
    -473,  -473,  -473,  -473,   191,  -473,   194,  -473,  -473,   197,
    -473,  -473,  -473,  -473,   447,   450,   451,   453,   454,  -473,
     201,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,
    -473,  -473,   224,  -473,   456,   442,  -473,  -473,   457,   461,
    -473,  -473,   459,   463,  -473,  -473,  -473,  -473,  -473,   151,
    -473,  -473,  -473,  -473,  -473,  -473,   257,  -473,   462,   464,
    -473,   465,   468,   469,   472,   473,   474,   225,  -473,  -473,
    -473,  -473,  -473,  -473,  -473,  -473,  -473,   226,  -473,  -473,
    -473,   228,   378,   381,  -473,  -473,   475,   476,  -473,  -473,
     477,   479,  -473,  -473,   452,  -473,   480,   377,  -473,  -473,
     481,   482,   483,   484,   382,   272,   383,   273,   392,   132,
    -473,  -473,    18,  -473,   426,    78,  -473,   427,    62,  -473,
     430,   186,  -473,    23,  -473,   -33,  -473,   432,   393,   404,
     406,   407,   408,   410,    91,  -473,   486,   487,    11,  -473,
    -473,  -473,   489,   490,  -473,   -14,  -473,   439,    68,  -473,
     441,   488,  -473,   491,  -473,   278,   414,   415,   416,  -473,
    -473,  -473,  -473,  -473,  -473,   232,  -473,   492,  -473,   496,
    -473,  -473,  -473,   236,  -473,  -473,  -473,  -473,  -473,  -473,
    -473,  -473,   417,   419,  -473,  -473,   420,   238,  -473,   498,
    -473,   421,   500,  -473,  -473,  -473,  -473,  -473,  -473,  -473,
    -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,
    -473,  -473,   258,  -473,   -13,   500,  -473,  -473,   493,  -473,
    -473,  -473,   239,  -473,  -473,  -473,  -473,  -473,   494,   422,
     495,   -13,  -473,   504,  -473,   424,  -473,   503,  -473,  -473,
     263,  -473,   428,   503,  -473,  -473,   240,  -473,  -473,   508,
     428,  -473,   425,  -473,  -473
  };

  const unsigned short int
  Dhcp4Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     1,    39,    32,    28,    27,    24,
      25,    26,    31,     3,    29,    30,    52,     5,    63,     7,
     100,     9,   199,    11,   310,    13,   330,    15,   249,    17,
     284,    19,   164,    21,   405,    23,    41,    35,     0,     0,
       0,     0,     0,   332,   251,   286,     0,     0,    43,     0,
      42,     0,     0,    36,    61,   458,   454,   456,     0,    60,
       0,    54,    56,    58,    59,    57,    94,     0,     0,   348,
     108,   110,     0,     0,     0,     0,   191,   241,   276,   144,
     372,   156,   175,     0,   393,   403,    87,     0,    65,    67,
      68,    69,    70,    84,    85,    72,    73,    74,    75,    79,
      80,    71,    77,    78,    86,    76,    81,    82,    83,   102,
     104,     0,    96,    98,    99,   376,   225,   227,   229,   302,
     223,   231,   233,     0,     0,   237,   235,   322,   368,   222,
     203,   204,   205,   217,     0,   201,   208,   219,   220,   221,
     209,   210,   213,   215,   211,   212,   206,   207,   214,   218,
     216,   318,   320,   317,   315,     0,   312,   314,   316,   350,
     352,   366,   356,   358,   362,   360,   364,   354,   347,   343,
       0,   333,   334,   344,   345,   346,   340,   336,   341,   338,
     339,   342,   337,   266,   138,     0,   270,   268,   273,     0,
     262,   263,     0,   252,   253,   255,   265,   256,   257,   258,
     272,   259,   260,   261,   297,     0,   295,   296,   299,   300,
       0,   287,   288,   290,   291,   292,   293,   294,   171,   173,
     168,     0,   166,   169,   170,     0,   426,   428,     0,   431,
       0,     0,   435,   439,     0,     0,     0,     0,   445,   452,
     424,     0,   407,   409,   410,   411,   412,   413,   414,   415,
     416,   417,   418,   419,   420,   421,   422,   423,    40,     0,
       0,    33,     0,     0,     0,     0,     0,    51,     0,    53,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    64,     0,     0,     0,   101,   378,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   200,     0,     0,     0,   311,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   331,     0,     0,     0,     0,
       0,     0,     0,     0,   250,     0,     0,     0,   285,     0,
       0,     0,     0,   165,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     406,    44,    37,     0,     0,     0,     0,     0,    55,     0,
      92,    93,     0,     0,     0,    88,    89,    90,    91,     0,
       0,     0,     0,     0,     0,     0,   392,     0,     0,    66,
       0,     0,    97,   390,   388,   389,   384,   385,   386,   387,
       0,   379,   380,   382,   383,     0,     0,     0,     0,     0,
       0,     0,   239,   240,     0,     0,     0,     0,   202,     0,
       0,   313,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   335,     0,     0,   264,     0,     0,     0,   275,   254,
       0,   301,   289,     0,     0,   167,   425,     0,     0,   430,
       0,   433,   434,     0,     0,   441,   442,   443,   444,     0,
       0,   408,     0,     0,     0,   455,   457,     0,   349,     0,
       0,   193,   243,   278,     0,     0,   158,     0,     0,     0,
      45,   103,   106,   107,   105,     0,   377,     0,   226,   228,
     230,   304,   224,   232,   234,   238,   236,   324,     0,   319,
      34,   321,   351,   353,   367,   357,   359,   363,   361,   365,
     355,   267,   139,   271,   269,   274,   298,   172,   174,   427,
     429,   432,   437,   438,   436,   440,   447,   448,   449,   450,
     451,   446,   453,    38,     0,   463,     0,   460,   462,     0,
     125,   131,   133,   135,     0,     0,     0,     0,     0,   124,
       0,   112,   114,   115,   116,   117,   118,   119,   120,   121,
     122,   123,     0,   197,     0,   194,   195,   247,     0,   244,
     245,   282,     0,   279,   280,   152,   153,   154,   155,     0,
     146,   148,   149,   150,   151,   374,     0,   162,     0,   159,
     160,     0,     0,     0,     0,     0,     0,     0,   177,   179,
     180,   181,   182,   183,   184,   399,   401,     0,   395,   397,
     398,     0,    47,     0,   381,   308,     0,   305,   306,   328,
       0,   325,   326,   370,     0,    62,     0,     0,   459,    95,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     109,   111,     0,   192,     0,   251,   242,     0,   286,   277,
       0,     0,   145,     0,   373,     0,   157,     0,     0,     0,
       0,     0,     0,     0,     0,   176,     0,     0,     0,   394,
     404,    49,     0,    48,   391,     0,   303,     0,   332,   323,
       0,     0,   369,     0,   461,     0,     0,     0,     0,   137,
     140,   141,   142,   143,   113,     0,   196,     0,   246,     0,
     281,   147,   375,     0,   161,   185,   186,   187,   188,   189,
     190,   178,     0,     0,   396,    46,     0,     0,   307,     0,
     327,     0,     0,   127,   128,   129,   130,   126,   132,   134,
     136,   198,   248,   283,   163,   400,   402,    50,   309,   329,
     371,   467,     0,   465,     0,     0,   464,   479,     0,   477,
     475,   471,     0,   469,   473,   474,   472,   466,     0,     0,
       0,     0,   468,     0,   476,     0,   470,     0,   478,   483,
       0,   481,     0,     0,   480,   487,     0,   485,   482,     0,
       0,   484,     0,   486,   488
  };

  const short int
  Dhcp4Parser::yypgoto_[] =
  {
    -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,
    -473,  -473,  -473,   -42,  -473,    40,  -473,  -473,  -473,  -473,
    -473,  -473,  -473,  -473,    71,  -473,  -473,  -473,   -58,  -473,
    -473,  -473,   229,  -473,  -473,  -473,  -473,    33,   208,   -60,
     -44,   -40,  -473,  -473,   -39,  -473,  -473,    34,   205,  -473,
    -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,
      30,  -137,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,
    -473,  -473,   -63,  -473,  -473,  -473,  -473,  -473,  -473,  -473,
    -473,  -146,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,
    -151,  -473,  -473,  -473,  -148,   166,  -473,  -473,  -473,  -473,
    -473,  -473,  -473,  -155,  -473,  -473,  -473,  -473,  -473,  -473,
    -473,  -473,  -473,  -473,  -134,  -473,  -473,  -473,  -131,   202,
    -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,
    -473,  -473,  -472,  -473,  -473,  -473,  -473,  -473,  -473,  -473,
    -473,  -473,  -133,  -473,  -473,  -473,  -132,  -473,   181,  -473,
     -49,  -473,  -473,  -473,  -473,  -473,   -47,  -473,  -473,  -473,
    -473,  -473,   -51,  -473,  -473,  -473,  -130,  -473,  -473,  -473,
    -125,  -473,   198,  -473,  -473,  -473,  -473,  -473,  -473,  -473,
    -473,  -473,  -473,  -149,  -473,  -473,  -473,  -143,   222,  -473,
    -473,  -473,  -473,  -473,  -473,  -473,  -473,  -142,  -473,  -473,
    -473,  -139,  -473,   214,   -48,  -473,  -297,  -473,  -296,  -473,
    -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,
    -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,
    -473,  -473,  -473,  -473,    54,  -473,  -473,  -473,  -473,  -473,
    -473,  -473,  -126,  -473,  -473,  -473,  -473,  -473,  -473,  -473,
    -473,    64,   190,  -473,  -473,  -473,  -473,  -473,  -473,  -473,
    -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,
    -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,
    -473,  -473,  -473,  -473,   -83,  -473,  -473,  -473,  -200,  -473,
    -473,  -215,  -473,  -473,  -473,  -473,  -473,  -473,  -226,  -473,
    -473,  -232,  -473
  };

  const short int
  Dhcp4Parser::yydefgoto_[] =
  {
      -1,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    32,    33,    34,    57,   521,    72,    73,
      35,    56,    69,    70,   501,   632,   692,   693,   106,    37,
      58,    80,    81,    82,   283,    39,    59,   107,   108,   109,
     110,   111,   112,   113,   114,   115,   290,   131,   132,    41,
      60,   133,   312,   134,   313,   504,   116,   294,   117,   295,
     570,   571,   572,   650,   747,   573,   651,   574,   652,   575,
     653,   576,   211,   348,   578,   579,   580,   581,   118,   303,
     599,   600,   601,   602,   603,   604,   119,   305,   608,   609,
     610,   675,    53,    66,   241,   242,   243,   360,   244,   361,
     120,   306,   617,   618,   619,   620,   621,   622,   623,   624,
     121,   300,   584,   585,   586,   662,    43,    61,   154,   155,
     156,   321,   157,   317,   158,   318,   159,   319,   160,   322,
     161,   323,   162,   327,   163,   326,   164,   165,   122,   301,
     588,   589,   590,   665,    49,    64,   212,   213,   214,   215,
     216,   217,   218,   347,   219,   351,   220,   350,   221,   222,
     352,   223,   123,   302,   592,   593,   594,   668,    51,    65,
     230,   231,   232,   233,   234,   356,   235,   236,   237,   167,
     320,   636,   637,   638,   695,    45,    62,   175,   176,   177,
     332,   178,   333,   168,   328,   640,   641,   642,   698,    47,
      63,   190,   191,   192,   124,   293,   194,   336,   195,   337,
     196,   344,   197,   339,   198,   340,   199,   342,   200,   341,
     201,   343,   202,   338,   170,   329,   644,   701,   125,   304,
     606,   316,   420,   421,   422,   423,   424,   505,   126,   127,
     308,   627,   628,   629,   686,   630,   687,   128,   309,    55,
      67,   261,   262,   263,   264,   365,   265,   366,   266,   267,
     368,   268,   269,   270,   371,   544,   271,   372,   272,   273,
     274,   275,   276,   377,   551,   277,   378,    83,   285,    84,
     286,    85,   284,   556,   557,   558,   646,   762,   763,   764,
     772,   773,   774,   775,   780,   776,   778,   790,   791,   792,
     796,   797,   799
  };

  const unsigned short int
  Dhcp4Parser::yytable_[] =
  {
      79,   150,   227,   149,   173,   188,   210,   226,   240,   260,
     166,   174,   189,   169,    68,   193,   228,   151,   229,   418,
     419,   152,   153,   605,    25,   135,    26,    74,    27,   542,
     135,    98,    24,   204,   288,    88,    89,   129,   130,   289,
      86,   171,   172,   238,   239,    87,    88,    89,   310,    36,
      90,    91,   314,   311,    92,    93,    94,   315,    38,   136,
     137,   138,    40,    98,    42,    92,    93,    94,    95,    96,
     238,   239,   139,    97,    98,   140,   141,   142,   143,   144,
     145,   502,   503,   278,   146,   147,    89,   179,   180,   146,
      44,   148,    99,   100,    89,   179,   180,    78,   625,   626,
     767,   203,   768,   769,   101,    46,    48,   102,   204,   224,
     205,   206,   225,    98,   103,   104,    78,    78,   105,   543,
     330,    98,   204,    50,   204,   331,   205,   206,    75,   207,
     208,   209,   181,    52,    76,    77,   182,   183,   184,   185,
     186,   413,   187,   546,   547,   548,   549,    78,    78,    28,
      29,    30,    31,   334,   671,   560,    54,   672,   335,    78,
     561,   562,   563,   564,   565,   566,   567,   568,    71,   550,
     611,   612,   613,   614,   615,   616,   279,   281,   204,     1,
       2,     3,     4,     5,     6,     7,     8,     9,    10,    11,
     362,   379,    78,   280,   310,   363,   380,   647,    78,   645,
     314,   722,   648,   282,   659,   649,    78,   287,    78,   660,
     418,   419,   245,   246,   247,   248,   249,   250,   251,   252,
     253,   254,   255,   256,   257,   258,   259,   659,   684,   688,
      79,   379,   661,   685,   689,   330,   690,   381,   382,   362,
     751,   334,   781,   800,   754,   291,   758,   782,   801,   292,
     296,   297,    78,   415,   595,   596,   597,   598,   414,   298,
     673,   765,    78,   674,   766,   416,   793,   345,   417,   794,
     150,   299,   149,   307,   324,   325,   173,   346,   355,   166,
     349,   353,   169,   174,   357,   359,   151,   354,   188,   358,
     152,   153,   364,   367,   369,   189,   227,   210,   193,   370,
     373,   226,   743,   744,   745,   746,   374,   375,   376,   383,
     228,   384,   229,   385,   386,   387,   389,   390,   391,   392,
     393,   260,   394,   395,   396,   399,   397,   398,   400,   401,
     402,   403,   404,   405,   407,   406,   408,   410,   411,   425,
     426,   427,   428,   429,   485,   486,   430,   431,   432,   433,
     434,   435,   436,   437,   439,   440,   442,   443,   444,   445,
     446,   447,   448,   449,   450,   452,   453,   455,   454,   456,
     457,   460,   463,   464,   467,   458,   461,   466,   468,   469,
     470,   471,   472,   473,   474,   475,   476,   477,   479,   478,
     480,   482,   483,   643,   488,   484,   487,   489,   490,   491,
     492,   493,   494,   495,   496,   710,   712,   497,   498,   499,
     500,   506,   507,   508,   509,   510,   511,   512,   517,   518,
     545,   513,   538,   514,   515,    26,   577,   577,   516,   519,
     522,   569,   569,   583,   587,   523,   525,   591,   526,   607,
     553,   260,   633,   527,   415,   664,   635,   528,   639,   414,
     529,   654,   530,   531,   655,   656,   416,   657,   658,   417,
     702,   532,   663,   666,   667,   669,   670,   677,   676,   678,
     533,   534,   679,   680,   535,   536,   681,   682,   683,   697,
     520,   696,   700,   699,   703,   705,   706,   707,   708,   555,
     732,   733,   741,   736,   537,   735,   742,   779,   783,   785,
     752,   539,   540,   541,   753,   552,   759,   761,   691,   787,
     789,   694,   802,   709,   711,   524,   554,   388,   409,   412,
     582,   559,   714,   713,   725,   721,   724,   723,   465,   731,
     716,   715,   438,   717,   718,   726,   459,   727,   728,   729,
     720,   730,   795,   719,   748,   749,   750,   755,   738,   756,
     757,   760,   737,   784,   788,   804,   441,   462,   740,   739,
     451,   634,   734,   631,   704,   777,   786,   798,   803,   481,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   577,     0,     0,     0,
       0,   569,   150,     0,   149,   227,     0,   210,     0,     0,
     226,   166,     0,     0,   169,     0,     0,   240,   151,   228,
       0,   229,   152,   153,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   173,     0,     0,
     188,     0,     0,     0,   174,     0,     0,   189,     0,     0,
     193,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   771,     0,     0,     0,     0,   770,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   771,     0,
       0,     0,     0,   770
  };

  const short int
  Dhcp4Parser::yycheck_[] =
  {
      58,    61,    65,    61,    62,    63,    64,    65,    66,    67,
      61,    62,    63,    61,    56,    63,    65,    61,    65,   316,
     316,    61,    61,   495,     5,     7,     7,    10,     9,    15,
       7,    45,     0,    46,     3,    17,    18,    12,    13,     8,
      11,    55,    56,    76,    77,    16,    17,    18,     3,     7,
      21,    22,     3,     8,    36,    37,    38,     8,     7,    41,
      42,    43,     7,    45,     7,    36,    37,    38,    39,    40,
      76,    77,    54,    44,    45,    57,    58,    59,    60,    61,
      62,    14,    15,     6,    66,    67,    18,    19,    20,    66,
       7,    73,    63,    64,    18,    19,    20,   130,    87,    88,
     113,    23,   115,   116,    75,     7,     7,    78,    46,    47,
      48,    49,    50,    45,    85,    86,   130,   130,    89,   105,
       3,    45,    46,     7,    46,     8,    48,    49,   111,    51,
      52,    53,    64,     7,   117,   118,    68,    69,    70,    71,
      72,    65,    74,   107,   108,   109,   110,   130,   130,   130,
     131,   132,   133,     3,     3,    23,     7,     6,     8,   130,
      28,    29,    30,    31,    32,    33,    34,    35,   130,   133,
      79,    80,    81,    82,    83,    84,     3,     8,    46,   119,
     120,   121,   122,   123,   124,   125,   126,   127,   128,   129,
       3,     3,   130,     4,     3,     8,     8,     3,   130,     8,
       3,   673,     8,     3,     3,     8,   130,     4,   130,     8,
     507,   507,    90,    91,    92,    93,    94,    95,    96,    97,
      98,    99,   100,   101,   102,   103,   104,     3,     3,     3,
     288,     3,     8,     8,     8,     3,     8,   279,   280,     3,
       8,     3,     3,     3,     8,     4,     8,     8,     8,     4,
       4,     4,   130,   316,    68,    69,    70,    71,   316,     4,
       3,     3,   130,     6,     6,   316,     3,     8,   316,     6,
     330,     4,   330,     4,     4,     4,   334,     3,     3,   330,
       4,     4,   330,   334,     4,     3,   330,     8,   346,     8,
     330,   330,     4,     4,     4,   346,   359,   355,   346,     4,
       4,   359,    24,    25,    26,    27,     4,     4,     4,   130,
     359,     4,   359,     4,     4,     4,     4,   133,   133,     4,
       4,   379,     4,   131,   131,     4,   131,   131,     4,     4,
       4,     4,     4,     4,     4,   131,     4,     4,     4,     4,
       4,     4,     4,     4,   386,   387,     4,     4,   131,   133,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,   131,     4,
       4,     4,     4,     4,     4,   133,   133,   133,     4,   131,
       4,   131,   131,     4,     4,   133,   133,   133,     4,   133,
       4,     4,     7,    74,   130,     7,     7,     7,     7,     5,
       5,     5,     5,     5,     5,   133,   133,     7,     7,     7,
       5,     8,     3,   130,   130,   130,     5,   130,     5,     7,
     106,   130,   464,   130,   130,     7,   489,   490,   130,   130,
     130,   489,   490,     7,     7,   130,   130,     7,   130,     7,
     482,   499,     4,   130,   507,     3,     7,   130,     7,   507,
     130,     4,   130,   130,     4,     4,   507,     4,     4,   507,
       8,   130,     6,     6,     3,     6,     3,     3,     6,     4,
     130,   130,     4,     4,   130,   130,     4,     4,     4,     3,
     440,     6,     3,     6,     4,     4,     4,     4,     4,   112,
       4,     4,     4,     3,   130,     6,     5,     4,     4,     4,
       8,   130,   130,   130,     8,   130,     8,     7,   130,     5,
       7,   130,     4,   131,   131,   444,   483,   288,   310,   314,
     490,   487,   659,   131,   131,   671,   677,   675,   362,   684,
     664,   662,   330,   665,   667,   131,   355,   131,   131,   131,
     670,   131,   114,   668,   130,   130,   130,   130,   697,   130,
     130,   130,   695,   131,   130,   130,   334,   359,   700,   698,
     346,   507,   688,   499,   647,   765,   781,   793,   800,   379,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   659,    -1,    -1,    -1,
      -1,   659,   662,    -1,   662,   668,    -1,   665,    -1,    -1,
     668,   662,    -1,    -1,   662,    -1,    -1,   675,   662,   668,
      -1,   668,   662,   662,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   695,    -1,    -1,
     698,    -1,    -1,    -1,   695,    -1,    -1,   698,    -1,    -1,
     698,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   764,    -1,    -1,    -1,    -1,   764,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   781,    -1,
      -1,    -1,    -1,   781
  };

  const unsigned short int
  Dhcp4Parser::yystos_[] =
  {
       0,   119,   120,   121,   122,   123,   124,   125,   126,   127,
     128,   129,   135,   136,   137,   138,   139,   140,   141,   142,
     143,   144,   145,   146,     0,     5,     7,     9,   130,   131,
     132,   133,   147,   148,   149,   154,     7,   163,     7,   169,
       7,   183,     7,   250,     7,   319,     7,   333,     7,   278,
       7,   302,     7,   226,     7,   383,   155,   150,   164,   170,
     184,   251,   320,   334,   279,   303,   227,   384,   147,   156,
     157,   130,   152,   153,    10,   111,   117,   118,   130,   162,
     165,   166,   167,   411,   413,   415,    11,    16,    17,    18,
      21,    22,    36,    37,    38,    39,    40,    44,    45,    63,
      64,    75,    78,    85,    86,    89,   162,   171,   172,   173,
     174,   175,   176,   177,   178,   179,   190,   192,   212,   220,
     234,   244,   272,   296,   338,   362,   372,   373,   381,    12,
      13,   181,   182,   185,   187,     7,    41,    42,    43,    54,
      57,    58,    59,    60,    61,    62,    66,    67,    73,   162,
     173,   174,   175,   178,   252,   253,   254,   256,   258,   260,
     262,   264,   266,   268,   270,   271,   296,   313,   327,   338,
     358,    55,    56,   162,   296,   321,   322,   323,   325,    19,
      20,    64,    68,    69,    70,    71,    72,    74,   162,   296,
     335,   336,   337,   338,   340,   342,   344,   346,   348,   350,
     352,   354,   356,    23,    46,    48,    49,    51,    52,    53,
     162,   206,   280,   281,   282,   283,   284,   285,   286,   288,
     290,   292,   293,   295,    47,    50,   162,   206,   284,   290,
     304,   305,   306,   307,   308,   310,   311,   312,    76,    77,
     162,   228,   229,   230,   232,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     162,   385,   386,   387,   388,   390,   392,   393,   395,   396,
     397,   400,   402,   403,   404,   405,   406,   409,     6,     3,
       4,     8,     3,   168,   416,   412,   414,     4,     3,     8,
     180,     4,     4,   339,   191,   193,     4,     4,     4,     4,
     245,   273,   297,   213,   363,   221,   235,     4,   374,   382,
       3,     8,   186,   188,     3,     8,   365,   257,   259,   261,
     314,   255,   263,   265,     4,     4,   269,   267,   328,   359,
       3,     8,   324,   326,     3,     8,   341,   343,   357,   347,
     349,   353,   351,   355,   345,     8,     3,   287,   207,     4,
     291,   289,   294,     4,     8,     3,   309,     4,     8,     3,
     231,   233,     3,     8,     4,   389,   391,     4,   394,     4,
       4,   398,   401,     4,     4,     4,     4,   407,   410,     3,
       8,   147,   147,   130,     4,     4,     4,     4,   166,     4,
     133,   133,     4,     4,     4,   131,   131,   131,   131,     4,
       4,     4,     4,     4,     4,     4,   131,     4,     4,   172,
       4,     4,   182,    65,   162,   206,   296,   338,   340,   342,
     366,   367,   368,   369,   370,     4,     4,     4,     4,     4,
       4,     4,   131,   133,     4,     4,     4,     4,   253,     4,
       4,   322,     4,     4,     4,     4,     4,     4,     4,     4,
       4,   337,     4,     4,   131,     4,     4,     4,   133,   282,
       4,   133,   306,     4,     4,   229,   133,     4,     4,   131,
       4,   131,   131,     4,     4,   133,   133,   133,   133,     4,
       4,   386,     4,     7,     7,   147,   147,     7,   130,     7,
       7,     5,     5,     5,     5,     5,     5,     7,     7,     7,
       5,   158,    14,    15,   189,   371,     8,     3,   130,   130,
     130,     5,   130,   130,   130,   130,   130,     5,     7,   130,
     149,   151,   130,   130,   158,   130,   130,   130,   130,   130,
     130,   130,   130,   130,   130,   130,   130,   130,   147,   130,
     130,   130,    15,   105,   399,   106,   107,   108,   109,   110,
     133,   408,   130,   147,   171,   112,   417,   418,   419,   181,
      23,    28,    29,    30,    31,    32,    33,    34,    35,   162,
     194,   195,   196,   199,   201,   203,   205,   206,   208,   209,
     210,   211,   194,     7,   246,   247,   248,     7,   274,   275,
     276,     7,   298,   299,   300,    68,    69,    70,    71,   214,
     215,   216,   217,   218,   219,   266,   364,     7,   222,   223,
     224,    79,    80,    81,    82,    83,    84,   236,   237,   238,
     239,   240,   241,   242,   243,    87,    88,   375,   376,   377,
     379,   385,   159,     4,   368,     7,   315,   316,   317,     7,
     329,   330,   331,    74,   360,     8,   420,     3,     8,     8,
     197,   200,   202,   204,     4,     4,     4,     4,     4,     3,
       8,     8,   249,     6,     3,   277,     6,     3,   301,     6,
       3,     3,     6,     3,     6,   225,     6,     3,     4,     4,
       4,     4,     4,     4,     3,     8,   378,   380,     3,     8,
       8,   130,   160,   161,   130,   318,     6,     3,   332,     6,
       3,   361,     8,     4,   418,     4,     4,     4,     4,   131,
     133,   131,   133,   131,   195,   252,   248,   280,   276,   304,
     300,   215,   266,   228,   224,   131,   131,   131,   131,   131,
     131,   237,     4,     4,   376,     6,     3,   321,   317,   335,
     331,     4,     5,    24,    25,    26,    27,   198,   130,   130,
     130,     8,     8,     8,     8,   130,   130,   130,     8,     8,
     130,     7,   421,   422,   423,     3,     6,   113,   115,   116,
     162,   206,   424,   425,   426,   427,   429,   422,   430,     4,
     428,     3,     8,     4,   131,     4,   425,     5,   130,     7,
     431,   432,   433,     3,     6,   114,   434,   435,   432,   436,
       3,     8,     4,   435,   130
  };

  const unsigned short int
  Dhcp4Parser::yyr1_[] =
  {
       0,   134,   136,   135,   137,   135,   138,   135,   139,   135,
     140,   135,   141,   135,   142,   135,   143,   135,   144,   135,
     145,   135,   146,   135,   147,   147,   147,   147,   147,   147,
     147,   148,   150,   149,   151,   152,   152,   153,   153,   155,
     154,   156,   156,   157,   157,   159,   158,   160,   160,   161,
     161,   162,   164,   163,   165,   165,   166,   166,   166,   166,
     166,   168,   167,   170,   169,   171,   171,   172,   172,   172,
     172,   172,   172,   172,   172,   172,   172,   172,   172,   172,
     172,   172,   172,   172,   172,   172,   172,   172,   173,   174,
     175,   176,   177,   178,   180,   179,   181,   181,   182,   182,
     184,   183,   186,   185,   188,   187,   189,   189,   191,   190,
     193,   192,   194,   194,   195,   195,   195,   195,   195,   195,
     195,   195,   195,   195,   195,   197,   196,   198,   198,   198,
     198,   200,   199,   202,   201,   204,   203,   205,   207,   206,
     208,   209,   210,   211,   213,   212,   214,   214,   215,   215,
     215,   215,   216,   217,   218,   219,   221,   220,   222,   222,
     223,   223,   225,   224,   227,   226,   228,   228,   228,   229,
     229,   231,   230,   233,   232,   235,   234,   236,   236,   237,
     237,   237,   237,   237,   237,   238,   239,   240,   241,   242,
     243,   245,   244,   246,   246,   247,   247,   249,   248,   251,
     250,   252,   252,   253,   253,   253,   253,   253,   253,   253,
     253,   253,   253,   253,   253,   253,   253,   253,   253,   253,
     253,   253,   253,   255,   254,   257,   256,   259,   258,   261,
     260,   263,   262,   265,   264,   267,   266,   269,   268,   270,
     271,   273,   272,   274,   274,   275,   275,   277,   276,   279,
     278,   280,   280,   281,   281,   282,   282,   282,   282,   282,
     282,   282,   282,   283,   284,   285,   287,   286,   289,   288,
     291,   290,   292,   294,   293,   295,   297,   296,   298,   298,
     299,   299,   301,   300,   303,   302,   304,   304,   305,   305,
     306,   306,   306,   306,   306,   306,   307,   309,   308,   310,
     311,   312,   314,   313,   315,   315,   316,   316,   318,   317,
     320,   319,   321,   321,   322,   322,   322,   322,   324,   323,
     326,   325,   328,   327,   329,   329,   330,   330,   332,   331,
     334,   333,   335,   335,   336,   336,   337,   337,   337,   337,
     337,   337,   337,   337,   337,   337,   337,   337,   339,   338,
     341,   340,   343,   342,   345,   344,   347,   346,   349,   348,
     351,   350,   353,   352,   355,   354,   357,   356,   359,   358,
     361,   360,   363,   362,   364,   364,   365,   266,   366,   366,
     367,   367,   368,   368,   368,   368,   368,   368,   368,   369,
     371,   370,   372,   374,   373,   375,   375,   376,   376,   378,
     377,   380,   379,   382,   381,   384,   383,   385,   385,   386,
     386,   386,   386,   386,   386,   386,   386,   386,   386,   386,
     386,   386,   386,   386,   386,   387,   389,   388,   391,   390,
     392,   394,   393,   395,   396,   398,   397,   399,   399,   401,
     400,   402,   403,   404,   405,   407,   406,   408,   408,   408,
     408,   408,   410,   409,   412,   411,   414,   413,   416,   415,
     417,   417,   418,   420,   419,   421,   421,   423,   422,   424,
     424,   425,   425,   425,   425,   425,   426,   428,   427,   430,
     429,   431,   431,   433,   432,   434,   434,   436,   435
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
       1,     1,     1,     1,     1,     0,     4,     1,     1,     1,
       1,     0,     4,     0,     4,     0,     4,     3,     0,     4,
       3,     3,     3,     3,     0,     6,     1,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     0,     6,     0,     1,
       1,     3,     0,     4,     0,     4,     1,     3,     1,     1,
       1,     0,     4,     0,     4,     0,     6,     1,     3,     1,
       1,     1,     1,     1,     1,     3,     3,     3,     3,     3,
       3,     0,     6,     0,     1,     1,     3,     0,     4,     0,
       4,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     0,     4,     0,     4,     0,     4,     0,
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
       0,     4,     0,     1,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     0,     4,
       0,     4,     0,     4,     0,     4,     0,     4,     0,     4,
       0,     4,     0,     4,     0,     4,     0,     4,     0,     6,
       0,     4,     0,     6,     1,     3,     0,     4,     0,     1,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       0,     4,     3,     0,     6,     1,     3,     1,     1,     0,
       4,     0,     4,     0,     6,     0,     4,     1,     3,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     3,     0,     4,     0,     4,
       3,     0,     4,     3,     3,     0,     4,     1,     1,     0,
       4,     3,     3,     3,     3,     0,     4,     1,     1,     1,
       1,     1,     0,     4,     0,     4,     0,     4,     0,     6,
       1,     3,     1,     0,     6,     1,     3,     0,     4,     1,
       3,     1,     1,     1,     1,     1,     3,     0,     4,     0,
       6,     1,     3,     0,     4,     1,     3,     0,     4
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
  "\"readonly\"", "\"connect-timeout\"", "\"valid-lifetime\"",
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
  "\"always-include-fqdn\"", "\"allow-client-update\"",
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
  "lfc_interval", "readonly", "connect_timeout",
  "host_reservation_identifiers", "$@29",
  "host_reservation_identifiers_list", "host_reservation_identifier",
  "duid_id", "hw_address_id", "circuit_id", "client_id", "hooks_libraries",
  "$@30", "hooks_libraries_list", "not_empty_hooks_libraries_list",
  "hooks_library", "$@31", "sub_hooks_library", "$@32", "hooks_params",
  "hooks_param", "library", "$@33", "parameters", "$@34",
  "expired_leases_processing", "$@35", "expired_leases_params",
  "expired_leases_param", "reclaim_timer_wait_time",
  "flush_reclaimed_timer_wait_time", "hold_reclaimed_time",
  "max_reclaim_leases", "max_reclaim_time", "unwarned_reclaim_cycles",
  "subnet4_list", "$@36", "subnet4_list_content", "not_empty_subnet4_list",
  "subnet4", "$@37", "sub_subnet4", "$@38", "subnet4_params",
  "subnet4_param", "subnet", "$@39", "subnet_4o6_interface", "$@40",
  "subnet_4o6_interface_id", "$@41", "subnet_4o6_subnet", "$@42",
  "interface", "$@43", "interface_id", "$@44", "client_class", "$@45",
  "reservation_mode", "$@46", "id", "rapid_commit", "option_def_list",
  "$@47", "option_def_list_content", "not_empty_option_def_list",
  "option_def_entry", "$@48", "sub_option_def", "$@49",
  "option_def_params", "not_empty_option_def_params", "option_def_param",
  "option_def_name", "code", "option_def_code", "option_def_type", "$@50",
  "option_def_record_types", "$@51", "space", "$@52", "option_def_space",
  "option_def_encapsulate", "$@53", "option_def_array", "option_data_list",
  "$@54", "option_data_list_content", "not_empty_option_data_list",
  "option_data_entry", "$@55", "sub_option_data", "$@56",
  "option_data_params", "not_empty_option_data_params",
  "option_data_param", "option_data_name", "option_data_data", "$@57",
  "option_data_code", "option_data_space", "option_data_csv_format",
  "pools_list", "$@58", "pools_list_content", "not_empty_pools_list",
  "pool_list_entry", "$@59", "sub_pool4", "$@60", "pool_params",
  "pool_param", "pool_entry", "$@61", "user_context", "$@62",
  "reservations", "$@63", "reservations_list",
  "not_empty_reservations_list", "reservation", "$@64", "sub_reservation",
  "$@65", "reservation_params", "not_empty_reservation_params",
  "reservation_param", "next_server", "$@66", "server_hostname", "$@67",
  "boot_file_name", "$@68", "ip_address", "$@69", "duid", "$@70",
  "hw_address", "$@71", "client_id_value", "$@72", "circuit_id_value",
  "$@73", "hostname", "$@74", "reservation_client_classes", "$@75",
  "relay", "$@76", "relay_map", "$@77", "client_classes", "$@78",
  "client_classes_list", "$@79", "client_class_params",
  "not_empty_client_class_params", "client_class_param",
  "client_class_name", "client_class_test", "$@80", "dhcp4o6_port",
  "control_socket", "$@81", "control_socket_params",
  "control_socket_param", "control_socket_type", "$@82",
  "control_socket_name", "$@83", "dhcp_ddns", "$@84", "sub_dhcp_ddns",
  "$@85", "dhcp_ddns_params", "dhcp_ddns_param", "enable_updates",
  "qualifying_suffix", "$@86", "server_ip", "$@87", "server_port",
  "sender_ip", "$@88", "sender_port", "max_queue_size", "ncr_protocol",
  "$@89", "ncr_protocol_value", "ncr_format", "$@90",
  "always_include_fqdn", "allow_client_update", "override_no_update",
  "override_client_update", "replace_client_name", "$@91",
  "replace_client_name_value", "generated_prefix", "$@92",
  "dhcp6_json_object", "$@93", "dhcpddns_json_object", "$@94",
  "logging_object", "$@95", "logging_params", "logging_param", "loggers",
  "$@96", "loggers_entries", "logger_entry", "$@97", "logger_params",
  "logger_param", "debuglevel", "severity", "$@98", "output_options_list",
  "$@99", "output_options_list_content", "output_entry", "$@100",
  "output_params", "output_param", "$@101", YY_NULLPTR
  };

#if PARSER4_DEBUG
  const unsigned short int
  Dhcp4Parser::yyrline_[] =
  {
       0,   214,   214,   214,   215,   215,   216,   216,   217,   217,
     218,   218,   219,   219,   220,   220,   221,   221,   222,   222,
     223,   223,   224,   224,   232,   233,   234,   235,   236,   237,
     238,   241,   246,   246,   257,   260,   261,   264,   268,   275,
     275,   282,   283,   286,   290,   297,   297,   304,   305,   308,
     312,   323,   333,   333,   345,   346,   350,   351,   352,   353,
     354,   357,   357,   374,   374,   382,   383,   388,   389,   390,
     391,   392,   393,   394,   395,   396,   397,   398,   399,   400,
     401,   402,   403,   404,   405,   406,   407,   408,   411,   416,
     421,   426,   431,   436,   442,   442,   452,   453,   456,   457,
     460,   460,   468,   468,   478,   478,   485,   486,   489,   489,
     499,   499,   509,   510,   513,   514,   515,   516,   517,   518,
     519,   520,   521,   522,   523,   526,   526,   533,   534,   535,
     536,   539,   539,   547,   547,   555,   555,   563,   568,   568,
     576,   581,   586,   591,   596,   596,   606,   607,   610,   611,
     612,   613,   616,   621,   626,   631,   636,   636,   646,   647,
     650,   651,   654,   654,   662,   662,   670,   671,   672,   675,
     676,   679,   679,   687,   687,   695,   695,   705,   706,   709,
     710,   711,   712,   713,   714,   717,   722,   727,   732,   737,
     742,   750,   750,   763,   764,   767,   768,   775,   775,   798,
     798,   807,   808,   812,   813,   814,   815,   816,   817,   818,
     819,   820,   821,   822,   823,   824,   825,   826,   827,   828,
     829,   830,   831,   834,   834,   842,   842,   850,   850,   858,
     858,   866,   866,   874,   874,   882,   882,   890,   890,   898,
     903,   912,   912,   924,   925,   928,   929,   934,   934,   945,
     945,   955,   956,   959,   960,   963,   964,   965,   966,   967,
     968,   969,   970,   973,   975,   980,   982,   982,   990,   990,
     998,   998,  1006,  1008,  1008,  1016,  1025,  1025,  1037,  1038,
    1043,  1044,  1049,  1049,  1060,  1060,  1071,  1072,  1077,  1078,
    1083,  1084,  1085,  1086,  1087,  1088,  1091,  1093,  1093,  1101,
    1103,  1105,  1113,  1113,  1125,  1126,  1129,  1130,  1133,  1133,
    1141,  1141,  1149,  1150,  1153,  1154,  1155,  1156,  1159,  1159,
    1167,  1167,  1177,  1177,  1187,  1188,  1191,  1192,  1195,  1195,
    1203,  1203,  1211,  1212,  1215,  1216,  1220,  1221,  1222,  1223,
    1224,  1225,  1226,  1227,  1228,  1229,  1230,  1231,  1234,  1234,
    1242,  1242,  1250,  1250,  1258,  1258,  1266,  1266,  1274,  1274,
    1282,  1282,  1290,  1290,  1299,  1299,  1307,  1307,  1320,  1320,
    1330,  1330,  1341,  1341,  1351,  1352,  1355,  1355,  1363,  1364,
    1367,  1368,  1371,  1372,  1373,  1374,  1375,  1376,  1377,  1380,
    1382,  1382,  1394,  1401,  1401,  1411,  1412,  1415,  1416,  1419,
    1419,  1427,  1427,  1437,  1437,  1447,  1447,  1455,  1456,  1459,
    1460,  1461,  1462,  1463,  1464,  1465,  1466,  1467,  1468,  1469,
    1470,  1471,  1472,  1473,  1474,  1477,  1482,  1482,  1490,  1490,
    1498,  1503,  1503,  1511,  1516,  1521,  1521,  1529,  1530,  1533,
    1533,  1541,  1546,  1551,  1556,  1561,  1561,  1569,  1572,  1575,
    1578,  1581,  1587,  1587,  1597,  1597,  1604,  1604,  1616,  1616,
    1629,  1630,  1634,  1638,  1638,  1650,  1651,  1655,  1655,  1663,
    1664,  1667,  1668,  1669,  1670,  1671,  1674,  1678,  1678,  1686,
    1686,  1696,  1697,  1700,  1700,  1708,  1709,  1712,  1712
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
#line 4008 "dhcp4_parser.cc" // lalr1.cc:1167
#line 1720 "dhcp4_parser.yy" // lalr1.cc:1168


void
isc::dhcp::Dhcp4Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
