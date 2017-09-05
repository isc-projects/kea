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

  case 235:
#line 881 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1699 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 236:
#line 883 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr subnet(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 1709 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 237:
#line 889 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1717 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 238:
#line 891 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface", iface);
    ctx.leave();
}
#line 1727 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 239:
#line 897 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1735 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 240:
#line 899 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface-id", iface);
    ctx.leave();
}
#line 1745 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 241:
#line 905 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1753 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 242:
#line 907 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-subnet", iface);
    ctx.leave();
}
#line 1763 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 243:
#line 913 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1771 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 244:
#line 915 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 1781 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 245:
#line 921 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1789 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 246:
#line 923 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface-id", iface);
    ctx.leave();
}
#line 1799 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 247:
#line 929 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.CLIENT_CLASS);
}
#line 1807 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 248:
#line 931 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr cls(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 1817 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 249:
#line 937 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.RESERVATION_MODE);
}
#line 1825 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 250:
#line 939 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("reservation-mode", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1834 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 251:
#line 944 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("disabled", ctx.loc2pos(yystack_[0].location))); }
#line 1840 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 252:
#line 945 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("out-of-pool", ctx.loc2pos(yystack_[0].location))); }
#line 1846 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 253:
#line 946 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("all", ctx.loc2pos(yystack_[0].location))); }
#line 1852 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 254:
#line 949 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr id(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 1861 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 255:
#line 954 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr rc(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rapid-commit", rc);
}
#line 1870 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 256:
#line 963 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 1881 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 257:
#line 968 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1890 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 259:
#line 995 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1899 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 262:
#line 985 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1917 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 263:
#line 989 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1929 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 264:
#line 996 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1939 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 265:
#line 1000 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 1951 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 279:
#line 1026 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr code(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 1960 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 281:
#line 1033 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1968 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 282:
#line 1035 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 1978 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 283:
#line 1041 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1986 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 284:
#line 1043 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 1996 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 285:
#line 1049 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2004 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 286:
#line 1051 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr space(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 2014 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 288:
#line 1059 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2022 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 289:
#line 1061 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr encap(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 2032 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 290:
#line 1067 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr array(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 2041 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 291:
#line 1076 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 2052 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 292:
#line 1081 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2061 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 297:
#line 1100 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2071 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 298:
#line 1104 "dhcp4_parser.yy" // lalr1.cc:859
    {
    /// @todo: the code or name parameters are required.
    ctx.stack_.pop_back();
}
#line 2080 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 299:
#line 1111 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2090 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 300:
#line 1115 "dhcp4_parser.yy" // lalr1.cc:859
    {
    /// @todo: the code or name parameters are required.
    // parsing completed
}
#line 2099 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 313:
#line 1145 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2107 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 314:
#line 1147 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr data(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 2117 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 317:
#line 1157 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr space(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", space);
}
#line 2126 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 318:
#line 1162 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr persist(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-send", persist);
}
#line 2135 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 319:
#line 1170 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 2146 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 320:
#line 1175 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2155 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 325:
#line 1190 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2165 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 326:
#line 1194 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2175 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 327:
#line 1198 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2185 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 328:
#line 1202 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2195 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 335:
#line 1216 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2203 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 336:
#line 1218 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr pool(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 2213 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 337:
#line 1224 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2221 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 338:
#line 1226 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("user-context", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2230 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 339:
#line 1234 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 2241 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 340:
#line 1239 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2250 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 345:
#line 1252 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2260 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 346:
#line 1256 "dhcp4_parser.yy" // lalr1.cc:859
    {
    /// @todo: an identifier parameter is required.
    ctx.stack_.pop_back();
}
#line 2269 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 347:
#line 1260 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2279 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 348:
#line 1264 "dhcp4_parser.yy" // lalr1.cc:859
    {
    /// @todo: an identifier parameter is required.
    // parsing completed
}
#line 2288 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 366:
#line 1292 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2296 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 367:
#line 1294 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr next_server(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("next-server", next_server);
    ctx.leave();
}
#line 2306 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 368:
#line 1300 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2314 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 369:
#line 1302 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr srv(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-hostname", srv);
    ctx.leave();
}
#line 2324 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 370:
#line 1308 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2332 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 371:
#line 1310 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr bootfile(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("boot-file-name", bootfile);
    ctx.leave();
}
#line 2342 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 372:
#line 1316 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2350 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 373:
#line 1318 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr addr(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", addr);
    ctx.leave();
}
#line 2360 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 374:
#line 1324 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2368 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 375:
#line 1326 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr d(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 2378 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 376:
#line 1332 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2386 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 377:
#line 1334 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 2396 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 378:
#line 1340 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2404 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 379:
#line 1342 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-id", hw);
    ctx.leave();
}
#line 2414 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 380:
#line 1348 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2422 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 381:
#line 1350 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("circuit-id", hw);
    ctx.leave();
}
#line 2432 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 382:
#line 1356 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2440 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 383:
#line 1358 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flex-id", hw);
    ctx.leave();
}
#line 2450 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 384:
#line 1364 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2458 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 385:
#line 1366 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr host(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 2468 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 386:
#line 1372 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2479 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 387:
#line 1377 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2488 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 388:
#line 1385 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 2499 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 389:
#line 1390 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2508 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 390:
#line 1395 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2516 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 391:
#line 1397 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr ip(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", ip);
    ctx.leave();
}
#line 2526 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 392:
#line 1406 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 2537 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 393:
#line 1411 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2546 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 396:
#line 1420 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2556 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 397:
#line 1424 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The name client class parameter is required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2566 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 410:
#line 1447 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2574 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 411:
#line 1449 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr test(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 2584 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 412:
#line 1459 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 2593 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 413:
#line 1466 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 2604 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 414:
#line 1471 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2613 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 419:
#line 1484 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2621 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 420:
#line 1486 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr stype(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 2631 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 421:
#line 1492 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2639 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 422:
#line 1494 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 2649 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 423:
#line 1502 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 2660 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 424:
#line 1507 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2671 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 425:
#line 1512 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2681 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 426:
#line 1516 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2691 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 444:
#line 1541 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 2700 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 445:
#line 1546 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2708 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 446:
#line 1548 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("qualifying-suffix", s);
    ctx.leave();
}
#line 2718 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 447:
#line 1554 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2726 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 448:
#line 1556 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 2736 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 449:
#line 1562 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 2745 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 450:
#line 1567 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2753 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 451:
#line 1569 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 2763 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 452:
#line 1575 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 2772 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 453:
#line 1580 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 2781 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 454:
#line 1585 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 2789 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 455:
#line 1587 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2798 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 456:
#line 1593 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 2804 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 457:
#line 1594 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 2810 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 458:
#line 1597 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NCR_FORMAT);
}
#line 2818 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 459:
#line 1599 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 2828 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 460:
#line 1605 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-include-fqdn", b);
}
#line 2837 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 461:
#line 1610 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-no-update", b);
}
#line 2846 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 462:
#line 1615 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-client-update", b);
}
#line 2855 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 463:
#line 1620 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 2863 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 464:
#line 1622 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("replace-client-name", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2872 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 465:
#line 1628 "dhcp4_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("when-present", ctx.loc2pos(yystack_[0].location))); 
      }
