// A Bison parser, made by GNU Bison 3.0.4.

// Skeleton interface for Bison LALR(1) parsers in C++

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

/**
 ** \file dhcp4_parser.h
 ** Define the isc::dhcp::parser class.
 */

// C++ LALR(1) parser skeleton written by Akim Demaille.

#ifndef YY_PARSER4_DHCP4_PARSER_H_INCLUDED
# define YY_PARSER4_DHCP4_PARSER_H_INCLUDED
// //                    "%code requires" blocks.
#line 17 "dhcp4_parser.yy" // lalr1.cc:377

#include <string>
#include <cc/data.h>
#include <dhcp/option.h>
#include <boost/lexical_cast.hpp>
#include <dhcp4/parser_context_decl.h>

using namespace isc::dhcp;
using namespace isc::data;
using namespace std;

#line 56 "dhcp4_parser.h" // lalr1.cc:377

# include <cassert>
# include <cstdlib> // std::abort
# include <iostream>
# include <stdexcept>
# include <string>
# include <vector>
# include "stack.hh"
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

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
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

/* Debug traces.  */
#ifndef PARSER4_DEBUG
# if defined YYDEBUG
#if YYDEBUG
#   define PARSER4_DEBUG 1
#  else
#   define PARSER4_DEBUG 0
#  endif
# else /* ! defined YYDEBUG */
#  define PARSER4_DEBUG 1
# endif /* ! defined YYDEBUG */
#endif  /* ! defined PARSER4_DEBUG */

#line 14 "dhcp4_parser.yy" // lalr1.cc:377
namespace isc { namespace dhcp {
#line 141 "dhcp4_parser.h" // lalr1.cc:377



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
      : yytypeid_ (YY_NULLPTR)
    {}

    /// Construct and fill.
    template <typename T>
    variant (const T& t)
      : yytypeid_ (&typeid (T))
    {
      YYASSERT (sizeof (T) <= S);
      new (yyas_<T> ()) T (t);
    }

    /// Destruction, allowed only if empty.
    ~variant ()
    {
      YYASSERT (!yytypeid_);
    }

    /// Instantiate an empty \a T in here.
    template <typename T>
    T&
    build ()
    {
      YYASSERT (!yytypeid_);
      YYASSERT (sizeof (T) <= S);
      yytypeid_ = & typeid (T);
      return *new (yyas_<T> ()) T;
    }

    /// Instantiate a \a T in here from \a t.
    template <typename T>
    T&
    build (const T& t)
    {
      YYASSERT (!yytypeid_);
      YYASSERT (sizeof (T) <= S);
      yytypeid_ = & typeid (T);
      return *new (yyas_<T> ()) T (t);
    }

    /// Accessor to a built \a T.
    template <typename T>
    T&
    as ()
    {
      YYASSERT (*yytypeid_ == typeid (T));
      YYASSERT (sizeof (T) <= S);
      return *yyas_<T> ();
    }

    /// Const accessor to a built \a T (for %printer).
    template <typename T>
    const T&
    as () const
    {
      YYASSERT (*yytypeid_ == typeid (T));
      YYASSERT (sizeof (T) <= S);
      return *yyas_<T> ();
    }

    /// Swap the content with \a other, of same type.
    ///
    /// Both variants must be built beforehand, because swapping the actual
    /// data requires reading it (with as()), and this is not possible on
    /// unconstructed variants: it would require some dynamic testing, which
    /// should not be the variant's responsability.
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
      build<T> ();
      swap<T> (other);
      other.destroy<T> ();
    }

