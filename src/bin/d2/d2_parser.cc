// A Bison parser, made by GNU Bison 3.0.5.

// Skeleton implementation for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015, 2018 Free Software Foundation, Inc.

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
#define yylex   d2_parser_lex

// First part of user declarations.

#line 39 "d2_parser.cc" // lalr1.cc:406

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

#include "d2_parser.h"

// User implementation prologue.

#line 53 "d2_parser.cc" // lalr1.cc:414
// Unqualified %code blocks.
#line 34 "d2_parser.yy" // lalr1.cc:415

#include <d2/parser_context.h>

#line 59 "d2_parser.cc" // lalr1.cc:415


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
#if D2_PARSER_DEBUG

// A pseudo ostream that takes yydebug_ into account.
# define YYCDEBUG if (yydebug_) (*yycdebug_)

# define YY_SYMBOL_PRINT(Title, Symbol)         \
  do {                                          \
    if (yydebug_)                               \
    {                                           \
      *yycdebug_ << Title << ' ';               \
      yy_print_ (*yycdebug_, Symbol);           \
      *yycdebug_ << '\n';                       \
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

#else // !D2_PARSER_DEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YYUSE (Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void> (0)
# define YY_STACK_PRINT()                static_cast<void> (0)

#endif // !D2_PARSER_DEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)

#line 14 "d2_parser.yy" // lalr1.cc:481
namespace isc { namespace d2 {
#line 145 "d2_parser.cc" // lalr1.cc:481

  /* Return YYSTR after stripping away unnecessary quotes and
     backslashes, so that it's suitable for yyerror.  The heuristic is
     that double-quoting is unnecessary unless the string contains an
     apostrophe, a comma, or backslash (other than backslash-backslash).
     YYSTR is taken from yytname.  */
  std::string
  D2Parser::yytnamerr_ (const char *yystr)
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
  D2Parser::D2Parser (isc::d2::D2ParserContext& ctx_yyarg)
    :
#if D2_PARSER_DEBUG
      yydebug_ (false),
      yycdebug_ (&std::cerr),
#endif
      ctx (ctx_yyarg)
  {}

  D2Parser::~D2Parser ()
  {}


  /*---------------.
  | Symbol types.  |
  `---------------*/



  // by_state.
  D2Parser::by_state::by_state ()
    : state (empty_state)
  {}

  D2Parser::by_state::by_state (const by_state& other)
    : state (other.state)
  {}

  void
  D2Parser::by_state::clear ()
  {
    state = empty_state;
  }

  void
  D2Parser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  D2Parser::by_state::by_state (state_type s)
    : state (s)
  {}

  D2Parser::symbol_number_type
  D2Parser::by_state::type_get () const
  {
    if (state == empty_state)
      return empty_symbol;
    else
      return yystos_[state];
  }

  D2Parser::stack_symbol_type::stack_symbol_type ()
  {}

  D2Parser::stack_symbol_type::stack_symbol_type (const stack_symbol_type& that)
    : super_type (that.state, that.location)
  {
    switch (that.type_get ())
    {
      case 68: // value
      case 72: // map_value
      case 96: // ncr_protocol_value
        value.copy< ElementPtr > (that.value);
        break;

      case 56: // "boolean"
        value.copy< bool > (that.value);
        break;

      case 55: // "floating point"
        value.copy< double > (that.value);
        break;

      case 54: // "integer"
        value.copy< int64_t > (that.value);
        break;

      case 53: // "constant string"
        value.copy< std::string > (that.value);
        break;

      default:
        break;
    }

  }

  D2Parser::stack_symbol_type::stack_symbol_type (state_type s, symbol_type& that)
    : super_type (s, that.location)
  {
    switch (that.type_get ())
    {
      case 68: // value
      case 72: // map_value
      case 96: // ncr_protocol_value
        value.move< ElementPtr > (that.value);
        break;

      case 56: // "boolean"
        value.move< bool > (that.value);
        break;

      case 55: // "floating point"
        value.move< double > (that.value);
        break;

      case 54: // "integer"
        value.move< int64_t > (that.value);
        break;

      case 53: // "constant string"
        value.move< std::string > (that.value);
        break;

      default:
        break;
    }

    // that is emptied.
    that.type = empty_symbol;
  }

  D2Parser::stack_symbol_type&
  D2Parser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
    switch (that.type_get ())
    {
      case 68: // value
      case 72: // map_value
      case 96: // ncr_protocol_value
        value.copy< ElementPtr > (that.value);
        break;

      case 56: // "boolean"
        value.copy< bool > (that.value);
        break;

      case 55: // "floating point"
        value.copy< double > (that.value);
        break;

      case 54: // "integer"
        value.copy< int64_t > (that.value);
        break;

      case 53: // "constant string"
        value.copy< std::string > (that.value);
        break;

      default:
        break;
    }

    location = that.location;
    return *this;
  }


  template <typename Base>
  void
  D2Parser::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);
  }

#if D2_PARSER_DEBUG
  template <typename Base>
  void
  D2Parser::yy_print_ (std::ostream& yyo,
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
            case 53: // "constant string"

#line 111 "d2_parser.yy" // lalr1.cc:635
        { yyoutput << yysym.value.template as< std::string > (); }
#line 378 "d2_parser.cc" // lalr1.cc:635
        break;

      case 54: // "integer"

#line 111 "d2_parser.yy" // lalr1.cc:635
        { yyoutput << yysym.value.template as< int64_t > (); }
#line 385 "d2_parser.cc" // lalr1.cc:635
        break;

      case 55: // "floating point"

#line 111 "d2_parser.yy" // lalr1.cc:635
        { yyoutput << yysym.value.template as< double > (); }
#line 392 "d2_parser.cc" // lalr1.cc:635
        break;

      case 56: // "boolean"

#line 111 "d2_parser.yy" // lalr1.cc:635
        { yyoutput << yysym.value.template as< bool > (); }
#line 399 "d2_parser.cc" // lalr1.cc:635
        break;

      case 68: // value

#line 111 "d2_parser.yy" // lalr1.cc:635
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 406 "d2_parser.cc" // lalr1.cc:635
        break;

      case 72: // map_value

#line 111 "d2_parser.yy" // lalr1.cc:635
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 413 "d2_parser.cc" // lalr1.cc:635
        break;

      case 96: // ncr_protocol_value

#line 111 "d2_parser.yy" // lalr1.cc:635
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 420 "d2_parser.cc" // lalr1.cc:635
        break;


      default:
        break;
    }
    yyo << ')';
  }
#endif

  void
  D2Parser::yypush_ (const char* m, state_type s, symbol_type& sym)
  {
    stack_symbol_type t (s, sym);
    yypush_ (m, t);
  }

  void
  D2Parser::yypush_ (const char* m, stack_symbol_type& s)
  {
    if (m)
      YY_SYMBOL_PRINT (m, s);
    yystack_.push (s);
  }

  void
  D2Parser::yypop_ (unsigned n)
  {
    yystack_.pop (n);
  }

