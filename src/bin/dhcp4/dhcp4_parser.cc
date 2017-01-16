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
      case 184: // socket_type
      case 397: // ncr_protocol_value
      case 406: // replace_client_name_value
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
      case 184: // socket_type
      case 397: // ncr_protocol_value
      case 406: // replace_client_name_value
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
#line 358 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 129: // "integer"

#line 202 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< int64_t > (); }
#line 365 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 130: // "floating point"

#line 202 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< double > (); }
#line 372 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 131: // "boolean"

#line 202 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< bool > (); }
#line 379 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 145: // value

#line 202 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 386 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 184: // socket_type

#line 202 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 393 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 397: // ncr_protocol_value

#line 202 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 400 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 406: // replace_client_name_value

#line 202 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 407 "dhcp4_parser.cc" // lalr1.cc:636
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
      case 184: // socket_type
      case 397: // ncr_protocol_value
      case 406: // replace_client_name_value
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
#line 650 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 4:
#line 212 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.CONFIG; }
#line 656 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 6:
#line 213 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.DHCP4; }
#line 662 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 8:
#line 214 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.INTERFACES_CONFIG; }
#line 668 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 10:
#line 215 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.SUBNET4; }
#line 674 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 12:
#line 216 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.POOLS; }
#line 680 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 14:
#line 217 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.RESERVATIONS; }
#line 686 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 16:
#line 218 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.OPTION_DEF; }
#line 692 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 18:
#line 219 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.OPTION_DATA; }
#line 698 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 20:
#line 220 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.HOOKS_LIBRARIES; }
#line 704 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 22:
#line 221 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.DHCP_DDNS; }
#line 710 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 24:
#line 229 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 716 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 25:
#line 230 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as< double > (), ctx.loc2pos(yystack_[0].location))); }
#line 722 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 26:
#line 231 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 728 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 27:
#line 232 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 734 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 28:
#line 233 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 740 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 29:
#line 234 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 746 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 30:
#line 235 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 752 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 31:
#line 238 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as< ElementPtr > ());
}
#line 761 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 32:
#line 243 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 772 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 33:
#line 248 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 782 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 36:
#line 259 "dhcp4_parser.yy" // lalr1.cc:859
    {
                  // map containing a single entry
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 791 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 37:
#line 263 "dhcp4_parser.yy" // lalr1.cc:859
    {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 801 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 38:
#line 270 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 810 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 39:
#line 273 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // list parsing complete. Put any sanity checking here
}
#line 818 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 40:
#line 278 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // List parsing about to start
}
#line 826 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 41:
#line 280 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // list parsing complete. Put any sanity checking here
    //ctx.stack_.pop_back();
}
#line 835 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 44:
#line 289 "dhcp4_parser.yy" // lalr1.cc:859
    {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 844 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 45:
#line 293 "dhcp4_parser.yy" // lalr1.cc:859
    {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 853 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 46:
#line 304 "dhcp4_parser.yy" // lalr1.cc:859
    {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as< std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 864 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 47:
#line 314 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 875 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 48:
#line 319 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 885 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 56:
#line 338 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Dhcp4", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP4);
}
#line 898 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 57:
#line 345 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 910 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 58:
#line 355 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the Dhcp4 map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 920 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 59:
#line 359 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 928 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 84:
#line 393 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 937 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 85:
#line 398 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 946 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 86:
#line 403 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 955 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 87:
#line 408 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr dpp(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 964 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 88:
#line 413 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr echo(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("echo-client-id", echo);
}
#line 973 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 89:
#line 418 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr match(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("match-client-id", match);
}
#line 982 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 90:
#line 424 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces-config", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.INTERFACES_CONFIG);
}
#line 993 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 91:
#line 429 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1002 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 96:
#line 442 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1012 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 97:
#line 446 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1020 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 98:
#line 450 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1031 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 99:
#line 455 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1040 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 100:
#line 460 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.DHCP_SOCKET_TYPE);
}
#line 1048 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 101:
#line 462 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("dhcp-socket-type", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1057 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 102:
#line 467 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("raw", ctx.loc2pos(yystack_[0].location))); }
#line 1063 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 103:
#line 468 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("udp", ctx.loc2pos(yystack_[0].location))); }
#line 1069 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 104:
#line 471 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lease-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.LEASE_DATABASE);
}
#line 1080 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 105:
#line 476 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1089 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 106:
#line 481 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1100 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 107:
#line 486 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1109 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 119:
#line 506 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1117 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 120:
#line 508 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 1127 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 121:
#line 514 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1135 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 122:
#line 516 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr user(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1145 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 123:
#line 522 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1153 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 124:
#line 524 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr pwd(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 1163 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 125:
#line 530 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1171 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 126:
#line 532 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr h(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 1181 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 127:
#line 538 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1189 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 128:
#line 540 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1199 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 129:
#line 546 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 1208 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 130:
#line 551 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 1217 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 131:
#line 556 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 1226 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 132:
#line 561 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1235 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 133:
#line 566 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 1246 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 134:
#line 571 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1255 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 141:
#line 586 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 1264 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 142:
#line 591 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr circuit(new StringElement("circuit-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(circuit);
}
#line 1273 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 143:
#line 596 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr client(new StringElement("client-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(client);
}
#line 1282 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 144:
#line 601 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 1293 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 145:
#line 606 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1302 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 150:
#line 619 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1312 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 151:
#line 623 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1320 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 152:
#line 627 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1330 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 153:
#line 631 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1338 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 159:
#line 644 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1346 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 160:
#line 646 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr lib(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 1356 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 161:
#line 652 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1364 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 162:
#line 654 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1373 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 163:
#line 660 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.EXPIRED_LEASES_PROCESSING);
}
#line 1384 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 164:
#line 665 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1393 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 173:
#line 682 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 1402 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 174:
#line 687 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 1411 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 175:
#line 692 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 1420 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 176:
#line 697 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 1429 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 177:
#line 702 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 1438 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 178:
#line 707 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 1447 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 179:
#line 715 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet4", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET4);
}
#line 1458 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 180:
#line 720 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1467 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 185:
#line 740 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1477 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 186:
#line 744 "dhcp4_parser.yy" // lalr1.cc:859
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
#line 1500 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 187:
#line 763 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the subnet4 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1510 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 188:
#line 767 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1518 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 211:
#line 799 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1526 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 212:
#line 801 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr subnet(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 1536 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 213:
#line 807 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1544 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 214:
#line 809 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface", iface);
    ctx.leave();
}
#line 1554 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 215:
#line 815 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1562 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 216:
#line 817 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface-id", iface);
    ctx.leave();
}
#line 1572 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 217:
#line 823 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1580 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 218:
#line 825 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-subnet", iface);
    ctx.leave();
}
#line 1590 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 219:
#line 831 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1598 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 220:
#line 833 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 1608 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 221:
#line 839 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1616 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 222:
#line 841 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface-id", iface);
    ctx.leave();
}
#line 1626 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 223:
#line 847 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.CLIENT_CLASS);
}
#line 1634 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 224:
#line 849 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr cls(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 1644 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 225:
#line 855 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1652 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 226:
#line 857 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr rm(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservation-mode", rm);
    ctx.leave();
}
#line 1662 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 227:
#line 863 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr id(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 1671 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 228:
#line 868 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr rc(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rapid-commit", rc);
}
#line 1680 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 229:
#line 877 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 1691 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 230:
#line 882 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1700 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 235:
#line 899 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1710 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 236:
#line 903 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1718 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 237:
#line 910 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1728 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 238:
#line 914 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1736 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 252:
#line 940 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr code(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 1745 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 255:
#line 949 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1753 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 256:
#line 951 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 1763 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 257:
#line 957 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1771 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 258:
#line 959 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr space(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 1781 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 260:
#line 967 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1789 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 261:
#line 969 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr encap(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 1799 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 262:
#line 975 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr array(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 1808 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 263:
#line 984 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 1819 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 264:
#line 989 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1828 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 269:
#line 1008 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1838 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 270:
#line 1012 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1846 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 271:
#line 1019 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1856 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 272:
#line 1023 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1864 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 284:
#line 1052 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1872 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 285:
#line 1054 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr data(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 1882 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 288:
#line 1064 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr space(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", space);
}
#line 1891 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 289:
#line 1072 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 1902 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 290:
#line 1077 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1911 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 295:
#line 1092 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1921 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 296:
#line 1096 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1929 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 297:
#line 1100 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1939 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 298:
#line 1104 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1947 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 304:
#line 1117 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1955 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 305:
#line 1119 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr pool(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 1965 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 306:
#line 1128 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 1976 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 307:
#line 1133 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1985 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 312:
#line 1146 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1995 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 313:
#line 1150 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2003 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 314:
#line 1154 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2013 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 315:
#line 1158 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 2021 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 332:
#line 1185 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2029 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 333:
#line 1187 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr next_server(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("next-server", next_server);
    ctx.leave();
}
#line 2039 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 334:
#line 1193 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2047 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 335:
#line 1195 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr srv(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-hostname", srv);
    ctx.leave();
}
#line 2057 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 336:
#line 1201 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2065 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 337:
#line 1203 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr bootfile(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("boot-file-name", bootfile);
    ctx.leave();
}
#line 2075 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 338:
#line 1209 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2083 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 339:
#line 1211 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr addr(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", addr);
    ctx.leave();
}
#line 2093 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 340:
#line 1217 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2101 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 341:
#line 1219 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr d(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 2111 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 342:
#line 1225 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2119 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 343:
#line 1227 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 2129 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 344:
#line 1233 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2137 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 345:
#line 1235 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-id", hw);
    ctx.leave();
}
#line 2147 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 346:
#line 1241 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2155 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 347:
#line 1243 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("circuit-id", hw);
    ctx.leave();
}
#line 2165 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 348:
#line 1250 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2173 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 349:
#line 1252 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr host(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 2183 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 350:
#line 1258 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2194 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 351:
#line 1263 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2203 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 352:
#line 1271 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 2214 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 353:
#line 1276 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2223 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 354:
#line 1281 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2231 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 355:
#line 1283 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr ip(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", ip);
    ctx.leave();
}
#line 2241 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 356:
#line 1292 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 2252 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 357:
#line 1297 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2261 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 360:
#line 1306 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2271 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 361:
#line 1310 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2279 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 374:
#line 1333 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2287 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 375:
#line 1335 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr test(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 2297 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 376:
#line 1344 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-id", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SERVER_ID);
}
#line 2308 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 377:
#line 1349 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2317 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 387:
#line 1367 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr htype(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("htype", htype);
}
#line 2326 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 388:
#line 1372 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2334 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 389:
#line 1374 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr id(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("identifier", id);
    ctx.leave();
}
#line 2344 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 390:
#line 1380 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("time", time);
}
#line 2353 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 391:
#line 1385 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enterprise-id", time);
}
#line 2362 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 392:
#line 1392 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 2371 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 393:
#line 1399 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 2382 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 394:
#line 1404 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2391 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 399:
#line 1417 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2399 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 400:
#line 1419 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr stype(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 2409 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 401:
#line 1425 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2417 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 402:
#line 1427 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 2427 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 403:
#line 1435 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 2438 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 404:
#line 1440 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2447 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 405:
#line 1445 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2457 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 406:
#line 1449 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 2465 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 425:
#line 1475 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 2474 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 426:
#line 1480 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2482 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 427:
#line 1482 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("qualifying-suffix", s);
    ctx.leave();
}
#line 2492 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 428:
#line 1488 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2500 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 429:
#line 1490 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 2510 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 430:
#line 1496 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 2519 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 431:
#line 1501 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2527 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 432:
#line 1503 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 2537 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 433:
#line 1509 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 2546 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 434:
#line 1514 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 2555 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 435:
#line 1519 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 2563 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 436:
#line 1521 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2572 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 437:
#line 1527 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 2578 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 438:
#line 1528 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 2584 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 439:
#line 1531 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NCR_FORMAT);
}
#line 2592 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 440:
#line 1533 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 2602 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 441:
#line 1539 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-include-fqdn", b);
}
#line 2611 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 442:
#line 1544 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("allow-client-update",  b);
}
#line 2620 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 443:
#line 1549 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-no-update", b);
}
#line 2629 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 444:
#line 1554 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-client-update", b);
}
#line 2638 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 445:
#line 1559 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 2646 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 446:
#line 1561 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("replace-client-name", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2655 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 447:
#line 1567 "dhcp4_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("when-present", ctx.loc2pos(yystack_[0].location))); 
      }
