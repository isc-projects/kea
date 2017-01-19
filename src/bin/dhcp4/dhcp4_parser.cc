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
      case 399: // ncr_protocol_value
      case 408: // replace_client_name_value
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
      case 399: // ncr_protocol_value
      case 408: // replace_client_name_value
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

      case 186: // socket_type

#line 202 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 393 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 399: // ncr_protocol_value

#line 202 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 400 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 408: // replace_client_name_value

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
      case 186: // socket_type
      case 399: // ncr_protocol_value
      case 408: // replace_client_name_value
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

  case 42:
#line 281 "dhcp4_parser.yy" // lalr1.cc:859
    {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 827 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 43:
#line 285 "dhcp4_parser.yy" // lalr1.cc:859
    {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 836 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 44:
#line 292 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // List parsing about to start
}
#line 844 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 45:
#line 294 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // list parsing complete. Put any sanity checking here
    //ctx.stack_.pop_back();
}
#line 853 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 48:
#line 303 "dhcp4_parser.yy" // lalr1.cc:859
    {
                          ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 862 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 49:
#line 307 "dhcp4_parser.yy" // lalr1.cc:859
    {
                          ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 871 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 50:
#line 318 "dhcp4_parser.yy" // lalr1.cc:859
    {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as< std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 882 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 51:
#line 328 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 893 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 52:
#line 333 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 903 "dhcp4_parser.cc" // lalr1.cc:859
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
#line 916 "dhcp4_parser.cc" // lalr1.cc:859
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
#line 928 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 62:
#line 369 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the Dhcp4 map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 938 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 63:
#line 373 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 946 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 88:
#line 407 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 955 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 89:
#line 412 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 964 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 90:
#line 417 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 973 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 91:
#line 422 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr dpp(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 982 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 92:
#line 427 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr echo(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("echo-client-id", echo);
}
#line 991 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 93:
#line 432 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr match(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("match-client-id", match);
}
#line 1000 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 94:
#line 438 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces-config", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.INTERFACES_CONFIG);
}
#line 1011 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 95:
#line 443 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1020 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 100:
#line 456 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1030 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 101:
#line 460 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1038 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 102:
#line 464 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1049 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 103:
#line 469 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1058 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 104:
#line 474 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.DHCP_SOCKET_TYPE);
}
#line 1066 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 105:
#line 476 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("dhcp-socket-type", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1075 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 106:
#line 481 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("raw", ctx.loc2pos(yystack_[0].location))); }
#line 1081 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 107:
#line 482 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("udp", ctx.loc2pos(yystack_[0].location))); }
#line 1087 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 108:
#line 485 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lease-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.LEASE_DATABASE);
}
#line 1098 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 109:
#line 490 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1107 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 110:
#line 495 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1118 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 111:
#line 500 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1127 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 123:
#line 520 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1135 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 124:
#line 522 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 1145 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 125:
#line 528 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1153 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 126:
#line 530 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr user(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1163 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 127:
#line 536 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1171 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 128:
#line 538 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr pwd(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 1181 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 129:
#line 544 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1189 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 130:
#line 546 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr h(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 1199 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 131:
#line 552 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1207 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 132:
#line 554 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1217 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 133:
#line 560 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 1226 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 134:
#line 565 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 1235 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 135:
#line 570 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 1244 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 136:
#line 575 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1253 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 137:
#line 580 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 1264 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 138:
#line 585 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1273 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 145:
#line 600 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 1282 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 146:
#line 605 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr circuit(new StringElement("circuit-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(circuit);
}
#line 1291 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 147:
#line 610 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr client(new StringElement("client-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(client);
}
#line 1300 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 148:
#line 615 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 1311 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 149:
#line 620 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1320 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 154:
#line 633 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1330 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 155:
#line 637 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1338 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 156:
#line 641 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1348 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 157:
#line 645 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1356 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 163:
#line 658 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1364 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 164:
#line 660 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr lib(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 1374 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 165:
#line 666 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1382 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 166:
#line 668 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1391 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 167:
#line 674 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.EXPIRED_LEASES_PROCESSING);
}
#line 1402 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 168:
#line 679 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1411 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 177:
#line 696 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 1420 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 178:
#line 701 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 1429 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 179:
#line 706 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 1438 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 180:
#line 711 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 1447 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 181:
#line 716 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 1456 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 182:
#line 721 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 1465 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 183:
#line 729 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet4", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET4);
}
#line 1476 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 184:
#line 734 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1485 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 189:
#line 754 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1495 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 190:
#line 758 "dhcp4_parser.yy" // lalr1.cc:859
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
#line 1518 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 191:
#line 777 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the subnet4 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1528 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 192:
#line 781 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1536 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 215:
#line 813 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1544 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 216:
#line 815 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr subnet(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 1554 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 217:
#line 821 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1562 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 218:
#line 823 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface", iface);
    ctx.leave();
}
#line 1572 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 219:
#line 829 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1580 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 220:
#line 831 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface-id", iface);
    ctx.leave();
}
#line 1590 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 221:
#line 837 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1598 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 222:
#line 839 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-subnet", iface);
    ctx.leave();
}
#line 1608 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 223:
#line 845 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1616 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 224:
#line 847 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 1626 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 225:
#line 853 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1634 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 226:
#line 855 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface-id", iface);
    ctx.leave();
}
#line 1644 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 227:
#line 861 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.CLIENT_CLASS);
}
#line 1652 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 228:
#line 863 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr cls(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 1662 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 229:
#line 869 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1670 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 230:
#line 871 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr rm(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservation-mode", rm);
    ctx.leave();
}
#line 1680 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 231:
#line 877 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr id(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 1689 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 232:
#line 882 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr rc(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rapid-commit", rc);
}
#line 1698 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 233:
#line 891 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 1709 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 234:
#line 896 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1718 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 239:
#line 913 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1728 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 240:
#line 917 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1736 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 241:
#line 924 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1746 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 242:
#line 928 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1754 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 256:
#line 954 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr code(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 1763 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 259:
#line 963 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1771 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 260:
#line 965 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 1781 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 261:
#line 971 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1789 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 262:
#line 973 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr space(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 1799 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 264:
#line 981 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1807 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 265:
#line 983 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr encap(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 1817 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 266:
#line 989 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr array(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 1826 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 267:
#line 998 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 1837 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 268:
#line 1003 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1846 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 273:
#line 1022 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1856 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 274:
#line 1026 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1864 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 275:
#line 1033 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1874 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 276:
#line 1037 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1882 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 288:
#line 1066 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1890 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 289:
#line 1068 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr data(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 1900 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 292:
#line 1078 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr space(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", space);
}
#line 1909 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 293:
#line 1086 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 1920 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 294:
#line 1091 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1929 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 299:
#line 1106 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1939 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 300:
#line 1110 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1947 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 301:
#line 1114 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1957 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 302:
#line 1118 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1965 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 308:
#line 1131 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1973 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 309:
#line 1133 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr pool(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 1983 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 310:
#line 1142 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 1994 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 311:
#line 1147 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2003 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 316:
#line 1160 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2013 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 317:
#line 1164 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2021 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 318:
#line 1168 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2031 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 319:
#line 1172 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 2039 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 336:
#line 1199 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2047 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 337:
#line 1201 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr next_server(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("next-server", next_server);
    ctx.leave();
}
#line 2057 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 338:
#line 1207 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2065 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 339:
#line 1209 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr srv(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-hostname", srv);
    ctx.leave();
}
#line 2075 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 340:
#line 1215 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2083 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 341:
#line 1217 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr bootfile(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("boot-file-name", bootfile);
    ctx.leave();
}
#line 2093 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 342:
#line 1223 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2101 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 343:
#line 1225 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr addr(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", addr);
    ctx.leave();
}
#line 2111 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 344:
#line 1231 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2119 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 345:
#line 1233 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr d(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 2129 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 346:
#line 1239 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2137 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 347:
#line 1241 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 2147 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 348:
#line 1247 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2155 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 349:
#line 1249 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-id", hw);
    ctx.leave();
}
#line 2165 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 350:
#line 1255 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2173 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 351:
#line 1257 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("circuit-id", hw);
    ctx.leave();
}
#line 2183 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 352:
#line 1264 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2191 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 353:
#line 1266 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr host(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 2201 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 354:
#line 1272 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2212 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 355:
#line 1277 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2221 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 356:
#line 1285 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 2232 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 357:
#line 1290 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2241 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 358:
#line 1295 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2249 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 359:
#line 1297 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr ip(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", ip);
    ctx.leave();
}
#line 2259 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 360:
#line 1306 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 2270 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 361:
#line 1311 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2279 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 364:
#line 1320 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2289 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 365:
#line 1324 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2297 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 378:
#line 1347 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2305 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 379:
#line 1349 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr test(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 2315 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 380:
#line 1358 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-id", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SERVER_ID);
}
#line 2326 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 381:
#line 1363 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2335 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 391:
#line 1381 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr htype(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("htype", htype);
}
#line 2344 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 392:
#line 1386 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2352 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 393:
#line 1388 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr id(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("identifier", id);
    ctx.leave();
}
#line 2362 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 394:
#line 1394 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("time", time);
}
#line 2371 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 395:
#line 1399 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enterprise-id", time);
}
#line 2380 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 396:
#line 1406 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 2389 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 397:
#line 1413 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 2400 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 398:
#line 1418 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2409 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 403:
#line 1431 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2417 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 404:
#line 1433 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr stype(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 2427 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 405:
#line 1439 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2435 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 406:
#line 1441 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 2445 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 407:
#line 1449 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 2456 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 408:
#line 1454 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2465 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 409:
#line 1459 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2475 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 410:
#line 1463 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 2483 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 429:
#line 1489 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 2492 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 430:
#line 1494 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2500 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 431:
#line 1496 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("qualifying-suffix", s);
    ctx.leave();
}
#line 2510 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 432:
#line 1502 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2518 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 433:
#line 1504 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 2528 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 434:
#line 1510 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 2537 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 435:
#line 1515 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2545 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 436:
#line 1517 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 2555 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 437:
#line 1523 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 2564 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 438:
#line 1528 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 2573 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 439:
#line 1533 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 2581 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 440:
#line 1535 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2590 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 441:
#line 1541 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 2596 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 442:
#line 1542 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 2602 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 443:
#line 1545 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NCR_FORMAT);
}
#line 2610 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 444:
#line 1547 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 2620 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 445:
#line 1553 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-include-fqdn", b);
}
#line 2629 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 446:
#line 1558 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("allow-client-update",  b);
}
#line 2638 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 447:
#line 1563 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-no-update", b);
}
#line 2647 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 448:
#line 1568 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-client-update", b);
}
#line 2656 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 449:
#line 1573 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 2664 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 450:
#line 1575 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("replace-client-name", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2673 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 451:
#line 1581 "dhcp4_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("when-present", ctx.loc2pos(yystack_[0].location))); 
      }
