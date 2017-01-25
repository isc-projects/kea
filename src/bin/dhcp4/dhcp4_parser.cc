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
      case 145: // value
      case 186: // socket_type
      case 195: // db_type
      case 393: // ncr_protocol_value
      case 402: // replace_client_name_value
        value.move< ElementPtr > (that.value);
        break;

      case 131: // "boolean"
        value.move< bool > (that.value);
        break;

      case 130: // "floating point"
        value.move< double > (that.value);
        break;

      case 129: // "integer"
        value.move< int64_t > (that.value);
        break;

      case 128: // "constant string"
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
      case 145: // value
      case 186: // socket_type
      case 195: // db_type
      case 393: // ncr_protocol_value
      case 402: // replace_client_name_value
        value.copy< ElementPtr > (that.value);
        break;

      case 131: // "boolean"
        value.copy< bool > (that.value);
        break;

      case 130: // "floating point"
        value.copy< double > (that.value);
        break;

      case 129: // "integer"
        value.copy< int64_t > (that.value);
        break;

      case 128: // "constant string"
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
            case 128: // "constant string"

#line 202 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< std::string > (); }
#line 360 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 129: // "integer"

#line 202 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< int64_t > (); }
#line 367 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 130: // "floating point"

#line 202 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< double > (); }
#line 374 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 131: // "boolean"

#line 202 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< bool > (); }
#line 381 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 145: // value

#line 202 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 388 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 186: // socket_type

#line 202 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 395 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 195: // db_type

#line 202 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 402 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 393: // ncr_protocol_value

#line 202 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 409 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 402: // replace_client_name_value

#line 202 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 416 "dhcp4_parser.cc" // lalr1.cc:636
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
      case 145: // value
      case 186: // socket_type
      case 195: // db_type
      case 393: // ncr_protocol_value
      case 402: // replace_client_name_value
        yylhs.value.build< ElementPtr > ();
        break;

      case 131: // "boolean"
        yylhs.value.build< bool > ();
        break;

      case 130: // "floating point"
        yylhs.value.build< double > ();
        break;

      case 129: // "integer"
        yylhs.value.build< int64_t > ();
        break;

      case 128: // "constant string"
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
#line 211 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.NO_KEYWORD; }
#line 660 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 4:
#line 212 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.CONFIG; }
#line 666 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 6:
#line 213 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.DHCP4; }
#line 672 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 8:
#line 214 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.INTERFACES_CONFIG; }
#line 678 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 10:
#line 215 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.SUBNET4; }
#line 684 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 12:
#line 216 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.POOLS; }
#line 690 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 14:
#line 217 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.RESERVATIONS; }
#line 696 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 16:
#line 218 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.OPTION_DEF; }
#line 702 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 18:
#line 219 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.OPTION_DATA; }
#line 708 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 20:
#line 220 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.HOOKS_LIBRARIES; }
#line 714 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 22:
#line 221 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.DHCP_DDNS; }
#line 720 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 24:
#line 229 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 726 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 25:
#line 230 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as< double > (), ctx.loc2pos(yystack_[0].location))); }
#line 732 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 26:
#line 231 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 738 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 27:
#line 232 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 744 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 28:
#line 233 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 750 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 29:
#line 234 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 756 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 30:
#line 235 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 762 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 31:
#line 238 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as< ElementPtr > ());
}
#line 771 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 32:
#line 243 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 782 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 33:
#line 248 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 792 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 36:
#line 259 "dhcp4_parser.yy" // lalr1.cc:859
    {
                  // map containing a single entry
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 801 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 37:
#line 263 "dhcp4_parser.yy" // lalr1.cc:859
    {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 811 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 38:
#line 270 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 820 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 39:
#line 273 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // list parsing complete. Put any sanity checking here
}
#line 828 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 42:
#line 281 "dhcp4_parser.yy" // lalr1.cc:859
    {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 837 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 43:
#line 285 "dhcp4_parser.yy" // lalr1.cc:859
    {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 846 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 44:
#line 292 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // List parsing about to start
}
#line 854 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 45:
#line 294 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // list parsing complete. Put any sanity checking here
    //ctx.stack_.pop_back();
}
#line 863 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 48:
#line 303 "dhcp4_parser.yy" // lalr1.cc:859
    {
                          ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 872 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 49:
#line 307 "dhcp4_parser.yy" // lalr1.cc:859
    {
                          ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 881 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 50:
#line 318 "dhcp4_parser.yy" // lalr1.cc:859
    {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as< std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 892 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 51:
#line 328 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 903 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 52:
#line 333 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 913 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 60:
#line 352 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Dhcp4", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP4);
}
#line 926 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 61:
#line 359 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 938 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 62:
#line 369 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the Dhcp4 map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 948 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 63:
#line 373 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 956 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 87:
#line 406 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 965 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 88:
#line 411 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 974 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 89:
#line 416 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 983 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 90:
#line 421 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr dpp(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 992 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 91:
#line 426 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr echo(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("echo-client-id", echo);
}
#line 1001 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 92:
#line 431 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr match(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("match-client-id", match);
}
#line 1010 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 93:
#line 437 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces-config", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.INTERFACES_CONFIG);
}
#line 1021 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 94:
#line 442 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1030 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 99:
#line 455 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1040 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 100:
#line 459 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1048 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 101:
#line 463 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1059 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 102:
#line 468 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1068 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 103:
#line 473 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.DHCP_SOCKET_TYPE);
}
#line 1076 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 104:
#line 475 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("dhcp-socket-type", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1085 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 105:
#line 480 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("raw", ctx.loc2pos(yystack_[0].location))); }
#line 1091 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 106:
#line 481 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("udp", ctx.loc2pos(yystack_[0].location))); }
#line 1097 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 107:
#line 484 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lease-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.LEASE_DATABASE);
}
#line 1108 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 108:
#line 489 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1117 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 109:
#line 494 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1128 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 110:
#line 499 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1137 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 123:
#line 520 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.DATABASE_TYPE);
}
#line 1145 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 124:
#line 522 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("type", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1154 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 125:
#line 527 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("memfile", ctx.loc2pos(yystack_[0].location))); }
#line 1160 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 126:
#line 528 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("mysql", ctx.loc2pos(yystack_[0].location))); }
#line 1166 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 127:
#line 529 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("postgresql", ctx.loc2pos(yystack_[0].location))); }
#line 1172 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 128:
#line 530 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("cql", ctx.loc2pos(yystack_[0].location))); }
#line 1178 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 129:
#line 533 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1186 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 130:
#line 535 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr user(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1196 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 131:
#line 541 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1204 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 132:
#line 543 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr pwd(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 1214 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 133:
#line 549 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1222 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 134:
#line 551 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr h(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 1232 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 135:
#line 557 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1240 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 136:
#line 559 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1250 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 137:
#line 565 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 1259 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 138:
#line 570 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 1268 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 139:
#line 575 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 1277 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 140:
#line 580 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("connect-timeout", n);
}
#line 1286 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 141:
#line 585 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 1297 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 142:
#line 590 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1306 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 149:
#line 605 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1315 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 150:
#line 610 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 1324 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 151:
#line 615 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr circuit(new StringElement("circuit-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(circuit);
}
#line 1333 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 152:
#line 620 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr client(new StringElement("client-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(client);
}
#line 1342 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 153:
#line 625 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 1353 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 154:
#line 630 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1362 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 159:
#line 643 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1372 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 160:
#line 647 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1380 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 161:
#line 651 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1390 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 162:
#line 655 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1398 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 168:
#line 668 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1406 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 169:
#line 670 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr lib(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 1416 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 170:
#line 676 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1424 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 171:
#line 678 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1433 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 172:
#line 684 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.EXPIRED_LEASES_PROCESSING);
}
#line 1444 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 173:
#line 689 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1453 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 182:
#line 706 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 1462 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 183:
#line 711 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 1471 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 184:
#line 716 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 1480 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 185:
#line 721 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 1489 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 186:
#line 726 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 1498 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 187:
#line 731 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 1507 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 188:
#line 739 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet4", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET4);
}
#line 1518 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 189:
#line 744 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1527 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 194:
#line 764 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1537 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 195:
#line 768 "dhcp4_parser.yy" // lalr1.cc:859
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
#line 1560 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 196:
#line 787 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the subnet4 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1570 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 197:
#line 791 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1578 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 220:
#line 823 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1586 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 221:
#line 825 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr subnet(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 1596 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 222:
#line 831 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1604 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 223:
#line 833 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface", iface);
    ctx.leave();
}
#line 1614 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 224:
#line 839 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1622 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 225:
#line 841 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface-id", iface);
    ctx.leave();
}
#line 1632 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 226:
#line 847 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1640 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 227:
#line 849 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-subnet", iface);
    ctx.leave();
}
#line 1650 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 228:
#line 855 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1658 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 229:
#line 857 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 1668 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 230:
#line 863 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1676 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 231:
#line 865 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface-id", iface);
    ctx.leave();
}
#line 1686 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 232:
#line 871 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.CLIENT_CLASS);
}
#line 1694 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 233:
#line 873 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr cls(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 1704 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 234:
#line 879 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1712 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 235:
#line 881 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr rm(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservation-mode", rm);
    ctx.leave();
}
#line 1722 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 236:
#line 887 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr id(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 1731 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 237:
#line 892 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr rc(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rapid-commit", rc);
}
#line 1740 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 238:
#line 901 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 1751 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 239:
#line 906 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1760 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 244:
#line 923 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1770 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 245:
#line 927 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1778 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 246:
#line 934 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1788 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 247:
#line 938 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1796 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 261:
#line 964 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr code(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 1805 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 263:
#line 971 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1813 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 264:
#line 973 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 1823 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 265:
#line 979 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1831 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 266:
#line 981 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 1841 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 267:
#line 987 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1849 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 268:
#line 989 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr space(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 1859 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 270:
#line 997 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1867 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 271:
#line 999 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr encap(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 1877 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 272:
#line 1005 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr array(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 1886 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 273:
#line 1014 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 1897 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 274:
#line 1019 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1906 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 279:
#line 1038 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1916 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 280:
#line 1042 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1924 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 281:
#line 1049 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1934 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 282:
#line 1053 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1942 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 294:
#line 1082 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1950 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 295:
#line 1084 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr data(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 1960 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 298:
#line 1094 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr space(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", space);
}
#line 1969 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 299:
#line 1102 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 1980 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 300:
#line 1107 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1989 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 305:
#line 1122 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1999 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 306:
#line 1126 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2007 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 307:
#line 1130 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2017 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 308:
#line 1134 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 2025 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 314:
#line 1147 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2033 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 315:
#line 1149 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr pool(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 2043 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 316:
#line 1158 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 2054 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 317:
#line 1163 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2063 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 322:
#line 1176 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2073 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 323:
#line 1180 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2081 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 324:
#line 1184 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2091 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 325:
#line 1188 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 2099 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 342:
#line 1215 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2107 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 343:
#line 1217 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr next_server(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("next-server", next_server);
    ctx.leave();
}
#line 2117 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 344:
#line 1223 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2125 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 345:
#line 1225 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr srv(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-hostname", srv);
    ctx.leave();
}
#line 2135 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 346:
#line 1231 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2143 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 347:
#line 1233 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr bootfile(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("boot-file-name", bootfile);
    ctx.leave();
}
#line 2153 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 348:
#line 1239 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2161 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 349:
#line 1241 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr addr(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", addr);
    ctx.leave();
}
#line 2171 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 350:
#line 1247 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2179 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 351:
#line 1249 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr d(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 2189 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 352:
#line 1255 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2197 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 353:
#line 1257 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 2207 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 354:
#line 1263 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2215 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 355:
#line 1265 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-id", hw);
    ctx.leave();
}
#line 2225 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 356:
#line 1271 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2233 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 357:
#line 1273 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("circuit-id", hw);
    ctx.leave();
}
#line 2243 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 358:
#line 1280 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2251 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 359:
#line 1282 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr host(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 2261 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 360:
#line 1288 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2272 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 361:
#line 1293 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2281 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 362:
#line 1301 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 2292 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 363:
#line 1306 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2301 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 364:
#line 1311 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2309 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 365:
#line 1313 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr ip(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", ip);
    ctx.leave();
}
#line 2319 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 366:
#line 1322 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 2330 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 367:
#line 1327 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2339 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 370:
#line 1336 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2349 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 371:
#line 1340 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2357 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 384:
#line 1363 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2365 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 385:
#line 1365 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr test(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 2375 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 386:
#line 1375 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 2384 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 387:
#line 1382 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 2395 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 388:
#line 1387 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2404 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 393:
#line 1400 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2412 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 394:
#line 1402 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr stype(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 2422 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 395:
#line 1408 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2430 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 396:
#line 1410 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 2440 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 397:
#line 1418 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 2451 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 398:
#line 1423 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2460 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 399:
#line 1428 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2470 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 400:
#line 1432 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 2478 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 419:
#line 1458 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 2487 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 420:
#line 1463 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2495 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 421:
#line 1465 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("qualifying-suffix", s);
    ctx.leave();
}
#line 2505 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 422:
#line 1471 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2513 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 423:
#line 1473 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 2523 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 424:
#line 1479 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 2532 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 425:
#line 1484 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2540 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 426:
#line 1486 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 2550 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 427:
#line 1492 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 2559 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 428:
#line 1497 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 2568 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 429:
#line 1502 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 2576 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 430:
#line 1504 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2585 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 431:
#line 1510 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 2591 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 432:
#line 1511 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 2597 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 433:
#line 1514 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NCR_FORMAT);
}
#line 2605 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 434:
#line 1516 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 2615 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 435:
#line 1522 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-include-fqdn", b);
}
#line 2624 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 436:
#line 1527 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("allow-client-update",  b);
}
#line 2633 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 437:
#line 1532 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-no-update", b);
}
#line 2642 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 438:
#line 1537 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-client-update", b);
}
#line 2651 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 439:
#line 1542 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 2659 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 440:
#line 1544 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("replace-client-name", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2668 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 441:
#line 1550 "dhcp4_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("when-present", ctx.loc2pos(yystack_[0].location))); 
      }
