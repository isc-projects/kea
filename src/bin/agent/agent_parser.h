// A Bison parser, made by GNU Bison 3.2.1.

// Skeleton interface for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015, 2018 Free Software Foundation, Inc.

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


/**
 ** \file agent_parser.h
 ** Define the isc::agent::parser class.
 */

// C++ LALR(1) parser skeleton written by Akim Demaille.

// Undocumented macros, especially those whose name start with YY_,
// are private implementation details.  Do not rely on them.

#ifndef YY_AGENT_AGENT_PARSER_H_INCLUDED
# define YY_AGENT_AGENT_PARSER_H_INCLUDED
// //                    "%code requires" blocks.
#line 17 "agent_parser.yy" // lalr1.cc:404

#include <string>
#include <cc/data.h>
#include <boost/lexical_cast.hpp>
#include <agent/parser_context_decl.h>

using namespace isc::agent;
using namespace isc::data;
using namespace std;

#line 59 "agent_parser.h" // lalr1.cc:404

# include <cassert>
# include <cstdlib> // std::abort
# include <iostream>
# include <stdexcept>
# include <string>
# include <vector>

// Support move semantics when possible.
#if defined __cplusplus && 201103L <= __cplusplus
# define YY_MOVE           std::move
# define YY_MOVE_OR_COPY   move
# define YY_MOVE_REF(Type) Type&&
# define YY_RVREF(Type)    Type&&
# define YY_COPY(Type)     Type
#else
# define YY_MOVE
# define YY_MOVE_OR_COPY   copy
# define YY_MOVE_REF(Type) Type&
# define YY_RVREF(Type)    const Type&
# define YY_COPY(Type)     const Type&
#endif
# include "location.hh"
#include <typeinfo>
#ifndef YYASSERT
# include <cassert>
# define YYASSERT assert
#endif


#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

/* Debug traces.  */
#ifndef AGENT_DEBUG
# if defined YYDEBUG
#if YYDEBUG
#   define AGENT_DEBUG 1
#  else
#   define AGENT_DEBUG 0
#  endif
# else /* ! defined YYDEBUG */
#  define AGENT_DEBUG 1
# endif /* ! defined YYDEBUG */
#endif  /* ! defined AGENT_DEBUG */

#line 14 "agent_parser.yy" // lalr1.cc:404
namespace isc { namespace agent {
#line 161 "agent_parser.h" // lalr1.cc:404

  /// A stack with random access from its top.
  template <typename T, typename S = std::vector<T> >
  class stack
  {
  public:
    // Hide our reversed order.
    typedef typename S::reverse_iterator iterator;
    typedef typename S::const_reverse_iterator const_iterator;
    typedef typename S::size_type size_type;

    stack (size_type n = 200)
      : seq_ (n)
    {}

    /// Random access.
    ///
    /// Index 0 returns the topmost element.
    T&
    operator[] (size_type i)
    {
      return seq_[size () - 1 - i];
    }

    /// Random access.
    ///
    /// Index 0 returns the topmost element.
    T&
    operator[] (int i)
    {
      return operator[] (size_type (i));
    }

    /// Random access.
    ///
    /// Index 0 returns the topmost element.
    const T&
    operator[] (size_type i) const
    {
      return seq_[size () - 1 - i];
    }

    /// Random access.
    ///
    /// Index 0 returns the topmost element.
    const T&
    operator[] (int i) const
    {
      return operator[] (size_type (i));
    }

    /// Steal the contents of \a t.
    ///
    /// Close to move-semantics.
    void
    push (YY_MOVE_REF (T) t)
    {
      seq_.push_back (T ());
      operator[](0).move (t);
    }

    void
    pop (int n = 1)
    {
      for (; 0 < n; --n)
        seq_.pop_back ();
    }

    void
    clear ()
    {
      seq_.clear ();
    }

    size_type
    size () const
    {
      return seq_.size ();
    }

    const_iterator
    begin () const
    {
      return seq_.rbegin ();
    }

    const_iterator
    end () const
    {
      return seq_.rend ();
    }

  private:
    stack (const stack&);
    stack& operator= (const stack&);
    /// The wrapped container.
    S seq_;
  };

  /// Present a slice of the top of a stack.
  template <typename T, typename S = stack<T> >
  class slice
  {
  public:
    slice (const S& stack, int range)
      : stack_ (stack)
      , range_ (range)
    {}

    const T&
    operator[] (int i) const
    {
      return stack_[range_ - i];
    }

  private:
    const S& stack_;
    int range_;
  };



  /// A char[S] buffer to store and retrieve objects.
  ///
  /// Sort of a variant, but does not keep track of the nature
  /// of the stored data, since that knowledge is available
  /// via the current state.
  template <size_t S>
  struct variant
  {
    /// Type of *this.
    typedef variant<S> self_type;

    /// Empty construction.
    variant ()
      : yybuffer_ ()
      , yytypeid_ (YY_NULLPTR)
    {}

