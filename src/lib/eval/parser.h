// A Bison parser, made by GNU Bison 3.3.2.

// Skeleton interface for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015, 2018-2019 Free Software Foundation, Inc.

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
#line 17 "parser.yy" // lalr1.cc:401

#include <string>
#include <eval/token.h>
#include <eval/eval_context_decl.h>
#include <dhcp/option.h>
#include <boost/lexical_cast.hpp>

using namespace isc::dhcp;
using namespace isc::eval;

#line 59 "parser.h" // lalr1.cc:401

# include <cassert>
# include <cstdlib> // std::abort
# include <iostream>
# include <stdexcept>
# include <string>
# include <vector>

#if defined __cplusplus
# define YY_CPLUSPLUS __cplusplus
#else
# define YY_CPLUSPLUS 199711L
#endif

// Support move semantics when possible.
#if 201103L <= YY_CPLUSPLUS
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

// Support noexcept when possible.
#if 201103L <= YY_CPLUSPLUS
# define YY_NOEXCEPT noexcept
# define YY_NOTHROW
#else
# define YY_NOEXCEPT
# define YY_NOTHROW throw ()
#endif

// Support constexpr when possible.
#if 201703 <= YY_CPLUSPLUS
# define YY_CONSTEXPR constexpr
#else
# define YY_CONSTEXPR
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

#line 14 "parser.yy" // lalr1.cc:401
namespace isc { namespace eval {
#line 183 "parser.h" // lalr1.cc:401



  /// A Bison parser.
  class EvalParser
  {
  public:
#ifndef EVALSTYPE
  /// A buffer to store and retrieve objects.
  ///
  /// Sort of a variant, but does not keep track of the nature
  /// of the stored data, since that knowledge is available
  /// via the current parser state.
  class semantic_type
  {
  public:
    /// Type of *this.
    typedef semantic_type self_type;

    /// Empty construction.
    semantic_type () YY_NOEXCEPT
      : yybuffer_ ()
      , yytypeid_ (YY_NULLPTR)
    {}

    /// Construct and fill.
    template <typename T>
    semantic_type (YY_RVREF (T) t)
      : yytypeid_ (&typeid (T))
    {
      YYASSERT (sizeof (T) <= size);
      new (yyas_<T> ()) T (YY_MOVE (t));
    }

    /// Destruction, allowed only if empty.
    ~semantic_type () YY_NOEXCEPT
    {
      YYASSERT (!yytypeid_);
    }

# if 201103L <= YY_CPLUSPLUS
    /// Instantiate a \a T in here from \a t.
    template <typename T, typename... U>
    T&
    emplace (U&&... u)
    {
      YYASSERT (!yytypeid_);
      YYASSERT (sizeof (T) <= size);
      yytypeid_ = & typeid (T);
      return *new (yyas_<T> ()) T (std::forward <U>(u)...);
    }
# else
    /// Instantiate an empty \a T in here.
    template <typename T>
    T&
    emplace ()
    {
      YYASSERT (!yytypeid_);
      YYASSERT (sizeof (T) <= size);
      yytypeid_ = & typeid (T);
      return *new (yyas_<T> ()) T ();
    }

