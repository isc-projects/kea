// A Bison parser, made by GNU Bison 3.8.2.

// Skeleton interface for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015, 2018-2021 Free Software Foundation, Inc.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

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

// DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
// especially those whose name start with YY_ or yy_.  They are
// private implementation details that can be changed or removed.

#ifndef YY_EVAL_PARSER_H_INCLUDED
# define YY_EVAL_PARSER_H_INCLUDED
// "%code requires" blocks.
#line 17 "parser.yy"

#include <string>
#include <eval/token.h>
#include <eval/eval_context_decl.h>
#include <dhcp/option.h>
#include <boost/lexical_cast.hpp>

using namespace isc::dhcp;
using namespace isc::eval;

#line 60 "parser.h"

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
#ifndef EVAL_ASSERT
# include <cassert>
# define EVAL_ASSERT assert
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
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

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
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

#line 14 "parser.yy"
namespace isc { namespace eval {
#line 209 "parser.h"




  /// A Bison parser.
  class EvalParser
  {
  public:
#ifdef EVALSTYPE
# ifdef __GNUC__
#  pragma GCC message "bison: do not #define EVALSTYPE in C++, use %define api.value.type"
# endif
    typedef EVALSTYPE value_type;
#else
  /// A buffer to store and retrieve objects.
  ///
  /// Sort of a variant, but does not keep track of the nature
  /// of the stored data, since that knowledge is available
  /// via the current parser state.
  class value_type
  {
  public:
    /// Type of *this.
    typedef value_type self_type;

    /// Empty construction.
    value_type () YY_NOEXCEPT
      : yyraw_ ()
      , yytypeid_ (YY_NULLPTR)
    {}

    /// Construct and fill.
    template <typename T>
    value_type (YY_RVREF (T) t)
      : yytypeid_ (&typeid (T))
    {
      EVAL_ASSERT (sizeof (T) <= size);
      new (yyas_<T> ()) T (YY_MOVE (t));
    }

#if 201103L <= YY_CPLUSPLUS
    /// Non copyable.
    value_type (const self_type&) = delete;
    /// Non copyable.
    self_type& operator= (const self_type&) = delete;
#endif

    /// Destruction, allowed only if empty.
    ~value_type () YY_NOEXCEPT
    {
      EVAL_ASSERT (!yytypeid_);
    }

# if 201103L <= YY_CPLUSPLUS
    /// Instantiate a \a T in here from \a t.
    template <typename T, typename... U>
    T&
    emplace (U&&... u)
    {
      EVAL_ASSERT (!yytypeid_);
      EVAL_ASSERT (sizeof (T) <= size);
      yytypeid_ = & typeid (T);
      return *new (yyas_<T> ()) T (std::forward <U>(u)...);
    }
# else
    /// Instantiate an empty \a T in here.
    template <typename T>
    T&
    emplace ()
    {
      EVAL_ASSERT (!yytypeid_);
      EVAL_ASSERT (sizeof (T) <= size);
      yytypeid_ = & typeid (T);
      return *new (yyas_<T> ()) T ();
    }

    /// Instantiate a \a T in here from \a t.
    template <typename T>
    T&
    emplace (const T& t)
    {
      EVAL_ASSERT (!yytypeid_);
      EVAL_ASSERT (sizeof (T) <= size);
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
      EVAL_ASSERT (yytypeid_);
      EVAL_ASSERT (*yytypeid_ == typeid (T));
      EVAL_ASSERT (sizeof (T) <= size);
      return *yyas_<T> ();
    }

    /// Const accessor to a built \a T (for %printer).
    template <typename T>
    const T&
    as () const YY_NOEXCEPT
    {
      EVAL_ASSERT (yytypeid_);
      EVAL_ASSERT (*yytypeid_ == typeid (T));
      EVAL_ASSERT (sizeof (T) <= size);
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
      EVAL_ASSERT (yytypeid_);
      EVAL_ASSERT (*yytypeid_ == *that.yytypeid_);
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
#if YY_CPLUSPLUS < 201103L
    /// Non copyable.
    value_type (const self_type&);
    /// Non copyable.
    self_type& operator= (const self_type&);
#endif

    /// Accessor to raw memory as \a T.
    template <typename T>
    T*
    yyas_ () YY_NOEXCEPT
    {
      void *yyp = yyraw_;
      return static_cast<T*> (yyp);
     }

    /// Const accessor to raw memory as \a T.
    template <typename T>
    const T*
    yyas_ () const YY_NOEXCEPT
    {
      const void *yyp = yyraw_;
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
      // sub_option_code
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
      long double yyalign_me_;
      /// A buffer large enough to store any of the semantic values.
      char yyraw_[size];
    };

    /// Whether the content is built: if defined, the name of the stored type.
    const std::type_info *yytypeid_;
  };

#endif
    /// Backward compatibility (Bison 3.8).
    typedef value_type semantic_type;

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

