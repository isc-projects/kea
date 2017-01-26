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
      case 149: // value
      case 153: // map_value
      case 191: // socket_type
      case 200: // db_type
      case 271: // hr_mode
      case 401: // ncr_protocol_value
      case 410: // replace_client_name_value
        value.move< ElementPtr > (that.value);
        break;

      case 135: // "boolean"
        value.move< bool > (that.value);
        break;

      case 134: // "floating point"
        value.move< double > (that.value);
        break;

      case 133: // "integer"
        value.move< int64_t > (that.value);
        break;

      case 132: // "constant string"
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
      case 149: // value
      case 153: // map_value
      case 191: // socket_type
      case 200: // db_type
      case 271: // hr_mode
      case 401: // ncr_protocol_value
      case 410: // replace_client_name_value
        value.copy< ElementPtr > (that.value);
        break;

      case 135: // "boolean"
        value.copy< bool > (that.value);
        break;

      case 134: // "floating point"
        value.copy< double > (that.value);
        break;

      case 133: // "integer"
        value.copy< int64_t > (that.value);
        break;

      case 132: // "constant string"
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
            case 132: // "constant string"

#line 208 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< std::string > (); }
#line 364 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 133: // "integer"

#line 208 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< int64_t > (); }
#line 371 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 134: // "floating point"

#line 208 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< double > (); }
#line 378 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 135: // "boolean"

#line 208 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< bool > (); }
#line 385 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 149: // value

#line 208 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 392 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 153: // map_value

#line 208 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 399 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 191: // socket_type

#line 208 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 406 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 200: // db_type

#line 208 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 413 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 271: // hr_mode

#line 208 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 420 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 401: // ncr_protocol_value

#line 208 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 427 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 410: // replace_client_name_value

