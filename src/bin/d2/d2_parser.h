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
 ** \file d2_parser.h
 ** Define the isc::d2::parser class.
 */

// C++ LALR(1) parser skeleton written by Akim Demaille.

// DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
// especially those whose name start with YY_ or yy_.  They are
// private implementation details that can be changed or removed.

#ifndef YY_D2_PARSER_D2_PARSER_H_INCLUDED
# define YY_D2_PARSER_D2_PARSER_H_INCLUDED
// "%code requires" blocks.
#line 17 "d2_parser.yy"

#include <config.h>
#include <string>
#include <cc/data.h>
#include <d2srv/d2_config.h>
#include <boost/lexical_cast.hpp>
#include <d2/parser_context_decl.h>

using namespace isc::d2;
using namespace isc::data;
using namespace std;

#line 62 "d2_parser.h"

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
#ifndef D2_PARSER__ASSERT
# include <cassert>
# define D2_PARSER__ASSERT assert
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
#ifndef D2_PARSER_DEBUG
# if defined YYDEBUG
#if YYDEBUG
#   define D2_PARSER_DEBUG 1
#  else
#   define D2_PARSER_DEBUG 0
#  endif
# else /* ! defined YYDEBUG */
#  define D2_PARSER_DEBUG 1
# endif /* ! defined YYDEBUG */
#endif  /* ! defined D2_PARSER_DEBUG */

#line 14 "d2_parser.yy"
namespace isc { namespace d2 {
#line 211 "d2_parser.h"




  /// A Bison parser.
  class D2Parser
  {
  public:
#ifdef D2_PARSER_STYPE
# ifdef __GNUC__
#  pragma GCC message "bison: do not #define D2_PARSER_STYPE in C++, use %define api.value.type"
# endif
    typedef D2_PARSER_STYPE value_type;
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
      D2_PARSER__ASSERT (sizeof (T) <= size);
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
      D2_PARSER__ASSERT (!yytypeid_);
    }

# if 201103L <= YY_CPLUSPLUS
    /// Instantiate a \a T in here from \a t.
    template <typename T, typename... U>
    T&
    emplace (U&&... u)
    {
      D2_PARSER__ASSERT (!yytypeid_);
      D2_PARSER__ASSERT (sizeof (T) <= size);
      yytypeid_ = & typeid (T);
      return *new (yyas_<T> ()) T (std::forward <U>(u)...);
    }
# else
    /// Instantiate an empty \a T in here.
    template <typename T>
    T&
    emplace ()
    {
      D2_PARSER__ASSERT (!yytypeid_);
      D2_PARSER__ASSERT (sizeof (T) <= size);
      yytypeid_ = & typeid (T);
      return *new (yyas_<T> ()) T ();
    }

    /// Instantiate a \a T in here from \a t.
    template <typename T>
    T&
    emplace (const T& t)
    {
      D2_PARSER__ASSERT (!yytypeid_);
      D2_PARSER__ASSERT (sizeof (T) <= size);
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
      D2_PARSER__ASSERT (yytypeid_);
      D2_PARSER__ASSERT (*yytypeid_ == typeid (T));
      D2_PARSER__ASSERT (sizeof (T) <= size);
      return *yyas_<T> ();
    }

