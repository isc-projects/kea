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
      case 153: // value
      case 157: // map_value
      case 195: // socket_type
      case 205: // db_type
      case 413: // ncr_protocol_value
      case 421: // replace_client_name_value
        value.move< ElementPtr > (that.value);
        break;

      case 139: // "boolean"
        value.move< bool > (that.value);
        break;

      case 138: // "floating point"
        value.move< double > (that.value);
        break;

      case 137: // "integer"
        value.move< int64_t > (that.value);
        break;

      case 136: // "constant string"
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
      case 153: // value
      case 157: // map_value
      case 195: // socket_type
      case 205: // db_type
      case 413: // ncr_protocol_value
      case 421: // replace_client_name_value
        value.copy< ElementPtr > (that.value);
        break;

      case 139: // "boolean"
        value.copy< bool > (that.value);
        break;

      case 138: // "floating point"
        value.copy< double > (that.value);
        break;

      case 137: // "integer"
        value.copy< int64_t > (that.value);
        break;

      case 136: // "constant string"
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
            case 136: // "constant string"

#line 211 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< std::string > (); }
#line 362 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 137: // "integer"

#line 211 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< int64_t > (); }
#line 369 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 138: // "floating point"

#line 211 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< double > (); }
#line 376 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 139: // "boolean"

#line 211 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< bool > (); }
#line 383 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 153: // value

#line 211 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 390 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 157: // map_value

#line 211 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 397 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 195: // socket_type

#line 211 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 404 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 205: // db_type

#line 211 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 411 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 413: // ncr_protocol_value

#line 211 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 418 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 421: // replace_client_name_value

