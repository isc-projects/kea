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
      case 157: // value
      case 161: // map_value
      case 199: // socket_type
      case 209: // db_type
      case 286: // hr_mode
      case 419: // ncr_protocol_value
      case 427: // replace_client_name_value
        value.move< ElementPtr > (that.value);
        break;

      case 143: // "boolean"
        value.move< bool > (that.value);
        break;

      case 142: // "floating point"
        value.move< double > (that.value);
        break;

      case 141: // "integer"
        value.move< int64_t > (that.value);
        break;

      case 140: // "constant string"
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
      case 157: // value
      case 161: // map_value
      case 199: // socket_type
      case 209: // db_type
      case 286: // hr_mode
      case 419: // ncr_protocol_value
      case 427: // replace_client_name_value
        value.copy< ElementPtr > (that.value);
        break;

      case 143: // "boolean"
        value.copy< bool > (that.value);
        break;

      case 142: // "floating point"
        value.copy< double > (that.value);
        break;

      case 141: // "integer"
        value.copy< int64_t > (that.value);
        break;

      case 140: // "constant string"
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
            case 140: // "constant string"

#line 216 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< std::string > (); }
#line 364 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 141: // "integer"

#line 216 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< int64_t > (); }
#line 371 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 142: // "floating point"

#line 216 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< double > (); }
#line 378 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 143: // "boolean"

#line 216 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< bool > (); }
#line 385 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 157: // value

#line 216 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 392 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 161: // map_value

#line 216 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 399 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 199: // socket_type

#line 216 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 406 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 209: // db_type

#line 216 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 413 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 286: // hr_mode

#line 216 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 420 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 419: // ncr_protocol_value

#line 216 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 427 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 427: // replace_client_name_value

