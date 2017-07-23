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
      case 418: // ncr_protocol_value
      case 426: // replace_client_name_value
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
      case 418: // ncr_protocol_value
      case 426: // replace_client_name_value
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

      case 418: // ncr_protocol_value

#line 216 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 427 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 426: // replace_client_name_value

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

    // FIXME: This should be completely indented.  It is not yet to
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
      case 418: // ncr_protocol_value
      case 426: // replace_client_name_value
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

  case 62:
#line 370 "dhcp4_parser.yy" // lalr1.cc:859
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

  case 63:
#line 377 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 964 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 64:
#line 387 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the Dhcp4 map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 974 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 65:
#line 391 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 982 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 89:
#line 424 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 991 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 90:
#line 429 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 1000 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 91:
#line 434 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 1009 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 92:
#line 439 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr dpp(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 1018 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 93:
#line 444 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr echo(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("echo-client-id", echo);
}
#line 1027 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 94:
#line 449 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr match(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("match-client-id", match);
}
#line 1036 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 95:
#line 455 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces-config", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.INTERFACES_CONFIG);
}
#line 1047 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 96:
#line 460 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1056 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 102:
#line 474 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1066 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 103:
#line 478 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1074 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 104:
#line 482 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1085 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 105:
#line 487 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1094 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 106:
#line 492 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.DHCP_SOCKET_TYPE);
}
#line 1102 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 107:
#line 494 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("dhcp-socket-type", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1111 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 108:
#line 499 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("raw", ctx.loc2pos(yystack_[0].location))); }
#line 1117 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 109:
#line 500 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("udp", ctx.loc2pos(yystack_[0].location))); }
#line 1123 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 110:
#line 503 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("re-detect", b);
}
#line 1132 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 111:
#line 509 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lease-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.LEASE_DATABASE);
}
#line 1143 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 112:
#line 514 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1152 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 113:
#line 519 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1163 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 114:
#line 524 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1172 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 130:
#line 548 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.DATABASE_TYPE);
}
#line 1180 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 131:
#line 550 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("type", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1189 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 132:
#line 555 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("memfile", ctx.loc2pos(yystack_[0].location))); }
#line 1195 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 133:
#line 556 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("mysql", ctx.loc2pos(yystack_[0].location))); }
#line 1201 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 134:
#line 557 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("postgresql", ctx.loc2pos(yystack_[0].location))); }
#line 1207 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 135:
#line 558 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("cql", ctx.loc2pos(yystack_[0].location))); }
#line 1213 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 136:
#line 561 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1221 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 137:
#line 563 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr user(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1231 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 138:
#line 569 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1239 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 139:
#line 571 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr pwd(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 1249 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 140:
#line 577 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1257 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 141:
#line 579 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr h(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 1267 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 142:
#line 585 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr p(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", p);
}
#line 1276 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 143:
#line 590 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1284 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 144:
#line 592 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1294 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 145:
#line 598 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 1303 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 146:
#line 603 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 1312 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 147:
#line 608 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 1321 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 148:
#line 613 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("connect-timeout", n);
}
#line 1330 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 149:
#line 618 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1338 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 150:
#line 620 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr cp(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("contact-points", cp);
    ctx.leave();
}
#line 1348 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 151:
#line 626 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1356 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 152:
#line 628 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr ks(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("keyspace", ks);
    ctx.leave();
}
#line 1366 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 153:
#line 635 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 1377 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 154:
#line 640 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1386 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 162:
#line 656 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1395 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 163:
#line 661 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 1404 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 164:
#line 666 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr circuit(new StringElement("circuit-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(circuit);
}
#line 1413 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 165:
#line 671 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr client(new StringElement("client-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(client);
}
#line 1422 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 166:
#line 676 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr flex_id(new StringElement("flex-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(flex_id);
}
#line 1431 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 167:
#line 681 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 1442 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 168:
#line 686 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1451 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 173:
#line 699 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1461 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 174:
#line 703 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1469 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 175:
#line 707 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1479 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 176:
#line 711 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1487 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 182:
#line 724 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1495 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 183:
#line 726 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr lib(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 1505 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 184:
#line 732 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1513 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 185:
#line 734 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1522 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 186:
#line 740 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.EXPIRED_LEASES_PROCESSING);
}
#line 1533 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 187:
#line 745 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1542 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 196:
#line 762 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 1551 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 197:
#line 767 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 1560 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 198:
#line 772 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 1569 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 199:
#line 777 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 1578 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 200:
#line 782 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 1587 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 201:
#line 787 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 1596 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 202:
#line 795 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet4", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET4);
}
#line 1607 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 203:
#line 800 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1616 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 208:
#line 820 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1626 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 209:
#line 824 "dhcp4_parser.yy" // lalr1.cc:859
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

  case 210:
