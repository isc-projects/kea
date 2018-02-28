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
      case 169: // value
      case 173: // map_value
      case 211: // socket_type
      case 214: // outbound_interface_value
      case 224: // db_type
      case 303: // hr_mode
      case 448: // ncr_protocol_value
      case 456: // replace_client_name_value
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
  Dhcp4Parser::stack_symbol_type&
  Dhcp4Parser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
      switch (that.type_get ())
    {
      case 169: // value
      case 173: // map_value
      case 211: // socket_type
      case 214: // outbound_interface_value
      case 224: // db_type
      case 303: // hr_mode
      case 448: // ncr_protocol_value
      case 456: // replace_client_name_value
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
            case 150: // "constant string"

#line 228 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< std::string > (); }
#line 366 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 151: // "integer"

#line 228 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< int64_t > (); }
#line 373 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 152: // "floating point"

#line 228 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< double > (); }
#line 380 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 153: // "boolean"

#line 228 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< bool > (); }
#line 387 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 169: // value

#line 228 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 394 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 173: // map_value

#line 228 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 401 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 211: // socket_type

#line 228 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 408 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 214: // outbound_interface_value

#line 228 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 415 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 224: // db_type

#line 228 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 422 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 303: // hr_mode

#line 228 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 429 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 448: // ncr_protocol_value

#line 228 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 436 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 456: // replace_client_name_value

#line 228 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 443 "dhcp4_parser.cc" // lalr1.cc:636
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
      case 169: // value
      case 173: // map_value
      case 211: // socket_type
      case 214: // outbound_interface_value
      case 224: // db_type
      case 303: // hr_mode
      case 448: // ncr_protocol_value
      case 456: // replace_client_name_value
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
#line 237 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.NO_KEYWORD; }
#line 690 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 4:
#line 238 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.CONFIG; }
#line 696 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 6:
#line 239 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.DHCP4; }
#line 702 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 8:
#line 240 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.INTERFACES_CONFIG; }
#line 708 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 10:
#line 241 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.SUBNET4; }
#line 714 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 12:
#line 242 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.POOLS; }
#line 720 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 14:
#line 243 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.RESERVATIONS; }
#line 726 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 16:
#line 244 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.DHCP4; }
#line 732 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 18:
#line 245 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.OPTION_DEF; }
#line 738 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 20:
#line 246 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.OPTION_DATA; }
#line 744 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 22:
#line 247 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.HOOKS_LIBRARIES; }
#line 750 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 24:
#line 248 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.DHCP_DDNS; }
#line 756 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 26:
#line 249 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.LOGGING; }
#line 762 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 28:
#line 257 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 768 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 29:
#line 258 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as< double > (), ctx.loc2pos(yystack_[0].location))); }
#line 774 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 30:
#line 259 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 780 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 31:
#line 260 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 786 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 32:
#line 261 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 792 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 33:
#line 262 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 798 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 34:
#line 263 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 804 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 35:
#line 266 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as< ElementPtr > ());
}
#line 813 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 36:
#line 271 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 824 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 37:
#line 276 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 834 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 38:
#line 282 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 840 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 41:
#line 289 "dhcp4_parser.yy" // lalr1.cc:859
    {
                  // map containing a single entry
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 849 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 42:
#line 293 "dhcp4_parser.yy" // lalr1.cc:859
    {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 859 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 43:
#line 300 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 868 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 44:
#line 303 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // list parsing complete. Put any sanity checking here
}
#line 876 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 47:
#line 311 "dhcp4_parser.yy" // lalr1.cc:859
    {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 885 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 48:
#line 315 "dhcp4_parser.yy" // lalr1.cc:859
    {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 894 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 49:
#line 322 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // List parsing about to start
}
#line 902 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 50:
#line 324 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // list parsing complete. Put any sanity checking here
    //ctx.stack_.pop_back();
}
#line 911 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 53:
#line 333 "dhcp4_parser.yy" // lalr1.cc:859
    {
                          ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 920 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 54:
#line 337 "dhcp4_parser.yy" // lalr1.cc:859
    {
                          ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 929 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 55:
#line 348 "dhcp4_parser.yy" // lalr1.cc:859
    {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as< std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 940 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 56:
#line 358 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 951 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 57:
#line 363 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.

    // Dhcp4 is required
    ctx.require("Dhcp4", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
}
#line 964 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 66:
#line 387 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Dhcp4", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP4);
}
#line 977 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 67:
#line 394 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // No global parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 987 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 68:
#line 402 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the Dhcp4 map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 997 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 69:
#line 406 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // No global parameter is required
    // parsing completed
}
#line 1006 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 98:
#line 445 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 1015 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 99:
#line 450 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 1024 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 100:
#line 455 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 1033 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 101:
#line 460 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr dpp(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 1042 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 102:
#line 465 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr echo(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("echo-client-id", echo);
}
#line 1051 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 103:
#line 470 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr match(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("match-client-id", match);
}
#line 1060 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 104:
#line 476 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces-config", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.INTERFACES_CONFIG);
}
#line 1071 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 105:
#line 481 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // No interfaces config param is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1081 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 115:
#line 500 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1091 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 116:
#line 504 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // No interfaces config param is required
    // parsing completed
}
#line 1100 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 117:
#line 509 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1111 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 118:
#line 514 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1120 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 119:
#line 519 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.DHCP_SOCKET_TYPE);
}
#line 1128 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 120:
#line 521 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("dhcp-socket-type", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1137 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 121:
#line 526 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("raw", ctx.loc2pos(yystack_[0].location))); }
#line 1143 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 122:
#line 527 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("udp", ctx.loc2pos(yystack_[0].location))); }
#line 1149 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 123:
#line 530 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.OUTBOUND_INTERFACE);
}
#line 1157 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 124:
#line 532 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("outbound-interface", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1166 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 125:
#line 537 "dhcp4_parser.yy" // lalr1.cc:859
    {
    yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("same-as-inbound", ctx.loc2pos(yystack_[0].location)));
}
#line 1174 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 126:
#line 539 "dhcp4_parser.yy" // lalr1.cc:859
    {
    yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("use-routing", ctx.loc2pos(yystack_[0].location)));
    }
