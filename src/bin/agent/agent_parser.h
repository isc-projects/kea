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
 ** \file agent_parser.h
 ** Define the isc::agent::parser class.
 */

// C++ LALR(1) parser skeleton written by Akim Demaille.

// DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
// especially those whose name start with YY_ or yy_.  They are
// private implementation details that can be changed or removed.

#ifndef YY_AGENT_AGENT_PARSER_H_INCLUDED
# define YY_AGENT_AGENT_PARSER_H_INCLUDED
// "%code requires" blocks.
#line 17 "agent_parser.yy"

#include <string>
#include <cc/data.h>
#include <boost/lexical_cast.hpp>
#include <agent/parser_context_decl.h>

using namespace isc::agent;
using namespace isc::data;
using namespace std;

#line 60 "agent_parser.h"

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
#ifndef AGENT__ASSERT
# include <cassert>
# define AGENT__ASSERT assert
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

#line 14 "agent_parser.yy"
namespace isc { namespace agent {
#line 209 "agent_parser.h"




  /// A Bison parser.
  class AgentParser
  {
  public:
#ifdef AGENT_STYPE
# ifdef __GNUC__
#  pragma GCC message "bison: do not #define AGENT_STYPE in C++, use %define api.value.type"
# endif
    typedef AGENT_STYPE value_type;
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
      AGENT__ASSERT (sizeof (T) <= size);
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
      AGENT__ASSERT (!yytypeid_);
    }

# if 201103L <= YY_CPLUSPLUS
    /// Instantiate a \a T in here from \a t.
    template <typename T, typename... U>
    T&
    emplace (U&&... u)
    {
      AGENT__ASSERT (!yytypeid_);
      AGENT__ASSERT (sizeof (T) <= size);
      yytypeid_ = & typeid (T);
      return *new (yyas_<T> ()) T (std::forward <U>(u)...);
    }
# else
    /// Instantiate an empty \a T in here.
    template <typename T>
    T&
    emplace ()
    {
      AGENT__ASSERT (!yytypeid_);
      AGENT__ASSERT (sizeof (T) <= size);
      yytypeid_ = & typeid (T);
      return *new (yyas_<T> ()) T ();
    }

    /// Instantiate a \a T in here from \a t.
    template <typename T>
    T&
    emplace (const T& t)
    {
      AGENT__ASSERT (!yytypeid_);
      AGENT__ASSERT (sizeof (T) <= size);
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
      AGENT__ASSERT (yytypeid_);
      AGENT__ASSERT (*yytypeid_ == typeid (T));
      AGENT__ASSERT (sizeof (T) <= size);
      return *yyas_<T> ();
    }