    /// Copy the content of \a other to this.
    template <typename T>
    void
    copy (const self_type& other)
    {
      build<T> (other.as<T> ());
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
    self_type& operator=(const self_type&);
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
  class Dhcp4Parser
  {
  public:
#ifndef PARSER4_STYPE
    /// An auxiliary type to compute the largest semantic type.
    union union_type
    {
      // value
      // map_value
      // socket_type
      // outbound_interface_value
      // db_type
      // hr_mode
      // ncr_protocol_value
      // replace_client_name_value
      char dummy1[sizeof(ElementPtr)];

      // "boolean"
      char dummy2[sizeof(bool)];

      // "floating point"
      char dummy3[sizeof(double)];

      // "integer"
      char dummy4[sizeof(int64_t)];

      // "constant string"
      char dummy5[sizeof(std::string)];
};

    /// Symbol semantic values.
    typedef variant<sizeof(union_type)> semantic_type;
#else
    typedef PARSER4_STYPE semantic_type;
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
        TOKEN_DHCP4 = 265,
        TOKEN_INTERFACES_CONFIG = 266,
        TOKEN_INTERFACES = 267,
        TOKEN_DHCP_SOCKET_TYPE = 268,
        TOKEN_RAW = 269,
        TOKEN_UDP = 270,
        TOKEN_OUTBOUND_INTERFACE = 271,
        TOKEN_SAME_AS_INBOUND = 272,
        TOKEN_USE_ROUTING = 273,
        TOKEN_RE_DETECT = 274,
        TOKEN_ECHO_CLIENT_ID = 275,
        TOKEN_MATCH_CLIENT_ID = 276,
        TOKEN_NEXT_SERVER = 277,
        TOKEN_SERVER_HOSTNAME = 278,
        TOKEN_BOOT_FILE_NAME = 279,
        TOKEN_LEASE_DATABASE = 280,
        TOKEN_HOSTS_DATABASE = 281,
        TOKEN_HOSTS_DATABASES = 282,
        TOKEN_TYPE = 283,
        TOKEN_MEMFILE = 284,
        TOKEN_MYSQL = 285,
        TOKEN_POSTGRESQL = 286,
        TOKEN_CQL = 287,
        TOKEN_USER = 288,
        TOKEN_PASSWORD = 289,
        TOKEN_HOST = 290,
        TOKEN_PORT = 291,
        TOKEN_PERSIST = 292,
        TOKEN_LFC_INTERVAL = 293,
        TOKEN_READONLY = 294,
        TOKEN_CONNECT_TIMEOUT = 295,
        TOKEN_CONTACT_POINTS = 296,
        TOKEN_KEYSPACE = 297,
        TOKEN_MAX_RECONNECT_TRIES = 298,
        TOKEN_RECONNECT_WAIT_TIME = 299,
        TOKEN_REQUEST_TIMEOUT = 300,
        TOKEN_TCP_KEEPALIVE = 301,
        TOKEN_TCP_NODELAY = 302,
        TOKEN_VALID_LIFETIME = 303,
        TOKEN_RENEW_TIMER = 304,
        TOKEN_REBIND_TIMER = 305,
        TOKEN_DECLINE_PROBATION_PERIOD = 306,
        TOKEN_SUBNET4 = 307,
        TOKEN_SUBNET_4O6_INTERFACE = 308,
        TOKEN_SUBNET_4O6_INTERFACE_ID = 309,
        TOKEN_SUBNET_4O6_SUBNET = 310,
        TOKEN_OPTION_DEF = 311,
        TOKEN_OPTION_DATA = 312,
        TOKEN_NAME = 313,
        TOKEN_DATA = 314,
        TOKEN_CODE = 315,
        TOKEN_SPACE = 316,
        TOKEN_CSV_FORMAT = 317,
        TOKEN_ALWAYS_SEND = 318,
        TOKEN_RECORD_TYPES = 319,
        TOKEN_ENCAPSULATE = 320,
        TOKEN_ARRAY = 321,
        TOKEN_SHARED_NETWORKS = 322,
        TOKEN_POOLS = 323,
        TOKEN_POOL = 324,
        TOKEN_USER_CONTEXT = 325,
        TOKEN_COMMENT = 326,
        TOKEN_SUBNET = 327,
        TOKEN_INTERFACE = 328,
        TOKEN_INTERFACE_ID = 329,
        TOKEN_ID = 330,
        TOKEN_RAPID_COMMIT = 331,
        TOKEN_RESERVATION_MODE = 332,
        TOKEN_DISABLED = 333,
        TOKEN_OUT_OF_POOL = 334,
        TOKEN_ALL = 335,
        TOKEN_HOST_RESERVATION_IDENTIFIERS = 336,
        TOKEN_CLIENT_CLASSES = 337,
        TOKEN_REQUIRE_CLIENT_CLASSES = 338,
        TOKEN_TEST = 339,
        TOKEN_ONLY_IF_REQUIRED = 340,
        TOKEN_CLIENT_CLASS = 341,
        TOKEN_RESERVATIONS = 342,
        TOKEN_DUID = 343,
        TOKEN_HW_ADDRESS = 344,
        TOKEN_CIRCUIT_ID = 345,
        TOKEN_CLIENT_ID = 346,
        TOKEN_HOSTNAME = 347,
        TOKEN_FLEX_ID = 348,
        TOKEN_RELAY = 349,
        TOKEN_IP_ADDRESS = 350,
        TOKEN_IP_ADDRESSES = 351,
        TOKEN_HOOKS_LIBRARIES = 352,
        TOKEN_LIBRARY = 353,
        TOKEN_PARAMETERS = 354,
        TOKEN_EXPIRED_LEASES_PROCESSING = 355,
        TOKEN_RECLAIM_TIMER_WAIT_TIME = 356,
        TOKEN_FLUSH_RECLAIMED_TIMER_WAIT_TIME = 357,
        TOKEN_HOLD_RECLAIMED_TIME = 358,
        TOKEN_MAX_RECLAIM_LEASES = 359,
        TOKEN_MAX_RECLAIM_TIME = 360,
        TOKEN_UNWARNED_RECLAIM_CYCLES = 361,
        TOKEN_DHCP4O6_PORT = 362,
        TOKEN_CONTROL_SOCKET = 363,
        TOKEN_SOCKET_TYPE = 364,
        TOKEN_SOCKET_NAME = 365,
        TOKEN_DHCP_DDNS = 366,
        TOKEN_ENABLE_UPDATES = 367,
        TOKEN_QUALIFYING_SUFFIX = 368,
        TOKEN_SERVER_IP = 369,
        TOKEN_SERVER_PORT = 370,
        TOKEN_SENDER_IP = 371,
        TOKEN_SENDER_PORT = 372,
        TOKEN_MAX_QUEUE_SIZE = 373,
        TOKEN_NCR_PROTOCOL = 374,
        TOKEN_NCR_FORMAT = 375,
        TOKEN_ALWAYS_INCLUDE_FQDN = 376,
        TOKEN_OVERRIDE_NO_UPDATE = 377,
        TOKEN_OVERRIDE_CLIENT_UPDATE = 378,
        TOKEN_REPLACE_CLIENT_NAME = 379,
        TOKEN_GENERATED_PREFIX = 380,
        TOKEN_TCP = 381,
        TOKEN_JSON = 382,
        TOKEN_WHEN_PRESENT = 383,
        TOKEN_NEVER = 384,
        TOKEN_ALWAYS = 385,
        TOKEN_WHEN_NOT_PRESENT = 386,
        TOKEN_LOGGING = 387,
        TOKEN_LOGGERS = 388,
        TOKEN_OUTPUT_OPTIONS = 389,
        TOKEN_OUTPUT = 390,
        TOKEN_DEBUGLEVEL = 391,
        TOKEN_SEVERITY = 392,
        TOKEN_FLUSH = 393,
        TOKEN_MAXSIZE = 394,
        TOKEN_MAXVER = 395,
        TOKEN_DHCP6 = 396,
        TOKEN_DHCPDDNS = 397,
        TOKEN_CONTROL_AGENT = 398,
        TOKEN_TOPLEVEL_JSON = 399,
        TOKEN_TOPLEVEL_DHCP4 = 400,
        TOKEN_SUB_DHCP4 = 401,
        TOKEN_SUB_INTERFACES4 = 402,
        TOKEN_SUB_SUBNET4 = 403,
        TOKEN_SUB_POOL4 = 404,
        TOKEN_SUB_RESERVATION = 405,
        TOKEN_SUB_OPTION_DEFS = 406,
        TOKEN_SUB_OPTION_DEF = 407,
        TOKEN_SUB_OPTION_DATA = 408,
        TOKEN_SUB_HOOKS_LIBRARY = 409,
        TOKEN_SUB_DHCP_DDNS = 410,
        TOKEN_SUB_LOGGING = 411,
        TOKEN_STRING = 412,
        TOKEN_INTEGER = 413,
        TOKEN_FLOAT = 414,
        TOKEN_BOOLEAN = 415
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
    /// via type_get().
    ///
    /// Provide access to semantic value and location.
    template <typename Base>
    struct basic_symbol : Base
    {
      /// Alias to Base.
      typedef Base super_type;

      /// Default constructor.
      basic_symbol ();

      /// Copy constructor.
      basic_symbol (const basic_symbol& other);

      /// Constructor for valueless symbols, and symbols from each type.

  basic_symbol (typename Base::kind_type t, const location_type& l);

  basic_symbol (typename Base::kind_type t, const ElementPtr v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const bool v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const double v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const int64_t v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const std::string v, const location_type& l);


      /// Constructor for symbols with semantic value.
      basic_symbol (typename Base::kind_type t,
                    const semantic_type& v,
                    const location_type& l);

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
      /// Assignment operator.
      basic_symbol& operator= (const basic_symbol& other);
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

    // Symbol constructors declarations.
    static inline
    symbol_type
    make_END (const location_type& l);

    static inline
    symbol_type
    make_COMMA (const location_type& l);

    static inline
    symbol_type
    make_COLON (const location_type& l);

    static inline
    symbol_type
    make_LSQUARE_BRACKET (const location_type& l);

    static inline
    symbol_type
    make_RSQUARE_BRACKET (const location_type& l);

    static inline
    symbol_type
    make_LCURLY_BRACKET (const location_type& l);

    static inline
    symbol_type
    make_RCURLY_BRACKET (const location_type& l);

    static inline
    symbol_type
    make_NULL_TYPE (const location_type& l);

    static inline
    symbol_type
    make_DHCP4 (const location_type& l);

    static inline
    symbol_type
    make_INTERFACES_CONFIG (const location_type& l);

    static inline
    symbol_type
    make_INTERFACES (const location_type& l);

    static inline
    symbol_type
    make_DHCP_SOCKET_TYPE (const location_type& l);

    static inline
    symbol_type
    make_RAW (const location_type& l);

    static inline
    symbol_type
    make_UDP (const location_type& l);

    static inline
    symbol_type
    make_OUTBOUND_INTERFACE (const location_type& l);

    static inline
    symbol_type
    make_SAME_AS_INBOUND (const location_type& l);

    static inline
    symbol_type
    make_USE_ROUTING (const location_type& l);

    static inline
    symbol_type
    make_RE_DETECT (const location_type& l);

    static inline
    symbol_type
    make_ECHO_CLIENT_ID (const location_type& l);

    static inline
    symbol_type
    make_MATCH_CLIENT_ID (const location_type& l);

    static inline
    symbol_type
    make_NEXT_SERVER (const location_type& l);

    static inline
    symbol_type
    make_SERVER_HOSTNAME (const location_type& l);

    static inline
    symbol_type
    make_BOOT_FILE_NAME (const location_type& l);

    static inline
    symbol_type
    make_LEASE_DATABASE (const location_type& l);

    static inline
    symbol_type
    make_HOSTS_DATABASE (const location_type& l);

    static inline
    symbol_type
    make_HOSTS_DATABASES (const location_type& l);

    static inline
    symbol_type
    make_TYPE (const location_type& l);

    static inline
    symbol_type
    make_MEMFILE (const location_type& l);

    static inline
    symbol_type
    make_MYSQL (const location_type& l);

    static inline
    symbol_type
    make_POSTGRESQL (const location_type& l);

    static inline
    symbol_type
    make_CQL (const location_type& l);

    static inline
    symbol_type
    make_USER (const location_type& l);

    static inline
    symbol_type
    make_PASSWORD (const location_type& l);

    static inline
    symbol_type
    make_HOST (const location_type& l);

    static inline
    symbol_type
    make_PORT (const location_type& l);

    static inline
    symbol_type
    make_PERSIST (const location_type& l);

    static inline
    symbol_type
    make_LFC_INTERVAL (const location_type& l);

    static inline
    symbol_type
    make_READONLY (const location_type& l);

    static inline
    symbol_type
    make_CONNECT_TIMEOUT (const location_type& l);

    static inline
    symbol_type
    make_CONTACT_POINTS (const location_type& l);

    static inline
    symbol_type
    make_KEYSPACE (const location_type& l);

    static inline
    symbol_type
    make_MAX_RECONNECT_TRIES (const location_type& l);

    static inline
    symbol_type
    make_RECONNECT_WAIT_TIME (const location_type& l);

    static inline
    symbol_type
    make_REQUEST_TIMEOUT (const location_type& l);

    static inline
    symbol_type
    make_TCP_KEEPALIVE (const location_type& l);

    static inline
    symbol_type
    make_TCP_NODELAY (const location_type& l);

    static inline
    symbol_type
    make_VALID_LIFETIME (const location_type& l);

    static inline
    symbol_type
    make_RENEW_TIMER (const location_type& l);

    static inline
    symbol_type
    make_REBIND_TIMER (const location_type& l);

    static inline
    symbol_type
    make_DECLINE_PROBATION_PERIOD (const location_type& l);

    static inline
    symbol_type
    make_SUBNET4 (const location_type& l);

    static inline
    symbol_type
    make_SUBNET_4O6_INTERFACE (const location_type& l);

    static inline
    symbol_type
    make_SUBNET_4O6_INTERFACE_ID (const location_type& l);

    static inline
    symbol_type
    make_SUBNET_4O6_SUBNET (const location_type& l);

    static inline
    symbol_type
    make_OPTION_DEF (const location_type& l);

    static inline
    symbol_type
    make_OPTION_DATA (const location_type& l);

    static inline
    symbol_type
    make_NAME (const location_type& l);

    static inline
    symbol_type
    make_DATA (const location_type& l);

    static inline
    symbol_type
    make_CODE (const location_type& l);

    static inline
    symbol_type
    make_SPACE (const location_type& l);

    static inline
    symbol_type
    make_CSV_FORMAT (const location_type& l);

    static inline
    symbol_type
    make_ALWAYS_SEND (const location_type& l);

    static inline
    symbol_type
    make_RECORD_TYPES (const location_type& l);

    static inline
    symbol_type
    make_ENCAPSULATE (const location_type& l);

    static inline
    symbol_type
    make_ARRAY (const location_type& l);

    static inline
    symbol_type
    make_SHARED_NETWORKS (const location_type& l);

    static inline
    symbol_type
    make_POOLS (const location_type& l);

    static inline
    symbol_type
    make_POOL (const location_type& l);

    static inline
    symbol_type
    make_USER_CONTEXT (const location_type& l);

    static inline
    symbol_type
    make_COMMENT (const location_type& l);

    static inline
    symbol_type
    make_SUBNET (const location_type& l);

    static inline
    symbol_type
    make_INTERFACE (const location_type& l);

    static inline
    symbol_type
    make_INTERFACE_ID (const location_type& l);

    static inline
    symbol_type
    make_ID (const location_type& l);

    static inline
    symbol_type
    make_RAPID_COMMIT (const location_type& l);

    static inline
    symbol_type
    make_RESERVATION_MODE (const location_type& l);

    static inline
    symbol_type
    make_DISABLED (const location_type& l);

    static inline
    symbol_type
    make_OUT_OF_POOL (const location_type& l);

    static inline
    symbol_type
    make_ALL (const location_type& l);

    static inline
    symbol_type
    make_HOST_RESERVATION_IDENTIFIERS (const location_type& l);

    static inline
    symbol_type
    make_CLIENT_CLASSES (const location_type& l);

    static inline
    symbol_type
    make_REQUIRE_CLIENT_CLASSES (const location_type& l);

    static inline
    symbol_type
    make_TEST (const location_type& l);

    static inline
    symbol_type
    make_ONLY_IF_REQUIRED (const location_type& l);

    static inline
    symbol_type
    make_CLIENT_CLASS (const location_type& l);

    static inline
    symbol_type
    make_RESERVATIONS (const location_type& l);

    static inline
    symbol_type
    make_DUID (const location_type& l);

    static inline
    symbol_type
    make_HW_ADDRESS (const location_type& l);

    static inline
    symbol_type
    make_CIRCUIT_ID (const location_type& l);

    static inline
    symbol_type
    make_CLIENT_ID (const location_type& l);

    static inline
    symbol_type
    make_HOSTNAME (const location_type& l);

    static inline
    symbol_type
    make_FLEX_ID (const location_type& l);

    static inline
    symbol_type
    make_RELAY (const location_type& l);

    static inline
    symbol_type
    make_IP_ADDRESS (const location_type& l);

    static inline
    symbol_type
    make_IP_ADDRESSES (const location_type& l);

    static inline
    symbol_type
    make_HOOKS_LIBRARIES (const location_type& l);

    static inline
    symbol_type
    make_LIBRARY (const location_type& l);

    static inline
    symbol_type
    make_PARAMETERS (const location_type& l);

    static inline
    symbol_type
    make_EXPIRED_LEASES_PROCESSING (const location_type& l);

    static inline
    symbol_type
    make_RECLAIM_TIMER_WAIT_TIME (const location_type& l);

    static inline
    symbol_type
    make_FLUSH_RECLAIMED_TIMER_WAIT_TIME (const location_type& l);

    static inline
    symbol_type
    make_HOLD_RECLAIMED_TIME (const location_type& l);

    static inline
    symbol_type
    make_MAX_RECLAIM_LEASES (const location_type& l);

    static inline
    symbol_type
    make_MAX_RECLAIM_TIME (const location_type& l);

    static inline
    symbol_type
    make_UNWARNED_RECLAIM_CYCLES (const location_type& l);

    static inline
    symbol_type
    make_DHCP4O6_PORT (const location_type& l);

    static inline
    symbol_type
    make_CONTROL_SOCKET (const location_type& l);

    static inline
    symbol_type
    make_SOCKET_TYPE (const location_type& l);

    static inline
    symbol_type
    make_SOCKET_NAME (const location_type& l);

    static inline
    symbol_type
    make_DHCP_DDNS (const location_type& l);

    static inline
    symbol_type
    make_ENABLE_UPDATES (const location_type& l);

    static inline
    symbol_type
    make_QUALIFYING_SUFFIX (const location_type& l);

    static inline
    symbol_type
    make_SERVER_IP (const location_type& l);

    static inline
    symbol_type
    make_SERVER_PORT (const location_type& l);

    static inline
    symbol_type
    make_SENDER_IP (const location_type& l);

    static inline
    symbol_type
    make_SENDER_PORT (const location_type& l);

    static inline
    symbol_type
    make_MAX_QUEUE_SIZE (const location_type& l);

    static inline
    symbol_type
    make_NCR_PROTOCOL (const location_type& l);

    static inline
    symbol_type
    make_NCR_FORMAT (const location_type& l);

    static inline
    symbol_type
    make_ALWAYS_INCLUDE_FQDN (const location_type& l);

    static inline
    symbol_type
    make_OVERRIDE_NO_UPDATE (const location_type& l);

    static inline
    symbol_type
    make_OVERRIDE_CLIENT_UPDATE (const location_type& l);

    static inline
    symbol_type
    make_REPLACE_CLIENT_NAME (const location_type& l);

    static inline
    symbol_type
    make_GENERATED_PREFIX (const location_type& l);

    static inline
    symbol_type
    make_TCP (const location_type& l);

    static inline
    symbol_type
    make_JSON (const location_type& l);

    static inline
    symbol_type
    make_WHEN_PRESENT (const location_type& l);

    static inline
    symbol_type
    make_NEVER (const location_type& l);

    static inline
    symbol_type
    make_ALWAYS (const location_type& l);

    static inline
    symbol_type
    make_WHEN_NOT_PRESENT (const location_type& l);

    static inline
    symbol_type
    make_LOGGING (const location_type& l);

    static inline
    symbol_type
    make_LOGGERS (const location_type& l);

    static inline
    symbol_type
    make_OUTPUT_OPTIONS (const location_type& l);

    static inline
    symbol_type
    make_OUTPUT (const location_type& l);

    static inline
    symbol_type
    make_DEBUGLEVEL (const location_type& l);

    static inline
    symbol_type
    make_SEVERITY (const location_type& l);

    static inline
    symbol_type
    make_FLUSH (const location_type& l);

    static inline
    symbol_type
    make_MAXSIZE (const location_type& l);

    static inline
    symbol_type
    make_MAXVER (const location_type& l);

    static inline
    symbol_type
    make_DHCP6 (const location_type& l);

    static inline
    symbol_type
    make_DHCPDDNS (const location_type& l);

    static inline
    symbol_type
    make_CONTROL_AGENT (const location_type& l);

    static inline
    symbol_type
    make_TOPLEVEL_JSON (const location_type& l);

    static inline
    symbol_type
    make_TOPLEVEL_DHCP4 (const location_type& l);

    static inline
    symbol_type
    make_SUB_DHCP4 (const location_type& l);

    static inline
    symbol_type
    make_SUB_INTERFACES4 (const location_type& l);

    static inline
    symbol_type
    make_SUB_SUBNET4 (const location_type& l);

    static inline
    symbol_type
    make_SUB_POOL4 (const location_type& l);

    static inline
    symbol_type
    make_SUB_RESERVATION (const location_type& l);

    static inline
    symbol_type
    make_SUB_OPTION_DEFS (const location_type& l);

    static inline
    symbol_type
    make_SUB_OPTION_DEF (const location_type& l);

    static inline
    symbol_type
    make_SUB_OPTION_DATA (const location_type& l);

    static inline
    symbol_type
    make_SUB_HOOKS_LIBRARY (const location_type& l);

    static inline
    symbol_type
    make_SUB_DHCP_DDNS (const location_type& l);

    static inline
    symbol_type
    make_SUB_LOGGING (const location_type& l);

    static inline
    symbol_type
    make_STRING (const std::string& v, const location_type& l);

    static inline
    symbol_type
    make_INTEGER (const int64_t& v, const location_type& l);

    static inline
    symbol_type
    make_FLOAT (const double& v, const location_type& l);

    static inline
    symbol_type
    make_BOOLEAN (const bool& v, const location_type& l);


    /// Build a parser object.
    Dhcp4Parser (isc::dhcp::Parser4Context& ctx_yyarg);
    virtual ~Dhcp4Parser ();

    /// Parse.
    /// \returns  0 iff parsing succeeded.
    virtual int parse ();

#if PARSER4_DEBUG
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

  private:
    /// This class is not copyable.
    Dhcp4Parser (const Dhcp4Parser&);
    Dhcp4Parser& operator= (const Dhcp4Parser&);

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

    static const short int yypact_ninf_;
    static const signed char yytable_ninf_;

    /// Convert a scanner token number \a t to a symbol number.
    static token_number_type yytranslate_ (token_type t);

    // Tables.
  // YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
  // STATE-NUM.
  static const short int yypact_[];

  // YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
  // Performed when YYTABLE does not specify something else to do.  Zero
  // means the default is an error.
  static const unsigned short int yydefact_[];

  // YYPGOTO[NTERM-NUM].
  static const short int yypgoto_[];

  // YYDEFGOTO[NTERM-NUM].
  static const short int yydefgoto_[];

  // YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
  // positive, shift that token.  If negative, reduce the rule whose
  // number is the opposite.  If YYTABLE_NINF, syntax error.
  static const unsigned short int yytable_[];

  static const short int yycheck_[];

  // YYSTOS[STATE-NUM] -- The (internal number of the) accessing
  // symbol of state STATE-NUM.
  static const unsigned short int yystos_[];

  // YYR1[YYN] -- Symbol number of symbol that rule YYN derives.
  static const unsigned short int yyr1_[];

  // YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.
  static const unsigned char yyr2_[];


    /// Convert the symbol name \a n to a form suitable for a diagnostic.
    static std::string yytnamerr_ (const char *n);


    /// For a symbol, its name in clear.
    static const char* const yytname_[];
#if PARSER4_DEBUG
  // YYRLINE[YYN] -- Source line where rule number YYN was defined.
  static const unsigned short int yyrline_[];
    /// Report on the debug stream that the rule \a r is going to be reduced.
    virtual void yy_reduce_print_ (int r);
    /// Print the state stack on the debug stream.
    virtual void yystack_print_ ();

    // Debugging.
    int yydebug_;
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
      /// Steal the contents from \a sym to build this.
      stack_symbol_type (state_type s, symbol_type& sym);
      /// Assignment, needed by push_back.
      stack_symbol_type& operator= (const stack_symbol_type& that);
    };

    /// Stack type.
    typedef stack<stack_symbol_type> stack_type;

    /// The stack.
    stack_type yystack_;

    /// Push a new state on the stack.
    /// \param m    a debug message to display
    ///             if null, no trace is output.
    /// \param s    the symbol
    /// \warning the contents of \a s.value is stolen.
    void yypush_ (const char* m, stack_symbol_type& s);

    /// Push a new look ahead token on the state on the stack.
    /// \param m    a debug message to display
    ///             if null, no trace is output.
    /// \param s    the state
    /// \param sym  the symbol (for its value and location).
    /// \warning the contents of \a s.value is stolen.
    void yypush_ (const char* m, state_type s, symbol_type& sym);

    /// Pop \a n symbols the three stacks.
    void yypop_ (unsigned int n = 1);

    /// Constants.
    enum
    {
      yyeof_ = 0,
      yylast_ = 935,     ///< Last index in yytable_.
      yynnts_ = 353,  ///< Number of nonterminal symbols.
      yyfinal_ = 28, ///< Termination state number.
      yyterror_ = 1,
      yyerrcode_ = 256,
      yyntokens_ = 161  ///< Number of tokens.
    };


    // User arguments.
    isc::dhcp::Parser4Context& ctx;
  };

  // Symbol number corresponding to token number t.
  inline
  Dhcp4Parser::token_number_type
  Dhcp4Parser::yytranslate_ (token_type t)
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
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   111,   112,   113,   114,
     115,   116,   117,   118,   119,   120,   121,   122,   123,   124,
     125,   126,   127,   128,   129,   130,   131,   132,   133,   134,
     135,   136,   137,   138,   139,   140,   141,   142,   143,   144,
     145,   146,   147,   148,   149,   150,   151,   152,   153,   154,
     155,   156,   157,   158,   159,   160
    };
    const unsigned int user_token_number_max_ = 415;
    const token_number_type undef_token_ = 2;