#line 2681 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 452:
#line 1584 "dhcp4_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location)));
      }
#line 2689 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 453:
#line 1587 "dhcp4_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("always", ctx.loc2pos(yystack_[0].location)));
      }
#line 2697 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 454:
#line 1590 "dhcp4_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("when-not-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 2705 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 455:
#line 1593 "dhcp4_parser.yy" // lalr1.cc:859
    {
      error(yystack_[0].location, "boolean values for the replace-client-name are "
                "no longer supported");
      }
#line 2714 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 456:
#line 1599 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2722 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 457:
#line 1601 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("generated-prefix", s);
    ctx.leave();
}
#line 2732 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 458:
#line 1609 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2740 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 459:
#line 1611 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("Dhcp6", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2749 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 460:
#line 1616 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2757 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 461:
#line 1618 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("DhcpDdns", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2766 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 462:
#line 1628 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Logging", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.LOGGING);
}
#line 2777 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 463:
#line 1633 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2786 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 467:
#line 1650 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 2797 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 468:
#line 1655 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2806 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 471:
#line 1667 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 2816 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 472:
#line 1671 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2824 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 480:
#line 1686 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr dl(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 2833 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 481:
#line 1690 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2841 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 482:
#line 1692 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 2851 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 483:
#line 1698 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 2862 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 484:
#line 1703 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2871 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 487:
#line 1712 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2881 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 488:
#line 1716 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2889 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 491:
#line 1724 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2897 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 492:
#line 1726 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 2907 "dhcp4_parser.cc" // lalr1.cc:859
    break;


