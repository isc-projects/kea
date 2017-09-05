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
      case 160: // value
      case 164: // map_value
      case 202: // socket_type
      case 212: // db_type
      case 289: // hr_mode
      case 424: // ncr_protocol_value
      case 432: // replace_client_name_value
        value.move< ElementPtr > (that.value);
        break;

      case 145: // "boolean"
        value.move< bool > (that.value);
        break;

      case 144: // "floating point"
        value.move< double > (that.value);
        break;

      case 143: // "integer"
        value.move< int64_t > (that.value);
        break;

      case 142: // "constant string"
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
      case 160: // value
      case 164: // map_value
      case 202: // socket_type
      case 212: // db_type
      case 289: // hr_mode
      case 424: // ncr_protocol_value
      case 432: // replace_client_name_value
        value.copy< ElementPtr > (that.value);
        break;

      case 145: // "boolean"
        value.copy< bool > (that.value);
        break;

      case 144: // "floating point"
        value.copy< double > (that.value);
        break;

      case 143: // "integer"
        value.copy< int64_t > (that.value);
        break;

      case 142: // "constant string"
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
            case 142: // "constant string"

#line 218 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< std::string > (); }
#line 364 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 143: // "integer"

#line 218 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< int64_t > (); }
#line 371 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 144: // "floating point"

#line 218 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< double > (); }
#line 378 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 145: // "boolean"

#line 218 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< bool > (); }
#line 385 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 160: // value

#line 218 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 392 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 164: // map_value

#line 218 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 399 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 202: // socket_type

#line 218 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 406 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 212: // db_type

#line 218 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 413 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 289: // hr_mode

#line 218 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 420 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 424: // ncr_protocol_value

#line 218 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 427 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 432: // replace_client_name_value