#if D2_PARSER_DEBUG
  std::ostream&
  D2Parser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  D2Parser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  D2Parser::debug_level_type
  D2Parser::debug_level () const
  {
    return yydebug_;
  }

  void
  D2Parser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // D2_PARSER_DEBUG

  D2Parser::state_type
  D2Parser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - yyntokens_] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - yyntokens_];
  }

  bool
  D2Parser::yy_pact_value_is_default_ (int yyvalue)
  {
    return yyvalue == yypact_ninf_;
  }

  bool
  D2Parser::yy_table_value_is_error_ (int yyvalue)
  {
    return yyvalue == yytable_ninf_;
  }

  int
  D2Parser::parse ()
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
    YYCDEBUG << "Starting parse\n";


    /* Initialize the stack.  The initial state will be set in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystack_.clear ();
    yypush_ (YY_NULLPTR, 0, yyla);

    // A new symbol was pushed on the stack.
  yynewstate:
    YYCDEBUG << "Entering state " << yystack_[0].state << '\n';

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
      yylhs.state = yy_lr_goto_state_ (yystack_[yylen].state, yyr1_[yyn]);
      /* Variants are always initialized to an empty instance of the
         correct type. The default '$$ = $1' action is NOT applied
         when using variants.  */
      switch (yyr1_[yyn])
    {
      case 68: // value
      case 72: // map_value
      case 96: // ncr_protocol_value
        yylhs.value.build< ElementPtr > ();
        break;

      case 56: // "boolean"
        yylhs.value.build< bool > ();
        break;

      case 55: // "floating point"
        yylhs.value.build< double > ();
        break;

      case 54: // "integer"
        yylhs.value.build< int64_t > ();
        break;

      case 53: // "constant string"
        yylhs.value.build< std::string > ();
        break;

      default:
        break;
    }


      // Default location.
      {
        slice<stack_symbol_type, stack_type> slice (yystack_, yylen);
        YYLLOC_DEFAULT (yylhs.location, slice, yylen);
        yyerror_range[1].location = yylhs.location;
      }

      // Perform the reduction.
      YY_REDUCE_PRINT (yyn);
      try
        {
          switch (yyn)
            {
  case 2:
#line 120 "d2_parser.yy" // lalr1.cc:856
    { ctx.ctx_ = ctx.NO_KEYWORD; }
#line 660 "d2_parser.cc" // lalr1.cc:856
    break;

  case 4:
#line 121 "d2_parser.yy" // lalr1.cc:856
    { ctx.ctx_ = ctx.CONFIG; }
#line 666 "d2_parser.cc" // lalr1.cc:856
    break;

  case 6:
#line 122 "d2_parser.yy" // lalr1.cc:856
    { ctx.ctx_ = ctx.DHCPDDNS; }
#line 672 "d2_parser.cc" // lalr1.cc:856
    break;

  case 8:
#line 123 "d2_parser.yy" // lalr1.cc:856
    { ctx.ctx_ = ctx.TSIG_KEY; }
#line 678 "d2_parser.cc" // lalr1.cc:856
    break;

  case 10:
#line 124 "d2_parser.yy" // lalr1.cc:856
    { ctx.ctx_ = ctx.TSIG_KEYS; }
#line 684 "d2_parser.cc" // lalr1.cc:856
    break;

  case 12:
#line 125 "d2_parser.yy" // lalr1.cc:856
    { ctx.ctx_ = ctx.DDNS_DOMAIN; }
#line 690 "d2_parser.cc" // lalr1.cc:856
    break;

  case 14:
#line 126 "d2_parser.yy" // lalr1.cc:856
    { ctx.ctx_ = ctx.DDNS_DOMAINS; }
#line 696 "d2_parser.cc" // lalr1.cc:856
    break;

  case 16:
#line 127 "d2_parser.yy" // lalr1.cc:856
    { ctx.ctx_ = ctx.DNS_SERVERS; }
#line 702 "d2_parser.cc" // lalr1.cc:856
    break;

  case 18:
#line 128 "d2_parser.yy" // lalr1.cc:856
    { ctx.ctx_ = ctx.DNS_SERVERS; }
#line 708 "d2_parser.cc" // lalr1.cc:856
    break;

  case 20:
#line 136 "d2_parser.yy" // lalr1.cc:856
    { yylhs.value.as< ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 714 "d2_parser.cc" // lalr1.cc:856
    break;

  case 21:
#line 137 "d2_parser.yy" // lalr1.cc:856
    { yylhs.value.as< ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as< double > (), ctx.loc2pos(yystack_[0].location))); }
#line 720 "d2_parser.cc" // lalr1.cc:856
    break;

  case 22:
#line 138 "d2_parser.yy" // lalr1.cc:856
    { yylhs.value.as< ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 726 "d2_parser.cc" // lalr1.cc:856
    break;

  case 23:
#line 139 "d2_parser.yy" // lalr1.cc:856
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 732 "d2_parser.cc" // lalr1.cc:856
    break;

  case 24:
#line 140 "d2_parser.yy" // lalr1.cc:856
    { yylhs.value.as< ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 738 "d2_parser.cc" // lalr1.cc:856
    break;

  case 25:
#line 141 "d2_parser.yy" // lalr1.cc:856
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 744 "d2_parser.cc" // lalr1.cc:856
    break;

  case 26:
#line 142 "d2_parser.yy" // lalr1.cc:856
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 750 "d2_parser.cc" // lalr1.cc:856
    break;

  case 27:
#line 145 "d2_parser.yy" // lalr1.cc:856
    {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as< ElementPtr > ());
}
#line 759 "d2_parser.cc" // lalr1.cc:856
    break;

  case 28:
#line 150 "d2_parser.yy" // lalr1.cc:856
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 770 "d2_parser.cc" // lalr1.cc:856
    break;

  case 29:
#line 155 "d2_parser.yy" // lalr1.cc:856
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 780 "d2_parser.cc" // lalr1.cc:856
    break;

  case 30:
#line 161 "d2_parser.yy" // lalr1.cc:856
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 786 "d2_parser.cc" // lalr1.cc:856
    break;

  case 33:
#line 168 "d2_parser.yy" // lalr1.cc:856
    {
                  // map containing a single entry
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 795 "d2_parser.cc" // lalr1.cc:856
    break;

  case 34:
#line 172 "d2_parser.yy" // lalr1.cc:856
    {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 805 "d2_parser.cc" // lalr1.cc:856
    break;

  case 35:
#line 179 "d2_parser.yy" // lalr1.cc:856
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 814 "d2_parser.cc" // lalr1.cc:856
    break;

  case 36:
#line 182 "d2_parser.yy" // lalr1.cc:856
    {
    // list parsing complete. Put any sanity checking here
}
#line 822 "d2_parser.cc" // lalr1.cc:856
    break;

  case 39:
#line 190 "d2_parser.yy" // lalr1.cc:856
    {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 831 "d2_parser.cc" // lalr1.cc:856
    break;

  case 40:
#line 194 "d2_parser.yy" // lalr1.cc:856
    {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 840 "d2_parser.cc" // lalr1.cc:856
    break;

  case 41:
#line 205 "d2_parser.yy" // lalr1.cc:856
    {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as< std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 851 "d2_parser.cc" // lalr1.cc:856
    break;

  case 42:
#line 215 "d2_parser.yy" // lalr1.cc:856
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 862 "d2_parser.cc" // lalr1.cc:856
    break;

  case 43:
#line 220 "d2_parser.yy" // lalr1.cc:856
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 872 "d2_parser.cc" // lalr1.cc:856
    break;

  case 52:
#line 242 "d2_parser.yy" // lalr1.cc:856
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("DhcpDdns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCPDDNS);
}
#line 883 "d2_parser.cc" // lalr1.cc:856
    break;

  case 53:
#line 247 "d2_parser.yy" // lalr1.cc:856
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 892 "d2_parser.cc" // lalr1.cc:856
    break;

  case 54:
#line 252 "d2_parser.yy" // lalr1.cc:856
    {
    // Parse the dhcpddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 902 "d2_parser.cc" // lalr1.cc:856
    break;

  case 55:
#line 256 "d2_parser.yy" // lalr1.cc:856
    {
    // parsing completed
}
#line 910 "d2_parser.cc" // lalr1.cc:856
    break;

  case 69:
#line 278 "d2_parser.yy" // lalr1.cc:856
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 918 "d2_parser.cc" // lalr1.cc:856
    break;

  case 70:
#line 280 "d2_parser.yy" // lalr1.cc:856
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", s);
    ctx.leave();
}
#line 928 "d2_parser.cc" // lalr1.cc:856
    break;

  case 71:
#line 286 "d2_parser.yy" // lalr1.cc:856
    {
    if (yystack_[0].value.as< int64_t > () <= 0 || yystack_[0].value.as< int64_t > () >= 65536 ) {
        error(yystack_[0].location, "port must be greater than zero but less than 65536");
    }
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", i);
}
#line 940 "d2_parser.cc" // lalr1.cc:856
    break;

  case 72:
#line 294 "d2_parser.yy" // lalr1.cc:856
    {
    if (yystack_[0].value.as< int64_t > () <= 0) {
        error(yystack_[0].location, "dns-server-timeout must be greater than zero");
    } else {
        ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
        ctx.stack_.back()->set("dns-server-timeout", i);
    }
}
#line 953 "d2_parser.cc" // lalr1.cc:856
    break;

  case 73:
#line 303 "d2_parser.yy" // lalr1.cc:856
    {
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 961 "d2_parser.cc" // lalr1.cc:856
    break;

  case 74:
#line 305 "d2_parser.yy" // lalr1.cc:856
    {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 970 "d2_parser.cc" // lalr1.cc:856
    break;

  case 75:
#line 311 "d2_parser.yy" // lalr1.cc:856
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 976 "d2_parser.cc" // lalr1.cc:856
    break;

  case 76:
#line 312 "d2_parser.yy" // lalr1.cc:856
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 982 "d2_parser.cc" // lalr1.cc:856
    break;

  case 77:
#line 315 "d2_parser.yy" // lalr1.cc:856
    {
    ctx.enter(ctx.NCR_FORMAT);
}
#line 990 "d2_parser.cc" // lalr1.cc:856
    break;

  case 78:
#line 317 "d2_parser.yy" // lalr1.cc:856
    {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 1000 "d2_parser.cc" // lalr1.cc:856
    break;

  case 79:
#line 323 "d2_parser.yy" // lalr1.cc:856
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1008 "d2_parser.cc" // lalr1.cc:856
    break;

  case 80:
#line 325 "d2_parser.yy" // lalr1.cc:856
    {
    ElementPtr parent = ctx.stack_.back();
    ElementPtr user_context = yystack_[0].value.as< ElementPtr > ();
    ConstElementPtr old = parent->get("user-context");

    // Handle already existing user context
    if (old) {
        // Check if it was a comment or a duplicate
        if ((old->size() != 1) || !old->contains("comment")) {
            std::stringstream msg;
            msg << "duplicate user-context entries (previous at "
                << old->getPosition().str() << ")";
            error(yystack_[3].location, msg.str());
        }
        // Merge the comment
        user_context->set("comment", old->get("comment"));
    }

    // Set the user context
    parent->set("user-context", user_context);
    ctx.leave();
}
#line 1035 "d2_parser.cc" // lalr1.cc:856
    break;

  case 81:
#line 348 "d2_parser.yy" // lalr1.cc:856
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1043 "d2_parser.cc" // lalr1.cc:856
    break;

  case 82:
#line 350 "d2_parser.yy" // lalr1.cc:856
    {
    ElementPtr parent = ctx.stack_.back();
    ElementPtr user_context(new MapElement(ctx.loc2pos(yystack_[3].location)));
    ElementPtr comment(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    user_context->set("comment", comment);

    // Handle already existing user context
    ConstElementPtr old = parent->get("user-context");
    if (old) {
        // Check for duplicate comment
        if (old->contains("comment")) {
            std::stringstream msg;
            msg << "duplicate user-context/comment entries (previous at "
                << old->getPosition().str() << ")";
            error(yystack_[3].location, msg.str());
        }
        // Merge the user context in the comment
        merge(user_context, old);
    }

    // Set the user context
    parent->set("user-context", user_context);
    ctx.leave();
}
#line 1072 "d2_parser.cc" // lalr1.cc:856
    break;

  case 83:
#line 375 "d2_parser.yy" // lalr1.cc:856
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("forward-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.FORWARD_DDNS);
}
#line 1083 "d2_parser.cc" // lalr1.cc:856
    break;

  case 84:
#line 380 "d2_parser.yy" // lalr1.cc:856
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1092 "d2_parser.cc" // lalr1.cc:856
    break;

  case 85:
#line 385 "d2_parser.yy" // lalr1.cc:856
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reverse-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.REVERSE_DDNS);
}
#line 1103 "d2_parser.cc" // lalr1.cc:856
    break;

  case 86:
#line 390 "d2_parser.yy" // lalr1.cc:856
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1112 "d2_parser.cc" // lalr1.cc:856
    break;

  case 93:
#line 409 "d2_parser.yy" // lalr1.cc:856
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-domains", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.DDNS_DOMAINS);
}
#line 1123 "d2_parser.cc" // lalr1.cc:856
    break;

  case 94:
#line 414 "d2_parser.yy" // lalr1.cc:856
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1132 "d2_parser.cc" // lalr1.cc:856
    break;

  case 95:
#line 419 "d2_parser.yy" // lalr1.cc:856
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 1141 "d2_parser.cc" // lalr1.cc:856
    break;

  case 96:
#line 422 "d2_parser.yy" // lalr1.cc:856
    {
    // parsing completed
}
#line 1149 "d2_parser.cc" // lalr1.cc:856
    break;

  case 101:
#line 434 "d2_parser.yy" // lalr1.cc:856
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1159 "d2_parser.cc" // lalr1.cc:856
    break;

  case 102:
#line 438 "d2_parser.yy" // lalr1.cc:856
    {
    ctx.stack_.pop_back();
}
#line 1167 "d2_parser.cc" // lalr1.cc:856
    break;

  case 103:
#line 442 "d2_parser.yy" // lalr1.cc:856
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1176 "d2_parser.cc" // lalr1.cc:856
    break;

  case 104:
#line 445 "d2_parser.yy" // lalr1.cc:856
    {
    // parsing completed
}
#line 1184 "d2_parser.cc" // lalr1.cc:856
    break;

  case 113:
#line 462 "d2_parser.yy" // lalr1.cc:856
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1192 "d2_parser.cc" // lalr1.cc:856
    break;

  case 114:
#line 464 "d2_parser.yy" // lalr1.cc:856
    {
    if (yystack_[0].value.as< std::string > () == "") {
        error(yystack_[1].location, "Ddns domain name cannot be blank");
    }
    ElementPtr elem(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1206 "d2_parser.cc" // lalr1.cc:856
    break;

  case 115:
#line 474 "d2_parser.yy" // lalr1.cc:856
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1214 "d2_parser.cc" // lalr1.cc:856
    break;

  case 116:
#line 476 "d2_parser.yy" // lalr1.cc:856
    {
    ElementPtr elem(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("key-name", name);
    ctx.leave();
}
#line 1225 "d2_parser.cc" // lalr1.cc:856
    break;

  case 117:
#line 486 "d2_parser.yy" // lalr1.cc:856
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dns-servers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.DNS_SERVERS);
}
#line 1236 "d2_parser.cc" // lalr1.cc:856
    break;

  case 118:
#line 491 "d2_parser.yy" // lalr1.cc:856
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1245 "d2_parser.cc" // lalr1.cc:856
    break;

  case 119:
#line 496 "d2_parser.yy" // lalr1.cc:856
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 1254 "d2_parser.cc" // lalr1.cc:856
    break;

  case 120:
#line 499 "d2_parser.yy" // lalr1.cc:856
    {
    // parsing completed
}
#line 1262 "d2_parser.cc" // lalr1.cc:856
    break;

  case 123:
#line 507 "d2_parser.yy" // lalr1.cc:856
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1272 "d2_parser.cc" // lalr1.cc:856
    break;

  case 124:
#line 511 "d2_parser.yy" // lalr1.cc:856
    {
    ctx.stack_.pop_back();
}
#line 1280 "d2_parser.cc" // lalr1.cc:856
    break;

  case 125:
#line 515 "d2_parser.yy" // lalr1.cc:856
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1289 "d2_parser.cc" // lalr1.cc:856
    break;

  case 126:
#line 518 "d2_parser.yy" // lalr1.cc:856
    {
    // parsing completed
}
#line 1297 "d2_parser.cc" // lalr1.cc:856
    break;

  case 135:
#line 534 "d2_parser.yy" // lalr1.cc:856
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1305 "d2_parser.cc" // lalr1.cc:856
    break;

  case 136:
#line 536 "d2_parser.yy" // lalr1.cc:856
    {
    if (yystack_[0].value.as< std::string > () != "") {
        error(yystack_[1].location, "hostname is not yet supported");
    }
    ElementPtr elem(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", name);
    ctx.leave();
}
#line 1319 "d2_parser.cc" // lalr1.cc:856
    break;

  case 137:
#line 546 "d2_parser.yy" // lalr1.cc:856
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1327 "d2_parser.cc" // lalr1.cc:856
    break;

  case 138:
#line 548 "d2_parser.yy" // lalr1.cc:856
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", s);
    ctx.leave();
}
#line 1337 "d2_parser.cc" // lalr1.cc:856
    break;

  case 139:
#line 554 "d2_parser.yy" // lalr1.cc:856
    {
    if (yystack_[0].value.as< int64_t > () <= 0 || yystack_[0].value.as< int64_t > () >= 65536 ) {
        error(yystack_[0].location, "port must be greater than zero but less than 65536");
    }
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", i);
}
#line 1349 "d2_parser.cc" // lalr1.cc:856
    break;

  case 140:
#line 568 "d2_parser.yy" // lalr1.cc:856
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tsig-keys", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.TSIG_KEYS);
}
#line 1360 "d2_parser.cc" // lalr1.cc:856
    break;

  case 141:
#line 573 "d2_parser.yy" // lalr1.cc:856
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1369 "d2_parser.cc" // lalr1.cc:856
    break;

  case 142:
#line 578 "d2_parser.yy" // lalr1.cc:856
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 1378 "d2_parser.cc" // lalr1.cc:856
    break;

  case 143:
#line 581 "d2_parser.yy" // lalr1.cc:856
    {
    // parsing completed
}
#line 1386 "d2_parser.cc" // lalr1.cc:856
    break;

  case 148:
#line 593 "d2_parser.yy" // lalr1.cc:856
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1396 "d2_parser.cc" // lalr1.cc:856
    break;

  case 149:
#line 597 "d2_parser.yy" // lalr1.cc:856
    {
    ctx.stack_.pop_back();
}
#line 1404 "d2_parser.cc" // lalr1.cc:856
    break;

  case 150:
#line 601 "d2_parser.yy" // lalr1.cc:856
    {
    // Parse tsig key list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1414 "d2_parser.cc" // lalr1.cc:856
    break;

  case 151:
#line 605 "d2_parser.yy" // lalr1.cc:856
    {
    // parsing completed
}
#line 1422 "d2_parser.cc" // lalr1.cc:856
    break;

  case 161:
#line 623 "d2_parser.yy" // lalr1.cc:856
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1430 "d2_parser.cc" // lalr1.cc:856
    break;

  case 162:
#line 625 "d2_parser.yy" // lalr1.cc:856
    {
    if (yystack_[0].value.as< std::string > () == "") {
        error(yystack_[1].location, "TSIG key name cannot be blank");
    }
    ElementPtr elem(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1444 "d2_parser.cc" // lalr1.cc:856
    break;

  case 163:
#line 635 "d2_parser.yy" // lalr1.cc:856
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1452 "d2_parser.cc" // lalr1.cc:856
    break;

  case 164:
#line 637 "d2_parser.yy" // lalr1.cc:856
    {
    if (yystack_[0].value.as< std::string > () == "") {
        error(yystack_[1].location, "TSIG key algorithm cannot be blank");
    }
    ElementPtr elem(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("algorithm", elem);
    ctx.leave();
}
#line 1465 "d2_parser.cc" // lalr1.cc:856
    break;

  case 165:
#line 646 "d2_parser.yy" // lalr1.cc:856
    {
    if (yystack_[0].value.as< int64_t > () < 0 || (yystack_[0].value.as< int64_t > () > 0  && (yystack_[0].value.as< int64_t > () % 8 != 0))) {
        error(yystack_[0].location, "TSIG key digest-bits must either be zero or a positive, multiple of eight");
    }
    ElementPtr elem(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("digest-bits", elem);
}
#line 1477 "d2_parser.cc" // lalr1.cc:856
    break;

  case 166:
#line 654 "d2_parser.yy" // lalr1.cc:856
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1485 "d2_parser.cc" // lalr1.cc:856
    break;

  case 167:
#line 656 "d2_parser.yy" // lalr1.cc:856
    {
    if (yystack_[0].value.as< std::string > () == "") {
        error(yystack_[1].location, "TSIG key secret cannot be blank");
    }
    ElementPtr elem(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("secret", elem);
    ctx.leave();
}
#line 1498 "d2_parser.cc" // lalr1.cc:856
    break;

  case 168:
#line 669 "d2_parser.yy" // lalr1.cc:856
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1506 "d2_parser.cc" // lalr1.cc:856
    break;

  case 169:
#line 671 "d2_parser.yy" // lalr1.cc:856
    {
    ctx.stack_.back()->set("Dhcp6", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1515 "d2_parser.cc" // lalr1.cc:856
    break;

  case 170:
#line 676 "d2_parser.yy" // lalr1.cc:856
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1523 "d2_parser.cc" // lalr1.cc:856
    break;

  case 171:
#line 678 "d2_parser.yy" // lalr1.cc:856
    {
    ctx.stack_.back()->set("Dhcp4", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1532 "d2_parser.cc" // lalr1.cc:856
    break;

  case 172:
#line 683 "d2_parser.yy" // lalr1.cc:856
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1540 "d2_parser.cc" // lalr1.cc:856
    break;

  case 173:
#line 685 "d2_parser.yy" // lalr1.cc:856
    {
    ctx.stack_.back()->set("Control-agent", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1549 "d2_parser.cc" // lalr1.cc:856
    break;

  case 174:
#line 695 "d2_parser.yy" // lalr1.cc:856
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Logging", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.LOGGING);
}
#line 1560 "d2_parser.cc" // lalr1.cc:856
    break;

  case 175:
#line 700 "d2_parser.yy" // lalr1.cc:856
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1569 "d2_parser.cc" // lalr1.cc:856
    break;

  case 179:
#line 717 "d2_parser.yy" // lalr1.cc:856
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 1580 "d2_parser.cc" // lalr1.cc:856
    break;

  case 180:
#line 722 "d2_parser.yy" // lalr1.cc:856
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1589 "d2_parser.cc" // lalr1.cc:856
    break;

  case 183:
#line 734 "d2_parser.yy" // lalr1.cc:856
    {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 1599 "d2_parser.cc" // lalr1.cc:856
    break;

  case 184:
#line 738 "d2_parser.yy" // lalr1.cc:856
    {
    ctx.stack_.pop_back();
}
#line 1607 "d2_parser.cc" // lalr1.cc:856
    break;

  case 194:
#line 755 "d2_parser.yy" // lalr1.cc:856
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1615 "d2_parser.cc" // lalr1.cc:856
    break;

  case 195:
#line 757 "d2_parser.yy" // lalr1.cc:856
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1625 "d2_parser.cc" // lalr1.cc:856
    break;

  case 196:
#line 763 "d2_parser.yy" // lalr1.cc:856
    {
    ElementPtr dl(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 1634 "d2_parser.cc" // lalr1.cc:856
    break;

  case 197:
#line 767 "d2_parser.yy" // lalr1.cc:856
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1642 "d2_parser.cc" // lalr1.cc:856
    break;

  case 198:
#line 769 "d2_parser.yy" // lalr1.cc:856
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 1652 "d2_parser.cc" // lalr1.cc:856
    break;

  case 199:
#line 775 "d2_parser.yy" // lalr1.cc:856
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 1663 "d2_parser.cc" // lalr1.cc:856
    break;

  case 200:
#line 780 "d2_parser.yy" // lalr1.cc:856
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1672 "d2_parser.cc" // lalr1.cc:856
    break;

  case 203:
#line 789 "d2_parser.yy" // lalr1.cc:856
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1682 "d2_parser.cc" // lalr1.cc:856
    break;

  case 204:
#line 793 "d2_parser.yy" // lalr1.cc:856
    {
    ctx.stack_.pop_back();
}
#line 1690 "d2_parser.cc" // lalr1.cc:856
    break;

  case 211:
#line 807 "d2_parser.yy" // lalr1.cc:856
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1698 "d2_parser.cc" // lalr1.cc:856
    break;

  case 212:
#line 809 "d2_parser.yy" // lalr1.cc:856
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 1708 "d2_parser.cc" // lalr1.cc:856
    break;

  case 213:
#line 815 "d2_parser.yy" // lalr1.cc:856
    {
    ElementPtr flush(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 1717 "d2_parser.cc" // lalr1.cc:856
    break;

  case 214:
#line 820 "d2_parser.yy" // lalr1.cc:856
    {
    ElementPtr maxsize(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 1726 "d2_parser.cc" // lalr1.cc:856
    break;

  case 215:
#line 825 "d2_parser.yy" // lalr1.cc:856
    {
    ElementPtr maxver(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 1735 "d2_parser.cc" // lalr1.cc:856
    break;


#line 1739 "d2_parser.cc" // lalr1.cc:856
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
        YYCDEBUG << "Exception caught: cleaning lookahead and stack\n";
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
  D2Parser::error (const syntax_error& yyexc)
  {
    error (yyexc.location, yyexc.what ());
  }

  // Generate an error message.
  std::string
  D2Parser::yysyntax_error_ (state_type yystate, const symbol_type& yyla) const
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
      default: // Avoid compiler warnings.
        YYCASE_ (0, YY_("syntax error"));
        YYCASE_ (1, YY_("syntax error, unexpected %s"));
        YYCASE_ (2, YY_("syntax error, unexpected %s, expecting %s"));
        YYCASE_ (3, YY_("syntax error, unexpected %s, expecting %s or %s"));
        YYCASE_ (4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
        YYCASE_ (5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
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


  const signed char D2Parser::yypact_ninf_ = -90;

  const signed char D2Parser::yytable_ninf_ = -1;

  const short int
  D2Parser::yypact_[] =
  {
      47,   -90,   -90,   -90,   -90,   -90,   -90,   -90,   -90,   -90,
      12,     2,     1,    23,    33,    11,    38,    58,    64,    73,
     -90,   -90,   -90,   -90,   -90,   -90,   -90,   -90,   -90,   -90,
     -90,   -90,   -90,   -90,   -90,   -90,   -90,   -90,   -90,   -90,
     -90,   -90,   -90,   -90,   -90,   -90,   -90,   -90,     2,   -25,
       8,     9,    15,    96,    37,   115,    21,   116,   -90,   124,
     113,   127,   130,   137,   -90,   -90,   -90,   -90,   -90,   146,
     -90,    19,   -90,   -90,   -90,   -90,   -90,   -90,   -90,   148,
     150,   -90,   -90,   -90,   -90,   -90,   -90,   -90,   -90,    46,
     -90,   -90,   -90,   -90,   -90,   -90,   -90,   -90,   -90,   -90,
     -90,   -90,   152,   -90,   -90,   -90,   -90,   -90,    76,   -90,
     -90,   -90,   -90,   -90,   -90,   151,   155,   -90,   -90,   -90,
     -90,   -90,   -90,   -90,    77,   -90,   -90,   -90,   -90,   -90,
     153,   157,   -90,   -90,   161,   -90,   -90,   -90,   -90,    78,
     -90,   -90,   -90,   -90,   -90,   118,   -90,   -90,     2,     2,
     -90,   108,   162,   163,   164,   165,   166,   -90,     8,   -90,
     167,   119,   120,   168,   171,   172,   173,   174,   175,   176,
       9,   -90,   177,   128,   179,   180,    15,   -90,    15,   -90,
      96,   181,   182,   183,    37,   -90,    37,   -90,   115,   184,
     135,   186,    21,   -90,    21,   116,   -90,   -90,   -90,   187,
       2,     2,     2,   185,   188,   -90,   140,   -90,   -90,    70,
     178,   189,   141,   190,   195,   198,   -90,   154,   -90,   156,
     158,   -90,    79,   -90,   159,   199,   160,   -90,    97,   -90,
     169,   -90,   170,   -90,    98,   -90,     2,   -90,   -90,   -90,
       9,   191,   -90,   -90,   -90,   -90,   -90,   -90,   -90,   -90,
     -12,   -12,    96,   -90,   -90,   -90,   -90,   -90,   116,   -90,
     -90,   -90,   -90,   -90,   -90,    99,   -90,   101,   -90,   -90,
     -90,   -90,   109,   -90,   -90,   -90,   110,   200,   126,   -90,
     201,   191,   -90,   204,   -12,   -90,   -90,   -90,   -90,   205,
     -90,   209,   -90,   208,   115,   -90,   143,   -90,   210,    30,
     208,   -90,   -90,   -90,   -90,   213,   -90,   -90,   -90,   -90,
     111,   -90,   -90,   -90,   -90,   -90,   -90,   214,   215,   192,
     216,    30,   -90,   194,   219,   -90,   197,   -90,   -90,   218,
     -90,   -90,   145,   -90,    34,   218,   -90,   -90,   217,   223,
     224,   112,   -90,   -90,   -90,   -90,   -90,   -90,   225,   196,
     202,   203,    34,   -90,   206,   -90,   -90,   -90,   -90,   -90
  };

  const unsigned char
  D2Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       1,    35,    28,    24,    23,    20,    21,    22,    27,     3,
      25,    26,    42,     5,    54,     7,   150,     9,   142,    11,
     103,    13,    95,    15,   125,    17,   119,    19,    37,    31,
       0,     0,     0,   144,     0,    97,     0,     0,    39,     0,
      38,     0,     0,    32,   168,   170,   172,    52,   174,     0,
      51,     0,    44,    49,    46,    48,    50,    47,    69,     0,
       0,    73,    77,    79,    81,    83,    85,   140,    68,     0,
      56,    58,    59,    60,    61,    62,    66,    67,    63,    64,
      65,   163,     0,   166,   161,   160,   158,   159,     0,   152,
     154,   155,   156,   157,   148,     0,   145,   146,   115,   117,
     113,   112,   110,   111,     0,   105,   107,   108,   109,   101,
       0,    98,    99,   137,     0,   135,   134,   132,   133,     0,
     127,   129,   130,   131,   123,     0,   121,    36,     0,     0,
      29,     0,     0,     0,     0,     0,     0,    41,     0,    43,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    55,     0,     0,     0,     0,     0,   151,     0,   143,
       0,     0,     0,     0,     0,   104,     0,    96,     0,     0,
       0,     0,     0,   126,     0,     0,   120,    40,    33,     0,
       0,     0,     0,     0,     0,    45,     0,    71,    72,     0,
       0,     0,     0,     0,     0,     0,    57,     0,   165,     0,
       0,   153,     0,   147,     0,     0,     0,   106,     0,   100,
       0,   139,     0,   128,     0,   122,     0,   169,   171,   173,
       0,     0,    70,    75,    76,    74,    78,    30,    80,    82,
      87,    87,   144,   164,   167,   162,   149,   116,     0,   114,
     102,   138,   136,   124,    34,     0,   179,     0,   176,   178,
      93,    92,     0,    88,    89,    91,     0,     0,     0,    53,
       0,     0,   175,     0,     0,    84,    86,   141,   118,     0,
     177,     0,    90,     0,    97,   183,     0,   181,     0,     0,
       0,   180,    94,   194,   199,     0,   197,   193,   191,   192,
       0,   185,   187,   189,   190,   188,   182,     0,     0,     0,
       0,     0,   184,     0,     0,   196,     0,   186,   195,     0,
     198,   203,     0,   201,     0,     0,   200,   211,     0,     0,
       0,     0,   205,   207,   208,   209,   210,   202,     0,     0,
       0,     0,     0,   204,     0,   213,   214,   215,   206,   212
  };

  const signed char
  D2Parser::yypgoto_[] =
  {
     -90,   -90,   -90,   -90,   -90,   -90,   -90,   -90,   -90,   -90,
     -90,   -38,   -90,    20,   -90,   -90,   -90,   -90,   -90,   -90,
     -90,   -90,   -50,   -90,   -90,   -90,    72,   -90,   -90,   -90,
     -90,    -8,    63,   -90,   -90,   -90,   -90,   -90,   -90,   -90,
     -90,   -90,   -51,   -90,   -39,   -90,   -90,   -90,   -90,   -90,
     -16,   -90,   -48,   -90,   -90,   -90,   -90,   -57,   -90,    50,
     -90,   -90,   -90,    53,    56,   -90,   -90,   -90,   -90,   -90,
     -90,   -90,   -90,   -17,    48,   -90,   -90,   -90,    51,    52,
     -90,   -90,   -90,   -90,   -90,   -90,   -90,   -90,   -90,   -10,
     -90,    71,   -90,   -90,   -90,    75,    82,   -90,   -90,   -90,
     -90,   -90,   -90,   -90,   -90,   -90,   -90,   -90,   -90,   -90,
     -90,   -90,   -90,   -27,   -90,   -90,   -90,   -45,   -90,   -90,
     -60,   -90,   -90,   -90,   -90,   -90,   -90,   -90,   -90,   -73,
     -90,   -90,   -89,   -90,   -90,   -90,   -90,   -90
  };

  const short int
  D2Parser::yydefgoto_[] =
  {
      -1,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    28,    29,    30,    49,   248,    62,    63,    31,    48,
      59,    60,    88,    33,    50,    71,    72,    73,   155,    35,
      51,    89,    90,    91,   160,    92,    93,    94,   163,   245,
      95,   164,    96,   165,    97,   166,    98,   167,    99,   168,
     272,   273,   274,   275,   283,    43,    55,   130,   131,   132,
     186,    41,    54,   124,   125,   126,   183,   127,   181,   128,
     182,    47,    57,   145,   146,   194,    45,    56,   139,   140,
     141,   191,   142,   189,   143,   100,   169,    39,    53,   115,
     116,   117,   178,    37,    52,   108,   109,   110,   175,   111,
     172,   112,   113,   174,    74,   152,    75,   153,    76,   154,
      77,   156,   267,   268,   269,   280,   296,   297,   299,   310,
     311,   312,   317,   313,   314,   320,   315,   318,   332,   333,
     334,   341,   342,   343,   348,   344,   345,   346
  };

  const unsigned short int
  D2Parser::yytable_[] =
  {
      70,   106,   105,   122,   121,   137,   136,    21,    32,    22,
      58,    23,    20,   107,   270,   123,    38,   138,    64,    65,
      66,    67,   158,    78,    79,    80,    81,   159,    61,    82,
      34,    83,    84,    85,    86,   133,   134,    83,    84,    87,
      36,    69,    68,    83,    84,    40,   101,   102,   103,   170,
     135,   104,    83,    84,   171,    24,    25,    26,    27,    83,
      84,    69,    69,    42,   118,   119,   303,   304,    69,   305,
     306,    44,   337,   120,    69,   338,   339,   340,    46,   176,
     184,   192,   176,    69,   177,   185,   193,   256,   243,   244,
      69,     1,     2,     3,     4,     5,     6,     7,     8,     9,
     184,   192,   170,   114,   281,   260,   263,   279,    70,   282,
     197,   198,   284,   284,   321,   352,   148,   285,   286,   322,
     353,   195,   129,   144,   196,   106,   105,   106,   105,   195,
     147,   149,   288,   122,   121,   122,   121,   107,   150,   107,
     151,   137,   136,   137,   136,   123,   300,   123,   335,   301,
     157,   336,   161,   138,   162,   138,   173,   179,   180,   187,
     188,   199,   237,   238,   239,   190,   200,   201,   202,   203,
     204,   206,   209,   207,   208,   210,   211,   212,   213,   214,
     215,   217,   218,   219,   220,   224,   225,   226,   230,   231,
     232,   236,   240,   242,   249,   241,    22,   250,   264,   246,
     271,   271,   251,   252,   258,   289,   287,   253,   291,   254,
     293,   255,   257,   259,   294,   295,   302,   319,   323,   324,
     326,   349,   261,   262,   329,   331,   266,   350,   351,   354,
     205,   247,   265,   216,   271,   276,   292,   298,   229,   228,
     227,   278,   277,   235,   233,   234,   325,   328,   308,   307,
     330,   223,   355,   222,   290,   316,   356,   357,   221,   359,
     309,   327,   347,   358,     0,     0,     0,     0,     0,     0,
     308,   307,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   309
  };

  const short int
  D2Parser::yycheck_[] =
  {
      50,    52,    52,    54,    54,    56,    56,     5,     7,     7,
      48,     9,     0,    52,    26,    54,     5,    56,    10,    11,
      12,    13,     3,    14,    15,    16,    17,     8,    53,    20,
       7,    22,    23,    24,    25,    14,    15,    22,    23,    30,
       7,    53,    34,    22,    23,     7,    31,    32,    33,     3,
      29,    36,    22,    23,     8,    53,    54,    55,    56,    22,
      23,    53,    53,     5,    27,    28,    36,    37,    53,    39,
      40,     7,    38,    36,    53,    41,    42,    43,     5,     3,
       3,     3,     3,    53,     8,     8,     8,     8,    18,    19,
      53,    44,    45,    46,    47,    48,    49,    50,    51,    52,
       3,     3,     3,     7,     3,     8,     8,     8,   158,     8,
     148,   149,     3,     3,     3,     3,     3,     8,     8,     8,
       8,     3,     7,     7,     6,   176,   176,   178,   178,     3,
       6,     4,     6,   184,   184,   186,   186,   176,     8,   178,
       3,   192,   192,   194,   194,   184,     3,   186,     3,     6,
       4,     6,     4,   192,     4,   194,     4,     6,     3,     6,
       3,    53,   200,   201,   202,     4,     4,     4,     4,     4,
       4,     4,     4,    54,    54,     4,     4,     4,     4,     4,
       4,     4,    54,     4,     4,     4,     4,     4,     4,    54,
       4,     4,     7,    53,    53,     7,     7,     7,   236,    21,
     250,   251,     7,     5,     5,     4,     6,    53,     4,    53,
       5,    53,    53,    53,     5,     7,     6,     4,     4,     4,
       4,     4,    53,    53,     5,     7,    35,     4,     4,     4,
     158,   211,   240,   170,   284,   251,   284,   294,   188,   186,
     184,   258,   252,   195,   192,   194,    54,    53,   299,   299,
      53,   180,    56,   178,   281,   300,    54,    54,   176,    53,
     299,   321,   335,   352,    -1,    -1,    -1,    -1,    -1,    -1,
     321,   321,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   321
  };

  const unsigned char
  D2Parser::yystos_[] =
  {
       0,    44,    45,    46,    47,    48,    49,    50,    51,    52,
      58,    59,    60,    61,    62,    63,    64,    65,    66,    67,
       0,     5,     7,     9,    53,    54,    55,    56,    68,    69,
      70,    75,     7,    80,     7,    86,     7,   150,     5,   144,
       7,   118,     5,   112,     7,   133,     5,   128,    76,    71,
      81,    87,   151,   145,   119,   113,   134,   129,    68,    77,
      78,    53,    73,    74,    10,    11,    12,    13,    34,    53,
      79,    82,    83,    84,   161,   163,   165,   167,    14,    15,
      16,    17,    20,    22,    23,    24,    25,    30,    79,    88,
      89,    90,    92,    93,    94,    97,    99,   101,   103,   105,
     142,    31,    32,    33,    36,    79,    99,   101,   152,   153,
     154,   156,   158,   159,     7,   146,   147,   148,    27,    28,
      36,    79,    99,   101,   120,   121,   122,   124,   126,     7,
     114,   115,   116,    14,    15,    29,    79,    99,   101,   135,
     136,   137,   139,   141,     7,   130,   131,     6,     3,     4,
       8,     3,   162,   164,   166,    85,   168,     4,     3,     8,
      91,     4,     4,    95,    98,   100,   102,   104,   106,   143,
       3,     8,   157,     4,   160,   155,     3,     8,   149,     6,
       3,   125,   127,   123,     3,     8,   117,     6,     3,   140,
       4,   138,     3,     8,   132,     3,     6,    68,    68,    53,
       4,     4,     4,     4,     4,    83,     4,    54,    54,     4,
       4,     4,     4,     4,     4,     4,    89,     4,    54,     4,
       4,   153,   152,   148,     4,     4,     4,   121,   120,   116,
       4,    54,     4,   136,   135,   131,     4,    68,    68,    68,
       7,     7,    53,    18,    19,    96,    21,    70,    72,    53,
       7,     7,     5,    53,    53,    53,     8,    53,     5,    53,
       8,    53,    53,     8,    68,    88,    35,   169,   170,   171,
      26,    79,   107,   108,   109,   110,   107,   146,   130,     8,
     172,     3,     8,   111,     3,     8,     8,     6,     6,     4,
     170,     4,   109,     5,     5,     7,   173,   174,   114,   175,
       3,     6,     6,    36,    37,    39,    40,    79,    99,   101,
     176,   177,   178,   180,   181,   183,   174,   179,   184,     4,
     182,     3,     8,     4,     4,    54,     4,   177,    53,     5,
      53,     7,   185,   186,   187,     3,     6,    38,    41,    42,
      43,   188,   189,   190,   192,   193,   194,   186,   191,     4,
       4,     4,     3,     8,     4,    56,    54,    54,   189,    53
  };

  const unsigned char
  D2Parser::yyr1_[] =
  {
       0,    57,    59,    58,    60,    58,    61,    58,    62,    58,
      63,    58,    64,    58,    65,    58,    66,    58,    67,    58,
      68,    68,    68,    68,    68,    68,    68,    69,    71,    70,
      72,    73,    73,    74,    74,    76,    75,    77,    77,    78,
      78,    79,    81,    80,    82,    82,    83,    83,    83,    83,
      83,    83,    85,    84,    87,    86,    88,    88,    89,    89,
      89,    89,    89,    89,    89,    89,    89,    89,    89,    91,
      90,    92,    93,    95,    94,    96,    96,    98,    97,   100,
      99,   102,   101,   104,   103,   106,   105,   107,   107,   108,
     108,   109,   109,   111,   110,   113,   112,   114,   114,   115,
     115,   117,   116,   119,   118,   120,   120,   121,   121,   121,
     121,   121,   121,   123,   122,   125,   124,   127,   126,   129,
     128,   130,   130,   132,   131,   134,   133,   135,   135,   136,
     136,   136,   136,   136,   136,   138,   137,   140,   139,   141,
     143,   142,   145,   144,   146,   146,   147,   147,   149,   148,
     151,   150,   152,   152,   153,   153,   153,   153,   153,   153,
     153,   155,   154,   157,   156,   158,   160,   159,   162,   161,
     164,   163,   166,   165,   168,   167,   169,   169,   170,   172,
     171,   173,   173,   175,   174,   176,   176,   177,   177,   177,
     177,   177,   177,   177,   179,   178,   180,   182,   181,   184,
     183,   185,   185,   187,   186,   188,   188,   189,   189,   189,
     189,   191,   190,   192,   193,   194
  };

  const unsigned char
  D2Parser::yyr2_[] =
  {
       0,     2,     0,     3,     0,     3,     0,     3,     0,     3,
       0,     3,     0,     3,     0,     3,     0,     3,     0,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     0,     4,
       1,     0,     1,     3,     5,     0,     4,     0,     1,     1,
       3,     2,     0,     4,     1,     3,     1,     1,     1,     1,
       1,     1,     0,     6,     0,     4,     1,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     0,
       4,     3,     3,     0,     4,     1,     1,     0,     4,     0,
       4,     0,     4,     0,     6,     0,     6,     0,     1,     1,
       3,     1,     1,     0,     6,     0,     4,     0,     1,     1,
       3,     0,     4,     0,     4,     1,     3,     1,     1,     1,
       1,     1,     1,     0,     4,     0,     4,     0,     6,     0,
       4,     1,     3,     0,     4,     0,     4,     1,     3,     1,
       1,     1,     1,     1,     1,     0,     4,     0,     4,     3,
       0,     6,     0,     4,     0,     1,     1,     3,     0,     4,
       0,     4,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     0,     4,     0,     4,     3,     0,     4,     0,     4,
       0,     4,     0,     4,     0,     6,     1,     3,     1,     0,
       6,     1,     3,     0,     4,     1,     3,     1,     1,     1,
       1,     1,     1,     1,     0,     4,     3,     0,     4,     0,
       6,     1,     3,     0,     4,     1,     3,     1,     1,     1,
       1,     0,     4,     3,     3,     3
  };



  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a yyntokens_, nonterminals.
  const char*
  const D2Parser::yytname_[] =
  {
  "\"end of file\"", "error", "$undefined", "\",\"", "\":\"", "\"[\"",
  "\"]\"", "\"{\"", "\"}\"", "\"null\"", "\"Dhcp6\"", "\"Dhcp4\"",
  "\"Control-agent\"", "\"DhcpDdns\"", "\"ip-address\"", "\"port\"",
  "\"dns-server-timeout\"", "\"ncr-protocol\"", "\"UDP\"", "\"TCP\"",
  "\"ncr-format\"", "\"JSON\"", "\"user-context\"", "\"comment\"",
  "\"forward-ddns\"", "\"reverse-ddns\"", "\"ddns-domains\"",
  "\"key-name\"", "\"dns-servers\"", "\"hostname\"", "\"tsig-keys\"",
  "\"algorithm\"", "\"digest-bits\"", "\"secret\"", "\"Logging\"",
  "\"loggers\"", "\"name\"", "\"output_options\"", "\"output\"",
  "\"debuglevel\"", "\"severity\"", "\"flush\"", "\"maxsize\"",
  "\"maxver\"", "TOPLEVEL_JSON", "TOPLEVEL_DHCPDDNS", "SUB_DHCPDDNS",
  "SUB_TSIG_KEY", "SUB_TSIG_KEYS", "SUB_DDNS_DOMAIN", "SUB_DDNS_DOMAINS",
  "SUB_DNS_SERVER", "SUB_DNS_SERVERS", "\"constant string\"",
  "\"integer\"", "\"floating point\"", "\"boolean\"", "$accept", "start",
  "$@1", "$@2", "$@3", "$@4", "$@5", "$@6", "$@7", "$@8", "$@9", "value",
  "sub_json", "map2", "$@10", "map_value", "map_content", "not_empty_map",
  "list_generic", "$@11", "list_content", "not_empty_list",
  "unknown_map_entry", "syntax_map", "$@12", "global_objects",
  "global_object", "dhcpddns_object", "$@13", "sub_dhcpddns", "$@14",
  "dhcpddns_params", "dhcpddns_param", "ip_address", "$@15", "port",
  "dns_server_timeout", "ncr_protocol", "$@16", "ncr_protocol_value",
  "ncr_format", "$@17", "user_context", "$@18", "comment", "$@19",
  "forward_ddns", "$@20", "reverse_ddns", "$@21", "ddns_mgr_params",
  "not_empty_ddns_mgr_params", "ddns_mgr_param", "ddns_domains", "$@22",
  "sub_ddns_domains", "$@23", "ddns_domain_list",
  "not_empty_ddns_domain_list", "ddns_domain", "$@24", "sub_ddns_domain",
  "$@25", "ddns_domain_params", "ddns_domain_param", "ddns_domain_name",
  "$@26", "ddns_domain_key_name", "$@27", "dns_servers", "$@28",
  "sub_dns_servers", "$@29", "dns_server_list", "dns_server", "$@30",
  "sub_dns_server", "$@31", "dns_server_params", "dns_server_param",
  "dns_server_hostname", "$@32", "dns_server_ip_address", "$@33",
  "dns_server_port", "tsig_keys", "$@34", "sub_tsig_keys", "$@35",
  "tsig_keys_list", "not_empty_tsig_keys_list", "tsig_key", "$@36",
  "sub_tsig_key", "$@37", "tsig_key_params", "tsig_key_param",
  "tsig_key_name", "$@38", "tsig_key_algorithm", "$@39",
  "tsig_key_digest_bits", "tsig_key_secret", "$@40", "dhcp6_json_object",
  "$@41", "dhcp4_json_object", "$@42", "control_agent_json_object", "$@43",
  "logging_object", "$@44", "logging_params", "logging_param", "loggers",
  "$@45", "loggers_entries", "logger_entry", "$@46", "logger_params",
  "logger_param", "name", "$@47", "debuglevel", "severity", "$@48",
  "output_options_list", "$@49", "output_options_list_content",
  "output_entry", "$@50", "output_params_list", "output_params", "output",
  "$@51", "flush", "maxsize", "maxver", YY_NULLPTR
  };

#if D2_PARSER_DEBUG
  const unsigned short int
  D2Parser::yyrline_[] =
  {
       0,   120,   120,   120,   121,   121,   122,   122,   123,   123,
     124,   124,   125,   125,   126,   126,   127,   127,   128,   128,
     136,   137,   138,   139,   140,   141,   142,   145,   150,   150,
     161,   164,   165,   168,   172,   179,   179,   186,   187,   190,
     194,   205,   215,   215,   227,   228,   232,   233,   234,   235,
     236,   237,   242,   242,   252,   252,   260,   261,   265,   266,
     267,   268,   269,   270,   271,   272,   273,   274,   275,   278,
     278,   286,   294,   303,   303,   311,   312,   315,   315,   323,
     323,   348,   348,   375,   375,   385,   385,   395,   396,   399,
     400,   403,   404,   409,   409,   419,   419,   426,   427,   430,
     431,   434,   434,   442,   442,   449,   450,   453,   454,   455,
     456,   457,   458,   462,   462,   474,   474,   486,   486,   496,
     496,   503,   504,   507,   507,   515,   515,   522,   523,   526,
     527,   528,   529,   530,   531,   534,   534,   546,   546,   554,
     568,   568,   578,   578,   585,   586,   589,   590,   593,   593,
     601,   601,   610,   611,   614,   615,   616,   617,   618,   619,
     620,   623,   623,   635,   635,   646,   654,   654,   669,   669,
     676,   676,   683,   683,   695,   695,   708,   709,   713,   717,
     717,   729,   730,   734,   734,   742,   743,   746,   747,   748,
     749,   750,   751,   752,   755,   755,   763,   767,   767,   775,
     775,   785,   786,   789,   789,   797,   798,   801,   802,   803,
     804,   807,   807,   815,   820,   825
  };

  // Print the state stack on the debug stream.
  void
  D2Parser::yystack_print_ ()
  {
    *yycdebug_ << "Stack now";
    for (stack_type::const_iterator
           i = yystack_.begin (),
           i_end = yystack_.end ();
         i != i_end; ++i)
      *yycdebug_ << ' ' << i->state;
    *yycdebug_ << '\n';
  }

  // Report on the debug stream that the rule \a yyrule is going to be reduced.
  void
  D2Parser::yy_reduce_print_ (int yyrule)
  {
    unsigned yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    // Print the symbols being reduced, and their result.
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
               << " (line " << yylno << "):\n";
    // The symbols being reduced.
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
                       yystack_[(yynrhs) - (yyi + 1)]);
  }
#endif // D2_PARSER_DEBUG


#line 14 "d2_parser.yy" // lalr1.cc:1163
} } // isc::d2
#line 2392 "d2_parser.cc" // lalr1.cc:1163
#line 830 "d2_parser.yy" // lalr1.cc:1164


void
isc::d2::D2Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
