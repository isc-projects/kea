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
      case 138: // value
      case 383: // ncr_protocol_value
      case 392: // replace_client_name_value
        value.move< ElementPtr > (that.value);
        break;

      case 124: // "boolean"
        value.move< bool > (that.value);
        break;

      case 123: // "floating point"
        value.move< double > (that.value);
        break;

      case 122: // "integer"
        value.move< int64_t > (that.value);
        break;

      case 121: // "constant string"
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
      case 138: // value
      case 383: // ncr_protocol_value
      case 392: // replace_client_name_value
        value.copy< ElementPtr > (that.value);
        break;

      case 124: // "boolean"
        value.copy< bool > (that.value);
        break;

      case 123: // "floating point"
        value.copy< double > (that.value);
        break;

      case 122: // "integer"
        value.copy< int64_t > (that.value);
        break;

      case 121: // "constant string"
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
            case 121: // "constant string"

#line 194 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< std::string > (); }
#line 356 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 122: // "integer"

#line 194 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< int64_t > (); }
#line 363 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 123: // "floating point"

#line 194 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< double > (); }
#line 370 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 124: // "boolean"

#line 194 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< bool > (); }
#line 377 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 138: // value

#line 194 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 384 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 383: // ncr_protocol_value

#line 194 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 391 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 392: // replace_client_name_value

#line 194 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 398 "dhcp4_parser.cc" // lalr1.cc:636
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
      case 138: // value
      case 383: // ncr_protocol_value
      case 392: // replace_client_name_value
        yylhs.value.build< ElementPtr > ();
        break;

      case 124: // "boolean"
        yylhs.value.build< bool > ();
        break;

      case 123: // "floating point"
        yylhs.value.build< double > ();
        break;

      case 122: // "integer"
        yylhs.value.build< int64_t > ();
        break;

      case 121: // "constant string"
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
#line 203 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.NO_KEYWORD; }
#line 640 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 4:
#line 204 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.CONFIG; }
#line 646 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 6:
#line 205 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.DHCP4; }
#line 652 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 8:
#line 206 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.INTERFACES_CONFIG; }
#line 658 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 10:
#line 207 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.SUBNET4; }
#line 664 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 12:
#line 208 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.POOLS; }
#line 670 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 14:
#line 209 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.RESERVATIONS; }
#line 676 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 16:
#line 210 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.OPTION_DEF; }
#line 682 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 18:
#line 211 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.OPTION_DATA; }
#line 688 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 20:
#line 212 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.HOOKS_LIBRARIES; }
#line 694 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 22:
#line 213 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.DHCP_DDNS; }
#line 700 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 24:
#line 221 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 706 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 25:
#line 222 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as< double > (), ctx.loc2pos(yystack_[0].location))); }
#line 712 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 26:
#line 223 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 718 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 27:
#line 224 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 724 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 28:
#line 225 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 730 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 29:
#line 226 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 736 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 30:
#line 227 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 742 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 31:
#line 230 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as< ElementPtr > ());
}
#line 751 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 32:
#line 235 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 762 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 33:
#line 240 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 772 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 36:
#line 251 "dhcp4_parser.yy" // lalr1.cc:859
    {
                  // map containing a single entry
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 781 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 37:
#line 255 "dhcp4_parser.yy" // lalr1.cc:859
    {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 791 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 38:
#line 262 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 800 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 39:
#line 265 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // list parsing complete. Put any sanity checking here
}
#line 808 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 40:
#line 270 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // List parsing about to start
}
#line 816 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 41:
#line 272 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // list parsing complete. Put any sanity checking here
    //ctx.stack_.pop_back();
}
#line 825 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 44:
#line 281 "dhcp4_parser.yy" // lalr1.cc:859
    {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 834 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 45:
#line 285 "dhcp4_parser.yy" // lalr1.cc:859
    {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 843 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 46:
#line 296 "dhcp4_parser.yy" // lalr1.cc:859
    {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as< std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 854 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 47:
#line 306 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 865 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 48:
#line 311 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 875 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 56:
#line 330 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Dhcp4", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP4);
}
#line 888 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 57:
#line 337 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 900 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 58:
#line 347 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the Dhcp4 map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 910 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 59:
#line 351 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 918 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 84:
#line 385 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 927 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 85:
#line 390 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 936 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 86:
#line 395 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 945 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 87:
#line 400 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr dpp(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 954 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 88:
#line 405 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr echo(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("echo-client-id", echo);
}
#line 963 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 89:
#line 410 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr match(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("match-client-id", match);
}
#line 972 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 90:
#line 416 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces-config", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.INTERFACES_CONFIG);
}
#line 983 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 91:
#line 421 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 992 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 96:
#line 434 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1002 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 97:
#line 438 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1010 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 98:
#line 442 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1021 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 99:
#line 447 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1030 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 100:
#line 452 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1038 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 101:
#line 454 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr type(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-socket-type", type);
    ctx.leave();
}
#line 1048 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 102:
#line 460 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lease-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.LEASE_DATABASE);
}
#line 1059 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 103:
#line 465 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1068 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 104:
#line 470 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1079 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 105:
#line 475 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1088 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 117:
#line 495 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1096 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 118:
#line 497 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 1106 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 119:
#line 503 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1114 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 120:
#line 505 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr user(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1124 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 121:
#line 511 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1132 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 122:
#line 513 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr pwd(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 1142 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 123:
#line 519 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1150 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 124:
#line 521 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr h(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 1160 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 125:
#line 527 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1168 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 126:
#line 529 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1178 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 127:
#line 535 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 1187 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 128:
#line 540 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 1196 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 129:
#line 545 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 1205 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 130:
#line 550 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1214 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 131:
#line 555 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 1225 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 132:
#line 560 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1234 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 139:
#line 575 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 1243 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 140:
#line 580 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr circuit(new StringElement("circuit-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(circuit);
}
#line 1252 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 141:
#line 585 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr client(new StringElement("client-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(client);
}
#line 1261 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 142:
#line 590 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 1272 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 143:
#line 595 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1281 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 148:
#line 608 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1291 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 149:
#line 612 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1299 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 150:
#line 616 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1309 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 151:
#line 620 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1317 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 157:
#line 633 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1325 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 158:
#line 635 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr lib(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 1335 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 159:
#line 641 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1343 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 160:
#line 643 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1352 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 161:
#line 649 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1363 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 162:
#line 654 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1372 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 165:
#line 666 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), value);
}
#line 1381 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 166:
#line 674 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet4", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET4);
}
#line 1392 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 167:
#line 679 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1401 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 172:
#line 699 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1411 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 173:
#line 703 "dhcp4_parser.yy" // lalr1.cc:859
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
#line 1434 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 174:
#line 722 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the subnet4 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1444 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 175:
#line 726 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1452 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 198:
#line 758 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1460 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 199:
#line 760 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr subnet(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 1470 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 200:
#line 766 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1478 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 201:
#line 768 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface", iface);
    ctx.leave();
}
#line 1488 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 202:
#line 774 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1496 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 203:
#line 776 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface-id", iface);
    ctx.leave();
}
#line 1506 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 204:
#line 782 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1514 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 205:
#line 784 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-subnet", iface);
    ctx.leave();
}
#line 1524 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 206:
#line 790 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1532 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 207:
#line 792 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 1542 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 208:
#line 798 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1550 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 209:
#line 800 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface-id", iface);
    ctx.leave();
}
#line 1560 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 210:
#line 806 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.CLIENT_CLASS);
}
#line 1568 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 211:
#line 808 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr cls(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 1578 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 212:
#line 814 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1586 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 213:
#line 816 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr rm(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservation-mode", rm);
    ctx.leave();
}
#line 1596 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 214:
#line 822 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr id(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 1605 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 215:
#line 827 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr rc(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rapid-commit", rc);
}
#line 1614 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 216:
#line 836 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 1625 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 217:
#line 841 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1634 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 222:
#line 858 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1644 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 223:
#line 862 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1652 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 224:
#line 869 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1662 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 225:
#line 873 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1670 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 239:
#line 899 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr code(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 1679 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 242:
#line 908 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1687 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 243:
#line 910 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 1697 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 244:
#line 916 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1705 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 245:
#line 918 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr space(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 1715 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 247:
#line 926 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1723 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 248:
#line 928 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr encap(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 1733 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 249:
#line 934 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr array(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 1742 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 250:
#line 943 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 1753 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 251:
#line 948 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1762 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 256:
#line 967 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1772 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 257:
#line 971 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1780 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 258:
#line 978 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1790 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 259:
#line 982 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1798 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 271:
#line 1011 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1806 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 272:
#line 1013 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr data(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 1816 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 275:
#line 1023 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr space(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", space);
}
#line 1825 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 276:
#line 1031 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 1836 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 277:
#line 1036 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1845 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 282:
#line 1051 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1855 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 283:
#line 1055 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1863 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 284:
#line 1059 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1873 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 285:
#line 1063 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1881 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 291:
#line 1076 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1889 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 292:
#line 1078 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr pool(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 1899 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 293:
#line 1087 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 1910 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 294:
#line 1092 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1919 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 299:
#line 1105 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1929 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 300:
#line 1109 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1937 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 301:
#line 1113 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1947 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 302:
#line 1117 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1955 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 319:
#line 1144 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1963 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 320:
#line 1146 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr next_server(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("next-server", next_server);
    ctx.leave();
}
#line 1973 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 321:
#line 1152 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1981 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 322:
#line 1154 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr srv(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-hostname", srv);
    ctx.leave();
}
#line 1991 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 323:
#line 1160 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1999 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 324:
#line 1162 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr bootfile(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("boot-file-name", bootfile);
    ctx.leave();
}
#line 2009 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 325:
#line 1168 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2017 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 326:
#line 1170 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr addr(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", addr);
    ctx.leave();
}
#line 2027 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 327:
#line 1176 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2035 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 328:
#line 1178 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr d(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 2045 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 329:
#line 1184 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2053 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 330:
#line 1186 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 2063 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 331:
#line 1192 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2071 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 332:
#line 1194 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-id", hw);
    ctx.leave();
}
#line 2081 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 333:
#line 1200 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2089 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 334:
#line 1202 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("circuit-id", hw);
    ctx.leave();
}
#line 2099 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 335:
#line 1209 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2107 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 336:
#line 1211 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr host(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 2117 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 337:
#line 1217 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2128 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 338:
#line 1222 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2137 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 339:
#line 1230 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 2148 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 340:
#line 1235 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2157 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 341:
#line 1240 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2165 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 342:
#line 1242 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr ip(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", ip);
    ctx.leave();
}
#line 2175 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 343:
#line 1251 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 2186 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 344:
#line 1256 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2195 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 347:
#line 1265 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2205 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 348:
#line 1269 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2213 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 361:
#line 1292 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2221 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 362:
#line 1294 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr test(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 2231 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 363:
#line 1303 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-id", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SERVER_ID);
}
#line 2242 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 364:
#line 1308 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2251 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 374:
#line 1326 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr htype(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("htype", htype);
}
#line 2260 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 375:
#line 1331 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2268 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 376:
#line 1333 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr id(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("identifier", id);
    ctx.leave();
}
#line 2278 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 377:
#line 1339 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("time", time);
}
#line 2287 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 378:
#line 1344 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enterprise-id", time);
}
#line 2296 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 379:
#line 1351 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 2305 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 380:
#line 1358 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 2316 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 381:
#line 1363 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2325 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 386:
#line 1376 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2333 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 387:
#line 1378 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr stype(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 2343 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 388:
#line 1384 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2351 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 389:
#line 1386 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 2361 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 390:
#line 1394 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 2372 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 391:
#line 1399 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2381 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 392:
#line 1404 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2391 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 393:
#line 1408 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 2399 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 412:
#line 1434 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 2408 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 413:
#line 1439 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2416 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 414:
#line 1441 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("qualifying-suffix", s);
    ctx.leave();
}
#line 2426 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 415:
#line 1447 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2434 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 416:
#line 1449 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 2444 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 417:
#line 1455 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 2453 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 418:
#line 1460 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2461 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 419:
#line 1462 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 2471 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 420:
#line 1468 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 2480 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 421:
#line 1473 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 2489 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 422:
#line 1478 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 2497 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 423:
#line 1480 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2506 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 424:
#line 1486 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 2512 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 425:
#line 1487 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 2518 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 426:
#line 1490 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NCR_FORMAT);
}
#line 2526 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 427:
#line 1492 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 2536 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 428:
#line 1498 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-include-fqdn", b);
}
#line 2545 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 429:
#line 1503 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("allow-client-update",  b);
}
#line 2554 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 430:
#line 1508 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-no-update", b);
}
#line 2563 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 431:
#line 1513 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-client-update", b);
}
#line 2572 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 432:
#line 1518 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 2580 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 433:
#line 1520 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("replace-client-name", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2589 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 434:
#line 1526 "dhcp4_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("when-present", ctx.loc2pos(yystack_[0].location))); 
      }