    /// Token kinds.
    struct token
    {
      enum token_kind_type
      {
        TOKEN_EVALEMPTY = -2,
    TOKEN_END = 0,                 // "end of file"
    TOKEN_EVALerror = 256,         // error
    TOKEN_EVALUNDEF = 257,         // "invalid token"
    TOKEN_LPAREN = 258,            // "("
    TOKEN_RPAREN = 259,            // ")"
    TOKEN_NOT = 260,               // "not"
    TOKEN_AND = 261,               // "and"
    TOKEN_OR = 262,                // "or"
    TOKEN_EQUAL = 263,             // "=="
    TOKEN_OPTION = 264,            // "option"
    TOKEN_RELAY4 = 265,            // "relay4"
    TOKEN_RELAY6 = 266,            // "relay6"
    TOKEN_MEMBER = 267,            // "member"
    TOKEN_PEERADDR = 268,          // "peeraddr"
    TOKEN_LINKADDR = 269,          // "linkaddr"
    TOKEN_LBRACKET = 270,          // "["
    TOKEN_RBRACKET = 271,          // "]"
    TOKEN_DOT = 272,               // "."
    TOKEN_TEXT = 273,              // "text"
    TOKEN_HEX = 274,               // "hex"
    TOKEN_EXISTS = 275,            // "exists"
    TOKEN_PKT = 276,               // "pkt"
    TOKEN_IFACE = 277,             // "iface"
    TOKEN_SRC = 278,               // "src"
    TOKEN_DST = 279,               // "dst"
    TOKEN_LEN = 280,               // "len"
    TOKEN_PKT4 = 281,              // "pkt4"
    TOKEN_CHADDR = 282,            // "mac"
    TOKEN_HLEN = 283,              // "hlen"
    TOKEN_HTYPE = 284,             // "htype"
    TOKEN_CIADDR = 285,            // "ciaddr"
    TOKEN_GIADDR = 286,            // "giaddr"
    TOKEN_YIADDR = 287,            // "yiaddr"
    TOKEN_SIADDR = 288,            // "siaddr"
    TOKEN_SUBSTRING = 289,         // "substring"
    TOKEN_SPLIT = 290,             // "split"
    TOKEN_ALL = 291,               // "all"
    TOKEN_COMA = 292,              // ","
    TOKEN_CONCAT = 293,            // "concat"
    TOKEN_PLUS = 294,              // "+"
    TOKEN_IFELSE = 295,            // "ifelse"
    TOKEN_TOHEXSTRING = 296,       // "hexstring"
    TOKEN_ADDRTOTEXT = 297,        // "addrtotext"
    TOKEN_INT8TOTEXT = 298,        // "int8totext"
    TOKEN_INT16TOTEXT = 299,       // "int16totext"
    TOKEN_INT32TOTEXT = 300,       // "int32totext"
    TOKEN_UINT8TOTEXT = 301,       // "uint8totext"
    TOKEN_UINT16TOTEXT = 302,      // "uint16totext"
    TOKEN_UINT32TOTEXT = 303,      // "uint32totext"
    TOKEN_PKT6 = 304,              // "pkt6"
    TOKEN_MSGTYPE = 305,           // "msgtype"
    TOKEN_TRANSID = 306,           // "transid"
    TOKEN_VENDOR_CLASS = 307,      // "vendor-class"
    TOKEN_VENDOR = 308,            // "vendor"
    TOKEN_ANY = 309,               // "*"
    TOKEN_DATA = 310,              // "data"
    TOKEN_ENTERPRISE = 311,        // "enterprise"
    TOKEN_TOPLEVEL_BOOL = 312,     // "top-level bool"
    TOKEN_TOPLEVEL_STRING = 313,   // "top-level string"
    TOKEN_STRING = 314,            // "constant string"
    TOKEN_INTEGER = 315,           // "integer"
    TOKEN_HEXSTRING = 316,         // "constant hexstring"
    TOKEN_OPTION_NAME = 317,       // "option name"
    TOKEN_IP_ADDRESS = 318         // "ip address"
      };
      /// Backward compatibility alias (Bison 3.6).
      typedef token_kind_type yytokentype;
    };

    /// Token kind, as returned by yylex.
    typedef token::token_kind_type token_kind_type;

    /// Backward compatibility alias (Bison 3.6).
    typedef token_kind_type token_type;

