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

  case 236:
#line 912 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1698 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 237:
#line 914 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr subnet(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 1708 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 238:
#line 920 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1716 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 239:
#line 922 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 1726 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 240:
#line 928 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1734 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 241:
#line 930 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface-id", iface);
    ctx.leave();
}
#line 1744 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 242:
#line 936 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.CLIENT_CLASS);
}
#line 1752 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 243:
#line 938 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr cls(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 1762 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 244:
#line 944 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.RESERVATION_MODE);
}
#line 1770 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 245:
#line 946 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("reservation-mode", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1779 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 246:
#line 951 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("disabled", ctx.loc2pos(yystack_[0].location))); }
#line 1785 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 247:
#line 952 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("out-of-pool", ctx.loc2pos(yystack_[0].location))); }
#line 1791 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 248:
#line 953 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("all", ctx.loc2pos(yystack_[0].location))); }
#line 1797 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 249:
#line 956 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr id(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 1806 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 250:
#line 961 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr rc(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rapid-commit", rc);
}
#line 1815 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 251:
#line 970 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 1826 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 252:
#line 975 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1835 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 253:
#line 983 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1844 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 254:
#line 986 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1852 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 259:
#line 1002 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1862 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 260:
#line 1006 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1874 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 261:
#line 1017 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1884 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 262:
#line 1021 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 1896 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 276:
#line 1051 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr code(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 1905 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 278:
#line 1058 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1913 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 279:
#line 1060 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 1923 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 280:
#line 1066 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1931 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 281:
#line 1068 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 1941 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 282:
#line 1074 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1949 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 283:
#line 1076 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr space(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 1959 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 285:
#line 1084 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1967 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 286:
#line 1086 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr encap(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 1977 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 287:
#line 1092 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr array(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 1986 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 288:
#line 1101 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 1997 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 289:
#line 1106 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2006 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 294:
#line 1125 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2016 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 295:
#line 1129 "dhcp6_parser.yy" // lalr1.cc:859
    {
    /// @todo: the code or name parameters are required.
    ctx.stack_.pop_back();
}
#line 2025 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 296:
#line 1137 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2035 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 297:
#line 1141 "dhcp6_parser.yy" // lalr1.cc:859
    {
    /// @todo: the code or name parameters are required.
    // parsing completed
}
#line 2044 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 310:
#line 1172 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2052 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 311:
#line 1174 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr data(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 2062 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 314:
#line 1184 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr space(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", space);
}
#line 2071 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 315:
#line 1189 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr persist(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-send", persist);
}
#line 2080 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 316:
#line 1197 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 2091 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 317:
#line 1202 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2100 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 322:
#line 1217 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2110 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 323:
#line 1221 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2120 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 324:
#line 1227 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2130 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 325:
#line 1231 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
}
#line 2139 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 332:
#line 1246 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2147 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 333:
#line 1248 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr pool(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 2157 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 334:
#line 1254 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2165 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 335:
#line 1256 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("user-context", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2174 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 336:
#line 1264 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pd-pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.PD_POOLS);
}
#line 2185 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 337:
#line 1269 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2194 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 342:
#line 1284 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2204 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 343:
#line 1288 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The prefix, prefix len and delegated len parameters are required.
    ctx.require("prefix", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("prefix-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("delegated-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2216 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 344:
#line 1296 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the pd-pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2226 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 345:
#line 1300 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The prefix, prefix len and delegated len parameters are required.
    ctx.require("prefix", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("prefix-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("delegated-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2238 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 356:
#line 1322 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2246 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 357:
#line 1324 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix", prf);
    ctx.leave();
}
#line 2256 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 358:
#line 1330 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix-len", prf);
}
#line 2265 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 359:
#line 1335 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2273 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 360:
#line 1337 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix", prf);
    ctx.leave();
}
#line 2283 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 361:
#line 1343 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix-len", prf);
}
#line 2292 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 362:
#line 1348 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr deleg(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("delegated-len", deleg);
}
#line 2301 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 363:
#line 1356 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 2312 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 364:
#line 1361 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2321 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 369:
#line 1374 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2331 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 370:
#line 1378 "dhcp6_parser.yy" // lalr1.cc:859
    {
    /// @todo: an identifier parameter is required.
    ctx.stack_.pop_back();
}
#line 2340 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 371:
#line 1383 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2350 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 372:
#line 1387 "dhcp6_parser.yy" // lalr1.cc:859
    {
    /// @todo: an identifier parameter is required.
    // parsing completed
}
#line 2359 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 386:
#line 1412 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-addresses", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2370 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 387:
#line 1417 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2379 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 388:
#line 1422 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefixes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2390 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 389:
#line 1427 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2399 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 390:
#line 1432 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2407 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 391:
#line 1434 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr d(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 2417 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 392:
#line 1440 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2425 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 393:
#line 1442 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 2435 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 394:
#line 1448 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2443 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 395:
#line 1450 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr host(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 2453 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 396:
#line 1456 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2461 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 397:
#line 1458 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flex-id", hw);
    ctx.leave();
}
#line 2471 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 398:
#line 1464 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2482 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 399:
#line 1469 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2491 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 400:
#line 1477 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 2502 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 401:
#line 1482 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2511 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 402:
#line 1487 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2519 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 403:
#line 1489 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr ip(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", ip);
    ctx.leave();
}
#line 2529 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 404:
#line 1498 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 2540 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 405:
#line 1503 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2549 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 408:
#line 1512 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2559 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 409:
#line 1516 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The name client class parameter is required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2569 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 419:
#line 1538 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2577 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 420:
#line 1540 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr test(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 2587 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 421:
#line 1549 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-id", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SERVER_ID);
}
#line 2598 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 422:
#line 1554 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The type parameter is required.
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2609 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 432:
#line 1574 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.DUID_TYPE);
}
#line 2617 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 433:
#line 1576 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("type", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2626 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 434:
#line 1581 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("LLT", ctx.loc2pos(yystack_[0].location))); }
#line 2632 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 435:
#line 1582 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("EN", ctx.loc2pos(yystack_[0].location))); }
#line 2638 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 436:
#line 1583 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("LL", ctx.loc2pos(yystack_[0].location))); }
#line 2644 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 437:
#line 1586 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr htype(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("htype", htype);
}
#line 2653 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 438:
#line 1591 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2661 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 439:
#line 1593 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr id(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("identifier", id);
    ctx.leave();
}
#line 2671 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 440:
#line 1599 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("time", time);
}
#line 2680 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 441:
#line 1604 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enterprise-id", time);
}
#line 2689 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 442:
#line 1611 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 2698 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 443:
#line 1618 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 2709 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 444:
#line 1623 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2718 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 449:
#line 1636 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2726 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 450:
#line 1638 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr stype(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 2736 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 451:
#line 1644 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2744 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 452:
#line 1646 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 2754 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 453:
#line 1654 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 2765 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 454:
#line 1659 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2776 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 455:
#line 1666 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2786 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 456:
#line 1670 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2796 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 474:
#line 1697 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 2805 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 475:
#line 1702 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2813 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 476:
#line 1704 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("qualifying-suffix", s);
    ctx.leave();
}
#line 2823 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 477:
#line 1710 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2831 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 478:
#line 1712 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 2841 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 479:
#line 1718 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 2850 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 480:
#line 1723 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2858 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 481:
#line 1725 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 2868 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 482:
#line 1731 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 2877 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 483:
#line 1736 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 2886 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 484:
#line 1741 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 2894 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 485:
#line 1743 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2903 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 486:
#line 1749 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 2909 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 487:
#line 1750 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 2915 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 488:
#line 1753 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NCR_FORMAT);
}
#line 2923 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 489:
#line 1755 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 2933 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 490:
#line 1761 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-include-fqdn", b);
}
#line 2942 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 491:
#line 1766 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-no-update", b);
}
#line 2951 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 492:
#line 1771 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-client-update", b);
}
#line 2960 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 493:
#line 1776 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 2968 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 494:
#line 1778 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("replace-client-name", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2977 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 495:
#line 1784 "dhcp6_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("when-present", ctx.loc2pos(yystack_[0].location))); 
      }
