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
 ** \file parser.h
 ** Define the isc::eval::parser class.
 */

// C++ LALR(1) parser skeleton written by Akim Demaille.

// Undocumented macros, especially those whose name start with YY_,
// are private implementation details.  Do not rely on them.

#ifndef YY_EVAL_PARSER_H_INCLUDED
# define YY_EVAL_PARSER_H_INCLUDED
// //                    "%code requires" blocks.
#line 17 "parser.yy" // lalr1.cc:404

#include <string>
#include <eval/token.h>
#include <eval/eval_context_decl.h>
#include <dhcp/option.h>
#include <boost/lexical_cast.hpp>

using namespace isc::dhcp;
using namespace isc::eval;

#line 59 "parser.h" // lalr1.cc:404

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
#ifndef EVALDEBUG
# if defined YYDEBUG
#if YYDEBUG
#   define EVALDEBUG 1
#  else
#   define EVALDEBUG 0
#  endif
# else /* ! defined YYDEBUG */
#  define EVALDEBUG 1
# endif /* ! defined YYDEBUG */
#endif  /* ! defined EVALDEBUG */

#line 14 "parser.yy" // lalr1.cc:404
namespace isc { namespace eval {
#line 161 "parser.h" // lalr1.cc:404

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
  class EvalParser
  {
  public:
#ifndef EVALSTYPE
    /// An auxiliary type to compute the largest semantic type.
    union union_type
    {
      // option_repr_type
      char dummy1[sizeof (TokenOption::RepresentationType)];

      // pkt4_field
      char dummy2[sizeof (TokenPkt4::FieldType)];

      // pkt6_field
      char dummy3[sizeof (TokenPkt6::FieldType)];

      // pkt_metadata
      char dummy4[sizeof (TokenPkt::MetadataType)];

      // relay6_field
      char dummy5[sizeof (TokenRelay6Field::FieldType)];

      // nest_level
      char dummy6[sizeof (int8_t)];

      // "constant string"
      // "integer"
      // "constant hexstring"
      // "option name"
      // "ip address"
      char dummy7[sizeof (std::string)];

      // option_code
      char dummy8[sizeof (uint16_t)];

      // integer_expr
      // enterprise_id
      char dummy9[sizeof (uint32_t)];
};