    /// Symbol kinds.
    struct symbol_kind
    {
      enum symbol_kind_type
      {
        YYNTOKENS = 64, ///< Number of tokens.
        S_YYEMPTY = -2,
        S_YYEOF = 0,                             // "end of file"
        S_YYerror = 1,                           // error
        S_YYUNDEF = 2,                           // "invalid token"
        S_LPAREN = 3,                            // "("
        S_RPAREN = 4,                            // ")"
        S_NOT = 5,                               // "not"
        S_AND = 6,                               // "and"
        S_OR = 7,                                // "or"
        S_EQUAL = 8,                             // "=="
        S_OPTION = 9,                            // "option"
        S_RELAY4 = 10,                           // "relay4"
        S_RELAY6 = 11,                           // "relay6"
        S_MEMBER = 12,                           // "member"
        S_PEERADDR = 13,                         // "peeraddr"
        S_LINKADDR = 14,                         // "linkaddr"
        S_LBRACKET = 15,                         // "["
        S_RBRACKET = 16,                         // "]"
        S_DOT = 17,                              // "."
        S_TEXT = 18,                             // "text"
        S_HEX = 19,                              // "hex"
        S_EXISTS = 20,                           // "exists"
        S_PKT = 21,                              // "pkt"
        S_IFACE = 22,                            // "iface"
        S_SRC = 23,                              // "src"
        S_DST = 24,                              // "dst"
        S_LEN = 25,                              // "len"
        S_PKT4 = 26,                             // "pkt4"
        S_CHADDR = 27,                           // "mac"
        S_HLEN = 28,                             // "hlen"
        S_HTYPE = 29,                            // "htype"
        S_CIADDR = 30,                           // "ciaddr"
        S_GIADDR = 31,                           // "giaddr"
        S_YIADDR = 32,                           // "yiaddr"
        S_SIADDR = 33,                           // "siaddr"
        S_SUBSTRING = 34,                        // "substring"
        S_SPLIT = 35,                            // "split"
        S_ALL = 36,                              // "all"
        S_COMA = 37,                             // ","
        S_CONCAT = 38,                           // "concat"
        S_PLUS = 39,                             // "+"
        S_IFELSE = 40,                           // "ifelse"
        S_TOHEXSTRING = 41,                      // "hexstring"
        S_ADDRTOTEXT = 42,                       // "addrtotext"
        S_INT8TOTEXT = 43,                       // "int8totext"
        S_INT16TOTEXT = 44,                      // "int16totext"
        S_INT32TOTEXT = 45,                      // "int32totext"
        S_UINT8TOTEXT = 46,                      // "uint8totext"
        S_UINT16TOTEXT = 47,                     // "uint16totext"
        S_UINT32TOTEXT = 48,                     // "uint32totext"
        S_PKT6 = 49,                             // "pkt6"
        S_MSGTYPE = 50,                          // "msgtype"
        S_TRANSID = 51,                          // "transid"
        S_VENDOR_CLASS = 52,                     // "vendor-class"
        S_VENDOR = 53,                           // "vendor"
        S_ANY = 54,                              // "*"
        S_DATA = 55,                             // "data"
        S_ENTERPRISE = 56,                       // "enterprise"
        S_TOPLEVEL_BOOL = 57,                    // "top-level bool"
        S_TOPLEVEL_STRING = 58,                  // "top-level string"
        S_STRING = 59,                           // "constant string"
        S_INTEGER = 60,                          // "integer"
        S_HEXSTRING = 61,                        // "constant hexstring"
        S_OPTION_NAME = 62,                      // "option name"
        S_IP_ADDRESS = 63,                       // "ip address"
        S_YYACCEPT = 64,                         // $accept
        S_start = 65,                            // start
        S_expression = 66,                       // expression
        S_bool_expr = 67,                        // bool_expr
        S_string_expr = 68,                      // string_expr
        S_integer_expr = 69,                     // integer_expr
        S_option_code = 70,                      // option_code
        S_sub_option_code = 71,                  // sub_option_code
        S_option_repr_type = 72,                 // option_repr_type
        S_nest_level = 73,                       // nest_level
        S_pkt_metadata = 74,                     // pkt_metadata
        S_enterprise_id = 75,                    // enterprise_id
        S_pkt4_field = 76,                       // pkt4_field
        S_pkt6_field = 77,                       // pkt6_field
        S_relay6_field = 78,                     // relay6_field
        S_start_expr = 79,                       // start_expr
        S_length_expr = 80,                      // length_expr
        S_int_expr = 81                          // int_expr
      };
    };

    /// (Internal) symbol kind.
    typedef symbol_kind::symbol_kind_type symbol_kind_type;

    /// The number of tokens.
    static const symbol_kind_type YYNTOKENS = symbol_kind::YYNTOKENS;