#line 208 "dhcp4_parser.yy" // lalr1.cc:636
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
      case 149: // value
      case 153: // map_value
      case 191: // socket_type
      case 200: // db_type
      case 271: // hr_mode
      case 401: // ncr_protocol_value
      case 410: // replace_client_name_value
        yylhs.value.build< ElementPtr > ();
        break;

      case 135: // "boolean"
        yylhs.value.build< bool > ();
        break;

      case 134: // "floating point"
        yylhs.value.build< double > ();
        break;

      case 133: // "integer"
        yylhs.value.build< int64_t > ();
        break;

      case 132: // "constant string"
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
#line 217 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.NO_KEYWORD; }
#line 680 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 4:
#line 218 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.CONFIG; }
#line 686 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 6:
#line 219 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.DHCP4; }
#line 692 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 8:
#line 220 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.INTERFACES_CONFIG; }
#line 698 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 10:
#line 221 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.SUBNET4; }
#line 704 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 12:
#line 222 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.POOLS; }
#line 710 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 14:
#line 223 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.RESERVATIONS; }
#line 716 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 16:
#line 224 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.OPTION_DEF; }
#line 722 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 18:
#line 225 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.OPTION_DATA; }
#line 728 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 20:
#line 226 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.HOOKS_LIBRARIES; }
#line 734 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 22:
#line 227 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.DHCP_DDNS; }
#line 740 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 24:
#line 235 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 746 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 25:
#line 236 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as< double > (), ctx.loc2pos(yystack_[0].location))); }
#line 752 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 26:
#line 237 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 758 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 27:
#line 238 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 764 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 28:
#line 239 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 770 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 29:
#line 240 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 776 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 30:
#line 241 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 782 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 31:
#line 244 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as< ElementPtr > ());
}
#line 791 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 32:
#line 249 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 802 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 33:
#line 254 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 812 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 34:
#line 260 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 818 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 37:
#line 267 "dhcp4_parser.yy" // lalr1.cc:859
    {
                  // map containing a single entry
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 827 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 38:
#line 271 "dhcp4_parser.yy" // lalr1.cc:859
    {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 837 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 39:
#line 278 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 846 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 40:
#line 281 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // list parsing complete. Put any sanity checking here
}
#line 854 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 43:
#line 289 "dhcp4_parser.yy" // lalr1.cc:859
    {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 863 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 44:
#line 293 "dhcp4_parser.yy" // lalr1.cc:859
    {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 872 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 45:
#line 300 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // List parsing about to start
}
#line 880 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 46:
#line 302 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // list parsing complete. Put any sanity checking here
    //ctx.stack_.pop_back();
}
#line 889 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 49:
#line 311 "dhcp4_parser.yy" // lalr1.cc:859
    {
                          ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 898 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 50:
#line 315 "dhcp4_parser.yy" // lalr1.cc:859
    {
                          ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 907 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 51:
#line 326 "dhcp4_parser.yy" // lalr1.cc:859
    {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as< std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 918 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 52:
#line 336 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 929 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 53:
#line 341 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 939 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 61:
#line 360 "dhcp4_parser.yy" // lalr1.cc:859
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
#line 367 "dhcp4_parser.yy" // lalr1.cc:859
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
#line 377 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the Dhcp4 map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 974 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 64:
#line 381 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 982 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 88:
#line 414 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 991 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 89:
#line 419 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 1000 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 90:
#line 424 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 1009 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 91:
#line 429 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr dpp(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 1018 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 92:
#line 434 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr echo(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("echo-client-id", echo);
}
#line 1027 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 93:
#line 439 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr match(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("match-client-id", match);
}
#line 1036 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 94:
#line 445 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces-config", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.INTERFACES_CONFIG);
}
#line 1047 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 95:
#line 450 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1056 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 100:
#line 463 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1066 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 101:
#line 467 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1074 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 102:
#line 471 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1085 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 103:
#line 476 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1094 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 104:
#line 481 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.DHCP_SOCKET_TYPE);
}
#line 1102 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 105:
#line 483 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("dhcp-socket-type", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1111 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 106:
#line 488 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("raw", ctx.loc2pos(yystack_[0].location))); }
#line 1117 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 107:
#line 489 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("udp", ctx.loc2pos(yystack_[0].location))); }
#line 1123 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 108:
#line 492 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lease-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.LEASE_DATABASE);
}
#line 1134 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 109:
#line 497 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1143 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 110:
#line 502 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1154 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 111:
#line 507 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1163 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 124:
#line 528 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.DATABASE_TYPE);
}
#line 1171 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 125:
#line 530 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("type", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1180 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 126:
#line 535 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("memfile", ctx.loc2pos(yystack_[0].location))); }
#line 1186 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 127:
#line 536 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("mysql", ctx.loc2pos(yystack_[0].location))); }
#line 1192 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 128:
#line 537 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("postgresql", ctx.loc2pos(yystack_[0].location))); }
#line 1198 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 129:
#line 538 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("cql", ctx.loc2pos(yystack_[0].location))); }
#line 1204 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 130:
#line 541 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1212 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 131:
#line 543 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr user(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1222 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 132:
#line 549 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1230 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 133:
#line 551 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr pwd(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 1240 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 134:
#line 557 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1248 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 135:
#line 559 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr h(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 1258 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 136:
#line 565 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1266 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 137:
#line 567 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1276 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 138:
#line 573 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 1285 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 139:
#line 578 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 1294 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 140:
#line 583 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 1303 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 141:
#line 588 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("connect-timeout", n);
}
#line 1312 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 142:
#line 593 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 1323 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 143:
#line 598 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1332 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 150:
#line 613 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1341 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 151:
#line 618 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 1350 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 152:
#line 623 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr circuit(new StringElement("circuit-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(circuit);
}
#line 1359 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 153:
#line 628 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr client(new StringElement("client-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(client);
}
#line 1368 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 154:
#line 633 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 1379 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 155:
#line 638 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1388 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 160:
#line 651 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1398 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 161:
#line 655 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1406 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 162:
#line 659 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1416 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 163:
#line 663 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1424 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 169:
#line 676 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1432 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 170:
#line 678 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr lib(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 1442 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 171:
#line 684 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1450 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 172:
#line 686 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1459 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 173:
#line 692 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.EXPIRED_LEASES_PROCESSING);
}
#line 1470 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 174:
#line 697 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1479 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 183:
#line 714 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 1488 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 184:
#line 719 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 1497 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 185:
#line 724 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 1506 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 186:
#line 729 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 1515 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 187:
#line 734 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 1524 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 188:
#line 739 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 1533 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 189:
#line 747 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet4", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET4);
}
#line 1544 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 190:
#line 752 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1553 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 195:
#line 772 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1563 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 196:
#line 776 "dhcp4_parser.yy" // lalr1.cc:859
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
#line 1586 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 197:
#line 795 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the subnet4 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1596 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 198:
#line 799 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1604 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 221:
#line 831 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1612 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 222:
#line 833 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr subnet(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 1622 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 223:
#line 839 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1630 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 224:
#line 841 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface", iface);
    ctx.leave();
}
#line 1640 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 225:
#line 847 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1648 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 226:
#line 849 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface-id", iface);
    ctx.leave();
}
#line 1658 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 227:
#line 855 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1666 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 228:
#line 857 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-subnet", iface);
    ctx.leave();
}
#line 1676 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 229:
#line 863 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1684 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 230:
#line 865 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 1694 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 231:
#line 871 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1702 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 232:
#line 873 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface-id", iface);
    ctx.leave();
}
#line 1712 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 233:
#line 879 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.CLIENT_CLASS);
}
#line 1720 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 234:
#line 881 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr cls(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 1730 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 235:
#line 887 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.RESERVATION_MODE);
}
#line 1738 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 236:
#line 889 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("reservation-mode", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1747 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 237:
#line 894 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("disabled", ctx.loc2pos(yystack_[0].location))); }
#line 1753 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 238:
#line 895 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("out-of-pool", ctx.loc2pos(yystack_[0].location))); }
#line 1759 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 239:
#line 896 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("all", ctx.loc2pos(yystack_[0].location))); }
#line 1765 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 240:
#line 899 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr id(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 1774 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 241:
#line 904 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr rc(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rapid-commit", rc);
}
#line 1783 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 242:
#line 913 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 1794 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 243:
#line 918 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1803 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 248:
#line 935 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1813 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 249:
#line 939 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1821 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 250:
#line 946 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1831 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 251:
#line 950 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1839 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 265:
#line 976 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr code(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 1848 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 267:
#line 983 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1856 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 268:
#line 985 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 1866 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 269:
#line 991 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1874 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 270:
#line 993 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 1884 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 271:
#line 999 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1892 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 272:
#line 1001 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr space(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 1902 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 274:
#line 1009 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1910 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 275:
#line 1011 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr encap(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 1920 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 276:
#line 1017 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr array(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 1929 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 277:
#line 1026 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 1940 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 278:
#line 1031 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1949 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 283:
#line 1050 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1959 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 284:
#line 1054 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1967 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 285:
#line 1061 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1977 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 286:
#line 1065 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1985 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 298:
#line 1094 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1993 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 299:
#line 1096 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr data(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 2003 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 302:
#line 1106 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr space(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", space);
}
#line 2012 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 303:
#line 1114 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 2023 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 304:
#line 1119 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2032 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 309:
#line 1134 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2042 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 310:
#line 1138 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2050 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 311:
#line 1142 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2060 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 312:
#line 1146 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 2068 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 319:
#line 1160 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2076 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 320:
#line 1162 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr pool(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 2086 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 321:
#line 1168 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2094 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 322:
#line 1170 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("user-context", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2103 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 323:
#line 1178 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 2114 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 324:
#line 1183 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2123 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 329:
#line 1196 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2133 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 330:
#line 1200 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2141 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 331:
#line 1204 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2151 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 332:
#line 1208 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 2159 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 349:
#line 1235 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2167 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 350:
#line 1237 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr next_server(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("next-server", next_server);
    ctx.leave();
}
#line 2177 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 351:
#line 1243 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2185 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 352:
#line 1245 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr srv(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-hostname", srv);
    ctx.leave();
}
#line 2195 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 353:
#line 1251 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2203 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 354:
#line 1253 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr bootfile(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("boot-file-name", bootfile);
    ctx.leave();
}
#line 2213 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 355:
#line 1259 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2221 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 356:
#line 1261 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr addr(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", addr);
    ctx.leave();
}
#line 2231 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 357:
#line 1267 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2239 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 358:
#line 1269 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr d(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 2249 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 359:
#line 1275 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2257 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 360:
#line 1277 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 2267 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 361:
#line 1283 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2275 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 362:
#line 1285 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-id", hw);
    ctx.leave();
}
#line 2285 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 363:
#line 1291 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2293 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 364:
#line 1293 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("circuit-id", hw);
    ctx.leave();
}
#line 2303 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 365:
#line 1300 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2311 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 366:
#line 1302 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr host(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 2321 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 367:
#line 1308 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2332 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 368:
#line 1313 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2341 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 369:
#line 1321 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 2352 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 370:
#line 1326 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2361 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 371:
#line 1331 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2369 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 372:
#line 1333 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr ip(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", ip);
    ctx.leave();
}
#line 2379 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 373:
#line 1342 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 2390 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 374:
#line 1347 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2399 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 377:
#line 1356 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2409 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 378:
#line 1360 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2417 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 391:
#line 1383 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2425 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 392:
#line 1385 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr test(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 2435 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 393:
#line 1395 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 2444 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 394:
#line 1402 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 2455 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 395:
#line 1407 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2464 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 400:
#line 1420 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2472 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 401:
#line 1422 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr stype(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 2482 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 402:
#line 1428 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2490 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 403:
#line 1430 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 2500 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 404:
#line 1438 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 2511 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 405:
#line 1443 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2520 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 406:
#line 1448 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2530 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 407:
#line 1452 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 2538 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 426:
#line 1478 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 2547 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 427:
#line 1483 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2555 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 428:
#line 1485 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("qualifying-suffix", s);
    ctx.leave();
}
#line 2565 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 429:
#line 1491 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2573 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 430:
#line 1493 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 2583 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 431:
#line 1499 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 2592 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 432:
#line 1504 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2600 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 433:
#line 1506 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 2610 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 434:
#line 1512 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 2619 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 435:
#line 1517 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 2628 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 436:
#line 1522 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 2636 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 437:
#line 1524 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2645 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 438:
#line 1530 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 2651 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 439:
#line 1531 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 2657 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 440:
#line 1534 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NCR_FORMAT);
}
#line 2665 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 441:
#line 1536 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 2675 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 442:
#line 1542 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-include-fqdn", b);
}
#line 2684 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 443:
#line 1547 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("allow-client-update",  b);
}
#line 2693 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 444:
#line 1552 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-no-update", b);
}
#line 2702 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 445:
#line 1557 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-client-update", b);
}
#line 2711 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 446:
#line 1562 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 2719 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 447:
#line 1564 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("replace-client-name", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2728 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 448:
#line 1570 "dhcp4_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("when-present", ctx.loc2pos(yystack_[0].location))); 
      }
#line 2736 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 449:
#line 1573 "dhcp4_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location)));
      }
#line 2744 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 450:
#line 1576 "dhcp4_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("always", ctx.loc2pos(yystack_[0].location)));
      }