    /// Const accessor to a built \a T (for %printer).
    template <typename T>
    const T&
    as () const YY_NOEXCEPT
    {
      AGENT__ASSERT (yytypeid_);
      AGENT__ASSERT (*yytypeid_ == typeid (T));
      AGENT__ASSERT (sizeof (T) <= size);
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
      AGENT__ASSERT (yytypeid_);
      AGENT__ASSERT (*yytypeid_ == *that.yytypeid_);
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
      // socket_type_value
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
        TOKEN_AGENT_EMPTY = -2,
    TOKEN_END = 0,                 // "end of file"
    TOKEN_AGENT_error = 256,       // error
    TOKEN_AGENT_UNDEF = 257,       // "invalid token"
    TOKEN_COMMA = 258,             // ","
    TOKEN_COLON = 259,             // ":"
    TOKEN_LSQUARE_BRACKET = 260,   // "["
    TOKEN_RSQUARE_BRACKET = 261,   // "]"
    TOKEN_LCURLY_BRACKET = 262,    // "{"
    TOKEN_RCURLY_BRACKET = 263,    // "}"
    TOKEN_NULL_TYPE = 264,         // "null"
    TOKEN_CONTROL_AGENT = 265,     // "Control-agent"
    TOKEN_HTTP_HOST = 266,         // "http-host"
    TOKEN_HTTP_PORT = 267,         // "http-port"
    TOKEN_USER_CONTEXT = 268,      // "user-context"
    TOKEN_COMMENT = 269,           // "comment"
    TOKEN_AUTHENTICATION = 270,    // "authentication"
    TOKEN_TYPE = 271,              // "type"
    TOKEN_BASIC = 272,             // "basic"
    TOKEN_REALM = 273,             // "realm"
    TOKEN_DIRECTORY = 274,         // "directory"
    TOKEN_CLIENTS = 275,           // "clients"
    TOKEN_USER = 276,              // "user"
    TOKEN_USER_FILE = 277,         // "user-file"
    TOKEN_PASSWORD = 278,          // "password"
    TOKEN_PASSWORD_FILE = 279,     // "password-file"
    TOKEN_TRUST_ANCHOR = 280,      // "trust-anchor"
    TOKEN_CERT_FILE = 281,         // "cert-file"
    TOKEN_KEY_FILE = 282,          // "key-file"
    TOKEN_CERT_REQUIRED = 283,     // "cert-required"
    TOKEN_CONTROL_SOCKETS = 284,   // "control-sockets"
    TOKEN_DHCP4_SERVER = 285,      // "dhcp4"
    TOKEN_DHCP6_SERVER = 286,      // "dhcp6"
    TOKEN_D2_SERVER = 287,         // "d2"
    TOKEN_SOCKET_NAME = 288,       // "socket-name"
    TOKEN_SOCKET_TYPE = 289,       // "socket-type"
    TOKEN_UNIX = 290,              // "unix"
    TOKEN_HOOKS_LIBRARIES = 291,   // "hooks-libraries"
    TOKEN_LIBRARY = 292,           // "library"
    TOKEN_PARAMETERS = 293,        // "parameters"
    TOKEN_LOGGERS = 294,           // "loggers"
    TOKEN_NAME = 295,              // "name"
    TOKEN_OUTPUT_OPTIONS = 296,    // "output_options"
    TOKEN_OUTPUT = 297,            // "output"
    TOKEN_DEBUGLEVEL = 298,        // "debuglevel"
    TOKEN_SEVERITY = 299,          // "severity"
    TOKEN_FLUSH = 300,             // "flush"
    TOKEN_MAXSIZE = 301,           // "maxsize"
    TOKEN_MAXVER = 302,            // "maxver"
    TOKEN_PATTERN = 303,           // "pattern"
    TOKEN_START_JSON = 304,        // START_JSON
    TOKEN_START_AGENT = 305,       // START_AGENT
    TOKEN_START_SUB_AGENT = 306,   // START_SUB_AGENT
    TOKEN_STRING = 307,            // "constant string"
    TOKEN_INTEGER = 308,           // "integer"
    TOKEN_FLOAT = 309,             // "floating point"
    TOKEN_BOOLEAN = 310            // "boolean"
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
        YYNTOKENS = 56, ///< Number of tokens.
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
        S_CONTROL_AGENT = 10,                    // "Control-agent"
        S_HTTP_HOST = 11,                        // "http-host"
        S_HTTP_PORT = 12,                        // "http-port"
        S_USER_CONTEXT = 13,                     // "user-context"
        S_COMMENT = 14,                          // "comment"
        S_AUTHENTICATION = 15,                   // "authentication"
        S_TYPE = 16,                             // "type"
        S_BASIC = 17,                            // "basic"
        S_REALM = 18,                            // "realm"
        S_DIRECTORY = 19,                        // "directory"
        S_CLIENTS = 20,                          // "clients"
        S_USER = 21,                             // "user"
        S_USER_FILE = 22,                        // "user-file"
        S_PASSWORD = 23,                         // "password"
        S_PASSWORD_FILE = 24,                    // "password-file"
        S_TRUST_ANCHOR = 25,                     // "trust-anchor"
        S_CERT_FILE = 26,                        // "cert-file"
        S_KEY_FILE = 27,                         // "key-file"
        S_CERT_REQUIRED = 28,                    // "cert-required"
        S_CONTROL_SOCKETS = 29,                  // "control-sockets"
        S_DHCP4_SERVER = 30,                     // "dhcp4"
        S_DHCP6_SERVER = 31,                     // "dhcp6"
        S_D2_SERVER = 32,                        // "d2"
        S_SOCKET_NAME = 33,                      // "socket-name"
        S_SOCKET_TYPE = 34,                      // "socket-type"
        S_UNIX = 35,                             // "unix"
        S_HOOKS_LIBRARIES = 36,                  // "hooks-libraries"
        S_LIBRARY = 37,                          // "library"
        S_PARAMETERS = 38,                       // "parameters"
        S_LOGGERS = 39,                          // "loggers"
        S_NAME = 40,                             // "name"
        S_OUTPUT_OPTIONS = 41,                   // "output_options"
        S_OUTPUT = 42,                           // "output"
        S_DEBUGLEVEL = 43,                       // "debuglevel"
        S_SEVERITY = 44,                         // "severity"
        S_FLUSH = 45,                            // "flush"
        S_MAXSIZE = 46,                          // "maxsize"
        S_MAXVER = 47,                           // "maxver"
        S_PATTERN = 48,                          // "pattern"
        S_START_JSON = 49,                       // START_JSON
        S_START_AGENT = 50,                      // START_AGENT
        S_START_SUB_AGENT = 51,                  // START_SUB_AGENT
        S_STRING = 52,                           // "constant string"
        S_INTEGER = 53,                          // "integer"
        S_FLOAT = 54,                            // "floating point"
        S_BOOLEAN = 55,                          // "boolean"
        S_YYACCEPT = 56,                         // $accept
        S_start = 57,                            // start
        S_58_1 = 58,                             // $@1
        S_59_2 = 59,                             // $@2
        S_60_3 = 60,                             // $@3
        S_sub_agent = 61,                        // sub_agent
        S_62_4 = 62,                             // $@4
        S_json = 63,                             // json
        S_value = 64,                            // value
        S_map = 65,                              // map
        S_66_5 = 66,                             // $@5
        S_map_value = 67,                        // map_value
        S_map_content = 68,                      // map_content
        S_not_empty_map = 69,                    // not_empty_map
        S_list_generic = 70,                     // list_generic
        S_71_6 = 71,                             // $@6
        S_list_content = 72,                     // list_content
        S_not_empty_list = 73,                   // not_empty_list
        S_unknown_map_entry = 74,                // unknown_map_entry
        S_agent_syntax_map = 75,                 // agent_syntax_map
        S_76_7 = 76,                             // $@7
        S_global_object = 77,                    // global_object
        S_78_8 = 78,                             // $@8
        S_global_object_comma = 79,              // global_object_comma
        S_global_params = 80,                    // global_params
        S_global_param = 81,                     // global_param
        S_http_host = 82,                        // http_host
        S_83_9 = 83,                             // $@9
        S_http_port = 84,                        // http_port
        S_trust_anchor = 85,                     // trust_anchor
        S_86_10 = 86,                            // $@10
        S_cert_file = 87,                        // cert_file
        S_88_11 = 88,                            // $@11
        S_key_file = 89,                         // key_file
        S_90_12 = 90,                            // $@12
        S_cert_required = 91,                    // cert_required
        S_user_context = 92,                     // user_context
        S_93_13 = 93,                            // $@13
        S_comment = 94,                          // comment
        S_95_14 = 95,                            // $@14
        S_hooks_libraries = 96,                  // hooks_libraries
        S_97_15 = 97,                            // $@15
        S_hooks_libraries_list = 98,             // hooks_libraries_list
        S_not_empty_hooks_libraries_list = 99,   // not_empty_hooks_libraries_list
        S_hooks_library = 100,                   // hooks_library
        S_101_16 = 101,                          // $@16
        S_hooks_params = 102,                    // hooks_params
        S_hooks_param = 103,                     // hooks_param
        S_library = 104,                         // library
        S_105_17 = 105,                          // $@17
        S_parameters = 106,                      // parameters
        S_107_18 = 107,                          // $@18
        S_control_sockets = 108,                 // control_sockets
        S_109_19 = 109,                          // $@19
        S_control_sockets_params = 110,          // control_sockets_params
        S_control_socket = 111,                  // control_socket
        S_dhcp4_server_socket = 112,             // dhcp4_server_socket
        S_113_20 = 113,                          // $@20
        S_dhcp6_server_socket = 114,             // dhcp6_server_socket
        S_115_21 = 115,                          // $@21
        S_d2_server_socket = 116,                // d2_server_socket
        S_117_22 = 117,                          // $@22
        S_control_socket_params = 118,           // control_socket_params
        S_control_socket_param = 119,            // control_socket_param
        S_socket_name = 120,                     // socket_name
        S_121_23 = 121,                          // $@23
        S_socket_type = 122,                     // socket_type
        S_123_24 = 123,                          // $@24
        S_socket_type_value = 124,               // socket_type_value
        S_authentication = 125,                  // authentication
        S_126_25 = 126,                          // $@25
        S_auth_params = 127,                     // auth_params
        S_auth_param = 128,                      // auth_param
        S_auth_type = 129,                       // auth_type
        S_130_26 = 130,                          // $@26
        S_auth_type_value = 131,                 // auth_type_value
        S_realm = 132,                           // realm
        S_133_27 = 133,                          // $@27
        S_directory = 134,                       // directory
        S_135_28 = 135,                          // $@28
        S_clients = 136,                         // clients
        S_137_29 = 137,                          // $@29
        S_clients_list = 138,                    // clients_list
        S_not_empty_clients_list = 139,          // not_empty_clients_list
        S_basic_auth = 140,                      // basic_auth
        S_141_30 = 141,                          // $@30
        S_clients_params = 142,                  // clients_params
        S_clients_param = 143,                   // clients_param
        S_user = 144,                            // user
        S_145_31 = 145,                          // $@31
        S_user_file = 146,                       // user_file
        S_147_32 = 147,                          // $@32
        S_password = 148,                        // password
        S_149_33 = 149,                          // $@33
        S_password_file = 150,                   // password_file
        S_151_34 = 151,                          // $@34
        S_loggers = 152,                         // loggers
        S_153_35 = 153,                          // $@35
        S_loggers_entries = 154,                 // loggers_entries
        S_logger_entry = 155,                    // logger_entry
        S_156_36 = 156,                          // $@36
        S_logger_params = 157,                   // logger_params
        S_logger_param = 158,                    // logger_param
        S_name = 159,                            // name
        S_160_37 = 160,                          // $@37
        S_debuglevel = 161,                      // debuglevel
        S_severity = 162,                        // severity
        S_163_38 = 163,                          // $@38
        S_output_options_list = 164,             // output_options_list
        S_165_39 = 165,                          // $@39
        S_output_options_list_content = 166,     // output_options_list_content
        S_output_entry = 167,                    // output_entry
        S_168_40 = 168,                          // $@40
        S_output_params_list = 169,              // output_params_list
        S_output_params = 170,                   // output_params
        S_output = 171,                          // output
        S_172_41 = 172,                          // $@41
        S_flush = 173,                           // flush
        S_maxsize = 174,                         // maxsize
        S_maxver = 175,                          // maxver
        S_pattern = 176,                         // pattern
        S_177_42 = 177                           // $@42
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
      case symbol_kind::S_socket_type_value: // socket_type_value
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
      case symbol_kind::S_socket_type_value: // socket_type_value
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
        return AgentParser::symbol_name (this->kind ());
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
        AGENT__ASSERT (tok == token::TOKEN_END
                   || (token::TOKEN_AGENT_error <= tok && tok <= token::TOKEN_START_SUB_AGENT));
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
        AGENT__ASSERT (tok == token::TOKEN_BOOLEAN);
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
        AGENT__ASSERT (tok == token::TOKEN_FLOAT);
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
        AGENT__ASSERT (tok == token::TOKEN_INTEGER);
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
        AGENT__ASSERT (tok == token::TOKEN_STRING);
#endif
      }
    };