    /// Const accessor to a built \a T (for %printer).
    template <typename T>
    const T&
    as () const YY_NOEXCEPT
    {
      D2_PARSER__ASSERT (yytypeid_);
      D2_PARSER__ASSERT (*yytypeid_ == typeid (T));
      D2_PARSER__ASSERT (sizeof (T) <= size);
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
      D2_PARSER__ASSERT (yytypeid_);
      D2_PARSER__ASSERT (*yytypeid_ == *that.yytypeid_);
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
      // value
      // map_value
      // ncr_protocol_value
      // control_socket_type_value
      // auth_type_value
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
        TOKEN_D2_PARSER_EMPTY = -2,
    TOKEN_END = 0,                 // "end of file"
    TOKEN_D2_PARSER_error = 256,   // error
    TOKEN_D2_PARSER_UNDEF = 257,   // "invalid token"
    TOKEN_COMMA = 258,             // ","
    TOKEN_COLON = 259,             // ":"
    TOKEN_LSQUARE_BRACKET = 260,   // "["
    TOKEN_RSQUARE_BRACKET = 261,   // "]"
    TOKEN_LCURLY_BRACKET = 262,    // "{"
    TOKEN_RCURLY_BRACKET = 263,    // "}"
    TOKEN_NULL_TYPE = 264,         // "null"
    TOKEN_DHCPDDNS = 265,          // "DhcpDdns"
    TOKEN_IP_ADDRESS = 266,        // "ip-address"
    TOKEN_PORT = 267,              // "port"
    TOKEN_DNS_SERVER_TIMEOUT = 268, // "dns-server-timeout"
    TOKEN_NCR_PROTOCOL = 269,      // "ncr-protocol"
    TOKEN_UDP = 270,               // "UDP"
    TOKEN_TCP = 271,               // "TCP"
    TOKEN_NCR_FORMAT = 272,        // "ncr-format"
    TOKEN_JSON = 273,              // "JSON"
    TOKEN_USER_CONTEXT = 274,      // "user-context"
    TOKEN_COMMENT = 275,           // "comment"
    TOKEN_FORWARD_DDNS = 276,      // "forward-ddns"
    TOKEN_REVERSE_DDNS = 277,      // "reverse-ddns"
    TOKEN_DDNS_DOMAINS = 278,      // "ddns-domains"
    TOKEN_KEY_NAME = 279,          // "key-name"
    TOKEN_DNS_SERVERS = 280,       // "dns-servers"
    TOKEN_HOSTNAME = 281,          // "hostname"
    TOKEN_TSIG_KEYS = 282,         // "tsig-keys"
    TOKEN_ALGORITHM = 283,         // "algorithm"
    TOKEN_DIGEST_BITS = 284,       // "digest-bits"
    TOKEN_SECRET = 285,            // "secret"
    TOKEN_SECRET_FILE = 286,       // "secret-file"
    TOKEN_CONTROL_SOCKET = 287,    // "control-socket"
    TOKEN_CONTROL_SOCKETS = 288,   // "control-sockets"
    TOKEN_SOCKET_TYPE = 289,       // "socket-type"
    TOKEN_UNIX = 290,              // "unix"
    TOKEN_HTTP = 291,              // "http"
    TOKEN_HTTPS = 292,             // "https"
    TOKEN_SOCKET_NAME = 293,       // "socket-name"
    TOKEN_SOCKET_ADDRESS = 294,    // "socket-address"
    TOKEN_SOCKET_PORT = 295,       // "socket-port"
    TOKEN_AUTHENTICATION = 296,    // "authentication"
    TOKEN_TYPE = 297,              // "type"
    TOKEN_BASIC = 298,             // "basic"
    TOKEN_REALM = 299,             // "realm"
    TOKEN_DIRECTORY = 300,         // "directory"
    TOKEN_CLIENTS = 301,           // "clients"
    TOKEN_USER = 302,              // "user"
    TOKEN_USER_FILE = 303,         // "user-file"
    TOKEN_PASSWORD = 304,          // "password"
    TOKEN_PASSWORD_FILE = 305,     // "password-file"
    TOKEN_TRUST_ANCHOR = 306,      // "trust-anchor"
    TOKEN_CERT_FILE = 307,         // "cert-file"
    TOKEN_KEY_FILE = 308,          // "key-file"
    TOKEN_CERT_REQUIRED = 309,     // "cert-required"
    TOKEN_HOOKS_LIBRARIES = 310,   // "hooks-libraries"
    TOKEN_LIBRARY = 311,           // "library"
    TOKEN_PARAMETERS = 312,        // "parameters"
    TOKEN_LOGGERS = 313,           // "loggers"
    TOKEN_NAME = 314,              // "name"
    TOKEN_OUTPUT_OPTIONS = 315,    // "output-options"
    TOKEN_OUTPUT = 316,            // "output"
    TOKEN_DEBUGLEVEL = 317,        // "debuglevel"
    TOKEN_SEVERITY = 318,          // "severity"
    TOKEN_FLUSH = 319,             // "flush"
    TOKEN_MAXSIZE = 320,           // "maxsize"
    TOKEN_MAXVER = 321,            // "maxver"
    TOKEN_PATTERN = 322,           // "pattern"
    TOKEN_TOPLEVEL_JSON = 323,     // TOPLEVEL_JSON
    TOKEN_TOPLEVEL_DHCPDDNS = 324, // TOPLEVEL_DHCPDDNS
    TOKEN_SUB_DHCPDDNS = 325,      // SUB_DHCPDDNS
    TOKEN_SUB_TSIG_KEY = 326,      // SUB_TSIG_KEY
    TOKEN_SUB_TSIG_KEYS = 327,     // SUB_TSIG_KEYS
    TOKEN_SUB_DDNS_DOMAIN = 328,   // SUB_DDNS_DOMAIN
    TOKEN_SUB_DDNS_DOMAINS = 329,  // SUB_DDNS_DOMAINS
    TOKEN_SUB_DNS_SERVER = 330,    // SUB_DNS_SERVER
    TOKEN_SUB_DNS_SERVERS = 331,   // SUB_DNS_SERVERS
    TOKEN_SUB_HOOKS_LIBRARY = 332, // SUB_HOOKS_LIBRARY
    TOKEN_STRING = 333,            // "constant string"
    TOKEN_INTEGER = 334,           // "integer"
    TOKEN_FLOAT = 335,             // "floating point"
    TOKEN_BOOLEAN = 336            // "boolean"
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
        YYNTOKENS = 82, ///< Number of tokens.
        S_YYEMPTY = -2,
        S_YYEOF = 0,                             // "end of file"
        S_YYerror = 1,                           // error
        S_YYUNDEF = 2,                           // "invalid token"
        S_COMMA = 3,                             // ","
        S_COLON = 4,                             // ":"
        S_LSQUARE_BRACKET = 5,                   // "["
        S_RSQUARE_BRACKET = 6,                   // "]"
        S_LCURLY_BRACKET = 7,                    // "{"
        S_RCURLY_BRACKET = 8,                    // "}"
        S_NULL_TYPE = 9,                         // "null"
        S_DHCPDDNS = 10,                         // "DhcpDdns"
        S_IP_ADDRESS = 11,                       // "ip-address"
        S_PORT = 12,                             // "port"
        S_DNS_SERVER_TIMEOUT = 13,               // "dns-server-timeout"
        S_NCR_PROTOCOL = 14,                     // "ncr-protocol"
        S_UDP = 15,                              // "UDP"
        S_TCP = 16,                              // "TCP"
        S_NCR_FORMAT = 17,                       // "ncr-format"
        S_JSON = 18,                             // "JSON"
        S_USER_CONTEXT = 19,                     // "user-context"
        S_COMMENT = 20,                          // "comment"
        S_FORWARD_DDNS = 21,                     // "forward-ddns"
        S_REVERSE_DDNS = 22,                     // "reverse-ddns"
        S_DDNS_DOMAINS = 23,                     // "ddns-domains"
        S_KEY_NAME = 24,                         // "key-name"
        S_DNS_SERVERS = 25,                      // "dns-servers"
        S_HOSTNAME = 26,                         // "hostname"
        S_TSIG_KEYS = 27,                        // "tsig-keys"
        S_ALGORITHM = 28,                        // "algorithm"
        S_DIGEST_BITS = 29,                      // "digest-bits"
        S_SECRET = 30,                           // "secret"
        S_SECRET_FILE = 31,                      // "secret-file"
        S_CONTROL_SOCKET = 32,                   // "control-socket"
        S_CONTROL_SOCKETS = 33,                  // "control-sockets"
        S_SOCKET_TYPE = 34,                      // "socket-type"
        S_UNIX = 35,                             // "unix"
        S_HTTP = 36,                             // "http"
        S_HTTPS = 37,                            // "https"
        S_SOCKET_NAME = 38,                      // "socket-name"
        S_SOCKET_ADDRESS = 39,                   // "socket-address"
        S_SOCKET_PORT = 40,                      // "socket-port"
        S_AUTHENTICATION = 41,                   // "authentication"
        S_TYPE = 42,                             // "type"
        S_BASIC = 43,                            // "basic"
        S_REALM = 44,                            // "realm"
        S_DIRECTORY = 45,                        // "directory"
        S_CLIENTS = 46,                          // "clients"
        S_USER = 47,                             // "user"
        S_USER_FILE = 48,                        // "user-file"
        S_PASSWORD = 49,                         // "password"
        S_PASSWORD_FILE = 50,                    // "password-file"
        S_TRUST_ANCHOR = 51,                     // "trust-anchor"
        S_CERT_FILE = 52,                        // "cert-file"
        S_KEY_FILE = 53,                         // "key-file"
        S_CERT_REQUIRED = 54,                    // "cert-required"
        S_HOOKS_LIBRARIES = 55,                  // "hooks-libraries"
        S_LIBRARY = 56,                          // "library"
        S_PARAMETERS = 57,                       // "parameters"
        S_LOGGERS = 58,                          // "loggers"
        S_NAME = 59,                             // "name"
        S_OUTPUT_OPTIONS = 60,                   // "output-options"
        S_OUTPUT = 61,                           // "output"
        S_DEBUGLEVEL = 62,                       // "debuglevel"
        S_SEVERITY = 63,                         // "severity"
        S_FLUSH = 64,                            // "flush"
        S_MAXSIZE = 65,                          // "maxsize"
        S_MAXVER = 66,                           // "maxver"
        S_PATTERN = 67,                          // "pattern"
        S_TOPLEVEL_JSON = 68,                    // TOPLEVEL_JSON
        S_TOPLEVEL_DHCPDDNS = 69,                // TOPLEVEL_DHCPDDNS
        S_SUB_DHCPDDNS = 70,                     // SUB_DHCPDDNS
        S_SUB_TSIG_KEY = 71,                     // SUB_TSIG_KEY
        S_SUB_TSIG_KEYS = 72,                    // SUB_TSIG_KEYS
        S_SUB_DDNS_DOMAIN = 73,                  // SUB_DDNS_DOMAIN
        S_SUB_DDNS_DOMAINS = 74,                 // SUB_DDNS_DOMAINS
        S_SUB_DNS_SERVER = 75,                   // SUB_DNS_SERVER
        S_SUB_DNS_SERVERS = 76,                  // SUB_DNS_SERVERS
        S_SUB_HOOKS_LIBRARY = 77,                // SUB_HOOKS_LIBRARY
        S_STRING = 78,                           // "constant string"
        S_INTEGER = 79,                          // "integer"
        S_FLOAT = 80,                            // "floating point"
        S_BOOLEAN = 81,                          // "boolean"
        S_YYACCEPT = 82,                         // $accept
        S_start = 83,                            // start
        S_84_1 = 84,                             // $@1
        S_85_2 = 85,                             // $@2
        S_86_3 = 86,                             // $@3
        S_87_4 = 87,                             // $@4
        S_88_5 = 88,                             // $@5
        S_89_6 = 89,                             // $@6
        S_90_7 = 90,                             // $@7
        S_91_8 = 91,                             // $@8
        S_92_9 = 92,                             // $@9
        S_93_10 = 93,                            // $@10
        S_value = 94,                            // value
        S_sub_json = 95,                         // sub_json
        S_map2 = 96,                             // map2
        S_97_11 = 97,                            // $@11
        S_map_value = 98,                        // map_value
        S_map_content = 99,                      // map_content
        S_not_empty_map = 100,                   // not_empty_map
        S_list_generic = 101,                    // list_generic
        S_102_12 = 102,                          // $@12
        S_list_content = 103,                    // list_content
        S_not_empty_list = 104,                  // not_empty_list
        S_unknown_map_entry = 105,               // unknown_map_entry
        S_syntax_map = 106,                      // syntax_map
        S_107_13 = 107,                          // $@13
        S_global_object = 108,                   // global_object
        S_109_14 = 109,                          // $@14
        S_global_object_comma = 110,             // global_object_comma
        S_sub_dhcpddns = 111,                    // sub_dhcpddns
        S_112_15 = 112,                          // $@15
        S_dhcpddns_params = 113,                 // dhcpddns_params
        S_dhcpddns_param = 114,                  // dhcpddns_param
        S_ip_address = 115,                      // ip_address
        S_116_16 = 116,                          // $@16
        S_port = 117,                            // port
        S_dns_server_timeout = 118,              // dns_server_timeout
        S_ncr_protocol = 119,                    // ncr_protocol
        S_120_17 = 120,                          // $@17
        S_ncr_protocol_value = 121,              // ncr_protocol_value
        S_ncr_format = 122,                      // ncr_format
        S_123_18 = 123,                          // $@18
        S_user_context = 124,                    // user_context
        S_125_19 = 125,                          // $@19
        S_comment = 126,                         // comment
        S_127_20 = 127,                          // $@20
        S_forward_ddns = 128,                    // forward_ddns
        S_129_21 = 129,                          // $@21
        S_reverse_ddns = 130,                    // reverse_ddns
        S_131_22 = 131,                          // $@22
        S_ddns_mgr_params = 132,                 // ddns_mgr_params
        S_not_empty_ddns_mgr_params = 133,       // not_empty_ddns_mgr_params
        S_ddns_mgr_param = 134,                  // ddns_mgr_param
        S_ddns_domains = 135,                    // ddns_domains
        S_136_23 = 136,                          // $@23
        S_sub_ddns_domains = 137,                // sub_ddns_domains
        S_138_24 = 138,                          // $@24
        S_ddns_domain_list = 139,                // ddns_domain_list
        S_not_empty_ddns_domain_list = 140,      // not_empty_ddns_domain_list
        S_ddns_domain = 141,                     // ddns_domain
        S_142_25 = 142,                          // $@25
        S_sub_ddns_domain = 143,                 // sub_ddns_domain
        S_144_26 = 144,                          // $@26
        S_ddns_domain_params = 145,              // ddns_domain_params
        S_ddns_domain_param = 146,               // ddns_domain_param
        S_ddns_domain_name = 147,                // ddns_domain_name
        S_148_27 = 148,                          // $@27
        S_ddns_key_name = 149,                   // ddns_key_name
        S_150_28 = 150,                          // $@28
        S_dns_servers = 151,                     // dns_servers
        S_152_29 = 152,                          // $@29
        S_sub_dns_servers = 153,                 // sub_dns_servers
        S_154_30 = 154,                          // $@30
        S_dns_server_list = 155,                 // dns_server_list
        S_dns_server = 156,                      // dns_server
        S_157_31 = 157,                          // $@31
        S_sub_dns_server = 158,                  // sub_dns_server
        S_159_32 = 159,                          // $@32
        S_dns_server_params = 160,               // dns_server_params
        S_dns_server_param = 161,                // dns_server_param
        S_dns_server_hostname = 162,             // dns_server_hostname
        S_163_33 = 163,                          // $@33
        S_dns_server_ip_address = 164,           // dns_server_ip_address
        S_165_34 = 165,                          // $@34
        S_dns_server_port = 166,                 // dns_server_port
        S_tsig_keys = 167,                       // tsig_keys
        S_168_35 = 168,                          // $@35
        S_sub_tsig_keys = 169,                   // sub_tsig_keys
        S_170_36 = 170,                          // $@36
        S_tsig_keys_list = 171,                  // tsig_keys_list
        S_not_empty_tsig_keys_list = 172,        // not_empty_tsig_keys_list
        S_tsig_key = 173,                        // tsig_key
        S_174_37 = 174,                          // $@37
        S_sub_tsig_key = 175,                    // sub_tsig_key
        S_176_38 = 176,                          // $@38
        S_tsig_key_params = 177,                 // tsig_key_params
        S_tsig_key_param = 178,                  // tsig_key_param
        S_tsig_key_name = 179,                   // tsig_key_name
        S_180_39 = 180,                          // $@39
        S_tsig_key_algorithm = 181,              // tsig_key_algorithm
        S_182_40 = 182,                          // $@40
        S_tsig_key_digest_bits = 183,            // tsig_key_digest_bits
        S_tsig_key_secret = 184,                 // tsig_key_secret
        S_185_41 = 185,                          // $@41
        S_tsig_key_secret_file = 186,            // tsig_key_secret_file
        S_187_42 = 187,                          // $@42
        S_control_socket = 188,                  // control_socket
        S_189_43 = 189,                          // $@43
        S_control_sockets = 190,                 // control_sockets
        S_191_44 = 191,                          // $@44
        S_control_socket_list = 192,             // control_socket_list
        S_not_empty_control_socket_list = 193,   // not_empty_control_socket_list
        S_control_socket_entry = 194,            // control_socket_entry
        S_195_45 = 195,                          // $@45
        S_control_socket_params = 196,           // control_socket_params
        S_control_socket_param = 197,            // control_socket_param
        S_control_socket_type = 198,             // control_socket_type
        S_199_46 = 199,                          // $@46
        S_control_socket_type_value = 200,       // control_socket_type_value
        S_control_socket_name = 201,             // control_socket_name
        S_202_47 = 202,                          // $@47
        S_control_socket_address = 203,          // control_socket_address
        S_204_48 = 204,                          // $@48
        S_control_socket_port = 205,             // control_socket_port
        S_trust_anchor = 206,                    // trust_anchor
        S_207_49 = 207,                          // $@49
        S_cert_file = 208,                       // cert_file
        S_209_50 = 209,                          // $@50
        S_key_file = 210,                        // key_file
        S_211_51 = 211,                          // $@51
        S_cert_required = 212,                   // cert_required
        S_authentication = 213,                  // authentication
        S_214_52 = 214,                          // $@52
        S_auth_params = 215,                     // auth_params
        S_auth_param = 216,                      // auth_param
        S_auth_type = 217,                       // auth_type
        S_218_53 = 218,                          // $@53
        S_auth_type_value = 219,                 // auth_type_value
        S_realm = 220,                           // realm
        S_221_54 = 221,                          // $@54
        S_directory = 222,                       // directory
        S_223_55 = 223,                          // $@55
        S_clients = 224,                         // clients
        S_225_56 = 225,                          // $@56
        S_clients_list = 226,                    // clients_list
        S_not_empty_clients_list = 227,          // not_empty_clients_list
        S_basic_auth = 228,                      // basic_auth
        S_229_57 = 229,                          // $@57
        S_clients_params = 230,                  // clients_params
        S_clients_param = 231,                   // clients_param
        S_user = 232,                            // user
        S_233_58 = 233,                          // $@58
        S_user_file = 234,                       // user_file
        S_235_59 = 235,                          // $@59
        S_password = 236,                        // password
        S_237_60 = 237,                          // $@60
        S_password_file = 238,                   // password_file
        S_239_61 = 239,                          // $@61
        S_hooks_libraries = 240,                 // hooks_libraries
        S_241_62 = 241,                          // $@62
        S_hooks_libraries_list = 242,            // hooks_libraries_list
        S_not_empty_hooks_libraries_list = 243,  // not_empty_hooks_libraries_list
        S_hooks_library = 244,                   // hooks_library
        S_245_63 = 245,                          // $@63
        S_sub_hooks_library = 246,               // sub_hooks_library
        S_247_64 = 247,                          // $@64
        S_hooks_params = 248,                    // hooks_params
        S_hooks_param = 249,                     // hooks_param
        S_library = 250,                         // library
        S_251_65 = 251,                          // $@65
        S_parameters = 252,                      // parameters
        S_253_66 = 253,                          // $@66
        S_loggers = 254,                         // loggers
        S_255_67 = 255,                          // $@67
        S_loggers_entries = 256,                 // loggers_entries
        S_logger_entry = 257,                    // logger_entry
        S_258_68 = 258,                          // $@68
        S_logger_params = 259,                   // logger_params
        S_logger_param = 260,                    // logger_param
        S_name = 261,                            // name
        S_262_69 = 262,                          // $@69
        S_debuglevel = 263,                      // debuglevel
        S_severity = 264,                        // severity
        S_265_70 = 265,                          // $@70
        S_output_options_list = 266,             // output_options_list
        S_267_71 = 267,                          // $@71
        S_output_options_list_content = 268,     // output_options_list_content
        S_output_entry = 269,                    // output_entry
        S_270_72 = 270,                          // $@72
        S_output_params_list = 271,              // output_params_list
        S_output_params = 272,                   // output_params
        S_output = 273,                          // output
        S_274_73 = 274,                          // $@73
        S_flush = 275,                           // flush
        S_maxsize = 276,                         // maxsize
        S_maxver = 277,                          // maxver
        S_pattern = 278,                         // pattern
        S_279_74 = 279                           // $@74
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
      case symbol_kind::S_value: // value
      case symbol_kind::S_map_value: // map_value
      case symbol_kind::S_ncr_protocol_value: // ncr_protocol_value
      case symbol_kind::S_control_socket_type_value: // control_socket_type_value
      case symbol_kind::S_auth_type_value: // auth_type_value
        value.move< ElementPtr > (std::move (that.value));
        break;

      case symbol_kind::S_BOOLEAN: // "boolean"
        value.move< bool > (std::move (that.value));
        break;

      case symbol_kind::S_FLOAT: // "floating point"
        value.move< double > (std::move (that.value));
        break;

      case symbol_kind::S_INTEGER: // "integer"
        value.move< int64_t > (std::move (that.value));
        break;

      case symbol_kind::S_STRING: // "constant string"
        value.move< std::string > (std::move (that.value));
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
      basic_symbol (typename Base::kind_type t, ElementPtr&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const ElementPtr& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, bool&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const bool& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, double&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const double& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, int64_t&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const int64_t& v, const location_type& l)
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
      case symbol_kind::S_value: // value
      case symbol_kind::S_map_value: // map_value
      case symbol_kind::S_ncr_protocol_value: // ncr_protocol_value
      case symbol_kind::S_control_socket_type_value: // control_socket_type_value
      case symbol_kind::S_auth_type_value: // auth_type_value
        value.template destroy< ElementPtr > ();
        break;

      case symbol_kind::S_BOOLEAN: // "boolean"
        value.template destroy< bool > ();
        break;

      case symbol_kind::S_FLOAT: // "floating point"
        value.template destroy< double > ();
        break;

      case symbol_kind::S_INTEGER: // "integer"
        value.template destroy< int64_t > ();
        break;

      case symbol_kind::S_STRING: // "constant string"
        value.template destroy< std::string > ();
        break;

      default:
        break;
    }