#line 843 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the subnet4 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1659 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 211:
#line 847 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1667 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 234:
#line 879 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1675 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 235:
#line 881 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr subnet(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 1685 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 236:
#line 887 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1693 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 237:
#line 889 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface", iface);
    ctx.leave();
}
#line 1703 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 238:
#line 895 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1711 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 239:
#line 897 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface-id", iface);
    ctx.leave();
}
#line 1721 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 240:
#line 903 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1729 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 241:
#line 905 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-subnet", iface);
    ctx.leave();
}
#line 1739 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 242:
#line 911 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1747 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 243:
#line 913 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 1757 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 244:
#line 919 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1765 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 245:
#line 921 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface-id", iface);
    ctx.leave();
}
#line 1775 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 246:
#line 927 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.CLIENT_CLASS);
}
#line 1783 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 247:
#line 929 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr cls(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 1793 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 248:
#line 935 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.RESERVATION_MODE);
}
#line 1801 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 249:
#line 937 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("reservation-mode", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1810 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 250:
#line 942 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("disabled", ctx.loc2pos(yystack_[0].location))); }
#line 1816 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 251:
#line 943 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("out-of-pool", ctx.loc2pos(yystack_[0].location))); }
#line 1822 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 252:
#line 944 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("all", ctx.loc2pos(yystack_[0].location))); }
#line 1828 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 253:
#line 947 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr id(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 1837 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 254:
#line 952 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr rc(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rapid-commit", rc);
}
#line 1846 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 255:
#line 961 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 1857 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 256:
#line 966 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1866 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 261:
#line 983 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1876 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 262:
#line 987 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1884 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 263:
#line 994 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1894 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 264:
#line 998 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1902 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 278:
#line 1024 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr code(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 1911 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 280:
#line 1031 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1919 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 281:
#line 1033 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 1929 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 282:
#line 1039 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1937 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 283:
#line 1041 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 1947 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 284:
#line 1047 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1955 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 285:
#line 1049 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr space(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 1965 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 287:
#line 1057 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1973 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 288:
#line 1059 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr encap(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 1983 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 289:
#line 1065 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr array(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 1992 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 290:
#line 1074 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 2003 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 291:
#line 1079 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2012 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 296:
#line 1098 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2022 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 297:
#line 1102 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2030 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 298:
#line 1109 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2040 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 299:
#line 1113 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 2048 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 311:
#line 1142 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2056 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 312:
#line 1144 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr data(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 2066 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 315:
#line 1154 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr space(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", space);
}
#line 2075 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 316:
#line 1162 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 2086 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 317:
#line 1167 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2095 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 322:
#line 1182 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2105 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 323:
#line 1186 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2113 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 324:
#line 1190 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2123 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 325:
#line 1194 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 2131 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 332:
#line 1208 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2139 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 333:
#line 1210 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr pool(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 2149 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 334:
#line 1216 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2157 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 335:
#line 1218 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("user-context", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2166 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 336:
#line 1226 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 2177 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 337:
#line 1231 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2186 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 342:
#line 1244 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2196 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 343:
#line 1248 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2204 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 344:
#line 1252 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2214 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 345:
#line 1256 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 2222 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 363:
#line 1284 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2230 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 364:
#line 1286 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr next_server(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("next-server", next_server);
    ctx.leave();
}
#line 2240 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 365:
#line 1292 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2248 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 366:
#line 1294 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr srv(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-hostname", srv);
    ctx.leave();
}
#line 2258 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 367:
#line 1300 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2266 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 368:
#line 1302 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr bootfile(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("boot-file-name", bootfile);
    ctx.leave();
}
#line 2276 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 369:
#line 1308 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2284 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 370:
#line 1310 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr addr(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", addr);
    ctx.leave();
}
#line 2294 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 371:
#line 1316 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2302 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 372:
#line 1318 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr d(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 2312 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 373:
#line 1324 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2320 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 374:
#line 1326 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 2330 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 375:
#line 1332 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2338 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 376:
#line 1334 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-id", hw);
    ctx.leave();
}
#line 2348 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 377:
#line 1340 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2356 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 378:
#line 1342 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("circuit-id", hw);
    ctx.leave();
}
#line 2366 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 379:
#line 1348 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2374 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 380:
#line 1350 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flex-id", hw);
    ctx.leave();
}
#line 2384 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 381:
#line 1356 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2392 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 382:
#line 1358 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr host(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 2402 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 383:
#line 1364 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2413 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 384:
#line 1369 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2422 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 385:
#line 1377 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 2433 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 386:
#line 1382 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2442 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 387:
#line 1387 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2450 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 388:
#line 1389 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr ip(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", ip);
    ctx.leave();
}
#line 2460 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 389:
#line 1398 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 2471 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 390:
#line 1403 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2480 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 393:
#line 1412 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2490 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 394:
#line 1416 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2498 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 407:
#line 1439 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2506 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 408:
#line 1441 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr test(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 2516 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 409:
#line 1451 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 2525 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 410:
#line 1458 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 2536 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 411:
#line 1463 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2545 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 416:
#line 1476 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2553 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 417:
#line 1478 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr stype(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 2563 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 418:
#line 1484 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2571 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 419:
#line 1486 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 2581 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 420:
#line 1494 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 2592 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 421:
#line 1499 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2601 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 422:
#line 1504 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2611 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 423:
#line 1508 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 2619 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 441:
#line 1533 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 2628 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 442:
#line 1538 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2636 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 443:
#line 1540 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("qualifying-suffix", s);
    ctx.leave();
}
#line 2646 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 444:
#line 1546 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2654 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 445:
#line 1548 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 2664 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 446:
#line 1554 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 2673 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 447:
#line 1559 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2681 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 448:
#line 1561 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 2691 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 449:
#line 1567 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 2700 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 450:
#line 1572 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 2709 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 451:
#line 1577 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 2717 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 452:
#line 1579 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2726 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 453:
#line 1585 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 2732 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 454:
#line 1586 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 2738 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 455:
#line 1589 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NCR_FORMAT);
}
#line 2746 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 456:
#line 1591 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 2756 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 457:
#line 1597 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-include-fqdn", b);
}
#line 2765 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 458:
#line 1602 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-no-update", b);
}
#line 2774 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 459:
#line 1607 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-client-update", b);
}
#line 2783 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 460:
#line 1612 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 2791 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 461:
#line 1614 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("replace-client-name", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2800 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 462:
#line 1620 "dhcp4_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("when-present", ctx.loc2pos(yystack_[0].location))); 
      }
#line 2808 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 463:
#line 1623 "dhcp4_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location)));
      }
#line 2816 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 464:
#line 1626 "dhcp4_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("always", ctx.loc2pos(yystack_[0].location)));
      }
#line 2824 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 465:
#line 1629 "dhcp4_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("when-not-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 2832 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 466:
#line 1632 "dhcp4_parser.yy" // lalr1.cc:859
    {
      error(yystack_[0].location, "boolean values for the replace-client-name are "
                "no longer supported");
      }
#line 2841 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 467:
#line 1638 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2849 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 468:
#line 1640 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("generated-prefix", s);
    ctx.leave();
}
#line 2859 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 469:
#line 1648 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2867 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 470:
#line 1650 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("Dhcp6", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2876 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 471:
#line 1655 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2884 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 472:
#line 1657 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("DhcpDdns", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2893 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 473:
#line 1662 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2901 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 474:
#line 1664 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("Control-agent", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2910 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 475:
#line 1674 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Logging", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.LOGGING);
}
#line 2921 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 476:
#line 1679 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2930 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 480:
#line 1696 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 2941 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 481:
#line 1701 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2950 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 484:
#line 1713 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 2960 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 485:
#line 1717 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2968 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 493:
#line 1732 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr dl(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 2977 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 494:
#line 1737 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2985 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 495:
#line 1739 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 2995 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 496:
#line 1745 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 3006 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 497:
#line 1750 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3015 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 500:
#line 1759 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3025 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 501:
#line 1763 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 3033 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 508:
#line 1777 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3041 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 509:
#line 1779 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 3051 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 510:
#line 1785 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr flush(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 3060 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 511:
#line 1790 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr maxsize(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 3069 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 512:
#line 1795 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr maxver(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 3078 "dhcp4_parser.cc" // lalr1.cc:859
    break;


