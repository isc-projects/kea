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
      case 156: // value
      case 160: // map_value
      case 198: // socket_type
      case 208: // db_type
      case 285: // hr_mode
      case 417: // ncr_protocol_value
      case 425: // replace_client_name_value
        value.move< ElementPtr > (that.value);
        break;

      case 142: // "boolean"
        value.move< bool > (that.value);
        break;

      case 141: // "floating point"
        value.move< double > (that.value);
        break;

      case 140: // "integer"
        value.move< int64_t > (that.value);
        break;

      case 139: // "constant string"
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
      case 156: // value
      case 160: // map_value
      case 198: // socket_type
      case 208: // db_type
      case 285: // hr_mode
      case 417: // ncr_protocol_value
      case 425: // replace_client_name_value
        value.copy< ElementPtr > (that.value);
        break;

      case 142: // "boolean"
        value.copy< bool > (that.value);
        break;

      case 141: // "floating point"
        value.copy< double > (that.value);
        break;

      case 140: // "integer"
        value.copy< int64_t > (that.value);
        break;

      case 139: // "constant string"
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
            case 139: // "constant string"

#line 215 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< std::string > (); }
#line 364 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 140: // "integer"

#line 215 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< int64_t > (); }
#line 371 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 141: // "floating point"

#line 215 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< double > (); }
#line 378 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 142: // "boolean"

#line 215 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< bool > (); }
#line 385 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 156: // value

#line 215 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 392 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 160: // map_value

#line 215 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 399 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 198: // socket_type

#line 215 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 406 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 208: // db_type

#line 215 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 413 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 285: // hr_mode

#line 215 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 420 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 417: // ncr_protocol_value

#line 215 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 427 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 425: // replace_client_name_value

#line 215 "dhcp4_parser.yy" // lalr1.cc:636
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
      case 156: // value
      case 160: // map_value
      case 198: // socket_type
      case 208: // db_type
      case 285: // hr_mode
      case 417: // ncr_protocol_value
      case 425: // replace_client_name_value
        yylhs.value.build< ElementPtr > ();
        break;

      case 142: // "boolean"
        yylhs.value.build< bool > ();
        break;

      case 141: // "floating point"
        yylhs.value.build< double > ();
        break;

      case 140: // "integer"
        yylhs.value.build< int64_t > ();
        break;

      case 139: // "constant string"
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
#line 224 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.NO_KEYWORD; }
#line 680 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 4:
#line 225 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.CONFIG; }
#line 686 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 6:
#line 226 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.DHCP4; }
#line 692 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 8:
#line 227 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.INTERFACES_CONFIG; }
#line 698 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 10:
#line 228 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.SUBNET4; }
#line 704 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 12:
#line 229 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.POOLS; }
#line 710 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 14:
#line 230 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.RESERVATIONS; }
#line 716 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 16:
#line 231 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.OPTION_DEF; }
#line 722 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 18:
#line 232 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.OPTION_DATA; }
#line 728 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 20:
#line 233 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.HOOKS_LIBRARIES; }
#line 734 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 22:
#line 234 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.DHCP_DDNS; }
#line 740 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 24:
#line 242 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 746 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 25:
#line 243 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as< double > (), ctx.loc2pos(yystack_[0].location))); }
#line 752 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 26:
#line 244 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 758 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 27:
#line 245 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 764 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 28:
#line 246 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 770 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 29:
#line 247 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 776 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 30:
#line 248 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 782 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 31:
#line 251 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as< ElementPtr > ());
}
#line 791 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 32:
#line 256 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 802 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 33:
#line 261 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 812 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 34:
#line 267 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 818 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 37:
#line 274 "dhcp4_parser.yy" // lalr1.cc:859
    {
                  // map containing a single entry
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 827 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 38:
#line 278 "dhcp4_parser.yy" // lalr1.cc:859
    {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 837 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 39:
#line 285 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 846 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 40:
#line 288 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // list parsing complete. Put any sanity checking here
}
#line 854 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 43:
#line 296 "dhcp4_parser.yy" // lalr1.cc:859
    {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 863 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 44:
#line 300 "dhcp4_parser.yy" // lalr1.cc:859
    {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 872 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 45:
#line 307 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // List parsing about to start
}
#line 880 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 46:
#line 309 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // list parsing complete. Put any sanity checking here
    //ctx.stack_.pop_back();
}
#line 889 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 49:
#line 318 "dhcp4_parser.yy" // lalr1.cc:859
    {
                          ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 898 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 50:
#line 322 "dhcp4_parser.yy" // lalr1.cc:859
    {
                          ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 907 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 51:
#line 333 "dhcp4_parser.yy" // lalr1.cc:859
    {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as< std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 918 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 52:
#line 343 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 929 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 53:
#line 348 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 939 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 61:
#line 367 "dhcp4_parser.yy" // lalr1.cc:859
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
#line 374 "dhcp4_parser.yy" // lalr1.cc:859
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
#line 384 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the Dhcp4 map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 974 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 64:
#line 388 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 982 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 88:
#line 421 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 991 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 89:
#line 426 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 1000 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 90:
#line 431 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 1009 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 91:
#line 436 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr dpp(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 1018 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 92:
#line 441 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr echo(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("echo-client-id", echo);
}
#line 1027 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 93:
#line 446 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr match(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("match-client-id", match);
}
#line 1036 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 94:
#line 452 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces-config", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.INTERFACES_CONFIG);
}
#line 1047 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 95:
#line 457 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1056 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 101:
#line 471 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1066 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 102:
#line 475 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1074 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 103:
#line 479 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1085 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 104:
#line 484 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1094 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 105:
#line 489 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.DHCP_SOCKET_TYPE);
}
#line 1102 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 106:
#line 491 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("dhcp-socket-type", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1111 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 107:
#line 496 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("raw", ctx.loc2pos(yystack_[0].location))); }
#line 1117 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 108:
#line 497 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("udp", ctx.loc2pos(yystack_[0].location))); }
#line 1123 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 109:
#line 500 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("re-detect", b);
}
#line 1132 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 110:
#line 506 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lease-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.LEASE_DATABASE);
}
#line 1143 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 111:
#line 511 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1152 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 112:
#line 516 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1163 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 113:
#line 521 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1172 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 129:
#line 545 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.DATABASE_TYPE);
}
#line 1180 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 130:
#line 547 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("type", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1189 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 131:
#line 552 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("memfile", ctx.loc2pos(yystack_[0].location))); }
#line 1195 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 132:
#line 553 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("mysql", ctx.loc2pos(yystack_[0].location))); }
#line 1201 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 133:
#line 554 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("postgresql", ctx.loc2pos(yystack_[0].location))); }
#line 1207 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 134:
#line 555 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("cql", ctx.loc2pos(yystack_[0].location))); }
#line 1213 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 135:
#line 558 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1221 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 136:
#line 560 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr user(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1231 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 137:
#line 566 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1239 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 138:
#line 568 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr pwd(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 1249 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 139:
#line 574 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1257 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 140:
#line 576 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr h(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 1267 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 141:
#line 582 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr p(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", p);
}
#line 1276 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 142:
#line 587 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1284 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 143:
#line 589 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1294 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 144:
#line 595 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 1303 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 145:
#line 600 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 1312 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 146:
#line 605 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 1321 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 147:
#line 610 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("connect-timeout", n);
}
#line 1330 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 148:
#line 615 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1338 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 149:
#line 617 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr cp(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("contact-points", cp);
    ctx.leave();
}
#line 1348 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 150:
#line 623 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1356 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 151:
#line 625 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr ks(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("keyspace", ks);
    ctx.leave();
}
#line 1366 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 152:
#line 632 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 1377 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 153:
#line 637 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1386 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 161:
#line 653 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1395 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 162:
#line 658 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 1404 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 163:
#line 663 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr circuit(new StringElement("circuit-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(circuit);
}
#line 1413 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 164:
#line 668 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr client(new StringElement("client-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(client);
}
#line 1422 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 165:
#line 673 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr flex_id(new StringElement("flex-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(flex_id);
}
#line 1431 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 166:
#line 678 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 1442 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 167:
#line 683 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1451 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 172:
#line 696 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1461 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 173:
#line 700 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1469 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 174:
#line 704 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1479 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 175:
#line 708 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1487 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 181:
#line 721 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1495 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 182:
#line 723 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr lib(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 1505 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 183:
#line 729 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1513 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 184:
#line 731 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1522 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 185:
#line 737 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.EXPIRED_LEASES_PROCESSING);
}
#line 1533 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 186:
#line 742 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1542 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 195:
#line 759 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 1551 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 196:
#line 764 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 1560 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 197:
#line 769 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 1569 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 198:
#line 774 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 1578 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 199:
#line 779 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 1587 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 200:
#line 784 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 1596 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 201:
#line 792 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet4", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET4);
}
#line 1607 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 202:
#line 797 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1616 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 207:
#line 817 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1626 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 208:
#line 821 "dhcp4_parser.yy" // lalr1.cc:859
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
#line 1649 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 209:
#line 840 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the subnet4 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1659 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 210:
#line 844 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1667 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 233:
#line 876 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1675 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 234:
#line 878 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr subnet(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 1685 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 235:
#line 884 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1693 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 236:
#line 886 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface", iface);
    ctx.leave();
}
#line 1703 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 237:
#line 892 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1711 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 238:
#line 894 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface-id", iface);
    ctx.leave();
}
#line 1721 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 239:
#line 900 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1729 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 240:
#line 902 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-subnet", iface);
    ctx.leave();
}
#line 1739 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 241:
#line 908 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1747 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 242:
#line 910 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 1757 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 243:
#line 916 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1765 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 244:
#line 918 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface-id", iface);
    ctx.leave();
}
#line 1775 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 245:
#line 924 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.CLIENT_CLASS);
}
#line 1783 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 246:
#line 926 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr cls(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 1793 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 247:
#line 932 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.RESERVATION_MODE);
}
#line 1801 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 248:
#line 934 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("reservation-mode", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1810 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 249:
#line 939 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("disabled", ctx.loc2pos(yystack_[0].location))); }
#line 1816 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 250:
#line 940 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("out-of-pool", ctx.loc2pos(yystack_[0].location))); }
#line 1822 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 251:
#line 941 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("all", ctx.loc2pos(yystack_[0].location))); }
#line 1828 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 252:
#line 944 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr id(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 1837 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 253:
#line 949 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr rc(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rapid-commit", rc);
}
#line 1846 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 254:
#line 958 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 1857 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 255:
#line 963 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1866 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 260:
#line 980 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1876 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 261:
#line 984 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1884 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 262:
#line 991 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1894 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 263:
#line 995 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1902 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 277:
#line 1021 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr code(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 1911 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 279:
#line 1028 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1919 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 280:
#line 1030 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 1929 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 281:
#line 1036 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1937 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 282:
#line 1038 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 1947 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 283:
#line 1044 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1955 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 284:
#line 1046 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr space(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 1965 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 286:
#line 1054 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1973 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 287:
#line 1056 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr encap(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 1983 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 288:
#line 1062 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr array(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 1992 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 289:
#line 1071 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 2003 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 290:
#line 1076 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2012 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 295:
#line 1095 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2022 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 296:
#line 1099 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2030 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 297:
#line 1106 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2040 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 298:
#line 1110 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 2048 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 310:
#line 1139 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2056 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 311:
#line 1141 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr data(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 2066 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 314:
#line 1151 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr space(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", space);
}
#line 2075 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 315:
#line 1159 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 2086 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 316:
#line 1164 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2095 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 321:
#line 1179 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2105 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 322:
#line 1183 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2113 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 323:
#line 1187 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2123 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 324:
#line 1191 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 2131 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 331:
#line 1205 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2139 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 332:
#line 1207 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr pool(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 2149 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 333:
#line 1213 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2157 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 334:
#line 1215 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("user-context", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2166 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 335:
#line 1223 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 2177 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 336:
#line 1228 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2186 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 341:
#line 1241 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2196 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 342:
#line 1245 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2204 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 343:
#line 1249 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2214 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 344:
#line 1253 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 2222 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 362:
#line 1281 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2230 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 363:
#line 1283 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr next_server(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("next-server", next_server);
    ctx.leave();
}
#line 2240 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 364:
#line 1289 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2248 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 365:
#line 1291 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr srv(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-hostname", srv);
    ctx.leave();
}
#line 2258 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 366:
#line 1297 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2266 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 367:
#line 1299 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr bootfile(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("boot-file-name", bootfile);
    ctx.leave();
}
#line 2276 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 368:
#line 1305 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2284 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 369:
#line 1307 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr addr(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", addr);
    ctx.leave();
}
#line 2294 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 370:
#line 1313 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2302 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 371:
#line 1315 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr d(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 2312 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 372:
#line 1321 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2320 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 373:
#line 1323 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 2330 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 374:
#line 1329 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2338 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 375:
#line 1331 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-id", hw);
    ctx.leave();
}
#line 2348 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 376:
#line 1337 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2356 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 377:
#line 1339 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("circuit-id", hw);
    ctx.leave();
}
#line 2366 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 378:
#line 1345 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2374 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 379:
#line 1347 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flex-id", hw);
    ctx.leave();
}
#line 2384 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 380:
#line 1353 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2392 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 381:
#line 1355 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr host(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 2402 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 382:
#line 1361 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2413 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 383:
#line 1366 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2422 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 384:
#line 1374 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 2433 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 385:
#line 1379 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2442 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 386:
#line 1384 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2450 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 387:
#line 1386 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr ip(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", ip);
    ctx.leave();
}
#line 2460 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 388:
#line 1395 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 2471 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 389:
#line 1400 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2480 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 392:
#line 1409 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2490 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 393:
#line 1413 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2498 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 406:
#line 1436 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2506 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 407:
#line 1438 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr test(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 2516 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 408:
#line 1448 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 2525 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 409:
#line 1455 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 2536 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 410:
#line 1460 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2545 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 415:
#line 1473 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2553 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 416:
#line 1475 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr stype(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 2563 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 417:
#line 1481 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2571 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 418:
#line 1483 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 2581 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 419:
#line 1491 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 2592 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 420:
#line 1496 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2601 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 421:
#line 1501 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2611 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 422:
#line 1505 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 2619 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 440:
#line 1530 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 2628 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 441:
#line 1535 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2636 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 442:
#line 1537 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("qualifying-suffix", s);
    ctx.leave();
}
#line 2646 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 443:
#line 1543 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2654 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 444:
#line 1545 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 2664 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 445:
#line 1551 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 2673 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 446:
#line 1556 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2681 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 447:
#line 1558 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 2691 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 448:
#line 1564 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 2700 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 449:
#line 1569 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 2709 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 450:
#line 1574 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 2717 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 451:
#line 1576 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2726 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 452:
#line 1582 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 2732 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 453:
#line 1583 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 2738 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 454:
#line 1586 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NCR_FORMAT);
}
#line 2746 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 455:
#line 1588 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 2756 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 456:
#line 1594 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-include-fqdn", b);
}
#line 2765 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 457:
#line 1599 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-no-update", b);
}
#line 2774 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 458:
#line 1604 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-client-update", b);
}
#line 2783 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 459:
#line 1609 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 2791 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 460:
#line 1611 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("replace-client-name", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2800 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 461:
#line 1617 "dhcp4_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("when-present", ctx.loc2pos(yystack_[0].location))); 
      }
