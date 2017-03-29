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
      case 408: // ncr_protocol_value
      case 416: // replace_client_name_value
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
      case 408: // ncr_protocol_value
      case 416: // replace_client_name_value
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

      case 408: // ncr_protocol_value

#line 207 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 418 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 416: // replace_client_name_value

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
      case 408: // ncr_protocol_value
      case 416: // replace_client_name_value
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

  case 159:
#line 638 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1376 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 160:
#line 643 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 1385 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 161:
#line 648 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr circuit(new StringElement("circuit-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(circuit);
}
#line 1394 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 162:
#line 653 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr client(new StringElement("client-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(client);
}
#line 1403 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 163:
#line 658 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr flex_id(new StringElement("flex-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(flex_id);
}
#line 1412 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 164:
#line 663 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 1423 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 165:
#line 668 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1432 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 170:
#line 681 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1442 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 171:
#line 685 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1450 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 172:
#line 689 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1460 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 173:
#line 693 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1468 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 179:
#line 706 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1476 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 180:
#line 708 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr lib(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 1486 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 181:
#line 714 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1494 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 182:
#line 716 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1503 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 183:
#line 722 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.EXPIRED_LEASES_PROCESSING);
}
#line 1514 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 184:
#line 727 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1523 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 193:
#line 744 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 1532 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 194:
#line 749 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 1541 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 195:
#line 754 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 1550 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 196:
#line 759 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 1559 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 197:
#line 764 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 1568 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 198:
#line 769 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 1577 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 199:
#line 777 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet4", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET4);
}
#line 1588 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 200:
#line 782 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1597 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 205:
#line 802 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1607 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 206:
#line 806 "dhcp4_parser.yy" // lalr1.cc:859
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
#line 825 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the subnet4 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1640 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 208:
#line 829 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1648 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 231:
#line 861 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1656 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 232:
#line 863 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr subnet(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 1666 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 233:
#line 869 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1674 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 234:
#line 871 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface", iface);
    ctx.leave();
}
#line 1684 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 235:
#line 877 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1692 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 236:
#line 879 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface-id", iface);
    ctx.leave();
}
#line 1702 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 237:
#line 885 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1710 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 238:
#line 887 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-subnet", iface);
    ctx.leave();
}
#line 1720 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 239:
#line 893 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1728 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 240:
#line 895 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 1738 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 241:
#line 901 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1746 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 242:
#line 903 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface-id", iface);
    ctx.leave();
}
#line 1756 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 243:
#line 909 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.CLIENT_CLASS);
}
#line 1764 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 244:
#line 911 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr cls(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 1774 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 245:
#line 917 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1782 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 246:
#line 919 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr rm(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservation-mode", rm);
    ctx.leave();
}
#line 1792 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 247:
#line 925 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr id(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 1801 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 248:
#line 930 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr rc(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rapid-commit", rc);
}
#line 1810 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 249:
#line 939 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 1821 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 250:
#line 944 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1830 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 255:
#line 961 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1840 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 256:
#line 965 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1848 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 257:
#line 972 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1858 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 258:
#line 976 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1866 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 272:
#line 1002 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr code(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 1875 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 274:
#line 1009 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1883 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 275:
#line 1011 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 1893 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 276:
#line 1017 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1901 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 277:
#line 1019 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 1911 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 278:
#line 1025 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1919 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 279:
#line 1027 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr space(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 1929 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 281:
#line 1035 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1937 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 282:
#line 1037 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr encap(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 1947 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 283:
#line 1043 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr array(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 1956 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 284:
#line 1052 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 1967 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 285:
#line 1057 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1976 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 290:
#line 1076 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1986 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 291:
#line 1080 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1994 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 292:
#line 1087 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2004 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 293:
#line 1091 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 2012 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 305:
#line 1120 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2020 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 306:
#line 1122 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr data(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 2030 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 309:
#line 1132 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr space(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", space);
}
#line 2039 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 310:
#line 1140 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 2050 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 311:
#line 1145 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2059 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 316:
#line 1160 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2069 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 317:
#line 1164 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2077 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 318:
#line 1168 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2087 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 319:
#line 1172 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 2095 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 326:
#line 1186 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2103 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 327:
#line 1188 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr pool(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 2113 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 328:
#line 1194 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2121 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 329:
#line 1196 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("user-context", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2130 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 330:
#line 1204 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 2141 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 331:
#line 1209 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2150 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 336:
#line 1222 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2160 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 337:
#line 1226 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2168 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 338:
#line 1230 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2178 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 339:
#line 1234 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 2186 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 357:
#line 1262 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2194 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 358:
#line 1264 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr next_server(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("next-server", next_server);
    ctx.leave();
}
#line 2204 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 359:
#line 1270 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2212 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 360:
#line 1272 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr srv(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-hostname", srv);
    ctx.leave();
}
#line 2222 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 361:
#line 1278 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2230 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 362:
#line 1280 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr bootfile(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("boot-file-name", bootfile);
    ctx.leave();
}
#line 2240 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 363:
#line 1286 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2248 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 364:
#line 1288 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr addr(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", addr);
    ctx.leave();
}
#line 2258 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 365:
#line 1294 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2266 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 366:
#line 1296 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr d(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 2276 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 367:
#line 1302 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2284 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 368:
#line 1304 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 2294 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 369:
#line 1310 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2302 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 370:
#line 1312 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-id", hw);
    ctx.leave();
}
#line 2312 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 371:
#line 1318 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2320 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 372:
#line 1320 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("circuit-id", hw);
    ctx.leave();
}
#line 2330 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 373:
#line 1326 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2338 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 374:
#line 1328 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flex-id", hw);
    ctx.leave();
}
#line 2348 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 375:
#line 1334 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2356 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 376:
#line 1336 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr host(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 2366 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 377:
#line 1342 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2377 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 378:
#line 1347 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2386 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 379:
#line 1355 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 2397 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 380:
#line 1360 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2406 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 381:
#line 1365 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2414 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 382:
#line 1367 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr ip(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", ip);
    ctx.leave();
}
#line 2424 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 383:
#line 1376 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 2435 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 384:
#line 1381 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2444 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 387:
#line 1390 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2454 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 388:
#line 1394 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2462 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 401:
#line 1417 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2470 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 402:
#line 1419 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr test(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 2480 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 403:
#line 1429 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 2489 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 404:
#line 1436 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 2500 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 405:
#line 1441 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2509 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 410:
#line 1454 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2517 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 411:
#line 1456 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr stype(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 2527 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 412:
#line 1462 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2535 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 413:
#line 1464 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 2545 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 414:
#line 1472 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 2556 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 415:
#line 1477 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2565 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 416:
#line 1482 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2575 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 417:
#line 1486 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 2583 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 435:
#line 1511 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 2592 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 436:
#line 1516 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2600 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 437:
#line 1518 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("qualifying-suffix", s);
    ctx.leave();
}
#line 2610 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 438:
#line 1524 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2618 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 439:
#line 1526 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 2628 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 440:
#line 1532 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 2637 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 441:
#line 1537 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2645 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 442:
#line 1539 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 2655 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 443:
#line 1545 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 2664 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 444:
#line 1550 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 2673 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 445:
#line 1555 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 2681 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 446:
#line 1557 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2690 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 447:
#line 1563 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 2696 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 448:
#line 1564 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 2702 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 449:
#line 1567 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NCR_FORMAT);
}
#line 2710 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 450:
#line 1569 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 2720 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 451:
#line 1575 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-include-fqdn", b);
}
#line 2729 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 452:
#line 1580 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-no-update", b);
}
#line 2738 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 453:
#line 1585 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-client-update", b);
}
#line 2747 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 454:
#line 1590 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 2755 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 455:
#line 1592 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("replace-client-name", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2764 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 456:
#line 1598 "dhcp4_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("when-present", ctx.loc2pos(yystack_[0].location))); 
      }
