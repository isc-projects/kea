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
#define yylex   parser6_lex

// First part of user declarations.

#line 39 "dhcp6_parser.cc" // lalr1.cc:404

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

#include "dhcp6_parser.h"

// User implementation prologue.

#line 53 "dhcp6_parser.cc" // lalr1.cc:412
// Unqualified %code blocks.
#line 34 "dhcp6_parser.yy" // lalr1.cc:413

#include <dhcp6/parser_context.h>

#line 59 "dhcp6_parser.cc" // lalr1.cc:413


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
#if PARSER6_DEBUG

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

#else // !PARSER6_DEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YYUSE(Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void>(0)
# define YY_STACK_PRINT()                static_cast<void>(0)

#endif // !PARSER6_DEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)

#line 14 "dhcp6_parser.yy" // lalr1.cc:479
namespace isc { namespace dhcp {
#line 145 "dhcp6_parser.cc" // lalr1.cc:479

  /* Return YYSTR after stripping away unnecessary quotes and
     backslashes, so that it's suitable for yyerror.  The heuristic is
     that double-quoting is unnecessary unless the string contains an
     apostrophe, a comma, or backslash (other than backslash-backslash).
     YYSTR is taken from yytname.  */
  std::string
  Dhcp6Parser::yytnamerr_ (const char *yystr)
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
  Dhcp6Parser::Dhcp6Parser (isc::dhcp::Parser6Context& ctx_yyarg)
    :
#if PARSER6_DEBUG
      yydebug_ (false),
      yycdebug_ (&std::cerr),
#endif
      ctx (ctx_yyarg)
  {}

  Dhcp6Parser::~Dhcp6Parser ()
  {}


  /*---------------.
  | Symbol types.  |
  `---------------*/



  // by_state.
  inline
  Dhcp6Parser::by_state::by_state ()
    : state (empty_state)
  {}

  inline
  Dhcp6Parser::by_state::by_state (const by_state& other)
    : state (other.state)
  {}

  inline
  void
  Dhcp6Parser::by_state::clear ()
  {
    state = empty_state;
  }

  inline
  void
  Dhcp6Parser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  inline
  Dhcp6Parser::by_state::by_state (state_type s)
    : state (s)
  {}

  inline
  Dhcp6Parser::symbol_number_type
  Dhcp6Parser::by_state::type_get () const
  {
    if (state == empty_state)
      return empty_symbol;
    else
      return yystos_[state];
  }

  inline
  Dhcp6Parser::stack_symbol_type::stack_symbol_type ()
  {}


  inline
  Dhcp6Parser::stack_symbol_type::stack_symbol_type (state_type s, symbol_type& that)
    : super_type (s, that.location)
  {
      switch (that.type_get ())
    {
      case 169: // value
      case 173: // map_value
      case 217: // db_type
      case 293: // hr_mode
      case 416: // duid_type
      case 449: // ncr_protocol_value
      case 457: // replace_client_name_value
        value.move< ElementPtr > (that.value);
        break;

      case 153: // "boolean"
        value.move< bool > (that.value);
        break;

      case 152: // "floating point"
        value.move< double > (that.value);
        break;

      case 151: // "integer"
        value.move< int64_t > (that.value);
        break;

      case 150: // "constant string"
        value.move< std::string > (that.value);
        break;

      default:
        break;
    }

    // that is emptied.
    that.type = empty_symbol;
  }

  inline
  Dhcp6Parser::stack_symbol_type&
  Dhcp6Parser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
      switch (that.type_get ())
    {
      case 169: // value
      case 173: // map_value
      case 217: // db_type
      case 293: // hr_mode
      case 416: // duid_type
      case 449: // ncr_protocol_value
      case 457: // replace_client_name_value
        value.copy< ElementPtr > (that.value);
        break;

      case 153: // "boolean"
        value.copy< bool > (that.value);
        break;

      case 152: // "floating point"
        value.copy< double > (that.value);
        break;

      case 151: // "integer"
        value.copy< int64_t > (that.value);
        break;

      case 150: // "constant string"
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
  Dhcp6Parser::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);
  }

#if PARSER6_DEBUG
  template <typename Base>
  void
  Dhcp6Parser::yy_print_ (std::ostream& yyo,
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
            case 150: // "constant string"

#line 226 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< std::string > (); }
#line 364 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 151: // "integer"

#line 226 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< int64_t > (); }
#line 371 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 152: // "floating point"

#line 226 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< double > (); }
#line 378 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 153: // "boolean"

#line 226 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< bool > (); }
#line 385 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 169: // value

#line 226 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 392 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 173: // map_value

#line 226 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 399 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 217: // db_type

#line 226 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 406 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 293: // hr_mode

#line 226 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 413 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 416: // duid_type

#line 226 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 420 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 449: // ncr_protocol_value

#line 226 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 427 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 457: // replace_client_name_value

#line 226 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 434 "dhcp6_parser.cc" // lalr1.cc:636
        break;


      default:
        break;
    }
    yyo << ')';
  }
#endif

  inline
  void
  Dhcp6Parser::yypush_ (const char* m, state_type s, symbol_type& sym)
  {
    stack_symbol_type t (s, sym);
    yypush_ (m, t);
  }

  inline
  void
  Dhcp6Parser::yypush_ (const char* m, stack_symbol_type& s)
  {
    if (m)
      YY_SYMBOL_PRINT (m, s);
    yystack_.push (s);
  }

  inline
  void
  Dhcp6Parser::yypop_ (unsigned int n)
  {
    yystack_.pop (n);
  }