    /// Construct and fill.
    template <typename T>
    variant (YY_RVREF (T) t)
      : yytypeid_ (&typeid (T))
    {
      YYASSERT (sizeof (T) <= S);
      new (yyas_<T> ()) T (YY_MOVE (t));
    }

    /// Destruction, allowed only if empty.
    ~variant ()
    {
      YYASSERT (!yytypeid_);
    }

    /// Instantiate an empty \a T in here.
    template <typename T>
    T&
    emplace ()
    {
      YYASSERT (!yytypeid_);
      YYASSERT (sizeof (T) <= S);
      yytypeid_ = & typeid (T);
      return *new (yyas_<T> ()) T ();
    }

# if defined __cplusplus && 201103L <= __cplusplus
    /// Instantiate a \a T in here from \a t.
    template <typename T, typename U>
    T&
    emplace (U&& u)
    {
      YYASSERT (!yytypeid_);
      YYASSERT (sizeof (T) <= S);
      yytypeid_ = & typeid (T);
      return *new (yyas_<T> ()) T (std::forward <U>(u));
    }
# else
    /// Instantiate a \a T in here from \a t.
    template <typename T>
    T&
    emplace (const T& t)
    {
      YYASSERT (!yytypeid_);
      YYASSERT (sizeof (T) <= S);
      yytypeid_ = & typeid (T);
      return *new (yyas_<T> ()) T (t);
    }
# endif

    /// Instantiate an empty \a T in here.
    /// Obsolete, use emplace.
    template <typename T>
    T&
    build ()
    {
      return emplace<T> ();
    }

    /// Instantiate a \a T in here from \a t.
    /// Obsolete, use emplace.
    template <typename T>
    T&
    build (const T& t)
    {
      return emplace<T> (t);
    }

    /// Accessor to a built \a T.
    template <typename T>
    T&
    as ()
    {
      YYASSERT (yytypeid_);
      YYASSERT (*yytypeid_ == typeid (T));
      YYASSERT (sizeof (T) <= S);
      return *yyas_<T> ();
    }

    /// Const accessor to a built \a T (for %printer).
    template <typename T>
    const T&
    as () const
    {
      YYASSERT (yytypeid_);
      YYASSERT (*yytypeid_ == typeid (T));
      YYASSERT (sizeof (T) <= S);
      return *yyas_<T> ();
    }

    /// Swap the content with \a other, of same type.
    ///
    /// Both variants must be built beforehand, because swapping the actual
    /// data requires reading it (with as()), and this is not possible on
    /// unconstructed variants: it would require some dynamic testing, which
    /// should not be the variant's responsibility.
    /// Swapping between built and (possibly) non-built is done with
    /// variant::move ().
    template <typename T>
    void
    swap (self_type& other)
    {
      YYASSERT (yytypeid_);
      YYASSERT (*yytypeid_ == *other.yytypeid_);
      std::swap (as<T> (), other.as<T> ());
    }

    /// Move the content of \a other to this.
    ///
    /// Destroys \a other.
    template <typename T>
    void
    move (self_type& other)
    {
# if defined __cplusplus && 201103L <= __cplusplus
      emplace<T> (std::move (other.as<T> ()));
# else
      emplace<T> ();
      swap<T> (other);
# endif
      other.destroy<T> ();
    }

# if defined __cplusplus && 201103L <= __cplusplus
    /// Move the content of \a other to this.
    template <typename T>
    void
    move (self_type&& other)
    {
      emplace<T> (std::move (other.as<T> ()));
      other.destroy<T> ();
    }
#endif

    /// Copy the content of \a other to this.
    template <typename T>
    void
    copy (const self_type& other)
    {
      emplace<T> (other.as<T> ());
    }

    /// Destroy the stored \a T.
    template <typename T>
    void
    destroy ()
    {
      as<T> ().~T ();
      yytypeid_ = YY_NULLPTR;
    }

  private:
    /// Prohibit blind copies.
    self_type& operator= (const self_type&);
    variant (const self_type&);

    /// Accessor to raw memory as \a T.
    template <typename T>
    T*
    yyas_ ()
    {
      void *yyp = yybuffer_.yyraw;
      return static_cast<T*> (yyp);
     }

    /// Const accessor to raw memory as \a T.
    template <typename T>
    const T*
    yyas_ () const
    {
      const void *yyp = yybuffer_.yyraw;
      return static_cast<const T*> (yyp);
     }

    union
    {
      /// Strongest alignment constraints.
      long double yyalign_me;
      /// A buffer large enough to store any of the semantic values.
      char yyraw[S];
    } yybuffer_;

    /// Whether the content is built: if defined, the name of the stored type.
    const std::type_info *yytypeid_;
  };


  /// A Bison parser.
  class AgentParser
  {
  public:
#ifndef AGENT_STYPE
    /// An auxiliary type to compute the largest semantic type.
    union union_type
    {
      // value
      // map_value
      // socket_type_value
      char dummy1[sizeof (ElementPtr)];