#line 2752 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 451:
#line 1579 "dhcp4_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("when-not-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 2760 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 452:
#line 1582 "dhcp4_parser.yy" // lalr1.cc:859
    {
      error(yystack_[0].location, "boolean values for the replace-client-name are "
                "no longer supported");
      }
#line 2769 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 453:
#line 1588 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2777 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 454:
#line 1590 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("generated-prefix", s);
    ctx.leave();
}
#line 2787 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 455:
#line 1598 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2795 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 456:
#line 1600 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("Dhcp6", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2804 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 457:
#line 1605 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2812 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 458:
#line 1607 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("DhcpDdns", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2821 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 459:
#line 1617 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Logging", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.LOGGING);
}
#line 2832 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 460:
#line 1622 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2841 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 464:
#line 1639 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 2852 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 465:
#line 1644 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2861 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 468:
#line 1656 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 2871 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 469:
#line 1660 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2879 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 477:
#line 1675 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr dl(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 2888 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 478:
#line 1679 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2896 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 479:
#line 1681 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 2906 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 480:
#line 1687 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 2917 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 481:
#line 1692 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2926 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 484:
#line 1701 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2936 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 485:
#line 1705 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2944 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 488:
#line 1713 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2952 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 489:
#line 1715 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 2962 "dhcp4_parser.cc" // lalr1.cc:859
    break;


