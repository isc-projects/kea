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
      case 146: // value
      case 150: // map_value
      case 188: // socket_type
      case 197: // db_type
      case 397: // ncr_protocol_value
      case 406: // replace_client_name_value
        value.move< ElementPtr > (that.value);
        break;

      case 132: // "boolean"
        value.move< bool > (that.value);
        break;

      case 131: // "floating point"
        value.move< double > (that.value);
        break;

      case 130: // "integer"
        value.move< int64_t > (that.value);
        break;

      case 129: // "constant string"
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
      case 146: // value
      case 150: // map_value
      case 188: // socket_type
      case 197: // db_type
      case 397: // ncr_protocol_value
      case 406: // replace_client_name_value
        value.copy< ElementPtr > (that.value);
        break;

      case 132: // "boolean"
        value.copy< bool > (that.value);
        break;

      case 131: // "floating point"
        value.copy< double > (that.value);
        break;

      case 130: // "integer"
        value.copy< int64_t > (that.value);
        break;

      case 129: // "constant string"
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
            case 129: // "constant string"

#line 204 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< std::string > (); }
#line 362 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 130: // "integer"

#line 204 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< int64_t > (); }
#line 369 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 131: // "floating point"

#line 204 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< double > (); }
#line 376 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 132: // "boolean"

#line 204 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< bool > (); }
#line 383 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 146: // value

#line 204 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 390 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 150: // map_value

#line 204 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 397 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 188: // socket_type

#line 204 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 404 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 197: // db_type

#line 204 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 411 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 397: // ncr_protocol_value

#line 204 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 418 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 406: // replace_client_name_value