    /// Instantiate a \a T in here from \a t.
    template <typename T>
    T&
    emplace (const T& t)
    {
      YYASSERT (!yytypeid_);
      YYASSERT (sizeof (T) <= size);
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
    as () YY_NOEXCEPT
    {
      YYASSERT (yytypeid_);
      YYASSERT (*yytypeid_ == typeid (T));
      YYASSERT (sizeof (T) <= size);
      return *yyas_<T> ();
    }

    /// Const accessor to a built \a T (for %printer).
    template <typename T>
    const T&
    as () const YY_NOEXCEPT
    {
      YYASSERT (yytypeid_);
      YYASSERT (*yytypeid_ == typeid (T));
      YYASSERT (sizeof (T) <= size);
      return *yyas_<T> ();
    }

    /// Swap the content with \a that, of same type.
    ///
    /// Both variants must be built beforehand, because swapping the actual
    /// data requires reading it (with as()), and this is not possible on
    /// unconstructed variants: it would require some dynamic testing, which
    /// should not be the variant's responsibility.
    /// Swapping between built and (possibly) non-built is done with
    /// self_type::move ().
    template <typename T>
    void
    swap (self_type& that) YY_NOEXCEPT
    {
      YYASSERT (yytypeid_);
      YYASSERT (*yytypeid_ == *that.yytypeid_);
      std::swap (as<T> (), that.as<T> ());
    }

    /// Move the content of \a that to this.
    ///
    /// Destroys \a that.
    template <typename T>
    void
    move (self_type& that)
    {
# if 201103L <= YY_CPLUSPLUS
      emplace<T> (std::move (that.as<T> ()));
# else
      emplace<T> ();
      swap<T> (that);
# endif
      that.destroy<T> ();
    }

# if 201103L <= YY_CPLUSPLUS
    /// Move the content of \a that to this.
    template <typename T>
    void
    move (self_type&& that)
    {
      emplace<T> (std::move (that.as<T> ()));
      that.destroy<T> ();
    }
#endif

    /// Copy the content of \a that to this.
    template <typename T>
    void
    copy (const self_type& that)
    {
      emplace<T> (that.as<T> ());
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
    semantic_type (const self_type&);

    /// Accessor to raw memory as \a T.
    template <typename T>
    T*
    yyas_ () YY_NOEXCEPT
    {
      void *yyp = yybuffer_.yyraw;
      return static_cast<T*> (yyp);
     }

    /// Const accessor to raw memory as \a T.
    template <typename T>
    const T*
    yyas_ () const YY_NOEXCEPT
    {
      const void *yyp = yybuffer_.yyraw;
      return static_cast<const T*> (yyp);
     }

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

    /// The size of the largest semantic type.
    enum { size = sizeof (union_type) };

    /// A buffer to store semantic values.
    union
    {
      /// Strongest alignment constraints.
      long double yyalign_me;
      /// A buffer large enough to store any of the semantic values.
      char yyraw[size];
    } yybuffer_;

    /// Whether the content is built: if defined, the name of the stored type.
    const std::type_info *yytypeid_;
  };

#else
    typedef EVALSTYPE semantic_type;
#endif
    /// Symbol locations.
    typedef location location_type;

    /// Syntax errors thrown from user actions.
    struct syntax_error : std::runtime_error
    {
      syntax_error (const location_type& l, const std::string& m)
        : std::runtime_error (m)
        , location (l)
      {}

      syntax_error (const syntax_error& s)
        : std::runtime_error (s.what ())
        , location (s.location)
      {}

      ~syntax_error () YY_NOEXCEPT YY_NOTHROW;

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
      basic_symbol ()
        : value ()
        , location ()
      {}

#if 201103L <= YY_CPLUSPLUS
      /// Move constructor.
      basic_symbol (basic_symbol&& that);
#endif

      /// Copy constructor.
      basic_symbol (const basic_symbol& that);

      /// Constructor for valueless symbols, and symbols from each type.
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, location_type&& l)
        : Base (t)
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const location_type& l)
        : Base (t)
        , location (l)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, TokenOption::RepresentationType&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const TokenOption::RepresentationType& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, TokenPkt4::FieldType&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const TokenPkt4::FieldType& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, TokenPkt6::FieldType&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const TokenPkt6::FieldType& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, TokenPkt::MetadataType&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const TokenPkt::MetadataType& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, TokenRelay6Field::FieldType&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const TokenRelay6Field::FieldType& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, int8_t&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const int8_t& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, std::string&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const std::string& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, uint16_t&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const uint16_t& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, uint32_t&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const uint32_t& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

      /// Destroy the symbol.
      ~basic_symbol ()
      {
        clear ();
      }

      /// Destroy contents, and record that is empty.
      void clear ()
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

      /// Whether empty.
      bool empty () const YY_NOEXCEPT;

      /// Destructive move, \a s is emptied into this.
      void move (basic_symbol& s);

      /// The semantic value.
      semantic_type value;

      /// The location.
      location_type location;

    private:
#if YY_CPLUSPLUS < 201103L
      /// Assignment operator.
      basic_symbol& operator= (const basic_symbol& that);
#endif
    };

    /// Type access provider for token (enum) based symbols.
    struct by_type
    {
      /// Default constructor.
      by_type ();

#if 201103L <= YY_CPLUSPLUS
      /// Move constructor.
      by_type (by_type&& that);
#endif