#line 3082 "dhcp4_parser.cc" // lalr1.cc:859
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


  const short int Dhcp4Parser::yypact_ninf_ = -482;

  const signed char Dhcp4Parser::yytable_ninf_ = -1;

  const short int
  Dhcp4Parser::yypact_[] =
  {
      66,  -482,  -482,  -482,  -482,  -482,  -482,  -482,  -482,  -482,
    -482,  -482,    99,    19,   102,   119,   168,   184,   185,   205,
     225,   235,   236,   247,  -482,  -482,  -482,  -482,  -482,  -482,
    -482,  -482,  -482,  -482,  -482,  -482,  -482,  -482,  -482,  -482,
    -482,  -482,  -482,  -482,  -482,  -482,  -482,  -482,  -482,  -482,
    -482,  -482,  -482,  -482,  -482,  -482,    19,   115,    17,    54,
     177,    18,    26,    93,   128,   -19,   -33,   120,  -482,   204,
     260,   265,   258,   270,  -482,  -482,  -482,  -482,  -482,   271,
    -482,    53,  -482,  -482,  -482,  -482,  -482,  -482,  -482,   279,
     280,  -482,  -482,  -482,   282,   283,   286,   287,  -482,  -482,
    -482,  -482,  -482,  -482,  -482,   289,  -482,  -482,  -482,    97,
    -482,  -482,  -482,  -482,  -482,  -482,  -482,  -482,  -482,  -482,
    -482,  -482,  -482,  -482,  -482,  -482,  -482,  -482,  -482,  -482,
    -482,  -482,  -482,   293,   125,  -482,  -482,  -482,  -482,  -482,
    -482,  -482,  -482,  -482,  -482,  -482,  -482,   294,   295,  -482,
    -482,  -482,  -482,  -482,  -482,  -482,  -482,  -482,   132,  -482,
    -482,  -482,  -482,  -482,  -482,  -482,  -482,  -482,  -482,  -482,
    -482,  -482,  -482,  -482,  -482,  -482,  -482,  -482,  -482,   134,
    -482,  -482,  -482,  -482,  -482,  -482,  -482,  -482,  -482,  -482,
    -482,  -482,  -482,  -482,  -482,   292,   298,  -482,  -482,  -482,
    -482,  -482,  -482,  -482,  -482,  -482,  -482,  -482,  -482,  -482,
    -482,   302,  -482,  -482,  -482,   303,  -482,  -482,   301,   307,
    -482,  -482,  -482,  -482,  -482,  -482,  -482,  -482,  -482,  -482,
    -482,   308,  -482,  -482,  -482,  -482,   305,   311,  -482,  -482,
    -482,  -482,  -482,  -482,  -482,  -482,  -482,   145,  -482,  -482,
    -482,   312,  -482,  -482,   314,  -482,   316,   317,  -482,  -482,
     318,   319,   320,  -482,  -482,  -482,   146,  -482,  -482,  -482,
    -482,  -482,  -482,  -482,  -482,  -482,  -482,  -482,  -482,  -482,
    -482,  -482,  -482,    19,    19,  -482,   171,   321,   322,   324,
     325,   326,  -482,    17,  -482,   327,   172,   189,   329,   330,
     331,   195,   196,   197,   198,   336,   337,   338,   339,   340,
     341,   342,   207,   343,   345,    54,  -482,   346,   347,   209,
     177,  -482,    67,   349,   350,   351,   355,   356,   357,   358,
     222,   221,   361,   362,   363,   364,    18,  -482,   365,   366,
      26,  -482,   367,   368,   369,   370,   371,   372,   373,   374,
     375,   376,  -482,    93,   377,   378,   244,   379,   380,   382,
     245,  -482,   128,   383,   246,  -482,   -19,   386,   387,   -15,
    -482,   251,   388,   389,   254,   392,   256,   257,   395,   396,
     261,   263,   264,   397,   398,   120,  -482,  -482,  -482,   399,
     401,   402,    19,    19,    19,  -482,   403,  -482,  -482,   272,
     404,   406,  -482,  -482,  -482,  -482,   400,   409,   410,   411,
     412,   413,   414,  -482,   415,   416,  -482,   419,   141,  -482,
    -482,  -482,  -482,  -482,  -482,  -482,  -482,  -482,   417,   423,
    -482,  -482,  -482,   288,   290,   291,   422,   299,   304,   306,
    -482,  -482,   213,   309,   424,   425,  -482,   315,   426,  -482,
     323,   332,   419,   333,   334,   335,   344,   348,   352,   353,
    -482,   354,   359,  -482,   360,   381,   384,  -482,  -482,   385,
    -482,  -482,   390,    19,  -482,  -482,   391,   393,  -482,   394,
    -482,  -482,    14,   405,  -482,  -482,  -482,    72,   407,  -482,
      19,    54,   408,  -482,  -482,  -482,   177,  -482,    11,    11,
     427,   431,   435,    43,    32,   436,   150,    70,   120,  -482,
    -482,  -482,  -482,  -482,   441,  -482,    67,  -482,  -482,  -482,
     440,  -482,  -482,  -482,  -482,  -482,  -482,  -482,  -482,   444,
     420,  -482,  -482,  -482,  -482,  -482,  -482,  -482,  -482,  -482,
    -482,  -482,  -482,  -482,  -482,  -482,  -482,  -482,  -482,  -482,
    -482,  -482,  -482,  -482,  -482,  -482,  -482,  -482,  -482,  -482,
    -482,  -482,  -482,  -482,  -482,  -482,  -482,   170,  -482,   173,
    -482,  -482,   203,  -482,  -482,  -482,  -482,   448,   452,   453,
     455,   456,  -482,  -482,  -482,   206,  -482,  -482,  -482,  -482,
    -482,  -482,  -482,  -482,  -482,  -482,  -482,  -482,  -482,   241,
    -482,   442,   458,  -482,  -482,   460,   459,  -482,  -482,   461,
     466,  -482,  -482,  -482,  -482,  -482,  -482,    64,  -482,  -482,
    -482,  -482,  -482,  -482,  -482,    86,  -482,   464,   468,  -482,
     472,   473,   474,   475,   476,   477,   242,  -482,  -482,  -482,
    -482,  -482,  -482,  -482,  -482,  -482,   243,  -482,  -482,  -482,
     249,   418,   421,  -482,  -482,   479,   480,  -482,  -482,   481,
     483,  -482,  -482,   482,  -482,   478,   408,  -482,  -482,   485,
     487,   491,   492,   278,   277,   428,   429,   430,   493,   494,
      11,  -482,  -482,    18,  -482,   427,   128,  -482,   431,   -19,
    -482,   435,    43,  -482,    32,  -482,   -33,  -482,   436,   432,
     433,   434,   437,   438,   439,   150,  -482,   498,   499,    70,
    -482,  -482,  -482,   500,   501,  -482,    26,  -482,   440,    93,
    -482,   444,   503,  -482,   504,  -482,    27,   443,   445,   446,
    -482,  -482,  -482,  -482,  -482,   447,   449,  -482,   250,  -482,
     497,  -482,   502,  -482,  -482,  -482,   253,  -482,  -482,  -482,
    -482,  -482,  -482,  -482,  -482,   450,   451,  -482,  -482,   454,
     259,  -482,   505,  -482,   457,   507,  -482,  -482,  -482,  -482,
    -482,  -482,  -482,  -482,  -482,  -482,  -482,  -482,  -482,  -482,
    -482,  -482,  -482,  -482,  -482,  -482,  -482,   100,  -482,   -11,
     507,  -482,  -482,   508,  -482,  -482,  -482,   262,  -482,  -482,
    -482,  -482,  -482,   511,   462,   512,   -11,  -482,   506,  -482,
     465,  -482,   513,  -482,  -482,   228,  -482,     7,   513,  -482,
    -482,   514,   515,   518,   269,  -482,  -482,  -482,  -482,  -482,
    -482,   519,   463,   467,   469,     7,  -482,   471,  -482,  -482,
    -482,  -482,  -482
  };

  const unsigned short int
  Dhcp4Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     1,    39,    32,    28,    27,    24,
      25,    26,    31,     3,    29,    30,    52,     5,    64,     7,
     102,     9,   210,    11,   324,    13,   344,    15,   263,    17,
     298,    19,   175,    21,   422,    23,    41,    35,     0,     0,
       0,     0,     0,   346,   265,   300,     0,     0,    43,     0,
      42,     0,     0,    36,    62,   475,   469,   471,   473,     0,
      61,     0,    54,    56,    58,    59,    60,    57,    95,     0,
       0,   363,   111,   113,     0,     0,     0,     0,   202,   255,
     290,   153,   389,   167,   186,     0,   410,   420,    88,     0,
      66,    68,    69,    70,    71,    85,    86,    73,    74,    75,
      76,    80,    81,    72,    78,    79,    87,    77,    82,    83,
      84,   104,   106,     0,     0,    97,    99,   100,   101,   393,
     236,   238,   240,   316,   234,   242,   244,     0,     0,   248,
     246,   336,   385,   233,   214,   215,   216,   228,     0,   212,
     219,   230,   231,   232,   220,   221,   224,   226,   222,   223,
     217,   218,   225,   229,   227,   332,   334,   331,   329,     0,
     326,   328,   330,   365,   367,   383,   371,   373,   377,   375,
     381,   379,   369,   362,   358,     0,   347,   348,   359,   360,
     361,   355,   350,   356,   352,   353,   354,   357,   351,   280,
     143,     0,   284,   282,   287,     0,   276,   277,     0,   266,
     267,   269,   279,   270,   271,   272,   286,   273,   274,   275,
     311,     0,   309,   310,   313,   314,     0,   301,   302,   304,
     305,   306,   307,   308,   182,   184,   179,     0,   177,   180,
     181,     0,   442,   444,     0,   447,     0,     0,   451,   455,
       0,     0,     0,   460,   467,   440,     0,   424,   426,   427,
     428,   429,   430,   431,   432,   433,   434,   435,   436,   437,
     438,   439,    40,     0,     0,    33,     0,     0,     0,     0,
       0,     0,    51,     0,    53,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    65,     0,     0,     0,
       0,   103,   395,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   211,     0,     0,
       0,   325,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   345,     0,     0,     0,     0,     0,     0,     0,
       0,   264,     0,     0,     0,   299,     0,     0,     0,     0,
     176,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   423,    44,    37,     0,
       0,     0,     0,     0,     0,    55,     0,    93,    94,     0,
       0,     0,    89,    90,    91,    92,     0,     0,     0,     0,
       0,     0,     0,   409,     0,     0,    67,     0,     0,   110,
      98,   407,   405,   406,   401,   402,   403,   404,     0,   396,
     397,   399,   400,     0,     0,     0,     0,     0,     0,     0,
     253,   254,     0,     0,     0,     0,   213,     0,     0,   327,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     349,     0,     0,   278,     0,     0,     0,   289,   268,     0,
     315,   303,     0,     0,   178,   441,     0,     0,   446,     0,
     449,   450,     0,     0,   457,   458,   459,     0,     0,   425,
       0,     0,     0,   470,   472,   474,     0,   364,     0,     0,
     204,   257,   292,     0,     0,   169,     0,     0,     0,    45,
     105,   108,   109,   107,     0,   394,     0,   237,   239,   241,
     318,   235,   243,   245,   250,   251,   252,   249,   247,   338,
       0,   333,    34,   335,   366,   368,   384,   372,   374,   378,
     376,   382,   380,   370,   281,   144,   285,   283,   288,   312,
     183,   185,   443,   445,   448,   453,   454,   452,   456,   462,
     463,   464,   465,   466,   461,   468,    38,     0,   480,     0,
     477,   479,     0,   130,   136,   138,   140,     0,     0,     0,
       0,     0,   149,   151,   129,     0,   115,   117,   118,   119,
     120,   121,   122,   123,   124,   125,   126,   127,   128,     0,
     208,     0,   205,   206,   261,     0,   258,   259,   296,     0,
     293,   294,   162,   163,   164,   165,   166,     0,   155,   157,
     158,   159,   160,   161,   391,     0,   173,     0,   170,   171,
       0,     0,     0,     0,     0,     0,     0,   188,   190,   191,
     192,   193,   194,   195,   416,   418,     0,   412,   414,   415,
       0,    47,     0,   398,   322,     0,   319,   320,   342,     0,
     339,   340,   387,     0,    63,     0,     0,   476,    96,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   112,   114,     0,   203,     0,   265,   256,     0,   300,
     291,     0,     0,   154,     0,   390,     0,   168,     0,     0,
       0,     0,     0,     0,     0,     0,   187,     0,     0,     0,
     411,   421,    49,     0,    48,   408,     0,   317,     0,   346,
     337,     0,     0,   386,     0,   478,     0,     0,     0,     0,
     142,   145,   146,   147,   148,     0,     0,   116,     0,   207,
       0,   260,     0,   295,   156,   392,     0,   172,   196,   197,
     198,   199,   200,   201,   189,     0,     0,   413,    46,     0,
       0,   321,     0,   341,     0,     0,   132,   133,   134,   135,
     131,   137,   139,   141,   150,   152,   209,   262,   297,   174,
     417,   419,    50,   323,   343,   388,   484,     0,   482,     0,
       0,   481,   496,     0,   494,   492,   488,     0,   486,   490,
     491,   489,   483,     0,     0,     0,     0,   485,     0,   493,
       0,   487,     0,   495,   500,     0,   498,     0,     0,   497,
     508,     0,     0,     0,     0,   502,   504,   505,   506,   507,
     499,     0,     0,     0,     0,     0,   501,     0,   510,   511,
     512,   503,   509
  };

  const short int
  Dhcp4Parser::yypgoto_[] =
  {
    -482,  -482,  -482,  -482,  -482,  -482,  -482,  -482,  -482,  -482,
    -482,  -482,  -482,   -36,  -482,    16,  -482,  -482,  -482,  -482,
    -482,  -482,  -482,  -482,    56,  -482,  -482,  -482,   -58,  -482,
    -482,  -482,   234,  -482,  -482,  -482,  -482,    37,   214,   -60,
     -44,   -42,  -482,  -482,   -40,  -482,  -482,    36,   215,  -482,
    -482,  -482,  -482,  -482,  -482,  -482,  -482,  -482,  -482,  -482,
    -482,    38,  -144,  -482,  -482,  -482,  -482,  -482,  -482,  -482,
    -482,  -482,  -482,   -63,  -482,  -482,  -482,  -482,  -482,  -482,
    -482,  -482,  -482,  -482,  -482,  -482,  -154,  -482,  -482,  -482,
    -482,  -482,  -482,  -482,  -482,  -482,  -159,  -482,  -482,  -482,
    -156,   174,  -482,  -482,  -482,  -482,  -482,  -482,  -482,  -164,
    -482,  -482,  -482,  -482,  -482,  -482,  -482,  -482,  -482,  -482,
    -143,  -482,  -482,  -482,  -139,   210,  -482,  -482,  -482,  -482,
    -482,  -482,  -482,  -482,  -482,  -482,  -482,  -482,  -481,  -482,
    -482,  -482,  -482,  -482,  -482,  -482,  -482,  -482,  -482,  -140,
    -482,  -482,  -482,  -141,  -482,   187,  -482,   -49,  -482,  -482,
    -482,  -482,  -482,   -47,  -482,  -482,  -482,  -482,  -482,   -51,
    -482,  -482,  -482,  -138,  -482,  -482,  -482,  -137,  -482,   188,
    -482,  -482,  -482,  -482,  -482,  -482,  -482,  -482,  -482,  -482,
    -168,  -482,  -482,  -482,  -165,   216,  -482,  -482,  -482,  -482,
    -482,  -482,  -482,  -482,  -166,  -482,  -482,  -482,  -162,  -482,
     211,   -48,  -482,  -308,  -482,  -300,  -482,  -482,  -482,  -482,
    -482,  -482,  -482,  -482,  -482,  -482,  -482,  -482,  -482,  -482,
    -482,  -482,  -482,  -482,  -482,  -482,  -482,  -482,  -482,  -482,
    -482,  -482,  -482,    44,  -482,  -482,  -482,  -482,  -482,  -482,
    -482,  -150,  -482,  -482,  -482,  -482,  -482,  -482,  -482,  -482,
      55,   180,  -482,  -482,  -482,  -482,  -482,  -482,  -482,  -482,
    -482,  -482,  -482,  -482,  -482,  -482,  -482,  -482,  -482,  -482,
    -482,  -482,  -482,  -482,  -482,  -482,  -482,  -482,  -482,  -482,
    -482,  -482,  -482,  -482,  -104,  -482,  -482,  -482,  -224,  -482,
    -482,  -239,  -482,  -482,  -482,  -482,  -482,  -482,  -250,  -482,
    -482,  -265,  -482,  -482,  -482,  -482,  -482
  };

  const short int
  Dhcp4Parser::yydefgoto_[] =
  {
      -1,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    32,    33,    34,    57,   533,    72,    73,
      35,    56,    69,    70,   510,   651,   713,   714,   108,    37,
      58,    81,    82,    83,   287,    39,    59,   109,   110,   111,
     112,   113,   114,   115,   116,   117,   295,   134,   135,    41,
      60,   136,   317,   137,   318,   513,   138,   118,   299,   119,
     300,   585,   586,   587,   669,   770,   588,   670,   589,   671,
     590,   672,   591,   217,   355,   593,   594,   595,   596,   597,
     678,   598,   679,   120,   308,   617,   618,   619,   620,   621,
     622,   623,   121,   310,   627,   628,   629,   696,    53,    66,
     247,   248,   249,   367,   250,   368,   122,   311,   636,   637,
     638,   639,   640,   641,   642,   643,   123,   305,   601,   602,
     603,   683,    43,    61,   158,   159,   160,   327,   161,   323,
     162,   324,   163,   325,   164,   328,   165,   329,   166,   333,
     167,   332,   527,   168,   169,   124,   306,   605,   606,   607,
     686,    49,    64,   218,   219,   220,   221,   222,   223,   224,
     354,   225,   358,   226,   357,   227,   228,   359,   229,   125,
     307,   609,   610,   611,   689,    51,    65,   236,   237,   238,
     239,   240,   363,   241,   242,   243,   171,   326,   655,   656,
     657,   716,    45,    62,   179,   180,   181,   338,   182,   339,
     172,   334,   659,   660,   661,   719,    47,    63,   195,   196,
     197,   126,   298,   199,   342,   200,   343,   201,   351,   202,
     345,   203,   346,   204,   348,   205,   347,   206,   350,   207,
     349,   208,   344,   174,   335,   663,   722,   127,   309,   625,
     322,   428,   429,   430,   431,   432,   514,   128,   129,   313,
     646,   647,   648,   707,   649,   708,   130,   314,    55,    67,
     266,   267,   268,   269,   372,   270,   373,   271,   272,   375,
     273,   274,   275,   378,   557,   276,   379,   277,   278,   279,
     280,   383,   564,   281,   384,    84,   289,    85,   290,    86,
     291,    87,   288,   569,   570,   571,   665,   787,   788,   789,
     797,   798,   799,   800,   805,   801,   803,   815,   816,   817,
     824,   825,   826,   831,   827,   828,   829
  };

  const unsigned short int
  Dhcp4Parser::yytable_[] =
  {
      80,   154,   233,   153,   177,   193,   216,   232,   246,   265,
     170,   178,   194,   173,   426,   198,   234,   155,   235,   156,
      68,   157,   427,   624,    25,   139,    26,    74,    27,   555,
     210,   230,   211,   212,   231,   573,    90,    91,   210,   139,
     574,   575,   576,   577,   578,   579,   580,   581,   582,   583,
     244,   245,   766,   767,   768,   769,   293,    94,    95,    96,
     210,   294,   140,   141,   142,    88,   100,   692,   244,   245,
     693,    89,    90,    91,   100,   143,    92,    93,   144,   145,
     146,   147,   148,   149,   175,   176,    91,   183,   184,   694,
     150,   151,   695,    94,    95,    96,    97,    98,   152,    24,
     315,    99,   100,   790,   150,   316,   791,    79,   792,    36,
     793,   794,    91,   183,   184,   100,   210,   612,   613,   614,
     615,    79,   616,   101,   102,   556,    38,   820,   320,    79,
     821,   822,   823,   321,    75,   336,   103,   340,   421,   104,
     337,   100,   341,    76,    77,    78,   105,   106,   369,   385,
     107,    79,   209,   370,   386,   511,   512,    79,    79,    28,
      29,    30,    31,   185,   644,   645,    79,   186,   187,   188,
     189,   190,   191,   315,   192,    40,   666,   210,   664,   211,
     212,   667,   213,   214,   215,   559,   560,   561,   562,   131,
     132,    42,    44,   133,    79,     1,     2,     3,     4,     5,
       6,     7,     8,     9,    10,    11,   320,    79,   426,   680,
     282,   668,    46,   745,   681,   563,   427,   251,   252,   253,
     254,   255,   256,   257,   258,   259,   260,   261,   262,   263,
     264,   818,    48,    79,   819,    80,   630,   631,   632,   633,
     634,   635,    50,    52,   680,   705,   709,   387,   388,   682,
     706,   710,   385,   336,    54,    71,   369,   711,   776,   423,
      79,   779,   340,   283,   422,   806,   285,   783,    79,   284,
     807,   424,   835,   286,   425,   292,   154,   836,   153,   524,
     525,   526,   177,   296,   297,   170,   301,   302,   173,   178,
     303,   304,   155,   312,   156,   193,   157,   319,   330,   331,
     352,   353,   194,   233,   216,   198,   356,   360,   232,   361,
     362,   389,   364,   365,   366,   397,   371,   234,   374,   235,
     376,   377,   380,   381,   382,   390,   391,   265,   392,   393,
     394,   396,   398,   399,   400,   401,   402,   403,   404,   405,
     406,   407,   408,   409,   410,   411,   412,   414,   413,   415,
     417,   418,   419,   433,   434,   435,   493,   494,   495,   436,
     437,   438,   439,   440,   441,   442,   443,   444,   445,   447,
     448,   450,   451,   452,   453,   454,   455,   456,   457,   458,
     459,   461,   462,   464,   465,   463,   466,   469,   467,   470,
     472,   473,   476,   477,   475,   478,   479,   480,   481,   482,
     483,   487,   488,   490,   484,   500,   485,   486,   491,   492,
     496,   498,   497,   499,   501,   502,   503,   504,   505,   730,
     731,   506,   507,   508,   509,   515,   516,   520,   517,   529,
     518,   519,   530,    26,   600,   592,   592,   551,   604,   521,
     584,   584,   608,   626,   522,   652,   523,   654,   684,   528,
     265,   658,   673,   423,   566,   531,   674,   675,   422,   676,
     677,   685,   688,   534,   532,   424,   687,   690,   425,   691,
     697,   698,   535,   537,   538,   539,   699,   700,   701,   702,
     703,   704,   724,   718,   540,   717,   721,   720,   541,   726,
     723,   727,   542,   543,   544,   728,   729,   735,   736,   545,
     546,   662,   755,   756,   759,   777,   758,   764,   536,   765,
     778,   812,   804,   784,   786,   808,   810,   558,   832,   833,
     814,   547,   834,   837,   548,   549,   568,   395,   567,   416,
     550,   552,   572,   553,   554,   420,   737,   599,   744,   747,
     746,   754,   739,   474,   738,   740,   446,   565,   741,   468,
     761,   760,   742,   743,   471,   763,   449,   762,   712,   757,
     653,   715,   725,   650,   460,   489,   802,   811,   830,   732,
     841,   734,   733,   748,   749,   750,     0,     0,   751,   752,
     753,     0,     0,   771,     0,   772,   773,   774,     0,   775,
     780,   781,     0,     0,   782,     0,     0,   785,     0,     0,
       0,     0,     0,   809,     0,   813,   838,     0,   839,     0,
     840,   842,     0,     0,     0,     0,     0,   592,     0,     0,
       0,     0,   584,   154,     0,   153,   233,     0,   216,     0,
       0,   232,   170,     0,     0,   173,     0,     0,   246,   155,
     234,   156,   235,   157,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   177,     0,
       0,   193,     0,     0,     0,   178,     0,     0,   194,     0,
       0,   198,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   796,     0,     0,     0,
       0,   795,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   796,     0,     0,     0,     0,   795
  };

  const short int
  Dhcp4Parser::yycheck_[] =
  {
      58,    61,    65,    61,    62,    63,    64,    65,    66,    67,
      61,    62,    63,    61,   322,    63,    65,    61,    65,    61,
      56,    61,   322,   504,     5,     7,     7,    10,     9,    15,
      49,    50,    51,    52,    53,    24,    18,    19,    49,     7,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      83,    84,    25,    26,    27,    28,     3,    39,    40,    41,
      49,     8,    44,    45,    46,    11,    48,     3,    83,    84,
       6,    17,    18,    19,    48,    57,    22,    23,    60,    61,
      62,    63,    64,    65,    58,    59,    19,    20,    21,     3,
      72,    73,     6,    39,    40,    41,    42,    43,    80,     0,
       3,    47,    48,     3,    72,     8,     6,   140,   119,     7,
     121,   122,    19,    20,    21,    48,    49,    74,    75,    76,
      77,   140,    79,    69,    70,   111,     7,   120,     3,   140,
     123,   124,   125,     8,   117,     3,    82,     3,    71,    85,
       8,    48,     8,   126,   127,   128,    92,    93,     3,     3,
      96,   140,    24,     8,     8,    14,    15,   140,   140,   140,
     141,   142,   143,    70,    94,    95,   140,    74,    75,    76,
      77,    78,    79,     3,    81,     7,     3,    49,     8,    51,
      52,     8,    54,    55,    56,   113,   114,   115,   116,    12,
      13,     7,     7,    16,   140,   129,   130,   131,   132,   133,
     134,   135,   136,   137,   138,   139,     3,   140,   516,     3,
       6,     8,     7,   694,     8,   143,   516,    97,    98,    99,
     100,   101,   102,   103,   104,   105,   106,   107,   108,   109,
     110,     3,     7,   140,     6,   293,    86,    87,    88,    89,
      90,    91,     7,     7,     3,     3,     3,   283,   284,     8,
       8,     8,     3,     3,     7,   140,     3,     8,     8,   322,
     140,     8,     3,     3,   322,     3,     8,     8,   140,     4,
       8,   322,     3,     3,   322,     4,   336,     8,   336,    66,
      67,    68,   340,     4,     4,   336,     4,     4,   336,   340,
       4,     4,   336,     4,   336,   353,   336,     4,     4,     4,
       8,     3,   353,   366,   362,   353,     4,     4,   366,     8,
       3,   140,     4,     8,     3,   143,     4,   366,     4,   366,
       4,     4,     4,     4,     4,     4,     4,   385,     4,     4,
       4,     4,   143,     4,     4,     4,   141,   141,   141,   141,
       4,     4,     4,     4,     4,     4,     4,     4,   141,     4,
       4,     4,   143,     4,     4,     4,   392,   393,   394,     4,
       4,     4,     4,   141,   143,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,   141,     4,     4,   143,   143,
       4,     4,     4,     4,   143,   141,     4,   141,   141,     4,
       4,     4,     4,     4,   143,     5,   143,   143,     7,     7,
       7,     7,   140,     7,     5,     5,     5,     5,     5,   141,
     143,     7,     7,     7,     5,     8,     3,     5,   140,     5,
     140,   140,     7,     7,     7,   498,   499,   473,     7,   140,
     498,   499,     7,     7,   140,     4,   140,     7,     6,   140,
     508,     7,     4,   516,   490,   140,     4,     4,   516,     4,
       4,     3,     3,   140,   448,   516,     6,     6,   516,     3,
       6,     3,   140,   140,   140,   140,     4,     4,     4,     4,
       4,     4,     4,     3,   140,     6,     3,     6,   140,     4,
       8,     4,   140,   140,   140,     4,     4,     4,     4,   140,
     140,    81,     4,     4,     3,     8,     6,     4,   452,     5,
       8,     5,     4,     8,     7,     4,     4,   112,     4,     4,
       7,   140,     4,     4,   140,   140,   118,   293,   491,   315,
     140,   140,   496,   140,   140,   320,   680,   499,   692,   698,
     696,   705,   685,   369,   683,   686,   336,   140,   688,   362,
     718,   716,   689,   691,   366,   721,   340,   719,   140,   709,
     516,   140,   666,   508,   353,   385,   790,   806,   818,   141,
     835,   141,   143,   141,   141,   141,    -1,    -1,   141,   141,
     141,    -1,    -1,   140,    -1,   140,   140,   140,    -1,   140,
     140,   140,    -1,    -1,   140,    -1,    -1,   140,    -1,    -1,
      -1,    -1,    -1,   141,    -1,   140,   143,    -1,   141,    -1,
     141,   140,    -1,    -1,    -1,    -1,    -1,   680,    -1,    -1,
      -1,    -1,   680,   683,    -1,   683,   689,    -1,   686,    -1,
      -1,   689,   683,    -1,    -1,   683,    -1,    -1,   696,   683,
     689,   683,   689,   683,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   716,    -1,
      -1,   719,    -1,    -1,    -1,   716,    -1,    -1,   719,    -1,
      -1,   719,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   789,    -1,    -1,    -1,
      -1,   789,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   806,    -1,    -1,    -1,    -1,   806
  };

  const unsigned short int
  Dhcp4Parser::yystos_[] =
  {
       0,   129,   130,   131,   132,   133,   134,   135,   136,   137,
     138,   139,   145,   146,   147,   148,   149,   150,   151,   152,
     153,   154,   155,   156,     0,     5,     7,     9,   140,   141,
     142,   143,   157,   158,   159,   164,     7,   173,     7,   179,
       7,   193,     7,   266,     7,   336,     7,   350,     7,   295,
       7,   319,     7,   242,     7,   402,   165,   160,   174,   180,
     194,   267,   337,   351,   296,   320,   243,   403,   157,   166,
     167,   140,   162,   163,    10,   117,   126,   127,   128,   140,
     172,   175,   176,   177,   429,   431,   433,   435,    11,    17,
      18,    19,    22,    23,    39,    40,    41,    42,    43,    47,
      48,    69,    70,    82,    85,    92,    93,    96,   172,   181,
     182,   183,   184,   185,   186,   187,   188,   189,   201,   203,
     227,   236,   250,   260,   289,   313,   355,   381,   391,   392,
     400,    12,    13,    16,   191,   192,   195,   197,   200,     7,
      44,    45,    46,    57,    60,    61,    62,    63,    64,    65,
      72,    73,    80,   172,   183,   184,   185,   188,   268,   269,
     270,   272,   274,   276,   278,   280,   282,   284,   287,   288,
     313,   330,   344,   355,   377,    58,    59,   172,   313,   338,
     339,   340,   342,    20,    21,    70,    74,    75,    76,    77,
      78,    79,    81,   172,   313,   352,   353,   354,   355,   357,
     359,   361,   363,   365,   367,   369,   371,   373,   375,    24,
      49,    51,    52,    54,    55,    56,   172,   217,   297,   298,
     299,   300,   301,   302,   303,   305,   307,   309,   310,   312,
      50,    53,   172,   217,   301,   307,   321,   322,   323,   324,
     325,   327,   328,   329,    83,    84,   172,   244,   245,   246,
     248,    97,    98,    99,   100,   101,   102,   103,   104,   105,
     106,   107,   108,   109,   110,   172,   404,   405,   406,   407,
     409,   411,   412,   414,   415,   416,   419,   421,   422,   423,
     424,   427,     6,     3,     4,     8,     3,   178,   436,   430,
     432,   434,     4,     3,     8,   190,     4,     4,   356,   202,
     204,     4,     4,     4,     4,   261,   290,   314,   228,   382,
     237,   251,     4,   393,   401,     3,     8,   196,   198,     4,
       3,     8,   384,   273,   275,   277,   331,   271,   279,   281,
       4,     4,   285,   283,   345,   378,     3,     8,   341,   343,
       3,     8,   358,   360,   376,   364,   366,   370,   368,   374,
     372,   362,     8,     3,   304,   218,     4,   308,   306,   311,
       4,     8,     3,   326,     4,     8,     3,   247,   249,     3,
       8,     4,   408,   410,     4,   413,     4,     4,   417,   420,
       4,     4,     4,   425,   428,     3,     8,   157,   157,   140,
       4,     4,     4,     4,     4,   176,     4,   143,   143,     4,
       4,     4,   141,   141,   141,   141,     4,     4,     4,     4,
       4,     4,     4,   141,     4,     4,   182,     4,     4,   143,
     192,    71,   172,   217,   313,   355,   357,   359,   385,   386,
     387,   388,   389,     4,     4,     4,     4,     4,     4,     4,
     141,   143,     4,     4,     4,     4,   269,     4,     4,   339,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
     354,     4,     4,   141,     4,     4,     4,   143,   299,     4,
     143,   323,     4,     4,   245,   143,     4,     4,   141,     4,
     141,   141,     4,     4,   143,   143,   143,     4,     4,   405,
       4,     7,     7,   157,   157,   157,     7,   140,     7,     7,
       5,     5,     5,     5,     5,     5,     7,     7,     7,     5,
     168,    14,    15,   199,   390,     8,     3,   140,   140,   140,
       5,   140,   140,   140,    66,    67,    68,   286,   140,     5,
       7,   140,   159,   161,   140,   140,   168,   140,   140,   140,
     140,   140,   140,   140,   140,   140,   140,   140,   140,   140,
     140,   157,   140,   140,   140,    15,   111,   418,   112,   113,
     114,   115,   116,   143,   426,   140,   157,   181,   118,   437,
     438,   439,   191,    24,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,   172,   205,   206,   207,   210,   212,
     214,   216,   217,   219,   220,   221,   222,   223,   225,   205,
       7,   262,   263,   264,     7,   291,   292,   293,     7,   315,
     316,   317,    74,    75,    76,    77,    79,   229,   230,   231,
     232,   233,   234,   235,   282,   383,     7,   238,   239,   240,
      86,    87,    88,    89,    90,    91,   252,   253,   254,   255,
     256,   257,   258,   259,    94,    95,   394,   395,   396,   398,
     404,   169,     4,   387,     7,   332,   333,   334,     7,   346,
     347,   348,    81,   379,     8,   440,     3,     8,     8,   208,
     211,   213,   215,     4,     4,     4,     4,     4,   224,   226,
       3,     8,     8,   265,     6,     3,   294,     6,     3,   318,
       6,     3,     3,     6,     3,     6,   241,     6,     3,     4,
       4,     4,     4,     4,     4,     3,     8,   397,   399,     3,
       8,     8,   140,   170,   171,   140,   335,     6,     3,   349,
       6,     3,   380,     8,     4,   438,     4,     4,     4,     4,
     141,   143,   141,   143,   141,     4,     4,   206,   268,   264,
     297,   293,   321,   317,   230,   282,   244,   240,   141,   141,
     141,   141,   141,   141,   253,     4,     4,   395,     6,     3,
     338,   334,   352,   348,     4,     5,    25,    26,    27,    28,
     209,   140,   140,   140,   140,   140,     8,     8,     8,     8,
     140,   140,   140,     8,     8,   140,     7,   441,   442,   443,
       3,     6,   119,   121,   122,   172,   217,   444,   445,   446,
     447,   449,   442,   450,     4,   448,     3,     8,     4,   141,
       4,   445,     5,   140,     7,   451,   452,   453,     3,     6,
     120,   123,   124,   125,   454,   455,   456,   458,   459,   460,
     452,   457,     4,     4,     4,     3,     8,     4,   143,   141,
     141,   455,   140
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
     176,   176,   178,   177,   180,   179,   181,   181,   182,   182,
     182,   182,   182,   182,   182,   182,   182,   182,   182,   182,
     182,   182,   182,   182,   182,   182,   182,   182,   182,   183,
     184,   185,   186,   187,   188,   190,   189,   191,   191,   192,
     192,   192,   194,   193,   196,   195,   198,   197,   199,   199,
     200,   202,   201,   204,   203,   205,   205,   206,   206,   206,
     206,   206,   206,   206,   206,   206,   206,   206,   206,   206,
     208,   207,   209,   209,   209,   209,   211,   210,   213,   212,
     215,   214,   216,   218,   217,   219,   220,   221,   222,   224,
     223,   226,   225,   228,   227,   229,   229,   230,   230,   230,
     230,   230,   231,   232,   233,   234,   235,   237,   236,   238,
     238,   239,   239,   241,   240,   243,   242,   244,   244,   244,
     245,   245,   247,   246,   249,   248,   251,   250,   252,   252,
     253,   253,   253,   253,   253,   253,   254,   255,   256,   257,
     258,   259,   261,   260,   262,   262,   263,   263,   265,   264,
     267,   266,   268,   268,   269,   269,   269,   269,   269,   269,
     269,   269,   269,   269,   269,   269,   269,   269,   269,   269,
     269,   269,   269,   269,   271,   270,   273,   272,   275,   274,
     277,   276,   279,   278,   281,   280,   283,   282,   285,   284,
     286,   286,   286,   287,   288,   290,   289,   291,   291,   292,
     292,   294,   293,   296,   295,   297,   297,   298,   298,   299,
     299,   299,   299,   299,   299,   299,   299,   300,   301,   302,
     304,   303,   306,   305,   308,   307,   309,   311,   310,   312,
     314,   313,   315,   315,   316,   316,   318,   317,   320,   319,
     321,   321,   322,   322,   323,   323,   323,   323,   323,   323,
     324,   326,   325,   327,   328,   329,   331,   330,   332,   332,
     333,   333,   335,   334,   337,   336,   338,   338,   339,   339,
     339,   339,   341,   340,   343,   342,   345,   344,   346,   346,
     347,   347,   349,   348,   351,   350,   352,   352,   353,   353,
     354,   354,   354,   354,   354,   354,   354,   354,   354,   354,
     354,   354,   354,   356,   355,   358,   357,   360,   359,   362,
     361,   364,   363,   366,   365,   368,   367,   370,   369,   372,
     371,   374,   373,   376,   375,   378,   377,   380,   379,   382,
     381,   383,   383,   384,   282,   385,   385,   386,   386,   387,
     387,   387,   387,   387,   387,   387,   388,   390,   389,   391,
     393,   392,   394,   394,   395,   395,   397,   396,   399,   398,
     401,   400,   403,   402,   404,   404,   405,   405,   405,   405,
     405,   405,   405,   405,   405,   405,   405,   405,   405,   405,
     405,   406,   408,   407,   410,   409,   411,   413,   412,   414,
     415,   417,   416,   418,   418,   420,   419,   421,   422,   423,
     425,   424,   426,   426,   426,   426,   426,   428,   427,   430,
     429,   432,   431,   434,   433,   436,   435,   437,   437,   438,
     440,   439,   441,   441,   443,   442,   444,   444,   445,   445,
     445,   445,   445,   446,   448,   447,   450,   449,   451,   451,
     453,   452,   454,   454,   455,   455,   455,   455,   457,   456,
     458,   459,   460
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
       1,     1,     0,     6,     0,     4,     1,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     3,
       3,     3,     3,     3,     3,     0,     6,     1,     3,     1,
       1,     1,     0,     4,     0,     4,     0,     4,     1,     1,
       3,     0,     6,     0,     6,     1,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       0,     4,     1,     1,     1,     1,     0,     4,     0,     4,
       0,     4,     3,     0,     4,     3,     3,     3,     3,     0,
       4,     0,     4,     0,     6,     1,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     0,     6,     0,
       1,     1,     3,     0,     4,     0,     4,     1,     3,     1,
       1,     1,     0,     4,     0,     4,     0,     6,     1,     3,
       1,     1,     1,     1,     1,     1,     3,     3,     3,     3,
       3,     3,     0,     6,     0,     1,     1,     3,     0,     4,
       0,     4,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     0,     4,     0,     4,     0,     4,
       0,     4,     0,     4,     0,     4,     0,     4,     0,     4,
       1,     1,     1,     3,     3,     0,     6,     0,     1,     1,
       3,     0,     4,     0,     4,     0,     1,     1,     3,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     3,     1,
       0,     4,     0,     4,     0,     4,     1,     0,     4,     3,
       0,     6,     0,     1,     1,     3,     0,     4,     0,     4,
       0,     1,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     0,     4,     1,     1,     3,     0,     6,     0,     1,
       1,     3,     0,     4,     0,     4,     1,     3,     1,     1,
       1,     1,     0,     4,     0,     4,     0,     6,     0,     1,
       1,     3,     0,     4,     0,     4,     0,     1,     1,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     0,     4,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     6,     0,     4,     0,
       6,     1,     3,     0,     4,     0,     1,     1,     3,     1,
       1,     1,     1,     1,     1,     1,     1,     0,     4,     3,
       0,     6,     1,     3,     1,     1,     0,     4,     0,     4,
       0,     6,     0,     4,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     3,     0,     4,     0,     4,     3,     0,     4,     3,
       3,     0,     4,     1,     1,     0,     4,     3,     3,     3,
       0,     4,     1,     1,     1,     1,     1,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     6,     1,     3,     1,
       0,     6,     1,     3,     0,     4,     1,     3,     1,     1,
       1,     1,     1,     3,     0,     4,     0,     6,     1,     3,
       0,     4,     1,     3,     1,     1,     1,     1,     0,     4,
       3,     3,     3
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
  "\"maxver\"", "\"Dhcp6\"", "\"DhcpDdns\"", "\"Control-agent\"",
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
  "$@20", "dhcp_socket_type", "$@21", "socket_type", "re_detect",
  "lease_database", "$@22", "hosts_database", "$@23",
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
  "dhcpddns_json_object", "$@97", "control_agent_json_object", "$@98",
  "logging_object", "$@99", "logging_params", "logging_param", "loggers",
  "$@100", "loggers_entries", "logger_entry", "$@101", "logger_params",
  "logger_param", "debuglevel", "severity", "$@102", "output_options_list",
  "$@103", "output_options_list_content", "output_entry", "$@104",
  "output_params_list", "output_params", "output", "$@105", "flush",
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
     323,   334,   344,   344,   357,   358,   362,   363,   364,   365,
     366,   367,   370,   370,   387,   387,   395,   396,   401,   402,
     403,   404,   405,   406,   407,   408,   409,   410,   411,   412,
     413,   414,   415,   416,   417,   418,   419,   420,   421,   424,
     429,   434,   439,   444,   449,   455,   455,   465,   466,   469,
     470,   471,   474,   474,   482,   482,   492,   492,   499,   500,
     503,   509,   509,   519,   519,   529,   530,   533,   534,   535,
     536,   537,   538,   539,   540,   541,   542,   543,   544,   545,
     548,   548,   555,   556,   557,   558,   561,   561,   569,   569,
     577,   577,   585,   590,   590,   598,   603,   608,   613,   618,
     618,   626,   626,   635,   635,   645,   646,   649,   650,   651,
     652,   653,   656,   661,   666,   671,   676,   681,   681,   691,
     692,   695,   696,   699,   699,   707,   707,   715,   716,   717,
     720,   721,   724,   724,   732,   732,   740,   740,   750,   751,
     754,   755,   756,   757,   758,   759,   762,   767,   772,   777,
     782,   787,   795,   795,   808,   809,   812,   813,   820,   820,
     843,   843,   852,   853,   857,   858,   859,   860,   861,   862,
     863,   864,   865,   866,   867,   868,   869,   870,   871,   872,
     873,   874,   875,   876,   879,   879,   887,   887,   895,   895,
     903,   903,   911,   911,   919,   919,   927,   927,   935,   935,
     942,   943,   944,   947,   952,   961,   961,   973,   974,   977,
     978,   983,   983,   994,   994,  1004,  1005,  1008,  1009,  1012,
    1013,  1014,  1015,  1016,  1017,  1018,  1019,  1022,  1024,  1029,
    1031,  1031,  1039,  1039,  1047,  1047,  1055,  1057,  1057,  1065,
    1074,  1074,  1086,  1087,  1092,  1093,  1098,  1098,  1109,  1109,
    1120,  1121,  1126,  1127,  1132,  1133,  1134,  1135,  1136,  1137,
    1140,  1142,  1142,  1150,  1152,  1154,  1162,  1162,  1174,  1175,
    1178,  1179,  1182,  1182,  1190,  1190,  1198,  1199,  1202,  1203,
    1204,  1205,  1208,  1208,  1216,  1216,  1226,  1226,  1236,  1237,
    1240,  1241,  1244,  1244,  1252,  1252,  1260,  1261,  1264,  1265,
    1269,  1270,  1271,  1272,  1273,  1274,  1275,  1276,  1277,  1278,
    1279,  1280,  1281,  1284,  1284,  1292,  1292,  1300,  1300,  1308,
    1308,  1316,  1316,  1324,  1324,  1332,  1332,  1340,  1340,  1348,
    1348,  1356,  1356,  1364,  1364,  1377,  1377,  1387,  1387,  1398,
    1398,  1408,  1409,  1412,  1412,  1420,  1421,  1424,  1425,  1428,
    1429,  1430,  1431,  1432,  1433,  1434,  1437,  1439,  1439,  1451,
    1458,  1458,  1468,  1469,  1472,  1473,  1476,  1476,  1484,  1484,
    1494,  1494,  1504,  1504,  1512,  1513,  1516,  1517,  1518,  1519,
    1520,  1521,  1522,  1523,  1524,  1525,  1526,  1527,  1528,  1529,
    1530,  1533,  1538,  1538,  1546,  1546,  1554,  1559,  1559,  1567,
    1572,  1577,  1577,  1585,  1586,  1589,  1589,  1597,  1602,  1607,
    1612,  1612,  1620,  1623,  1626,  1629,  1632,  1638,  1638,  1648,
    1648,  1655,  1655,  1662,  1662,  1674,  1674,  1687,  1688,  1692,
    1696,  1696,  1708,  1709,  1713,  1713,  1721,  1722,  1725,  1726,
    1727,  1728,  1729,  1732,  1737,  1737,  1745,  1745,  1755,  1756,
    1759,  1759,  1767,  1768,  1771,  1772,  1773,  1774,  1777,  1777,
    1785,  1790,  1795
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
#line 4175 "dhcp4_parser.cc" // lalr1.cc:1167
#line 1800 "dhcp4_parser.yy" // lalr1.cc:1168


void
isc::dhcp::Dhcp4Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