#line 204 "dhcp4_parser.yy" // lalr1.cc:636
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
      case 146: // value
      case 150: // map_value
      case 188: // socket_type
      case 197: // db_type
      case 397: // ncr_protocol_value
      case 406: // replace_client_name_value
        yylhs.value.build< ElementPtr > ();
        break;

      case 132: // "boolean"
        yylhs.value.build< bool > ();
        break;

      case 131: // "floating point"
        yylhs.value.build< double > ();
        break;

      case 130: // "integer"
        yylhs.value.build< int64_t > ();
        break;

      case 129: // "constant string"
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
#line 213 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.NO_KEYWORD; }
#line 670 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 4:
#line 214 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.CONFIG; }
#line 676 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 6:
#line 215 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.DHCP4; }
#line 682 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 8:
#line 216 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.INTERFACES_CONFIG; }
#line 688 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 10:
#line 217 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.SUBNET4; }
#line 694 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 12:
#line 218 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.POOLS; }
#line 700 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 14:
#line 219 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.RESERVATIONS; }
#line 706 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 16:
#line 220 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.OPTION_DEF; }
#line 712 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 18:
#line 221 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.OPTION_DATA; }
#line 718 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 20:
#line 222 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.HOOKS_LIBRARIES; }
#line 724 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 22:
#line 223 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.DHCP_DDNS; }
#line 730 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 24:
#line 231 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 736 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 25:
#line 232 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as< double > (), ctx.loc2pos(yystack_[0].location))); }
#line 742 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 26:
#line 233 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 748 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 27:
#line 234 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 754 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 28:
#line 235 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 760 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 29:
#line 236 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 766 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 30:
#line 237 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 772 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 31:
#line 240 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as< ElementPtr > ());
}
#line 781 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 32:
#line 245 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 792 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 33:
#line 250 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 802 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 34:
#line 256 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 808 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 37:
#line 263 "dhcp4_parser.yy" // lalr1.cc:859
    {
                  // map containing a single entry
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 817 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 38:
#line 267 "dhcp4_parser.yy" // lalr1.cc:859
    {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 827 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 39:
#line 274 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 836 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 40:
#line 277 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // list parsing complete. Put any sanity checking here
}
#line 844 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 43:
#line 285 "dhcp4_parser.yy" // lalr1.cc:859
    {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 853 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 44:
#line 289 "dhcp4_parser.yy" // lalr1.cc:859
    {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 862 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 45:
#line 296 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // List parsing about to start
}
#line 870 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 46:
#line 298 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // list parsing complete. Put any sanity checking here
    //ctx.stack_.pop_back();
}
#line 879 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 49:
#line 307 "dhcp4_parser.yy" // lalr1.cc:859
    {
                          ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 888 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 50:
#line 311 "dhcp4_parser.yy" // lalr1.cc:859
    {
                          ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 897 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 51:
#line 322 "dhcp4_parser.yy" // lalr1.cc:859
    {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as< std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 908 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 52:
#line 332 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 919 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 53:
#line 337 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 929 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 61:
#line 356 "dhcp4_parser.yy" // lalr1.cc:859
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
#line 363 "dhcp4_parser.yy" // lalr1.cc:859
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
#line 373 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the Dhcp4 map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 964 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 64:
#line 377 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 972 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 88:
#line 410 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 981 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 89:
#line 415 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 990 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 90:
#line 420 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 999 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 91:
#line 425 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr dpp(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 1008 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 92:
#line 430 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr echo(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("echo-client-id", echo);
}
#line 1017 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 93:
#line 435 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr match(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("match-client-id", match);
}
#line 1026 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 94:
#line 441 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces-config", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.INTERFACES_CONFIG);
}
#line 1037 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 95:
#line 446 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1046 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 100:
#line 459 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1056 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 101:
#line 463 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1064 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 102:
#line 467 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1075 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 103:
#line 472 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1084 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 104:
#line 477 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.DHCP_SOCKET_TYPE);
}
#line 1092 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 105:
#line 479 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("dhcp-socket-type", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1101 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 106:
#line 484 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("raw", ctx.loc2pos(yystack_[0].location))); }
#line 1107 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 107:
#line 485 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("udp", ctx.loc2pos(yystack_[0].location))); }
#line 1113 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 108:
#line 488 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lease-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.LEASE_DATABASE);
}
#line 1124 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 109:
#line 493 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1133 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 110:
#line 498 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1144 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 111:
#line 503 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1153 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 124:
#line 524 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.DATABASE_TYPE);
}
#line 1161 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 125:
#line 526 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("type", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1170 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 126:
#line 531 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("memfile", ctx.loc2pos(yystack_[0].location))); }
#line 1176 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 127:
#line 532 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("mysql", ctx.loc2pos(yystack_[0].location))); }
#line 1182 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 128:
#line 533 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("postgresql", ctx.loc2pos(yystack_[0].location))); }
#line 1188 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 129:
#line 534 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("cql", ctx.loc2pos(yystack_[0].location))); }
#line 1194 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 130:
#line 537 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1202 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 131:
#line 539 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr user(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1212 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 132:
#line 545 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1220 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 133:
#line 547 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr pwd(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 1230 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 134:
#line 553 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1238 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 135:
#line 555 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr h(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 1248 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 136:
#line 561 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1256 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 137:
#line 563 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1266 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 138:
#line 569 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 1275 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 139:
#line 574 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 1284 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 140:
#line 579 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 1293 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 141:
#line 584 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("connect-timeout", n);
}
#line 1302 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 142:
#line 589 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 1313 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 143:
#line 594 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1322 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 150:
#line 609 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1331 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 151:
#line 614 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 1340 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 152:
#line 619 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr circuit(new StringElement("circuit-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(circuit);
}
#line 1349 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 153:
#line 624 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr client(new StringElement("client-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(client);
}
#line 1358 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 154:
#line 629 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 1369 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 155:
#line 634 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1378 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 160:
#line 647 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1388 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 161:
#line 651 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1396 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 162:
#line 655 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1406 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 163:
#line 659 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1414 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 169:
#line 672 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1422 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 170:
#line 674 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr lib(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 1432 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 171:
#line 680 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1440 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 172:
#line 682 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1449 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 173:
#line 688 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.EXPIRED_LEASES_PROCESSING);
}
#line 1460 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 174:
#line 693 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1469 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 183:
#line 710 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 1478 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 184:
#line 715 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 1487 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 185:
#line 720 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 1496 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 186:
#line 725 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 1505 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 187:
#line 730 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 1514 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 188:
#line 735 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 1523 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 189:
#line 743 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet4", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET4);
}
#line 1534 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 190:
#line 748 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1543 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 195:
#line 768 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1553 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 196:
#line 772 "dhcp4_parser.yy" // lalr1.cc:859
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
#line 1576 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 197:
#line 791 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the subnet4 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1586 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 198:
#line 795 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1594 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 221:
#line 827 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1602 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 222:
#line 829 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr subnet(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 1612 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 223:
#line 835 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1620 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 224:
#line 837 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface", iface);
    ctx.leave();
}
#line 1630 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 225:
#line 843 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1638 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 226:
#line 845 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface-id", iface);
    ctx.leave();
}
#line 1648 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 227:
#line 851 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1656 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 228:
#line 853 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-subnet", iface);
    ctx.leave();
}
#line 1666 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 229:
#line 859 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1674 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 230:
#line 861 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 1684 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 231:
#line 867 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1692 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 232:
#line 869 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface-id", iface);
    ctx.leave();
}
#line 1702 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 233:
#line 875 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.CLIENT_CLASS);
}
#line 1710 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 234:
#line 877 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr cls(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 1720 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 235:
#line 883 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1728 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 236:
#line 885 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr rm(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservation-mode", rm);
    ctx.leave();
}
#line 1738 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 237:
#line 891 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr id(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 1747 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 238:
#line 896 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr rc(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rapid-commit", rc);
}
#line 1756 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 239:
#line 905 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 1767 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 240:
#line 910 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1776 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 245:
#line 927 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1786 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 246:
#line 931 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1794 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 247:
#line 938 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1804 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 248:
#line 942 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1812 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 262:
#line 968 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr code(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 1821 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 264:
#line 975 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1829 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 265:
#line 977 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 1839 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 266:
#line 983 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1847 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 267:
#line 985 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 1857 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 268:
#line 991 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1865 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 269:
#line 993 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr space(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 1875 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 271:
#line 1001 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1883 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 272:
#line 1003 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr encap(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 1893 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 273:
#line 1009 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr array(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 1902 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 274:
#line 1018 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 1913 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 275:
#line 1023 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1922 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 280:
#line 1042 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1932 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 281:
#line 1046 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1940 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 282:
#line 1053 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1950 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 283:
#line 1057 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1958 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 295:
#line 1086 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1966 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 296:
#line 1088 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr data(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 1976 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 299:
#line 1098 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr space(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", space);
}
#line 1985 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 300:
#line 1106 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 1996 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 301:
#line 1111 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2005 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 306:
#line 1126 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2015 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 307:
#line 1130 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2023 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 308:
#line 1134 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2033 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 309:
#line 1138 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 2041 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 316:
#line 1152 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2049 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 317:
#line 1154 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr pool(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 2059 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 318:
#line 1160 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2067 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 319:
#line 1162 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("user-context", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2076 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 320:
#line 1170 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 2087 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 321:
#line 1175 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2096 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 326:
#line 1188 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2106 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 327:
#line 1192 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2114 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 328:
#line 1196 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2124 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 329:
#line 1200 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 2132 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 346:
#line 1227 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2140 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 347:
#line 1229 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr next_server(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("next-server", next_server);
    ctx.leave();
}
#line 2150 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 348:
#line 1235 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2158 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 349:
#line 1237 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr srv(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-hostname", srv);
    ctx.leave();
}
#line 2168 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 350:
#line 1243 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2176 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 351:
#line 1245 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr bootfile(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("boot-file-name", bootfile);
    ctx.leave();
}
#line 2186 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 352:
#line 1251 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2194 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 353:
#line 1253 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr addr(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", addr);
    ctx.leave();
}
#line 2204 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 354:
#line 1259 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2212 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 355:
#line 1261 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr d(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 2222 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 356:
#line 1267 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2230 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 357:
#line 1269 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 2240 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 358:
#line 1275 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2248 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 359:
#line 1277 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-id", hw);
    ctx.leave();
}
#line 2258 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 360:
#line 1283 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2266 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 361:
#line 1285 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("circuit-id", hw);
    ctx.leave();
}
#line 2276 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 362:
#line 1292 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2284 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 363:
#line 1294 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr host(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 2294 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 364:
#line 1300 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2305 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 365:
#line 1305 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2314 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 366:
#line 1313 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 2325 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 367:
#line 1318 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2334 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 368:
#line 1323 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2342 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 369:
#line 1325 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr ip(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", ip);
    ctx.leave();
}
#line 2352 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 370:
#line 1334 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 2363 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 371:
#line 1339 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2372 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 374:
#line 1348 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2382 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 375:
#line 1352 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2390 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 388:
#line 1375 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2398 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 389:
#line 1377 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr test(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 2408 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 390:
#line 1387 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 2417 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 391:
#line 1394 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 2428 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 392:
#line 1399 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2437 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 397:
#line 1412 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2445 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 398:
#line 1414 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr stype(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 2455 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 399:
#line 1420 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2463 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 400:
#line 1422 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 2473 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 401:
#line 1430 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 2484 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 402:
#line 1435 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2493 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 403:
#line 1440 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2503 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 404:
#line 1444 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 2511 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 423:
#line 1470 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 2520 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 424:
#line 1475 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2528 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 425:
#line 1477 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("qualifying-suffix", s);
    ctx.leave();
}
#line 2538 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 426:
#line 1483 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2546 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 427:
#line 1485 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 2556 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 428:
#line 1491 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 2565 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 429:
#line 1496 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2573 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 430:
#line 1498 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 2583 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 431:
#line 1504 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 2592 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 432:
#line 1509 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 2601 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 433:
#line 1514 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 2609 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 434:
#line 1516 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2618 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 435:
#line 1522 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 2624 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 436:
#line 1523 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 2630 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 437:
#line 1526 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NCR_FORMAT);
}
#line 2638 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 438:
#line 1528 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 2648 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 439:
#line 1534 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-include-fqdn", b);
}
#line 2657 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 440:
#line 1539 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("allow-client-update",  b);
}
#line 2666 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 441:
#line 1544 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-no-update", b);
}
#line 2675 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 442:
#line 1549 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-client-update", b);
}
#line 2684 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 443:
#line 1554 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 2692 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 444:
#line 1556 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("replace-client-name", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2701 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 445:
#line 1562 "dhcp4_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("when-present", ctx.loc2pos(yystack_[0].location))); 
      }