      // "boolean"
      char dummy2[sizeof (bool)];

      // "floating point"
      char dummy3[sizeof (double)];

      // "integer"
      char dummy4[sizeof (int64_t)];

      // "constant string"
      char dummy5[sizeof (std::string)];
};

    /// Symbol semantic values.
    typedef variant<sizeof (union_type)> semantic_type;
#else
    typedef AGENT_STYPE semantic_type;
#endif
    /// Symbol locations.
    typedef location location_type;

    /// Syntax errors thrown from user actions.
    struct syntax_error : std::runtime_error
    {
      syntax_error (const location_type& l, const std::string& m);
      location_type location;
    };

    /// Tokens.
    struct token
    {
      enum yytokentype
      {
        TOKEN_END = 0,
        TOKEN_COMMA = 258,
        TOKEN_COLON = 259,
        TOKEN_LSQUARE_BRACKET = 260,
        TOKEN_RSQUARE_BRACKET = 261,
        TOKEN_LCURLY_BRACKET = 262,
        TOKEN_RCURLY_BRACKET = 263,
        TOKEN_NULL_TYPE = 264,
        TOKEN_CONTROL_AGENT = 265,
        TOKEN_HTTP_HOST = 266,
        TOKEN_HTTP_PORT = 267,
        TOKEN_USER_CONTEXT = 268,
        TOKEN_COMMENT = 269,
        TOKEN_CONTROL_SOCKETS = 270,
        TOKEN_DHCP4_SERVER = 271,
        TOKEN_DHCP6_SERVER = 272,
        TOKEN_D2_SERVER = 273,
        TOKEN_SOCKET_NAME = 274,
        TOKEN_SOCKET_TYPE = 275,
        TOKEN_UNIX = 276,
        TOKEN_HOOKS_LIBRARIES = 277,
        TOKEN_LIBRARY = 278,
        TOKEN_PARAMETERS = 279,
        TOKEN_LOGGING = 280,
        TOKEN_LOGGERS = 281,
        TOKEN_NAME = 282,
        TOKEN_OUTPUT_OPTIONS = 283,
        TOKEN_OUTPUT = 284,
        TOKEN_DEBUGLEVEL = 285,
        TOKEN_SEVERITY = 286,
        TOKEN_FLUSH = 287,
        TOKEN_MAXSIZE = 288,
        TOKEN_MAXVER = 289,
        TOKEN_DHCP4 = 290,
        TOKEN_DHCP6 = 291,
        TOKEN_DHCPDDNS = 292,
        TOKEN_START_JSON = 293,
        TOKEN_START_AGENT = 294,
        TOKEN_START_SUB_AGENT = 295,
        TOKEN_STRING = 296,
        TOKEN_INTEGER = 297,
        TOKEN_FLOAT = 298,
        TOKEN_BOOLEAN = 299
      };
    };

    /// (External) token type, as returned by yylex.
    typedef token::yytokentype token_type;

    /// Symbol type: an internal symbol number.
    typedef int symbol_number_type;

    /// The symbol type number to denote an empty symbol.
    enum { empty_symbol = -2 };

    /// Internal symbol number for tokens (subsumed by symbol_number_type).
    typedef unsigned char token_number_type;

    /// A complete symbol.
    ///
    /// Expects its Base type to provide access to the symbol type
    /// via type_get ().
    ///
    /// Provide access to semantic value and location.
    template <typename Base>
    struct basic_symbol : Base
    {
      /// Alias to Base.
      typedef Base super_type;

      /// Default constructor.
      basic_symbol ();

      /// Move or copy constructor.
      basic_symbol (YY_RVREF (basic_symbol) other);


      /// Constructor for valueless symbols, and symbols from each type.
      basic_symbol (typename Base::kind_type t, YY_RVREF (location_type) l);
      basic_symbol (typename Base::kind_type t, YY_RVREF (ElementPtr) v, YY_RVREF (location_type) l);
      basic_symbol (typename Base::kind_type t, YY_RVREF (bool) v, YY_RVREF (location_type) l);
      basic_symbol (typename Base::kind_type t, YY_RVREF (double) v, YY_RVREF (location_type) l);
      basic_symbol (typename Base::kind_type t, YY_RVREF (int64_t) v, YY_RVREF (location_type) l);
      basic_symbol (typename Base::kind_type t, YY_RVREF (std::string) v, YY_RVREF (location_type) l);


      /// Destroy the symbol.
      ~basic_symbol ();

      /// Destroy contents, and record that is empty.
      void clear ();

      /// Whether empty.
      bool empty () const;

      /// Destructive move, \a s is emptied into this.
      void move (basic_symbol& s);

      /// The semantic value.
      semantic_type value;

      /// The location.
      location_type location;

    private:
#if !defined __cplusplus || __cplusplus < 201103L
      /// Assignment operator.
      basic_symbol& operator= (const basic_symbol& other);
#endif
    };