#line 2911 "dhcp4_parser.cc" // lalr1.cc:859
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


  const short int Dhcp4Parser::yypact_ninf_ = -482;

  const signed char Dhcp4Parser::yytable_ninf_ = -1;

  const short int
  Dhcp4Parser::yypact_[] =
  {
     194,  -482,  -482,  -482,  -482,  -482,  -482,  -482,  -482,  -482,
    -482,  -482,    36,    23,    80,   123,   139,   159,   168,   172,
     215,   221,   222,   223,  -482,  -482,  -482,  -482,  -482,  -482,
    -482,  -482,  -482,  -482,  -482,  -482,  -482,  -482,  -482,  -482,
    -482,  -482,  -482,  -482,  -482,  -482,  -482,  -482,  -482,  -482,
    -482,  -482,  -482,  -482,  -482,  -482,    23,   -85,    19,    93,
      64,    20,     5,    27,   142,    55,   -35,   235,  -482,    43,
     102,   205,   108,   208,  -482,  -482,  -482,  -482,   241,  -482,
      50,  -482,  -482,  -482,  -482,  -482,  -482,   243,   244,  -482,
    -482,  -482,   245,   246,   247,   248,  -482,  -482,  -482,  -482,
    -482,  -482,  -482,  -482,   249,  -482,  -482,  -482,    61,  -482,
    -482,  -482,  -482,  -482,  -482,  -482,  -482,  -482,  -482,  -482,
    -482,  -482,  -482,  -482,  -482,  -482,  -482,  -482,  -482,  -482,
    -482,  -482,  -482,    75,  -482,  -482,  -482,  -482,  -482,  -482,
    -482,  -482,  -482,  -482,  -482,   250,   252,  -482,  -482,  -482,
    -482,  -482,  -482,  -482,  -482,  -482,    98,  -482,  -482,  -482,
    -482,  -482,  -482,  -482,  -482,  -482,  -482,  -482,  -482,  -482,
    -482,  -482,  -482,  -482,  -482,  -482,    99,  -482,  -482,  -482,
    -482,  -482,  -482,  -482,  -482,  -482,  -482,  -482,  -482,  -482,
     230,   254,  -482,  -482,  -482,  -482,  -482,  -482,  -482,  -482,
    -482,  -482,  -482,  -482,  -482,   255,  -482,  -482,  -482,   257,
    -482,  -482,  -482,   256,   259,  -482,  -482,  -482,  -482,  -482,
    -482,  -482,  -482,  -482,  -482,  -482,   261,  -482,  -482,  -482,
    -482,   258,   260,  -482,  -482,  -482,  -482,  -482,  -482,  -482,
    -482,  -482,   100,  -482,  -482,  -482,   264,  -482,  -482,   265,
    -482,   269,   271,  -482,  -482,   272,   274,   275,   276,  -482,
    -482,  -482,   109,  -482,  -482,  -482,  -482,  -482,  -482,  -482,
    -482,  -482,  -482,  -482,  -482,  -482,  -482,  -482,  -482,  -482,
      23,    23,  -482,   130,   278,   279,   282,   283,  -482,    19,
    -482,   284,   162,   163,   291,   295,   297,   174,   175,   176,
     177,   303,   305,   334,   335,   336,   337,   338,   339,   218,
     340,   341,    93,  -482,   342,   346,    64,  -482,    42,   347,
     348,   349,   350,   351,   352,   353,   229,   228,   356,   357,
     358,   360,    20,  -482,   361,     5,  -482,   362,   363,   364,
     365,   366,   367,   368,   369,   370,  -482,    27,   371,   372,
     251,   373,   374,   375,   253,  -482,   142,   377,   262,  -482,
      55,   378,   379,    68,  -482,   263,   381,   382,   266,   383,
     267,   268,   384,   385,   270,   273,   277,   280,   386,   387,
     235,  -482,  -482,  -482,   388,   391,   392,    23,    23,  -482,
     393,  -482,  -482,   281,   395,   396,  -482,  -482,  -482,  -482,
     400,   401,   402,   405,   407,   408,   409,   410,  -482,   411,
     412,  -482,   415,   145,  -482,  -482,  -482,  -482,  -482,  -482,
    -482,  -482,   406,   418,  -482,  -482,  -482,   287,   294,   296,
     420,   301,   302,   306,  -482,  -482,   307,   308,   426,   416,
    -482,   309,  -482,   310,   311,   415,   312,   314,   317,   319,
     320,   321,  -482,   322,   324,  -482,   325,   326,   327,  -482,
    -482,   328,  -482,  -482,   329,    23,  -482,  -482,   331,   332,
    -482,   333,  -482,  -482,    33,   359,  -482,  -482,  -482,  -482,
     -66,   343,  -482,    23,    93,   354,  -482,  -482,    64,  -482,
     116,   116,   458,   459,   460,   171,    26,   461,   118,    40,
     112,   235,  -482,  -482,  -482,  -482,  -482,   465,  -482,    42,
    -482,  -482,  -482,   463,  -482,  -482,  -482,  -482,  -482,   466,
     413,  -482,  -482,  -482,  -482,  -482,  -482,  -482,  -482,  -482,
    -482,  -482,  -482,  -482,  -482,  -482,  -482,  -482,  -482,  -482,
    -482,  -482,  -482,  -482,  -482,  -482,  -482,  -482,  -482,  -482,
    -482,  -482,  -482,  -482,   110,  -482,   154,  -482,  -482,   155,
    -482,  -482,  -482,   468,   470,   471,  -482,   164,  -482,  -482,
    -482,  -482,  -482,  -482,  -482,  -482,  -482,   166,  -482,   472,
     473,  -482,  -482,   475,   474,  -482,  -482,   476,   480,  -482,
    -482,  -482,  -482,  -482,  -482,   220,  -482,  -482,  -482,  -482,
    -482,   233,  -482,   478,   482,  -482,   483,   484,   485,   486,
     487,   488,   170,  -482,  -482,  -482,  -482,  -482,  -482,  -482,
    -482,   489,   490,   491,  -482,  -482,  -482,   178,  -482,  -482,
    -482,  -482,  -482,  -482,  -482,   196,  -482,  -482,  -482,   198,
     376,   380,  -482,  -482,   492,   493,  -482,  -482,   494,   496,
    -482,  -482,   495,  -482,   497,   354,  -482,  -482,   498,   501,
     502,   355,   389,   390,   116,  -482,  -482,    20,  -482,   458,
     142,  -482,   459,    55,  -482,   460,   171,  -482,    26,  -482,
     -35,  -482,   461,   394,   397,   398,   399,   403,   404,   118,
    -482,   503,   414,   417,   419,    40,  -482,   505,   506,   112,
    -482,  -482,  -482,   507,   508,  -482,     5,  -482,   463,    27,
    -482,   466,   510,  -482,   511,  -482,   421,   422,   423,  -482,
    -482,  -482,  -482,   202,  -482,   504,  -482,   509,  -482,  -482,
    -482,   204,  -482,  -482,  -482,  -482,  -482,  -482,  -482,  -482,
     424,  -482,  -482,  -482,  -482,   425,   427,  -482,  -482,   428,
     210,  -482,   512,  -482,   429,   515,  -482,  -482,  -482,  -482,
    -482,  -482,  -482,  -482,  -482,  -482,  -482,  -482,  -482,  -482,
    -482,   234,  -482,    89,   515,  -482,  -482,   520,  -482,  -482,
    -482,   216,  -482,  -482,  -482,  -482,  -482,   521,   430,   525,
      89,  -482,   514,  -482,   432,  -482,   523,  -482,  -482,   240,
    -482,   433,   523,  -482,  -482,   217,  -482,  -482,   527,   433,
    -482,   434,  -482,  -482
  };

  const unsigned short int
  Dhcp4Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     1,    38,    32,    28,    27,    24,
      25,    26,    31,     3,    29,    30,    51,     5,    62,     7,
     100,     9,   191,    11,   301,    13,   318,    15,   241,    17,
     275,    19,   156,    21,   409,    23,    40,    34,     0,     0,
       0,     0,     0,   320,   243,   277,     0,     0,    42,     0,
      41,     0,     0,    35,    60,   462,   458,   460,     0,    59,
       0,    53,    55,    57,    58,    56,    94,     0,     0,   336,
     108,   110,     0,     0,     0,     0,   183,   233,   267,   137,
     360,   148,   167,   380,     0,   397,   407,    87,     0,    64,
      66,    67,    68,    69,    84,    85,    71,    72,    73,    74,
      78,    79,    70,    76,    77,    86,    75,    80,    81,    82,
      83,   102,   104,     0,    96,    98,    99,   364,   217,   219,
     221,   293,   215,   223,   225,     0,     0,   229,   227,   310,
     356,   214,   195,   196,   197,   209,     0,   193,   200,   211,
     212,   213,   201,   202,   205,   207,   203,   204,   198,   199,
     206,   210,   208,   308,   307,   306,     0,   303,   305,   338,
     340,   354,   344,   346,   350,   348,   352,   342,   335,   331,
       0,   321,   322,   332,   333,   334,   328,   324,   329,   326,
     327,   330,   325,   123,   131,     0,   261,   259,   264,     0,
     254,   258,   255,     0,   244,   245,   247,   257,   248,   249,
     250,   263,   251,   252,   253,   288,     0,   286,   287,   290,
     291,     0,   278,   279,   281,   282,   283,   284,   285,   163,
     165,   160,     0,   158,   161,   162,     0,   430,   432,     0,
     435,     0,     0,   439,   443,     0,     0,     0,     0,   449,
     456,   428,     0,   411,   413,   414,   415,   416,   417,   418,
     419,   420,   421,   422,   423,   424,   425,   426,   427,    39,
       0,     0,    33,     0,     0,     0,     0,     0,    50,     0,
      52,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    63,     0,     0,     0,   101,   366,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   192,     0,     0,   302,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   319,     0,     0,     0,
       0,     0,     0,     0,     0,   242,     0,     0,     0,   276,
       0,     0,     0,     0,   157,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   410,    43,    36,     0,     0,     0,     0,     0,    54,
       0,    92,    93,     0,     0,     0,    88,    89,    90,    91,
       0,     0,     0,     0,     0,     0,     0,     0,   396,     0,
       0,    65,     0,     0,    97,   378,   376,   377,   372,   373,
     374,   375,     0,   367,   368,   370,   371,     0,     0,     0,
       0,     0,     0,     0,   231,   232,     0,     0,     0,     0,
     194,     0,   304,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   323,     0,     0,   256,     0,     0,     0,   266,
     246,     0,   292,   280,     0,     0,   159,   429,     0,     0,
     434,     0,   437,   438,     0,     0,   445,   446,   447,   448,
       0,     0,   412,     0,     0,     0,   459,   461,     0,   337,
       0,     0,   185,   235,   269,     0,     0,   150,     0,     0,
       0,     0,    44,   103,   106,   107,   105,     0,   365,     0,
     218,   220,   222,   295,   216,   224,   226,   230,   228,   312,
       0,   309,   339,   341,   355,   345,   347,   351,   349,   353,
     343,   124,   132,   262,   260,   265,   289,   164,   166,   431,
     433,   436,   441,   442,   440,   444,   451,   452,   453,   454,
     455,   450,   457,    37,     0,   467,     0,   464,   466,     0,
     125,   127,   129,     0,     0,     0,   122,     0,   112,   114,
     115,   116,   117,   118,   119,   120,   121,     0,   189,     0,
     186,   187,   239,     0,   236,   237,   273,     0,   270,   271,
     136,   145,   146,   147,   141,     0,   139,   142,   143,   144,
     362,     0,   154,     0,   151,   152,     0,     0,     0,     0,
       0,     0,     0,   169,   171,   172,   173,   174,   175,   176,
     392,     0,     0,     0,   390,   384,   389,     0,   382,   387,
     385,   386,   388,   403,   405,     0,   399,   401,   402,     0,
      46,     0,   369,   299,     0,   296,   297,   316,     0,   313,
     314,   358,     0,    61,     0,     0,   463,    95,     0,     0,
       0,     0,     0,     0,     0,   109,   111,     0,   184,     0,
     243,   234,     0,   277,   268,     0,     0,   138,     0,   361,
       0,   149,     0,     0,     0,     0,     0,     0,     0,     0,
     168,     0,     0,     0,     0,     0,   381,     0,     0,     0,
     398,   408,    48,     0,    47,   379,     0,   294,     0,   320,
     311,     0,     0,   357,     0,   465,     0,     0,     0,   133,
     134,   135,   113,     0,   188,     0,   238,     0,   272,   140,
     363,     0,   153,   177,   178,   179,   180,   181,   182,   170,
       0,   391,   394,   395,   383,     0,     0,   400,    45,     0,
       0,   298,     0,   315,     0,     0,   126,   128,   130,   190,
     240,   274,   155,   393,   404,   406,    49,   300,   317,   359,
     471,     0,   469,     0,     0,   468,   483,     0,   481,   479,
     475,     0,   473,   477,   478,   476,   470,     0,     0,     0,
       0,   472,     0,   480,     0,   474,     0,   482,   487,     0,
     485,     0,     0,   484,   491,     0,   489,   486,     0,     0,
     488,     0,   490,   492
  };

  const short int
  Dhcp4Parser::yypgoto_[] =
  {
    -482,  -482,  -482,  -482,  -482,  -482,  -482,  -482,  -482,  -482,
    -482,  -482,  -482,   -39,  -482,  -482,  -482,  -482,  -482,  -482,
    -482,  -482,  -482,    34,  -482,  -482,  -482,   -58,  -482,  -482,
    -482,   226,  -482,  -482,  -482,  -482,    13,   224,   -60,   -42,
     -41,  -482,  -482,   -40,  -482,  -482,    46,   219,  -482,  -482,
    -482,  -482,  -482,  -482,  -482,  -482,  -482,  -482,  -482,    47,
    -127,  -468,  -482,  -482,  -482,  -482,  -482,  -482,  -482,   -63,
    -482,  -481,  -482,  -482,  -482,  -482,  -482,  -482,  -137,  -482,
    -482,  -482,  -482,  -482,  -482,  -482,  -142,  -482,  -482,  -482,
    -139,   179,  -482,  -482,  -482,  -482,  -482,  -482,  -482,  -145,
    -482,  -482,  -482,  -482,  -482,  -482,  -482,  -482,  -482,  -482,
    -122,  -482,  -482,  -482,  -113,   231,  -482,  -482,  -482,  -482,
    -482,  -482,  -482,  -482,  -482,  -482,  -482,  -482,  -470,  -482,
    -482,  -482,  -482,  -482,  -482,  -482,  -482,  -482,  -114,  -482,
    -482,  -482,  -109,  -482,   209,  -482,   -52,  -482,  -482,  -482,
    -482,   -50,  -482,  -482,  -482,  -482,  -482,   -51,  -482,  -482,
    -482,  -111,  -482,  -482,  -482,  -107,  -482,   207,  -482,  -482,
    -482,  -482,  -482,  -482,  -482,  -482,  -482,  -482,  -140,  -482,
    -482,  -482,  -136,   236,  -482,  -482,  -482,  -482,  -482,  -482,
    -138,  -482,  -482,  -482,  -135,  -482,   225,   -47,  -482,  -294,
    -482,  -293,  -482,  -482,  -482,  -482,  -482,  -482,  -482,  -482,
    -482,  -482,  -482,  -482,  -482,  -482,  -482,  -482,  -482,  -482,
    -482,  -482,  -482,  -482,  -482,  -482,  -482,    60,  -482,  -482,
    -482,  -482,  -482,  -482,  -120,  -482,  -482,  -482,  -482,  -482,
    -482,  -482,  -482,  -482,  -123,  -482,  -482,  -482,  -482,  -482,
    -482,  -482,  -482,    76,   199,  -482,  -482,  -482,  -482,  -482,
    -482,  -482,  -482,  -482,  -482,  -482,  -482,  -482,  -482,  -482,
    -482,  -482,  -482,  -482,  -482,  -482,  -482,  -482,  -482,  -482,
    -482,  -482,  -482,  -482,  -482,  -482,   -77,  -482,  -482,  -482,
    -194,  -482,  -482,  -209,  -482,  -482,  -482,  -482,  -482,  -482,
    -220,  -482,  -482,  -226,  -482
  };

  const short int
  Dhcp4Parser::yydefgoto_[] =
  {
      -1,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    32,    33,    34,    57,    72,    73,    35,
      56,    69,    70,   503,   640,   703,   704,   107,    37,    58,
      80,    81,    82,   284,    39,    59,   108,   109,   110,   111,
     112,   113,   114,   115,   116,   291,   133,   134,    41,    60,
     135,   314,   136,   315,   506,   117,   295,   118,   296,   567,
     568,   211,   348,   570,   658,   571,   659,   572,   660,   212,
     349,   574,   575,   576,   594,   119,   304,   595,   596,   597,
     598,   599,   120,   306,   603,   604,   605,   680,    53,    66,
     242,   243,   244,   361,   245,   362,   121,   307,   612,   613,
     614,   615,   616,   617,   618,   619,   122,   301,   579,   580,
     581,   667,    43,    61,   156,   157,   158,   323,   159,   319,
     160,   320,   161,   321,   162,   324,   163,   325,   164,   329,
     165,   328,   166,   167,   123,   302,   583,   584,   585,   670,
      49,    64,   213,   214,   215,   216,   217,   218,   219,   220,
     352,   221,   351,   222,   223,   353,   224,   124,   303,   587,
     588,   589,   673,    51,    65,   231,   232,   233,   234,   235,
     357,   236,   237,   238,   169,   322,   644,   645,   646,   706,
      45,    62,   176,   177,   178,   334,   170,   330,   648,   649,
     650,   709,    47,    63,   190,   191,   192,   125,   294,   194,
     337,   195,   338,   196,   345,   197,   340,   198,   341,   199,
     343,   200,   342,   201,   344,   202,   339,   172,   331,   652,
     712,   126,   305,   601,   318,   422,   423,   424,   425,   426,
     507,   127,   308,   627,   628,   629,   630,   691,   631,   632,
     128,   129,   310,   635,   636,   637,   697,   638,   698,   130,
     311,    55,    67,   262,   263,   264,   265,   366,   266,   367,
     267,   268,   369,   269,   270,   271,   372,   544,   272,   373,
     273,   274,   275,   276,   277,   378,   551,   278,   379,    83,
     286,    84,   287,    85,   285,   556,   557,   558,   654,   771,
     772,   773,   781,   782,   783,   784,   789,   785,   787,   799,
     800,   801,   805,   806,   808
  };

  const unsigned short int
  Dhcp4Parser::yytable_[] =
  {
      79,   152,   228,   151,   174,   188,   210,   227,   241,   261,
     168,   175,   189,   229,   171,   230,   193,    68,   626,   153,
     154,   155,   569,   569,   420,   421,   600,   137,    25,    74,
      26,   625,    27,   137,   239,   240,    24,    88,    89,   546,
     547,   548,   549,    71,    98,    89,   179,   180,   542,   279,
      92,    93,    94,   289,   173,   138,   139,   140,   290,    98,
      89,   179,   180,   203,   312,   550,    98,   563,   141,   313,
     142,   143,   144,   145,   146,   147,   131,   132,   316,   148,
     149,    98,   204,   317,   181,   148,   150,    36,   182,   183,
     184,   185,   186,    78,   187,   204,   225,   205,   206,   226,
     415,   332,   335,   363,    86,   280,   333,   336,   364,    87,
      88,    89,   380,   312,    90,    91,   282,   381,   653,   620,
     621,   622,   623,    92,    93,    94,    95,    96,    75,   204,
      38,    97,    98,    78,    76,    77,   543,   239,   240,   203,
     560,   561,   562,   563,   564,   565,    40,    78,    78,    99,
     100,    28,    29,    30,    31,    78,   204,   655,   316,   504,
     505,   101,   656,   657,   102,   203,    42,   664,    78,   664,
      78,   103,   665,   689,   666,    44,   104,   105,   690,    46,
     106,   695,   204,    78,   205,   206,   696,   207,   208,   209,
     606,   607,   608,   609,   610,   611,   569,   633,   634,   699,
     776,   380,   777,   778,   700,   332,   701,   363,   730,   281,
     759,   283,   762,   335,   626,   420,   421,    78,   767,   790,
     809,    78,    48,   676,   791,   810,   677,   625,    50,    52,
      54,    79,   590,   591,   592,   593,   678,   774,   346,   679,
     775,   382,   383,   802,    78,   288,   803,   292,   293,   297,
     298,   299,   300,   309,   326,   417,   327,   347,   384,   350,
     416,   354,   356,   360,   355,   358,   359,   418,   365,   368,
      78,   419,   152,   370,   151,   371,   374,   174,   375,   376,
     377,   168,   385,   386,   175,   171,   387,   388,   390,   188,
     153,   154,   155,   391,   392,   393,   189,   228,   210,   394,
     193,   395,   227,   396,   397,   398,   399,   400,   229,   401,
     230,     1,     2,     3,     4,     5,     6,     7,     8,     9,
      10,    11,   261,   246,   247,   248,   249,   250,   251,   252,
     253,   254,   255,   256,   257,   258,   259,   260,   402,   403,
     404,   405,   406,   407,   409,   410,   412,   408,   486,   487,
     413,   427,   428,   429,   430,   431,   432,   433,   434,   435,
     436,   437,   438,    78,   439,   441,   443,   444,   445,   446,
     447,   448,   449,   450,   451,   453,   454,   456,   457,   458,
     455,   461,   464,   465,   459,   468,   469,   471,   474,   475,
     480,   481,   483,   462,   467,   470,   472,   473,   484,   485,
     488,   476,   490,   491,   477,   492,   493,   494,   478,   489,
     495,   479,   496,   497,   508,   510,   498,   499,   500,   501,
     502,   509,   511,   520,   512,   513,   538,   573,   573,   514,
     515,   519,   566,   566,   516,   517,   518,   521,   522,   523,
     525,   624,   526,   261,   553,   527,   417,   528,   529,   530,
     531,   416,   532,   533,   534,   535,   536,   537,   418,   539,
     540,   541,   419,   545,   555,   578,   582,   586,   602,   641,
     643,   552,   661,   647,   662,   663,   669,   672,   668,   524,
     651,   671,   674,   675,   681,   682,   719,   683,   684,   685,
     686,   687,   688,   692,   693,   694,   708,   554,   707,   711,
     710,   714,   716,   713,   702,   717,   718,   740,   705,   745,
     746,   749,   760,   748,   754,   389,   755,   761,   720,   796,
     768,   721,   770,   733,   788,   792,   734,   735,   736,   794,
     798,   811,   737,   738,   559,   414,   411,   722,   577,   729,
     732,   731,   466,   741,   739,   804,   742,   724,   743,   756,
     757,   758,   763,   764,   723,   765,   766,   769,   726,   793,
     797,   725,   813,   440,   728,   460,   727,   463,   751,   642,
     750,   442,   452,   753,   752,   744,   747,   639,   715,   482,
     786,   795,   807,   812,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   573,     0,     0,     0,     0,   566,   152,     0,   151,
     228,     0,   210,     0,     0,   227,   168,     0,     0,     0,
     171,   229,   241,   230,     0,   153,   154,   155,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   624,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   174,     0,
       0,   188,     0,     0,     0,   175,     0,     0,   189,     0,
       0,     0,   193,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     780,     0,     0,     0,     0,   779,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   780,     0,     0,
       0,     0,   779
  };

  const short int
  Dhcp4Parser::yycheck_[] =
  {
      58,    61,    65,    61,    62,    63,    64,    65,    66,    67,
      61,    62,    63,    65,    61,    65,    63,    56,   499,    61,
      61,    61,   490,   491,   318,   318,   496,     7,     5,    10,
       7,   499,     9,     7,    69,    70,     0,    17,    18,   105,
     106,   107,   108,   128,    39,    18,    19,    20,    15,     6,
      30,    31,    32,     3,    49,    35,    36,    37,     8,    39,
      18,    19,    20,    23,     3,   131,    39,    27,    48,     8,
      50,    51,    52,    53,    54,    55,    12,    13,     3,    59,
      60,    39,    40,     8,    57,    59,    66,     7,    61,    62,
      63,    64,    65,   128,    67,    40,    41,    42,    43,    44,
      58,     3,     3,     3,    11,     3,     8,     8,     8,    16,
      17,    18,     3,     3,    21,    22,     8,     8,     8,    79,
      80,    81,    82,    30,    31,    32,    33,    34,   109,    40,
       7,    38,    39,   128,   115,   116,   103,    69,    70,    23,
      24,    25,    26,    27,    28,    29,     7,   128,   128,    56,
      57,   128,   129,   130,   131,   128,    40,     3,     3,    14,
      15,    68,     8,     8,    71,    23,     7,     3,   128,     3,
     128,    78,     8,     3,     8,     7,    83,    84,     8,     7,
      87,     3,    40,   128,    42,    43,     8,    45,    46,    47,
      72,    73,    74,    75,    76,    77,   664,    85,    86,     3,
     111,     3,   113,   114,     8,     3,     8,     3,   678,     4,
       8,     3,     8,     3,   695,   509,   509,   128,     8,     3,
       3,   128,     7,     3,     8,     8,     6,   695,     7,     7,
       7,   289,    61,    62,    63,    64,     3,     3,     8,     6,
       6,   280,   281,     3,   128,     4,     6,     4,     4,     4,
       4,     4,     4,     4,     4,   318,     4,     3,   128,     4,
     318,     4,     3,     3,     8,     4,     8,   318,     4,     4,
     128,   318,   332,     4,   332,     4,     4,   335,     4,     4,
       4,   332,     4,     4,   335,   332,     4,     4,     4,   347,
     332,   332,   332,   131,   131,     4,   347,   360,   356,     4,
     347,     4,   360,   129,   129,   129,   129,     4,   360,     4,
     360,   117,   118,   119,   120,   121,   122,   123,   124,   125,
     126,   127,   380,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,     4,     4,
       4,     4,     4,     4,     4,     4,     4,   129,   387,   388,
       4,     4,     4,     4,     4,     4,     4,     4,   129,   131,
       4,     4,     4,   128,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
     129,     4,     4,     4,   131,     4,     4,     4,     4,     4,
       4,     4,     4,   131,   131,   129,   129,   129,     7,     7,
       7,   131,     7,     7,   131,     5,     5,     5,   131,   128,
       5,   131,     5,     5,     8,   128,     7,     7,     7,     7,
       5,     3,   128,     7,   128,     5,   465,   490,   491,   128,
     128,     5,   490,   491,   128,   128,   128,   128,   128,   128,
     128,   499,   128,   501,   483,   128,   509,   128,   128,   128,
     128,   509,   128,   128,   128,   128,   128,   128,   509,   128,
     128,   128,   509,   104,   110,     7,     7,     7,     7,     4,
       7,   128,     4,     7,     4,     4,     3,     3,     6,   445,
      67,     6,     6,     3,     6,     3,   131,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     3,   484,     6,     3,
       6,     4,     4,     8,   128,     4,     4,     4,   128,     4,
       4,     3,     8,     6,     4,   289,     5,     8,   129,     5,
       8,   131,     7,   129,     4,     4,   129,   129,   129,     4,
       7,     4,   129,   129,   488,   316,   312,   664,   491,   676,
     682,   680,   363,   129,   689,   112,   129,   669,   129,   128,
     128,   128,   128,   128,   667,   128,   128,   128,   672,   129,
     128,   670,   128,   332,   675,   356,   673,   360,   708,   509,
     706,   335,   347,   711,   709,   695,   699,   501,   655,   380,
     774,   790,   802,   809,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   664,    -1,    -1,    -1,    -1,   664,   667,    -1,   667,
     673,    -1,   670,    -1,    -1,   673,   667,    -1,    -1,    -1,
     667,   673,   680,   673,    -1,   667,   667,   667,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   695,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   706,    -1,
      -1,   709,    -1,    -1,    -1,   706,    -1,    -1,   709,    -1,
      -1,    -1,   709,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     773,    -1,    -1,    -1,    -1,   773,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   790,    -1,    -1,
      -1,    -1,   790
  };

  const unsigned short int
  Dhcp4Parser::yystos_[] =
  {
       0,   117,   118,   119,   120,   121,   122,   123,   124,   125,
     126,   127,   133,   134,   135,   136,   137,   138,   139,   140,
     141,   142,   143,   144,     0,     5,     7,     9,   128,   129,
     130,   131,   145,   146,   147,   151,     7,   160,     7,   166,
       7,   180,     7,   244,     7,   312,     7,   324,     7,   272,
       7,   295,     7,   220,     7,   383,   152,   148,   161,   167,
     181,   245,   313,   325,   273,   296,   221,   384,   145,   153,
     154,   128,   149,   150,    10,   109,   115,   116,   128,   159,
     162,   163,   164,   411,   413,   415,    11,    16,    17,    18,
      21,    22,    30,    31,    32,    33,    34,    38,    39,    56,
      57,    68,    71,    78,    83,    84,    87,   159,   168,   169,
     170,   171,   172,   173,   174,   175,   176,   187,   189,   207,
     214,   228,   238,   266,   289,   329,   353,   363,   372,   373,
     381,    12,    13,   178,   179,   182,   184,     7,    35,    36,
      37,    48,    50,    51,    52,    53,    54,    55,    59,    60,
      66,   159,   170,   171,   172,   175,   246,   247,   248,   250,
     252,   254,   256,   258,   260,   262,   264,   265,   289,   306,
     318,   329,   349,    49,   159,   289,   314,   315,   316,    19,
      20,    57,    61,    62,    63,    64,    65,    67,   159,   289,
     326,   327,   328,   329,   331,   333,   335,   337,   339,   341,
     343,   345,   347,    23,    40,    42,    43,    45,    46,    47,
     159,   193,   201,   274,   275,   276,   277,   278,   279,   280,
     281,   283,   285,   286,   288,    41,    44,   159,   201,   278,
     283,   297,   298,   299,   300,   301,   303,   304,   305,    69,
      70,   159,   222,   223,   224,   226,    88,    89,    90,    91,
      92,    93,    94,    95,    96,    97,    98,    99,   100,   101,
     102,   159,   385,   386,   387,   388,   390,   392,   393,   395,
     396,   397,   400,   402,   403,   404,   405,   406,   409,     6,
       3,     4,     8,     3,   165,   416,   412,   414,     4,     3,
       8,   177,     4,     4,   330,   188,   190,     4,     4,     4,
       4,   239,   267,   290,   208,   354,   215,   229,   364,     4,
     374,   382,     3,     8,   183,   185,     3,     8,   356,   251,
     253,   255,   307,   249,   257,   259,     4,     4,   263,   261,
     319,   350,     3,     8,   317,     3,     8,   332,   334,   348,
     338,   340,   344,   342,   346,   336,     8,     3,   194,   202,
       4,   284,   282,   287,     4,     8,     3,   302,     4,     8,
       3,   225,   227,     3,     8,     4,   389,   391,     4,   394,
       4,     4,   398,   401,     4,     4,     4,     4,   407,   410,
       3,     8,   145,   145,   128,     4,     4,     4,     4,   163,
       4,   131,   131,     4,     4,     4,   129,   129,   129,   129,
       4,     4,     4,     4,     4,     4,     4,     4,   129,     4,
       4,   169,     4,     4,   179,    58,   159,   201,   289,   329,
     331,   333,   357,   358,   359,   360,   361,     4,     4,     4,
       4,     4,     4,     4,   129,   131,     4,     4,     4,     4,
     247,     4,   315,     4,     4,     4,     4,     4,     4,     4,
       4,     4,   328,     4,     4,   129,     4,     4,     4,   131,
     276,     4,   131,   299,     4,     4,   223,   131,     4,     4,
     129,     4,   129,   129,     4,     4,   131,   131,   131,   131,
       4,     4,   386,     4,     7,     7,   145,   145,     7,   128,
       7,     7,     5,     5,     5,     5,     5,     5,     7,     7,
       7,     7,     5,   155,    14,    15,   186,   362,     8,     3,
     128,   128,   128,     5,   128,   128,   128,   128,   128,     5,
       7,   128,   128,   128,   155,   128,   128,   128,   128,   128,
     128,   128,   128,   128,   128,   128,   128,   128,   145,   128,
     128,   128,    15,   103,   399,   104,   105,   106,   107,   108,
     131,   408,   128,   145,   168,   110,   417,   418,   419,   178,
      24,    25,    26,    27,    28,    29,   159,   191,   192,   193,
     195,   197,   199,   201,   203,   204,   205,   191,     7,   240,
     241,   242,     7,   268,   269,   270,     7,   291,   292,   293,
      61,    62,    63,    64,   206,   209,   210,   211,   212,   213,
     260,   355,     7,   216,   217,   218,    72,    73,    74,    75,
      76,    77,   230,   231,   232,   233,   234,   235,   236,   237,
      79,    80,    81,    82,   159,   193,   203,   365,   366,   367,
     368,   370,   371,    85,    86,   375,   376,   377,   379,   385,
     156,     4,   359,     7,   308,   309,   310,     7,   320,   321,
     322,    67,   351,     8,   420,     3,     8,     8,   196,   198,
     200,     4,     4,     4,     3,     8,     8,   243,     6,     3,
     271,     6,     3,   294,     6,     3,     3,     6,     3,     6,
     219,     6,     3,     4,     4,     4,     4,     4,     4,     3,
       8,   369,     4,     4,     4,     3,     8,   378,   380,     3,
       8,     8,   128,   157,   158,   128,   311,     6,     3,   323,
       6,     3,   352,     8,     4,   418,     4,     4,     4,   131,
     129,   131,   192,   246,   242,   274,   270,   297,   293,   210,
     260,   222,   218,   129,   129,   129,   129,   129,   129,   231,
       4,   129,   129,   129,   366,     4,     4,   376,     6,     3,
     314,   310,   326,   322,     4,     5,   128,   128,   128,     8,
       8,     8,     8,   128,   128,   128,   128,     8,     8,   128,
       7,   421,   422,   423,     3,     6,   111,   113,   114,   159,
     201,   424,   425,   426,   427,   429,   422,   430,     4,   428,
       3,     8,     4,   129,     4,   425,     5,   128,     7,   431,
     432,   433,     3,     6,   112,   434,   435,   432,   436,     3,
       8,     4,   435,   128
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
     169,   169,   169,   169,   169,   169,   169,   169,   170,   171,
     172,   173,   174,   175,   177,   176,   178,   178,   179,   179,
     181,   180,   183,   182,   185,   184,   186,   186,   188,   187,
     190,   189,   191,   191,   192,   192,   192,   192,   192,   192,
     192,   192,   192,   194,   193,   196,   195,   198,   197,   200,
     199,   202,   201,   203,   204,   205,   206,   208,   207,   209,
     209,   210,   210,   210,   210,   211,   212,   213,   215,   214,
     216,   216,   217,   217,   219,   218,   221,   220,   222,   222,
     222,   223,   223,   225,   224,   227,   226,   229,   228,   230,
     230,   231,   231,   231,   231,   231,   231,   232,   233,   234,
     235,   236,   237,   239,   238,   240,   240,   241,   241,   243,
     242,   245,   244,   246,   246,   247,   247,   247,   247,   247,
     247,   247,   247,   247,   247,   247,   247,   247,   247,   247,
     247,   247,   247,   247,   247,   249,   248,   251,   250,   253,
     252,   255,   254,   257,   256,   259,   258,   261,   260,   263,
     262,   264,   265,   267,   266,   268,   268,   269,   269,   271,
     270,   273,   272,   274,   274,   275,   275,   276,   276,   276,
     276,   276,   276,   276,   276,   277,   278,   279,   280,   282,
     281,   284,   283,   285,   287,   286,   288,   290,   289,   291,
     291,   292,   292,   294,   293,   296,   295,   297,   297,   298,
     298,   299,   299,   299,   299,   299,   299,   300,   302,   301,
     303,   304,   305,   307,   306,   308,   308,   309,   309,   311,
     310,   313,   312,   314,   314,   315,   315,   315,   317,   316,
     319,   318,   320,   320,   321,   321,   323,   322,   325,   324,
     326,   326,   327,   327,   328,   328,   328,   328,   328,   328,
     328,   328,   328,   328,   328,   328,   330,   329,   332,   331,
     334,   333,   336,   335,   338,   337,   340,   339,   342,   341,
     344,   343,   346,   345,   348,   347,   350,   349,   352,   351,
     354,   353,   355,   355,   356,   260,   357,   357,   358,   358,
     359,   359,   359,   359,   359,   359,   359,   360,   362,   361,
     364,   363,   365,   365,   366,   366,   366,   366,   366,   366,
     366,   367,   369,   368,   370,   371,   372,   374,   373,   375,
     375,   376,   376,   378,   377,   380,   379,   382,   381,   384,
     383,   385,   385,   386,   386,   386,   386,   386,   386,   386,
     386,   386,   386,   386,   386,   386,   386,   386,   386,   387,
     389,   388,   391,   390,   392,   394,   393,   395,   396,   398,
     397,   399,   399,   401,   400,   402,   403,   404,   405,   407,
     406,   408,   408,   408,   408,   408,   410,   409,   412,   411,
     414,   413,   416,   415,   417,   417,   418,   420,   419,   421,
     421,   423,   422,   424,   424,   425,   425,   425,   425,   425,
     426,   428,   427,   430,   429,   431,   431,   433,   432,   434,
     434,   436,   435
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
       1,     1,     1,     1,     1,     1,     1,     1,     3,     3,
       3,     3,     3,     3,     0,     6,     1,     3,     1,     1,
       0,     4,     0,     4,     0,     4,     1,     1,     0,     6,
       0,     6,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     0,     4,     0,     4,     0,     4,     0,
       4,     0,     4,     3,     3,     3,     1,     0,     6,     1,
       3,     1,     1,     1,     1,     1,     1,     1,     0,     6,
       0,     1,     1,     3,     0,     4,     0,     4,     1,     3,
       1,     1,     1,     0,     4,     0,     4,     0,     6,     1,
       3,     1,     1,     1,     1,     1,     1,     3,     3,     3,
       3,     3,     3,     0,     6,     0,     1,     1,     3,     0,
       4,     0,     4,     1,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       4,     3,     3,     0,     6,     0,     1,     1,     3,     0,
       4,     0,     4,     0,     1,     1,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     3,     1,     1,     0,
       4,     0,     4,     1,     0,     4,     3,     0,     6,     0,
       1,     1,     3,     0,     4,     0,     4,     0,     1,     1,
       3,     1,     1,     1,     1,     1,     1,     1,     0,     4,
       1,     1,     3,     0,     6,     0,     1,     1,     3,     0,
       4,     0,     4,     1,     3,     1,     1,     1,     0,     4,
       0,     6,     0,     1,     1,     3,     0,     4,     0,     4,
       0,     1,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     0,     4,     0,     4,
       0,     4,     0,     4,     0,     4,     0,     4,     0,     4,
       0,     4,     0,     4,     0,     4,     0,     6,     0,     4,
       0,     6,     1,     3,     0,     4,     0,     1,     1,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     0,     4,
       0,     6,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     3,     0,     4,     3,     3,     3,     0,     6,     1,
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
     277,   278,   281,   285,   292,   292,   299,   300,   303,   307,
     318,   328,   328,   340,   341,   345,   346,   347,   348,   349,
     352,   352,   369,   369,   377,   378,   383,   384,   385,   386,
     387,   388,   389,   390,   391,   392,   393,   394,   395,   396,
     397,   398,   399,   400,   401,   402,   403,   404,   407,   412,
     417,   422,   427,   432,   438,   438,   448,   449,   452,   453,
     456,   456,   464,   464,   474,   474,   481,   482,   485,   485,
     495,   495,   505,   506,   509,   510,   511,   512,   513,   514,
     515,   516,   517,   520,   520,   528,   528,   536,   536,   544,
     544,   552,   552,   560,   565,   570,   575,   580,   580,   590,
     591,   594,   595,   596,   597,   600,   605,   610,   615,   615,
     625,   626,   629,   630,   633,   633,   641,   641,   649,   650,
     651,   654,   655,   658,   658,   666,   666,   674,   674,   684,
     685,   688,   689,   690,   691,   692,   693,   696,   701,   706,
     711,   716,   721,   729,   729,   742,   743,   746,   747,   754,
     754,   777,   777,   786,   787,   791,   792,   793,   794,   795,
     796,   797,   798,   799,   800,   801,   802,   803,   804,   805,
     806,   807,   808,   809,   810,   813,   813,   821,   821,   829,
     829,   837,   837,   845,   845,   853,   853,   861,   861,   869,
     869,   877,   882,   891,   891,   903,   904,   907,   908,   913,
     913,   924,   924,   934,   935,   938,   939,   942,   943,   944,
     945,   946,   947,   948,   949,   952,   954,   959,   961,   963,
     963,   971,   971,   979,   981,   981,   989,   998,   998,  1010,
    1011,  1016,  1017,  1022,  1022,  1033,  1033,  1044,  1045,  1050,
    1051,  1056,  1057,  1058,  1059,  1060,  1061,  1064,  1066,  1066,
    1074,  1076,  1078,  1086,  1086,  1098,  1099,  1102,  1103,  1106,
    1106,  1114,  1114,  1122,  1123,  1126,  1127,  1128,  1131,  1131,
    1142,  1142,  1152,  1153,  1156,  1157,  1160,  1160,  1168,  1168,
    1176,  1177,  1180,  1181,  1185,  1186,  1187,  1188,  1189,  1190,
    1191,  1192,  1193,  1194,  1195,  1196,  1199,  1199,  1207,  1207,
    1215,  1215,  1223,  1223,  1231,  1231,  1239,  1239,  1247,  1247,
    1255,  1255,  1264,  1264,  1272,  1272,  1285,  1285,  1295,  1295,
    1306,  1306,  1316,  1317,  1320,  1320,  1328,  1329,  1332,  1333,
    1336,  1337,  1338,  1339,  1340,  1341,  1342,  1345,  1347,  1347,
    1358,  1358,  1368,  1369,  1372,  1373,  1374,  1375,  1376,  1377,
    1378,  1381,  1386,  1386,  1394,  1399,  1406,  1413,  1413,  1423,
    1424,  1427,  1428,  1431,  1431,  1439,  1439,  1449,  1449,  1459,
    1459,  1467,  1468,  1471,  1472,  1473,  1474,  1475,  1476,  1477,
    1478,  1479,  1480,  1481,  1482,  1483,  1484,  1485,  1486,  1489,
    1494,  1494,  1502,  1502,  1510,  1515,  1515,  1523,  1528,  1533,
    1533,  1541,  1542,  1545,  1545,  1553,  1558,  1563,  1568,  1573,
    1573,  1581,  1584,  1587,  1590,  1593,  1599,  1599,  1609,  1609,
    1616,  1616,  1628,  1628,  1641,  1642,  1646,  1650,  1650,  1662,
    1663,  1667,  1667,  1675,  1676,  1679,  1680,  1681,  1682,  1683,
    1686,  1690,  1690,  1698,  1698,  1708,  1709,  1712,  1712,  1720,
    1721,  1724,  1724
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
#line 3978 "dhcp4_parser.cc" // lalr1.cc:1167
#line 1732 "dhcp4_parser.yy" // lalr1.cc:1168


void
isc::dhcp::Dhcp4Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