#if PARSER6_DEBUG
  std::ostream&
  Dhcp6Parser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  Dhcp6Parser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  Dhcp6Parser::debug_level_type
  Dhcp6Parser::debug_level () const
  {
    return yydebug_;
  }

  void
  Dhcp6Parser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // PARSER6_DEBUG

  inline Dhcp6Parser::state_type
  Dhcp6Parser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - yyntokens_] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - yyntokens_];
  }

  inline bool
  Dhcp6Parser::yy_pact_value_is_default_ (int yyvalue)
  {
    return yyvalue == yypact_ninf_;
  }

  inline bool
  Dhcp6Parser::yy_table_value_is_error_ (int yyvalue)
  {
    return yyvalue == yytable_ninf_;
  }

  int
  Dhcp6Parser::parse ()
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
      case 169: // value
      case 173: // map_value
      case 217: // db_type
      case 293: // hr_mode
      case 416: // duid_type
      case 449: // ncr_protocol_value
      case 457: // replace_client_name_value
        yylhs.value.build< ElementPtr > ();
        break;

      case 153: // "boolean"
        yylhs.value.build< bool > ();
        break;

      case 152: // "floating point"
        yylhs.value.build< double > ();
        break;

      case 151: // "integer"
        yylhs.value.build< int64_t > ();
        break;

      case 150: // "constant string"
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
#line 235 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.NO_KEYWORD; }
#line 680 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 4:
#line 236 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.CONFIG; }
#line 686 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 6:
#line 237 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.DHCP6; }
#line 692 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 8:
#line 238 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.INTERFACES_CONFIG; }
#line 698 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 10:
#line 239 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.SUBNET6; }
#line 704 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 12:
#line 240 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.POOLS; }
#line 710 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 14:
#line 241 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.PD_POOLS; }
#line 716 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 16:
#line 242 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.RESERVATIONS; }
#line 722 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 18:
#line 243 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.DHCP6; }
#line 728 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 20:
#line 244 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.OPTION_DEF; }
#line 734 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 22:
#line 245 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.OPTION_DATA; }
#line 740 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 24:
#line 246 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.HOOKS_LIBRARIES; }
#line 746 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 26:
#line 247 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.DHCP_DDNS; }
#line 752 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 28:
#line 255 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 758 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 29:
#line 256 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as< double > (), ctx.loc2pos(yystack_[0].location))); }
#line 764 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 30:
#line 257 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 770 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 31:
#line 258 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 776 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 32:
#line 259 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 782 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 33:
#line 260 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 788 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 34:
#line 261 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 794 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 35:
#line 264 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as< ElementPtr > ());
}
#line 803 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 36:
#line 269 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 814 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 37:
#line 274 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 824 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 38:
#line 280 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 830 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 41:
#line 287 "dhcp6_parser.yy" // lalr1.cc:859
    {
                  // map containing a single entry
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 839 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 42:
#line 291 "dhcp6_parser.yy" // lalr1.cc:859
    {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 849 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 43:
#line 298 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 858 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 44:
#line 301 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // list parsing complete. Put any sanity checking here
}
#line 866 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 47:
#line 309 "dhcp6_parser.yy" // lalr1.cc:859
    {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 875 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 48:
#line 313 "dhcp6_parser.yy" // lalr1.cc:859
    {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 884 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 49:
#line 320 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // List parsing about to start
}
#line 892 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 50:
#line 322 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // list parsing complete. Put any sanity checking here
    //ctx.stack_.pop_back();
}
#line 901 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 53:
#line 331 "dhcp6_parser.yy" // lalr1.cc:859
    {
                          ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 910 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 54:
#line 335 "dhcp6_parser.yy" // lalr1.cc:859
    {
                          ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 919 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 55:
#line 346 "dhcp6_parser.yy" // lalr1.cc:859
    {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as< std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 930 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 56:
#line 356 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 941 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 57:
#line 361 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.

    // Dhcp6 is required
    ctx.require("Dhcp6", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
}
#line 954 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 66:
#line 384 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Dhcp6", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP6);
}
#line 967 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 67:
#line 391 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // No global parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 977 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 68:
#line 399 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the Dhcp6 map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 987 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 69:
#line 403 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // No global parameter is required
    // parsing completed
}
#line 996 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 94:
#line 438 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("preferred-lifetime", prf);
}
#line 1005 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 95:
#line 443 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 1014 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 96:
#line 448 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 1023 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 97:
#line 453 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 1032 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 98:
#line 458 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr dpp(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 1041 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 99:
#line 463 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces-config", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.INTERFACES_CONFIG);
}
#line 1052 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 100:
#line 468 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // No interfaces config param is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1062 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 101:
#line 474 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1072 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 102:
#line 478 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // No interfaces config param is required
    // parsing completed
}
#line 1081 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 107:
#line 491 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1092 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 108:
#line 496 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1101 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 109:
#line 501 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("re-detect", b);
}
#line 1110 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 110:
#line 507 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lease-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.LEASE_DATABASE);
}
#line 1121 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 111:
#line 512 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1132 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 112:
#line 519 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1143 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 113:
#line 524 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1154 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 129:
#line 550 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.DATABASE_TYPE);
}
#line 1162 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 130:
#line 552 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("type", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1171 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 131:
#line 557 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("memfile", ctx.loc2pos(yystack_[0].location))); }
#line 1177 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 132:
#line 558 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("mysql", ctx.loc2pos(yystack_[0].location))); }
#line 1183 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 133:
#line 559 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("postgresql", ctx.loc2pos(yystack_[0].location))); }
#line 1189 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 134:
#line 560 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("cql", ctx.loc2pos(yystack_[0].location))); }
#line 1195 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 135:
#line 563 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1203 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 136:
#line 565 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr user(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1213 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 137:
#line 571 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1221 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 138:
#line 573 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr pwd(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 1231 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 139:
#line 579 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1239 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 140:
#line 581 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr h(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 1249 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 141:
#line 587 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr p(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", p);
}
#line 1258 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 142:
#line 592 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1266 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 143:
#line 594 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1276 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 144:
#line 600 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 1285 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 145:
#line 605 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 1294 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 146:
#line 610 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 1303 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 147:
#line 615 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("connect-timeout", n);
}
#line 1312 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 148:
#line 620 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1320 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 149:
#line 622 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr cp(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("contact-points", cp);
    ctx.leave();
}
#line 1330 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 150:
#line 628 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1338 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 151:
#line 630 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr ks(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("keyspace", ks);
    ctx.leave();
}
#line 1348 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 152:
#line 637 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("mac-sources", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.MAC_SOURCES);
}
#line 1359 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 153:
#line 642 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1368 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 158:
#line 655 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1377 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 159:
#line 660 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr duid(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1386 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 160:
#line 665 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 1397 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 161:
#line 670 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1406 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 167:
#line 684 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 1415 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 168:
#line 689 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr flex_id(new StringElement("flex-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(flex_id);
}
#line 1424 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 169:
#line 696 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay-supplied-options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1435 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 170:
#line 701 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1444 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 171:
#line 706 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 1455 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 172:
#line 711 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1464 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 177:
#line 724 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1474 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 178:
#line 728 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1484 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 179:
#line 734 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1494 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 180:
#line 738 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 1504 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 186:
#line 753 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1512 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 187:
#line 755 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr lib(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 1522 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 188:
#line 761 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1530 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 189:
#line 763 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1539 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 190:
#line 769 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.EXPIRED_LEASES_PROCESSING);
}
#line 1550 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 191:
#line 774 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // No expired lease parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1560 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 200:
#line 792 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 1569 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 201:
#line 797 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 1578 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 202:
#line 802 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 1587 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 203:
#line 807 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 1596 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 204:
#line 812 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 1605 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 205:
#line 817 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 1614 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 206:
#line 825 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet6", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET6);
}
#line 1625 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 207:
#line 830 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1634 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 212:
#line 850 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1644 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 213:
#line 854 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Once we reached this place, the subnet parsing is now complete.
    // If we want to, we can implement default values here.
    // In particular we can do things like this:
    // if (!ctx.stack_.back()->get("interface")) {
    //     ctx.stack_.back()->set("interface", StringElement("loopback"));
    // }
    //
    // We can also stack up one level (Dhcp6) and copy over whatever
    // global parameters we want to:
    // if (!ctx.stack_.back()->get("renew-timer")) {
    //     ElementPtr renew = ctx_stack_[...].get("renew-timer");
    //     if (renew) {
    //         ctx.stack_.back()->set("renew-timer", renew);
    //     }
    // }

    // The subnet subnet6 parameter is required
    ctx.require("subnet", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1670 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 214:
#line 876 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the subnet6 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1680 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 215:
#line 880 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The subnet subnet6 parameter is required
    ctx.require("subnet", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 1690 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 235:
#line 911 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1698 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 236:
#line 913 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr subnet(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 1708 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 237:
#line 919 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1716 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 238:
#line 921 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 1726 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 239:
#line 927 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1734 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 240:
#line 929 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface-id", iface);
    ctx.leave();
}
#line 1744 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 241:
#line 935 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.CLIENT_CLASS);
}
#line 1752 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 242:
#line 937 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr cls(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 1762 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 243:
#line 943 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.RESERVATION_MODE);
}
#line 1770 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 244:
#line 945 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("reservation-mode", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1779 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 245:
#line 950 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("disabled", ctx.loc2pos(yystack_[0].location))); }
#line 1785 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 246:
#line 951 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("out-of-pool", ctx.loc2pos(yystack_[0].location))); }
#line 1791 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 247:
#line 952 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("all", ctx.loc2pos(yystack_[0].location))); }
#line 1797 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 248:
#line 955 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr id(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 1806 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 249:
#line 960 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr rc(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rapid-commit", rc);
}
#line 1815 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 250:
#line 969 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 1826 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 251:
#line 974 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1835 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 252:
#line 982 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1844 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 253:
#line 985 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1852 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 258:
#line 1001 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1862 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 259:
#line 1005 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1874 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 260:
#line 1016 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1884 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 261:
#line 1020 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 1896 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 275:
#line 1050 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr code(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 1905 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 277:
#line 1057 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1913 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 278:
#line 1059 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 1923 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 279:
#line 1065 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1931 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 280:
#line 1067 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 1941 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 281:
#line 1073 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1949 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 282:
#line 1075 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr space(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 1959 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 284:
#line 1083 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1967 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 285:
#line 1085 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr encap(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 1977 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 286:
#line 1091 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr array(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 1986 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 287:
#line 1100 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 1997 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 288:
#line 1105 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2006 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 293:
#line 1124 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2016 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 294:
#line 1128 "dhcp6_parser.yy" // lalr1.cc:859
    {
    /// @todo: the code or name parameters are required.
    ctx.stack_.pop_back();
}
#line 2025 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 295:
#line 1136 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2035 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 296:
#line 1140 "dhcp6_parser.yy" // lalr1.cc:859
    {
    /// @todo: the code or name parameters are required.
    // parsing completed
}
#line 2044 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 309:
#line 1171 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2052 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 310:
#line 1173 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr data(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 2062 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 313:
#line 1183 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr space(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", space);
}
#line 2071 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 314:
#line 1188 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr persist(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-send", persist);
}
#line 2080 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 315:
#line 1196 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 2091 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 316:
#line 1201 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2100 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 321:
#line 1216 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2110 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 322:
#line 1220 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2120 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 323:
#line 1226 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2130 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 324:
#line 1230 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
}
#line 2139 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 331:
#line 1245 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2147 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 332:
#line 1247 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr pool(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 2157 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 333:
#line 1253 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2165 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 334:
#line 1255 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("user-context", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2174 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 335:
#line 1263 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pd-pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.PD_POOLS);
}
#line 2185 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 336:
#line 1268 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2194 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 341:
#line 1283 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2204 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 342:
#line 1287 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The prefix, prefix len and delegated len parameters are required.
    ctx.require("prefix", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("prefix-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("delegated-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2216 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 343:
#line 1295 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the pd-pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2226 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 344:
#line 1299 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The prefix, prefix len and delegated len parameters are required.
    ctx.require("prefix", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("prefix-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("delegated-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2238 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 355:
#line 1321 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2246 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 356:
#line 1323 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix", prf);
    ctx.leave();
}
#line 2256 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 357:
#line 1329 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix-len", prf);
}
#line 2265 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 358:
#line 1334 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2273 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 359:
#line 1336 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix", prf);
    ctx.leave();
}
#line 2283 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 360:
#line 1342 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix-len", prf);
}
#line 2292 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 361:
#line 1347 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr deleg(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("delegated-len", deleg);
}
#line 2301 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 362:
#line 1355 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 2312 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 363:
#line 1360 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2321 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 368:
#line 1373 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2331 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 369:
#line 1377 "dhcp6_parser.yy" // lalr1.cc:859
    {
    /// @todo: an identifier parameter is required.
    ctx.stack_.pop_back();
}
#line 2340 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 370:
#line 1382 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2350 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 371:
#line 1386 "dhcp6_parser.yy" // lalr1.cc:859
    {
    /// @todo: an identifier parameter is required.
    // parsing completed
}
#line 2359 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 385:
#line 1411 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-addresses", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2370 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 386:
#line 1416 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2379 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 387:
#line 1421 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefixes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2390 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 388:
#line 1426 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2399 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 389:
#line 1431 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2407 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 390:
#line 1433 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr d(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 2417 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 391:
#line 1439 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2425 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 392:
#line 1441 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 2435 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 393:
#line 1447 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2443 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 394:
#line 1449 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr host(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 2453 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 395:
#line 1455 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2461 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 396:
#line 1457 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flex-id", hw);
    ctx.leave();
}
#line 2471 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 397:
#line 1463 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2482 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 398:
#line 1468 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2491 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 399:
#line 1476 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 2502 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 400:
#line 1481 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2511 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 401:
#line 1486 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2519 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 402:
#line 1488 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr ip(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", ip);
    ctx.leave();
}
#line 2529 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 403:
#line 1497 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 2540 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 404:
#line 1502 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2549 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 407:
#line 1511 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2559 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 408:
#line 1515 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The name client class parameter is required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2569 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 418:
#line 1537 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2577 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 419:
#line 1539 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr test(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 2587 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 420:
#line 1548 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-id", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SERVER_ID);
}
#line 2598 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 421:
#line 1553 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The type parameter is required.
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2609 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 431:
#line 1573 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.DUID_TYPE);
}
#line 2617 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 432:
#line 1575 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("type", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2626 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 433:
#line 1580 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("LLT", ctx.loc2pos(yystack_[0].location))); }
#line 2632 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 434:
#line 1581 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("EN", ctx.loc2pos(yystack_[0].location))); }
#line 2638 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 435:
#line 1582 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("LL", ctx.loc2pos(yystack_[0].location))); }
#line 2644 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 436:
#line 1585 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr htype(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("htype", htype);
}
#line 2653 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 437:
#line 1590 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2661 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 438:
#line 1592 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr id(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("identifier", id);
    ctx.leave();
}
#line 2671 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 439:
#line 1598 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("time", time);
}
#line 2680 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 440:
#line 1603 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enterprise-id", time);
}
#line 2689 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 441:
#line 1610 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 2698 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 442:
#line 1617 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 2709 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 443:
#line 1622 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2718 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 448:
#line 1635 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2726 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 449:
#line 1637 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr stype(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 2736 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 450:
#line 1643 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2744 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 451:
#line 1645 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 2754 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 452:
#line 1653 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 2765 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 453:
#line 1658 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2776 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 454:
#line 1665 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2786 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 455:
#line 1669 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2796 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 473:
#line 1696 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 2805 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 474:
#line 1701 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2813 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 475:
#line 1703 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("qualifying-suffix", s);
    ctx.leave();
}
#line 2823 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 476:
#line 1709 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2831 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 477:
#line 1711 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 2841 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 478:
#line 1717 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 2850 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 479:
#line 1722 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2858 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 480:
#line 1724 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 2868 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 481:
#line 1730 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 2877 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 482:
#line 1735 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 2886 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 483:
#line 1740 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 2894 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 484:
#line 1742 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2903 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 485:
#line 1748 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 2909 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 486:
#line 1749 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 2915 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 487:
#line 1752 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NCR_FORMAT);
}
#line 2923 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 488:
#line 1754 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 2933 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 489:
#line 1760 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-include-fqdn", b);
}
#line 2942 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 490:
#line 1765 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-no-update", b);
}
#line 2951 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 491:
#line 1770 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-client-update", b);
}
#line 2960 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 492:
#line 1775 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 2968 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 493:
#line 1777 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("replace-client-name", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2977 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 494:
#line 1783 "dhcp6_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("when-present", ctx.loc2pos(yystack_[0].location))); 
      }