#line 218 "dhcp4_parser.yy" // lalr1.cc:636
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
      case 160: // value
      case 164: // map_value
      case 202: // socket_type
      case 212: // db_type
      case 289: // hr_mode
      case 424: // ncr_protocol_value
      case 432: // replace_client_name_value
        yylhs.value.build< ElementPtr > ();
        break;

      case 145: // "boolean"
        yylhs.value.build< bool > ();
        break;

      case 144: // "floating point"
        yylhs.value.build< double > ();
        break;

      case 143: // "integer"
        yylhs.value.build< int64_t > ();
        break;

      case 142: // "constant string"
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
#line 227 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.NO_KEYWORD; }
#line 680 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 4:
#line 228 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.CONFIG; }
#line 686 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 6:
#line 229 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.DHCP4; }
#line 692 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 8:
#line 230 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.INTERFACES_CONFIG; }
#line 698 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 10:
#line 231 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.SUBNET4; }
#line 704 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 12:
#line 232 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.POOLS; }
#line 710 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 14:
#line 233 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.RESERVATIONS; }
#line 716 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 16:
#line 234 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.DHCP4; }
#line 722 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 18:
#line 235 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.OPTION_DEF; }
#line 728 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 20:
#line 236 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.OPTION_DATA; }
#line 734 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 22:
#line 237 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.HOOKS_LIBRARIES; }
#line 740 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 24:
#line 238 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.DHCP_DDNS; }
#line 746 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 26:
#line 246 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 752 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 27:
#line 247 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as< double > (), ctx.loc2pos(yystack_[0].location))); }
#line 758 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 28:
#line 248 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 764 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 29:
#line 249 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 770 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 30:
#line 250 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 776 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 31:
#line 251 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 782 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 32:
#line 252 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 788 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 33:
#line 255 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as< ElementPtr > ());
}
#line 797 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 34:
#line 260 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 808 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 35:
#line 265 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 818 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 36:
#line 271 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 824 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 39:
#line 278 "dhcp4_parser.yy" // lalr1.cc:859
    {
                  // map containing a single entry
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 833 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 40:
#line 282 "dhcp4_parser.yy" // lalr1.cc:859
    {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 843 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 41:
#line 289 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 852 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 42:
#line 292 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // list parsing complete. Put any sanity checking here
}
#line 860 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 45:
#line 300 "dhcp4_parser.yy" // lalr1.cc:859
    {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 869 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 46:
#line 304 "dhcp4_parser.yy" // lalr1.cc:859
    {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 878 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 47:
#line 311 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // List parsing about to start
}
#line 886 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 48:
#line 313 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // list parsing complete. Put any sanity checking here
    //ctx.stack_.pop_back();
}
#line 895 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 51:
#line 322 "dhcp4_parser.yy" // lalr1.cc:859
    {
                          ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 904 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 52:
#line 326 "dhcp4_parser.yy" // lalr1.cc:859
    {
                          ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 913 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 53:
#line 337 "dhcp4_parser.yy" // lalr1.cc:859
    {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as< std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 924 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 54:
#line 347 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 935 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 55:
#line 352 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.

    // Dhcp4 is required
    ctx.require("Dhcp4", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
}
#line 948 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 64:
#line 376 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Dhcp4", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP4);
}
#line 961 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 65:
#line 383 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // No global parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 971 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 66:
#line 391 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the Dhcp4 map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 981 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 67:
#line 395 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // No global parameter is required
    // parsing completed
}
#line 990 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 91:
#line 429 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 999 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 92:
#line 434 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 1008 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 93:
#line 439 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 1017 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 94:
#line 444 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr dpp(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 1026 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 95:
#line 449 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr echo(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("echo-client-id", echo);
}
#line 1035 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 96:
#line 454 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr match(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("match-client-id", match);
}
#line 1044 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 97:
#line 460 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces-config", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.INTERFACES_CONFIG);
}
#line 1055 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 98:
#line 465 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // No interfaces config param is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1065 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 104:
#line 480 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1075 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 105:
#line 484 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // No interfaces config param is required
    // parsing completed
}
#line 1084 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 106:
#line 489 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1095 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 107:
#line 494 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1104 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 108:
#line 499 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.DHCP_SOCKET_TYPE);
}
#line 1112 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 109:
#line 501 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("dhcp-socket-type", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1121 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 110:
#line 506 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("raw", ctx.loc2pos(yystack_[0].location))); }
#line 1127 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 111:
#line 507 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("udp", ctx.loc2pos(yystack_[0].location))); }
#line 1133 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 112:
#line 510 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("re-detect", b);
}
#line 1142 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 113:
#line 516 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lease-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.LEASE_DATABASE);
}
#line 1153 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 114:
#line 521 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1164 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 115:
#line 528 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1175 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 116:
#line 533 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1186 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 132:
#line 559 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.DATABASE_TYPE);
}
#line 1194 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 133:
#line 561 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("type", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1203 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 134:
#line 566 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("memfile", ctx.loc2pos(yystack_[0].location))); }
#line 1209 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 135:
#line 567 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("mysql", ctx.loc2pos(yystack_[0].location))); }
#line 1215 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 136:
#line 568 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("postgresql", ctx.loc2pos(yystack_[0].location))); }
#line 1221 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 137:
#line 569 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("cql", ctx.loc2pos(yystack_[0].location))); }
#line 1227 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 138:
#line 572 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1235 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 139:
#line 574 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr user(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1245 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 140:
#line 580 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1253 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 141:
#line 582 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr pwd(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 1263 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 142:
#line 588 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1271 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 143:
#line 590 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr h(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 1281 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 144:
#line 596 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr p(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", p);
}
#line 1290 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 145:
#line 601 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1298 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 146:
#line 603 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1308 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 147:
#line 609 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 1317 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 148:
#line 614 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 1326 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 149:
#line 619 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 1335 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 150:
#line 624 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("connect-timeout", n);
}
#line 1344 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 151:
#line 629 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1352 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 152:
#line 631 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr cp(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("contact-points", cp);
    ctx.leave();
}
#line 1362 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 153:
#line 637 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1370 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 154:
#line 639 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr ks(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("keyspace", ks);
    ctx.leave();
}
#line 1380 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 155:
#line 646 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 1391 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 156:
#line 651 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1400 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 164:
#line 667 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1409 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 165:
#line 672 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 1418 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 166:
#line 677 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr circuit(new StringElement("circuit-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(circuit);
}
#line 1427 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 167:
#line 682 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr client(new StringElement("client-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(client);
}
#line 1436 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 168:
#line 687 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr flex_id(new StringElement("flex-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(flex_id);
}
#line 1445 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 169:
#line 692 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 1456 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 170:
#line 697 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1465 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 175:
#line 710 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1475 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 176:
#line 714 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1485 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 177:
#line 720 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1495 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 178:
#line 724 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 1505 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 184:
#line 739 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1513 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 185:
#line 741 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr lib(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 1523 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 186:
#line 747 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1531 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 187:
#line 749 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1540 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 188:
#line 755 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.EXPIRED_LEASES_PROCESSING);
}
#line 1551 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 189:
#line 760 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // No expired lease parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1561 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 198:
#line 778 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 1570 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 199:
#line 783 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 1579 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 200:
#line 788 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 1588 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 201:
#line 793 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 1597 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 202:
#line 798 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 1606 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 203:
#line 803 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 1615 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 204:
#line 811 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet4", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET4);
}
#line 1626 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 205:
#line 816 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1635 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 210:
#line 836 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1645 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 211:
#line 840 "dhcp4_parser.yy" // lalr1.cc:859
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

    // The subnet subnet4 parameter is required
    ctx.require("subnet", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1671 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 212:
#line 862 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the subnet4 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1681 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 213:
#line 866 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The subnet subnet4 parameter is required
    ctx.require("subnet", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 1691 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 237:
#line 901 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1699 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 238:
#line 903 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr subnet(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 1709 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 239:
#line 909 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1717 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 240:
#line 911 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface", iface);
    ctx.leave();
}
#line 1727 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 241:
#line 917 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1735 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 242:
#line 919 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface-id", iface);
    ctx.leave();
}
#line 1745 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 243:
#line 925 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1753 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 244:
#line 927 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-subnet", iface);
    ctx.leave();
}
#line 1763 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 245:
#line 933 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1771 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 246:
#line 935 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 1781 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 247:
#line 941 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1789 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 248:
#line 943 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface-id", iface);
    ctx.leave();
}
#line 1799 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 249:
#line 949 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.CLIENT_CLASS);
}
#line 1807 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 250:
#line 951 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr cls(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 1817 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 251:
#line 957 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.RESERVATION_MODE);
}
#line 1825 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 252:
#line 959 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("reservation-mode", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1834 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 253:
#line 964 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("disabled", ctx.loc2pos(yystack_[0].location))); }
#line 1840 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 254:
#line 965 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("out-of-pool", ctx.loc2pos(yystack_[0].location))); }
#line 1846 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 255:
#line 966 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("all", ctx.loc2pos(yystack_[0].location))); }
#line 1852 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 256:
#line 969 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr id(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 1861 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 257:
#line 974 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr rc(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rapid-commit", rc);
}
#line 1870 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 258:
#line 983 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 1881 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 259:
#line 988 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1890 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 260:
#line 996 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1899 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 261:
#line 999 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1907 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 266:
#line 1015 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1917 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 267:
#line 1019 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1929 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 268:
#line 1030 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1939 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 269:
#line 1034 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 1951 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 283:
#line 1064 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr code(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 1960 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 285:
#line 1071 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1968 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 286:
#line 1073 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 1978 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 287:
#line 1079 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1986 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 288:
#line 1081 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 1996 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 289:
#line 1087 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2004 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 290:
#line 1089 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr space(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 2014 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 292:
#line 1097 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2022 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 293:
#line 1099 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr encap(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 2032 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 294:
#line 1105 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr array(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 2041 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 295:
#line 1114 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 2052 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 296:
#line 1119 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2061 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 301:
#line 1138 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2071 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 302:
#line 1142 "dhcp4_parser.yy" // lalr1.cc:859
    {
    /// @todo: the code or name parameters are required.
    ctx.stack_.pop_back();
}
#line 2080 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 303:
#line 1150 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2090 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 304:
#line 1154 "dhcp4_parser.yy" // lalr1.cc:859
    {
    /// @todo: the code or name parameters are required.
    // parsing completed
}
#line 2099 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 317:
#line 1185 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2107 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 318:
#line 1187 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr data(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 2117 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 321:
#line 1197 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr space(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", space);
}
#line 2126 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 322:
#line 1202 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr persist(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-send", persist);
}
#line 2135 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 323:
#line 1210 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 2146 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 324:
#line 1215 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2155 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 329:
#line 1230 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2165 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 330:
#line 1234 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2175 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 331:
#line 1240 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2185 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 332:
#line 1244 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2195 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 339:
#line 1260 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2203 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 340:
#line 1262 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr pool(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 2213 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 341:
#line 1268 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2221 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 342:
#line 1270 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("user-context", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2230 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 343:
#line 1278 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 2241 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 344:
#line 1283 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2250 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 349:
#line 1296 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2260 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 350:
#line 1300 "dhcp4_parser.yy" // lalr1.cc:859
    {
    /// @todo: an identifier parameter is required.
    ctx.stack_.pop_back();
}
#line 2269 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 351:
#line 1305 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2279 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 352:
#line 1309 "dhcp4_parser.yy" // lalr1.cc:859
    {
    /// @todo: an identifier parameter is required.
    // parsing completed
}
#line 2288 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 370:
#line 1338 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2296 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 371:
#line 1340 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr next_server(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("next-server", next_server);
    ctx.leave();
}
#line 2306 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 372:
#line 1346 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2314 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 373:
#line 1348 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr srv(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-hostname", srv);
    ctx.leave();
}
#line 2324 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 374:
#line 1354 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2332 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 375:
#line 1356 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr bootfile(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("boot-file-name", bootfile);
    ctx.leave();
}
#line 2342 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 376:
#line 1362 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2350 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 377:
#line 1364 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr addr(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", addr);
    ctx.leave();
}
#line 2360 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 378:
#line 1370 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2368 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 379:
#line 1372 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr d(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 2378 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 380:
#line 1378 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2386 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 381:
#line 1380 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 2396 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 382:
#line 1386 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2404 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 383:
#line 1388 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-id", hw);
    ctx.leave();
}
#line 2414 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 384:
#line 1394 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2422 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 385:
#line 1396 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("circuit-id", hw);
    ctx.leave();
}
#line 2432 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 386:
#line 1402 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2440 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 387:
#line 1404 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flex-id", hw);
    ctx.leave();
}
#line 2450 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 388:
#line 1410 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2458 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 389:
#line 1412 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr host(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 2468 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 390:
#line 1418 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2479 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 391:
#line 1423 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2488 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 392:
#line 1431 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 2499 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 393:
#line 1436 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2508 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 394:
#line 1441 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2516 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 395:
#line 1443 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr ip(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", ip);
    ctx.leave();
}
#line 2526 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 396:
#line 1452 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 2537 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 397:
#line 1457 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2546 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 400:
#line 1466 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2556 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 401:
#line 1470 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The name client class parameter is required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2566 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 414:
#line 1495 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2574 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 415:
#line 1497 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr test(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 2584 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 416:
#line 1507 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 2593 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 417:
#line 1514 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 2604 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 418:
#line 1519 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2613 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 423:
#line 1532 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2621 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 424:
#line 1534 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr stype(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 2631 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 425:
#line 1540 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2639 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 426:
#line 1542 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 2649 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 427:
#line 1550 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 2660 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 428:
#line 1555 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2671 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 429:
#line 1562 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2681 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 430:
#line 1566 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2691 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 448:
#line 1593 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 2700 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 449:
#line 1598 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2708 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 450:
#line 1600 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("qualifying-suffix", s);
    ctx.leave();
}
#line 2718 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 451:
#line 1606 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2726 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 452:
#line 1608 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 2736 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 453:
#line 1614 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 2745 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 454:
#line 1619 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2753 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 455:
#line 1621 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 2763 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 456:
#line 1627 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 2772 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 457:
#line 1632 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 2781 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 458:
#line 1637 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 2789 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 459:
#line 1639 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2798 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 460:
#line 1645 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 2804 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 461:
#line 1646 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 2810 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 462:
#line 1649 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NCR_FORMAT);
}
#line 2818 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 463:
#line 1651 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 2828 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 464:
#line 1657 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-include-fqdn", b);
}
#line 2837 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 465:
#line 1662 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-no-update", b);
}
#line 2846 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 466:
#line 1667 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-client-update", b);
}
#line 2855 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 467:
#line 1672 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 2863 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 468:
#line 1674 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("replace-client-name", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2872 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 469:
#line 1680 "dhcp4_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("when-present", ctx.loc2pos(yystack_[0].location))); 
      }
#line 2880 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 470:
#line 1683 "dhcp4_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location)));
      }
#line 2888 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 471:
#line 1686 "dhcp4_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("always", ctx.loc2pos(yystack_[0].location)));
      }
#line 2896 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 472:
#line 1689 "dhcp4_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("when-not-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 2904 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 473:
#line 1692 "dhcp4_parser.yy" // lalr1.cc:859
    {
      error(yystack_[0].location, "boolean values for the replace-client-name are "
                "no longer supported");
      }
#line 2913 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 474:
#line 1698 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2921 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 475:
#line 1700 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("generated-prefix", s);
    ctx.leave();
}
#line 2931 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 476:
#line 1708 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2939 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 477:
#line 1710 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("Dhcp6", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2948 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 478:
#line 1715 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2956 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 479:
#line 1717 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("DhcpDdns", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2965 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 480:
#line 1722 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2973 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 481:
#line 1724 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("Control-agent", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2982 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 482:
#line 1734 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Logging", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.LOGGING);
}
#line 2993 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 483:
#line 1739 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3002 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 487:
#line 1756 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 3013 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 488:
#line 1761 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3022 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 491:
#line 1773 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 3032 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 492:
#line 1777 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 3040 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 500:
#line 1792 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr dl(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 3049 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 501:
#line 1797 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3057 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 502:
#line 1799 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 3067 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 503:
#line 1805 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 3078 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 504:
#line 1810 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3087 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 507:
#line 1819 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3097 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 508:
#line 1823 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 3105 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 515:
#line 1837 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3113 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 516:
#line 1839 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 3123 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 517:
#line 1845 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr flush(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 3132 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 518:
#line 1850 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr maxsize(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 3141 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 519:
#line 1855 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr maxver(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 3150 "dhcp4_parser.cc" // lalr1.cc:859
    break;