    /// Symbol semantic values.
    typedef variant<sizeof (union_type)> semantic_type;
#else
    typedef EVALSTYPE semantic_type;
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
        TOKEN_LPAREN = 258,
        TOKEN_RPAREN = 259,
        TOKEN_NOT = 260,
        TOKEN_AND = 261,
        TOKEN_OR = 262,
        TOKEN_EQUAL = 263,
        TOKEN_OPTION = 264,
        TOKEN_RELAY4 = 265,
        TOKEN_RELAY6 = 266,
        TOKEN_MEMBER = 267,
        TOKEN_PEERADDR = 268,
        TOKEN_LINKADDR = 269,
        TOKEN_LBRACKET = 270,
        TOKEN_RBRACKET = 271,
        TOKEN_DOT = 272,
        TOKEN_TEXT = 273,
        TOKEN_HEX = 274,
        TOKEN_EXISTS = 275,
        TOKEN_PKT = 276,
        TOKEN_IFACE = 277,
        TOKEN_SRC = 278,
        TOKEN_DST = 279,
        TOKEN_LEN = 280,
        TOKEN_PKT4 = 281,
        TOKEN_CHADDR = 282,
        TOKEN_HLEN = 283,
        TOKEN_HTYPE = 284,
        TOKEN_CIADDR = 285,
        TOKEN_GIADDR = 286,
        TOKEN_YIADDR = 287,
        TOKEN_SIADDR = 288,
        TOKEN_SUBSTRING = 289,
        TOKEN_ALL = 290,
        TOKEN_COMA = 291,
        TOKEN_CONCAT = 292,
        TOKEN_IFELSE = 293,
        TOKEN_TOHEXSTRING = 294,
        TOKEN_PKT6 = 295,
        TOKEN_MSGTYPE = 296,
        TOKEN_TRANSID = 297,
        TOKEN_VENDOR_CLASS = 298,
        TOKEN_VENDOR = 299,
        TOKEN_ANY = 300,
        TOKEN_DATA = 301,
        TOKEN_ENTERPRISE = 302,
        TOKEN_TOPLEVEL_BOOL = 303,
        TOKEN_TOPLEVEL_STRING = 304,
        TOKEN_STRING = 305,
        TOKEN_INTEGER = 306,
        TOKEN_HEXSTRING = 307,
        TOKEN_OPTION_NAME = 308,
        TOKEN_IP_ADDRESS = 309
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
      basic_symbol (typename Base::kind_type t, YY_RVREF (TokenOption::RepresentationType) v, YY_RVREF (location_type) l);
      basic_symbol (typename Base::kind_type t, YY_RVREF (TokenPkt4::FieldType) v, YY_RVREF (location_type) l);
      basic_symbol (typename Base::kind_type t, YY_RVREF (TokenPkt6::FieldType) v, YY_RVREF (location_type) l);
      basic_symbol (typename Base::kind_type t, YY_RVREF (TokenPkt::MetadataType) v, YY_RVREF (location_type) l);
      basic_symbol (typename Base::kind_type t, YY_RVREF (TokenRelay6Field::FieldType) v, YY_RVREF (location_type) l);
      basic_symbol (typename Base::kind_type t, YY_RVREF (int8_t) v, YY_RVREF (location_type) l);
      basic_symbol (typename Base::kind_type t, YY_RVREF (std::string) v, YY_RVREF (location_type) l);
      basic_symbol (typename Base::kind_type t, YY_RVREF (uint16_t) v, YY_RVREF (location_type) l);
      basic_symbol (typename Base::kind_type t, YY_RVREF (uint32_t) v, YY_RVREF (location_type) l);


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
    EvalParser (EvalContext& ctx_yyarg);
    virtual ~EvalParser ();

    /// Parse.  An alias for parse ().
    /// \returns  0 iff parsing succeeded.
    int operator() ();

    /// Parse.
    /// \returns  0 iff parsing succeeded.
    virtual int parse ();

#if EVALDEBUG
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
    make_LPAREN (YY_COPY (location_type) l);

    static
    symbol_type
    make_RPAREN (YY_COPY (location_type) l);

    static
    symbol_type
    make_NOT (YY_COPY (location_type) l);

    static
    symbol_type
    make_AND (YY_COPY (location_type) l);

    static
    symbol_type
    make_OR (YY_COPY (location_type) l);

    static
    symbol_type
    make_EQUAL (YY_COPY (location_type) l);

    static
    symbol_type
    make_OPTION (YY_COPY (location_type) l);

    static
    symbol_type
    make_RELAY4 (YY_COPY (location_type) l);

    static
    symbol_type
    make_RELAY6 (YY_COPY (location_type) l);

    static
    symbol_type
    make_MEMBER (YY_COPY (location_type) l);

    static
    symbol_type
    make_PEERADDR (YY_COPY (location_type) l);

    static
    symbol_type
    make_LINKADDR (YY_COPY (location_type) l);

    static
    symbol_type
    make_LBRACKET (YY_COPY (location_type) l);

    static
    symbol_type
    make_RBRACKET (YY_COPY (location_type) l);

    static
    symbol_type
    make_DOT (YY_COPY (location_type) l);

    static
    symbol_type
    make_TEXT (YY_COPY (location_type) l);

    static
    symbol_type
    make_HEX (YY_COPY (location_type) l);

    static
    symbol_type
    make_EXISTS (YY_COPY (location_type) l);

    static
    symbol_type
    make_PKT (YY_COPY (location_type) l);

    static
    symbol_type
    make_IFACE (YY_COPY (location_type) l);

    static
    symbol_type
    make_SRC (YY_COPY (location_type) l);

    static
    symbol_type
    make_DST (YY_COPY (location_type) l);