#line 2985 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 495:
#line 1786 "dhcp6_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location)));
      }
#line 2993 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 496:
#line 1789 "dhcp6_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("always", ctx.loc2pos(yystack_[0].location)));
      }
#line 3001 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 497:
#line 1792 "dhcp6_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("when-not-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 3009 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 498:
#line 1795 "dhcp6_parser.yy" // lalr1.cc:859
    {
      error(yystack_[0].location, "boolean values for the replace-client-name are "
                "no longer supported");
      }
#line 3018 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 499:
#line 1801 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3026 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 500:
#line 1803 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("generated-prefix", s);
    ctx.leave();
}
#line 3036 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 501:
#line 1811 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3044 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 502:
#line 1813 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("Dhcp4", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3053 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 503:
#line 1818 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3061 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 504:
#line 1820 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("DhcpDdns", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3070 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 505:
#line 1825 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3078 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 506:
#line 1827 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("Control-agent", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3087 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 507:
#line 1838 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Logging", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.LOGGING);
}
#line 3098 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 508:
#line 1843 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3107 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 512:
#line 1860 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 3118 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 513:
#line 1865 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3127 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 516:
#line 1877 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 3137 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 517:
#line 1881 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 3145 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 525:
#line 1896 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr dl(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 3154 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 526:
#line 1901 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3162 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 527:
#line 1903 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 3172 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 528:
#line 1909 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 3183 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 529:
#line 1914 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3192 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 532:
#line 1923 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3202 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 533:
#line 1927 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 3210 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 540:
#line 1941 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3218 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 541:
#line 1943 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 3228 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 542:
#line 1949 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr flush(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 3237 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 543:
#line 1954 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr maxsize(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 3246 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 544:
#line 1959 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr maxver(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 3255 "dhcp6_parser.cc" // lalr1.cc:859
    break;