#line 2676 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 442:
#line 1553 "dhcp4_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location)));
      }
#line 2684 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 443:
#line 1556 "dhcp4_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("always", ctx.loc2pos(yystack_[0].location)));
      }
#line 2692 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 444:
#line 1559 "dhcp4_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("when-not-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 2700 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 445:
#line 1562 "dhcp4_parser.yy" // lalr1.cc:859
    {
      error(yystack_[0].location, "boolean values for the replace-client-name are "
                "no longer supported");
      }
#line 2709 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 446:
#line 1568 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2717 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 447:
#line 1570 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("generated-prefix", s);
    ctx.leave();
}
#line 2727 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 448:
#line 1578 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2735 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 449:
#line 1580 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("Dhcp6", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2744 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 450:
#line 1585 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2752 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 451:
#line 1587 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("DhcpDdns", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2761 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 452:
#line 1597 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Logging", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.LOGGING);
}
#line 2772 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 453:
#line 1602 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2781 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 457:
#line 1619 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 2792 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 458:
#line 1624 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2801 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 461:
#line 1636 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 2811 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 462:
#line 1640 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2819 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 470:
#line 1655 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr dl(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 2828 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 471:
#line 1659 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2836 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 472:
#line 1661 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 2846 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 473:
#line 1667 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 2857 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 474:
#line 1672 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2866 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 477:
#line 1681 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2876 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 478:
#line 1685 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2884 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 481:
#line 1693 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2892 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 482:
#line 1695 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 2902 "dhcp4_parser.cc" // lalr1.cc:859
    break;