    /// A complete symbol.
    ///
    /// Expects its Base type to provide access to the symbol kind
    /// via kind ().
    ///
    /// Provide access to semantic value and location.
    template <typename Base>
    struct basic_symbol : Base
    {
      /// Alias to Base.
      typedef Base super_type;

      /// Default constructor.
      basic_symbol () YY_NOEXCEPT
        : value ()
        , location ()
      {}

#if 201103L <= YY_CPLUSPLUS
      /// Move constructor.
      basic_symbol (basic_symbol&& that)
        : Base (std::move (that))
        , value ()
        , location (std::move (that.location))
      {
        switch (this->kind ())
    {
      case symbol_kind::S_option_repr_type: // option_repr_type
        value.move< TokenOption::RepresentationType > (std::move (that.value));
        break;

      case symbol_kind::S_pkt4_field: // pkt4_field
        value.move< TokenPkt4::FieldType > (std::move (that.value));
        break;

      case symbol_kind::S_pkt6_field: // pkt6_field
        value.move< TokenPkt6::FieldType > (std::move (that.value));
        break;

      case symbol_kind::S_pkt_metadata: // pkt_metadata
        value.move< TokenPkt::MetadataType > (std::move (that.value));
        break;

      case symbol_kind::S_relay6_field: // relay6_field
        value.move< TokenRelay6Field::FieldType > (std::move (that.value));
        break;

      case symbol_kind::S_nest_level: // nest_level
        value.move< int8_t > (std::move (that.value));
        break;

      case symbol_kind::S_STRING: // "constant string"
      case symbol_kind::S_INTEGER: // "integer"
      case symbol_kind::S_HEXSTRING: // "constant hexstring"
      case symbol_kind::S_OPTION_NAME: // "option name"
      case symbol_kind::S_IP_ADDRESS: // "ip address"
        value.move< std::string > (std::move (that.value));
        break;

      case symbol_kind::S_option_code: // option_code
      case symbol_kind::S_sub_option_code: // sub_option_code
        value.move< uint16_t > (std::move (that.value));
        break;

      case symbol_kind::S_integer_expr: // integer_expr
      case symbol_kind::S_enterprise_id: // enterprise_id
        value.move< uint32_t > (std::move (that.value));
        break;

      default:
        break;
    }

      }
#endif

      /// Copy constructor.
      basic_symbol (const basic_symbol& that);

      /// Constructors for typed symbols.
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
      void clear () YY_NOEXCEPT
      {
        // User destructor.
        symbol_kind_type yykind = this->kind ();
        basic_symbol<Base>& yysym = *this;
        (void) yysym;
        switch (yykind)
        {
       default:
          break;
        }

        // Value type destructor.
switch (yykind)
    {
      case symbol_kind::S_option_repr_type: // option_repr_type
        value.template destroy< TokenOption::RepresentationType > ();
        break;

      case symbol_kind::S_pkt4_field: // pkt4_field
        value.template destroy< TokenPkt4::FieldType > ();
        break;

      case symbol_kind::S_pkt6_field: // pkt6_field
        value.template destroy< TokenPkt6::FieldType > ();
        break;

      case symbol_kind::S_pkt_metadata: // pkt_metadata
        value.template destroy< TokenPkt::MetadataType > ();
        break;

      case symbol_kind::S_relay6_field: // relay6_field
        value.template destroy< TokenRelay6Field::FieldType > ();
        break;

      case symbol_kind::S_nest_level: // nest_level
        value.template destroy< int8_t > ();
        break;

      case symbol_kind::S_STRING: // "constant string"
      case symbol_kind::S_INTEGER: // "integer"
      case symbol_kind::S_HEXSTRING: // "constant hexstring"
      case symbol_kind::S_OPTION_NAME: // "option name"
      case symbol_kind::S_IP_ADDRESS: // "ip address"
        value.template destroy< std::string > ();
        break;

      case symbol_kind::S_option_code: // option_code
      case symbol_kind::S_sub_option_code: // sub_option_code
        value.template destroy< uint16_t > ();
        break;

      case symbol_kind::S_integer_expr: // integer_expr
      case symbol_kind::S_enterprise_id: // enterprise_id
        value.template destroy< uint32_t > ();
        break;

      default:
        break;
    }

        Base::clear ();
      }

      /// The user-facing name of this symbol.
      std::string name () const YY_NOEXCEPT
      {
        return EvalParser::symbol_name (this->kind ());
      }

      /// Backward compatibility (Bison 3.6).
      symbol_kind_type type_get () const YY_NOEXCEPT;

      /// Whether empty.
      bool empty () const YY_NOEXCEPT;

      /// Destructive move, \a s is emptied into this.
      void move (basic_symbol& s);

      /// The semantic value.
      value_type value;

      /// The location.
      location_type location;