#line 3259 "dhcp6_parser.cc" // lalr1.cc:859
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
  Dhcp6Parser::error (const syntax_error& yyexc)
  {
    error (yyexc.location, yyexc.what());
  }

  // Generate an error message.
  std::string
  Dhcp6Parser::yysyntax_error_ (state_type yystate, const symbol_type& yyla) const
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


  const short int Dhcp6Parser::yypact_ninf_ = -509;

  const signed char Dhcp6Parser::yytable_ninf_ = -1;

  const short int
  Dhcp6Parser::yypact_[] =
  {
     107,  -509,  -509,  -509,  -509,  -509,  -509,  -509,  -509,  -509,
    -509,  -509,  -509,  -509,    30,    20,    26,    37,    68,    75,
      82,    85,    95,   118,   124,   140,   183,   200,  -509,  -509,
    -509,  -509,  -509,  -509,  -509,  -509,  -509,  -509,  -509,  -509,
    -509,  -509,  -509,  -509,  -509,  -509,  -509,  -509,  -509,  -509,
    -509,  -509,  -509,  -509,  -509,  -509,  -509,  -509,  -509,  -509,
    -509,  -509,  -509,  -509,    20,  -111,    18,    27,    97,    19,
      -2,    32,    86,   188,    58,    73,   -27,    89,  -509,   231,
     254,   263,   251,   291,  -509,  -509,  -509,  -509,  -509,   292,
    -509,    29,  -509,  -509,  -509,  -509,  -509,  -509,  -509,  -509,
    -509,   298,   305,   320,   321,   322,  -509,  -509,  -509,  -509,
    -509,  -509,  -509,  -509,  -509,  -509,   323,  -509,  -509,  -509,
     141,  -509,  -509,  -509,  -509,  -509,  -509,  -509,  -509,  -509,
    -509,  -509,  -509,  -509,  -509,  -509,  -509,  -509,  -509,  -509,
    -509,  -509,  -509,  -509,   324,   142,  -509,  -509,  -509,  -509,
    -509,  -509,  -509,  -509,  -509,   325,   326,  -509,  -509,  -509,
    -509,  -509,  -509,  -509,  -509,  -509,   206,  -509,  -509,  -509,
    -509,  -509,  -509,  -509,  -509,  -509,  -509,  -509,  -509,  -509,
    -509,  -509,  -509,  -509,   208,  -509,  -509,  -509,  -509,   327,
    -509,   329,   330,  -509,  -509,  -509,   210,  -509,  -509,  -509,
    -509,  -509,  -509,  -509,  -509,  -509,  -509,  -509,  -509,  -509,
    -509,  -509,   303,   314,  -509,  -509,  -509,  -509,  -509,  -509,
    -509,  -509,   328,  -509,  -509,   331,  -509,  -509,  -509,   333,
    -509,  -509,   332,   335,  -509,  -509,  -509,  -509,  -509,  -509,
    -509,  -509,  -509,  -509,  -509,   337,   338,  -509,  -509,  -509,
    -509,   336,   340,  -509,  -509,  -509,  -509,  -509,  -509,  -509,
    -509,  -509,  -509,   212,  -509,  -509,  -509,   341,  -509,  -509,
     342,  -509,   343,   344,  -509,  -509,   345,   346,   347,  -509,
    -509,  -509,   214,  -509,  -509,  -509,  -509,  -509,  -509,  -509,
    -509,  -509,  -509,  -509,  -509,  -509,  -509,  -509,  -509,    20,
      20,  -509,   202,   349,   350,   351,   352,   353,  -509,    18,
    -509,   354,   355,   356,   211,   213,   215,   217,   219,   357,
     359,   361,   363,   365,   367,   368,   369,   370,   371,   227,
     372,   373,    27,  -509,   375,   228,    97,  -509,    -4,   376,
     378,   379,   380,   381,   236,   233,   384,   385,   386,   387,
      19,  -509,   388,   389,    -2,  -509,   390,   244,   392,   246,
     247,    32,  -509,   395,   396,   397,   398,   399,   400,   401,
    -509,    86,  -509,   402,   403,   259,   404,   405,   407,   260,
    -509,    58,   408,   261,   262,  -509,    73,   412,   413,   196,
    -509,   270,   414,   415,   273,   421,   275,   276,   424,   425,
     278,   279,   280,   426,   430,    89,  -509,  -509,  -509,   431,
     429,   432,    20,    20,    20,  -509,   433,   434,   437,  -509,
    -509,  -509,  -509,  -509,   440,   441,   442,   443,   444,   447,
     448,   449,   450,   451,  -509,   452,   455,  -509,   459,  -509,
    -509,  -509,  -509,  -509,  -509,   457,   435,  -509,  -509,  -509,
     461,   462,   287,   306,   319,  -509,  -509,    93,   334,   465,
     464,  -509,   339,   466,  -509,   348,  -509,   358,  -509,  -509,
    -509,   459,   459,   459,   360,   362,   364,   366,  -509,   374,
     377,  -509,   382,   383,   391,  -509,  -509,   393,  -509,  -509,
    -509,   394,    20,  -509,  -509,   406,   409,  -509,   410,  -509,
    -509,   168,   411,  -509,  -509,  -509,    57,   416,  -509,    20,
      27,   419,  -509,  -509,  -509,    97,   112,   112,   467,   468,
     469,   -44,    20,   -30,    36,   471,    98,    24,    74,    89,
    -509,  -509,   475,  -509,    -4,   473,   474,  -509,  -509,  -509,
    -509,  -509,  -509,  -509,  -509,   476,   417,  -509,  -509,  -509,
    -509,  -509,  -509,  -509,  -509,  -509,  -509,  -509,  -509,  -509,
    -509,  -509,  -509,  -509,  -509,  -509,  -509,  -509,  -509,  -509,
    -509,  -509,  -509,  -509,  -509,  -509,  -509,  -509,  -509,  -509,
    -509,  -509,   216,  -509,   218,  -509,  -509,   224,  -509,  -509,
    -509,  -509,   478,   481,   482,   483,   484,  -509,  -509,  -509,
     225,  -509,  -509,  -509,  -509,  -509,  -509,  -509,  -509,  -509,
    -509,  -509,  -509,  -509,   226,  -509,   485,   487,  -509,  -509,
     486,   490,  -509,  -509,   488,   492,  -509,  -509,  -509,   126,
    -509,  -509,  -509,   493,  -509,  -509,  -509,   235,  -509,  -509,
    -509,  -509,   297,  -509,   495,   499,  -509,   500,   501,   502,
     503,   505,   507,   232,  -509,  -509,  -509,  -509,  -509,  -509,
    -509,  -509,  -509,   509,   511,   514,  -509,  -509,   255,  -509,
    -509,  -509,  -509,  -509,  -509,  -509,  -509,   257,  -509,  -509,
    -509,   258,   418,   420,  -509,  -509,   497,   516,  -509,  -509,
     515,   517,  -509,  -509,   519,   520,  -509,  -509,   518,  -509,
     524,   419,  -509,  -509,   525,   526,   530,   531,   304,   422,
     423,   427,   428,   532,   533,   112,  -509,  -509,    19,  -509,
     467,    58,  -509,   468,    73,  -509,   469,   -44,  -509,  -509,
     -30,  -509,    36,  -509,   -27,  -509,   471,   436,   438,   439,
     445,   446,   453,    98,  -509,   534,   535,   454,   456,   458,
      24,  -509,   536,   538,    74,  -509,  -509,  -509,   540,   544,
    -509,    -2,  -509,   473,    32,  -509,   474,    86,  -509,   476,
     545,  -509,   491,  -509,   272,   460,   463,   470,  -509,  -509,
    -509,  -509,  -509,   472,   477,  -509,   265,  -509,   542,  -509,
     543,  -509,  -509,  -509,  -509,   266,  -509,  -509,  -509,  -509,
    -509,  -509,  -509,  -509,   229,   479,  -509,  -509,  -509,  -509,
     480,   489,  -509,  -509,   494,   267,  -509,   268,  -509,   546,
    -509,   496,   541,  -509,  -509,  -509,  -509,  -509,  -509,  -509,
    -509,  -509,  -509,  -509,  -509,  -509,  -509,  -509,  -509,  -509,
    -509,  -509,  -509,  -509,  -509,  -509,  -509,  -509,  -509,  -509,
     307,  -509,    62,   541,  -509,  -509,   548,  -509,  -509,  -509,
     274,  -509,  -509,  -509,  -509,  -509,   549,   506,   551,    62,
    -509,   552,  -509,   498,  -509,   554,  -509,  -509,   313,  -509,
     -60,   554,  -509,  -509,   558,   559,   560,   277,  -509,  -509,
    -509,  -509,  -509,  -509,   561,   510,   508,   513,   -60,  -509,
     504,  -509,  -509,  -509,  -509,  -509
  };

  const unsigned short int
  Dhcp6Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,    24,    26,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     1,    43,
      36,    32,    31,    28,    29,    30,    35,     3,    33,    34,
      56,     5,    68,     7,   101,     9,   214,    11,   323,    13,
     343,    15,   370,    17,   252,    19,   260,    21,   295,    23,
     179,    25,   454,    27,    45,    39,     0,     0,     0,     0,
       0,     0,   372,     0,   262,   297,     0,     0,    47,     0,
      46,     0,     0,    40,    66,   507,   501,   503,   505,     0,
      65,     0,    58,    60,    62,    63,    64,    61,    99,   110,
     112,     0,     0,     0,     0,     0,   206,   250,   287,   152,
     169,   160,   403,   171,   190,   420,     0,   442,   452,    93,
       0,    70,    72,    73,    74,    75,    76,    78,    79,    80,
      81,    83,    82,    87,    88,    77,    85,    86,    84,    89,
      90,    91,    92,   107,     0,     0,   103,   105,   106,   407,
     315,   335,   235,   237,   239,     0,     0,   243,   241,   362,
     399,   234,   218,   219,   220,   221,     0,   216,   225,   226,
     227,   230,   232,   228,   229,   222,   223,   224,   231,   233,
     331,   333,   330,   328,     0,   325,   327,   329,   355,     0,
     358,     0,     0,   354,   350,   353,     0,   345,   347,   348,
     351,   352,   349,   397,   385,   387,   389,   391,   393,   395,
     384,   383,     0,   373,   374,   378,   379,   376,   380,   381,
     382,   377,     0,   277,   142,     0,   281,   279,   284,     0,
     273,   274,     0,   263,   264,   266,   276,   267,   268,   269,
     283,   270,   271,   272,   309,     0,     0,   307,   308,   311,
     312,     0,   298,   299,   301,   302,   303,   304,   305,   306,
     186,   188,   183,     0,   181,   184,   185,     0,   474,   476,
       0,   479,     0,     0,   483,   487,     0,     0,     0,   492,
     499,   472,     0,   456,   458,   459,   460,   461,   462,   463,
     464,   465,   466,   467,   468,   469,   470,   471,    44,     0,
       0,    37,     0,     0,     0,     0,     0,     0,    55,     0,
      57,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    69,     0,     0,     0,   102,   409,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   215,     0,     0,     0,   324,     0,     0,     0,     0,
       0,     0,   344,     0,     0,     0,     0,     0,     0,     0,
     371,     0,   253,     0,     0,     0,     0,     0,     0,     0,
     261,     0,     0,     0,     0,   296,     0,     0,     0,     0,
     180,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   455,    48,    41,     0,
       0,     0,     0,     0,     0,    59,     0,     0,     0,    94,
      95,    96,    97,    98,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   441,     0,     0,    71,     0,   109,
     104,   418,   416,   417,   415,     0,   410,   411,   413,   414,
       0,     0,     0,     0,     0,   248,   249,     0,     0,     0,
       0,   217,     0,     0,   326,     0,   357,     0,   360,   361,
     346,     0,     0,     0,     0,     0,     0,     0,   375,     0,
       0,   275,     0,     0,     0,   286,   265,     0,   313,   314,
     300,     0,     0,   182,   473,     0,     0,   478,     0,   481,
     482,     0,     0,   489,   490,   491,     0,     0,   457,     0,
       0,     0,   502,   504,   506,     0,     0,     0,   208,   254,
     289,     0,    45,     0,     0,   173,     0,     0,     0,     0,
      49,   108,     0,   408,     0,   317,   337,   236,   238,   240,
     245,   246,   247,   244,   242,   364,     0,   332,    38,   334,
     356,   359,   398,   386,   388,   390,   392,   394,   396,   278,
     143,   282,   280,   285,   310,   187,   189,   475,   477,   480,
     485,   486,   484,   488,   494,   495,   496,   497,   498,   493,
     500,    42,     0,   512,     0,   509,   511,     0,   129,   135,
     137,   139,     0,     0,     0,     0,     0,   148,   150,   128,
       0,   114,   116,   117,   118,   119,   120,   121,   122,   123,
     124,   125,   126,   127,     0,   212,     0,   209,   210,   258,
       0,   255,   256,   293,     0,   290,   291,   158,   159,     0,
     154,   156,   157,     0,   167,   168,   164,     0,   162,   165,
     166,   405,     0,   177,     0,   174,   175,     0,     0,     0,
       0,     0,     0,     0,   192,   194,   195,   196,   197,   198,
     199,   431,   437,     0,     0,     0,   430,   429,     0,   422,
     424,   427,   425,   426,   428,   448,   450,     0,   444,   446,
     447,     0,    51,     0,   412,   321,     0,   318,   319,   341,
       0,   338,   339,   368,     0,   365,   366,   401,     0,    67,
       0,     0,   508,   100,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   111,   113,     0,   207,
       0,   262,   251,     0,   297,   288,     0,     0,   153,   170,
       0,   161,     0,   404,     0,   172,     0,     0,     0,     0,
       0,     0,     0,     0,   191,     0,     0,     0,     0,     0,
       0,   421,     0,     0,     0,   443,   453,    53,     0,    52,
     419,     0,   316,     0,     0,   336,     0,   372,   363,     0,
       0,   400,     0,   510,     0,     0,     0,     0,   141,   144,
     145,   146,   147,     0,     0,   115,     0,   211,     0,   257,
       0,   292,   155,   163,   406,     0,   176,   200,   201,   202,
     203,   204,   205,   193,     0,     0,   436,   439,   440,   423,
       0,     0,   445,    50,     0,     0,   320,     0,   340,     0,
     367,     0,     0,   131,   132,   133,   134,   130,   136,   138,
     140,   149,   151,   213,   259,   294,   178,   433,   434,   435,
     432,   438,   449,   451,    54,   322,   342,   369,   402,   516,
       0,   514,     0,     0,   513,   528,     0,   526,   524,   520,
       0,   518,   522,   523,   521,   515,     0,     0,     0,     0,
     517,     0,   525,     0,   519,     0,   527,   532,     0,   530,
       0,     0,   529,   540,     0,     0,     0,     0,   534,   536,
     537,   538,   539,   531,     0,     0,     0,     0,     0,   533,
       0,   542,   543,   544,   535,   541
  };

  const short int
  Dhcp6Parser::yypgoto_[] =
  {
    -509,  -509,  -509,  -509,  -509,  -509,  -509,  -509,  -509,  -509,
    -509,  -509,  -509,  -509,  -509,     8,  -509,     9,  -509,  -509,
    -509,  -509,  -509,  -509,     0,  -509,  -306,  -509,  -509,  -509,
     -66,  -509,  -509,  -509,   249,  -509,  -509,  -509,  -509,    59,
     239,   -67,   -52,   -51,   -49,  -509,  -509,  -509,  -509,  -509,
      52,   237,  -509,  -509,  -509,  -509,  -509,  -509,  -509,    55,
    -139,  -509,  -509,  -509,  -509,  -509,  -509,  -509,  -509,  -509,
    -509,   -74,  -509,  -508,  -509,  -509,  -509,  -509,  -509,  -509,
    -509,  -509,  -509,  -509,  -150,  -499,  -509,  -509,  -509,  -509,
    -152,  -509,  -509,  -509,  -509,  -509,  -509,  -509,  -509,  -155,
    -509,  -509,  -509,  -151,   193,  -509,  -509,  -509,  -509,  -509,
    -509,  -509,  -159,  -509,  -509,  -509,  -509,  -509,  -509,  -509,
    -509,  -509,  -509,  -135,  -509,  -509,  -509,  -132,   238,  -509,
    -509,  -509,  -509,  -509,  -509,  -502,  -509,  -509,  -509,  -509,
    -509,  -509,   521,  -509,  -509,  -509,  -509,  -509,  -131,  -509,
    -509,  -509,  -130,  -509,   220,  -509,   -68,  -509,  -509,  -509,
    -509,  -509,   -54,  -509,  -509,  -509,  -509,  -509,   -57,  -509,
    -509,  -509,  -133,  -509,  -509,  -509,  -129,  -509,   222,  -509,
    -509,  -509,  -509,  -509,  -509,  -509,  -509,  -509,  -509,  -509,
    -165,  -509,  -509,  -509,  -162,   248,  -509,  -509,   -55,  -509,
    -509,  -509,  -509,  -509,  -166,  -509,  -509,  -509,  -161,   245,
    -509,  -509,  -509,  -509,  -509,  -509,  -509,  -509,  -509,  -509,
    -509,  -158,  -509,  -509,  -509,  -153,  -509,   241,  -509,  -509,
    -509,  -509,  -509,  -509,  -509,  -509,  -509,  -509,  -509,  -509,
    -509,  -509,  -509,  -509,  -509,  -509,  -509,  -509,  -509,  -509,
    -509,  -509,    81,  -509,  -509,  -509,  -509,  -509,  -509,  -134,
    -509,  -509,  -509,  -509,  -509,  -509,  -509,  -509,  -509,  -509,
    -509,  -509,  -137,  -509,  -509,  -509,  -509,  -509,  -509,  -509,
    -509,    90,   221,  -509,  -509,  -509,  -509,  -509,  -509,  -509,
    -509,  -509,  -509,  -509,  -509,  -509,  -509,  -509,  -509,  -509,
    -509,  -509,  -509,  -509,  -509,  -509,  -509,  -509,  -509,  -509,
    -509,  -509,  -509,  -509,  -509,   -83,  -509,  -509,  -509,  -232,
    -509,  -509,  -246,  -509,  -509,  -509,  -509,  -509,  -509,  -257,
    -509,  -509,  -273,  -509,  -509,  -509,  -509,  -509
  };

  const short int
  Dhcp6Parser::yydefgoto_[] =
  {
      -1,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    78,    37,    38,    65,   549,
      82,    83,    39,    64,    79,    80,   531,   682,   758,   759,
     119,    41,    66,    91,    92,    93,   303,    43,    67,   120,
     121,   122,   123,   124,   125,   126,   127,   311,    45,    68,
     145,   146,   147,   334,   148,   128,   312,   129,   313,   600,
     601,   602,   704,   827,   603,   705,   604,   706,   605,   707,
     606,   231,   374,   608,   609,   610,   611,   612,   713,   613,
     714,   130,   322,   629,   630,   631,   632,   131,   324,   637,
     638,   639,   640,   132,   323,   133,   326,   644,   645,   646,
     734,    61,    76,   263,   264,   265,   387,   266,   388,   134,
     327,   653,   654,   655,   656,   657,   658,   659,   660,   135,
     319,   616,   617,   618,   718,    47,    69,   166,   167,   168,
     341,   169,   342,   170,   343,   171,   347,   172,   346,   543,
     173,   174,   136,   320,    55,    73,   620,   621,   622,   721,
      57,    74,   232,   233,   234,   235,   236,   237,   238,   373,
     239,   377,   240,   376,   241,   242,   378,   243,   137,   321,
     624,   625,   626,   724,    59,    75,   251,   252,   253,   254,
     255,   382,   256,   257,   258,   259,   176,   339,   686,   687,
     688,   761,    49,    70,   184,   185,   186,   352,   187,   353,
     177,   340,   690,   691,   692,   764,    51,    71,   196,   197,
     198,   356,   199,   200,   358,   201,   202,   178,   348,   694,
     695,   696,   767,    53,    72,   212,   213,   214,   215,   364,
     216,   365,   217,   366,   218,   367,   219,   368,   220,   369,
     221,   363,   179,   349,   698,   770,   138,   325,   642,   338,
     445,   446,   447,   448,   449,   532,   139,   328,   668,   669,
     670,   745,   840,   671,   672,   746,   673,   674,   140,   141,
     330,   677,   678,   679,   752,   680,   753,   142,   331,    63,
      77,   282,   283,   284,   285,   392,   286,   393,   287,   288,
     395,   289,   290,   291,   398,   572,   292,   399,   293,   294,
     295,   296,   403,   579,   297,   404,    94,   305,    95,   306,
      96,   307,    97,   304,   584,   585,   586,   700,   850,   851,
     852,   860,   861,   862,   863,   868,   864,   866,   878,   879,
     880,   887,   888,   889,   894,   890,   891,   892
  };

  const unsigned short int
  Dhcp6Parser::yytable_[] =
  {
      90,   248,   162,   161,   182,   193,   210,   249,   230,   247,
     262,   281,   175,   183,   194,   211,   195,   163,   164,   667,
     165,   250,   641,    36,   636,    29,   149,    30,    84,    31,
      28,   627,   309,    40,   108,   224,   108,   310,    98,    81,
     661,    99,   100,   149,    42,   627,   634,   180,   635,   593,
     101,   102,   103,   104,   181,   260,   261,   108,   101,   102,
     103,   104,   105,   106,   107,   108,   441,   150,   883,   151,
     108,   884,   885,   886,   223,    44,   152,   153,   154,   155,
     156,   157,    46,   188,   189,   190,   191,   192,   181,    48,
     158,   159,    50,   109,   110,   111,   112,   224,   160,   225,
     226,   224,    52,   227,   228,   229,   628,   158,   113,   143,
     144,   114,   224,   244,   225,   226,   245,   246,   115,   662,
     663,   664,   665,    89,   108,    54,   116,   117,   588,   727,
     118,    56,   728,   589,   590,   591,   592,   593,   594,   595,
     596,   597,   598,    85,   332,   336,    89,    58,    89,   333,
     337,   224,    86,    87,    88,   203,   540,   541,   542,   204,
     205,   206,   207,   208,   209,   552,   553,   554,    89,    89,
      32,    33,    34,    35,    89,   675,   676,    89,   574,   575,
     576,   577,    89,   647,   648,   649,   650,   651,   652,   855,
      60,   856,   857,   267,   268,   269,   270,   271,   272,   273,
     274,   275,   276,   277,   278,   279,   280,    62,    89,   350,
     578,   354,    89,   361,   351,   389,   355,   405,   362,   332,
     390,   701,   406,    89,   699,   107,   702,   336,   715,   715,
     794,   636,   703,   716,   717,   743,    89,   298,   730,    89,
     744,   731,   667,    90,     1,     2,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    13,   299,   750,   301,
     754,   405,    89,   751,   443,   755,   756,   300,   350,   389,
     354,   361,   442,   833,   836,   845,   846,   869,   260,   261,
     898,   444,   870,   162,   161,   899,   570,   571,   182,   823,
     824,   825,   826,   175,   302,   193,   308,   183,   163,   164,
     732,   165,   314,   733,   194,   210,   195,   407,   408,   315,
     853,   370,   248,   854,   211,   230,   881,   371,   249,   882,
     247,   837,   838,   839,   316,   317,   318,   329,   335,   344,
     345,   357,   250,   359,   360,   375,   372,   379,   381,   281,
     380,   383,   384,   386,   385,   391,   394,   396,   397,   400,
     401,   402,   409,   410,   411,   412,   413,   414,   416,   417,
     418,   424,   419,   425,   420,   426,   421,   427,   422,   428,
     423,   429,   430,   431,   432,   433,   435,   436,   434,   438,
     450,   439,   451,   452,   453,   454,   456,   455,   457,   458,
     459,   460,   462,   463,   465,   466,   467,   468,   469,   471,
     472,   473,   474,   475,   476,   477,   479,   480,   482,   483,
     481,   484,   487,   485,   488,   489,   491,   492,   495,   496,
     512,   513,   514,   494,   497,   498,   499,   500,   501,   502,
     506,   503,   504,   505,   507,   509,   510,   537,   534,   511,
     515,   516,   607,   607,   517,   518,   519,   520,   521,   522,
     599,   599,   523,   524,   525,   778,   538,   526,   527,   528,
     443,   666,   529,   281,   530,   533,   535,   536,   442,   539,
     545,   546,   548,    30,   615,   619,   623,   444,   643,   683,
     685,   689,   708,   693,   544,   709,   710,   711,   712,   547,
     720,   719,   722,   723,   725,   726,   822,   697,   550,   729,
     566,   735,   736,   762,   737,   738,   739,   740,   551,   741,
     555,   742,   556,   747,   557,   748,   558,   581,   749,   763,
     766,   765,   633,   769,   559,   768,   771,   560,   772,   774,
     775,   573,   561,   562,   776,   777,   783,   784,   804,   805,
     810,   563,   811,   564,   565,   583,   813,   814,   849,   821,
     834,   835,   867,   871,   847,   873,   567,   875,   415,   568,
     569,   877,   895,   896,   897,   900,   580,   587,   757,   582,
     760,   437,   614,   440,   780,   779,   785,   792,   793,   782,
     781,   796,   493,   795,   803,   787,   786,   797,   461,   798,
     799,   788,   789,   791,   222,   790,   800,   801,   816,   815,
     818,   486,   464,   817,   802,   806,   470,   807,   490,   808,
     828,   820,   478,   829,   819,   684,   809,   812,   773,   681,
     830,   865,   831,   874,   893,   904,   508,   832,     0,   841,
     842,     0,     0,     0,     0,     0,     0,     0,     0,   843,
       0,   607,     0,     0,   844,     0,   848,     0,   876,   599,
     248,   162,   161,     0,   905,   230,   249,   872,   247,   902,
       0,   175,     0,   901,   903,     0,   163,   164,   262,   165,
     250,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   666,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   182,     0,     0,   193,     0,
       0,   210,     0,     0,   183,     0,     0,   194,     0,   195,
     211,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   859,     0,
       0,     0,     0,     0,     0,     0,   858,     0,     0,     0,
       0,     0,     0,     0,     0,   859,     0,     0,     0,     0,
       0,     0,     0,   858
  };

  const short int
  Dhcp6Parser::yycheck_[] =
  {
      66,    75,    69,    69,    70,    71,    72,    75,    74,    75,
      76,    77,    69,    70,    71,    72,    71,    69,    69,   527,
      69,    75,   524,    15,   523,     5,     7,     7,    10,     9,
       0,    75,     3,     7,    38,    39,    38,     8,    11,   150,
      16,    14,    15,     7,     7,    75,    76,    49,    78,    25,
      31,    32,    33,    34,    56,    82,    83,    38,    31,    32,
      33,    34,    35,    36,    37,    38,    70,    48,   128,    50,
      38,   131,   132,   133,    16,     7,    57,    58,    59,    60,
      61,    62,     7,    51,    52,    53,    54,    55,    56,     7,
      71,    72,     7,    66,    67,    68,    69,    39,    79,    41,
      42,    39,     7,    45,    46,    47,   150,    71,    81,    12,
      13,    84,    39,    40,    41,    42,    43,    44,    91,    95,
      96,    97,    98,   150,    38,     7,    99,   100,    16,     3,
     103,     7,     6,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,   125,     3,     3,   150,     7,   150,     8,
       8,    39,   134,   135,   136,    69,    63,    64,    65,    73,
      74,    75,    76,    77,    78,   471,   472,   473,   150,   150,
     150,   151,   152,   153,   150,   101,   102,   150,   121,   122,
     123,   124,   150,    85,    86,    87,    88,    89,    90,   127,
       7,   129,   130,   104,   105,   106,   107,   108,   109,   110,
     111,   112,   113,   114,   115,   116,   117,     7,   150,     3,
     153,     3,   150,     3,     8,     3,     8,     3,     8,     3,
       8,     3,     8,   150,     8,    37,     8,     3,     3,     3,
     732,   730,     8,     8,     8,     3,   150,     6,     3,   150,
       8,     6,   750,   309,   137,   138,   139,   140,   141,   142,
     143,   144,   145,   146,   147,   148,   149,     3,     3,     8,
       3,     3,   150,     8,   338,     8,     8,     4,     3,     3,
       3,     3,   338,     8,     8,     8,     8,     3,    82,    83,
       3,   338,     8,   350,   350,     8,   118,   119,   354,    17,
      18,    19,    20,   350,     3,   361,     4,   354,   350,   350,
       3,   350,     4,     6,   361,   371,   361,   299,   300,     4,
       3,     8,   386,     6,   371,   381,     3,     3,   386,     6,
     386,    92,    93,    94,     4,     4,     4,     4,     4,     4,
       4,     4,   386,     4,     4,     4,     8,     4,     3,   405,
       8,     4,     4,     3,     8,     4,     4,     4,     4,     4,
       4,     4,   150,     4,     4,     4,     4,     4,     4,     4,
       4,     4,   151,     4,   151,     4,   151,     4,   151,     4,
     151,     4,     4,     4,     4,     4,     4,     4,   151,     4,
       4,   153,     4,     4,     4,     4,   153,   151,     4,     4,
       4,     4,     4,     4,     4,   151,     4,   151,   151,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
     151,     4,     4,   153,   153,   153,     4,     4,     4,     4,
     412,   413,   414,   153,   151,     4,   151,   151,     4,     4,
       4,   153,   153,   153,     4,     4,     7,   150,     3,     7,
       7,     7,   516,   517,     7,     5,     5,     5,     5,     5,
     516,   517,     5,     5,     5,   151,   150,     7,     7,     7,
     534,   527,     7,   529,     5,     8,     5,     5,   534,   150,
       5,     7,   463,     7,     7,     7,     7,   534,     7,     4,
       7,     7,     4,     7,   150,     4,     4,     4,     4,   150,
       3,     6,     6,     3,     6,     3,     5,    80,   150,     6,
     492,     6,     3,     6,     4,     4,     4,     4,   150,     4,
     150,     4,   150,     4,   150,     4,   150,   509,     4,     3,
       3,     6,   522,     3,   150,     6,     8,   150,     4,     4,
       4,   120,   150,   150,     4,     4,     4,     4,     4,     4,
       4,   150,     4,   150,   150,   126,     6,     3,     7,     4,
       8,     8,     4,     4,     8,     4,   150,     5,   309,   150,
     150,     7,     4,     4,     4,     4,   150,   515,   150,   510,
     150,   332,   517,   336,   151,   153,   715,   727,   730,   151,
     153,   736,   389,   734,   743,   720,   718,   151,   350,   151,
     151,   721,   723,   726,    73,   724,   151,   151,   763,   761,
     766,   381,   354,   764,   151,   151,   361,   151,   386,   151,
     150,   769,   371,   150,   767,   534,   750,   754,   701,   529,
     150,   853,   150,   869,   881,   898,   405,   150,    -1,   150,
     150,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   150,
      -1,   715,    -1,    -1,   150,    -1,   150,    -1,   150,   715,
     724,   718,   718,    -1,   150,   721,   724,   151,   724,   151,
      -1,   718,    -1,   153,   151,    -1,   718,   718,   734,   718,
     724,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   750,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   761,    -1,    -1,   764,    -1,
      -1,   767,    -1,    -1,   761,    -1,    -1,   764,    -1,   764,
     767,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   852,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   852,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   869,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   869
  };

  const unsigned short int
  Dhcp6Parser::yystos_[] =
  {
       0,   137,   138,   139,   140,   141,   142,   143,   144,   145,
     146,   147,   148,   149,   155,   156,   157,   158,   159,   160,
     161,   162,   163,   164,   165,   166,   167,   168,     0,     5,
       7,     9,   150,   151,   152,   153,   169,   170,   171,   176,
       7,   185,     7,   191,     7,   202,     7,   279,     7,   346,
       7,   360,     7,   377,     7,   298,     7,   304,     7,   328,
       7,   255,     7,   433,   177,   172,   186,   192,   203,   280,
     347,   361,   378,   299,   305,   329,   256,   434,   169,   178,
     179,   150,   174,   175,    10,   125,   134,   135,   136,   150,
     184,   187,   188,   189,   460,   462,   464,   466,    11,    14,
      15,    31,    32,    33,    34,    35,    36,    37,    38,    66,
      67,    68,    69,    81,    84,    91,    99,   100,   103,   184,
     193,   194,   195,   196,   197,   198,   199,   200,   209,   211,
     235,   241,   247,   249,   263,   273,   296,   322,   400,   410,
     422,   423,   431,    12,    13,   204,   205,   206,   208,     7,
      48,    50,    57,    58,    59,    60,    61,    62,    71,    72,
      79,   184,   195,   196,   197,   198,   281,   282,   283,   285,
     287,   289,   291,   294,   295,   322,   340,   354,   371,   396,
      49,    56,   184,   322,   348,   349,   350,   352,    51,    52,
      53,    54,    55,   184,   322,   352,   362,   363,   364,   366,
     367,   369,   370,    69,    73,    74,    75,    76,    77,    78,
     184,   322,   379,   380,   381,   382,   384,   386,   388,   390,
     392,   394,   296,    16,    39,    41,    42,    45,    46,    47,
     184,   225,   306,   307,   308,   309,   310,   311,   312,   314,
     316,   318,   319,   321,    40,    43,    44,   184,   225,   310,
     316,   330,   331,   332,   333,   334,   336,   337,   338,   339,
      82,    83,   184,   257,   258,   259,   261,   104,   105,   106,
     107,   108,   109,   110,   111,   112,   113,   114,   115,   116,
     117,   184,   435,   436,   437,   438,   440,   442,   443,   445,
     446,   447,   450,   452,   453,   454,   455,   458,     6,     3,
       4,     8,     3,   190,   467,   461,   463,   465,     4,     3,
       8,   201,   210,   212,     4,     4,     4,     4,     4,   274,
     297,   323,   236,   248,   242,   401,   250,   264,   411,     4,
     424,   432,     3,     8,   207,     4,     3,     8,   403,   341,
     355,   284,   286,   288,     4,     4,   292,   290,   372,   397,
       3,     8,   351,   353,     3,     8,   365,     4,   368,     4,
       4,     3,     8,   395,   383,   385,   387,   389,   391,   393,
       8,     3,     8,   313,   226,     4,   317,   315,   320,     4,
       8,     3,   335,     4,     4,     8,     3,   260,   262,     3,
       8,     4,   439,   441,     4,   444,     4,     4,   448,   451,
       4,     4,     4,   456,   459,     3,     8,   169,   169,   150,
       4,     4,     4,     4,     4,   188,     4,     4,     4,   151,
     151,   151,   151,   151,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,   151,     4,     4,   194,     4,   153,
     205,    70,   184,   225,   322,   404,   405,   406,   407,   408,
       4,     4,     4,     4,     4,   151,   153,     4,     4,     4,
       4,   282,     4,     4,   349,     4,   151,     4,   151,   151,
     363,     4,     4,     4,     4,     4,     4,     4,   381,     4,
       4,   151,     4,     4,     4,   153,   308,     4,   153,   153,
     332,     4,     4,   258,   153,     4,     4,   151,     4,   151,
     151,     4,     4,   153,   153,   153,     4,     4,   436,     4,
       7,     7,   169,   169,   169,     7,     7,     7,     5,     5,
       5,     5,     5,     5,     5,     5,     7,     7,     7,     7,
       5,   180,   409,     8,     3,     5,     5,   150,   150,   150,
      63,    64,    65,   293,   150,     5,     7,   150,   171,   173,
     150,   150,   180,   180,   180,   150,   150,   150,   150,   150,
     150,   150,   150,   150,   150,   150,   169,   150,   150,   150,
     118,   119,   449,   120,   121,   122,   123,   124,   153,   457,
     150,   169,   193,   126,   468,   469,   470,   204,    16,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,   184,
     213,   214,   215,   218,   220,   222,   224,   225,   227,   228,
     229,   230,   231,   233,   213,     7,   275,   276,   277,     7,
     300,   301,   302,     7,   324,   325,   326,    75,   150,   237,
     238,   239,   240,   178,    76,    78,   239,   243,   244,   245,
     246,   289,   402,     7,   251,   252,   253,    85,    86,    87,
      88,    89,    90,   265,   266,   267,   268,   269,   270,   271,
     272,    16,    95,    96,    97,    98,   184,   227,   412,   413,
     414,   417,   418,   420,   421,   101,   102,   425,   426,   427,
     429,   435,   181,     4,   406,     7,   342,   343,   344,     7,
     356,   357,   358,     7,   373,   374,   375,    80,   398,     8,
     471,     3,     8,     8,   216,   219,   221,   223,     4,     4,
       4,     4,     4,   232,   234,     3,     8,     8,   278,     6,
       3,   303,     6,     3,   327,     6,     3,     3,     6,     6,
       3,     6,     3,     6,   254,     6,     3,     4,     4,     4,
       4,     4,     4,     3,     8,   415,   419,     4,     4,     4,
       3,     8,   428,   430,     3,     8,     8,   150,   182,   183,
     150,   345,     6,     3,   359,     6,     3,   376,     6,     3,
     399,     8,     4,   469,     4,     4,     4,     4,   151,   153,
     151,   153,   151,     4,     4,   214,   281,   277,   306,   302,
     330,   326,   238,   244,   289,   257,   253,   151,   151,   151,
     151,   151,   151,   266,     4,     4,   151,   151,   151,   413,
       4,     4,   426,     6,     3,   348,   344,   362,   358,   379,
     375,     4,     5,    17,    18,    19,    20,   217,   150,   150,
     150,   150,   150,     8,     8,     8,     8,    92,    93,    94,
     416,   150,   150,   150,   150,     8,     8,     8,   150,     7,
     472,   473,   474,     3,     6,   127,   129,   130,   184,   225,
     475,   476,   477,   478,   480,   473,   481,     4,   479,     3,
       8,     4,   151,     4,   476,     5,   150,     7,   482,   483,
     484,     3,     6,   128,   131,   132,   133,   485,   486,   487,
     489,   490,   491,   483,   488,     4,     4,     4,     3,     8,
       4,   153,   151,   151,   486,   150
  };

  const unsigned short int
  Dhcp6Parser::yyr1_[] =
  {
       0,   154,   156,   155,   157,   155,   158,   155,   159,   155,
     160,   155,   161,   155,   162,   155,   163,   155,   164,   155,
     165,   155,   166,   155,   167,   155,   168,   155,   169,   169,
     169,   169,   169,   169,   169,   170,   172,   171,   173,   174,
     174,   175,   175,   177,   176,   178,   178,   179,   179,   181,
     180,   182,   182,   183,   183,   184,   186,   185,   187,   187,
     188,   188,   188,   188,   188,   188,   190,   189,   192,   191,
     193,   193,   194,   194,   194,   194,   194,   194,   194,   194,
     194,   194,   194,   194,   194,   194,   194,   194,   194,   194,
     194,   194,   194,   194,   195,   196,   197,   198,   199,   201,
     200,   203,   202,   204,   204,   205,   205,   207,   206,   208,
     210,   209,   212,   211,   213,   213,   214,   214,   214,   214,
     214,   214,   214,   214,   214,   214,   214,   214,   214,   216,
     215,   217,   217,   217,   217,   219,   218,   221,   220,   223,
     222,   224,   226,   225,   227,   228,   229,   230,   232,   231,
     234,   233,   236,   235,   237,   237,   238,   238,   239,   240,
     242,   241,   243,   243,   244,   244,   244,   245,   246,   248,
     247,   250,   249,   251,   251,   252,   252,   254,   253,   256,
     255,   257,   257,   257,   258,   258,   260,   259,   262,   261,
     264,   263,   265,   265,   266,   266,   266,   266,   266,   266,
     267,   268,   269,   270,   271,   272,   274,   273,   275,   275,
     276,   276,   278,   277,   280,   279,   281,   281,   282,   282,
     282,   282,   282,   282,   282,   282,   282,   282,   282,   282,
     282,   282,   282,   282,   282,   284,   283,   286,   285,   288,
     287,   290,   289,   292,   291,   293,   293,   293,   294,   295,
     297,   296,   299,   298,   300,   300,   301,   301,   303,   302,
     305,   304,   306,   306,   307,   307,   308,   308,   308,   308,
     308,   308,   308,   308,   309,   310,   311,   313,   312,   315,
     314,   317,   316,   318,   320,   319,   321,   323,   322,   324,
     324,   325,   325,   327,   326,   329,   328,   330,   330,   331,
     331,   332,   332,   332,   332,   332,   332,   332,   333,   335,
     334,   336,   337,   338,   339,   341,   340,   342,   342,   343,
     343,   345,   344,   347,   346,   348,   348,   349,   349,   349,
     349,   351,   350,   353,   352,   355,   354,   356,   356,   357,
     357,   359,   358,   361,   360,   362,   362,   363,   363,   363,
     363,   363,   363,   363,   363,   365,   364,   366,   368,   367,
     369,   370,   372,   371,   373,   373,   374,   374,   376,   375,
     378,   377,   379,   379,   380,   380,   381,   381,   381,   381,
     381,   381,   381,   381,   381,   383,   382,   385,   384,   387,
     386,   389,   388,   391,   390,   393,   392,   395,   394,   397,
     396,   399,   398,   401,   400,   402,   402,   403,   289,   404,
     404,   405,   405,   406,   406,   406,   406,   407,   409,   408,
     411,   410,   412,   412,   413,   413,   413,   413,   413,   413,
     413,   415,   414,   416,   416,   416,   417,   419,   418,   420,
     421,   422,   424,   423,   425,   425,   426,   426,   428,   427,
     430,   429,   432,   431,   434,   433,   435,   435,   436,   436,
     436,   436,   436,   436,   436,   436,   436,   436,   436,   436,
     436,   436,   436,   437,   439,   438,   441,   440,   442,   444,
     443,   445,   446,   448,   447,   449,   449,   451,   450,   452,
     453,   454,   456,   455,   457,   457,   457,   457,   457,   459,
     458,   461,   460,   463,   462,   465,   464,   467,   466,   468,
     468,   469,   471,   470,   472,   472,   474,   473,   475,   475,
     476,   476,   476,   476,   476,   477,   479,   478,   481,   480,
     482,   482,   484,   483,   485,   485,   486,   486,   486,   486,
     488,   487,   489,   490,   491
  };

  const unsigned char
  Dhcp6Parser::yyr2_[] =
  {
       0,     2,     0,     3,     0,     3,     0,     3,     0,     3,
       0,     3,     0,     3,     0,     3,     0,     3,     0,     3,
       0,     3,     0,     3,     0,     3,     0,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     0,     4,     1,     0,
       1,     3,     5,     0,     4,     0,     1,     1,     3,     0,
       4,     0,     1,     1,     3,     2,     0,     4,     1,     3,
       1,     1,     1,     1,     1,     1,     0,     6,     0,     4,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     3,     3,     3,     3,     3,     0,
       6,     0,     4,     1,     3,     1,     1,     0,     4,     3,
       0,     6,     0,     6,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     0,
       4,     1,     1,     1,     1,     0,     4,     0,     4,     0,
       4,     3,     0,     4,     3,     3,     3,     3,     0,     4,
       0,     4,     0,     6,     1,     3,     1,     1,     1,     1,
       0,     6,     1,     3,     1,     1,     1,     1,     1,     0,
       6,     0,     6,     0,     1,     1,     3,     0,     4,     0,
       4,     1,     3,     1,     1,     1,     0,     4,     0,     4,
       0,     6,     1,     3,     1,     1,     1,     1,     1,     1,
       3,     3,     3,     3,     3,     3,     0,     6,     0,     1,
       1,     3,     0,     4,     0,     4,     1,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     4,     1,     1,     1,     3,     3,
       0,     6,     0,     4,     0,     1,     1,     3,     0,     4,
       0,     4,     0,     1,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     3,     1,     0,     4,     0,
       4,     0,     4,     1,     0,     4,     3,     0,     6,     0,
       1,     1,     3,     0,     4,     0,     4,     0,     1,     1,
       3,     1,     1,     1,     1,     1,     1,     1,     1,     0,
       4,     1,     1,     3,     3,     0,     6,     0,     1,     1,
       3,     0,     4,     0,     4,     1,     3,     1,     1,     1,
       1,     0,     4,     0,     4,     0,     6,     0,     1,     1,
       3,     0,     4,     0,     4,     1,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     0,     4,     3,     0,     4,
       3,     3,     0,     6,     0,     1,     1,     3,     0,     4,
       0,     4,     0,     1,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       6,     0,     4,     0,     6,     1,     3,     0,     4,     0,
       1,     1,     3,     1,     1,     1,     1,     1,     0,     4,
       0,     6,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     0,     4,     1,     1,     1,     3,     0,     4,     3,
       3,     3,     0,     6,     1,     3,     1,     1,     0,     4,
       0,     4,     0,     6,     0,     4,     1,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     3,     0,     4,     0,     4,     3,     0,
       4,     3,     3,     0,     4,     1,     1,     0,     4,     3,
       3,     3,     0,     4,     1,     1,     1,     1,     1,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     6,     1,
       3,     1,     0,     6,     1,     3,     0,     4,     1,     3,
       1,     1,     1,     1,     1,     3,     0,     4,     0,     6,
       1,     3,     0,     4,     1,     3,     1,     1,     1,     1,
       0,     4,     3,     3,     3
  };



  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a yyntokens_, nonterminals.
  const char*
  const Dhcp6Parser::yytname_[] =
  {
  "\"end of file\"", "error", "$undefined", "\",\"", "\":\"", "\"[\"",
  "\"]\"", "\"{\"", "\"}\"", "\"null\"", "\"Dhcp6\"",
  "\"interfaces-config\"", "\"interfaces\"", "\"re-detect\"",
  "\"lease-database\"", "\"hosts-database\"", "\"type\"", "\"memfile\"",
  "\"mysql\"", "\"postgresql\"", "\"cql\"", "\"user\"", "\"password\"",
  "\"host\"", "\"port\"", "\"persist\"", "\"lfc-interval\"",
  "\"readonly\"", "\"connect-timeout\"", "\"contact-points\"",
  "\"keyspace\"", "\"preferred-lifetime\"", "\"valid-lifetime\"",
  "\"renew-timer\"", "\"rebind-timer\"", "\"decline-probation-period\"",
  "\"subnet6\"", "\"option-def\"", "\"option-data\"", "\"name\"",
  "\"data\"", "\"code\"", "\"space\"", "\"csv-format\"", "\"always-send\"",
  "\"record-types\"", "\"encapsulate\"", "\"array\"", "\"pools\"",
  "\"pool\"", "\"pd-pools\"", "\"prefix\"", "\"prefix-len\"",
  "\"excluded-prefix\"", "\"excluded-prefix-len\"", "\"delegated-len\"",
  "\"user-context\"", "\"subnet\"", "\"interface\"", "\"interface-id\"",
  "\"id\"", "\"rapid-commit\"", "\"reservation-mode\"", "\"disabled\"",
  "\"out-of-pool\"", "\"all\"", "\"mac-sources\"",
  "\"relay-supplied-options\"", "\"host-reservation-identifiers\"",
  "\"client-classes\"", "\"test\"", "\"client-class\"", "\"reservations\"",
  "\"ip-addresses\"", "\"prefixes\"", "\"duid\"", "\"hw-address\"",
  "\"hostname\"", "\"flex-id\"", "\"relay\"", "\"ip-address\"",
  "\"hooks-libraries\"", "\"library\"", "\"parameters\"",
  "\"expired-leases-processing\"", "\"reclaim-timer-wait-time\"",
  "\"flush-reclaimed-timer-wait-time\"", "\"hold-reclaimed-time\"",
  "\"max-reclaim-leases\"", "\"max-reclaim-time\"",
  "\"unwarned-reclaim-cycles\"", "\"server-id\"", "\"LLT\"", "\"EN\"",
  "\"LL\"", "\"identifier\"", "\"htype\"", "\"time\"", "\"enterprise-id\"",
  "\"dhcp4o6-port\"", "\"control-socket\"", "\"socket-type\"",
  "\"socket-name\"", "\"dhcp-ddns\"", "\"enable-updates\"",
  "\"qualifying-suffix\"", "\"server-ip\"", "\"server-port\"",
  "\"sender-ip\"", "\"sender-port\"", "\"max-queue-size\"",
  "\"ncr-protocol\"", "\"ncr-format\"", "\"always-include-fqdn\"",
  "\"override-no-update\"", "\"override-client-update\"",
  "\"replace-client-name\"", "\"generated-prefix\"", "\"UDP\"", "\"TCP\"",
  "\"JSON\"", "\"when-present\"", "\"never\"", "\"always\"",
  "\"when-not-present\"", "\"Logging\"", "\"loggers\"",
  "\"output_options\"", "\"output\"", "\"debuglevel\"", "\"severity\"",
  "\"flush\"", "\"maxsize\"", "\"maxver\"", "\"Dhcp4\"", "\"DhcpDdns\"",
  "\"Control-agent\"", "TOPLEVEL_JSON", "TOPLEVEL_DHCP6", "SUB_DHCP6",
  "SUB_INTERFACES6", "SUB_SUBNET6", "SUB_POOL6", "SUB_PD_POOL",
  "SUB_RESERVATION", "SUB_OPTION_DEFS", "SUB_OPTION_DEF",
  "SUB_OPTION_DATA", "SUB_HOOKS_LIBRARY", "SUB_DHCP_DDNS",
  "\"constant string\"", "\"integer\"", "\"floating point\"",
  "\"boolean\"", "$accept", "start", "$@1", "$@2", "$@3", "$@4", "$@5",
  "$@6", "$@7", "$@8", "$@9", "$@10", "$@11", "$@12", "$@13", "value",
  "sub_json", "map2", "$@14", "map_value", "map_content", "not_empty_map",
  "list_generic", "$@15", "list_content", "not_empty_list", "list_strings",
  "$@16", "list_strings_content", "not_empty_list_strings",
  "unknown_map_entry", "syntax_map", "$@17", "global_objects",
  "global_object", "dhcp6_object", "$@18", "sub_dhcp6", "$@19",
  "global_params", "global_param", "preferred_lifetime", "valid_lifetime",
  "renew_timer", "rebind_timer", "decline_probation_period",
  "interfaces_config", "$@20", "sub_interfaces6", "$@21",
  "interfaces_config_params", "interfaces_config_param", "interfaces_list",
  "$@22", "re_detect", "lease_database", "$@23", "hosts_database", "$@24",
  "database_map_params", "database_map_param", "database_type", "$@25",
  "db_type", "user", "$@26", "password", "$@27", "host", "$@28", "port",
  "name", "$@29", "persist", "lfc_interval", "readonly", "connect_timeout",
  "contact_points", "$@30", "keyspace", "$@31", "mac_sources", "$@32",
  "mac_sources_list", "mac_sources_value", "duid_id", "string_id",
  "host_reservation_identifiers", "$@33",
  "host_reservation_identifiers_list", "host_reservation_identifier",
  "hw_address_id", "flex_id", "relay_supplied_options", "$@34",
  "hooks_libraries", "$@35", "hooks_libraries_list",
  "not_empty_hooks_libraries_list", "hooks_library", "$@36",
  "sub_hooks_library", "$@37", "hooks_params", "hooks_param", "library",
  "$@38", "parameters", "$@39", "expired_leases_processing", "$@40",
  "expired_leases_params", "expired_leases_param",
  "reclaim_timer_wait_time", "flush_reclaimed_timer_wait_time",
  "hold_reclaimed_time", "max_reclaim_leases", "max_reclaim_time",
  "unwarned_reclaim_cycles", "subnet6_list", "$@41",
  "subnet6_list_content", "not_empty_subnet6_list", "subnet6", "$@42",
  "sub_subnet6", "$@43", "subnet6_params", "subnet6_param", "subnet",
  "$@44", "interface", "$@45", "interface_id", "$@46", "client_class",
  "$@47", "reservation_mode", "$@48", "hr_mode", "id", "rapid_commit",
  "option_def_list", "$@49", "sub_option_def_list", "$@50",
  "option_def_list_content", "not_empty_option_def_list",
  "option_def_entry", "$@51", "sub_option_def", "$@52",
  "option_def_params", "not_empty_option_def_params", "option_def_param",
  "option_def_name", "code", "option_def_code", "option_def_type", "$@53",
  "option_def_record_types", "$@54", "space", "$@55", "option_def_space",
  "option_def_encapsulate", "$@56", "option_def_array", "option_data_list",
  "$@57", "option_data_list_content", "not_empty_option_data_list",
  "option_data_entry", "$@58", "sub_option_data", "$@59",
  "option_data_params", "not_empty_option_data_params",
  "option_data_param", "option_data_name", "option_data_data", "$@60",
  "option_data_code", "option_data_space", "option_data_csv_format",
  "option_data_always_send", "pools_list", "$@61", "pools_list_content",
  "not_empty_pools_list", "pool_list_entry", "$@62", "sub_pool6", "$@63",
  "pool_params", "pool_param", "pool_entry", "$@64", "user_context",
  "$@65", "pd_pools_list", "$@66", "pd_pools_list_content",
  "not_empty_pd_pools_list", "pd_pool_entry", "$@67", "sub_pd_pool",
  "$@68", "pd_pool_params", "pd_pool_param", "pd_prefix", "$@69",
  "pd_prefix_len", "excluded_prefix", "$@70", "excluded_prefix_len",
  "pd_delegated_len", "reservations", "$@71", "reservations_list",
  "not_empty_reservations_list", "reservation", "$@72", "sub_reservation",
  "$@73", "reservation_params", "not_empty_reservation_params",
  "reservation_param", "ip_addresses", "$@74", "prefixes", "$@75", "duid",
  "$@76", "hw_address", "$@77", "hostname", "$@78", "flex_id_value",
  "$@79", "reservation_client_classes", "$@80", "relay", "$@81",
  "relay_map", "$@82", "client_classes", "$@83", "client_classes_list",
  "$@84", "client_class_params", "not_empty_client_class_params",
  "client_class_param", "client_class_name", "client_class_test", "$@85",
  "server_id", "$@86", "server_id_params", "server_id_param",
  "server_id_type", "$@87", "duid_type", "htype", "identifier", "$@88",
  "time", "enterprise_id", "dhcp4o6_port", "control_socket", "$@89",
  "control_socket_params", "control_socket_param", "socket_type", "$@90",
  "socket_name", "$@91", "dhcp_ddns", "$@92", "sub_dhcp_ddns", "$@93",
  "dhcp_ddns_params", "dhcp_ddns_param", "enable_updates",
  "qualifying_suffix", "$@94", "server_ip", "$@95", "server_port",
  "sender_ip", "$@96", "sender_port", "max_queue_size", "ncr_protocol",
  "$@97", "ncr_protocol_value", "ncr_format", "$@98",
  "always_include_fqdn", "override_no_update", "override_client_update",
  "replace_client_name", "$@99", "replace_client_name_value",
  "generated_prefix", "$@100", "dhcp4_json_object", "$@101",
  "dhcpddns_json_object", "$@102", "control_agent_json_object", "$@103",
  "logging_object", "$@104", "logging_params", "logging_param", "loggers",
  "$@105", "loggers_entries", "logger_entry", "$@106", "logger_params",
  "logger_param", "debuglevel", "severity", "$@107", "output_options_list",
  "$@108", "output_options_list_content", "output_entry", "$@109",
  "output_params_list", "output_params", "output", "$@110", "flush",
  "maxsize", "maxver", YY_NULLPTR
  };