#line 2966 "dhcp4_parser.cc" // lalr1.cc:859
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
     201,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,
    -473,  -473,    32,    19,    23,    36,    56,    73,    90,   104,
     128,   139,   141,   164,  -473,  -473,  -473,  -473,  -473,  -473,
    -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,
    -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,
    -473,  -473,  -473,  -473,  -473,  -473,    19,   -95,    17,    29,
      57,    18,   -13,    94,    81,    43,   -30,    84,  -473,   157,
     170,   217,   221,   228,  -473,  -473,  -473,  -473,   248,  -473,
      30,  -473,  -473,  -473,  -473,  -473,  -473,   252,   253,  -473,
    -473,  -473,   255,   256,   257,   258,  -473,  -473,  -473,  -473,
    -473,  -473,  -473,   259,  -473,  -473,  -473,    31,  -473,  -473,
    -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,
    -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,
    -473,    49,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,
    -473,  -473,  -473,   260,   262,  -473,  -473,  -473,  -473,  -473,
    -473,  -473,  -473,  -473,    53,  -473,  -473,  -473,  -473,  -473,
    -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,
    -473,  -473,  -473,  -473,  -473,    93,  -473,  -473,  -473,  -473,
    -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,
     261,   264,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,
    -473,  -473,  -473,  -473,  -473,   267,  -473,  -473,  -473,   269,
    -473,  -473,   266,   272,  -473,  -473,  -473,  -473,  -473,  -473,
    -473,  -473,  -473,  -473,  -473,   273,  -473,  -473,  -473,  -473,
     270,   277,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,
    -473,   100,  -473,  -473,  -473,   280,  -473,  -473,   281,  -473,
     283,   285,  -473,  -473,   288,   289,   290,   295,  -473,  -473,
    -473,   107,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,
    -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,    19,
      19,  -473,   149,   296,   298,   299,   300,  -473,    17,  -473,
     301,   171,   172,   304,   305,   307,   180,   181,   182,   183,
     313,   314,   315,   316,   329,   330,   331,   203,   333,   334,
      29,  -473,   335,   336,    57,  -473,    80,   337,   338,   339,
     342,   343,   344,   345,   218,   219,   346,   348,   349,   351,
      18,  -473,   352,   353,   -13,  -473,   354,   355,   356,   357,
     358,   359,   360,   361,   362,  -473,    94,   363,   364,   237,
     365,   367,   368,   238,  -473,    81,   370,   240,  -473,    43,
     372,   373,   162,  -473,   243,   375,   376,   249,   377,   250,
     251,   381,   382,   254,   263,   265,   268,   383,   384,    84,
    -473,  -473,  -473,   386,   385,   387,    19,    19,  -473,   388,
    -473,  -473,   274,   389,   390,  -473,  -473,  -473,  -473,   394,
     396,   397,   399,   400,   402,   401,  -473,   403,   404,  -473,
     407,   235,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,
     405,   406,  -473,  -473,  -473,   282,   284,   286,   410,   287,
     291,   292,  -473,  -473,   144,   293,   412,   413,  -473,   297,
     414,  -473,   302,   303,   407,   306,   310,   311,   318,   319,
     320,  -473,   321,   322,  -473,   323,   325,   326,  -473,  -473,
     328,  -473,  -473,   332,    19,  -473,  -473,   340,   341,  -473,
     347,  -473,  -473,    14,   366,  -473,  -473,  -473,  -473,   -28,
     350,  -473,    19,    29,   279,  -473,  -473,    57,  -473,   111,
     111,   421,   423,   426,   163,    37,   429,   110,   165,    84,
    -473,  -473,  -473,  -473,  -473,   433,  -473,    80,  -473,  -473,
    -473,   432,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,
     438,   371,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,
    -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,
    -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,
    -473,  -473,  -473,  -473,  -473,  -473,  -473,   115,  -473,   119,
    -473,  -473,   166,  -473,  -473,  -473,  -473,   442,   444,   457,
     458,  -473,   194,  -473,  -473,  -473,  -473,  -473,  -473,  -473,
    -473,  -473,  -473,   195,  -473,   459,   460,  -473,  -473,   461,
     463,  -473,  -473,   462,   466,  -473,  -473,  -473,  -473,  -473,
     156,  -473,  -473,  -473,  -473,  -473,  -473,   222,  -473,   464,
     468,  -473,   471,   472,   473,   474,   476,   477,   196,  -473,
    -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,   197,  -473,
    -473,  -473,   206,   369,   374,  -473,  -473,   478,   480,  -473,
    -473,   479,   483,  -473,  -473,   481,  -473,   484,   279,  -473,
    -473,   486,   487,   488,   489,   378,   379,   380,   391,   111,
    -473,  -473,    18,  -473,   421,    81,  -473,   423,    43,  -473,
     426,   163,  -473,    37,  -473,   -30,  -473,   429,   392,   393,
     395,   398,   408,   409,   110,  -473,   490,   491,   165,  -473,
    -473,  -473,   492,   493,  -473,   -13,  -473,   432,    94,  -473,
     438,   495,  -473,   482,  -473,   220,   411,   415,   416,  -473,
    -473,  -473,  -473,  -473,   212,  -473,   494,  -473,   496,  -473,
    -473,  -473,   214,  -473,  -473,  -473,  -473,  -473,  -473,  -473,
    -473,   417,   418,  -473,  -473,   419,   215,  -473,   497,  -473,
     420,   500,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,
    -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,
    -473,   236,  -473,    40,   500,  -473,  -473,   499,  -473,  -473,
    -473,   216,  -473,  -473,  -473,  -473,  -473,   504,   422,   505,
      40,  -473,   506,  -473,   424,  -473,   503,  -473,  -473,   245,
    -473,   275,   503,  -473,  -473,   224,  -473,  -473,   510,   275,
    -473,   425,  -473,  -473
  };

  const unsigned short int
  Dhcp4Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     1,    39,    32,    28,    27,    24,
      25,    26,    31,     3,    29,    30,    52,     5,    63,     7,
     100,     9,   197,    11,   311,    13,   331,    15,   250,    17,
     285,    19,   162,    21,   406,    23,    41,    35,     0,     0,
       0,     0,     0,   333,   252,   287,     0,     0,    43,     0,
      42,     0,     0,    36,    61,   459,   455,   457,     0,    60,
       0,    54,    56,    58,    59,    57,    94,     0,     0,   349,
     108,   110,     0,     0,     0,     0,   189,   242,   277,   142,
     373,   154,   173,     0,   394,   404,    87,     0,    65,    67,
      68,    69,    70,    84,    85,    72,    73,    74,    75,    79,
      80,    71,    77,    78,    86,    76,    81,    82,    83,   102,
     104,     0,    96,    98,    99,   377,   223,   225,   227,   303,
     221,   229,   231,     0,     0,   235,   233,   323,   369,   220,
     201,   202,   203,   215,     0,   199,   206,   217,   218,   219,
     207,   208,   211,   213,   209,   210,   204,   205,   212,   216,
     214,   319,   321,   318,   316,     0,   313,   315,   317,   351,
     353,   367,   357,   359,   363,   361,   365,   355,   348,   344,
       0,   334,   335,   345,   346,   347,   341,   337,   342,   339,
     340,   343,   338,   267,   136,     0,   271,   269,   274,     0,
     263,   264,     0,   253,   254,   256,   266,   257,   258,   259,
     273,   260,   261,   262,   298,     0,   296,   297,   300,   301,
       0,   288,   289,   291,   292,   293,   294,   295,   169,   171,
     166,     0,   164,   167,   168,     0,   427,   429,     0,   432,
       0,     0,   436,   440,     0,     0,     0,     0,   446,   453,
     425,     0,   408,   410,   411,   412,   413,   414,   415,   416,
     417,   418,   419,   420,   421,   422,   423,   424,    40,     0,
       0,    33,     0,     0,     0,     0,     0,    51,     0,    53,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    64,     0,     0,     0,   101,   379,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   198,     0,     0,     0,   312,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   332,     0,     0,     0,     0,
       0,     0,     0,     0,   251,     0,     0,     0,   286,     0,
       0,     0,     0,   163,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     407,    44,    37,     0,     0,     0,     0,     0,    55,     0,
      92,    93,     0,     0,     0,    88,    89,    90,    91,     0,
       0,     0,     0,     0,     0,     0,   393,     0,     0,    66,
       0,     0,    97,   391,   389,   390,   385,   386,   387,   388,
       0,   380,   381,   383,   384,     0,     0,     0,     0,     0,
       0,     0,   240,   241,     0,     0,     0,     0,   200,     0,
       0,   314,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   336,     0,     0,   265,     0,     0,     0,   276,   255,
       0,   302,   290,     0,     0,   165,   426,     0,     0,   431,
       0,   434,   435,     0,     0,   442,   443,   444,   445,     0,
       0,   409,     0,     0,     0,   456,   458,     0,   350,     0,
       0,   191,   244,   279,     0,     0,   156,     0,     0,     0,
      45,   103,   106,   107,   105,     0,   378,     0,   224,   226,
     228,   305,   222,   230,   232,   237,   238,   239,   236,   234,
     325,     0,   320,    34,   322,   352,   354,   368,   358,   360,
     364,   362,   366,   356,   268,   137,   272,   270,   275,   299,
     170,   172,   428,   430,   433,   438,   439,   437,   441,   448,
     449,   450,   451,   452,   447,   454,    38,     0,   464,     0,
     461,   463,     0,   124,   130,   132,   134,     0,     0,     0,
       0,   123,     0,   112,   114,   115,   116,   117,   118,   119,
     120,   121,   122,     0,   195,     0,   192,   193,   248,     0,
     245,   246,   283,     0,   280,   281,   150,   151,   152,   153,
       0,   144,   146,   147,   148,   149,   375,     0,   160,     0,
     157,   158,     0,     0,     0,     0,     0,     0,     0,   175,
     177,   178,   179,   180,   181,   182,   400,   402,     0,   396,
     398,   399,     0,    47,     0,   382,   309,     0,   306,   307,
     329,     0,   326,   327,   371,     0,    62,     0,     0,   460,
      95,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     109,   111,     0,   190,     0,   252,   243,     0,   287,   278,
       0,     0,   143,     0,   374,     0,   155,     0,     0,     0,
       0,     0,     0,     0,     0,   174,     0,     0,     0,   395,
     405,    49,     0,    48,   392,     0,   304,     0,   333,   324,
       0,     0,   370,     0,   462,     0,     0,     0,     0,   138,
     139,   140,   141,   113,     0,   194,     0,   247,     0,   282,
     145,   376,     0,   159,   183,   184,   185,   186,   187,   188,
     176,     0,     0,   397,    46,     0,     0,   308,     0,   328,
       0,     0,   126,   127,   128,   129,   125,   131,   133,   135,
     196,   249,   284,   161,   401,   403,    50,   310,   330,   372,
     468,     0,   466,     0,     0,   465,   480,     0,   478,   476,
     472,     0,   470,   474,   475,   473,   467,     0,     0,     0,
       0,   469,     0,   477,     0,   471,     0,   479,   484,     0,
     482,     0,     0,   481,   488,     0,   486,   483,     0,     0,
     485,     0,   487,   489
  };

  const short int
  Dhcp4Parser::yypgoto_[] =
  {
    -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,
    -473,  -473,  -473,   -42,  -473,    60,  -473,  -473,  -473,  -473,
    -473,  -473,  -473,  -473,    72,  -473,  -473,  -473,   -58,  -473,
    -473,  -473,   209,  -473,  -473,  -473,  -473,    34,   208,   -60,
     -44,   -40,  -473,  -473,   -39,  -473,  -473,    33,   205,  -473,
    -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,
      39,  -138,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,
    -473,   -63,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,
    -149,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -154,
    -473,  -473,  -473,  -148,   168,  -473,  -473,  -473,  -473,  -473,
    -473,  -473,  -152,  -473,  -473,  -473,  -473,  -473,  -473,  -473,
    -473,  -473,  -473,  -131,  -473,  -473,  -473,  -128,   207,  -473,
    -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,
    -473,  -472,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,
    -473,  -473,  -132,  -473,  -473,  -473,  -129,  -473,   184,  -473,
     -49,  -473,  -473,  -473,  -473,  -473,   -47,  -473,  -473,  -473,
    -473,  -473,   -51,  -473,  -473,  -473,  -130,  -473,  -473,  -473,
    -124,  -473,   179,  -473,  -473,  -473,  -473,  -473,  -473,  -473,
    -473,  -473,  -473,  -151,  -473,  -473,  -473,  -150,   225,  -473,
    -473,  -473,  -473,  -473,  -473,  -473,  -473,  -147,  -473,  -473,
    -473,  -144,  -473,   223,   -48,  -473,  -297,  -473,  -296,  -473,
    -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,
    -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,
    -473,  -473,  -473,  -473,    51,  -473,  -473,  -473,  -473,  -473,
    -473,  -473,  -127,  -473,  -473,  -473,  -473,  -473,  -473,  -473,
    -473,    61,   185,  -473,  -473,  -473,  -473,  -473,  -473,  -473,
    -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,
    -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,  -473,
    -473,  -473,  -473,  -473,   -86,  -473,  -473,  -473,  -201,  -473,
    -473,  -215,  -473,  -473,  -473,  -473,  -473,  -473,  -226,  -473,
    -473,  -232,  -473
  };

  const short int
  Dhcp4Parser::yydefgoto_[] =
  {
      -1,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    32,    33,    34,    57,   524,    72,    73,
      35,    56,    69,    70,   501,   633,   692,   693,   106,    37,
      58,    80,    81,    82,   283,    39,    59,   107,   108,   109,
     110,   111,   112,   113,   114,   115,   290,   131,   132,    41,
      60,   133,   312,   134,   313,   504,   116,   294,   117,   295,
     572,   573,   574,   651,   746,   575,   652,   576,   653,   577,
     654,   211,   348,   579,   580,   581,   582,   118,   303,   600,
     601,   602,   603,   604,   605,   119,   305,   609,   610,   611,
     675,    53,    66,   241,   242,   243,   360,   244,   361,   120,
     306,   618,   619,   620,   621,   622,   623,   624,   625,   121,
     300,   585,   586,   587,   662,    43,    61,   154,   155,   156,
     321,   157,   317,   158,   318,   159,   319,   160,   322,   161,
     323,   162,   327,   163,   326,   518,   164,   165,   122,   301,
     589,   590,   591,   665,    49,    64,   212,   213,   214,   215,
     216,   217,   218,   347,   219,   351,   220,   350,   221,   222,
     352,   223,   123,   302,   593,   594,   595,   668,    51,    65,
     230,   231,   232,   233,   234,   356,   235,   236,   237,   167,
     320,   637,   638,   639,   695,    45,    62,   175,   176,   177,
     332,   178,   333,   168,   328,   641,   642,   643,   698,    47,
      63,   190,   191,   192,   124,   293,   194,   336,   195,   337,
     196,   344,   197,   339,   198,   340,   199,   342,   200,   341,
     201,   343,   202,   338,   170,   329,   645,   701,   125,   304,
     607,   316,   420,   421,   422,   423,   424,   505,   126,   127,
     308,   628,   629,   630,   686,   631,   687,   128,   309,    55,
      67,   261,   262,   263,   264,   365,   265,   366,   266,   267,
     368,   268,   269,   270,   371,   547,   271,   372,   272,   273,
     274,   275,   276,   377,   554,   277,   378,    83,   285,    84,
     286,    85,   284,   559,   560,   561,   647,   761,   762,   763,
     771,   772,   773,   774,   779,   775,   777,   789,   790,   791,
     795,   796,   798
  };

  const unsigned short int
  Dhcp4Parser::yytable_[] =
  {
      79,   150,   227,   149,   173,   188,   210,   226,   240,   260,
     166,   174,   189,   169,    68,   193,   228,   151,   229,   418,
     419,   152,   153,   606,    25,   135,    26,    74,    27,   545,
      36,    98,    24,   288,   310,    88,    89,    71,   289,   311,
      86,   171,   172,    38,   135,    87,    88,    89,   238,   239,
      90,    91,   314,    92,    93,    94,   330,   315,   136,   137,
     138,   331,    98,    40,    92,    93,    94,    95,    96,   129,
     130,   139,    97,    98,   140,   141,   142,   143,   144,   145,
      42,   549,   550,   551,   552,   204,   146,   147,   204,   224,
     205,   206,   225,   148,    99,   100,   334,    44,    89,   179,
     180,   335,    78,   362,   203,   146,   101,   553,   363,   102,
     379,    46,    89,   179,   180,   380,   103,   104,   310,    78,
     105,   546,   648,   646,    98,   204,   204,   649,   205,   206,
      75,   207,   208,   209,   563,    48,    76,    77,    98,   564,
     565,   566,   567,   568,   569,   570,    50,   413,    52,    78,
      78,    28,    29,    30,    31,   766,   204,   767,   768,   671,
     181,    78,   672,   278,   182,   183,   184,   185,   186,   314,
     187,    54,    78,   279,   650,    78,   245,   246,   247,   248,
     249,   250,   251,   252,   253,   254,   255,   256,   257,   258,
     259,   612,   613,   614,   615,   616,   617,   659,   659,   684,
     688,   721,   660,   661,   685,   689,   515,   516,   517,   379,
     418,   419,    78,    78,   690,   330,    78,   362,   334,   780,
     750,   280,   753,   757,   781,   673,    78,   799,   674,   281,
      79,   282,   800,   596,   597,   598,   599,   381,   382,   764,
     238,   239,   765,    78,   742,   743,   744,   745,   792,   502,
     503,   793,   287,   415,   626,   627,   291,   292,   414,   296,
     297,   298,   299,   307,   324,   416,   325,   346,   417,   345,
     150,   349,   149,   353,   354,   355,   173,   357,   358,   166,
     359,   383,   169,   174,   364,   367,   151,   369,   188,   370,
     152,   153,   373,   374,   375,   189,   227,   210,   193,   376,
     384,   226,   385,   386,   387,   389,   390,   391,   392,   393,
     228,   394,   229,   395,   396,   397,   398,   399,   400,   401,
     402,   260,     1,     2,     3,     4,     5,     6,     7,     8,
       9,    10,    11,   403,   404,   405,   406,   407,   408,   410,
     411,   425,   426,   427,   485,   486,   428,   429,   430,   431,
     434,   432,   435,   436,   433,   437,   439,   440,   442,   443,
     444,   445,   446,   447,   448,   449,   450,   452,   453,   455,
     454,   456,   457,   458,   460,   461,   463,   464,   466,   467,
     468,   470,   469,   471,   472,   473,   474,   479,   480,   475,
     482,   794,   483,   558,   484,   487,   489,   490,   476,   491,
     477,   492,   493,   478,   494,   495,   488,   496,   497,   507,
     498,   499,   500,   506,   508,   511,   509,   520,   510,   512,
     521,    26,   541,   513,   514,   519,   578,   578,   584,   522,
     588,   571,   571,   592,   525,   526,   608,   634,   528,   636,
     556,   260,   529,   530,   415,   640,   655,   644,   656,   414,
     531,   532,   533,   534,   535,   536,   416,   537,   538,   417,
     539,   657,   658,   664,   540,   663,   667,   666,   669,   670,
     676,   677,   542,   543,   548,   678,   679,   680,   681,   544,
     682,   683,   555,   697,   696,   699,   700,   741,   703,   702,
     705,   706,   707,   708,   731,   732,   735,   388,   734,   740,
     523,   691,   751,   778,   752,   758,   694,   760,   782,   784,
     788,   786,   710,   709,   801,   711,   527,   557,   409,   412,
     562,   713,   720,   723,   712,   724,   725,   722,   726,   583,
     465,   727,   730,   715,   714,   717,   716,   438,   462,   459,
     719,   728,   729,   747,   718,   736,   737,   748,   749,   754,
     755,   756,   759,   739,   738,   783,   787,   803,   635,   441,
     632,   733,   704,   776,   481,   785,   797,   802,     0,   451,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   578,     0,     0,     0,
       0,   571,   150,     0,   149,   227,     0,   210,     0,     0,
     226,   166,     0,     0,   169,     0,     0,   240,   151,   228,
       0,   229,   152,   153,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   173,     0,     0,
     188,     0,     0,     0,   174,     0,     0,   189,     0,     0,
     193,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     770,     0,     0,     0,     0,   769,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   770,     0,     0,
       0,     0,   769
  };

  const short int
  Dhcp4Parser::yycheck_[] =
  {
      58,    61,    65,    61,    62,    63,    64,    65,    66,    67,
      61,    62,    63,    61,    56,    63,    65,    61,    65,   316,
     316,    61,    61,   495,     5,     7,     7,    10,     9,    15,
       7,    44,     0,     3,     3,    17,    18,   132,     8,     8,
      11,    54,    55,     7,     7,    16,    17,    18,    78,    79,
      21,    22,     3,    35,    36,    37,     3,     8,    40,    41,
      42,     8,    44,     7,    35,    36,    37,    38,    39,    12,
      13,    53,    43,    44,    56,    57,    58,    59,    60,    61,
       7,   109,   110,   111,   112,    45,    68,    69,    45,    46,
      47,    48,    49,    75,    65,    66,     3,     7,    18,    19,
      20,     8,   132,     3,    23,    68,    77,   135,     8,    80,
       3,     7,    18,    19,    20,     8,    87,    88,     3,   132,
      91,   107,     3,     8,    44,    45,    45,     8,    47,    48,
     113,    50,    51,    52,    23,     7,   119,   120,    44,    28,
      29,    30,    31,    32,    33,    34,     7,    67,     7,   132,
     132,   132,   133,   134,   135,   115,    45,   117,   118,     3,
      66,   132,     6,     6,    70,    71,    72,    73,    74,     3,
      76,     7,   132,     3,     8,   132,    92,    93,    94,    95,
      96,    97,    98,    99,   100,   101,   102,   103,   104,   105,
     106,    81,    82,    83,    84,    85,    86,     3,     3,     3,
       3,   673,     8,     8,     8,     8,    62,    63,    64,     3,
     507,   507,   132,   132,     8,     3,   132,     3,     3,     3,
       8,     4,     8,     8,     8,     3,   132,     3,     6,     8,
     288,     3,     8,    70,    71,    72,    73,   279,   280,     3,
      78,    79,     6,   132,    24,    25,    26,    27,     3,    14,
      15,     6,     4,   316,    89,    90,     4,     4,   316,     4,
       4,     4,     4,     4,     4,   316,     4,     3,   316,     8,
     330,     4,   330,     4,     8,     3,   334,     4,     8,   330,
       3,   132,   330,   334,     4,     4,   330,     4,   346,     4,
     330,   330,     4,     4,     4,   346,   359,   355,   346,     4,
       4,   359,     4,     4,     4,     4,   135,   135,     4,     4,
     359,     4,   359,   133,   133,   133,   133,     4,     4,     4,
       4,   379,   121,   122,   123,   124,   125,   126,   127,   128,
     129,   130,   131,     4,     4,     4,   133,     4,     4,     4,
       4,     4,     4,     4,   386,   387,     4,     4,     4,     4,
       4,   133,     4,     4,   135,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
     133,     4,     4,   135,     4,   135,     4,     4,   135,     4,
       4,     4,   133,   133,   133,     4,     4,     4,     4,   135,
       4,   116,     7,   114,     7,     7,     7,     7,   135,     5,
     135,     5,     5,   135,     5,     5,   132,     5,     7,     3,
       7,     7,     5,     8,   132,     5,   132,     5,   132,   132,
       7,     7,   464,   132,   132,   132,   489,   490,     7,   132,
       7,   489,   490,     7,   132,   132,     7,     4,   132,     7,
     482,   499,   132,   132,   507,     7,     4,    76,     4,   507,
     132,   132,   132,   132,   132,   132,   507,   132,   132,   507,
     132,     4,     4,     3,   132,     6,     3,     6,     6,     3,
       6,     3,   132,   132,   108,     4,     4,     4,     4,   132,
       4,     4,   132,     3,     6,     6,     3,     5,     4,     8,
       4,     4,     4,     4,     4,     4,     3,   288,     6,     4,
     440,   132,     8,     4,     8,     8,   132,     7,     4,     4,
       7,     5,   133,   135,     4,   135,   444,   483,   310,   314,
     487,   659,   671,   677,   133,   133,   133,   675,   133,   490,
     362,   133,   684,   664,   662,   667,   665,   330,   359,   355,
     670,   133,   133,   132,   668,   695,   697,   132,   132,   132,
     132,   132,   132,   700,   698,   133,   132,   132,   507,   334,
     499,   688,   648,   764,   379,   780,   792,   799,    -1,   346,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   659,    -1,    -1,    -1,
      -1,   659,   662,    -1,   662,   668,    -1,   665,    -1,    -1,
     668,   662,    -1,    -1,   662,    -1,    -1,   675,   662,   668,
      -1,   668,   662,   662,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   695,    -1,    -1,
     698,    -1,    -1,    -1,   695,    -1,    -1,   698,    -1,    -1,
     698,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     763,    -1,    -1,    -1,    -1,   763,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   780,    -1,    -1,
      -1,    -1,   780
  };

  const unsigned short int
  Dhcp4Parser::yystos_[] =
  {
       0,   121,   122,   123,   124,   125,   126,   127,   128,   129,
     130,   131,   137,   138,   139,   140,   141,   142,   143,   144,
     145,   146,   147,   148,     0,     5,     7,     9,   132,   133,
     134,   135,   149,   150,   151,   156,     7,   165,     7,   171,
       7,   185,     7,   251,     7,   321,     7,   335,     7,   280,
       7,   304,     7,   227,     7,   385,   157,   152,   166,   172,
     186,   252,   322,   336,   281,   305,   228,   386,   149,   158,
     159,   132,   154,   155,    10,   113,   119,   120,   132,   164,
     167,   168,   169,   413,   415,   417,    11,    16,    17,    18,
      21,    22,    35,    36,    37,    38,    39,    43,    44,    65,
      66,    77,    80,    87,    88,    91,   164,   173,   174,   175,
     176,   177,   178,   179,   180,   181,   192,   194,   213,   221,
     235,   245,   274,   298,   340,   364,   374,   375,   383,    12,
      13,   183,   184,   187,   189,     7,    40,    41,    42,    53,
      56,    57,    58,    59,    60,    61,    68,    69,    75,   164,
     175,   176,   177,   180,   253,   254,   255,   257,   259,   261,
     263,   265,   267,   269,   272,   273,   298,   315,   329,   340,
     360,    54,    55,   164,   298,   323,   324,   325,   327,    19,
      20,    66,    70,    71,    72,    73,    74,    76,   164,   298,
     337,   338,   339,   340,   342,   344,   346,   348,   350,   352,
     354,   356,   358,    23,    45,    47,    48,    50,    51,    52,
     164,   207,   282,   283,   284,   285,   286,   287,   288,   290,
     292,   294,   295,   297,    46,    49,   164,   207,   286,   292,
     306,   307,   308,   309,   310,   312,   313,   314,    78,    79,
     164,   229,   230,   231,   233,    92,    93,    94,    95,    96,
      97,    98,    99,   100,   101,   102,   103,   104,   105,   106,
     164,   387,   388,   389,   390,   392,   394,   395,   397,   398,
     399,   402,   404,   405,   406,   407,   408,   411,     6,     3,
       4,     8,     3,   170,   418,   414,   416,     4,     3,     8,
     182,     4,     4,   341,   193,   195,     4,     4,     4,     4,
     246,   275,   299,   214,   365,   222,   236,     4,   376,   384,
       3,     8,   188,   190,     3,     8,   367,   258,   260,   262,
     316,   256,   264,   266,     4,     4,   270,   268,   330,   361,
       3,     8,   326,   328,     3,     8,   343,   345,   359,   349,
     351,   355,   353,   357,   347,     8,     3,   289,   208,     4,
     293,   291,   296,     4,     8,     3,   311,     4,     8,     3,
     232,   234,     3,     8,     4,   391,   393,     4,   396,     4,
       4,   400,   403,     4,     4,     4,     4,   409,   412,     3,
       8,   149,   149,   132,     4,     4,     4,     4,   168,     4,
     135,   135,     4,     4,     4,   133,   133,   133,   133,     4,
       4,     4,     4,     4,     4,     4,   133,     4,     4,   174,
       4,     4,   184,    67,   164,   207,   298,   340,   342,   344,
     368,   369,   370,   371,   372,     4,     4,     4,     4,     4,
       4,     4,   133,   135,     4,     4,     4,     4,   254,     4,
       4,   324,     4,     4,     4,     4,     4,     4,     4,     4,
       4,   339,     4,     4,   133,     4,     4,     4,   135,   284,
       4,   135,   308,     4,     4,   230,   135,     4,     4,   133,
       4,   133,   133,     4,     4,   135,   135,   135,   135,     4,
       4,   388,     4,     7,     7,   149,   149,     7,   132,     7,
       7,     5,     5,     5,     5,     5,     5,     7,     7,     7,
       5,   160,    14,    15,   191,   373,     8,     3,   132,   132,
     132,     5,   132,   132,   132,    62,    63,    64,   271,   132,
       5,     7,   132,   151,   153,   132,   132,   160,   132,   132,
     132,   132,   132,   132,   132,   132,   132,   132,   132,   132,
     132,   149,   132,   132,   132,    15,   107,   401,   108,   109,
     110,   111,   112,   135,   410,   132,   149,   173,   114,   419,
     420,   421,   183,    23,    28,    29,    30,    31,    32,    33,
      34,   164,   196,   197,   198,   201,   203,   205,   207,   209,
     210,   211,   212,   196,     7,   247,   248,   249,     7,   276,
     277,   278,     7,   300,   301,   302,    70,    71,    72,    73,
     215,   216,   217,   218,   219,   220,   267,   366,     7,   223,
     224,   225,    81,    82,    83,    84,    85,    86,   237,   238,
     239,   240,   241,   242,   243,   244,    89,    90,   377,   378,
     379,   381,   387,   161,     4,   370,     7,   317,   318,   319,
       7,   331,   332,   333,    76,   362,     8,   422,     3,     8,
       8,   199,   202,   204,   206,     4,     4,     4,     4,     3,
       8,     8,   250,     6,     3,   279,     6,     3,   303,     6,
       3,     3,     6,     3,     6,   226,     6,     3,     4,     4,
       4,     4,     4,     4,     3,     8,   380,   382,     3,     8,
       8,   132,   162,   163,   132,   320,     6,     3,   334,     6,
       3,   363,     8,     4,   420,     4,     4,     4,     4,   135,
     133,   135,   133,   197,   253,   249,   282,   278,   306,   302,
     216,   267,   229,   225,   133,   133,   133,   133,   133,   133,
     238,     4,     4,   378,     6,     3,   323,   319,   337,   333,
       4,     5,    24,    25,    26,    27,   200,   132,   132,   132,
       8,     8,     8,     8,   132,   132,   132,     8,     8,   132,
       7,   423,   424,   425,     3,     6,   115,   117,   118,   164,
     207,   426,   427,   428,   429,   431,   424,   432,     4,   430,
       3,     8,     4,   133,     4,   427,     5,   132,     7,   433,
     434,   435,     3,     6,   116,   436,   437,   434,   438,     3,
       8,     4,   437,   132
  };

  const unsigned short int
  Dhcp4Parser::yyr1_[] =
  {
       0,   136,   138,   137,   139,   137,   140,   137,   141,   137,
     142,   137,   143,   137,   144,   137,   145,   137,   146,   137,
     147,   137,   148,   137,   149,   149,   149,   149,   149,   149,
     149,   150,   152,   151,   153,   154,   154,   155,   155,   157,
     156,   158,   158,   159,   159,   161,   160,   162,   162,   163,
     163,   164,   166,   165,   167,   167,   168,   168,   168,   168,
     168,   170,   169,   172,   171,   173,   173,   174,   174,   174,
     174,   174,   174,   174,   174,   174,   174,   174,   174,   174,
     174,   174,   174,   174,   174,   174,   174,   174,   175,   176,
     177,   178,   179,   180,   182,   181,   183,   183,   184,   184,
     186,   185,   188,   187,   190,   189,   191,   191,   193,   192,
     195,   194,   196,   196,   197,   197,   197,   197,   197,   197,
     197,   197,   197,   197,   199,   198,   200,   200,   200,   200,
     202,   201,   204,   203,   206,   205,   208,   207,   209,   210,
     211,   212,   214,   213,   215,   215,   216,   216,   216,   216,
     217,   218,   219,   220,   222,   221,   223,   223,   224,   224,
     226,   225,   228,   227,   229,   229,   229,   230,   230,   232,
     231,   234,   233,   236,   235,   237,   237,   238,   238,   238,
     238,   238,   238,   239,   240,   241,   242,   243,   244,   246,
     245,   247,   247,   248,   248,   250,   249,   252,   251,   253,
     253,   254,   254,   254,   254,   254,   254,   254,   254,   254,
     254,   254,   254,   254,   254,   254,   254,   254,   254,   254,
     254,   256,   255,   258,   257,   260,   259,   262,   261,   264,
     263,   266,   265,   268,   267,   270,   269,   271,   271,   271,
     272,   273,   275,   274,   276,   276,   277,   277,   279,   278,
     281,   280,   282,   282,   283,   283,   284,   284,   284,   284,
     284,   284,   284,   284,   285,   286,   287,   289,   288,   291,
     290,   293,   292,   294,   296,   295,   297,   299,   298,   300,
     300,   301,   301,   303,   302,   305,   304,   306,   306,   307,
     307,   308,   308,   308,   308,   308,   308,   309,   311,   310,
     312,   313,   314,   316,   315,   317,   317,   318,   318,   320,
     319,   322,   321,   323,   323,   324,   324,   324,   324,   326,
     325,   328,   327,   330,   329,   331,   331,   332,   332,   334,
     333,   336,   335,   337,   337,   338,   338,   339,   339,   339,
     339,   339,   339,   339,   339,   339,   339,   339,   339,   341,
     340,   343,   342,   345,   344,   347,   346,   349,   348,   351,
     350,   353,   352,   355,   354,   357,   356,   359,   358,   361,
     360,   363,   362,   365,   364,   366,   366,   367,   267,   368,
     368,   369,   369,   370,   370,   370,   370,   370,   370,   370,
     371,   373,   372,   374,   376,   375,   377,   377,   378,   378,
     380,   379,   382,   381,   384,   383,   386,   385,   387,   387,
     388,   388,   388,   388,   388,   388,   388,   388,   388,   388,
     388,   388,   388,   388,   388,   388,   389,   391,   390,   393,
     392,   394,   396,   395,   397,   398,   400,   399,   401,   401,
     403,   402,   404,   405,   406,   407,   409,   408,   410,   410,
     410,   410,   410,   412,   411,   414,   413,   416,   415,   418,
     417,   419,   419,   420,   422,   421,   423,   423,   425,   424,
     426,   426,   427,   427,   427,   427,   427,   428,   430,   429,
     432,   431,   433,   433,   435,   434,   436,   436,   438,   437
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
       4,     0,     4,     0,     4,     0,     4,     1,     1,     1,
       3,     3,     0,     6,     0,     1,     1,     3,     0,     4,
       0,     4,     0,     1,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     3,     1,     0,     4,     0,
       4,     0,     4,     1,     0,     4,     3,     0,     6,     0,
       1,     1,     3,     0,     4,     0,     4,     0,     1,     1,
       3,     1,     1,     1,     1,     1,     1,     1,     0,     4,
       1,     1,     3,     0,     6,     0,     1,     1,     3,     0,
       4,     0,     4,     1,     3,     1,     1,     1,     1,     0,
       4,     0,     4,     0,     6,     0,     1,     1,     3,     0,
       4,     0,     4,     0,     1,     1,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       6,     0,     4,     0,     6,     1,     3,     0,     4,     0,
       1,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     0,     4,     3,     0,     6,     1,     3,     1,     1,
       0,     4,     0,     4,     0,     6,     0,     4,     1,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     3,     0,     4,     0,
       4,     3,     0,     4,     3,     3,     0,     4,     1,     1,
       0,     4,     3,     3,     3,     3,     0,     4,     1,     1,
       1,     1,     1,     0,     4,     0,     4,     0,     4,     0,
       6,     1,     3,     1,     0,     6,     1,     3,     0,     4,
       1,     3,     1,     1,     1,     1,     1,     3,     0,     4,
       0,     6,     1,     3,     0,     4,     1,     3,     0,     4
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
  "\"reservation-mode\"", "\"disabled\"", "\"out-of-pool\"", "\"all\"",
  "\"host-reservation-identifiers\"", "\"client-classes\"", "\"test\"",
  "\"client-class\"", "\"reservations\"", "\"duid\"", "\"hw-address\"",
  "\"circuit-id\"", "\"client-id\"", "\"hostname\"", "\"relay\"",
  "\"ip-address\"", "\"hooks-libraries\"", "\"library\"", "\"parameters\"",
  "\"expired-leases-processing\"", "\"reclaim-timer-wait-time\"",
  "\"flush-reclaimed-timer-wait-time\"", "\"hold-reclaimed-time\"",
  "\"max-reclaim-leases\"", "\"max-reclaim-time\"",
  "\"unwarned-reclaim-cycles\"", "\"dhcp4o6-port\"", "\"control-socket\"",
  "\"socket-type\"", "\"socket-name\"", "\"dhcp-ddns\"",
  "\"enable-updates\"", "\"qualifying-suffix\"", "\"server-ip\"",
  "\"server-port\"", "\"sender-ip\"", "\"sender-port\"",
  "\"max-queue-size\"", "\"ncr-protocol\"", "\"ncr-format\"",
  "\"always-include-fqdn\"", "\"allow-client-update\"",
  "\"override-no-update\"", "\"override-client-update\"",
  "\"replace-client-name\"", "\"generated-prefix\"", "\"tcp\"", "\"JSON\"",
  "\"when-present\"", "\"never\"", "\"always\"", "\"when-not-present\"",
  "\"Logging\"", "\"loggers\"", "\"output_options\"", "\"output\"",
  "\"debuglevel\"", "\"severity\"", "\"Dhcp6\"", "\"DhcpDdns\"",
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
  "$@20", "dhcp_socket_type", "$@21", "socket_type", "lease_database",
  "$@22", "hosts_database", "$@23", "database_map_params",
  "database_map_param", "database_type", "$@24", "db_type", "user", "$@25",
  "password", "$@26", "host", "$@27", "name", "$@28", "persist",
  "lfc_interval", "readonly", "connect_timeout",
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
  "reservation_mode", "$@46", "hr_mode", "id", "rapid_commit",
  "option_def_list", "$@47", "option_def_list_content",
  "not_empty_option_def_list", "option_def_entry", "$@48",
  "sub_option_def", "$@49", "option_def_params",
  "not_empty_option_def_params", "option_def_param", "option_def_name",
  "code", "option_def_code", "option_def_type", "$@50",
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
       0,   217,   217,   217,   218,   218,   219,   219,   220,   220,
     221,   221,   222,   222,   223,   223,   224,   224,   225,   225,
     226,   226,   227,   227,   235,   236,   237,   238,   239,   240,
     241,   244,   249,   249,   260,   263,   264,   267,   271,   278,
     278,   285,   286,   289,   293,   300,   300,   307,   308,   311,
     315,   326,   336,   336,   348,   349,   353,   354,   355,   356,
     357,   360,   360,   377,   377,   385,   386,   391,   392,   393,
     394,   395,   396,   397,   398,   399,   400,   401,   402,   403,
     404,   405,   406,   407,   408,   409,   410,   411,   414,   419,
     424,   429,   434,   439,   445,   445,   455,   456,   459,   460,
     463,   463,   471,   471,   481,   481,   488,   489,   492,   492,
     502,   502,   512,   513,   516,   517,   518,   519,   520,   521,
     522,   523,   524,   525,   528,   528,   535,   536,   537,   538,
     541,   541,   549,   549,   557,   557,   565,   565,   573,   578,
     583,   588,   593,   593,   603,   604,   607,   608,   609,   610,
     613,   618,   623,   628,   633,   633,   643,   644,   647,   648,
     651,   651,   659,   659,   667,   668,   669,   672,   673,   676,
     676,   684,   684,   692,   692,   702,   703,   706,   707,   708,
     709,   710,   711,   714,   719,   724,   729,   734,   739,   747,
     747,   760,   761,   764,   765,   772,   772,   795,   795,   804,
     805,   809,   810,   811,   812,   813,   814,   815,   816,   817,
     818,   819,   820,   821,   822,   823,   824,   825,   826,   827,
     828,   831,   831,   839,   839,   847,   847,   855,   855,   863,
     863,   871,   871,   879,   879,   887,   887,   894,   895,   896,
     899,   904,   913,   913,   925,   926,   929,   930,   935,   935,
     946,   946,   956,   957,   960,   961,   964,   965,   966,   967,
     968,   969,   970,   971,   974,   976,   981,   983,   983,   991,
     991,   999,   999,  1007,  1009,  1009,  1017,  1026,  1026,  1038,
    1039,  1044,  1045,  1050,  1050,  1061,  1061,  1072,  1073,  1078,
    1079,  1084,  1085,  1086,  1087,  1088,  1089,  1092,  1094,  1094,
    1102,  1104,  1106,  1114,  1114,  1126,  1127,  1130,  1131,  1134,
    1134,  1142,  1142,  1150,  1151,  1154,  1155,  1156,  1157,  1160,
    1160,  1168,  1168,  1178,  1178,  1188,  1189,  1192,  1193,  1196,
    1196,  1204,  1204,  1212,  1213,  1216,  1217,  1221,  1222,  1223,
    1224,  1225,  1226,  1227,  1228,  1229,  1230,  1231,  1232,  1235,
    1235,  1243,  1243,  1251,  1251,  1259,  1259,  1267,  1267,  1275,
    1275,  1283,  1283,  1291,  1291,  1300,  1300,  1308,  1308,  1321,
    1321,  1331,  1331,  1342,  1342,  1352,  1353,  1356,  1356,  1364,
    1365,  1368,  1369,  1372,  1373,  1374,  1375,  1376,  1377,  1378,
    1381,  1383,  1383,  1395,  1402,  1402,  1412,  1413,  1416,  1417,
    1420,  1420,  1428,  1428,  1438,  1438,  1448,  1448,  1456,  1457,
    1460,  1461,  1462,  1463,  1464,  1465,  1466,  1467,  1468,  1469,
    1470,  1471,  1472,  1473,  1474,  1475,  1478,  1483,  1483,  1491,
    1491,  1499,  1504,  1504,  1512,  1517,  1522,  1522,  1530,  1531,
    1534,  1534,  1542,  1547,  1552,  1557,  1562,  1562,  1570,  1573,
    1576,  1579,  1582,  1588,  1588,  1598,  1598,  1605,  1605,  1617,
    1617,  1630,  1631,  1635,  1639,  1639,  1651,  1652,  1656,  1656,
    1664,  1665,  1668,  1669,  1670,  1671,  1672,  1675,  1679,  1679,
    1687,  1687,  1697,  1698,  1701,  1701,  1709,  1710,  1713,  1713
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
#line 4027 "dhcp4_parser.cc" // lalr1.cc:1167
#line 1721 "dhcp4_parser.yy" // lalr1.cc:1168


void
isc::dhcp::Dhcp4Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