#line 1182 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 127:
#line 543 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("re-detect", b);
}
#line 1191 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 128:
#line 549 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lease-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.LEASE_DATABASE);
}
#line 1202 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 129:
#line 554 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1213 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 130:
#line 561 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1224 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 131:
#line 566 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1235 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 149:
#line 594 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.DATABASE_TYPE);
}
#line 1243 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 150:
#line 596 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("type", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1252 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 151:
#line 601 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("memfile", ctx.loc2pos(yystack_[0].location))); }
#line 1258 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 152:
#line 602 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("mysql", ctx.loc2pos(yystack_[0].location))); }
#line 1264 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 153:
#line 603 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("postgresql", ctx.loc2pos(yystack_[0].location))); }
#line 1270 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 154:
#line 604 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("cql", ctx.loc2pos(yystack_[0].location))); }
#line 1276 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 155:
#line 607 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1284 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 156:
#line 609 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr user(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1294 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 157:
#line 615 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1302 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 158:
#line 617 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr pwd(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 1312 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 159:
#line 623 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1320 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 160:
#line 625 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr h(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 1330 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 161:
#line 631 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr p(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", p);
}
#line 1339 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 162:
#line 636 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1347 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 163:
#line 638 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1357 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 164:
#line 644 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 1366 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 165:
#line 649 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 1375 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 166:
#line 654 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 1384 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 167:
#line 659 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("connect-timeout", n);
}
#line 1393 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 168:
#line 664 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1401 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 169:
#line 666 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr cp(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("contact-points", cp);
    ctx.leave();
}
#line 1411 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 170:
#line 672 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1419 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 171:
#line 674 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr ks(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("keyspace", ks);
    ctx.leave();
}
#line 1429 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 172:
#line 680 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reconnect-tries", n);
}
#line 1438 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 173:
#line 685 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reconnect-wait-time", n);
}
#line 1447 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 174:
#line 690 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 1458 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 175:
#line 695 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1467 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 183:
#line 711 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1476 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 184:
#line 716 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 1485 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 185:
#line 721 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr circuit(new StringElement("circuit-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(circuit);
}
#line 1494 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 186:
#line 726 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr client(new StringElement("client-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(client);
}
#line 1503 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 187:
#line 731 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr flex_id(new StringElement("flex-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(flex_id);
}
#line 1512 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 188:
#line 736 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 1523 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 189:
#line 741 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1532 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 194:
#line 754 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1542 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 195:
#line 758 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1552 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 196:
#line 764 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1562 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 197:
#line 768 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 1572 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 203:
#line 783 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1580 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 204:
#line 785 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr lib(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 1590 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 205:
#line 791 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1598 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 206:
#line 793 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1607 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 207:
#line 799 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.EXPIRED_LEASES_PROCESSING);
}
#line 1618 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 208:
#line 804 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // No expired lease parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1628 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 217:
#line 822 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 1637 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 218:
#line 827 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 1646 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 219:
#line 832 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 1655 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 220:
#line 837 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 1664 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 221:
#line 842 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 1673 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 222:
#line 847 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 1682 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 223:
#line 855 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet4", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET4);
}
#line 1693 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 224:
#line 860 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1702 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 229:
#line 880 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1712 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 230:
#line 884 "dhcp4_parser.yy" // lalr1.cc:859
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
#line 1738 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 231:
#line 906 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the subnet4 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1748 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 232:
#line 910 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The subnet subnet4 parameter is required
    ctx.require("subnet", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 1758 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 259:
#line 948 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1766 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 260:
#line 950 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr subnet(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 1776 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 261:
#line 956 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1784 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 262:
#line 958 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface", iface);
    ctx.leave();
}
#line 1794 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 263:
#line 964 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1802 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 264:
#line 966 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface-id", iface);
    ctx.leave();
}
#line 1812 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 265:
#line 972 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1820 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 266:
#line 974 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-subnet", iface);
    ctx.leave();
}
#line 1830 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 267:
#line 980 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1838 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 268:
#line 982 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 1848 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 269:
#line 988 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1856 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 270:
#line 990 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface-id", iface);
    ctx.leave();
}
#line 1866 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 271:
#line 996 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.CLIENT_CLASS);
}
#line 1874 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 272:
#line 998 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr cls(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 1884 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 273:
#line 1004 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.RESERVATION_MODE);
}
#line 1892 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 274:
#line 1006 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("reservation-mode", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1901 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 275:
#line 1011 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("disabled", ctx.loc2pos(yystack_[0].location))); }
#line 1907 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 276:
#line 1012 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("out-of-pool", ctx.loc2pos(yystack_[0].location))); }
#line 1913 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 277:
#line 1013 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("all", ctx.loc2pos(yystack_[0].location))); }
#line 1919 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 278:
#line 1016 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr id(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 1928 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 279:
#line 1021 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr rc(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rapid-commit", rc);
}
#line 1937 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 280:
#line 1028 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("shared-networks", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SHARED_NETWORK);
}
#line 1948 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 281:
#line 1033 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1957 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 286:
#line 1048 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1967 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 287:
#line 1052 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1975 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 307:
#line 1083 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 1986 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 308:
#line 1088 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1995 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 309:
#line 1096 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2004 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 310:
#line 1099 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 2012 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 315:
#line 1115 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2022 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 316:
#line 1119 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2034 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 317:
#line 1130 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2044 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 318:
#line 1134 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2056 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 334:
#line 1166 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr code(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 2065 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 336:
#line 1173 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2073 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 337:
#line 1175 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 2083 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 338:
#line 1181 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2091 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 339:
#line 1183 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 2101 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 340:
#line 1189 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2109 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 341:
#line 1191 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr space(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 2119 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 343:
#line 1199 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2127 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 344:
#line 1201 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr encap(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 2137 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 345:
#line 1207 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr array(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 2146 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 346:
#line 1216 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 2157 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 347:
#line 1221 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2166 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 352:
#line 1240 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2176 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 353:
#line 1244 "dhcp4_parser.yy" // lalr1.cc:859
    {
    /// @todo: the code or name parameters are required.
    ctx.stack_.pop_back();
}
#line 2185 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 354:
#line 1252 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2195 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 355:
#line 1256 "dhcp4_parser.yy" // lalr1.cc:859
    {
    /// @todo: the code or name parameters are required.
    // parsing completed
}
#line 2204 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 370:
#line 1289 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2212 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 371:
#line 1291 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr data(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 2222 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 374:
#line 1301 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr space(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", space);
}
#line 2231 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 375:
#line 1306 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr persist(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-send", persist);
}
#line 2240 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 376:
#line 1314 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 2251 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 377:
#line 1319 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2260 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 382:
#line 1334 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2270 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 383:
#line 1338 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2280 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 384:
#line 1344 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2290 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 385:
#line 1348 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2300 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 393:
#line 1365 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2308 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 394:
#line 1367 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr pool(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 2318 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 395:
#line 1373 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2326 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 396:
#line 1375 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr parent = ctx.stack_.back();
    ElementPtr user_context = yystack_[0].value.as< ElementPtr > ();
    ConstElementPtr old = parent->get("user-context");

    // Handle already existing user context
    if (old) {
        // Check if it was a comment or a duplicate
        if ((old->size() != 1) || !old->contains("comment")) {
            std::stringstream msg;
            msg << "duplicate user-context entries (previous at "
                << old->getPosition().str() << ")";
            error(yystack_[3].location, msg.str());
        }
        // Merge the comment
        user_context->set("comment", old->get("comment"));
    }

    // Set the user context
    parent->set("user-context", user_context);
    ctx.leave();
}
#line 2353 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 397:
#line 1398 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2361 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 398:
#line 1400 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr parent = ctx.stack_.back();
    ElementPtr user_context(new MapElement(ctx.loc2pos(yystack_[3].location)));
    ElementPtr comment(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    user_context->set("comment", comment);

    // Handle already existing user context
    ConstElementPtr old = parent->get("user-context");
    if (old) {
        // Check for duplicate comment
        if (old->contains("comment")) {
            std::stringstream msg;
            msg << "duplicate user-context/comment entries (previous at "
                << old->getPosition().str() << ")";
            error(yystack_[3].location, msg.str());
        }
        // Merge the user context in the comment
        merge(user_context, old);
    }

    // Set the user context
    parent->set("user-context", user_context);
    ctx.leave();
}
#line 2390 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 399:
#line 1428 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 2401 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 400:
#line 1433 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2410 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 405:
#line 1446 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2420 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 406:
#line 1450 "dhcp4_parser.yy" // lalr1.cc:859
    {
    /// @todo: an identifier parameter is required.
    ctx.stack_.pop_back();
}
#line 2429 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 407:
#line 1455 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2439 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 408:
#line 1459 "dhcp4_parser.yy" // lalr1.cc:859
    {
    /// @todo: an identifier parameter is required.
    // parsing completed
}
#line 2448 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 428:
#line 1490 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2456 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 429:
#line 1492 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr next_server(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("next-server", next_server);
    ctx.leave();
}
#line 2466 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 430:
#line 1498 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2474 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 431:
#line 1500 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr srv(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-hostname", srv);
    ctx.leave();
}
#line 2484 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 432:
#line 1506 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2492 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 433:
#line 1508 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr bootfile(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("boot-file-name", bootfile);
    ctx.leave();
}
#line 2502 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 434:
#line 1514 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2510 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 435:
#line 1516 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr addr(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", addr);
    ctx.leave();
}
#line 2520 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 436:
#line 1522 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2528 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 437:
#line 1524 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr d(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 2538 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 438:
#line 1530 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2546 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 439:
#line 1532 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 2556 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 440:
#line 1538 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2564 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 441:
#line 1540 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-id", hw);
    ctx.leave();
}
#line 2574 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 442:
#line 1546 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2582 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 443:
#line 1548 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("circuit-id", hw);
    ctx.leave();
}
#line 2592 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 444:
#line 1554 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2600 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 445:
#line 1556 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flex-id", hw);
    ctx.leave();
}
#line 2610 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 446:
#line 1562 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2618 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 447:
#line 1564 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr host(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 2628 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 448:
#line 1570 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2639 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 449:
#line 1575 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2648 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 450:
#line 1583 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 2659 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 451:
#line 1588 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2668 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 452:
#line 1593 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2676 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 453:
#line 1595 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr ip(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", ip);
    ctx.leave();
}
#line 2686 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 454:
#line 1604 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 2697 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 455:
#line 1609 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2706 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 458:
#line 1618 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2716 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 459:
#line 1622 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The name client class parameter is required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2726 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 475:
#line 1650 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2734 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 476:
#line 1652 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr test(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 2744 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 477:
#line 1662 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 2753 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 478:
#line 1669 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 2764 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 479:
#line 1674 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2773 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 487:
#line 1690 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2781 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 488:
#line 1692 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr stype(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 2791 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 489:
#line 1698 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2799 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 490:
#line 1700 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 2809 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 491:
#line 1708 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 2820 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 492:
#line 1713 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2831 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 493:
#line 1720 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2841 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 494:
#line 1724 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2851 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 514:
#line 1753 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 2860 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 515:
#line 1758 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2868 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 516:
#line 1760 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("qualifying-suffix", s);
    ctx.leave();
}
#line 2878 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 517:
#line 1766 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2886 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 518:
#line 1768 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 2896 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 519:
#line 1774 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 2905 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 520:
#line 1779 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2913 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 521:
#line 1781 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 2923 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 522:
#line 1787 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 2932 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 523:
#line 1792 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 2941 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 524:
#line 1797 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 2949 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 525:
#line 1799 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2958 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 526:
#line 1805 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 2964 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 527:
#line 1806 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 2970 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 528:
#line 1809 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NCR_FORMAT);
}
#line 2978 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 529:
#line 1811 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 2988 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 530:
#line 1817 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-include-fqdn", b);
}
#line 2997 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 531:
#line 1822 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-no-update", b);
}
#line 3006 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 532:
#line 1827 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-client-update", b);
}
#line 3015 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 533:
#line 1832 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 3023 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 534:
#line 1834 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("replace-client-name", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3032 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 535:
#line 1840 "dhcp4_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("when-present", ctx.loc2pos(yystack_[0].location))); 
      }
#line 3040 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 536:
#line 1843 "dhcp4_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location)));
      }
#line 3048 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 537:
#line 1846 "dhcp4_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("always", ctx.loc2pos(yystack_[0].location)));
      }
#line 3056 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 538:
#line 1849 "dhcp4_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("when-not-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 3064 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 539:
#line 1852 "dhcp4_parser.yy" // lalr1.cc:859
    {
      error(yystack_[0].location, "boolean values for the replace-client-name are "
                "no longer supported");
      }
#line 3073 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 540:
#line 1858 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3081 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 541:
#line 1860 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("generated-prefix", s);
    ctx.leave();
}
#line 3091 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 542:
#line 1868 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3099 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 543:
#line 1870 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("Dhcp6", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3108 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 544:
#line 1875 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3116 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 545:
#line 1877 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("DhcpDdns", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3125 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 546:
#line 1882 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3133 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 547:
#line 1884 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("Control-agent", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3142 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 548:
#line 1894 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Logging", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.LOGGING);
}
#line 3153 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 549:
#line 1899 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3162 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 550:
#line 1904 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the Logging map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3172 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 551:
#line 1908 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 3180 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 555:
#line 1924 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 3191 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 556:
#line 1929 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3200 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 559:
#line 1941 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 3210 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 560:
#line 1945 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 3218 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 570:
#line 1962 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr dl(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 3227 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 571:
#line 1967 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3235 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 572:
#line 1969 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 3245 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 573:
#line 1975 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 3256 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 574:
#line 1980 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3265 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 577:
#line 1989 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3275 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 578:
#line 1993 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 3283 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 585:
#line 2007 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3291 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 586:
#line 2009 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 3301 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 587:
#line 2015 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr flush(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 3310 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 588:
#line 2020 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr maxsize(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 3319 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 589:
#line 2025 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr maxver(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 3328 "dhcp4_parser.cc" // lalr1.cc:859
    break;