#line 2663 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 448:
#line 1570 "dhcp4_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location)));
      }
#line 2671 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 449:
#line 1573 "dhcp4_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("always", ctx.loc2pos(yystack_[0].location)));
      }
#line 2679 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 450:
#line 1576 "dhcp4_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("when-not-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 2687 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 451:
#line 1579 "dhcp4_parser.yy" // lalr1.cc:859
    {
      error(yystack_[0].location, "boolean values for the replace-client-name are "
                "no longer supported");
      }
#line 2696 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 452:
#line 1585 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2704 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 453:
#line 1587 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("generated-prefix", s);
    ctx.leave();
}
#line 2714 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 454:
#line 1595 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2722 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 455:
#line 1597 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("Dhcp6", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2731 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 456:
#line 1602 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2739 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 457:
#line 1604 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("DhcpDdns", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2748 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 458:
#line 1614 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Logging", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.LOGGING);
}
#line 2759 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 459:
#line 1619 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2768 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 463:
#line 1636 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 2779 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 464:
#line 1641 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2788 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 467:
#line 1653 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 2798 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 468:
#line 1657 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2806 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 476:
#line 1672 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr dl(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 2815 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 477:
#line 1676 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2823 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 478:
#line 1678 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 2833 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 479:
#line 1684 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 2844 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 480:
#line 1689 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2853 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 483:
#line 1698 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2863 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 484:
#line 1702 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2871 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 487:
#line 1710 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2879 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 488:
#line 1712 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 2889 "dhcp4_parser.cc" // lalr1.cc:859
    break;