    private:
#if YY_CPLUSPLUS < 201103L
      /// Assignment operator.
      basic_symbol& operator= (const basic_symbol& that);
#endif
    };

    /// Type access provider for token (enum) based symbols.
    struct by_kind
    {
      /// The symbol kind as needed by the constructor.
      typedef token_kind_type kind_type;

      /// Default constructor.
      by_kind () YY_NOEXCEPT;

#if 201103L <= YY_CPLUSPLUS
      /// Move constructor.
      by_kind (by_kind&& that) YY_NOEXCEPT;
#endif

      /// Copy constructor.
      by_kind (const by_kind& that) YY_NOEXCEPT;

      /// Constructor from (external) token numbers.
      by_kind (kind_type t) YY_NOEXCEPT;



      /// Record that this symbol is empty.
      void clear () YY_NOEXCEPT;

      /// Steal the symbol kind from \a that.
      void move (by_kind& that);

      /// The (internal) type number (corresponding to \a type).
      /// \a empty when empty.
      symbol_kind_type kind () const YY_NOEXCEPT;

      /// Backward compatibility (Bison 3.6).
      symbol_kind_type type_get () const YY_NOEXCEPT;

      /// The symbol kind.
      /// \a S_YYEMPTY when empty.
      symbol_kind_type kind_;
    };

    /// Backward compatibility for a private implementation detail (Bison 3.6).
    typedef by_kind by_type;

    /// "External" symbols: returned by the scanner.
    struct symbol_type : basic_symbol<by_kind>
    {
      /// Superclass.
      typedef basic_symbol<by_kind> super_type;

      /// Empty symbol.
      symbol_type () YY_NOEXCEPT {}

      /// Constructor for valueless symbols, and symbols from each type.
#if 201103L <= YY_CPLUSPLUS
      symbol_type (int tok, location_type l)
        : super_type (token_kind_type (tok), std::move (l))
#else
      symbol_type (int tok, const location_type& l)
        : super_type (token_kind_type (tok), l)
#endif
      {
#if !defined _MSC_VER || defined __clang__
        EVAL_ASSERT (tok == token::TOKEN_END
                   || (token::TOKEN_EVALerror <= tok && tok <= token::TOKEN_TOPLEVEL_STRING));
#endif
      }
#if 201103L <= YY_CPLUSPLUS
      symbol_type (int tok, std::string v, location_type l)
        : super_type (token_kind_type (tok), std::move (v), std::move (l))
#else
      symbol_type (int tok, const std::string& v, const location_type& l)
        : super_type (token_kind_type (tok), v, l)
#endif
      {
#if !defined _MSC_VER || defined __clang__
        EVAL_ASSERT ((token::TOKEN_STRING <= tok && tok <= token::TOKEN_IP_ADDRESS));
#endif
      }
    };

    /// Build a parser object.
    EvalParser (EvalContext& ctx_yyarg);
    virtual ~EvalParser ();

#if 201103L <= YY_CPLUSPLUS
    /// Non copyable.
    EvalParser (const EvalParser&) = delete;
    /// Non copyable.
    EvalParser& operator= (const EvalParser&) = delete;
#endif

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

    /// The user-facing name of the symbol whose (internal) number is
    /// YYSYMBOL.  No bounds checking.
    static std::string symbol_name (symbol_kind_type yysymbol);