        Base::clear ();
      }

      /// The user-facing name of this symbol.
      std::string name () const YY_NOEXCEPT
      {
        return D2Parser::symbol_name (this->kind ());
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
        D2_PARSER__ASSERT (tok == token::TOKEN_END
                   || (token::TOKEN_D2_PARSER_error <= tok && tok <= token::TOKEN_SUB_HOOKS_LIBRARY));
#endif
      }
#if 201103L <= YY_CPLUSPLUS
      symbol_type (int tok, bool v, location_type l)
        : super_type (token_kind_type (tok), std::move (v), std::move (l))
#else
      symbol_type (int tok, const bool& v, const location_type& l)
        : super_type (token_kind_type (tok), v, l)
#endif
      {
#if !defined _MSC_VER || defined __clang__
        D2_PARSER__ASSERT (tok == token::TOKEN_BOOLEAN);
#endif
      }
#if 201103L <= YY_CPLUSPLUS
      symbol_type (int tok, double v, location_type l)
        : super_type (token_kind_type (tok), std::move (v), std::move (l))
#else
      symbol_type (int tok, const double& v, const location_type& l)
        : super_type (token_kind_type (tok), v, l)
#endif
      {
#if !defined _MSC_VER || defined __clang__
        D2_PARSER__ASSERT (tok == token::TOKEN_FLOAT);
#endif
      }
#if 201103L <= YY_CPLUSPLUS
      symbol_type (int tok, int64_t v, location_type l)
        : super_type (token_kind_type (tok), std::move (v), std::move (l))
#else
      symbol_type (int tok, const int64_t& v, const location_type& l)
        : super_type (token_kind_type (tok), v, l)
#endif
      {
#if !defined _MSC_VER || defined __clang__
        D2_PARSER__ASSERT (tok == token::TOKEN_INTEGER);
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
        D2_PARSER__ASSERT (tok == token::TOKEN_STRING);
#endif
      }
    };

    /// Build a parser object.
    D2Parser (isc::d2::D2ParserContext& ctx_yyarg);
    virtual ~D2Parser ();