#line 2808 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 462:
#line 1620 "dhcp4_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location)));
      }
#line 2816 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 463:
#line 1623 "dhcp4_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("always", ctx.loc2pos(yystack_[0].location)));
      }
#line 2824 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 464:
#line 1626 "dhcp4_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("when-not-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 2832 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 465:
#line 1629 "dhcp4_parser.yy" // lalr1.cc:859
    {
      error(yystack_[0].location, "boolean values for the replace-client-name are "
                "no longer supported");
      }
#line 2841 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 466:
#line 1635 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2849 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 467:
#line 1637 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("generated-prefix", s);
    ctx.leave();
}
#line 2859 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 468:
#line 1645 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2867 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 469:
#line 1647 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("Dhcp6", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2876 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 470:
#line 1652 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2884 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 471:
#line 1654 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("DhcpDdns", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2893 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 472:
#line 1664 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Logging", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.LOGGING);
}
#line 2904 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 473:
#line 1669 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2913 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 477:
#line 1686 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 2924 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 478:
#line 1691 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2933 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 481:
#line 1703 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 2943 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 482:
#line 1707 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2951 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 490:
#line 1722 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr dl(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 2960 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 491:
#line 1727 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2968 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 492:
#line 1729 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 2978 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 493:
#line 1735 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 2989 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 494:
#line 1740 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2998 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 497:
#line 1749 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3008 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 498:
#line 1753 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 3016 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 505:
#line 1767 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3024 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 506:
#line 1769 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 3034 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 507:
#line 1775 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr flush(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 3043 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 508:
#line 1780 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr maxsize(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 3052 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 509:
#line 1785 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr maxver(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 3061 "dhcp4_parser.cc" // lalr1.cc:859
    break;