#line 2709 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 446:
#line 1565 "dhcp4_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location)));
      }
#line 2717 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 447:
#line 1568 "dhcp4_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("always", ctx.loc2pos(yystack_[0].location)));
      }
#line 2725 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 448:
#line 1571 "dhcp4_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("when-not-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 2733 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 449:
#line 1574 "dhcp4_parser.yy" // lalr1.cc:859
    {
      error(yystack_[0].location, "boolean values for the replace-client-name are "
                "no longer supported");
      }
#line 2742 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 450:
#line 1580 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2750 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 451:
#line 1582 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("generated-prefix", s);
    ctx.leave();
}
#line 2760 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 452:
#line 1590 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2768 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 453:
#line 1592 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("Dhcp6", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2777 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 454:
#line 1597 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2785 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 455:
#line 1599 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("DhcpDdns", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2794 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 456:
#line 1609 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Logging", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.LOGGING);
}
#line 2805 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 457:
#line 1614 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2814 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 461:
#line 1631 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 2825 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 462:
#line 1636 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2834 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 465:
#line 1648 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 2844 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 466:
#line 1652 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2852 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 474:
#line 1667 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr dl(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 2861 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 475:
#line 1671 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2869 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 476:
#line 1673 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 2879 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 477:
#line 1679 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 2890 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 478:
#line 1684 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2899 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 481:
#line 1693 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2909 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 482:
#line 1697 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2917 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 485:
#line 1705 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2925 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 486:
#line 1707 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 2935 "dhcp4_parser.cc" // lalr1.cc:859
    break;