    static
    symbol_type
    make_LEN (YY_COPY (location_type) l);

    static
    symbol_type
    make_PKT4 (YY_COPY (location_type) l);

    static
    symbol_type
    make_CHADDR (YY_COPY (location_type) l);

    static
    symbol_type
    make_HLEN (YY_COPY (location_type) l);

    static
    symbol_type
    make_HTYPE (YY_COPY (location_type) l);

    static
    symbol_type
    make_CIADDR (YY_COPY (location_type) l);

    static
    symbol_type
    make_GIADDR (YY_COPY (location_type) l);

    static
    symbol_type
    make_YIADDR (YY_COPY (location_type) l);

    static
    symbol_type
    make_SIADDR (YY_COPY (location_type) l);

    static
    symbol_type
    make_SUBSTRING (YY_COPY (location_type) l);

    static
    symbol_type
    make_ALL (YY_COPY (location_type) l);

    static
    symbol_type
    make_COMA (YY_COPY (location_type) l);

    static
    symbol_type
    make_CONCAT (YY_COPY (location_type) l);

    static
    symbol_type
    make_IFELSE (YY_COPY (location_type) l);

    static
    symbol_type
    make_TOHEXSTRING (YY_COPY (location_type) l);

    static
    symbol_type
    make_PKT6 (YY_COPY (location_type) l);

    static
    symbol_type
    make_MSGTYPE (YY_COPY (location_type) l);

    static
    symbol_type
    make_TRANSID (YY_COPY (location_type) l);

    static
    symbol_type
    make_VENDOR_CLASS (YY_COPY (location_type) l);

    static
    symbol_type
    make_VENDOR (YY_COPY (location_type) l);

    static
    symbol_type
    make_ANY (YY_COPY (location_type) l);

    static
    symbol_type
    make_DATA (YY_COPY (location_type) l);

    static
    symbol_type
    make_ENTERPRISE (YY_COPY (location_type) l);

    static
    symbol_type
    make_TOPLEVEL_BOOL (YY_COPY (location_type) l);

    static
    symbol_type
    make_TOPLEVEL_STRING (YY_COPY (location_type) l);

    static
    symbol_type
    make_STRING (YY_COPY (std::string) v, YY_COPY (location_type) l);

    static
    symbol_type
    make_INTEGER (YY_COPY (std::string) v, YY_COPY (location_type) l);

    static
    symbol_type
    make_HEXSTRING (YY_COPY (std::string) v, YY_COPY (location_type) l);

    static
    symbol_type
    make_OPTION_NAME (YY_COPY (std::string) v, YY_COPY (location_type) l);

    static
    symbol_type
    make_IP_ADDRESS (YY_COPY (std::string) v, YY_COPY (location_type) l);



  private:
    /// This class is not copyable.
    EvalParser (const EvalParser&);
    EvalParser& operator= (const EvalParser&);

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
  static const short yypgoto_[];

  // YYDEFGOTO[NTERM-NUM].
  static const short yydefgoto_[];

  // YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
  // positive, shift that token.  If negative, reduce the rule whose
  // number is the opposite.  If YYTABLE_NINF, syntax error.
  static const unsigned char yytable_[];

  static const unsigned char yycheck_[];

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
#if EVALDEBUG
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
      yylast_ = 197,     ///< Last index in yytable_.
      yynnts_ = 16,  ///< Number of nonterminal symbols.
      yyfinal_ = 33, ///< Termination state number.
      yyterror_ = 1,
      yyerrcode_ = 256,
      yyntokens_ = 55  ///< Number of tokens.
    };


    // User arguments.
    EvalContext& ctx;
  };