#line 2597 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 435:
#line 1529 "dhcp4_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location)));
      }
#line 2605 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 436:
#line 1532 "dhcp4_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("always", ctx.loc2pos(yystack_[0].location)));
      }
#line 2613 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 437:
#line 1535 "dhcp4_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("when-not-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 2621 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 438:
#line 1538 "dhcp4_parser.yy" // lalr1.cc:859
    {
      error(yystack_[0].location, "boolean values for the replace-client-name are "
                "no longer supported");
      }
#line 2630 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 439:
#line 1544 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2638 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 440:
#line 1546 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("generated-prefix", s);
    ctx.leave();
}
#line 2648 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 441:
#line 1554 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2656 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 442:
#line 1556 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("Dhcp6", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2665 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 443:
#line 1561 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2673 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 444:
#line 1563 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("DhcpDdns", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2682 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 445:
#line 1573 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Logging", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.LOGGING);
}
#line 2693 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 446:
#line 1578 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2702 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 450:
#line 1595 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 2713 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 451:
#line 1600 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2722 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 454:
#line 1612 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 2732 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 455:
#line 1616 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2740 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 463:
#line 1631 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr dl(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 2749 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 464:
#line 1635 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2757 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 465:
#line 1637 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 2767 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 466:
#line 1643 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 2778 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 467:
#line 1648 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2787 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 470:
#line 1657 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2797 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 471:
#line 1661 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2805 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 474:
#line 1669 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2813 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 475:
#line 1671 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 2823 "dhcp4_parser.cc" // lalr1.cc:859
    break;