#line 3154 "dhcp4_parser.cc" // lalr1.cc:859
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


  const short int Dhcp4Parser::yypact_ninf_ = -496;

  const signed char Dhcp4Parser::yytable_ninf_ = -1;

  const short int
  Dhcp4Parser::yypact_[] =
  {
     231,  -496,  -496,  -496,  -496,  -496,  -496,  -496,  -496,  -496,
    -496,  -496,  -496,    31,    20,    33,    55,    71,    83,    90,
     105,   115,   143,   145,   149,   175,  -496,  -496,  -496,  -496,
    -496,  -496,  -496,  -496,  -496,  -496,  -496,  -496,  -496,  -496,
    -496,  -496,  -496,  -496,  -496,  -496,  -496,  -496,  -496,  -496,
    -496,  -496,  -496,  -496,  -496,  -496,  -496,  -496,  -496,  -496,
      20,   -68,    18,    84,   163,    19,     9,   109,    69,    62,
      88,   -51,   237,  -496,   177,   197,   221,   233,   236,  -496,
    -496,  -496,  -496,  -496,   246,  -496,    27,  -496,  -496,  -496,
    -496,  -496,  -496,  -496,   251,   252,  -496,  -496,  -496,   253,
     254,   255,   256,  -496,  -496,  -496,  -496,  -496,  -496,  -496,
     257,  -496,  -496,  -496,    53,  -496,  -496,  -496,  -496,  -496,
    -496,  -496,  -496,  -496,  -496,  -496,  -496,  -496,  -496,  -496,
    -496,  -496,  -496,  -496,  -496,  -496,  -496,  -496,   259,    67,
    -496,  -496,  -496,  -496,  -496,  -496,  -496,  -496,  -496,  -496,
    -496,  -496,  -496,   260,   261,  -496,  -496,  -496,  -496,  -496,
    -496,  -496,  -496,  -496,    68,  -496,  -496,  -496,  -496,  -496,
    -496,  -496,  -496,  -496,  -496,  -496,  -496,  -496,  -496,  -496,
    -496,  -496,  -496,  -496,  -496,    86,  -496,  -496,  -496,  -496,
    -496,  -496,  -496,  -496,  -496,  -496,  -496,  -496,  -496,  -496,
    -496,   258,   264,  -496,  -496,  -496,  -496,  -496,  -496,  -496,
    -496,  -496,  -496,  -496,  -496,   262,  -496,  -496,   267,  -496,
    -496,  -496,   268,  -496,  -496,   265,   271,  -496,  -496,  -496,
    -496,  -496,  -496,  -496,  -496,  -496,  -496,  -496,   272,   273,
    -496,  -496,  -496,  -496,   274,   276,  -496,  -496,  -496,  -496,
    -496,  -496,  -496,  -496,  -496,  -496,    96,  -496,  -496,  -496,
     277,  -496,  -496,   282,  -496,   284,   285,  -496,  -496,   286,
     287,   290,  -496,  -496,  -496,   112,  -496,  -496,  -496,  -496,
    -496,  -496,  -496,  -496,  -496,  -496,  -496,  -496,  -496,  -496,
    -496,  -496,    20,    20,  -496,   126,   291,   293,   295,   297,
     298,  -496,    18,  -496,   302,   130,   135,   303,   307,   308,
     170,   173,   174,   176,   314,   316,   317,   318,   319,   320,
     322,   186,   324,   326,    84,  -496,   327,   328,   188,   163,
    -496,    24,   345,   346,   347,   348,   349,   350,   351,   352,
     214,   230,   369,   370,   372,   373,    19,  -496,   374,     9,
    -496,   376,   377,   378,   379,   380,   381,   382,   383,   384,
     385,  -496,   109,  -496,   386,   387,   249,   389,   390,   391,
     263,  -496,    62,   392,   266,   269,  -496,    88,   393,   394,
       3,  -496,   270,   395,   396,   275,   397,   278,   279,   398,
     399,   280,   281,   283,   400,   401,   237,  -496,  -496,  -496,
     402,   403,   405,    20,    20,    20,  -496,   406,  -496,  -496,
     288,   409,   410,  -496,  -496,  -496,  -496,   404,   414,   415,
     418,   419,   422,   424,  -496,   425,   426,  -496,   429,   120,
    -496,  -496,  -496,  -496,  -496,  -496,  -496,  -496,  -496,   421,
     432,  -496,  -496,  -496,   294,   296,   301,   434,   430,   304,
     305,   309,  -496,  -496,   185,   310,   439,   438,  -496,   311,
    -496,   312,   313,   429,   321,   323,   325,   329,   330,   331,
     332,  -496,   334,   335,  -496,   336,   337,   339,  -496,  -496,
     340,  -496,  -496,  -496,   341,    20,  -496,  -496,   342,   343,
    -496,   344,  -496,  -496,    21,   355,  -496,  -496,  -496,    57,
     353,  -496,    20,    84,   368,  -496,  -496,  -496,   163,  -496,
      17,    17,   443,   449,   453,   121,    25,   454,   118,    73,
     237,  -496,  -496,  -496,  -496,  -496,   458,  -496,    24,  -496,
    -496,  -496,   457,  -496,  -496,  -496,  -496,  -496,  -496,  -496,
    -496,  -496,  -496,   462,   388,  -496,  -496,  -496,  -496,  -496,
    -496,  -496,  -496,  -496,  -496,  -496,  -496,  -496,  -496,  -496,
    -496,  -496,  -496,  -496,  -496,  -496,  -496,  -496,  -496,  -496,
    -496,  -496,  -496,  -496,  -496,  -496,  -496,  -496,  -496,   140,
    -496,   141,  -496,  -496,   150,  -496,  -496,  -496,  -496,   484,
     485,   486,   487,   488,  -496,  -496,  -496,   209,  -496,  -496,
    -496,  -496,  -496,  -496,  -496,  -496,  -496,  -496,  -496,  -496,
    -496,   212,  -496,   490,   491,  -496,  -496,   492,   494,  -496,
    -496,   493,   497,  -496,  -496,  -496,  -496,  -496,  -496,    36,
    -496,  -496,  -496,  -496,  -496,  -496,  -496,   187,  -496,   495,
     499,  -496,   489,   500,   501,   502,   503,   504,   213,  -496,
    -496,  -496,  -496,  -496,  -496,  -496,  -496,  -496,   215,  -496,
    -496,  -496,   216,   361,   367,  -496,  -496,   505,   507,  -496,
    -496,   506,   510,  -496,  -496,   508,  -496,   511,   368,  -496,
    -496,   513,   514,   515,   516,   371,   407,   408,   411,   412,
     517,   518,    17,  -496,  -496,    19,  -496,   443,    62,  -496,
     449,    88,  -496,   453,   121,  -496,    25,  -496,   -51,  -496,
     454,   416,   417,   420,   423,   427,   428,   118,  -496,   519,
     520,    73,  -496,  -496,  -496,   521,   522,  -496,     9,  -496,
     457,   109,  -496,   462,   524,  -496,   525,  -496,   217,   431,
     433,   435,  -496,  -496,  -496,  -496,  -496,   436,   437,  -496,
     219,  -496,   523,  -496,   526,  -496,  -496,  -496,   225,  -496,
    -496,  -496,  -496,  -496,  -496,  -496,  -496,   440,   441,  -496,
    -496,   442,   226,  -496,   527,  -496,   444,   529,  -496,  -496,
    -496,  -496,  -496,  -496,  -496,  -496,  -496,  -496,  -496,  -496,
    -496,  -496,  -496,  -496,  -496,  -496,  -496,  -496,  -496,   232,
    -496,    72,   529,  -496,  -496,   528,  -496,  -496,  -496,   228,
    -496,  -496,  -496,  -496,  -496,   533,   445,   534,    72,  -496,
     535,  -496,   447,  -496,   532,  -496,  -496,   243,  -496,   -16,
     532,  -496,  -496,   537,   538,   539,   229,  -496,  -496,  -496,
    -496,  -496,  -496,   540,   413,   448,   450,   -16,  -496,   452,
    -496,  -496,  -496,  -496,  -496
  };

  const unsigned short int
  Dhcp4Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,    24,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     1,    41,    34,    30,
      29,    26,    27,    28,    33,     3,    31,    32,    54,     5,
      66,     7,   104,     9,   212,    11,   331,    13,   351,    15,
     260,    17,   268,    19,   303,    21,   177,    23,   429,    25,
      43,    37,     0,     0,     0,     0,     0,   353,     0,   270,
     305,     0,     0,    45,     0,    44,     0,     0,    38,    64,
     482,   476,   478,   480,     0,    63,     0,    56,    58,    60,
      61,    62,    59,    97,     0,     0,   370,   113,   115,     0,
       0,     0,     0,   204,   258,   295,   155,   396,   169,   188,
       0,   417,   427,    90,     0,    68,    70,    71,    72,    73,
      87,    88,    75,    76,    77,    78,    82,    83,    74,    80,
      81,    89,    79,    84,    85,    86,   106,   108,     0,     0,
      99,   101,   102,   103,   400,   239,   241,   243,   323,   341,
     237,   245,   247,     0,     0,   251,   249,   343,   392,   236,
     216,   217,   218,   230,     0,   214,   221,   232,   233,   234,
     222,   223,   226,   228,   224,   225,   219,   220,   235,   227,
     231,   229,   339,   338,   336,     0,   333,   335,   337,   372,
     374,   390,   378,   380,   384,   382,   388,   386,   376,   369,
     365,     0,   354,   355,   366,   367,   368,   362,   357,   363,
     359,   360,   361,   364,   358,     0,   285,   145,     0,   289,
     287,   292,     0,   281,   282,     0,   271,   272,   274,   284,
     275,   276,   277,   291,   278,   279,   280,   317,     0,     0,
     315,   316,   319,   320,     0,   306,   307,   309,   310,   311,
     312,   313,   314,   184,   186,   181,     0,   179,   182,   183,
       0,   449,   451,     0,   454,     0,     0,   458,   462,     0,
       0,     0,   467,   474,   447,     0,   431,   433,   434,   435,
     436,   437,   438,   439,   440,   441,   442,   443,   444,   445,
     446,    42,     0,     0,    35,     0,     0,     0,     0,     0,
       0,    53,     0,    55,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    67,     0,     0,     0,     0,
     105,   402,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   213,     0,     0,
     332,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   352,     0,   261,     0,     0,     0,     0,     0,     0,
       0,   269,     0,     0,     0,     0,   304,     0,     0,     0,
       0,   178,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   430,    46,    39,
       0,     0,     0,     0,     0,     0,    57,     0,    95,    96,
       0,     0,     0,    91,    92,    93,    94,     0,     0,     0,
       0,     0,     0,     0,   416,     0,     0,    69,     0,     0,
     112,   100,   414,   412,   413,   408,   409,   410,   411,     0,
     403,   404,   406,   407,     0,     0,     0,     0,     0,     0,
       0,     0,   256,   257,     0,     0,     0,     0,   215,     0,
     334,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   356,     0,     0,   283,     0,     0,     0,   294,   273,
       0,   321,   322,   308,     0,     0,   180,   448,     0,     0,
     453,     0,   456,   457,     0,     0,   464,   465,   466,     0,
       0,   432,     0,     0,     0,   477,   479,   481,     0,   371,
       0,     0,   206,   262,   297,     0,     0,   171,     0,     0,
       0,    47,   107,   110,   111,   109,     0,   401,     0,   240,
     242,   244,   325,    36,   342,   238,   246,   248,   253,   254,
     255,   252,   250,   345,     0,   340,   373,   375,   391,   379,
     381,   385,   383,   389,   387,   377,   286,   146,   290,   288,
     293,   318,   185,   187,   450,   452,   455,   460,   461,   459,
     463,   469,   470,   471,   472,   473,   468,   475,    40,     0,
     487,     0,   484,   486,     0,   132,   138,   140,   142,     0,
       0,     0,     0,     0,   151,   153,   131,     0,   117,   119,
     120,   121,   122,   123,   124,   125,   126,   127,   128,   129,
     130,     0,   210,     0,   207,   208,   266,     0,   263,   264,
     301,     0,   298,   299,   164,   165,   166,   167,   168,     0,
     157,   159,   160,   161,   162,   163,   398,     0,   175,     0,
     172,   173,     0,     0,     0,     0,     0,     0,     0,   190,
     192,   193,   194,   195,   196,   197,   423,   425,     0,   419,
     421,   422,     0,    49,     0,   405,   329,     0,   326,   327,
     349,     0,   346,   347,   394,     0,    65,     0,     0,   483,
      98,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   114,   116,     0,   205,     0,   270,   259,
       0,   305,   296,     0,     0,   156,     0,   397,     0,   170,
       0,     0,     0,     0,     0,     0,     0,     0,   189,     0,
       0,     0,   418,   428,    51,     0,    50,   415,     0,   324,
       0,   353,   344,     0,     0,   393,     0,   485,     0,     0,
       0,     0,   144,   147,   148,   149,   150,     0,     0,   118,
       0,   209,     0,   265,     0,   300,   158,   399,     0,   174,
     198,   199,   200,   201,   202,   203,   191,     0,     0,   420,
      48,     0,     0,   328,     0,   348,     0,     0,   134,   135,
     136,   137,   133,   139,   141,   143,   152,   154,   211,   267,
     302,   176,   424,   426,    52,   330,   350,   395,   491,     0,
     489,     0,     0,   488,   503,     0,   501,   499,   495,     0,
     493,   497,   498,   496,   490,     0,     0,     0,     0,   492,
       0,   500,     0,   494,     0,   502,   507,     0,   505,     0,
       0,   504,   515,     0,     0,     0,     0,   509,   511,   512,
     513,   514,   506,     0,     0,     0,     0,     0,   508,     0,
     517,   518,   519,   510,   516
  };

  const short int
  Dhcp4Parser::yypgoto_[] =
  {
    -496,  -496,  -496,  -496,  -496,  -496,  -496,  -496,  -496,  -496,
    -496,  -496,  -496,  -496,   -45,  -496,    78,  -496,  -496,  -496,
    -496,  -496,  -496,  -496,  -496,   -56,  -496,  -496,  -496,   -62,
    -496,  -496,  -496,   227,  -496,  -496,  -496,  -496,    30,   222,
     -54,   -43,   -42,  -496,  -496,   -41,  -496,  -496,    37,   218,
    -496,  -496,  -496,  -496,  -496,  -496,  -496,  -496,  -496,  -496,
    -496,  -496,    38,  -144,  -496,  -496,  -496,  -496,  -496,  -496,
    -496,  -496,  -496,  -496,   -69,  -496,  -496,  -496,  -496,  -496,
    -496,  -496,  -496,  -496,  -496,  -496,  -496,  -154,  -496,  -496,
    -496,  -496,  -496,  -496,  -496,  -496,  -496,  -157,  -496,  -496,
    -496,  -151,   181,  -496,  -496,  -496,  -496,  -496,  -496,  -496,
    -163,  -496,  -496,  -496,  -496,  -496,  -496,  -496,  -496,  -496,
    -496,  -135,  -496,  -496,  -496,  -131,   223,  -496,  -496,  -496,
    -496,  -496,  -496,  -496,  -496,  -496,  -496,  -496,  -496,  -495,
    -496,  -496,  -496,  -496,  -496,  -496,   512,  -496,  -496,  -496,
    -496,  -496,  -133,  -496,  -496,  -496,  -130,  -496,   193,  -496,
     -52,  -496,  -496,  -496,  -496,  -496,   -50,  -496,  -496,  -496,
    -496,  -496,   -53,  -496,  -496,  -496,  -129,  -496,  -496,  -496,
    -125,  -496,   195,  -496,  -496,  -496,  -496,  -496,  -496,  -496,
    -496,  -496,  -496,  -496,  -149,  -496,  -496,  -496,  -143,   238,
    -496,  -496,   -64,  -496,  -496,  -496,  -496,  -496,  -141,  -496,
    -496,  -496,  -136,  -496,   234,   -48,  -496,  -325,  -496,  -315,
    -496,  -496,  -496,  -496,  -496,  -496,  -496,  -496,  -496,  -496,
    -496,  -496,  -496,  -496,  -496,  -496,  -496,  -496,  -496,  -496,
    -496,  -496,  -496,  -496,  -496,  -496,  -496,    70,  -496,  -496,
    -496,  -496,  -496,  -496,  -496,  -124,  -496,  -496,  -496,  -496,
    -496,  -496,  -496,  -496,    79,   194,  -496,  -496,  -496,  -496,
    -496,  -496,  -496,  -496,  -496,  -496,  -496,  -496,  -496,  -496,
    -496,  -496,  -496,  -496,  -496,  -496,  -496,  -496,  -496,  -496,
    -496,  -496,  -496,  -496,  -496,  -496,  -496,  -496,   -78,  -496,
    -496,  -496,  -201,  -496,  -496,  -216,  -496,  -496,  -496,  -496,
    -496,  -496,  -227,  -496,  -496,  -243,  -496,  -496,  -496,  -496,
    -496
  };

  const short int
  Dhcp4Parser::yydefgoto_[] =
  {
      -1,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    34,    35,    36,    61,   534,    77,
      78,    37,    60,    74,    75,   522,   663,   725,   726,   113,
      39,    62,    86,    87,    88,   296,    41,    63,   114,   115,
     116,   117,   118,   119,   120,   121,   122,   304,   139,   140,
      43,    64,   141,   326,   142,   327,   525,   143,   123,   308,
     124,   309,   597,   598,   599,   681,   782,   600,   682,   601,
     683,   602,   684,   603,   224,   365,   605,   606,   607,   608,
     609,   690,   610,   691,   125,   317,   629,   630,   631,   632,
     633,   634,   635,   126,   319,   639,   640,   641,   708,    57,
      71,   256,   257,   258,   378,   259,   379,   127,   320,   648,
     649,   650,   651,   652,   653,   654,   655,   128,   314,   613,
     614,   615,   695,    45,    65,   164,   165,   166,   337,   167,
     332,   168,   333,   169,   334,   170,   338,   171,   339,   172,
     343,   173,   342,   541,   174,   175,   129,   315,    51,    68,
     617,   618,   619,   698,    53,    69,   225,   226,   227,   228,
     229,   230,   231,   364,   232,   368,   233,   367,   234,   235,
     369,   236,   130,   316,   621,   622,   623,   701,    55,    70,
     244,   245,   246,   247,   248,   373,   249,   250,   251,   252,
     177,   335,   667,   668,   669,   728,    47,    66,   185,   186,
     187,   348,   178,   336,   179,   344,   671,   672,   673,   731,
      49,    67,   201,   202,   203,   131,   307,   205,   351,   206,
     352,   207,   360,   208,   354,   209,   355,   210,   357,   211,
     356,   212,   359,   213,   358,   214,   353,   181,   345,   675,
     734,   132,   318,   637,   331,   439,   440,   441,   442,   443,
     526,   133,   134,   322,   658,   659,   660,   719,   661,   720,
     135,   323,    59,    72,   275,   276,   277,   278,   383,   279,
     384,   280,   281,   386,   282,   283,   284,   389,   569,   285,
     390,   286,   287,   288,   289,   394,   576,   290,   395,    89,
     298,    90,   299,    91,   300,    92,   297,   581,   582,   583,
     677,   799,   800,   801,   809,   810,   811,   812,   817,   813,
     815,   827,   828,   829,   836,   837,   838,   843,   839,   840,
     841
  };

  const unsigned short int
  Dhcp4Parser::yytable_[] =
  {
      85,   241,   188,   159,   183,   199,   437,   223,   240,   255,
     274,   160,   176,   184,   200,    73,   438,   180,   242,   204,
     243,   636,   161,   162,   163,    27,   144,    28,    79,    29,
     302,    26,   144,   253,   254,   303,   567,    95,    96,   704,
      38,   585,   705,    96,   189,   190,   586,   587,   588,   589,
     590,   591,   592,   593,   594,   595,   324,   105,    99,   100,
     101,   325,    40,   145,   146,   147,   217,   105,   182,   149,
     329,   346,   105,   217,    76,   330,   347,   148,    42,   149,
     150,   151,   152,   153,   154,   155,   216,   253,   254,   349,
      44,    84,   156,   157,   350,    93,   432,    46,   156,   380,
     158,    94,    95,    96,   381,   832,    97,    98,   833,   834,
     835,   217,    48,   218,   219,   396,   104,   220,   221,   222,
     397,   217,    50,    99,   100,   101,   102,   103,    96,   189,
     190,   104,   105,   568,   523,   524,    80,   217,   237,   218,
     219,   238,   239,   324,   678,    81,    82,    83,   676,   679,
      52,    84,    54,   329,   106,   107,    56,   105,   680,    84,
      84,    84,    30,    31,    32,    33,    84,   108,   656,   657,
     109,   571,   572,   573,   574,   136,   137,   110,   111,   138,
     191,   112,    58,   291,   192,   193,   194,   195,   196,   197,
     706,   198,   804,   707,   805,   806,   624,   625,   626,   627,
     292,   628,   575,   437,    84,   642,   643,   644,   645,   646,
     647,   757,   692,   438,    84,   692,   717,   693,   721,   396,
     694,   718,   346,   722,   723,   293,    84,   788,   380,   349,
      84,   818,   847,   791,   795,   802,   819,   848,   803,   295,
      85,   294,   778,   779,   780,   781,   830,   398,   399,   831,
     301,    84,   538,   539,   540,   305,   306,   310,   311,   312,
     313,   321,   434,   328,   340,   341,   361,   362,   400,   433,
     363,   366,   370,   371,   372,   408,   374,   375,   435,   377,
     409,   382,   376,   436,   159,   188,   385,   183,   387,   388,
     391,   392,   160,   176,   393,   401,   184,   402,   180,   403,
     199,   404,   405,   161,   162,   163,   407,   410,   241,   200,
     223,   411,   412,   413,   204,   240,   414,   415,   417,   416,
     418,   419,   420,   421,   422,   242,   423,   243,   425,   424,
     426,   428,   429,   430,   274,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   444,
     445,   446,   447,   448,   449,   450,   451,   452,   505,   506,
     507,     1,     2,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,   454,   455,   453,   456,   457,   459,    84,
     461,   462,   463,   464,   465,   466,   467,   468,   469,   470,
     472,   473,   474,   475,   476,   477,   480,   484,   485,   488,
     489,   491,   494,   495,   499,   500,   502,   548,   478,   512,
     503,   481,   504,   508,   482,   487,   510,   511,   490,   513,
     514,   492,   493,   515,   516,   496,   497,   517,   498,   527,
     509,   518,   519,   520,   521,   528,   529,    28,   530,   532,
     563,   604,   604,   531,   543,   544,   535,   536,   596,   596,
     612,   537,   542,   545,   546,   547,   616,   578,   274,   434,
     620,   638,   664,   549,   666,   550,   433,   551,   570,   670,
     674,   552,   553,   554,   555,   435,   556,   557,   558,   559,
     436,   560,   561,   562,   564,   565,   566,   580,   685,   686,
     687,   688,   689,   711,   697,   577,   696,   700,   699,   702,
     703,   709,   710,   724,   712,   713,   714,   715,   716,   727,
     730,   729,   732,   733,   742,   736,   735,   738,   739,   740,
     741,   747,   748,   767,   768,   771,   533,   770,   776,   406,
     777,   789,   816,   579,   790,   796,   798,   820,   822,   826,
     824,   844,   845,   846,   849,   584,   427,   431,   749,   611,
     756,   744,   743,   759,   766,   746,   745,   758,   850,   760,
     761,   486,   751,   762,   750,   479,   763,   753,   752,   458,
     764,   765,   483,   783,   755,   784,   754,   785,   786,   787,
     215,   773,   792,   793,   794,   772,   797,   460,   821,   825,
     501,   851,   775,   852,   854,   774,   471,   769,   665,   662,
     737,   814,   823,   842,   853,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   604,     0,     0,     0,     0,     0,     0,
     596,     0,   241,   159,     0,     0,   223,     0,     0,   240,
       0,   160,   176,     0,     0,     0,   255,   180,     0,   242,
       0,   243,   161,   162,   163,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   188,     0,   183,     0,     0,   199,
       0,     0,     0,     0,     0,   184,     0,     0,   200,     0,
       0,     0,     0,   204,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   808,     0,     0,     0,     0,     0,     0,   807,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   808,
       0,     0,     0,     0,     0,     0,   807
  };

  const short int
  Dhcp4Parser::yycheck_[] =
  {
      62,    70,    66,    65,    66,    67,   331,    69,    70,    71,
      72,    65,    65,    66,    67,    60,   331,    65,    70,    67,
      70,   516,    65,    65,    65,     5,     7,     7,    10,     9,
       3,     0,     7,    84,    85,     8,    15,    18,    19,     3,
       7,    24,     6,    19,    20,    21,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,     3,    48,    39,    40,
      41,     8,     7,    44,    45,    46,    49,    48,    59,    60,
       3,     3,    48,    49,   142,     8,     8,    58,     7,    60,
      61,    62,    63,    64,    65,    66,    24,    84,    85,     3,
       7,   142,    73,    74,     8,    11,    72,     7,    73,     3,
      81,    17,    18,    19,     8,   121,    22,    23,   124,   125,
     126,    49,     7,    51,    52,     3,    47,    55,    56,    57,
       8,    49,     7,    39,    40,    41,    42,    43,    19,    20,
      21,    47,    48,   112,    14,    15,   118,    49,    50,    51,
      52,    53,    54,     3,     3,   127,   128,   129,     8,     8,
       7,   142,     7,     3,    70,    71,     7,    48,     8,   142,
     142,   142,   142,   143,   144,   145,   142,    83,    95,    96,
      86,   114,   115,   116,   117,    12,    13,    93,    94,    16,
      71,    97,     7,     6,    75,    76,    77,    78,    79,    80,
       3,    82,   120,     6,   122,   123,    75,    76,    77,    78,
       3,    80,   145,   528,   142,    87,    88,    89,    90,    91,
      92,   706,     3,   528,   142,     3,     3,     8,     3,     3,
       8,     8,     3,     8,     8,     4,   142,     8,     3,     3,
     142,     3,     3,     8,     8,     3,     8,     8,     6,     3,
     302,     8,    25,    26,    27,    28,     3,   292,   293,     6,
       4,   142,    67,    68,    69,     4,     4,     4,     4,     4,
       4,     4,   331,     4,     4,     4,     8,     3,   142,   331,
       8,     4,     4,     8,     3,   145,     4,     4,   331,     3,
     145,     4,     8,   331,   346,   349,     4,   349,     4,     4,
       4,     4,   346,   346,     4,     4,   349,     4,   346,     4,
     362,     4,     4,   346,   346,   346,     4,     4,   377,   362,
     372,     4,     4,   143,   362,   377,   143,   143,     4,   143,
       4,     4,     4,     4,     4,   377,     4,   377,     4,   143,
       4,     4,     4,   145,   396,    98,    99,   100,   101,   102,
     103,   104,   105,   106,   107,   108,   109,   110,   111,     4,
       4,     4,     4,     4,     4,     4,     4,   143,   403,   404,
     405,   130,   131,   132,   133,   134,   135,   136,   137,   138,
     139,   140,   141,     4,     4,   145,     4,     4,     4,   142,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,   143,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,   463,   145,     5,
       7,   145,     7,     7,   145,   145,     7,     7,   143,     5,
       5,   143,   143,     5,     5,   145,   145,     5,   145,     8,
     142,     7,     7,     7,     5,     3,   142,     7,   142,     5,
     485,   510,   511,   142,     5,     7,   142,   142,   510,   511,
       7,   142,   142,   142,   142,   142,     7,   502,   520,   528,
       7,     7,     4,   142,     7,   142,   528,   142,   113,     7,
      82,   142,   142,   142,   142,   528,   142,   142,   142,   142,
     528,   142,   142,   142,   142,   142,   142,   119,     4,     4,
       4,     4,     4,     4,     3,   142,     6,     3,     6,     6,
       3,     6,     3,   142,     4,     4,     4,     4,     4,   142,
       3,     6,     6,     3,   143,     4,     8,     4,     4,     4,
       4,     4,     4,     4,     4,     3,   448,     6,     4,   302,
       5,     8,     4,   503,     8,     8,     7,     4,     4,     7,
       5,     4,     4,     4,     4,   508,   324,   329,   692,   511,
     704,   143,   145,   710,   717,   143,   145,   708,   145,   143,
     143,   380,   697,   143,   695,   372,   143,   700,   698,   346,
     143,   143,   377,   142,   703,   142,   701,   142,   142,   142,
      68,   730,   142,   142,   142,   728,   142,   349,   143,   142,
     396,   143,   733,   143,   142,   731,   362,   721,   528,   520,
     678,   802,   818,   830,   847,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   692,    -1,    -1,    -1,    -1,    -1,    -1,
     692,    -1,   701,   695,    -1,    -1,   698,    -1,    -1,   701,
      -1,   695,   695,    -1,    -1,    -1,   708,   695,    -1,   701,
      -1,   701,   695,   695,   695,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   728,    -1,   728,    -1,    -1,   731,
      -1,    -1,    -1,    -1,    -1,   728,    -1,    -1,   731,    -1,
      -1,    -1,    -1,   731,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   801,    -1,    -1,    -1,    -1,    -1,    -1,   801,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   818,
      -1,    -1,    -1,    -1,    -1,    -1,   818
  };

  const unsigned short int
  Dhcp4Parser::yystos_[] =
  {
       0,   130,   131,   132,   133,   134,   135,   136,   137,   138,
     139,   140,   141,   147,   148,   149,   150,   151,   152,   153,
     154,   155,   156,   157,   158,   159,     0,     5,     7,     9,
     142,   143,   144,   145,   160,   161,   162,   167,     7,   176,
       7,   182,     7,   196,     7,   269,     7,   342,     7,   356,
       7,   294,     7,   300,     7,   324,     7,   245,     7,   408,
     168,   163,   177,   183,   197,   270,   343,   357,   295,   301,
     325,   246,   409,   160,   169,   170,   142,   165,   166,    10,
     118,   127,   128,   129,   142,   175,   178,   179,   180,   435,
     437,   439,   441,    11,    17,    18,    19,    22,    23,    39,
      40,    41,    42,    43,    47,    48,    70,    71,    83,    86,
      93,    94,    97,   175,   184,   185,   186,   187,   188,   189,
     190,   191,   192,   204,   206,   230,   239,   253,   263,   292,
     318,   361,   387,   397,   398,   406,    12,    13,    16,   194,
     195,   198,   200,   203,     7,    44,    45,    46,    58,    60,
      61,    62,    63,    64,    65,    66,    73,    74,    81,   175,
     186,   187,   188,   191,   271,   272,   273,   275,   277,   279,
     281,   283,   285,   287,   290,   291,   318,   336,   348,   350,
     361,   383,    59,   175,   318,   344,   345,   346,   348,    20,
      21,    71,    75,    76,    77,    78,    79,    80,    82,   175,
     318,   358,   359,   360,   361,   363,   365,   367,   369,   371,
     373,   375,   377,   379,   381,   292,    24,    49,    51,    52,
      55,    56,    57,   175,   220,   302,   303,   304,   305,   306,
     307,   308,   310,   312,   314,   315,   317,    50,    53,    54,
     175,   220,   306,   312,   326,   327,   328,   329,   330,   332,
     333,   334,   335,    84,    85,   175,   247,   248,   249,   251,
      98,    99,   100,   101,   102,   103,   104,   105,   106,   107,
     108,   109,   110,   111,   175,   410,   411,   412,   413,   415,
     417,   418,   420,   421,   422,   425,   427,   428,   429,   430,
     433,     6,     3,     4,     8,     3,   181,   442,   436,   438,
     440,     4,     3,     8,   193,     4,     4,   362,   205,   207,
       4,     4,     4,     4,   264,   293,   319,   231,   388,   240,
     254,     4,   399,   407,     3,     8,   199,   201,     4,     3,
       8,   390,   276,   278,   280,   337,   349,   274,   282,   284,
       4,     4,   288,   286,   351,   384,     3,     8,   347,     3,
       8,   364,   366,   382,   370,   372,   376,   374,   380,   378,
     368,     8,     3,     8,   309,   221,     4,   313,   311,   316,
       4,     8,     3,   331,     4,     4,     8,     3,   250,   252,
       3,     8,     4,   414,   416,     4,   419,     4,     4,   423,
     426,     4,     4,     4,   431,   434,     3,     8,   160,   160,
     142,     4,     4,     4,     4,     4,   179,     4,   145,   145,
       4,     4,     4,   143,   143,   143,   143,     4,     4,     4,
       4,     4,     4,     4,   143,     4,     4,   185,     4,     4,
     145,   195,    72,   175,   220,   318,   361,   363,   365,   391,
     392,   393,   394,   395,     4,     4,     4,     4,     4,     4,
       4,     4,   143,   145,     4,     4,     4,     4,   272,     4,
     345,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,   360,     4,     4,   143,     4,     4,     4,   145,   304,
       4,   145,   145,   328,     4,     4,   248,   145,     4,     4,
     143,     4,   143,   143,     4,     4,   145,   145,   145,     4,
       4,   411,     4,     7,     7,   160,   160,   160,     7,   142,
       7,     7,     5,     5,     5,     5,     5,     5,     7,     7,
       7,     5,   171,    14,    15,   202,   396,     8,     3,   142,
     142,   142,     5,   162,   164,   142,   142,   142,    67,    68,
      69,   289,   142,     5,     7,   142,   142,   142,   171,   142,
     142,   142,   142,   142,   142,   142,   142,   142,   142,   142,
     142,   142,   142,   160,   142,   142,   142,    15,   112,   424,
     113,   114,   115,   116,   117,   145,   432,   142,   160,   184,
     119,   443,   444,   445,   194,    24,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,   175,   208,   209,   210,
     213,   215,   217,   219,   220,   222,   223,   224,   225,   226,
     228,   208,     7,   265,   266,   267,     7,   296,   297,   298,
       7,   320,   321,   322,    75,    76,    77,    78,    80,   232,
     233,   234,   235,   236,   237,   238,   285,   389,     7,   241,
     242,   243,    87,    88,    89,    90,    91,    92,   255,   256,
     257,   258,   259,   260,   261,   262,    95,    96,   400,   401,
     402,   404,   410,   172,     4,   393,     7,   338,   339,   340,
       7,   352,   353,   354,    82,   385,     8,   446,     3,     8,
       8,   211,   214,   216,   218,     4,     4,     4,     4,     4,
     227,   229,     3,     8,     8,   268,     6,     3,   299,     6,
       3,   323,     6,     3,     3,     6,     3,     6,   244,     6,
       3,     4,     4,     4,     4,     4,     4,     3,     8,   403,
     405,     3,     8,     8,   142,   173,   174,   142,   341,     6,
       3,   355,     6,     3,   386,     8,     4,   444,     4,     4,
       4,     4,   143,   145,   143,   145,   143,     4,     4,   209,
     271,   267,   302,   298,   326,   322,   233,   285,   247,   243,
     143,   143,   143,   143,   143,   143,   256,     4,     4,   401,
       6,     3,   344,   340,   358,   354,     4,     5,    25,    26,
      27,    28,   212,   142,   142,   142,   142,   142,     8,     8,
       8,     8,   142,   142,   142,     8,     8,   142,     7,   447,
     448,   449,     3,     6,   120,   122,   123,   175,   220,   450,
     451,   452,   453,   455,   448,   456,     4,   454,     3,     8,
       4,   143,     4,   451,     5,   142,     7,   457,   458,   459,
       3,     6,   121,   124,   125,   126,   460,   461,   462,   464,
     465,   466,   458,   463,     4,     4,     4,     3,     8,     4,
     145,   143,   143,   461,   142
  };

  const unsigned short int
  Dhcp4Parser::yyr1_[] =
  {
       0,   146,   148,   147,   149,   147,   150,   147,   151,   147,
     152,   147,   153,   147,   154,   147,   155,   147,   156,   147,
     157,   147,   158,   147,   159,   147,   160,   160,   160,   160,
     160,   160,   160,   161,   163,   162,   164,   165,   165,   166,
     166,   168,   167,   169,   169,   170,   170,   172,   171,   173,
     173,   174,   174,   175,   177,   176,   178,   178,   179,   179,
     179,   179,   179,   179,   181,   180,   183,   182,   184,   184,
     185,   185,   185,   185,   185,   185,   185,   185,   185,   185,
     185,   185,   185,   185,   185,   185,   185,   185,   185,   185,
     185,   186,   187,   188,   189,   190,   191,   193,   192,   194,
     194,   195,   195,   195,   197,   196,   199,   198,   201,   200,
     202,   202,   203,   205,   204,   207,   206,   208,   208,   209,
     209,   209,   209,   209,   209,   209,   209,   209,   209,   209,
     209,   209,   211,   210,   212,   212,   212,   212,   214,   213,
     216,   215,   218,   217,   219,   221,   220,   222,   223,   224,
     225,   227,   226,   229,   228,   231,   230,   232,   232,   233,
     233,   233,   233,   233,   234,   235,   236,   237,   238,   240,
     239,   241,   241,   242,   242,   244,   243,   246,   245,   247,
     247,   247,   248,   248,   250,   249,   252,   251,   254,   253,
     255,   255,   256,   256,   256,   256,   256,   256,   257,   258,
     259,   260,   261,   262,   264,   263,   265,   265,   266,   266,
     268,   267,   270,   269,   271,   271,   272,   272,   272,   272,
     272,   272,   272,   272,   272,   272,   272,   272,   272,   272,
     272,   272,   272,   272,   272,   272,   272,   274,   273,   276,
     275,   278,   277,   280,   279,   282,   281,   284,   283,   286,
     285,   288,   287,   289,   289,   289,   290,   291,   293,   292,
     295,   294,   296,   296,   297,   297,   299,   298,   301,   300,
     302,   302,   303,   303,   304,   304,   304,   304,   304,   304,
     304,   304,   305,   306,   307,   309,   308,   311,   310,   313,
     312,   314,   316,   315,   317,   319,   318,   320,   320,   321,
     321,   323,   322,   325,   324,   326,   326,   327,   327,   328,
     328,   328,   328,   328,   328,   328,   329,   331,   330,   332,
     333,   334,   335,   337,   336,   338,   338,   339,   339,   341,
     340,   343,   342,   344,   344,   345,   345,   345,   345,   347,
     346,   349,   348,   351,   350,   352,   352,   353,   353,   355,
     354,   357,   356,   358,   358,   359,   359,   360,   360,   360,
     360,   360,   360,   360,   360,   360,   360,   360,   360,   360,
     362,   361,   364,   363,   366,   365,   368,   367,   370,   369,
     372,   371,   374,   373,   376,   375,   378,   377,   380,   379,
     382,   381,   384,   383,   386,   385,   388,   387,   389,   389,
     390,   285,   391,   391,   392,   392,   393,   393,   393,   393,
     393,   393,   393,   394,   396,   395,   397,   399,   398,   400,
     400,   401,   401,   403,   402,   405,   404,   407,   406,   409,
     408,   410,   410,   411,   411,   411,   411,   411,   411,   411,
     411,   411,   411,   411,   411,   411,   411,   411,   412,   414,
     413,   416,   415,   417,   419,   418,   420,   421,   423,   422,
     424,   424,   426,   425,   427,   428,   429,   431,   430,   432,
     432,   432,   432,   432,   434,   433,   436,   435,   438,   437,
     440,   439,   442,   441,   443,   443,   444,   446,   445,   447,
     447,   449,   448,   450,   450,   451,   451,   451,   451,   451,
     452,   454,   453,   456,   455,   457,   457,   459,   458,   460,
     460,   461,   461,   461,   461,   463,   462,   464,   465,   466
  };

  const unsigned char
  Dhcp4Parser::yyr2_[] =
  {
       0,     2,     0,     3,     0,     3,     0,     3,     0,     3,
       0,     3,     0,     3,     0,     3,     0,     3,     0,     3,
       0,     3,     0,     3,     0,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     0,     4,     1,     0,     1,     3,
       5,     0,     4,     0,     1,     1,     3,     0,     4,     0,
       1,     1,     3,     2,     0,     4,     1,     3,     1,     1,
       1,     1,     1,     1,     0,     6,     0,     4,     1,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     3,     3,     3,     3,     3,     3,     0,     6,     1,
       3,     1,     1,     1,     0,     4,     0,     4,     0,     4,
       1,     1,     3,     0,     6,     0,     6,     1,     3,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     0,     4,     1,     1,     1,     1,     0,     4,
       0,     4,     0,     4,     3,     0,     4,     3,     3,     3,
       3,     0,     4,     0,     4,     0,     6,     1,     3,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     0,
       6,     0,     1,     1,     3,     0,     4,     0,     4,     1,
       3,     1,     1,     1,     0,     4,     0,     4,     0,     6,
       1,     3,     1,     1,     1,     1,     1,     1,     3,     3,
       3,     3,     3,     3,     0,     6,     0,     1,     1,     3,
       0,     4,     0,     4,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       4,     0,     4,     1,     1,     1,     3,     3,     0,     6,
       0,     4,     0,     1,     1,     3,     0,     4,     0,     4,
       0,     1,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     3,     1,     0,     4,     0,     4,     0,
       4,     1,     0,     4,     3,     0,     6,     0,     1,     1,
       3,     0,     4,     0,     4,     0,     1,     1,     3,     1,
       1,     1,     1,     1,     1,     1,     1,     0,     4,     1,
       1,     3,     3,     0,     6,     0,     1,     1,     3,     0,
       4,     0,     4,     1,     3,     1,     1,     1,     1,     0,
       4,     0,     4,     0,     6,     0,     1,     1,     3,     0,
       4,     0,     4,     0,     1,     1,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       0,     4,     0,     4,     0,     4,     0,     4,     0,     4,
       0,     4,     0,     4,     0,     4,     0,     4,     0,     4,
       0,     4,     0,     6,     0,     4,     0,     6,     1,     3,
       0,     4,     0,     1,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     0,     4,     3,     0,     6,     1,
       3,     1,     1,     0,     4,     0,     4,     0,     6,     0,
       4,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     3,     0,
       4,     0,     4,     3,     0,     4,     3,     3,     0,     4,
       1,     1,     0,     4,     3,     3,     3,     0,     4,     1,
       1,     1,     1,     1,     0,     4,     0,     4,     0,     4,
       0,     4,     0,     6,     1,     3,     1,     0,     6,     1,
       3,     0,     4,     1,     3,     1,     1,     1,     1,     1,
       3,     0,     4,     0,     6,     1,     3,     0,     4,     1,
       3,     1,     1,     1,     1,     0,     4,     3,     3,     3
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
  "\"maxver\"", "\"Dhcp6\"", "\"DhcpDdns\"", "\"Control-agent\"",
  "TOPLEVEL_JSON", "TOPLEVEL_DHCP4", "SUB_DHCP4", "SUB_INTERFACES4",
  "SUB_SUBNET4", "SUB_POOL4", "SUB_RESERVATION", "SUB_OPTION_DEFS",
  "SUB_OPTION_DEF", "SUB_OPTION_DATA", "SUB_HOOKS_LIBRARY",
  "SUB_DHCP_DDNS", "\"constant string\"", "\"integer\"",
  "\"floating point\"", "\"boolean\"", "$accept", "start", "$@1", "$@2",
  "$@3", "$@4", "$@5", "$@6", "$@7", "$@8", "$@9", "$@10", "$@11", "$@12",
  "value", "sub_json", "map2", "$@13", "map_value", "map_content",
  "not_empty_map", "list_generic", "$@14", "list_content",
  "not_empty_list", "list_strings", "$@15", "list_strings_content",
  "not_empty_list_strings", "unknown_map_entry", "syntax_map", "$@16",
  "global_objects", "global_object", "dhcp4_object", "$@17", "sub_dhcp4",
  "$@18", "global_params", "global_param", "valid_lifetime", "renew_timer",
  "rebind_timer", "decline_probation_period", "echo_client_id",
  "match_client_id", "interfaces_config", "$@19",
  "interfaces_config_params", "interfaces_config_param", "sub_interfaces4",
  "$@20", "interfaces_list", "$@21", "dhcp_socket_type", "$@22",
  "socket_type", "re_detect", "lease_database", "$@23", "hosts_database",
  "$@24", "database_map_params", "database_map_param", "database_type",
  "$@25", "db_type", "user", "$@26", "password", "$@27", "host", "$@28",
  "port", "name", "$@29", "persist", "lfc_interval", "readonly",
  "connect_timeout", "contact_points", "$@30", "keyspace", "$@31",
  "host_reservation_identifiers", "$@32",
  "host_reservation_identifiers_list", "host_reservation_identifier",
  "duid_id", "hw_address_id", "circuit_id", "client_id", "flex_id",
  "hooks_libraries", "$@33", "hooks_libraries_list",
  "not_empty_hooks_libraries_list", "hooks_library", "$@34",
  "sub_hooks_library", "$@35", "hooks_params", "hooks_param", "library",
  "$@36", "parameters", "$@37", "expired_leases_processing", "$@38",
  "expired_leases_params", "expired_leases_param",
  "reclaim_timer_wait_time", "flush_reclaimed_timer_wait_time",
  "hold_reclaimed_time", "max_reclaim_leases", "max_reclaim_time",
  "unwarned_reclaim_cycles", "subnet4_list", "$@39",
  "subnet4_list_content", "not_empty_subnet4_list", "subnet4", "$@40",
  "sub_subnet4", "$@41", "subnet4_params", "subnet4_param", "subnet",
  "$@42", "subnet_4o6_interface", "$@43", "subnet_4o6_interface_id",
  "$@44", "subnet_4o6_subnet", "$@45", "interface", "$@46", "interface_id",
  "$@47", "client_class", "$@48", "reservation_mode", "$@49", "hr_mode",
  "id", "rapid_commit", "option_def_list", "$@50", "sub_option_def_list",
  "$@51", "option_def_list_content", "not_empty_option_def_list",
  "option_def_entry", "$@52", "sub_option_def", "$@53",
  "option_def_params", "not_empty_option_def_params", "option_def_param",
  "option_def_name", "code", "option_def_code", "option_def_type", "$@54",
  "option_def_record_types", "$@55", "space", "$@56", "option_def_space",
  "option_def_encapsulate", "$@57", "option_def_array", "option_data_list",
  "$@58", "option_data_list_content", "not_empty_option_data_list",
  "option_data_entry", "$@59", "sub_option_data", "$@60",
  "option_data_params", "not_empty_option_data_params",
  "option_data_param", "option_data_name", "option_data_data", "$@61",
  "option_data_code", "option_data_space", "option_data_csv_format",
  "option_data_always_send", "pools_list", "$@62", "pools_list_content",
  "not_empty_pools_list", "pool_list_entry", "$@63", "sub_pool4", "$@64",
  "pool_params", "pool_param", "pool_entry", "$@65", "user_context",
  "$@66", "reservations", "$@67", "reservations_list",
  "not_empty_reservations_list", "reservation", "$@68", "sub_reservation",
  "$@69", "reservation_params", "not_empty_reservation_params",
  "reservation_param", "next_server", "$@70", "server_hostname", "$@71",
  "boot_file_name", "$@72", "ip_address", "$@73", "duid", "$@74",
  "hw_address", "$@75", "client_id_value", "$@76", "circuit_id_value",
  "$@77", "flex_id_value", "$@78", "hostname", "$@79",
  "reservation_client_classes", "$@80", "relay", "$@81", "relay_map",
  "$@82", "client_classes", "$@83", "client_classes_list", "$@84",
  "client_class_params", "not_empty_client_class_params",
  "client_class_param", "client_class_name", "client_class_test", "$@85",
  "dhcp4o6_port", "control_socket", "$@86", "control_socket_params",
  "control_socket_param", "control_socket_type", "$@87",
  "control_socket_name", "$@88", "dhcp_ddns", "$@89", "sub_dhcp_ddns",
  "$@90", "dhcp_ddns_params", "dhcp_ddns_param", "enable_updates",
  "qualifying_suffix", "$@91", "server_ip", "$@92", "server_port",
  "sender_ip", "$@93", "sender_port", "max_queue_size", "ncr_protocol",
  "$@94", "ncr_protocol_value", "ncr_format", "$@95",
  "always_include_fqdn", "override_no_update", "override_client_update",
  "replace_client_name", "$@96", "replace_client_name_value",
  "generated_prefix", "$@97", "dhcp6_json_object", "$@98",
  "dhcpddns_json_object", "$@99", "control_agent_json_object", "$@100",
  "logging_object", "$@101", "logging_params", "logging_param", "loggers",
  "$@102", "loggers_entries", "logger_entry", "$@103", "logger_params",
  "logger_param", "debuglevel", "severity", "$@104", "output_options_list",
  "$@105", "output_options_list_content", "output_entry", "$@106",
  "output_params_list", "output_params", "output", "$@107", "flush",
  "maxsize", "maxver", YY_NULLPTR
  };

