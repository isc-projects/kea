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

  case 234:
#line 892 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1698 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 235:
#line 894 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr subnet(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 1708 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 236:
#line 900 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1716 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 237:
#line 902 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 1726 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 238:
#line 908 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1734 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 239:
#line 910 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface-id", iface);
    ctx.leave();
}
#line 1744 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 240:
#line 916 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.CLIENT_CLASS);
}
#line 1752 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 241:
#line 918 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr cls(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 1762 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 242:
#line 924 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.RESERVATION_MODE);
}
#line 1770 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 243:
#line 926 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("reservation-mode", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1779 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 244:
#line 931 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("disabled", ctx.loc2pos(yystack_[0].location))); }
#line 1785 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 245:
#line 932 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("out-of-pool", ctx.loc2pos(yystack_[0].location))); }
#line 1791 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 246:
#line 933 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("all", ctx.loc2pos(yystack_[0].location))); }
#line 1797 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 247:
#line 936 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr id(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 1806 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 248:
#line 941 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr rc(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rapid-commit", rc);
}
#line 1815 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 249:
#line 950 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 1826 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 250:
#line 955 "dhcp6_parser.yy" // lalr1.cc:859
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

  case 255:
#line 972 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1862 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 256:
#line 976 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1874 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 257:
#line 983 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1884 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 258:
#line 987 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 1896 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 272:
#line 1013 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr code(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 1905 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 274:
#line 1020 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1913 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 275:
#line 1022 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 1923 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 276:
#line 1028 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1931 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 277:
#line 1030 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 1941 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 278:
#line 1036 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1949 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 279:
#line 1038 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr space(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 1959 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 281:
#line 1046 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1967 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 282:
#line 1048 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr encap(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 1977 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 283:
#line 1054 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr array(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 1986 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 284:
#line 1063 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 1997 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 285:
#line 1068 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2006 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 290:
#line 1087 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2016 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 291:
#line 1091 "dhcp6_parser.yy" // lalr1.cc:859
    {
    /// @todo: the code or name parameters are required.
    ctx.stack_.pop_back();
}
#line 2025 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 292:
#line 1098 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2035 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 293:
#line 1102 "dhcp6_parser.yy" // lalr1.cc:859
    {
    /// @todo: the code or name parameters are required.
    // parsing completed
}
#line 2044 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 306:
#line 1132 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2052 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 307:
#line 1134 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr data(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 2062 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 310:
#line 1144 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr space(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", space);
}
#line 2071 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 311:
#line 1149 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr persist(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-send", persist);
}
#line 2080 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 312:
#line 1157 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 2091 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 313:
#line 1162 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2100 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 318:
#line 1177 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2110 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 319:
#line 1181 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2120 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 320:
#line 1185 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2130 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 321:
#line 1189 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
}
#line 2139 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 328:
#line 1203 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2147 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 329:
#line 1205 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr pool(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 2157 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 330:
#line 1211 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2165 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 331:
#line 1213 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("user-context", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2174 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 332:
#line 1221 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pd-pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.PD_POOLS);
}
#line 2185 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 333:
#line 1226 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2194 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 338:
#line 1241 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2204 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 339:
#line 1245 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The prefix, prefix len and delegated len parameters are required.
    ctx.require("prefix", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("prefix-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("delegated-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2216 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 340:
#line 1249 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the pd-pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2226 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 341:
#line 1253 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The prefix, prefix len and delegated len parameters are required.
    ctx.require("prefix", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("prefix-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("delegated-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2238 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 352:
#line 1271 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2246 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 353:
#line 1273 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix", prf);
    ctx.leave();
}
#line 2256 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 354:
#line 1279 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix-len", prf);
}
#line 2265 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 355:
#line 1284 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2273 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 356:
#line 1286 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix", prf);
    ctx.leave();
}
#line 2283 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 357:
#line 1292 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix-len", prf);
}
#line 2292 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 358:
#line 1297 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr deleg(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("delegated-len", deleg);
}
#line 2301 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 359:
#line 1305 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 2312 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 360:
#line 1310 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2321 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 365:
#line 1323 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2331 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 366:
#line 1327 "dhcp6_parser.yy" // lalr1.cc:859
    {
    /// @todo: an identifier parameter is required.
    ctx.stack_.pop_back();
}
#line 2340 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 367:
#line 1331 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2350 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 368:
#line 1335 "dhcp6_parser.yy" // lalr1.cc:859
    {
    /// @todo: an identifier parameter is required.
    // parsing completed
}
#line 2359 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 382:
#line 1359 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-addresses", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2370 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 383:
#line 1364 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2379 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 384:
#line 1369 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefixes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2390 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 385:
#line 1374 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2399 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 386:
#line 1379 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2407 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 387:
#line 1381 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr d(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 2417 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 388:
#line 1387 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2425 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 389:
#line 1389 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 2435 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 390:
#line 1395 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2443 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 391:
#line 1397 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr host(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 2453 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 392:
#line 1403 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2461 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 393:
#line 1405 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flex-id", hw);
    ctx.leave();
}
#line 2471 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 394:
#line 1411 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2482 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 395:
#line 1416 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2491 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 396:
#line 1424 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 2502 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 397:
#line 1429 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2511 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 398:
#line 1434 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2519 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 399:
#line 1436 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr ip(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", ip);
    ctx.leave();
}
#line 2529 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 400:
#line 1445 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 2540 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 401:
#line 1450 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2549 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 404:
#line 1459 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2559 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 405:
#line 1463 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The name client class parameter is required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2569 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 415:
#line 1483 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2577 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 416:
#line 1485 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr test(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 2587 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 417:
#line 1494 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-id", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SERVER_ID);
}
#line 2598 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 418:
#line 1499 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The type parameter is required.
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2609 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 428:
#line 1517 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.DUID_TYPE);
}
#line 2617 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 429:
#line 1519 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("type", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2626 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 430:
#line 1524 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("LLT", ctx.loc2pos(yystack_[0].location))); }
#line 2632 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 431:
#line 1525 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("EN", ctx.loc2pos(yystack_[0].location))); }
#line 2638 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 432:
#line 1526 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("LL", ctx.loc2pos(yystack_[0].location))); }
#line 2644 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 433:
#line 1529 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr htype(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("htype", htype);
}
#line 2653 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 434:
#line 1534 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2661 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 435:
#line 1536 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr id(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("identifier", id);
    ctx.leave();
}
#line 2671 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 436:
#line 1542 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("time", time);
}
#line 2680 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 437:
#line 1547 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enterprise-id", time);
}
#line 2689 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 438:
#line 1554 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 2698 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 439:
#line 1561 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 2709 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 440:
#line 1566 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2718 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 445:
#line 1579 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2726 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 446:
#line 1581 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr stype(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 2736 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 447:
#line 1587 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2744 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 448:
#line 1589 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 2754 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 449:
#line 1597 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 2765 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 450:
#line 1602 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2776 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 451:
#line 1607 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2786 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 452:
#line 1611 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2796 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 470:
#line 1636 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 2805 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 471:
#line 1641 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2813 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 472:
#line 1643 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("qualifying-suffix", s);
    ctx.leave();
}
#line 2823 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 473:
#line 1649 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2831 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 474:
#line 1651 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 2841 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 475:
#line 1657 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 2850 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 476:
#line 1662 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2858 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 477:
#line 1664 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 2868 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 478:
#line 1670 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 2877 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 479:
#line 1675 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 2886 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 480:
#line 1680 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 2894 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 481:
#line 1682 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2903 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 482:
#line 1688 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 2909 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 483:
#line 1689 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 2915 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 484:
#line 1692 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NCR_FORMAT);
}
#line 2923 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 485:
#line 1694 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 2933 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 486:
#line 1700 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-include-fqdn", b);
}
#line 2942 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 487:
#line 1705 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-no-update", b);
}
#line 2951 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 488:
#line 1710 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-client-update", b);
}
#line 2960 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 489:
#line 1715 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 2968 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 490:
#line 1717 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("replace-client-name", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2977 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 491:
#line 1723 "dhcp6_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("when-present", ctx.loc2pos(yystack_[0].location))); 
      }