#line 3065 "dhcp4_parser.cc" // lalr1.cc:859
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


  const short int Dhcp4Parser::yypact_ninf_ = -477;

  const signed char Dhcp4Parser::yytable_ninf_ = -1;

  const short int
  Dhcp4Parser::yypact_[] =
  {
     105,  -477,  -477,  -477,  -477,  -477,  -477,  -477,  -477,  -477,
    -477,  -477,    60,    19,    47,    62,    67,    85,   109,   122,
     128,   134,   144,   156,  -477,  -477,  -477,  -477,  -477,  -477,
    -477,  -477,  -477,  -477,  -477,  -477,  -477,  -477,  -477,  -477,
    -477,  -477,  -477,  -477,  -477,  -477,  -477,  -477,  -477,  -477,
    -477,  -477,  -477,  -477,  -477,  -477,    19,    35,    17,    54,
     106,    18,   -19,    92,    76,   -18,   -35,   119,  -477,    82,
      96,   171,   168,   185,  -477,  -477,  -477,  -477,   190,  -477,
      53,  -477,  -477,  -477,  -477,  -477,  -477,   206,   208,  -477,
    -477,  -477,   226,   259,   262,   266,  -477,  -477,  -477,  -477,
    -477,  -477,  -477,   270,  -477,  -477,  -477,    81,  -477,  -477,
    -477,  -477,  -477,  -477,  -477,  -477,  -477,  -477,  -477,  -477,
    -477,  -477,  -477,  -477,  -477,  -477,  -477,  -477,  -477,  -477,
    -477,   276,   130,  -477,  -477,  -477,  -477,  -477,  -477,  -477,
    -477,  -477,  -477,  -477,  -477,   280,   284,  -477,  -477,  -477,
    -477,  -477,  -477,  -477,  -477,  -477,   145,  -477,  -477,  -477,
    -477,  -477,  -477,  -477,  -477,  -477,  -477,  -477,  -477,  -477,
    -477,  -477,  -477,  -477,  -477,  -477,  -477,   146,  -477,  -477,
    -477,  -477,  -477,  -477,  -477,  -477,  -477,  -477,  -477,  -477,
    -477,  -477,  -477,   243,   274,  -477,  -477,  -477,  -477,  -477,
    -477,  -477,  -477,  -477,  -477,  -477,  -477,  -477,  -477,   290,
    -477,  -477,  -477,   292,  -477,  -477,   289,   301,  -477,  -477,
    -477,  -477,  -477,  -477,  -477,  -477,  -477,  -477,  -477,   306,
    -477,  -477,  -477,  -477,   303,   309,  -477,  -477,  -477,  -477,
    -477,  -477,  -477,  -477,  -477,   188,  -477,  -477,  -477,   311,
    -477,  -477,   313,  -477,   314,   315,  -477,  -477,   316,   317,
     318,  -477,  -477,  -477,   201,  -477,  -477,  -477,  -477,  -477,
    -477,  -477,  -477,  -477,  -477,  -477,  -477,  -477,  -477,  -477,
    -477,    19,    19,  -477,   174,   319,   321,   322,   323,  -477,
      17,  -477,   324,   187,   191,   326,   327,   328,   194,   195,
     196,   197,   334,   335,   336,   337,   338,   339,   340,   207,
     341,   342,    54,  -477,   344,   345,   209,   106,  -477,    66,
     346,   348,   351,   352,   353,   354,   355,   220,   219,   358,
     359,   360,   361,    18,  -477,   362,   363,   -19,  -477,   364,
     365,   366,   367,   368,   369,   370,   371,   372,   373,  -477,
      92,   374,   375,   240,   377,   378,   379,   242,  -477,    76,
     381,   246,  -477,   -18,   382,   383,   -16,  -477,   248,   385,
     387,   252,   389,   255,   256,   390,   393,   258,   260,   263,
     394,   395,   119,  -477,  -477,  -477,   397,   396,   399,    19,
      19,  -477,   400,  -477,  -477,   265,   401,   402,  -477,  -477,
    -477,  -477,   405,   406,   407,   408,   409,   410,   411,  -477,
     412,   413,  -477,   416,   150,  -477,  -477,  -477,  -477,  -477,
    -477,  -477,  -477,  -477,   414,   420,  -477,  -477,  -477,   277,
     278,   285,   421,   286,   288,   293,  -477,  -477,   -21,   298,
     423,   422,  -477,   299,   427,  -477,   300,   302,   416,   304,
     305,   307,   308,   310,   312,   320,  -477,   325,   329,  -477,
     330,   331,   332,  -477,  -477,   333,  -477,  -477,   343,    19,
    -477,  -477,   347,   349,  -477,   350,  -477,  -477,    15,   380,
    -477,  -477,  -477,   -72,   356,  -477,    19,    54,   357,  -477,
    -477,   106,  -477,   148,   148,   433,   435,   445,   -24,    31,
     447,   112,    12,   119,  -477,  -477,  -477,  -477,  -477,   451,
    -477,    66,  -477,  -477,  -477,   449,  -477,  -477,  -477,  -477,
    -477,  -477,  -477,  -477,   450,   384,  -477,  -477,  -477,  -477,
    -477,  -477,  -477,  -477,  -477,  -477,  -477,  -477,  -477,  -477,
    -477,  -477,  -477,  -477,  -477,  -477,  -477,  -477,  -477,  -477,
    -477,  -477,  -477,  -477,  -477,  -477,  -477,  -477,  -477,  -477,
    -477,  -477,   241,  -477,   244,  -477,  -477,   245,  -477,  -477,
    -477,  -477,   454,   457,   458,   462,   463,  -477,  -477,  -477,
     247,  -477,  -477,  -477,  -477,  -477,  -477,  -477,  -477,  -477,
    -477,  -477,  -477,  -477,   251,  -477,   467,   471,  -477,  -477,
     470,   474,  -477,  -477,   472,   476,  -477,  -477,  -477,  -477,
    -477,  -477,   139,  -477,  -477,  -477,  -477,  -477,  -477,  -477,
     149,  -477,   475,   477,  -477,   479,   480,   481,   483,   486,
     487,   254,  -477,  -477,  -477,  -477,  -477,  -477,  -477,  -477,
    -477,   257,  -477,  -477,  -477,   261,   376,   386,  -477,  -477,
     488,   490,  -477,  -477,   491,   493,  -477,  -477,   492,  -477,
     494,   357,  -477,  -477,   495,   497,   498,   499,   388,   391,
     392,   398,   403,   500,   501,   148,  -477,  -477,    18,  -477,
     433,    76,  -477,   435,   -18,  -477,   445,   -24,  -477,    31,
    -477,   -35,  -477,   447,   404,   415,   417,   418,   419,   424,
     112,  -477,   502,   503,    12,  -477,  -477,  -477,   504,   505,
    -477,   -19,  -477,   449,    92,  -477,   450,   507,  -477,   508,
    -477,   281,   426,   428,   429,  -477,  -477,  -477,  -477,  -477,
     430,   431,  -477,   264,  -477,   506,  -477,   509,  -477,  -477,
    -477,   273,  -477,  -477,  -477,  -477,  -477,  -477,  -477,  -477,
     432,   434,  -477,  -477,   436,   275,  -477,   510,  -477,   437,
     512,  -477,  -477,  -477,  -477,  -477,  -477,  -477,  -477,  -477,
    -477,  -477,  -477,  -477,  -477,  -477,  -477,  -477,  -477,  -477,
    -477,  -477,   189,  -477,    68,   512,  -477,  -477,   516,  -477,
    -477,  -477,   287,  -477,  -477,  -477,  -477,  -477,   517,   438,
     518,    68,  -477,   511,  -477,   440,  -477,   519,  -477,  -477,
     205,  -477,   -15,   519,  -477,  -477,   520,   523,   525,   295,
    -477,  -477,  -477,  -477,  -477,  -477,   526,   439,   442,   443,
     -15,  -477,   441,  -477,  -477,  -477,  -477,  -477
  };

  const unsigned short int
  Dhcp4Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     1,    39,    32,    28,    27,    24,
      25,    26,    31,     3,    29,    30,    52,     5,    63,     7,
     101,     9,   209,    11,   323,    13,   343,    15,   262,    17,
     297,    19,   174,    21,   421,    23,    41,    35,     0,     0,
       0,     0,     0,   345,   264,   299,     0,     0,    43,     0,
      42,     0,     0,    36,    61,   472,   468,   470,     0,    60,
       0,    54,    56,    58,    59,    57,    94,     0,     0,   362,
     110,   112,     0,     0,     0,     0,   201,   254,   289,   152,
     388,   166,   185,     0,   409,   419,    87,     0,    65,    67,
      68,    69,    70,    84,    85,    72,    73,    74,    75,    79,
      80,    71,    77,    78,    86,    76,    81,    82,    83,   103,
     105,     0,     0,    96,    98,    99,   100,   392,   235,   237,
     239,   315,   233,   241,   243,     0,     0,   247,   245,   335,
     384,   232,   213,   214,   215,   227,     0,   211,   218,   229,
     230,   231,   219,   220,   223,   225,   221,   222,   216,   217,
     224,   228,   226,   331,   333,   330,   328,     0,   325,   327,
     329,   364,   366,   382,   370,   372,   376,   374,   380,   378,
     368,   361,   357,     0,   346,   347,   358,   359,   360,   354,
     349,   355,   351,   352,   353,   356,   350,   279,   142,     0,
     283,   281,   286,     0,   275,   276,     0,   265,   266,   268,
     278,   269,   270,   271,   285,   272,   273,   274,   310,     0,
     308,   309,   312,   313,     0,   300,   301,   303,   304,   305,
     306,   307,   181,   183,   178,     0,   176,   179,   180,     0,
     441,   443,     0,   446,     0,     0,   450,   454,     0,     0,
       0,   459,   466,   439,     0,   423,   425,   426,   427,   428,
     429,   430,   431,   432,   433,   434,   435,   436,   437,   438,
      40,     0,     0,    33,     0,     0,     0,     0,     0,    51,
       0,    53,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    64,     0,     0,     0,     0,   102,   394,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   210,     0,     0,     0,   324,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   344,
       0,     0,     0,     0,     0,     0,     0,     0,   263,     0,
       0,     0,   298,     0,     0,     0,     0,   175,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   422,    44,    37,     0,     0,     0,     0,
       0,    55,     0,    92,    93,     0,     0,     0,    88,    89,
      90,    91,     0,     0,     0,     0,     0,     0,     0,   408,
       0,     0,    66,     0,     0,   109,    97,   406,   404,   405,
     400,   401,   402,   403,     0,   395,   396,   398,   399,     0,
       0,     0,     0,     0,     0,     0,   252,   253,     0,     0,
       0,     0,   212,     0,     0,   326,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   348,     0,     0,   277,
       0,     0,     0,   288,   267,     0,   314,   302,     0,     0,
     177,   440,     0,     0,   445,     0,   448,   449,     0,     0,
     456,   457,   458,     0,     0,   424,     0,     0,     0,   469,
     471,     0,   363,     0,     0,   203,   256,   291,     0,     0,
     168,     0,     0,     0,    45,   104,   107,   108,   106,     0,
     393,     0,   236,   238,   240,   317,   234,   242,   244,   249,
     250,   251,   248,   246,   337,     0,   332,    34,   334,   365,
     367,   383,   371,   373,   377,   375,   381,   379,   369,   280,
     143,   284,   282,   287,   311,   182,   184,   442,   444,   447,
     452,   453,   451,   455,   461,   462,   463,   464,   465,   460,
     467,    38,     0,   477,     0,   474,   476,     0,   129,   135,
     137,   139,     0,     0,     0,     0,     0,   148,   150,   128,
       0,   114,   116,   117,   118,   119,   120,   121,   122,   123,
     124,   125,   126,   127,     0,   207,     0,   204,   205,   260,
       0,   257,   258,   295,     0,   292,   293,   161,   162,   163,
     164,   165,     0,   154,   156,   157,   158,   159,   160,   390,
       0,   172,     0,   169,   170,     0,     0,     0,     0,     0,
       0,     0,   187,   189,   190,   191,   192,   193,   194,   415,
     417,     0,   411,   413,   414,     0,    47,     0,   397,   321,
       0,   318,   319,   341,     0,   338,   339,   386,     0,    62,
       0,     0,   473,    95,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   111,   113,     0,   202,
       0,   264,   255,     0,   299,   290,     0,     0,   153,     0,
     389,     0,   167,     0,     0,     0,     0,     0,     0,     0,
       0,   186,     0,     0,     0,   410,   420,    49,     0,    48,
     407,     0,   316,     0,   345,   336,     0,     0,   385,     0,
     475,     0,     0,     0,     0,   141,   144,   145,   146,   147,
       0,     0,   115,     0,   206,     0,   259,     0,   294,   155,
     391,     0,   171,   195,   196,   197,   198,   199,   200,   188,
       0,     0,   412,    46,     0,     0,   320,     0,   340,     0,
       0,   131,   132,   133,   134,   130,   136,   138,   140,   149,
     151,   208,   261,   296,   173,   416,   418,    50,   322,   342,
     387,   481,     0,   479,     0,     0,   478,   493,     0,   491,
     489,   485,     0,   483,   487,   488,   486,   480,     0,     0,
       0,     0,   482,     0,   490,     0,   484,     0,   492,   497,
       0,   495,     0,     0,   494,   505,     0,     0,     0,     0,
     499,   501,   502,   503,   504,   496,     0,     0,     0,     0,
       0,   498,     0,   507,   508,   509,   500,   506
  };

  const short int
  Dhcp4Parser::yypgoto_[] =
  {
    -477,  -477,  -477,  -477,  -477,  -477,  -477,  -477,  -477,  -477,
    -477,  -477,  -477,   -36,  -477,    65,  -477,  -477,  -477,  -477,
    -477,  -477,  -477,  -477,    64,  -477,  -477,  -477,   -58,  -477,
    -477,  -477,   233,  -477,  -477,  -477,  -477,    44,   222,   -60,
     -44,   -42,  -477,  -477,   -40,  -477,  -477,    45,   218,  -477,
    -477,  -477,  -477,  -477,  -477,  -477,  -477,  -477,  -477,  -477,
    -477,    43,  -137,  -477,  -477,  -477,  -477,  -477,  -477,  -477,
    -477,  -477,  -477,   -63,  -477,  -477,  -477,  -477,  -477,  -477,
    -477,  -477,  -477,  -477,  -477,  -477,  -148,  -477,  -477,  -477,
    -477,  -477,  -477,  -477,  -477,  -477,  -152,  -477,  -477,  -477,
    -149,   179,  -477,  -477,  -477,  -477,  -477,  -477,  -477,  -154,
    -477,  -477,  -477,  -477,  -477,  -477,  -477,  -477,  -477,  -477,
    -133,  -477,  -477,  -477,  -130,   216,  -477,  -477,  -477,  -477,
    -477,  -477,  -477,  -477,  -477,  -477,  -477,  -477,  -476,  -477,
    -477,  -477,  -477,  -477,  -477,  -477,  -477,  -477,  -477,  -132,
    -477,  -477,  -477,  -131,  -477,   193,  -477,   -49,  -477,  -477,
    -477,  -477,  -477,   -47,  -477,  -477,  -477,  -477,  -477,   -51,
    -477,  -477,  -477,  -126,  -477,  -477,  -477,  -128,  -477,   198,
    -477,  -477,  -477,  -477,  -477,  -477,  -477,  -477,  -477,  -477,
    -160,  -477,  -477,  -477,  -157,   225,  -477,  -477,  -477,  -477,
    -477,  -477,  -477,  -477,  -153,  -477,  -477,  -477,  -142,  -477,
     224,   -48,  -477,  -305,  -477,  -297,  -477,  -477,  -477,  -477,
    -477,  -477,  -477,  -477,  -477,  -477,  -477,  -477,  -477,  -477,
    -477,  -477,  -477,  -477,  -477,  -477,  -477,  -477,  -477,  -477,
    -477,  -477,  -477,    55,  -477,  -477,  -477,  -477,  -477,  -477,
    -477,  -127,  -477,  -477,  -477,  -477,  -477,  -477,  -477,  -477,
      83,   202,  -477,  -477,  -477,  -477,  -477,  -477,  -477,  -477,
    -477,  -477,  -477,  -477,  -477,  -477,  -477,  -477,  -477,  -477,
    -477,  -477,  -477,  -477,  -477,  -477,  -477,  -477,  -477,  -477,
    -477,  -477,   -76,  -477,  -477,  -477,  -198,  -477,  -477,  -213,
    -477,  -477,  -477,  -477,  -477,  -477,  -224,  -477,  -477,  -240,
    -477,  -477,  -477,  -477,  -477
  };

  const short int
  Dhcp4Parser::yydefgoto_[] =
  {
      -1,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    32,    33,    34,    57,   528,    72,    73,
      35,    56,    69,    70,   505,   646,   708,   709,   106,    37,
      58,    80,    81,    82,   285,    39,    59,   107,   108,   109,
     110,   111,   112,   113,   114,   115,   292,   132,   133,    41,
      60,   134,   314,   135,   315,   508,   136,   116,   296,   117,
     297,   580,   581,   582,   664,   765,   583,   665,   584,   666,
     585,   667,   586,   215,   352,   588,   589,   590,   591,   592,
     673,   593,   674,   118,   305,   612,   613,   614,   615,   616,
     617,   618,   119,   307,   622,   623,   624,   691,    53,    66,
     245,   246,   247,   364,   248,   365,   120,   308,   631,   632,
     633,   634,   635,   636,   637,   638,   121,   302,   596,   597,
     598,   678,    43,    61,   156,   157,   158,   324,   159,   320,
     160,   321,   161,   322,   162,   325,   163,   326,   164,   330,
     165,   329,   522,   166,   167,   122,   303,   600,   601,   602,
     681,    49,    64,   216,   217,   218,   219,   220,   221,   222,
     351,   223,   355,   224,   354,   225,   226,   356,   227,   123,
     304,   604,   605,   606,   684,    51,    65,   234,   235,   236,
     237,   238,   360,   239,   240,   241,   169,   323,   650,   651,
     652,   711,    45,    62,   177,   178,   179,   335,   180,   336,
     170,   331,   654,   655,   656,   714,    47,    63,   193,   194,
     195,   124,   295,   197,   339,   198,   340,   199,   348,   200,
     342,   201,   343,   202,   345,   203,   344,   204,   347,   205,
     346,   206,   341,   172,   332,   658,   717,   125,   306,   620,
     319,   424,   425,   426,   427,   428,   509,   126,   127,   310,
     641,   642,   643,   702,   644,   703,   128,   311,    55,    67,
     264,   265,   266,   267,   369,   268,   370,   269,   270,   372,
     271,   272,   273,   375,   552,   274,   376,   275,   276,   277,
     278,   380,   559,   279,   381,    83,   287,    84,   288,    85,
     286,   564,   565,   566,   660,   782,   783,   784,   792,   793,
     794,   795,   800,   796,   798,   810,   811,   812,   819,   820,
     821,   826,   822,   823,   824
  };

  const unsigned short int
  Dhcp4Parser::yytable_[] =
  {
      79,   152,   231,   151,   175,   191,   214,   230,   244,   263,
     168,   176,   192,   171,   422,   196,   232,   153,   233,   154,
      68,   155,   423,   619,    25,   137,    26,    74,    27,    98,
     550,   208,   228,   209,   210,   229,    88,    89,   137,   173,
     174,   554,   555,   556,   557,   519,   520,   521,   242,   243,
     607,   608,   609,   610,    36,   611,   290,    92,    93,    94,
      24,   291,   138,   139,   140,    86,    98,   242,   243,    38,
     558,    87,    88,    89,    40,   141,    90,    91,   142,   143,
     144,   145,   146,   147,   312,    89,   181,   182,   280,   313,
     148,   149,    42,    92,    93,    94,    95,    96,   150,   281,
     207,    97,    98,   148,    78,   815,   639,   640,   816,   817,
     818,    89,   181,   182,    98,   208,    44,   208,   129,   130,
      78,    78,   131,    99,   100,   208,   551,   209,   210,    46,
     211,   212,   213,   317,    75,    48,   101,   417,   318,   102,
      98,    50,   687,    76,    77,   688,   103,   104,   333,   337,
     105,    52,   689,   334,   338,   690,    78,    78,    28,    29,
      30,    31,   183,    54,   506,   507,   184,   185,   186,   187,
     188,   189,   568,   190,    71,   282,   283,   569,   570,   571,
     572,   573,   574,   575,   576,   577,   578,   787,   284,   788,
     789,   366,   785,    78,   289,   786,   367,   208,   625,   626,
     627,   628,   629,   630,   382,    78,   422,    78,   813,   383,
     293,   814,   294,   740,   423,    78,   249,   250,   251,   252,
     253,   254,   255,   256,   257,   258,   259,   260,   261,   262,
     298,    78,    79,     1,     2,     3,     4,     5,     6,     7,
       8,     9,    10,    11,   312,   384,   385,   661,   317,   659,
     675,   349,   662,   663,   675,   676,   419,   700,    78,   677,
     704,   418,   701,   299,   382,   705,   300,   333,   420,   706,
     301,   421,   771,   152,   309,   151,   366,   350,   337,   175,
     316,   774,   168,   778,   327,   171,   176,    78,   328,   153,
     801,   154,   191,   155,   353,   802,   357,   358,   830,   192,
     231,   214,   196,   831,   359,   230,   761,   762,   763,   764,
     361,   362,   363,   386,   232,   368,   233,   371,   373,   374,
     377,   378,   379,   387,   263,   388,   389,   390,   392,   393,
     395,   396,   397,   394,   398,   399,   400,   401,   402,   403,
     404,   405,   406,   407,   408,   410,   411,   409,   413,   414,
     429,   415,   430,   489,   490,   431,   432,   433,   434,   435,
     436,   437,   438,   439,   440,   441,   443,   444,   446,   447,
     448,   449,   450,   451,   452,   453,   454,   455,   457,   458,
     459,   460,   461,   462,   463,   465,   468,   469,   466,   472,
     471,   473,   474,   475,   478,   476,   477,   479,   483,   484,
     480,   486,   481,   487,   492,   482,   488,   491,   493,   494,
     495,   496,   497,   498,   499,   500,   512,   513,   501,   502,
     503,   504,   510,   511,   514,   516,   515,   517,   524,   525,
     587,   587,   518,   546,    26,   579,   579,   523,   526,   529,
     595,   530,   599,   532,   533,   263,   534,   535,   419,   536,
     561,   537,   603,   418,   621,   647,   649,   653,   668,   538,
     420,   669,   670,   421,   539,   657,   671,   672,   540,   541,
     542,   543,   544,   679,   680,   563,   682,   683,   685,   686,
     693,   692,   545,   694,   695,   696,   547,   697,   548,   549,
     698,   699,   553,   713,   712,   560,   716,   715,   719,   721,
     718,   722,   723,   724,   730,   731,   750,   751,   754,   527,
     753,   759,   531,   760,   772,   707,   807,   773,   779,   781,
     799,   803,   805,   391,   827,   710,   809,   828,   725,   829,
     832,   562,   727,   726,   412,   416,   567,   594,   732,   739,
     728,   742,   741,   729,   743,   470,   749,   734,   733,   442,
     735,   736,   464,   756,   755,   744,   737,   745,   746,   747,
     738,   467,   445,   758,   748,   766,   648,   767,   768,   769,
     770,   775,   757,   776,   456,   777,   780,   752,   804,   808,
     837,   833,   834,   835,   485,   720,   645,   797,   806,   825,
     836,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   587,     0,     0,     0,     0,   579,   152,     0,
     151,   231,     0,   214,     0,     0,   230,   168,     0,     0,
     171,     0,     0,   244,   153,   232,   154,   233,   155,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   175,     0,     0,   191,     0,     0,     0,
     176,     0,     0,   192,     0,     0,   196,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   791,     0,     0,     0,     0,   790,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   791,     0,
       0,     0,     0,   790
  };

  const short int
  Dhcp4Parser::yycheck_[] =
  {
      58,    61,    65,    61,    62,    63,    64,    65,    66,    67,
      61,    62,    63,    61,   319,    63,    65,    61,    65,    61,
      56,    61,   319,   499,     5,     7,     7,    10,     9,    48,
      15,    49,    50,    51,    52,    53,    18,    19,     7,    58,
      59,   113,   114,   115,   116,    66,    67,    68,    83,    84,
      74,    75,    76,    77,     7,    79,     3,    39,    40,    41,
       0,     8,    44,    45,    46,    11,    48,    83,    84,     7,
     142,    17,    18,    19,     7,    57,    22,    23,    60,    61,
      62,    63,    64,    65,     3,    19,    20,    21,     6,     8,
      72,    73,     7,    39,    40,    41,    42,    43,    80,     3,
      24,    47,    48,    72,   139,   120,    94,    95,   123,   124,
     125,    19,    20,    21,    48,    49,     7,    49,    12,    13,
     139,   139,    16,    69,    70,    49,   111,    51,    52,     7,
      54,    55,    56,     3,   117,     7,    82,    71,     8,    85,
      48,     7,     3,   126,   127,     6,    92,    93,     3,     3,
      96,     7,     3,     8,     8,     6,   139,   139,   139,   140,
     141,   142,    70,     7,    14,    15,    74,    75,    76,    77,
      78,    79,    24,    81,   139,     4,     8,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,   119,     3,   121,
     122,     3,     3,   139,     4,     6,     8,    49,    86,    87,
      88,    89,    90,    91,     3,   139,   511,   139,     3,     8,
       4,     6,     4,   689,   511,   139,    97,    98,    99,   100,
     101,   102,   103,   104,   105,   106,   107,   108,   109,   110,
       4,   139,   290,   128,   129,   130,   131,   132,   133,   134,
     135,   136,   137,   138,     3,   281,   282,     3,     3,     8,
       3,     8,     8,     8,     3,     8,   319,     3,   139,     8,
       3,   319,     8,     4,     3,     8,     4,     3,   319,     8,
       4,   319,     8,   333,     4,   333,     3,     3,     3,   337,
       4,     8,   333,     8,     4,   333,   337,   139,     4,   333,
       3,   333,   350,   333,     4,     8,     4,     8,     3,   350,
     363,   359,   350,     8,     3,   363,    25,    26,    27,    28,
       4,     8,     3,   139,   363,     4,   363,     4,     4,     4,
       4,     4,     4,     4,   382,     4,     4,     4,     4,   142,
       4,     4,     4,   142,   140,   140,   140,   140,     4,     4,
       4,     4,     4,     4,     4,     4,     4,   140,     4,     4,
       4,   142,     4,   389,   390,     4,     4,     4,     4,     4,
     140,   142,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
     140,     4,     4,     4,   142,     4,     4,     4,   142,     4,
     142,     4,   140,     4,     4,   140,   140,     4,     4,     4,
     142,     4,   142,     7,   139,   142,     7,     7,     7,     7,
       5,     5,     5,     5,     5,     5,   139,   139,     7,     7,
       7,     5,     8,     3,   139,   139,     5,   139,     5,     7,
     493,   494,   139,   469,     7,   493,   494,   139,   139,   139,
       7,   139,     7,   139,   139,   503,   139,   139,   511,   139,
     486,   139,     7,   511,     7,     4,     7,     7,     4,   139,
     511,     4,     4,   511,   139,    81,     4,     4,   139,   139,
     139,   139,   139,     6,     3,   118,     6,     3,     6,     3,
       3,     6,   139,     4,     4,     4,   139,     4,   139,   139,
       4,     4,   112,     3,     6,   139,     3,     6,     4,     4,
       8,     4,     4,     4,     4,     4,     4,     4,     3,   444,
       6,     4,   448,     5,     8,   139,     5,     8,     8,     7,
       4,     4,     4,   290,     4,   139,     7,     4,   140,     4,
       4,   487,   140,   142,   312,   317,   491,   494,   675,   687,
     142,   693,   691,   140,   140,   366,   700,   680,   678,   333,
     681,   683,   359,   713,   711,   140,   684,   140,   140,   140,
     686,   363,   337,   716,   140,   139,   511,   139,   139,   139,
     139,   139,   714,   139,   350,   139,   139,   704,   140,   139,
     139,   142,   140,   140,   382,   661,   503,   785,   801,   813,
     830,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   675,    -1,    -1,    -1,    -1,   675,   678,    -1,
     678,   684,    -1,   681,    -1,    -1,   684,   678,    -1,    -1,
     678,    -1,    -1,   691,   678,   684,   678,   684,   678,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   711,    -1,    -1,   714,    -1,    -1,    -1,
     711,    -1,    -1,   714,    -1,    -1,   714,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   784,    -1,    -1,    -1,    -1,   784,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   801,    -1,
      -1,    -1,    -1,   801
  };

  const unsigned short int
  Dhcp4Parser::yystos_[] =
  {
       0,   128,   129,   130,   131,   132,   133,   134,   135,   136,
     137,   138,   144,   145,   146,   147,   148,   149,   150,   151,
     152,   153,   154,   155,     0,     5,     7,     9,   139,   140,
     141,   142,   156,   157,   158,   163,     7,   172,     7,   178,
       7,   192,     7,   265,     7,   335,     7,   349,     7,   294,
       7,   318,     7,   241,     7,   401,   164,   159,   173,   179,
     193,   266,   336,   350,   295,   319,   242,   402,   156,   165,
     166,   139,   161,   162,    10,   117,   126,   127,   139,   171,
     174,   175,   176,   428,   430,   432,    11,    17,    18,    19,
      22,    23,    39,    40,    41,    42,    43,    47,    48,    69,
      70,    82,    85,    92,    93,    96,   171,   180,   181,   182,
     183,   184,   185,   186,   187,   188,   200,   202,   226,   235,
     249,   259,   288,   312,   354,   380,   390,   391,   399,    12,
      13,    16,   190,   191,   194,   196,   199,     7,    44,    45,
      46,    57,    60,    61,    62,    63,    64,    65,    72,    73,
      80,   171,   182,   183,   184,   187,   267,   268,   269,   271,
     273,   275,   277,   279,   281,   283,   286,   287,   312,   329,
     343,   354,   376,    58,    59,   171,   312,   337,   338,   339,
     341,    20,    21,    70,    74,    75,    76,    77,    78,    79,
      81,   171,   312,   351,   352,   353,   354,   356,   358,   360,
     362,   364,   366,   368,   370,   372,   374,    24,    49,    51,
      52,    54,    55,    56,   171,   216,   296,   297,   298,   299,
     300,   301,   302,   304,   306,   308,   309,   311,    50,    53,
     171,   216,   300,   306,   320,   321,   322,   323,   324,   326,
     327,   328,    83,    84,   171,   243,   244,   245,   247,    97,
      98,    99,   100,   101,   102,   103,   104,   105,   106,   107,
     108,   109,   110,   171,   403,   404,   405,   406,   408,   410,
     411,   413,   414,   415,   418,   420,   421,   422,   423,   426,
       6,     3,     4,     8,     3,   177,   433,   429,   431,     4,
       3,     8,   189,     4,     4,   355,   201,   203,     4,     4,
       4,     4,   260,   289,   313,   227,   381,   236,   250,     4,
     392,   400,     3,     8,   195,   197,     4,     3,     8,   383,
     272,   274,   276,   330,   270,   278,   280,     4,     4,   284,
     282,   344,   377,     3,     8,   340,   342,     3,     8,   357,
     359,   375,   363,   365,   369,   367,   373,   371,   361,     8,
       3,   303,   217,     4,   307,   305,   310,     4,     8,     3,
     325,     4,     8,     3,   246,   248,     3,     8,     4,   407,
     409,     4,   412,     4,     4,   416,   419,     4,     4,     4,
     424,   427,     3,     8,   156,   156,   139,     4,     4,     4,
       4,   175,     4,   142,   142,     4,     4,     4,   140,   140,
     140,   140,     4,     4,     4,     4,     4,     4,     4,   140,
       4,     4,   181,     4,     4,   142,   191,    71,   171,   216,
     312,   354,   356,   358,   384,   385,   386,   387,   388,     4,
       4,     4,     4,     4,     4,     4,   140,   142,     4,     4,
       4,     4,   268,     4,     4,   338,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,   353,     4,     4,   140,
       4,     4,     4,   142,   298,     4,   142,   322,     4,     4,
     244,   142,     4,     4,   140,     4,   140,   140,     4,     4,
     142,   142,   142,     4,     4,   404,     4,     7,     7,   156,
     156,     7,   139,     7,     7,     5,     5,     5,     5,     5,
       5,     7,     7,     7,     5,   167,    14,    15,   198,   389,
       8,     3,   139,   139,   139,     5,   139,   139,   139,    66,
      67,    68,   285,   139,     5,     7,   139,   158,   160,   139,
     139,   167,   139,   139,   139,   139,   139,   139,   139,   139,
     139,   139,   139,   139,   139,   139,   156,   139,   139,   139,
      15,   111,   417,   112,   113,   114,   115,   116,   142,   425,
     139,   156,   180,   118,   434,   435,   436,   190,    24,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,   171,
     204,   205,   206,   209,   211,   213,   215,   216,   218,   219,
     220,   221,   222,   224,   204,     7,   261,   262,   263,     7,
     290,   291,   292,     7,   314,   315,   316,    74,    75,    76,
      77,    79,   228,   229,   230,   231,   232,   233,   234,   281,
     382,     7,   237,   238,   239,    86,    87,    88,    89,    90,
      91,   251,   252,   253,   254,   255,   256,   257,   258,    94,
      95,   393,   394,   395,   397,   403,   168,     4,   386,     7,
     331,   332,   333,     7,   345,   346,   347,    81,   378,     8,
     437,     3,     8,     8,   207,   210,   212,   214,     4,     4,
       4,     4,     4,   223,   225,     3,     8,     8,   264,     6,
       3,   293,     6,     3,   317,     6,     3,     3,     6,     3,
       6,   240,     6,     3,     4,     4,     4,     4,     4,     4,
       3,     8,   396,   398,     3,     8,     8,   139,   169,   170,
     139,   334,     6,     3,   348,     6,     3,   379,     8,     4,
     435,     4,     4,     4,     4,   140,   142,   140,   142,   140,
       4,     4,   205,   267,   263,   296,   292,   320,   316,   229,
     281,   243,   239,   140,   140,   140,   140,   140,   140,   252,
       4,     4,   394,     6,     3,   337,   333,   351,   347,     4,
       5,    25,    26,    27,    28,   208,   139,   139,   139,   139,
     139,     8,     8,     8,     8,   139,   139,   139,     8,     8,
     139,     7,   438,   439,   440,     3,     6,   119,   121,   122,
     171,   216,   441,   442,   443,   444,   446,   439,   447,     4,
     445,     3,     8,     4,   140,     4,   442,     5,   139,     7,
     448,   449,   450,     3,     6,   120,   123,   124,   125,   451,
     452,   453,   455,   456,   457,   449,   454,     4,     4,     4,
       3,     8,     4,   142,   140,   140,   452,   139
  };

  const unsigned short int
  Dhcp4Parser::yyr1_[] =
  {
       0,   143,   145,   144,   146,   144,   147,   144,   148,   144,
     149,   144,   150,   144,   151,   144,   152,   144,   153,   144,
     154,   144,   155,   144,   156,   156,   156,   156,   156,   156,
     156,   157,   159,   158,   160,   161,   161,   162,   162,   164,
     163,   165,   165,   166,   166,   168,   167,   169,   169,   170,
     170,   171,   173,   172,   174,   174,   175,   175,   175,   175,
     175,   177,   176,   179,   178,   180,   180,   181,   181,   181,
     181,   181,   181,   181,   181,   181,   181,   181,   181,   181,
     181,   181,   181,   181,   181,   181,   181,   181,   182,   183,
     184,   185,   186,   187,   189,   188,   190,   190,   191,   191,
     191,   193,   192,   195,   194,   197,   196,   198,   198,   199,
     201,   200,   203,   202,   204,   204,   205,   205,   205,   205,
     205,   205,   205,   205,   205,   205,   205,   205,   205,   207,
     206,   208,   208,   208,   208,   210,   209,   212,   211,   214,
     213,   215,   217,   216,   218,   219,   220,   221,   223,   222,
     225,   224,   227,   226,   228,   228,   229,   229,   229,   229,
     229,   230,   231,   232,   233,   234,   236,   235,   237,   237,
     238,   238,   240,   239,   242,   241,   243,   243,   243,   244,
     244,   246,   245,   248,   247,   250,   249,   251,   251,   252,
     252,   252,   252,   252,   252,   253,   254,   255,   256,   257,
     258,   260,   259,   261,   261,   262,   262,   264,   263,   266,
     265,   267,   267,   268,   268,   268,   268,   268,   268,   268,
     268,   268,   268,   268,   268,   268,   268,   268,   268,   268,
     268,   268,   268,   270,   269,   272,   271,   274,   273,   276,
     275,   278,   277,   280,   279,   282,   281,   284,   283,   285,
     285,   285,   286,   287,   289,   288,   290,   290,   291,   291,
     293,   292,   295,   294,   296,   296,   297,   297,   298,   298,
     298,   298,   298,   298,   298,   298,   299,   300,   301,   303,
     302,   305,   304,   307,   306,   308,   310,   309,   311,   313,
     312,   314,   314,   315,   315,   317,   316,   319,   318,   320,
     320,   321,   321,   322,   322,   322,   322,   322,   322,   323,
     325,   324,   326,   327,   328,   330,   329,   331,   331,   332,
     332,   334,   333,   336,   335,   337,   337,   338,   338,   338,
     338,   340,   339,   342,   341,   344,   343,   345,   345,   346,
     346,   348,   347,   350,   349,   351,   351,   352,   352,   353,
     353,   353,   353,   353,   353,   353,   353,   353,   353,   353,
     353,   353,   355,   354,   357,   356,   359,   358,   361,   360,
     363,   362,   365,   364,   367,   366,   369,   368,   371,   370,
     373,   372,   375,   374,   377,   376,   379,   378,   381,   380,
     382,   382,   383,   281,   384,   384,   385,   385,   386,   386,
     386,   386,   386,   386,   386,   387,   389,   388,   390,   392,
     391,   393,   393,   394,   394,   396,   395,   398,   397,   400,
     399,   402,   401,   403,   403,   404,   404,   404,   404,   404,
     404,   404,   404,   404,   404,   404,   404,   404,   404,   404,
     405,   407,   406,   409,   408,   410,   412,   411,   413,   414,
     416,   415,   417,   417,   419,   418,   420,   421,   422,   424,
     423,   425,   425,   425,   425,   425,   427,   426,   429,   428,
     431,   430,   433,   432,   434,   434,   435,   437,   436,   438,
     438,   440,   439,   441,   441,   442,   442,   442,   442,   442,
     443,   445,   444,   447,   446,   448,   448,   450,   449,   451,
     451,   452,   452,   452,   452,   454,   453,   455,   456,   457
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
       1,     0,     4,     0,     4,     0,     4,     1,     1,     3,
       0,     6,     0,     6,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     0,
       4,     1,     1,     1,     1,     0,     4,     0,     4,     0,
       4,     3,     0,     4,     3,     3,     3,     3,     0,     4,
       0,     4,     0,     6,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     0,     6,     0,     1,
       1,     3,     0,     4,     0,     4,     1,     3,     1,     1,
       1,     0,     4,     0,     4,     0,     6,     1,     3,     1,
       1,     1,     1,     1,     1,     3,     3,     3,     3,     3,
       3,     0,     6,     0,     1,     1,     3,     0,     4,     0,
       4,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     0,     4,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     4,     1,
       1,     1,     3,     3,     0,     6,     0,     1,     1,     3,
       0,     4,     0,     4,     0,     1,     1,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     3,     1,     0,
       4,     0,     4,     0,     4,     1,     0,     4,     3,     0,
       6,     0,     1,     1,     3,     0,     4,     0,     4,     0,
       1,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       0,     4,     1,     1,     3,     0,     6,     0,     1,     1,
       3,     0,     4,     0,     4,     1,     3,     1,     1,     1,
       1,     0,     4,     0,     4,     0,     6,     0,     1,     1,
       3,     0,     4,     0,     4,     0,     1,     1,     3,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     0,     4,     0,     4,     0,     4,     0,     4,
       0,     4,     0,     4,     0,     4,     0,     4,     0,     4,
       0,     4,     0,     4,     0,     6,     0,     4,     0,     6,
       1,     3,     0,     4,     0,     1,     1,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     0,     4,     3,     0,
       6,     1,     3,     1,     1,     0,     4,     0,     4,     0,
       6,     0,     4,     1,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       3,     0,     4,     0,     4,     3,     0,     4,     3,     3,
       0,     4,     1,     1,     0,     4,     3,     3,     3,     0,
       4,     1,     1,     1,     1,     1,     0,     4,     0,     4,
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
  "\"data\"", "\"code\"", "\"space\"", "\"csv-format\"",
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
  "\"maxver\"", "\"Dhcp6\"", "\"DhcpDdns\"", "TOPLEVEL_JSON",
  "TOPLEVEL_DHCP4", "SUB_DHCP4", "SUB_INTERFACES4", "SUB_SUBNET4",
  "SUB_POOL4", "SUB_RESERVATION", "SUB_OPTION_DEF", "SUB_OPTION_DATA",
  "SUB_HOOKS_LIBRARY", "SUB_DHCP_DDNS", "\"constant string\"",
  "\"integer\"", "\"floating point\"", "\"boolean\"", "$accept", "start",
  "$@1", "$@2", "$@3", "$@4", "$@5", "$@6", "$@7", "$@8", "$@9", "$@10",
  "$@11", "value", "sub_json", "map2", "$@12", "map_value", "map_content",
  "not_empty_map", "list_generic", "$@13", "list_content",
  "not_empty_list", "list_strings", "$@14", "list_strings_content",
  "not_empty_list_strings", "unknown_map_entry", "syntax_map", "$@15",
  "global_objects", "global_object", "dhcp4_object", "$@16", "sub_dhcp4",
  "$@17", "global_params", "global_param", "valid_lifetime", "renew_timer",
  "rebind_timer", "decline_probation_period", "echo_client_id",
  "match_client_id", "interfaces_config", "$@18",
  "interfaces_config_params", "interfaces_config_param", "sub_interfaces4",
  "$@19", "interfaces_list", "$@20", "dhcp_socket_type", "$@21",
  "socket_type", "re_detect", "lease_database", "$@22", "hosts_database",
  "$@23", "database_map_params", "database_map_param", "database_type",
  "$@24", "db_type", "user", "$@25", "password", "$@26", "host", "$@27",
  "port", "name", "$@28", "persist", "lfc_interval", "readonly",
  "connect_timeout", "contact_points", "$@29", "keyspace", "$@30",
  "host_reservation_identifiers", "$@31",
  "host_reservation_identifiers_list", "host_reservation_identifier",
  "duid_id", "hw_address_id", "circuit_id", "client_id", "flex_id",
  "hooks_libraries", "$@32", "hooks_libraries_list",
  "not_empty_hooks_libraries_list", "hooks_library", "$@33",
  "sub_hooks_library", "$@34", "hooks_params", "hooks_param", "library",
  "$@35", "parameters", "$@36", "expired_leases_processing", "$@37",
  "expired_leases_params", "expired_leases_param",
  "reclaim_timer_wait_time", "flush_reclaimed_timer_wait_time",
  "hold_reclaimed_time", "max_reclaim_leases", "max_reclaim_time",
  "unwarned_reclaim_cycles", "subnet4_list", "$@38",
  "subnet4_list_content", "not_empty_subnet4_list", "subnet4", "$@39",
  "sub_subnet4", "$@40", "subnet4_params", "subnet4_param", "subnet",
  "$@41", "subnet_4o6_interface", "$@42", "subnet_4o6_interface_id",
  "$@43", "subnet_4o6_subnet", "$@44", "interface", "$@45", "interface_id",
  "$@46", "client_class", "$@47", "reservation_mode", "$@48", "hr_mode",
  "id", "rapid_commit", "option_def_list", "$@49",
  "option_def_list_content", "not_empty_option_def_list",
  "option_def_entry", "$@50", "sub_option_def", "$@51",
  "option_def_params", "not_empty_option_def_params", "option_def_param",
  "option_def_name", "code", "option_def_code", "option_def_type", "$@52",
  "option_def_record_types", "$@53", "space", "$@54", "option_def_space",
  "option_def_encapsulate", "$@55", "option_def_array", "option_data_list",
  "$@56", "option_data_list_content", "not_empty_option_data_list",
  "option_data_entry", "$@57", "sub_option_data", "$@58",
  "option_data_params", "not_empty_option_data_params",
  "option_data_param", "option_data_name", "option_data_data", "$@59",
  "option_data_code", "option_data_space", "option_data_csv_format",
  "pools_list", "$@60", "pools_list_content", "not_empty_pools_list",
  "pool_list_entry", "$@61", "sub_pool4", "$@62", "pool_params",
  "pool_param", "pool_entry", "$@63", "user_context", "$@64",
  "reservations", "$@65", "reservations_list",
  "not_empty_reservations_list", "reservation", "$@66", "sub_reservation",
  "$@67", "reservation_params", "not_empty_reservation_params",
  "reservation_param", "next_server", "$@68", "server_hostname", "$@69",
  "boot_file_name", "$@70", "ip_address", "$@71", "duid", "$@72",
  "hw_address", "$@73", "client_id_value", "$@74", "circuit_id_value",
  "$@75", "flex_id_value", "$@76", "hostname", "$@77",
  "reservation_client_classes", "$@78", "relay", "$@79", "relay_map",
  "$@80", "client_classes", "$@81", "client_classes_list", "$@82",
  "client_class_params", "not_empty_client_class_params",
  "client_class_param", "client_class_name", "client_class_test", "$@83",
  "dhcp4o6_port", "control_socket", "$@84", "control_socket_params",
  "control_socket_param", "control_socket_type", "$@85",
  "control_socket_name", "$@86", "dhcp_ddns", "$@87", "sub_dhcp_ddns",
  "$@88", "dhcp_ddns_params", "dhcp_ddns_param", "enable_updates",
  "qualifying_suffix", "$@89", "server_ip", "$@90", "server_port",
  "sender_ip", "$@91", "sender_port", "max_queue_size", "ncr_protocol",
  "$@92", "ncr_protocol_value", "ncr_format", "$@93",
  "always_include_fqdn", "override_no_update", "override_client_update",
  "replace_client_name", "$@94", "replace_client_name_value",
  "generated_prefix", "$@95", "dhcp6_json_object", "$@96",
  "dhcpddns_json_object", "$@97", "logging_object", "$@98",
  "logging_params", "logging_param", "loggers", "$@99", "loggers_entries",
  "logger_entry", "$@100", "logger_params", "logger_param", "debuglevel",
  "severity", "$@101", "output_options_list", "$@102",
  "output_options_list_content", "output_entry", "$@103",
  "output_params_list", "output_params", "output", "$@104", "flush",
  "maxsize", "maxver", YY_NULLPTR
  };