#if PARSER4_DEBUG
  const unsigned short int
  Dhcp4Parser::yyrline_[] =
  {
       0,   227,   227,   227,   228,   228,   229,   229,   230,   230,
     231,   231,   232,   232,   233,   233,   234,   234,   235,   235,
     236,   236,   237,   237,   238,   238,   246,   247,   248,   249,
     250,   251,   252,   255,   260,   260,   271,   274,   275,   278,
     282,   289,   289,   296,   297,   300,   304,   311,   311,   318,
     319,   322,   326,   337,   347,   347,   363,   364,   368,   369,
     370,   371,   372,   373,   376,   376,   391,   391,   400,   401,
     406,   407,   408,   409,   410,   411,   412,   413,   414,   415,
     416,   417,   418,   419,   420,   421,   422,   423,   424,   425,
     426,   429,   434,   439,   444,   449,   454,   460,   460,   471,
     472,   475,   476,   477,   480,   480,   489,   489,   499,   499,
     506,   507,   510,   516,   516,   528,   528,   540,   541,   544,
     545,   546,   547,   548,   549,   550,   551,   552,   553,   554,
     555,   556,   559,   559,   566,   567,   568,   569,   572,   572,
     580,   580,   588,   588,   596,   601,   601,   609,   614,   619,
     624,   629,   629,   637,   637,   646,   646,   656,   657,   660,
     661,   662,   663,   664,   667,   672,   677,   682,   687,   692,
     692,   702,   703,   706,   707,   710,   710,   720,   720,   730,
     731,   732,   735,   736,   739,   739,   747,   747,   755,   755,
     766,   767,   770,   771,   772,   773,   774,   775,   778,   783,
     788,   793,   798,   803,   811,   811,   824,   825,   828,   829,
     836,   836,   862,   862,   873,   874,   878,   879,   880,   881,
     882,   883,   884,   885,   886,   887,   888,   889,   890,   891,
     892,   893,   894,   895,   896,   897,   898,   901,   901,   909,
     909,   917,   917,   925,   925,   933,   933,   941,   941,   949,
     949,   957,   957,   964,   965,   966,   969,   974,   983,   983,
     996,   996,  1005,  1006,  1009,  1010,  1015,  1015,  1030,  1030,
    1044,  1045,  1048,  1049,  1052,  1053,  1054,  1055,  1056,  1057,
    1058,  1059,  1062,  1064,  1069,  1071,  1071,  1079,  1079,  1087,
    1087,  1095,  1097,  1097,  1105,  1114,  1114,  1126,  1127,  1132,
    1133,  1138,  1138,  1150,  1150,  1162,  1163,  1168,  1169,  1174,
    1175,  1176,  1177,  1178,  1179,  1180,  1183,  1185,  1185,  1193,
    1195,  1197,  1202,  1210,  1210,  1222,  1223,  1226,  1227,  1230,
    1230,  1240,  1240,  1250,  1251,  1254,  1255,  1256,  1257,  1260,
    1260,  1268,  1268,  1278,  1278,  1288,  1289,  1292,  1293,  1296,
    1296,  1305,  1305,  1314,  1315,  1318,  1319,  1323,  1324,  1325,
    1326,  1327,  1328,  1329,  1330,  1331,  1332,  1333,  1334,  1335,
    1338,  1338,  1346,  1346,  1354,  1354,  1362,  1362,  1370,  1370,
    1378,  1378,  1386,  1386,  1394,  1394,  1402,  1402,  1410,  1410,
    1418,  1418,  1431,  1431,  1441,  1441,  1452,  1452,  1462,  1463,
    1466,  1466,  1476,  1477,  1480,  1481,  1484,  1485,  1486,  1487,
    1488,  1489,  1490,  1493,  1495,  1495,  1507,  1514,  1514,  1524,
    1525,  1528,  1529,  1532,  1532,  1540,  1540,  1550,  1550,  1562,
    1562,  1572,  1573,  1576,  1577,  1578,  1579,  1580,  1581,  1582,
    1583,  1584,  1585,  1586,  1587,  1588,  1589,  1590,  1593,  1598,
    1598,  1606,  1606,  1614,  1619,  1619,  1627,  1632,  1637,  1637,
    1645,  1646,  1649,  1649,  1657,  1662,  1667,  1672,  1672,  1680,
    1683,  1686,  1689,  1692,  1698,  1698,  1708,  1708,  1715,  1715,
    1722,  1722,  1734,  1734,  1747,  1748,  1752,  1756,  1756,  1768,
    1769,  1773,  1773,  1781,  1782,  1785,  1786,  1787,  1788,  1789,
    1792,  1797,  1797,  1805,  1805,  1815,  1816,  1819,  1819,  1827,
    1828,  1831,  1832,  1833,  1834,  1837,  1837,  1845,  1850,  1855
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
#line 4254 "dhcp4_parser.cc" // lalr1.cc:1167
#line 1860 "dhcp4_parser.yy" // lalr1.cc:1168


void
isc::dhcp::Dhcp4Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