      /// Copy constructor.
      by_type (const by_type& that);

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
      symbol_number_type type_get () const YY_NOEXCEPT;

      /// The token.
      token_type token () const YY_NOEXCEPT;

      /// The symbol type.
      /// \a empty_symbol when empty.
      /// An int, not token_number_type, to be able to store empty_symbol.
      int type;
    };

    /// "External" symbols: returned by the scanner.
    struct symbol_type : basic_symbol<by_type>
    {
      /// Superclass.
      typedef basic_symbol<by_type> super_type;

      /// Empty symbol.
      symbol_type () {}

      /// Constructor for valueless symbols, and symbols from each type.
#if 201103L <= YY_CPLUSPLUS
      symbol_type (int tok, location_type l)
        : super_type(token_type (tok), std::move (l))
      {
        YYASSERT (tok == token::TOKEN_END || tok == token::TOKEN_LPAREN || tok == token::TOKEN_RPAREN || tok == token::TOKEN_NOT || tok == token::TOKEN_AND || tok == token::TOKEN_OR || tok == token::TOKEN_EQUAL || tok == token::TOKEN_OPTION || tok == token::TOKEN_RELAY4 || tok == token::TOKEN_RELAY6 || tok == token::TOKEN_MEMBER || tok == token::TOKEN_PEERADDR || tok == token::TOKEN_LINKADDR || tok == token::TOKEN_LBRACKET || tok == token::TOKEN_RBRACKET || tok == token::TOKEN_DOT || tok == token::TOKEN_TEXT || tok == token::TOKEN_HEX || tok == token::TOKEN_EXISTS || tok == token::TOKEN_PKT || tok == token::TOKEN_IFACE || tok == token::TOKEN_SRC || tok == token::TOKEN_DST || tok == token::TOKEN_LEN || tok == token::TOKEN_PKT4 || tok == token::TOKEN_CHADDR || tok == token::TOKEN_HLEN || tok == token::TOKEN_HTYPE || tok == token::TOKEN_CIADDR || tok == token::TOKEN_GIADDR || tok == token::TOKEN_YIADDR || tok == token::TOKEN_SIADDR || tok == token::TOKEN_SUBSTRING || tok == token::TOKEN_ALL || tok == token::TOKEN_COMA || tok == token::TOKEN_CONCAT || tok == token::TOKEN_IFELSE || tok == token::TOKEN_TOHEXSTRING || tok == token::TOKEN_PKT6 || tok == token::TOKEN_MSGTYPE || tok == token::TOKEN_TRANSID || tok == token::TOKEN_VENDOR_CLASS || tok == token::TOKEN_VENDOR || tok == token::TOKEN_ANY || tok == token::TOKEN_DATA || tok == token::TOKEN_ENTERPRISE || tok == token::TOKEN_TOPLEVEL_BOOL || tok == token::TOKEN_TOPLEVEL_STRING);
      }
#else
      symbol_type (int tok, const location_type& l)
        : super_type(token_type (tok), l)
      {
        YYASSERT (tok == token::TOKEN_END || tok == token::TOKEN_LPAREN || tok == token::TOKEN_RPAREN || tok == token::TOKEN_NOT || tok == token::TOKEN_AND || tok == token::TOKEN_OR || tok == token::TOKEN_EQUAL || tok == token::TOKEN_OPTION || tok == token::TOKEN_RELAY4 || tok == token::TOKEN_RELAY6 || tok == token::TOKEN_MEMBER || tok == token::TOKEN_PEERADDR || tok == token::TOKEN_LINKADDR || tok == token::TOKEN_LBRACKET || tok == token::TOKEN_RBRACKET || tok == token::TOKEN_DOT || tok == token::TOKEN_TEXT || tok == token::TOKEN_HEX || tok == token::TOKEN_EXISTS || tok == token::TOKEN_PKT || tok == token::TOKEN_IFACE || tok == token::TOKEN_SRC || tok == token::TOKEN_DST || tok == token::TOKEN_LEN || tok == token::TOKEN_PKT4 || tok == token::TOKEN_CHADDR || tok == token::TOKEN_HLEN || tok == token::TOKEN_HTYPE || tok == token::TOKEN_CIADDR || tok == token::TOKEN_GIADDR || tok == token::TOKEN_YIADDR || tok == token::TOKEN_SIADDR || tok == token::TOKEN_SUBSTRING || tok == token::TOKEN_ALL || tok == token::TOKEN_COMA || tok == token::TOKEN_CONCAT || tok == token::TOKEN_IFELSE || tok == token::TOKEN_TOHEXSTRING || tok == token::TOKEN_PKT6 || tok == token::TOKEN_MSGTYPE || tok == token::TOKEN_TRANSID || tok == token::TOKEN_VENDOR_CLASS || tok == token::TOKEN_VENDOR || tok == token::TOKEN_ANY || tok == token::TOKEN_DATA || tok == token::TOKEN_ENTERPRISE || tok == token::TOKEN_TOPLEVEL_BOOL || tok == token::TOKEN_TOPLEVEL_STRING);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      symbol_type (int tok, std::string v, location_type l)
        : super_type(token_type (tok), std::move (v), std::move (l))
      {
        YYASSERT (tok == token::TOKEN_STRING || tok == token::TOKEN_INTEGER || tok == token::TOKEN_HEXSTRING || tok == token::TOKEN_OPTION_NAME || tok == token::TOKEN_IP_ADDRESS);
      }
#else
      symbol_type (int tok, const std::string& v, const location_type& l)
        : super_type(token_type (tok), v, l)
      {
        YYASSERT (tok == token::TOKEN_STRING || tok == token::TOKEN_INTEGER || tok == token::TOKEN_HEXSTRING || tok == token::TOKEN_OPTION_NAME || tok == token::TOKEN_IP_ADDRESS);
      }
#endif
    };

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