  // Symbol number corresponding to token number t.
  inline
  EvalParser::token_number_type
  EvalParser::yytranslate_ (token_type t)
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
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54
    };
    const unsigned user_token_number_max_ = 309;
    const token_number_type undef_token_ = 2;

    if (static_cast<int> (t) <= yyeof_)
      return yyeof_;
    else if (static_cast<unsigned> (t) <= user_token_number_max_)
      return translate_table[t];
    else
      return undef_token_;
  }

  inline
  EvalParser::syntax_error::syntax_error (const location_type& l, const std::string& m)
    : std::runtime_error (m)
    , location (l)
  {}

  // basic_symbol.
  template <typename Base>
  EvalParser::basic_symbol<Base>::basic_symbol ()
    : value ()
    , location ()
  {}

  template <typename Base>
  EvalParser::basic_symbol<Base>::basic_symbol (YY_RVREF (basic_symbol) other)
    : Base (YY_MOVE (other))
    , value ()
    , location (YY_MOVE (other.location))
  {
    switch (other.type_get ())
    {
      case 62: // option_repr_type
        value.YY_MOVE_OR_COPY< TokenOption::RepresentationType > (YY_MOVE (other.value));
        break;

      case 66: // pkt4_field
        value.YY_MOVE_OR_COPY< TokenPkt4::FieldType > (YY_MOVE (other.value));
        break;

      case 67: // pkt6_field
        value.YY_MOVE_OR_COPY< TokenPkt6::FieldType > (YY_MOVE (other.value));
        break;

      case 64: // pkt_metadata
        value.YY_MOVE_OR_COPY< TokenPkt::MetadataType > (YY_MOVE (other.value));
        break;

      case 68: // relay6_field
        value.YY_MOVE_OR_COPY< TokenRelay6Field::FieldType > (YY_MOVE (other.value));
        break;

      case 63: // nest_level
        value.YY_MOVE_OR_COPY< int8_t > (YY_MOVE (other.value));
        break;

      case 50: // "constant string"
      case 51: // "integer"
      case 52: // "constant hexstring"
      case 53: // "option name"
      case 54: // "ip address"
        value.YY_MOVE_OR_COPY< std::string > (YY_MOVE (other.value));
        break;

      case 61: // option_code
        value.YY_MOVE_OR_COPY< uint16_t > (YY_MOVE (other.value));
        break;

      case 60: // integer_expr
      case 65: // enterprise_id
        value.YY_MOVE_OR_COPY< uint32_t > (YY_MOVE (other.value));
        break;

      default:
        break;
    }

  }


  // Implementation of basic_symbol constructor for each type.
  template <typename Base>
  EvalParser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, YY_RVREF (location_type) l)
    : Base (t)
    , location (YY_MOVE (l))
  {}

  template <typename Base>
  EvalParser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, YY_RVREF (TokenOption::RepresentationType) v, YY_RVREF (location_type) l)
    : Base (t)
    , value (YY_MOVE (v))
    , location (YY_MOVE (l))
  {}

  template <typename Base>
  EvalParser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, YY_RVREF (TokenPkt4::FieldType) v, YY_RVREF (location_type) l)
    : Base (t)
    , value (YY_MOVE (v))
    , location (YY_MOVE (l))
  {}

  template <typename Base>
  EvalParser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, YY_RVREF (TokenPkt6::FieldType) v, YY_RVREF (location_type) l)
    : Base (t)
    , value (YY_MOVE (v))
    , location (YY_MOVE (l))
  {}

  template <typename Base>
  EvalParser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, YY_RVREF (TokenPkt::MetadataType) v, YY_RVREF (location_type) l)
    : Base (t)
    , value (YY_MOVE (v))
    , location (YY_MOVE (l))
  {}

  template <typename Base>
  EvalParser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, YY_RVREF (TokenRelay6Field::FieldType) v, YY_RVREF (location_type) l)
    : Base (t)
    , value (YY_MOVE (v))
    , location (YY_MOVE (l))
  {}

  template <typename Base>
  EvalParser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, YY_RVREF (int8_t) v, YY_RVREF (location_type) l)
    : Base (t)
    , value (YY_MOVE (v))
    , location (YY_MOVE (l))
  {}

  template <typename Base>
  EvalParser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, YY_RVREF (std::string) v, YY_RVREF (location_type) l)
    : Base (t)
    , value (YY_MOVE (v))
    , location (YY_MOVE (l))
  {}

  template <typename Base>
  EvalParser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, YY_RVREF (uint16_t) v, YY_RVREF (location_type) l)
    : Base (t)
    , value (YY_MOVE (v))
    , location (YY_MOVE (l))
  {}

  template <typename Base>
  EvalParser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, YY_RVREF (uint32_t) v, YY_RVREF (location_type) l)
    : Base (t)
    , value (YY_MOVE (v))
    , location (YY_MOVE (l))
  {}



  template <typename Base>
  EvalParser::basic_symbol<Base>::~basic_symbol ()
  {
    clear ();
  }

  template <typename Base>
  void
  EvalParser::basic_symbol<Base>::clear ()
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
      case 62: // option_repr_type
        value.template destroy< TokenOption::RepresentationType > ();
        break;

      case 66: // pkt4_field
        value.template destroy< TokenPkt4::FieldType > ();
        break;

      case 67: // pkt6_field
        value.template destroy< TokenPkt6::FieldType > ();
        break;

      case 64: // pkt_metadata
        value.template destroy< TokenPkt::MetadataType > ();
        break;

      case 68: // relay6_field
        value.template destroy< TokenRelay6Field::FieldType > ();
        break;

      case 63: // nest_level
        value.template destroy< int8_t > ();
        break;

      case 50: // "constant string"
      case 51: // "integer"
      case 52: // "constant hexstring"
      case 53: // "option name"
      case 54: // "ip address"
        value.template destroy< std::string > ();
        break;

      case 61: // option_code
        value.template destroy< uint16_t > ();
        break;

      case 60: // integer_expr
      case 65: // enterprise_id
        value.template destroy< uint32_t > ();
        break;

      default:
        break;
    }

    Base::clear ();
  }

  template <typename Base>
  bool
  EvalParser::basic_symbol<Base>::empty () const
  {
    return Base::type_get () == empty_symbol;
  }

  template <typename Base>
  void
  EvalParser::basic_symbol<Base>::move (basic_symbol& s)
  {
    super_type::move (s);
    switch (this->type_get ())
    {
      case 62: // option_repr_type
        value.move< TokenOption::RepresentationType > (YY_MOVE (s.value));
        break;

      case 66: // pkt4_field
        value.move< TokenPkt4::FieldType > (YY_MOVE (s.value));
        break;

      case 67: // pkt6_field
        value.move< TokenPkt6::FieldType > (YY_MOVE (s.value));
        break;

      case 64: // pkt_metadata
        value.move< TokenPkt::MetadataType > (YY_MOVE (s.value));
        break;

      case 68: // relay6_field
        value.move< TokenRelay6Field::FieldType > (YY_MOVE (s.value));
        break;

      case 63: // nest_level
        value.move< int8_t > (YY_MOVE (s.value));
        break;

      case 50: // "constant string"
      case 51: // "integer"
      case 52: // "constant hexstring"
      case 53: // "option name"
      case 54: // "ip address"
        value.move< std::string > (YY_MOVE (s.value));
        break;

      case 61: // option_code
        value.move< uint16_t > (YY_MOVE (s.value));
        break;

      case 60: // integer_expr
      case 65: // enterprise_id
        value.move< uint32_t > (YY_MOVE (s.value));
        break;

      default:
        break;
    }

    location = YY_MOVE (s.location);
  }

  // by_type.
  inline
  EvalParser::by_type::by_type ()
    : type (empty_symbol)
  {}

  inline
  EvalParser::by_type::by_type (const by_type& other)
    : type (other.type)
  {}

  inline
  EvalParser::by_type::by_type (token_type t)
    : type (yytranslate_ (t))
  {}

  inline
  void
  EvalParser::by_type::clear ()
  {
    type = empty_symbol;
  }

  inline
  void
  EvalParser::by_type::move (by_type& that)
  {
    type = that.type;
    that.clear ();
  }

  inline
  int
  EvalParser::by_type::type_get () const
  {
    return type;
  }

  inline
  EvalParser::token_type
  EvalParser::by_type::token () const
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
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309
    };
    return static_cast<token_type> (yytoken_number_[type]);
  }

  // Implementation of make_symbol for each symbol type.
  inline
  EvalParser::symbol_type
  EvalParser::make_END (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_END, YY_MOVE (l));
  }

  inline
  EvalParser::symbol_type
  EvalParser::make_LPAREN (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_LPAREN, YY_MOVE (l));
  }

  inline
  EvalParser::symbol_type
  EvalParser::make_RPAREN (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_RPAREN, YY_MOVE (l));
  }

  inline
  EvalParser::symbol_type
  EvalParser::make_NOT (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_NOT, YY_MOVE (l));
  }

  inline
  EvalParser::symbol_type
  EvalParser::make_AND (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_AND, YY_MOVE (l));
  }

  inline
  EvalParser::symbol_type
  EvalParser::make_OR (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_OR, YY_MOVE (l));
  }

  inline
  EvalParser::symbol_type
  EvalParser::make_EQUAL (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_EQUAL, YY_MOVE (l));
  }

  inline
  EvalParser::symbol_type
  EvalParser::make_OPTION (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_OPTION, YY_MOVE (l));
  }

  inline
  EvalParser::symbol_type
  EvalParser::make_RELAY4 (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_RELAY4, YY_MOVE (l));
  }

  inline
  EvalParser::symbol_type
  EvalParser::make_RELAY6 (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_RELAY6, YY_MOVE (l));
  }

  inline
  EvalParser::symbol_type
  EvalParser::make_MEMBER (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_MEMBER, YY_MOVE (l));
  }

  inline
  EvalParser::symbol_type
  EvalParser::make_PEERADDR (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_PEERADDR, YY_MOVE (l));
  }

  inline
  EvalParser::symbol_type
  EvalParser::make_LINKADDR (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_LINKADDR, YY_MOVE (l));
  }

  inline
  EvalParser::symbol_type
  EvalParser::make_LBRACKET (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_LBRACKET, YY_MOVE (l));
  }

  inline
  EvalParser::symbol_type
  EvalParser::make_RBRACKET (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_RBRACKET, YY_MOVE (l));
  }

  inline
  EvalParser::symbol_type
  EvalParser::make_DOT (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_DOT, YY_MOVE (l));
  }

  inline
  EvalParser::symbol_type
  EvalParser::make_TEXT (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_TEXT, YY_MOVE (l));
  }

  inline
  EvalParser::symbol_type
  EvalParser::make_HEX (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_HEX, YY_MOVE (l));
  }

  inline
  EvalParser::symbol_type
  EvalParser::make_EXISTS (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_EXISTS, YY_MOVE (l));
  }

  inline
  EvalParser::symbol_type
  EvalParser::make_PKT (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_PKT, YY_MOVE (l));
  }

  inline
  EvalParser::symbol_type
  EvalParser::make_IFACE (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_IFACE, YY_MOVE (l));
  }

  inline
  EvalParser::symbol_type
  EvalParser::make_SRC (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_SRC, YY_MOVE (l));
  }

  inline
  EvalParser::symbol_type
  EvalParser::make_DST (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_DST, YY_MOVE (l));
  }

  inline
  EvalParser::symbol_type
  EvalParser::make_LEN (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_LEN, YY_MOVE (l));
  }

  inline
  EvalParser::symbol_type
  EvalParser::make_PKT4 (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_PKT4, YY_MOVE (l));
  }

  inline
  EvalParser::symbol_type
  EvalParser::make_CHADDR (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_CHADDR, YY_MOVE (l));
  }

  inline
  EvalParser::symbol_type
  EvalParser::make_HLEN (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_HLEN, YY_MOVE (l));
  }

  inline
  EvalParser::symbol_type
  EvalParser::make_HTYPE (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_HTYPE, YY_MOVE (l));
  }

  inline
  EvalParser::symbol_type
  EvalParser::make_CIADDR (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_CIADDR, YY_MOVE (l));
  }

  inline
  EvalParser::symbol_type
  EvalParser::make_GIADDR (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_GIADDR, YY_MOVE (l));
  }

  inline
  EvalParser::symbol_type
  EvalParser::make_YIADDR (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_YIADDR, YY_MOVE (l));
  }

  inline
  EvalParser::symbol_type
  EvalParser::make_SIADDR (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_SIADDR, YY_MOVE (l));
  }

  inline
  EvalParser::symbol_type
  EvalParser::make_SUBSTRING (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_SUBSTRING, YY_MOVE (l));
  }

  inline
  EvalParser::symbol_type
  EvalParser::make_ALL (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_ALL, YY_MOVE (l));
  }

  inline
  EvalParser::symbol_type
  EvalParser::make_COMA (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_COMA, YY_MOVE (l));
  }

  inline
  EvalParser::symbol_type
  EvalParser::make_CONCAT (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_CONCAT, YY_MOVE (l));
  }

  inline
  EvalParser::symbol_type
  EvalParser::make_IFELSE (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_IFELSE, YY_MOVE (l));
  }

  inline
  EvalParser::symbol_type
  EvalParser::make_TOHEXSTRING (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_TOHEXSTRING, YY_MOVE (l));
  }

  inline
  EvalParser::symbol_type
  EvalParser::make_PKT6 (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_PKT6, YY_MOVE (l));
  }

  inline
  EvalParser::symbol_type
  EvalParser::make_MSGTYPE (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_MSGTYPE, YY_MOVE (l));
  }

  inline
  EvalParser::symbol_type
  EvalParser::make_TRANSID (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_TRANSID, YY_MOVE (l));
  }

  inline
  EvalParser::symbol_type
  EvalParser::make_VENDOR_CLASS (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_VENDOR_CLASS, YY_MOVE (l));
  }

  inline
  EvalParser::symbol_type
  EvalParser::make_VENDOR (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_VENDOR, YY_MOVE (l));
  }

  inline
  EvalParser::symbol_type
  EvalParser::make_ANY (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_ANY, YY_MOVE (l));
  }

  inline
  EvalParser::symbol_type
  EvalParser::make_DATA (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_DATA, YY_MOVE (l));
  }

  inline
  EvalParser::symbol_type
  EvalParser::make_ENTERPRISE (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_ENTERPRISE, YY_MOVE (l));
  }

  inline
  EvalParser::symbol_type
  EvalParser::make_TOPLEVEL_BOOL (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_TOPLEVEL_BOOL, YY_MOVE (l));
  }

  inline
  EvalParser::symbol_type
  EvalParser::make_TOPLEVEL_STRING (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_TOPLEVEL_STRING, YY_MOVE (l));
  }

  inline
  EvalParser::symbol_type
  EvalParser::make_STRING (YY_COPY (std::string) v, YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_STRING, YY_MOVE (v), YY_MOVE (l));
  }

  inline
  EvalParser::symbol_type
  EvalParser::make_INTEGER (YY_COPY (std::string) v, YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_INTEGER, YY_MOVE (v), YY_MOVE (l));
  }

  inline
  EvalParser::symbol_type
  EvalParser::make_HEXSTRING (YY_COPY (std::string) v, YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_HEXSTRING, YY_MOVE (v), YY_MOVE (l));
  }

  inline
  EvalParser::symbol_type
  EvalParser::make_OPTION_NAME (YY_COPY (std::string) v, YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_OPTION_NAME, YY_MOVE (v), YY_MOVE (l));
  }

  inline
  EvalParser::symbol_type
  EvalParser::make_IP_ADDRESS (YY_COPY (std::string) v, YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_IP_ADDRESS, YY_MOVE (v), YY_MOVE (l));
  }


#line 14 "parser.yy" // lalr1.cc:404
} } // isc::eval
#line 1912 "parser.h" // lalr1.cc:404




#endif // !YY_EVAL_PARSER_H_INCLUDED