#line 216 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 434 "dhcp4_parser.cc" // lalr1.cc:636
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
      case 157: // value
      case 161: // map_value
      case 199: // socket_type
      case 209: // db_type
      case 286: // hr_mode
      case 419: // ncr_protocol_value
      case 427: // replace_client_name_value
        yylhs.value.build< ElementPtr > ();
        break;

      case 143: // "boolean"
        yylhs.value.build< bool > ();
        break;

      case 142: // "floating point"
        yylhs.value.build< double > ();
        break;

      case 141: // "integer"
        yylhs.value.build< int64_t > ();
        break;

      case 140: // "constant string"
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
#line 225 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.NO_KEYWORD; }
#line 680 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 4:
#line 226 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.CONFIG; }
#line 686 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 6:
#line 227 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.DHCP4; }
#line 692 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 8:
#line 228 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.INTERFACES_CONFIG; }
#line 698 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 10:
#line 229 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.SUBNET4; }
#line 704 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 12:
#line 230 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.POOLS; }
#line 710 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 14:
#line 231 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.RESERVATIONS; }
#line 716 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 16:
#line 232 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.OPTION_DEF; }
#line 722 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 18:
#line 233 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.OPTION_DATA; }
#line 728 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 20:
#line 234 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.HOOKS_LIBRARIES; }
#line 734 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 22:
#line 235 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.DHCP_DDNS; }
#line 740 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 24:
#line 243 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 746 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 25:
#line 244 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as< double > (), ctx.loc2pos(yystack_[0].location))); }
#line 752 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 26:
#line 245 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 758 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 27:
#line 246 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 764 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 28:
#line 247 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 770 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 29:
#line 248 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 776 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 30:
#line 249 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 782 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 31:
#line 252 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as< ElementPtr > ());
}
#line 791 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 32:
#line 257 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 802 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 33:
#line 262 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 812 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 34:
#line 268 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 818 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 37:
#line 275 "dhcp4_parser.yy" // lalr1.cc:859
    {
                  // map containing a single entry
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 827 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 38:
#line 279 "dhcp4_parser.yy" // lalr1.cc:859
    {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 837 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 39:
#line 286 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 846 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 40:
#line 289 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // list parsing complete. Put any sanity checking here
}
#line 854 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 43:
#line 297 "dhcp4_parser.yy" // lalr1.cc:859
    {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 863 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 44:
#line 301 "dhcp4_parser.yy" // lalr1.cc:859
    {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 872 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 45:
#line 308 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // List parsing about to start
}
#line 880 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 46:
#line 310 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // list parsing complete. Put any sanity checking here
    //ctx.stack_.pop_back();
}
#line 889 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 49:
#line 319 "dhcp4_parser.yy" // lalr1.cc:859
    {
                          ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 898 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 50:
#line 323 "dhcp4_parser.yy" // lalr1.cc:859
    {
                          ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 907 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 51:
#line 334 "dhcp4_parser.yy" // lalr1.cc:859
    {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as< std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 918 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 52:
#line 344 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 929 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 53:
#line 349 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 939 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 61:
#line 368 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Dhcp4", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP4);
}
#line 952 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 62:
#line 375 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 964 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 63:
#line 385 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the Dhcp4 map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 974 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 64:
#line 389 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 982 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 88:
#line 422 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 991 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 89:
#line 427 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 1000 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 90:
#line 432 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 1009 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 91:
#line 437 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr dpp(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 1018 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 92:
#line 442 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr echo(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("echo-client-id", echo);
}
#line 1027 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 93:
#line 447 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr match(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("match-client-id", match);
}
#line 1036 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 94:
#line 453 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces-config", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.INTERFACES_CONFIG);
}
#line 1047 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 95:
#line 458 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1056 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 101:
#line 472 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1066 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 102:
#line 476 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1074 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 103:
#line 480 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1085 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 104:
#line 485 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1094 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 105:
#line 490 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.DHCP_SOCKET_TYPE);
}
#line 1102 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 106:
#line 492 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("dhcp-socket-type", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1111 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 107:
#line 497 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("raw", ctx.loc2pos(yystack_[0].location))); }
#line 1117 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 108:
#line 498 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("udp", ctx.loc2pos(yystack_[0].location))); }
#line 1123 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 109:
#line 501 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("re-detect", b);
}
#line 1132 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 110:
#line 507 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lease-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.LEASE_DATABASE);
}
#line 1143 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 111:
#line 512 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1152 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 112:
#line 517 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1163 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 113:
#line 522 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1172 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 129:
#line 546 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.DATABASE_TYPE);
}
#line 1180 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 130:
#line 548 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("type", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1189 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 131:
#line 553 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("memfile", ctx.loc2pos(yystack_[0].location))); }
#line 1195 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 132:
#line 554 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("mysql", ctx.loc2pos(yystack_[0].location))); }
#line 1201 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 133:
#line 555 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("postgresql", ctx.loc2pos(yystack_[0].location))); }
#line 1207 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 134:
#line 556 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("cql", ctx.loc2pos(yystack_[0].location))); }
#line 1213 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 135:
#line 559 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1221 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 136:
#line 561 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr user(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1231 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 137:
#line 567 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1239 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 138:
#line 569 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr pwd(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 1249 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 139:
#line 575 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1257 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 140:
#line 577 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr h(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 1267 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 141:
#line 583 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr p(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", p);
}
#line 1276 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 142:
#line 588 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1284 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 143:
#line 590 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1294 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 144:
#line 596 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 1303 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 145:
#line 601 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 1312 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 146:
#line 606 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 1321 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 147:
#line 611 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("connect-timeout", n);
}
#line 1330 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 148:
#line 616 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1338 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 149:
#line 618 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr cp(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("contact-points", cp);
    ctx.leave();
}
#line 1348 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 150:
#line 624 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1356 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 151:
#line 626 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr ks(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("keyspace", ks);
    ctx.leave();
}
#line 1366 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 152:
#line 633 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 1377 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 153:
#line 638 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1386 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 161:
#line 654 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1395 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 162:
#line 659 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 1404 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 163:
#line 664 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr circuit(new StringElement("circuit-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(circuit);
}
#line 1413 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 164:
#line 669 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr client(new StringElement("client-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(client);
}
#line 1422 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 165:
#line 674 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr flex_id(new StringElement("flex-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(flex_id);
}
#line 1431 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 166:
#line 679 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 1442 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 167:
#line 684 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1451 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 172:
#line 697 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1461 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 173:
#line 701 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1469 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 174:
#line 705 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1479 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 175:
#line 709 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1487 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 181:
#line 722 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1495 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 182:
#line 724 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr lib(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 1505 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 183:
#line 730 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1513 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 184:
#line 732 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1522 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 185:
#line 738 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.EXPIRED_LEASES_PROCESSING);
}
#line 1533 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 186:
#line 743 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1542 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 195:
#line 760 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 1551 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 196:
#line 765 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 1560 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 197:
#line 770 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 1569 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 198:
#line 775 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 1578 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 199:
#line 780 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 1587 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 200:
#line 785 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 1596 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 201:
#line 793 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet4", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET4);
}
#line 1607 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 202:
#line 798 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1616 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 207:
#line 818 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1626 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 208:
#line 822 "dhcp4_parser.yy" // lalr1.cc:859
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
#line 1649 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 209:
#line 841 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the subnet4 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1659 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 210:
#line 845 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1667 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 233:
#line 877 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1675 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 234:
#line 879 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr subnet(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 1685 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 235:
#line 885 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1693 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 236:
#line 887 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface", iface);
    ctx.leave();
}
#line 1703 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 237:
#line 893 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1711 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 238:
#line 895 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface-id", iface);
    ctx.leave();
}
#line 1721 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 239:
#line 901 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1729 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 240:
#line 903 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-subnet", iface);
    ctx.leave();
}
#line 1739 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 241:
#line 909 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1747 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 242:
#line 911 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 1757 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 243:
#line 917 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1765 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 244:
#line 919 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface-id", iface);
    ctx.leave();
}
#line 1775 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 245:
#line 925 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.CLIENT_CLASS);
}
#line 1783 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 246:
#line 927 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr cls(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 1793 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 247:
#line 933 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.RESERVATION_MODE);
}
#line 1801 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 248:
#line 935 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("reservation-mode", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1810 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 249:
#line 940 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("disabled", ctx.loc2pos(yystack_[0].location))); }
#line 1816 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 250:
#line 941 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("out-of-pool", ctx.loc2pos(yystack_[0].location))); }
#line 1822 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 251:
#line 942 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("all", ctx.loc2pos(yystack_[0].location))); }
#line 1828 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 252:
#line 945 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr id(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 1837 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 253:
#line 950 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr rc(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rapid-commit", rc);
}
#line 1846 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 254:
#line 959 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 1857 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 255:
#line 964 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1866 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 260:
#line 981 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1876 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 261:
#line 985 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1884 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 262:
#line 992 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1894 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 263:
#line 996 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1902 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 277:
#line 1022 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr code(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 1911 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 279:
#line 1029 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1919 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 280:
#line 1031 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 1929 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 281:
#line 1037 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1937 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 282:
#line 1039 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 1947 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 283:
#line 1045 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1955 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 284:
#line 1047 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr space(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 1965 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 286:
#line 1055 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1973 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 287:
#line 1057 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr encap(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 1983 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 288:
#line 1063 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr array(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 1992 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 289:
#line 1072 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 2003 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 290:
#line 1077 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2012 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 295:
#line 1096 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2022 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 296:
#line 1100 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2030 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 297:
#line 1107 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2040 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 298:
#line 1111 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 2048 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 311:
#line 1141 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2056 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 312:
#line 1143 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr data(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 2066 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 315:
#line 1153 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr space(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", space);
}
#line 2075 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 316:
#line 1158 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr persist(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-send", persist);
}
#line 2084 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 317:
#line 1166 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 2095 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 318:
#line 1171 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2104 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 323:
#line 1186 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2114 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 324:
#line 1190 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2122 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 325:
#line 1194 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2132 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 326:
#line 1198 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 2140 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 333:
#line 1212 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2148 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 334:
#line 1214 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr pool(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 2158 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 335:
#line 1220 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2166 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 336:
#line 1222 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("user-context", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2175 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 337:
#line 1230 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 2186 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 338:
#line 1235 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2195 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 343:
#line 1248 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2205 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 344:
#line 1252 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2213 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 345:
#line 1256 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2223 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 346:
#line 1260 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 2231 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 364:
#line 1288 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2239 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 365:
#line 1290 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr next_server(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("next-server", next_server);
    ctx.leave();
}
#line 2249 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 366:
#line 1296 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2257 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 367:
#line 1298 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr srv(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-hostname", srv);
    ctx.leave();
}
#line 2267 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 368:
#line 1304 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2275 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 369:
#line 1306 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr bootfile(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("boot-file-name", bootfile);
    ctx.leave();
}
#line 2285 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 370:
#line 1312 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2293 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 371:
#line 1314 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr addr(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", addr);
    ctx.leave();
}
#line 2303 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 372:
#line 1320 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2311 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 373:
#line 1322 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr d(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 2321 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 374:
#line 1328 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2329 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 375:
#line 1330 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 2339 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 376:
#line 1336 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2347 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 377:
#line 1338 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-id", hw);
    ctx.leave();
}
#line 2357 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 378:
#line 1344 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2365 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 379:
#line 1346 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("circuit-id", hw);
    ctx.leave();
}
#line 2375 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 380:
#line 1352 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2383 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 381:
#line 1354 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flex-id", hw);
    ctx.leave();
}
#line 2393 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 382:
#line 1360 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2401 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 383:
#line 1362 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr host(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 2411 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 384:
#line 1368 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2422 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 385:
#line 1373 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2431 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 386:
#line 1381 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 2442 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 387:
#line 1386 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2451 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 388:
#line 1391 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2459 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 389:
#line 1393 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr ip(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", ip);
    ctx.leave();
}
#line 2469 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 390:
#line 1402 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 2480 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 391:
#line 1407 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2489 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 394:
#line 1416 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2499 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 395:
#line 1420 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2507 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 408:
#line 1443 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2515 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 409:
#line 1445 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr test(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 2525 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 410:
#line 1455 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 2534 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 411:
#line 1462 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 2545 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 412:
#line 1467 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2554 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 417:
#line 1480 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2562 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 418:
#line 1482 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr stype(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 2572 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 419:
#line 1488 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2580 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 420:
#line 1490 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 2590 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 421:
#line 1498 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 2601 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 422:
#line 1503 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2610 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 423:
#line 1508 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2620 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 424:
#line 1512 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 2628 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 442:
#line 1537 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 2637 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 443:
#line 1542 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2645 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 444:
#line 1544 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("qualifying-suffix", s);
    ctx.leave();
}
#line 2655 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 445:
#line 1550 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2663 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 446:
#line 1552 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 2673 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 447:
#line 1558 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 2682 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 448:
#line 1563 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2690 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 449:
#line 1565 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 2700 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 450:
#line 1571 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 2709 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 451:
#line 1576 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 2718 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 452:
#line 1581 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 2726 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 453:
#line 1583 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2735 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 454:
#line 1589 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 2741 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 455:
#line 1590 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 2747 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 456:
#line 1593 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NCR_FORMAT);
}
#line 2755 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 457:
#line 1595 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 2765 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 458:
#line 1601 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-include-fqdn", b);
}
#line 2774 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 459:
#line 1606 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-no-update", b);
}
#line 2783 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 460:
#line 1611 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-client-update", b);
}
#line 2792 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 461:
#line 1616 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 2800 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 462:
#line 1618 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("replace-client-name", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2809 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 463:
#line 1624 "dhcp4_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("when-present", ctx.loc2pos(yystack_[0].location))); 
      }
#line 2817 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 464:
#line 1627 "dhcp4_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location)));
      }
#line 2825 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 465:
#line 1630 "dhcp4_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("always", ctx.loc2pos(yystack_[0].location)));
      }
#line 2833 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 466:
#line 1633 "dhcp4_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("when-not-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 2841 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 467:
#line 1636 "dhcp4_parser.yy" // lalr1.cc:859
    {
      error(yystack_[0].location, "boolean values for the replace-client-name are "
                "no longer supported");
      }