#line 2827 "dhcp4_parser.cc" // lalr1.cc:859
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


  const short int Dhcp4Parser::yypact_ninf_ = -476;

  const signed char Dhcp4Parser::yytable_ninf_ = -1;

  const short int
  Dhcp4Parser::yypact_[] =
  {
     107,  -476,  -476,  -476,  -476,  -476,  -476,  -476,  -476,  -476,
    -476,  -476,    58,    23,    69,   108,   128,   149,   153,   155,
     166,   223,   246,   247,  -476,  -476,  -476,  -476,  -476,  -476,
    -476,  -476,  -476,  -476,  -476,  -476,  -476,  -476,  -476,  -476,
    -476,  -476,  -476,  -476,  -476,  -476,  -476,  -476,  -476,  -476,
    -476,  -476,  -476,  -476,  -476,  -476,    23,    21,    19,    82,
      39,    20,    28,    44,    42,    50,   -21,   158,  -476,   180,
     233,   257,   254,   260,  -476,  -476,  -476,  -476,   261,  -476,
      30,  -476,  -476,  -476,  -476,  -476,  -476,   262,   264,  -476,
    -476,  -476,   265,   266,   269,   271,  -476,  -476,  -476,  -476,
    -476,  -476,  -476,  -476,   272,  -476,  -476,  -476,    56,  -476,
    -476,  -476,  -476,  -476,  -476,  -476,  -476,  -476,  -476,  -476,
    -476,  -476,  -476,  -476,  -476,  -476,  -476,  -476,  -476,  -476,
    -476,  -476,  -476,    71,  -476,  -476,  -476,  -476,  -476,  -476,
    -476,  -476,  -476,  -476,  -476,   274,   276,  -476,  -476,  -476,
    -476,  -476,  -476,  -476,  -476,  -476,   121,  -476,  -476,  -476,
    -476,  -476,  -476,  -476,  -476,  -476,  -476,  -476,  -476,  -476,
    -476,  -476,  -476,  -476,  -476,  -476,   122,  -476,  -476,  -476,
    -476,  -476,  -476,  -476,  -476,  -476,  -476,  -476,  -476,  -476,
     256,   279,  -476,  -476,  -476,  -476,  -476,  -476,  -476,  -476,
    -476,  -476,  -476,  -476,  -476,   282,  -476,  -476,  -476,   283,
    -476,  -476,  -476,   275,   285,  -476,  -476,  -476,  -476,  -476,
    -476,  -476,  -476,  -476,  -476,  -476,   291,  -476,  -476,  -476,
    -476,   293,   296,  -476,  -476,  -476,  -476,  -476,  -476,  -476,
    -476,  -476,   123,  -476,  -476,  -476,   299,  -476,  -476,   300,
    -476,   301,   302,  -476,  -476,   303,   305,   307,   308,  -476,
    -476,  -476,   135,  -476,  -476,  -476,  -476,  -476,  -476,  -476,
    -476,  -476,  -476,  -476,  -476,  -476,  -476,  -476,  -476,  -476,
      23,    23,  -476,   194,   309,   310,   312,   313,  -476,    19,
    -476,   314,   195,   196,   317,   319,   320,   203,   204,   206,
     207,   323,   326,   327,   328,   329,   330,   331,   332,   215,
     334,   335,    82,  -476,   336,   337,    39,  -476,   116,   338,
     339,   340,   341,   342,   343,   344,   227,   228,   346,   347,
     349,   350,    20,  -476,   351,    28,  -476,   352,   353,   354,
     355,   356,   357,   358,   359,   360,  -476,    44,   361,   362,
     245,   364,   365,   366,   248,  -476,    42,   367,   249,  -476,
      50,   370,   371,    27,  -476,   252,   373,   374,   258,   375,
     259,   263,   378,   379,   267,   268,   270,   273,   380,   382,
     158,  -476,  -476,  -476,   383,   381,   386,    23,    23,  -476,
     388,  -476,  -476,   277,   389,   392,  -476,  -476,  -476,  -476,
     384,   385,   397,   398,   399,   400,   401,   402,  -476,   403,
     404,  -476,   407,   286,  -476,  -476,  -476,  -476,  -476,  -476,
    -476,  -476,   405,   411,  -476,  -476,  -476,   294,   295,   297,
     412,   298,   304,   315,  -476,  -476,   316,   318,   415,   414,
    -476,   321,  -476,   324,   325,   407,   333,   345,   348,   363,
     368,   369,  -476,   372,   376,  -476,   377,   387,   390,  -476,
    -476,   391,  -476,  -476,   393,    23,  -476,  -476,   394,   395,
    -476,   396,  -476,  -476,   103,   406,  -476,  -476,  -476,  -476,
      80,   408,  -476,    23,    82,   410,  -476,  -476,    39,  -476,
      18,    18,   416,   417,   419,   197,    60,   422,   409,    95,
      45,   158,  -476,  -476,  -476,   418,  -476,   116,  -476,  -476,
    -476,   423,  -476,  -476,  -476,  -476,  -476,   424,   420,  -476,
    -476,  -476,  -476,  -476,  -476,  -476,  -476,  -476,  -476,  -476,
    -476,  -476,  -476,  -476,  -476,  -476,  -476,  -476,  -476,  -476,
    -476,  -476,  -476,  -476,  -476,  -476,  -476,  -476,  -476,  -476,
    -476,  -476,   147,  -476,   156,  -476,  -476,   167,  -476,  -476,
    -476,   430,   431,   434,  -476,   179,  -476,  -476,  -476,  -476,
    -476,  -476,  -476,  -476,  -476,   181,  -476,   441,   437,  -476,
    -476,   442,   447,  -476,  -476,   445,   449,  -476,  -476,  -476,
    -476,  -476,  -476,    31,  -476,  -476,  -476,  -476,  -476,   208,
    -476,   451,   450,  -476,   454,   182,  -476,  -476,   455,   457,
     458,  -476,  -476,  -476,   185,  -476,  -476,  -476,  -476,  -476,
    -476,  -476,   189,  -476,  -476,  -476,   192,    23,   413,  -476,
    -476,   459,   452,  -476,  -476,   461,   460,  -476,  -476,   456,
    -476,   464,   410,  -476,  -476,   466,   467,   468,   421,   284,
     425,    18,  -476,  -476,    20,  -476,   416,    42,  -476,   417,
      50,  -476,   419,   197,  -476,    60,  -476,   -21,  -476,   422,
     426,   409,  -476,   469,   428,   429,   432,    95,  -476,   470,
     471,    45,  -476,  -476,   473,  -476,    28,  -476,   423,    44,
    -476,   424,   472,  -476,   475,  -476,   435,   436,   438,  -476,
    -476,  -476,  -476,   193,  -476,   474,  -476,   478,  -476,  -476,
    -476,   202,  -476,  -476,  -476,   439,  -476,  -476,  -476,  -476,
     440,   443,  -476,  -476,   205,  -476,   479,  -476,   444,   476,
    -476,  -476,  -476,  -476,  -476,  -476,  -476,  -476,  -476,  -476,
    -476,  -476,  -476,  -476,   209,  -476,    70,   476,  -476,  -476,
     477,  -476,  -476,  -476,   225,  -476,  -476,  -476,  -476,  -476,
     484,   433,   487,    70,  -476,   489,  -476,   446,  -476,   485,
    -476,  -476,   229,  -476,   427,   485,  -476,  -476,   226,  -476,
    -476,   491,   427,  -476,   448,  -476,  -476
  };

  const unsigned short int
  Dhcp4Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     1,    38,    32,    28,    27,    24,
      25,    26,    31,     3,    29,    30,    47,     5,    58,     7,
      96,     9,   174,    11,   284,    13,   301,    15,   224,    17,
     258,    19,   150,    21,   392,    23,    42,    34,     0,     0,
       0,     0,     0,   303,   226,   260,     0,     0,    44,     0,
      43,     0,     0,    35,    56,   445,   441,   443,     0,    55,
       0,    49,    51,    53,    54,    52,    90,     0,     0,   319,
     102,   104,     0,     0,     0,     0,   166,   216,   250,   131,
     343,   142,   161,   363,     0,   380,   390,    83,     0,    60,
      62,    63,    64,    65,    80,    81,    67,    68,    69,    70,
      74,    75,    66,    72,    73,    82,    71,    76,    77,    78,
      79,    98,   100,     0,    92,    94,    95,   347,   200,   202,
     204,   276,   198,   206,   208,     0,     0,   212,   210,   293,
     339,   197,   178,   179,   180,   192,     0,   176,   183,   194,
     195,   196,   184,   185,   188,   190,   186,   187,   181,   182,
     189,   193,   191,   291,   290,   289,     0,   286,   288,   321,
     323,   337,   327,   329,   333,   331,   335,   325,   318,   314,
       0,   304,   305,   315,   316,   317,   311,   307,   312,   309,
     310,   313,   308,   117,   125,     0,   244,   242,   247,     0,
     237,   241,   238,     0,   227,   228,   230,   240,   231,   232,
     233,   246,   234,   235,   236,   271,     0,   269,   270,   273,
     274,     0,   261,   262,   264,   265,   266,   267,   268,   157,
     159,   154,     0,   152,   155,   156,     0,   413,   415,     0,
     418,     0,     0,   422,   426,     0,     0,     0,     0,   432,
     439,   411,     0,   394,   396,   397,   398,   399,   400,   401,
     402,   403,   404,   405,   406,   407,   408,   409,   410,    39,
       0,     0,    33,     0,     0,     0,     0,     0,    46,     0,
      48,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    59,     0,     0,     0,    97,   349,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   175,     0,     0,   285,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   302,     0,     0,     0,
       0,     0,     0,     0,     0,   225,     0,     0,     0,   259,
       0,     0,     0,     0,   151,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   393,    45,    36,     0,     0,     0,     0,     0,    50,
       0,    88,    89,     0,     0,     0,    84,    85,    86,    87,
       0,     0,     0,     0,     0,     0,     0,     0,   379,     0,
       0,    61,     0,     0,    93,   361,   359,   360,   355,   356,
     357,   358,     0,   350,   351,   353,   354,     0,     0,     0,
       0,     0,     0,     0,   214,   215,     0,     0,     0,     0,
     177,     0,   287,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   306,     0,     0,   239,     0,     0,     0,   249,
     229,     0,   275,   263,     0,     0,   153,   412,     0,     0,
     417,     0,   420,   421,     0,     0,   428,   429,   430,   431,
       0,     0,   395,     0,     0,     0,   442,   444,     0,   320,
       0,     0,   168,   218,   252,     0,     0,   144,     0,     0,
       0,     0,    40,    99,   101,     0,   348,     0,   201,   203,
     205,   278,   199,   207,   209,   213,   211,   295,     0,   292,
     322,   324,   338,   328,   330,   334,   332,   336,   326,   118,
     126,   245,   243,   248,   272,   158,   160,   414,   416,   419,
     424,   425,   423,   427,   434,   435,   436,   437,   438,   433,
     440,    37,     0,   450,     0,   447,   449,     0,   119,   121,
     123,     0,     0,     0,   116,     0,   106,   108,   109,   110,
     111,   112,   113,   114,   115,     0,   172,     0,   169,   170,
     222,     0,   219,   220,   256,     0,   253,   254,   130,   139,
     140,   141,   135,     0,   133,   136,   137,   138,   345,     0,
     148,     0,   145,   146,     0,     0,   163,   375,     0,     0,
       0,   373,   367,   372,     0,   365,   370,   368,   369,   371,
     386,   388,     0,   382,   384,   385,     0,    42,     0,   352,
     282,     0,   279,   280,   299,     0,   296,   297,   341,     0,
      57,     0,     0,   446,    91,     0,     0,     0,     0,     0,
       0,     0,   103,   105,     0,   167,     0,   226,   217,     0,
     260,   251,     0,     0,   132,     0,   344,     0,   143,     0,
       0,     0,   162,     0,     0,     0,     0,     0,   364,     0,
       0,     0,   381,   391,     0,   362,     0,   277,     0,   303,
     294,     0,     0,   340,     0,   448,     0,     0,     0,   127,
     128,   129,   107,     0,   171,     0,   221,     0,   255,   134,
     346,     0,   147,   165,   164,     0,   374,   377,   378,   366,
       0,     0,   383,    41,     0,   281,     0,   298,     0,     0,
     120,   122,   124,   173,   223,   257,   149,   376,   387,   389,
     283,   300,   342,   454,     0,   452,     0,     0,   451,   466,
       0,   464,   462,   458,     0,   456,   460,   461,   459,   453,
       0,     0,     0,     0,   455,     0,   463,     0,   457,     0,
     465,   470,     0,   468,     0,     0,   467,   474,     0,   472,
     469,     0,     0,   471,     0,   473,   475
  };

  const short int
  Dhcp4Parser::yypgoto_[] =
  {
    -476,  -476,  -476,  -476,  -476,  -476,  -476,  -476,  -476,  -476,
    -476,  -476,  -476,    13,  -476,  -476,  -476,  -476,  -476,  -476,
    -476,    32,  -476,  -128,  -476,   -58,  -476,  -476,  -476,   211,
    -476,  -476,  -476,  -476,    17,   190,   -60,   -42,   -41,  -476,
    -476,   -40,  -476,  -476,    16,   191,  -476,  -476,  -476,  -476,
    -476,  -476,  -476,  -476,  -476,  -476,    14,  -145,  -468,  -476,
    -476,  -476,  -476,  -476,  -476,  -476,   -63,  -476,  -475,  -476,
    -476,  -476,  -476,  -476,  -476,  -154,  -476,  -476,  -476,  -476,
    -476,  -476,  -476,  -159,  -476,  -476,  -476,  -149,   157,  -476,
    -476,  -476,  -476,  -476,  -476,  -476,  -152,  -476,  -476,  -476,
    -476,  -135,  -476,  -476,  -476,  -132,   199,  -476,  -476,  -476,
    -476,  -476,  -476,  -476,  -476,  -476,  -476,  -476,  -476,  -471,
    -476,  -476,  -476,  -476,  -476,  -476,  -476,  -476,  -476,  -136,
    -476,  -476,  -476,  -133,  -476,   169,  -476,   -52,  -476,  -476,
    -476,  -476,   -50,  -476,  -476,  -476,  -476,  -476,   -51,  -476,
    -476,  -476,  -134,  -476,  -476,  -476,  -127,  -476,   175,  -476,
    -476,  -476,  -476,  -476,  -476,  -476,  -476,  -476,  -476,  -162,
    -476,  -476,  -476,  -150,   212,  -476,  -476,  -476,  -476,  -476,
    -476,  -164,  -476,  -476,  -476,  -151,  -476,   216,   -47,  -476,
    -301,  -476,  -300,  -476,  -476,  -476,  -476,  -476,  -476,  -476,
    -476,  -476,  -476,  -476,  -476,  -476,  -476,  -476,  -476,  -476,
    -476,  -476,  -476,  -476,  -476,  -476,  -476,  -476,    33,  -476,
    -476,  -476,  -476,  -476,  -476,  -140,  -476,  -476,  -476,  -476,
    -476,  -476,  -476,  -476,  -476,  -142,  -476,  -476,  -476,  -476,
    -476,  -476,  -476,  -476,    40,   162,  -476,  -476,  -476,  -476,
    -476,  -476,  -476,  -476,  -476,  -476,  -476,  -476,  -476,  -476,
    -476,  -476,  -476,  -476,  -476,  -476,  -476,  -476,  -476,  -476,
    -476,  -476,  -476,  -476,  -476,  -476,  -476,   -99,  -476,  -476,
    -476,  -203,  -476,  -476,  -217,  -476,  -476,  -476,  -476,  -476,
    -476,  -223,  -476,  -476,  -229,  -476
  };

  const short int
  Dhcp4Parser::yydefgoto_[] =
  {
      -1,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    68,    33,    34,    57,    72,    73,    35,
      56,   503,   627,    69,    70,   107,    37,    58,    80,    81,
      82,   284,    39,    59,   108,   109,   110,   111,   112,   113,
     114,   115,   116,   291,   133,   134,    41,    60,   135,   314,
     136,   315,   117,   295,   118,   296,   565,   566,   211,   348,
     568,   645,   569,   646,   570,   647,   212,   349,   572,   573,
     574,   592,   119,   304,   593,   594,   595,   596,   597,   120,
     306,   601,   602,   603,   667,    53,    66,   242,   243,   244,
     361,   245,   362,   121,   307,   605,   606,   122,   301,   577,
     578,   579,   654,    43,    61,   156,   157,   158,   323,   159,
     319,   160,   320,   161,   321,   162,   324,   163,   325,   164,
     329,   165,   328,   166,   167,   123,   302,   581,   582,   583,
     657,    49,    64,   213,   214,   215,   216,   217,   218,   219,
     220,   352,   221,   351,   222,   223,   353,   224,   124,   303,
     585,   586,   587,   660,    51,    65,   231,   232,   233,   234,
     235,   357,   236,   237,   238,   169,   322,   631,   632,   633,
     686,    45,    62,   176,   177,   178,   334,   170,   330,   635,
     636,   637,   689,    47,    63,   190,   191,   192,   125,   294,
     194,   337,   195,   338,   196,   345,   197,   340,   198,   341,
     199,   343,   200,   342,   201,   344,   202,   339,   172,   331,
     639,   692,   126,   305,   599,   318,   422,   423,   424,   425,
     426,   505,   127,   308,   614,   615,   616,   617,   673,   618,
     619,   128,   129,   310,   622,   623,   624,   679,   625,   680,
     130,   311,    55,    67,   262,   263,   264,   265,   366,   266,
     367,   267,   268,   369,   269,   270,   271,   372,   542,   272,
     373,   273,   274,   275,   276,   277,   378,   549,   278,   379,
      83,   286,    84,   287,    85,   285,   554,   555,   556,   641,
     744,   745,   746,   754,   755,   756,   757,   762,   758,   760,
     772,   773,   774,   778,   779,   781
  };

  const unsigned short int
  Dhcp4Parser::yytable_[] =
  {
      79,   152,   228,   151,   174,   188,   210,   227,   241,   261,
     168,   175,   189,   229,   171,   230,   193,   420,   421,   153,
     154,   155,   567,   567,   613,   598,    32,   137,    25,    74,
      26,   612,    27,   289,   663,    88,    89,   664,   290,   203,
     558,   559,   560,   561,   562,   563,   239,   240,    92,    93,
      94,   131,   132,   138,   139,   140,   204,    98,    24,   312,
      89,   179,   180,   203,   313,    98,   141,   137,   142,   143,
     144,   145,   146,   147,   316,   173,    36,   148,   149,   317,
     204,    98,   205,   206,   150,   207,   208,   209,   204,   225,
     205,   206,   226,    86,   239,   240,    87,    88,    89,   181,
      78,    90,    91,   182,   183,   184,   185,   186,   204,   187,
      92,    93,    94,    95,    96,    38,   203,   148,    97,    98,
     561,    75,   620,   621,   332,   335,   363,    76,    77,   333,
     336,   364,    89,   179,   180,    40,    99,   100,   380,    78,
      78,    78,    71,   381,    28,    29,    30,    31,   101,    78,
     312,   102,   103,    98,   204,   640,    42,   104,   105,   642,
      44,   106,    46,    78,   643,    78,   607,   608,   609,   610,
     316,    78,   415,    48,   749,   644,   750,   751,   544,   545,
     546,   547,   651,   567,   651,   671,   279,   652,   677,   653,
     672,    78,   681,   678,   710,   380,   332,   682,   540,   541,
     683,   733,   613,    78,   548,   363,   420,   421,   335,   612,
     736,   665,   747,   740,   666,   748,    78,     1,     2,     3,
       4,     5,     6,     7,     8,     9,    10,    11,   763,   782,
      50,    79,   775,   764,   783,   776,   280,    78,   246,   247,
     248,   249,   250,   251,   252,   253,   254,   255,   256,   257,
     258,   259,   260,    52,    54,   417,   588,   589,   590,   591,
     416,   281,   282,   283,   346,   288,   292,   418,   293,   297,
     298,   419,   152,   299,   151,   300,   309,   174,   326,    78,
     327,   168,   347,   355,   175,   171,   350,   354,   356,   188,
     153,   154,   155,   382,   383,   358,   189,   228,   210,   360,
     193,   359,   227,   365,   368,   370,   371,   374,   229,   375,
     230,   376,   377,   385,   386,   384,   387,   388,   390,   391,
     392,   393,   261,   394,   395,   396,   397,   400,   398,   399,
     401,   402,   403,   404,   405,   406,   407,   408,   409,   410,
     412,   413,   427,   428,   429,   430,   431,   432,   433,   434,
     436,   437,   435,   438,   439,   441,   443,   444,   445,   446,
     447,   448,   449,   450,   451,   453,   454,   455,   456,   457,
     458,   461,   459,   462,   464,   465,   467,   468,   469,   471,
     470,   472,   474,   475,   480,   473,   481,   483,   484,   492,
     493,   476,   477,   485,   478,   488,   490,   479,   489,   491,
     486,   487,   494,   495,   496,   497,   700,   504,   498,   499,
     500,   501,   502,   506,   507,   508,   509,   511,   510,   512,
     517,   518,   628,   576,   580,   513,   584,   571,   571,   600,
     630,   634,   564,   564,   648,   649,   514,   515,   650,   516,
     656,   611,   519,   261,   417,   520,   521,   655,   658,   416,
     659,   661,   662,   669,   523,   688,   418,   668,   670,   674,
     419,   675,   676,   691,   693,   687,   524,   690,   694,   525,
     696,   697,   698,   715,   720,   721,   728,   522,   536,   723,
     729,   761,   734,   743,   526,   638,   735,   741,   765,   527,
     528,   767,   771,   529,   769,   784,   551,   530,   531,   684,
     389,   552,   411,   543,   557,   575,   702,   414,   532,   709,
     712,   533,   534,   553,   535,   537,   538,   539,   711,   714,
     466,   704,   703,   706,   705,   460,   725,   727,   708,   550,
     604,   440,   777,   707,   685,   463,   724,   719,   726,   722,
     629,   626,   482,   695,   759,   699,   768,   442,   713,   701,
     716,   717,   780,   785,   718,   766,   730,   731,     0,   732,
     737,   738,     0,   452,   739,   742,     0,   770,     0,   786,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   571,     0,
       0,     0,     0,   564,   152,     0,   151,   228,     0,   210,
       0,     0,   227,   168,     0,     0,     0,   171,   229,   241,
     230,     0,   153,   154,   155,     0,     0,     0,     0,   611,
       0,     0,     0,     0,     0,     0,     0,     0,   174,     0,
       0,   188,     0,     0,     0,   175,     0,     0,   189,     0,
       0,     0,   193,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   753,     0,     0,     0,     0,   752,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     753,     0,     0,     0,     0,   752
  };

  const short int
  Dhcp4Parser::yycheck_[] =
  {
      58,    61,    65,    61,    62,    63,    64,    65,    66,    67,
      61,    62,    63,    65,    61,    65,    63,   318,   318,    61,
      61,    61,   490,   491,   499,   496,    13,     7,     5,    10,
       7,   499,     9,     3,     3,    15,    16,     6,     8,    21,
      22,    23,    24,    25,    26,    27,    67,    68,    28,    29,
      30,    12,    13,    33,    34,    35,    38,    37,     0,     3,
      16,    17,    18,    21,     8,    37,    46,     7,    48,    49,
      50,    51,    52,    53,     3,    47,     7,    57,    58,     8,
      38,    37,    40,    41,    64,    43,    44,    45,    38,    39,
      40,    41,    42,    11,    67,    68,    14,    15,    16,    55,
     121,    19,    20,    59,    60,    61,    62,    63,    38,    65,
      28,    29,    30,    31,    32,     7,    21,    57,    36,    37,
      25,   102,    77,    78,     3,     3,     3,   108,   109,     8,
       8,     8,    16,    17,    18,     7,    54,    55,     3,   121,
     121,   121,   121,     8,   121,   122,   123,   124,    66,   121,
       3,    69,    70,    37,    38,     8,     7,    75,    76,     3,
       7,    79,     7,   121,     8,   121,    71,    72,    73,    74,
       3,   121,    56,     7,   104,     8,   106,   107,    98,    99,
     100,   101,     3,   651,     3,     3,     6,     8,     3,     8,
       8,   121,     3,     8,   665,     3,     3,     8,    95,    96,
       8,     8,   677,   121,   124,     3,   507,   507,     3,   677,
       8,     3,     3,     8,     6,     6,   121,   110,   111,   112,
     113,   114,   115,   116,   117,   118,   119,   120,     3,     3,
       7,   289,     3,     8,     8,     6,     3,   121,    80,    81,
      82,    83,    84,    85,    86,    87,    88,    89,    90,    91,
      92,    93,    94,     7,     7,   318,    59,    60,    61,    62,
     318,     4,     8,     3,     8,     4,     4,   318,     4,     4,
       4,   318,   332,     4,   332,     4,     4,   335,     4,   121,
       4,   332,     3,     8,   335,   332,     4,     4,     3,   347,
     332,   332,   332,   280,   281,     4,   347,   360,   356,     3,
     347,     8,   360,     4,     4,     4,     4,     4,   360,     4,
     360,     4,     4,     4,     4,   121,     4,     4,     4,   124,
     124,     4,   380,     4,     4,   122,   122,     4,   122,   122,
       4,     4,     4,     4,     4,     4,     4,   122,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,   122,
       4,     4,   124,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,   122,     4,     4,
       4,     4,   124,   124,     4,     4,   124,     4,     4,     4,
     122,   122,     4,     4,     4,   122,     4,     4,     7,     5,
       5,   124,   124,     7,   124,     7,     7,   124,   121,     7,
     387,   388,     5,     5,     5,     5,   122,   121,     7,     7,
       7,     7,     5,     8,     3,   121,   121,     5,   121,   121,
       5,     7,     4,     7,     7,   121,     7,   490,   491,     7,
       7,     7,   490,   491,     4,     4,   121,   121,     4,   121,
       3,   499,   121,   501,   507,   121,   121,     6,     6,   507,
       3,     6,     3,     3,   121,     3,   507,     6,     4,     4,
     507,     4,     4,     3,     8,     6,   121,     6,     4,   121,
       4,     4,     4,     4,     4,     4,     4,   445,   465,     6,
       5,     4,     8,     7,   121,    65,     8,     8,     4,   121,
     121,     4,     7,   121,     5,     4,   483,   121,   121,   627,
     289,   484,   312,    97,   488,   491,   651,   316,   121,   663,
     669,   121,   121,   103,   121,   121,   121,   121,   667,   671,
     363,   656,   654,   659,   657,   356,   688,   691,   662,   121,
     121,   332,   105,   660,   121,   360,   686,   677,   689,   681,
     507,   501,   380,   642,   747,   124,   763,   335,   122,   124,
     122,   122,   775,   782,   122,   122,   121,   121,    -1,   121,
     121,   121,    -1,   347,   121,   121,    -1,   121,    -1,   121,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   651,    -1,
      -1,    -1,    -1,   651,   654,    -1,   654,   660,    -1,   657,
      -1,    -1,   660,   654,    -1,    -1,    -1,   654,   660,   667,
     660,    -1,   654,   654,   654,    -1,    -1,    -1,    -1,   677,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   686,    -1,
      -1,   689,    -1,    -1,    -1,   686,    -1,    -1,   689,    -1,
      -1,    -1,   689,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   746,    -1,    -1,    -1,    -1,   746,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     763,    -1,    -1,    -1,    -1,   763
  };

  const unsigned short int
  Dhcp4Parser::yystos_[] =
  {
       0,   110,   111,   112,   113,   114,   115,   116,   117,   118,
     119,   120,   126,   127,   128,   129,   130,   131,   132,   133,
     134,   135,   136,   137,     0,     5,     7,     9,   121,   122,
     123,   124,   138,   139,   140,   144,     7,   151,     7,   157,
       7,   171,     7,   228,     7,   296,     7,   308,     7,   256,
       7,   279,     7,   210,     7,   367,   145,   141,   152,   158,
     172,   229,   297,   309,   257,   280,   211,   368,   138,   148,
     149,   121,   142,   143,    10,   102,   108,   109,   121,   150,
     153,   154,   155,   395,   397,   399,    11,    14,    15,    16,
      19,    20,    28,    29,    30,    31,    32,    36,    37,    54,
      55,    66,    69,    70,    75,    76,    79,   150,   159,   160,
     161,   162,   163,   164,   165,   166,   167,   177,   179,   197,
     204,   218,   222,   250,   273,   313,   337,   347,   356,   357,
     365,    12,    13,   169,   170,   173,   175,     7,    33,    34,
      35,    46,    48,    49,    50,    51,    52,    53,    57,    58,
      64,   150,   161,   162,   163,   166,   230,   231,   232,   234,
     236,   238,   240,   242,   244,   246,   248,   249,   273,   290,
     302,   313,   333,    47,   150,   273,   298,   299,   300,    17,
      18,    55,    59,    60,    61,    62,    63,    65,   150,   273,
     310,   311,   312,   313,   315,   317,   319,   321,   323,   325,
     327,   329,   331,    21,    38,    40,    41,    43,    44,    45,
     150,   183,   191,   258,   259,   260,   261,   262,   263,   264,
     265,   267,   269,   270,   272,    39,    42,   150,   191,   262,
     267,   281,   282,   283,   284,   285,   287,   288,   289,    67,
      68,   150,   212,   213,   214,   216,    80,    81,    82,    83,
      84,    85,    86,    87,    88,    89,    90,    91,    92,    93,
      94,   150,   369,   370,   371,   372,   374,   376,   377,   379,
     380,   381,   384,   386,   387,   388,   389,   390,   393,     6,
       3,     4,     8,     3,   156,   400,   396,   398,     4,     3,
       8,   168,     4,     4,   314,   178,   180,     4,     4,     4,
       4,   223,   251,   274,   198,   338,   205,   219,   348,     4,
     358,   366,     3,     8,   174,   176,     3,     8,   340,   235,
     237,   239,   291,   233,   241,   243,     4,     4,   247,   245,
     303,   334,     3,     8,   301,     3,     8,   316,   318,   332,
     322,   324,   328,   326,   330,   320,     8,     3,   184,   192,
       4,   268,   266,   271,     4,     8,     3,   286,     4,     8,
       3,   215,   217,     3,     8,     4,   373,   375,     4,   378,
       4,     4,   382,   385,     4,     4,     4,     4,   391,   394,
       3,     8,   138,   138,   121,     4,     4,     4,     4,   154,
       4,   124,   124,     4,     4,     4,   122,   122,   122,   122,
       4,     4,     4,     4,     4,     4,     4,     4,   122,     4,
       4,   160,     4,     4,   170,    56,   150,   191,   273,   313,
     315,   317,   341,   342,   343,   344,   345,     4,     4,     4,
       4,     4,     4,     4,   122,   124,     4,     4,     4,     4,
     231,     4,   299,     4,     4,     4,     4,     4,     4,     4,
       4,     4,   312,     4,     4,   122,     4,     4,     4,   124,
     260,     4,   124,   283,     4,     4,   213,   124,     4,     4,
     122,     4,   122,   122,     4,     4,   124,   124,   124,   124,
       4,     4,   370,     4,     7,     7,   138,   138,     7,   121,
       7,     7,     5,     5,     5,     5,     5,     5,     7,     7,
       7,     7,     5,   146,   121,   346,     8,     3,   121,   121,
     121,     5,   121,   121,   121,   121,   121,     5,     7,   121,
     121,   121,   146,   121,   121,   121,   121,   121,   121,   121,
     121,   121,   121,   121,   121,   121,   138,   121,   121,   121,
      95,    96,   383,    97,    98,    99,   100,   101,   124,   392,
     121,   138,   159,   103,   401,   402,   403,   169,    22,    23,
      24,    25,    26,    27,   150,   181,   182,   183,   185,   187,
     189,   191,   193,   194,   195,   181,     7,   224,   225,   226,
       7,   252,   253,   254,     7,   275,   276,   277,    59,    60,
      61,    62,   196,   199,   200,   201,   202,   203,   244,   339,
       7,   206,   207,   208,   121,   220,   221,    71,    72,    73,
      74,   150,   183,   193,   349,   350,   351,   352,   354,   355,
      77,    78,   359,   360,   361,   363,   369,   147,     4,   343,
       7,   292,   293,   294,     7,   304,   305,   306,    65,   335,
       8,   404,     3,     8,     8,   186,   188,   190,     4,     4,
       4,     3,     8,     8,   227,     6,     3,   255,     6,     3,
     278,     6,     3,     3,     6,     3,     6,   209,     6,     3,
       4,     3,     8,   353,     4,     4,     4,     3,     8,   362,
     364,     3,     8,     8,   148,   121,   295,     6,     3,   307,
       6,     3,   336,     8,     4,   402,     4,     4,     4,   124,
     122,   124,   182,   230,   226,   258,   254,   281,   277,   200,
     244,   212,   208,   122,   221,     4,   122,   122,   122,   350,
       4,     4,   360,     6,   298,   294,   310,   306,     4,     5,
     121,   121,   121,     8,     8,     8,     8,   121,   121,   121,
       8,     8,   121,     7,   405,   406,   407,     3,     6,   104,
     106,   107,   150,   191,   408,   409,   410,   411,   413,   406,
     414,     4,   412,     3,     8,     4,   122,     4,   409,     5,
     121,     7,   415,   416,   417,     3,     6,   105,   418,   419,
     416,   420,     3,     8,     4,   419,   121
  };

  const unsigned short int
  Dhcp4Parser::yyr1_[] =
  {
       0,   125,   127,   126,   128,   126,   129,   126,   130,   126,
     131,   126,   132,   126,   133,   126,   134,   126,   135,   126,
     136,   126,   137,   126,   138,   138,   138,   138,   138,   138,
     138,   139,   141,   140,   142,   142,   143,   143,   145,   144,
     147,   146,   148,   148,   149,   149,   150,   152,   151,   153,
     153,   154,   154,   154,   154,   154,   156,   155,   158,   157,
     159,   159,   160,   160,   160,   160,   160,   160,   160,   160,
     160,   160,   160,   160,   160,   160,   160,   160,   160,   160,
     160,   160,   160,   160,   161,   162,   163,   164,   165,   166,
     168,   167,   169,   169,   170,   170,   172,   171,   174,   173,
     176,   175,   178,   177,   180,   179,   181,   181,   182,   182,
     182,   182,   182,   182,   182,   182,   182,   184,   183,   186,
     185,   188,   187,   190,   189,   192,   191,   193,   194,   195,
     196,   198,   197,   199,   199,   200,   200,   200,   200,   201,
     202,   203,   205,   204,   206,   206,   207,   207,   209,   208,
     211,   210,   212,   212,   212,   213,   213,   215,   214,   217,
     216,   219,   218,   220,   220,   221,   223,   222,   224,   224,
     225,   225,   227,   226,   229,   228,   230,   230,   231,   231,
     231,   231,   231,   231,   231,   231,   231,   231,   231,   231,
     231,   231,   231,   231,   231,   231,   231,   231,   233,   232,
     235,   234,   237,   236,   239,   238,   241,   240,   243,   242,
     245,   244,   247,   246,   248,   249,   251,   250,   252,   252,
     253,   253,   255,   254,   257,   256,   258,   258,   259,   259,
     260,   260,   260,   260,   260,   260,   260,   260,   261,   262,
     263,   264,   266,   265,   268,   267,   269,   271,   270,   272,
     274,   273,   275,   275,   276,   276,   278,   277,   280,   279,
     281,   281,   282,   282,   283,   283,   283,   283,   283,   283,
     284,   286,   285,   287,   288,   289,   291,   290,   292,   292,
     293,   293,   295,   294,   297,   296,   298,   298,   299,   299,
     299,   301,   300,   303,   302,   304,   304,   305,   305,   307,
     306,   309,   308,   310,   310,   311,   311,   312,   312,   312,
     312,   312,   312,   312,   312,   312,   312,   312,   312,   314,
     313,   316,   315,   318,   317,   320,   319,   322,   321,   324,
     323,   326,   325,   328,   327,   330,   329,   332,   331,   334,
     333,   336,   335,   338,   337,   339,   339,   340,   244,   341,
     341,   342,   342,   343,   343,   343,   343,   343,   343,   343,
     344,   346,   345,   348,   347,   349,   349,   350,   350,   350,
     350,   350,   350,   350,   351,   353,   352,   354,   355,   356,
     358,   357,   359,   359,   360,   360,   362,   361,   364,   363,
     366,   365,   368,   367,   369,   369,   370,   370,   370,   370,
     370,   370,   370,   370,   370,   370,   370,   370,   370,   370,
     370,   370,   371,   373,   372,   375,   374,   376,   378,   377,
     379,   380,   382,   381,   383,   383,   385,   384,   386,   387,
     388,   389,   391,   390,   392,   392,   392,   392,   392,   394,
     393,   396,   395,   398,   397,   400,   399,   401,   401,   402,
     404,   403,   405,   405,   407,   406,   408,   408,   409,   409,
     409,   409,   409,   410,   412,   411,   414,   413,   415,   415,
     417,   416,   418,   418,   420,   419
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
       0,     4,     0,     6,     0,     6,     1,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     4,     3,     3,     3,
       1,     0,     6,     1,     3,     1,     1,     1,     1,     1,
       1,     1,     0,     6,     0,     1,     1,     3,     0,     4,
       0,     4,     1,     3,     1,     1,     1,     0,     4,     0,
       4,     0,     6,     1,     3,     3,     0,     6,     0,     1,
       1,     3,     0,     4,     0,     4,     1,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     0,     4,
       0,     4,     0,     4,     0,     4,     0,     4,     0,     4,
       0,     4,     0,     4,     3,     3,     0,     6,     0,     1,
       1,     3,     0,     4,     0,     4,     0,     1,     1,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     3,
       1,     1,     0,     4,     0,     4,     1,     0,     4,     3,
       0,     6,     0,     1,     1,     3,     0,     4,     0,     4,
       0,     1,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     0,     4,     1,     1,     3,     0,     6,     0,     1,
       1,     3,     0,     4,     0,     4,     1,     3,     1,     1,
       1,     0,     4,     0,     6,     0,     1,     1,     3,     0,
       4,     0,     4,     0,     1,     1,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       6,     0,     4,     0,     6,     1,     3,     0,     4,     0,
       1,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     0,     4,     0,     6,     1,     3,     1,     1,     1,
       1,     1,     1,     1,     3,     0,     4,     3,     3,     3,
       0,     6,     1,     3,     1,     1,     0,     4,     0,     4,
       0,     6,     0,     4,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     3,     0,     4,     0,     4,     3,     0,     4,
       3,     3,     0,     4,     1,     1,     0,     4,     3,     3,
       3,     3,     0,     4,     1,     1,     1,     1,     1,     0,
       4,     0,     4,     0,     4,     0,     6,     1,     3,     1,
       0,     6,     1,     3,     0,     4,     1,     3,     1,     1,
       1,     1,     1,     3,     0,     4,     0,     6,     1,     3,
       0,     4,     1,     3,     0,     4
  };



  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a yyntokens_, nonterminals.
  const char*
  const Dhcp4Parser::yytname_[] =
  {
  "\"end of file\"", "error", "$undefined", "\",\"", "\":\"", "\"[\"",
  "\"]\"", "\"{\"", "\"}\"", "\"null\"", "\"Dhcp4\"",
  "\"interfaces-config\"", "\"interfaces\"", "\"dhcp-socket-type\"",
  "\"echo-client-id\"", "\"match-client-id\"", "\"next-server\"",
  "\"server-hostname\"", "\"boot-file-name\"", "\"lease-database\"",
  "\"hosts-database\"", "\"type\"", "\"user\"", "\"password\"", "\"host\"",
  "\"persist\"", "\"lfc-interval\"", "\"readonly\"", "\"valid-lifetime\"",
  "\"renew-timer\"", "\"rebind-timer\"", "\"decline-probation-period\"",
  "\"subnet4\"", "\"4o6-interface\"", "\"4o6-interface-id\"",
  "\"4o6-subnet\"", "\"option-def\"", "\"option-data\"", "\"name\"",
  "\"data\"", "\"code\"", "\"space\"", "\"csv-format\"",
  "\"record-types\"", "\"encapsulate\"", "\"array\"", "\"pools\"",
  "\"pool\"", "\"subnet\"", "\"interface\"", "\"interface-id\"", "\"id\"",
  "\"rapid-commit\"", "\"reservation-mode\"",
  "\"host-reservation-identifiers\"", "\"client-classes\"", "\"test\"",
  "\"client-class\"", "\"reservations\"", "\"duid\"", "\"hw-address\"",
  "\"circuit-id\"", "\"client-id\"", "\"hostname\"", "\"relay\"",
  "\"ip-address\"", "\"hooks-libraries\"", "\"library\"", "\"parameters\"",
  "\"expired-leases-processing\"", "\"server-id\"", "\"identifier\"",
  "\"htype\"", "\"time\"", "\"enterprise-id\"", "\"dhcp4o6-port\"",
  "\"control-socket\"", "\"socket-type\"", "\"socket-name\"",
  "\"dhcp-ddns\"", "\"enable-updates\"", "\"qualifying-suffix\"",
  "\"server-ip\"", "\"server-port\"", "\"sender-ip\"", "\"sender-port\"",
  "\"max-queue-size\"", "\"ncr-protocol\"", "\"ncr-format\"",
  "\"always-include-fqdn\"", "\"allow-client-update\"",
  "\"override-no-update\"", "\"override-client-update\"",
  "\"replace-client-name\"", "\"generated-prefix\"", "\"UDP\"", "\"TCP\"",
  "\"JSON\"", "\"when-present\"", "\"never\"", "\"always\"",
  "\"when-not-present\"", "\"Logging\"", "\"loggers\"",
  "\"output_options\"", "\"output\"", "\"debuglevel\"", "\"severity\"",
  "\"Dhcp6\"", "\"DhcpDdns\"", "TOPLEVEL_JSON", "TOPLEVEL_DHCP4",
  "SUB_DHCP4", "SUB_INTERFACES4", "SUB_SUBNET4", "SUB_POOL4",
  "SUB_RESERVATION", "SUB_OPTION_DEF", "SUB_OPTION_DATA",
  "SUB_HOOKS_LIBRARY", "SUB_DHCP_DDNS", "\"constant string\"",
  "\"integer\"", "\"floating point\"", "\"boolean\"", "$accept", "start",
  "$@1", "$@2", "$@3", "$@4", "$@5", "$@6", "$@7", "$@8", "$@9", "$@10",
  "$@11", "value", "sub_json", "map2", "$@12", "map_content",
  "not_empty_map", "list_generic", "$@13", "list2", "$@14", "list_content",
  "not_empty_list", "unknown_map_entry", "syntax_map", "$@15",
  "global_objects", "global_object", "dhcp4_object", "$@16", "sub_dhcp4",
  "$@17", "global_params", "global_param", "valid_lifetime", "renew_timer",
  "rebind_timer", "decline_probation_period", "echo_client_id",
  "match_client_id", "interfaces_config", "$@18",
  "interfaces_config_params", "interfaces_config_param", "sub_interfaces4",
  "$@19", "interfaces_list", "$@20", "dhcp_socket_type", "$@21",
  "lease_database", "$@22", "hosts_database", "$@23",
  "database_map_params", "database_map_param", "type", "$@24", "user",
  "$@25", "password", "$@26", "host", "$@27", "name", "$@28", "persist",
  "lfc_interval", "readonly", "duid_id", "host_reservation_identifiers",
  "$@29", "host_reservation_identifiers_list",
  "host_reservation_identifier", "hw_address_id", "circuit_id",
  "client_id", "hooks_libraries", "$@30", "hooks_libraries_list",
  "not_empty_hooks_libraries_list", "hooks_library", "$@31",
  "sub_hooks_library", "$@32", "hooks_params", "hooks_param", "library",
  "$@33", "parameters", "$@34", "expired_leases_processing", "$@35",
  "expired_leases_params", "expired_leases_param", "subnet4_list", "$@36",
  "subnet4_list_content", "not_empty_subnet4_list", "subnet4", "$@37",
  "sub_subnet4", "$@38", "subnet4_params", "subnet4_param", "subnet",
  "$@39", "subnet_4o6_interface", "$@40", "subnet_4o6_interface_id",
  "$@41", "subnet_4o6_subnet", "$@42", "interface", "$@43", "interface_id",
  "$@44", "client_class", "$@45", "reservation_mode", "$@46", "id",
  "rapid_commit", "option_def_list", "$@47", "option_def_list_content",
  "not_empty_option_def_list", "option_def_entry", "$@48",
  "sub_option_def", "$@49", "option_def_params",
  "not_empty_option_def_params", "option_def_param", "option_def_name",
  "code", "option_def_code", "option_def_type", "option_def_record_types",
  "$@50", "space", "$@51", "option_def_space", "option_def_encapsulate",
  "$@52", "option_def_array", "option_data_list", "$@53",
  "option_data_list_content", "not_empty_option_data_list",
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
  "control_socket_param", "socket_type", "$@82", "socket_name", "$@83",
  "dhcp_ddns", "$@84", "sub_dhcp_ddns", "$@85", "dhcp_ddns_params",
  "dhcp_ddns_param", "enable_updates", "qualifying_suffix", "$@86",
  "server_ip", "$@87", "server_port", "sender_ip", "$@88", "sender_port",
  "max_queue_size", "ncr_protocol", "$@89", "ncr_protocol_value",
  "ncr_format", "$@90", "always_include_fqdn", "allow_client_update",
  "override_no_update", "override_client_update", "replace_client_name",
  "$@91", "replace_client_name_value", "generated_prefix", "$@92",
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
       0,   203,   203,   203,   204,   204,   205,   205,   206,   206,
     207,   207,   208,   208,   209,   209,   210,   210,   211,   211,
     212,   212,   213,   213,   221,   222,   223,   224,   225,   226,
     227,   230,   235,   235,   247,   248,   251,   255,   262,   262,
     270,   270,   277,   278,   281,   285,   296,   306,   306,   318,
     319,   323,   324,   325,   326,   327,   330,   330,   347,   347,
     355,   356,   361,   362,   363,   364,   365,   366,   367,   368,
     369,   370,   371,   372,   373,   374,   375,   376,   377,   378,
     379,   380,   381,   382,   385,   390,   395,   400,   405,   410,
     416,   416,   426,   427,   430,   431,   434,   434,   442,   442,
     452,   452,   460,   460,   470,   470,   480,   481,   484,   485,
     486,   487,   488,   489,   490,   491,   492,   495,   495,   503,
     503,   511,   511,   519,   519,   527,   527,   535,   540,   545,
     550,   555,   555,   565,   566,   569,   570,   571,   572,   575,
     580,   585,   590,   590,   600,   601,   604,   605,   608,   608,
     616,   616,   624,   625,   626,   629,   630,   633,   633,   641,
     641,   649,   649,   659,   660,   666,   674,   674,   687,   688,
     691,   692,   699,   699,   722,   722,   731,   732,   736,   737,
     738,   739,   740,   741,   742,   743,   744,   745,   746,   747,
     748,   749,   750,   751,   752,   753,   754,   755,   758,   758,
     766,   766,   774,   774,   782,   782,   790,   790,   798,   798,
     806,   806,   814,   814,   822,   827,   836,   836,   848,   849,
     852,   853,   858,   858,   869,   869,   879,   880,   883,   884,
     887,   888,   889,   890,   891,   892,   893,   894,   897,   899,
     904,   906,   908,   908,   916,   916,   924,   926,   926,   934,
     943,   943,   955,   956,   961,   962,   967,   967,   978,   978,
     989,   990,   995,   996,  1001,  1002,  1003,  1004,  1005,  1006,
    1009,  1011,  1011,  1019,  1021,  1023,  1031,  1031,  1043,  1044,
    1047,  1048,  1051,  1051,  1059,  1059,  1067,  1068,  1071,  1072,
    1073,  1076,  1076,  1087,  1087,  1097,  1098,  1101,  1102,  1105,
    1105,  1113,  1113,  1121,  1122,  1125,  1126,  1130,  1131,  1132,
    1133,  1134,  1135,  1136,  1137,  1138,  1139,  1140,  1141,  1144,
    1144,  1152,  1152,  1160,  1160,  1168,  1168,  1176,  1176,  1184,
    1184,  1192,  1192,  1200,  1200,  1209,  1209,  1217,  1217,  1230,
    1230,  1240,  1240,  1251,  1251,  1261,  1262,  1265,  1265,  1273,
    1274,  1277,  1278,  1281,  1282,  1283,  1284,  1285,  1286,  1287,
    1290,  1292,  1292,  1303,  1303,  1313,  1314,  1317,  1318,  1319,
    1320,  1321,  1322,  1323,  1326,  1331,  1331,  1339,  1344,  1351,
    1358,  1358,  1368,  1369,  1372,  1373,  1376,  1376,  1384,  1384,
    1394,  1394,  1404,  1404,  1412,  1413,  1416,  1417,  1418,  1419,
    1420,  1421,  1422,  1423,  1424,  1425,  1426,  1427,  1428,  1429,
    1430,  1431,  1434,  1439,  1439,  1447,  1447,  1455,  1460,  1460,
    1468,  1473,  1478,  1478,  1486,  1487,  1490,  1490,  1498,  1503,
    1508,  1513,  1518,  1518,  1526,  1529,  1532,  1535,  1538,  1544,
    1544,  1554,  1554,  1561,  1561,  1573,  1573,  1586,  1587,  1591,
    1595,  1595,  1607,  1608,  1612,  1612,  1620,  1621,  1624,  1625,
    1626,  1627,  1628,  1631,  1635,  1635,  1643,  1643,  1653,  1654,
    1657,  1657,  1665,  1666,  1669,  1669
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
#line 3864 "dhcp4_parser.cc" // lalr1.cc:1167
#line 1677 "dhcp4_parser.yy" // lalr1.cc:1168


void
isc::dhcp::Dhcp4Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