#if 201103L <= YY_CPLUSPLUS
    /// Non copyable.
    D2Parser (const D2Parser&) = delete;
    /// Non copyable.
    D2Parser& operator= (const D2Parser&) = delete;
#endif

    /// Parse.  An alias for parse ().
    /// \returns  0 iff parsing succeeded.
    int operator() ();

    /// Parse.
    /// \returns  0 iff parsing succeeded.
    virtual int parse ();

#if D2_PARSER_DEBUG
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
      make_D2_PARSER_error (location_type l)
      {
        return symbol_type (token::TOKEN_D2_PARSER_error, std::move (l));
      }
#else
      static
      symbol_type
      make_D2_PARSER_error (const location_type& l)
      {
        return symbol_type (token::TOKEN_D2_PARSER_error, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_D2_PARSER_UNDEF (location_type l)
      {
        return symbol_type (token::TOKEN_D2_PARSER_UNDEF, std::move (l));
      }
#else
      static
      symbol_type
      make_D2_PARSER_UNDEF (const location_type& l)
      {
        return symbol_type (token::TOKEN_D2_PARSER_UNDEF, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_COMMA (location_type l)
      {
        return symbol_type (token::TOKEN_COMMA, std::move (l));
      }
#else
      static
      symbol_type
      make_COMMA (const location_type& l)
      {
        return symbol_type (token::TOKEN_COMMA, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_COLON (location_type l)
      {
        return symbol_type (token::TOKEN_COLON, std::move (l));
      }
#else
      static
      symbol_type
      make_COLON (const location_type& l)
      {
        return symbol_type (token::TOKEN_COLON, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_LSQUARE_BRACKET (location_type l)
      {
        return symbol_type (token::TOKEN_LSQUARE_BRACKET, std::move (l));
      }
#else
      static
      symbol_type
      make_LSQUARE_BRACKET (const location_type& l)
      {
        return symbol_type (token::TOKEN_LSQUARE_BRACKET, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_RSQUARE_BRACKET (location_type l)
      {
        return symbol_type (token::TOKEN_RSQUARE_BRACKET, std::move (l));
      }
#else
      static
      symbol_type
      make_RSQUARE_BRACKET (const location_type& l)
      {
        return symbol_type (token::TOKEN_RSQUARE_BRACKET, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_LCURLY_BRACKET (location_type l)
      {
        return symbol_type (token::TOKEN_LCURLY_BRACKET, std::move (l));
      }
#else
      static
      symbol_type
      make_LCURLY_BRACKET (const location_type& l)
      {
        return symbol_type (token::TOKEN_LCURLY_BRACKET, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_RCURLY_BRACKET (location_type l)
      {
        return symbol_type (token::TOKEN_RCURLY_BRACKET, std::move (l));
      }
#else
      static
      symbol_type
      make_RCURLY_BRACKET (const location_type& l)
      {
        return symbol_type (token::TOKEN_RCURLY_BRACKET, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_NULL_TYPE (location_type l)
      {
        return symbol_type (token::TOKEN_NULL_TYPE, std::move (l));
      }
#else
      static
      symbol_type
      make_NULL_TYPE (const location_type& l)
      {
        return symbol_type (token::TOKEN_NULL_TYPE, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_DHCPDDNS (location_type l)
      {
        return symbol_type (token::TOKEN_DHCPDDNS, std::move (l));
      }
#else
      static
      symbol_type
      make_DHCPDDNS (const location_type& l)
      {
        return symbol_type (token::TOKEN_DHCPDDNS, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_IP_ADDRESS (location_type l)
      {
        return symbol_type (token::TOKEN_IP_ADDRESS, std::move (l));
      }
#else
      static
      symbol_type
      make_IP_ADDRESS (const location_type& l)
      {
        return symbol_type (token::TOKEN_IP_ADDRESS, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_PORT (location_type l)
      {
        return symbol_type (token::TOKEN_PORT, std::move (l));
      }
#else
      static
      symbol_type
      make_PORT (const location_type& l)
      {
        return symbol_type (token::TOKEN_PORT, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_DNS_SERVER_TIMEOUT (location_type l)
      {
        return symbol_type (token::TOKEN_DNS_SERVER_TIMEOUT, std::move (l));
      }
#else
      static
      symbol_type
      make_DNS_SERVER_TIMEOUT (const location_type& l)
      {
        return symbol_type (token::TOKEN_DNS_SERVER_TIMEOUT, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_NCR_PROTOCOL (location_type l)
      {
        return symbol_type (token::TOKEN_NCR_PROTOCOL, std::move (l));
      }
#else
      static
      symbol_type
      make_NCR_PROTOCOL (const location_type& l)
      {
        return symbol_type (token::TOKEN_NCR_PROTOCOL, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_UDP (location_type l)
      {
        return symbol_type (token::TOKEN_UDP, std::move (l));
      }
#else
      static
      symbol_type
      make_UDP (const location_type& l)
      {
        return symbol_type (token::TOKEN_UDP, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TCP (location_type l)
      {
        return symbol_type (token::TOKEN_TCP, std::move (l));
      }
#else
      static
      symbol_type
      make_TCP (const location_type& l)
      {
        return symbol_type (token::TOKEN_TCP, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_NCR_FORMAT (location_type l)
      {
        return symbol_type (token::TOKEN_NCR_FORMAT, std::move (l));
      }
#else
      static
      symbol_type
      make_NCR_FORMAT (const location_type& l)
      {
        return symbol_type (token::TOKEN_NCR_FORMAT, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_JSON (location_type l)
      {
        return symbol_type (token::TOKEN_JSON, std::move (l));
      }
#else
      static
      symbol_type
      make_JSON (const location_type& l)
      {
        return symbol_type (token::TOKEN_JSON, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_USER_CONTEXT (location_type l)
      {
        return symbol_type (token::TOKEN_USER_CONTEXT, std::move (l));
      }
#else
      static
      symbol_type
      make_USER_CONTEXT (const location_type& l)
      {
        return symbol_type (token::TOKEN_USER_CONTEXT, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_COMMENT (location_type l)
      {
        return symbol_type (token::TOKEN_COMMENT, std::move (l));
      }
#else
      static
      symbol_type
      make_COMMENT (const location_type& l)
      {
        return symbol_type (token::TOKEN_COMMENT, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_FORWARD_DDNS (location_type l)
      {
        return symbol_type (token::TOKEN_FORWARD_DDNS, std::move (l));
      }
#else
      static
      symbol_type
      make_FORWARD_DDNS (const location_type& l)
      {
        return symbol_type (token::TOKEN_FORWARD_DDNS, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_REVERSE_DDNS (location_type l)
      {
        return symbol_type (token::TOKEN_REVERSE_DDNS, std::move (l));
      }
#else
      static
      symbol_type
      make_REVERSE_DDNS (const location_type& l)
      {
        return symbol_type (token::TOKEN_REVERSE_DDNS, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_DDNS_DOMAINS (location_type l)
      {
        return symbol_type (token::TOKEN_DDNS_DOMAINS, std::move (l));
      }
#else
      static
      symbol_type
      make_DDNS_DOMAINS (const location_type& l)
      {
        return symbol_type (token::TOKEN_DDNS_DOMAINS, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_KEY_NAME (location_type l)
      {
        return symbol_type (token::TOKEN_KEY_NAME, std::move (l));
      }
#else
      static
      symbol_type
      make_KEY_NAME (const location_type& l)
      {
        return symbol_type (token::TOKEN_KEY_NAME, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_DNS_SERVERS (location_type l)
      {
        return symbol_type (token::TOKEN_DNS_SERVERS, std::move (l));
      }
#else
      static
      symbol_type
      make_DNS_SERVERS (const location_type& l)
      {
        return symbol_type (token::TOKEN_DNS_SERVERS, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_HOSTNAME (location_type l)
      {
        return symbol_type (token::TOKEN_HOSTNAME, std::move (l));
      }
#else
      static
      symbol_type
      make_HOSTNAME (const location_type& l)
      {
        return symbol_type (token::TOKEN_HOSTNAME, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TSIG_KEYS (location_type l)
      {
        return symbol_type (token::TOKEN_TSIG_KEYS, std::move (l));
      }
#else
      static
      symbol_type
      make_TSIG_KEYS (const location_type& l)
      {
        return symbol_type (token::TOKEN_TSIG_KEYS, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ALGORITHM (location_type l)
      {
        return symbol_type (token::TOKEN_ALGORITHM, std::move (l));
      }
#else
      static
      symbol_type
      make_ALGORITHM (const location_type& l)
      {
        return symbol_type (token::TOKEN_ALGORITHM, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_DIGEST_BITS (location_type l)
      {
        return symbol_type (token::TOKEN_DIGEST_BITS, std::move (l));
      }
#else
      static
      symbol_type
      make_DIGEST_BITS (const location_type& l)
      {
        return symbol_type (token::TOKEN_DIGEST_BITS, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_SECRET (location_type l)
      {
        return symbol_type (token::TOKEN_SECRET, std::move (l));
      }
#else
      static
      symbol_type
      make_SECRET (const location_type& l)
      {
        return symbol_type (token::TOKEN_SECRET, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_SECRET_FILE (location_type l)
      {
        return symbol_type (token::TOKEN_SECRET_FILE, std::move (l));
      }
#else
      static
      symbol_type
      make_SECRET_FILE (const location_type& l)
      {
        return symbol_type (token::TOKEN_SECRET_FILE, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_CONTROL_SOCKET (location_type l)
      {
        return symbol_type (token::TOKEN_CONTROL_SOCKET, std::move (l));
      }
#else
      static
      symbol_type
      make_CONTROL_SOCKET (const location_type& l)
      {
        return symbol_type (token::TOKEN_CONTROL_SOCKET, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_CONTROL_SOCKETS (location_type l)
      {
        return symbol_type (token::TOKEN_CONTROL_SOCKETS, std::move (l));
      }
#else
      static
      symbol_type
      make_CONTROL_SOCKETS (const location_type& l)
      {
        return symbol_type (token::TOKEN_CONTROL_SOCKETS, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_SOCKET_TYPE (location_type l)
      {
        return symbol_type (token::TOKEN_SOCKET_TYPE, std::move (l));
      }
#else
      static
      symbol_type
      make_SOCKET_TYPE (const location_type& l)
      {
        return symbol_type (token::TOKEN_SOCKET_TYPE, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_UNIX (location_type l)
      {
        return symbol_type (token::TOKEN_UNIX, std::move (l));
      }
#else
      static
      symbol_type
      make_UNIX (const location_type& l)
      {
        return symbol_type (token::TOKEN_UNIX, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_HTTP (location_type l)
      {
        return symbol_type (token::TOKEN_HTTP, std::move (l));
      }
#else
      static
      symbol_type
      make_HTTP (const location_type& l)
      {
        return symbol_type (token::TOKEN_HTTP, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_HTTPS (location_type l)
      {
        return symbol_type (token::TOKEN_HTTPS, std::move (l));
      }
#else
      static
      symbol_type
      make_HTTPS (const location_type& l)
      {
        return symbol_type (token::TOKEN_HTTPS, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_SOCKET_NAME (location_type l)
      {
        return symbol_type (token::TOKEN_SOCKET_NAME, std::move (l));
      }
#else
      static
      symbol_type
      make_SOCKET_NAME (const location_type& l)
      {
        return symbol_type (token::TOKEN_SOCKET_NAME, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_SOCKET_ADDRESS (location_type l)
      {
        return symbol_type (token::TOKEN_SOCKET_ADDRESS, std::move (l));
      }
#else
      static
      symbol_type
      make_SOCKET_ADDRESS (const location_type& l)
      {
        return symbol_type (token::TOKEN_SOCKET_ADDRESS, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_SOCKET_PORT (location_type l)
      {
        return symbol_type (token::TOKEN_SOCKET_PORT, std::move (l));
      }
#else
      static
      symbol_type
      make_SOCKET_PORT (const location_type& l)
      {
        return symbol_type (token::TOKEN_SOCKET_PORT, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_AUTHENTICATION (location_type l)
      {
        return symbol_type (token::TOKEN_AUTHENTICATION, std::move (l));
      }
#else
      static
      symbol_type
      make_AUTHENTICATION (const location_type& l)
      {
        return symbol_type (token::TOKEN_AUTHENTICATION, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TYPE (location_type l)
      {
        return symbol_type (token::TOKEN_TYPE, std::move (l));
      }
#else
      static
      symbol_type
      make_TYPE (const location_type& l)
      {
        return symbol_type (token::TOKEN_TYPE, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_BASIC (location_type l)
      {
        return symbol_type (token::TOKEN_BASIC, std::move (l));
      }
#else
      static
      symbol_type
      make_BASIC (const location_type& l)
      {
        return symbol_type (token::TOKEN_BASIC, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_REALM (location_type l)
      {
        return symbol_type (token::TOKEN_REALM, std::move (l));
      }
#else
      static
      symbol_type
      make_REALM (const location_type& l)
      {
        return symbol_type (token::TOKEN_REALM, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_DIRECTORY (location_type l)
      {
        return symbol_type (token::TOKEN_DIRECTORY, std::move (l));
      }
#else
      static
      symbol_type
      make_DIRECTORY (const location_type& l)
      {
        return symbol_type (token::TOKEN_DIRECTORY, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_CLIENTS (location_type l)
      {
        return symbol_type (token::TOKEN_CLIENTS, std::move (l));
      }
#else
      static
      symbol_type
      make_CLIENTS (const location_type& l)
      {
        return symbol_type (token::TOKEN_CLIENTS, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_USER (location_type l)
      {
        return symbol_type (token::TOKEN_USER, std::move (l));
      }
#else
      static
      symbol_type
      make_USER (const location_type& l)
      {
        return symbol_type (token::TOKEN_USER, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_USER_FILE (location_type l)
      {
        return symbol_type (token::TOKEN_USER_FILE, std::move (l));
      }
#else
      static
      symbol_type
      make_USER_FILE (const location_type& l)
      {
        return symbol_type (token::TOKEN_USER_FILE, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_PASSWORD (location_type l)
      {
        return symbol_type (token::TOKEN_PASSWORD, std::move (l));
      }
#else
      static
      symbol_type
      make_PASSWORD (const location_type& l)
      {
        return symbol_type (token::TOKEN_PASSWORD, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_PASSWORD_FILE (location_type l)
      {
        return symbol_type (token::TOKEN_PASSWORD_FILE, std::move (l));
      }
#else
      static
      symbol_type
      make_PASSWORD_FILE (const location_type& l)
      {
        return symbol_type (token::TOKEN_PASSWORD_FILE, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TRUST_ANCHOR (location_type l)
      {
        return symbol_type (token::TOKEN_TRUST_ANCHOR, std::move (l));
      }
#else
      static
      symbol_type
      make_TRUST_ANCHOR (const location_type& l)
      {
        return symbol_type (token::TOKEN_TRUST_ANCHOR, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_CERT_FILE (location_type l)
      {
        return symbol_type (token::TOKEN_CERT_FILE, std::move (l));
      }
#else
      static
      symbol_type
      make_CERT_FILE (const location_type& l)
      {
        return symbol_type (token::TOKEN_CERT_FILE, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_KEY_FILE (location_type l)
      {
        return symbol_type (token::TOKEN_KEY_FILE, std::move (l));
      }
#else
      static
      symbol_type
      make_KEY_FILE (const location_type& l)
      {
        return symbol_type (token::TOKEN_KEY_FILE, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_CERT_REQUIRED (location_type l)
      {
        return symbol_type (token::TOKEN_CERT_REQUIRED, std::move (l));
      }
#else
      static
      symbol_type
      make_CERT_REQUIRED (const location_type& l)
      {
        return symbol_type (token::TOKEN_CERT_REQUIRED, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_HOOKS_LIBRARIES (location_type l)
      {
        return symbol_type (token::TOKEN_HOOKS_LIBRARIES, std::move (l));
      }
#else
      static
      symbol_type
      make_HOOKS_LIBRARIES (const location_type& l)
      {
        return symbol_type (token::TOKEN_HOOKS_LIBRARIES, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_LIBRARY (location_type l)
      {
        return symbol_type (token::TOKEN_LIBRARY, std::move (l));
      }
#else
      static
      symbol_type
      make_LIBRARY (const location_type& l)
      {
        return symbol_type (token::TOKEN_LIBRARY, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_PARAMETERS (location_type l)
      {
        return symbol_type (token::TOKEN_PARAMETERS, std::move (l));
      }
#else
      static
      symbol_type
      make_PARAMETERS (const location_type& l)
      {
        return symbol_type (token::TOKEN_PARAMETERS, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_LOGGERS (location_type l)
      {
        return symbol_type (token::TOKEN_LOGGERS, std::move (l));
      }
#else
      static
      symbol_type
      make_LOGGERS (const location_type& l)
      {
        return symbol_type (token::TOKEN_LOGGERS, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_NAME (location_type l)
      {
        return symbol_type (token::TOKEN_NAME, std::move (l));
      }
#else
      static
      symbol_type
      make_NAME (const location_type& l)
      {
        return symbol_type (token::TOKEN_NAME, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_OUTPUT_OPTIONS (location_type l)
      {
        return symbol_type (token::TOKEN_OUTPUT_OPTIONS, std::move (l));
      }
#else
      static
      symbol_type
      make_OUTPUT_OPTIONS (const location_type& l)
      {
        return symbol_type (token::TOKEN_OUTPUT_OPTIONS, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_OUTPUT (location_type l)
      {
        return symbol_type (token::TOKEN_OUTPUT, std::move (l));
      }
#else
      static
      symbol_type
      make_OUTPUT (const location_type& l)
      {
        return symbol_type (token::TOKEN_OUTPUT, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_DEBUGLEVEL (location_type l)
      {
        return symbol_type (token::TOKEN_DEBUGLEVEL, std::move (l));
      }
#else
      static
      symbol_type
      make_DEBUGLEVEL (const location_type& l)
      {
        return symbol_type (token::TOKEN_DEBUGLEVEL, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_SEVERITY (location_type l)
      {
        return symbol_type (token::TOKEN_SEVERITY, std::move (l));
      }
#else
      static
      symbol_type
      make_SEVERITY (const location_type& l)
      {
        return symbol_type (token::TOKEN_SEVERITY, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_FLUSH (location_type l)
      {
        return symbol_type (token::TOKEN_FLUSH, std::move (l));
      }
#else
      static
      symbol_type
      make_FLUSH (const location_type& l)
      {
        return symbol_type (token::TOKEN_FLUSH, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_MAXSIZE (location_type l)
      {
        return symbol_type (token::TOKEN_MAXSIZE, std::move (l));
      }
#else
      static
      symbol_type
      make_MAXSIZE (const location_type& l)
      {
        return symbol_type (token::TOKEN_MAXSIZE, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_MAXVER (location_type l)
      {
        return symbol_type (token::TOKEN_MAXVER, std::move (l));
      }
#else
      static
      symbol_type
      make_MAXVER (const location_type& l)
      {
        return symbol_type (token::TOKEN_MAXVER, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_PATTERN (location_type l)
      {
        return symbol_type (token::TOKEN_PATTERN, std::move (l));
      }
#else
      static
      symbol_type
      make_PATTERN (const location_type& l)
      {
        return symbol_type (token::TOKEN_PATTERN, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TOPLEVEL_JSON (location_type l)
      {
        return symbol_type (token::TOKEN_TOPLEVEL_JSON, std::move (l));
      }
#else
      static
      symbol_type
      make_TOPLEVEL_JSON (const location_type& l)
      {
        return symbol_type (token::TOKEN_TOPLEVEL_JSON, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TOPLEVEL_DHCPDDNS (location_type l)
      {
        return symbol_type (token::TOKEN_TOPLEVEL_DHCPDDNS, std::move (l));
      }
#else
      static
      symbol_type
      make_TOPLEVEL_DHCPDDNS (const location_type& l)
      {
        return symbol_type (token::TOKEN_TOPLEVEL_DHCPDDNS, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_SUB_DHCPDDNS (location_type l)
      {
        return symbol_type (token::TOKEN_SUB_DHCPDDNS, std::move (l));
      }
#else
      static
      symbol_type
      make_SUB_DHCPDDNS (const location_type& l)
      {
        return symbol_type (token::TOKEN_SUB_DHCPDDNS, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_SUB_TSIG_KEY (location_type l)
      {
        return symbol_type (token::TOKEN_SUB_TSIG_KEY, std::move (l));
      }
#else
      static
      symbol_type
      make_SUB_TSIG_KEY (const location_type& l)
      {
        return symbol_type (token::TOKEN_SUB_TSIG_KEY, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_SUB_TSIG_KEYS (location_type l)
      {
        return symbol_type (token::TOKEN_SUB_TSIG_KEYS, std::move (l));
      }
#else
      static
      symbol_type
      make_SUB_TSIG_KEYS (const location_type& l)
      {
        return symbol_type (token::TOKEN_SUB_TSIG_KEYS, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_SUB_DDNS_DOMAIN (location_type l)
      {
        return symbol_type (token::TOKEN_SUB_DDNS_DOMAIN, std::move (l));
      }
#else
      static
      symbol_type
      make_SUB_DDNS_DOMAIN (const location_type& l)
      {
        return symbol_type (token::TOKEN_SUB_DDNS_DOMAIN, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_SUB_DDNS_DOMAINS (location_type l)
      {
        return symbol_type (token::TOKEN_SUB_DDNS_DOMAINS, std::move (l));
      }
#else
      static
      symbol_type
      make_SUB_DDNS_DOMAINS (const location_type& l)
      {
        return symbol_type (token::TOKEN_SUB_DDNS_DOMAINS, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_SUB_DNS_SERVER (location_type l)
      {
        return symbol_type (token::TOKEN_SUB_DNS_SERVER, std::move (l));
      }
#else
      static
      symbol_type
      make_SUB_DNS_SERVER (const location_type& l)
      {
        return symbol_type (token::TOKEN_SUB_DNS_SERVER, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_SUB_DNS_SERVERS (location_type l)
      {
        return symbol_type (token::TOKEN_SUB_DNS_SERVERS, std::move (l));
      }
#else
      static
      symbol_type
      make_SUB_DNS_SERVERS (const location_type& l)
      {
        return symbol_type (token::TOKEN_SUB_DNS_SERVERS, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_SUB_HOOKS_LIBRARY (location_type l)
      {
        return symbol_type (token::TOKEN_SUB_HOOKS_LIBRARY, std::move (l));
      }
#else
      static
      symbol_type
      make_SUB_HOOKS_LIBRARY (const location_type& l)
      {
        return symbol_type (token::TOKEN_SUB_HOOKS_LIBRARY, l);
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
      make_INTEGER (int64_t v, location_type l)
      {
        return symbol_type (token::TOKEN_INTEGER, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_INTEGER (const int64_t& v, const location_type& l)
      {
        return symbol_type (token::TOKEN_INTEGER, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_FLOAT (double v, location_type l)
      {
        return symbol_type (token::TOKEN_FLOAT, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_FLOAT (const double& v, const location_type& l)
      {
        return symbol_type (token::TOKEN_FLOAT, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_BOOLEAN (bool v, location_type l)
      {
        return symbol_type (token::TOKEN_BOOLEAN, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_BOOLEAN (const bool& v, const location_type& l)
      {
        return symbol_type (token::TOKEN_BOOLEAN, v, l);
      }
#endif


    class context
    {
    public:
      context (const D2Parser& yyparser, const symbol_type& yyla);
      const symbol_type& lookahead () const YY_NOEXCEPT { return yyla_; }
      symbol_kind_type token () const YY_NOEXCEPT { return yyla_.kind (); }
      const location_type& location () const YY_NOEXCEPT { return yyla_.location; }

      /// Put in YYARG at most YYARGN of the expected tokens, and return the
      /// number of tokens stored in YYARG.  If YYARG is null, return the
      /// number of expected tokens (guaranteed to be less than YYNTOKENS).
      int expected_tokens (symbol_kind_type yyarg[], int yyargn) const;

    private:
      const D2Parser& yyparser_;
      const symbol_type& yyla_;
    };

  private:
#if YY_CPLUSPLUS < 201103L
    /// Non copyable.
    D2Parser (const D2Parser&);
    /// Non copyable.
    D2Parser& operator= (const D2Parser&);
#endif


    /// Stored state numbers (used for stacks).
    typedef short state_type;

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
    static const short yydefact_[];

    // YYPGOTO[NTERM-NUM].
    static const short yypgoto_[];

    // YYDEFGOTO[NTERM-NUM].
    static const short yydefgoto_[];

    // YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
    // positive, shift that token.  If negative, reduce the rule whose
    // number is the opposite.  If YYTABLE_NINF, syntax error.
    static const short yytable_[];

    static const short yycheck_[];

    // YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
    // state STATE-NUM.
    static const short yystos_[];

    // YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.
    static const short yyr1_[];

    // YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.
    static const signed char yyr2_[];


#if D2_PARSER_DEBUG
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
      yylast_ = 461,     ///< Last index in yytable_.
      yynnts_ = 198,  ///< Number of nonterminal symbols.
      yyfinal_ = 22 ///< Termination state number.
    };


    // User arguments.
    isc::d2::D2ParserContext& ctx;

  };

  inline
  D2Parser::symbol_kind_type
  D2Parser::yytranslate_ (int t) YY_NOEXCEPT
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
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81
    };
    // Last valid token kind.
    const int code_max = 336;

    if (t <= 0)
      return symbol_kind::S_YYEOF;
    else if (t <= code_max)
      return static_cast <symbol_kind_type> (translate_table[t]);
    else
      return symbol_kind::S_YYUNDEF;
  }

  // basic_symbol.
  template <typename Base>
  D2Parser::basic_symbol<Base>::basic_symbol (const basic_symbol& that)
    : Base (that)
    , value ()
    , location (that.location)
  {
    switch (this->kind ())
    {
      case symbol_kind::S_value: // value
      case symbol_kind::S_map_value: // map_value
      case symbol_kind::S_ncr_protocol_value: // ncr_protocol_value
      case symbol_kind::S_control_socket_type_value: // control_socket_type_value
      case symbol_kind::S_auth_type_value: // auth_type_value
        value.copy< ElementPtr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_BOOLEAN: // "boolean"
        value.copy< bool > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_FLOAT: // "floating point"
        value.copy< double > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_INTEGER: // "integer"
        value.copy< int64_t > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_STRING: // "constant string"
        value.copy< std::string > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

  }




  template <typename Base>
  D2Parser::symbol_kind_type
  D2Parser::basic_symbol<Base>::type_get () const YY_NOEXCEPT
  {
    return this->kind ();
  }


  template <typename Base>
  bool
  D2Parser::basic_symbol<Base>::empty () const YY_NOEXCEPT
  {
    return this->kind () == symbol_kind::S_YYEMPTY;
  }

  template <typename Base>
  void
  D2Parser::basic_symbol<Base>::move (basic_symbol& s)
  {
    super_type::move (s);
    switch (this->kind ())
    {
      case symbol_kind::S_value: // value
      case symbol_kind::S_map_value: // map_value
      case symbol_kind::S_ncr_protocol_value: // ncr_protocol_value
      case symbol_kind::S_control_socket_type_value: // control_socket_type_value
      case symbol_kind::S_auth_type_value: // auth_type_value
        value.move< ElementPtr > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_BOOLEAN: // "boolean"
        value.move< bool > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_FLOAT: // "floating point"
        value.move< double > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_INTEGER: // "integer"
        value.move< int64_t > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_STRING: // "constant string"
        value.move< std::string > (YY_MOVE (s.value));
        break;

      default:
        break;
    }

    location = YY_MOVE (s.location);
  }

  // by_kind.
  inline
  D2Parser::by_kind::by_kind () YY_NOEXCEPT
    : kind_ (symbol_kind::S_YYEMPTY)
  {}

#if 201103L <= YY_CPLUSPLUS
  inline
  D2Parser::by_kind::by_kind (by_kind&& that) YY_NOEXCEPT
    : kind_ (that.kind_)
  {
    that.clear ();
  }
#endif

  inline
  D2Parser::by_kind::by_kind (const by_kind& that) YY_NOEXCEPT
    : kind_ (that.kind_)
  {}

  inline
  D2Parser::by_kind::by_kind (token_kind_type t) YY_NOEXCEPT
    : kind_ (yytranslate_ (t))
  {}



  inline
  void
  D2Parser::by_kind::clear () YY_NOEXCEPT
  {
    kind_ = symbol_kind::S_YYEMPTY;
  }

  inline
  void
  D2Parser::by_kind::move (by_kind& that)
  {
    kind_ = that.kind_;
    that.clear ();
  }

  inline
  D2Parser::symbol_kind_type
  D2Parser::by_kind::kind () const YY_NOEXCEPT
  {
    return kind_;
  }


  inline
  D2Parser::symbol_kind_type
  D2Parser::by_kind::type_get () const YY_NOEXCEPT
  {
    return this->kind ();
  }


#line 14 "d2_parser.yy"
} } // isc::d2
#line 3057 "d2_parser.h"




#endif // !YY_D2_PARSER_D2_PARSER_H_INCLUDED