    // Implementation of make_symbol for each symbol type.
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_END (location_type l)
      {
        return symbol_type (token::TOKEN_END, std::move (l));
      }
#else
      static
      symbol_type
      make_END (const location_type& l)
      {
        return symbol_type (token::TOKEN_END, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_LPAREN (location_type l)
      {
        return symbol_type (token::TOKEN_LPAREN, std::move (l));
      }
#else
      static
      symbol_type
      make_LPAREN (const location_type& l)
      {
        return symbol_type (token::TOKEN_LPAREN, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_RPAREN (location_type l)
      {
        return symbol_type (token::TOKEN_RPAREN, std::move (l));
      }
#else
      static
      symbol_type
      make_RPAREN (const location_type& l)
      {
        return symbol_type (token::TOKEN_RPAREN, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_NOT (location_type l)
      {
        return symbol_type (token::TOKEN_NOT, std::move (l));
      }
#else
      static
      symbol_type
      make_NOT (const location_type& l)
      {
        return symbol_type (token::TOKEN_NOT, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_AND (location_type l)
      {
        return symbol_type (token::TOKEN_AND, std::move (l));
      }
#else
      static
      symbol_type
      make_AND (const location_type& l)
      {
        return symbol_type (token::TOKEN_AND, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_OR (location_type l)
      {
        return symbol_type (token::TOKEN_OR, std::move (l));
      }
#else
      static
      symbol_type
      make_OR (const location_type& l)
      {
        return symbol_type (token::TOKEN_OR, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_EQUAL (location_type l)
      {
        return symbol_type (token::TOKEN_EQUAL, std::move (l));
      }
#else
      static
      symbol_type
      make_EQUAL (const location_type& l)
      {
        return symbol_type (token::TOKEN_EQUAL, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_OPTION (location_type l)
      {
        return symbol_type (token::TOKEN_OPTION, std::move (l));
      }
#else
      static
      symbol_type
      make_OPTION (const location_type& l)
      {
        return symbol_type (token::TOKEN_OPTION, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_RELAY4 (location_type l)
      {
        return symbol_type (token::TOKEN_RELAY4, std::move (l));
      }
#else
      static
      symbol_type
      make_RELAY4 (const location_type& l)
      {
        return symbol_type (token::TOKEN_RELAY4, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_RELAY6 (location_type l)
      {
        return symbol_type (token::TOKEN_RELAY6, std::move (l));
      }
#else
      static
      symbol_type
      make_RELAY6 (const location_type& l)
      {
        return symbol_type (token::TOKEN_RELAY6, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_MEMBER (location_type l)
      {
        return symbol_type (token::TOKEN_MEMBER, std::move (l));
      }
#else
      static
      symbol_type
      make_MEMBER (const location_type& l)
      {
        return symbol_type (token::TOKEN_MEMBER, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_PEERADDR (location_type l)
      {
        return symbol_type (token::TOKEN_PEERADDR, std::move (l));
      }
#else
      static
      symbol_type
      make_PEERADDR (const location_type& l)
      {
        return symbol_type (token::TOKEN_PEERADDR, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_LINKADDR (location_type l)
      {
        return symbol_type (token::TOKEN_LINKADDR, std::move (l));
      }
#else
      static
      symbol_type
      make_LINKADDR (const location_type& l)
      {
        return symbol_type (token::TOKEN_LINKADDR, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_LBRACKET (location_type l)
      {
        return symbol_type (token::TOKEN_LBRACKET, std::move (l));
      }
#else
      static
      symbol_type
      make_LBRACKET (const location_type& l)
      {
        return symbol_type (token::TOKEN_LBRACKET, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_RBRACKET (location_type l)
      {
        return symbol_type (token::TOKEN_RBRACKET, std::move (l));
      }
#else
      static
      symbol_type
      make_RBRACKET (const location_type& l)
      {
        return symbol_type (token::TOKEN_RBRACKET, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_DOT (location_type l)
      {
        return symbol_type (token::TOKEN_DOT, std::move (l));
      }
#else
      static
      symbol_type
      make_DOT (const location_type& l)
      {
        return symbol_type (token::TOKEN_DOT, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TEXT (location_type l)
      {
        return symbol_type (token::TOKEN_TEXT, std::move (l));
      }
#else
      static
      symbol_type
      make_TEXT (const location_type& l)
      {
        return symbol_type (token::TOKEN_TEXT, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_HEX (location_type l)
      {
        return symbol_type (token::TOKEN_HEX, std::move (l));
      }
#else
      static
      symbol_type
      make_HEX (const location_type& l)
      {
        return symbol_type (token::TOKEN_HEX, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_EXISTS (location_type l)
      {
        return symbol_type (token::TOKEN_EXISTS, std::move (l));
      }
#else
      static
      symbol_type
      make_EXISTS (const location_type& l)
      {
        return symbol_type (token::TOKEN_EXISTS, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_PKT (location_type l)
      {
        return symbol_type (token::TOKEN_PKT, std::move (l));
      }
#else
      static
      symbol_type
      make_PKT (const location_type& l)
      {
        return symbol_type (token::TOKEN_PKT, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_IFACE (location_type l)
      {
        return symbol_type (token::TOKEN_IFACE, std::move (l));
      }
#else
      static
      symbol_type
      make_IFACE (const location_type& l)
      {
        return symbol_type (token::TOKEN_IFACE, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_SRC (location_type l)
      {
        return symbol_type (token::TOKEN_SRC, std::move (l));
      }
#else
      static
      symbol_type
      make_SRC (const location_type& l)
      {
        return symbol_type (token::TOKEN_SRC, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_DST (location_type l)
      {
        return symbol_type (token::TOKEN_DST, std::move (l));
      }
#else
      static
      symbol_type
      make_DST (const location_type& l)
      {
        return symbol_type (token::TOKEN_DST, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_LEN (location_type l)
      {
        return symbol_type (token::TOKEN_LEN, std::move (l));
      }
#else
      static
      symbol_type
      make_LEN (const location_type& l)
      {
        return symbol_type (token::TOKEN_LEN, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_PKT4 (location_type l)
      {
        return symbol_type (token::TOKEN_PKT4, std::move (l));
      }
#else
      static
      symbol_type
      make_PKT4 (const location_type& l)
      {
        return symbol_type (token::TOKEN_PKT4, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_CHADDR (location_type l)
      {
        return symbol_type (token::TOKEN_CHADDR, std::move (l));
      }
#else
      static
      symbol_type
      make_CHADDR (const location_type& l)
      {
        return symbol_type (token::TOKEN_CHADDR, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_HLEN (location_type l)
      {
        return symbol_type (token::TOKEN_HLEN, std::move (l));
      }
#else
      static
      symbol_type
      make_HLEN (const location_type& l)
      {
        return symbol_type (token::TOKEN_HLEN, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_HTYPE (location_type l)
      {
        return symbol_type (token::TOKEN_HTYPE, std::move (l));
      }
#else
      static
      symbol_type
      make_HTYPE (const location_type& l)
      {
        return symbol_type (token::TOKEN_HTYPE, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_CIADDR (location_type l)
      {
        return symbol_type (token::TOKEN_CIADDR, std::move (l));
      }
#else
      static
      symbol_type
      make_CIADDR (const location_type& l)
      {
        return symbol_type (token::TOKEN_CIADDR, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_GIADDR (location_type l)
      {
        return symbol_type (token::TOKEN_GIADDR, std::move (l));
      }
#else
      static
      symbol_type
      make_GIADDR (const location_type& l)
      {
        return symbol_type (token::TOKEN_GIADDR, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_YIADDR (location_type l)
      {
        return symbol_type (token::TOKEN_YIADDR, std::move (l));
      }
#else
      static
      symbol_type
      make_YIADDR (const location_type& l)
      {
        return symbol_type (token::TOKEN_YIADDR, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_SIADDR (location_type l)
      {
        return symbol_type (token::TOKEN_SIADDR, std::move (l));
      }
#else
      static
      symbol_type
      make_SIADDR (const location_type& l)
      {
        return symbol_type (token::TOKEN_SIADDR, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_SUBSTRING (location_type l)
      {
        return symbol_type (token::TOKEN_SUBSTRING, std::move (l));
      }
#else
      static
      symbol_type
      make_SUBSTRING (const location_type& l)
      {
        return symbol_type (token::TOKEN_SUBSTRING, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ALL (location_type l)
      {
        return symbol_type (token::TOKEN_ALL, std::move (l));
      }
#else
      static
      symbol_type
      make_ALL (const location_type& l)
      {
        return symbol_type (token::TOKEN_ALL, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_COMA (location_type l)
      {
        return symbol_type (token::TOKEN_COMA, std::move (l));
      }
#else
      static
      symbol_type
      make_COMA (const location_type& l)
      {
        return symbol_type (token::TOKEN_COMA, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_CONCAT (location_type l)
      {
        return symbol_type (token::TOKEN_CONCAT, std::move (l));
      }
#else
      static
      symbol_type
      make_CONCAT (const location_type& l)
      {
        return symbol_type (token::TOKEN_CONCAT, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_IFELSE (location_type l)
      {
        return symbol_type (token::TOKEN_IFELSE, std::move (l));
      }
#else
      static
      symbol_type
      make_IFELSE (const location_type& l)
      {
        return symbol_type (token::TOKEN_IFELSE, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TOHEXSTRING (location_type l)
      {
        return symbol_type (token::TOKEN_TOHEXSTRING, std::move (l));
      }
#else
      static
      symbol_type
      make_TOHEXSTRING (const location_type& l)
      {
        return symbol_type (token::TOKEN_TOHEXSTRING, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_PKT6 (location_type l)
      {
        return symbol_type (token::TOKEN_PKT6, std::move (l));
      }
#else
      static
      symbol_type
      make_PKT6 (const location_type& l)
      {
        return symbol_type (token::TOKEN_PKT6, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_MSGTYPE (location_type l)
      {
        return symbol_type (token::TOKEN_MSGTYPE, std::move (l));
      }
#else
      static
      symbol_type
      make_MSGTYPE (const location_type& l)
      {
        return symbol_type (token::TOKEN_MSGTYPE, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TRANSID (location_type l)
      {
        return symbol_type (token::TOKEN_TRANSID, std::move (l));
      }
#else
      static
      symbol_type
      make_TRANSID (const location_type& l)
      {
        return symbol_type (token::TOKEN_TRANSID, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_VENDOR_CLASS (location_type l)
      {
        return symbol_type (token::TOKEN_VENDOR_CLASS, std::move (l));
      }
#else
      static
      symbol_type
      make_VENDOR_CLASS (const location_type& l)
      {
        return symbol_type (token::TOKEN_VENDOR_CLASS, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_VENDOR (location_type l)
      {
        return symbol_type (token::TOKEN_VENDOR, std::move (l));
      }
#else
      static
      symbol_type
      make_VENDOR (const location_type& l)
      {
        return symbol_type (token::TOKEN_VENDOR, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ANY (location_type l)
      {
        return symbol_type (token::TOKEN_ANY, std::move (l));
      }
#else
      static
      symbol_type
      make_ANY (const location_type& l)
      {
        return symbol_type (token::TOKEN_ANY, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_DATA (location_type l)
      {
        return symbol_type (token::TOKEN_DATA, std::move (l));
      }
#else
      static
      symbol_type
      make_DATA (const location_type& l)
      {
        return symbol_type (token::TOKEN_DATA, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ENTERPRISE (location_type l)
      {
        return symbol_type (token::TOKEN_ENTERPRISE, std::move (l));
      }
#else
      static
      symbol_type
      make_ENTERPRISE (const location_type& l)
      {
        return symbol_type (token::TOKEN_ENTERPRISE, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TOPLEVEL_BOOL (location_type l)
      {
        return symbol_type (token::TOKEN_TOPLEVEL_BOOL, std::move (l));
      }
#else
      static
      symbol_type
      make_TOPLEVEL_BOOL (const location_type& l)
      {
        return symbol_type (token::TOKEN_TOPLEVEL_BOOL, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TOPLEVEL_STRING (location_type l)
      {
        return symbol_type (token::TOKEN_TOPLEVEL_STRING, std::move (l));
      }
#else
      static
      symbol_type
      make_TOPLEVEL_STRING (const location_type& l)
      {
        return symbol_type (token::TOKEN_TOPLEVEL_STRING, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_STRING (std::string v, location_type l)
      {
        return symbol_type (token::TOKEN_STRING, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_STRING (const std::string& v, const location_type& l)
      {
        return symbol_type (token::TOKEN_STRING, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_INTEGER (std::string v, location_type l)
      {
        return symbol_type (token::TOKEN_INTEGER, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_INTEGER (const std::string& v, const location_type& l)
      {
        return symbol_type (token::TOKEN_INTEGER, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_HEXSTRING (std::string v, location_type l)
      {
        return symbol_type (token::TOKEN_HEXSTRING, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_HEXSTRING (const std::string& v, const location_type& l)
      {
        return symbol_type (token::TOKEN_HEXSTRING, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_OPTION_NAME (std::string v, location_type l)
      {
        return symbol_type (token::TOKEN_OPTION_NAME, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_OPTION_NAME (const std::string& v, const location_type& l)
      {
        return symbol_type (token::TOKEN_OPTION_NAME, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_IP_ADDRESS (std::string v, location_type l)
      {
        return symbol_type (token::TOKEN_IP_ADDRESS, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_IP_ADDRESS (const std::string& v, const location_type& l)
      {
        return symbol_type (token::TOKEN_IP_ADDRESS, v, l);
      }
#endif


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
      by_state () YY_NOEXCEPT;

      /// The symbol type as needed by the constructor.
      typedef state_type kind_type;

      /// Constructor.
      by_state (kind_type s) YY_NOEXCEPT;

      /// Copy constructor.
      by_state (const by_state& that) YY_NOEXCEPT;

      /// Record that this symbol is empty.
      void clear () YY_NOEXCEPT;

      /// Steal the symbol type from \a that.
      void move (by_state& that);

      /// The (internal) type number (corresponding to \a state).
      /// \a empty_symbol when empty.
      symbol_number_type type_get () const YY_NOEXCEPT;

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
#if YY_CPLUSPLUS < 201103L
      /// Assignment, needed by push_back by some old implementations.
      /// Moves the contents of that.
      stack_symbol_type& operator= (stack_symbol_type& that);
#endif
    };

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
        operator[] (0).move (t);
      }

      /// Pop elements from the stack.
      void
      pop (int n = 1) YY_NOEXCEPT
      {
        for (; 0 < n; --n)
          seq_.pop_back ();
      }

      /// Pop all elements from the stack.
      void
      clear () YY_NOEXCEPT
      {
        seq_.clear ();
      }

      /// Number of elements on the stack.
      size_type
      size () const YY_NOEXCEPT
      {
        return seq_.size ();
      }

      /// Iterator on top of the stack (going downwards).
      const_iterator
      begin () const YY_NOEXCEPT
      {
        return seq_.rbegin ();
      }

      /// Bottom of the stack.
      const_iterator
      end () const YY_NOEXCEPT
      {
        return seq_.rend ();
      }

      /// Present a slice of the top of a stack.
      class slice
      {
      public:
        slice (const stack& stack, int range)
          : stack_ (stack)
          , range_ (range)
        {}

        const T&
        operator[] (int i) const
        {
          return stack_[range_ - i];
        }

      private:
        const stack& stack_;
        int range_;
      };

    private:
      stack (const stack&);
      stack& operator= (const stack&);
      /// The wrapped container.
      S seq_;
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

  inline
  EvalParser::token_number_type
  EvalParser::yytranslate_ (token_type t)
  {
    // YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to
    // TOKEN-NUM as returned by yylex.
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

  // basic_symbol.
#if 201103L <= YY_CPLUSPLUS
  template <typename Base>
  EvalParser::basic_symbol<Base>::basic_symbol (basic_symbol&& that)
    : Base (std::move (that))
    , value ()
    , location (std::move (that.location))
  {
    switch (this->type_get ())
    {
      case 62: // option_repr_type
        value.move< TokenOption::RepresentationType > (std::move (that.value));
        break;

      case 66: // pkt4_field
        value.move< TokenPkt4::FieldType > (std::move (that.value));
        break;

      case 67: // pkt6_field
        value.move< TokenPkt6::FieldType > (std::move (that.value));
        break;

      case 64: // pkt_metadata
        value.move< TokenPkt::MetadataType > (std::move (that.value));
        break;

      case 68: // relay6_field
        value.move< TokenRelay6Field::FieldType > (std::move (that.value));
        break;

      case 63: // nest_level
        value.move< int8_t > (std::move (that.value));
        break;

      case 50: // "constant string"
      case 51: // "integer"
      case 52: // "constant hexstring"
      case 53: // "option name"
      case 54: // "ip address"
        value.move< std::string > (std::move (that.value));
        break;

      case 61: // option_code
        value.move< uint16_t > (std::move (that.value));
        break;

      case 60: // integer_expr
      case 65: // enterprise_id
        value.move< uint32_t > (std::move (that.value));
        break;

      default:
        break;
    }

  }
#endif

  template <typename Base>
  EvalParser::basic_symbol<Base>::basic_symbol (const basic_symbol& that)
    : Base (that)
    , value ()
    , location (that.location)
  {
    switch (this->type_get ())
    {
      case 62: // option_repr_type
        value.copy< TokenOption::RepresentationType > (YY_MOVE (that.value));
        break;

      case 66: // pkt4_field
        value.copy< TokenPkt4::FieldType > (YY_MOVE (that.value));
        break;

      case 67: // pkt6_field
        value.copy< TokenPkt6::FieldType > (YY_MOVE (that.value));
        break;

      case 64: // pkt_metadata
        value.copy< TokenPkt::MetadataType > (YY_MOVE (that.value));
        break;

      case 68: // relay6_field
        value.copy< TokenRelay6Field::FieldType > (YY_MOVE (that.value));
        break;

      case 63: // nest_level
        value.copy< int8_t > (YY_MOVE (that.value));
        break;

      case 50: // "constant string"
      case 51: // "integer"
      case 52: // "constant hexstring"
      case 53: // "option name"
      case 54: // "ip address"
        value.copy< std::string > (YY_MOVE (that.value));
        break;

      case 61: // option_code
        value.copy< uint16_t > (YY_MOVE (that.value));
        break;

      case 60: // integer_expr
      case 65: // enterprise_id
        value.copy< uint32_t > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

  }



  template <typename Base>
  bool
  EvalParser::basic_symbol<Base>::empty () const YY_NOEXCEPT
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

#if 201103L <= YY_CPLUSPLUS
  inline
  EvalParser::by_type::by_type (by_type&& that)
    : type (that.type)
  {
    that.clear ();
  }
#endif

  inline
  EvalParser::by_type::by_type (const by_type& that)
    : type (that.type)
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
  EvalParser::by_type::type_get () const YY_NOEXCEPT
  {
    return type;
  }

  inline
  EvalParser::token_type
  EvalParser::by_type::token () const YY_NOEXCEPT
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
    return token_type (yytoken_number_[type]);
  }

#line 14 "parser.yy" // lalr1.cc:401
} } // isc::eval
#line 2302 "parser.h" // lalr1.cc:401




#endif // !YY_EVAL_PARSER_H_INCLUDED