#line 211 "dhcp4_parser.yy" // lalr1.cc:636
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
      case 153: // value
      case 157: // map_value
      case 195: // socket_type
      case 205: // db_type
      case 413: // ncr_protocol_value
      case 421: // replace_client_name_value
        yylhs.value.build< ElementPtr > ();
        break;

      case 139: // "boolean"
        yylhs.value.build< bool > ();
        break;

      case 138: // "floating point"
        yylhs.value.build< double > ();
        break;

      case 137: // "integer"
        yylhs.value.build< int64_t > ();
        break;

      case 136: // "constant string"
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
#line 220 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.NO_KEYWORD; }
#line 670 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 4:
#line 221 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.CONFIG; }
#line 676 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 6:
#line 222 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.DHCP4; }
#line 682 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 8:
#line 223 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.INTERFACES_CONFIG; }
#line 688 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 10:
#line 224 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.SUBNET4; }
#line 694 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 12:
#line 225 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.POOLS; }
#line 700 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 14:
#line 226 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.RESERVATIONS; }
#line 706 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 16:
#line 227 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.OPTION_DEF; }
#line 712 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 18:
#line 228 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.OPTION_DATA; }
#line 718 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 20:
#line 229 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.HOOKS_LIBRARIES; }
#line 724 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 22:
#line 230 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.DHCP_DDNS; }
#line 730 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 24:
#line 238 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 736 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 25:
#line 239 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as< double > (), ctx.loc2pos(yystack_[0].location))); }
#line 742 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 26:
#line 240 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 748 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 27:
#line 241 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 754 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 28:
#line 242 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 760 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 29:
#line 243 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 766 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 30:
#line 244 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 772 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 31:
#line 247 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as< ElementPtr > ());
}
#line 781 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 32:
#line 252 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 792 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 33:
#line 257 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 802 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 34:
#line 263 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 808 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 37:
#line 270 "dhcp4_parser.yy" // lalr1.cc:859
    {
                  // map containing a single entry
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 817 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 38:
#line 274 "dhcp4_parser.yy" // lalr1.cc:859
    {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 827 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 39:
#line 281 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 836 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 40:
#line 284 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // list parsing complete. Put any sanity checking here
}
#line 844 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 43:
#line 292 "dhcp4_parser.yy" // lalr1.cc:859
    {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 853 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 44:
#line 296 "dhcp4_parser.yy" // lalr1.cc:859
    {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 862 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 45:
#line 303 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // List parsing about to start
}
#line 870 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 46:
#line 305 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // list parsing complete. Put any sanity checking here
    //ctx.stack_.pop_back();
}
#line 879 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 49:
#line 314 "dhcp4_parser.yy" // lalr1.cc:859
    {
                          ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 888 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 50:
#line 318 "dhcp4_parser.yy" // lalr1.cc:859
    {
                          ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 897 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 51:
#line 329 "dhcp4_parser.yy" // lalr1.cc:859
    {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as< std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 908 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 52:
#line 339 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 919 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 53:
#line 344 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 929 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 61:
#line 363 "dhcp4_parser.yy" // lalr1.cc:859
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
#line 370 "dhcp4_parser.yy" // lalr1.cc:859
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
#line 380 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the Dhcp4 map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 964 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 64:
#line 384 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 972 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 88:
#line 417 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 981 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 89:
#line 422 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 990 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 90:
#line 427 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 999 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 91:
#line 432 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr dpp(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 1008 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 92:
#line 437 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr echo(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("echo-client-id", echo);
}
#line 1017 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 93:
#line 442 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr match(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("match-client-id", match);
}
#line 1026 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 94:
#line 448 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces-config", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.INTERFACES_CONFIG);
}
#line 1037 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 95:
#line 453 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1046 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 101:
#line 467 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1056 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 102:
#line 471 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1064 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 103:
#line 475 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1075 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 104:
#line 480 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1084 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 105:
#line 485 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.DHCP_SOCKET_TYPE);
}
#line 1092 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 106:
#line 487 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("dhcp-socket-type", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1101 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 107:
#line 492 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("raw", ctx.loc2pos(yystack_[0].location))); }
#line 1107 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 108:
#line 493 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("udp", ctx.loc2pos(yystack_[0].location))); }
#line 1113 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 109:
#line 496 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("re-detect", b);
}
#line 1122 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 110:
#line 502 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lease-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.LEASE_DATABASE);
}
#line 1133 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 111:
#line 507 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1142 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 112:
#line 512 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1153 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 113:
#line 517 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1162 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 129:
#line 541 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.DATABASE_TYPE);
}
#line 1170 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 130:
#line 543 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("type", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1179 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 131:
#line 548 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("memfile", ctx.loc2pos(yystack_[0].location))); }
#line 1185 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 132:
#line 549 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("mysql", ctx.loc2pos(yystack_[0].location))); }
#line 1191 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 133:
#line 550 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("postgresql", ctx.loc2pos(yystack_[0].location))); }
#line 1197 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 134:
#line 551 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("cql", ctx.loc2pos(yystack_[0].location))); }
#line 1203 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 135:
#line 554 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1211 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 136:
#line 556 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr user(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1221 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 137:
#line 562 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1229 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 138:
#line 564 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr pwd(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 1239 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 139:
#line 570 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1247 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 140:
#line 572 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr h(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 1257 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 141:
#line 578 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr p(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", p);
}
#line 1266 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 142:
#line 583 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1274 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 143:
#line 585 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1284 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 144:
#line 591 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 1293 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 145:
#line 596 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 1302 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 146:
#line 601 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 1311 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 147:
#line 606 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("connect-timeout", n);
}
#line 1320 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 148:
#line 611 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1328 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 149:
#line 613 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr cp(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("contact-points", cp);
    ctx.leave();
}
#line 1338 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 150:
#line 619 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1346 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 151:
#line 621 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr ks(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("keyspace", ks);
    ctx.leave();
}
#line 1356 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 152:
#line 628 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 1367 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 153:
#line 633 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1376 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 161:
#line 649 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1385 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 162:
#line 654 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 1394 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 163:
#line 659 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr circuit(new StringElement("circuit-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(circuit);
}
#line 1403 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 164:
#line 664 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr client(new StringElement("client-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(client);
}
#line 1412 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 165:
#line 669 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr flex_id(new StringElement("flex-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(flex_id);
}
#line 1421 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 166:
#line 674 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 1432 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 167:
#line 679 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1441 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 172:
#line 692 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1451 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 173:
#line 696 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1459 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 174:
#line 700 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1469 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 175:
#line 704 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1477 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 181:
#line 717 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1485 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 182:
#line 719 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr lib(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 1495 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 183:
#line 725 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1503 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 184:
#line 727 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1512 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 185:
#line 733 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.EXPIRED_LEASES_PROCESSING);
}
#line 1523 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 186:
#line 738 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1532 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 195:
#line 755 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 1541 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 196:
#line 760 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 1550 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 197:
#line 765 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 1559 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 198:
#line 770 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 1568 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 199:
#line 775 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 1577 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 200:
#line 780 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 1586 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 201:
#line 788 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet4", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET4);
}
#line 1597 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 202:
#line 793 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1606 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 207:
#line 813 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1616 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 208:
#line 817 "dhcp4_parser.yy" // lalr1.cc:859
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
#line 1639 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 209:
#line 836 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the subnet4 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1649 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 210:
#line 840 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1657 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 233:
#line 872 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1665 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 234:
#line 874 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr subnet(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 1675 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 235:
#line 880 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1683 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 236:
#line 882 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface", iface);
    ctx.leave();
}
#line 1693 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 237:
#line 888 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1701 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 238:
#line 890 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface-id", iface);
    ctx.leave();
}
#line 1711 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 239:
#line 896 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1719 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 240:
#line 898 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-subnet", iface);
    ctx.leave();
}
#line 1729 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 241:
#line 904 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1737 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 242:
#line 906 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 1747 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 243:
#line 912 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1755 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 244:
#line 914 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface-id", iface);
    ctx.leave();
}
#line 1765 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 245:
#line 920 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.CLIENT_CLASS);
}
#line 1773 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 246:
#line 922 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr cls(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 1783 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 247:
#line 928 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1791 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 248:
#line 930 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr rm(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservation-mode", rm);
    ctx.leave();
}
#line 1801 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 249:
#line 936 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr id(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 1810 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 250:
#line 941 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr rc(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rapid-commit", rc);
}
#line 1819 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 251:
#line 950 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 1830 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 252:
#line 955 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1839 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 257:
#line 972 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1849 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 258:
#line 976 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1857 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 259:
#line 983 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1867 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 260:
#line 987 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1875 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 274:
#line 1013 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr code(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 1884 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 276:
#line 1020 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1892 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 277:
#line 1022 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 1902 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 278:
#line 1028 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1910 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 279:
#line 1030 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 1920 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 280:
#line 1036 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1928 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 281:
#line 1038 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr space(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 1938 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 283:
#line 1046 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1946 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 284:
#line 1048 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr encap(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 1956 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 285:
#line 1054 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr array(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 1965 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 286:
#line 1063 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 1976 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 287:
#line 1068 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1985 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 292:
#line 1087 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1995 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 293:
#line 1091 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2003 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 294:
#line 1098 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2013 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 295:
#line 1102 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 2021 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 307:
#line 1131 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2029 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 308:
#line 1133 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr data(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 2039 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 311:
#line 1143 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr space(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", space);
}
#line 2048 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 312:
#line 1151 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 2059 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 313:
#line 1156 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2068 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 318:
#line 1171 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2078 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 319:
#line 1175 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2086 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 320:
#line 1179 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2096 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 321:
#line 1183 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 2104 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 328:
#line 1197 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2112 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 329:
#line 1199 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr pool(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 2122 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 330:
#line 1205 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2130 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 331:
#line 1207 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("user-context", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2139 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 332:
#line 1215 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 2150 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 333:
#line 1220 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2159 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 338:
#line 1233 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2169 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 339:
#line 1237 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2177 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 340:
#line 1241 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2187 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 341:
#line 1245 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 2195 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 359:
#line 1273 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2203 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 360:
#line 1275 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr next_server(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("next-server", next_server);
    ctx.leave();
}
#line 2213 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 361:
#line 1281 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2221 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 362:
#line 1283 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr srv(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-hostname", srv);
    ctx.leave();
}
#line 2231 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 363:
#line 1289 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2239 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 364:
#line 1291 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr bootfile(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("boot-file-name", bootfile);
    ctx.leave();
}
#line 2249 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 365:
#line 1297 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2257 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 366:
#line 1299 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr addr(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", addr);
    ctx.leave();
}
#line 2267 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 367:
#line 1305 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2275 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 368:
#line 1307 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr d(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 2285 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 369:
#line 1313 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2293 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 370:
#line 1315 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 2303 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 371:
#line 1321 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2311 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 372:
#line 1323 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-id", hw);
    ctx.leave();
}
#line 2321 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 373:
#line 1329 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2329 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 374:
#line 1331 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("circuit-id", hw);
    ctx.leave();
}
#line 2339 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 375:
#line 1337 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2347 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 376:
#line 1339 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flex-id", hw);
    ctx.leave();
}
#line 2357 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 377:
#line 1345 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2365 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 378:
#line 1347 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr host(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 2375 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 379:
#line 1353 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2386 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 380:
#line 1358 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2395 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 381:
#line 1366 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 2406 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 382:
#line 1371 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2415 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 383:
#line 1376 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2423 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 384:
#line 1378 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr ip(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", ip);
    ctx.leave();
}
#line 2433 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 385:
#line 1387 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 2444 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 386:
#line 1392 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2453 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 389:
#line 1401 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2463 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 390:
#line 1405 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2471 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 403:
#line 1428 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2479 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 404:
#line 1430 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr test(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 2489 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 405:
#line 1440 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 2498 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 406:
#line 1447 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 2509 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 407:
#line 1452 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2518 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 412:
#line 1465 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2526 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 413:
#line 1467 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr stype(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 2536 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 414:
#line 1473 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2544 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 415:
#line 1475 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 2554 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 416:
#line 1483 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 2565 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 417:
#line 1488 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2574 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 418:
#line 1493 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2584 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 419:
#line 1497 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 2592 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 437:
#line 1522 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 2601 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 438:
#line 1527 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2609 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 439:
#line 1529 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("qualifying-suffix", s);
    ctx.leave();
}
#line 2619 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 440:
#line 1535 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2627 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 441:
#line 1537 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 2637 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 442:
#line 1543 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 2646 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 443:
#line 1548 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2654 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 444:
#line 1550 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 2664 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 445:
#line 1556 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 2673 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 446:
#line 1561 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 2682 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 447:
#line 1566 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 2690 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 448:
#line 1568 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2699 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 449:
#line 1574 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 2705 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 450:
#line 1575 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 2711 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 451:
#line 1578 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NCR_FORMAT);
}
#line 2719 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 452:
#line 1580 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 2729 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 453:
#line 1586 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-include-fqdn", b);
}
#line 2738 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 454:
#line 1591 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-no-update", b);
}
#line 2747 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 455:
#line 1596 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-client-update", b);
}
#line 2756 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 456:
#line 1601 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 2764 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 457:
#line 1603 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("replace-client-name", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2773 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 458:
#line 1609 "dhcp4_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("when-present", ctx.loc2pos(yystack_[0].location))); 
      }
#line 2781 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 459:
#line 1612 "dhcp4_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location)));
      }
#line 2789 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 460:
#line 1615 "dhcp4_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("always", ctx.loc2pos(yystack_[0].location)));
      }
#line 2797 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 461:
#line 1618 "dhcp4_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("when-not-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 2805 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 462:
#line 1621 "dhcp4_parser.yy" // lalr1.cc:859
    {
      error(yystack_[0].location, "boolean values for the replace-client-name are "
                "no longer supported");
      }