#line 3332 "dhcp4_parser.cc" // lalr1.cc:859
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


  const short int Dhcp4Parser::yypact_ninf_ = -752;

  const signed char Dhcp4Parser::yytable_ninf_ = -1;

  const short int
  Dhcp4Parser::yypact_[] =
  {
     455,  -752,  -752,  -752,  -752,  -752,  -752,  -752,  -752,  -752,
    -752,  -752,  -752,  -752,    12,    29,     9,    26,    30,    81,
      96,    98,   108,   143,   145,   156,   158,   160,  -752,  -752,
    -752,  -752,  -752,  -752,  -752,  -752,  -752,  -752,  -752,  -752,
    -752,  -752,  -752,  -752,  -752,  -752,  -752,  -752,  -752,  -752,
    -752,  -752,  -752,  -752,  -752,  -752,  -752,  -752,  -752,  -752,
    -752,  -752,  -752,  -752,    29,  -127,     1,   173,   111,    40,
      16,   374,    80,   181,   198,   -49,   359,    50,  -752,   140,
     182,   185,   204,   211,  -752,  -752,  -752,  -752,  -752,   220,
    -752,    36,  -752,  -752,  -752,  -752,  -752,  -752,  -752,   229,
     242,  -752,  -752,  -752,  -752,  -752,   254,   264,   293,   301,
    -752,  -752,  -752,  -752,  -752,  -752,  -752,  -752,  -752,  -752,
     302,  -752,  -752,  -752,    45,  -752,  -752,  -752,  -752,  -752,
    -752,  -752,  -752,  -752,  -752,  -752,  -752,  -752,  -752,  -752,
    -752,  -752,  -752,  -752,  -752,  -752,  -752,  -752,  -752,  -752,
    -752,  -752,  -752,  -752,   303,  -752,    62,  -752,  -752,  -752,
    -752,  -752,  -752,  -752,  -752,  -752,  -752,  -752,  -752,  -752,
    -752,  -752,   304,   306,  -752,  -752,  -752,  -752,  -752,  -752,
    -752,  -752,  -752,    69,  -752,  -752,  -752,  -752,  -752,  -752,
    -752,  -752,  -752,  -752,  -752,  -752,  -752,  -752,  -752,  -752,
    -752,  -752,  -752,  -752,  -752,  -752,  -752,    71,  -752,  -752,
    -752,  -752,  -752,  -752,  -752,  -752,  -752,  -752,  -752,  -752,
    -752,  -752,  -752,  -752,   252,   308,  -752,  -752,  -752,  -752,
    -752,  -752,  -752,  -752,  -752,  -752,  -752,  -752,   307,  -752,
    -752,   310,  -752,  -752,  -752,   313,  -752,  -752,   311,   309,
    -752,  -752,  -752,  -752,  -752,  -752,  -752,  -752,  -752,  -752,
    -752,  -752,  -752,   316,   318,  -752,  -752,  -752,  -752,   317,
     324,  -752,  -752,  -752,  -752,  -752,  -752,  -752,  -752,  -752,
    -752,  -752,  -752,    72,  -752,  -752,  -752,   325,  -752,  -752,
     330,  -752,   331,   333,  -752,  -752,   334,   335,   337,  -752,
    -752,  -752,  -752,  -752,    84,  -752,  -752,  -752,  -752,  -752,
    -752,  -752,  -752,  -752,  -752,  -752,  -752,  -752,  -752,  -752,
    -752,   130,  -752,  -752,  -752,    29,    29,  -752,   178,   340,
     341,   342,   351,   352,  -752,     1,  -752,   353,   217,   218,
     370,   371,   372,   376,   378,   227,   232,   234,   239,   388,
     389,   395,   397,   398,   399,   400,   402,   403,   404,   261,
     410,   411,   173,  -752,   412,   413,   414,   266,   111,  -752,
     134,   416,   417,   418,   420,   438,   439,   440,   294,   296,
     442,   443,   444,   447,    40,  -752,   449,    16,  -752,   450,
     451,   458,   474,   475,   476,   477,   478,  -752,   374,  -752,
     479,   480,   336,   481,   482,   484,   338,  -752,   181,   486,
     339,   343,  -752,   198,   491,   496,   -46,  -752,   348,   498,
     499,   354,   500,   357,   361,   506,   509,   362,   364,   366,
     510,   516,   359,  -752,   517,    50,  -752,  -752,  -752,   518,
     519,   523,    29,    29,    29,  -752,   524,  -752,  -752,   375,
     382,   383,   527,   528,  -752,  -752,  -752,  -752,   532,   533,
     534,   536,   535,   393,   539,   540,   542,   541,  -752,   543,
     544,  -752,   547,   208,   283,  -752,  -752,  -752,  -752,  -752,
    -752,  -752,  -752,  -752,  -752,  -752,  -752,   548,   546,  -752,
    -752,  -752,   405,   407,   408,   554,   419,   421,   422,  -752,
    -752,    20,   424,   555,   556,  -752,   425,  -752,   547,   426,
     427,   428,   429,   430,   432,   433,  -752,   434,   435,  -752,
     437,   456,   457,  -752,  -752,   459,  -752,  -752,  -752,   460,
      29,  -752,  -752,   461,   462,  -752,   463,  -752,  -752,    25,
     441,  -752,  -752,  -752,   -24,   464,  -752,   557,  -752,    29,
     173,    50,  -752,  -752,  -752,   111,  -752,  -752,  -752,   396,
     396,   559,   560,   561,   563,  -752,  -752,  -752,   147,    34,
     581,    75,   125,   359,  -752,  -752,  -752,  -752,  -752,  -752,
    -752,  -752,   585,  -752,   134,  -752,  -752,  -752,   583,  -752,
    -752,  -752,  -752,  -752,  -752,  -752,  -752,   598,   526,  -752,
    -752,  -752,  -752,  -752,  -752,  -752,  -752,  -752,  -752,  -752,
    -752,  -752,  -752,  -752,  -752,  -752,  -752,  -752,  -752,  -752,
    -752,  -752,  -752,  -752,  -752,  -752,  -752,  -752,  -752,  -752,
     601,  -752,   151,   152,   199,  -752,  -752,  -752,  -752,   612,
     613,   614,   615,   616,  -752,  -752,   617,   618,  -752,   201,
    -752,  -752,  -752,  -752,  -752,  -752,  -752,  -752,  -752,  -752,
    -752,  -752,  -752,  -752,  -752,   203,  -752,   558,   620,  -752,
    -752,   619,   621,  -752,  -752,   622,   623,  -752,  -752,   624,
     626,  -752,  -752,  -752,  -752,  -752,  -752,    53,  -752,  -752,
    -752,  -752,  -752,  -752,  -752,   119,  -752,   625,   629,  -752,
     630,   631,   632,   633,   634,   635,   241,  -752,  -752,  -752,
    -752,  -752,  -752,  -752,  -752,  -752,  -752,  -752,  -752,   277,
    -752,  -752,  -752,   278,   483,   490,  -752,  -752,   636,   638,
    -752,  -752,   637,   641,  -752,  -752,   639,  -752,   128,  -752,
    -752,  -752,  -752,   642,   644,   645,   646,   494,   501,   502,
     503,   504,   647,   648,   507,   508,   396,  -752,  -752,    40,
    -752,   559,   181,  -752,   560,   198,  -752,   561,    95,  -752,
     563,   147,  -752,    34,  -752,   -49,  -752,   581,   511,   512,
     513,   514,   515,   520,    75,  -752,   653,   656,   125,  -752,
    -752,  -752,   655,   664,  -752,    16,  -752,   583,   374,  -752,
     598,   665,  -752,   149,   601,  -752,   332,   522,   525,   529,
    -752,  -752,  -752,  -752,  -752,   530,   531,  -752,  -752,  -752,
     279,  -752,   660,  -752,   662,  -752,  -752,  -752,  -752,  -752,
    -752,  -752,  -752,  -752,  -752,  -752,   280,  -752,  -752,  -752,
    -752,  -752,  -752,  -752,  -752,  -752,  -752,  -752,   286,  -752,
    -752,  -752,  -752,  -752,  -752,  -752,  -752,   537,   538,  -752,
    -752,   551,   287,  -752,   666,  -752,   553,  -752,   669,  -752,
    -752,  -752,  -752,  -752,   288,  -752,  -752,  -752,  -752,  -752,
    -752,  -752,  -752,  -752,  -752,  -752,  -752,  -752,  -752,  -752,
    -752,  -752,  -752,    95,  -752,  -752,  -752,  -752,  -752,  -752,
    -752,  -752,   672,   562,   673,   149,  -752,  -752,   677,  -752,
     564,  -752,   671,  -752,  -752,   256,  -752,   139,   671,  -752,
    -752,   679,   680,   681,   295,  -752,  -752,  -752,  -752,  -752,
    -752,   682,   545,   565,   568,   139,  -752,   573,  -752,  -752,
    -752,  -752,  -752
  };

  const unsigned short int
  Dhcp4Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,    24,    26,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     1,    43,
      36,    32,    31,    28,    29,    30,    35,     3,    33,    34,
      56,     5,    68,     7,   115,     9,   231,    11,   384,    13,
     407,    15,   309,    17,   317,    19,   354,    21,   196,    23,
     493,    25,   550,    27,    45,    39,     0,     0,     0,     0,
       0,   409,     0,   319,   356,     0,     0,     0,    47,     0,
      46,     0,     0,    40,    66,   548,   542,   544,   546,     0,
      65,     0,    58,    60,    62,    63,    64,    61,   104,     0,
       0,   428,   430,   432,   128,   130,     0,     0,     0,     0,
     223,   307,   346,   280,   395,   397,   174,   454,   188,   207,
       0,   478,   491,    97,     0,    70,    72,    73,    74,    75,
      90,    91,    78,    79,    80,    81,    85,    86,    76,    77,
      83,    84,    95,    96,    92,    93,    94,    82,    87,    88,
      89,   117,   119,   123,     0,   114,     0,   106,   108,   109,
     110,   111,   112,   113,   458,   261,   263,   265,   376,   259,
     267,   269,     0,     0,   273,   271,   399,   450,   258,   235,
     236,   237,   249,     0,   233,   240,   253,   254,   255,   241,
     242,   245,   247,   243,   244,   238,   239,   256,   257,   246,
     250,   251,   252,   248,   393,   392,   389,     0,   386,   388,
     390,   391,   448,   436,   438,   442,   440,   446,   444,   434,
     427,   421,   425,   426,     0,   410,   411,   422,   423,   424,
     418,   413,   419,   415,   416,   417,   420,   414,     0,   336,
     162,     0,   340,   338,   343,     0,   332,   333,     0,   320,
     321,   323,   335,   324,   325,   326,   342,   327,   328,   329,
     330,   331,   370,     0,     0,   368,   369,   372,   373,     0,
     357,   358,   360,   361,   362,   363,   364,   365,   366,   367,
     203,   205,   200,     0,   198,   201,   202,     0,   515,   517,
       0,   520,     0,     0,   524,   528,     0,     0,     0,   533,
     540,   513,   511,   512,     0,   495,   497,   498,   499,   500,
     501,   502,   503,   504,   505,   506,   507,   508,   509,   510,
     555,     0,   552,   554,    44,     0,     0,    37,     0,     0,
       0,     0,     0,     0,    55,     0,    57,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    69,     0,     0,     0,     0,     0,   116,
     460,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   232,     0,     0,   385,     0,
       0,     0,     0,     0,     0,     0,     0,   408,     0,   310,
       0,     0,     0,     0,     0,     0,     0,   318,     0,     0,
       0,     0,   355,     0,     0,     0,     0,   197,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   494,     0,     0,   551,    48,    41,     0,
       0,     0,     0,     0,     0,    59,     0,   102,   103,     0,
       0,     0,     0,     0,    98,    99,   100,   101,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   477,     0,
       0,    71,     0,     0,     0,   127,   107,   475,   473,   474,
     466,   467,   471,   472,   468,   469,   470,     0,   461,   462,
     464,   465,     0,     0,     0,     0,     0,     0,     0,   278,
     279,     0,     0,     0,     0,   234,     0,   387,     0,     0,
       0,     0,     0,     0,     0,     0,   412,     0,     0,   334,
       0,     0,     0,   345,   322,     0,   374,   375,   359,     0,
       0,   199,   514,     0,     0,   519,     0,   522,   523,     0,
       0,   530,   531,   532,     0,     0,   496,     0,   553,     0,
       0,     0,   543,   545,   547,     0,   429,   431,   433,     0,
       0,   225,   311,   348,   282,    38,   396,   398,     0,     0,
     190,     0,     0,     0,    49,   118,   121,   122,   120,   125,
     126,   124,     0,   459,     0,   262,   264,   266,   378,   260,
     268,   270,   275,   276,   277,   274,   272,   401,     0,   394,
     449,   437,   439,   443,   441,   447,   445,   435,   337,   163,
     341,   339,   344,   371,   204,   206,   516,   518,   521,   526,
     527,   525,   529,   535,   536,   537,   538,   539,   534,   541,
       0,    42,     0,     0,     0,   149,   155,   157,   159,     0,
       0,     0,     0,     0,   168,   170,     0,     0,   148,     0,
     132,   134,   135,   136,   137,   138,   139,   140,   141,   142,
     143,   144,   147,   145,   146,     0,   229,     0,   226,   227,
     315,     0,   312,   313,   352,     0,   349,   350,   286,     0,
     283,   284,   183,   184,   185,   186,   187,     0,   176,   178,
     179,   180,   181,   182,   456,     0,   194,     0,   191,   192,
       0,     0,     0,     0,     0,     0,     0,   209,   211,   212,
     213,   214,   215,   216,   487,   489,   486,   484,   485,     0,
     480,   482,   483,     0,    51,     0,   463,   382,     0,   379,
     380,   405,     0,   402,   403,   452,     0,   559,     0,   557,
      67,   549,   105,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   129,   131,     0,
     224,     0,   319,   308,     0,   356,   347,     0,     0,   281,
       0,     0,   175,     0,   455,     0,   189,     0,     0,     0,
       0,     0,     0,     0,     0,   208,     0,     0,     0,   479,
     492,    53,     0,    52,   476,     0,   377,     0,   409,   400,
       0,     0,   451,     0,     0,   556,     0,     0,     0,     0,
     161,   164,   165,   166,   167,     0,     0,   172,   173,   133,
       0,   228,     0,   314,     0,   351,   306,   303,   293,   294,
     296,   290,   291,   292,   302,   301,     0,   288,   295,   304,
     305,   297,   298,   299,   300,   285,   177,   457,     0,   193,
     217,   218,   219,   220,   221,   222,   210,     0,     0,   481,
      50,     0,     0,   381,     0,   404,     0,   573,     0,   571,
     569,   563,   567,   568,     0,   561,   565,   566,   564,   558,
     151,   152,   153,   154,   150,   156,   158,   160,   169,   171,
     230,   316,   353,     0,   287,   195,   488,   490,    54,   383,
     406,   453,     0,     0,     0,     0,   560,   289,     0,   570,
       0,   562,     0,   572,   577,     0,   575,     0,     0,   574,
     585,     0,     0,     0,     0,   579,   581,   582,   583,   584,
     576,     0,     0,     0,     0,     0,   578,     0,   587,   588,
     589,   580,   586
  };

  const short int
  Dhcp4Parser::yypgoto_[] =
  {
    -752,  -752,  -752,  -752,  -752,  -752,  -752,  -752,  -752,  -752,
    -752,  -752,  -752,  -752,  -752,   -33,  -752,   165,  -752,  -752,
    -752,  -752,  -752,  -752,  -752,  -752,   184,  -752,  -752,  -752,
     -66,  -752,  -752,  -752,   377,  -752,  -752,  -752,  -752,   144,
     327,   -68,   -51,   -48,  -752,  -752,   -34,  -752,  -752,   142,
     358,  -752,  -752,  -752,  -752,  -752,  -752,  -752,  -752,  -752,
    -752,  -752,  -752,  -752,  -752,  -752,   146,   -29,  -752,  -752,
    -752,  -752,  -752,  -752,  -752,  -752,  -752,  -752,   -61,  -752,
    -752,  -752,  -752,  -752,  -752,  -752,  -752,  -752,  -752,  -752,
    -752,  -752,  -752,   -43,  -752,  -752,  -752,  -752,  -752,  -752,
    -752,  -752,  -752,   -47,  -752,  -752,  -752,   -42,   315,  -752,
    -752,  -752,  -752,  -752,  -752,  -752,   -45,  -752,  -752,  -752,
    -752,  -752,  -752,  -751,  -752,  -752,  -752,   -26,  -752,  -752,
    -752,   -23,   363,  -752,  -752,  -752,  -752,  -752,  -752,  -752,
    -752,  -748,  -752,  -752,  -752,  -563,  -752,  -746,  -752,  -752,
    -752,  -752,  -752,  -752,  -752,  -752,   -32,  -752,  -752,  -152,
     -57,  -752,  -752,  -752,  -752,  -752,   -14,  -752,  -752,  -752,
     -17,  -752,   344,  -752,   -60,  -752,  -752,  -752,  -752,  -752,
     -55,  -752,  -752,  -752,  -752,  -752,    -3,  -752,  -752,  -752,
     -12,  -752,  -752,  -752,    -7,  -752,   347,  -752,  -752,  -752,
    -752,  -752,  -752,  -752,  -752,  -752,  -752,  -752,   -35,  -752,
    -752,  -752,   -31,   380,  -752,  -752,   -44,  -752,   -19,  -752,
    -752,  -752,  -752,  -752,   -37,  -752,  -752,  -752,   -30,  -752,
     355,   -11,  -752,     2,  -752,     7,  -752,  -752,  -752,  -752,
    -752,  -752,  -752,  -752,  -752,  -752,  -752,  -752,  -752,  -752,
    -752,  -752,  -752,  -740,  -752,  -752,  -752,  -752,  -752,  -752,
    -752,  -752,  -752,   187,  -752,  -752,  -752,  -752,  -752,  -752,
    -752,   -16,  -752,  -752,  -752,  -752,  -752,  -752,  -752,  -752,
     200,   345,  -752,  -752,  -752,  -752,  -752,  -752,  -752,  -752,
    -752,  -752,  -752,  -752,  -752,  -752,  -752,  -752,  -752,  -752,
    -752,  -752,  -752,  -752,  -752,  -752,  -752,  -752,  -752,  -752,
    -752,  -752,  -752,  -752,  -752,   223,   346,  -752,  -752,  -752,
     -22,  -752,  -752,  -125,  -752,  -752,  -752,  -752,  -752,  -752,
    -140,  -752,  -752,  -150,  -752,  -752,  -752,  -752,  -752
  };

  const short int
  Dhcp4Parser::yydefgoto_[] =
  {
      -1,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    36,    37,    38,    65,   566,
      82,    83,    39,    64,    79,    80,   575,   724,   792,   793,
     123,    41,    66,    91,    92,    93,   329,    43,    67,   124,
     125,   126,   127,   128,   129,   130,   131,   132,   337,   156,
     157,    45,    68,   158,   364,   159,   365,   578,   160,   366,
     581,   161,   133,   343,   134,   344,   649,   650,   651,   743,
     884,   652,   744,   653,   745,   654,   746,   655,   247,   401,
     657,   658,   659,   660,   661,   752,   662,   753,   663,   664,
     135,   355,   687,   688,   689,   690,   691,   692,   693,   136,
     357,   697,   698,   699,   775,    59,    75,   283,   284,   285,
     414,   286,   415,   137,   358,   706,   707,   708,   709,   710,
     711,   712,   713,   138,   349,   667,   668,   669,   759,    47,
      69,   183,   184,   185,   375,   186,   371,   187,   372,   188,
     373,   189,   376,   190,   377,   191,   381,   192,   380,   595,
     193,   194,   139,   352,   679,   680,   681,   768,   836,   837,
     140,   350,    53,    72,   671,   672,   673,   762,    55,    73,
     248,   249,   250,   251,   252,   253,   254,   400,   255,   404,
     256,   403,   257,   258,   405,   259,   141,   351,   675,   676,
     677,   765,    57,    74,   269,   270,   271,   272,   273,   409,
     274,   275,   276,   277,   196,   374,   728,   729,   730,   795,
      49,    70,   207,   208,   209,   386,   142,   353,   143,   354,
     199,   382,   732,   733,   734,   798,    51,    71,   224,   225,
     226,   144,   340,   145,   341,   146,   342,   230,   396,   231,
     390,   232,   391,   233,   393,   234,   392,   235,   395,   236,
     394,   237,   389,   203,   383,   736,   801,   147,   356,   695,
     370,   487,   488,   489,   490,   491,   582,   148,   149,   360,
     719,   720,   721,   786,   722,   787,   150,   361,    61,    76,
     304,   305,   306,   307,   419,   308,   420,   309,   310,   422,
     311,   312,   313,   425,   621,   314,   426,   315,   316,   317,
     318,   430,   628,   319,   431,    94,   331,    95,   332,    96,
     333,    97,   330,    63,    77,   321,   322,   323,   434,   738,
     739,   803,   874,   875,   876,   877,   904,   878,   902,   915,
     916,   917,   924,   925,   926,   931,   927,   928,   929
  };

  const unsigned short int
  Dhcp4Parser::yytable_[] =
  {
      90,   179,   155,   178,   205,   220,   694,   246,   265,   282,
     301,    84,    28,   266,   267,   238,    40,   832,   180,   268,
     833,   181,   835,    81,   162,   197,   210,   222,   844,   260,
     278,    78,   302,    42,    29,   182,    30,    44,    31,   335,
     619,   164,   280,   281,   336,   280,   281,   164,   362,   163,
     198,   211,   223,   363,   261,   279,   771,   303,   200,   772,
     227,   100,   101,   102,   103,   368,   195,   206,   221,   112,
     369,   201,   384,   228,   387,   416,   202,   385,   229,   388,
     417,   204,   114,   115,   106,   107,   108,   432,    46,   165,
     166,   167,   433,   112,   592,   593,   594,   623,   624,   625,
     626,    89,   164,    48,   168,    50,   114,   115,   169,   170,
     171,   172,   173,   174,   175,    52,   100,   101,   102,   103,
     175,   176,   773,   151,   152,   774,    85,   153,   177,   627,
     154,   804,   111,   435,   805,    86,    87,    88,   436,   106,
     107,   108,   832,   110,   620,   833,   324,   835,   112,   240,
      54,    89,    56,   844,   362,   435,   101,   102,   103,   740,
     741,   114,   115,    58,   170,    60,    89,    62,   174,   700,
     701,   702,   703,   704,   705,   175,   320,   114,   115,    32,
      33,    34,    35,   177,    98,   325,   111,   112,   240,   326,
      89,   114,   115,    99,   100,   101,   102,   103,   104,   105,
     114,   115,   368,   240,   756,   834,   756,   742,   239,   757,
     847,   758,   327,   477,   328,   114,   115,   106,   107,   108,
     109,   110,   576,   577,   334,   111,   112,   714,   715,   682,
     683,   684,   685,   338,   686,   240,   113,   241,   242,   114,
     115,   243,   244,   245,   784,    89,   339,   114,   115,   785,
     116,   117,   240,   262,   241,   242,   263,   264,   345,   918,
     397,    89,   919,   118,   114,   115,   119,   920,   346,    90,
     921,   922,   923,   120,   121,    89,   867,   122,   868,   869,
     788,   432,   384,   893,    89,   789,   790,   890,   894,   416,
     387,   905,   437,   438,   895,   899,   906,   347,   935,    89,
     579,   580,   155,   936,   478,   348,   359,   367,   378,   479,
     379,   398,   408,   480,   402,   399,   179,   406,   178,   407,
     410,   205,   411,    89,   162,   412,   482,   413,   439,   418,
     834,    89,   220,   180,   421,   423,   181,   424,   427,   428,
     197,   429,   246,   210,   440,   441,   442,   265,    89,   163,
     182,   483,   266,   267,   222,   443,   444,   446,   268,   484,
     880,   881,   882,   883,   260,   198,   301,   481,   211,   278,
     447,   448,   485,   200,   449,   450,   451,   486,   454,   223,
     452,   195,   453,   455,   206,   456,   201,   227,   302,   261,
     457,   202,   458,   459,   279,   221,   101,   102,   103,   460,
     228,   461,   462,   463,   464,   229,   465,   466,   467,   552,
     553,   554,   468,   303,   469,   470,   472,   473,   474,   475,
     492,   493,   494,   635,   495,   114,   115,   112,   636,   637,
     638,   639,   640,   641,   642,   643,   644,   645,   646,   647,
     114,   115,   496,   497,   498,   499,   501,   502,   503,   500,
     240,   504,   212,   506,   508,   509,   213,   214,   215,   216,
     217,   218,   510,   219,   287,   288,   289,   290,   291,   292,
     293,   294,   295,   296,   297,   298,   299,   300,   511,   512,
     513,   514,   515,   517,   518,   520,   521,   519,   522,   155,
     525,   523,   526,   648,   648,   529,   527,   615,   656,   656,
     530,   532,   533,   534,   536,   535,   716,   301,   537,    89,
     539,   162,   538,   540,   544,   541,   631,   542,   478,   543,
     545,   547,   549,   479,    89,   556,   550,   480,   717,   302,
     551,   555,   557,   558,   559,   560,   163,   561,   562,   563,
     482,   564,    30,   567,   568,   569,    89,   570,   571,   584,
     572,   573,   574,   718,   303,   585,   583,   586,   587,   588,
     597,   622,   630,   598,   760,   483,   666,   670,   674,   589,
     678,   590,   591,   484,   596,   599,   601,   602,   603,   604,
     605,   481,   606,   607,   608,   609,   485,   610,   696,   725,
     727,   486,     1,     2,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,   731,   611,   612,   737,   613,
     614,   616,   617,   618,   629,   735,   747,   748,   749,   750,
     751,   754,   755,   761,   764,   763,   767,   565,   766,   770,
     769,   776,   777,   791,   778,   779,   780,   781,   782,   783,
     794,   797,   796,   799,   800,   810,   806,   802,   807,   808,
     809,   815,   816,   812,   811,   814,   813,   857,   817,   818,
     858,   860,   850,   851,   852,   853,   854,   861,   891,   866,
     892,   855,   885,   903,   900,   886,   908,   910,   914,   887,
     888,   889,   912,   932,   933,   934,   937,   896,   897,   471,
     648,   179,   600,   178,   632,   656,   246,   634,   938,   265,
     827,   898,   826,   901,   266,   267,   665,   831,   180,   282,
     268,   181,   445,   909,   913,   197,   939,   828,   260,   940,
     829,   278,   716,   942,   839,   182,   476,   819,   846,   205,
     849,   531,   220,   848,   830,   821,   820,   870,   845,   856,
     198,   907,   871,   261,   717,   822,   279,   505,   200,   840,
     823,   210,   524,   516,   222,   825,   195,   841,   824,   872,
     528,   201,   863,   865,   862,   838,   202,   507,   864,   718,
     842,   726,   859,   723,   633,   843,   211,   546,   930,   223,
     911,   548,   879,     0,   873,   941,     0,   227,     0,     0,
       0,     0,   206,     0,     0,   221,     0,     0,     0,     0,
     228,     0,     0,     0,     0,   229,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   827,     0,   826,     0,     0,
       0,     0,   831,     0,     0,     0,     0,     0,     0,   870,
       0,     0,   828,     0,   871,   829,     0,     0,     0,   839,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   830,
       0,   872,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   840,     0,     0,     0,     0,     0,
       0,     0,   841,     0,     0,     0,   873,     0,     0,     0,
     838,     0,     0,     0,     0,   842,     0,     0,     0,     0,
     843
  };

  const short int
  Dhcp4Parser::yycheck_[] =
  {
      66,    69,    68,    69,    70,    71,   569,    73,    74,    75,
      76,    10,     0,    74,    74,    72,     7,   768,    69,    74,
     768,    69,   768,   150,    68,    69,    70,    71,   768,    73,
      74,    64,    76,     7,     5,    69,     7,     7,     9,     3,
      15,     7,    91,    92,     8,    91,    92,     7,     3,    68,
      69,    70,    71,     8,    73,    74,     3,    76,    69,     6,
      71,    21,    22,    23,    24,     3,    69,    70,    71,    53,
       8,    69,     3,    71,     3,     3,    69,     8,    71,     8,
       8,    65,    66,    67,    44,    45,    46,     3,     7,    49,
      50,    51,     8,    53,    74,    75,    76,   121,   122,   123,
     124,   150,     7,     7,    64,     7,    66,    67,    68,    69,
      70,    71,    72,    73,    80,     7,    21,    22,    23,    24,
      80,    81,     3,    12,    13,     6,   125,    16,    88,   153,
      19,     3,    52,     3,     6,   134,   135,   136,     8,    44,
      45,    46,   893,    48,   119,   893,     6,   893,    53,    54,
       7,   150,     7,   893,     3,     3,    22,    23,    24,     8,
       8,    66,    67,     7,    69,     7,   150,     7,    73,    94,
      95,    96,    97,    98,    99,    80,   126,    66,    67,   150,
     151,   152,   153,    88,    11,     3,    52,    53,    54,     4,
     150,    66,    67,    20,    21,    22,    23,    24,    25,    26,
      66,    67,     3,    54,     3,   768,     3,     8,    27,     8,
     773,     8,     8,    79,     3,    66,    67,    44,    45,    46,
      47,    48,    14,    15,     4,    52,    53,   102,   103,    82,
      83,    84,    85,     4,    87,    54,    63,    56,    57,    66,
      67,    60,    61,    62,     3,   150,     4,    66,    67,     8,
      77,    78,    54,    55,    56,    57,    58,    59,     4,     3,
       8,   150,     6,    90,    66,    67,    93,   128,     4,   335,
     131,   132,   133,   100,   101,   150,   127,   104,   129,   130,
       3,     3,     3,     3,   150,     8,     8,     8,     8,     3,
       3,     3,   325,   326,     8,     8,     8,     4,     3,   150,
      17,    18,   368,     8,   370,     4,     4,     4,     4,   370,
       4,     3,     3,   370,     4,     8,   384,     4,   384,     8,
       4,   387,     4,   150,   368,     8,   370,     3,   150,     4,
     893,   150,   398,   384,     4,     4,   384,     4,     4,     4,
     384,     4,   408,   387,     4,     4,     4,   413,   150,   368,
     384,   370,   413,   413,   398,     4,     4,     4,   413,   370,
      28,    29,    30,    31,   408,   384,   432,   370,   387,   413,
     153,   153,   370,   384,     4,     4,     4,   370,   151,   398,
       4,   384,     4,   151,   387,   151,   384,   398,   432,   408,
     151,   384,     4,     4,   413,   398,    22,    23,    24,     4,
     398,     4,     4,     4,     4,   398,     4,     4,     4,   442,
     443,   444,   151,   432,     4,     4,     4,     4,     4,   153,
       4,     4,     4,    27,     4,    66,    67,    53,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    43,
      66,    67,     4,     4,     4,   151,     4,     4,     4,   153,
      54,     4,    78,     4,     4,     4,    82,    83,    84,    85,
      86,    87,     4,    89,   105,   106,   107,   108,   109,   110,
     111,   112,   113,   114,   115,   116,   117,   118,     4,     4,
       4,     4,     4,     4,     4,     4,     4,   151,     4,   555,
       4,   153,   153,   559,   560,     4,   153,   530,   559,   560,
       4,   153,     4,     4,     4,   151,   572,   573,   151,   150,
       4,   555,   151,     4,     4,   153,   549,   153,   584,   153,
       4,     4,     4,   584,   150,   150,     7,   584,   572,   573,
       7,     7,   150,   150,     7,     7,   555,     5,     5,     5,
     584,     5,     7,   150,     5,     5,   150,     5,     7,     3,
       7,     7,     5,   572,   573,   150,     8,   150,   150,     5,
       5,   120,     5,     7,     6,   584,     7,     7,     7,   150,
       7,   150,   150,   584,   150,   150,   150,   150,   150,   150,
     150,   584,   150,   150,   150,   150,   584,   150,     7,     4,
       7,   584,   137,   138,   139,   140,   141,   142,   143,   144,
     145,   146,   147,   148,   149,     7,   150,   150,     7,   150,
     150,   150,   150,   150,   150,    89,     4,     4,     4,     4,
       4,     4,     4,     3,     3,     6,     3,   462,     6,     3,
       6,     6,     3,   150,     4,     4,     4,     4,     4,     4,
     150,     3,     6,     6,     3,   151,     4,     8,     4,     4,
       4,     4,     4,   151,   153,   151,   153,     4,   151,   151,
       4,     6,   151,   151,   151,   151,   151,     3,     8,     4,
       8,   151,   150,     4,     8,   150,     4,     4,     7,   150,
     150,   150,     5,     4,     4,     4,     4,   150,   150,   362,
     756,   759,   508,   759,   550,   756,   762,   555,   153,   765,
     768,   150,   768,   150,   765,   765,   560,   768,   759,   775,
     765,   759,   335,   151,   150,   759,   151,   768,   762,   151,
     768,   765,   788,   150,   768,   759,   368,   756,   771,   795,
     777,   416,   798,   775,   768,   761,   759,   803,   770,   784,
     759,   893,   803,   762,   788,   762,   765,   384,   759,   768,
     764,   795,   408,   398,   798,   767,   759,   768,   765,   803,
     413,   759,   797,   800,   795,   768,   759,   387,   798,   788,
     768,   584,   788,   573,   551,   768,   795,   432,   918,   798,
     905,   435,   804,    -1,   803,   935,    -1,   798,    -1,    -1,
      -1,    -1,   795,    -1,    -1,   798,    -1,    -1,    -1,    -1,
     798,    -1,    -1,    -1,    -1,   798,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   893,    -1,   893,    -1,    -1,
      -1,    -1,   893,    -1,    -1,    -1,    -1,    -1,    -1,   905,
      -1,    -1,   893,    -1,   905,   893,    -1,    -1,    -1,   893,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   893,
      -1,   905,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   893,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   893,    -1,    -1,    -1,   905,    -1,    -1,    -1,
     893,    -1,    -1,    -1,    -1,   893,    -1,    -1,    -1,    -1,
     893
  };

  const unsigned short int
  Dhcp4Parser::yystos_[] =
  {
       0,   137,   138,   139,   140,   141,   142,   143,   144,   145,
     146,   147,   148,   149,   155,   156,   157,   158,   159,   160,
     161,   162,   163,   164,   165,   166,   167,   168,     0,     5,
       7,     9,   150,   151,   152,   153,   169,   170,   171,   176,
       7,   185,     7,   191,     7,   205,     7,   283,     7,   364,
       7,   380,     7,   316,     7,   322,     7,   346,     7,   259,
       7,   432,     7,   467,   177,   172,   186,   192,   206,   284,
     365,   381,   317,   323,   347,   260,   433,   468,   169,   178,
     179,   150,   174,   175,    10,   125,   134,   135,   136,   150,
     184,   187,   188,   189,   459,   461,   463,   465,    11,    20,
      21,    22,    23,    24,    25,    26,    44,    45,    46,    47,
      48,    52,    53,    63,    66,    67,    77,    78,    90,    93,
     100,   101,   104,   184,   193,   194,   195,   196,   197,   198,
     199,   200,   201,   216,   218,   244,   253,   267,   277,   306,
     314,   340,   370,   372,   385,   387,   389,   411,   421,   422,
     430,    12,    13,    16,    19,   184,   203,   204,   207,   209,
     212,   215,   370,   372,     7,    49,    50,    51,    64,    68,
      69,    70,    71,    72,    73,    80,    81,    88,   184,   195,
     196,   197,   200,   285,   286,   287,   289,   291,   293,   295,
     297,   299,   301,   304,   305,   340,   358,   370,   372,   374,
     385,   387,   389,   407,    65,   184,   340,   366,   367,   368,
     370,   372,    78,    82,    83,    84,    85,    86,    87,    89,
     184,   340,   370,   372,   382,   383,   384,   385,   387,   389,
     391,   393,   395,   397,   399,   401,   403,   405,   314,    27,
      54,    56,    57,    60,    61,    62,   184,   232,   324,   325,
     326,   327,   328,   329,   330,   332,   334,   336,   337,   339,
     370,   372,    55,    58,    59,   184,   232,   328,   334,   348,
     349,   350,   351,   352,   354,   355,   356,   357,   370,   372,
      91,    92,   184,   261,   262,   263,   265,   105,   106,   107,
     108,   109,   110,   111,   112,   113,   114,   115,   116,   117,
     118,   184,   370,   372,   434,   435,   436,   437,   439,   441,
     442,   444,   445,   446,   449,   451,   452,   453,   454,   457,
     126,   469,   470,   471,     6,     3,     4,     8,     3,   190,
     466,   460,   462,   464,     4,     3,     8,   202,     4,     4,
     386,   388,   390,   217,   219,     4,     4,     4,     4,   278,
     315,   341,   307,   371,   373,   245,   412,   254,   268,     4,
     423,   431,     3,     8,   208,   210,   213,     4,     3,     8,
     414,   290,   292,   294,   359,   288,   296,   298,     4,     4,
     302,   300,   375,   408,     3,     8,   369,     3,     8,   406,
     394,   396,   400,   398,   404,   402,   392,     8,     3,     8,
     331,   233,     4,   335,   333,   338,     4,     8,     3,   353,
       4,     4,     8,     3,   264,   266,     3,     8,     4,   438,
     440,     4,   443,     4,     4,   447,   450,     4,     4,     4,
     455,   458,     3,     8,   472,     3,     8,   169,   169,   150,
       4,     4,     4,     4,     4,   188,     4,   153,   153,     4,
       4,     4,     4,     4,   151,   151,   151,   151,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,   151,     4,
       4,   194,     4,     4,     4,   153,   204,    79,   184,   232,
     314,   340,   370,   372,   385,   387,   389,   415,   416,   417,
     418,   419,     4,     4,     4,     4,     4,     4,     4,   151,
     153,     4,     4,     4,     4,   286,     4,   367,     4,     4,
       4,     4,     4,     4,     4,     4,   384,     4,     4,   151,
       4,     4,     4,   153,   326,     4,   153,   153,   350,     4,
       4,   262,   153,     4,     4,   151,     4,   151,   151,     4,
       4,   153,   153,   153,     4,     4,   435,     4,   470,     4,
       7,     7,   169,   169,   169,     7,   150,   150,   150,     7,
       7,     5,     5,     5,     5,   171,   173,   150,     5,     5,
       5,     7,     7,     7,     5,   180,    14,    15,   211,    17,
      18,   214,   420,     8,     3,   150,   150,   150,     5,   150,
     150,   150,    74,    75,    76,   303,   150,     5,     7,   150,
     180,   150,   150,   150,   150,   150,   150,   150,   150,   150,
     150,   150,   150,   150,   150,   169,   150,   150,   150,    15,
     119,   448,   120,   121,   122,   123,   124,   153,   456,   150,
       5,   169,   193,   469,   203,    27,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,   184,   220,
     221,   222,   225,   227,   229,   231,   232,   234,   235,   236,
     237,   238,   240,   242,   243,   220,     7,   279,   280,   281,
       7,   318,   319,   320,     7,   342,   343,   344,     7,   308,
     309,   310,    82,    83,    84,    85,    87,   246,   247,   248,
     249,   250,   251,   252,   299,   413,     7,   255,   256,   257,
      94,    95,    96,    97,    98,    99,   269,   270,   271,   272,
     273,   274,   275,   276,   102,   103,   184,   370,   372,   424,
     425,   426,   428,   434,   181,     4,   417,     7,   360,   361,
     362,     7,   376,   377,   378,    89,   409,     7,   473,   474,
       8,     8,     8,   223,   226,   228,   230,     4,     4,     4,
       4,     4,   239,   241,     4,     4,     3,     8,     8,   282,
       6,     3,   321,     6,     3,   345,     6,     3,   311,     6,
       3,     3,     6,     3,     6,   258,     6,     3,     4,     4,
       4,     4,     4,     4,     3,     8,   427,   429,     3,     8,
       8,   150,   182,   183,   150,   363,     6,     3,   379,     6,
       3,   410,     8,   475,     3,     6,     4,     4,     4,     4,
     151,   153,   151,   153,   151,     4,     4,   151,   151,   221,
     285,   281,   324,   320,   348,   344,   184,   195,   196,   197,
     200,   232,   277,   295,   299,   301,   312,   313,   340,   370,
     372,   385,   387,   389,   407,   310,   247,   299,   261,   257,
     151,   151,   151,   151,   151,   151,   270,     4,     4,   425,
       6,     3,   366,   362,   382,   378,     4,   127,   129,   130,
     184,   232,   370,   372,   476,   477,   478,   479,   481,   474,
      28,    29,    30,    31,   224,   150,   150,   150,   150,   150,
       8,     8,     8,     3,     8,     8,   150,   150,   150,     8,
       8,   150,   482,     4,   480,     3,     8,   313,     4,   151,
       4,   477,     5,   150,     7,   483,   484,   485,     3,     6,
     128,   131,   132,   133,   486,   487,   488,   490,   491,   492,
     484,   489,     4,     4,     4,     3,     8,     4,   153,   151,
     151,   487,   150
  };

  const unsigned short int
  Dhcp4Parser::yyr1_[] =
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
     194,   194,   194,   194,   194,   194,   194,   194,   195,   196,
     197,   198,   199,   200,   202,   201,   203,   203,   204,   204,
     204,   204,   204,   204,   204,   206,   205,   208,   207,   210,
     209,   211,   211,   213,   212,   214,   214,   215,   217,   216,
     219,   218,   220,   220,   221,   221,   221,   221,   221,   221,
     221,   221,   221,   221,   221,   221,   221,   221,   221,   223,
     222,   224,   224,   224,   224,   226,   225,   228,   227,   230,
     229,   231,   233,   232,   234,   235,   236,   237,   239,   238,
     241,   240,   242,   243,   245,   244,   246,   246,   247,   247,
     247,   247,   247,   248,   249,   250,   251,   252,   254,   253,
     255,   255,   256,   256,   258,   257,   260,   259,   261,   261,
     261,   262,   262,   264,   263,   266,   265,   268,   267,   269,
     269,   270,   270,   270,   270,   270,   270,   271,   272,   273,
     274,   275,   276,   278,   277,   279,   279,   280,   280,   282,
     281,   284,   283,   285,   285,   286,   286,   286,   286,   286,
     286,   286,   286,   286,   286,   286,   286,   286,   286,   286,
     286,   286,   286,   286,   286,   286,   286,   286,   286,   288,
     287,   290,   289,   292,   291,   294,   293,   296,   295,   298,
     297,   300,   299,   302,   301,   303,   303,   303,   304,   305,
     307,   306,   308,   308,   309,   309,   311,   310,   312,   312,
     313,   313,   313,   313,   313,   313,   313,   313,   313,   313,
     313,   313,   313,   313,   313,   313,   313,   315,   314,   317,
     316,   318,   318,   319,   319,   321,   320,   323,   322,   324,
     324,   325,   325,   326,   326,   326,   326,   326,   326,   326,
     326,   326,   326,   327,   328,   329,   331,   330,   333,   332,
     335,   334,   336,   338,   337,   339,   341,   340,   342,   342,
     343,   343,   345,   344,   347,   346,   348,   348,   349,   349,
     350,   350,   350,   350,   350,   350,   350,   350,   350,   351,
     353,   352,   354,   355,   356,   357,   359,   358,   360,   360,
     361,   361,   363,   362,   365,   364,   366,   366,   367,   367,
     367,   367,   367,   369,   368,   371,   370,   373,   372,   375,
     374,   376,   376,   377,   377,   379,   378,   381,   380,   382,
     382,   383,   383,   384,   384,   384,   384,   384,   384,   384,
     384,   384,   384,   384,   384,   384,   384,   384,   386,   385,
     388,   387,   390,   389,   392,   391,   394,   393,   396,   395,
     398,   397,   400,   399,   402,   401,   404,   403,   406,   405,
     408,   407,   410,   409,   412,   411,   413,   413,   414,   299,
     415,   415,   416,   416,   417,   417,   417,   417,   417,   417,
     417,   417,   417,   417,   418,   420,   419,   421,   423,   422,
     424,   424,   425,   425,   425,   425,   425,   427,   426,   429,
     428,   431,   430,   433,   432,   434,   434,   435,   435,   435,
     435,   435,   435,   435,   435,   435,   435,   435,   435,   435,
     435,   435,   435,   435,   436,   438,   437,   440,   439,   441,
     443,   442,   444,   445,   447,   446,   448,   448,   450,   449,
     451,   452,   453,   455,   454,   456,   456,   456,   456,   456,
     458,   457,   460,   459,   462,   461,   464,   463,   466,   465,
     468,   467,   469,   469,   470,   472,   471,   473,   473,   475,
     474,   476,   476,   477,   477,   477,   477,   477,   477,   477,
     478,   480,   479,   482,   481,   483,   483,   485,   484,   486,
     486,   487,   487,   487,   487,   489,   488,   490,   491,   492
  };

  const unsigned char
  Dhcp4Parser::yyr2_[] =
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
       1,     1,     1,     1,     1,     1,     1,     1,     3,     3,
       3,     3,     3,     3,     0,     6,     1,     3,     1,     1,
       1,     1,     1,     1,     1,     0,     4,     0,     4,     0,
       4,     1,     1,     0,     4,     1,     1,     3,     0,     6,
       0,     6,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     0,
       4,     1,     1,     1,     1,     0,     4,     0,     4,     0,
       4,     3,     0,     4,     3,     3,     3,     3,     0,     4,
       0,     4,     3,     3,     0,     6,     1,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     0,     6,
       0,     1,     1,     3,     0,     4,     0,     4,     1,     3,
       1,     1,     1,     0,     4,     0,     4,     0,     6,     1,
       3,     1,     1,     1,     1,     1,     1,     3,     3,     3,
       3,     3,     3,     0,     6,     0,     1,     1,     3,     0,
       4,     0,     4,     1,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     4,     1,     1,     1,     3,     3,
       0,     6,     0,     1,     1,     3,     0,     4,     1,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     0,     6,     0,
       4,     0,     1,     1,     3,     0,     4,     0,     4,     0,
       1,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     3,     1,     0,     4,     0,     4,
       0,     4,     1,     0,     4,     3,     0,     6,     0,     1,
       1,     3,     0,     4,     0,     4,     0,     1,     1,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       0,     4,     1,     1,     3,     3,     0,     6,     0,     1,
       1,     3,     0,     4,     0,     4,     1,     3,     1,     1,
       1,     1,     1,     0,     4,     0,     4,     0,     4,     0,
       6,     0,     1,     1,     3,     0,     4,     0,     4,     0,
       1,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     0,     4,
       0,     4,     0,     4,     0,     4,     0,     4,     0,     4,
       0,     4,     0,     4,     0,     4,     0,     4,     0,     4,
       0,     6,     0,     4,     0,     6,     1,     3,     0,     4,
       0,     1,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     0,     4,     3,     0,     6,
       1,     3,     1,     1,     1,     1,     1,     0,     4,     0,
       4,     0,     6,     0,     4,     1,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     3,     0,     4,     0,     4,     3,
       0,     4,     3,     3,     0,     4,     1,     1,     0,     4,
       3,     3,     3,     0,     4,     1,     1,     1,     1,     1,
       0,     4,     0,     4,     0,     4,     0,     4,     0,     6,
       0,     4,     1,     3,     1,     0,     6,     1,     3,     0,
       4,     1,     3,     1,     1,     1,     1,     1,     1,     1,
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
  "\"raw\"", "\"udp\"", "\"outbound-interface\"", "\"same-as-inbound\"",
  "\"use-routing\"", "\"re-detect\"", "\"echo-client-id\"",
  "\"match-client-id\"", "\"next-server\"", "\"server-hostname\"",
  "\"boot-file-name\"", "\"lease-database\"", "\"hosts-database\"",
  "\"type\"", "\"memfile\"", "\"mysql\"", "\"postgresql\"", "\"cql\"",
  "\"user\"", "\"password\"", "\"host\"", "\"port\"", "\"persist\"",
  "\"lfc-interval\"", "\"readonly\"", "\"connect-timeout\"",
  "\"contact-points\"", "\"keyspace\"", "\"max-reconnect-tries\"",
  "\"reconnect-wait-time\"", "\"valid-lifetime\"", "\"renew-timer\"",
  "\"rebind-timer\"", "\"decline-probation-period\"", "\"subnet4\"",
  "\"4o6-interface\"", "\"4o6-interface-id\"", "\"4o6-subnet\"",
  "\"option-def\"", "\"option-data\"", "\"name\"", "\"data\"", "\"code\"",
  "\"space\"", "\"csv-format\"", "\"always-send\"", "\"record-types\"",
  "\"encapsulate\"", "\"array\"", "\"shared-networks\"", "\"pools\"",
  "\"pool\"", "\"user-context\"", "\"comment\"", "\"subnet\"",
  "\"interface\"", "\"interface-id\"", "\"id\"", "\"rapid-commit\"",
  "\"reservation-mode\"", "\"disabled\"", "\"out-of-pool\"", "\"all\"",
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
  "SUB_DHCP_DDNS", "SUB_LOGGING", "\"constant string\"", "\"integer\"",
  "\"floating point\"", "\"boolean\"", "$accept", "start", "$@1", "$@2",
  "$@3", "$@4", "$@5", "$@6", "$@7", "$@8", "$@9", "$@10", "$@11", "$@12",
  "$@13", "value", "sub_json", "map2", "$@14", "map_value", "map_content",
  "not_empty_map", "list_generic", "$@15", "list_content",
  "not_empty_list", "list_strings", "$@16", "list_strings_content",
  "not_empty_list_strings", "unknown_map_entry", "syntax_map", "$@17",
  "global_objects", "global_object", "dhcp4_object", "$@18", "sub_dhcp4",
  "$@19", "global_params", "global_param", "valid_lifetime", "renew_timer",
  "rebind_timer", "decline_probation_period", "echo_client_id",
  "match_client_id", "interfaces_config", "$@20",
  "interfaces_config_params", "interfaces_config_param", "sub_interfaces4",
  "$@21", "interfaces_list", "$@22", "dhcp_socket_type", "$@23",
  "socket_type", "outbound_interface", "$@24", "outbound_interface_value",
  "re_detect", "lease_database", "$@25", "hosts_database", "$@26",
  "database_map_params", "database_map_param", "database_type", "$@27",
  "db_type", "user", "$@28", "password", "$@29", "host", "$@30", "port",
  "name", "$@31", "persist", "lfc_interval", "readonly", "connect_timeout",
  "contact_points", "$@32", "keyspace", "$@33", "max_reconnect_tries",
  "reconnect_wait_time", "host_reservation_identifiers", "$@34",
  "host_reservation_identifiers_list", "host_reservation_identifier",
  "duid_id", "hw_address_id", "circuit_id", "client_id", "flex_id",
  "hooks_libraries", "$@35", "hooks_libraries_list",
  "not_empty_hooks_libraries_list", "hooks_library", "$@36",
  "sub_hooks_library", "$@37", "hooks_params", "hooks_param", "library",
  "$@38", "parameters", "$@39", "expired_leases_processing", "$@40",
  "expired_leases_params", "expired_leases_param",
  "reclaim_timer_wait_time", "flush_reclaimed_timer_wait_time",
  "hold_reclaimed_time", "max_reclaim_leases", "max_reclaim_time",
  "unwarned_reclaim_cycles", "subnet4_list", "$@41",
  "subnet4_list_content", "not_empty_subnet4_list", "subnet4", "$@42",
  "sub_subnet4", "$@43", "subnet4_params", "subnet4_param", "subnet",
  "$@44", "subnet_4o6_interface", "$@45", "subnet_4o6_interface_id",
  "$@46", "subnet_4o6_subnet", "$@47", "interface", "$@48", "interface_id",
  "$@49", "client_class", "$@50", "reservation_mode", "$@51", "hr_mode",
  "id", "rapid_commit", "shared_networks", "$@52",
  "shared_networks_content", "shared_networks_list", "shared_network",
  "$@53", "shared_network_params", "shared_network_param",
  "option_def_list", "$@54", "sub_option_def_list", "$@55",
  "option_def_list_content", "not_empty_option_def_list",
  "option_def_entry", "$@56", "sub_option_def", "$@57",
  "option_def_params", "not_empty_option_def_params", "option_def_param",
  "option_def_name", "code", "option_def_code", "option_def_type", "$@58",
  "option_def_record_types", "$@59", "space", "$@60", "option_def_space",
  "option_def_encapsulate", "$@61", "option_def_array", "option_data_list",
  "$@62", "option_data_list_content", "not_empty_option_data_list",
  "option_data_entry", "$@63", "sub_option_data", "$@64",
  "option_data_params", "not_empty_option_data_params",
  "option_data_param", "option_data_name", "option_data_data", "$@65",
  "option_data_code", "option_data_space", "option_data_csv_format",
  "option_data_always_send", "pools_list", "$@66", "pools_list_content",
  "not_empty_pools_list", "pool_list_entry", "$@67", "sub_pool4", "$@68",
  "pool_params", "pool_param", "pool_entry", "$@69", "user_context",
  "$@70", "comment", "$@71", "reservations", "$@72", "reservations_list",
  "not_empty_reservations_list", "reservation", "$@73", "sub_reservation",
  "$@74", "reservation_params", "not_empty_reservation_params",
  "reservation_param", "next_server", "$@75", "server_hostname", "$@76",
  "boot_file_name", "$@77", "ip_address", "$@78", "duid", "$@79",
  "hw_address", "$@80", "client_id_value", "$@81", "circuit_id_value",
  "$@82", "flex_id_value", "$@83", "hostname", "$@84",
  "reservation_client_classes", "$@85", "relay", "$@86", "relay_map",
  "$@87", "client_classes", "$@88", "client_classes_list", "$@89",
  "client_class_params", "not_empty_client_class_params",
  "client_class_param", "client_class_name", "client_class_test", "$@90",
  "dhcp4o6_port", "control_socket", "$@91", "control_socket_params",
  "control_socket_param", "control_socket_type", "$@92",
  "control_socket_name", "$@93", "dhcp_ddns", "$@94", "sub_dhcp_ddns",
  "$@95", "dhcp_ddns_params", "dhcp_ddns_param", "enable_updates",
  "qualifying_suffix", "$@96", "server_ip", "$@97", "server_port",
  "sender_ip", "$@98", "sender_port", "max_queue_size", "ncr_protocol",
  "$@99", "ncr_protocol_value", "ncr_format", "$@100",
  "always_include_fqdn", "override_no_update", "override_client_update",
  "replace_client_name", "$@101", "replace_client_name_value",
  "generated_prefix", "$@102", "dhcp6_json_object", "$@103",
  "dhcpddns_json_object", "$@104", "control_agent_json_object", "$@105",
  "logging_object", "$@106", "sub_logging", "$@107", "logging_params",
  "logging_param", "loggers", "$@108", "loggers_entries", "logger_entry",
  "$@109", "logger_params", "logger_param", "debuglevel", "severity",
  "$@110", "output_options_list", "$@111", "output_options_list_content",
  "output_entry", "$@112", "output_params_list", "output_params", "output",
  "$@113", "flush", "maxsize", "maxver", YY_NULLPTR
  };