#line 2906 "dhcp4_parser.cc" // lalr1.cc:859
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


  const short int Dhcp4Parser::yypact_ninf_ = -469;

  const signed char Dhcp4Parser::yytable_ninf_ = -1;

  const short int
  Dhcp4Parser::yypact_[] =
  {
     190,  -469,  -469,  -469,  -469,  -469,  -469,  -469,  -469,  -469,
    -469,  -469,    32,    19,    57,    72,    74,   103,   115,   130,
     151,   158,   159,   166,  -469,  -469,  -469,  -469,  -469,  -469,
    -469,  -469,  -469,  -469,  -469,  -469,  -469,  -469,  -469,  -469,
    -469,  -469,  -469,  -469,  -469,  -469,  -469,  -469,  -469,  -469,
    -469,  -469,  -469,  -469,  -469,  -469,    19,    53,    17,    80,
      44,    18,   -14,   116,    61,    82,   -23,   124,  -469,   185,
     200,   189,   197,   203,  -469,  -469,  -469,  -469,   229,  -469,
      26,  -469,  -469,  -469,  -469,  -469,  -469,   236,   237,  -469,
    -469,  -469,   239,   245,   246,   249,  -469,  -469,  -469,  -469,
    -469,  -469,  -469,   250,  -469,  -469,  -469,    30,  -469,  -469,
    -469,  -469,  -469,  -469,  -469,  -469,  -469,  -469,  -469,  -469,
    -469,  -469,  -469,  -469,  -469,  -469,  -469,  -469,  -469,  -469,
    -469,    62,  -469,  -469,  -469,  -469,  -469,  -469,  -469,  -469,
    -469,  -469,  -469,   251,   257,  -469,  -469,  -469,  -469,  -469,
    -469,  -469,  -469,  -469,    77,  -469,  -469,  -469,  -469,  -469,
    -469,  -469,  -469,  -469,  -469,  -469,  -469,  -469,  -469,  -469,
    -469,  -469,  -469,  -469,    84,  -469,  -469,  -469,  -469,  -469,
    -469,  -469,  -469,  -469,  -469,  -469,  -469,  -469,   254,   261,
    -469,  -469,  -469,  -469,  -469,  -469,  -469,  -469,  -469,  -469,
    -469,  -469,  -469,   262,  -469,  -469,  -469,   265,  -469,  -469,
     263,   269,  -469,  -469,  -469,  -469,  -469,  -469,  -469,  -469,
    -469,  -469,  -469,   270,  -469,  -469,  -469,  -469,   267,   273,
    -469,  -469,  -469,  -469,  -469,  -469,  -469,  -469,  -469,    87,
    -469,  -469,  -469,   274,  -469,  -469,   275,  -469,   278,   279,
    -469,  -469,   280,   285,   286,   287,  -469,  -469,  -469,    91,
    -469,  -469,  -469,  -469,  -469,  -469,  -469,  -469,  -469,  -469,
    -469,  -469,  -469,  -469,  -469,  -469,  -469,    19,    19,  -469,
     137,   291,   293,   295,   296,  -469,    17,  -469,   297,   174,
     188,   298,   299,   316,   192,   193,   194,   195,   321,   322,
     323,   324,   325,   326,   327,   204,   328,   330,    80,  -469,
     331,   332,    44,  -469,    23,   333,   334,   335,   336,   337,
     338,   339,   217,   216,   344,   345,   346,   347,    18,  -469,
     348,   -14,  -469,   349,   350,   351,   352,   353,   354,   355,
     356,   357,  -469,   116,   358,   359,   235,   361,   362,   363,
     238,  -469,    61,   364,   240,  -469,    82,   366,   368,    46,
    -469,   242,   370,   371,   247,   373,   252,   253,   374,   375,
     255,   256,   258,   259,   376,   379,   124,  -469,  -469,  -469,
     380,   378,   381,    19,    19,  -469,   384,  -469,  -469,   264,
     386,   387,  -469,  -469,  -469,  -469,   390,   391,   392,   393,
     394,   395,   396,  -469,   397,   398,  -469,   401,   125,  -469,
    -469,  -469,  -469,  -469,  -469,  -469,  -469,   399,   405,  -469,
    -469,  -469,   281,   282,   283,   407,   288,   289,   290,  -469,
    -469,   292,   301,   408,   412,  -469,   302,  -469,   303,   304,
     401,   305,   306,   307,   308,   310,   313,  -469,   314,   315,
    -469,   318,   319,   320,  -469,  -469,   329,  -469,  -469,   340,
      19,  -469,  -469,   341,   342,  -469,   343,  -469,  -469,    22,
     311,  -469,  -469,  -469,  -469,    63,   360,  -469,    19,    80,
     365,  -469,  -469,    44,  -469,    16,    16,   417,   418,   419,
     179,    24,   437,   120,    69,   124,  -469,  -469,  -469,  -469,
    -469,   410,  -469,    23,  -469,  -469,  -469,   442,  -469,  -469,
    -469,  -469,  -469,   443,   382,  -469,  -469,  -469,  -469,  -469,
    -469,  -469,  -469,  -469,  -469,  -469,  -469,  -469,  -469,  -469,
    -469,  -469,  -469,  -469,  -469,  -469,  -469,  -469,  -469,  -469,
    -469,  -469,  -469,  -469,  -469,  -469,  -469,  -469,   135,  -469,
     149,  -469,  -469,   169,  -469,  -469,  -469,  -469,   447,   449,
     451,   454,  -469,   171,  -469,  -469,  -469,  -469,  -469,  -469,
    -469,  -469,  -469,  -469,   172,  -469,   453,   457,  -469,  -469,
     455,   459,  -469,  -469,   458,   460,  -469,  -469,  -469,  -469,
    -469,    60,  -469,  -469,  -469,  -469,  -469,  -469,    66,  -469,
     461,   462,  -469,   468,   469,   470,   472,   473,   474,   184,
    -469,  -469,  -469,  -469,  -469,  -469,  -469,  -469,  -469,   187,
    -469,  -469,  -469,   201,   367,   369,  -469,  -469,   475,   463,
    -469,  -469,   476,   477,  -469,  -469,   471,  -469,   479,   365,
    -469,  -469,   480,   481,   482,   483,   271,   272,   372,   377,
      16,  -469,  -469,    18,  -469,   417,    61,  -469,   418,    82,
    -469,   419,   179,  -469,    24,  -469,   -23,  -469,   437,   383,
     385,   388,   389,   400,   402,   120,  -469,   485,   486,    69,
    -469,  -469,  -469,   487,   488,  -469,   -14,  -469,   442,   116,
    -469,   443,   490,  -469,   491,  -469,   233,   404,   406,   409,
    -469,  -469,  -469,  -469,  -469,   224,  -469,   484,  -469,   492,
    -469,  -469,  -469,   226,  -469,  -469,  -469,  -469,  -469,  -469,
    -469,  -469,   411,   413,  -469,  -469,   414,   227,  -469,   493,
    -469,   415,   495,  -469,  -469,  -469,  -469,  -469,  -469,  -469,
    -469,  -469,  -469,  -469,  -469,  -469,  -469,  -469,  -469,  -469,
    -469,  -469,    97,  -469,    48,   495,  -469,  -469,   494,  -469,
    -469,  -469,   228,  -469,  -469,  -469,  -469,  -469,   500,   416,
     501,    48,  -469,   502,  -469,   420,  -469,   503,  -469,  -469,
     101,  -469,   403,   503,  -469,  -469,   234,  -469,  -469,   504,
     403,  -469,   421,  -469,  -469
  };

  const unsigned short int
  Dhcp4Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     1,    38,    32,    28,    27,    24,
      25,    26,    31,     3,    29,    30,    51,     5,    62,     7,
      99,     9,   196,    11,   307,    13,   324,    15,   246,    17,
     281,    19,   161,    21,   399,    23,    40,    34,     0,     0,
       0,     0,     0,   326,   248,   283,     0,     0,    42,     0,
      41,     0,     0,    35,    60,   452,   448,   450,     0,    59,
       0,    53,    55,    57,    58,    56,    93,     0,     0,   342,
     107,   109,     0,     0,     0,     0,   188,   238,   273,   141,
     366,   153,   172,     0,   387,   397,    86,     0,    64,    66,
      67,    68,    69,    83,    84,    71,    72,    73,    74,    78,
      79,    70,    76,    77,    85,    75,    80,    81,    82,   101,
     103,     0,    95,    97,    98,   370,   222,   224,   226,   299,
     220,   228,   230,     0,     0,   234,   232,   316,   362,   219,
     200,   201,   202,   214,     0,   198,   205,   216,   217,   218,
     206,   207,   210,   212,   208,   209,   203,   204,   211,   215,
     213,   314,   313,   312,     0,   309,   311,   344,   346,   360,
     350,   352,   356,   354,   358,   348,   341,   337,     0,   327,
     328,   338,   339,   340,   334,   330,   335,   332,   333,   336,
     331,   263,   135,     0,   267,   265,   270,     0,   259,   260,
       0,   249,   250,   252,   262,   253,   254,   255,   269,   256,
     257,   258,   294,     0,   292,   293,   296,   297,     0,   284,
     285,   287,   288,   289,   290,   291,   168,   170,   165,     0,
     163,   166,   167,     0,   420,   422,     0,   425,     0,     0,
     429,   433,     0,     0,     0,     0,   439,   446,   418,     0,
     401,   403,   404,   405,   406,   407,   408,   409,   410,   411,
     412,   413,   414,   415,   416,   417,    39,     0,     0,    33,
       0,     0,     0,     0,     0,    50,     0,    52,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    63,
       0,     0,     0,   100,   372,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   197,
       0,     0,   308,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   325,     0,     0,     0,     0,     0,     0,     0,
       0,   247,     0,     0,     0,   282,     0,     0,     0,     0,
     162,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   400,    43,    36,
       0,     0,     0,     0,     0,    54,     0,    91,    92,     0,
       0,     0,    87,    88,    89,    90,     0,     0,     0,     0,
       0,     0,     0,   386,     0,     0,    65,     0,     0,    96,
     384,   382,   383,   378,   379,   380,   381,     0,   373,   374,
     376,   377,     0,     0,     0,     0,     0,     0,     0,   236,
     237,     0,     0,     0,     0,   199,     0,   310,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   329,     0,     0,
     261,     0,     0,     0,   272,   251,     0,   298,   286,     0,
       0,   164,   419,     0,     0,   424,     0,   427,   428,     0,
       0,   435,   436,   437,   438,     0,     0,   402,     0,     0,
       0,   449,   451,     0,   343,     0,     0,   190,   240,   275,
       0,     0,   155,     0,     0,     0,    44,   102,   105,   106,
     104,     0,   371,     0,   223,   225,   227,   301,   221,   229,
     231,   235,   233,   318,     0,   315,   345,   347,   361,   351,
     353,   357,   355,   359,   349,   264,   136,   268,   266,   271,
     295,   169,   171,   421,   423,   426,   431,   432,   430,   434,
     441,   442,   443,   444,   445,   440,   447,    37,     0,   457,
       0,   454,   456,     0,   123,   129,   131,   133,     0,     0,
       0,     0,   122,     0,   111,   113,   114,   115,   116,   117,
     118,   119,   120,   121,     0,   194,     0,   191,   192,   244,
       0,   241,   242,   279,     0,   276,   277,   149,   150,   151,
     152,     0,   143,   145,   146,   147,   148,   368,     0,   159,
       0,   156,   157,     0,     0,     0,     0,     0,     0,     0,
     174,   176,   177,   178,   179,   180,   181,   393,   395,     0,
     389,   391,   392,     0,    46,     0,   375,   305,     0,   302,
     303,   322,     0,   319,   320,   364,     0,    61,     0,     0,
     453,    94,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   108,   110,     0,   189,     0,   248,   239,     0,   283,
     274,     0,     0,   142,     0,   367,     0,   154,     0,     0,
       0,     0,     0,     0,     0,     0,   173,     0,     0,     0,
     388,   398,    48,     0,    47,   385,     0,   300,     0,   326,
     317,     0,     0,   363,     0,   455,     0,     0,     0,     0,
     137,   138,   139,   140,   112,     0,   193,     0,   243,     0,
     278,   144,   369,     0,   158,   182,   183,   184,   185,   186,
     187,   175,     0,     0,   390,    45,     0,     0,   304,     0,
     321,     0,     0,   125,   126,   127,   128,   124,   130,   132,
     134,   195,   245,   280,   160,   394,   396,    49,   306,   323,
     365,   461,     0,   459,     0,     0,   458,   473,     0,   471,
     469,   465,     0,   463,   467,   468,   466,   460,     0,     0,
       0,     0,   462,     0,   470,     0,   464,     0,   472,   477,
       0,   475,     0,     0,   474,   481,     0,   479,   476,     0,
       0,   478,     0,   480,   482
  };

  const short int
  Dhcp4Parser::yypgoto_[] =
  {
    -469,  -469,  -469,  -469,  -469,  -469,  -469,  -469,  -469,  -469,
    -469,  -469,  -469,   -39,  -469,  -469,  -469,  -469,  -469,  -469,
    -469,  -469,  -469,    59,  -469,  -469,  -469,   -58,  -469,  -469,
    -469,   223,  -469,  -469,  -469,  -469,    34,   208,   -60,   -42,
     -41,  -469,  -469,   -40,  -469,  -469,    28,   207,  -469,  -469,
    -469,  -469,  -469,  -469,  -469,  -469,  -469,  -469,  -469,    35,
    -130,  -469,  -469,  -469,  -469,  -469,  -469,  -469,  -469,  -469,
     -63,  -469,  -469,  -469,  -469,  -469,  -469,  -469,  -469,  -140,
    -469,  -469,  -469,  -469,  -469,  -469,  -469,  -469,  -145,  -469,
    -469,  -469,  -142,   167,  -469,  -469,  -469,  -469,  -469,  -469,
    -469,  -150,  -469,  -469,  -469,  -469,  -469,  -469,  -469,  -469,
    -469,  -469,  -128,  -469,  -469,  -469,  -125,   202,  -469,  -469,
    -469,  -469,  -469,  -469,  -469,  -469,  -469,  -469,  -469,  -469,
    -468,  -469,  -469,  -469,  -469,  -469,  -469,  -469,  -469,  -469,
    -123,  -469,  -469,  -469,  -120,  -469,   181,  -469,   -52,  -469,
    -469,  -469,  -469,  -469,   -50,  -469,  -469,  -469,  -469,  -469,
     -51,  -469,  -469,  -469,  -121,  -469,  -469,  -469,  -115,  -469,
     182,  -469,  -469,  -469,  -469,  -469,  -469,  -469,  -469,  -469,
    -469,  -141,  -469,  -469,  -469,  -136,   215,  -469,  -469,  -469,
    -469,  -469,  -469,  -139,  -469,  -469,  -469,  -138,  -469,   210,
     -47,  -469,  -296,  -469,  -292,  -469,  -469,  -469,  -469,  -469,
    -469,  -469,  -469,  -469,  -469,  -469,  -469,  -469,  -469,  -469,
    -469,  -469,  -469,  -469,  -469,  -469,  -469,  -469,  -469,  -469,
      51,  -469,  -469,  -469,  -469,  -469,  -469,  -469,  -124,  -469,
    -469,  -469,  -469,  -469,  -469,  -469,  -469,    64,   180,  -469,
    -469,  -469,  -469,  -469,  -469,  -469,  -469,  -469,  -469,  -469,
    -469,  -469,  -469,  -469,  -469,  -469,  -469,  -469,  -469,  -469,
    -469,  -469,  -469,  -469,  -469,  -469,  -469,  -469,  -469,  -469,
     -82,  -469,  -469,  -469,  -197,  -469,  -469,  -211,  -469,  -469,
    -469,  -469,  -469,  -469,  -222,  -469,  -469,  -228,  -469
  };

  const short int
  Dhcp4Parser::yydefgoto_[] =
  {
      -1,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    32,    33,    34,    57,    72,    73,    35,
      56,    69,    70,   497,   624,   683,   684,   106,    37,    58,
      80,    81,    82,   281,    39,    59,   107,   108,   109,   110,
     111,   112,   113,   114,   115,   288,   131,   132,    41,    60,
     133,   310,   134,   311,   500,   116,   292,   117,   293,   563,
     564,   565,   642,   737,   566,   643,   567,   644,   568,   645,
     209,   345,   570,   571,   572,   573,   118,   301,   591,   592,
     593,   594,   595,   596,   119,   303,   600,   601,   602,   666,
      53,    66,   239,   240,   241,   357,   242,   358,   120,   304,
     609,   610,   611,   612,   613,   614,   615,   616,   121,   298,
     576,   577,   578,   653,    43,    61,   154,   155,   156,   319,
     157,   315,   158,   316,   159,   317,   160,   320,   161,   321,
     162,   325,   163,   324,   164,   165,   122,   299,   580,   581,
     582,   656,    49,    64,   210,   211,   212,   213,   214,   215,
     216,   344,   217,   348,   218,   347,   219,   220,   349,   221,
     123,   300,   584,   585,   586,   659,    51,    65,   228,   229,
     230,   231,   232,   353,   233,   234,   235,   167,   318,   628,
     629,   630,   686,    45,    62,   174,   175,   176,   330,   168,
     326,   632,   633,   634,   689,    47,    63,   188,   189,   190,
     124,   291,   192,   333,   193,   334,   194,   341,   195,   336,
     196,   337,   197,   339,   198,   338,   199,   340,   200,   335,
     170,   327,   636,   692,   125,   302,   598,   314,   417,   418,
     419,   420,   421,   501,   126,   127,   306,   619,   620,   621,
     677,   622,   678,   128,   307,    55,    67,   259,   260,   261,
     262,   362,   263,   363,   264,   265,   365,   266,   267,   268,
     368,   538,   269,   369,   270,   271,   272,   273,   274,   374,
     545,   275,   375,    83,   283,    84,   284,    85,   282,   550,
     551,   552,   638,   752,   753,   754,   762,   763,   764,   765,
     770,   766,   768,   780,   781,   782,   786,   787,   789
  };

  const unsigned short int
  Dhcp4Parser::yytable_[] =
  {
      79,   150,   225,   149,   172,   186,   208,   224,   238,   258,
     166,   173,   187,   226,   169,   227,   191,    68,   415,   151,
     152,   153,   416,   597,    25,   135,    26,    74,    27,   286,
      98,   135,    24,   308,   287,    88,    89,   536,   309,   554,
     171,    89,   177,   178,   555,   556,   557,   558,   559,   560,
     561,   236,   237,    92,    93,    94,   129,   130,   136,   137,
     138,   202,    98,   662,    36,   312,   663,    98,   202,   664,
     313,   139,   665,   140,   141,   142,   143,   144,   145,    38,
     328,    40,   146,   147,   201,   329,   410,   331,   146,   148,
     359,    86,   332,   202,   376,   360,    87,    88,    89,   377,
     755,    90,    91,   756,   783,    78,   202,   784,   203,   204,
      42,   205,   206,   207,    78,    92,    93,    94,    95,    96,
     236,   237,    44,    97,    98,   537,    75,   202,   222,   203,
     204,   223,    76,    77,    89,   177,   178,    46,   308,   498,
     499,    99,   100,   637,    78,    78,    78,    28,    29,    30,
      31,    78,   639,   101,   617,   618,   102,   640,    48,   757,
      98,   758,   759,   103,   104,    50,    52,   105,   540,   541,
     542,   543,   312,    54,   650,   650,    78,   641,   179,   651,
     652,    71,   180,   181,   182,   183,   184,   675,   185,    78,
     679,   276,   676,   278,   544,   680,   712,   603,   604,   605,
     606,   607,   608,   277,   376,   279,   280,   415,    78,   681,
      78,   416,   243,   244,   245,   246,   247,   248,   249,   250,
     251,   252,   253,   254,   255,   256,   257,   328,    79,   359,
     331,   771,   741,   285,   744,   748,   772,   790,   378,   379,
     289,   290,   791,   294,    78,   587,   588,   589,   590,   295,
     296,   412,    78,   297,   305,   322,   411,   733,   734,   735,
     736,   323,   342,   413,   343,   380,   346,   414,   150,   350,
     149,   351,   352,   172,   354,   355,   356,   166,   361,   364,
     173,   169,   366,   367,   370,   186,   151,   152,   153,   371,
     372,   373,   187,   225,   208,   381,   191,   382,   224,   383,
     384,   386,   389,   390,   226,   387,   227,     1,     2,     3,
       4,     5,     6,     7,     8,     9,    10,    11,   258,   388,
     391,   392,   393,   394,   395,   396,   397,   398,   399,   400,
     401,   402,   404,   403,   405,   407,   408,   422,   423,   424,
     425,   426,   427,   428,   481,   482,   429,   430,   431,   432,
     433,   434,   436,   438,   439,   440,   441,   442,   443,   444,
     445,   446,   448,   449,   450,   451,   452,   453,   456,   454,
     459,   457,   460,   462,   463,   464,   465,   466,   469,   470,
     475,   467,   468,   476,   478,   479,   471,   472,   480,   473,
     474,   483,   484,   485,   486,   487,   488,   489,   490,   491,
     492,   701,   700,   493,   494,   495,   496,   502,   503,   504,
     505,   506,   507,   513,   625,   539,   508,   509,   510,   514,
     511,   532,   569,   569,   575,   579,   583,   562,   562,   512,
     515,   516,   517,   519,   520,   521,   522,   258,   523,   547,
     412,   524,   525,   526,   599,   411,   527,   528,   529,   627,
     631,   646,   413,   647,   635,   648,   414,   530,   649,   654,
     655,   657,   658,   661,   660,   668,   688,   667,   531,   533,
     534,   535,   669,   670,   671,   549,   672,   673,   674,   693,
     691,   687,   690,   694,   696,   697,   698,   699,   546,   722,
     723,   726,   742,   725,   731,   682,   732,   685,   769,   518,
     743,   749,   751,   702,   773,   775,   703,   777,   792,   385,
     779,   553,   715,   548,   716,   785,   406,   717,   718,   409,
     704,   574,   711,   714,   713,   721,   461,   706,   705,   719,
     435,   720,   738,   455,   739,   708,   707,   740,   458,   745,
     710,   746,   747,   750,   709,   774,   437,   728,   778,   794,
     727,   729,   730,   447,   626,   724,   477,   695,   767,   623,
     776,   788,   793,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   569,     0,     0,
       0,     0,   562,   150,     0,   149,   225,     0,   208,     0,
       0,   224,   166,     0,     0,     0,   169,   226,   238,   227,
       0,   151,   152,   153,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   172,     0,
       0,   186,     0,     0,     0,   173,     0,     0,   187,     0,
       0,     0,   191,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   761,     0,     0,     0,     0,   760,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   761,     0,
       0,     0,     0,   760
  };

  const short int
  Dhcp4Parser::yycheck_[] =
  {
      58,    61,    65,    61,    62,    63,    64,    65,    66,    67,
      61,    62,    63,    65,    61,    65,    63,    56,   314,    61,
      61,    61,   314,   491,     5,     7,     7,    10,     9,     3,
      44,     7,     0,     3,     8,    17,    18,    15,     8,    23,
      54,    18,    19,    20,    28,    29,    30,    31,    32,    33,
      34,    74,    75,    35,    36,    37,    12,    13,    40,    41,
      42,    45,    44,     3,     7,     3,     6,    44,    45,     3,
       8,    53,     6,    55,    56,    57,    58,    59,    60,     7,
       3,     7,    64,    65,    23,     8,    63,     3,    64,    71,
       3,    11,     8,    45,     3,     8,    16,    17,    18,     8,
       3,    21,    22,     6,     3,   128,    45,     6,    47,    48,
       7,    50,    51,    52,   128,    35,    36,    37,    38,    39,
      74,    75,     7,    43,    44,   103,   109,    45,    46,    47,
      48,    49,   115,   116,    18,    19,    20,     7,     3,    14,
      15,    61,    62,     8,   128,   128,   128,   128,   129,   130,
     131,   128,     3,    73,    85,    86,    76,     8,     7,   111,
      44,   113,   114,    83,    84,     7,     7,    87,   105,   106,
     107,   108,     3,     7,     3,     3,   128,     8,    62,     8,
       8,   128,    66,    67,    68,    69,    70,     3,    72,   128,
       3,     6,     8,     4,   131,     8,   664,    77,    78,    79,
      80,    81,    82,     3,     3,     8,     3,   503,   128,     8,
     128,   503,    88,    89,    90,    91,    92,    93,    94,    95,
      96,    97,    98,    99,   100,   101,   102,     3,   286,     3,
       3,     3,     8,     4,     8,     8,     8,     3,   277,   278,
       4,     4,     8,     4,   128,    66,    67,    68,    69,     4,
       4,   314,   128,     4,     4,     4,   314,    24,    25,    26,
      27,     4,     8,   314,     3,   128,     4,   314,   328,     4,
     328,     8,     3,   331,     4,     8,     3,   328,     4,     4,
     331,   328,     4,     4,     4,   343,   328,   328,   328,     4,
       4,     4,   343,   356,   352,     4,   343,     4,   356,     4,
       4,     4,     4,     4,   356,   131,   356,   117,   118,   119,
     120,   121,   122,   123,   124,   125,   126,   127,   376,   131,
       4,   129,   129,   129,   129,     4,     4,     4,     4,     4,
       4,     4,     4,   129,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,   383,   384,   129,   131,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,   129,     4,     4,     4,     4,   131,
       4,   131,     4,   131,     4,     4,   129,     4,     4,     4,
       4,   129,   129,     4,     4,     7,   131,   131,     7,   131,
     131,     7,   128,     7,     7,     5,     5,     5,     5,     5,
       5,   129,   131,     7,     7,     7,     5,     8,     3,   128,
     128,   128,     5,     5,     4,   104,   128,   128,   128,     7,
     128,   460,   485,   486,     7,     7,     7,   485,   486,   128,
     128,   128,   128,   128,   128,   128,   128,   495,   128,   478,
     503,   128,   128,   128,     7,   503,   128,   128,   128,     7,
       7,     4,   503,     4,    72,     4,   503,   128,     4,     6,
       3,     6,     3,     3,     6,     3,     3,     6,   128,   128,
     128,   128,     4,     4,     4,   110,     4,     4,     4,     8,
       3,     6,     6,     4,     4,     4,     4,     4,   128,     4,
       4,     3,     8,     6,     4,   128,     5,   128,     4,   440,
       8,     8,     7,   131,     4,     4,   129,     5,     4,   286,
       7,   483,   129,   479,   129,   112,   308,   129,   129,   312,
     650,   486,   662,   668,   666,   675,   359,   655,   653,   129,
     328,   129,   128,   352,   128,   658,   656,   128,   356,   128,
     661,   128,   128,   128,   659,   129,   331,   688,   128,   128,
     686,   689,   691,   343,   503,   679,   376,   639,   755,   495,
     771,   783,   790,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   650,    -1,    -1,
      -1,    -1,   650,   653,    -1,   653,   659,    -1,   656,    -1,
      -1,   659,   653,    -1,    -1,    -1,   653,   659,   666,   659,
      -1,   653,   653,   653,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   686,    -1,
      -1,   689,    -1,    -1,    -1,   686,    -1,    -1,   689,    -1,
      -1,    -1,   689,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   754,    -1,    -1,    -1,    -1,   754,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   771,    -1,
      -1,    -1,    -1,   771
  };

  const unsigned short int
  Dhcp4Parser::yystos_[] =
  {
       0,   117,   118,   119,   120,   121,   122,   123,   124,   125,
     126,   127,   133,   134,   135,   136,   137,   138,   139,   140,
     141,   142,   143,   144,     0,     5,     7,     9,   128,   129,
     130,   131,   145,   146,   147,   151,     7,   160,     7,   166,
       7,   180,     7,   246,     7,   315,     7,   327,     7,   274,
       7,   298,     7,   222,     7,   377,   152,   148,   161,   167,
     181,   247,   316,   328,   275,   299,   223,   378,   145,   153,
     154,   128,   149,   150,    10,   109,   115,   116,   128,   159,
     162,   163,   164,   405,   407,   409,    11,    16,    17,    18,
      21,    22,    35,    36,    37,    38,    39,    43,    44,    61,
      62,    73,    76,    83,    84,    87,   159,   168,   169,   170,
     171,   172,   173,   174,   175,   176,   187,   189,   208,   216,
     230,   240,   268,   292,   332,   356,   366,   367,   375,    12,
      13,   178,   179,   182,   184,     7,    40,    41,    42,    53,
      55,    56,    57,    58,    59,    60,    64,    65,    71,   159,
     170,   171,   172,   175,   248,   249,   250,   252,   254,   256,
     258,   260,   262,   264,   266,   267,   292,   309,   321,   332,
     352,    54,   159,   292,   317,   318,   319,    19,    20,    62,
      66,    67,    68,    69,    70,    72,   159,   292,   329,   330,
     331,   332,   334,   336,   338,   340,   342,   344,   346,   348,
     350,    23,    45,    47,    48,    50,    51,    52,   159,   202,
     276,   277,   278,   279,   280,   281,   282,   284,   286,   288,
     289,   291,    46,    49,   159,   202,   280,   286,   300,   301,
     302,   303,   304,   306,   307,   308,    74,    75,   159,   224,
     225,   226,   228,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   159,   379,
     380,   381,   382,   384,   386,   387,   389,   390,   391,   394,
     396,   397,   398,   399,   400,   403,     6,     3,     4,     8,
       3,   165,   410,   406,   408,     4,     3,     8,   177,     4,
       4,   333,   188,   190,     4,     4,     4,     4,   241,   269,
     293,   209,   357,   217,   231,     4,   368,   376,     3,     8,
     183,   185,     3,     8,   359,   253,   255,   257,   310,   251,
     259,   261,     4,     4,   265,   263,   322,   353,     3,     8,
     320,     3,     8,   335,   337,   351,   341,   343,   347,   345,
     349,   339,     8,     3,   283,   203,     4,   287,   285,   290,
       4,     8,     3,   305,     4,     8,     3,   227,   229,     3,
       8,     4,   383,   385,     4,   388,     4,     4,   392,   395,
       4,     4,     4,     4,   401,   404,     3,     8,   145,   145,
     128,     4,     4,     4,     4,   163,     4,   131,   131,     4,
       4,     4,   129,   129,   129,   129,     4,     4,     4,     4,
       4,     4,     4,   129,     4,     4,   169,     4,     4,   179,
      63,   159,   202,   292,   332,   334,   336,   360,   361,   362,
     363,   364,     4,     4,     4,     4,     4,     4,     4,   129,
     131,     4,     4,     4,     4,   249,     4,   318,     4,     4,
       4,     4,     4,     4,     4,     4,     4,   331,     4,     4,
     129,     4,     4,     4,   131,   278,     4,   131,   302,     4,
       4,   225,   131,     4,     4,   129,     4,   129,   129,     4,
       4,   131,   131,   131,   131,     4,     4,   380,     4,     7,
       7,   145,   145,     7,   128,     7,     7,     5,     5,     5,
       5,     5,     5,     7,     7,     7,     5,   155,    14,    15,
     186,   365,     8,     3,   128,   128,   128,     5,   128,   128,
     128,   128,   128,     5,     7,   128,   128,   128,   155,   128,
     128,   128,   128,   128,   128,   128,   128,   128,   128,   128,
     128,   128,   145,   128,   128,   128,    15,   103,   393,   104,
     105,   106,   107,   108,   131,   402,   128,   145,   168,   110,
     411,   412,   413,   178,    23,    28,    29,    30,    31,    32,
      33,    34,   159,   191,   192,   193,   196,   198,   200,   202,
     204,   205,   206,   207,   191,     7,   242,   243,   244,     7,
     270,   271,   272,     7,   294,   295,   296,    66,    67,    68,
      69,   210,   211,   212,   213,   214,   215,   262,   358,     7,
     218,   219,   220,    77,    78,    79,    80,    81,    82,   232,
     233,   234,   235,   236,   237,   238,   239,    85,    86,   369,
     370,   371,   373,   379,   156,     4,   362,     7,   311,   312,
     313,     7,   323,   324,   325,    72,   354,     8,   414,     3,
       8,     8,   194,   197,   199,   201,     4,     4,     4,     4,
       3,     8,     8,   245,     6,     3,   273,     6,     3,   297,
       6,     3,     3,     6,     3,     6,   221,     6,     3,     4,
       4,     4,     4,     4,     4,     3,     8,   372,   374,     3,
       8,     8,   128,   157,   158,   128,   314,     6,     3,   326,
       6,     3,   355,     8,     4,   412,     4,     4,     4,     4,
     131,   129,   131,   129,   192,   248,   244,   276,   272,   300,
     296,   211,   262,   224,   220,   129,   129,   129,   129,   129,
     129,   233,     4,     4,   370,     6,     3,   317,   313,   329,
     325,     4,     5,    24,    25,    26,    27,   195,   128,   128,
     128,     8,     8,     8,     8,   128,   128,   128,     8,     8,
     128,     7,   415,   416,   417,     3,     6,   111,   113,   114,
     159,   202,   418,   419,   420,   421,   423,   416,   424,     4,
     422,     3,     8,     4,   129,     4,   419,     5,   128,     7,
     425,   426,   427,     3,     6,   112,   428,   429,   426,   430,
       3,     8,     4,   429,   128
  };

  const unsigned short int
  Dhcp4Parser::yyr1_[] =
  {
       0,   132,   134,   133,   135,   133,   136,   133,   137,   133,
     138,   133,   139,   133,   140,   133,   141,   133,   142,   133,
     143,   133,   144,   133,   145,   145,   145,   145,   145,   145,
     145,   146,   148,   147,   149,   149,   150,   150,   152,   151,
     153,   153,   154,   154,   156,   155,   157,   157,   158,   158,
     159,   161,   160,   162,   162,   163,   163,   163,   163,   163,
     165,   164,   167,   166,   168,   168,   169,   169,   169,   169,
     169,   169,   169,   169,   169,   169,   169,   169,   169,   169,
     169,   169,   169,   169,   169,   169,   169,   170,   171,   172,
     173,   174,   175,   177,   176,   178,   178,   179,   179,   181,
     180,   183,   182,   185,   184,   186,   186,   188,   187,   190,
     189,   191,   191,   192,   192,   192,   192,   192,   192,   192,
     192,   192,   192,   194,   193,   195,   195,   195,   195,   197,
     196,   199,   198,   201,   200,   203,   202,   204,   205,   206,
     207,   209,   208,   210,   210,   211,   211,   211,   211,   212,
     213,   214,   215,   217,   216,   218,   218,   219,   219,   221,
     220,   223,   222,   224,   224,   224,   225,   225,   227,   226,
     229,   228,   231,   230,   232,   232,   233,   233,   233,   233,
     233,   233,   234,   235,   236,   237,   238,   239,   241,   240,
     242,   242,   243,   243,   245,   244,   247,   246,   248,   248,
     249,   249,   249,   249,   249,   249,   249,   249,   249,   249,
     249,   249,   249,   249,   249,   249,   249,   249,   249,   249,
     251,   250,   253,   252,   255,   254,   257,   256,   259,   258,
     261,   260,   263,   262,   265,   264,   266,   267,   269,   268,
     270,   270,   271,   271,   273,   272,   275,   274,   276,   276,
     277,   277,   278,   278,   278,   278,   278,   278,   278,   278,
     279,   280,   281,   283,   282,   285,   284,   287,   286,   288,
     290,   289,   291,   293,   292,   294,   294,   295,   295,   297,
     296,   299,   298,   300,   300,   301,   301,   302,   302,   302,
     302,   302,   302,   303,   305,   304,   306,   307,   308,   310,
     309,   311,   311,   312,   312,   314,   313,   316,   315,   317,
     317,   318,   318,   318,   320,   319,   322,   321,   323,   323,
     324,   324,   326,   325,   328,   327,   329,   329,   330,   330,
     331,   331,   331,   331,   331,   331,   331,   331,   331,   331,
     331,   331,   333,   332,   335,   334,   337,   336,   339,   338,
     341,   340,   343,   342,   345,   344,   347,   346,   349,   348,
     351,   350,   353,   352,   355,   354,   357,   356,   358,   358,
     359,   262,   360,   360,   361,   361,   362,   362,   362,   362,
     362,   362,   362,   363,   365,   364,   366,   368,   367,   369,
     369,   370,   370,   372,   371,   374,   373,   376,   375,   378,
     377,   379,   379,   380,   380,   380,   380,   380,   380,   380,
     380,   380,   380,   380,   380,   380,   380,   380,   380,   381,
     383,   382,   385,   384,   386,   388,   387,   389,   390,   392,
     391,   393,   393,   395,   394,   396,   397,   398,   399,   401,
     400,   402,   402,   402,   402,   402,   404,   403,   406,   405,
     408,   407,   410,   409,   411,   411,   412,   414,   413,   415,
     415,   417,   416,   418,   418,   419,   419,   419,   419,   419,
     420,   422,   421,   424,   423,   425,   425,   427,   426,   428,
     428,   430,   429
  };

  const unsigned char
  Dhcp4Parser::yyr2_[] =
  {
       0,     2,     0,     3,     0,     3,     0,     3,     0,     3,
       0,     3,     0,     3,     0,     3,     0,     3,     0,     3,
       0,     3,     0,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     0,     4,     0,     1,     3,     5,     0,     4,
       0,     1,     1,     3,     0,     4,     0,     1,     1,     3,
       2,     0,     4,     1,     3,     1,     1,     1,     1,     1,
       0,     6,     0,     4,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     3,     3,     3,
       3,     3,     3,     0,     6,     1,     3,     1,     1,     0,
       4,     0,     4,     0,     4,     1,     1,     0,     6,     0,
       6,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     0,     4,     1,     1,     1,     1,     0,
       4,     0,     4,     0,     4,     0,     4,     3,     3,     3,
       3,     0,     6,     1,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     0,     6,     0,     1,     1,     3,     0,
       4,     0,     4,     1,     3,     1,     1,     1,     0,     4,
       0,     4,     0,     6,     1,     3,     1,     1,     1,     1,
       1,     1,     3,     3,     3,     3,     3,     3,     0,     6,
       0,     1,     1,     3,     0,     4,     0,     4,     1,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       0,     4,     0,     4,     0,     4,     0,     4,     0,     4,
       0,     4,     0,     4,     0,     4,     3,     3,     0,     6,
       0,     1,     1,     3,     0,     4,     0,     4,     0,     1,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     3,     1,     0,     4,     0,     4,     0,     4,     1,
       0,     4,     3,     0,     6,     0,     1,     1,     3,     0,
       4,     0,     4,     0,     1,     1,     3,     1,     1,     1,
       1,     1,     1,     1,     0,     4,     1,     1,     3,     0,
       6,     0,     1,     1,     3,     0,     4,     0,     4,     1,
       3,     1,     1,     1,     0,     4,     0,     6,     0,     1,
       1,     3,     0,     4,     0,     4,     0,     1,     1,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     0,     4,     0,     4,     0,     4,     0,     4,
       0,     4,     0,     4,     0,     4,     0,     4,     0,     4,
       0,     4,     0,     6,     0,     4,     0,     6,     1,     3,
       0,     4,     0,     1,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     0,     4,     3,     0,     6,     1,
       3,     1,     1,     0,     4,     0,     4,     0,     6,     0,
       4,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     3,
       0,     4,     0,     4,     3,     0,     4,     3,     3,     0,
       4,     1,     1,     0,     4,     3,     3,     3,     3,     0,
       4,     1,     1,     1,     1,     1,     0,     4,     0,     4,
       0,     4,     0,     6,     1,     3,     1,     0,     6,     1,
       3,     0,     4,     1,     3,     1,     1,     1,     1,     1,
       3,     0,     4,     0,     6,     1,     3,     0,     4,     1,
       3,     0,     4
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
  "\"array\"", "\"pools\"", "\"pool\"", "\"subnet\"", "\"interface\"",
  "\"interface-id\"", "\"id\"", "\"rapid-commit\"", "\"reservation-mode\"",
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
  "$@12", "map_content", "not_empty_map", "list_generic", "$@13",
  "list_content", "not_empty_list", "list_strings", "$@14",
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
  "reservation_mode", "$@46", "id", "rapid_commit", "option_def_list",
  "$@47", "option_def_list_content", "not_empty_option_def_list",
  "option_def_entry", "$@48", "sub_option_def", "$@49",
  "option_def_params", "not_empty_option_def_params", "option_def_param",
  "option_def_name", "code", "option_def_code", "option_def_type", "$@50",
  "option_def_record_types", "$@51", "space", "$@52", "option_def_space",
  "option_def_encapsulate", "$@53", "option_def_array", "option_data_list",
  "$@54", "option_data_list_content", "not_empty_option_data_list",
  "option_data_entry", "$@55", "sub_option_data", "$@56",
  "option_data_params", "not_empty_option_data_params",
  "option_data_param", "option_data_name", "option_data_data", "$@57",
  "option_data_code", "option_data_space", "option_data_csv_format",
  "pools_list", "$@58", "pools_list_content", "not_empty_pools_list",
  "pool_list_entry", "$@59", "sub_pool4", "$@60", "pool_params",
  "pool_param", "pool_entry", "$@61", "reservations", "$@62",
  "reservations_list", "not_empty_reservations_list", "reservation",
  "$@63", "sub_reservation", "$@64", "reservation_params",
  "not_empty_reservation_params", "reservation_param", "next_server",
  "$@65", "server_hostname", "$@66", "boot_file_name", "$@67",
  "ip_address", "$@68", "duid", "$@69", "hw_address", "$@70",
  "client_id_value", "$@71", "circuit_id_value", "$@72", "hostname",
  "$@73", "reservation_client_classes", "$@74", "relay", "$@75",
  "relay_map", "$@76", "client_classes", "$@77", "client_classes_list",
  "$@78", "client_class_params", "not_empty_client_class_params",
  "client_class_param", "client_class_name", "client_class_test", "$@79",
  "dhcp4o6_port", "control_socket", "$@80", "control_socket_params",
  "control_socket_param", "control_socket_type", "$@81",
  "control_socket_name", "$@82", "dhcp_ddns", "$@83", "sub_dhcp_ddns",
  "$@84", "dhcp_ddns_params", "dhcp_ddns_param", "enable_updates",
  "qualifying_suffix", "$@85", "server_ip", "$@86", "server_port",
  "sender_ip", "$@87", "sender_port", "max_queue_size", "ncr_protocol",
  "$@88", "ncr_protocol_value", "ncr_format", "$@89",
  "always_include_fqdn", "allow_client_update", "override_no_update",
  "override_client_update", "replace_client_name", "$@90",
  "replace_client_name_value", "generated_prefix", "$@91",
  "dhcp6_json_object", "$@92", "dhcpddns_json_object", "$@93",
  "logging_object", "$@94", "logging_params", "logging_param", "loggers",
  "$@95", "loggers_entries", "logger_entry", "$@96", "logger_params",
  "logger_param", "debuglevel", "severity", "$@97", "output_options_list",
  "$@98", "output_options_list_content", "output_entry", "$@99",
  "output_params", "output_param", "$@100", YY_NULLPTR
  };