#line 2985 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 496:
#line 1787 "dhcp6_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location)));
      }
#line 2993 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 497:
#line 1790 "dhcp6_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("always", ctx.loc2pos(yystack_[0].location)));
      }
#line 3001 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 498:
#line 1793 "dhcp6_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("when-not-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 3009 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 499:
#line 1796 "dhcp6_parser.yy" // lalr1.cc:859
    {
      error(yystack_[0].location, "boolean values for the replace-client-name are "
                "no longer supported");
      }
#line 3018 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 500:
#line 1802 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3026 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 501:
#line 1804 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("generated-prefix", s);
    ctx.leave();
}
#line 3036 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 502:
#line 1812 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3044 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 503:
#line 1814 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("Dhcp4", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3053 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 504:
#line 1819 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3061 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 505:
#line 1821 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("DhcpDdns", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3070 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 506:
#line 1826 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3078 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 507:
#line 1828 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("Control-agent", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3087 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 508:
#line 1839 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Logging", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.LOGGING);
}
#line 3098 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 509:
#line 1844 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3107 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 513:
#line 1861 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 3118 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 514:
#line 1866 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3127 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 517:
#line 1878 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 3137 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 518:
#line 1882 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 3145 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 526:
#line 1897 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr dl(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 3154 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 527:
#line 1902 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3162 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 528:
#line 1904 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 3172 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 529:
#line 1910 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 3183 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 530:
#line 1915 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3192 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 533:
#line 1924 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3202 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 534:
#line 1928 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 3210 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 541:
#line 1942 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3218 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 542:
#line 1944 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 3228 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 543:
#line 1950 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr flush(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 3237 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 544:
#line 1955 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr maxsize(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 3246 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 545:
#line 1960 "dhcp6_parser.yy" // lalr1.cc:859
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


  const short int Dhcp6Parser::yypact_ninf_ = -510;

  const signed char Dhcp6Parser::yytable_ninf_ = -1;

  const short int
  Dhcp6Parser::yypact_[] =
  {
     218,  -510,  -510,  -510,  -510,  -510,  -510,  -510,  -510,  -510,
    -510,  -510,  -510,  -510,    53,    20,    90,   123,   129,   160,
     170,   255,   256,   257,   259,   260,   261,   262,  -510,  -510,
    -510,  -510,  -510,  -510,  -510,  -510,  -510,  -510,  -510,  -510,
    -510,  -510,  -510,  -510,  -510,  -510,  -510,  -510,  -510,  -510,
    -510,  -510,  -510,  -510,  -510,  -510,  -510,  -510,  -510,  -510,
    -510,  -510,  -510,  -510,    20,   -75,    18,    32,   102,    24,
      -5,   106,    73,    40,    63,    50,   -44,   237,  -510,   247,
     215,   224,   263,   252,  -510,  -510,  -510,  -510,  -510,   266,
    -510,    68,  -510,  -510,  -510,  -510,  -510,  -510,  -510,  -510,
    -510,   268,   270,   271,   272,   273,  -510,  -510,  -510,  -510,
    -510,  -510,  -510,  -510,  -510,  -510,   274,  -510,  -510,  -510,
      70,  -510,  -510,  -510,  -510,  -510,  -510,  -510,  -510,  -510,
    -510,  -510,  -510,  -510,  -510,  -510,  -510,  -510,  -510,  -510,
    -510,  -510,  -510,  -510,   275,   114,  -510,  -510,  -510,  -510,
    -510,  -510,  -510,  -510,  -510,  -510,   276,   277,  -510,  -510,
    -510,  -510,  -510,  -510,  -510,  -510,  -510,   125,  -510,  -510,
    -510,  -510,  -510,  -510,  -510,  -510,  -510,  -510,  -510,  -510,
    -510,  -510,  -510,  -510,  -510,   126,  -510,  -510,  -510,  -510,
     279,  -510,   280,   283,  -510,  -510,  -510,   172,  -510,  -510,
    -510,  -510,  -510,  -510,  -510,  -510,  -510,  -510,  -510,  -510,
    -510,  -510,  -510,   284,   285,  -510,  -510,  -510,  -510,  -510,
    -510,  -510,  -510,   286,  -510,  -510,   287,  -510,  -510,  -510,
     289,  -510,  -510,   291,   294,  -510,  -510,  -510,  -510,  -510,
    -510,  -510,  -510,  -510,  -510,  -510,   296,   297,  -510,  -510,
    -510,  -510,   302,   308,  -510,  -510,  -510,  -510,  -510,  -510,
    -510,  -510,  -510,  -510,   173,  -510,  -510,  -510,   310,  -510,
    -510,   313,  -510,   314,   315,  -510,  -510,   316,   318,   319,
    -510,  -510,  -510,   199,  -510,  -510,  -510,  -510,  -510,  -510,
    -510,  -510,  -510,  -510,  -510,  -510,  -510,  -510,  -510,  -510,
      20,    20,  -510,   174,   321,   322,   323,   325,   326,  -510,
      18,  -510,   327,   328,   329,   183,   185,   186,   187,   188,
     364,   365,   366,   367,   368,   369,   370,   371,   372,   373,
     227,   375,   376,    32,  -510,   377,   229,   102,  -510,    49,
     379,   380,   381,   382,   384,   385,   239,   238,   388,   389,
     390,   391,    24,  -510,   392,    -5,  -510,   393,   249,   394,
     250,   251,   106,  -510,   395,   399,   400,   401,   402,   403,
     404,  -510,    73,  -510,   405,   406,   264,   407,   408,   409,
     265,  -510,    63,   410,   278,   281,  -510,    50,   412,   413,
     155,  -510,   282,   415,   419,   288,   420,   290,   295,   421,
     422,   292,   300,   301,   423,   424,   237,  -510,  -510,  -510,
     425,   426,   429,    20,    20,    20,  -510,   430,   431,   433,
    -510,  -510,  -510,  -510,  -510,   427,   437,   442,   443,   444,
     445,   450,   451,   452,   453,  -510,   456,   458,  -510,   461,
    -510,  -510,  -510,  -510,  -510,  -510,   449,   455,  -510,  -510,
    -510,   462,   463,   464,   320,   324,   330,  -510,  -510,   -29,
     331,   467,   466,  -510,   332,  -510,   333,  -510,   334,  -510,
    -510,  -510,   461,   461,   461,   335,   336,   337,   338,  -510,
     339,   340,  -510,   341,   342,   343,  -510,  -510,   344,  -510,
    -510,  -510,   345,    20,  -510,  -510,   346,   347,  -510,   348,
    -510,  -510,    37,   355,  -510,  -510,  -510,    16,   349,  -510,
      20,    32,   304,  -510,  -510,  -510,   102,   162,   162,   469,
     470,   472,   -43,    20,   -26,    41,   494,   108,    29,   159,
     237,  -510,  -510,   498,  -510,    49,   496,   497,  -510,  -510,
    -510,  -510,  -510,  -510,  -510,  -510,  -510,  -510,   499,   428,
    -510,  -510,  -510,  -510,  -510,  -510,  -510,  -510,  -510,  -510,
    -510,  -510,  -510,  -510,  -510,  -510,  -510,  -510,  -510,  -510,
    -510,  -510,  -510,  -510,  -510,  -510,  -510,  -510,  -510,  -510,
    -510,  -510,  -510,   200,  -510,   201,  -510,  -510,   202,  -510,
    -510,  -510,  -510,   501,   503,   505,   506,   507,  -510,  -510,
    -510,   203,  -510,  -510,  -510,  -510,  -510,  -510,  -510,  -510,
    -510,  -510,  -510,  -510,  -510,   209,  -510,   508,   509,  -510,
    -510,   510,   512,  -510,  -510,   513,   515,  -510,  -510,  -510,
     240,  -510,  -510,  -510,   514,  -510,  -510,  -510,   242,  -510,
    -510,  -510,  -510,   244,  -510,   516,   518,  -510,   519,   520,
     521,   522,   523,   524,   211,  -510,  -510,  -510,  -510,  -510,
    -510,  -510,  -510,  -510,   525,   526,   527,  -510,  -510,   212,
    -510,  -510,  -510,  -510,  -510,  -510,  -510,  -510,   213,  -510,
    -510,  -510,   219,   363,   383,  -510,  -510,   528,   529,  -510,
    -510,   530,   532,  -510,  -510,   531,   535,  -510,  -510,   533,
    -510,   536,   304,  -510,  -510,   538,   539,   540,   541,   396,
     386,   397,   398,   411,   542,   545,   162,  -510,  -510,    24,
    -510,   469,    63,  -510,   470,    50,  -510,   472,   -43,  -510,
    -510,   -26,  -510,    41,  -510,   -44,  -510,   494,   414,   416,
     417,   418,   432,   434,   108,  -510,   546,   548,   435,   436,
     438,    29,  -510,   549,   550,   159,  -510,  -510,  -510,   551,
     552,  -510,    -5,  -510,   496,   106,  -510,   497,    73,  -510,
     499,   554,  -510,   555,  -510,   146,   440,   441,   446,  -510,
    -510,  -510,  -510,  -510,   447,   448,  -510,   221,  -510,   553,
    -510,   556,  -510,  -510,  -510,  -510,   222,  -510,  -510,  -510,
    -510,  -510,  -510,  -510,  -510,   -33,   454,  -510,  -510,  -510,
    -510,   457,   459,  -510,  -510,   460,   223,  -510,   231,  -510,
     558,  -510,   465,   563,  -510,  -510,  -510,  -510,  -510,  -510,
    -510,  -510,  -510,  -510,  -510,  -510,  -510,  -510,  -510,  -510,
    -510,  -510,  -510,  -510,  -510,  -510,  -510,  -510,  -510,  -510,
    -510,   246,  -510,    -9,   563,  -510,  -510,   559,  -510,  -510,
    -510,   232,  -510,  -510,  -510,  -510,  -510,   567,   468,   568,
      -9,  -510,   569,  -510,   471,  -510,   566,  -510,  -510,   248,
    -510,   -91,   566,  -510,  -510,   571,   572,   573,   233,  -510,
    -510,  -510,  -510,  -510,  -510,   574,   439,   473,   474,   -91,
    -510,   476,  -510,  -510,  -510,  -510,  -510
  };

  const unsigned short int
  Dhcp6Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,    24,    26,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     1,    43,
      36,    32,    31,    28,    29,    30,    35,     3,    33,    34,
      56,     5,    68,     7,   101,     9,   214,    11,   324,    13,
     344,    15,   371,    17,   253,    19,   261,    21,   296,    23,
     179,    25,   455,    27,    45,    39,     0,     0,     0,     0,
       0,     0,   373,     0,   263,   298,     0,     0,    47,     0,
      46,     0,     0,    40,    66,   508,   502,   504,   506,     0,
      65,     0,    58,    60,    62,    63,    64,    61,    99,   110,
     112,     0,     0,     0,     0,     0,   206,   251,   288,   152,
     169,   160,   404,   171,   190,   421,     0,   443,   453,    93,
       0,    70,    72,    73,    74,    75,    76,    78,    79,    80,
      81,    83,    82,    87,    88,    77,    85,    86,    84,    89,
      90,    91,    92,   107,     0,     0,   103,   105,   106,   408,
     316,   336,   334,   236,   238,   240,     0,     0,   244,   242,
     363,   400,   235,   218,   219,   220,   221,     0,   216,   225,
     226,   227,   230,   232,   228,   229,   222,   223,   234,   224,
     231,   233,   332,   331,   329,     0,   326,   328,   330,   356,
       0,   359,     0,     0,   355,   351,   354,     0,   346,   348,
     349,   352,   353,   350,   398,   386,   388,   390,   392,   394,
     396,   385,   384,     0,   374,   375,   379,   380,   377,   381,
     382,   383,   378,     0,   278,   142,     0,   282,   280,   285,
       0,   274,   275,     0,   264,   265,   267,   277,   268,   269,
     270,   284,   271,   272,   273,   310,     0,     0,   308,   309,
     312,   313,     0,   299,   300,   302,   303,   304,   305,   306,
     307,   186,   188,   183,     0,   181,   184,   185,     0,   475,
     477,     0,   480,     0,     0,   484,   488,     0,     0,     0,
     493,   500,   473,     0,   457,   459,   460,   461,   462,   463,
     464,   465,   466,   467,   468,   469,   470,   471,   472,    44,
       0,     0,    37,     0,     0,     0,     0,     0,     0,    55,
       0,    57,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    69,     0,     0,     0,   102,   410,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   215,     0,     0,   325,     0,     0,     0,
       0,     0,     0,   345,     0,     0,     0,     0,     0,     0,
       0,   372,     0,   254,     0,     0,     0,     0,     0,     0,
       0,   262,     0,     0,     0,     0,   297,     0,     0,     0,
       0,   180,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   456,    48,    41,
       0,     0,     0,     0,     0,     0,    59,     0,     0,     0,
      94,    95,    96,    97,    98,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   442,     0,     0,    71,     0,
     109,   104,   419,   417,   418,   416,     0,   411,   412,   414,
     415,     0,     0,     0,     0,     0,     0,   249,   250,     0,
       0,     0,     0,   217,     0,   327,     0,   358,     0,   361,
     362,   347,     0,     0,     0,     0,     0,     0,     0,   376,
       0,     0,   276,     0,     0,     0,   287,   266,     0,   314,
     315,   301,     0,     0,   182,   474,     0,     0,   479,     0,
     482,   483,     0,     0,   490,   491,   492,     0,     0,   458,
       0,     0,     0,   503,   505,   507,     0,     0,     0,   208,
     255,   290,     0,    45,     0,     0,   173,     0,     0,     0,
       0,    49,   108,     0,   409,     0,   318,   338,    38,   335,
     237,   239,   241,   246,   247,   248,   245,   243,   365,     0,
     333,   357,   360,   399,   387,   389,   391,   393,   395,   397,
     279,   143,   283,   281,   286,   311,   187,   189,   476,   478,
     481,   486,   487,   485,   489,   495,   496,   497,   498,   499,
     494,   501,    42,     0,   513,     0,   510,   512,     0,   129,
     135,   137,   139,     0,     0,     0,     0,     0,   148,   150,
     128,     0,   114,   116,   117,   118,   119,   120,   121,   122,
     123,   124,   125,   126,   127,     0,   212,     0,   209,   210,
     259,     0,   256,   257,   294,     0,   291,   292,   158,   159,
       0,   154,   156,   157,     0,   167,   168,   164,     0,   162,
     165,   166,   406,     0,   177,     0,   174,   175,     0,     0,
       0,     0,     0,     0,     0,   192,   194,   195,   196,   197,
     198,   199,   432,   438,     0,     0,     0,   431,   430,     0,
     423,   425,   428,   426,   427,   429,   449,   451,     0,   445,
     447,   448,     0,    51,     0,   413,   322,     0,   319,   320,
     342,     0,   339,   340,   369,     0,   366,   367,   402,     0,
      67,     0,     0,   509,   100,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   111,   113,     0,
     207,     0,   263,   252,     0,   298,   289,     0,     0,   153,
     170,     0,   161,     0,   405,     0,   172,     0,     0,     0,
       0,     0,     0,     0,     0,   191,     0,     0,     0,     0,
       0,     0,   422,     0,     0,     0,   444,   454,    53,     0,
      52,   420,     0,   317,     0,     0,   337,     0,   373,   364,
       0,     0,   401,     0,   511,     0,     0,     0,     0,   141,
     144,   145,   146,   147,     0,     0,   115,     0,   211,     0,
     258,     0,   293,   155,   163,   407,     0,   176,   200,   201,
     202,   203,   204,   205,   193,     0,     0,   437,   440,   441,
     424,     0,     0,   446,    50,     0,     0,   321,     0,   341,
       0,   368,     0,     0,   131,   132,   133,   134,   130,   136,
     138,   140,   149,   151,   213,   260,   295,   178,   434,   435,
     436,   433,   439,   450,   452,    54,   323,   343,   370,   403,
     517,     0,   515,     0,     0,   514,   529,     0,   527,   525,
     521,     0,   519,   523,   524,   522,   516,     0,     0,     0,
       0,   518,     0,   526,     0,   520,     0,   528,   533,     0,
     531,     0,     0,   530,   541,     0,     0,     0,     0,   535,
     537,   538,   539,   540,   532,     0,     0,     0,     0,     0,
     534,     0,   543,   544,   545,   536,   542
  };

  const short int
  Dhcp6Parser::yypgoto_[] =
  {
    -510,  -510,  -510,  -510,  -510,  -510,  -510,  -510,  -510,  -510,
    -510,  -510,  -510,  -510,  -510,     7,  -510,   103,  -510,  -510,
    -510,  -510,  -510,  -510,    36,  -510,  -215,  -510,  -510,  -510,
     -66,  -510,  -510,  -510,   269,  -510,  -510,  -510,  -510,    69,
     267,   -67,   -62,   -49,   -48,  -510,  -510,  -510,  -510,  -510,
      65,   245,  -510,  -510,  -510,  -510,  -510,  -510,  -510,    66,
    -128,  -510,  -510,  -510,  -510,  -510,  -510,  -510,  -510,  -510,
    -510,   -74,  -510,  -509,  -510,  -510,  -510,  -510,  -510,  -510,
    -510,  -510,  -510,  -510,  -135,  -498,  -510,  -510,  -510,  -510,
    -137,  -510,  -510,  -510,  -510,  -510,  -510,  -510,  -510,  -142,
    -510,  -510,  -510,  -136,   216,  -510,  -510,  -510,  -510,  -510,
    -510,  -510,  -143,  -510,  -510,  -510,  -510,  -510,  -510,  -510,
    -510,  -510,  -510,  -119,  -510,  -510,  -510,  -116,   253,  -510,
    -510,  -510,  -510,  -510,  -510,  -501,  -510,  -510,  -510,  -510,
    -510,  -510,   543,  -510,  -510,  -510,  -510,  -510,  -113,  -510,
    -510,  -510,  -114,  -510,   230,  -510,   -59,  -510,  -510,  -510,
    -510,  -510,   -52,  -510,  -510,  -510,  -510,  -510,   -57,  -510,
    -510,  -510,  -110,  -510,  -510,  -510,  -112,  -510,   235,  -510,
    -510,  -510,  -510,  -510,  -510,  -510,  -510,  -510,  -510,  -510,
    -150,  -510,  -510,  -510,  -144,   293,  -510,  -510,   -53,  -510,
    -510,  -510,  -510,  -510,  -147,  -510,  -510,  -510,  -138,   298,
    -510,  -510,  -510,  -510,  -510,  -510,  -510,  -510,  -510,  -510,
    -510,  -141,  -510,  -510,  -510,  -145,  -510,   258,  -510,  -510,
    -510,  -510,  -510,  -510,  -510,  -510,  -510,  -510,  -510,  -510,
    -510,  -510,  -510,  -510,  -510,  -510,  -510,  -510,  -510,  -510,
    -510,  -510,    93,  -510,  -510,  -510,  -510,  -510,  -510,  -120,
    -510,  -510,  -510,  -510,  -510,  -510,  -510,  -510,  -510,  -510,
    -510,  -510,  -123,  -510,  -510,  -510,  -510,  -510,  -510,  -510,
    -510,   104,   234,  -510,  -510,  -510,  -510,  -510,  -510,  -510,
    -510,  -510,  -510,  -510,  -510,  -510,  -510,  -510,  -510,  -510,
    -510,  -510,  -510,  -510,  -510,  -510,  -510,  -510,  -510,  -510,
    -510,  -510,  -510,  -510,  -510,   -69,  -510,  -510,  -510,  -219,
    -510,  -510,  -234,  -510,  -510,  -510,  -510,  -510,  -510,  -245,
    -510,  -510,  -261,  -510,  -510,  -510,  -510,  -510
  };

  const short int
  Dhcp6Parser::yydefgoto_[] =
  {
      -1,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    78,    37,    38,    65,   539,
      82,    83,    39,    64,    79,    80,   532,   683,   759,   760,
     119,    41,    66,    91,    92,    93,   304,    43,    67,   120,
     121,   122,   123,   124,   125,   126,   127,   312,    45,    68,
     145,   146,   147,   335,   148,   128,   313,   129,   314,   601,
     602,   603,   705,   828,   604,   706,   605,   707,   606,   708,
     607,   232,   375,   609,   610,   611,   612,   613,   714,   614,
     715,   130,   323,   630,   631,   632,   633,   131,   325,   638,
     639,   640,   641,   132,   324,   133,   327,   645,   646,   647,
     735,    61,    76,   264,   265,   266,   388,   267,   389,   134,
     328,   654,   655,   656,   657,   658,   659,   660,   661,   135,
     320,   617,   618,   619,   719,    47,    69,   167,   168,   169,
     343,   170,   344,   171,   345,   172,   349,   173,   348,   546,
     174,   175,   136,   321,    55,    73,   621,   622,   623,   722,
      57,    74,   233,   234,   235,   236,   237,   238,   239,   374,
     240,   378,   241,   377,   242,   243,   379,   244,   137,   322,
     625,   626,   627,   725,    59,    75,   252,   253,   254,   255,
     256,   383,   257,   258,   259,   260,   177,   340,   687,   688,
     689,   762,    49,    70,   185,   186,   187,   354,   178,   342,
     179,   341,   691,   692,   693,   765,    51,    71,   197,   198,
     199,   357,   200,   201,   359,   202,   203,   180,   350,   695,
     696,   697,   768,    53,    72,   213,   214,   215,   216,   365,
     217,   366,   218,   367,   219,   368,   220,   369,   221,   370,
     222,   364,   181,   351,   699,   771,   138,   326,   643,   339,
     446,   447,   448,   449,   450,   533,   139,   329,   669,   670,
     671,   746,   841,   672,   673,   747,   674,   675,   140,   141,
     331,   678,   679,   680,   753,   681,   754,   142,   332,    63,
      77,   283,   284,   285,   286,   393,   287,   394,   288,   289,
     396,   290,   291,   292,   399,   573,   293,   400,   294,   295,
     296,   297,   404,   580,   298,   405,    94,   306,    95,   307,
      96,   308,    97,   305,   585,   586,   587,   701,   851,   852,
     853,   861,   862,   863,   864,   869,   865,   867,   879,   880,
     881,   888,   889,   890,   895,   891,   892,   893
  };

  const unsigned short int
  Dhcp6Parser::yytable_[] =
  {
      90,   249,   163,   162,   183,   194,   211,   164,   231,   248,
     263,   282,   176,   184,   195,   212,   250,   188,   196,   668,
     165,   166,    36,   251,   642,    29,   637,    30,    84,    31,
     225,   149,   628,   108,   543,   544,   545,   884,   261,   262,
     885,   886,   887,    98,   182,   662,    99,   100,   149,   628,
     635,   152,   636,    28,   594,   101,   102,   103,   104,   838,
     839,   840,   108,   101,   102,   103,   104,   105,   106,   107,
     108,   310,   150,   333,   151,    81,   311,   107,   334,   224,
     152,   153,   154,   155,   156,   157,   158,   108,   225,   225,
     245,   226,   227,   246,   247,   159,   160,    40,   109,   110,
     111,   112,   225,   161,   226,   227,    89,   629,   228,   229,
     230,   108,   159,   113,   143,   144,   114,   337,   856,   442,
     857,   858,   338,   115,   663,   664,   665,   666,   352,   355,
      42,   116,   117,   353,   356,   118,    44,   575,   576,   577,
     578,    89,   204,    85,   108,    89,   205,   206,   207,   208,
     209,   210,    86,    87,    88,   571,   572,   189,   190,   191,
     192,   193,   152,   824,   825,   826,   827,    46,    89,   579,
      32,    33,    34,    35,    89,   362,   390,    48,   589,    89,
     363,   391,    89,   590,   591,   592,   593,   594,   595,   596,
     597,   598,   599,   648,   649,   650,   651,   652,   653,    89,
      89,   225,   406,   333,   702,   337,   716,   407,   700,   703,
     704,   717,   716,    89,   744,   751,   755,   718,   300,   745,
     752,   756,   406,    89,   352,   390,   355,   757,   301,   834,
     837,   846,   795,   637,   362,   870,   899,   261,   262,   847,
     871,   900,   668,   728,    90,   731,   729,   733,   732,   854,
     734,   882,   855,   299,   883,   303,    89,   553,   554,   555,
     676,   677,    50,    52,    54,   444,    56,    58,    60,    62,
     309,   302,   315,   443,   316,   317,   318,   319,   330,   336,
     346,   347,   445,   358,   360,   163,   162,   361,   372,   183,
     164,   376,   371,   380,   373,   176,   194,   382,   184,   381,
     384,   385,   188,   165,   166,   195,   211,   408,   409,   196,
     386,   387,    89,   249,   392,   212,   231,   395,   397,   398,
     401,   248,   402,   403,   410,   411,   412,   413,   250,   414,
     415,   417,   418,   419,   420,   251,   421,   422,   423,   424,
     282,   268,   269,   270,   271,   272,   273,   274,   275,   276,
     277,   278,   279,   280,   281,     1,     2,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,   425,   426,
     427,   428,   429,   430,   431,   432,   433,   434,   435,   436,
     437,   439,   440,   451,   452,   453,   454,    89,   455,   456,
     457,   458,   459,   460,   461,   462,   464,   466,   468,   472,
     467,   469,   470,   473,   474,   475,   476,   477,   478,   480,
     481,   483,   484,   485,   488,   482,   492,   493,   486,   496,
     513,   514,   515,   497,   499,   502,   503,   507,   508,   510,
     584,   489,   519,   511,   490,   495,   512,   516,   517,   498,
     518,   500,   520,   608,   608,   504,   501,   521,   522,   523,
     524,   600,   600,   505,   506,   525,   526,   534,   535,   527,
     528,   444,   667,   529,   282,   530,   531,   536,   537,   443,
     540,    30,   548,   549,   541,   574,   616,   620,   445,   624,
     542,   547,   550,   551,   552,   556,   557,   558,   559,   560,
     561,   562,   563,   564,   565,   566,   568,   569,   570,   581,
     567,   644,   684,   686,   690,   709,   694,   710,   698,   711,
     712,   713,   721,   758,   720,   724,   723,   582,   727,   726,
     730,   737,   736,   738,   739,   740,   741,   742,   743,   748,
     749,   750,   764,   761,   763,   767,   766,   769,   770,   780,
     773,   772,   775,   776,   777,   778,   784,   779,   781,   785,
     805,   782,   806,   811,   812,   815,   538,   814,   822,   634,
     823,   835,   783,   868,   836,   798,   848,   799,   800,   801,
     850,   872,   874,   878,   876,   896,   897,   898,   901,   416,
     583,   588,   441,   802,   615,   803,   807,   808,   786,   809,
     829,   830,   902,   793,   794,   797,   831,   832,   833,   796,
     438,   804,   788,   787,   842,   463,   494,   843,   789,   844,
     845,   790,   487,   791,   817,   849,   223,   792,   816,   873,
     819,   877,   491,   820,   903,   904,   906,   818,   685,   821,
     479,   810,   813,   774,   682,   866,   875,   894,   905,     0,
     509,     0,   608,     0,     0,     0,     0,     0,   465,     0,
     600,   249,   163,   162,     0,     0,   231,   164,     0,   248,
     471,     0,   176,     0,     0,     0,   250,     0,     0,   263,
     165,   166,     0,   251,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   667,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   183,     0,     0,   194,
       0,     0,   211,     0,     0,   184,     0,     0,   195,   188,
       0,   212,   196,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   860,
       0,     0,     0,     0,     0,     0,     0,   859,     0,     0,
       0,     0,     0,     0,     0,     0,   860,     0,     0,     0,
       0,     0,     0,     0,   859
  };

  const short int
  Dhcp6Parser::yycheck_[] =
  {
      66,    75,    69,    69,    70,    71,    72,    69,    74,    75,
      76,    77,    69,    70,    71,    72,    75,    70,    71,   528,
      69,    69,    15,    75,   525,     5,   524,     7,    10,     9,
      39,     7,    75,    38,    63,    64,    65,   128,    82,    83,
     131,   132,   133,    11,    49,    16,    14,    15,     7,    75,
      76,    56,    78,     0,    25,    31,    32,    33,    34,    92,
      93,    94,    38,    31,    32,    33,    34,    35,    36,    37,
      38,     3,    48,     3,    50,   150,     8,    37,     8,    16,
      56,    57,    58,    59,    60,    61,    62,    38,    39,    39,
      40,    41,    42,    43,    44,    71,    72,     7,    66,    67,
      68,    69,    39,    79,    41,    42,   150,   150,    45,    46,
      47,    38,    71,    81,    12,    13,    84,     3,   127,    70,
     129,   130,     8,    91,    95,    96,    97,    98,     3,     3,
       7,    99,   100,     8,     8,   103,     7,   121,   122,   123,
     124,   150,    69,   125,    38,   150,    73,    74,    75,    76,
      77,    78,   134,   135,   136,   118,   119,    51,    52,    53,
      54,    55,    56,    17,    18,    19,    20,     7,   150,   153,
     150,   151,   152,   153,   150,     3,     3,     7,    16,   150,
       8,     8,   150,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    85,    86,    87,    88,    89,    90,   150,
     150,    39,     3,     3,     3,     3,     3,     8,     8,     8,
       8,     8,     3,   150,     3,     3,     3,     8,     3,     8,
       8,     8,     3,   150,     3,     3,     3,     8,     4,     8,
       8,     8,   733,   731,     3,     3,     3,    82,    83,     8,
       8,     8,   751,     3,   310,     3,     6,     3,     6,     3,
       6,     3,     6,     6,     6,     3,   150,   472,   473,   474,
     101,   102,     7,     7,     7,   339,     7,     7,     7,     7,
       4,     8,     4,   339,     4,     4,     4,     4,     4,     4,
       4,     4,   339,     4,     4,   352,   352,     4,     3,   355,
     352,     4,     8,     4,     8,   352,   362,     3,   355,     8,
       4,     4,   355,   352,   352,   362,   372,   300,   301,   362,
       8,     3,   150,   387,     4,   372,   382,     4,     4,     4,
       4,   387,     4,     4,   150,     4,     4,     4,   387,     4,
       4,     4,     4,     4,   151,   387,   151,   151,   151,   151,
     406,   104,   105,   106,   107,   108,   109,   110,   111,   112,
     113,   114,   115,   116,   117,   137,   138,   139,   140,   141,
     142,   143,   144,   145,   146,   147,   148,   149,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,   151,     4,
       4,     4,   153,     4,     4,     4,     4,   150,     4,     4,
     151,   153,     4,     4,     4,     4,     4,     4,     4,     4,
     151,   151,   151,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,   151,     4,     4,   153,     4,
     413,   414,   415,     4,     4,     4,     4,     4,     4,     4,
     126,   153,     5,     7,   153,   153,     7,     7,     7,   151,
       7,   151,     5,   517,   518,   153,   151,     5,     5,     5,
       5,   517,   518,   153,   153,     5,     5,     8,     3,     7,
       7,   535,   528,     7,   530,     7,     5,     5,     5,   535,
     150,     7,     5,     7,   150,   120,     7,     7,   535,     7,
     150,   150,   150,   150,   150,   150,   150,   150,   150,   150,
     150,   150,   150,   150,   150,   150,   150,   150,   150,   150,
     493,     7,     4,     7,     7,     4,     7,     4,    80,     4,
       4,     4,     3,   150,     6,     3,     6,   510,     3,     6,
       6,     3,     6,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     3,   150,     6,     3,     6,     6,     3,   153,
       4,     8,     4,     4,     4,     4,     4,   151,   151,     4,
       4,   153,     4,     4,     4,     3,   453,     6,     4,   523,
       5,     8,   151,     4,     8,   151,     8,   151,   151,   151,
       7,     4,     4,     7,     5,     4,     4,     4,     4,   310,
     511,   516,   337,   151,   518,   151,   151,   151,   716,   151,
     150,   150,   153,   728,   731,   737,   150,   150,   150,   735,
     333,   744,   721,   719,   150,   352,   390,   150,   722,   150,
     150,   724,   382,   725,   764,   150,    73,   727,   762,   151,
     767,   150,   387,   768,   151,   151,   150,   765,   535,   770,
     372,   751,   755,   702,   530,   854,   870,   882,   899,    -1,
     406,    -1,   716,    -1,    -1,    -1,    -1,    -1,   355,    -1,
     716,   725,   719,   719,    -1,    -1,   722,   719,    -1,   725,
     362,    -1,   719,    -1,    -1,    -1,   725,    -1,    -1,   735,
     719,   719,    -1,   725,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   751,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   762,    -1,    -1,   765,
      -1,    -1,   768,    -1,    -1,   762,    -1,    -1,   765,   762,
      -1,   768,   765,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   853,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   853,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   870,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   870
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
      48,    50,    56,    57,    58,    59,    60,    61,    62,    71,
      72,    79,   184,   195,   196,   197,   198,   281,   282,   283,
     285,   287,   289,   291,   294,   295,   322,   340,   352,   354,
     371,   396,    49,   184,   322,   348,   349,   350,   352,    51,
      52,    53,    54,    55,   184,   322,   352,   362,   363,   364,
     366,   367,   369,   370,    69,    73,    74,    75,    76,    77,
      78,   184,   322,   379,   380,   381,   382,   384,   386,   388,
     390,   392,   394,   296,    16,    39,    41,    42,    45,    46,
      47,   184,   225,   306,   307,   308,   309,   310,   311,   312,
     314,   316,   318,   319,   321,    40,    43,    44,   184,   225,
     310,   316,   330,   331,   332,   333,   334,   336,   337,   338,
     339,    82,    83,   184,   257,   258,   259,   261,   104,   105,
     106,   107,   108,   109,   110,   111,   112,   113,   114,   115,
     116,   117,   184,   435,   436,   437,   438,   440,   442,   443,
     445,   446,   447,   450,   452,   453,   454,   455,   458,     6,
       3,     4,     8,     3,   190,   467,   461,   463,   465,     4,
       3,     8,   201,   210,   212,     4,     4,     4,     4,     4,
     274,   297,   323,   236,   248,   242,   401,   250,   264,   411,
       4,   424,   432,     3,     8,   207,     4,     3,     8,   403,
     341,   355,   353,   284,   286,   288,     4,     4,   292,   290,
     372,   397,     3,     8,   351,     3,     8,   365,     4,   368,
       4,     4,     3,     8,   395,   383,   385,   387,   389,   391,
     393,     8,     3,     8,   313,   226,     4,   317,   315,   320,
       4,     8,     3,   335,     4,     4,     8,     3,   260,   262,
       3,     8,     4,   439,   441,     4,   444,     4,     4,   448,
     451,     4,     4,     4,   456,   459,     3,     8,   169,   169,
     150,     4,     4,     4,     4,     4,   188,     4,     4,     4,
     151,   151,   151,   151,   151,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,   151,     4,     4,   194,     4,
     153,   205,    70,   184,   225,   322,   404,   405,   406,   407,
     408,     4,     4,     4,     4,     4,     4,   151,   153,     4,
       4,     4,     4,   282,     4,   349,     4,   151,     4,   151,
     151,   363,     4,     4,     4,     4,     4,     4,     4,   381,
       4,     4,   151,     4,     4,     4,   153,   308,     4,   153,
     153,   332,     4,     4,   258,   153,     4,     4,   151,     4,
     151,   151,     4,     4,   153,   153,   153,     4,     4,   436,
       4,     7,     7,   169,   169,   169,     7,     7,     7,     5,
       5,     5,     5,     5,     5,     5,     5,     7,     7,     7,
       7,     5,   180,   409,     8,     3,     5,     5,   171,   173,
     150,   150,   150,    63,    64,    65,   293,   150,     5,     7,
     150,   150,   150,   180,   180,   180,   150,   150,   150,   150,
     150,   150,   150,   150,   150,   150,   150,   169,   150,   150,
     150,   118,   119,   449,   120,   121,   122,   123,   124,   153,
     457,   150,   169,   193,   126,   468,   469,   470,   204,    16,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
     184,   213,   214,   215,   218,   220,   222,   224,   225,   227,
     228,   229,   230,   231,   233,   213,     7,   275,   276,   277,
       7,   300,   301,   302,     7,   324,   325,   326,    75,   150,
     237,   238,   239,   240,   178,    76,    78,   239,   243,   244,
     245,   246,   289,   402,     7,   251,   252,   253,    85,    86,
      87,    88,    89,    90,   265,   266,   267,   268,   269,   270,
     271,   272,    16,    95,    96,    97,    98,   184,   227,   412,
     413,   414,   417,   418,   420,   421,   101,   102,   425,   426,
     427,   429,   435,   181,     4,   406,     7,   342,   343,   344,
       7,   356,   357,   358,     7,   373,   374,   375,    80,   398,
       8,   471,     3,     8,     8,   216,   219,   221,   223,     4,
       4,     4,     4,     4,   232,   234,     3,     8,     8,   278,
       6,     3,   303,     6,     3,   327,     6,     3,     3,     6,
       6,     3,     6,     3,     6,   254,     6,     3,     4,     4,
       4,     4,     4,     4,     3,     8,   415,   419,     4,     4,
       4,     3,     8,   428,   430,     3,     8,     8,   150,   182,
     183,   150,   345,     6,     3,   359,     6,     3,   376,     6,
       3,   399,     8,     4,   469,     4,     4,     4,     4,   151,
     153,   151,   153,   151,     4,     4,   214,   281,   277,   306,
     302,   330,   326,   238,   244,   289,   257,   253,   151,   151,
     151,   151,   151,   151,   266,     4,     4,   151,   151,   151,
     413,     4,     4,   426,     6,     3,   348,   344,   362,   358,
     379,   375,     4,     5,    17,    18,    19,    20,   217,   150,
     150,   150,   150,   150,     8,     8,     8,     8,    92,    93,
      94,   416,   150,   150,   150,   150,     8,     8,     8,   150,
       7,   472,   473,   474,     3,     6,   127,   129,   130,   184,
     225,   475,   476,   477,   478,   480,   473,   481,     4,   479,
       3,     8,     4,   151,     4,   476,     5,   150,     7,   482,
     483,   484,     3,     6,   128,   131,   132,   133,   485,   486,
     487,   489,   490,   491,   483,   488,     4,     4,     4,     3,
       8,     4,   153,   151,   151,   486,   150
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
     282,   282,   282,   282,   282,   282,   284,   283,   286,   285,
     288,   287,   290,   289,   292,   291,   293,   293,   293,   294,
     295,   297,   296,   299,   298,   300,   300,   301,   301,   303,
     302,   305,   304,   306,   306,   307,   307,   308,   308,   308,
     308,   308,   308,   308,   308,   309,   310,   311,   313,   312,
     315,   314,   317,   316,   318,   320,   319,   321,   323,   322,
     324,   324,   325,   325,   327,   326,   329,   328,   330,   330,
     331,   331,   332,   332,   332,   332,   332,   332,   332,   333,
     335,   334,   336,   337,   338,   339,   341,   340,   342,   342,
     343,   343,   345,   344,   347,   346,   348,   348,   349,   349,
     349,   349,   351,   350,   353,   352,   355,   354,   356,   356,
     357,   357,   359,   358,   361,   360,   362,   362,   363,   363,
     363,   363,   363,   363,   363,   363,   365,   364,   366,   368,
     367,   369,   370,   372,   371,   373,   373,   374,   374,   376,
     375,   378,   377,   379,   379,   380,   380,   381,   381,   381,
     381,   381,   381,   381,   381,   381,   383,   382,   385,   384,
     387,   386,   389,   388,   391,   390,   393,   392,   395,   394,
     397,   396,   399,   398,   401,   400,   402,   402,   403,   289,
     404,   404,   405,   405,   406,   406,   406,   406,   407,   409,
     408,   411,   410,   412,   412,   413,   413,   413,   413,   413,
     413,   413,   415,   414,   416,   416,   416,   417,   419,   418,
     420,   421,   422,   424,   423,   425,   425,   426,   426,   428,
     427,   430,   429,   432,   431,   434,   433,   435,   435,   436,
     436,   436,   436,   436,   436,   436,   436,   436,   436,   436,
     436,   436,   436,   436,   437,   439,   438,   441,   440,   442,
     444,   443,   445,   446,   448,   447,   449,   449,   451,   450,
     452,   453,   454,   456,   455,   457,   457,   457,   457,   457,
     459,   458,   461,   460,   463,   462,   465,   464,   467,   466,
     468,   468,   469,   471,   470,   472,   472,   474,   473,   475,
     475,   476,   476,   476,   476,   476,   477,   479,   478,   481,
     480,   482,   482,   484,   483,   485,   485,   486,   486,   486,
     486,   488,   487,   489,   490,   491
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
       1,     1,     1,     1,     1,     1,     0,     4,     0,     4,
       0,     4,     0,     4,     0,     4,     1,     1,     1,     3,
       3,     0,     6,     0,     4,     0,     1,     1,     3,     0,
       4,     0,     4,     0,     1,     1,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     3,     1,     0,     4,
       0,     4,     0,     4,     1,     0,     4,     3,     0,     6,
       0,     1,     1,     3,     0,     4,     0,     4,     0,     1,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       0,     4,     1,     1,     3,     3,     0,     6,     0,     1,
       1,     3,     0,     4,     0,     4,     1,     3,     1,     1,
       1,     1,     0,     4,     0,     4,     0,     6,     0,     1,
       1,     3,     0,     4,     0,     4,     1,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     0,     4,     3,     0,
       4,     3,     3,     0,     6,     0,     1,     1,     3,     0,
       4,     0,     4,     0,     1,     1,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     0,     4,     0,     4,
       0,     4,     0,     4,     0,     4,     0,     4,     0,     4,
       0,     6,     0,     4,     0,     6,     1,     3,     0,     4,
       0,     1,     1,     3,     1,     1,     1,     1,     1,     0,
       4,     0,     6,     1,     3,     1,     1,     1,     1,     1,
       1,     1,     0,     4,     1,     1,     1,     3,     0,     4,
       3,     3,     3,     0,     6,     1,     3,     1,     1,     0,
       4,     0,     4,     0,     6,     0,     4,     1,     3,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     3,     0,     4,     0,     4,     3,
       0,     4,     3,     3,     0,     4,     1,     1,     0,     4,
       3,     3,     3,     0,     4,     1,     1,     1,     1,     1,
       0,     4,     0,     4,     0,     4,     0,     4,     0,     6,
       1,     3,     1,     0,     6,     1,     3,     0,     4,     1,
       3,     1,     1,     1,     1,     1,     3,     0,     4,     0,
       6,     1,     3,     0,     4,     1,     3,     1,     1,     1,
       1,     0,     4,     3,     3,     3
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
     904,   905,   906,   907,   908,   909,   912,   912,   920,   920,
     928,   928,   936,   936,   944,   944,   951,   952,   953,   956,
     961,   970,   970,   983,   983,   992,   993,   996,   997,  1002,
    1002,  1017,  1017,  1031,  1032,  1035,  1036,  1039,  1040,  1041,
    1042,  1043,  1044,  1045,  1046,  1049,  1051,  1056,  1058,  1058,
    1066,  1066,  1074,  1074,  1082,  1084,  1084,  1092,  1101,  1101,
    1113,  1114,  1119,  1120,  1125,  1125,  1137,  1137,  1149,  1150,
    1155,  1156,  1161,  1162,  1163,  1164,  1165,  1166,  1167,  1170,
    1172,  1172,  1180,  1182,  1184,  1189,  1197,  1197,  1209,  1210,
    1213,  1214,  1217,  1217,  1227,  1227,  1236,  1237,  1240,  1241,
    1242,  1243,  1246,  1246,  1254,  1254,  1264,  1264,  1276,  1277,
    1280,  1281,  1284,  1284,  1296,  1296,  1308,  1309,  1312,  1313,
    1314,  1315,  1316,  1317,  1318,  1319,  1322,  1322,  1330,  1335,
    1335,  1343,  1348,  1356,  1356,  1366,  1367,  1370,  1371,  1374,
    1374,  1383,  1383,  1392,  1393,  1396,  1397,  1401,  1402,  1403,
    1404,  1405,  1406,  1407,  1408,  1409,  1412,  1412,  1422,  1422,
    1432,  1432,  1440,  1440,  1448,  1448,  1456,  1456,  1464,  1464,
    1477,  1477,  1487,  1487,  1498,  1498,  1508,  1509,  1512,  1512,
    1522,  1523,  1526,  1527,  1530,  1531,  1532,  1533,  1536,  1538,
    1538,  1549,  1549,  1561,  1562,  1565,  1566,  1567,  1568,  1569,
    1570,  1571,  1574,  1574,  1581,  1582,  1583,  1586,  1591,  1591,
    1599,  1604,  1611,  1618,  1618,  1628,  1629,  1632,  1633,  1636,
    1636,  1644,  1644,  1654,  1654,  1666,  1666,  1676,  1677,  1680,
    1681,  1682,  1683,  1684,  1685,  1686,  1687,  1688,  1689,  1690,
    1691,  1692,  1693,  1694,  1697,  1702,  1702,  1710,  1710,  1718,
    1723,  1723,  1731,  1736,  1741,  1741,  1749,  1750,  1753,  1753,
    1761,  1766,  1771,  1776,  1776,  1784,  1787,  1790,  1793,  1796,
    1802,  1802,  1812,  1812,  1819,  1819,  1826,  1826,  1839,  1839,
    1852,  1853,  1857,  1861,  1861,  1873,  1874,  1878,  1878,  1886,
    1887,  1890,  1891,  1892,  1893,  1894,  1897,  1902,  1902,  1910,
    1910,  1920,  1921,  1924,  1924,  1932,  1933,  1936,  1937,  1938,
    1939,  1942,  1942,  1950,  1955,  1960
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
#line 1965 "dhcp6_parser.yy" // lalr1.cc:1168


void
isc::dhcp::Dhcp6Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