    /// Build a parser object.
    AgentParser (isc::agent::ParserContext& ctx_yyarg);
    virtual ~AgentParser ();

#if 201103L <= YY_CPLUSPLUS
    /// Non copyable.
    AgentParser (const AgentParser&) = delete;
    /// Non copyable.
    AgentParser& operator= (const AgentParser&) = delete;
#endif

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
      make_AGENT_error (location_type l)
      {
        return symbol_type (token::TOKEN_AGENT_error, std::move (l));
      }
#else
      static
      symbol_type
      make_AGENT_error (const location_type& l)
      {
        return symbol_type (token::TOKEN_AGENT_error, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_AGENT_UNDEF (location_type l)
      {
        return symbol_type (token::TOKEN_AGENT_UNDEF, std::move (l));
      }
#else
      static
      symbol_type
      make_AGENT_UNDEF (const location_type& l)
      {
        return symbol_type (token::TOKEN_AGENT_UNDEF, l);
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
      make_CONTROL_AGENT (location_type l)
      {
        return symbol_type (token::TOKEN_CONTROL_AGENT, std::move (l));
      }
#else
      static
      symbol_type
      make_CONTROL_AGENT (const location_type& l)
      {
        return symbol_type (token::TOKEN_CONTROL_AGENT, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_HTTP_HOST (location_type l)
      {
        return symbol_type (token::TOKEN_HTTP_HOST, std::move (l));
      }
#else
      static
      symbol_type
      make_HTTP_HOST (const location_type& l)
      {
        return symbol_type (token::TOKEN_HTTP_HOST, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_HTTP_PORT (location_type l)
      {
        return symbol_type (token::TOKEN_HTTP_PORT, std::move (l));
      }
#else
      static
      symbol_type
      make_HTTP_PORT (const location_type& l)
      {
        return symbol_type (token::TOKEN_HTTP_PORT, l);
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
      make_DHCP4_SERVER (location_type l)
      {
        return symbol_type (token::TOKEN_DHCP4_SERVER, std::move (l));
      }
#else
      static
      symbol_type
      make_DHCP4_SERVER (const location_type& l)
      {
        return symbol_type (token::TOKEN_DHCP4_SERVER, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_DHCP6_SERVER (location_type l)
      {
        return symbol_type (token::TOKEN_DHCP6_SERVER, std::move (l));
      }
#else
      static
      symbol_type
      make_DHCP6_SERVER (const location_type& l)
      {
        return symbol_type (token::TOKEN_DHCP6_SERVER, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_D2_SERVER (location_type l)
      {
        return symbol_type (token::TOKEN_D2_SERVER, std::move (l));
      }
#else
      static
      symbol_type
      make_D2_SERVER (const location_type& l)
      {
        return symbol_type (token::TOKEN_D2_SERVER, l);
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
      make_START_JSON (location_type l)
      {
        return symbol_type (token::TOKEN_START_JSON, std::move (l));
      }
#else
      static
      symbol_type
      make_START_JSON (const location_type& l)
      {
        return symbol_type (token::TOKEN_START_JSON, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_START_AGENT (location_type l)
      {
        return symbol_type (token::TOKEN_START_AGENT, std::move (l));
      }
#else
      static
      symbol_type
      make_START_AGENT (const location_type& l)
      {
        return symbol_type (token::TOKEN_START_AGENT, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_START_SUB_AGENT (location_type l)
      {
        return symbol_type (token::TOKEN_START_SUB_AGENT, std::move (l));
      }
#else
      static
      symbol_type
      make_START_SUB_AGENT (const location_type& l)
      {
        return symbol_type (token::TOKEN_START_SUB_AGENT, l);
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
      context (const AgentParser& yyparser, const symbol_type& yyla);
      const symbol_type& lookahead () const YY_NOEXCEPT { return yyla_; }
      symbol_kind_type token () const YY_NOEXCEPT { return yyla_.kind (); }
      const location_type& location () const YY_NOEXCEPT { return yyla_.location; }

      /// Put in YYARG at most YYARGN of the expected tokens, and return the
      /// number of tokens stored in YYARG.  If YYARG is null, return the
      /// number of expected tokens (guaranteed to be less than YYNTOKENS).
      int expected_tokens (symbol_kind_type yyarg[], int yyargn) const;

    private:
      const AgentParser& yyparser_;
      const symbol_type& yyla_;
    };

  private:
#if YY_CPLUSPLUS < 201103L
    /// Non copyable.
    AgentParser (const AgentParser&);
    /// Non copyable.
    AgentParser& operator= (const AgentParser&);
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
    static const unsigned char yydefact_[];

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
    static const unsigned char yystos_[];

    // YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.
    static const unsigned char yyr1_[];

    // YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.
    static const signed char yyr2_[];


#if AGENT_DEBUG
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
      yylast_ = 252,     ///< Last index in yytable_.
      yynnts_ = 122,  ///< Number of nonterminal symbols.
      yyfinal_ = 8 ///< Termination state number.
    };


    // User arguments.
    isc::agent::ParserContext& ctx;

  };

  inline
  AgentParser::symbol_kind_type
  AgentParser::yytranslate_ (int t) YY_NOEXCEPT
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
      55
    };
    // Last valid token kind.
    const int code_max = 310;

    if (t <= 0)
      return symbol_kind::S_YYEOF;
    else if (t <= code_max)
      return static_cast <symbol_kind_type> (translate_table[t]);
    else
      return symbol_kind::S_YYUNDEF;
  }

  // basic_symbol.
  template <typename Base>
  AgentParser::basic_symbol<Base>::basic_symbol (const basic_symbol& that)
    : Base (that)
    , value ()
    , location (that.location)
  {
    switch (this->kind ())
    {
      case symbol_kind::S_value: // value
      case symbol_kind::S_map_value: // map_value
      case symbol_kind::S_socket_type_value: // socket_type_value
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
  AgentParser::symbol_kind_type
  AgentParser::basic_symbol<Base>::type_get () const YY_NOEXCEPT
  {
    return this->kind ();
  }


  template <typename Base>
  bool
  AgentParser::basic_symbol<Base>::empty () const YY_NOEXCEPT
  {
    return this->kind () == symbol_kind::S_YYEMPTY;
  }

  template <typename Base>
  void
  AgentParser::basic_symbol<Base>::move (basic_symbol& s)
  {
    super_type::move (s);
    switch (this->kind ())
    {
      case symbol_kind::S_value: // value
      case symbol_kind::S_map_value: // map_value
      case symbol_kind::S_socket_type_value: // socket_type_value
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
  AgentParser::by_kind::by_kind () YY_NOEXCEPT
    : kind_ (symbol_kind::S_YYEMPTY)
  {}

#if 201103L <= YY_CPLUSPLUS
  inline
  AgentParser::by_kind::by_kind (by_kind&& that) YY_NOEXCEPT
    : kind_ (that.kind_)
  {
    that.clear ();
  }
#endif

  inline
  AgentParser::by_kind::by_kind (const by_kind& that) YY_NOEXCEPT
    : kind_ (that.kind_)
  {}

  inline
  AgentParser::by_kind::by_kind (token_kind_type t) YY_NOEXCEPT
    : kind_ (yytranslate_ (t))
  {}



  inline
  void
  AgentParser::by_kind::clear () YY_NOEXCEPT
  {
    kind_ = symbol_kind::S_YYEMPTY;
  }

  inline
  void
  AgentParser::by_kind::move (by_kind& that)
  {
    kind_ = that.kind_;
    that.clear ();
  }

  inline
  AgentParser::symbol_kind_type
  AgentParser::by_kind::kind () const YY_NOEXCEPT
  {
    return kind_;
  }


  inline
  AgentParser::symbol_kind_type
  AgentParser::by_kind::type_get () const YY_NOEXCEPT
  {
    return this->kind ();
  }


#line 14 "agent_parser.yy"
} } // isc::agent
#line 2530 "agent_parser.h"




#endif // !YY_AGENT_AGENT_PARSER_H_INCLUDED