#if PARSER4_DEBUG
  const unsigned short int
  Dhcp4Parser::yyrline_[] =
  {
       0,   211,   211,   211,   212,   212,   213,   213,   214,   214,
     215,   215,   216,   216,   217,   217,   218,   218,   219,   219,
     220,   220,   221,   221,   229,   230,   231,   232,   233,   234,
     235,   238,   243,   243,   255,   256,   259,   263,   270,   270,
     277,   278,   281,   285,   292,   292,   299,   300,   303,   307,
     318,   328,   328,   340,   341,   345,   346,   347,   348,   349,
     352,   352,   369,   369,   377,   378,   383,   384,   385,   386,
     387,   388,   389,   390,   391,   392,   393,   394,   395,   396,
     397,   398,   399,   400,   401,   402,   403,   406,   411,   416,
     421,   426,   431,   437,   437,   447,   448,   451,   452,   455,
     455,   463,   463,   473,   473,   480,   481,   484,   484,   494,
     494,   504,   505,   508,   509,   510,   511,   512,   513,   514,
     515,   516,   517,   520,   520,   527,   528,   529,   530,   533,
     533,   541,   541,   549,   549,   557,   557,   565,   570,   575,
     580,   585,   585,   595,   596,   599,   600,   601,   602,   605,
     610,   615,   620,   625,   625,   635,   636,   639,   640,   643,
     643,   651,   651,   659,   660,   661,   664,   665,   668,   668,
     676,   676,   684,   684,   694,   695,   698,   699,   700,   701,
     702,   703,   706,   711,   716,   721,   726,   731,   739,   739,
     752,   753,   756,   757,   764,   764,   787,   787,   796,   797,
     801,   802,   803,   804,   805,   806,   807,   808,   809,   810,
     811,   812,   813,   814,   815,   816,   817,   818,   819,   820,
     823,   823,   831,   831,   839,   839,   847,   847,   855,   855,
     863,   863,   871,   871,   879,   879,   887,   892,   901,   901,
     913,   914,   917,   918,   923,   923,   934,   934,   944,   945,
     948,   949,   952,   953,   954,   955,   956,   957,   958,   959,
     962,   964,   969,   971,   971,   979,   979,   987,   987,   995,
     997,   997,  1005,  1014,  1014,  1026,  1027,  1032,  1033,  1038,
    1038,  1049,  1049,  1060,  1061,  1066,  1067,  1072,  1073,  1074,
    1075,  1076,  1077,  1080,  1082,  1082,  1090,  1092,  1094,  1102,
    1102,  1114,  1115,  1118,  1119,  1122,  1122,  1130,  1130,  1138,
    1139,  1142,  1143,  1144,  1147,  1147,  1158,  1158,  1168,  1169,
    1172,  1173,  1176,  1176,  1184,  1184,  1192,  1193,  1196,  1197,
    1201,  1202,  1203,  1204,  1205,  1206,  1207,  1208,  1209,  1210,
    1211,  1212,  1215,  1215,  1223,  1223,  1231,  1231,  1239,  1239,
    1247,  1247,  1255,  1255,  1263,  1263,  1271,  1271,  1280,  1280,
    1288,  1288,  1301,  1301,  1311,  1311,  1322,  1322,  1332,  1333,
    1336,  1336,  1344,  1345,  1348,  1349,  1352,  1353,  1354,  1355,
    1356,  1357,  1358,  1361,  1363,  1363,  1375,  1382,  1382,  1392,
    1393,  1396,  1397,  1400,  1400,  1408,  1408,  1418,  1418,  1428,
    1428,  1436,  1437,  1440,  1441,  1442,  1443,  1444,  1445,  1446,
    1447,  1448,  1449,  1450,  1451,  1452,  1453,  1454,  1455,  1458,
    1463,  1463,  1471,  1471,  1479,  1484,  1484,  1492,  1497,  1502,
    1502,  1510,  1511,  1514,  1514,  1522,  1527,  1532,  1537,  1542,
    1542,  1550,  1553,  1556,  1559,  1562,  1568,  1568,  1578,  1578,
    1585,  1585,  1597,  1597,  1610,  1611,  1615,  1619,  1619,  1631,
    1632,  1636,  1636,  1644,  1645,  1648,  1649,  1650,  1651,  1652,
    1655,  1659,  1659,  1667,  1667,  1677,  1678,  1681,  1681,  1689,
    1690,  1693,  1693
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
#line 3957 "dhcp4_parser.cc" // lalr1.cc:1167
#line 1701 "dhcp4_parser.yy" // lalr1.cc:1168


void
isc::dhcp::Dhcp4Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