    // Implementation of make_symbol for each token kind.
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
      make_EVALerror (location_type l)
      {
        return symbol_type (token::TOKEN_EVALerror, std::move (l));
      }
#else
      static
      symbol_type
      make_EVALerror (const location_type& l)
      {
        return symbol_type (token::TOKEN_EVALerror, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_EVALUNDEF (location_type l)
      {
        return symbol_type (token::TOKEN_EVALUNDEF, std::move (l));
      }
#else
      static
      symbol_type
      make_EVALUNDEF (const location_type& l)
      {
        return symbol_type (token::TOKEN_EVALUNDEF, l);
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
      make_SPLIT (location_type l)
      {
        return symbol_type (token::TOKEN_SPLIT, std::move (l));
      }
#else
      static
      symbol_type
      make_SPLIT (const location_type& l)
      {
        return symbol_type (token::TOKEN_SPLIT, l);
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
      make_PLUS (location_type l)
      {
        return symbol_type (token::TOKEN_PLUS, std::move (l));
      }
#else
      static
      symbol_type
      make_PLUS (const location_type& l)
      {
        return symbol_type (token::TOKEN_PLUS, l);
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
      make_ADDRTOTEXT (location_type l)
      {
        return symbol_type (token::TOKEN_ADDRTOTEXT, std::move (l));
      }
#else
      static
      symbol_type
      make_ADDRTOTEXT (const location_type& l)
      {
        return symbol_type (token::TOKEN_ADDRTOTEXT, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_INT8TOTEXT (location_type l)
      {
        return symbol_type (token::TOKEN_INT8TOTEXT, std::move (l));
      }
#else
      static
      symbol_type
      make_INT8TOTEXT (const location_type& l)
      {
        return symbol_type (token::TOKEN_INT8TOTEXT, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_INT16TOTEXT (location_type l)
      {
        return symbol_type (token::TOKEN_INT16TOTEXT, std::move (l));
      }
#else
      static
      symbol_type
      make_INT16TOTEXT (const location_type& l)
      {
        return symbol_type (token::TOKEN_INT16TOTEXT, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_INT32TOTEXT (location_type l)
      {
        return symbol_type (token::TOKEN_INT32TOTEXT, std::move (l));
      }
#else
      static
      symbol_type
      make_INT32TOTEXT (const location_type& l)
      {
        return symbol_type (token::TOKEN_INT32TOTEXT, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_UINT8TOTEXT (location_type l)
      {
        return symbol_type (token::TOKEN_UINT8TOTEXT, std::move (l));
      }
#else
      static
      symbol_type
      make_UINT8TOTEXT (const location_type& l)
      {
        return symbol_type (token::TOKEN_UINT8TOTEXT, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_UINT16TOTEXT (location_type l)
      {
        return symbol_type (token::TOKEN_UINT16TOTEXT, std::move (l));
      }
#else
      static
      symbol_type
      make_UINT16TOTEXT (const location_type& l)
      {
        return symbol_type (token::TOKEN_UINT16TOTEXT, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_UINT32TOTEXT (location_type l)
      {
        return symbol_type (token::TOKEN_UINT32TOTEXT, std::move (l));
      }
#else
      static
      symbol_type
      make_UINT32TOTEXT (const location_type& l)
      {
        return symbol_type (token::TOKEN_UINT32TOTEXT, l);
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


    class context
    {
    public:
      context (const EvalParser& yyparser, const symbol_type& yyla);
      const symbol_type& lookahead () const YY_NOEXCEPT { return yyla_; }
      symbol_kind_type token () const YY_NOEXCEPT { return yyla_.kind (); }
      const location_type& location () const YY_NOEXCEPT { return yyla_.location; }

      /// Put in YYARG at most YYARGN of the expected tokens, and return the
      /// number of tokens stored in YYARG.  If YYARG is null, return the
      /// number of expected tokens (guaranteed to be less than YYNTOKENS).
      int expected_tokens (symbol_kind_type yyarg[], int yyargn) const;

    private:
      const EvalParser& yyparser_;
      const symbol_type& yyla_;
    };

  private:
#if YY_CPLUSPLUS < 201103L
    /// Non copyable.
    EvalParser (const EvalParser&);
    /// Non copyable.
    EvalParser& operator= (const EvalParser&);
#endif


    /// Stored state numbers (used for stacks).
    typedef unsigned char state_type;

    /// The arguments of the error message.
    int yy_syntax_error_arguments_ (const context& yyctx,
                                    symbol_kind_type yyarg[], int yyargn) const;

    /// Generate an error message.
    /// \param yyctx     the context in which the error occurred.
    virtual std::string yysyntax_error_ (const context& yyctx) const;
    /// Compute post-reduction state.
    /// \param yystate   the current state
    /// \param yysym     the nonterminal to push on the stack
    static state_type yy_lr_goto_state_ (state_type yystate, int yysym);

    /// Whether the given \c yypact_ value indicates a defaulted state.
    /// \param yyvalue   the value to check
    static bool yy_pact_value_is_default_ (int yyvalue) YY_NOEXCEPT;

    /// Whether the given \c yytable_ value indicates a syntax error.
    /// \param yyvalue   the value to check
    static bool yy_table_value_is_error_ (int yyvalue) YY_NOEXCEPT;

    static const short yypact_ninf_;
    static const signed char yytable_ninf_;

    /// Convert a scanner token kind \a t to a symbol kind.
    /// In theory \a t should be a token_kind_type, but character literals
    /// are valid, yet not members of the token_kind_type enum.
    static symbol_kind_type yytranslate_ (int t) YY_NOEXCEPT;

    /// Convert the symbol name \a n to a form suitable for a diagnostic.
    static std::string yytnamerr_ (const char *yystr);

    /// For a symbol, its name in clear.
    static const char* const yytname_[];


    // Tables.
    // YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
    // STATE-NUM.
    static const short yypact_[];

    // YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
    // Performed when YYTABLE does not specify something else to do.  Zero
    // means the default is an error.
    static const signed char yydefact_[];

    // YYPGOTO[NTERM-NUM].
    static const short yypgoto_[];

    // YYDEFGOTO[NTERM-NUM].
    static const unsigned char yydefgoto_[];

    // YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
    // positive, shift that token.  If negative, reduce the rule whose
    // number is the opposite.  If YYTABLE_NINF, syntax error.
    static const unsigned char yytable_[];

    static const short yycheck_[];

    // YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
    // state STATE-NUM.
    static const signed char yystos_[];

    // YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.
    static const signed char yyr1_[];

    // YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.
    static const signed char yyr2_[];


#if EVALDEBUG
    // YYRLINE[YYN] -- Source line where rule number YYN was defined.
    static const short yyrline_[];
    /// Report on the debug stream that the rule \a r is going to be reduced.
    virtual void yy_reduce_print_ (int r) const;
    /// Print the state stack on the debug stream.
    virtual void yy_stack_print_ () const;

    /// Debugging level.
    int yydebug_;
    /// Debug stream.
    std::ostream* yycdebug_;

    /// \brief Display a symbol kind, value and location.
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

      /// The symbol kind as needed by the constructor.
      typedef state_type kind_type;

      /// Constructor.
      by_state (kind_type s) YY_NOEXCEPT;

      /// Copy constructor.
      by_state (const by_state& that) YY_NOEXCEPT;

      /// Record that this symbol is empty.
      void clear () YY_NOEXCEPT;

      /// Steal the symbol kind from \a that.
      void move (by_state& that);

      /// The symbol kind (corresponding to \a state).
      /// \a symbol_kind::S_YYEMPTY when empty.
      symbol_kind_type kind () const YY_NOEXCEPT;

      /// The state number used to denote an empty symbol.
      /// We use the initial state, as it does not have a value.
      enum { empty_state = 0 };

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

      /// Assignment, needed by push_back by other implementations.
      /// Needed by some other old implementations.
      stack_symbol_type& operator= (const stack_symbol_type& that);
#endif
    };

    /// A stack with random access from its top.
    template <typename T, typename S = std::vector<T> >
    class stack
    {
    public:
      // Hide our reversed order.
      typedef typename S::iterator iterator;
      typedef typename S::const_iterator const_iterator;
      typedef typename S::size_type size_type;
      typedef typename std::ptrdiff_t index_type;

      stack (size_type n = 200) YY_NOEXCEPT
        : seq_ (n)
      {}

#if 201103L <= YY_CPLUSPLUS
      /// Non copyable.
      stack (const stack&) = delete;
      /// Non copyable.
      stack& operator= (const stack&) = delete;
#endif

      /// Random access.
      ///
      /// Index 0 returns the topmost element.
      const T&
      operator[] (index_type i) const
      {
        return seq_[size_type (size () - 1 - i)];
      }

      /// Random access.
      ///
      /// Index 0 returns the topmost element.
      T&
      operator[] (index_type i)
      {
        return seq_[size_type (size () - 1 - i)];
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
      pop (std::ptrdiff_t n = 1) YY_NOEXCEPT
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
      index_type
      size () const YY_NOEXCEPT
      {
        return index_type (seq_.size ());
      }

      /// Iterator on top of the stack (going downwards).
      const_iterator
      begin () const YY_NOEXCEPT
      {
        return seq_.begin ();
      }

      /// Bottom of the stack.
      const_iterator
      end () const YY_NOEXCEPT
      {
        return seq_.end ();
      }

      /// Present a slice of the top of a stack.
      class slice
      {
      public:
        slice (const stack& stack, index_type range) YY_NOEXCEPT
          : stack_ (stack)
          , range_ (range)
        {}

        const T&
        operator[] (index_type i) const
        {
          return stack_[range_ - i];
        }

      private:
        const stack& stack_;
        index_type range_;
      };

    private:
#if YY_CPLUSPLUS < 201103L
      /// Non copyable.
      stack (const stack&);
      /// Non copyable.
      stack& operator= (const stack&);
#endif
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
    void yypop_ (int n = 1) YY_NOEXCEPT;

    /// Constants.
    enum
    {
      yylast_ = 286,     ///< Last index in yytable_.
      yynnts_ = 18,  ///< Number of nonterminal symbols.
      yyfinal_ = 42 ///< Termination state number.
    };


    // User arguments.
    EvalContext& ctx;

  };

  inline
  EvalParser::symbol_kind_type
  EvalParser::yytranslate_ (int t) YY_NOEXCEPT
  {
    // YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to
    // TOKEN-NUM as returned by yylex.
    static
    const signed char
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
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63
    };
    // Last valid token kind.
    const int code_max = 318;

    if (t <= 0)
      return symbol_kind::S_YYEOF;
    else if (t <= code_max)
      return static_cast <symbol_kind_type> (translate_table[t]);
    else
      return symbol_kind::S_YYUNDEF;
  }

  // basic_symbol.
  template <typename Base>
  EvalParser::basic_symbol<Base>::basic_symbol (const basic_symbol& that)
    : Base (that)
    , value ()
    , location (that.location)
  {
    switch (this->kind ())
    {
      case symbol_kind::S_option_repr_type: // option_repr_type
        value.copy< TokenOption::RepresentationType > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_pkt4_field: // pkt4_field
        value.copy< TokenPkt4::FieldType > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_pkt6_field: // pkt6_field
        value.copy< TokenPkt6::FieldType > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_pkt_metadata: // pkt_metadata
        value.copy< TokenPkt::MetadataType > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_relay6_field: // relay6_field
        value.copy< TokenRelay6Field::FieldType > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_nest_level: // nest_level
        value.copy< int8_t > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_STRING: // "constant string"
      case symbol_kind::S_INTEGER: // "integer"
      case symbol_kind::S_HEXSTRING: // "constant hexstring"
      case symbol_kind::S_OPTION_NAME: // "option name"
      case symbol_kind::S_IP_ADDRESS: // "ip address"
        value.copy< std::string > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_option_code: // option_code
      case symbol_kind::S_sub_option_code: // sub_option_code
        value.copy< uint16_t > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_integer_expr: // integer_expr
      case symbol_kind::S_enterprise_id: // enterprise_id
        value.copy< uint32_t > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

  }




  template <typename Base>
  EvalParser::symbol_kind_type
  EvalParser::basic_symbol<Base>::type_get () const YY_NOEXCEPT
  {
    return this->kind ();
  }


  template <typename Base>
  bool
  EvalParser::basic_symbol<Base>::empty () const YY_NOEXCEPT
  {
    return this->kind () == symbol_kind::S_YYEMPTY;
  }

  template <typename Base>
  void
  EvalParser::basic_symbol<Base>::move (basic_symbol& s)
  {
    super_type::move (s);
    switch (this->kind ())
    {
      case symbol_kind::S_option_repr_type: // option_repr_type
        value.move< TokenOption::RepresentationType > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_pkt4_field: // pkt4_field
        value.move< TokenPkt4::FieldType > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_pkt6_field: // pkt6_field
        value.move< TokenPkt6::FieldType > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_pkt_metadata: // pkt_metadata
        value.move< TokenPkt::MetadataType > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_relay6_field: // relay6_field
        value.move< TokenRelay6Field::FieldType > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_nest_level: // nest_level
        value.move< int8_t > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_STRING: // "constant string"
      case symbol_kind::S_INTEGER: // "integer"
      case symbol_kind::S_HEXSTRING: // "constant hexstring"
      case symbol_kind::S_OPTION_NAME: // "option name"
      case symbol_kind::S_IP_ADDRESS: // "ip address"
        value.move< std::string > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_option_code: // option_code
      case symbol_kind::S_sub_option_code: // sub_option_code
        value.move< uint16_t > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_integer_expr: // integer_expr
      case symbol_kind::S_enterprise_id: // enterprise_id
        value.move< uint32_t > (YY_MOVE (s.value));
        break;

      default:
        break;
    }

    location = YY_MOVE (s.location);
  }

  // by_kind.
  inline
  EvalParser::by_kind::by_kind () YY_NOEXCEPT
    : kind_ (symbol_kind::S_YYEMPTY)
  {}

#if 201103L <= YY_CPLUSPLUS
  inline
  EvalParser::by_kind::by_kind (by_kind&& that) YY_NOEXCEPT
    : kind_ (that.kind_)
  {
    that.clear ();
  }
#endif

  inline
  EvalParser::by_kind::by_kind (const by_kind& that) YY_NOEXCEPT
    : kind_ (that.kind_)
  {}

  inline
  EvalParser::by_kind::by_kind (token_kind_type t) YY_NOEXCEPT
    : kind_ (yytranslate_ (t))
  {}



  inline
  void
  EvalParser::by_kind::clear () YY_NOEXCEPT
  {
    kind_ = symbol_kind::S_YYEMPTY;
  }

  inline
  void
  EvalParser::by_kind::move (by_kind& that)
  {
    kind_ = that.kind_;
    that.clear ();
  }

  inline
  EvalParser::symbol_kind_type
  EvalParser::by_kind::kind () const YY_NOEXCEPT
  {
    return kind_;
  }


  inline
  EvalParser::symbol_kind_type
  EvalParser::by_kind::type_get () const YY_NOEXCEPT
  {
    return this->kind ();
  }


#line 14 "parser.yy"
} } // isc::eval
#line 2673 "parser.h"




#endif // !YY_EVAL_PARSER_H_INCLUDED