#line 2772 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 457:
#line 1601 "dhcp4_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location)));
      }
#line 2780 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 458:
#line 1604 "dhcp4_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("always", ctx.loc2pos(yystack_[0].location)));
      }
#line 2788 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 459:
#line 1607 "dhcp4_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("when-not-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 2796 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 460:
#line 1610 "dhcp4_parser.yy" // lalr1.cc:859
    {
      error(yystack_[0].location, "boolean values for the replace-client-name are "
                "no longer supported");
      }
#line 2805 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 461:
#line 1616 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2813 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 462:
#line 1618 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("generated-prefix", s);
    ctx.leave();
}
#line 2823 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 463:
#line 1626 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2831 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 464:
#line 1628 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("Dhcp6", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2840 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 465:
#line 1633 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2848 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 466:
#line 1635 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("DhcpDdns", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2857 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 467:
#line 1645 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Logging", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.LOGGING);
}
#line 2868 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 468:
#line 1650 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2877 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 472:
#line 1667 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 2888 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 473:
#line 1672 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2897 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 476:
#line 1684 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 2907 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 477:
#line 1688 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2915 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 485:
#line 1703 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr dl(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 2924 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 486:
#line 1708 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2932 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 487:
#line 1710 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 2942 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 488:
#line 1716 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 2953 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 489:
#line 1721 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2962 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 492:
#line 1730 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2972 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 493:
#line 1734 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2980 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 496:
#line 1742 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2988 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 497:
#line 1744 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 2998 "dhcp4_parser.cc" // lalr1.cc:859
    break;