#line 2880 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 466:
#line 1631 "dhcp4_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location)));
      }
#line 2888 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 467:
#line 1634 "dhcp4_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("always", ctx.loc2pos(yystack_[0].location)));
      }
#line 2896 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 468:
#line 1637 "dhcp4_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("when-not-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 2904 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 469:
#line 1640 "dhcp4_parser.yy" // lalr1.cc:859
    {
      error(yystack_[0].location, "boolean values for the replace-client-name are "
                "no longer supported");
      }
#line 2913 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 470:
#line 1646 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2921 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 471:
#line 1648 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("generated-prefix", s);
    ctx.leave();
}
#line 2931 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 472:
#line 1656 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2939 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 473:
#line 1658 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("Dhcp6", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2948 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 474:
#line 1663 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2956 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 475:
#line 1665 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("DhcpDdns", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2965 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 476:
#line 1670 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2973 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 477:
#line 1672 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("Control-agent", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2982 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 478:
#line 1682 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Logging", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.LOGGING);
}
#line 2993 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 479:
#line 1687 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3002 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 483:
#line 1704 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 3013 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 484:
#line 1709 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3022 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 487:
#line 1721 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 3032 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 488:
#line 1725 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 3040 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 496:
#line 1740 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr dl(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 3049 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 497:
#line 1745 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3057 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 498:
#line 1747 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 3067 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 499:
#line 1753 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 3078 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 500:
#line 1758 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3087 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 503:
#line 1767 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3097 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 504:
#line 1771 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 3105 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 511:
#line 1785 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3113 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 512:
#line 1787 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 3123 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 513:
#line 1793 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr flush(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 3132 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 514:
#line 1798 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr maxsize(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 3141 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 515:
#line 1803 "dhcp4_parser.yy" // lalr1.cc:859
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


  const short int Dhcp4Parser::yypact_ninf_ = -493;

  const signed char Dhcp4Parser::yytable_ninf_ = -1;

  const short int
  Dhcp4Parser::yypact_[] =
  {
     214,  -486,  -486,  -486,  -486,  -486,  -486,  -486,  -486,  -486,
    -486,  -486,    40,    20,    35,    55,    63,    71,    90,   101,
     159,   175,   176,   219,  -486,  -486,  -486,  -486,  -486,  -486,
    -486,  -486,  -486,  -486,  -486,  -486,  -486,  -486,  -486,  -486,
    -486,  -486,  -486,  -486,  -486,  -486,  -486,  -486,  -486,  -486,
    -486,  -486,  -486,  -486,  -486,  -486,    20,   -21,    18,    84,
     224,    19,     9,   109,    62,   -19,     3,   153,  -486,   147,
     207,   223,   212,   231,  -486,  -486,  -486,  -486,  -486,   235,
    -486,    53,  -486,  -486,  -486,  -486,  -486,  -486,  -486,   261,
     262,  -486,  -486,  -486,   264,   265,   266,   268,  -486,  -486,
    -486,  -486,  -486,  -486,  -486,   269,  -486,  -486,  -486,    86,
    -486,  -486,  -486,  -486,  -486,  -486,  -486,  -486,  -486,  -486,
    -486,  -486,  -486,  -486,  -486,  -486,  -486,  -486,  -486,  -486,
    -486,  -486,  -486,   275,    96,  -486,  -486,  -486,  -486,  -486,
    -486,  -486,  -486,  -486,  -486,  -486,  -486,  -486,   276,   277,
    -486,  -486,  -486,  -486,  -486,  -486,  -486,  -486,  -486,   107,
    -486,  -486,  -486,  -486,  -486,  -486,  -486,  -486,  -486,  -486,
    -486,  -486,  -486,  -486,  -486,  -486,  -486,  -486,  -486,  -486,
     113,  -486,  -486,  -486,  -486,  -486,  -486,  -486,  -486,  -486,
    -486,  -486,  -486,  -486,  -486,  -486,   239,   281,  -486,  -486,
    -486,  -486,  -486,  -486,  -486,  -486,  -486,  -486,  -486,  -486,
    -486,  -486,   282,  -486,  -486,  -486,   283,  -486,  -486,   280,
     287,  -486,  -486,  -486,  -486,  -486,  -486,  -486,  -486,  -486,
    -486,  -486,   288,   291,  -486,  -486,  -486,  -486,   294,   300,
    -486,  -486,  -486,  -486,  -486,  -486,  -486,  -486,  -486,  -486,
     140,  -486,  -486,  -486,   302,  -486,  -486,   304,  -486,   306,
     307,  -486,  -486,   309,   310,   311,  -486,  -486,  -486,   148,
    -486,  -486,  -486,  -486,  -486,  -486,  -486,  -486,  -486,  -486,
    -486,  -486,  -486,  -486,  -486,  -486,    20,    20,  -486,   150,
     313,   315,   316,   317,   319,  -486,    18,  -486,   320,   160,
     181,   322,   323,   324,   187,   188,   190,   191,   330,   331,
     332,   333,   334,   335,   336,   217,   351,   352,    84,  -486,
     353,   354,   218,   224,  -486,    24,   356,   357,   359,   360,
     361,   362,   363,   364,   228,   229,   365,   367,   368,   370,
      19,  -486,   371,     9,  -486,   372,   373,   374,   375,   376,
     377,   378,   379,   380,   381,  -486,   109,   382,   383,   246,
     385,   386,   387,   248,  -486,    62,   389,   250,   251,  -486,
     -19,   392,   393,     6,  -486,   254,   395,   396,   259,   398,
     263,   267,   399,   400,   270,   271,   272,   402,   403,   153,
    -486,  -486,  -486,   404,   405,   406,    20,    20,    20,  -486,
     410,  -486,  -486,   278,   411,   413,  -486,  -486,  -486,  -486,
     416,   417,   419,   420,   421,   422,   423,  -486,   424,   425,
    -486,   428,   120,  -486,  -486,  -486,  -486,  -486,  -486,  -486,
    -486,  -486,   426,   407,  -486,  -486,  -486,   295,   296,   297,
     430,   432,   301,   303,   312,  -486,  -486,   208,   318,   436,
     440,  -486,   321,  -486,   325,   327,   428,   328,   337,   338,
     339,   340,   341,   342,  -486,   343,   344,  -486,   345,   346,
     347,  -486,  -486,   348,  -486,  -486,  -486,   349,    20,  -486,
    -486,   350,   355,  -486,   358,  -486,  -486,    21,   298,  -486,
    -486,  -486,    78,   366,  -486,    20,    84,   329,  -486,  -486,
    -486,   224,  -486,    17,    17,   444,   445,   447,   121,    32,
     449,    50,    80,   153,  -486,  -486,  -486,  -486,  -486,   439,
    -486,    24,  -486,  -486,  -486,   450,  -486,  -486,  -486,  -486,
    -486,  -486,  -486,  -486,  -486,  -486,   451,   390,  -486,  -486,
    -486,  -486,  -486,  -486,  -486,  -486,  -486,  -486,  -486,  -486,
    -486,  -486,  -486,  -486,  -486,  -486,  -486,  -486,  -486,  -486,
    -486,  -486,  -486,  -486,  -486,  -486,  -486,  -486,  -486,  -486,
    -486,  -486,   165,  -486,   171,  -486,  -486,   197,  -486,  -486,
    -486,  -486,   456,   457,   460,   461,   467,  -486,  -486,  -486,
     199,  -486,  -486,  -486,  -486,  -486,  -486,  -486,  -486,  -486,
    -486,  -486,  -486,  -486,   201,  -486,   469,   470,  -486,  -486,
     471,   473,  -486,  -486,   486,   490,  -486,  -486,  -486,  -486,
    -486,  -486,   106,  -486,  -486,  -486,  -486,  -486,  -486,  -486,
     146,  -486,   488,   492,  -486,   493,   494,   496,   497,   498,
     499,   203,  -486,  -486,  -486,  -486,  -486,  -486,  -486,  -486,
    -486,   205,  -486,  -486,  -486,   209,   369,   384,  -486,  -486,
     500,   501,  -486,  -486,   502,   506,  -486,  -486,   503,  -486,
     508,   329,  -486,  -486,   509,   510,   511,   512,   286,   285,
     388,   391,   394,   513,   514,    17,  -486,  -486,    19,  -486,
     444,    62,  -486,   445,   -19,  -486,   447,   121,  -486,    32,
    -486,     3,  -486,   449,   397,   401,   408,   409,   412,   414,
      50,  -486,   515,   516,    80,  -486,  -486,  -486,   517,   518,
    -486,     9,  -486,   450,   109,  -486,   451,   520,  -486,   521,
    -486,   216,   418,   427,   429,  -486,  -486,  -486,  -486,  -486,
     431,   433,  -486,   213,  -486,   519,  -486,   523,  -486,  -486,
    -486,   215,  -486,  -486,  -486,  -486,  -486,  -486,  -486,  -486,
     434,   435,  -486,  -486,   437,   221,  -486,   524,  -486,   438,
     522,  -486,  -486,  -486,  -486,  -486,  -486,  -486,  -486,  -486,
    -486,  -486,  -486,  -486,  -486,  -486,  -486,  -486,  -486,  -486,
    -486,  -486,   242,  -486,    49,   522,  -486,  -486,   529,  -486,
    -486,  -486,   225,  -486,  -486,  -486,  -486,  -486,   530,   415,
     533,    49,  -486,   535,  -486,   441,  -486,   531,  -486,  -486,
     243,  -486,   -50,   531,  -486,  -486,   537,   538,   540,   227,
    -486,  -486,  -486,  -486,  -486,  -486,   541,   442,   443,   446,
     -50,  -486,   448,  -486,  -486,  -486,  -486,  -486
  };

  const unsigned short int
  Dhcp4Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     1,    39,    32,    28,    27,    24,
      25,    26,    31,     3,    29,    30,    52,     5,    64,     7,
     102,     9,   210,    11,   327,    13,   347,    15,   264,    17,
     299,    19,   175,    21,   425,    23,    41,    35,     0,     0,
       0,     0,     0,   349,   266,   301,     0,     0,    43,     0,
      42,     0,     0,    36,    62,   478,   472,   474,   476,     0,
      61,     0,    54,    56,    58,    59,    60,    57,    95,     0,
       0,   366,   111,   113,     0,     0,     0,     0,   202,   256,
     291,   153,   392,   167,   186,     0,   413,   423,    88,     0,
      66,    68,    69,    70,    71,    85,    86,    73,    74,    75,
      76,    80,    81,    72,    78,    79,    87,    77,    82,    83,
      84,   104,   106,     0,     0,    97,    99,   100,   101,   396,
     237,   239,   241,   319,   337,   235,   243,   245,     0,     0,
     249,   247,   339,   388,   234,   214,   215,   216,   228,     0,
     212,   219,   230,   231,   232,   220,   221,   224,   226,   222,
     223,   217,   218,   233,   225,   229,   227,   335,   334,   332,
       0,   329,   331,   333,   368,   370,   386,   374,   376,   380,
     378,   384,   382,   372,   365,   361,     0,   350,   351,   362,
     363,   364,   358,   353,   359,   355,   356,   357,   360,   354,
     281,   143,     0,   285,   283,   288,     0,   277,   278,     0,
     267,   268,   270,   280,   271,   272,   273,   287,   274,   275,
     276,   313,     0,     0,   311,   312,   315,   316,     0,   302,
     303,   305,   306,   307,   308,   309,   310,   182,   184,   179,
       0,   177,   180,   181,     0,   445,   447,     0,   450,     0,
       0,   454,   458,     0,     0,     0,   463,   470,   443,     0,
     427,   429,   430,   431,   432,   433,   434,   435,   436,   437,
     438,   439,   440,   441,   442,    40,     0,     0,    33,     0,
       0,     0,     0,     0,     0,    51,     0,    53,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    65,
       0,     0,     0,     0,   103,   398,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   211,     0,     0,   328,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   348,     0,     0,     0,     0,
       0,     0,     0,     0,   265,     0,     0,     0,     0,   300,
       0,     0,     0,     0,   176,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     426,    44,    37,     0,     0,     0,     0,     0,     0,    55,
       0,    93,    94,     0,     0,     0,    89,    90,    91,    92,
       0,     0,     0,     0,     0,     0,     0,   412,     0,     0,
      67,     0,     0,   110,    98,   410,   408,   409,   404,   405,
     406,   407,     0,   399,   400,   402,   403,     0,     0,     0,
       0,     0,     0,     0,     0,   254,   255,     0,     0,     0,
       0,   213,     0,   330,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   352,     0,     0,   279,     0,     0,
       0,   290,   269,     0,   317,   318,   304,     0,     0,   178,
     444,     0,     0,   449,     0,   452,   453,     0,     0,   460,
     461,   462,     0,     0,   428,     0,     0,     0,   473,   475,
     477,     0,   367,     0,     0,   204,   258,   293,     0,     0,
     169,     0,     0,     0,    45,   105,   108,   109,   107,     0,
     397,     0,   238,   240,   242,   321,    34,   338,   236,   244,
     246,   251,   252,   253,   250,   248,   341,     0,   336,   369,
     371,   387,   375,   377,   381,   379,   385,   383,   373,   282,
     144,   286,   284,   289,   314,   183,   185,   446,   448,   451,
     456,   457,   455,   459,   465,   466,   467,   468,   469,   464,
     471,    38,     0,   483,     0,   480,   482,     0,   130,   136,
     138,   140,     0,     0,     0,     0,     0,   149,   151,   129,
       0,   115,   117,   118,   119,   120,   121,   122,   123,   124,
     125,   126,   127,   128,     0,   208,     0,   205,   206,   262,
       0,   259,   260,   297,     0,   294,   295,   162,   163,   164,
     165,   166,     0,   155,   157,   158,   159,   160,   161,   394,
       0,   173,     0,   170,   171,     0,     0,     0,     0,     0,
       0,     0,   188,   190,   191,   192,   193,   194,   195,   419,
     421,     0,   415,   417,   418,     0,    47,     0,   401,   325,
       0,   322,   323,   345,     0,   342,   343,   390,     0,    63,
       0,     0,   479,    96,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   112,   114,     0,   203,
       0,   266,   257,     0,   301,   292,     0,     0,   154,     0,
     393,     0,   168,     0,     0,     0,     0,     0,     0,     0,
       0,   187,     0,     0,     0,   414,   424,    49,     0,    48,
     411,     0,   320,     0,   349,   340,     0,     0,   389,     0,
     481,     0,     0,     0,     0,   142,   145,   146,   147,   148,
       0,     0,   116,     0,   207,     0,   261,     0,   296,   156,
     395,     0,   172,   196,   197,   198,   199,   200,   201,   189,
       0,     0,   416,    46,     0,     0,   324,     0,   344,     0,
       0,   132,   133,   134,   135,   131,   137,   139,   141,   150,
     152,   209,   263,   298,   174,   420,   422,    50,   326,   346,
     391,   487,     0,   485,     0,     0,   484,   499,     0,   497,
     495,   491,     0,   489,   493,   494,   492,   486,     0,     0,
       0,     0,   488,     0,   496,     0,   490,     0,   498,   503,
       0,   501,     0,     0,   500,   511,     0,     0,     0,     0,
     505,   507,   508,   509,   510,   502,     0,     0,     0,     0,
       0,   504,     0,   513,   514,   515,   506,   512
  };

  const short int
  Dhcp4Parser::yypgoto_[] =
  {
    -486,  -486,  -486,  -486,  -486,  -486,  -486,  -486,  -486,  -486,
    -486,  -486,  -486,   -55,  -486,    64,  -486,  -486,  -486,  -486,
    -486,  -486,  -486,  -486,    66,  -486,  -486,  -486,   -58,  -486,
    -486,  -486,   232,  -486,  -486,  -486,  -486,    51,   230,   -43,
     -41,   -40,  -486,  -486,   -39,  -486,  -486,    45,   226,  -486,
    -486,  -486,  -486,  -486,  -486,  -486,  -486,  -486,  -486,  -486,
    -486,    48,  -132,  -486,  -486,  -486,  -486,  -486,  -486,  -486,
    -486,  -486,  -486,   -54,  -486,  -486,  -486,  -486,  -486,  -486,
    -486,  -486,  -486,  -486,  -486,  -486,  -142,  -486,  -486,  -486,
    -486,  -486,  -486,  -486,  -486,  -486,  -145,  -486,  -486,  -486,
    -141,   189,  -486,  -486,  -486,  -486,  -486,  -486,  -486,  -149,
    -486,  -486,  -486,  -486,  -486,  -486,  -486,  -486,  -486,  -486,
    -127,  -486,  -486,  -486,  -124,   233,  -486,  -486,  -486,  -486,
    -486,  -486,  -486,  -486,  -486,  -486,  -486,  -486,  -485,  -486,
    -486,  -486,  -486,  -486,  -486,  -486,  -486,  -486,  -486,  -128,
    -486,  -486,  -486,  -125,  -486,   202,  -486,   -52,  -486,  -486,
    -486,  -486,  -486,   -48,  -486,  -486,  -486,  -486,  -486,   -47,
    -486,  -486,  -486,  -119,  -486,  -486,  -486,  -123,  -486,   210,
    -486,  -486,  -486,  -486,  -486,  -486,  -486,  -486,  -486,  -486,
    -486,  -154,  -486,  -486,  -486,  -140,   240,  -486,  -486,   -60,
    -486,  -486,  -486,  -486,  -486,  -139,  -486,  -486,  -486,  -134,
    -486,   236,   -51,  -486,  -306,  -486,  -302,  -486,  -486,  -486,
    -486,  -486,  -486,  -486,  -486,  -486,  -486,  -486,  -486,  -486,
    -486,  -486,  -486,  -486,  -486,  -486,  -486,  -486,  -486,  -486,
    -486,  -486,  -486,  -486,    70,  -486,  -486,  -486,  -486,  -486,
    -486,  -486,  -130,  -486,  -486,  -486,  -486,  -486,  -486,  -486,
    -486,    81,   204,  -486,  -486,  -486,  -486,  -486,  -486,  -486,
    -486,  -486,  -486,  -486,  -486,  -486,  -486,  -486,  -486,  -486,
    -486,  -486,  -486,  -486,  -486,  -486,  -486,  -486,  -486,  -486,
    -486,  -486,  -486,  -486,  -486,   -76,  -486,  -486,  -486,  -199,
    -486,  -486,  -214,  -486,  -486,  -486,  -486,  -486,  -486,  -225,
    -486,  -486,  -241,  -486,  -486,  -486,  -486,  -486
  };

  const short int
  Dhcp4Parser::yydefgoto_[] =
  {
      -1,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    32,    33,    34,    57,   527,    72,    73,
      35,    56,    69,    70,   515,   656,   718,   719,   108,    37,
      58,    81,    82,    83,   290,    39,    59,   109,   110,   111,
     112,   113,   114,   115,   116,   117,   298,   134,   135,    41,
      60,   136,   320,   137,   321,   518,   138,   118,   302,   119,
     303,   590,   591,   592,   674,   775,   593,   675,   594,   676,
     595,   677,   596,   218,   358,   598,   599,   600,   601,   602,
     683,   603,   684,   120,   311,   622,   623,   624,   625,   626,
     627,   628,   121,   313,   632,   633,   634,   701,    53,    66,
     250,   251,   252,   371,   253,   372,   122,   314,   641,   642,
     643,   644,   645,   646,   647,   648,   123,   308,   606,   607,
     608,   688,    43,    61,   159,   160,   161,   331,   162,   326,
     163,   327,   164,   328,   165,   332,   166,   333,   167,   337,
     168,   336,   534,   169,   170,   124,   309,   610,   611,   612,
     691,    49,    64,   219,   220,   221,   222,   223,   224,   225,
     357,   226,   361,   227,   360,   228,   229,   362,   230,   125,
     310,   614,   615,   616,   694,    51,    65,   238,   239,   240,
     241,   242,   366,   243,   244,   245,   246,   172,   329,   660,
     661,   662,   721,    45,    62,   180,   181,   182,   342,   173,
     330,   174,   338,   664,   665,   666,   724,    47,    63,   196,
     197,   198,   126,   301,   200,   345,   201,   346,   202,   354,
     203,   348,   204,   349,   205,   351,   206,   350,   207,   353,
     208,   352,   209,   347,   176,   339,   668,   727,   127,   312,
     630,   325,   432,   433,   434,   435,   436,   519,   128,   129,
     316,   651,   652,   653,   712,   654,   713,   130,   317,    55,
      67,   269,   270,   271,   272,   376,   273,   377,   274,   275,
     379,   276,   277,   278,   382,   562,   279,   383,   280,   281,
     282,   283,   387,   569,   284,   388,    84,   292,    85,   293,
      86,   294,    87,   291,   574,   575,   576,   670,   792,   793,
     794,   802,   803,   804,   805,   810,   806,   808,   820,   821,
     822,   829,   830,   831,   836,   832,   833,   834
  };

  const unsigned short int
  Dhcp4Parser::yytable_[] =
  {
      80,    68,   183,   154,   178,   194,   217,   234,   249,   268,
     175,   235,   199,   236,   171,   179,   195,   237,   155,   430,
     156,   157,   158,   431,   629,    25,   139,    26,    74,    27,
     211,   231,   212,   213,   232,   233,   560,    90,    91,   139,
      24,   578,    36,    91,   184,   185,   579,   580,   581,   582,
     583,   584,   585,   586,   587,   588,   296,   100,    94,    95,
      96,   297,    38,   140,   141,   142,   211,   100,   177,   144,
      40,   825,   100,   211,   826,   827,   828,   143,    42,   144,
     145,   146,   147,   148,   149,   150,   210,   247,   248,   318,
     247,   248,   151,   152,   319,    88,   425,    44,   211,   323,
     153,    89,    90,    91,   324,   151,    92,    93,    46,   697,
     340,   211,   698,   212,   213,   341,   343,   214,   215,   216,
      71,   344,    79,    94,    95,    96,    97,    98,    91,   184,
     185,    99,   100,   561,   516,   517,    75,   635,   636,   637,
     638,   639,   640,   373,    79,    76,    77,    78,   374,   699,
      79,   389,   700,   285,   101,   102,   390,   100,    79,    79,
      79,    28,    29,    30,    31,    79,    48,   103,   318,   797,
     104,   798,   799,   669,   671,   649,   650,   105,   106,   672,
     186,   107,    50,    52,   187,   188,   189,   190,   191,   192,
      79,   193,   564,   565,   566,   567,   617,   618,   619,   620,
     323,   621,   685,    79,   685,   673,   710,   686,   714,   687,
     286,   711,   389,   715,   750,   430,   340,   716,   373,   431,
     288,   781,   568,   784,   343,    79,    54,   287,   811,   788,
     840,   391,   392,   812,   289,   841,   131,   132,    80,   295,
     133,   771,   772,   773,   774,   795,   823,   355,   796,   824,
      79,   254,   255,   256,   257,   258,   259,   260,   261,   262,
     263,   264,   265,   266,   267,   299,   300,   426,   304,   305,
     306,   427,   307,   315,   429,   531,   532,   533,   428,   322,
     334,   335,   154,   183,   356,   178,   359,   363,   364,   175,
     365,   393,   367,   171,    79,   368,   179,   155,   194,   156,
     157,   158,   369,   370,   401,   199,   375,   217,   378,   195,
     380,   381,   234,   384,   385,   386,   235,   394,   236,   395,
     396,   397,   237,   398,   400,   402,   403,   404,   405,   406,
     407,   268,   408,   409,   410,   411,   412,   413,   414,   415,
     416,   498,   499,   500,     1,     2,     3,     4,     5,     6,
       7,     8,     9,    10,    11,   418,   419,   421,   422,   417,
     437,   438,   423,   439,   440,   441,   442,   443,   444,   447,
     445,   448,   449,   446,   450,   452,   454,   455,   456,   457,
     458,   459,   460,   461,   462,   463,   465,   466,   467,   468,
     469,   470,   471,   473,   474,   475,   477,   478,   480,   481,
     482,   483,   484,   487,   488,   485,   492,   493,   495,   486,
     521,   563,   496,   497,   489,   490,   491,   501,   503,   502,
     504,   505,   506,   556,   507,   508,   509,   510,   735,   736,
     511,   512,   513,   514,   520,   525,   522,   523,   524,    26,
     571,   536,   528,   657,   529,   589,   589,   537,   573,   597,
     597,   605,   609,   530,   613,   268,   631,   659,   663,   535,
     678,   679,   538,   426,   680,   681,   539,   427,   540,   542,
     429,   682,   667,   690,   428,   689,   693,   692,   543,   544,
     545,   546,   547,   548,   549,   550,   551,   552,   553,   554,
     555,   557,   695,   696,   702,   703,   558,   704,   705,   559,
     706,   707,   708,   709,   723,   526,   722,   570,   725,   726,
     717,   728,   729,   731,   732,   733,   734,   740,   741,   760,
     761,   764,   541,   763,   769,   720,   770,   782,   399,   791,
     737,   783,   789,   809,   813,   738,   739,   815,   819,   753,
     817,   837,   838,   754,   839,   842,   577,   572,   420,   424,
     755,   756,   604,   742,   757,   749,   758,   814,   752,   776,
     751,   759,   479,   744,   743,   746,   745,   472,   777,   766,
     778,   747,   779,   451,   780,   785,   786,   748,   787,   790,
     476,   765,   818,   453,   762,   844,   843,   768,   845,   847,
     767,   658,   464,   494,   655,   730,   807,   816,   835,   846,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   589,     0,     0,
     154,   597,     0,   217,     0,     0,   234,   175,     0,     0,
     235,   171,   236,   249,     0,   155,   237,   156,   157,   158,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   183,     0,   178,     0,     0,   194,     0,     0,     0,
       0,     0,     0,   199,   179,     0,     0,   195,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   800,     0,     0,     0,
     801,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   800,     0,     0,     0,   801
  };

  const short int
  Dhcp4Parser::yycheck_[] =
  {
      58,    56,    62,    61,    62,    63,    64,    65,    66,    67,
      61,    65,    63,    65,    61,    62,    63,    65,    61,   325,
      61,    61,    61,   325,   509,     5,     7,     7,    10,     9,
      49,    50,    51,    52,    53,    54,    15,    18,    19,     7,
       0,    24,     7,    19,    20,    21,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,     3,    48,    39,    40,
      41,     8,     7,    44,    45,    46,    49,    48,    59,    60,
       7,   121,    48,    49,   124,   125,   126,    58,     7,    60,
      61,    62,    63,    64,    65,    66,    24,    84,    85,     3,
      84,    85,    73,    74,     8,    11,    72,     7,    49,     3,
      81,    17,    18,    19,     8,    73,    22,    23,     7,     3,
       3,    49,     6,    51,    52,     8,     3,    55,    56,    57,
     141,     8,   141,    39,    40,    41,    42,    43,    19,    20,
      21,    47,    48,   112,    14,    15,   118,    87,    88,    89,
      90,    91,    92,     3,   141,   127,   128,   129,     8,     3,
     141,     3,     6,     6,    70,    71,     8,    48,   141,   141,
     141,   141,   142,   143,   144,   141,     7,    83,     3,   120,
      86,   122,   123,     8,     3,    95,    96,    93,    94,     8,
      71,    97,     7,     7,    75,    76,    77,    78,    79,    80,
     141,    82,   114,   115,   116,   117,    75,    76,    77,    78,
       3,    80,     3,   141,     3,     8,     3,     8,     3,     8,
       3,     8,     3,     8,   699,   521,     3,     8,     3,   521,
       8,     8,   144,     8,     3,   141,     7,     4,     3,     8,
       3,   286,   287,     8,     3,     8,    12,    13,   296,     4,
      16,    25,    26,    27,    28,     3,     3,     8,     6,     6,
     141,    98,    99,   100,   101,   102,   103,   104,   105,   106,
     107,   108,   109,   110,   111,     4,     4,   325,     4,     4,
       4,   325,     4,     4,   325,    67,    68,    69,   325,     4,
       4,     4,   340,   343,     3,   343,     4,     4,     8,   340,
       3,   141,     4,   340,   141,     4,   343,   340,   356,   340,
     340,   340,     8,     3,   144,   356,     4,   365,     4,   356,
       4,     4,   370,     4,     4,     4,   370,     4,   370,     4,
       4,     4,   370,     4,     4,   144,     4,     4,     4,   142,
     142,   389,   142,   142,     4,     4,     4,     4,     4,     4,
       4,   396,   397,   398,   130,   131,   132,   133,   134,   135,
     136,   137,   138,   139,   140,     4,     4,     4,     4,   142,
       4,     4,   144,     4,     4,     4,     4,     4,     4,     4,
     142,     4,     4,   144,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,   142,     4,
       4,     4,   144,     4,   144,   144,     4,     4,   144,     4,
       4,   142,     4,     4,     4,   142,     4,     4,     4,   142,
       3,   113,     7,     7,   144,   144,   144,     7,     7,   141,
       7,     5,     5,   478,     5,     5,     5,     5,   142,   144,
       7,     7,     7,     5,     8,     5,   141,   141,   141,     7,
     495,     5,   141,     4,   141,   503,   504,     7,   119,   503,
     504,     7,     7,   141,     7,   513,     7,     7,     7,   141,
       4,     4,   141,   521,     4,     4,   141,   521,   141,   141,
     521,     4,    82,     3,   521,     6,     3,     6,   141,   141,
     141,   141,   141,   141,   141,   141,   141,   141,   141,   141,
     141,   141,     6,     3,     6,     3,   141,     4,     4,   141,
       4,     4,     4,     4,     3,   441,     6,   141,     6,     3,
     141,     8,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     3,   456,     6,     4,   141,     5,     8,   296,     7,
     142,     8,     8,     4,     4,   144,   142,     4,     7,   142,
       5,     4,     4,   142,     4,     4,   501,   496,   318,   323,
     142,   142,   504,   685,   142,   697,   142,   142,   703,   141,
     701,   710,   373,   690,   688,   693,   691,   365,   141,   723,
     141,   694,   141,   340,   141,   141,   141,   696,   141,   141,
     370,   721,   141,   343,   714,   142,   144,   726,   142,   141,
     724,   521,   356,   389,   513,   671,   795,   811,   823,   840,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   685,    -1,    -1,
     688,   685,    -1,   691,    -1,    -1,   694,   688,    -1,    -1,
     694,   688,   694,   701,    -1,   688,   694,   688,   688,   688,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   721,    -1,   721,    -1,    -1,   724,    -1,    -1,    -1,
      -1,    -1,    -1,   724,   721,    -1,    -1,   724,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   794,    -1,    -1,    -1,
     794,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   811,    -1,    -1,    -1,   811
  };

  const unsigned short int
  Dhcp4Parser::yystos_[] =
  {
       0,   130,   131,   132,   133,   134,   135,   136,   137,   138,
     139,   140,   146,   147,   148,   149,   150,   151,   152,   153,
     154,   155,   156,   157,     0,     5,     7,     9,   141,   142,
     143,   144,   158,   159,   160,   165,     7,   174,     7,   180,
       7,   194,     7,   267,     7,   338,     7,   352,     7,   296,
       7,   320,     7,   243,     7,   404,   166,   161,   175,   181,
     195,   268,   339,   353,   297,   321,   244,   405,   158,   167,
     168,   141,   163,   164,    10,   118,   127,   128,   129,   141,
     173,   176,   177,   178,   431,   433,   435,   437,    11,    17,
      18,    19,    22,    23,    39,    40,    41,    42,    43,    47,
      48,    70,    71,    83,    86,    93,    94,    97,   173,   182,
     183,   184,   185,   186,   187,   188,   189,   190,   202,   204,
     228,   237,   251,   261,   290,   314,   357,   383,   393,   394,
     402,    12,    13,    16,   192,   193,   196,   198,   201,     7,
      44,    45,    46,    58,    60,    61,    62,    63,    64,    65,
      66,    73,    74,    81,   173,   184,   185,   186,   189,   269,
     270,   271,   273,   275,   277,   279,   281,   283,   285,   288,
     289,   314,   332,   344,   346,   357,   379,    59,   173,   314,
     340,   341,   342,   344,    20,    21,    71,    75,    76,    77,
      78,    79,    80,    82,   173,   314,   354,   355,   356,   357,
     359,   361,   363,   365,   367,   369,   371,   373,   375,   377,
      24,    49,    51,    52,    55,    56,    57,   173,   218,   298,
     299,   300,   301,   302,   303,   304,   306,   308,   310,   311,
     313,    50,    53,    54,   173,   218,   302,   308,   322,   323,
     324,   325,   326,   328,   329,   330,   331,    84,    85,   173,
     245,   246,   247,   249,    98,    99,   100,   101,   102,   103,
     104,   105,   106,   107,   108,   109,   110,   111,   173,   406,
     407,   408,   409,   411,   413,   414,   416,   417,   418,   421,
     423,   424,   425,   426,   429,     6,     3,     4,     8,     3,
     179,   438,   432,   434,   436,     4,     3,     8,   191,     4,
       4,   358,   203,   205,     4,     4,     4,     4,   262,   291,
     315,   229,   384,   238,   252,     4,   395,   403,     3,     8,
     197,   199,     4,     3,     8,   386,   274,   276,   278,   333,
     345,   272,   280,   282,     4,     4,   286,   284,   347,   380,
       3,     8,   343,     3,     8,   360,   362,   378,   366,   368,
     372,   370,   376,   374,   364,     8,     3,   305,   219,     4,
     309,   307,   312,     4,     8,     3,   327,     4,     4,     8,
       3,   248,   250,     3,     8,     4,   410,   412,     4,   415,
       4,     4,   419,   422,     4,     4,     4,   427,   430,     3,
       8,   158,   158,   141,     4,     4,     4,     4,     4,   177,
       4,   144,   144,     4,     4,     4,   142,   142,   142,   142,
       4,     4,     4,     4,     4,     4,     4,   142,     4,     4,
     183,     4,     4,   144,   193,    72,   173,   218,   314,   357,
     359,   361,   387,   388,   389,   390,   391,     4,     4,     4,
       4,     4,     4,     4,     4,   142,   144,     4,     4,     4,
       4,   270,     4,   341,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,   356,     4,     4,   142,     4,     4,
       4,   144,   300,     4,   144,   144,   324,     4,     4,   246,
     144,     4,     4,   142,     4,   142,   142,     4,     4,   144,
     144,   144,     4,     4,   407,     4,     7,     7,   158,   158,
     158,     7,   141,     7,     7,     5,     5,     5,     5,     5,
       5,     7,     7,     7,     5,   169,    14,    15,   200,   392,
       8,     3,   141,   141,   141,     5,   160,   162,   141,   141,
     141,    67,    68,    69,   287,   141,     5,     7,   141,   141,
     141,   169,   141,   141,   141,   141,   141,   141,   141,   141,
     141,   141,   141,   141,   141,   141,   158,   141,   141,   141,
      15,   112,   420,   113,   114,   115,   116,   117,   144,   428,
     141,   158,   182,   119,   439,   440,   441,   192,    24,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,   173,
     206,   207,   208,   211,   213,   215,   217,   218,   220,   221,
     222,   223,   224,   226,   206,     7,   263,   264,   265,     7,
     292,   293,   294,     7,   316,   317,   318,    75,    76,    77,
      78,    80,   230,   231,   232,   233,   234,   235,   236,   283,
     385,     7,   239,   240,   241,    87,    88,    89,    90,    91,
      92,   253,   254,   255,   256,   257,   258,   259,   260,    95,
      96,   396,   397,   398,   400,   406,   170,     4,   389,     7,
     334,   335,   336,     7,   348,   349,   350,    82,   381,     8,
     442,     3,     8,     8,   209,   212,   214,   216,     4,     4,
       4,     4,     4,   225,   227,     3,     8,     8,   266,     6,
       3,   295,     6,     3,   319,     6,     3,     3,     6,     3,
       6,   242,     6,     3,     4,     4,     4,     4,     4,     4,
       3,     8,   399,   401,     3,     8,     8,   141,   171,   172,
     141,   337,     6,     3,   351,     6,     3,   382,     8,     4,
     440,     4,     4,     4,     4,   142,   144,   142,   144,   142,
       4,     4,   207,   269,   265,   298,   294,   322,   318,   231,
     283,   245,   241,   142,   142,   142,   142,   142,   142,   254,
       4,     4,   397,     6,     3,   340,   336,   354,   350,     4,
       5,    25,    26,    27,    28,   210,   141,   141,   141,   141,
     141,     8,     8,     8,     8,   141,   141,   141,     8,     8,
     141,     7,   443,   444,   445,     3,     6,   120,   122,   123,
     173,   218,   446,   447,   448,   449,   451,   444,   452,     4,
     450,     3,     8,     4,   142,     4,   447,     5,   141,     7,
     453,   454,   455,     3,     6,   121,   124,   125,   126,   456,
     457,   458,   460,   461,   462,   454,   459,     4,     4,     4,
       3,     8,     4,   144,   142,   142,   457,   141
  };

  const unsigned short int
  Dhcp4Parser::yyr1_[] =
  {
       0,   145,   147,   146,   148,   146,   149,   146,   150,   146,
     151,   146,   152,   146,   153,   146,   154,   146,   155,   146,
     156,   146,   157,   146,   158,   158,   158,   158,   158,   158,
     158,   159,   161,   160,   162,   163,   163,   164,   164,   166,
     165,   167,   167,   168,   168,   170,   169,   171,   171,   172,
     172,   173,   175,   174,   176,   176,   177,   177,   177,   177,
     177,   177,   179,   178,   181,   180,   182,   182,   183,   183,
     183,   183,   183,   183,   183,   183,   183,   183,   183,   183,
     183,   183,   183,   183,   183,   183,   183,   183,   183,   184,
     185,   186,   187,   188,   189,   191,   190,   192,   192,   193,
     193,   193,   195,   194,   197,   196,   199,   198,   200,   200,
     201,   203,   202,   205,   204,   206,   206,   207,   207,   207,
     207,   207,   207,   207,   207,   207,   207,   207,   207,   207,
     209,   208,   210,   210,   210,   210,   212,   211,   214,   213,
     216,   215,   217,   219,   218,   220,   221,   222,   223,   225,
     224,   227,   226,   229,   228,   230,   230,   231,   231,   231,
     231,   231,   232,   233,   234,   235,   236,   238,   237,   239,
     239,   240,   240,   242,   241,   244,   243,   245,   245,   245,
     246,   246,   248,   247,   250,   249,   252,   251,   253,   253,
     254,   254,   254,   254,   254,   254,   255,   256,   257,   258,
     259,   260,   262,   261,   263,   263,   264,   264,   266,   265,
     268,   267,   269,   269,   270,   270,   270,   270,   270,   270,
     270,   270,   270,   270,   270,   270,   270,   270,   270,   270,
     270,   270,   270,   270,   270,   272,   271,   274,   273,   276,
     275,   278,   277,   280,   279,   282,   281,   284,   283,   286,
     285,   287,   287,   287,   288,   289,   291,   290,   292,   292,
     293,   293,   295,   294,   297,   296,   298,   298,   299,   299,
     300,   300,   300,   300,   300,   300,   300,   300,   301,   302,
     303,   305,   304,   307,   306,   309,   308,   310,   312,   311,
     313,   315,   314,   316,   316,   317,   317,   319,   318,   321,
     320,   322,   322,   323,   323,   324,   324,   324,   324,   324,
     324,   324,   325,   327,   326,   328,   329,   330,   331,   333,
     332,   334,   334,   335,   335,   337,   336,   339,   338,   340,
     340,   341,   341,   341,   341,   343,   342,   345,   344,   347,
     346,   348,   348,   349,   349,   351,   350,   353,   352,   354,
     354,   355,   355,   356,   356,   356,   356,   356,   356,   356,
     356,   356,   356,   356,   356,   356,   358,   357,   360,   359,
     362,   361,   364,   363,   366,   365,   368,   367,   370,   369,
     372,   371,   374,   373,   376,   375,   378,   377,   380,   379,
     382,   381,   384,   383,   385,   385,   386,   283,   387,   387,
     388,   388,   389,   389,   389,   389,   389,   389,   389,   390,
     392,   391,   393,   395,   394,   396,   396,   397,   397,   399,
     398,   401,   400,   403,   402,   405,   404,   406,   406,   407,
     407,   407,   407,   407,   407,   407,   407,   407,   407,   407,
     407,   407,   407,   407,   408,   410,   409,   412,   411,   413,
     415,   414,   416,   417,   419,   418,   420,   420,   422,   421,
     423,   424,   425,   427,   426,   428,   428,   428,   428,   428,
     430,   429,   432,   431,   434,   433,   436,   435,   438,   437,
     439,   439,   440,   442,   441,   443,   443,   445,   444,   446,
     446,   447,   447,   447,   447,   447,   448,   450,   449,   452,
     451,   453,   453,   455,   454,   456,   456,   457,   457,   457,
     457,   459,   458,   460,   461,   462
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
       1,     1,     1,     1,     1,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       4,     1,     1,     1,     3,     3,     0,     6,     0,     1,
       1,     3,     0,     4,     0,     4,     0,     1,     1,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     3,
       1,     0,     4,     0,     4,     0,     4,     1,     0,     4,
       3,     0,     6,     0,     1,     1,     3,     0,     4,     0,
       4,     0,     1,     1,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     0,     4,     1,     1,     3,     3,     0,
       6,     0,     1,     1,     3,     0,     4,     0,     4,     1,
       3,     1,     1,     1,     1,     0,     4,     0,     4,     0,
       6,     0,     1,     1,     3,     0,     4,     0,     4,     0,
       1,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     0,     4,     0,     4,
       0,     4,     0,     4,     0,     4,     0,     4,     0,     4,
       0,     4,     0,     4,     0,     4,     0,     4,     0,     6,
       0,     4,     0,     6,     1,     3,     0,     4,     0,     1,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       0,     4,     3,     0,     6,     1,     3,     1,     1,     0,
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
       0,   226,   226,   226,   227,   227,   228,   228,   229,   229,
     230,   230,   231,   231,   232,   232,   233,   233,   234,   234,
     235,   235,   236,   236,   244,   245,   246,   247,   248,   249,
     250,   253,   258,   258,   269,   272,   273,   276,   280,   287,
     287,   294,   295,   298,   302,   309,   309,   316,   317,   320,
     324,   335,   345,   345,   358,   359,   363,   364,   365,   366,
     367,   368,   371,   371,   388,   388,   396,   397,   402,   403,
     404,   405,   406,   407,   408,   409,   410,   411,   412,   413,
     414,   415,   416,   417,   418,   419,   420,   421,   422,   425,
     430,   435,   440,   445,   450,   456,   456,   466,   467,   470,
     471,   472,   475,   475,   483,   483,   493,   493,   500,   501,
     504,   510,   510,   520,   520,   530,   531,   534,   535,   536,
     537,   538,   539,   540,   541,   542,   543,   544,   545,   546,
     549,   549,   556,   557,   558,   559,   562,   562,   570,   570,
     578,   578,   586,   591,   591,   599,   604,   609,   614,   619,
     619,   627,   627,   636,   636,   646,   647,   650,   651,   652,
     653,   654,   657,   662,   667,   672,   677,   682,   682,   692,
     693,   696,   697,   700,   700,   708,   708,   716,   717,   718,
     721,   722,   725,   725,   733,   733,   741,   741,   751,   752,
     755,   756,   757,   758,   759,   760,   763,   768,   773,   778,
     783,   788,   796,   796,   809,   810,   813,   814,   821,   821,
     844,   844,   853,   854,   858,   859,   860,   861,   862,   863,
     864,   865,   866,   867,   868,   869,   870,   871,   872,   873,
     874,   875,   876,   877,   878,   881,   881,   889,   889,   897,
     897,   905,   905,   913,   913,   921,   921,   929,   929,   937,
     937,   944,   945,   946,   949,   954,   963,   963,   975,   976,
     979,   980,   985,   985,   996,   996,  1006,  1007,  1010,  1011,
    1014,  1015,  1016,  1017,  1018,  1019,  1020,  1021,  1024,  1026,
    1031,  1033,  1033,  1041,  1041,  1049,  1049,  1057,  1059,  1059,
    1067,  1076,  1076,  1088,  1089,  1094,  1095,  1100,  1100,  1111,
    1111,  1122,  1123,  1128,  1129,  1134,  1135,  1136,  1137,  1138,
    1139,  1140,  1143,  1145,  1145,  1153,  1155,  1157,  1162,  1170,
    1170,  1182,  1183,  1186,  1187,  1190,  1190,  1198,  1198,  1206,
    1207,  1210,  1211,  1212,  1213,  1216,  1216,  1224,  1224,  1234,
    1234,  1244,  1245,  1248,  1249,  1252,  1252,  1260,  1260,  1268,
    1269,  1272,  1273,  1277,  1278,  1279,  1280,  1281,  1282,  1283,
    1284,  1285,  1286,  1287,  1288,  1289,  1292,  1292,  1300,  1300,
    1308,  1308,  1316,  1316,  1324,  1324,  1332,  1332,  1340,  1340,
    1348,  1348,  1356,  1356,  1364,  1364,  1372,  1372,  1385,  1385,
    1395,  1395,  1406,  1406,  1416,  1417,  1420,  1420,  1428,  1429,
    1432,  1433,  1436,  1437,  1438,  1439,  1440,  1441,  1442,  1445,
    1447,  1447,  1459,  1466,  1466,  1476,  1477,  1480,  1481,  1484,
    1484,  1492,  1492,  1502,  1502,  1512,  1512,  1520,  1521,  1524,
    1525,  1526,  1527,  1528,  1529,  1530,  1531,  1532,  1533,  1534,
    1535,  1536,  1537,  1538,  1541,  1546,  1546,  1554,  1554,  1562,
    1567,  1567,  1575,  1580,  1585,  1585,  1593,  1594,  1597,  1597,
    1605,  1610,  1615,  1620,  1620,  1628,  1631,  1634,  1637,  1640,
    1646,  1646,  1656,  1656,  1663,  1663,  1670,  1670,  1682,  1682,
    1695,  1696,  1700,  1704,  1704,  1716,  1717,  1721,  1721,  1729,
    1730,  1733,  1734,  1735,  1736,  1737,  1740,  1745,  1745,  1753,
    1753,  1763,  1764,  1767,  1767,  1775,  1776,  1779,  1780,  1781,
    1782,  1785,  1785,  1793,  1798,  1803
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
#line 4186 "dhcp4_parser.cc" // lalr1.cc:1167
#line 1808 "dhcp4_parser.yy" // lalr1.cc:1168


void
isc::dhcp::Dhcp4Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