    if (static_cast<int>(t) <= yyeof_)
      return yyeof_;
    else if (static_cast<unsigned int> (t) <= user_token_number_max_)
      return translate_table[t];
    else
      return undef_token_;
  }

  inline
  Dhcp4Parser::syntax_error::syntax_error (const location_type& l, const std::string& m)
    : std::runtime_error (m)
    , location (l)
  {}

  // basic_symbol.
  template <typename Base>
  inline
  Dhcp4Parser::basic_symbol<Base>::basic_symbol ()
    : value ()
  {}

  template <typename Base>
  inline
  Dhcp4Parser::basic_symbol<Base>::basic_symbol (const basic_symbol& other)
    : Base (other)
    , value ()
    , location (other.location)
  {
      switch (other.type_get ())
    {
      case 176: // value
      case 180: // map_value
      case 218: // socket_type
      case 221: // outbound_interface_value
      case 237: // db_type
      case 321: // hr_mode
      case 469: // ncr_protocol_value
      case 477: // replace_client_name_value
        value.copy< ElementPtr > (other.value);
        break;

      case 160: // "boolean"
        value.copy< bool > (other.value);
        break;

      case 159: // "floating point"
        value.copy< double > (other.value);
        break;

      case 158: // "integer"
        value.copy< int64_t > (other.value);
        break;

      case 157: // "constant string"
        value.copy< std::string > (other.value);
        break;

      default:
        break;
    }

  }


  template <typename Base>
  inline
  Dhcp4Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const semantic_type& v, const location_type& l)
    : Base (t)
    , value ()
    , location (l)
  {
    (void) v;
      switch (this->type_get ())
    {
      case 176: // value
      case 180: // map_value
      case 218: // socket_type
      case 221: // outbound_interface_value
      case 237: // db_type
      case 321: // hr_mode
      case 469: // ncr_protocol_value
      case 477: // replace_client_name_value
        value.copy< ElementPtr > (v);
        break;

      case 160: // "boolean"
        value.copy< bool > (v);
        break;

      case 159: // "floating point"
        value.copy< double > (v);
        break;

      case 158: // "integer"
        value.copy< int64_t > (v);
        break;

      case 157: // "constant string"
        value.copy< std::string > (v);
        break;

      default:
        break;
    }
}


  // Implementation of basic_symbol constructor for each type.

  template <typename Base>
  Dhcp4Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const location_type& l)
    : Base (t)
    , value ()
    , location (l)
  {}

  template <typename Base>
  Dhcp4Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const ElementPtr v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  Dhcp4Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const bool v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  Dhcp4Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const double v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  Dhcp4Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const int64_t v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  Dhcp4Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const std::string v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}


  template <typename Base>
  inline
  Dhcp4Parser::basic_symbol<Base>::~basic_symbol ()
  {
    clear ();
  }

  template <typename Base>
  inline
  void
  Dhcp4Parser::basic_symbol<Base>::clear ()
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
      case 176: // value
      case 180: // map_value
      case 218: // socket_type
      case 221: // outbound_interface_value
      case 237: // db_type
      case 321: // hr_mode
      case 469: // ncr_protocol_value
      case 477: // replace_client_name_value
        value.template destroy< ElementPtr > ();
        break;

      case 160: // "boolean"
        value.template destroy< bool > ();
        break;

      case 159: // "floating point"
        value.template destroy< double > ();
        break;

      case 158: // "integer"
        value.template destroy< int64_t > ();
        break;

      case 157: // "constant string"
        value.template destroy< std::string > ();
        break;

      default:
        break;
    }

    Base::clear ();
  }

  template <typename Base>
  inline
  bool
  Dhcp4Parser::basic_symbol<Base>::empty () const
  {
    return Base::type_get () == empty_symbol;
  }

  template <typename Base>
  inline
  void
  Dhcp4Parser::basic_symbol<Base>::move (basic_symbol& s)
  {
    super_type::move(s);
      switch (this->type_get ())
    {
      case 176: // value
      case 180: // map_value
      case 218: // socket_type
      case 221: // outbound_interface_value
      case 237: // db_type
      case 321: // hr_mode
      case 469: // ncr_protocol_value
      case 477: // replace_client_name_value
        value.move< ElementPtr > (s.value);
        break;

      case 160: // "boolean"
        value.move< bool > (s.value);
        break;

      case 159: // "floating point"
        value.move< double > (s.value);
        break;

      case 158: // "integer"
        value.move< int64_t > (s.value);
        break;

      case 157: // "constant string"
        value.move< std::string > (s.value);
        break;

      default:
        break;
    }

    location = s.location;
  }

  // by_type.
  inline
  Dhcp4Parser::by_type::by_type ()
    : type (empty_symbol)
  {}

  inline
  Dhcp4Parser::by_type::by_type (const by_type& other)
    : type (other.type)
  {}

  inline
  Dhcp4Parser::by_type::by_type (token_type t)
    : type (yytranslate_ (t))
  {}

  inline
  void
  Dhcp4Parser::by_type::clear ()
  {
    type = empty_symbol;
  }

  inline
  void
  Dhcp4Parser::by_type::move (by_type& that)
  {
    type = that.type;
    that.clear ();
  }

  inline
  int
  Dhcp4Parser::by_type::type_get () const
  {
    return type;
  }

  inline
  Dhcp4Parser::token_type
  Dhcp4Parser::by_type::token () const
  {
    // YYTOKNUM[NUM] -- (External) token number corresponding to the
    // (internal) symbol number NUM (which must be that of a token).  */
    static
    const unsigned short int
    yytoken_number_[] =
    {
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330,   331,   332,   333,   334,
     335,   336,   337,   338,   339,   340,   341,   342,   343,   344,
     345,   346,   347,   348,   349,   350,   351,   352,   353,   354,
     355,   356,   357,   358,   359,   360,   361,   362,   363,   364,
     365,   366,   367,   368,   369,   370,   371,   372,   373,   374,
     375,   376,   377,   378,   379,   380,   381,   382,   383,   384,
     385,   386,   387,   388,   389,   390,   391,   392,   393,   394,
     395,   396,   397,   398,   399,   400,   401,   402,   403,   404,
     405,   406,   407,   408,   409,   410,   411,   412,   413,   414,
     415
    };
    return static_cast<token_type> (yytoken_number_[type]);
  }
  // Implementation of make_symbol for each symbol type.
  Dhcp4Parser::symbol_type
  Dhcp4Parser::make_END (const location_type& l)
  {
    return symbol_type (token::TOKEN_END, l);
  }

  Dhcp4Parser::symbol_type
  Dhcp4Parser::make_COMMA (const location_type& l)
  {
    return symbol_type (token::TOKEN_COMMA, l);
  }

  Dhcp4Parser::symbol_type
  Dhcp4Parser::make_COLON (const location_type& l)
  {
    return symbol_type (token::TOKEN_COLON, l);
  }

  Dhcp4Parser::symbol_type
  Dhcp4Parser::make_LSQUARE_BRACKET (const location_type& l)
  {
    return symbol_type (token::TOKEN_LSQUARE_BRACKET, l);
  }

  Dhcp4Parser::symbol_type
  Dhcp4Parser::make_RSQUARE_BRACKET (const location_type& l)
  {
    return symbol_type (token::TOKEN_RSQUARE_BRACKET, l);
  }

  Dhcp4Parser::symbol_type
  Dhcp4Parser::make_LCURLY_BRACKET (const location_type& l)
  {
    return symbol_type (token::TOKEN_LCURLY_BRACKET, l);
  }

  Dhcp4Parser::symbol_type
  Dhcp4Parser::make_RCURLY_BRACKET (const location_type& l)
  {
    return symbol_type (token::TOKEN_RCURLY_BRACKET, l);
  }

  Dhcp4Parser::symbol_type
  Dhcp4Parser::make_NULL_TYPE (const location_type& l)
  {
    return symbol_type (token::TOKEN_NULL_TYPE, l);
  }

  Dhcp4Parser::symbol_type
  Dhcp4Parser::make_DHCP4 (const location_type& l)
  {
    return symbol_type (token::TOKEN_DHCP4, l);
  }

  Dhcp4Parser::symbol_type
  Dhcp4Parser::make_INTERFACES_CONFIG (const location_type& l)
  {
    return symbol_type (token::TOKEN_INTERFACES_CONFIG, l);
  }

  Dhcp4Parser::symbol_type
  Dhcp4Parser::make_INTERFACES (const location_type& l)
  {
    return symbol_type (token::TOKEN_INTERFACES, l);
  }

  Dhcp4Parser::symbol_type
  Dhcp4Parser::make_DHCP_SOCKET_TYPE (const location_type& l)
  {
    return symbol_type (token::TOKEN_DHCP_SOCKET_TYPE, l);
  }

  Dhcp4Parser::symbol_type
  Dhcp4Parser::make_RAW (const location_type& l)
  {
    return symbol_type (token::TOKEN_RAW, l);
  }

  Dhcp4Parser::symbol_type
  Dhcp4Parser::make_UDP (const location_type& l)
  {
    return symbol_type (token::TOKEN_UDP, l);
  }

  Dhcp4Parser::symbol_type
  Dhcp4Parser::make_OUTBOUND_INTERFACE (const location_type& l)
  {
    return symbol_type (token::TOKEN_OUTBOUND_INTERFACE, l);
  }

  Dhcp4Parser::symbol_type
  Dhcp4Parser::make_SAME_AS_INBOUND (const location_type& l)
  {
    return symbol_type (token::TOKEN_SAME_AS_INBOUND, l);
  }

  Dhcp4Parser::symbol_type
  Dhcp4Parser::make_USE_ROUTING (const location_type& l)
  {
    return symbol_type (token::TOKEN_USE_ROUTING, l);
  }

  Dhcp4Parser::symbol_type
  Dhcp4Parser::make_RE_DETECT (const location_type& l)
  {
    return symbol_type (token::TOKEN_RE_DETECT, l);
  }

  Dhcp4Parser::symbol_type
  Dhcp4Parser::make_ECHO_CLIENT_ID (const location_type& l)
  {
    return symbol_type (token::TOKEN_ECHO_CLIENT_ID, l);
  }

  Dhcp4Parser::symbol_type
  Dhcp4Parser::make_MATCH_CLIENT_ID (const location_type& l)
  {
    return symbol_type (token::TOKEN_MATCH_CLIENT_ID, l);
  }

  Dhcp4Parser::symbol_type
  Dhcp4Parser::make_NEXT_SERVER (const location_type& l)
  {
    return symbol_type (token::TOKEN_NEXT_SERVER, l);
  }

  Dhcp4Parser::symbol_type
  Dhcp4Parser::make_SERVER_HOSTNAME (const location_type& l)
  {
    return symbol_type (token::TOKEN_SERVER_HOSTNAME, l);
  }

  Dhcp4Parser::symbol_type
  Dhcp4Parser::make_BOOT_FILE_NAME (const location_type& l)
  {
    return symbol_type (token::TOKEN_BOOT_FILE_NAME, l);
  }

  Dhcp4Parser::symbol_type
  Dhcp4Parser::make_LEASE_DATABASE (const location_type& l)
  {
    return symbol_type (token::TOKEN_LEASE_DATABASE, l);
  }

  Dhcp4Parser::symbol_type
  Dhcp4Parser::make_HOSTS_DATABASE (const location_type& l)
  {
    return symbol_type (token::TOKEN_HOSTS_DATABASE, l);
  }

  Dhcp4Parser::symbol_type
  Dhcp4Parser::make_HOSTS_DATABASES (const location_type& l)
  {
    return symbol_type (token::TOKEN_HOSTS_DATABASES, l);
  }

  Dhcp4Parser::symbol_type
  Dhcp4Parser::make_TYPE (const location_type& l)
  {
    return symbol_type (token::TOKEN_TYPE, l);
  }

  Dhcp4Parser::symbol_type
  Dhcp4Parser::make_MEMFILE (const location_type& l)
  {
    return symbol_type (token::TOKEN_MEMFILE, l);
  }

  Dhcp4Parser::symbol_type
  Dhcp4Parser::make_MYSQL (const location_type& l)
  {
    return symbol_type (token::TOKEN_MYSQL, l);
  }

  Dhcp4Parser::symbol_type
  Dhcp4Parser::make_POSTGRESQL (const location_type& l)
  {
    return symbol_type (token::TOKEN_POSTGRESQL, l);
  }

  Dhcp4Parser::symbol_type
  Dhcp4Parser::make_CQL (const location_type& l)
  {
    return symbol_type (token::TOKEN_CQL, l);
  }

  Dhcp4Parser::symbol_type
  Dhcp4Parser::make_USER (const location_type& l)
  {
    return symbol_type (token::TOKEN_USER, l);
  }

  Dhcp4Parser::symbol_type
  Dhcp4Parser::make_PASSWORD (const location_type& l)
  {
    return symbol_type (token::TOKEN_PASSWORD, l);
  }

  Dhcp4Parser::symbol_type
  Dhcp4Parser::make_HOST (const location_type& l)
  {
    return symbol_type (token::TOKEN_HOST, l);
  }

  Dhcp4Parser::symbol_type
  Dhcp4Parser::make_PORT (const location_type& l)
  {
    return symbol_type (token::TOKEN_PORT, l);
  }

  Dhcp4Parser::symbol_type
  Dhcp4Parser::make_PERSIST (const location_type& l)
  {
    return symbol_type (token::TOKEN_PERSIST, l);
  }

  Dhcp4Parser::symbol_type
  Dhcp4Parser::make_LFC_INTERVAL (const location_type& l)
  {
    return symbol_type (token::TOKEN_LFC_INTERVAL, l);
  }

  Dhcp4Parser::symbol_type
  Dhcp4Parser::make_READONLY (const location_type& l)
  {
    return symbol_type (token::TOKEN_READONLY, l);
  }

  Dhcp4Parser::symbol_type
  Dhcp4Parser::make_CONNECT_TIMEOUT (const location_type& l)
  {
    return symbol_type (token::TOKEN_CONNECT_TIMEOUT, l);
  }

  Dhcp4Parser::symbol_type
  Dhcp4Parser::make_CONTACT_POINTS (const location_type& l)
  {
    return symbol_type (token::TOKEN_CONTACT_POINTS, l);
  }

  Dhcp4Parser::symbol_type
  Dhcp4Parser::make_KEYSPACE (const location_type& l)
  {
    return symbol_type (token::TOKEN_KEYSPACE, l);
  }

  Dhcp4Parser::symbol_type
  Dhcp4Parser::make_MAX_RECONNECT_TRIES (const location_type& l)
  {
    return symbol_type (token::TOKEN_MAX_RECONNECT_TRIES, l);
  }

  Dhcp4Parser::symbol_type
  Dhcp4Parser::make_RECONNECT_WAIT_TIME (const location_type& l)
  {
    return symbol_type (token::TOKEN_RECONNECT_WAIT_TIME, l);
  }

  Dhcp4Parser::symbol_type
  Dhcp4Parser::make_REQUEST_TIMEOUT (const location_type& l)
  {
    return symbol_type (token::TOKEN_REQUEST_TIMEOUT, l);
  }

  Dhcp4Parser::symbol_type
  Dhcp4Parser::make_TCP_KEEPALIVE (const location_type& l)
  {
    return symbol_type (token::TOKEN_TCP_KEEPALIVE, l);
  }

  Dhcp4Parser::symbol_type
  Dhcp4Parser::make_TCP_NODELAY (const location_type& l)
  {
    return symbol_type (token::TOKEN_TCP_NODELAY, l);
  }

  Dhcp4Parser::symbol_type
  Dhcp4Parser::make_VALID_LIFETIME (const location_type& l)
  {
    return symbol_type (token::TOKEN_VALID_LIFETIME, l);
  }

  Dhcp4Parser::symbol_type
  Dhcp4Parser::make_RENEW_TIMER (const location_type& l)
  {
    return symbol_type (token::TOKEN_RENEW_TIMER, l);
  }

  Dhcp4Parser::symbol_type
  Dhcp4Parser::make_REBIND_TIMER (const location_type& l)
  {
    return symbol_type (token::TOKEN_REBIND_TIMER, l);
  }

  Dhcp4Parser::symbol_type
  Dhcp4Parser::make_DECLINE_PROBATION_PERIOD (const location_type& l)
  {
    return symbol_type (token::TOKEN_DECLINE_PROBATION_PERIOD, l);
  }

  Dhcp4Parser::symbol_type
  Dhcp4Parser::make_SUBNET4 (const location_type& l)
  {
    return symbol_type (token::TOKEN_SUBNET4, l);
  }

  Dhcp4Parser::symbol_type
  Dhcp4Parser::make_SUBNET_4O6_INTERFACE (const location_type& l)
  {
    return symbol_type (token::TOKEN_SUBNET_4O6_INTERFACE, l);
  }

  Dhcp4Parser::symbol_type
  Dhcp4Parser::make_SUBNET_4O6_INTERFACE_ID (const location_type& l)
  {
    return symbol_type (token::TOKEN_SUBNET_4O6_INTERFACE_ID, l);
  }

  Dhcp4Parser::symbol_type
  Dhcp4Parser::make_SUBNET_4O6_SUBNET (const location_type& l)
  {
    return symbol_type (token::TOKEN_SUBNET_4O6_SUBNET, l);
  }

  Dhcp4Parser::symbol_type
  Dhcp4Parser::make_OPTION_DEF (const location_type& l)
  {
    return symbol_type (token::TOKEN_OPTION_DEF, l);
  }

  Dhcp4Parser::symbol_type
  Dhcp4Parser::make_OPTION_DATA (const location_type& l)
  {
    return symbol_type (token::TOKEN_OPTION_DATA, l);
  }

  Dhcp4Parser::symbol_type
  Dhcp4Parser::make_NAME (const location_type& l)
  {
    return symbol_type (token::TOKEN_NAME, l);
  }

  Dhcp4Parser::symbol_type
  Dhcp4Parser::make_DATA (const location_type& l)
  {
    return symbol_type (token::TOKEN_DATA, l);
  }

  Dhcp4Parser::symbol_type
  Dhcp4Parser::make_CODE (const location_type& l)
  {
    return symbol_type (token::TOKEN_CODE, l);
  }

  Dhcp4Parser::symbol_type
  Dhcp4Parser::make_SPACE (const location_type& l)
  {
    return symbol_type (token::TOKEN_SPACE, l);
  }

  Dhcp4Parser::symbol_type
  Dhcp4Parser::make_CSV_FORMAT (const location_type& l)
  {
    return symbol_type (token::TOKEN_CSV_FORMAT, l);
  }

  Dhcp4Parser::symbol_type
  Dhcp4Parser::make_ALWAYS_SEND (const location_type& l)
  {
    return symbol_type (token::TOKEN_ALWAYS_SEND, l);
  }

  Dhcp4Parser::symbol_type
  Dhcp4Parser::make_RECORD_TYPES (const location_type& l)
  {
    return symbol_type (token::TOKEN_RECORD_TYPES, l);
  }

  Dhcp4Parser::symbol_type
  Dhcp4Parser::make_ENCAPSULATE (const location_type& l)
  {
    return symbol_type (token::TOKEN_ENCAPSULATE, l);
  }

  Dhcp4Parser::symbol_type
  Dhcp4Parser::make_ARRAY (const location_type& l)
  {
    return symbol_type (token::TOKEN_ARRAY, l);
  }

  Dhcp4Parser::symbol_type
  Dhcp4Parser::make_SHARED_NETWORKS (const location_type& l)
  {
    return symbol_type (token::TOKEN_SHARED_NETWORKS, l);
  }

  Dhcp4Parser::symbol_type
  Dhcp4Parser::make_POOLS (const location_type& l)
  {
    return symbol_type (token::TOKEN_POOLS, l);
  }

  Dhcp4Parser::symbol_type
  Dhcp4Parser::make_POOL (const location_type& l)
  {
    return symbol_type (token::TOKEN_POOL, l);
  }

  Dhcp4Parser::symbol_type
  Dhcp4Parser::make_USER_CONTEXT (const location_type& l)
  {
    return symbol_type (token::TOKEN_USER_CONTEXT, l);
  }

  Dhcp4Parser::symbol_type
  Dhcp4Parser::make_COMMENT (const location_type& l)
  {
    return symbol_type (token::TOKEN_COMMENT, l);
  }

  Dhcp4Parser::symbol_type
  Dhcp4Parser::make_SUBNET (const location_type& l)
  {
    return symbol_type (token::TOKEN_SUBNET, l);
  }

  Dhcp4Parser::symbol_type
  Dhcp4Parser::make_INTERFACE (const location_type& l)
  {
    return symbol_type (token::TOKEN_INTERFACE, l);
  }

  Dhcp4Parser::symbol_type
  Dhcp4Parser::make_INTERFACE_ID (const location_type& l)
  {
    return symbol_type (token::TOKEN_INTERFACE_ID, l);
  }

  Dhcp4Parser::symbol_type
  Dhcp4Parser::make_ID (const location_type& l)
  {
    return symbol_type (token::TOKEN_ID, l);
  }

  Dhcp4Parser::symbol_type
  Dhcp4Parser::make_RAPID_COMMIT (const location_type& l)
  {
    return symbol_type (token::TOKEN_RAPID_COMMIT, l);
  }

  Dhcp4Parser::symbol_type
  Dhcp4Parser::make_RESERVATION_MODE (const location_type& l)
  {
    return symbol_type (token::TOKEN_RESERVATION_MODE, l);
  }

  Dhcp4Parser::symbol_type
  Dhcp4Parser::make_DISABLED (const location_type& l)
  {
    return symbol_type (token::TOKEN_DISABLED, l);
  }

  Dhcp4Parser::symbol_type
  Dhcp4Parser::make_OUT_OF_POOL (const location_type& l)
  {
    return symbol_type (token::TOKEN_OUT_OF_POOL, l);
  }

  Dhcp4Parser::symbol_type
  Dhcp4Parser::make_ALL (const location_type& l)
  {
    return symbol_type (token::TOKEN_ALL, l);
  }

  Dhcp4Parser::symbol_type
  Dhcp4Parser::make_HOST_RESERVATION_IDENTIFIERS (const location_type& l)
  {
    return symbol_type (token::TOKEN_HOST_RESERVATION_IDENTIFIERS, l);
  }

  Dhcp4Parser::symbol_type
  Dhcp4Parser::make_CLIENT_CLASSES (const location_type& l)
  {
    return symbol_type (token::TOKEN_CLIENT_CLASSES, l);
  }

  Dhcp4Parser::symbol_type
  Dhcp4Parser::make_REQUIRE_CLIENT_CLASSES (const location_type& l)
  {
    return symbol_type (token::TOKEN_REQUIRE_CLIENT_CLASSES, l);
  }

  Dhcp4Parser::symbol_type
  Dhcp4Parser::make_TEST (const location_type& l)
  {
    return symbol_type (token::TOKEN_TEST, l);
  }

  Dhcp4Parser::symbol_type
  Dhcp4Parser::make_ONLY_IF_REQUIRED (const location_type& l)
  {
    return symbol_type (token::TOKEN_ONLY_IF_REQUIRED, l);
  }

  Dhcp4Parser::symbol_type
  Dhcp4Parser::make_CLIENT_CLASS (const location_type& l)
  {
    return symbol_type (token::TOKEN_CLIENT_CLASS, l);
  }

  Dhcp4Parser::symbol_type
  Dhcp4Parser::make_RESERVATIONS (const location_type& l)
  {
    return symbol_type (token::TOKEN_RESERVATIONS, l);
  }

  Dhcp4Parser::symbol_type
  Dhcp4Parser::make_DUID (const location_type& l)
  {
    return symbol_type (token::TOKEN_DUID, l);
  }

  Dhcp4Parser::symbol_type
  Dhcp4Parser::make_HW_ADDRESS (const location_type& l)
  {
    return symbol_type (token::TOKEN_HW_ADDRESS, l);
  }

  Dhcp4Parser::symbol_type
  Dhcp4Parser::make_CIRCUIT_ID (const location_type& l)
  {
    return symbol_type (token::TOKEN_CIRCUIT_ID, l);
  }

  Dhcp4Parser::symbol_type
  Dhcp4Parser::make_CLIENT_ID (const location_type& l)
  {
    return symbol_type (token::TOKEN_CLIENT_ID, l);
  }

  Dhcp4Parser::symbol_type
  Dhcp4Parser::make_HOSTNAME (const location_type& l)
  {
    return symbol_type (token::TOKEN_HOSTNAME, l);
  }

  Dhcp4Parser::symbol_type
  Dhcp4Parser::make_FLEX_ID (const location_type& l)
  {
    return symbol_type (token::TOKEN_FLEX_ID, l);
  }

  Dhcp4Parser::symbol_type
  Dhcp4Parser::make_RELAY (const location_type& l)
  {
    return symbol_type (token::TOKEN_RELAY, l);
  }

  Dhcp4Parser::symbol_type
  Dhcp4Parser::make_IP_ADDRESS (const location_type& l)
  {
    return symbol_type (token::TOKEN_IP_ADDRESS, l);
  }

  Dhcp4Parser::symbol_type
  Dhcp4Parser::make_IP_ADDRESSES (const location_type& l)
  {
    return symbol_type (token::TOKEN_IP_ADDRESSES, l);
  }

  Dhcp4Parser::symbol_type
  Dhcp4Parser::make_HOOKS_LIBRARIES (const location_type& l)
  {
    return symbol_type (token::TOKEN_HOOKS_LIBRARIES, l);
  }

  Dhcp4Parser::symbol_type
  Dhcp4Parser::make_LIBRARY (const location_type& l)
  {
    return symbol_type (token::TOKEN_LIBRARY, l);
  }

  Dhcp4Parser::symbol_type
  Dhcp4Parser::make_PARAMETERS (const location_type& l)
  {
    return symbol_type (token::TOKEN_PARAMETERS, l);
  }

  Dhcp4Parser::symbol_type
  Dhcp4Parser::make_EXPIRED_LEASES_PROCESSING (const location_type& l)
  {
    return symbol_type (token::TOKEN_EXPIRED_LEASES_PROCESSING, l);
  }

  Dhcp4Parser::symbol_type
  Dhcp4Parser::make_RECLAIM_TIMER_WAIT_TIME (const location_type& l)
  {
    return symbol_type (token::TOKEN_RECLAIM_TIMER_WAIT_TIME, l);
  }

  Dhcp4Parser::symbol_type
  Dhcp4Parser::make_FLUSH_RECLAIMED_TIMER_WAIT_TIME (const location_type& l)
  {
    return symbol_type (token::TOKEN_FLUSH_RECLAIMED_TIMER_WAIT_TIME, l);
  }

  Dhcp4Parser::symbol_type
  Dhcp4Parser::make_HOLD_RECLAIMED_TIME (const location_type& l)
  {
    return symbol_type (token::TOKEN_HOLD_RECLAIMED_TIME, l);
  }

  Dhcp4Parser::symbol_type
  Dhcp4Parser::make_MAX_RECLAIM_LEASES (const location_type& l)
  {
    return symbol_type (token::TOKEN_MAX_RECLAIM_LEASES, l);
  }

  Dhcp4Parser::symbol_type
  Dhcp4Parser::make_MAX_RECLAIM_TIME (const location_type& l)
  {
    return symbol_type (token::TOKEN_MAX_RECLAIM_TIME, l);
  }

  Dhcp4Parser::symbol_type
  Dhcp4Parser::make_UNWARNED_RECLAIM_CYCLES (const location_type& l)
  {
    return symbol_type (token::TOKEN_UNWARNED_RECLAIM_CYCLES, l);
  }

  Dhcp4Parser::symbol_type
  Dhcp4Parser::make_DHCP4O6_PORT (const location_type& l)
  {
    return symbol_type (token::TOKEN_DHCP4O6_PORT, l);
  }

  Dhcp4Parser::symbol_type
  Dhcp4Parser::make_CONTROL_SOCKET (const location_type& l)
  {
    return symbol_type (token::TOKEN_CONTROL_SOCKET, l);
  }

  Dhcp4Parser::symbol_type
  Dhcp4Parser::make_SOCKET_TYPE (const location_type& l)
  {
    return symbol_type (token::TOKEN_SOCKET_TYPE, l);
  }

  Dhcp4Parser::symbol_type
  Dhcp4Parser::make_SOCKET_NAME (const location_type& l)
  {
    return symbol_type (token::TOKEN_SOCKET_NAME, l);
  }

  Dhcp4Parser::symbol_type
  Dhcp4Parser::make_DHCP_DDNS (const location_type& l)
  {
    return symbol_type (token::TOKEN_DHCP_DDNS, l);
  }

  Dhcp4Parser::symbol_type
  Dhcp4Parser::make_ENABLE_UPDATES (const location_type& l)
  {
    return symbol_type (token::TOKEN_ENABLE_UPDATES, l);
  }

  Dhcp4Parser::symbol_type
  Dhcp4Parser::make_QUALIFYING_SUFFIX (const location_type& l)
  {
    return symbol_type (token::TOKEN_QUALIFYING_SUFFIX, l);
  }

  Dhcp4Parser::symbol_type
  Dhcp4Parser::make_SERVER_IP (const location_type& l)
  {
    return symbol_type (token::TOKEN_SERVER_IP, l);
  }

  Dhcp4Parser::symbol_type
  Dhcp4Parser::make_SERVER_PORT (const location_type& l)
  {
    return symbol_type (token::TOKEN_SERVER_PORT, l);
  }

  Dhcp4Parser::symbol_type
  Dhcp4Parser::make_SENDER_IP (const location_type& l)
  {
    return symbol_type (token::TOKEN_SENDER_IP, l);
  }

  Dhcp4Parser::symbol_type
  Dhcp4Parser::make_SENDER_PORT (const location_type& l)
  {
    return symbol_type (token::TOKEN_SENDER_PORT, l);
  }

  Dhcp4Parser::symbol_type
  Dhcp4Parser::make_MAX_QUEUE_SIZE (const location_type& l)
  {
    return symbol_type (token::TOKEN_MAX_QUEUE_SIZE, l);
  }

  Dhcp4Parser::symbol_type
  Dhcp4Parser::make_NCR_PROTOCOL (const location_type& l)
  {
    return symbol_type (token::TOKEN_NCR_PROTOCOL, l);
  }

  Dhcp4Parser::symbol_type
  Dhcp4Parser::make_NCR_FORMAT (const location_type& l)
  {
    return symbol_type (token::TOKEN_NCR_FORMAT, l);
  }

  Dhcp4Parser::symbol_type
  Dhcp4Parser::make_ALWAYS_INCLUDE_FQDN (const location_type& l)
  {
    return symbol_type (token::TOKEN_ALWAYS_INCLUDE_FQDN, l);
  }

  Dhcp4Parser::symbol_type
  Dhcp4Parser::make_OVERRIDE_NO_UPDATE (const location_type& l)
  {
    return symbol_type (token::TOKEN_OVERRIDE_NO_UPDATE, l);
  }

  Dhcp4Parser::symbol_type
  Dhcp4Parser::make_OVERRIDE_CLIENT_UPDATE (const location_type& l)
  {
    return symbol_type (token::TOKEN_OVERRIDE_CLIENT_UPDATE, l);
  }

  Dhcp4Parser::symbol_type
  Dhcp4Parser::make_REPLACE_CLIENT_NAME (const location_type& l)
  {
    return symbol_type (token::TOKEN_REPLACE_CLIENT_NAME, l);
  }

  Dhcp4Parser::symbol_type
  Dhcp4Parser::make_GENERATED_PREFIX (const location_type& l)
  {
    return symbol_type (token::TOKEN_GENERATED_PREFIX, l);
  }

  Dhcp4Parser::symbol_type
  Dhcp4Parser::make_TCP (const location_type& l)
  {
    return symbol_type (token::TOKEN_TCP, l);
  }

  Dhcp4Parser::symbol_type
  Dhcp4Parser::make_JSON (const location_type& l)
  {
    return symbol_type (token::TOKEN_JSON, l);
  }

  Dhcp4Parser::symbol_type
  Dhcp4Parser::make_WHEN_PRESENT (const location_type& l)
  {
    return symbol_type (token::TOKEN_WHEN_PRESENT, l);
  }

  Dhcp4Parser::symbol_type
  Dhcp4Parser::make_NEVER (const location_type& l)
  {
    return symbol_type (token::TOKEN_NEVER, l);
  }

  Dhcp4Parser::symbol_type
  Dhcp4Parser::make_ALWAYS (const location_type& l)
  {
    return symbol_type (token::TOKEN_ALWAYS, l);
  }

  Dhcp4Parser::symbol_type
  Dhcp4Parser::make_WHEN_NOT_PRESENT (const location_type& l)
  {
    return symbol_type (token::TOKEN_WHEN_NOT_PRESENT, l);
  }

  Dhcp4Parser::symbol_type
  Dhcp4Parser::make_LOGGING (const location_type& l)
  {
    return symbol_type (token::TOKEN_LOGGING, l);
  }

  Dhcp4Parser::symbol_type
  Dhcp4Parser::make_LOGGERS (const location_type& l)
  {
    return symbol_type (token::TOKEN_LOGGERS, l);
  }

  Dhcp4Parser::symbol_type
  Dhcp4Parser::make_OUTPUT_OPTIONS (const location_type& l)
  {
    return symbol_type (token::TOKEN_OUTPUT_OPTIONS, l);
  }

  Dhcp4Parser::symbol_type
  Dhcp4Parser::make_OUTPUT (const location_type& l)
  {
    return symbol_type (token::TOKEN_OUTPUT, l);
  }

  Dhcp4Parser::symbol_type
  Dhcp4Parser::make_DEBUGLEVEL (const location_type& l)
  {
    return symbol_type (token::TOKEN_DEBUGLEVEL, l);
  }

  Dhcp4Parser::symbol_type
  Dhcp4Parser::make_SEVERITY (const location_type& l)
  {
    return symbol_type (token::TOKEN_SEVERITY, l);
  }

  Dhcp4Parser::symbol_type
  Dhcp4Parser::make_FLUSH (const location_type& l)
  {
    return symbol_type (token::TOKEN_FLUSH, l);
  }

  Dhcp4Parser::symbol_type
  Dhcp4Parser::make_MAXSIZE (const location_type& l)
  {
    return symbol_type (token::TOKEN_MAXSIZE, l);
  }

  Dhcp4Parser::symbol_type
  Dhcp4Parser::make_MAXVER (const location_type& l)
  {
    return symbol_type (token::TOKEN_MAXVER, l);
  }

  Dhcp4Parser::symbol_type
  Dhcp4Parser::make_DHCP6 (const location_type& l)
  {
    return symbol_type (token::TOKEN_DHCP6, l);
  }

  Dhcp4Parser::symbol_type
  Dhcp4Parser::make_DHCPDDNS (const location_type& l)
  {
    return symbol_type (token::TOKEN_DHCPDDNS, l);
  }

  Dhcp4Parser::symbol_type
  Dhcp4Parser::make_CONTROL_AGENT (const location_type& l)
  {
    return symbol_type (token::TOKEN_CONTROL_AGENT, l);
  }

  Dhcp4Parser::symbol_type
  Dhcp4Parser::make_TOPLEVEL_JSON (const location_type& l)
  {
    return symbol_type (token::TOKEN_TOPLEVEL_JSON, l);
  }

  Dhcp4Parser::symbol_type
  Dhcp4Parser::make_TOPLEVEL_DHCP4 (const location_type& l)
  {
    return symbol_type (token::TOKEN_TOPLEVEL_DHCP4, l);
  }

  Dhcp4Parser::symbol_type
  Dhcp4Parser::make_SUB_DHCP4 (const location_type& l)
  {
    return symbol_type (token::TOKEN_SUB_DHCP4, l);
  }

  Dhcp4Parser::symbol_type
  Dhcp4Parser::make_SUB_INTERFACES4 (const location_type& l)
  {
    return symbol_type (token::TOKEN_SUB_INTERFACES4, l);
  }

  Dhcp4Parser::symbol_type
  Dhcp4Parser::make_SUB_SUBNET4 (const location_type& l)
  {
    return symbol_type (token::TOKEN_SUB_SUBNET4, l);
  }

  Dhcp4Parser::symbol_type
  Dhcp4Parser::make_SUB_POOL4 (const location_type& l)
  {
    return symbol_type (token::TOKEN_SUB_POOL4, l);
  }

  Dhcp4Parser::symbol_type
  Dhcp4Parser::make_SUB_RESERVATION (const location_type& l)
  {
    return symbol_type (token::TOKEN_SUB_RESERVATION, l);
  }

  Dhcp4Parser::symbol_type
  Dhcp4Parser::make_SUB_OPTION_DEFS (const location_type& l)
  {
    return symbol_type (token::TOKEN_SUB_OPTION_DEFS, l);
  }

  Dhcp4Parser::symbol_type
  Dhcp4Parser::make_SUB_OPTION_DEF (const location_type& l)
  {
    return symbol_type (token::TOKEN_SUB_OPTION_DEF, l);
  }

  Dhcp4Parser::symbol_type
  Dhcp4Parser::make_SUB_OPTION_DATA (const location_type& l)
  {
    return symbol_type (token::TOKEN_SUB_OPTION_DATA, l);
  }

  Dhcp4Parser::symbol_type
  Dhcp4Parser::make_SUB_HOOKS_LIBRARY (const location_type& l)
  {
    return symbol_type (token::TOKEN_SUB_HOOKS_LIBRARY, l);
  }

  Dhcp4Parser::symbol_type
  Dhcp4Parser::make_SUB_DHCP_DDNS (const location_type& l)
  {
    return symbol_type (token::TOKEN_SUB_DHCP_DDNS, l);
  }

  Dhcp4Parser::symbol_type
  Dhcp4Parser::make_SUB_LOGGING (const location_type& l)
  {
    return symbol_type (token::TOKEN_SUB_LOGGING, l);
  }

  Dhcp4Parser::symbol_type
  Dhcp4Parser::make_STRING (const std::string& v, const location_type& l)
  {
    return symbol_type (token::TOKEN_STRING, v, l);
  }

  Dhcp4Parser::symbol_type
  Dhcp4Parser::make_INTEGER (const int64_t& v, const location_type& l)
  {
    return symbol_type (token::TOKEN_INTEGER, v, l);
  }

  Dhcp4Parser::symbol_type
  Dhcp4Parser::make_FLOAT (const double& v, const location_type& l)
  {
    return symbol_type (token::TOKEN_FLOAT, v, l);
  }

  Dhcp4Parser::symbol_type
  Dhcp4Parser::make_BOOLEAN (const bool& v, const location_type& l)
  {
    return symbol_type (token::TOKEN_BOOLEAN, v, l);
  }


#line 14 "dhcp4_parser.yy" // lalr1.cc:377
} } // isc::dhcp
#line 2820 "dhcp4_parser.h" // lalr1.cc:377




#endif // !YY_PARSER4_DHCP4_PARSER_H_INCLUDED