#if PARSER4_DEBUG
  const unsigned short int
  Dhcp4Parser::yyrline_[] =
  {
       0,   237,   237,   237,   238,   238,   239,   239,   240,   240,
     241,   241,   242,   242,   243,   243,   244,   244,   245,   245,
     246,   246,   247,   247,   248,   248,   249,   249,   257,   258,
     259,   260,   261,   262,   263,   266,   271,   271,   282,   285,
     286,   289,   293,   300,   300,   307,   308,   311,   315,   322,
     322,   329,   330,   333,   337,   348,   358,   358,   374,   375,
     379,   380,   381,   382,   383,   384,   387,   387,   402,   402,
     411,   412,   417,   418,   419,   420,   421,   422,   423,   424,
     425,   426,   427,   428,   429,   430,   431,   432,   433,   434,
     435,   436,   437,   438,   439,   440,   441,   442,   445,   450,
     455,   460,   465,   470,   476,   476,   487,   488,   491,   492,
     493,   494,   495,   496,   497,   500,   500,   509,   509,   519,
     519,   526,   527,   530,   530,   537,   539,   543,   549,   549,
     561,   561,   573,   574,   577,   578,   579,   580,   581,   582,
     583,   584,   585,   586,   587,   588,   589,   590,   591,   594,
     594,   601,   602,   603,   604,   607,   607,   615,   615,   623,
     623,   631,   636,   636,   644,   649,   654,   659,   664,   664,
     672,   672,   680,   685,   690,   690,   700,   701,   704,   705,
     706,   707,   708,   711,   716,   721,   726,   731,   736,   736,
     746,   747,   750,   751,   754,   754,   764,   764,   774,   775,
     776,   779,   780,   783,   783,   791,   791,   799,   799,   810,
     811,   814,   815,   816,   817,   818,   819,   822,   827,   832,
     837,   842,   847,   855,   855,   868,   869,   872,   873,   880,
     880,   906,   906,   917,   918,   922,   923,   924,   925,   926,
     927,   928,   929,   930,   931,   932,   933,   934,   935,   936,
     937,   938,   939,   940,   941,   942,   943,   944,   945,   948,
     948,   956,   956,   964,   964,   972,   972,   980,   980,   988,
     988,   996,   996,  1004,  1004,  1011,  1012,  1013,  1016,  1021,
    1028,  1028,  1039,  1040,  1044,  1045,  1048,  1048,  1056,  1057,
    1060,  1061,  1062,  1063,  1064,  1065,  1066,  1067,  1068,  1069,
    1070,  1071,  1072,  1073,  1074,  1075,  1076,  1083,  1083,  1096,
    1096,  1105,  1106,  1109,  1110,  1115,  1115,  1130,  1130,  1144,
    1145,  1148,  1149,  1152,  1153,  1154,  1155,  1156,  1157,  1158,
    1159,  1160,  1161,  1164,  1166,  1171,  1173,  1173,  1181,  1181,
    1189,  1189,  1197,  1199,  1199,  1207,  1216,  1216,  1228,  1229,
    1234,  1235,  1240,  1240,  1252,  1252,  1264,  1265,  1270,  1271,
    1276,  1277,  1278,  1279,  1280,  1281,  1282,  1283,  1284,  1287,
    1289,  1289,  1297,  1299,  1301,  1306,  1314,  1314,  1326,  1327,
    1330,  1331,  1334,  1334,  1344,  1344,  1354,  1355,  1358,  1359,
    1360,  1361,  1362,  1365,  1365,  1373,  1373,  1398,  1398,  1428,
    1428,  1438,  1439,  1442,  1443,  1446,  1446,  1455,  1455,  1464,
    1465,  1468,  1469,  1473,  1474,  1475,  1476,  1477,  1478,  1479,
    1480,  1481,  1482,  1483,  1484,  1485,  1486,  1487,  1490,  1490,
    1498,  1498,  1506,  1506,  1514,  1514,  1522,  1522,  1530,  1530,
    1538,  1538,  1546,  1546,  1554,  1554,  1562,  1562,  1570,  1570,
    1583,  1583,  1593,  1593,  1604,  1604,  1614,  1615,  1618,  1618,
    1628,  1629,  1632,  1633,  1636,  1637,  1638,  1639,  1640,  1641,
    1642,  1643,  1644,  1645,  1648,  1650,  1650,  1662,  1669,  1669,
    1679,  1680,  1683,  1684,  1685,  1686,  1687,  1690,  1690,  1698,
    1698,  1708,  1708,  1720,  1720,  1730,  1731,  1734,  1735,  1736,
    1737,  1738,  1739,  1740,  1741,  1742,  1743,  1744,  1745,  1746,
    1747,  1748,  1749,  1750,  1753,  1758,  1758,  1766,  1766,  1774,
    1779,  1779,  1787,  1792,  1797,  1797,  1805,  1806,  1809,  1809,
    1817,  1822,  1827,  1832,  1832,  1840,  1843,  1846,  1849,  1852,
    1858,  1858,  1868,  1868,  1875,  1875,  1882,  1882,  1894,  1894,
    1904,  1904,  1915,  1916,  1920,  1924,  1924,  1936,  1937,  1941,
    1941,  1949,  1950,  1953,  1954,  1955,  1956,  1957,  1958,  1959,
    1962,  1967,  1967,  1975,  1975,  1985,  1986,  1989,  1989,  1997,
    1998,  2001,  2002,  2003,  2004,  2007,  2007,  2015,  2020,  2025
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
#line 4518 "dhcp4_parser.cc" // lalr1.cc:1167
#line 2030 "dhcp4_parser.yy" // lalr1.cc:1168


void
isc::dhcp::Dhcp4Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