#line 2850 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 468:
#line 1642 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2858 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 469:
#line 1644 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("generated-prefix", s);
    ctx.leave();
}
#line 2868 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 470:
#line 1652 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2876 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 471:
#line 1654 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("Dhcp6", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2885 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 472:
#line 1659 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2893 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 473:
#line 1661 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("DhcpDdns", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2902 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 474:
#line 1671 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Logging", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.LOGGING);
}
#line 2913 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 475:
#line 1676 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2922 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 479:
#line 1693 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 2933 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 480:
#line 1698 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2942 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 483:
#line 1710 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 2952 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 484:
#line 1714 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2960 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 492:
#line 1729 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr dl(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 2969 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 493:
#line 1734 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2977 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 494:
#line 1736 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 2987 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 495:
#line 1742 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 2998 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 496:
#line 1747 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3007 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 499:
#line 1756 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3017 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 500:
#line 1760 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 3025 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 507:
#line 1774 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3033 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 508:
#line 1776 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 3043 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 509:
#line 1782 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr flush(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 3052 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 510:
#line 1787 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr maxsize(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 3061 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 511:
#line 1792 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr maxver(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 3070 "dhcp4_parser.cc" // lalr1.cc:859
    break;


#line 3074 "dhcp4_parser.cc" // lalr1.cc:859
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


  const short int Dhcp4Parser::yypact_ninf_ = -479;

  const signed char Dhcp4Parser::yytable_ninf_ = -1;

  const short int
  Dhcp4Parser::yypact_[] =
  {
     118,  -479,  -479,  -479,  -479,  -479,  -479,  -479,  -479,  -479,
    -479,  -479,    32,    19,    81,    87,    93,   102,   123,   124,
     135,   148,   156,   158,  -479,  -479,  -479,  -479,  -479,  -479,
    -479,  -479,  -479,  -479,  -479,  -479,  -479,  -479,  -479,  -479,
    -479,  -479,  -479,  -479,  -479,  -479,  -479,  -479,  -479,  -479,
    -479,  -479,  -479,  -479,  -479,  -479,    19,    27,    17,    28,
     266,    16,   -17,    72,    77,    53,   -44,   120,  -479,    46,
     177,   190,   208,   195,  -479,  -479,  -479,  -479,   238,  -479,
      41,  -479,  -479,  -479,  -479,  -479,  -479,   239,   254,  -479,
    -479,  -479,   267,   268,   281,   285,  -479,  -479,  -479,  -479,
    -479,  -479,  -479,   287,  -479,  -479,  -479,    45,  -479,  -479,
    -479,  -479,  -479,  -479,  -479,  -479,  -479,  -479,  -479,  -479,
    -479,  -479,  -479,  -479,  -479,  -479,  -479,  -479,  -479,  -479,
    -479,   289,    51,  -479,  -479,  -479,  -479,  -479,  -479,  -479,
    -479,  -479,  -479,  -479,  -479,   295,   298,  -479,  -479,  -479,
    -479,  -479,  -479,  -479,  -479,  -479,    55,  -479,  -479,  -479,
    -479,  -479,  -479,  -479,  -479,  -479,  -479,  -479,  -479,  -479,
    -479,  -479,  -479,  -479,  -479,  -479,  -479,   107,  -479,  -479,
    -479,  -479,  -479,  -479,  -479,  -479,  -479,  -479,  -479,  -479,
    -479,  -479,  -479,   261,   301,  -479,  -479,  -479,  -479,  -479,
    -479,  -479,  -479,  -479,  -479,  -479,  -479,  -479,  -479,   302,
    -479,  -479,  -479,   303,  -479,  -479,   290,   306,  -479,  -479,
    -479,  -479,  -479,  -479,  -479,  -479,  -479,  -479,  -479,   307,
     309,  -479,  -479,  -479,  -479,   308,   312,  -479,  -479,  -479,
    -479,  -479,  -479,  -479,  -479,  -479,  -479,   116,  -479,  -479,
    -479,   313,  -479,  -479,   315,  -479,   316,   317,  -479,  -479,
     318,   319,   320,  -479,  -479,  -479,   138,  -479,  -479,  -479,
    -479,  -479,  -479,  -479,  -479,  -479,  -479,  -479,  -479,  -479,
    -479,  -479,  -479,    19,    19,  -479,   170,   321,   322,   324,
     325,  -479,    17,  -479,   326,   191,   192,   327,   328,   329,
     196,   197,   198,   199,   332,   337,   338,   339,   340,   341,
     342,   206,   344,   345,    28,  -479,   346,   347,   209,   266,
    -479,    64,   349,   352,   353,   354,   355,   356,   357,   221,
     220,   360,   361,   362,   363,    16,  -479,   364,   365,   -17,
    -479,   366,   367,   368,   369,   370,   371,   372,   373,   374,
     375,  -479,    72,   376,   377,   241,   379,   380,   381,   243,
    -479,    77,   383,   245,   246,  -479,    53,   386,   387,   -19,
    -479,   249,   389,   390,   255,   391,   257,   260,   393,   395,
     262,   263,   264,   396,   398,   120,  -479,  -479,  -479,   399,
     397,   401,    19,    19,  -479,   402,  -479,  -479,   270,   404,
     405,  -479,  -479,  -479,  -479,   408,   409,   410,   411,   412,
     413,   414,  -479,   415,   416,  -479,   419,    58,  -479,  -479,
    -479,  -479,  -479,  -479,  -479,  -479,  -479,   417,   423,  -479,
    -479,  -479,   279,   288,   291,   422,   292,   293,   296,  -479,
    -479,    49,   297,   424,   427,  -479,   305,   431,  -479,   310,
     311,   419,   314,   323,   330,   331,   333,   334,   335,  -479,
     336,   343,  -479,   348,   350,   351,  -479,  -479,   358,  -479,
    -479,  -479,   359,    19,  -479,  -479,   378,   382,  -479,   384,
    -479,  -479,    15,   388,  -479,  -479,  -479,    23,   385,  -479,
      19,    28,   392,  -479,  -479,   266,  -479,   140,   140,   434,
     435,   439,   125,    22,   440,    96,    -9,   120,  -479,  -479,
    -479,  -479,  -479,   426,  -479,    64,  -479,  -479,  -479,   441,
    -479,  -479,  -479,  -479,  -479,  -479,  -479,  -479,   446,   400,
    -479,  -479,  -479,  -479,  -479,  -479,  -479,  -479,  -479,  -479,
    -479,  -479,  -479,  -479,  -479,  -479,  -479,  -479,  -479,  -479,
    -479,  -479,  -479,  -479,  -479,  -479,  -479,  -479,  -479,  -479,
    -479,  -479,  -479,  -479,  -479,  -479,   150,  -479,   187,  -479,
    -479,   188,  -479,  -479,  -479,  -479,   451,   452,   454,   455,
     456,  -479,  -479,  -479,   189,  -479,  -479,  -479,  -479,  -479,
    -479,  -479,  -479,  -479,  -479,  -479,  -479,  -479,   203,  -479,
     459,   463,  -479,  -479,   461,   466,  -479,  -479,   471,   469,
    -479,  -479,  -479,  -479,  -479,  -479,   259,  -479,  -479,  -479,
    -479,  -479,  -479,  -479,   280,  -479,   472,   476,  -479,   458,
     477,   480,   481,   482,   483,   229,  -479,  -479,  -479,  -479,
    -479,  -479,  -479,  -479,  -479,   230,  -479,  -479,  -479,   232,
     394,   403,  -479,  -479,   474,   486,  -479,  -479,   487,   489,
    -479,  -479,   488,  -479,   490,   392,  -479,  -479,   491,   493,
     496,   498,   406,   277,   407,   418,   421,   499,   500,   140,
    -479,  -479,    16,  -479,   434,    77,  -479,   435,    53,  -479,
     439,   125,  -479,    22,  -479,   -44,  -479,   440,   425,   428,
     429,   430,   432,   433,    96,  -479,   501,   502,    -9,  -479,
    -479,  -479,   503,   504,  -479,   -17,  -479,   441,    72,  -479,
     446,   506,  -479,   507,  -479,   182,   420,   436,   437,  -479,
    -479,  -479,  -479,  -479,   438,   442,  -479,   233,  -479,   505,
    -479,   508,  -479,  -479,  -479,   236,  -479,  -479,  -479,  -479,
    -479,  -479,  -479,  -479,   443,   444,  -479,  -479,   445,   256,
    -479,   509,  -479,   447,   512,  -479,  -479,  -479,  -479,  -479,
    -479,  -479,  -479,  -479,  -479,  -479,  -479,  -479,  -479,  -479,
    -479,  -479,  -479,  -479,  -479,  -479,   284,  -479,    59,   512,
    -479,  -479,   510,  -479,  -479,  -479,   258,  -479,  -479,  -479,
    -479,  -479,   511,   448,   516,    59,  -479,   518,  -479,   450,
    -479,   514,  -479,  -479,   294,  -479,   -88,   514,  -479,  -479,
     522,   523,   524,   265,  -479,  -479,  -479,  -479,  -479,  -479,
     525,   449,   453,   457,   -88,  -479,   460,  -479,  -479,  -479,
    -479,  -479
  };

  const unsigned short int
  Dhcp4Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     1,    39,    32,    28,    27,    24,
      25,    26,    31,     3,    29,    30,    52,     5,    63,     7,
     101,     9,   209,    11,   325,    13,   345,    15,   262,    17,
     297,    19,   174,    21,   423,    23,    41,    35,     0,     0,
       0,     0,     0,   347,   264,   299,     0,     0,    43,     0,
      42,     0,     0,    36,    61,   474,   470,   472,     0,    60,
       0,    54,    56,    58,    59,    57,    94,     0,     0,   364,
     110,   112,     0,     0,     0,     0,   201,   254,   289,   152,
     390,   166,   185,     0,   411,   421,    87,     0,    65,    67,
      68,    69,    70,    84,    85,    72,    73,    74,    75,    79,
      80,    71,    77,    78,    86,    76,    81,    82,    83,   103,
     105,     0,     0,    96,    98,    99,   100,   394,   235,   237,
     239,   317,   233,   241,   243,     0,     0,   247,   245,   337,
     386,   232,   213,   214,   215,   227,     0,   211,   218,   229,
     230,   231,   219,   220,   223,   225,   221,   222,   216,   217,
     224,   228,   226,   333,   335,   332,   330,     0,   327,   329,
     331,   366,   368,   384,   372,   374,   378,   376,   382,   380,
     370,   363,   359,     0,   348,   349,   360,   361,   362,   356,
     351,   357,   353,   354,   355,   358,   352,   279,   142,     0,
     283,   281,   286,     0,   275,   276,     0,   265,   266,   268,
     278,   269,   270,   271,   285,   272,   273,   274,   311,     0,
       0,   309,   310,   313,   314,     0,   300,   301,   303,   304,
     305,   306,   307,   308,   181,   183,   178,     0,   176,   179,
     180,     0,   443,   445,     0,   448,     0,     0,   452,   456,
       0,     0,     0,   461,   468,   441,     0,   425,   427,   428,
     429,   430,   431,   432,   433,   434,   435,   436,   437,   438,
     439,   440,    40,     0,     0,    33,     0,     0,     0,     0,
       0,    51,     0,    53,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    64,     0,     0,     0,     0,
     102,   396,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   210,     0,     0,     0,
     326,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   346,     0,     0,     0,     0,     0,     0,     0,     0,
     263,     0,     0,     0,     0,   298,     0,     0,     0,     0,
     175,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   424,    44,    37,     0,
       0,     0,     0,     0,    55,     0,    92,    93,     0,     0,
       0,    88,    89,    90,    91,     0,     0,     0,     0,     0,
       0,     0,   410,     0,     0,    66,     0,     0,   109,    97,
     408,   406,   407,   402,   403,   404,   405,     0,   397,   398,
     400,   401,     0,     0,     0,     0,     0,     0,     0,   252,
     253,     0,     0,     0,     0,   212,     0,     0,   328,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   350,
       0,     0,   277,     0,     0,     0,   288,   267,     0,   315,
     316,   302,     0,     0,   177,   442,     0,     0,   447,     0,
     450,   451,     0,     0,   458,   459,   460,     0,     0,   426,
       0,     0,     0,   471,   473,     0,   365,     0,     0,   203,
     256,   291,     0,     0,   168,     0,     0,     0,    45,   104,
     107,   108,   106,     0,   395,     0,   236,   238,   240,   319,
     234,   242,   244,   249,   250,   251,   248,   246,   339,     0,
     334,    34,   336,   367,   369,   385,   373,   375,   379,   377,
     383,   381,   371,   280,   143,   284,   282,   287,   312,   182,
     184,   444,   446,   449,   454,   455,   453,   457,   463,   464,
     465,   466,   467,   462,   469,    38,     0,   479,     0,   476,
     478,     0,   129,   135,   137,   139,     0,     0,     0,     0,
       0,   148,   150,   128,     0,   114,   116,   117,   118,   119,
     120,   121,   122,   123,   124,   125,   126,   127,     0,   207,
       0,   204,   205,   260,     0,   257,   258,   295,     0,   292,
     293,   161,   162,   163,   164,   165,     0,   154,   156,   157,
     158,   159,   160,   392,     0,   172,     0,   169,   170,     0,
       0,     0,     0,     0,     0,     0,   187,   189,   190,   191,
     192,   193,   194,   417,   419,     0,   413,   415,   416,     0,
      47,     0,   399,   323,     0,   320,   321,   343,     0,   340,
     341,   388,     0,    62,     0,     0,   475,    95,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     111,   113,     0,   202,     0,   264,   255,     0,   299,   290,
       0,     0,   153,     0,   391,     0,   167,     0,     0,     0,
       0,     0,     0,     0,     0,   186,     0,     0,     0,   412,
     422,    49,     0,    48,   409,     0,   318,     0,   347,   338,
       0,     0,   387,     0,   477,     0,     0,     0,     0,   141,
     144,   145,   146,   147,     0,     0,   115,     0,   206,     0,
     259,     0,   294,   155,   393,     0,   171,   195,   196,   197,
     198,   199,   200,   188,     0,     0,   414,    46,     0,     0,
     322,     0,   342,     0,     0,   131,   132,   133,   134,   130,
     136,   138,   140,   149,   151,   208,   261,   296,   173,   418,
     420,    50,   324,   344,   389,   483,     0,   481,     0,     0,
     480,   495,     0,   493,   491,   487,     0,   485,   489,   490,
     488,   482,     0,     0,     0,     0,   484,     0,   492,     0,
     486,     0,   494,   499,     0,   497,     0,     0,   496,   507,
       0,     0,     0,     0,   501,   503,   504,   505,   506,   498,
       0,     0,     0,     0,     0,   500,     0,   509,   510,   511,
     502,   508
  };

  const short int
  Dhcp4Parser::yypgoto_[] =
  {
    -479,  -479,  -479,  -479,  -479,  -479,  -479,  -479,  -479,  -479,
    -479,  -479,  -479,   -38,  -479,    61,  -479,  -479,  -479,  -479,
    -479,  -479,  -479,  -479,    79,  -479,  -479,  -479,   -58,  -479,
    -479,  -479,   240,  -479,  -479,  -479,  -479,    40,   219,   -60,
     -59,   -40,  -479,  -479,   -39,  -479,  -479,    42,   216,  -479,
    -479,  -479,  -479,  -479,  -479,  -479,  -479,  -479,  -479,  -479,
    -479,    38,  -141,  -479,  -479,  -479,  -479,  -479,  -479,  -479,
    -479,  -479,  -479,   -54,  -479,  -479,  -479,  -479,  -479,  -479,
    -479,  -479,  -479,  -479,  -479,  -479,  -152,  -479,  -479,  -479,
    -479,  -479,  -479,  -479,  -479,  -479,  -157,  -479,  -479,  -479,
    -154,   173,  -479,  -479,  -479,  -479,  -479,  -479,  -479,  -160,
    -479,  -479,  -479,  -479,  -479,  -479,  -479,  -479,  -479,  -479,
    -139,  -479,  -479,  -479,  -136,   214,  -479,  -479,  -479,  -479,
    -479,  -479,  -479,  -479,  -479,  -479,  -479,  -479,  -478,  -479,
    -479,  -479,  -479,  -479,  -479,  -479,  -479,  -479,  -479,  -137,
    -479,  -479,  -479,  -134,  -479,   193,  -479,   -52,  -479,  -479,
    -479,  -479,  -479,   -48,  -479,  -479,  -479,  -479,  -479,   -47,
    -479,  -479,  -479,  -138,  -479,  -479,  -479,  -135,  -479,   201,
    -479,  -479,  -479,  -479,  -479,  -479,  -479,  -479,  -479,  -479,
    -479,  -162,  -479,  -479,  -479,  -159,   218,  -479,  -479,  -479,
    -479,  -479,  -479,  -479,  -479,  -161,  -479,  -479,  -479,  -155,
    -479,   212,   -51,  -479,  -302,  -479,  -301,  -479,  -479,  -479,
    -479,  -479,  -479,  -479,  -479,  -479,  -479,  -479,  -479,  -479,
    -479,  -479,  -479,  -479,  -479,  -479,  -479,  -479,  -479,  -479,
    -479,  -479,  -479,  -479,    43,  -479,  -479,  -479,  -479,  -479,
    -479,  -479,  -143,  -479,  -479,  -479,  -479,  -479,  -479,  -479,
    -479,    65,   183,  -479,  -479,  -479,  -479,  -479,  -479,  -479,
    -479,  -479,  -479,  -479,  -479,  -479,  -479,  -479,  -479,  -479,
    -479,  -479,  -479,  -479,  -479,  -479,  -479,  -479,  -479,  -479,
    -479,  -479,  -479,   -90,  -479,  -479,  -479,  -210,  -479,  -479,
    -225,  -479,  -479,  -479,  -479,  -479,  -479,  -236,  -479,  -479,
    -248,  -479,  -479,  -479,  -479,  -479
  };

  const short int
  Dhcp4Parser::yydefgoto_[] =
  {
      -1,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    32,    33,    34,    57,   532,    72,    73,
      35,    56,    69,    70,   509,   650,   712,   713,   106,    37,
      58,    80,    81,    82,   287,    39,    59,   107,   108,   109,
     110,   111,   112,   113,   114,   115,   294,   132,   133,    41,
      60,   134,   316,   135,   317,   512,   136,   116,   298,   117,
     299,   584,   585,   586,   668,   769,   587,   669,   588,   670,
     589,   671,   590,   215,   354,   592,   593,   594,   595,   596,
     677,   597,   678,   118,   307,   616,   617,   618,   619,   620,
     621,   622,   119,   309,   626,   627,   628,   695,    53,    66,
     247,   248,   249,   367,   250,   368,   120,   310,   635,   636,
     637,   638,   639,   640,   641,   642,   121,   304,   600,   601,
     602,   682,    43,    61,   156,   157,   158,   326,   159,   322,
     160,   323,   161,   324,   162,   327,   163,   328,   164,   332,
     165,   331,   526,   166,   167,   122,   305,   604,   605,   606,
     685,    49,    64,   216,   217,   218,   219,   220,   221,   222,
     353,   223,   357,   224,   356,   225,   226,   358,   227,   123,
     306,   608,   609,   610,   688,    51,    65,   235,   236,   237,
     238,   239,   362,   240,   241,   242,   243,   169,   325,   654,
     655,   656,   715,    45,    62,   177,   178,   179,   337,   180,
     338,   170,   333,   658,   659,   660,   718,    47,    63,   193,
     194,   195,   124,   297,   197,   341,   198,   342,   199,   350,
     200,   344,   201,   345,   202,   347,   203,   346,   204,   349,
     205,   348,   206,   343,   172,   334,   662,   721,   125,   308,
     624,   321,   427,   428,   429,   430,   431,   513,   126,   127,
     312,   645,   646,   647,   706,   648,   707,   128,   313,    55,
      67,   266,   267,   268,   269,   372,   270,   373,   271,   272,
     375,   273,   274,   275,   378,   556,   276,   379,   277,   278,
     279,   280,   383,   563,   281,   384,    83,   289,    84,   290,
      85,   288,   568,   569,   570,   664,   786,   787,   788,   796,
     797,   798,   799,   804,   800,   802,   814,   815,   816,   823,
     824,   825,   830,   826,   827,   828
  };

  const unsigned short int
  Dhcp4Parser::yytable_[] =
  {
      79,   152,   153,   151,   175,   191,   214,   231,   246,   265,
     171,   232,   196,   233,   168,   176,   192,   234,    68,   425,
     426,   154,   155,   137,    25,   623,    26,    74,    27,   137,
     554,    98,    24,   819,    88,    89,   820,   821,   822,    86,
     244,   245,   173,   174,   292,    87,    88,    89,   314,   293,
      90,    91,   282,   315,   319,    92,    93,    94,   335,   320,
     138,   139,   140,   336,    98,   244,   245,    92,    93,    94,
      95,    96,   510,   511,   141,    97,    98,   142,   143,   144,
     145,   146,   147,    89,   181,   182,   643,   644,    36,   148,
     149,    89,   181,   182,    38,   148,    78,   150,    99,   100,
      40,   207,   208,   228,   209,   210,   229,   230,   208,    42,
     339,   101,    98,   208,   102,   340,   523,   524,   525,   369,
      98,   103,   104,    78,   370,   105,   208,   555,   209,   210,
      44,    46,   211,   212,   213,    75,   420,   558,   559,   560,
     561,   385,    48,   183,    76,    77,   386,   184,   185,   186,
     187,   188,   189,   314,   190,    50,    78,    78,   663,    28,
      29,    30,    31,    52,   572,    54,   562,    71,    78,   573,
     574,   575,   576,   577,   578,   579,   580,   581,   582,   791,
     283,   792,   793,   629,   630,   631,   632,   633,   634,   208,
     665,   319,   679,    78,   284,   666,   667,   680,   286,    78,
     611,   612,   613,   614,    78,   615,   679,   765,   766,   767,
     768,   681,    78,   425,   426,   744,   285,    78,   251,   252,
     253,   254,   255,   256,   257,   258,   259,   260,   261,   262,
     263,   264,   704,   708,    79,   385,   335,   705,   709,   369,
     710,   775,   291,   295,   778,   387,   388,     1,     2,     3,
       4,     5,     6,     7,     8,     9,    10,    11,   296,   339,
      78,   805,   691,   421,   782,   692,   806,   422,   834,   351,
     424,   300,   301,   835,   423,   152,   153,   151,   129,   130,
      78,   175,   131,   693,   171,   302,   694,   789,   168,   303,
     790,   311,   176,   318,   191,   154,   155,   817,   360,   329,
     818,   196,   330,   214,   352,   192,   355,   359,   231,   361,
     389,   363,   232,   364,   233,   366,   365,   371,   234,   374,
     376,   377,   380,   381,   382,   390,   391,   265,   392,   393,
     395,   398,   399,   400,   396,   397,   405,   401,   402,   403,
     404,   406,   407,   408,   409,   410,   411,   412,   413,   414,
     416,   417,   418,   432,   493,   494,   433,   434,   435,   436,
     437,   438,   439,   440,   441,   442,   443,   444,   446,   447,
     449,   450,   451,   452,   453,   454,   455,   456,   457,   458,
     460,   461,   462,   463,   464,   465,   466,   468,   469,   470,
     472,   473,   475,   476,   477,   479,   478,   482,   480,   483,
     487,   481,   488,   490,   491,   484,   485,   486,   492,   495,
     496,   497,   498,   499,   500,   501,   502,   503,   504,   516,
     730,   505,   506,   507,   508,   514,   515,   519,   517,   528,
     651,   518,   520,   521,   529,   550,   522,   527,    26,   583,
     583,   599,   603,   591,   591,   530,   607,   625,   653,   265,
     533,   534,   565,   657,   536,   672,   673,   421,   674,   675,
     676,   422,   698,   537,   424,   683,   684,   686,   423,   687,
     538,   539,   690,   540,   541,   542,   543,   689,   696,   697,
     716,   699,   661,   544,   700,   701,   702,   703,   545,   717,
     546,   547,   720,   719,   723,   725,   722,   726,   548,   549,
     727,   557,   728,   734,   735,   754,   755,   758,   531,   757,
     763,   567,   764,   776,   803,   807,   777,   783,   551,   785,
     809,   813,   552,   811,   553,   564,   831,   832,   833,   836,
     535,   566,   394,   415,   711,   419,   598,   571,   736,   743,
     746,   745,   474,   714,   753,   738,   737,   729,   731,   445,
     740,   739,   742,   741,   467,   760,   759,   448,   652,   762,
     770,   732,   733,   761,   459,   756,   747,   471,   489,   748,
     749,   750,   649,   751,   752,   724,   771,   772,   773,   801,
     810,   829,   774,   779,   780,   781,   840,   784,     0,   808,
     812,     0,   837,     0,   838,     0,     0,     0,   839,     0,
     841,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   583,   152,   153,   151,   591,     0,   214,     0,     0,
     231,   171,     0,     0,   232,   168,   233,   246,     0,     0,
     234,     0,   154,   155,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   175,     0,     0,
     191,     0,     0,     0,     0,     0,     0,   196,   176,     0,
       0,   192,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     794,     0,     0,     0,   795,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   794,     0,     0,
       0,   795
  };

  const short int
  Dhcp4Parser::yycheck_[] =
  {
      58,    61,    61,    61,    62,    63,    64,    65,    66,    67,
      61,    65,    63,    65,    61,    62,    63,    65,    56,   321,
     321,    61,    61,     7,     5,   503,     7,    10,     9,     7,
      15,    48,     0,   121,    18,    19,   124,   125,   126,    11,
      84,    85,    59,    60,     3,    17,    18,    19,     3,     8,
      22,    23,     6,     8,     3,    39,    40,    41,     3,     8,
      44,    45,    46,     8,    48,    84,    85,    39,    40,    41,
      42,    43,    14,    15,    58,    47,    48,    61,    62,    63,
      64,    65,    66,    19,    20,    21,    95,    96,     7,    73,
      74,    19,    20,    21,     7,    73,   140,    81,    70,    71,
       7,    24,    49,    50,    51,    52,    53,    54,    49,     7,
       3,    83,    48,    49,    86,     8,    67,    68,    69,     3,
      48,    93,    94,   140,     8,    97,    49,   112,    51,    52,
       7,     7,    55,    56,    57,   118,    72,   114,   115,   116,
     117,     3,     7,    71,   127,   128,     8,    75,    76,    77,
      78,    79,    80,     3,    82,     7,   140,   140,     8,   140,
     141,   142,   143,     7,    24,     7,   143,   140,   140,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,   120,
       3,   122,   123,    87,    88,    89,    90,    91,    92,    49,
       3,     3,     3,   140,     4,     8,     8,     8,     3,   140,
      75,    76,    77,    78,   140,    80,     3,    25,    26,    27,
      28,     8,   140,   515,   515,   693,     8,   140,    98,    99,
     100,   101,   102,   103,   104,   105,   106,   107,   108,   109,
     110,   111,     3,     3,   292,     3,     3,     8,     8,     3,
       8,     8,     4,     4,     8,   283,   284,   129,   130,   131,
     132,   133,   134,   135,   136,   137,   138,   139,     4,     3,
     140,     3,     3,   321,     8,     6,     8,   321,     3,     8,
     321,     4,     4,     8,   321,   335,   335,   335,    12,    13,
     140,   339,    16,     3,   335,     4,     6,     3,   335,     4,
       6,     4,   339,     4,   352,   335,   335,     3,     8,     4,
       6,   352,     4,   361,     3,   352,     4,     4,   366,     3,
     140,     4,   366,     4,   366,     3,     8,     4,   366,     4,
       4,     4,     4,     4,     4,     4,     4,   385,     4,     4,
       4,     4,     4,     4,   143,   143,     4,   141,   141,   141,
     141,     4,     4,     4,     4,     4,     4,   141,     4,     4,
       4,     4,   143,     4,   392,   393,     4,     4,     4,     4,
       4,     4,   141,   143,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,   141,     4,     4,     4,   143,     4,   143,   143,
       4,     4,   143,     4,     4,     4,   141,     4,   141,     4,
       4,   141,     4,     4,     7,   143,   143,   143,     7,     7,
     140,     7,     7,     5,     5,     5,     5,     5,     5,   140,
     143,     7,     7,     7,     5,     8,     3,     5,   140,     5,
       4,   140,   140,   140,     7,   473,   140,   140,     7,   497,
     498,     7,     7,   497,   498,   140,     7,     7,     7,   507,
     140,   140,   490,     7,   140,     4,     4,   515,     4,     4,
       4,   515,     4,   140,   515,     6,     3,     6,   515,     3,
     140,   140,     3,   140,   140,   140,   140,     6,     6,     3,
       6,     4,    82,   140,     4,     4,     4,     4,   140,     3,
     140,   140,     3,     6,     4,     4,     8,     4,   140,   140,
       4,   113,     4,     4,     4,     4,     4,     3,   447,     6,
       4,   119,     5,     8,     4,     4,     8,     8,   140,     7,
       4,     7,   140,     5,   140,   140,     4,     4,     4,     4,
     451,   491,   292,   314,   140,   319,   498,   495,   679,   691,
     697,   695,   369,   140,   704,   684,   682,   141,   141,   335,
     687,   685,   690,   688,   361,   717,   715,   339,   515,   720,
     140,   143,   141,   718,   352,   708,   141,   366,   385,   141,
     141,   141,   507,   141,   141,   665,   140,   140,   140,   789,
     805,   817,   140,   140,   140,   140,   834,   140,    -1,   141,
     140,    -1,   143,    -1,   141,    -1,    -1,    -1,   141,    -1,
     140,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   679,   682,   682,   682,   679,    -1,   685,    -1,    -1,
     688,   682,    -1,    -1,   688,   682,   688,   695,    -1,    -1,
     688,    -1,   682,   682,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   715,    -1,    -1,
     718,    -1,    -1,    -1,    -1,    -1,    -1,   718,   715,    -1,
      -1,   718,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     788,    -1,    -1,    -1,   788,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   805,    -1,    -1,
      -1,   805
  };

  const unsigned short int
  Dhcp4Parser::yystos_[] =
  {
       0,   129,   130,   131,   132,   133,   134,   135,   136,   137,
     138,   139,   145,   146,   147,   148,   149,   150,   151,   152,
     153,   154,   155,   156,     0,     5,     7,     9,   140,   141,
     142,   143,   157,   158,   159,   164,     7,   173,     7,   179,
       7,   193,     7,   266,     7,   337,     7,   351,     7,   295,
       7,   319,     7,   242,     7,   403,   165,   160,   174,   180,
     194,   267,   338,   352,   296,   320,   243,   404,   157,   166,
     167,   140,   162,   163,    10,   118,   127,   128,   140,   172,
     175,   176,   177,   430,   432,   434,    11,    17,    18,    19,
      22,    23,    39,    40,    41,    42,    43,    47,    48,    70,
      71,    83,    86,    93,    94,    97,   172,   181,   182,   183,
     184,   185,   186,   187,   188,   189,   201,   203,   227,   236,
     250,   260,   289,   313,   356,   382,   392,   393,   401,    12,
      13,    16,   191,   192,   195,   197,   200,     7,    44,    45,
      46,    58,    61,    62,    63,    64,    65,    66,    73,    74,
      81,   172,   183,   184,   185,   188,   268,   269,   270,   272,
     274,   276,   278,   280,   282,   284,   287,   288,   313,   331,
     345,   356,   378,    59,    60,   172,   313,   339,   340,   341,
     343,    20,    21,    71,    75,    76,    77,    78,    79,    80,
      82,   172,   313,   353,   354,   355,   356,   358,   360,   362,
     364,   366,   368,   370,   372,   374,   376,    24,    49,    51,
      52,    55,    56,    57,   172,   217,   297,   298,   299,   300,
     301,   302,   303,   305,   307,   309,   310,   312,    50,    53,
      54,   172,   217,   301,   307,   321,   322,   323,   324,   325,
     327,   328,   329,   330,    84,    85,   172,   244,   245,   246,
     248,    98,    99,   100,   101,   102,   103,   104,   105,   106,
     107,   108,   109,   110,   111,   172,   405,   406,   407,   408,
     410,   412,   413,   415,   416,   417,   420,   422,   423,   424,
     425,   428,     6,     3,     4,     8,     3,   178,   435,   431,
     433,     4,     3,     8,   190,     4,     4,   357,   202,   204,
       4,     4,     4,     4,   261,   290,   314,   228,   383,   237,
     251,     4,   394,   402,     3,     8,   196,   198,     4,     3,
       8,   385,   273,   275,   277,   332,   271,   279,   281,     4,
       4,   285,   283,   346,   379,     3,     8,   342,   344,     3,
       8,   359,   361,   377,   365,   367,   371,   369,   375,   373,
     363,     8,     3,   304,   218,     4,   308,   306,   311,     4,
       8,     3,   326,     4,     4,     8,     3,   247,   249,     3,
       8,     4,   409,   411,     4,   414,     4,     4,   418,   421,
       4,     4,     4,   426,   429,     3,     8,   157,   157,   140,
       4,     4,     4,     4,   176,     4,   143,   143,     4,     4,
       4,   141,   141,   141,   141,     4,     4,     4,     4,     4,
       4,     4,   141,     4,     4,   182,     4,     4,   143,   192,
      72,   172,   217,   313,   356,   358,   360,   386,   387,   388,
     389,   390,     4,     4,     4,     4,     4,     4,     4,   141,
     143,     4,     4,     4,     4,   269,     4,     4,   340,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,   355,
       4,     4,   141,     4,     4,     4,   143,   299,     4,   143,
     143,   323,     4,     4,   245,   143,     4,     4,   141,     4,
     141,   141,     4,     4,   143,   143,   143,     4,     4,   406,
       4,     7,     7,   157,   157,     7,   140,     7,     7,     5,
       5,     5,     5,     5,     5,     7,     7,     7,     5,   168,
      14,    15,   199,   391,     8,     3,   140,   140,   140,     5,
     140,   140,   140,    67,    68,    69,   286,   140,     5,     7,
     140,   159,   161,   140,   140,   168,   140,   140,   140,   140,
     140,   140,   140,   140,   140,   140,   140,   140,   140,   140,
     157,   140,   140,   140,    15,   112,   419,   113,   114,   115,
     116,   117,   143,   427,   140,   157,   181,   119,   436,   437,
     438,   191,    24,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,   172,   205,   206,   207,   210,   212,   214,
     216,   217,   219,   220,   221,   222,   223,   225,   205,     7,
     262,   263,   264,     7,   291,   292,   293,     7,   315,   316,
     317,    75,    76,    77,    78,    80,   229,   230,   231,   232,
     233,   234,   235,   282,   384,     7,   238,   239,   240,    87,
      88,    89,    90,    91,    92,   252,   253,   254,   255,   256,
     257,   258,   259,    95,    96,   395,   396,   397,   399,   405,
     169,     4,   388,     7,   333,   334,   335,     7,   347,   348,
     349,    82,   380,     8,   439,     3,     8,     8,   208,   211,
     213,   215,     4,     4,     4,     4,     4,   224,   226,     3,
       8,     8,   265,     6,     3,   294,     6,     3,   318,     6,
       3,     3,     6,     3,     6,   241,     6,     3,     4,     4,
       4,     4,     4,     4,     3,     8,   398,   400,     3,     8,
       8,   140,   170,   171,   140,   336,     6,     3,   350,     6,
       3,   381,     8,     4,   437,     4,     4,     4,     4,   141,
     143,   141,   143,   141,     4,     4,   206,   268,   264,   297,
     293,   321,   317,   230,   282,   244,   240,   141,   141,   141,
     141,   141,   141,   253,     4,     4,   396,     6,     3,   339,
     335,   353,   349,     4,     5,    25,    26,    27,    28,   209,
     140,   140,   140,   140,   140,     8,     8,     8,     8,   140,
     140,   140,     8,     8,   140,     7,   440,   441,   442,     3,
       6,   120,   122,   123,   172,   217,   443,   444,   445,   446,
     448,   441,   449,     4,   447,     3,     8,     4,   141,     4,
     444,     5,   140,     7,   450,   451,   452,     3,     6,   121,
     124,   125,   126,   453,   454,   455,   457,   458,   459,   451,
     456,     4,     4,     4,     3,     8,     4,   143,   141,   141,
     454,   140
  };

  const unsigned short int
  Dhcp4Parser::yyr1_[] =
  {
       0,   144,   146,   145,   147,   145,   148,   145,   149,   145,
     150,   145,   151,   145,   152,   145,   153,   145,   154,   145,
     155,   145,   156,   145,   157,   157,   157,   157,   157,   157,
     157,   158,   160,   159,   161,   162,   162,   163,   163,   165,
     164,   166,   166,   167,   167,   169,   168,   170,   170,   171,
     171,   172,   174,   173,   175,   175,   176,   176,   176,   176,
     176,   178,   177,   180,   179,   181,   181,   182,   182,   182,
     182,   182,   182,   182,   182,   182,   182,   182,   182,   182,
     182,   182,   182,   182,   182,   182,   182,   182,   183,   184,
     185,   186,   187,   188,   190,   189,   191,   191,   192,   192,
     192,   194,   193,   196,   195,   198,   197,   199,   199,   200,
     202,   201,   204,   203,   205,   205,   206,   206,   206,   206,
     206,   206,   206,   206,   206,   206,   206,   206,   206,   208,
     207,   209,   209,   209,   209,   211,   210,   213,   212,   215,
     214,   216,   218,   217,   219,   220,   221,   222,   224,   223,
     226,   225,   228,   227,   229,   229,   230,   230,   230,   230,
     230,   231,   232,   233,   234,   235,   237,   236,   238,   238,
     239,   239,   241,   240,   243,   242,   244,   244,   244,   245,
     245,   247,   246,   249,   248,   251,   250,   252,   252,   253,
     253,   253,   253,   253,   253,   254,   255,   256,   257,   258,
     259,   261,   260,   262,   262,   263,   263,   265,   264,   267,
     266,   268,   268,   269,   269,   269,   269,   269,   269,   269,
     269,   269,   269,   269,   269,   269,   269,   269,   269,   269,
     269,   269,   269,   271,   270,   273,   272,   275,   274,   277,
     276,   279,   278,   281,   280,   283,   282,   285,   284,   286,
     286,   286,   287,   288,   290,   289,   291,   291,   292,   292,
     294,   293,   296,   295,   297,   297,   298,   298,   299,   299,
     299,   299,   299,   299,   299,   299,   300,   301,   302,   304,
     303,   306,   305,   308,   307,   309,   311,   310,   312,   314,
     313,   315,   315,   316,   316,   318,   317,   320,   319,   321,
     321,   322,   322,   323,   323,   323,   323,   323,   323,   323,
     324,   326,   325,   327,   328,   329,   330,   332,   331,   333,
     333,   334,   334,   336,   335,   338,   337,   339,   339,   340,
     340,   340,   340,   342,   341,   344,   343,   346,   345,   347,
     347,   348,   348,   350,   349,   352,   351,   353,   353,   354,
     354,   355,   355,   355,   355,   355,   355,   355,   355,   355,
     355,   355,   355,   355,   357,   356,   359,   358,   361,   360,
     363,   362,   365,   364,   367,   366,   369,   368,   371,   370,
     373,   372,   375,   374,   377,   376,   379,   378,   381,   380,
     383,   382,   384,   384,   385,   282,   386,   386,   387,   387,
     388,   388,   388,   388,   388,   388,   388,   389,   391,   390,
     392,   394,   393,   395,   395,   396,   396,   398,   397,   400,
     399,   402,   401,   404,   403,   405,   405,   406,   406,   406,
     406,   406,   406,   406,   406,   406,   406,   406,   406,   406,
     406,   406,   407,   409,   408,   411,   410,   412,   414,   413,
     415,   416,   418,   417,   419,   419,   421,   420,   422,   423,
     424,   426,   425,   427,   427,   427,   427,   427,   429,   428,
     431,   430,   433,   432,   435,   434,   436,   436,   437,   439,
     438,   440,   440,   442,   441,   443,   443,   444,   444,   444,
     444,   444,   445,   447,   446,   449,   448,   450,   450,   452,
     451,   453,   453,   454,   454,   454,   454,   456,   455,   457,
     458,   459
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
       4,     0,     4,     0,     4,     0,     4,     0,     4,     1,
       1,     1,     3,     3,     0,     6,     0,     1,     1,     3,
       0,     4,     0,     4,     0,     1,     1,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     3,     1,     0,
       4,     0,     4,     0,     4,     1,     0,     4,     3,     0,
       6,     0,     1,     1,     3,     0,     4,     0,     4,     0,
       1,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     0,     4,     1,     1,     3,     3,     0,     6,     0,
       1,     1,     3,     0,     4,     0,     4,     1,     3,     1,
       1,     1,     1,     0,     4,     0,     4,     0,     6,     0,
       1,     1,     3,     0,     4,     0,     4,     0,     1,     1,
       3,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     0,     4,     0,     4,     0,     4,
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
       4,     1,     3,     1,     1,     1,     1,     0,     4,     3,
       3,     3
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
  "\"data\"", "\"code\"", "\"space\"", "\"csv-format\"", "\"always-send\"",
  "\"record-types\"", "\"encapsulate\"", "\"array\"", "\"pools\"",
  "\"pool\"", "\"user-context\"", "\"subnet\"", "\"interface\"",
  "\"interface-id\"", "\"id\"", "\"rapid-commit\"", "\"reservation-mode\"",
  "\"disabled\"", "\"out-of-pool\"", "\"all\"",
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
  "$@46", "client_class", "$@47", "reservation_mode", "$@48", "hr_mode",
  "id", "rapid_commit", "option_def_list", "$@49",
  "option_def_list_content", "not_empty_option_def_list",
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
  "option_data_always_send", "pools_list", "$@60", "pools_list_content",
  "not_empty_pools_list", "pool_list_entry", "$@61", "sub_pool4", "$@62",
  "pool_params", "pool_param", "pool_entry", "$@63", "user_context",
  "$@64", "reservations", "$@65", "reservations_list",
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
       0,   225,   225,   225,   226,   226,   227,   227,   228,   228,
     229,   229,   230,   230,   231,   231,   232,   232,   233,   233,
     234,   234,   235,   235,   243,   244,   245,   246,   247,   248,
     249,   252,   257,   257,   268,   271,   272,   275,   279,   286,
     286,   293,   294,   297,   301,   308,   308,   315,   316,   319,
     323,   334,   344,   344,   356,   357,   361,   362,   363,   364,
     365,   368,   368,   385,   385,   393,   394,   399,   400,   401,
     402,   403,   404,   405,   406,   407,   408,   409,   410,   411,
     412,   413,   414,   415,   416,   417,   418,   419,   422,   427,
     432,   437,   442,   447,   453,   453,   463,   464,   467,   468,
     469,   472,   472,   480,   480,   490,   490,   497,   498,   501,
     507,   507,   517,   517,   527,   528,   531,   532,   533,   534,
     535,   536,   537,   538,   539,   540,   541,   542,   543,   546,
     546,   553,   554,   555,   556,   559,   559,   567,   567,   575,
     575,   583,   588,   588,   596,   601,   606,   611,   616,   616,
     624,   624,   633,   633,   643,   644,   647,   648,   649,   650,
     651,   654,   659,   664,   669,   674,   679,   679,   689,   690,
     693,   694,   697,   697,   705,   705,   713,   714,   715,   718,
     719,   722,   722,   730,   730,   738,   738,   748,   749,   752,
     753,   754,   755,   756,   757,   760,   765,   770,   775,   780,
     785,   793,   793,   806,   807,   810,   811,   818,   818,   841,
     841,   850,   851,   855,   856,   857,   858,   859,   860,   861,
     862,   863,   864,   865,   866,   867,   868,   869,   870,   871,
     872,   873,   874,   877,   877,   885,   885,   893,   893,   901,
     901,   909,   909,   917,   917,   925,   925,   933,   933,   940,
     941,   942,   945,   950,   959,   959,   971,   972,   975,   976,
     981,   981,   992,   992,  1002,  1003,  1006,  1007,  1010,  1011,
    1012,  1013,  1014,  1015,  1016,  1017,  1020,  1022,  1027,  1029,
    1029,  1037,  1037,  1045,  1045,  1053,  1055,  1055,  1063,  1072,
    1072,  1084,  1085,  1090,  1091,  1096,  1096,  1107,  1107,  1118,
    1119,  1124,  1125,  1130,  1131,  1132,  1133,  1134,  1135,  1136,
    1139,  1141,  1141,  1149,  1151,  1153,  1158,  1166,  1166,  1178,
    1179,  1182,  1183,  1186,  1186,  1194,  1194,  1202,  1203,  1206,
    1207,  1208,  1209,  1212,  1212,  1220,  1220,  1230,  1230,  1240,
    1241,  1244,  1245,  1248,  1248,  1256,  1256,  1264,  1265,  1268,
    1269,  1273,  1274,  1275,  1276,  1277,  1278,  1279,  1280,  1281,
    1282,  1283,  1284,  1285,  1288,  1288,  1296,  1296,  1304,  1304,
    1312,  1312,  1320,  1320,  1328,  1328,  1336,  1336,  1344,  1344,
    1352,  1352,  1360,  1360,  1368,  1368,  1381,  1381,  1391,  1391,
    1402,  1402,  1412,  1413,  1416,  1416,  1424,  1425,  1428,  1429,
    1432,  1433,  1434,  1435,  1436,  1437,  1438,  1441,  1443,  1443,
    1455,  1462,  1462,  1472,  1473,  1476,  1477,  1480,  1480,  1488,
    1488,  1498,  1498,  1508,  1508,  1516,  1517,  1520,  1521,  1522,
    1523,  1524,  1525,  1526,  1527,  1528,  1529,  1530,  1531,  1532,
    1533,  1534,  1537,  1542,  1542,  1550,  1550,  1558,  1563,  1563,
    1571,  1576,  1581,  1581,  1589,  1590,  1593,  1593,  1601,  1606,
    1611,  1616,  1616,  1624,  1627,  1630,  1633,  1636,  1642,  1642,
    1652,  1652,  1659,  1659,  1671,  1671,  1684,  1685,  1689,  1693,
    1693,  1705,  1706,  1710,  1710,  1718,  1719,  1722,  1723,  1724,
    1725,  1726,  1729,  1734,  1734,  1742,  1742,  1752,  1753,  1756,
    1756,  1764,  1765,  1768,  1769,  1770,  1771,  1774,  1774,  1782,
    1787,  1792
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
#line 4168 "dhcp4_parser.cc" // lalr1.cc:1167
#line 1797 "dhcp4_parser.yy" // lalr1.cc:1168


void
isc::dhcp::Dhcp4Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