#line 2939 "dhcp4_parser.cc" // lalr1.cc:859
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
     121,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,
    -473,  -473,    32,    19,    23,    45,    56,    74,    82,    86,
     104,   115,   119,   148,  -473,  -473,  -473,  -473,  -473,  -473,
    -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,
    -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,
    -473,  -473,  -473,  -473,  -473,  -473,    19,   -92,    17,    29,
     154,    18,   -13,    68,    57,    52,    -6,   123,  -473,   169,
     125,   205,   184,   226,  -473,  -473,  -473,  -473,   255,  -473,
      30,  -473,  -473,  -473,  -473,  -473,  -473,   262,   263,  -473,
    -473,  -473,   265,   267,   269,   270,  -473,  -473,  -473,  -473,
    -473,  -473,  -473,   271,  -473,  -473,  -473,    31,  -473,  -473,
    -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,
    -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,
    -473,    40,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,
    -473,  -473,  -473,   273,   274,  -473,  -473,  -473,  -473,  -473,
    -473,  -473,  -473,  -473,    41,  -473,  -473,  -473,  -473,  -473,
    -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,
    -473,  -473,  -473,  -473,  -473,    53,  -473,  -473,  -473,  -473,
    -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,
     272,   278,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,
    -473,  -473,  -473,  -473,  -473,   280,  -473,  -473,  -473,   281,
    -473,  -473,   279,   286,  -473,  -473,  -473,  -473,  -473,  -473,
    -473,  -473,  -473,  -473,  -473,   288,  -473,  -473,  -473,  -473,
     285,   291,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,
    -473,   116,  -473,  -473,  -473,   295,  -473,  -473,   296,  -473,
     298,   299,  -473,  -473,   300,   301,   302,   303,  -473,  -473,
    -473,   122,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,
    -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,    19,
      19,  -473,   180,   304,   307,   309,   310,  -473,    17,  -473,
     311,   187,   190,   312,   313,   314,   193,   194,   195,   197,
     316,   322,   324,   325,   326,   327,   328,   203,   330,   331,
      29,  -473,   332,   333,   154,  -473,    76,   334,   335,   336,
     337,   338,   339,   342,   217,   216,   345,   346,   347,   348,
      18,  -473,   349,   350,   -13,  -473,   351,   352,   353,   354,
     355,   356,   357,   358,   359,  -473,    68,   360,   361,   237,
     362,   364,   365,   238,  -473,    57,   367,   240,  -473,    52,
     369,   370,   186,  -473,   243,   372,   373,   248,   375,   250,
     251,   378,   379,   252,   253,   254,   256,   383,   385,   123,
    -473,  -473,  -473,   386,   384,   387,    19,    19,  -473,   388,
    -473,  -473,   264,   389,   390,  -473,  -473,  -473,  -473,   393,
     394,   395,   396,   397,   398,   399,  -473,   400,   401,  -473,
     404,   236,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,
     402,   408,  -473,  -473,  -473,   275,   276,   283,   409,   284,
     287,   289,  -473,  -473,   290,   292,   410,   413,  -473,   294,
     417,  -473,   305,   306,   404,   308,   317,   318,   319,   321,
     323,  -473,   329,   340,  -473,   341,   343,   344,  -473,  -473,
     363,  -473,  -473,   366,    19,  -473,  -473,   368,   371,  -473,
     374,  -473,  -473,    14,   320,  -473,  -473,  -473,  -473,    36,
     376,  -473,    19,    29,   377,  -473,  -473,   154,  -473,   131,
     131,   421,   422,   423,   166,    50,   426,    91,   177,   123,
    -473,  -473,  -473,  -473,  -473,   432,  -473,    76,  -473,  -473,
    -473,   431,  -473,  -473,  -473,  -473,  -473,   435,   380,  -473,
    -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,
    -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,
    -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,
    -473,  -473,  -473,  -473,   149,  -473,   175,  -473,  -473,   179,
    -473,  -473,  -473,  -473,   439,   441,   447,   450,  -473,   181,
    -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,
     182,  -473,   411,   436,  -473,  -473,   449,   454,  -473,  -473,
     455,   457,  -473,  -473,  -473,  -473,  -473,    79,  -473,  -473,
    -473,  -473,  -473,  -473,   126,  -473,   456,   460,  -473,   461,
     462,   463,   464,   467,   470,   185,  -473,  -473,  -473,  -473,
    -473,  -473,  -473,  -473,  -473,   188,  -473,  -473,  -473,   192,
     381,   382,  -473,  -473,   458,   472,  -473,  -473,   471,   473,
    -473,  -473,   474,  -473,   475,   377,  -473,  -473,   476,   477,
     479,   480,   260,   391,   392,   403,   131,  -473,  -473,    18,
    -473,   421,    57,  -473,   422,    52,  -473,   423,   166,  -473,
      50,  -473,    -6,  -473,   426,   405,   406,   407,   412,   414,
     415,    91,  -473,   481,   482,   177,  -473,  -473,  -473,   483,
     484,  -473,   -13,  -473,   431,    68,  -473,   435,   486,  -473,
     488,  -473,   230,   418,   419,   420,  -473,  -473,  -473,  -473,
    -473,   196,  -473,   490,  -473,   491,  -473,  -473,  -473,   198,
    -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,   424,   425,
    -473,  -473,   427,   199,  -473,   493,  -473,   428,   487,  -473,
    -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,
    -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,   150,  -473,
      65,   487,  -473,  -473,   492,  -473,  -473,  -473,   200,  -473,
    -473,  -473,  -473,  -473,   498,   416,   500,    65,  -473,   501,
    -473,   429,  -473,   502,  -473,  -473,   225,  -473,   430,   502,
    -473,  -473,   224,  -473,  -473,   503,   430,  -473,   433,  -473,
    -473
  };

  const unsigned short int
  Dhcp4Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     1,    39,    32,    28,    27,    24,
      25,    26,    31,     3,    29,    30,    52,     5,    63,     7,
     100,     9,   197,    11,   308,    13,   328,    15,   247,    17,
     282,    19,   162,    21,   403,    23,    41,    35,     0,     0,
       0,     0,     0,   330,   249,   284,     0,     0,    43,     0,
      42,     0,     0,    36,    61,   456,   452,   454,     0,    60,
       0,    54,    56,    58,    59,    57,    94,     0,     0,   346,
     108,   110,     0,     0,     0,     0,   189,   239,   274,   142,
     370,   154,   173,     0,   391,   401,    87,     0,    65,    67,
      68,    69,    70,    84,    85,    72,    73,    74,    75,    79,
      80,    71,    77,    78,    86,    76,    81,    82,    83,   102,
     104,     0,    96,    98,    99,   374,   223,   225,   227,   300,
     221,   229,   231,     0,     0,   235,   233,   320,   366,   220,
     201,   202,   203,   215,     0,   199,   206,   217,   218,   219,
     207,   208,   211,   213,   209,   210,   204,   205,   212,   216,
     214,   316,   318,   315,   313,     0,   310,   312,   314,   348,
     350,   364,   354,   356,   360,   358,   362,   352,   345,   341,
       0,   331,   332,   342,   343,   344,   338,   334,   339,   336,
     337,   340,   335,   264,   136,     0,   268,   266,   271,     0,
     260,   261,     0,   250,   251,   253,   263,   254,   255,   256,
     270,   257,   258,   259,   295,     0,   293,   294,   297,   298,
       0,   285,   286,   288,   289,   290,   291,   292,   169,   171,
     166,     0,   164,   167,   168,     0,   424,   426,     0,   429,
       0,     0,   433,   437,     0,     0,     0,     0,   443,   450,
     422,     0,   405,   407,   408,   409,   410,   411,   412,   413,
     414,   415,   416,   417,   418,   419,   420,   421,    40,     0,
       0,    33,     0,     0,     0,     0,     0,    51,     0,    53,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    64,     0,     0,     0,   101,   376,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   198,     0,     0,     0,   309,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   329,     0,     0,     0,     0,
       0,     0,     0,     0,   248,     0,     0,     0,   283,     0,
       0,     0,     0,   163,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     404,    44,    37,     0,     0,     0,     0,     0,    55,     0,
      92,    93,     0,     0,     0,    88,    89,    90,    91,     0,
       0,     0,     0,     0,     0,     0,   390,     0,     0,    66,
       0,     0,    97,   388,   386,   387,   382,   383,   384,   385,
       0,   377,   378,   380,   381,     0,     0,     0,     0,     0,
       0,     0,   237,   238,     0,     0,     0,     0,   200,     0,
       0,   311,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   333,     0,     0,   262,     0,     0,     0,   273,   252,
       0,   299,   287,     0,     0,   165,   423,     0,     0,   428,
       0,   431,   432,     0,     0,   439,   440,   441,   442,     0,
       0,   406,     0,     0,     0,   453,   455,     0,   347,     0,
       0,   191,   241,   276,     0,     0,   156,     0,     0,     0,
      45,   103,   106,   107,   105,     0,   375,     0,   224,   226,
     228,   302,   222,   230,   232,   236,   234,   322,     0,   317,
      34,   319,   349,   351,   365,   355,   357,   361,   359,   363,
     353,   265,   137,   269,   267,   272,   296,   170,   172,   425,
     427,   430,   435,   436,   434,   438,   445,   446,   447,   448,
     449,   444,   451,    38,     0,   461,     0,   458,   460,     0,
     124,   130,   132,   134,     0,     0,     0,     0,   123,     0,
     112,   114,   115,   116,   117,   118,   119,   120,   121,   122,
       0,   195,     0,   192,   193,   245,     0,   242,   243,   280,
       0,   277,   278,   150,   151,   152,   153,     0,   144,   146,
     147,   148,   149,   372,     0,   160,     0,   157,   158,     0,
       0,     0,     0,     0,     0,     0,   175,   177,   178,   179,
     180,   181,   182,   397,   399,     0,   393,   395,   396,     0,
      47,     0,   379,   306,     0,   303,   304,   326,     0,   323,
     324,   368,     0,    62,     0,     0,   457,    95,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   109,   111,     0,
     190,     0,   249,   240,     0,   284,   275,     0,     0,   143,
       0,   371,     0,   155,     0,     0,     0,     0,     0,     0,
       0,     0,   174,     0,     0,     0,   392,   402,    49,     0,
      48,   389,     0,   301,     0,   330,   321,     0,     0,   367,
       0,   459,     0,     0,     0,     0,   138,   139,   140,   141,
     113,     0,   194,     0,   244,     0,   279,   145,   373,     0,
     159,   183,   184,   185,   186,   187,   188,   176,     0,     0,
     394,    46,     0,     0,   305,     0,   325,     0,     0,   126,
     127,   128,   129,   125,   131,   133,   135,   196,   246,   281,
     161,   398,   400,    50,   307,   327,   369,   465,     0,   463,
       0,     0,   462,   477,     0,   475,   473,   469,     0,   467,
     471,   472,   470,   464,     0,     0,     0,     0,   466,     0,
     474,     0,   468,     0,   476,   481,     0,   479,     0,     0,
     478,   485,     0,   483,   480,     0,     0,   482,     0,   484,
     486
  };

  const short int
  Dhcp4Parser::yypgoto_[] =
  {
    -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,
    -473,  -473,  -473,   -42,  -473,    38,  -473,  -473,  -473,  -473,
    -473,  -473,  -473,  -473,    47,  -473,  -473,  -473,   -58,  -473,
    -473,  -473,   220,  -473,  -473,  -473,  -473,    33,   202,   -60,
     -44,   -40,  -473,  -473,   -39,  -473,  -473,    26,   201,  -473,
    -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,
      24,  -139,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,
    -473,   -63,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,
    -150,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -155,
    -473,  -473,  -473,  -152,   160,  -473,  -473,  -473,  -473,  -473,
    -473,  -473,  -158,  -473,  -473,  -473,  -473,  -473,  -473,  -473,
    -473,  -473,  -473,  -136,  -473,  -473,  -473,  -133,   204,  -473,
    -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,
    -473,  -472,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,
    -473,  -137,  -473,  -473,  -473,  -134,  -473,   174,  -473,   -49,
    -473,  -473,  -473,  -473,  -473,   -47,  -473,  -473,  -473,  -473,
    -473,   -51,  -473,  -473,  -473,  -135,  -473,  -473,  -473,  -127,
    -473,   171,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,
    -473,  -473,  -163,  -473,  -473,  -473,  -153,   206,  -473,  -473,
    -473,  -473,  -473,  -473,  -473,  -473,  -156,  -473,  -473,  -473,
    -145,  -473,   209,   -48,  -473,  -297,  -473,  -296,  -473,  -473,
    -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,
    -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,
    -473,  -473,  -473,    44,  -473,  -473,  -473,  -473,  -473,  -473,
    -473,  -126,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,
      61,   173,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,
    -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,
    -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,
    -473,  -473,  -473,   -84,  -473,  -473,  -473,  -198,  -473,  -473,
    -213,  -473,  -473,  -473,  -473,  -473,  -473,  -224,  -473,  -473,
    -230,  -473
  };

  const short int
  Dhcp4Parser::yydefgoto_[] =
  {
      -1,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    32,    33,    34,    57,   521,    72,    73,
      35,    56,    69,    70,   501,   630,   689,   690,   106,    37,
      58,    80,    81,    82,   283,    39,    59,   107,   108,   109,
     110,   111,   112,   113,   114,   115,   290,   131,   132,    41,
      60,   133,   312,   134,   313,   504,   116,   294,   117,   295,
     569,   570,   571,   648,   743,   572,   649,   573,   650,   574,
     651,   211,   348,   576,   577,   578,   579,   118,   303,   597,
     598,   599,   600,   601,   602,   119,   305,   606,   607,   608,
     672,    53,    66,   241,   242,   243,   360,   244,   361,   120,
     306,   615,   616,   617,   618,   619,   620,   621,   622,   121,
     300,   582,   583,   584,   659,    43,    61,   154,   155,   156,
     321,   157,   317,   158,   318,   159,   319,   160,   322,   161,
     323,   162,   327,   163,   326,   164,   165,   122,   301,   586,
     587,   588,   662,    49,    64,   212,   213,   214,   215,   216,
     217,   218,   347,   219,   351,   220,   350,   221,   222,   352,
     223,   123,   302,   590,   591,   592,   665,    51,    65,   230,
     231,   232,   233,   234,   356,   235,   236,   237,   167,   320,
     634,   635,   636,   692,    45,    62,   175,   176,   177,   332,
     178,   333,   168,   328,   638,   639,   640,   695,    47,    63,
     190,   191,   192,   124,   293,   194,   336,   195,   337,   196,
     344,   197,   339,   198,   340,   199,   342,   200,   341,   201,
     343,   202,   338,   170,   329,   642,   698,   125,   304,   604,
     316,   420,   421,   422,   423,   424,   505,   126,   127,   308,
     625,   626,   627,   683,   628,   684,   128,   309,    55,    67,
     261,   262,   263,   264,   365,   265,   366,   266,   267,   368,
     268,   269,   270,   371,   544,   271,   372,   272,   273,   274,
     275,   276,   377,   551,   277,   378,    83,   285,    84,   286,
      85,   284,   556,   557,   558,   644,   758,   759,   760,   768,
     769,   770,   771,   776,   772,   774,   786,   787,   788,   792,
     793,   795
  };

  const unsigned short int
  Dhcp4Parser::yytable_[] =
  {
      79,   150,   227,   149,   173,   188,   210,   226,   240,   260,
     166,   174,   189,   169,    68,   193,   228,   151,   229,   418,
     419,   152,   153,   603,    25,   135,    26,    74,    27,   542,
      36,    98,    24,   288,   310,    88,    89,    71,   289,   311,
      86,   171,   172,   314,   330,    87,    88,    89,   315,   331,
      90,    91,    38,    92,    93,    94,   334,   135,   136,   137,
     138,   335,    98,    40,    92,    93,    94,    95,    96,   238,
     239,   139,    97,    98,   140,   141,   142,   143,   144,   145,
     203,    42,   668,   146,   147,   669,    89,   179,   180,    44,
     148,    99,   100,    46,    89,   179,   180,   204,   224,   205,
     206,   225,   204,   101,   205,   206,   102,   207,   208,   209,
     204,    48,    98,   103,   104,   146,    78,   105,   543,   362,
      98,   204,    50,    78,   363,   379,    52,    75,   279,   670,
     380,   181,   671,    76,    77,   182,   183,   184,   185,   186,
     413,   187,   546,   547,   548,   549,    78,    78,    28,    29,
      30,    31,   310,   761,   560,    54,   762,   643,    78,   561,
     562,   563,   564,   565,   566,   567,   129,   130,   550,   609,
     610,   611,   612,   613,   614,   278,   204,   763,   645,   764,
     765,    78,   314,   646,   656,   656,    78,   647,   681,   657,
     658,   685,   281,   682,    78,   379,   686,    78,   718,   330,
     687,   362,   334,   777,   747,    78,   750,   754,   778,   280,
     418,   419,   245,   246,   247,   248,   249,   250,   251,   252,
     253,   254,   255,   256,   257,   258,   259,   796,   789,   282,
      79,   790,   797,   593,   594,   595,   596,   381,   382,     1,
       2,     3,     4,     5,     6,     7,     8,     9,    10,    11,
     502,   503,    78,   415,   739,   740,   741,   742,   414,   287,
      78,   238,   239,   623,   624,   416,   291,   292,   417,   296,
     150,   297,   149,   298,   299,   307,   173,   324,   325,   166,
     345,   346,   169,   174,   349,   353,   151,   354,   188,   355,
     152,   153,   357,   358,   359,   189,   227,   210,   193,   364,
     367,   226,   369,   370,   373,   374,   375,   376,   384,   383,
     228,   385,   229,   386,   387,   389,   392,   393,   394,   390,
     399,   260,   391,   395,   396,   397,   400,   398,   401,   402,
     403,   404,   405,   406,   407,   408,   410,   411,   425,   426,
     427,   428,   429,   430,   485,   486,   431,   432,   433,   434,
     435,   436,   437,   439,   440,   442,   443,   444,   445,   446,
     447,   448,   449,   450,   452,   453,   455,   454,   456,   457,
     458,   460,   461,   463,   464,   466,   467,   468,   469,   470,
     471,   472,   473,   474,   475,   476,   477,   479,   478,   480,
     482,   483,   706,   488,   484,   487,   489,   490,   491,   492,
     493,   494,   495,   496,   508,   509,   497,   498,   499,   500,
     506,   507,   510,   512,   511,   517,   513,   660,   514,   515,
     518,   516,   538,   519,    26,   545,   575,   575,   581,   585,
     589,   568,   568,   605,   522,   523,   631,   525,   633,   661,
     553,   260,   637,   652,   415,   653,   526,   527,   528,   414,
     529,   654,   530,   641,   655,   663,   416,   664,   531,   417,
     667,   666,   673,   674,   693,   675,   676,   677,   678,   532,
     533,   679,   534,   535,   680,   694,   697,   696,   520,   700,
     702,   703,   699,   704,   705,   728,   729,   732,   555,   731,
     737,   524,   536,   738,   757,   537,   775,   539,   748,   749,
     540,   755,   779,   541,   781,   552,   783,   798,   388,   785,
     688,   691,   409,   559,   580,   412,   554,   710,   717,   720,
     719,   707,   465,   727,   708,   712,   711,   714,   713,   459,
     462,   734,   716,   709,   438,   721,   722,   723,   715,   733,
     441,   736,   724,   791,   725,   726,   780,   744,   745,   746,
     735,   632,   481,   751,   752,   451,   753,   756,   784,   730,
     629,   701,   800,   773,   782,   794,   799,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   575,     0,     0,     0,     0,   568,   150,
       0,   149,   227,     0,   210,     0,     0,   226,   166,     0,
       0,   169,     0,     0,   240,   151,   228,     0,   229,   152,
     153,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   173,     0,     0,   188,     0,     0,
       0,   174,     0,     0,   189,     0,     0,   193,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   767,     0,     0,
       0,     0,   766,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   767,     0,     0,     0,     0,   766
  };

  const short int
  Dhcp4Parser::yycheck_[] =
  {
      58,    61,    65,    61,    62,    63,    64,    65,    66,    67,
      61,    62,    63,    61,    56,    63,    65,    61,    65,   316,
     316,    61,    61,   495,     5,     7,     7,    10,     9,    15,
       7,    44,     0,     3,     3,    17,    18,   129,     8,     8,
      11,    54,    55,     3,     3,    16,    17,    18,     8,     8,
      21,    22,     7,    35,    36,    37,     3,     7,    40,    41,
      42,     8,    44,     7,    35,    36,    37,    38,    39,    75,
      76,    53,    43,    44,    56,    57,    58,    59,    60,    61,
      23,     7,     3,    65,    66,     6,    18,    19,    20,     7,
      72,    62,    63,     7,    18,    19,    20,    45,    46,    47,
      48,    49,    45,    74,    47,    48,    77,    50,    51,    52,
      45,     7,    44,    84,    85,    65,   129,    88,   104,     3,
      44,    45,     7,   129,     8,     3,     7,   110,     3,     3,
       8,    63,     6,   116,   117,    67,    68,    69,    70,    71,
      64,    73,   106,   107,   108,   109,   129,   129,   129,   130,
     131,   132,     3,     3,    23,     7,     6,     8,   129,    28,
      29,    30,    31,    32,    33,    34,    12,    13,   132,    78,
      79,    80,    81,    82,    83,     6,    45,   112,     3,   114,
     115,   129,     3,     8,     3,     3,   129,     8,     3,     8,
       8,     3,     8,     8,   129,     3,     8,   129,   670,     3,
       8,     3,     3,     3,     8,   129,     8,     8,     8,     4,
     507,   507,    89,    90,    91,    92,    93,    94,    95,    96,
      97,    98,    99,   100,   101,   102,   103,     3,     3,     3,
     288,     6,     8,    67,    68,    69,    70,   279,   280,   118,
     119,   120,   121,   122,   123,   124,   125,   126,   127,   128,
      14,    15,   129,   316,    24,    25,    26,    27,   316,     4,
     129,    75,    76,    86,    87,   316,     4,     4,   316,     4,
     330,     4,   330,     4,     4,     4,   334,     4,     4,   330,
       8,     3,   330,   334,     4,     4,   330,     8,   346,     3,
     330,   330,     4,     8,     3,   346,   359,   355,   346,     4,
       4,   359,     4,     4,     4,     4,     4,     4,     4,   129,
     359,     4,   359,     4,     4,     4,     4,     4,     4,   132,
       4,   379,   132,   130,   130,   130,     4,   130,     4,     4,
       4,     4,     4,   130,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,   386,   387,     4,   130,   132,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,   130,     4,     4,
     132,     4,   132,     4,     4,   132,     4,     4,   130,     4,
     130,   130,     4,     4,   132,   132,   132,     4,   132,     4,
       4,     7,   132,   129,     7,     7,     7,     7,     5,     5,
       5,     5,     5,     5,   129,   129,     7,     7,     7,     5,
       8,     3,   129,   129,     5,     5,   129,     6,   129,   129,
       7,   129,   464,   129,     7,   105,   489,   490,     7,     7,
       7,   489,   490,     7,   129,   129,     4,   129,     7,     3,
     482,   499,     7,     4,   507,     4,   129,   129,   129,   507,
     129,     4,   129,    73,     4,     6,   507,     3,   129,   507,
       3,     6,     6,     3,     6,     4,     4,     4,     4,   129,
     129,     4,   129,   129,     4,     3,     3,     6,   440,     4,
       4,     4,     8,     4,     4,     4,     4,     3,   111,     6,
       4,   444,   129,     5,     7,   129,     4,   129,     8,     8,
     129,     8,     4,   129,     4,   129,     5,     4,   288,     7,
     129,   129,   310,   487,   490,   314,   483,   656,   668,   674,
     672,   130,   362,   681,   132,   661,   659,   664,   662,   355,
     359,   694,   667,   130,   330,   130,   130,   130,   665,   692,
     334,   697,   130,   113,   130,   130,   130,   129,   129,   129,
     695,   507,   379,   129,   129,   346,   129,   129,   129,   685,
     499,   645,   129,   761,   777,   789,   796,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   656,    -1,    -1,    -1,    -1,   656,   659,
      -1,   659,   665,    -1,   662,    -1,    -1,   665,   659,    -1,
      -1,   659,    -1,    -1,   672,   659,   665,    -1,   665,   659,
     659,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   692,    -1,    -1,   695,    -1,    -1,
      -1,   692,    -1,    -1,   695,    -1,    -1,   695,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   760,    -1,    -1,
      -1,    -1,   760,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   777,    -1,    -1,    -1,    -1,   777
  };

  const unsigned short int
  Dhcp4Parser::yystos_[] =
  {
       0,   118,   119,   120,   121,   122,   123,   124,   125,   126,
     127,   128,   134,   135,   136,   137,   138,   139,   140,   141,
     142,   143,   144,   145,     0,     5,     7,     9,   129,   130,
     131,   132,   146,   147,   148,   153,     7,   162,     7,   168,
       7,   182,     7,   248,     7,   317,     7,   331,     7,   276,
       7,   300,     7,   224,     7,   381,   154,   149,   163,   169,
     183,   249,   318,   332,   277,   301,   225,   382,   146,   155,
     156,   129,   151,   152,    10,   110,   116,   117,   129,   161,
     164,   165,   166,   409,   411,   413,    11,    16,    17,    18,
      21,    22,    35,    36,    37,    38,    39,    43,    44,    62,
      63,    74,    77,    84,    85,    88,   161,   170,   171,   172,
     173,   174,   175,   176,   177,   178,   189,   191,   210,   218,
     232,   242,   270,   294,   336,   360,   370,   371,   379,    12,
      13,   180,   181,   184,   186,     7,    40,    41,    42,    53,
      56,    57,    58,    59,    60,    61,    65,    66,    72,   161,
     172,   173,   174,   177,   250,   251,   252,   254,   256,   258,
     260,   262,   264,   266,   268,   269,   294,   311,   325,   336,
     356,    54,    55,   161,   294,   319,   320,   321,   323,    19,
      20,    63,    67,    68,    69,    70,    71,    73,   161,   294,
     333,   334,   335,   336,   338,   340,   342,   344,   346,   348,
     350,   352,   354,    23,    45,    47,    48,    50,    51,    52,
     161,   204,   278,   279,   280,   281,   282,   283,   284,   286,
     288,   290,   291,   293,    46,    49,   161,   204,   282,   288,
     302,   303,   304,   305,   306,   308,   309,   310,    75,    76,
     161,   226,   227,   228,   230,    89,    90,    91,    92,    93,
      94,    95,    96,    97,    98,    99,   100,   101,   102,   103,
     161,   383,   384,   385,   386,   388,   390,   391,   393,   394,
     395,   398,   400,   401,   402,   403,   404,   407,     6,     3,
       4,     8,     3,   167,   414,   410,   412,     4,     3,     8,
     179,     4,     4,   337,   190,   192,     4,     4,     4,     4,
     243,   271,   295,   211,   361,   219,   233,     4,   372,   380,
       3,     8,   185,   187,     3,     8,   363,   255,   257,   259,
     312,   253,   261,   263,     4,     4,   267,   265,   326,   357,
       3,     8,   322,   324,     3,     8,   339,   341,   355,   345,
     347,   351,   349,   353,   343,     8,     3,   285,   205,     4,
     289,   287,   292,     4,     8,     3,   307,     4,     8,     3,
     229,   231,     3,     8,     4,   387,   389,     4,   392,     4,
       4,   396,   399,     4,     4,     4,     4,   405,   408,     3,
       8,   146,   146,   129,     4,     4,     4,     4,   165,     4,
     132,   132,     4,     4,     4,   130,   130,   130,   130,     4,
       4,     4,     4,     4,     4,     4,   130,     4,     4,   171,
       4,     4,   181,    64,   161,   204,   294,   336,   338,   340,
     364,   365,   366,   367,   368,     4,     4,     4,     4,     4,
       4,     4,   130,   132,     4,     4,     4,     4,   251,     4,
       4,   320,     4,     4,     4,     4,     4,     4,     4,     4,
       4,   335,     4,     4,   130,     4,     4,     4,   132,   280,
       4,   132,   304,     4,     4,   227,   132,     4,     4,   130,
       4,   130,   130,     4,     4,   132,   132,   132,   132,     4,
       4,   384,     4,     7,     7,   146,   146,     7,   129,     7,
       7,     5,     5,     5,     5,     5,     5,     7,     7,     7,
       5,   157,    14,    15,   188,   369,     8,     3,   129,   129,
     129,     5,   129,   129,   129,   129,   129,     5,     7,   129,
     148,   150,   129,   129,   157,   129,   129,   129,   129,   129,
     129,   129,   129,   129,   129,   129,   129,   129,   146,   129,
     129,   129,    15,   104,   397,   105,   106,   107,   108,   109,
     132,   406,   129,   146,   170,   111,   415,   416,   417,   180,
      23,    28,    29,    30,    31,    32,    33,    34,   161,   193,
     194,   195,   198,   200,   202,   204,   206,   207,   208,   209,
     193,     7,   244,   245,   246,     7,   272,   273,   274,     7,
     296,   297,   298,    67,    68,    69,    70,   212,   213,   214,
     215,   216,   217,   264,   362,     7,   220,   221,   222,    78,
      79,    80,    81,    82,    83,   234,   235,   236,   237,   238,
     239,   240,   241,    86,    87,   373,   374,   375,   377,   383,
     158,     4,   366,     7,   313,   314,   315,     7,   327,   328,
     329,    73,   358,     8,   418,     3,     8,     8,   196,   199,
     201,   203,     4,     4,     4,     4,     3,     8,     8,   247,
       6,     3,   275,     6,     3,   299,     6,     3,     3,     6,
       3,     6,   223,     6,     3,     4,     4,     4,     4,     4,
       4,     3,     8,   376,   378,     3,     8,     8,   129,   159,
     160,   129,   316,     6,     3,   330,     6,     3,   359,     8,
       4,   416,     4,     4,     4,     4,   132,   130,   132,   130,
     194,   250,   246,   278,   274,   302,   298,   213,   264,   226,
     222,   130,   130,   130,   130,   130,   130,   235,     4,     4,
     374,     6,     3,   319,   315,   333,   329,     4,     5,    24,
      25,    26,    27,   197,   129,   129,   129,     8,     8,     8,
       8,   129,   129,   129,     8,     8,   129,     7,   419,   420,
     421,     3,     6,   112,   114,   115,   161,   204,   422,   423,
     424,   425,   427,   420,   428,     4,   426,     3,     8,     4,
     130,     4,   423,     5,   129,     7,   429,   430,   431,     3,
       6,   113,   432,   433,   430,   434,     3,     8,     4,   433,
     129
  };

  const unsigned short int
  Dhcp4Parser::yyr1_[] =
  {
       0,   133,   135,   134,   136,   134,   137,   134,   138,   134,
     139,   134,   140,   134,   141,   134,   142,   134,   143,   134,
     144,   134,   145,   134,   146,   146,   146,   146,   146,   146,
     146,   147,   149,   148,   150,   151,   151,   152,   152,   154,
     153,   155,   155,   156,   156,   158,   157,   159,   159,   160,
     160,   161,   163,   162,   164,   164,   165,   165,   165,   165,
     165,   167,   166,   169,   168,   170,   170,   171,   171,   171,
     171,   171,   171,   171,   171,   171,   171,   171,   171,   171,
     171,   171,   171,   171,   171,   171,   171,   171,   172,   173,
     174,   175,   176,   177,   179,   178,   180,   180,   181,   181,
     183,   182,   185,   184,   187,   186,   188,   188,   190,   189,
     192,   191,   193,   193,   194,   194,   194,   194,   194,   194,
     194,   194,   194,   194,   196,   195,   197,   197,   197,   197,
     199,   198,   201,   200,   203,   202,   205,   204,   206,   207,
     208,   209,   211,   210,   212,   212,   213,   213,   213,   213,
     214,   215,   216,   217,   219,   218,   220,   220,   221,   221,
     223,   222,   225,   224,   226,   226,   226,   227,   227,   229,
     228,   231,   230,   233,   232,   234,   234,   235,   235,   235,
     235,   235,   235,   236,   237,   238,   239,   240,   241,   243,
     242,   244,   244,   245,   245,   247,   246,   249,   248,   250,
     250,   251,   251,   251,   251,   251,   251,   251,   251,   251,
     251,   251,   251,   251,   251,   251,   251,   251,   251,   251,
     251,   253,   252,   255,   254,   257,   256,   259,   258,   261,
     260,   263,   262,   265,   264,   267,   266,   268,   269,   271,
     270,   272,   272,   273,   273,   275,   274,   277,   276,   278,
     278,   279,   279,   280,   280,   280,   280,   280,   280,   280,
     280,   281,   282,   283,   285,   284,   287,   286,   289,   288,
     290,   292,   291,   293,   295,   294,   296,   296,   297,   297,
     299,   298,   301,   300,   302,   302,   303,   303,   304,   304,
     304,   304,   304,   304,   305,   307,   306,   308,   309,   310,
     312,   311,   313,   313,   314,   314,   316,   315,   318,   317,
     319,   319,   320,   320,   320,   320,   322,   321,   324,   323,
     326,   325,   327,   327,   328,   328,   330,   329,   332,   331,
     333,   333,   334,   334,   335,   335,   335,   335,   335,   335,
     335,   335,   335,   335,   335,   335,   337,   336,   339,   338,
     341,   340,   343,   342,   345,   344,   347,   346,   349,   348,
     351,   350,   353,   352,   355,   354,   357,   356,   359,   358,
     361,   360,   362,   362,   363,   264,   364,   364,   365,   365,
     366,   366,   366,   366,   366,   366,   366,   367,   369,   368,
     370,   372,   371,   373,   373,   374,   374,   376,   375,   378,
     377,   380,   379,   382,   381,   383,   383,   384,   384,   384,
     384,   384,   384,   384,   384,   384,   384,   384,   384,   384,
     384,   384,   384,   385,   387,   386,   389,   388,   390,   392,
     391,   393,   394,   396,   395,   397,   397,   399,   398,   400,
     401,   402,   403,   405,   404,   406,   406,   406,   406,   406,
     408,   407,   410,   409,   412,   411,   414,   413,   415,   415,
     416,   418,   417,   419,   419,   421,   420,   422,   422,   423,
     423,   423,   423,   423,   424,   426,   425,   428,   427,   429,
     429,   431,   430,   432,   432,   434,   433
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
       1,     1,     1,     1,     0,     4,     1,     1,     1,     1,
       0,     4,     0,     4,     0,     4,     0,     4,     3,     3,
       3,     3,     0,     6,     1,     3,     1,     1,     1,     1,
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
       1,     1,     1,     3,     0,     4,     0,     4,     3,     0,
       4,     3,     3,     0,     4,     1,     1,     0,     4,     3,
       3,     3,     3,     0,     4,     1,     1,     1,     1,     1,
       0,     4,     0,     4,     0,     4,     0,     6,     1,     3,
       1,     0,     6,     1,     3,     0,     4,     1,     3,     1,
       1,     1,     1,     1,     3,     0,     4,     0,     6,     1,
       3,     0,     4,     1,     3,     0,     4
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
  "\"host\"", "\"persist\"", "\"lfc-interval\"", "\"readonly\"",
  "\"connect-timeout\"", "\"valid-lifetime\"", "\"renew-timer\"",
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
  "db_type", "user", "$@25", "password", "$@26", "host", "$@27", "name",
  "$@28", "persist", "lfc_interval", "readonly", "connect_timeout",
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
       0,   213,   213,   213,   214,   214,   215,   215,   216,   216,
     217,   217,   218,   218,   219,   219,   220,   220,   221,   221,
     222,   222,   223,   223,   231,   232,   233,   234,   235,   236,
     237,   240,   245,   245,   256,   259,   260,   263,   267,   274,
     274,   281,   282,   285,   289,   296,   296,   303,   304,   307,
     311,   322,   332,   332,   344,   345,   349,   350,   351,   352,
     353,   356,   356,   373,   373,   381,   382,   387,   388,   389,
     390,   391,   392,   393,   394,   395,   396,   397,   398,   399,
     400,   401,   402,   403,   404,   405,   406,   407,   410,   415,
     420,   425,   430,   435,   441,   441,   451,   452,   455,   456,
     459,   459,   467,   467,   477,   477,   484,   485,   488,   488,
     498,   498,   508,   509,   512,   513,   514,   515,   516,   517,
     518,   519,   520,   521,   524,   524,   531,   532,   533,   534,
     537,   537,   545,   545,   553,   553,   561,   561,   569,   574,
     579,   584,   589,   589,   599,   600,   603,   604,   605,   606,
     609,   614,   619,   624,   629,   629,   639,   640,   643,   644,
     647,   647,   655,   655,   663,   664,   665,   668,   669,   672,
     672,   680,   680,   688,   688,   698,   699,   702,   703,   704,
     705,   706,   707,   710,   715,   720,   725,   730,   735,   743,
     743,   756,   757,   760,   761,   768,   768,   791,   791,   800,
     801,   805,   806,   807,   808,   809,   810,   811,   812,   813,
     814,   815,   816,   817,   818,   819,   820,   821,   822,   823,
     824,   827,   827,   835,   835,   843,   843,   851,   851,   859,
     859,   867,   867,   875,   875,   883,   883,   891,   896,   905,
     905,   917,   918,   921,   922,   927,   927,   938,   938,   948,
     949,   952,   953,   956,   957,   958,   959,   960,   961,   962,
     963,   966,   968,   973,   975,   975,   983,   983,   991,   991,
     999,  1001,  1001,  1009,  1018,  1018,  1030,  1031,  1036,  1037,
    1042,  1042,  1053,  1053,  1064,  1065,  1070,  1071,  1076,  1077,
    1078,  1079,  1080,  1081,  1084,  1086,  1086,  1094,  1096,  1098,
    1106,  1106,  1118,  1119,  1122,  1123,  1126,  1126,  1134,  1134,
    1142,  1143,  1146,  1147,  1148,  1149,  1152,  1152,  1160,  1160,
    1170,  1170,  1180,  1181,  1184,  1185,  1188,  1188,  1196,  1196,
    1204,  1205,  1208,  1209,  1213,  1214,  1215,  1216,  1217,  1218,
    1219,  1220,  1221,  1222,  1223,  1224,  1227,  1227,  1235,  1235,
    1243,  1243,  1251,  1251,  1259,  1259,  1267,  1267,  1275,  1275,
    1283,  1283,  1292,  1292,  1300,  1300,  1313,  1313,  1323,  1323,
    1334,  1334,  1344,  1345,  1348,  1348,  1356,  1357,  1360,  1361,
    1364,  1365,  1366,  1367,  1368,  1369,  1370,  1373,  1375,  1375,
    1387,  1394,  1394,  1404,  1405,  1408,  1409,  1412,  1412,  1420,
    1420,  1430,  1430,  1440,  1440,  1448,  1449,  1452,  1453,  1454,
    1455,  1456,  1457,  1458,  1459,  1460,  1461,  1462,  1463,  1464,
    1465,  1466,  1467,  1470,  1475,  1475,  1483,  1483,  1491,  1496,
    1496,  1504,  1509,  1514,  1514,  1522,  1523,  1526,  1526,  1534,
    1539,  1544,  1549,  1554,  1554,  1562,  1565,  1568,  1571,  1574,
    1580,  1580,  1590,  1590,  1597,  1597,  1609,  1609,  1622,  1623,
    1627,  1631,  1631,  1643,  1644,  1648,  1648,  1656,  1657,  1660,
    1661,  1662,  1663,  1664,  1667,  1671,  1671,  1679,  1679,  1689,
    1690,  1693,  1693,  1701,  1702,  1705,  1705
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
#line 3996 "dhcp4_parser.cc" // lalr1.cc:1167
#line 1713 "dhcp4_parser.yy" // lalr1.cc:1168


void
isc::dhcp::Dhcp4Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