    /// Type access provider for token (enum) based symbols.
    struct by_type
    {
      /// Default constructor.
      by_type ();

      /// Copy constructor.
      by_type (const by_type& other);

      /// The symbol type as needed by the constructor.
      typedef token_type kind_type;

      /// Constructor from (external) token numbers.
      by_type (kind_type t);

      /// Record that this symbol is empty.
      void clear ();

      /// Steal the symbol type from \a that.
      void move (by_type& that);

      /// The (internal) type number (corresponding to \a type).
      /// \a empty when empty.
      symbol_number_type type_get () const;

      /// The token.
      token_type token () const;

      /// The symbol type.
      /// \a empty_symbol when empty.
      /// An int, not token_number_type, to be able to store empty_symbol.
      int type;
    };

    /// "External" symbols: returned by the scanner.
    typedef basic_symbol<by_type> symbol_type;

    /// Build a parser object.
    AgentParser (isc::agent::ParserContext& ctx_yyarg);
    virtual ~AgentParser ();

    /// Parse.  An alias for parse ().
    /// \returns  0 iff parsing succeeded.
    int operator() ();

    /// Parse.
    /// \returns  0 iff parsing succeeded.
    virtual int parse ();

#if AGENT_DEBUG
    /// The current debugging stream.
    std::ostream& debug_stream () const YY_ATTRIBUTE_PURE;
    /// Set the current debugging stream.
    void set_debug_stream (std::ostream &);

    /// Type for debugging levels.
    typedef int debug_level_type;
    /// The current debugging level.
    debug_level_type debug_level () const YY_ATTRIBUTE_PURE;
    /// Set the current debugging level.
    void set_debug_level (debug_level_type l);
#endif

    /// Report a syntax error.
    /// \param loc    where the syntax error is found.
    /// \param msg    a description of the syntax error.
    virtual void error (const location_type& loc, const std::string& msg);

    /// Report a syntax error.
    void error (const syntax_error& err);

    // Symbol constructors declarations.
    static
    symbol_type
    make_END (YY_COPY (location_type) l);

    static
    symbol_type
    make_COMMA (YY_COPY (location_type) l);

    static
    symbol_type
    make_COLON (YY_COPY (location_type) l);

    static
    symbol_type
    make_LSQUARE_BRACKET (YY_COPY (location_type) l);

    static
    symbol_type
    make_RSQUARE_BRACKET (YY_COPY (location_type) l);

    static
    symbol_type
    make_LCURLY_BRACKET (YY_COPY (location_type) l);

    static
    symbol_type
    make_RCURLY_BRACKET (YY_COPY (location_type) l);

    static
    symbol_type
    make_NULL_TYPE (YY_COPY (location_type) l);

    static
    symbol_type
    make_CONTROL_AGENT (YY_COPY (location_type) l);

    static
    symbol_type
    make_HTTP_HOST (YY_COPY (location_type) l);

    static
    symbol_type
    make_HTTP_PORT (YY_COPY (location_type) l);

    static
    symbol_type
    make_USER_CONTEXT (YY_COPY (location_type) l);

    static
    symbol_type
    make_COMMENT (YY_COPY (location_type) l);

    static
    symbol_type
    make_CONTROL_SOCKETS (YY_COPY (location_type) l);

    static
    symbol_type
    make_DHCP4_SERVER (YY_COPY (location_type) l);

    static
    symbol_type
    make_DHCP6_SERVER (YY_COPY (location_type) l);

    static
    symbol_type
    make_D2_SERVER (YY_COPY (location_type) l);

    static
    symbol_type
    make_SOCKET_NAME (YY_COPY (location_type) l);

    static
    symbol_type
    make_SOCKET_TYPE (YY_COPY (location_type) l);

    static
    symbol_type
    make_UNIX (YY_COPY (location_type) l);

    static
    symbol_type
    make_HOOKS_LIBRARIES (YY_COPY (location_type) l);

    static
    symbol_type
    make_LIBRARY (YY_COPY (location_type) l);

    static
    symbol_type
    make_PARAMETERS (YY_COPY (location_type) l);

    static
    symbol_type
    make_LOGGING (YY_COPY (location_type) l);

    static
    symbol_type
    make_LOGGERS (YY_COPY (location_type) l);

    static
    symbol_type
    make_NAME (YY_COPY (location_type) l);

    static
    symbol_type
    make_OUTPUT_OPTIONS (YY_COPY (location_type) l);

    static
    symbol_type
    make_OUTPUT (YY_COPY (location_type) l);

    static
    symbol_type
    make_DEBUGLEVEL (YY_COPY (location_type) l);

    static
    symbol_type
    make_SEVERITY (YY_COPY (location_type) l);

    static
    symbol_type
    make_FLUSH (YY_COPY (location_type) l);

    static
    symbol_type
    make_MAXSIZE (YY_COPY (location_type) l);

    static
    symbol_type
    make_MAXVER (YY_COPY (location_type) l);

    static
    symbol_type
    make_DHCP4 (YY_COPY (location_type) l);