#line 2893 "dhcp4_parser.cc" // lalr1.cc:859
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


  const short int Dhcp4Parser::yypact_ninf_ = -483;

  const signed char Dhcp4Parser::yytable_ninf_ = -1;

  const short int
  Dhcp4Parser::yypact_[] =
  {
     194,  -483,  -483,  -483,  -483,  -483,  -483,  -483,  -483,  -483,
    -483,  -483,    35,    23,    56,    58,    80,    86,   124,   125,
     160,   169,   184,   201,  -483,  -483,  -483,  -483,  -483,  -483,
    -483,  -483,  -483,  -483,  -483,  -483,  -483,  -483,  -483,  -483,
    -483,  -483,  -483,  -483,  -483,  -483,  -483,  -483,  -483,  -483,
    -483,  -483,  -483,  -483,  -483,  -483,    23,   -33,    19,    88,
      64,    20,    -5,    27,   118,    71,   -30,   235,  -483,   101,
     147,   206,   214,   225,  -483,  -483,  -483,  -483,   228,  -483,
      40,  -483,  -483,  -483,  -483,  -483,  -483,   239,   240,  -483,
    -483,  -483,   241,   243,   244,   245,  -483,  -483,  -483,  -483,
    -483,  -483,  -483,  -483,   246,  -483,  -483,  -483,    46,  -483,
    -483,  -483,  -483,  -483,  -483,  -483,  -483,  -483,  -483,  -483,
    -483,  -483,  -483,  -483,  -483,  -483,  -483,  -483,  -483,  -483,
    -483,  -483,  -483,    50,  -483,  -483,  -483,  -483,  -483,  -483,
    -483,  -483,  -483,  -483,  -483,   247,   248,  -483,  -483,  -483,
    -483,  -483,  -483,  -483,  -483,  -483,    75,  -483,  -483,  -483,
    -483,  -483,  -483,  -483,  -483,  -483,  -483,  -483,  -483,  -483,
    -483,  -483,  -483,  -483,  -483,  -483,    93,  -483,  -483,  -483,
    -483,  -483,  -483,  -483,  -483,  -483,  -483,  -483,  -483,  -483,
     249,   250,  -483,  -483,  -483,  -483,  -483,  -483,  -483,  -483,
    -483,  -483,  -483,  -483,  -483,   252,  -483,  -483,  -483,   254,
    -483,  -483,  -483,   251,   258,  -483,  -483,  -483,  -483,  -483,
    -483,  -483,  -483,  -483,  -483,  -483,   259,  -483,  -483,  -483,
    -483,   256,   262,  -483,  -483,  -483,  -483,  -483,  -483,  -483,
    -483,  -483,    94,  -483,  -483,  -483,   264,  -483,  -483,   265,
    -483,   266,   269,  -483,  -483,   271,   272,   274,   275,  -483,
    -483,  -483,   100,  -483,  -483,  -483,  -483,  -483,  -483,  -483,
    -483,  -483,  -483,  -483,  -483,  -483,  -483,  -483,  -483,  -483,
      23,    23,  -483,   126,   276,   279,   282,   283,  -483,    19,
    -483,   284,   131,   135,   291,   295,   297,   175,   176,   177,
     178,   299,   305,   334,   335,   336,   337,   338,   339,   216,
     340,   342,    88,  -483,   343,   344,    64,  -483,    42,   345,
     346,   347,   348,   349,   350,   351,   229,   226,   352,   355,
     356,   357,    20,  -483,   358,    -5,  -483,   360,   361,   362,
     363,   364,   365,   366,   367,   368,  -483,    27,   369,   370,
     253,   371,   372,   373,   255,  -483,   118,   374,   257,  -483,
      71,   375,   376,   -28,  -483,   260,   377,   379,   261,   380,
     263,   267,   381,   383,   268,   273,   277,   278,   385,   389,
     235,  -483,  -483,  -483,   390,   388,   391,    23,    23,  -483,
     395,  -483,  -483,   285,   396,   398,  -483,  -483,  -483,  -483,
     392,   401,   402,   405,   406,   407,   408,   409,  -483,   410,
     411,  -483,   414,   102,  -483,  -483,  -483,  -483,  -483,  -483,
    -483,  -483,   412,   418,  -483,  -483,  -483,   286,   294,   296,
     420,   298,   301,   302,  -483,  -483,   303,   306,   430,   416,
    -483,   308,  -483,   309,   310,   414,   311,   312,   314,   316,
     317,   319,  -483,   320,   321,  -483,   322,   324,   325,  -483,
    -483,   326,  -483,  -483,   327,    23,  -483,  -483,   328,   329,
    -483,   331,  -483,  -483,    21,   359,  -483,  -483,  -483,  -483,
      31,   332,  -483,    23,    88,   354,  -483,  -483,    64,  -483,
     154,   154,   454,   458,   459,   174,    26,   460,   128,   106,
     155,   235,  -483,  -483,  -483,  -483,  -483,   464,  -483,    42,
    -483,  -483,  -483,   462,  -483,  -483,  -483,  -483,  -483,   463,
     404,  -483,  -483,  -483,  -483,  -483,  -483,  -483,  -483,  -483,
    -483,  -483,  -483,  -483,  -483,  -483,  -483,  -483,  -483,  -483,
    -483,  -483,  -483,  -483,  -483,  -483,  -483,  -483,  -483,  -483,
    -483,  -483,  -483,  -483,   122,  -483,   165,  -483,  -483,   166,
    -483,  -483,  -483,   468,   469,   470,  -483,   181,  -483,  -483,
    -483,  -483,  -483,  -483,  -483,  -483,  -483,   187,  -483,   471,
     472,  -483,  -483,   473,   477,  -483,  -483,   475,   479,  -483,
    -483,  -483,  -483,  -483,  -483,    61,  -483,  -483,  -483,  -483,
    -483,   143,  -483,   478,   480,  -483,   481,   482,   483,   484,
     485,   486,   189,  -483,  -483,  -483,  -483,  -483,  -483,  -483,
    -483,   487,   488,   489,  -483,  -483,  -483,   190,  -483,  -483,
    -483,  -483,  -483,  -483,  -483,   203,  -483,  -483,  -483,   209,
      23,   378,  -483,  -483,   491,   492,  -483,  -483,   493,   495,
    -483,  -483,   494,  -483,   490,   354,  -483,  -483,   496,   497,
     499,   382,   386,   387,   154,  -483,  -483,    20,  -483,   454,
     118,  -483,   458,    71,  -483,   459,   174,  -483,    26,  -483,
     -30,  -483,   460,   393,   394,   397,   399,   400,   403,   128,
    -483,   500,   413,   415,   417,   106,  -483,   501,   503,   155,
    -483,  -483,   502,  -483,    -5,  -483,   462,    27,  -483,   463,
     505,  -483,   506,  -483,   384,   419,   421,  -483,  -483,  -483,
    -483,   211,  -483,   508,  -483,   509,  -483,  -483,  -483,   215,
    -483,  -483,  -483,  -483,  -483,  -483,  -483,  -483,   422,  -483,
    -483,  -483,  -483,   423,   424,  -483,  -483,   217,  -483,   511,
    -483,   425,   507,  -483,  -483,  -483,  -483,  -483,  -483,  -483,
    -483,  -483,  -483,  -483,  -483,  -483,  -483,   227,  -483,    29,
     507,  -483,  -483,   516,  -483,  -483,  -483,   218,  -483,  -483,
    -483,  -483,  -483,   517,   426,   520,    29,  -483,   522,  -483,
     428,  -483,   518,  -483,  -483,   236,  -483,   427,   518,  -483,
    -483,   221,  -483,  -483,   526,   427,  -483,   429,  -483,  -483
  };

  const unsigned short int
  Dhcp4Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     1,    38,    32,    28,    27,    24,
      25,    26,    31,     3,    29,    30,    47,     5,    58,     7,
      96,     9,   187,    11,   297,    13,   314,    15,   237,    17,
     271,    19,   152,    21,   405,    23,    42,    34,     0,     0,
       0,     0,     0,   316,   239,   273,     0,     0,    44,     0,
      43,     0,     0,    35,    56,   458,   454,   456,     0,    55,
       0,    49,    51,    53,    54,    52,    90,     0,     0,   332,
     104,   106,     0,     0,     0,     0,   179,   229,   263,   133,
     356,   144,   163,   376,     0,   393,   403,    83,     0,    60,
      62,    63,    64,    65,    80,    81,    67,    68,    69,    70,
      74,    75,    66,    72,    73,    82,    71,    76,    77,    78,
      79,    98,   100,     0,    92,    94,    95,   360,   213,   215,
     217,   289,   211,   219,   221,     0,     0,   225,   223,   306,
     352,   210,   191,   192,   193,   205,     0,   189,   196,   207,
     208,   209,   197,   198,   201,   203,   199,   200,   194,   195,
     202,   206,   204,   304,   303,   302,     0,   299,   301,   334,
     336,   350,   340,   342,   346,   344,   348,   338,   331,   327,
       0,   317,   318,   328,   329,   330,   324,   320,   325,   322,
     323,   326,   321,   119,   127,     0,   257,   255,   260,     0,
     250,   254,   251,     0,   240,   241,   243,   253,   244,   245,
     246,   259,   247,   248,   249,   284,     0,   282,   283,   286,
     287,     0,   274,   275,   277,   278,   279,   280,   281,   159,
     161,   156,     0,   154,   157,   158,     0,   426,   428,     0,
     431,     0,     0,   435,   439,     0,     0,     0,     0,   445,
     452,   424,     0,   407,   409,   410,   411,   412,   413,   414,
     415,   416,   417,   418,   419,   420,   421,   422,   423,    39,
       0,     0,    33,     0,     0,     0,     0,     0,    46,     0,
      48,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    59,     0,     0,     0,    97,   362,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   188,     0,     0,   298,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   315,     0,     0,     0,
       0,     0,     0,     0,     0,   238,     0,     0,     0,   272,
       0,     0,     0,     0,   153,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   406,    45,    36,     0,     0,     0,     0,     0,    50,
       0,    88,    89,     0,     0,     0,    84,    85,    86,    87,
       0,     0,     0,     0,     0,     0,     0,     0,   392,     0,
       0,    61,     0,     0,    93,   374,   372,   373,   368,   369,
     370,   371,     0,   363,   364,   366,   367,     0,     0,     0,
       0,     0,     0,     0,   227,   228,     0,     0,     0,     0,
     190,     0,   300,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   319,     0,     0,   252,     0,     0,     0,   262,
     242,     0,   288,   276,     0,     0,   155,   425,     0,     0,
     430,     0,   433,   434,     0,     0,   441,   442,   443,   444,
       0,     0,   408,     0,     0,     0,   455,   457,     0,   333,
       0,     0,   181,   231,   265,     0,     0,   146,     0,     0,
       0,     0,    40,    99,   102,   103,   101,     0,   361,     0,
     214,   216,   218,   291,   212,   220,   222,   226,   224,   308,
       0,   305,   335,   337,   351,   341,   343,   347,   345,   349,
     339,   120,   128,   258,   256,   261,   285,   160,   162,   427,
     429,   432,   437,   438,   436,   440,   447,   448,   449,   450,
     451,   446,   453,    37,     0,   463,     0,   460,   462,     0,
     121,   123,   125,     0,     0,     0,   118,     0,   108,   110,
     111,   112,   113,   114,   115,   116,   117,     0,   185,     0,
     182,   183,   235,     0,   232,   233,   269,     0,   266,   267,
     132,   141,   142,   143,   137,     0,   135,   138,   139,   140,
     358,     0,   150,     0,   147,   148,     0,     0,     0,     0,
       0,     0,     0,   165,   167,   168,   169,   170,   171,   172,
     388,     0,     0,     0,   386,   380,   385,     0,   378,   383,
     381,   382,   384,   399,   401,     0,   395,   397,   398,     0,
      42,     0,   365,   295,     0,   292,   293,   312,     0,   309,
     310,   354,     0,    57,     0,     0,   459,    91,     0,     0,
       0,     0,     0,     0,     0,   105,   107,     0,   180,     0,
     239,   230,     0,   273,   264,     0,     0,   134,     0,   357,
       0,   145,     0,     0,     0,     0,     0,     0,     0,     0,
     164,     0,     0,     0,     0,     0,   377,     0,     0,     0,
     394,   404,     0,   375,     0,   290,     0,   316,   307,     0,
       0,   353,     0,   461,     0,     0,     0,   129,   130,   131,
     109,     0,   184,     0,   234,     0,   268,   136,   359,     0,
     149,   173,   174,   175,   176,   177,   178,   166,     0,   387,
     390,   391,   379,     0,     0,   396,    41,     0,   294,     0,
     311,     0,     0,   122,   124,   126,   186,   236,   270,   151,
     389,   400,   402,   296,   313,   355,   467,     0,   465,     0,
       0,   464,   479,     0,   477,   475,   471,     0,   469,   473,
     474,   472,   466,     0,     0,     0,     0,   468,     0,   476,
       0,   470,     0,   478,   483,     0,   481,     0,     0,   480,
     487,     0,   485,   482,     0,     0,   484,     0,   486,   488
  };

  const short int
  Dhcp4Parser::yypgoto_[] =
  {
    -483,  -483,  -483,  -483,  -483,  -483,  -483,  -483,  -483,  -483,
    -483,  -483,  -483,    13,  -483,  -483,  -483,  -483,  -483,  -483,
    -483,    65,  -483,  -164,  -483,   -58,  -483,  -483,  -483,   242,
    -483,  -483,  -483,  -483,    49,   222,   -60,   -42,   -41,  -483,
    -483,   -40,  -483,  -483,    47,   220,  -483,  -483,  -483,  -483,
    -483,  -483,  -483,  -483,  -483,  -483,  -483,    52,  -127,  -468,
    -483,  -483,  -483,  -483,  -483,  -483,  -483,   -63,  -483,  -482,
    -483,  -483,  -483,  -483,  -483,  -483,  -138,  -483,  -483,  -483,
    -483,  -483,  -483,  -483,  -142,  -483,  -483,  -483,  -139,   182,
    -483,  -483,  -483,  -483,  -483,  -483,  -483,  -141,  -483,  -483,
    -483,  -483,  -483,  -483,  -483,  -483,  -483,  -483,  -115,  -483,
    -483,  -483,  -109,   230,  -483,  -483,  -483,  -483,  -483,  -483,
    -483,  -483,  -483,  -483,  -483,  -483,  -471,  -483,  -483,  -483,
    -483,  -483,  -483,  -483,  -483,  -483,  -113,  -483,  -483,  -483,
    -110,  -483,   205,  -483,   -52,  -483,  -483,  -483,  -483,   -50,
    -483,  -483,  -483,  -483,  -483,   -51,  -483,  -483,  -483,  -112,
    -483,  -483,  -483,  -108,  -483,   204,  -483,  -483,  -483,  -483,
    -483,  -483,  -483,  -483,  -483,  -483,  -140,  -483,  -483,  -483,
    -137,   233,  -483,  -483,  -483,  -483,  -483,  -483,  -136,  -483,
    -483,  -483,  -135,  -483,   223,   -47,  -483,  -300,  -483,  -294,
    -483,  -483,  -483,  -483,  -483,  -483,  -483,  -483,  -483,  -483,
    -483,  -483,  -483,  -483,  -483,  -483,  -483,  -483,  -483,  -483,
    -483,  -483,  -483,  -483,  -483,    60,  -483,  -483,  -483,  -483,
    -483,  -483,  -124,  -483,  -483,  -483,  -483,  -483,  -483,  -483,
    -483,  -483,  -125,  -483,  -483,  -483,  -483,  -483,  -483,  -483,
    -483,    74,   196,  -483,  -483,  -483,  -483,  -483,  -483,  -483,
    -483,  -483,  -483,  -483,  -483,  -483,  -483,  -483,  -483,  -483,
    -483,  -483,  -483,  -483,  -483,  -483,  -483,  -483,  -483,  -483,
    -483,  -483,  -483,  -483,   -78,  -483,  -483,  -483,  -192,  -483,
    -483,  -207,  -483,  -483,  -483,  -483,  -483,  -483,  -218,  -483,
    -483,  -224,  -483
  };

  const short int
  Dhcp4Parser::yydefgoto_[] =
  {
      -1,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    68,    33,    34,    57,    72,    73,    35,
      56,   503,   640,    69,    70,   107,    37,    58,    80,    81,
      82,   284,    39,    59,   108,   109,   110,   111,   112,   113,
     114,   115,   116,   291,   133,   134,    41,    60,   135,   314,
     136,   315,   506,   117,   295,   118,   296,   567,   568,   211,
     348,   570,   658,   571,   659,   572,   660,   212,   349,   574,
     575,   576,   594,   119,   304,   595,   596,   597,   598,   599,
     120,   306,   603,   604,   605,   680,    53,    66,   242,   243,
     244,   361,   245,   362,   121,   307,   612,   613,   614,   615,
     616,   617,   618,   619,   122,   301,   579,   580,   581,   667,
      43,    61,   156,   157,   158,   323,   159,   319,   160,   320,
     161,   321,   162,   324,   163,   325,   164,   329,   165,   328,
     166,   167,   123,   302,   583,   584,   585,   670,    49,    64,
     213,   214,   215,   216,   217,   218,   219,   220,   352,   221,
     351,   222,   223,   353,   224,   124,   303,   587,   588,   589,
     673,    51,    65,   231,   232,   233,   234,   235,   357,   236,
     237,   238,   169,   322,   644,   645,   646,   704,    45,    62,
     176,   177,   178,   334,   170,   330,   648,   649,   650,   707,
      47,    63,   190,   191,   192,   125,   294,   194,   337,   195,
     338,   196,   345,   197,   340,   198,   341,   199,   343,   200,
     342,   201,   344,   202,   339,   172,   331,   652,   710,   126,
     305,   601,   318,   422,   423,   424,   425,   426,   507,   127,
     308,   627,   628,   629,   630,   691,   631,   632,   128,   129,
     310,   635,   636,   637,   697,   638,   698,   130,   311,    55,
      67,   262,   263,   264,   265,   366,   266,   367,   267,   268,
     369,   269,   270,   271,   372,   544,   272,   373,   273,   274,
     275,   276,   277,   378,   551,   278,   379,    83,   286,    84,
     287,    85,   285,   556,   557,   558,   654,   767,   768,   769,
     777,   778,   779,   780,   785,   781,   783,   795,   796,   797,
     801,   802,   804
  };

  const unsigned short int
  Dhcp4Parser::yytable_[] =
  {
      79,   152,   228,   151,   174,   188,   210,   227,   241,   261,
     168,   175,   189,   229,   171,   230,   193,   626,   420,   153,
     154,   155,   569,   569,   421,   600,    32,   137,    25,    74,
      26,   625,    27,   137,    98,    24,   542,    88,    89,   239,
     240,   239,   240,   289,   173,    89,   179,   180,   290,   312,
      92,    93,    94,   316,   313,   138,   139,   140,   317,    98,
      89,   179,   180,    36,   676,    38,    98,   677,   141,   204,
     142,   143,   144,   145,   146,   147,   131,   132,   332,   148,
     149,    98,   204,   333,   181,   148,   150,    40,   182,   183,
     184,   185,   186,    42,   187,    71,   335,   363,    78,    86,
     415,   336,   364,   380,    87,    88,    89,   279,   381,    90,
      91,   204,   225,   205,   206,   226,   504,   505,    92,    93,
      94,    95,    96,    78,   543,   312,    97,    98,    75,   203,
     653,    44,    46,   563,    76,    77,   546,   547,   548,   549,
     772,   203,   773,   774,    99,   100,   678,    78,    78,   679,
     280,    28,    29,    30,    31,    78,   101,    78,   204,   102,
     205,   206,   550,   207,   208,   209,   103,    48,   655,   316,
      78,   104,   105,   656,   657,   106,    50,   203,   560,   561,
     562,   563,   564,   565,   664,   620,   621,   622,   623,   665,
     664,    52,   689,   695,   204,   666,   569,   690,   696,    78,
     606,   607,   608,   609,   610,   611,   699,   728,    54,   420,
     281,   700,   380,   626,   332,   421,    78,   701,   363,   756,
     335,   786,   282,   759,   805,   763,   787,   625,   283,   806,
     770,    79,   288,   771,    78,   590,   591,   592,   593,   798,
     633,   634,   799,   292,   293,   297,    78,   298,   299,   300,
     309,   326,   327,   347,   384,   417,   350,   346,   354,   355,
     416,   356,   391,   358,   359,   360,   392,   418,   365,   368,
     370,   419,   152,   371,   151,   374,   375,   174,   376,   377,
     385,   168,    78,   386,   175,   171,   387,   388,   390,   188,
     153,   154,   155,   382,   383,   393,   189,   228,   210,   394,
     193,   395,   227,   400,   396,   397,   398,   399,   229,   401,
     230,     1,     2,     3,     4,     5,     6,     7,     8,     9,
      10,    11,   261,   246,   247,   248,   249,   250,   251,   252,
     253,   254,   255,   256,   257,   258,   259,   260,   402,   403,
     404,   405,   406,   407,   409,   408,   410,   412,   413,   427,
     428,   429,   430,   431,   432,   433,   436,   435,   434,   437,
     438,   439,   441,    78,   443,   444,   445,   446,   447,   448,
     449,   450,   451,   453,   454,   456,   457,   458,   461,   464,
     465,   468,   455,   469,   471,   474,   459,   475,   462,   480,
     470,   467,   472,   481,   483,   484,   473,   492,   485,   476,
     486,   487,   488,   490,   477,   491,   493,   494,   478,   479,
     495,   496,   497,   489,   510,   498,   499,   500,   501,   502,
     508,   509,   511,   520,   512,   513,   514,   573,   573,   515,
     516,   517,   566,   566,   518,   519,   521,   522,   523,   525,
     526,   624,   527,   261,   528,   529,   417,   530,   531,   532,
     533,   416,   534,   535,   536,   537,   539,   540,   418,   541,
     552,   578,   419,   545,   555,   582,   586,   602,   641,   643,
     647,   651,   661,   662,   663,   669,   702,   668,   538,   671,
     672,   674,   675,   682,   681,   683,   684,   685,   686,   687,
     688,   692,   693,   694,   712,   706,   553,   705,   709,   708,
     714,   715,   711,   716,   738,   743,   703,   744,   746,   751,
     524,   752,   753,   717,   766,   718,   757,   758,   719,   764,
     784,   788,   731,   732,   790,   794,   733,   792,   734,   735,
     807,   389,   736,   554,   411,   559,   414,   720,   727,   800,
     730,   729,   739,   577,   740,   466,   741,   754,   737,   755,
     760,   761,   762,   765,   722,   789,   793,   809,   721,   724,
     723,   460,   440,   726,   463,   725,   748,   747,   442,   642,
     452,   742,   749,   750,   745,   639,   482,   713,   782,   791,
     803,   808,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   573,     0,     0,     0,     0,   566,   152,     0,   151,
     228,     0,   210,     0,     0,   227,   168,     0,     0,     0,
     171,   229,   241,   230,     0,   153,   154,   155,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   624,     0,     0,
       0,     0,     0,     0,     0,     0,   174,     0,     0,   188,
       0,     0,     0,   175,     0,     0,   189,     0,     0,     0,
     193,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   776,     0,     0,     0,
       0,   775,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   776,     0,     0,     0,     0,   775
  };

  const short int
  Dhcp4Parser::yycheck_[] =
  {
      58,    61,    65,    61,    62,    63,    64,    65,    66,    67,
      61,    62,    63,    65,    61,    65,    63,   499,   318,    61,
      61,    61,   490,   491,   318,   496,    13,     7,     5,    10,
       7,   499,     9,     7,    39,     0,    15,    17,    18,    69,
      70,    69,    70,     3,    49,    18,    19,    20,     8,     3,
      30,    31,    32,     3,     8,    35,    36,    37,     8,    39,
      18,    19,    20,     7,     3,     7,    39,     6,    48,    40,
      50,    51,    52,    53,    54,    55,    12,    13,     3,    59,
      60,    39,    40,     8,    57,    59,    66,     7,    61,    62,
      63,    64,    65,     7,    67,   128,     3,     3,   128,    11,
      58,     8,     8,     3,    16,    17,    18,     6,     8,    21,
      22,    40,    41,    42,    43,    44,    14,    15,    30,    31,
      32,    33,    34,   128,   103,     3,    38,    39,   109,    23,
       8,     7,     7,    27,   115,   116,   105,   106,   107,   108,
     111,    23,   113,   114,    56,    57,     3,   128,   128,     6,
       3,   128,   129,   130,   131,   128,    68,   128,    40,    71,
      42,    43,   131,    45,    46,    47,    78,     7,     3,     3,
     128,    83,    84,     8,     8,    87,     7,    23,    24,    25,
      26,    27,    28,    29,     3,    79,    80,    81,    82,     8,
       3,     7,     3,     3,    40,     8,   664,     8,     8,   128,
      72,    73,    74,    75,    76,    77,     3,   678,     7,   509,
       4,     8,     3,   695,     3,   509,   128,     8,     3,     8,
       3,     3,     8,     8,     3,     8,     8,   695,     3,     8,
       3,   289,     4,     6,   128,    61,    62,    63,    64,     3,
      85,    86,     6,     4,     4,     4,   128,     4,     4,     4,
       4,     4,     4,     3,   128,   318,     4,     8,     4,     8,
     318,     3,   131,     4,     8,     3,   131,   318,     4,     4,
       4,   318,   332,     4,   332,     4,     4,   335,     4,     4,
       4,   332,   128,     4,   335,   332,     4,     4,     4,   347,
     332,   332,   332,   280,   281,     4,   347,   360,   356,     4,
     347,     4,   360,     4,   129,   129,   129,   129,   360,     4,
     360,   117,   118,   119,   120,   121,   122,   123,   124,   125,
     126,   127,   380,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,     4,     4,
       4,     4,     4,     4,     4,   129,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,   131,   129,     4,
       4,     4,     4,   128,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,   129,     4,     4,     4,   131,     4,   131,     4,
     129,   131,   129,     4,     4,     7,   129,     5,     7,   131,
     387,   388,     7,     7,   131,     7,     5,     5,   131,   131,
       5,     5,     5,   128,   128,     7,     7,     7,     7,     5,
       8,     3,   128,     7,   128,     5,   128,   490,   491,   128,
     128,   128,   490,   491,   128,     5,   128,   128,   128,   128,
     128,   499,   128,   501,   128,   128,   509,   128,   128,   128,
     128,   509,   128,   128,   128,   128,   128,   128,   509,   128,
     128,     7,   509,   104,   110,     7,     7,     7,     4,     7,
       7,    67,     4,     4,     4,     3,   640,     6,   465,     6,
       3,     6,     3,     3,     6,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     3,   483,     6,     3,     6,
       4,     4,     8,     4,     4,     4,   128,     4,     6,     4,
     445,     5,   128,   131,     7,   129,     8,     8,   131,     8,
       4,     4,   129,   129,     4,     7,   129,     5,   129,   129,
       4,   289,   129,   484,   312,   488,   316,   664,   676,   112,
     682,   680,   129,   491,   129,   363,   129,   128,   689,   128,
     128,   128,   128,   128,   669,   129,   128,   128,   667,   672,
     670,   356,   332,   675,   360,   673,   706,   704,   335,   509,
     347,   695,   707,   709,   699,   501,   380,   655,   770,   786,
     798,   805,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   664,    -1,    -1,    -1,    -1,   664,   667,    -1,   667,
     673,    -1,   670,    -1,    -1,   673,   667,    -1,    -1,    -1,
     667,   673,   680,   673,    -1,   667,   667,   667,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   695,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   704,    -1,    -1,   707,
      -1,    -1,    -1,   704,    -1,    -1,   707,    -1,    -1,    -1,
     707,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   769,    -1,    -1,    -1,
      -1,   769,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   786,    -1,    -1,    -1,    -1,   786
  };

  const unsigned short int
  Dhcp4Parser::yystos_[] =
  {
       0,   117,   118,   119,   120,   121,   122,   123,   124,   125,
     126,   127,   133,   134,   135,   136,   137,   138,   139,   140,
     141,   142,   143,   144,     0,     5,     7,     9,   128,   129,
     130,   131,   145,   146,   147,   151,     7,   158,     7,   164,
       7,   178,     7,   242,     7,   310,     7,   322,     7,   270,
       7,   293,     7,   218,     7,   381,   152,   148,   159,   165,
     179,   243,   311,   323,   271,   294,   219,   382,   145,   155,
     156,   128,   149,   150,    10,   109,   115,   116,   128,   157,
     160,   161,   162,   409,   411,   413,    11,    16,    17,    18,
      21,    22,    30,    31,    32,    33,    34,    38,    39,    56,
      57,    68,    71,    78,    83,    84,    87,   157,   166,   167,
     168,   169,   170,   171,   172,   173,   174,   185,   187,   205,
     212,   226,   236,   264,   287,   327,   351,   361,   370,   371,
     379,    12,    13,   176,   177,   180,   182,     7,    35,    36,
      37,    48,    50,    51,    52,    53,    54,    55,    59,    60,
      66,   157,   168,   169,   170,   173,   244,   245,   246,   248,
     250,   252,   254,   256,   258,   260,   262,   263,   287,   304,
     316,   327,   347,    49,   157,   287,   312,   313,   314,    19,
      20,    57,    61,    62,    63,    64,    65,    67,   157,   287,
     324,   325,   326,   327,   329,   331,   333,   335,   337,   339,
     341,   343,   345,    23,    40,    42,    43,    45,    46,    47,
     157,   191,   199,   272,   273,   274,   275,   276,   277,   278,
     279,   281,   283,   284,   286,    41,    44,   157,   199,   276,
     281,   295,   296,   297,   298,   299,   301,   302,   303,    69,
      70,   157,   220,   221,   222,   224,    88,    89,    90,    91,
      92,    93,    94,    95,    96,    97,    98,    99,   100,   101,
     102,   157,   383,   384,   385,   386,   388,   390,   391,   393,
     394,   395,   398,   400,   401,   402,   403,   404,   407,     6,
       3,     4,     8,     3,   163,   414,   410,   412,     4,     3,
       8,   175,     4,     4,   328,   186,   188,     4,     4,     4,
       4,   237,   265,   288,   206,   352,   213,   227,   362,     4,
     372,   380,     3,     8,   181,   183,     3,     8,   354,   249,
     251,   253,   305,   247,   255,   257,     4,     4,   261,   259,
     317,   348,     3,     8,   315,     3,     8,   330,   332,   346,
     336,   338,   342,   340,   344,   334,     8,     3,   192,   200,
       4,   282,   280,   285,     4,     8,     3,   300,     4,     8,
       3,   223,   225,     3,     8,     4,   387,   389,     4,   392,
       4,     4,   396,   399,     4,     4,     4,     4,   405,   408,
       3,     8,   145,   145,   128,     4,     4,     4,     4,   161,
       4,   131,   131,     4,     4,     4,   129,   129,   129,   129,
       4,     4,     4,     4,     4,     4,     4,     4,   129,     4,
       4,   167,     4,     4,   177,    58,   157,   199,   287,   327,
     329,   331,   355,   356,   357,   358,   359,     4,     4,     4,
       4,     4,     4,     4,   129,   131,     4,     4,     4,     4,
     245,     4,   313,     4,     4,     4,     4,     4,     4,     4,
       4,     4,   326,     4,     4,   129,     4,     4,     4,   131,
     274,     4,   131,   297,     4,     4,   221,   131,     4,     4,
     129,     4,   129,   129,     4,     4,   131,   131,   131,   131,
       4,     4,   384,     4,     7,     7,   145,   145,     7,   128,
       7,     7,     5,     5,     5,     5,     5,     5,     7,     7,
       7,     7,     5,   153,    14,    15,   184,   360,     8,     3,
     128,   128,   128,     5,   128,   128,   128,   128,   128,     5,
       7,   128,   128,   128,   153,   128,   128,   128,   128,   128,
     128,   128,   128,   128,   128,   128,   128,   128,   145,   128,
     128,   128,    15,   103,   397,   104,   105,   106,   107,   108,
     131,   406,   128,   145,   166,   110,   415,   416,   417,   176,
      24,    25,    26,    27,    28,    29,   157,   189,   190,   191,
     193,   195,   197,   199,   201,   202,   203,   189,     7,   238,
     239,   240,     7,   266,   267,   268,     7,   289,   290,   291,
      61,    62,    63,    64,   204,   207,   208,   209,   210,   211,
     258,   353,     7,   214,   215,   216,    72,    73,    74,    75,
      76,    77,   228,   229,   230,   231,   232,   233,   234,   235,
      79,    80,    81,    82,   157,   191,   201,   363,   364,   365,
     366,   368,   369,    85,    86,   373,   374,   375,   377,   383,
     154,     4,   357,     7,   306,   307,   308,     7,   318,   319,
     320,    67,   349,     8,   418,     3,     8,     8,   194,   196,
     198,     4,     4,     4,     3,     8,     8,   241,     6,     3,
     269,     6,     3,   292,     6,     3,     3,     6,     3,     6,
     217,     6,     3,     4,     4,     4,     4,     4,     4,     3,
       8,   367,     4,     4,     4,     3,     8,   376,   378,     3,
       8,     8,   155,   128,   309,     6,     3,   321,     6,     3,
     350,     8,     4,   416,     4,     4,     4,   131,   129,   131,
     190,   244,   240,   272,   268,   295,   291,   208,   258,   220,
     216,   129,   129,   129,   129,   129,   129,   229,     4,   129,
     129,   129,   364,     4,     4,   374,     6,   312,   308,   324,
     320,     4,     5,   128,   128,   128,     8,     8,     8,     8,
     128,   128,   128,     8,     8,   128,     7,   419,   420,   421,
       3,     6,   111,   113,   114,   157,   199,   422,   423,   424,
     425,   427,   420,   428,     4,   426,     3,     8,     4,   129,
       4,   423,     5,   128,     7,   429,   430,   431,     3,     6,
     112,   432,   433,   430,   434,     3,     8,     4,   433,   128
  };

  const unsigned short int
  Dhcp4Parser::yyr1_[] =
  {
       0,   132,   134,   133,   135,   133,   136,   133,   137,   133,
     138,   133,   139,   133,   140,   133,   141,   133,   142,   133,
     143,   133,   144,   133,   145,   145,   145,   145,   145,   145,
     145,   146,   148,   147,   149,   149,   150,   150,   152,   151,
     154,   153,   155,   155,   156,   156,   157,   159,   158,   160,
     160,   161,   161,   161,   161,   161,   163,   162,   165,   164,
     166,   166,   167,   167,   167,   167,   167,   167,   167,   167,
     167,   167,   167,   167,   167,   167,   167,   167,   167,   167,
     167,   167,   167,   167,   168,   169,   170,   171,   172,   173,
     175,   174,   176,   176,   177,   177,   179,   178,   181,   180,
     183,   182,   184,   184,   186,   185,   188,   187,   189,   189,
     190,   190,   190,   190,   190,   190,   190,   190,   190,   192,
     191,   194,   193,   196,   195,   198,   197,   200,   199,   201,
     202,   203,   204,   206,   205,   207,   207,   208,   208,   208,
     208,   209,   210,   211,   213,   212,   214,   214,   215,   215,
     217,   216,   219,   218,   220,   220,   220,   221,   221,   223,
     222,   225,   224,   227,   226,   228,   228,   229,   229,   229,
     229,   229,   229,   230,   231,   232,   233,   234,   235,   237,
     236,   238,   238,   239,   239,   241,   240,   243,   242,   244,
     244,   245,   245,   245,   245,   245,   245,   245,   245,   245,
     245,   245,   245,   245,   245,   245,   245,   245,   245,   245,
     245,   247,   246,   249,   248,   251,   250,   253,   252,   255,
     254,   257,   256,   259,   258,   261,   260,   262,   263,   265,
     264,   266,   266,   267,   267,   269,   268,   271,   270,   272,
     272,   273,   273,   274,   274,   274,   274,   274,   274,   274,
     274,   275,   276,   277,   278,   280,   279,   282,   281,   283,
     285,   284,   286,   288,   287,   289,   289,   290,   290,   292,
     291,   294,   293,   295,   295,   296,   296,   297,   297,   297,
     297,   297,   297,   298,   300,   299,   301,   302,   303,   305,
     304,   306,   306,   307,   307,   309,   308,   311,   310,   312,
     312,   313,   313,   313,   315,   314,   317,   316,   318,   318,
     319,   319,   321,   320,   323,   322,   324,   324,   325,   325,
     326,   326,   326,   326,   326,   326,   326,   326,   326,   326,
     326,   326,   328,   327,   330,   329,   332,   331,   334,   333,
     336,   335,   338,   337,   340,   339,   342,   341,   344,   343,
     346,   345,   348,   347,   350,   349,   352,   351,   353,   353,
     354,   258,   355,   355,   356,   356,   357,   357,   357,   357,
     357,   357,   357,   358,   360,   359,   362,   361,   363,   363,
     364,   364,   364,   364,   364,   364,   364,   365,   367,   366,
     368,   369,   370,   372,   371,   373,   373,   374,   374,   376,
     375,   378,   377,   380,   379,   382,   381,   383,   383,   384,
     384,   384,   384,   384,   384,   384,   384,   384,   384,   384,
     384,   384,   384,   384,   384,   385,   387,   386,   389,   388,
     390,   392,   391,   393,   394,   396,   395,   397,   397,   399,
     398,   400,   401,   402,   403,   405,   404,   406,   406,   406,
     406,   406,   408,   407,   410,   409,   412,   411,   414,   413,
     415,   415,   416,   418,   417,   419,   419,   421,   420,   422,
     422,   423,   423,   423,   423,   423,   424,   426,   425,   428,
     427,   429,   429,   431,   430,   432,   432,   434,   433
  };

  const unsigned char
  Dhcp4Parser::yyr2_[] =
  {
       0,     2,     0,     3,     0,     3,     0,     3,     0,     3,
       0,     3,     0,     3,     0,     3,     0,     3,     0,     3,
       0,     3,     0,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     0,     4,     0,     1,     3,     5,     0,     4,
       0,     4,     0,     1,     1,     3,     2,     0,     4,     1,
       3,     1,     1,     1,     1,     1,     0,     6,     0,     4,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     3,     3,     3,     3,     3,     3,
       0,     6,     1,     3,     1,     1,     0,     4,     0,     4,
       0,     4,     1,     1,     0,     6,     0,     6,     1,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     4,     3,
       3,     3,     1,     0,     6,     1,     3,     1,     1,     1,
       1,     1,     1,     1,     0,     6,     0,     1,     1,     3,
       0,     4,     0,     4,     1,     3,     1,     1,     1,     0,
       4,     0,     4,     0,     6,     1,     3,     1,     1,     1,
       1,     1,     1,     3,     3,     3,     3,     3,     3,     0,
       6,     0,     1,     1,     3,     0,     4,     0,     4,     1,
       3,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     4,     3,     3,     0,
       6,     0,     1,     1,     3,     0,     4,     0,     4,     0,
       1,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     3,     1,     1,     0,     4,     0,     4,     1,
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
       1,     1,     1,     1,     0,     4,     0,     6,     1,     3,
       1,     1,     1,     1,     1,     1,     1,     3,     0,     4,
       3,     3,     3,     0,     6,     1,     3,     1,     1,     0,
       4,     0,     4,     0,     6,     0,     4,     1,     3,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     3,     0,     4,     0,     4,
       3,     0,     4,     3,     3,     0,     4,     1,     1,     0,
       4,     3,     3,     3,     3,     0,     4,     1,     1,     1,
       1,     1,     0,     4,     0,     4,     0,     4,     0,     6,
       1,     3,     1,     0,     6,     1,     3,     0,     4,     1,
       3,     1,     1,     1,     1,     1,     3,     0,     4,     0,
       6,     1,     3,     0,     4,     1,     3,     0,     4
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
  "\"lease-database\"", "\"hosts-database\"", "\"type\"", "\"user\"",
  "\"password\"", "\"host\"", "\"persist\"", "\"lfc-interval\"",
  "\"readonly\"", "\"valid-lifetime\"", "\"renew-timer\"",
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
  "\"unwarned-reclaim-cycles\"", "\"server-id\"", "\"identifier\"",
  "\"htype\"", "\"time\"", "\"enterprise-id\"", "\"dhcp4o6-port\"",
  "\"control-socket\"", "\"socket-type\"", "\"socket-name\"",
  "\"dhcp-ddns\"", "\"enable-updates\"", "\"qualifying-suffix\"",
  "\"server-ip\"", "\"server-port\"", "\"sender-ip\"", "\"sender-port\"",
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
  "$@12", "map_content", "not_empty_map", "list_generic", "$@13", "list2",
  "$@14", "list_content", "not_empty_list", "unknown_map_entry",
  "syntax_map", "$@15", "global_objects", "global_object", "dhcp4_object",
  "$@16", "sub_dhcp4", "$@17", "global_params", "global_param",
  "valid_lifetime", "renew_timer", "rebind_timer",
  "decline_probation_period", "echo_client_id", "match_client_id",
  "interfaces_config", "$@18", "interfaces_config_params",
  "interfaces_config_param", "sub_interfaces4", "$@19", "interfaces_list",
  "$@20", "dhcp_socket_type", "$@21", "socket_type", "lease_database",
  "$@22", "hosts_database", "$@23", "database_map_params",
  "database_map_param", "type", "$@24", "user", "$@25", "password", "$@26",
  "host", "$@27", "name", "$@28", "persist", "lfc_interval", "readonly",
  "duid_id", "host_reservation_identifiers", "$@29",
  "host_reservation_identifiers_list", "host_reservation_identifier",
  "hw_address_id", "circuit_id", "client_id", "hooks_libraries", "$@30",
  "hooks_libraries_list", "not_empty_hooks_libraries_list",
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
  "option_def_name", "code", "option_def_code", "option_def_type",
  "option_def_record_types", "$@50", "space", "$@51", "option_def_space",
  "option_def_encapsulate", "$@52", "option_def_array", "option_data_list",
  "$@53", "option_data_list_content", "not_empty_option_data_list",
  "option_data_entry", "$@54", "sub_option_data", "$@55",
  "option_data_params", "not_empty_option_data_params",
  "option_data_param", "option_data_name", "option_data_data", "$@56",
  "option_data_code", "option_data_space", "option_data_csv_format",
  "pools_list", "$@57", "pools_list_content", "not_empty_pools_list",
  "pool_list_entry", "$@58", "sub_pool4", "$@59", "pool_params",
  "pool_param", "pool_entry", "$@60", "reservations", "$@61",
  "reservations_list", "not_empty_reservations_list", "reservation",
  "$@62", "sub_reservation", "$@63", "reservation_params",
  "not_empty_reservation_params", "reservation_param", "next_server",
  "$@64", "server_hostname", "$@65", "boot_file_name", "$@66",
  "ip_address", "$@67", "duid", "$@68", "hw_address", "$@69",
  "client_id_value", "$@70", "circuit_id_value", "$@71", "hostname",
  "$@72", "reservation_client_classes", "$@73", "relay", "$@74",
  "relay_map", "$@75", "client_classes", "$@76", "client_classes_list",
  "$@77", "client_class_params", "not_empty_client_class_params",
  "client_class_param", "client_class_name", "client_class_test", "$@78",
  "server_id", "$@79", "server_id_params", "server_id_param", "htype",
  "identifier", "$@80", "time", "enterprise_id", "dhcp4o6_port",
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
       0,   211,   211,   211,   212,   212,   213,   213,   214,   214,
     215,   215,   216,   216,   217,   217,   218,   218,   219,   219,
     220,   220,   221,   221,   229,   230,   231,   232,   233,   234,
     235,   238,   243,   243,   255,   256,   259,   263,   270,   270,
     278,   278,   285,   286,   289,   293,   304,   314,   314,   326,
     327,   331,   332,   333,   334,   335,   338,   338,   355,   355,
     363,   364,   369,   370,   371,   372,   373,   374,   375,   376,
     377,   378,   379,   380,   381,   382,   383,   384,   385,   386,
     387,   388,   389,   390,   393,   398,   403,   408,   413,   418,
     424,   424,   434,   435,   438,   439,   442,   442,   450,   450,
     460,   460,   467,   468,   471,   471,   481,   481,   491,   492,
     495,   496,   497,   498,   499,   500,   501,   502,   503,   506,
     506,   514,   514,   522,   522,   530,   530,   538,   538,   546,
     551,   556,   561,   566,   566,   576,   577,   580,   581,   582,
     583,   586,   591,   596,   601,   601,   611,   612,   615,   616,
     619,   619,   627,   627,   635,   636,   637,   640,   641,   644,
     644,   652,   652,   660,   660,   670,   671,   674,   675,   676,
     677,   678,   679,   682,   687,   692,   697,   702,   707,   715,
     715,   728,   729,   732,   733,   740,   740,   763,   763,   772,
     773,   777,   778,   779,   780,   781,   782,   783,   784,   785,
     786,   787,   788,   789,   790,   791,   792,   793,   794,   795,
     796,   799,   799,   807,   807,   815,   815,   823,   823,   831,
     831,   839,   839,   847,   847,   855,   855,   863,   868,   877,
     877,   889,   890,   893,   894,   899,   899,   910,   910,   920,
     921,   924,   925,   928,   929,   930,   931,   932,   933,   934,
     935,   938,   940,   945,   947,   949,   949,   957,   957,   965,
     967,   967,   975,   984,   984,   996,   997,  1002,  1003,  1008,
    1008,  1019,  1019,  1030,  1031,  1036,  1037,  1042,  1043,  1044,
    1045,  1046,  1047,  1050,  1052,  1052,  1060,  1062,  1064,  1072,
    1072,  1084,  1085,  1088,  1089,  1092,  1092,  1100,  1100,  1108,
    1109,  1112,  1113,  1114,  1117,  1117,  1128,  1128,  1138,  1139,
    1142,  1143,  1146,  1146,  1154,  1154,  1162,  1163,  1166,  1167,
    1171,  1172,  1173,  1174,  1175,  1176,  1177,  1178,  1179,  1180,
    1181,  1182,  1185,  1185,  1193,  1193,  1201,  1201,  1209,  1209,
    1217,  1217,  1225,  1225,  1233,  1233,  1241,  1241,  1250,  1250,
    1258,  1258,  1271,  1271,  1281,  1281,  1292,  1292,  1302,  1303,
    1306,  1306,  1314,  1315,  1318,  1319,  1322,  1323,  1324,  1325,
    1326,  1327,  1328,  1331,  1333,  1333,  1344,  1344,  1354,  1355,
    1358,  1359,  1360,  1361,  1362,  1363,  1364,  1367,  1372,  1372,
    1380,  1385,  1392,  1399,  1399,  1409,  1410,  1413,  1414,  1417,
    1417,  1425,  1425,  1435,  1435,  1445,  1445,  1453,  1454,  1457,
    1458,  1459,  1460,  1461,  1462,  1463,  1464,  1465,  1466,  1467,
    1468,  1469,  1470,  1471,  1472,  1475,  1480,  1480,  1488,  1488,
    1496,  1501,  1501,  1509,  1514,  1519,  1519,  1527,  1528,  1531,
    1531,  1539,  1544,  1549,  1554,  1559,  1559,  1567,  1570,  1573,
    1576,  1579,  1585,  1585,  1595,  1595,  1602,  1602,  1614,  1614,
    1627,  1628,  1632,  1636,  1636,  1648,  1649,  1653,  1653,  1661,
    1662,  1665,  1666,  1667,  1668,  1669,  1672,  1676,  1676,  1684,
    1684,  1694,  1695,  1698,  1698,  1706,  1707,  1710,  1710
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
#line 3951 "dhcp4_parser.cc" // lalr1.cc:1167
#line 1718 "dhcp4_parser.yy" // lalr1.cc:1168


void
isc::dhcp::Dhcp4Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