#line 2985 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 492:
#line 1726 "dhcp6_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location)));
      }
#line 2993 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 493:
#line 1729 "dhcp6_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("always", ctx.loc2pos(yystack_[0].location)));
      }
#line 3001 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 494:
#line 1732 "dhcp6_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("when-not-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 3009 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 495:
#line 1735 "dhcp6_parser.yy" // lalr1.cc:859
    {
      error(yystack_[0].location, "boolean values for the replace-client-name are "
                "no longer supported");
      }
#line 3018 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 496:
#line 1741 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3026 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 497:
#line 1743 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("generated-prefix", s);
    ctx.leave();
}
#line 3036 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 498:
#line 1751 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3044 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 499:
#line 1753 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("Dhcp4", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3053 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 500:
#line 1758 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3061 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 501:
#line 1760 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("DhcpDdns", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3070 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 502:
#line 1765 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3078 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 503:
#line 1767 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("Control-agent", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3087 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 504:
#line 1778 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Logging", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.LOGGING);
}
#line 3098 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 505:
#line 1783 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3107 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 509:
#line 1800 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 3118 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 510:
#line 1805 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3127 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 513:
#line 1817 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 3137 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 514:
#line 1821 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 3145 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 522:
#line 1836 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr dl(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 3154 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 523:
#line 1841 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3162 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 524:
#line 1843 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 3172 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 525:
#line 1849 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 3183 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 526:
#line 1854 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3192 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 529:
#line 1863 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3202 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 530:
#line 1867 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 3210 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 537:
#line 1881 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3218 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 538:
#line 1883 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 3228 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 539:
#line 1889 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr flush(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 3237 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 540:
#line 1894 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr maxsize(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 3246 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 541:
#line 1899 "dhcp6_parser.yy" // lalr1.cc:859
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


  const short int Dhcp6Parser::yypact_ninf_ = -520;

  const signed char Dhcp6Parser::yytable_ninf_ = -1;

  const short int
  Dhcp6Parser::yypact_[] =
  {
      92,  -520,  -520,  -520,  -520,  -520,  -520,  -520,  -520,  -520,
    -520,  -520,  -520,    24,    23,    26,    30,    34,    43,    55,
      67,    69,    78,   132,   136,   145,  -520,  -520,  -520,  -520,
    -520,  -520,  -520,  -520,  -520,  -520,  -520,  -520,  -520,  -520,
    -520,  -520,  -520,  -520,  -520,  -520,  -520,  -520,  -520,  -520,
    -520,  -520,  -520,  -520,  -520,  -520,  -520,  -520,  -520,  -520,
      23,   -83,    13,    20,    86,    11,    -9,    41,    40,    61,
     124,   -44,   151,  -520,   153,   158,   166,   179,   185,  -520,
    -520,  -520,  -520,  -520,   205,  -520,   133,  -520,  -520,  -520,
    -520,  -520,  -520,  -520,  -520,  -520,   247,   249,   272,   295,
     297,  -520,  -520,  -520,  -520,  -520,  -520,  -520,  -520,  -520,
    -520,   306,  -520,  -520,  -520,   134,  -520,  -520,  -520,  -520,
    -520,  -520,  -520,  -520,  -520,  -520,  -520,  -520,  -520,  -520,
    -520,  -520,  -520,  -520,  -520,  -520,  -520,  -520,  -520,   308,
     142,  -520,  -520,  -520,  -520,  -520,  -520,  -520,  -520,  -520,
    -520,   310,   328,  -520,  -520,  -520,  -520,  -520,  -520,  -520,
    -520,  -520,   143,  -520,  -520,  -520,  -520,  -520,  -520,  -520,
    -520,  -520,  -520,  -520,  -520,  -520,  -520,  -520,  -520,  -520,
     150,  -520,  -520,  -520,  -520,   329,  -520,   330,   331,  -520,
    -520,  -520,   168,  -520,  -520,  -520,  -520,  -520,  -520,  -520,
    -520,  -520,  -520,  -520,  -520,  -520,  -520,  -520,   208,   267,
    -520,  -520,  -520,  -520,  -520,  -520,  -520,  -520,  -520,  -520,
     332,  -520,  -520,  -520,   334,  -520,  -520,   283,   336,  -520,
    -520,  -520,  -520,  -520,  -520,  -520,  -520,  -520,  -520,  -520,
     337,   338,  -520,  -520,  -520,  -520,   335,   341,  -520,  -520,
    -520,  -520,  -520,  -520,  -520,  -520,  -520,  -520,   195,  -520,
    -520,  -520,   342,  -520,  -520,   343,  -520,   344,   345,  -520,
    -520,   346,   347,   348,  -520,  -520,  -520,   196,  -520,  -520,
    -520,  -520,  -520,  -520,  -520,  -520,  -520,  -520,  -520,  -520,
    -520,  -520,  -520,  -520,    23,    23,  -520,   191,   349,   350,
     351,   352,   353,  -520,    13,  -520,   354,   355,   356,   211,
     213,   215,   217,   221,   358,   360,   362,   364,   365,   366,
     368,   369,   370,   371,   226,   373,   374,    20,  -520,   375,
     193,    86,  -520,    42,   376,   377,   378,   379,   380,   381,
     236,   235,   384,   385,   386,   387,    11,  -520,   388,    -9,
    -520,   389,   245,   390,   246,   248,    41,  -520,   393,   395,
     396,   397,   398,   399,   400,  -520,    40,   401,   402,   257,
     404,   405,   406,   259,  -520,    61,   408,   262,   263,  -520,
     124,   409,   412,   214,  -520,   265,   414,   415,   270,   417,
     273,   274,   418,   421,   275,   279,   281,   422,   428,   151,
    -520,  -520,  -520,   430,   429,   431,    23,    23,    23,  -520,
     432,   433,   434,  -520,  -520,  -520,  -520,  -520,   437,   438,
     439,   440,   441,   442,   445,   446,   447,   448,  -520,   449,
     450,  -520,   453,  -520,  -520,  -520,  -520,  -520,  -520,   427,
     457,  -520,  -520,  -520,   458,   459,   455,   288,   316,   318,
    -520,  -520,   260,   319,   464,   465,  -520,   322,  -520,   324,
    -520,   325,  -520,  -520,  -520,   453,   453,   453,   326,   327,
     333,   339,  -520,   340,   357,  -520,   361,   363,   367,  -520,
    -520,   372,  -520,  -520,  -520,   382,    23,  -520,  -520,   383,
     391,  -520,   392,  -520,  -520,     6,   359,  -520,  -520,  -520,
      62,   394,  -520,    23,    20,   403,  -520,  -520,  -520,    86,
     105,   105,   471,   473,   474,   -27,    23,   102,    39,   476,
     107,    59,   218,   151,  -520,  -520,   480,  -520,    42,   478,
     479,  -520,  -520,  -520,  -520,  -520,  -520,  -520,  -520,  -520,
    -520,   483,   407,  -520,  -520,  -520,  -520,  -520,  -520,  -520,
    -520,  -520,  -520,  -520,  -520,  -520,  -520,  -520,  -520,  -520,
    -520,  -520,  -520,  -520,  -520,  -520,  -520,  -520,  -520,  -520,
    -520,  -520,  -520,  -520,  -520,  -520,   197,  -520,   199,  -520,
    -520,   203,  -520,  -520,  -520,  -520,   487,   488,   489,   490,
     491,  -520,  -520,  -520,   209,  -520,  -520,  -520,  -520,  -520,
    -520,  -520,  -520,  -520,  -520,  -520,  -520,  -520,   210,  -520,
     492,   493,  -520,  -520,   494,   496,  -520,  -520,   495,   499,
    -520,  -520,  -520,   220,  -520,  -520,  -520,   497,  -520,  -520,
    -520,   280,  -520,  -520,  -520,  -520,   282,  -520,   498,   502,
    -520,   503,   505,   507,   509,   510,   511,   212,  -520,  -520,
    -520,  -520,  -520,  -520,  -520,  -520,  -520,   513,   514,   515,
    -520,  -520,   216,  -520,  -520,  -520,  -520,  -520,  -520,  -520,
    -520,   219,  -520,  -520,  -520,   238,   410,   411,  -520,  -520,
     516,   517,  -520,  -520,   518,   520,  -520,  -520,   521,   523,
    -520,  -520,   522,  -520,   524,   403,  -520,  -520,   529,   530,
     531,   532,   413,   416,   419,   420,   423,   533,   534,   105,
    -520,  -520,    11,  -520,   471,    61,  -520,   473,   124,  -520,
     474,   -27,  -520,  -520,   102,  -520,    39,  -520,   -44,  -520,
     476,   424,   425,   426,   435,   436,   443,   107,  -520,   535,
     538,   444,   451,   452,    59,  -520,   540,   541,   218,  -520,
    -520,  -520,   542,   543,  -520,    -9,  -520,   478,    41,  -520,
     479,    40,  -520,   483,   545,  -520,   546,  -520,   261,   454,
     456,   460,  -520,  -520,  -520,  -520,  -520,   461,   462,  -520,
     240,  -520,   539,  -520,   544,  -520,  -520,  -520,  -520,   241,
    -520,  -520,  -520,  -520,  -520,  -520,  -520,  -520,   234,   463,
    -520,  -520,  -520,  -520,   466,   467,  -520,  -520,   468,   242,
    -520,   244,  -520,   547,  -520,   469,   549,  -520,  -520,  -520,
    -520,  -520,  -520,  -520,  -520,  -520,  -520,  -520,  -520,  -520,
    -520,  -520,  -520,  -520,  -520,  -520,  -520,  -520,  -520,  -520,
    -520,  -520,  -520,  -520,   286,  -520,    52,   549,  -520,  -520,
     550,  -520,  -520,  -520,   266,  -520,  -520,  -520,  -520,  -520,
     553,   470,   554,    52,  -520,   548,  -520,   472,  -520,   555,
    -520,  -520,   287,  -520,   -68,   555,  -520,  -520,   557,   560,
     561,   269,  -520,  -520,  -520,  -520,  -520,  -520,   562,   475,
     481,   482,   -68,  -520,   477,  -520,  -520,  -520,  -520,  -520
  };

  const unsigned short int
  Dhcp6Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,    24,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     1,    41,    34,    30,
      29,    26,    27,    28,    33,     3,    31,    32,    54,     5,
      66,     7,    99,     9,   212,    11,   320,    13,   340,    15,
     367,    17,   257,    19,   292,    21,   177,    23,   451,    25,
      43,    37,     0,     0,     0,     0,     0,     0,   369,   259,
     294,     0,     0,    45,     0,    44,     0,     0,    38,    64,
     504,   498,   500,   502,     0,    63,     0,    56,    58,    60,
      61,    62,    59,    97,   108,   110,     0,     0,     0,     0,
       0,   204,   249,   284,   150,   167,   158,   400,   169,   188,
     417,     0,   439,   449,    91,     0,    68,    70,    71,    72,
      73,    74,    76,    77,    78,    79,    81,    80,    85,    86,
      75,    83,    84,    82,    87,    88,    89,    90,   105,     0,
       0,   101,   103,   104,   404,   312,   332,   330,   234,   236,
     238,     0,     0,   242,   240,   359,   396,   233,   216,   217,
     218,   219,     0,   214,   223,   224,   225,   228,   230,   226,
     227,   220,   221,   232,   222,   229,   231,   328,   327,   325,
       0,   322,   324,   326,   352,     0,   355,     0,     0,   351,
     347,   350,     0,   342,   344,   345,   348,   349,   346,   394,
     382,   384,   386,   388,   390,   392,   381,   380,     0,   370,
     371,   375,   376,   373,   377,   378,   379,   374,   274,   140,
       0,   278,   276,   281,     0,   270,   271,     0,   260,   261,
     263,   273,   264,   265,   266,   280,   267,   268,   269,   306,
       0,     0,   304,   305,   308,   309,     0,   295,   296,   298,
     299,   300,   301,   302,   303,   184,   186,   181,     0,   179,
     182,   183,     0,   471,   473,     0,   476,     0,     0,   480,
     484,     0,     0,     0,   489,   496,   469,     0,   453,   455,
     456,   457,   458,   459,   460,   461,   462,   463,   464,   465,
     466,   467,   468,    42,     0,     0,    35,     0,     0,     0,
       0,     0,     0,    53,     0,    55,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    67,     0,
       0,     0,   100,   406,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   213,     0,     0,
     321,     0,     0,     0,     0,     0,     0,   341,     0,     0,
       0,     0,     0,     0,     0,   368,     0,     0,     0,     0,
       0,     0,     0,     0,   258,     0,     0,     0,     0,   293,
       0,     0,     0,     0,   178,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     452,    46,    39,     0,     0,     0,     0,     0,     0,    57,
       0,     0,     0,    92,    93,    94,    95,    96,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   438,     0,
       0,    69,     0,   107,   102,   415,   413,   414,   412,     0,
     407,   408,   410,   411,     0,     0,     0,     0,     0,     0,
     247,   248,     0,     0,     0,     0,   215,     0,   323,     0,
     354,     0,   357,   358,   343,     0,     0,     0,     0,     0,
       0,     0,   372,     0,     0,   272,     0,     0,     0,   283,
     262,     0,   310,   311,   297,     0,     0,   180,   470,     0,
       0,   475,     0,   478,   479,     0,     0,   486,   487,   488,
       0,     0,   454,     0,     0,     0,   499,   501,   503,     0,
       0,     0,   206,   251,   286,     0,    43,     0,     0,   171,
       0,     0,     0,     0,    47,   106,     0,   405,     0,   314,
     334,    36,   331,   235,   237,   239,   244,   245,   246,   243,
     241,   361,     0,   329,   353,   356,   395,   383,   385,   387,
     389,   391,   393,   275,   141,   279,   277,   282,   307,   185,
     187,   472,   474,   477,   482,   483,   481,   485,   491,   492,
     493,   494,   495,   490,   497,    40,     0,   509,     0,   506,
     508,     0,   127,   133,   135,   137,     0,     0,     0,     0,
       0,   146,   148,   126,     0,   112,   114,   115,   116,   117,
     118,   119,   120,   121,   122,   123,   124,   125,     0,   210,
       0,   207,   208,   255,     0,   252,   253,   290,     0,   287,
     288,   156,   157,     0,   152,   154,   155,     0,   165,   166,
     162,     0,   160,   163,   164,   402,     0,   175,     0,   172,
     173,     0,     0,     0,     0,     0,     0,     0,   190,   192,
     193,   194,   195,   196,   197,   428,   434,     0,     0,     0,
     427,   426,     0,   419,   421,   424,   422,   423,   425,   445,
     447,     0,   441,   443,   444,     0,    49,     0,   409,   318,
       0,   315,   316,   338,     0,   335,   336,   365,     0,   362,
     363,   398,     0,    65,     0,     0,   505,    98,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     109,   111,     0,   205,     0,   259,   250,     0,   294,   285,
       0,     0,   151,   168,     0,   159,     0,   401,     0,   170,
       0,     0,     0,     0,     0,     0,     0,     0,   189,     0,
       0,     0,     0,     0,     0,   418,     0,     0,     0,   440,
     450,    51,     0,    50,   416,     0,   313,     0,     0,   333,
       0,   369,   360,     0,     0,   397,     0,   507,     0,     0,
       0,     0,   139,   142,   143,   144,   145,     0,     0,   113,
       0,   209,     0,   254,     0,   289,   153,   161,   403,     0,
     174,   198,   199,   200,   201,   202,   203,   191,     0,     0,
     433,   436,   437,   420,     0,     0,   442,    48,     0,     0,
     317,     0,   337,     0,   364,     0,     0,   129,   130,   131,
     132,   128,   134,   136,   138,   147,   149,   211,   256,   291,
     176,   430,   431,   432,   429,   435,   446,   448,    52,   319,
     339,   366,   399,   513,     0,   511,     0,     0,   510,   525,
       0,   523,   521,   517,     0,   515,   519,   520,   518,   512,
       0,     0,     0,     0,   514,     0,   522,     0,   516,     0,
     524,   529,     0,   527,     0,     0,   526,   537,     0,     0,
       0,     0,   531,   533,   534,   535,   536,   528,     0,     0,
       0,     0,     0,   530,     0,   539,   540,   541,   532,   538
  };

  const short int
  Dhcp6Parser::yypgoto_[] =
  {
    -520,  -520,  -520,  -520,  -520,  -520,  -520,  -520,  -520,  -520,
    -520,  -520,  -520,  -520,    22,  -520,    51,  -520,  -520,  -520,
    -520,  -520,  -520,    54,  -520,  -136,  -520,  -520,  -520,   -62,
    -520,  -520,  -520,   276,  -520,  -520,  -520,  -520,    46,   250,
     -43,   -40,   -39,   -38,  -520,  -520,  -520,  -520,  -520,    58,
     251,  -520,  -520,  -520,  -520,  -520,  -520,  -520,    60,  -131,
    -520,  -520,  -520,  -520,  -520,  -520,  -520,  -520,  -520,  -520,
     -58,  -520,  -519,  -520,  -520,  -520,  -520,  -520,  -520,  -520,
    -520,  -520,  -520,  -142,  -496,  -520,  -520,  -520,  -520,  -143,
    -520,  -520,  -520,  -520,  -520,  -520,  -520,  -520,  -147,  -520,
    -520,  -520,  -144,   204,  -520,  -520,  -520,  -520,  -520,  -520,
    -520,  -149,  -520,  -520,  -520,  -520,  -520,  -520,  -520,  -520,
    -520,  -520,  -125,  -520,  -520,  -520,  -122,   252,  -520,  -520,
    -520,  -520,  -520,  -520,  -505,  -520,  -520,  -520,  -520,  -520,
    -520,  -520,  -520,  -520,  -520,  -126,  -520,  -520,  -520,  -123,
    -520,   222,  -520,   -69,  -520,  -520,  -520,  -520,  -520,   -59,
    -520,  -520,  -520,  -520,  -520,   -51,  -520,  -520,  -520,  -124,
    -520,  -520,  -520,  -119,  -520,   224,  -520,  -520,  -520,  -520,
    -520,  -520,  -520,  -520,  -520,  -520,  -520,  -162,  -520,  -520,
    -520,  -155,   258,  -520,  -520,   -47,  -520,  -520,  -520,  -520,
    -520,  -154,  -520,  -520,  -520,  -150,   268,  -520,  -520,  -520,
    -520,  -520,  -520,  -520,  -520,  -520,  -520,  -520,  -141,  -520,
    -520,  -520,  -148,  -520,   253,  -520,  -520,  -520,  -520,  -520,
    -520,  -520,  -520,  -520,  -520,  -520,  -520,  -520,  -520,  -520,
    -520,  -520,  -520,  -520,  -520,  -520,  -520,  -520,  -520,    95,
    -520,  -520,  -520,  -520,  -520,  -520,  -130,  -520,  -520,  -520,
    -520,  -520,  -520,  -520,  -520,  -520,  -520,  -520,  -520,  -120,
    -520,  -520,  -520,  -520,  -520,  -520,  -520,  -520,   106,   231,
    -520,  -520,  -520,  -520,  -520,  -520,  -520,  -520,  -520,  -520,
    -520,  -520,  -520,  -520,  -520,  -520,  -520,  -520,  -520,  -520,
    -520,  -520,  -520,  -520,  -520,  -520,  -520,  -520,  -520,  -520,
    -520,  -520,   -70,  -520,  -520,  -520,  -214,  -520,  -520,  -229,
    -520,  -520,  -520,  -520,  -520,  -520,  -240,  -520,  -520,  -256,
    -520,  -520,  -520,  -520,  -520
  };

  const short int
  Dhcp6Parser::yydefgoto_[] =
  {
      -1,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    73,    35,    36,    61,   532,    77,
      78,    37,    60,    74,    75,   525,   676,   752,   753,   114,
      39,    62,    86,    87,    88,   298,    41,    63,   115,   116,
     117,   118,   119,   120,   121,   122,   306,    43,    64,   140,
     141,   142,   329,   143,   123,   307,   124,   308,   594,   595,
     596,   698,   821,   597,   699,   598,   700,   599,   701,   600,
     226,   368,   602,   603,   604,   605,   606,   707,   607,   708,
     125,   317,   623,   624,   625,   626,   126,   319,   631,   632,
     633,   634,   127,   318,   128,   321,   638,   639,   640,   728,
      57,    71,   258,   259,   260,   381,   261,   382,   129,   322,
     647,   648,   649,   650,   651,   652,   653,   654,   130,   314,
     610,   611,   612,   712,    45,    65,   162,   163,   164,   337,
     165,   338,   166,   339,   167,   343,   168,   342,   539,   169,
     170,   131,   315,   614,   615,   616,   715,    53,    69,   227,
     228,   229,   230,   231,   232,   233,   367,   234,   371,   235,
     370,   236,   237,   372,   238,   132,   316,   618,   619,   620,
     718,    55,    70,   246,   247,   248,   249,   250,   376,   251,
     252,   253,   254,   172,   334,   680,   681,   682,   755,    47,
      66,   180,   181,   182,   348,   173,   336,   174,   335,   684,
     685,   686,   758,    49,    67,   192,   193,   194,   351,   195,
     196,   353,   197,   198,   175,   344,   688,   689,   690,   761,
      51,    68,   208,   209,   210,   211,   359,   212,   360,   213,
     361,   214,   362,   215,   363,   216,   364,   217,   358,   176,
     345,   692,   764,   133,   320,   636,   333,   439,   440,   441,
     442,   443,   526,   134,   323,   662,   663,   664,   739,   834,
     665,   666,   740,   667,   668,   135,   136,   325,   671,   672,
     673,   746,   674,   747,   137,   326,    59,    72,   277,   278,
     279,   280,   386,   281,   387,   282,   283,   389,   284,   285,
     286,   392,   566,   287,   393,   288,   289,   290,   291,   397,
     573,   292,   398,    89,   300,    90,   301,    91,   302,    92,
     299,   578,   579,   580,   694,   844,   845,   846,   854,   855,
     856,   857,   862,   858,   860,   872,   873,   874,   881,   882,
     883,   888,   884,   885,   886
  };

  const unsigned short int
  Dhcp6Parser::yytable_[] =
  {
      85,   244,   661,   157,   178,   189,   206,   225,   242,   257,
     276,   245,   243,   635,   171,   179,   190,   207,   144,   183,
     191,   630,   158,    79,    26,   159,   160,   161,    27,   103,
      28,    93,    29,    38,    94,    95,    34,    40,   255,   256,
     177,    42,    96,    97,    98,    99,   144,   147,   621,   103,
      44,    96,    97,    98,    99,   100,   101,   102,   103,   145,
     877,   146,    46,   878,   879,   880,    76,   147,   148,   149,
     150,   151,   152,   153,    48,   655,    50,   218,   103,   103,
     103,   219,   154,   155,   587,    52,   104,   105,   106,   107,
     156,   219,   184,   185,   186,   187,   188,   147,   138,   139,
     219,   108,   220,   221,   109,    84,   222,   223,   224,   199,
     154,   110,   435,   200,   201,   202,   203,   204,   205,   111,
     112,   582,   622,   113,   564,   565,   583,   584,   585,   586,
     587,   588,   589,   590,   591,   592,   304,   327,    80,    54,
      84,   305,   328,    56,   219,   331,   346,    81,    82,    83,
     332,   347,    58,   349,   656,   657,   658,   659,   350,   293,
      84,   294,    84,   219,   239,   220,   221,   240,   241,    84,
     295,   356,    30,    31,    32,    33,   357,   621,   628,   849,
     629,   850,   851,   568,   569,   570,   571,   296,   297,    84,
      84,    84,   641,   642,   643,   644,   645,   646,   383,   399,
     327,    84,   695,   384,   400,   693,   331,   696,    84,   303,
      84,   697,   709,   709,   572,   737,   365,   710,   711,   744,
     738,   788,   748,   721,   745,   661,   722,   749,   630,     1,
       2,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,   399,    85,   346,   383,   349,   750,   356,   827,   830,
     839,   309,   840,   310,    84,   262,   263,   264,   265,   266,
     267,   268,   269,   270,   271,   272,   273,   274,   275,   863,
     366,   436,   892,    84,   864,   437,   311,   893,   817,   818,
     819,   820,   438,   724,   157,   726,   725,   178,   727,   847,
     875,   374,   848,   876,   189,   171,   255,   256,   179,   312,
      84,   313,   183,   158,   206,   190,   159,   160,   161,   191,
     324,   244,   330,   225,   340,   207,   401,   402,   242,   669,
     670,   245,   243,   536,   537,   538,   831,   832,   833,   546,
     547,   548,   341,   352,   354,   355,   369,   276,   373,   375,
     403,   377,   378,   379,   380,   433,   385,   388,   390,   391,
     394,   395,   396,   404,   405,   406,   407,   408,   410,   411,
     412,   413,   418,   414,   419,   415,   420,   416,   421,   422,
     423,   417,   424,   425,   426,   427,   428,   429,   430,   432,
     444,   445,   446,   447,   448,   449,   450,   451,   452,   453,
     454,   455,   457,   459,   461,   460,   462,   465,   463,   466,
     467,   468,   469,   470,   471,   473,   474,   475,   476,   477,
     478,   479,   481,   485,   482,   483,   486,   488,   489,   490,
     491,   492,   495,   493,   494,   496,   500,   497,   506,   507,
     508,   498,   501,   499,   503,   527,   504,   533,   505,   509,
     510,   511,   512,   513,   514,   515,   516,   517,   593,   593,
     518,   519,   601,   601,   520,   521,   522,   523,   524,   660,
     528,   276,    28,   529,   530,   534,   436,   535,   540,   541,
     437,   543,   542,   544,   545,   549,   550,   438,   609,   567,
     613,   617,   551,   637,   677,   679,   683,   691,   552,   553,
     687,   702,   703,   704,   705,   706,   714,   531,   713,   717,
     716,   719,   720,   723,   729,   730,   554,   731,   560,   732,
     555,   733,   556,   734,   735,   736,   557,   741,   742,   743,
     757,   558,   756,   760,   759,   575,   763,   762,   766,   577,
     765,   559,   561,   768,   769,   770,   771,   777,   778,   798,
     562,   563,   799,   574,   804,   805,   808,   828,   807,   815,
     576,   816,   829,   869,   861,   841,   843,   865,   867,   751,
     754,   889,   871,   772,   890,   891,   894,   581,   773,   774,
     627,   608,   775,   776,   791,   792,   793,   431,   779,   786,
     409,   787,   434,   790,   789,   794,   795,   487,   797,   781,
     780,   783,   782,   796,   800,   810,   785,   480,   456,   784,
     809,   801,   802,   822,   484,   823,   812,   458,   811,   824,
     825,   826,   835,   813,   803,   836,   837,   838,   842,   472,
     866,   870,   814,   678,   464,   767,   899,   895,   806,   675,
     502,   896,   897,   859,   868,   887,   898,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   593,     0,   244,
     157,   601,     0,   225,     0,     0,   242,     0,     0,   245,
     243,   171,     0,     0,     0,     0,   257,     0,     0,   158,
       0,     0,   159,   160,   161,     0,     0,     0,     0,     0,
       0,     0,   660,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   178,     0,     0,   189,     0,     0,   206,
       0,     0,     0,     0,   179,     0,     0,   190,   183,     0,
     207,   191,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   852,     0,     0,     0,   853,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   852,     0,     0,     0,   853
  };

  const short int
  Dhcp6Parser::yycheck_[] =
  {
      62,    70,   521,    65,    66,    67,    68,    69,    70,    71,
      72,    70,    70,   518,    65,    66,    67,    68,     7,    66,
      67,   517,    65,    10,     0,    65,    65,    65,     5,    38,
       7,    11,     9,     7,    14,    15,    14,     7,    82,    83,
      49,     7,    31,    32,    33,    34,     7,    56,    75,    38,
       7,    31,    32,    33,    34,    35,    36,    37,    38,    48,
     128,    50,     7,   131,   132,   133,   149,    56,    57,    58,
      59,    60,    61,    62,     7,    16,     7,    16,    38,    38,
      38,    39,    71,    72,    25,     7,    66,    67,    68,    69,
      79,    39,    51,    52,    53,    54,    55,    56,    12,    13,
      39,    81,    41,    42,    84,   149,    45,    46,    47,    69,
      71,    91,    70,    73,    74,    75,    76,    77,    78,    99,
     100,    16,   149,   103,   118,   119,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,     3,     3,   125,     7,
     149,     8,     8,     7,    39,     3,     3,   134,   135,   136,
       8,     8,     7,     3,    95,    96,    97,    98,     8,     6,
     149,     3,   149,    39,    40,    41,    42,    43,    44,   149,
       4,     3,   149,   150,   151,   152,     8,    75,    76,   127,
      78,   129,   130,   121,   122,   123,   124,     8,     3,   149,
     149,   149,    85,    86,    87,    88,    89,    90,     3,     3,
       3,   149,     3,     8,     8,     8,     3,     8,   149,     4,
     149,     8,     3,     3,   152,     3,     8,     8,     8,     3,
       8,   726,     3,     3,     8,   744,     6,     8,   724,   137,
     138,   139,   140,   141,   142,   143,   144,   145,   146,   147,
     148,     3,   304,     3,     3,     3,     8,     3,     8,     8,
       8,     4,     8,     4,   149,   104,   105,   106,   107,   108,
     109,   110,   111,   112,   113,   114,   115,   116,   117,     3,
       3,   333,     3,   149,     8,   333,     4,     8,    17,    18,
      19,    20,   333,     3,   346,     3,     6,   349,     6,     3,
       3,     8,     6,     6,   356,   346,    82,    83,   349,     4,
     149,     4,   349,   346,   366,   356,   346,   346,   346,   356,
       4,   380,     4,   375,     4,   366,   294,   295,   380,   101,
     102,   380,   380,    63,    64,    65,    92,    93,    94,   465,
     466,   467,     4,     4,     4,     4,     4,   399,     4,     3,
     149,     4,     4,     8,     3,   152,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,   150,     4,   150,     4,   150,     4,   150,     4,     4,
       4,   150,     4,     4,     4,     4,   150,     4,     4,     4,
       4,     4,     4,     4,     4,     4,   150,   152,     4,     4,
       4,     4,     4,     4,     4,   150,   150,     4,   150,     4,
       4,     4,     4,     4,     4,     4,     4,   150,     4,     4,
       4,   152,     4,     4,   152,   152,     4,   152,     4,     4,
     150,     4,     4,   150,   150,     4,     4,   152,   406,   407,
     408,   152,     4,   152,     4,     8,     7,   149,     7,     7,
       7,     7,     5,     5,     5,     5,     5,     5,   510,   511,
       5,     5,   510,   511,     7,     7,     7,     7,     5,   521,
       3,   523,     7,     5,     5,   149,   528,   149,   149,     5,
     528,   149,     7,   149,   149,   149,   149,   528,     7,   120,
       7,     7,   149,     7,     4,     7,     7,    80,   149,   149,
       7,     4,     4,     4,     4,     4,     3,   446,     6,     3,
       6,     6,     3,     6,     6,     3,   149,     4,   486,     4,
     149,     4,   149,     4,     4,     4,   149,     4,     4,     4,
       3,   149,     6,     3,     6,   503,     3,     6,     4,   126,
       8,   149,   149,     4,     4,     4,     4,     4,     4,     4,
     149,   149,     4,   149,     4,     4,     3,     8,     6,     4,
     504,     5,     8,     5,     4,     8,     7,     4,     4,   149,
     149,     4,     7,   150,     4,     4,     4,   509,   152,   150,
     516,   511,   152,   150,   150,   150,   150,   327,   709,   721,
     304,   724,   331,   730,   728,   150,   150,   383,   737,   714,
     712,   717,   715,   150,   150,   757,   720,   375,   346,   718,
     755,   150,   150,   149,   380,   149,   760,   349,   758,   149,
     149,   149,   149,   761,   744,   149,   149,   149,   149,   366,
     150,   149,   763,   528,   356,   695,   149,   152,   748,   523,
     399,   150,   150,   847,   863,   875,   892,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   709,    -1,   718,
     712,   709,    -1,   715,    -1,    -1,   718,    -1,    -1,   718,
     718,   712,    -1,    -1,    -1,    -1,   728,    -1,    -1,   712,
      -1,    -1,   712,   712,   712,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   744,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   755,    -1,    -1,   758,    -1,    -1,   761,
      -1,    -1,    -1,    -1,   755,    -1,    -1,   758,   755,    -1,
     761,   758,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   846,    -1,    -1,    -1,   846,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   863,    -1,    -1,    -1,   863
  };

  const unsigned short int
  Dhcp6Parser::yystos_[] =
  {
       0,   137,   138,   139,   140,   141,   142,   143,   144,   145,
     146,   147,   148,   154,   155,   156,   157,   158,   159,   160,
     161,   162,   163,   164,   165,   166,     0,     5,     7,     9,
     149,   150,   151,   152,   167,   168,   169,   174,     7,   183,
       7,   189,     7,   200,     7,   277,     7,   342,     7,   356,
       7,   373,     7,   300,     7,   324,     7,   253,     7,   429,
     175,   170,   184,   190,   201,   278,   343,   357,   374,   301,
     325,   254,   430,   167,   176,   177,   149,   172,   173,    10,
     125,   134,   135,   136,   149,   182,   185,   186,   187,   456,
     458,   460,   462,    11,    14,    15,    31,    32,    33,    34,
      35,    36,    37,    38,    66,    67,    68,    69,    81,    84,
      91,    99,   100,   103,   182,   191,   192,   193,   194,   195,
     196,   197,   198,   207,   209,   233,   239,   245,   247,   261,
     271,   294,   318,   396,   406,   418,   419,   427,    12,    13,
     202,   203,   204,   206,     7,    48,    50,    56,    57,    58,
      59,    60,    61,    62,    71,    72,    79,   182,   193,   194,
     195,   196,   279,   280,   281,   283,   285,   287,   289,   292,
     293,   318,   336,   348,   350,   367,   392,    49,   182,   318,
     344,   345,   346,   348,    51,    52,    53,    54,    55,   182,
     318,   348,   358,   359,   360,   362,   363,   365,   366,    69,
      73,    74,    75,    76,    77,    78,   182,   318,   375,   376,
     377,   378,   380,   382,   384,   386,   388,   390,    16,    39,
      41,    42,    45,    46,    47,   182,   223,   302,   303,   304,
     305,   306,   307,   308,   310,   312,   314,   315,   317,    40,
      43,    44,   182,   223,   306,   312,   326,   327,   328,   329,
     330,   332,   333,   334,   335,    82,    83,   182,   255,   256,
     257,   259,   104,   105,   106,   107,   108,   109,   110,   111,
     112,   113,   114,   115,   116,   117,   182,   431,   432,   433,
     434,   436,   438,   439,   441,   442,   443,   446,   448,   449,
     450,   451,   454,     6,     3,     4,     8,     3,   188,   463,
     457,   459,   461,     4,     3,     8,   199,   208,   210,     4,
       4,     4,     4,     4,   272,   295,   319,   234,   246,   240,
     397,   248,   262,   407,     4,   420,   428,     3,     8,   205,
       4,     3,     8,   399,   337,   351,   349,   282,   284,   286,
       4,     4,   290,   288,   368,   393,     3,     8,   347,     3,
       8,   361,     4,   364,     4,     4,     3,     8,   391,   379,
     381,   383,   385,   387,   389,     8,     3,   309,   224,     4,
     313,   311,   316,     4,     8,     3,   331,     4,     4,     8,
       3,   258,   260,     3,     8,     4,   435,   437,     4,   440,
       4,     4,   444,   447,     4,     4,     4,   452,   455,     3,
       8,   167,   167,   149,     4,     4,     4,     4,     4,   186,
       4,     4,     4,   150,   150,   150,   150,   150,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,   150,     4,
       4,   192,     4,   152,   203,    70,   182,   223,   318,   400,
     401,   402,   403,   404,     4,     4,     4,     4,     4,     4,
     150,   152,     4,     4,     4,     4,   280,     4,   345,     4,
     150,     4,   150,   150,   359,     4,     4,     4,     4,     4,
       4,     4,   377,     4,     4,   150,     4,     4,     4,   152,
     304,     4,   152,   152,   328,     4,     4,   256,   152,     4,
       4,   150,     4,   150,   150,     4,     4,   152,   152,   152,
       4,     4,   432,     4,     7,     7,   167,   167,   167,     7,
       7,     7,     5,     5,     5,     5,     5,     5,     5,     5,
       7,     7,     7,     7,     5,   178,   405,     8,     3,     5,
       5,   169,   171,   149,   149,   149,    63,    64,    65,   291,
     149,     5,     7,   149,   149,   149,   178,   178,   178,   149,
     149,   149,   149,   149,   149,   149,   149,   149,   149,   149,
     167,   149,   149,   149,   118,   119,   445,   120,   121,   122,
     123,   124,   152,   453,   149,   167,   191,   126,   464,   465,
     466,   202,    16,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,   182,   211,   212,   213,   216,   218,   220,
     222,   223,   225,   226,   227,   228,   229,   231,   211,     7,
     273,   274,   275,     7,   296,   297,   298,     7,   320,   321,
     322,    75,   149,   235,   236,   237,   238,   176,    76,    78,
     237,   241,   242,   243,   244,   287,   398,     7,   249,   250,
     251,    85,    86,    87,    88,    89,    90,   263,   264,   265,
     266,   267,   268,   269,   270,    16,    95,    96,    97,    98,
     182,   225,   408,   409,   410,   413,   414,   416,   417,   101,
     102,   421,   422,   423,   425,   431,   179,     4,   402,     7,
     338,   339,   340,     7,   352,   353,   354,     7,   369,   370,
     371,    80,   394,     8,   467,     3,     8,     8,   214,   217,
     219,   221,     4,     4,     4,     4,     4,   230,   232,     3,
       8,     8,   276,     6,     3,   299,     6,     3,   323,     6,
       3,     3,     6,     6,     3,     6,     3,     6,   252,     6,
       3,     4,     4,     4,     4,     4,     4,     3,     8,   411,
     415,     4,     4,     4,     3,     8,   424,   426,     3,     8,
       8,   149,   180,   181,   149,   341,     6,     3,   355,     6,
       3,   372,     6,     3,   395,     8,     4,   465,     4,     4,
       4,     4,   150,   152,   150,   152,   150,     4,     4,   212,
     279,   275,   302,   298,   326,   322,   236,   242,   287,   255,
     251,   150,   150,   150,   150,   150,   150,   264,     4,     4,
     150,   150,   150,   409,     4,     4,   422,     6,     3,   344,
     340,   358,   354,   375,   371,     4,     5,    17,    18,    19,
      20,   215,   149,   149,   149,   149,   149,     8,     8,     8,
       8,    92,    93,    94,   412,   149,   149,   149,   149,     8,
       8,     8,   149,     7,   468,   469,   470,     3,     6,   127,
     129,   130,   182,   223,   471,   472,   473,   474,   476,   469,
     477,     4,   475,     3,     8,     4,   150,     4,   472,     5,
     149,     7,   478,   479,   480,     3,     6,   128,   131,   132,
     133,   481,   482,   483,   485,   486,   487,   479,   484,     4,
       4,     4,     3,     8,     4,   152,   150,   150,   482,   149
  };

  const unsigned short int
  Dhcp6Parser::yyr1_[] =
  {
       0,   153,   155,   154,   156,   154,   157,   154,   158,   154,
     159,   154,   160,   154,   161,   154,   162,   154,   163,   154,
     164,   154,   165,   154,   166,   154,   167,   167,   167,   167,
     167,   167,   167,   168,   170,   169,   171,   172,   172,   173,
     173,   175,   174,   176,   176,   177,   177,   179,   178,   180,
     180,   181,   181,   182,   184,   183,   185,   185,   186,   186,
     186,   186,   186,   186,   188,   187,   190,   189,   191,   191,
     192,   192,   192,   192,   192,   192,   192,   192,   192,   192,
     192,   192,   192,   192,   192,   192,   192,   192,   192,   192,
     192,   192,   193,   194,   195,   196,   197,   199,   198,   201,
     200,   202,   202,   203,   203,   205,   204,   206,   208,   207,
     210,   209,   211,   211,   212,   212,   212,   212,   212,   212,
     212,   212,   212,   212,   212,   212,   212,   214,   213,   215,
     215,   215,   215,   217,   216,   219,   218,   221,   220,   222,
     224,   223,   225,   226,   227,   228,   230,   229,   232,   231,
     234,   233,   235,   235,   236,   236,   237,   238,   240,   239,
     241,   241,   242,   242,   242,   243,   244,   246,   245,   248,
     247,   249,   249,   250,   250,   252,   251,   254,   253,   255,
     255,   255,   256,   256,   258,   257,   260,   259,   262,   261,
     263,   263,   264,   264,   264,   264,   264,   264,   265,   266,
     267,   268,   269,   270,   272,   271,   273,   273,   274,   274,
     276,   275,   278,   277,   279,   279,   280,   280,   280,   280,
     280,   280,   280,   280,   280,   280,   280,   280,   280,   280,
     280,   280,   280,   280,   282,   281,   284,   283,   286,   285,
     288,   287,   290,   289,   291,   291,   291,   292,   293,   295,
     294,   296,   296,   297,   297,   299,   298,   301,   300,   302,
     302,   303,   303,   304,   304,   304,   304,   304,   304,   304,
     304,   305,   306,   307,   309,   308,   311,   310,   313,   312,
     314,   316,   315,   317,   319,   318,   320,   320,   321,   321,
     323,   322,   325,   324,   326,   326,   327,   327,   328,   328,
     328,   328,   328,   328,   328,   329,   331,   330,   332,   333,
     334,   335,   337,   336,   338,   338,   339,   339,   341,   340,
     343,   342,   344,   344,   345,   345,   345,   345,   347,   346,
     349,   348,   351,   350,   352,   352,   353,   353,   355,   354,
     357,   356,   358,   358,   359,   359,   359,   359,   359,   359,
     359,   359,   361,   360,   362,   364,   363,   365,   366,   368,
     367,   369,   369,   370,   370,   372,   371,   374,   373,   375,
     375,   376,   376,   377,   377,   377,   377,   377,   377,   377,
     377,   377,   379,   378,   381,   380,   383,   382,   385,   384,
     387,   386,   389,   388,   391,   390,   393,   392,   395,   394,
     397,   396,   398,   398,   399,   287,   400,   400,   401,   401,
     402,   402,   402,   402,   403,   405,   404,   407,   406,   408,
     408,   409,   409,   409,   409,   409,   409,   409,   411,   410,
     412,   412,   412,   413,   415,   414,   416,   417,   418,   420,
     419,   421,   421,   422,   422,   424,   423,   426,   425,   428,
     427,   430,   429,   431,   431,   432,   432,   432,   432,   432,
     432,   432,   432,   432,   432,   432,   432,   432,   432,   432,
     433,   435,   434,   437,   436,   438,   440,   439,   441,   442,
     444,   443,   445,   445,   447,   446,   448,   449,   450,   452,
     451,   453,   453,   453,   453,   453,   455,   454,   457,   456,
     459,   458,   461,   460,   463,   462,   464,   464,   465,   467,
     466,   468,   468,   470,   469,   471,   471,   472,   472,   472,
     472,   472,   473,   475,   474,   477,   476,   478,   478,   480,
     479,   481,   481,   482,   482,   482,   482,   484,   483,   485,
     486,   487
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
       1,     1,     1,     1,     0,     4,     0,     4,     0,     4,
       0,     4,     0,     4,     1,     1,     1,     3,     3,     0,
       6,     0,     1,     1,     3,     0,     4,     0,     4,     0,
       1,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     3,     1,     0,     4,     0,     4,     0,     4,
       1,     0,     4,     3,     0,     6,     0,     1,     1,     3,
       0,     4,     0,     4,     0,     1,     1,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     0,     4,     1,     1,
       3,     3,     0,     6,     0,     1,     1,     3,     0,     4,
       0,     4,     1,     3,     1,     1,     1,     1,     0,     4,
       0,     4,     0,     6,     0,     1,     1,     3,     0,     4,
       0,     4,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     0,     4,     3,     0,     4,     3,     3,     0,
       6,     0,     1,     1,     3,     0,     4,     0,     4,     0,
       1,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     0,     4,     0,     4,     0,     4,     0,     4,
       0,     4,     0,     4,     0,     4,     0,     6,     0,     4,
       0,     6,     1,     3,     0,     4,     0,     1,     1,     3,
       1,     1,     1,     1,     1,     0,     4,     0,     6,     1,
       3,     1,     1,     1,     1,     1,     1,     1,     0,     4,
       1,     1,     1,     3,     0,     4,     3,     3,     3,     0,
       6,     1,     3,     1,     1,     0,     4,     0,     4,     0,
       6,     0,     4,     1,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       3,     0,     4,     0,     4,     3,     0,     4,     3,     3,
       0,     4,     1,     1,     0,     4,     3,     3,     3,     0,
       4,     1,     1,     1,     1,     1,     0,     4,     0,     4,
       0,     4,     0,     4,     0,     6,     1,     3,     1,     0,
       6,     1,     3,     0,     4,     1,     3,     1,     1,     1,
       1,     1,     3,     0,     4,     0,     6,     1,     3,     0,
       4,     1,     3,     1,     1,     1,     1,     0,     4,     3,
       3,     3
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
       0,   234,   234,   234,   235,   235,   236,   236,   237,   237,
     238,   238,   239,   239,   240,   240,   241,   241,   242,   242,
     243,   243,   244,   244,   245,   245,   253,   254,   255,   256,
     257,   258,   259,   262,   267,   267,   278,   281,   282,   285,
     289,   296,   296,   303,   304,   307,   311,   318,   318,   325,
     326,   329,   333,   344,   354,   354,   366,   367,   371,   372,
     373,   374,   375,   376,   379,   379,   396,   396,   404,   405,
     410,   411,   412,   413,   414,   415,   416,   417,   418,   419,
     420,   421,   422,   423,   424,   425,   426,   427,   428,   429,
     430,   431,   434,   439,   444,   449,   454,   459,   459,   469,
     469,   477,   478,   481,   482,   485,   485,   495,   501,   501,
     511,   511,   521,   522,   525,   526,   527,   528,   529,   530,
     531,   532,   533,   534,   535,   536,   537,   540,   540,   547,
     548,   549,   550,   553,   553,   561,   561,   569,   569,   577,
     582,   582,   590,   595,   600,   605,   610,   610,   618,   618,
     627,   627,   637,   638,   641,   642,   645,   650,   655,   655,
     665,   666,   669,   670,   671,   674,   679,   686,   686,   696,
     696,   706,   707,   710,   711,   714,   714,   722,   722,   730,
     731,   732,   735,   736,   739,   739,   747,   747,   755,   755,
     765,   766,   769,   770,   771,   772,   773,   774,   777,   782,
     787,   792,   797,   802,   810,   810,   823,   824,   827,   828,
     835,   835,   858,   858,   867,   868,   872,   873,   874,   875,
     876,   877,   878,   879,   880,   881,   882,   883,   884,   885,
     886,   887,   888,   889,   892,   892,   900,   900,   908,   908,
     916,   916,   924,   924,   931,   932,   933,   936,   941,   950,
     950,   962,   963,   966,   967,   972,   972,   983,   983,   993,
     994,   997,   998,  1001,  1002,  1003,  1004,  1005,  1006,  1007,
    1008,  1011,  1013,  1018,  1020,  1020,  1028,  1028,  1036,  1036,
    1044,  1046,  1046,  1054,  1063,  1063,  1075,  1076,  1081,  1082,
    1087,  1087,  1098,  1098,  1109,  1110,  1115,  1116,  1121,  1122,
    1123,  1124,  1125,  1126,  1127,  1130,  1132,  1132,  1140,  1142,
    1144,  1149,  1157,  1157,  1169,  1170,  1173,  1174,  1177,  1177,
    1185,  1185,  1193,  1194,  1197,  1198,  1199,  1200,  1203,  1203,
    1211,  1211,  1221,  1221,  1233,  1234,  1237,  1238,  1241,  1241,
    1249,  1249,  1257,  1258,  1261,  1262,  1263,  1264,  1265,  1266,
    1267,  1268,  1271,  1271,  1279,  1284,  1284,  1292,  1297,  1305,
    1305,  1315,  1316,  1319,  1320,  1323,  1323,  1331,  1331,  1339,
    1340,  1343,  1344,  1348,  1349,  1350,  1351,  1352,  1353,  1354,
    1355,  1356,  1359,  1359,  1369,  1369,  1379,  1379,  1387,  1387,
    1395,  1395,  1403,  1403,  1411,  1411,  1424,  1424,  1434,  1434,
    1445,  1445,  1455,  1456,  1459,  1459,  1467,  1468,  1471,  1472,
    1475,  1476,  1477,  1478,  1481,  1483,  1483,  1494,  1494,  1504,
    1505,  1508,  1509,  1510,  1511,  1512,  1513,  1514,  1517,  1517,
    1524,  1525,  1526,  1529,  1534,  1534,  1542,  1547,  1554,  1561,
    1561,  1571,  1572,  1575,  1576,  1579,  1579,  1587,  1587,  1597,
    1597,  1607,  1607,  1615,  1616,  1619,  1620,  1621,  1622,  1623,
    1624,  1625,  1626,  1627,  1628,  1629,  1630,  1631,  1632,  1633,
    1636,  1641,  1641,  1649,  1649,  1657,  1662,  1662,  1670,  1675,
    1680,  1680,  1688,  1689,  1692,  1692,  1700,  1705,  1710,  1715,
    1715,  1723,  1726,  1729,  1732,  1735,  1741,  1741,  1751,  1751,
    1758,  1758,  1765,  1765,  1778,  1778,  1791,  1792,  1796,  1800,
    1800,  1812,  1813,  1817,  1817,  1825,  1826,  1829,  1830,  1831,
    1832,  1833,  1836,  1841,  1841,  1849,  1849,  1859,  1860,  1863,
    1863,  1871,  1872,  1875,  1876,  1877,  1878,  1881,  1881,  1889,
    1894,  1899
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
#line 4325 "dhcp6_parser.cc" // lalr1.cc:1167
#line 1904 "dhcp6_parser.yy" // lalr1.cc:1168


void
isc::dhcp::Dhcp6Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