    static
    symbol_type
    make_DHCP6 (YY_COPY (location_type) l);

    static
    symbol_type
    make_DHCPDDNS (YY_COPY (location_type) l);

    static
    symbol_type
    make_START_JSON (YY_COPY (location_type) l);

    static
    symbol_type
    make_START_AGENT (YY_COPY (location_type) l);

    static
    symbol_type
    make_START_SUB_AGENT (YY_COPY (location_type) l);

    static
    symbol_type
    make_STRING (YY_COPY (std::string) v, YY_COPY (location_type) l);

    static
    symbol_type
    make_INTEGER (YY_COPY (int64_t) v, YY_COPY (location_type) l);

    static
    symbol_type
    make_FLOAT (YY_COPY (double) v, YY_COPY (location_type) l);

    static
    symbol_type
    make_BOOLEAN (YY_COPY (bool) v, YY_COPY (location_type) l);



  private:
    /// This class is not copyable.
    AgentParser (const AgentParser&);
    AgentParser& operator= (const AgentParser&);

    /// State numbers.
    typedef int state_type;

    /// Generate an error message.
    /// \param yystate   the state where the error occurred.
    /// \param yyla      the lookahead token.
    virtual std::string yysyntax_error_ (state_type yystate,
                                         const symbol_type& yyla) const;

    /// Compute post-reduction state.
    /// \param yystate   the current state
    /// \param yysym     the nonterminal to push on the stack
    state_type yy_lr_goto_state_ (state_type yystate, int yysym);

    /// Whether the given \c yypact_ value indicates a defaulted state.
    /// \param yyvalue   the value to check
    static bool yy_pact_value_is_default_ (int yyvalue);

    /// Whether the given \c yytable_ value indicates a syntax error.
    /// \param yyvalue   the value to check
    static bool yy_table_value_is_error_ (int yyvalue);

    static const signed char yypact_ninf_;
    static const signed char yytable_ninf_;

    /// Convert a scanner token number \a t to a symbol number.
    static token_number_type yytranslate_ (token_type t);

    // Tables.
  // YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
  // STATE-NUM.
  static const short yypact_[];

  // YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
  // Performed when YYTABLE does not specify something else to do.  Zero
  // means the default is an error.
  static const unsigned char yydefact_[];

  // YYPGOTO[NTERM-NUM].
  static const signed char yypgoto_[];

  // YYDEFGOTO[NTERM-NUM].
  static const short yydefgoto_[];

  // YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
  // positive, shift that token.  If negative, reduce the rule whose
  // number is the opposite.  If YYTABLE_NINF, syntax error.
  static const unsigned char yytable_[];

  static const short yycheck_[];

  // YYSTOS[STATE-NUM] -- The (internal number of the) accessing
  // symbol of state STATE-NUM.
  static const unsigned char yystos_[];

  // YYR1[YYN] -- Symbol number of symbol that rule YYN derives.
  static const unsigned char yyr1_[];

  // YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.
  static const unsigned char yyr2_[];


    /// Convert the symbol name \a n to a form suitable for a diagnostic.
    static std::string yytnamerr_ (const char *n);


    /// For a symbol, its name in clear.
    static const char* const yytname_[];
#if AGENT_DEBUG
  // YYRLINE[YYN] -- Source line where rule number YYN was defined.
  static const unsigned short yyrline_[];
    /// Report on the debug stream that the rule \a r is going to be reduced.
    virtual void yy_reduce_print_ (int r);
    /// Print the state stack on the debug stream.
    virtual void yystack_print_ ();

    /// Debugging level.
    int yydebug_;
    /// Debug stream.
    std::ostream* yycdebug_;

    /// \brief Display a symbol type, value and location.
    /// \param yyo    The output stream.
    /// \param yysym  The symbol.
    template <typename Base>
    void yy_print_ (std::ostream& yyo, const basic_symbol<Base>& yysym) const;
#endif

    /// \brief Reclaim the memory associated to a symbol.
    /// \param yymsg     Why this token is reclaimed.
    ///                  If null, print nothing.
    /// \param yysym     The symbol.
    template <typename Base>
    void yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const;

  private:
    /// Type access provider for state based symbols.
    struct by_state
    {
      /// Default constructor.
      by_state ();

      /// The symbol type as needed by the constructor.
      typedef state_type kind_type;

      /// Constructor.
      by_state (kind_type s);

      /// Copy constructor.
      by_state (const by_state& other);

      /// Record that this symbol is empty.
      void clear ();

      /// Steal the symbol type from \a that.
      void move (by_state& that);

      /// The (internal) type number (corresponding to \a state).
      /// \a empty_symbol when empty.
      symbol_number_type type_get () const;

      /// The state number used to denote an empty symbol.
      enum { empty_state = -1 };

      /// The state.
      /// \a empty when empty.
      state_type state;
    };