#if PARSER6_DEBUG
  const unsigned short int
  Dhcp6Parser::yyrline_[] =
  {
       0,   235,   235,   235,   236,   236,   237,   237,   238,   238,
     239,   239,   240,   240,   241,   241,   242,   242,   243,   243,
     244,   244,   245,   245,   246,   246,   247,   247,   255,   256,
     257,   258,   259,   260,   261,   264,   269,   269,   280,   283,
     284,   287,   291,   298,   298,   305,   306,   309,   313,   320,
     320,   327,   328,   331,   335,   346,   356,   356,   371,   372,
     376,   377,   378,   379,   380,   381,   384,   384,   399,   399,
     408,   409,   414,   415,   416,   417,   418,   419,   420,   421,
     422,   423,   424,   425,   426,   427,   428,   429,   430,   431,
     432,   433,   434,   435,   438,   443,   448,   453,   458,   463,
     463,   474,   474,   483,   484,   487,   488,   491,   491,   501,
     507,   507,   519,   519,   531,   532,   535,   536,   537,   538,
     539,   540,   541,   542,   543,   544,   545,   546,   547,   550,
     550,   557,   558,   559,   560,   563,   563,   571,   571,   579,
     579,   587,   592,   592,   600,   605,   610,   615,   620,   620,
     628,   628,   637,   637,   647,   648,   651,   652,   655,   660,
     665,   665,   675,   676,   679,   680,   681,   684,   689,   696,
     696,   706,   706,   716,   717,   720,   721,   724,   724,   734,
     734,   744,   745,   746,   749,   750,   753,   753,   761,   761,
     769,   769,   780,   781,   784,   785,   786,   787,   788,   789,
     792,   797,   802,   807,   812,   817,   825,   825,   838,   839,
     842,   843,   850,   850,   876,   876,   887,   888,   892,   893,
     894,   895,   896,   897,   898,   899,   900,   901,   902,   903,
     904,   905,   906,   907,   908,   911,   911,   919,   919,   927,
     927,   935,   935,   943,   943,   950,   951,   952,   955,   960,
     969,   969,   982,   982,   991,   992,   995,   996,  1001,  1001,
    1016,  1016,  1030,  1031,  1034,  1035,  1038,  1039,  1040,  1041,
    1042,  1043,  1044,  1045,  1048,  1050,  1055,  1057,  1057,  1065,
    1065,  1073,  1073,  1081,  1083,  1083,  1091,  1100,  1100,  1112,
    1113,  1118,  1119,  1124,  1124,  1136,  1136,  1148,  1149,  1154,
    1155,  1160,  1161,  1162,  1163,  1164,  1165,  1166,  1169,  1171,
    1171,  1179,  1181,  1183,  1188,  1196,  1196,  1208,  1209,  1212,
    1213,  1216,  1216,  1226,  1226,  1235,  1236,  1239,  1240,  1241,
    1242,  1245,  1245,  1253,  1253,  1263,  1263,  1275,  1276,  1279,
    1280,  1283,  1283,  1295,  1295,  1307,  1308,  1311,  1312,  1313,
    1314,  1315,  1316,  1317,  1318,  1321,  1321,  1329,  1334,  1334,
    1342,  1347,  1355,  1355,  1365,  1366,  1369,  1370,  1373,  1373,
    1382,  1382,  1391,  1392,  1395,  1396,  1400,  1401,  1402,  1403,
    1404,  1405,  1406,  1407,  1408,  1411,  1411,  1421,  1421,  1431,
    1431,  1439,  1439,  1447,  1447,  1455,  1455,  1463,  1463,  1476,
    1476,  1486,  1486,  1497,  1497,  1507,  1508,  1511,  1511,  1521,
    1522,  1525,  1526,  1529,  1530,  1531,  1532,  1535,  1537,  1537,
    1548,  1548,  1560,  1561,  1564,  1565,  1566,  1567,  1568,  1569,
    1570,  1573,  1573,  1580,  1581,  1582,  1585,  1590,  1590,  1598,
    1603,  1610,  1617,  1617,  1627,  1628,  1631,  1632,  1635,  1635,
    1643,  1643,  1653,  1653,  1665,  1665,  1675,  1676,  1679,  1680,
    1681,  1682,  1683,  1684,  1685,  1686,  1687,  1688,  1689,  1690,
    1691,  1692,  1693,  1696,  1701,  1701,  1709,  1709,  1717,  1722,
    1722,  1730,  1735,  1740,  1740,  1748,  1749,  1752,  1752,  1760,
    1765,  1770,  1775,  1775,  1783,  1786,  1789,  1792,  1795,  1801,
    1801,  1811,  1811,  1818,  1818,  1825,  1825,  1838,  1838,  1851,
    1852,  1856,  1860,  1860,  1872,  1873,  1877,  1877,  1885,  1886,
    1889,  1890,  1891,  1892,  1893,  1896,  1901,  1901,  1909,  1909,
    1919,  1920,  1923,  1923,  1931,  1932,  1935,  1936,  1937,  1938,
    1941,  1941,  1949,  1954,  1959
  };

  // Print the state stack on the debug stream.
  void
  Dhcp6Parser::yystack_print_ ()
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
  Dhcp6Parser::yy_reduce_print_ (int yyrule)
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
#endif // PARSER6_DEBUG


#line 14 "dhcp6_parser.yy" // lalr1.cc:1167
} } // isc::dhcp
#line 4400 "dhcp6_parser.cc" // lalr1.cc:1167
#line 1964 "dhcp6_parser.yy" // lalr1.cc:1168


void
isc::dhcp::Dhcp6Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