#if PARSER4_DEBUG
  const unsigned short int
  Dhcp4Parser::yyrline_[] =
  {
       0,   224,   224,   224,   225,   225,   226,   226,   227,   227,
     228,   228,   229,   229,   230,   230,   231,   231,   232,   232,
     233,   233,   234,   234,   242,   243,   244,   245,   246,   247,
     248,   251,   256,   256,   267,   270,   271,   274,   278,   285,
     285,   292,   293,   296,   300,   307,   307,   314,   315,   318,
     322,   333,   343,   343,   355,   356,   360,   361,   362,   363,
     364,   367,   367,   384,   384,   392,   393,   398,   399,   400,
     401,   402,   403,   404,   405,   406,   407,   408,   409,   410,
     411,   412,   413,   414,   415,   416,   417,   418,   421,   426,
     431,   436,   441,   446,   452,   452,   462,   463,   466,   467,
     468,   471,   471,   479,   479,   489,   489,   496,   497,   500,
     506,   506,   516,   516,   526,   527,   530,   531,   532,   533,
     534,   535,   536,   537,   538,   539,   540,   541,   542,   545,
     545,   552,   553,   554,   555,   558,   558,   566,   566,   574,
     574,   582,   587,   587,   595,   600,   605,   610,   615,   615,
     623,   623,   632,   632,   642,   643,   646,   647,   648,   649,
     650,   653,   658,   663,   668,   673,   678,   678,   688,   689,
     692,   693,   696,   696,   704,   704,   712,   713,   714,   717,
     718,   721,   721,   729,   729,   737,   737,   747,   748,   751,
     752,   753,   754,   755,   756,   759,   764,   769,   774,   779,
     784,   792,   792,   805,   806,   809,   810,   817,   817,   840,
     840,   849,   850,   854,   855,   856,   857,   858,   859,   860,
     861,   862,   863,   864,   865,   866,   867,   868,   869,   870,
     871,   872,   873,   876,   876,   884,   884,   892,   892,   900,
     900,   908,   908,   916,   916,   924,   924,   932,   932,   939,
     940,   941,   944,   949,   958,   958,   970,   971,   974,   975,
     980,   980,   991,   991,  1001,  1002,  1005,  1006,  1009,  1010,
    1011,  1012,  1013,  1014,  1015,  1016,  1019,  1021,  1026,  1028,
    1028,  1036,  1036,  1044,  1044,  1052,  1054,  1054,  1062,  1071,
    1071,  1083,  1084,  1089,  1090,  1095,  1095,  1106,  1106,  1117,
    1118,  1123,  1124,  1129,  1130,  1131,  1132,  1133,  1134,  1137,
    1139,  1139,  1147,  1149,  1151,  1159,  1159,  1171,  1172,  1175,
    1176,  1179,  1179,  1187,  1187,  1195,  1196,  1199,  1200,  1201,
    1202,  1205,  1205,  1213,  1213,  1223,  1223,  1233,  1234,  1237,
    1238,  1241,  1241,  1249,  1249,  1257,  1258,  1261,  1262,  1266,
    1267,  1268,  1269,  1270,  1271,  1272,  1273,  1274,  1275,  1276,
    1277,  1278,  1281,  1281,  1289,  1289,  1297,  1297,  1305,  1305,
    1313,  1313,  1321,  1321,  1329,  1329,  1337,  1337,  1345,  1345,
    1353,  1353,  1361,  1361,  1374,  1374,  1384,  1384,  1395,  1395,
    1405,  1406,  1409,  1409,  1417,  1418,  1421,  1422,  1425,  1426,
    1427,  1428,  1429,  1430,  1431,  1434,  1436,  1436,  1448,  1455,
    1455,  1465,  1466,  1469,  1470,  1473,  1473,  1481,  1481,  1491,
    1491,  1501,  1501,  1509,  1510,  1513,  1514,  1515,  1516,  1517,
    1518,  1519,  1520,  1521,  1522,  1523,  1524,  1525,  1526,  1527,
    1530,  1535,  1535,  1543,  1543,  1551,  1556,  1556,  1564,  1569,
    1574,  1574,  1582,  1583,  1586,  1586,  1594,  1599,  1604,  1609,
    1609,  1617,  1620,  1623,  1626,  1629,  1635,  1635,  1645,  1645,
    1652,  1652,  1664,  1664,  1677,  1678,  1682,  1686,  1686,  1698,
    1699,  1703,  1703,  1711,  1712,  1715,  1716,  1717,  1718,  1719,
    1722,  1727,  1727,  1735,  1735,  1745,  1746,  1749,  1749,  1757,
    1758,  1761,  1762,  1763,  1764,  1767,  1767,  1775,  1780,  1785
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
#line 4151 "dhcp4_parser.cc" // lalr1.cc:1167
#line 1790 "dhcp4_parser.yy" // lalr1.cc:1168


void
isc::dhcp::Dhcp4Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