    /// "Internal" symbol: element of the stack.
    struct stack_symbol_type : basic_symbol<by_state>
    {
      /// Superclass.
      typedef basic_symbol<by_state> super_type;
      /// Construct an empty symbol.
      stack_symbol_type ();
      /// Move or copy construction.
      stack_symbol_type (YY_RVREF (stack_symbol_type) that);
      /// Steal the contents from \a sym to build this.
      stack_symbol_type (state_type s, YY_MOVE_REF (symbol_type) sym);
#if !defined __cplusplus || __cplusplus < 201103L
      /// Assignment, needed by push_back by some old implementations.
      /// Moves the contents of that.
      stack_symbol_type& operator= (stack_symbol_type& that);
#endif
    };

    /// Stack type.
    typedef stack<stack_symbol_type> stack_type;

    /// The stack.
    stack_type yystack_;

    /// Push a new state on the stack.
    /// \param m    a debug message to display
    ///             if null, no trace is output.
    /// \param sym  the symbol
    /// \warning the contents of \a s.value is stolen.
    void yypush_ (const char* m, YY_MOVE_REF (stack_symbol_type) sym);

    /// Push a new look ahead token on the state on the stack.
    /// \param m    a debug message to display
    ///             if null, no trace is output.
    /// \param s    the state
    /// \param sym  the symbol (for its value and location).
    /// \warning the contents of \a sym.value is stolen.
    void yypush_ (const char* m, state_type s, YY_MOVE_REF (symbol_type) sym);

    /// Pop \a n symbols from the stack.
    void yypop_ (int n = 1);

    /// Constants.
    enum
    {
      yyeof_ = 0,
      yylast_ = 190,     ///< Last index in yytable_.
      yynnts_ = 97,  ///< Number of nonterminal symbols.
      yyfinal_ = 8, ///< Termination state number.
      yyterror_ = 1,
      yyerrcode_ = 256,
      yyntokens_ = 45  ///< Number of tokens.
    };


    // User arguments.
    isc::agent::ParserContext& ctx;
  };

  // Symbol number corresponding to token number t.
  inline
  AgentParser::token_number_type
  AgentParser::yytranslate_ (token_type t)
  {
    static
    const token_number_type
    translate_table[] =
    {
     0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44
    };
    const unsigned user_token_number_max_ = 299;
    const token_number_type undef_token_ = 2;

    if (static_cast<int> (t) <= yyeof_)
      return yyeof_;
    else if (static_cast<unsigned> (t) <= user_token_number_max_)
      return translate_table[t];
    else
      return undef_token_;
  }

  inline
  AgentParser::syntax_error::syntax_error (const location_type& l, const std::string& m)
    : std::runtime_error (m)
    , location (l)
  {}

  // basic_symbol.
  template <typename Base>
  AgentParser::basic_symbol<Base>::basic_symbol ()
    : value ()
    , location ()
  {}

  template <typename Base>
  AgentParser::basic_symbol<Base>::basic_symbol (YY_RVREF (basic_symbol) other)
    : Base (YY_MOVE (other))
    , value ()
    , location (YY_MOVE (other.location))
  {
    switch (other.type_get ())
    {
      case 53: // value
      case 56: // map_value
      case 107: // socket_type_value
        value.YY_MOVE_OR_COPY< ElementPtr > (YY_MOVE (other.value));
        break;

      case 44: // "boolean"
        value.YY_MOVE_OR_COPY< bool > (YY_MOVE (other.value));
        break;

      case 43: // "floating point"
        value.YY_MOVE_OR_COPY< double > (YY_MOVE (other.value));
        break;

      case 42: // "integer"
        value.YY_MOVE_OR_COPY< int64_t > (YY_MOVE (other.value));
        break;

      case 41: // "constant string"
        value.YY_MOVE_OR_COPY< std::string > (YY_MOVE (other.value));
        break;

      default:
        break;
    }

  }


  // Implementation of basic_symbol constructor for each type.
  template <typename Base>
  AgentParser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, YY_RVREF (location_type) l)
    : Base (t)
    , location (YY_MOVE (l))
  {}