#line 3002 "dhcp4_parser.cc" // lalr1.cc:859
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
    -473,  -473,    60,    19,    22,    57,    59,    68,    82,    84,
      86,    99,   124,   128,  -473,  -473,  -473,  -473,  -473,  -473,
    -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,
    -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,
    -473,  -473,  -473,  -473,  -473,  -473,    19,   -16,    17,    79,
     102,    18,    41,   109,   139,     1,   -25,   122,  -473,   142,
     173,   174,   187,   203,  -473,  -473,  -473,  -473,   200,  -473,
      29,  -473,  -473,  -473,  -473,  -473,  -473,   235,   244,  -473,
    -473,  -473,   245,   251,   258,   259,  -473,  -473,  -473,  -473,
    -473,  -473,  -473,   260,  -473,  -473,  -473,    30,  -473,  -473,
    -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,
    -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,
    -473,   155,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,
    -473,  -473,  -473,   262,   263,  -473,  -473,  -473,  -473,  -473,
    -473,  -473,  -473,  -473,   156,  -473,  -473,  -473,  -473,  -473,
    -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,
    -473,  -473,  -473,  -473,  -473,   158,  -473,  -473,  -473,  -473,
    -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,
    -473,   261,   205,  -473,  -473,  -473,  -473,  -473,  -473,  -473,
    -473,  -473,  -473,  -473,  -473,  -473,  -473,   269,  -473,  -473,
    -473,   270,  -473,  -473,   267,   274,  -473,  -473,  -473,  -473,
    -473,  -473,  -473,  -473,  -473,  -473,  -473,   276,  -473,  -473,
    -473,  -473,   273,   275,  -473,  -473,  -473,  -473,  -473,  -473,
    -473,  -473,  -473,   162,  -473,  -473,  -473,   280,  -473,  -473,
     281,  -473,   283,   287,  -473,  -473,   288,   289,   290,  -473,
    -473,  -473,   166,  -473,  -473,  -473,  -473,  -473,  -473,  -473,
    -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,    19,
      19,  -473,   163,   296,   297,   299,   300,  -473,    17,  -473,
     301,   171,   172,   304,   305,   306,   179,   181,   183,   184,
     311,   314,   315,   316,   329,   330,   331,   207,   332,   333,
      79,  -473,   334,   335,   102,  -473,    65,   337,   338,   339,
     340,   341,   342,   343,   215,   214,   348,   349,   350,   351,
      18,  -473,   352,   353,    41,  -473,   354,   355,   356,   357,
     358,   359,   360,   361,   362,   363,  -473,   109,   364,   365,
     237,   367,   368,   369,   240,  -473,   139,   370,   241,  -473,
       1,   373,   374,    44,  -473,   246,   375,   376,   250,   378,
     252,   254,   380,   382,   255,   256,   257,   384,   385,   122,
    -473,  -473,  -473,   389,   387,   388,    19,    19,  -473,   390,
    -473,  -473,   264,   391,   392,  -473,  -473,  -473,  -473,   395,
     396,   397,   398,   399,   400,   401,  -473,   402,   403,  -473,
     406,   132,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,
     404,   410,  -473,  -473,  -473,   282,   284,   285,   413,   291,
     292,   293,  -473,  -473,   298,   302,   414,   408,  -473,   303,
     415,  -473,   307,   308,   406,   310,   313,   318,   319,   320,
     321,   322,  -473,   323,   325,  -473,   326,   328,   336,  -473,
    -473,   344,  -473,  -473,   345,    19,  -473,  -473,   346,   347,
    -473,   366,  -473,  -473,    15,   312,  -473,  -473,  -473,    -1,
     371,  -473,    19,    79,   324,  -473,  -473,   102,  -473,    11,
      11,   421,   426,   429,    -3,    24,   430,   116,   170,   122,
    -473,  -473,  -473,  -473,  -473,   417,  -473,    65,  -473,  -473,
    -473,   436,  -473,  -473,  -473,  -473,  -473,   440,   386,  -473,
    -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,
    -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,
    -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,
    -473,  -473,  -473,  -473,  -473,   169,  -473,   188,  -473,  -473,
     204,  -473,  -473,  -473,  -473,   444,   457,   458,   460,   461,
    -473,  -473,  -473,   206,  -473,  -473,  -473,  -473,  -473,  -473,
    -473,  -473,  -473,  -473,  -473,  -473,  -473,   226,  -473,   463,
     464,  -473,  -473,   465,   467,  -473,  -473,   466,   470,  -473,
    -473,  -473,  -473,  -473,  -473,    70,  -473,  -473,  -473,  -473,
    -473,  -473,  -473,   136,  -473,   468,   472,  -473,   462,   476,
     477,   478,   479,   480,   228,  -473,  -473,  -473,  -473,  -473,
    -473,  -473,  -473,  -473,   229,  -473,  -473,  -473,   230,   372,
     377,  -473,  -473,   481,   482,  -473,  -473,   483,   485,  -473,
    -473,   484,  -473,   486,   324,  -473,  -473,   487,   489,   490,
     491,   379,   271,   381,   272,   383,   492,   493,    11,  -473,
    -473,    18,  -473,   421,   139,  -473,   426,     1,  -473,   429,
      -3,  -473,    24,  -473,   -25,  -473,   430,   393,   394,   405,
     407,   409,   411,   116,  -473,   495,   496,   170,  -473,  -473,
    -473,   499,   498,  -473,    41,  -473,   436,   109,  -473,   440,
     502,  -473,   497,  -473,    78,   416,   418,   419,  -473,  -473,
    -473,  -473,  -473,   420,   422,  -473,   232,  -473,   500,  -473,
     503,  -473,  -473,  -473,   239,  -473,  -473,  -473,  -473,  -473,
    -473,  -473,  -473,   423,   424,  -473,  -473,   425,   242,  -473,
     505,  -473,   427,   508,  -473,  -473,  -473,  -473,  -473,  -473,
    -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,
    -473,  -473,  -473,  -473,  -473,   182,  -473,    23,   508,  -473,
    -473,   506,  -473,  -473,  -473,   243,  -473,  -473,  -473,  -473,
    -473,   513,   412,   514,    23,  -473,   515,  -473,   428,  -473,
     512,  -473,  -473,   253,  -473,   431,   512,  -473,  -473,   249,
    -473,  -473,   517,   431,  -473,   432,  -473,  -473
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
       0,   487,   492,     0,   490,     0,     0,   489,   496,     0,
     494,   491,     0,     0,   493,     0,   495,   497
  };

  const short int
  Dhcp4Parser::yypgoto_[] =
  {
    -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,
    -473,  -473,  -473,   -36,  -473,    46,  -473,  -473,  -473,  -473,
    -473,  -473,  -473,  -473,    63,  -473,  -473,  -473,   -58,  -473,
    -473,  -473,   234,  -473,  -473,  -473,  -473,    40,   218,   -60,
     -44,   -42,  -473,  -473,   -40,  -473,  -473,    37,   211,  -473,
    -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,
      39,  -138,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,
    -473,  -473,   -63,  -473,  -473,  -473,  -473,  -473,  -473,  -473,
    -473,  -473,  -473,  -473,  -473,  -149,  -473,  -473,  -473,  -473,
    -473,  -473,  -473,  -473,  -473,  -154,  -473,  -473,  -473,  -151,
     176,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -159,  -473,
    -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -137,
    -473,  -473,  -473,  -136,   213,  -473,  -473,  -473,  -473,  -473,
    -473,  -473,  -473,  -473,  -473,  -473,  -473,  -472,  -473,  -473,
    -473,  -473,  -473,  -473,  -473,  -473,  -473,  -139,  -473,  -473,
    -473,  -133,  -473,   190,  -473,   -49,  -473,  -473,  -473,  -473,
    -473,   -47,  -473,  -473,  -473,  -473,  -473,   -51,  -473,  -473,
    -473,  -130,  -473,  -473,  -473,  -124,  -473,   198,  -473,  -473,
    -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -145,  -473,
    -473,  -473,  -142,   231,  -473,  -473,  -473,  -473,  -473,  -473,
    -473,  -473,  -146,  -473,  -473,  -473,  -141,  -473,   220,   -48,
    -473,  -302,  -473,  -294,  -473,  -473,  -473,  -473,  -473,  -473,
    -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,
    -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,
    -473,    61,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -128,
    -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,    71,   192,
    -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,
    -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,
    -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,
     -82,  -473,  -473,  -473,  -205,  -473,  -473,  -220,  -473,  -473,
    -473,  -473,  -473,  -473,  -231,  -473,  -473,  -237,  -473
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
     793,   789,   791,   803,   804,   805,   809,   810,   812
  };

  const unsigned short int
  Dhcp4Parser::yytable_[] =
  {
      79,   150,   229,   149,   173,   189,   212,   228,   242,   261,
     166,   174,   190,   169,   418,   194,   230,   151,   231,   152,
      68,   153,   419,   612,    25,   135,    26,    74,    27,    36,
     543,   135,   288,   310,   561,    88,    89,   289,   311,   562,
     563,   564,   565,   566,   567,   568,   569,   570,   571,   206,
     226,   207,   208,   227,   240,   241,    92,    93,    94,   206,
      24,   136,   137,   138,    38,    98,    40,   600,   601,   602,
     603,   206,   604,   680,   139,    42,   681,   140,   141,   142,
     143,   144,   145,    89,   179,   180,   146,   147,    98,    44,
      86,    46,   146,    48,   148,    87,    88,    89,   171,   172,
      90,    91,   754,   755,   756,   757,    50,    78,   547,   548,
     549,   550,    98,   206,   129,   130,    71,    92,    93,    94,
      95,    96,   544,   240,   241,    97,    98,    89,   179,   180,
      75,    52,   413,    78,   551,    54,    76,    77,   780,   682,
     781,   782,   683,    78,    99,   100,   502,   503,   278,    78,
      78,    28,    29,    30,    31,    78,    98,   101,   314,   330,
     102,   334,   205,   315,   331,   363,   335,   103,   104,   379,
     364,   105,   310,    78,   380,   181,   279,   652,   280,   182,
     183,   184,   185,   186,   187,   778,   188,   206,   779,   207,
     208,   654,   209,   210,   211,   281,   655,    78,   618,   619,
     620,   621,   622,   623,   287,   418,   282,   314,   347,   668,
     733,    78,   656,   419,   669,   247,   248,   249,   250,   251,
     252,   253,   254,   255,   256,   257,   258,   259,   260,   668,
      79,   693,   697,   379,   670,   330,   694,   698,   699,   291,
     764,    78,   363,   381,   382,   334,   794,   767,   292,   296,
     771,   795,   813,   415,    78,   297,   806,   814,   414,   807,
     632,   633,   298,   299,   307,   416,   324,   325,   417,   346,
     150,    78,   149,   350,   354,   355,   173,   356,   360,   166,
     358,   359,   169,   174,   365,   368,   151,   370,   152,   189,
     153,   371,   374,   375,   376,   383,   190,   229,   212,   194,
     384,   385,   228,   386,   387,   389,   390,   391,   392,   393,
     394,   230,   395,   231,   396,   399,   397,   398,   400,   401,
     402,   261,     1,     2,     3,     4,     5,     6,     7,     8,
       9,    10,    11,   403,   404,   405,   407,   408,   410,   411,
     406,   425,   426,   427,   428,   429,   430,   431,   432,   433,
     485,   486,   434,   435,   436,   437,   439,   440,   442,   443,
     444,   445,   446,   447,   448,   449,   450,   451,   453,   454,
     455,   456,   457,   458,   461,   459,   462,   464,   465,   468,
     469,   467,   471,   470,   474,   472,   475,   473,   479,   480,
     476,   477,   478,   482,   483,   484,   488,   487,   489,   490,
     491,   492,   493,   494,   495,   496,   719,   721,   497,   498,
     499,   500,   506,   507,   508,   518,   509,   510,   511,   517,
     546,   640,    26,   512,   513,   514,   580,   580,   588,   539,
     515,   572,   572,   592,   516,   519,   596,   614,   556,   522,
     523,   261,   525,   642,   415,   526,   554,   646,   661,   414,
     527,   528,   529,   530,   531,   532,   416,   533,   534,   417,
     535,   662,   663,   650,   664,   665,   687,   673,   536,   672,
     676,   675,   678,   679,   685,   686,   537,   538,   540,   541,
     688,   689,   690,   691,   692,   706,   520,   705,   709,   708,
     712,   714,   711,   715,   716,   717,   723,   724,   542,   743,
     744,   747,   753,   553,   700,   746,   752,   524,   765,   703,
     792,   766,   718,   772,   720,   774,   722,   796,   798,   802,
     800,   815,   388,   555,   560,   412,   736,   737,   409,   587,
     725,   732,   735,   734,   742,   726,   727,   729,   738,   466,
     739,   728,   740,   438,   741,   797,   460,   808,   759,   731,
     760,   761,   762,   730,   763,   768,   769,   770,   463,   773,
     801,   749,   748,   751,   817,   441,   750,   452,   641,   745,
     638,   481,   713,   790,   799,   811,   816,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
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
      56,    61,   316,   495,     5,     7,     7,    10,     9,     7,
      15,     7,     3,     3,    23,    17,    18,     8,     8,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    48,
      49,    50,    51,    52,    79,    80,    38,    39,    40,    48,
       0,    43,    44,    45,     7,    47,     7,    70,    71,    72,
      73,    48,    75,     3,    56,     7,     6,    59,    60,    61,
      62,    63,    64,    18,    19,    20,    68,    69,    47,     7,
      11,     7,    68,     7,    76,    16,    17,    18,    57,    58,
      21,    22,    24,    25,    26,    27,     7,   132,   109,   110,
     111,   112,    47,    48,    12,    13,   132,    38,    39,    40,
      41,    42,   107,    79,    80,    46,    47,    18,    19,    20,
     113,     7,    67,   132,   135,     7,   119,   120,   115,     3,
     117,   118,     6,   132,    65,    66,    14,    15,     6,   132,
     132,   132,   133,   134,   135,   132,    47,    78,     3,     3,
      81,     3,    23,     8,     8,     3,     8,    88,    89,     3,
       8,    92,     3,   132,     8,    66,     3,     8,     4,    70,
      71,    72,    73,    74,    75,     3,    77,    48,     6,    50,
      51,     3,    53,    54,    55,     8,     8,   132,    82,    83,
      84,    85,    86,    87,     4,   507,     3,     3,     3,     3,
     682,   132,     8,   507,     8,    93,    94,    95,    96,    97,
      98,    99,   100,   101,   102,   103,   104,   105,   106,     3,
     288,     3,     3,     3,     8,     3,     8,     8,     8,     4,
       8,   132,     3,   279,   280,     3,     3,     8,     4,     4,
       8,     8,     3,   316,   132,     4,     3,     8,   316,     6,
      90,    91,     4,     4,     4,   316,     4,     4,   316,     8,
     330,   132,   330,     4,     4,     8,   334,     3,     3,   330,
       4,     8,   330,   334,     4,     4,   330,     4,   330,   347,
     330,     4,     4,     4,     4,   132,   347,   360,   356,   347,
       4,     4,   360,     4,     4,     4,   135,   135,     4,     4,
       4,   360,   133,   360,   133,     4,   133,   133,     4,     4,
       4,   379,   121,   122,   123,   124,   125,   126,   127,   128,
     129,   130,   131,     4,     4,     4,     4,     4,     4,     4,
     133,     4,     4,     4,     4,     4,     4,     4,   133,   135,
     386,   387,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
     133,     4,     4,     4,     4,   135,   135,     4,     4,     4,
       4,   135,     4,   133,     4,   133,     4,   133,     4,     4,
     135,   135,   135,     4,     7,     7,   132,     7,     7,     7,
       5,     5,     5,     5,     5,     5,   135,   135,     7,     7,
       7,     5,     8,     3,   132,     7,   132,   132,     5,     5,
     108,     4,     7,   132,   132,   132,   489,   490,     7,   465,
     132,   489,   490,     7,   132,   132,     7,     7,   114,   132,
     132,   499,   132,     7,   507,   132,   482,     7,     4,   507,
     132,   132,   132,   132,   132,   132,   507,   132,   132,   507,
     132,     4,     4,    77,     4,     4,     4,     3,   132,     6,
       3,     6,     6,     3,     6,     3,   132,   132,   132,   132,
       4,     4,     4,     4,     4,     3,   440,     6,     3,     6,
       4,     4,     8,     4,     4,     4,     4,     4,   132,     4,
       4,     3,     5,   132,   132,     6,     4,   444,     8,   132,
       4,     8,   133,     8,   133,     7,   133,     4,     4,     7,
       5,     4,   288,   483,   487,   314,   133,   133,   310,   490,
     668,   680,   686,   684,   693,   671,   673,   676,   133,   363,
     133,   674,   133,   330,   133,   133,   356,   116,   132,   679,
     132,   132,   132,   677,   132,   132,   132,   132,   360,   132,
     132,   706,   704,   709,   132,   334,   707,   347,   507,   697,
     499,   379,   654,   778,   794,   806,   813,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
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
       0,   121,   122,   123,   124,   125,   126,   127,   128,   129,
     130,   131,   137,   138,   139,   140,   141,   142,   143,   144,
     145,   146,   147,   148,     0,     5,     7,     9,   132,   133,
     134,   135,   149,   150,   151,   156,     7,   165,     7,   171,
       7,   185,     7,   257,     7,   326,     7,   340,     7,   285,
       7,   309,     7,   233,     7,   392,   157,   152,   166,   172,
     186,   258,   327,   341,   286,   310,   234,   393,   149,   158,
     159,   132,   154,   155,    10,   113,   119,   120,   132,   164,
     167,   168,   169,   419,   421,   423,    11,    16,    17,    18,
      21,    22,    38,    39,    40,    41,    42,    46,    47,    65,
      66,    78,    81,    88,    89,    92,   164,   173,   174,   175,
     176,   177,   178,   179,   180,   181,   192,   194,   218,   227,
     241,   251,   279,   303,   345,   371,   381,   382,   390,    12,
      13,   183,   184,   187,   189,     7,    43,    44,    45,    56,
      59,    60,    61,    62,    63,    64,    68,    69,    76,   164,
     175,   176,   177,   180,   259,   260,   261,   263,   265,   267,
     269,   271,   273,   275,   277,   278,   303,   320,   334,   345,
     367,    57,    58,   164,   303,   328,   329,   330,   332,    19,
      20,    66,    70,    71,    72,    73,    74,    75,    77,   164,
     303,   342,   343,   344,   345,   347,   349,   351,   353,   355,
     357,   359,   361,   363,   365,    23,    48,    50,    51,    53,
      54,    55,   164,   208,   287,   288,   289,   290,   291,   292,
     293,   295,   297,   299,   300,   302,    49,    52,   164,   208,
     291,   297,   311,   312,   313,   314,   315,   317,   318,   319,
      79,    80,   164,   235,   236,   237,   239,    93,    94,    95,
      96,    97,    98,    99,   100,   101,   102,   103,   104,   105,
     106,   164,   394,   395,   396,   397,   399,   401,   402,   404,
     405,   406,   409,   411,   412,   413,   414,   417,     6,     3,
       4,     8,     3,   170,   424,   420,   422,     4,     3,     8,
     182,     4,     4,   346,   193,   195,     4,     4,     4,     4,
     252,   280,   304,   219,   372,   228,   242,     4,   383,   391,
       3,     8,   188,   190,     3,     8,   374,   264,   266,   268,
     321,   262,   270,   272,     4,     4,   276,   274,   335,   368,
       3,     8,   331,   333,     3,     8,   348,   350,   366,   354,
     356,   360,   358,   364,   362,   352,     8,     3,   294,   209,
       4,   298,   296,   301,     4,     8,     3,   316,     4,     8,
       3,   238,   240,     3,     8,     4,   398,   400,     4,   403,
       4,     4,   407,   410,     4,     4,     4,   415,   418,     3,
       8,   149,   149,   132,     4,     4,     4,     4,   168,     4,
     135,   135,     4,     4,     4,   133,   133,   133,   133,     4,
       4,     4,     4,     4,     4,     4,   133,     4,     4,   174,
       4,     4,   184,    67,   164,   208,   303,   345,   347,   349,
     375,   376,   377,   378,   379,     4,     4,     4,     4,     4,
       4,     4,   133,   135,     4,     4,     4,     4,   260,     4,
       4,   329,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,   344,     4,     4,   133,     4,     4,     4,   135,
     289,     4,   135,   313,     4,     4,   236,   135,     4,     4,
     133,     4,   133,   133,     4,     4,   135,   135,   135,     4,
       4,   395,     4,     7,     7,   149,   149,     7,   132,     7,
       7,     5,     5,     5,     5,     5,     5,     7,     7,     7,
       5,   160,    14,    15,   191,   380,     8,     3,   132,   132,
     132,     5,   132,   132,   132,   132,   132,     5,     7,   132,
     151,   153,   132,   132,   160,   132,   132,   132,   132,   132,
     132,   132,   132,   132,   132,   132,   132,   132,   132,   149,
     132,   132,   132,    15,   107,   408,   108,   109,   110,   111,
     112,   135,   416,   132,   149,   173,   114,   425,   426,   427,
     183,    23,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,   164,   196,   197,   198,   201,   203,   205,   207,
     208,   210,   211,   212,   213,   214,   216,   196,     7,   253,
     254,   255,     7,   281,   282,   283,     7,   305,   306,   307,
      70,    71,    72,    73,    75,   220,   221,   222,   223,   224,
     225,   226,   273,   373,     7,   229,   230,   231,    82,    83,
      84,    85,    86,    87,   243,   244,   245,   246,   247,   248,
     249,   250,    90,    91,   384,   385,   386,   388,   394,   161,
       4,   377,     7,   322,   323,   324,     7,   336,   337,   338,
      77,   369,     8,   428,     3,     8,     8,   199,   202,   204,
     206,     4,     4,     4,     4,     4,   215,   217,     3,     8,
       8,   256,     6,     3,   284,     6,     3,   308,     6,     3,
       3,     6,     3,     6,   232,     6,     3,     4,     4,     4,
       4,     4,     4,     3,     8,   387,   389,     3,     8,     8,
     132,   162,   163,   132,   325,     6,     3,   339,     6,     3,
     370,     8,     4,   426,     4,     4,     4,     4,   133,   135,
     133,   135,   133,     4,     4,   197,   259,   255,   287,   283,
     311,   307,   221,   273,   235,   231,   133,   133,   133,   133,
     133,   133,   244,     4,     4,   385,     6,     3,   328,   324,
     342,   338,     4,     5,    24,    25,    26,    27,   200,   132,
     132,   132,   132,   132,     8,     8,     8,     8,   132,   132,
     132,     8,     8,   132,     7,   429,   430,   431,     3,     6,
     115,   117,   118,   164,   208,   432,   433,   434,   435,   437,
     430,   438,     4,   436,     3,     8,     4,   133,     4,   433,
       5,   132,     7,   439,   440,   441,     3,     6,   116,   442,
     443,   440,   444,     3,     8,     4,   443,   132
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
     219,   218,   220,   220,   221,   221,   221,   221,   221,   222,
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
     344,   344,   344,   344,   344,   344,   344,   346,   345,   348,
     347,   350,   349,   352,   351,   354,   353,   356,   355,   358,
     357,   360,   359,   362,   361,   364,   363,   366,   365,   368,
     367,   370,   369,   372,   371,   373,   373,   374,   273,   375,
     375,   376,   376,   377,   377,   377,   377,   377,   377,   377,
     378,   380,   379,   381,   383,   382,   384,   384,   385,   385,
     387,   386,   389,   388,   391,   390,   393,   392,   394,   394,
     395,   395,   395,   395,   395,   395,   395,   395,   395,   395,
     395,   395,   395,   395,   395,   396,   398,   397,   400,   399,
     401,   403,   402,   404,   405,   407,   406,   408,   408,   410,
     409,   411,   412,   413,   415,   414,   416,   416,   416,   416,
     416,   418,   417,   420,   419,   422,   421,   424,   423,   425,
     425,   426,   428,   427,   429,   429,   431,   430,   432,   432,
     433,   433,   433,   433,   433,   434,   436,   435,   438,   437,
     439,   439,   441,   440,   442,   442,   444,   443
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
       1,     3,     0,     4,     1,     3,     0,     4
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
  "output_options_list_content", "output_entry", "$@103", "output_params",
  "output_param", "$@104", YY_NULLPTR
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
     617,   617,   627,   628,   631,   632,   633,   634,   635,   638,
     643,   648,   653,   658,   663,   663,   673,   674,   677,   678,
     681,   681,   689,   689,   697,   698,   699,   702,   703,   706,
     706,   714,   714,   722,   722,   732,   733,   736,   737,   738,
     739,   740,   741,   744,   749,   754,   759,   764,   769,   777,
     777,   790,   791,   794,   795,   802,   802,   825,   825,   834,
     835,   839,   840,   841,   842,   843,   844,   845,   846,   847,
     848,   849,   850,   851,   852,   853,   854,   855,   856,   857,
     858,   861,   861,   869,   869,   877,   877,   885,   885,   893,
     893,   901,   901,   909,   909,   917,   917,   925,   930,   939,
     939,   951,   952,   955,   956,   961,   961,   972,   972,   982,
     983,   986,   987,   990,   991,   992,   993,   994,   995,   996,
     997,  1000,  1002,  1007,  1009,  1009,  1017,  1017,  1025,  1025,
    1033,  1035,  1035,  1043,  1052,  1052,  1064,  1065,  1070,  1071,
    1076,  1076,  1087,  1087,  1098,  1099,  1104,  1105,  1110,  1111,
    1112,  1113,  1114,  1115,  1118,  1120,  1120,  1128,  1130,  1132,
    1140,  1140,  1152,  1153,  1156,  1157,  1160,  1160,  1168,  1168,
    1176,  1177,  1180,  1181,  1182,  1183,  1186,  1186,  1194,  1194,
    1204,  1204,  1214,  1215,  1218,  1219,  1222,  1222,  1230,  1230,
    1238,  1239,  1242,  1243,  1247,  1248,  1249,  1250,  1251,  1252,
    1253,  1254,  1255,  1256,  1257,  1258,  1259,  1262,  1262,  1270,
    1270,  1278,  1278,  1286,  1286,  1294,  1294,  1302,  1302,  1310,
    1310,  1318,  1318,  1326,  1326,  1334,  1334,  1342,  1342,  1355,
    1355,  1365,  1365,  1376,  1376,  1386,  1387,  1390,  1390,  1398,
    1399,  1402,  1403,  1406,  1407,  1408,  1409,  1410,  1411,  1412,
    1415,  1417,  1417,  1429,  1436,  1436,  1446,  1447,  1450,  1451,
    1454,  1454,  1462,  1462,  1472,  1472,  1482,  1482,  1490,  1491,
    1494,  1495,  1496,  1497,  1498,  1499,  1500,  1501,  1502,  1503,
    1504,  1505,  1506,  1507,  1508,  1511,  1516,  1516,  1524,  1524,
    1532,  1537,  1537,  1545,  1550,  1555,  1555,  1563,  1564,  1567,
    1567,  1575,  1580,  1585,  1590,  1590,  1598,  1601,  1604,  1607,
    1610,  1616,  1616,  1626,  1626,  1633,  1633,  1645,  1645,  1658,
    1659,  1663,  1667,  1667,  1679,  1680,  1684,  1684,  1692,  1693,
    1696,  1697,  1698,  1699,  1700,  1703,  1708,  1708,  1716,  1716,
    1726,  1727,  1730,  1730,  1738,  1739,  1742,  1742
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
#line 4072 "dhcp4_parser.cc" // lalr1.cc:1167
#line 1750 "dhcp4_parser.yy" // lalr1.cc:1168


void
isc::dhcp::Dhcp4Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