#line 2814 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 463:
#line 1627 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2822 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 464:
#line 1629 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("generated-prefix", s);
    ctx.leave();
}
#line 2832 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 465:
#line 1637 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2840 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 466:
#line 1639 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("Dhcp6", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2849 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 467:
#line 1644 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2857 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 468:
#line 1646 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("DhcpDdns", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2866 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 469:
#line 1656 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Logging", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.LOGGING);
}
#line 2877 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 470:
#line 1661 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2886 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 474:
#line 1678 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 2897 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 475:
#line 1683 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2906 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 478:
#line 1695 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 2916 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 479:
#line 1699 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2924 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 487:
#line 1714 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr dl(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 2933 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 488:
#line 1719 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2941 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 489:
#line 1721 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 2951 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 490:
#line 1727 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 2962 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 491:
#line 1732 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2971 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 494:
#line 1741 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2981 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 495:
#line 1745 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2989 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 502:
#line 1759 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2997 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 503:
#line 1761 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 3007 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 504:
#line 1767 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr flush(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 3016 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 505:
#line 1772 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr maxsize(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 3025 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 506:
#line 1777 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr maxver(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 3034 "dhcp4_parser.cc" // lalr1.cc:859
    break;


#line 3038 "dhcp4_parser.cc" // lalr1.cc:859
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


  const short int Dhcp4Parser::yypact_ninf_ = -477;

  const signed char Dhcp4Parser::yytable_ninf_ = -1;

  const short int
  Dhcp4Parser::yypact_[] =
  {
     108,  -477,  -477,  -477,  -477,  -477,  -477,  -477,  -477,  -477,
    -477,  -477,    65,    19,    23,    86,   109,   129,   130,   131,
     170,   183,   185,   187,  -477,  -477,  -477,  -477,  -477,  -477,
    -477,  -477,  -477,  -477,  -477,  -477,  -477,  -477,  -477,  -477,
    -477,  -477,  -477,  -477,  -477,  -477,  -477,  -477,  -477,  -477,
    -477,  -477,  -477,  -477,  -477,  -477,    19,    69,    17,    80,
     136,    18,   -19,   113,   127,    -1,   -46,   123,  -477,   169,
     204,   207,   223,   212,  -477,  -477,  -477,  -477,   240,  -477,
      30,  -477,  -477,  -477,  -477,  -477,  -477,   250,   262,  -477,
    -477,  -477,   266,   270,   276,   280,  -477,  -477,  -477,  -477,
    -477,  -477,  -477,   283,  -477,  -477,  -477,    38,  -477,  -477,
    -477,  -477,  -477,  -477,  -477,  -477,  -477,  -477,  -477,  -477,
    -477,  -477,  -477,  -477,  -477,  -477,  -477,  -477,  -477,  -477,
    -477,   284,    39,  -477,  -477,  -477,  -477,  -477,  -477,  -477,
    -477,  -477,  -477,  -477,  -477,   286,   294,  -477,  -477,  -477,
    -477,  -477,  -477,  -477,  -477,  -477,    52,  -477,  -477,  -477,
    -477,  -477,  -477,  -477,  -477,  -477,  -477,  -477,  -477,  -477,
    -477,  -477,  -477,  -477,  -477,  -477,  -477,    53,  -477,  -477,
    -477,  -477,  -477,  -477,  -477,  -477,  -477,  -477,  -477,  -477,
    -477,  -477,  -477,   243,   255,  -477,  -477,  -477,  -477,  -477,
    -477,  -477,  -477,  -477,  -477,  -477,  -477,  -477,  -477,   299,
    -477,  -477,  -477,   300,  -477,  -477,   298,   274,  -477,  -477,
    -477,  -477,  -477,  -477,  -477,  -477,  -477,  -477,  -477,   303,
    -477,  -477,  -477,  -477,   301,   305,  -477,  -477,  -477,  -477,
    -477,  -477,  -477,  -477,  -477,    68,  -477,  -477,  -477,   306,
    -477,  -477,   307,  -477,   308,   309,  -477,  -477,   311,   313,
     314,  -477,  -477,  -477,    81,  -477,  -477,  -477,  -477,  -477,
    -477,  -477,  -477,  -477,  -477,  -477,  -477,  -477,  -477,  -477,
    -477,    19,    19,  -477,   184,   315,   317,   318,   319,  -477,
      17,  -477,   321,   188,   189,   322,   325,   326,   194,   195,
     196,   197,   331,   332,   333,   334,   335,   336,   337,   205,
     339,   340,    80,  -477,   341,   342,   208,   136,  -477,    24,
     344,   345,   346,   347,   348,   351,   352,   220,   219,   355,
     356,   357,   358,    18,  -477,   359,   360,   -19,  -477,   361,
     362,   363,   364,   365,   366,   367,   368,   369,   370,  -477,
     113,   371,   372,   241,   373,   375,   376,   242,  -477,   127,
     378,   246,  -477,    -1,   379,   380,   -27,  -477,   248,   382,
     384,   252,   386,   256,   258,   387,   388,   259,   260,   263,
     390,   392,   123,  -477,  -477,  -477,   393,   394,   396,    19,
      19,  -477,   397,  -477,  -477,   271,   398,   399,  -477,  -477,
    -477,  -477,   395,   403,   404,   405,   406,   407,   408,  -477,
     409,   410,  -477,   413,   115,  -477,  -477,  -477,  -477,  -477,
    -477,  -477,  -477,  -477,   411,   417,  -477,  -477,  -477,   277,
     278,   285,   418,   288,   289,   290,  -477,  -477,   291,   292,
     424,   415,  -477,   296,   427,  -477,   302,   304,   413,   310,
     316,   320,   323,   328,   329,   330,  -477,   338,   343,  -477,
     349,   350,   353,  -477,  -477,   354,  -477,  -477,   374,    19,
    -477,  -477,   377,   381,  -477,   383,  -477,  -477,    16,   385,
    -477,  -477,  -477,   -43,   389,  -477,    19,    80,   324,  -477,
    -477,   136,  -477,    76,    76,   430,   434,   435,    92,    25,
     436,   114,    -6,   123,  -477,  -477,  -477,  -477,  -477,   440,
    -477,    24,  -477,  -477,  -477,   442,  -477,  -477,  -477,  -477,
    -477,   444,   391,  -477,  -477,  -477,  -477,  -477,  -477,  -477,
    -477,  -477,  -477,  -477,  -477,  -477,  -477,  -477,  -477,  -477,
    -477,  -477,  -477,  -477,  -477,  -477,  -477,  -477,  -477,  -477,
    -477,  -477,  -477,  -477,  -477,  -477,  -477,  -477,  -477,   142,
    -477,   164,  -477,  -477,   200,  -477,  -477,  -477,  -477,   443,
     450,   451,   453,   454,  -477,  -477,  -477,   201,  -477,  -477,
    -477,  -477,  -477,  -477,  -477,  -477,  -477,  -477,  -477,  -477,
    -477,   244,  -477,   455,   459,  -477,  -477,   461,   465,  -477,
    -477,   464,   468,  -477,  -477,  -477,  -477,  -477,  -477,    71,
    -477,  -477,  -477,  -477,  -477,  -477,  -477,    98,  -477,   466,
     470,  -477,   471,   472,   473,   474,   476,   477,   245,  -477,
    -477,  -477,  -477,  -477,  -477,  -477,  -477,  -477,   247,  -477,
    -477,  -477,   254,   400,   401,  -477,  -477,   478,   479,  -477,
    -477,   481,   480,  -477,  -477,   483,  -477,   484,   324,  -477,
    -477,   488,   489,   491,   492,   402,   412,   416,   419,   420,
     493,   494,    76,  -477,  -477,    18,  -477,   430,   127,  -477,
     434,    -1,  -477,   435,    92,  -477,    25,  -477,   -46,  -477,
     436,   422,   423,   425,   426,   428,   429,   114,  -477,   495,
     496,    -6,  -477,  -477,  -477,   497,   498,  -477,   -19,  -477,
     442,   113,  -477,   444,   500,  -477,   501,  -477,   269,   414,
     431,   432,  -477,  -477,  -477,  -477,  -477,   433,   437,  -477,
     257,  -477,   499,  -477,   503,  -477,  -477,  -477,   261,  -477,
    -477,  -477,  -477,  -477,  -477,  -477,  -477,   438,   439,  -477,
    -477,   441,   264,  -477,   504,  -477,   445,   502,  -477,  -477,
    -477,  -477,  -477,  -477,  -477,  -477,  -477,  -477,  -477,  -477,
    -477,  -477,  -477,  -477,  -477,  -477,  -477,  -477,  -477,   112,
    -477,    77,   502,  -477,  -477,   510,  -477,  -477,  -477,   273,
    -477,  -477,  -477,  -477,  -477,   511,   446,   512,    77,  -477,
     513,  -477,   448,  -477,   514,  -477,  -477,   168,  -477,    22,
     514,  -477,  -477,   516,   518,   519,   275,  -477,  -477,  -477,
    -477,  -477,  -477,   520,   447,   452,   456,    22,  -477,   449,
    -477,  -477,  -477,  -477,  -477
  };

  const unsigned short int
  Dhcp4Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     1,    39,    32,    28,    27,    24,
      25,    26,    31,     3,    29,    30,    52,     5,    63,     7,
     101,     9,   209,    11,   320,    13,   340,    15,   259,    17,
     294,    19,   174,    21,   418,    23,    41,    35,     0,     0,
       0,     0,     0,   342,   261,   296,     0,     0,    43,     0,
      42,     0,     0,    36,    61,   469,   465,   467,     0,    60,
       0,    54,    56,    58,    59,    57,    94,     0,     0,   359,
     110,   112,     0,     0,     0,     0,   201,   251,   286,   152,
     385,   166,   185,     0,   406,   416,    87,     0,    65,    67,
      68,    69,    70,    84,    85,    72,    73,    74,    75,    79,
      80,    71,    77,    78,    86,    76,    81,    82,    83,   103,
     105,     0,     0,    96,    98,    99,   100,   389,   235,   237,
     239,   312,   233,   241,   243,     0,     0,   247,   245,   332,
     381,   232,   213,   214,   215,   227,     0,   211,   218,   229,
     230,   231,   219,   220,   223,   225,   221,   222,   216,   217,
     224,   228,   226,   328,   330,   327,   325,     0,   322,   324,
     326,   361,   363,   379,   367,   369,   373,   371,   377,   375,
     365,   358,   354,     0,   343,   344,   355,   356,   357,   351,
     346,   352,   348,   349,   350,   353,   347,   276,   142,     0,
     280,   278,   283,     0,   272,   273,     0,   262,   263,   265,
     275,   266,   267,   268,   282,   269,   270,   271,   307,     0,
     305,   306,   309,   310,     0,   297,   298,   300,   301,   302,
     303,   304,   181,   183,   178,     0,   176,   179,   180,     0,
     438,   440,     0,   443,     0,     0,   447,   451,     0,     0,
       0,   456,   463,   436,     0,   420,   422,   423,   424,   425,
     426,   427,   428,   429,   430,   431,   432,   433,   434,   435,
      40,     0,     0,    33,     0,     0,     0,     0,     0,    51,
       0,    53,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    64,     0,     0,     0,     0,   102,   391,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   210,     0,     0,     0,   321,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   341,
       0,     0,     0,     0,     0,     0,     0,     0,   260,     0,
       0,     0,   295,     0,     0,     0,     0,   175,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   419,    44,    37,     0,     0,     0,     0,
       0,    55,     0,    92,    93,     0,     0,     0,    88,    89,
      90,    91,     0,     0,     0,     0,     0,     0,     0,   405,
       0,     0,    66,     0,     0,   109,    97,   403,   401,   402,
     397,   398,   399,   400,     0,   392,   393,   395,   396,     0,
       0,     0,     0,     0,     0,     0,   249,   250,     0,     0,
       0,     0,   212,     0,     0,   323,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   345,     0,     0,   274,
       0,     0,     0,   285,   264,     0,   311,   299,     0,     0,
     177,   437,     0,     0,   442,     0,   445,   446,     0,     0,
     453,   454,   455,     0,     0,   421,     0,     0,     0,   466,
     468,     0,   360,     0,     0,   203,   253,   288,     0,     0,
     168,     0,     0,     0,    45,   104,   107,   108,   106,     0,
     390,     0,   236,   238,   240,   314,   234,   242,   244,   248,
     246,   334,     0,   329,    34,   331,   362,   364,   380,   368,
     370,   374,   372,   378,   376,   366,   277,   143,   281,   279,
     284,   308,   182,   184,   439,   441,   444,   449,   450,   448,
     452,   458,   459,   460,   461,   462,   457,   464,    38,     0,
     474,     0,   471,   473,     0,   129,   135,   137,   139,     0,
       0,     0,     0,     0,   148,   150,   128,     0,   114,   116,
     117,   118,   119,   120,   121,   122,   123,   124,   125,   126,
     127,     0,   207,     0,   204,   205,   257,     0,   254,   255,
     292,     0,   289,   290,   161,   162,   163,   164,   165,     0,
     154,   156,   157,   158,   159,   160,   387,     0,   172,     0,
     169,   170,     0,     0,     0,     0,     0,     0,     0,   187,
     189,   190,   191,   192,   193,   194,   412,   414,     0,   408,
     410,   411,     0,    47,     0,   394,   318,     0,   315,   316,
     338,     0,   335,   336,   383,     0,    62,     0,     0,   470,
      95,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   111,   113,     0,   202,     0,   261,   252,
       0,   296,   287,     0,     0,   153,     0,   386,     0,   167,
       0,     0,     0,     0,     0,     0,     0,     0,   186,     0,
       0,     0,   407,   417,    49,     0,    48,   404,     0,   313,
       0,   342,   333,     0,     0,   382,     0,   472,     0,     0,
       0,     0,   141,   144,   145,   146,   147,     0,     0,   115,
       0,   206,     0,   256,     0,   291,   155,   388,     0,   171,
     195,   196,   197,   198,   199,   200,   188,     0,     0,   409,
      46,     0,     0,   317,     0,   337,     0,     0,   131,   132,
     133,   134,   130,   136,   138,   140,   149,   151,   208,   258,
     293,   173,   413,   415,    50,   319,   339,   384,   478,     0,
     476,     0,     0,   475,   490,     0,   488,   486,   482,     0,
     480,   484,   485,   483,   477,     0,     0,     0,     0,   479,
       0,   487,     0,   481,     0,   489,   494,     0,   492,     0,
       0,   491,   502,     0,     0,     0,     0,   496,   498,   499,
     500,   501,   493,     0,     0,     0,     0,     0,   495,     0,
     504,   505,   506,   497,   503
  };

  const short int
  Dhcp4Parser::yypgoto_[] =
  {
    -477,  -477,  -477,  -477,  -477,  -477,  -477,  -477,  -477,  -477,
    -477,  -477,  -477,   -36,  -477,    58,  -477,  -477,  -477,  -477,
    -477,  -477,  -477,  -477,    57,  -477,  -477,  -477,   -58,  -477,
    -477,  -477,   218,  -477,  -477,  -477,  -477,    40,   214,   -60,
     -44,   -42,  -477,  -477,   -40,  -477,  -477,    37,   213,  -477,
    -477,  -477,  -477,  -477,  -477,  -477,  -477,  -477,  -477,  -477,
    -477,    35,  -141,  -477,  -477,  -477,  -477,  -477,  -477,  -477,
    -477,  -477,  -477,   -63,  -477,  -477,  -477,  -477,  -477,  -477,
    -477,  -477,  -477,  -477,  -477,  -477,  -152,  -477,  -477,  -477,
    -477,  -477,  -477,  -477,  -477,  -477,  -157,  -477,  -477,  -477,
    -154,   172,  -477,  -477,  -477,  -477,  -477,  -477,  -477,  -162,
    -477,  -477,  -477,  -477,  -477,  -477,  -477,  -477,  -477,  -477,
    -137,  -477,  -477,  -477,  -134,   209,  -477,  -477,  -477,  -477,
    -477,  -477,  -477,  -477,  -477,  -477,  -477,  -477,  -476,  -477,
    -477,  -477,  -477,  -477,  -477,  -477,  -477,  -477,  -136,  -477,
    -477,  -477,  -135,  -477,   186,  -477,   -49,  -477,  -477,  -477,
    -477,  -477,   -47,  -477,  -477,  -477,  -477,  -477,   -51,  -477,
    -477,  -477,  -131,  -477,  -477,  -477,  -133,  -477,   191,  -477,
    -477,  -477,  -477,  -477,  -477,  -477,  -477,  -477,  -477,  -164,
    -477,  -477,  -477,  -161,   224,  -477,  -477,  -477,  -477,  -477,
    -477,  -477,  -477,  -158,  -477,  -477,  -477,  -155,  -477,   199,
     -48,  -477,  -305,  -477,  -297,  -477,  -477,  -477,  -477,  -477,
    -477,  -477,  -477,  -477,  -477,  -477,  -477,  -477,  -477,  -477,
    -477,  -477,  -477,  -477,  -477,  -477,  -477,  -477,  -477,  -477,
    -477,  -477,    59,  -477,  -477,  -477,  -477,  -477,  -477,  -477,
    -130,  -477,  -477,  -477,  -477,  -477,  -477,  -477,  -477,    61,
     190,  -477,  -477,  -477,  -477,  -477,  -477,  -477,  -477,  -477,
    -477,  -477,  -477,  -477,  -477,  -477,  -477,  -477,  -477,  -477,
    -477,  -477,  -477,  -477,  -477,  -477,  -477,  -477,  -477,  -477,
    -477,   -82,  -477,  -477,  -477,  -204,  -477,  -477,  -219,  -477,
    -477,  -477,  -477,  -477,  -477,  -230,  -477,  -477,  -245,  -477,
    -477,  -477,  -477,  -477
  };

  const short int
  Dhcp4Parser::yydefgoto_[] =
  {
      -1,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    32,    33,    34,    57,   525,    72,    73,
      35,    56,    69,    70,   505,   643,   705,   706,   106,    37,
      58,    80,    81,    82,   285,    39,    59,   107,   108,   109,
     110,   111,   112,   113,   114,   115,   292,   132,   133,    41,
      60,   134,   314,   135,   315,   508,   136,   116,   296,   117,
     297,   577,   578,   579,   661,   762,   580,   662,   581,   663,
     582,   664,   583,   215,   352,   585,   586,   587,   588,   589,
     670,   590,   671,   118,   305,   609,   610,   611,   612,   613,
     614,   615,   119,   307,   619,   620,   621,   688,    53,    66,
     245,   246,   247,   364,   248,   365,   120,   308,   628,   629,
     630,   631,   632,   633,   634,   635,   121,   302,   593,   594,
     595,   675,    43,    61,   156,   157,   158,   324,   159,   320,
     160,   321,   161,   322,   162,   325,   163,   326,   164,   330,
     165,   329,   166,   167,   122,   303,   597,   598,   599,   678,
      49,    64,   216,   217,   218,   219,   220,   221,   222,   351,
     223,   355,   224,   354,   225,   226,   356,   227,   123,   304,
     601,   602,   603,   681,    51,    65,   234,   235,   236,   237,
     238,   360,   239,   240,   241,   169,   323,   647,   648,   649,
     708,    45,    62,   177,   178,   179,   335,   180,   336,   170,
     331,   651,   652,   653,   711,    47,    63,   193,   194,   195,
     124,   295,   197,   339,   198,   340,   199,   348,   200,   342,
     201,   343,   202,   345,   203,   344,   204,   347,   205,   346,
     206,   341,   172,   332,   655,   714,   125,   306,   617,   319,
     424,   425,   426,   427,   428,   509,   126,   127,   310,   638,
     639,   640,   699,   641,   700,   128,   311,    55,    67,   264,
     265,   266,   267,   369,   268,   370,   269,   270,   372,   271,
     272,   273,   375,   549,   274,   376,   275,   276,   277,   278,
     380,   556,   279,   381,    83,   287,    84,   288,    85,   286,
     561,   562,   563,   657,   779,   780,   781,   789,   790,   791,
     792,   797,   793,   795,   807,   808,   809,   816,   817,   818,
     823,   819,   820,   821
  };

  const unsigned short int
  Dhcp4Parser::yytable_[] =
  {
      79,   152,   231,   151,   175,   191,   214,   230,   244,   263,
     168,   176,   192,   171,   422,   196,   232,   153,   233,   154,
      68,   155,   423,   616,    25,   137,    26,    74,    27,    98,
      36,   547,   137,   290,   242,   243,    88,    89,   291,   173,
     174,   312,   317,    89,   181,   182,   313,   318,   208,   228,
     209,   210,   229,   242,   243,   333,   337,    92,    93,    94,
     334,   338,   138,   139,   140,    24,    98,   551,   552,   553,
     554,   366,    98,   208,   684,   141,   367,   685,   142,   143,
     144,   145,   146,   147,   382,   636,   637,   148,   149,   383,
      78,    86,   417,    38,   148,   150,   555,    87,    88,    89,
     565,   686,    90,    91,   687,   566,   567,   568,   569,   570,
     571,   572,   573,   574,   575,   782,    40,    78,   783,    92,
      93,    94,    95,    96,   548,   208,   208,    97,    98,   506,
     507,    75,    89,   181,   182,    78,    42,    44,    46,   812,
      76,    77,   813,   814,   815,   312,    99,   100,   129,   130,
     656,   207,   131,    78,    78,    28,    29,    30,    31,   101,
      78,    98,   102,   604,   605,   606,   607,   658,   608,   103,
     104,   810,   659,   105,   811,   280,   208,    48,   209,   210,
     183,   211,   212,   213,   184,   185,   186,   187,   188,   189,
      50,   190,    52,   784,    54,   785,   786,   622,   623,   624,
     625,   626,   627,   317,   672,    71,   422,   281,   660,   673,
     737,   282,    78,    78,   423,   284,    78,   249,   250,   251,
     252,   253,   254,   255,   256,   257,   258,   259,   260,   261,
     262,   283,    79,     1,     2,     3,     4,     5,     6,     7,
       8,     9,    10,    11,   289,   384,   385,   672,   697,    78,
     701,   349,   674,   698,   293,   702,   419,   382,   350,    78,
     333,   418,   703,    78,   366,   768,   294,   337,   420,   771,
     298,   421,   775,   152,   299,   151,   798,   359,   827,   175,
     300,   799,   168,   828,   301,   171,   176,   309,   316,   153,
     327,   154,   191,   155,   758,   759,   760,   761,   328,   192,
     231,   214,   196,   353,   357,   230,   358,   361,   363,   362,
     368,   371,   373,   374,   232,   377,   233,   378,   379,   387,
     386,   388,   389,   390,   263,   392,   395,   393,   394,   396,
     397,   398,   399,   400,   401,   402,   403,   404,   405,   406,
     407,   408,   409,   410,   411,   413,   414,   415,   429,   430,
     431,   432,   433,   489,   490,   434,   435,   436,   437,   438,
     439,   440,   441,   443,   444,   446,   447,   448,   449,   450,
     451,   452,   453,   454,   455,   457,   458,   460,   459,   461,
     462,   463,   465,   468,   469,   466,   472,   471,   473,   474,
     475,   478,   479,   476,   483,   477,   484,   486,   480,   481,
     495,   487,   482,   488,   491,   493,   494,   492,   496,   497,
     498,   499,   500,   512,   513,   501,   502,   503,   504,   510,
     511,   514,   522,   515,   516,   517,   518,   519,   520,   521,
     584,   584,   523,   543,    26,   576,   576,   592,   526,   560,
     527,   596,   600,   618,   644,   263,   529,   665,   419,   646,
     558,   650,   530,   418,   666,   667,   531,   668,   669,   532,
     420,   676,   677,   421,   533,   534,   535,   679,   680,   654,
     682,   683,   689,   690,   536,   691,   692,   693,   694,   537,
     695,   696,   710,   713,   709,   538,   539,   712,   716,   540,
     541,   715,   718,   719,   550,   720,   721,   727,   728,   747,
     748,   751,   524,   750,   756,   528,   757,   769,   391,   778,
     542,   770,   776,   544,   796,   800,   802,   545,   804,   546,
     824,   806,   825,   826,   829,   557,   412,   559,   564,   591,
     416,   729,   736,   739,   738,   746,   704,   707,   470,   722,
     731,   730,   442,   732,   733,   464,   753,   752,   734,   456,
     763,   723,   735,   724,   467,   755,   754,   726,   725,   740,
     741,   445,   742,   743,   642,   744,   745,   764,   765,   766,
     645,   749,   485,   767,   772,   773,   717,   774,   794,   803,
     822,   777,   833,   801,   805,   834,   830,     0,     0,   831,
       0,     0,     0,   832,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   584,
       0,     0,     0,     0,   576,   152,     0,   151,   231,     0,
     214,     0,     0,   230,   168,     0,     0,   171,     0,     0,
     244,   153,   232,   154,   233,   155,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     175,     0,     0,   191,     0,     0,     0,   176,     0,     0,
     192,     0,     0,   196,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   788,     0,
       0,     0,     0,   787,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   788,     0,     0,     0,     0,
     787
  };

  const short int
  Dhcp4Parser::yycheck_[] =
  {
      58,    61,    65,    61,    62,    63,    64,    65,    66,    67,
      61,    62,    63,    61,   319,    63,    65,    61,    65,    61,
      56,    61,   319,   499,     5,     7,     7,    10,     9,    48,
       7,    15,     7,     3,    80,    81,    18,    19,     8,    58,
      59,     3,     3,    19,    20,    21,     8,     8,    49,    50,
      51,    52,    53,    80,    81,     3,     3,    39,    40,    41,
       8,     8,    44,    45,    46,     0,    48,   110,   111,   112,
     113,     3,    48,    49,     3,    57,     8,     6,    60,    61,
      62,    63,    64,    65,     3,    91,    92,    69,    70,     8,
     136,    11,    68,     7,    69,    77,   139,    17,    18,    19,
      24,     3,    22,    23,     6,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,     3,     7,   136,     6,    39,
      40,    41,    42,    43,   108,    49,    49,    47,    48,    14,
      15,   114,    19,    20,    21,   136,     7,     7,     7,   117,
     123,   124,   120,   121,   122,     3,    66,    67,    12,    13,
       8,    24,    16,   136,   136,   136,   137,   138,   139,    79,
     136,    48,    82,    71,    72,    73,    74,     3,    76,    89,
      90,     3,     8,    93,     6,     6,    49,     7,    51,    52,
      67,    54,    55,    56,    71,    72,    73,    74,    75,    76,
       7,    78,     7,   116,     7,   118,   119,    83,    84,    85,
      86,    87,    88,     3,     3,   136,   511,     3,     8,     8,
     686,     4,   136,   136,   511,     3,   136,    94,    95,    96,
      97,    98,    99,   100,   101,   102,   103,   104,   105,   106,
     107,     8,   290,   125,   126,   127,   128,   129,   130,   131,
     132,   133,   134,   135,     4,   281,   282,     3,     3,   136,
       3,     8,     8,     8,     4,     8,   319,     3,     3,   136,
       3,   319,     8,   136,     3,     8,     4,     3,   319,     8,
       4,   319,     8,   333,     4,   333,     3,     3,     3,   337,
       4,     8,   333,     8,     4,   333,   337,     4,     4,   333,
       4,   333,   350,   333,    25,    26,    27,    28,     4,   350,
     363,   359,   350,     4,     4,   363,     8,     4,     3,     8,
       4,     4,     4,     4,   363,     4,   363,     4,     4,     4,
     136,     4,     4,     4,   382,     4,     4,   139,   139,     4,
       4,   137,   137,   137,   137,     4,     4,     4,     4,     4,
       4,     4,   137,     4,     4,     4,     4,   139,     4,     4,
       4,     4,     4,   389,   390,     4,     4,   137,   139,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,   137,     4,
       4,   139,     4,     4,     4,   139,     4,   139,     4,   137,
       4,     4,     4,   137,     4,   137,     4,     4,   139,   139,
       5,     7,   139,     7,     7,     7,     7,   136,     5,     5,
       5,     5,     5,   136,   136,     7,     7,     7,     5,     8,
       3,   136,     7,     5,   136,   136,   136,   136,   136,     5,
     493,   494,   136,   469,     7,   493,   494,     7,   136,   115,
     136,     7,     7,     7,     4,   503,   136,     4,   511,     7,
     486,     7,   136,   511,     4,     4,   136,     4,     4,   136,
     511,     6,     3,   511,   136,   136,   136,     6,     3,    78,
       6,     3,     6,     3,   136,     4,     4,     4,     4,   136,
       4,     4,     3,     3,     6,   136,   136,     6,     4,   136,
     136,     8,     4,     4,   109,     4,     4,     4,     4,     4,
       4,     3,   444,     6,     4,   448,     5,     8,   290,     7,
     136,     8,     8,   136,     4,     4,     4,   136,     5,   136,
       4,     7,     4,     4,     4,   136,   312,   487,   491,   494,
     317,   672,   684,   690,   688,   697,   136,   136,   366,   137,
     677,   675,   333,   678,   680,   359,   710,   708,   681,   350,
     136,   139,   683,   137,   363,   713,   711,   137,   139,   137,
     137,   337,   137,   137,   503,   137,   137,   136,   136,   136,
     511,   701,   382,   136,   136,   136,   658,   136,   782,   798,
     810,   136,   827,   137,   136,   136,   139,    -1,    -1,   137,
      -1,    -1,    -1,   137,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   672,
      -1,    -1,    -1,    -1,   672,   675,    -1,   675,   681,    -1,
     678,    -1,    -1,   681,   675,    -1,    -1,   675,    -1,    -1,
     688,   675,   681,   675,   681,   675,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     708,    -1,    -1,   711,    -1,    -1,    -1,   708,    -1,    -1,
     711,    -1,    -1,   711,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   781,    -1,
      -1,    -1,    -1,   781,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   798,    -1,    -1,    -1,    -1,
     798
  };

  const unsigned short int
  Dhcp4Parser::yystos_[] =
  {
       0,   125,   126,   127,   128,   129,   130,   131,   132,   133,
     134,   135,   141,   142,   143,   144,   145,   146,   147,   148,
     149,   150,   151,   152,     0,     5,     7,     9,   136,   137,
     138,   139,   153,   154,   155,   160,     7,   169,     7,   175,
       7,   189,     7,   262,     7,   331,     7,   345,     7,   290,
       7,   314,     7,   238,     7,   397,   161,   156,   170,   176,
     190,   263,   332,   346,   291,   315,   239,   398,   153,   162,
     163,   136,   158,   159,    10,   114,   123,   124,   136,   168,
     171,   172,   173,   424,   426,   428,    11,    17,    18,    19,
      22,    23,    39,    40,    41,    42,    43,    47,    48,    66,
      67,    79,    82,    89,    90,    93,   168,   177,   178,   179,
     180,   181,   182,   183,   184,   185,   197,   199,   223,   232,
     246,   256,   284,   308,   350,   376,   386,   387,   395,    12,
      13,    16,   187,   188,   191,   193,   196,     7,    44,    45,
      46,    57,    60,    61,    62,    63,    64,    65,    69,    70,
      77,   168,   179,   180,   181,   184,   264,   265,   266,   268,
     270,   272,   274,   276,   278,   280,   282,   283,   308,   325,
     339,   350,   372,    58,    59,   168,   308,   333,   334,   335,
     337,    20,    21,    67,    71,    72,    73,    74,    75,    76,
      78,   168,   308,   347,   348,   349,   350,   352,   354,   356,
     358,   360,   362,   364,   366,   368,   370,    24,    49,    51,
      52,    54,    55,    56,   168,   213,   292,   293,   294,   295,
     296,   297,   298,   300,   302,   304,   305,   307,    50,    53,
     168,   213,   296,   302,   316,   317,   318,   319,   320,   322,
     323,   324,    80,    81,   168,   240,   241,   242,   244,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   168,   399,   400,   401,   402,   404,   406,
     407,   409,   410,   411,   414,   416,   417,   418,   419,   422,
       6,     3,     4,     8,     3,   174,   429,   425,   427,     4,
       3,     8,   186,     4,     4,   351,   198,   200,     4,     4,
       4,     4,   257,   285,   309,   224,   377,   233,   247,     4,
     388,   396,     3,     8,   192,   194,     4,     3,     8,   379,
     269,   271,   273,   326,   267,   275,   277,     4,     4,   281,
     279,   340,   373,     3,     8,   336,   338,     3,     8,   353,
     355,   371,   359,   361,   365,   363,   369,   367,   357,     8,
       3,   299,   214,     4,   303,   301,   306,     4,     8,     3,
     321,     4,     8,     3,   243,   245,     3,     8,     4,   403,
     405,     4,   408,     4,     4,   412,   415,     4,     4,     4,
     420,   423,     3,     8,   153,   153,   136,     4,     4,     4,
       4,   172,     4,   139,   139,     4,     4,     4,   137,   137,
     137,   137,     4,     4,     4,     4,     4,     4,     4,   137,
       4,     4,   178,     4,     4,   139,   188,    68,   168,   213,
     308,   350,   352,   354,   380,   381,   382,   383,   384,     4,
       4,     4,     4,     4,     4,     4,   137,   139,     4,     4,
       4,     4,   265,     4,     4,   334,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,   349,     4,     4,   137,
       4,     4,     4,   139,   294,     4,   139,   318,     4,     4,
     241,   139,     4,     4,   137,     4,   137,   137,     4,     4,
     139,   139,   139,     4,     4,   400,     4,     7,     7,   153,
     153,     7,   136,     7,     7,     5,     5,     5,     5,     5,
       5,     7,     7,     7,     5,   164,    14,    15,   195,   385,
       8,     3,   136,   136,   136,     5,   136,   136,   136,   136,
     136,     5,     7,   136,   155,   157,   136,   136,   164,   136,
     136,   136,   136,   136,   136,   136,   136,   136,   136,   136,
     136,   136,   136,   153,   136,   136,   136,    15,   108,   413,
     109,   110,   111,   112,   113,   139,   421,   136,   153,   177,
     115,   430,   431,   432,   187,    24,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,   168,   201,   202,   203,
     206,   208,   210,   212,   213,   215,   216,   217,   218,   219,
     221,   201,     7,   258,   259,   260,     7,   286,   287,   288,
       7,   310,   311,   312,    71,    72,    73,    74,    76,   225,
     226,   227,   228,   229,   230,   231,   278,   378,     7,   234,
     235,   236,    83,    84,    85,    86,    87,    88,   248,   249,
     250,   251,   252,   253,   254,   255,    91,    92,   389,   390,
     391,   393,   399,   165,     4,   382,     7,   327,   328,   329,
       7,   341,   342,   343,    78,   374,     8,   433,     3,     8,
       8,   204,   207,   209,   211,     4,     4,     4,     4,     4,
     220,   222,     3,     8,     8,   261,     6,     3,   289,     6,
       3,   313,     6,     3,     3,     6,     3,     6,   237,     6,
       3,     4,     4,     4,     4,     4,     4,     3,     8,   392,
     394,     3,     8,     8,   136,   166,   167,   136,   330,     6,
       3,   344,     6,     3,   375,     8,     4,   431,     4,     4,
       4,     4,   137,   139,   137,   139,   137,     4,     4,   202,
     264,   260,   292,   288,   316,   312,   226,   278,   240,   236,
     137,   137,   137,   137,   137,   137,   249,     4,     4,   390,
       6,     3,   333,   329,   347,   343,     4,     5,    25,    26,
      27,    28,   205,   136,   136,   136,   136,   136,     8,     8,
       8,     8,   136,   136,   136,     8,     8,   136,     7,   434,
     435,   436,     3,     6,   116,   118,   119,   168,   213,   437,
     438,   439,   440,   442,   435,   443,     4,   441,     3,     8,
       4,   137,     4,   438,     5,   136,     7,   444,   445,   446,
       3,     6,   117,   120,   121,   122,   447,   448,   449,   451,
     452,   453,   445,   450,     4,     4,     4,     3,     8,     4,
     139,   137,   137,   448,   136
  };

  const unsigned short int
  Dhcp4Parser::yyr1_[] =
  {
       0,   140,   142,   141,   143,   141,   144,   141,   145,   141,
     146,   141,   147,   141,   148,   141,   149,   141,   150,   141,
     151,   141,   152,   141,   153,   153,   153,   153,   153,   153,
     153,   154,   156,   155,   157,   158,   158,   159,   159,   161,
     160,   162,   162,   163,   163,   165,   164,   166,   166,   167,
     167,   168,   170,   169,   171,   171,   172,   172,   172,   172,
     172,   174,   173,   176,   175,   177,   177,   178,   178,   178,
     178,   178,   178,   178,   178,   178,   178,   178,   178,   178,
     178,   178,   178,   178,   178,   178,   178,   178,   179,   180,
     181,   182,   183,   184,   186,   185,   187,   187,   188,   188,
     188,   190,   189,   192,   191,   194,   193,   195,   195,   196,
     198,   197,   200,   199,   201,   201,   202,   202,   202,   202,
     202,   202,   202,   202,   202,   202,   202,   202,   202,   204,
     203,   205,   205,   205,   205,   207,   206,   209,   208,   211,
     210,   212,   214,   213,   215,   216,   217,   218,   220,   219,
     222,   221,   224,   223,   225,   225,   226,   226,   226,   226,
     226,   227,   228,   229,   230,   231,   233,   232,   234,   234,
     235,   235,   237,   236,   239,   238,   240,   240,   240,   241,
     241,   243,   242,   245,   244,   247,   246,   248,   248,   249,
     249,   249,   249,   249,   249,   250,   251,   252,   253,   254,
     255,   257,   256,   258,   258,   259,   259,   261,   260,   263,
     262,   264,   264,   265,   265,   265,   265,   265,   265,   265,
     265,   265,   265,   265,   265,   265,   265,   265,   265,   265,
     265,   265,   265,   267,   266,   269,   268,   271,   270,   273,
     272,   275,   274,   277,   276,   279,   278,   281,   280,   282,
     283,   285,   284,   286,   286,   287,   287,   289,   288,   291,
     290,   292,   292,   293,   293,   294,   294,   294,   294,   294,
     294,   294,   294,   295,   296,   297,   299,   298,   301,   300,
     303,   302,   304,   306,   305,   307,   309,   308,   310,   310,
     311,   311,   313,   312,   315,   314,   316,   316,   317,   317,
     318,   318,   318,   318,   318,   318,   319,   321,   320,   322,
     323,   324,   326,   325,   327,   327,   328,   328,   330,   329,
     332,   331,   333,   333,   334,   334,   334,   334,   336,   335,
     338,   337,   340,   339,   341,   341,   342,   342,   344,   343,
     346,   345,   347,   347,   348,   348,   349,   349,   349,   349,
     349,   349,   349,   349,   349,   349,   349,   349,   349,   351,
     350,   353,   352,   355,   354,   357,   356,   359,   358,   361,
     360,   363,   362,   365,   364,   367,   366,   369,   368,   371,
     370,   373,   372,   375,   374,   377,   376,   378,   378,   379,
     278,   380,   380,   381,   381,   382,   382,   382,   382,   382,
     382,   382,   383,   385,   384,   386,   388,   387,   389,   389,
     390,   390,   392,   391,   394,   393,   396,   395,   398,   397,
     399,   399,   400,   400,   400,   400,   400,   400,   400,   400,
     400,   400,   400,   400,   400,   400,   400,   401,   403,   402,
     405,   404,   406,   408,   407,   409,   410,   412,   411,   413,
     413,   415,   414,   416,   417,   418,   420,   419,   421,   421,
     421,   421,   421,   423,   422,   425,   424,   427,   426,   429,
     428,   430,   430,   431,   433,   432,   434,   434,   436,   435,
     437,   437,   438,   438,   438,   438,   438,   439,   441,   440,
     443,   442,   444,   444,   446,   445,   447,   447,   448,   448,
     448,   448,   450,   449,   451,   452,   453
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
       1,     1,     1,     1,     1,     1,     1,     1,     1,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       4,     0,     6,     0,     4,     0,     6,     1,     3,     0,
       4,     0,     1,     1,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     0,     4,     3,     0,     6,     1,     3,
       1,     1,     0,     4,     0,     4,     0,     6,     0,     4,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     3,     0,     4,
       0,     4,     3,     0,     4,     3,     3,     0,     4,     1,
       1,     0,     4,     3,     3,     3,     0,     4,     1,     1,
       1,     1,     1,     0,     4,     0,     4,     0,     4,     0,
       6,     1,     3,     1,     0,     6,     1,     3,     0,     4,
       1,     3,     1,     1,     1,     1,     1,     3,     0,     4,
       0,     6,     1,     3,     0,     4,     1,     3,     1,     1,
       1,     1,     0,     4,     3,     3,     3
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
  "\"circuit-id\"", "\"client-id\"", "\"hostname\"", "\"flex-id\"",
  "\"relay\"", "\"ip-address\"", "\"hooks-libraries\"", "\"library\"",
  "\"parameters\"", "\"expired-leases-processing\"",
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
  "\"debuglevel\"", "\"severity\"", "\"flush\"", "\"maxsize\"",
  "\"maxver\"", "\"Dhcp6\"", "\"DhcpDdns\"", "TOPLEVEL_JSON",
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
       0,   220,   220,   220,   221,   221,   222,   222,   223,   223,
     224,   224,   225,   225,   226,   226,   227,   227,   228,   228,
     229,   229,   230,   230,   238,   239,   240,   241,   242,   243,
     244,   247,   252,   252,   263,   266,   267,   270,   274,   281,
     281,   288,   289,   292,   296,   303,   303,   310,   311,   314,
     318,   329,   339,   339,   351,   352,   356,   357,   358,   359,
     360,   363,   363,   380,   380,   388,   389,   394,   395,   396,
     397,   398,   399,   400,   401,   402,   403,   404,   405,   406,
     407,   408,   409,   410,   411,   412,   413,   414,   417,   422,
     427,   432,   437,   442,   448,   448,   458,   459,   462,   463,
     464,   467,   467,   475,   475,   485,   485,   492,   493,   496,
     502,   502,   512,   512,   522,   523,   526,   527,   528,   529,
     530,   531,   532,   533,   534,   535,   536,   537,   538,   541,
     541,   548,   549,   550,   551,   554,   554,   562,   562,   570,
     570,   578,   583,   583,   591,   596,   601,   606,   611,   611,
     619,   619,   628,   628,   638,   639,   642,   643,   644,   645,
     646,   649,   654,   659,   664,   669,   674,   674,   684,   685,
     688,   689,   692,   692,   700,   700,   708,   709,   710,   713,
     714,   717,   717,   725,   725,   733,   733,   743,   744,   747,
     748,   749,   750,   751,   752,   755,   760,   765,   770,   775,
     780,   788,   788,   801,   802,   805,   806,   813,   813,   836,
     836,   845,   846,   850,   851,   852,   853,   854,   855,   856,
     857,   858,   859,   860,   861,   862,   863,   864,   865,   866,
     867,   868,   869,   872,   872,   880,   880,   888,   888,   896,
     896,   904,   904,   912,   912,   920,   920,   928,   928,   936,
     941,   950,   950,   962,   963,   966,   967,   972,   972,   983,
     983,   993,   994,   997,   998,  1001,  1002,  1003,  1004,  1005,
    1006,  1007,  1008,  1011,  1013,  1018,  1020,  1020,  1028,  1028,
    1036,  1036,  1044,  1046,  1046,  1054,  1063,  1063,  1075,  1076,
    1081,  1082,  1087,  1087,  1098,  1098,  1109,  1110,  1115,  1116,
    1121,  1122,  1123,  1124,  1125,  1126,  1129,  1131,  1131,  1139,
    1141,  1143,  1151,  1151,  1163,  1164,  1167,  1168,  1171,  1171,
    1179,  1179,  1187,  1188,  1191,  1192,  1193,  1194,  1197,  1197,
    1205,  1205,  1215,  1215,  1225,  1226,  1229,  1230,  1233,  1233,
    1241,  1241,  1249,  1250,  1253,  1254,  1258,  1259,  1260,  1261,
    1262,  1263,  1264,  1265,  1266,  1267,  1268,  1269,  1270,  1273,
    1273,  1281,  1281,  1289,  1289,  1297,  1297,  1305,  1305,  1313,
    1313,  1321,  1321,  1329,  1329,  1337,  1337,  1345,  1345,  1353,
    1353,  1366,  1366,  1376,  1376,  1387,  1387,  1397,  1398,  1401,
    1401,  1409,  1410,  1413,  1414,  1417,  1418,  1419,  1420,  1421,
    1422,  1423,  1426,  1428,  1428,  1440,  1447,  1447,  1457,  1458,
    1461,  1462,  1465,  1465,  1473,  1473,  1483,  1483,  1493,  1493,
    1501,  1502,  1505,  1506,  1507,  1508,  1509,  1510,  1511,  1512,
    1513,  1514,  1515,  1516,  1517,  1518,  1519,  1522,  1527,  1527,
    1535,  1535,  1543,  1548,  1548,  1556,  1561,  1566,  1566,  1574,
    1575,  1578,  1578,  1586,  1591,  1596,  1601,  1601,  1609,  1612,
    1615,  1618,  1621,  1627,  1627,  1637,  1637,  1644,  1644,  1656,
    1656,  1669,  1670,  1674,  1678,  1678,  1690,  1691,  1695,  1695,
    1703,  1704,  1707,  1708,  1709,  1710,  1711,  1714,  1719,  1719,
    1727,  1727,  1737,  1738,  1741,  1741,  1749,  1750,  1753,  1754,
    1755,  1756,  1759,  1759,  1767,  1772,  1777
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
#line 4123 "dhcp4_parser.cc" // lalr1.cc:1167
#line 1782 "dhcp4_parser.yy" // lalr1.cc:1168


void
isc::dhcp::Dhcp4Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