  template <typename Base>
  AgentParser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, YY_RVREF (ElementPtr) v, YY_RVREF (location_type) l)
    : Base (t)
    , value (YY_MOVE (v))
    , location (YY_MOVE (l))
  {}

  template <typename Base>
  AgentParser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, YY_RVREF (bool) v, YY_RVREF (location_type) l)
    : Base (t)
    , value (YY_MOVE (v))
    , location (YY_MOVE (l))
  {}

  template <typename Base>
  AgentParser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, YY_RVREF (double) v, YY_RVREF (location_type) l)
    : Base (t)
    , value (YY_MOVE (v))
    , location (YY_MOVE (l))
  {}

  template <typename Base>
  AgentParser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, YY_RVREF (int64_t) v, YY_RVREF (location_type) l)
    : Base (t)
    , value (YY_MOVE (v))
    , location (YY_MOVE (l))
  {}

  template <typename Base>
  AgentParser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, YY_RVREF (std::string) v, YY_RVREF (location_type) l)
    : Base (t)
    , value (YY_MOVE (v))
    , location (YY_MOVE (l))
  {}



  template <typename Base>
  AgentParser::basic_symbol<Base>::~basic_symbol ()
  {
    clear ();
  }

  template <typename Base>
  void
  AgentParser::basic_symbol<Base>::clear ()
  {
    // User destructor.
    symbol_number_type yytype = this->type_get ();
    basic_symbol<Base>& yysym = *this;
    (void) yysym;
    switch (yytype)
    {
   default:
      break;
    }

    // Type destructor.
  switch (yytype)
    {
      case 53: // value
      case 56: // map_value
      case 107: // socket_type_value
        value.template destroy< ElementPtr > ();
        break;

      case 44: // "boolean"
        value.template destroy< bool > ();
        break;

      case 43: // "floating point"
        value.template destroy< double > ();
        break;

      case 42: // "integer"
        value.template destroy< int64_t > ();
        break;

      case 41: // "constant string"
        value.template destroy< std::string > ();
        break;

      default:
        break;
    }

    Base::clear ();
  }

  template <typename Base>
  bool
  AgentParser::basic_symbol<Base>::empty () const
  {
    return Base::type_get () == empty_symbol;
  }

  template <typename Base>
  void
  AgentParser::basic_symbol<Base>::move (basic_symbol& s)
  {
    super_type::move (s);
    switch (this->type_get ())
    {
      case 53: // value
      case 56: // map_value
      case 107: // socket_type_value
        value.move< ElementPtr > (YY_MOVE (s.value));
        break;

      case 44: // "boolean"
        value.move< bool > (YY_MOVE (s.value));
        break;

      case 43: // "floating point"
        value.move< double > (YY_MOVE (s.value));
        break;

      case 42: // "integer"
        value.move< int64_t > (YY_MOVE (s.value));
        break;

      case 41: // "constant string"
        value.move< std::string > (YY_MOVE (s.value));
        break;

      default:
        break;
    }

    location = YY_MOVE (s.location);
  }

  // by_type.
  inline
  AgentParser::by_type::by_type ()
    : type (empty_symbol)
  {}

  inline
  AgentParser::by_type::by_type (const by_type& other)
    : type (other.type)
  {}

  inline
  AgentParser::by_type::by_type (token_type t)
    : type (yytranslate_ (t))
  {}

  inline
  void
  AgentParser::by_type::clear ()
  {
    type = empty_symbol;
  }

  inline
  void
  AgentParser::by_type::move (by_type& that)
  {
    type = that.type;
    that.clear ();
  }

  inline
  int
  AgentParser::by_type::type_get () const
  {
    return type;
  }

  inline
  AgentParser::token_type
  AgentParser::by_type::token () const
  {
    // YYTOKNUM[NUM] -- (External) token number corresponding to the
    // (internal) symbol number NUM (which must be that of a token).  */
    static
    const unsigned short
    yytoken_number_[] =
    {
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299
    };
    return static_cast<token_type> (yytoken_number_[type]);
  }

  // Implementation of make_symbol for each symbol type.
  inline
  AgentParser::symbol_type
  AgentParser::make_END (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_END, YY_MOVE (l));
  }

  inline
  AgentParser::symbol_type
  AgentParser::make_COMMA (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_COMMA, YY_MOVE (l));
  }

  inline
  AgentParser::symbol_type
  AgentParser::make_COLON (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_COLON, YY_MOVE (l));
  }

  inline
  AgentParser::symbol_type
  AgentParser::make_LSQUARE_BRACKET (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_LSQUARE_BRACKET, YY_MOVE (l));
  }

  inline
  AgentParser::symbol_type
  AgentParser::make_RSQUARE_BRACKET (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_RSQUARE_BRACKET, YY_MOVE (l));
  }

  inline
  AgentParser::symbol_type
  AgentParser::make_LCURLY_BRACKET (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_LCURLY_BRACKET, YY_MOVE (l));
  }

  inline
  AgentParser::symbol_type
  AgentParser::make_RCURLY_BRACKET (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_RCURLY_BRACKET, YY_MOVE (l));
  }

  inline
  AgentParser::symbol_type
  AgentParser::make_NULL_TYPE (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_NULL_TYPE, YY_MOVE (l));
  }

  inline
  AgentParser::symbol_type
  AgentParser::make_CONTROL_AGENT (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_CONTROL_AGENT, YY_MOVE (l));
  }

  inline
  AgentParser::symbol_type
  AgentParser::make_HTTP_HOST (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_HTTP_HOST, YY_MOVE (l));
  }

  inline
  AgentParser::symbol_type
  AgentParser::make_HTTP_PORT (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_HTTP_PORT, YY_MOVE (l));
  }

  inline
  AgentParser::symbol_type
  AgentParser::make_USER_CONTEXT (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_USER_CONTEXT, YY_MOVE (l));
  }

  inline
  AgentParser::symbol_type
  AgentParser::make_COMMENT (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_COMMENT, YY_MOVE (l));
  }

  inline
  AgentParser::symbol_type
  AgentParser::make_CONTROL_SOCKETS (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_CONTROL_SOCKETS, YY_MOVE (l));
  }

  inline
  AgentParser::symbol_type
  AgentParser::make_DHCP4_SERVER (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_DHCP4_SERVER, YY_MOVE (l));
  }

  inline
  AgentParser::symbol_type
  AgentParser::make_DHCP6_SERVER (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_DHCP6_SERVER, YY_MOVE (l));
  }

  inline
  AgentParser::symbol_type
  AgentParser::make_D2_SERVER (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_D2_SERVER, YY_MOVE (l));
  }

  inline
  AgentParser::symbol_type
  AgentParser::make_SOCKET_NAME (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_SOCKET_NAME, YY_MOVE (l));
  }

  inline
  AgentParser::symbol_type
  AgentParser::make_SOCKET_TYPE (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_SOCKET_TYPE, YY_MOVE (l));
  }

  inline
  AgentParser::symbol_type
  AgentParser::make_UNIX (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_UNIX, YY_MOVE (l));
  }

  inline
  AgentParser::symbol_type
  AgentParser::make_HOOKS_LIBRARIES (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_HOOKS_LIBRARIES, YY_MOVE (l));
  }

  inline
  AgentParser::symbol_type
  AgentParser::make_LIBRARY (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_LIBRARY, YY_MOVE (l));
  }

  inline
  AgentParser::symbol_type
  AgentParser::make_PARAMETERS (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_PARAMETERS, YY_MOVE (l));
  }

  inline
  AgentParser::symbol_type
  AgentParser::make_LOGGING (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_LOGGING, YY_MOVE (l));
  }

  inline
  AgentParser::symbol_type
  AgentParser::make_LOGGERS (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_LOGGERS, YY_MOVE (l));
  }

  inline
  AgentParser::symbol_type
  AgentParser::make_NAME (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_NAME, YY_MOVE (l));
  }

  inline
  AgentParser::symbol_type
  AgentParser::make_OUTPUT_OPTIONS (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_OUTPUT_OPTIONS, YY_MOVE (l));
  }

  inline
  AgentParser::symbol_type
  AgentParser::make_OUTPUT (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_OUTPUT, YY_MOVE (l));
  }

  inline
  AgentParser::symbol_type
  AgentParser::make_DEBUGLEVEL (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_DEBUGLEVEL, YY_MOVE (l));
  }

  inline
  AgentParser::symbol_type
  AgentParser::make_SEVERITY (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_SEVERITY, YY_MOVE (l));
  }

  inline
  AgentParser::symbol_type
  AgentParser::make_FLUSH (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_FLUSH, YY_MOVE (l));
  }

  inline
  AgentParser::symbol_type
  AgentParser::make_MAXSIZE (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_MAXSIZE, YY_MOVE (l));
  }

  inline
  AgentParser::symbol_type
  AgentParser::make_MAXVER (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_MAXVER, YY_MOVE (l));
  }

  inline
  AgentParser::symbol_type
  AgentParser::make_DHCP4 (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_DHCP4, YY_MOVE (l));
  }

  inline
  AgentParser::symbol_type
  AgentParser::make_DHCP6 (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_DHCP6, YY_MOVE (l));
  }

  inline
  AgentParser::symbol_type
  AgentParser::make_DHCPDDNS (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_DHCPDDNS, YY_MOVE (l));
  }

  inline
  AgentParser::symbol_type
  AgentParser::make_START_JSON (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_START_JSON, YY_MOVE (l));
  }

  inline
  AgentParser::symbol_type
  AgentParser::make_START_AGENT (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_START_AGENT, YY_MOVE (l));
  }

  inline
  AgentParser::symbol_type
  AgentParser::make_START_SUB_AGENT (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_START_SUB_AGENT, YY_MOVE (l));
  }

  inline
  AgentParser::symbol_type
  AgentParser::make_STRING (YY_COPY (std::string) v, YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_STRING, YY_MOVE (v), YY_MOVE (l));
  }

  inline
  AgentParser::symbol_type
  AgentParser::make_INTEGER (YY_COPY (int64_t) v, YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_INTEGER, YY_MOVE (v), YY_MOVE (l));
  }

  inline
  AgentParser::symbol_type
  AgentParser::make_FLOAT (YY_COPY (double) v, YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_FLOAT, YY_MOVE (v), YY_MOVE (l));
  }

  inline
  AgentParser::symbol_type
  AgentParser::make_BOOLEAN (YY_COPY (bool) v, YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_BOOLEAN, YY_MOVE (v), YY_MOVE (l));
  }


#line 14 "agent_parser.yy" // lalr1.cc:404
} } // isc::agent
#line 1686 "agent_parser.h" // lalr1.cc:404




#endif // !YY_AGENT_AGENT_PARSER_H_INCLUDED
