// A Bison parser, made by GNU Bison 3.7.2.

// Skeleton interface for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015, 2018-2020 Free Software Foundation, Inc.

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
 ** \file dhcp6_parser.h
 ** Define the isc::dhcp::parser class.
 */

// C++ LALR(1) parser skeleton written by Akim Demaille.

// DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
// especially those whose name start with YY_ or yy_.  They are
// private implementation details that can be changed or removed.

#ifndef YY_PARSER6_DHCP6_PARSER_H_INCLUDED
# define YY_PARSER6_DHCP6_PARSER_H_INCLUDED
// "%code requires" blocks.
#line 17 "dhcp6_parser.yy"

#include <string>
#include <cc/data.h>
#include <dhcp/option.h>
#include <boost/lexical_cast.hpp>
#include <dhcp6/parser_context_decl.h>

using namespace isc::dhcp;
using namespace isc::data;
using namespace std;

#line 61 "dhcp6_parser.h"

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
#ifndef YY_ASSERT
# include <cassert>
# define YY_ASSERT assert
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
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
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
#ifndef PARSER6_DEBUG
# if defined YYDEBUG
#if YYDEBUG
#   define PARSER6_DEBUG 1
#  else
#   define PARSER6_DEBUG 0
#  endif
# else /* ! defined YYDEBUG */
#  define PARSER6_DEBUG 1
# endif /* ! defined YYDEBUG */
#endif  /* ! defined PARSER6_DEBUG */

#line 14 "dhcp6_parser.yy"
namespace isc { namespace dhcp {
#line 204 "dhcp6_parser.h"




  /// A Bison parser.
  class Dhcp6Parser
  {
  public:
#ifndef PARSER6_STYPE
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
      YY_ASSERT (sizeof (T) <= size);
      new (yyas_<T> ()) T (YY_MOVE (t));
    }

#if 201103L <= YY_CPLUSPLUS
    /// Non copyable.
    semantic_type (const self_type&) = delete;
    /// Non copyable.
    self_type& operator= (const self_type&) = delete;
#endif

    /// Destruction, allowed only if empty.
    ~semantic_type () YY_NOEXCEPT
    {
      YY_ASSERT (!yytypeid_);
    }

# if 201103L <= YY_CPLUSPLUS
    /// Instantiate a \a T in here from \a t.
    template <typename T, typename... U>
    T&
    emplace (U&&... u)
    {
      YY_ASSERT (!yytypeid_);
      YY_ASSERT (sizeof (T) <= size);
      yytypeid_ = & typeid (T);
      return *new (yyas_<T> ()) T (std::forward <U>(u)...);
    }
# else
    /// Instantiate an empty \a T in here.
    template <typename T>
    T&
    emplace ()
    {
      YY_ASSERT (!yytypeid_);
      YY_ASSERT (sizeof (T) <= size);
      yytypeid_ = & typeid (T);
      return *new (yyas_<T> ()) T ();
    }

    /// Instantiate a \a T in here from \a t.
    template <typename T>
    T&
    emplace (const T& t)
    {
      YY_ASSERT (!yytypeid_);
      YY_ASSERT (sizeof (T) <= size);
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
      YY_ASSERT (yytypeid_);
      YY_ASSERT (*yytypeid_ == typeid (T));
      YY_ASSERT (sizeof (T) <= size);
      return *yyas_<T> ();
    }

    /// Const accessor to a built \a T (for %printer).
    template <typename T>
    const T&
    as () const YY_NOEXCEPT
    {
      YY_ASSERT (yytypeid_);
      YY_ASSERT (*yytypeid_ == typeid (T));
      YY_ASSERT (sizeof (T) <= size);
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
      YY_ASSERT (yytypeid_);
      YY_ASSERT (*yytypeid_ == *that.yytypeid_);
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
    semantic_type (const self_type&);
    /// Non copyable.
    self_type& operator= (const self_type&);
#endif

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
      // value
      // map_value
      // ddns_replace_client_name_value
      // db_type
      // hr_mode
      // duid_type
      // ncr_protocol_value
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
      long double yyalign_me;
      /// A buffer large enough to store any of the semantic values.
      char yyraw[size];
    } yybuffer_;

    /// Whether the content is built: if defined, the name of the stored type.
    const std::type_info *yytypeid_;
  };

#else
    typedef PARSER6_STYPE semantic_type;
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

    /// Token kinds.
    struct token
    {
      enum token_kind_type
      {
        TOKEN_PARSER6_EMPTY = -2,
    TOKEN_END = 0,                 // "end of file"
    TOKEN_PARSER6_error = 256,     // error
    TOKEN_PARSER6_UNDEF = 257,     // "invalid token"
    TOKEN_COMMA = 258,             // ","
    TOKEN_COLON = 259,             // ":"
    TOKEN_LSQUARE_BRACKET = 260,   // "["
    TOKEN_RSQUARE_BRACKET = 261,   // "]"
    TOKEN_LCURLY_BRACKET = 262,    // "{"
    TOKEN_RCURLY_BRACKET = 263,    // "}"
    TOKEN_NULL_TYPE = 264,         // "null"
    TOKEN_DHCP6 = 265,             // "Dhcp6"
    TOKEN_DATA_DIRECTORY = 266,    // "data-directory"
    TOKEN_CONFIG_CONTROL = 267,    // "config-control"
    TOKEN_CONFIG_DATABASES = 268,  // "config-databases"
    TOKEN_CONFIG_FETCH_WAIT_TIME = 269, // "config-fetch-wait-time"
    TOKEN_INTERFACES_CONFIG = 270, // "interfaces-config"
    TOKEN_INTERFACES = 271,        // "interfaces"
    TOKEN_RE_DETECT = 272,         // "re-detect"
    TOKEN_LEASE_DATABASE = 273,    // "lease-database"
    TOKEN_HOSTS_DATABASE = 274,    // "hosts-database"
    TOKEN_HOSTS_DATABASES = 275,   // "hosts-databases"
    TOKEN_TYPE = 276,              // "type"
    TOKEN_MEMFILE = 277,           // "memfile"
    TOKEN_MYSQL = 278,             // "mysql"
    TOKEN_POSTGRESQL = 279,        // "postgresql"
    TOKEN_CQL = 280,               // "cql"
    TOKEN_USER = 281,              // "user"
    TOKEN_PASSWORD = 282,          // "password"
    TOKEN_HOST = 283,              // "host"
    TOKEN_PORT = 284,              // "port"
    TOKEN_PERSIST = 285,           // "persist"
    TOKEN_LFC_INTERVAL = 286,      // "lfc-interval"
    TOKEN_READONLY = 287,          // "readonly"
    TOKEN_CONNECT_TIMEOUT = 288,   // "connect-timeout"
    TOKEN_CONTACT_POINTS = 289,    // "contact-points"
    TOKEN_MAX_RECONNECT_TRIES = 290, // "max-reconnect-tries"
    TOKEN_RECONNECT_WAIT_TIME = 291, // "reconnect-wait-time"
    TOKEN_KEYSPACE = 292,          // "keyspace"
    TOKEN_CONSISTENCY = 293,       // "consistency"
    TOKEN_SERIAL_CONSISTENCY = 294, // "serial-consistency"
    TOKEN_REQUEST_TIMEOUT = 295,   // "request-timeout"
    TOKEN_TCP_KEEPALIVE = 296,     // "tcp-keepalive"
    TOKEN_TCP_NODELAY = 297,       // "tcp-nodelay"
    TOKEN_MAX_ROW_ERRORS = 298,    // "max-row-errors"
    TOKEN_PREFERRED_LIFETIME = 299, // "preferred-lifetime"
    TOKEN_MIN_PREFERRED_LIFETIME = 300, // "min-preferred-lifetime"
    TOKEN_MAX_PREFERRED_LIFETIME = 301, // "max-preferred-lifetime"
    TOKEN_VALID_LIFETIME = 302,    // "valid-lifetime"
    TOKEN_MIN_VALID_LIFETIME = 303, // "min-valid-lifetime"
    TOKEN_MAX_VALID_LIFETIME = 304, // "max-valid-lifetime"
    TOKEN_RENEW_TIMER = 305,       // "renew-timer"
    TOKEN_REBIND_TIMER = 306,      // "rebind-timer"
    TOKEN_CALCULATE_TEE_TIMES = 307, // "calculate-tee-times"
    TOKEN_T1_PERCENT = 308,        // "t1-percent"
    TOKEN_T2_PERCENT = 309,        // "t2-percent"
    TOKEN_CACHE_THRESHOLD = 310,   // "cache-threshold"
    TOKEN_CACHE_MAX_AGE = 311,     // "cache-max-age"
    TOKEN_DECLINE_PROBATION_PERIOD = 312, // "decline-probation-period"
    TOKEN_SERVER_TAG = 313,        // "server-tag"
    TOKEN_STATISTIC_DEFAULT_SAMPLE_COUNT = 314, // "statistic-default-sample-count"
    TOKEN_STATISTIC_DEFAULT_SAMPLE_AGE = 315, // "statistic-default-sample-age"
    TOKEN_DDNS_SEND_UPDATES = 316, // "ddns-send-updates"
    TOKEN_DDNS_OVERRIDE_NO_UPDATE = 317, // "ddns-override-no-update"
    TOKEN_DDNS_OVERRIDE_CLIENT_UPDATE = 318, // "ddns-override-client-update"
    TOKEN_DDNS_REPLACE_CLIENT_NAME = 319, // "ddns-replace-client-name"
    TOKEN_DDNS_GENERATED_PREFIX = 320, // "ddns-generated-prefix"
    TOKEN_DDNS_QUALIFYING_SUFFIX = 321, // "ddns-qualifying-suffix"
    TOKEN_DDNS_UPDATE_ON_RENEW = 322, // "ddns-update-on-renew"
    TOKEN_STORE_EXTENDED_INFO = 323, // "store-extended-info"
    TOKEN_SUBNET6 = 324,           // "subnet6"
    TOKEN_OPTION_DEF = 325,        // "option-def"
    TOKEN_OPTION_DATA = 326,       // "option-data"
    TOKEN_NAME = 327,              // "name"
    TOKEN_DATA = 328,              // "data"
    TOKEN_CODE = 329,              // "code"
    TOKEN_SPACE = 330,             // "space"
    TOKEN_CSV_FORMAT = 331,        // "csv-format"
    TOKEN_ALWAYS_SEND = 332,       // "always-send"
    TOKEN_RECORD_TYPES = 333,      // "record-types"
    TOKEN_ENCAPSULATE = 334,       // "encapsulate"
    TOKEN_ARRAY = 335,             // "array"
    TOKEN_SHARED_NETWORKS = 336,   // "shared-networks"
    TOKEN_POOLS = 337,             // "pools"
    TOKEN_POOL = 338,              // "pool"
    TOKEN_PD_POOLS = 339,          // "pd-pools"
    TOKEN_PREFIX = 340,            // "prefix"
    TOKEN_PREFIX_LEN = 341,        // "prefix-len"
    TOKEN_EXCLUDED_PREFIX = 342,   // "excluded-prefix"
    TOKEN_EXCLUDED_PREFIX_LEN = 343, // "excluded-prefix-len"
    TOKEN_DELEGATED_LEN = 344,     // "delegated-len"
    TOKEN_USER_CONTEXT = 345,      // "user-context"
    TOKEN_COMMENT = 346,           // "comment"
    TOKEN_SUBNET = 347,            // "subnet"
    TOKEN_INTERFACE = 348,         // "interface"
    TOKEN_INTERFACE_ID = 349,      // "interface-id"
    TOKEN_ID = 350,                // "id"
    TOKEN_RAPID_COMMIT = 351,      // "rapid-commit"
    TOKEN_RESERVATION_MODE = 352,  // "reservation-mode"
    TOKEN_RESERVATIONS_OUT_OF_POOL = 353, // "reservations-out-of-pool"
    TOKEN_RESERVATIONS_IN_SUBNET = 354, // "reservations-in-subnet"
    TOKEN_RESERVATIONS_GLOBAL = 355, // "reservations-global"
    TOKEN_DISABLED = 356,          // "disabled"
    TOKEN_OUT_OF_POOL = 357,       // "out-of-pool"
    TOKEN_GLOBAL = 358,            // "global"
    TOKEN_ALL = 359,               // "all"
    TOKEN_MAC_SOURCES = 360,       // "mac-sources"
    TOKEN_RELAY_SUPPLIED_OPTIONS = 361, // "relay-supplied-options"
    TOKEN_HOST_RESERVATION_IDENTIFIERS = 362, // "host-reservation-identifiers"
    TOKEN_SANITY_CHECKS = 363,     // "sanity-checks"
    TOKEN_LEASE_CHECKS = 364,      // "lease-checks"
    TOKEN_CLIENT_CLASSES = 365,    // "client-classes"
    TOKEN_REQUIRE_CLIENT_CLASSES = 366, // "require-client-classes"
    TOKEN_TEST = 367,              // "test"
    TOKEN_ONLY_IF_REQUIRED = 368,  // "only-if-required"
    TOKEN_CLIENT_CLASS = 369,      // "client-class"
    TOKEN_RESERVATIONS = 370,      // "reservations"
    TOKEN_IP_ADDRESSES = 371,      // "ip-addresses"
    TOKEN_PREFIXES = 372,          // "prefixes"
    TOKEN_DUID = 373,              // "duid"
    TOKEN_HW_ADDRESS = 374,        // "hw-address"
    TOKEN_HOSTNAME = 375,          // "hostname"
    TOKEN_FLEX_ID = 376,           // "flex-id"
    TOKEN_RELAY = 377,             // "relay"
    TOKEN_IP_ADDRESS = 378,        // "ip-address"
    TOKEN_HOOKS_LIBRARIES = 379,   // "hooks-libraries"
    TOKEN_LIBRARY = 380,           // "library"
    TOKEN_PARAMETERS = 381,        // "parameters"
    TOKEN_EXPIRED_LEASES_PROCESSING = 382, // "expired-leases-processing"
    TOKEN_RECLAIM_TIMER_WAIT_TIME = 383, // "reclaim-timer-wait-time"
    TOKEN_FLUSH_RECLAIMED_TIMER_WAIT_TIME = 384, // "flush-reclaimed-timer-wait-time"
    TOKEN_HOLD_RECLAIMED_TIME = 385, // "hold-reclaimed-time"
    TOKEN_MAX_RECLAIM_LEASES = 386, // "max-reclaim-leases"
    TOKEN_MAX_RECLAIM_TIME = 387,  // "max-reclaim-time"
    TOKEN_UNWARNED_RECLAIM_CYCLES = 388, // "unwarned-reclaim-cycles"
    TOKEN_SERVER_ID = 389,         // "server-id"
    TOKEN_LLT = 390,               // "LLT"
    TOKEN_EN = 391,                // "EN"
    TOKEN_LL = 392,                // "LL"
    TOKEN_IDENTIFIER = 393,        // "identifier"
    TOKEN_HTYPE = 394,             // "htype"
    TOKEN_TIME = 395,              // "time"
    TOKEN_ENTERPRISE_ID = 396,     // "enterprise-id"
    TOKEN_DHCP4O6_PORT = 397,      // "dhcp4o6-port"
    TOKEN_DHCP_MULTI_THREADING = 398, // "multi-threading"
    TOKEN_ENABLE_MULTI_THREADING = 399, // "enable-multi-threading"
    TOKEN_THREAD_POOL_SIZE = 400,  // "thread-pool-size"
    TOKEN_PACKET_QUEUE_SIZE = 401, // "packet-queue-size"
    TOKEN_CONTROL_SOCKET = 402,    // "control-socket"
    TOKEN_SOCKET_TYPE = 403,       // "socket-type"
    TOKEN_SOCKET_NAME = 404,       // "socket-name"
    TOKEN_DHCP_QUEUE_CONTROL = 405, // "dhcp-queue-control"
    TOKEN_ENABLE_QUEUE = 406,      // "enable-queue"
    TOKEN_QUEUE_TYPE = 407,        // "queue-type"
    TOKEN_CAPACITY = 408,          // "capacity"
    TOKEN_DHCP_DDNS = 409,         // "dhcp-ddns"
    TOKEN_ENABLE_UPDATES = 410,    // "enable-updates"
    TOKEN_QUALIFYING_SUFFIX = 411, // "qualifying-suffix"
    TOKEN_SERVER_IP = 412,         // "server-ip"
    TOKEN_SERVER_PORT = 413,       // "server-port"
    TOKEN_SENDER_IP = 414,         // "sender-ip"
    TOKEN_SENDER_PORT = 415,       // "sender-port"
    TOKEN_MAX_QUEUE_SIZE = 416,    // "max-queue-size"
    TOKEN_NCR_PROTOCOL = 417,      // "ncr-protocol"
    TOKEN_NCR_FORMAT = 418,        // "ncr-format"
    TOKEN_OVERRIDE_NO_UPDATE = 419, // "override-no-update"
    TOKEN_OVERRIDE_CLIENT_UPDATE = 420, // "override-client-update"
    TOKEN_REPLACE_CLIENT_NAME = 421, // "replace-client-name"
    TOKEN_GENERATED_PREFIX = 422,  // "generated-prefix"
    TOKEN_UDP = 423,               // "UDP"
    TOKEN_TCP = 424,               // "TCP"
    TOKEN_JSON = 425,              // "JSON"
    TOKEN_WHEN_PRESENT = 426,      // "when-present"
    TOKEN_NEVER = 427,             // "never"
    TOKEN_ALWAYS = 428,            // "always"
    TOKEN_WHEN_NOT_PRESENT = 429,  // "when-not-present"
    TOKEN_HOSTNAME_CHAR_SET = 430, // "hostname-char-set"
    TOKEN_HOSTNAME_CHAR_REPLACEMENT = 431, // "hostname-char-replacement"
    TOKEN_IP_RESERVATIONS_UNIQUE = 432, // "ip-reservations-unique"
    TOKEN_LOGGERS = 433,           // "loggers"
    TOKEN_OUTPUT_OPTIONS = 434,    // "output_options"
    TOKEN_OUTPUT = 435,            // "output"
    TOKEN_DEBUGLEVEL = 436,        // "debuglevel"
    TOKEN_SEVERITY = 437,          // "severity"
    TOKEN_FLUSH = 438,             // "flush"
    TOKEN_MAXSIZE = 439,           // "maxsize"
    TOKEN_MAXVER = 440,            // "maxver"
    TOKEN_PATTERN = 441,           // "pattern"
    TOKEN_TOPLEVEL_JSON = 442,     // TOPLEVEL_JSON
    TOKEN_TOPLEVEL_DHCP6 = 443,    // TOPLEVEL_DHCP6
    TOKEN_SUB_DHCP6 = 444,         // SUB_DHCP6
    TOKEN_SUB_INTERFACES6 = 445,   // SUB_INTERFACES6
    TOKEN_SUB_SUBNET6 = 446,       // SUB_SUBNET6
    TOKEN_SUB_POOL6 = 447,         // SUB_POOL6
    TOKEN_SUB_PD_POOL = 448,       // SUB_PD_POOL
    TOKEN_SUB_RESERVATION = 449,   // SUB_RESERVATION
    TOKEN_SUB_OPTION_DEFS = 450,   // SUB_OPTION_DEFS
    TOKEN_SUB_OPTION_DEF = 451,    // SUB_OPTION_DEF
    TOKEN_SUB_OPTION_DATA = 452,   // SUB_OPTION_DATA
    TOKEN_SUB_HOOKS_LIBRARY = 453, // SUB_HOOKS_LIBRARY
    TOKEN_SUB_DHCP_DDNS = 454,     // SUB_DHCP_DDNS
    TOKEN_SUB_CONFIG_CONTROL = 455, // SUB_CONFIG_CONTROL
    TOKEN_STRING = 456,            // "constant string"
    TOKEN_INTEGER = 457,           // "integer"
    TOKEN_FLOAT = 458,             // "floating point"
    TOKEN_BOOLEAN = 459            // "boolean"
      };
      /// Backward compatibility alias (Bison 3.6).
      typedef token_kind_type yytokentype;
    };

    /// Token kind, as returned by yylex.
    typedef token::yytokentype token_kind_type;

    /// Backward compatibility alias (Bison 3.6).
    typedef token_kind_type token_type;

    /// Symbol kinds.
    struct symbol_kind
    {
      enum symbol_kind_type
      {
        YYNTOKENS = 205, ///< Number of tokens.
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
        S_DHCP6 = 10,                            // "Dhcp6"
        S_DATA_DIRECTORY = 11,                   // "data-directory"
        S_CONFIG_CONTROL = 12,                   // "config-control"
        S_CONFIG_DATABASES = 13,                 // "config-databases"
        S_CONFIG_FETCH_WAIT_TIME = 14,           // "config-fetch-wait-time"
        S_INTERFACES_CONFIG = 15,                // "interfaces-config"
        S_INTERFACES = 16,                       // "interfaces"
        S_RE_DETECT = 17,                        // "re-detect"
        S_LEASE_DATABASE = 18,                   // "lease-database"
        S_HOSTS_DATABASE = 19,                   // "hosts-database"
        S_HOSTS_DATABASES = 20,                  // "hosts-databases"
        S_TYPE = 21,                             // "type"
        S_MEMFILE = 22,                          // "memfile"
        S_MYSQL = 23,                            // "mysql"
        S_POSTGRESQL = 24,                       // "postgresql"
        S_CQL = 25,                              // "cql"
        S_USER = 26,                             // "user"
        S_PASSWORD = 27,                         // "password"
        S_HOST = 28,                             // "host"
        S_PORT = 29,                             // "port"
        S_PERSIST = 30,                          // "persist"
        S_LFC_INTERVAL = 31,                     // "lfc-interval"
        S_READONLY = 32,                         // "readonly"
        S_CONNECT_TIMEOUT = 33,                  // "connect-timeout"
        S_CONTACT_POINTS = 34,                   // "contact-points"
        S_MAX_RECONNECT_TRIES = 35,              // "max-reconnect-tries"
        S_RECONNECT_WAIT_TIME = 36,              // "reconnect-wait-time"
        S_KEYSPACE = 37,                         // "keyspace"
        S_CONSISTENCY = 38,                      // "consistency"
        S_SERIAL_CONSISTENCY = 39,               // "serial-consistency"
        S_REQUEST_TIMEOUT = 40,                  // "request-timeout"
        S_TCP_KEEPALIVE = 41,                    // "tcp-keepalive"
        S_TCP_NODELAY = 42,                      // "tcp-nodelay"
        S_MAX_ROW_ERRORS = 43,                   // "max-row-errors"
        S_PREFERRED_LIFETIME = 44,               // "preferred-lifetime"
        S_MIN_PREFERRED_LIFETIME = 45,           // "min-preferred-lifetime"
        S_MAX_PREFERRED_LIFETIME = 46,           // "max-preferred-lifetime"
        S_VALID_LIFETIME = 47,                   // "valid-lifetime"
        S_MIN_VALID_LIFETIME = 48,               // "min-valid-lifetime"
        S_MAX_VALID_LIFETIME = 49,               // "max-valid-lifetime"
        S_RENEW_TIMER = 50,                      // "renew-timer"
        S_REBIND_TIMER = 51,                     // "rebind-timer"
        S_CALCULATE_TEE_TIMES = 52,              // "calculate-tee-times"
        S_T1_PERCENT = 53,                       // "t1-percent"
        S_T2_PERCENT = 54,                       // "t2-percent"
        S_CACHE_THRESHOLD = 55,                  // "cache-threshold"
        S_CACHE_MAX_AGE = 56,                    // "cache-max-age"
        S_DECLINE_PROBATION_PERIOD = 57,         // "decline-probation-period"
        S_SERVER_TAG = 58,                       // "server-tag"
        S_STATISTIC_DEFAULT_SAMPLE_COUNT = 59,   // "statistic-default-sample-count"
        S_STATISTIC_DEFAULT_SAMPLE_AGE = 60,     // "statistic-default-sample-age"
        S_DDNS_SEND_UPDATES = 61,                // "ddns-send-updates"
        S_DDNS_OVERRIDE_NO_UPDATE = 62,          // "ddns-override-no-update"
        S_DDNS_OVERRIDE_CLIENT_UPDATE = 63,      // "ddns-override-client-update"
        S_DDNS_REPLACE_CLIENT_NAME = 64,         // "ddns-replace-client-name"
        S_DDNS_GENERATED_PREFIX = 65,            // "ddns-generated-prefix"
        S_DDNS_QUALIFYING_SUFFIX = 66,           // "ddns-qualifying-suffix"
        S_DDNS_UPDATE_ON_RENEW = 67,             // "ddns-update-on-renew"
        S_STORE_EXTENDED_INFO = 68,              // "store-extended-info"
        S_SUBNET6 = 69,                          // "subnet6"
        S_OPTION_DEF = 70,                       // "option-def"
        S_OPTION_DATA = 71,                      // "option-data"
        S_NAME = 72,                             // "name"
        S_DATA = 73,                             // "data"
        S_CODE = 74,                             // "code"
        S_SPACE = 75,                            // "space"
        S_CSV_FORMAT = 76,                       // "csv-format"
        S_ALWAYS_SEND = 77,                      // "always-send"
        S_RECORD_TYPES = 78,                     // "record-types"
        S_ENCAPSULATE = 79,                      // "encapsulate"
        S_ARRAY = 80,                            // "array"
        S_SHARED_NETWORKS = 81,                  // "shared-networks"
        S_POOLS = 82,                            // "pools"
        S_POOL = 83,                             // "pool"
        S_PD_POOLS = 84,                         // "pd-pools"
        S_PREFIX = 85,                           // "prefix"
        S_PREFIX_LEN = 86,                       // "prefix-len"
        S_EXCLUDED_PREFIX = 87,                  // "excluded-prefix"
        S_EXCLUDED_PREFIX_LEN = 88,              // "excluded-prefix-len"
        S_DELEGATED_LEN = 89,                    // "delegated-len"
        S_USER_CONTEXT = 90,                     // "user-context"
        S_COMMENT = 91,                          // "comment"
        S_SUBNET = 92,                           // "subnet"
        S_INTERFACE = 93,                        // "interface"
        S_INTERFACE_ID = 94,                     // "interface-id"
        S_ID = 95,                               // "id"
        S_RAPID_COMMIT = 96,                     // "rapid-commit"
        S_RESERVATION_MODE = 97,                 // "reservation-mode"
        S_RESERVATIONS_OUT_OF_POOL = 98,         // "reservations-out-of-pool"
        S_RESERVATIONS_IN_SUBNET = 99,           // "reservations-in-subnet"
        S_RESERVATIONS_GLOBAL = 100,             // "reservations-global"
        S_DISABLED = 101,                        // "disabled"
        S_OUT_OF_POOL = 102,                     // "out-of-pool"
        S_GLOBAL = 103,                          // "global"
        S_ALL = 104,                             // "all"
        S_MAC_SOURCES = 105,                     // "mac-sources"
        S_RELAY_SUPPLIED_OPTIONS = 106,          // "relay-supplied-options"
        S_HOST_RESERVATION_IDENTIFIERS = 107,    // "host-reservation-identifiers"
        S_SANITY_CHECKS = 108,                   // "sanity-checks"
        S_LEASE_CHECKS = 109,                    // "lease-checks"
        S_CLIENT_CLASSES = 110,                  // "client-classes"
        S_REQUIRE_CLIENT_CLASSES = 111,          // "require-client-classes"
        S_TEST = 112,                            // "test"
        S_ONLY_IF_REQUIRED = 113,                // "only-if-required"
        S_CLIENT_CLASS = 114,                    // "client-class"
        S_RESERVATIONS = 115,                    // "reservations"
        S_IP_ADDRESSES = 116,                    // "ip-addresses"
        S_PREFIXES = 117,                        // "prefixes"
        S_DUID = 118,                            // "duid"
        S_HW_ADDRESS = 119,                      // "hw-address"
        S_HOSTNAME = 120,                        // "hostname"
        S_FLEX_ID = 121,                         // "flex-id"
        S_RELAY = 122,                           // "relay"
        S_IP_ADDRESS = 123,                      // "ip-address"
        S_HOOKS_LIBRARIES = 124,                 // "hooks-libraries"
        S_LIBRARY = 125,                         // "library"
        S_PARAMETERS = 126,                      // "parameters"
        S_EXPIRED_LEASES_PROCESSING = 127,       // "expired-leases-processing"
        S_RECLAIM_TIMER_WAIT_TIME = 128,         // "reclaim-timer-wait-time"
        S_FLUSH_RECLAIMED_TIMER_WAIT_TIME = 129, // "flush-reclaimed-timer-wait-time"
        S_HOLD_RECLAIMED_TIME = 130,             // "hold-reclaimed-time"
        S_MAX_RECLAIM_LEASES = 131,              // "max-reclaim-leases"
        S_MAX_RECLAIM_TIME = 132,                // "max-reclaim-time"
        S_UNWARNED_RECLAIM_CYCLES = 133,         // "unwarned-reclaim-cycles"
        S_SERVER_ID = 134,                       // "server-id"
        S_LLT = 135,                             // "LLT"
        S_EN = 136,                              // "EN"
        S_LL = 137,                              // "LL"
        S_IDENTIFIER = 138,                      // "identifier"
        S_HTYPE = 139,                           // "htype"
        S_TIME = 140,                            // "time"
        S_ENTERPRISE_ID = 141,                   // "enterprise-id"
        S_DHCP4O6_PORT = 142,                    // "dhcp4o6-port"
        S_DHCP_MULTI_THREADING = 143,            // "multi-threading"
        S_ENABLE_MULTI_THREADING = 144,          // "enable-multi-threading"
        S_THREAD_POOL_SIZE = 145,                // "thread-pool-size"
        S_PACKET_QUEUE_SIZE = 146,               // "packet-queue-size"
        S_CONTROL_SOCKET = 147,                  // "control-socket"
        S_SOCKET_TYPE = 148,                     // "socket-type"
        S_SOCKET_NAME = 149,                     // "socket-name"
        S_DHCP_QUEUE_CONTROL = 150,              // "dhcp-queue-control"
        S_ENABLE_QUEUE = 151,                    // "enable-queue"
        S_QUEUE_TYPE = 152,                      // "queue-type"
        S_CAPACITY = 153,                        // "capacity"
        S_DHCP_DDNS = 154,                       // "dhcp-ddns"
        S_ENABLE_UPDATES = 155,                  // "enable-updates"
        S_QUALIFYING_SUFFIX = 156,               // "qualifying-suffix"
        S_SERVER_IP = 157,                       // "server-ip"
        S_SERVER_PORT = 158,                     // "server-port"
        S_SENDER_IP = 159,                       // "sender-ip"
        S_SENDER_PORT = 160,                     // "sender-port"
        S_MAX_QUEUE_SIZE = 161,                  // "max-queue-size"
        S_NCR_PROTOCOL = 162,                    // "ncr-protocol"
        S_NCR_FORMAT = 163,                      // "ncr-format"
        S_OVERRIDE_NO_UPDATE = 164,              // "override-no-update"
        S_OVERRIDE_CLIENT_UPDATE = 165,          // "override-client-update"
        S_REPLACE_CLIENT_NAME = 166,             // "replace-client-name"
        S_GENERATED_PREFIX = 167,                // "generated-prefix"
        S_UDP = 168,                             // "UDP"
        S_TCP = 169,                             // "TCP"
        S_JSON = 170,                            // "JSON"
        S_WHEN_PRESENT = 171,                    // "when-present"
        S_NEVER = 172,                           // "never"
        S_ALWAYS = 173,                          // "always"
        S_WHEN_NOT_PRESENT = 174,                // "when-not-present"
        S_HOSTNAME_CHAR_SET = 175,               // "hostname-char-set"
        S_HOSTNAME_CHAR_REPLACEMENT = 176,       // "hostname-char-replacement"
        S_IP_RESERVATIONS_UNIQUE = 177,          // "ip-reservations-unique"
        S_LOGGERS = 178,                         // "loggers"
        S_OUTPUT_OPTIONS = 179,                  // "output_options"
        S_OUTPUT = 180,                          // "output"
        S_DEBUGLEVEL = 181,                      // "debuglevel"
        S_SEVERITY = 182,                        // "severity"
        S_FLUSH = 183,                           // "flush"
        S_MAXSIZE = 184,                         // "maxsize"
        S_MAXVER = 185,                          // "maxver"
        S_PATTERN = 186,                         // "pattern"
        S_TOPLEVEL_JSON = 187,                   // TOPLEVEL_JSON
        S_TOPLEVEL_DHCP6 = 188,                  // TOPLEVEL_DHCP6
        S_SUB_DHCP6 = 189,                       // SUB_DHCP6
        S_SUB_INTERFACES6 = 190,                 // SUB_INTERFACES6
        S_SUB_SUBNET6 = 191,                     // SUB_SUBNET6
        S_SUB_POOL6 = 192,                       // SUB_POOL6
        S_SUB_PD_POOL = 193,                     // SUB_PD_POOL
        S_SUB_RESERVATION = 194,                 // SUB_RESERVATION
        S_SUB_OPTION_DEFS = 195,                 // SUB_OPTION_DEFS
        S_SUB_OPTION_DEF = 196,                  // SUB_OPTION_DEF
        S_SUB_OPTION_DATA = 197,                 // SUB_OPTION_DATA
        S_SUB_HOOKS_LIBRARY = 198,               // SUB_HOOKS_LIBRARY
        S_SUB_DHCP_DDNS = 199,                   // SUB_DHCP_DDNS
        S_SUB_CONFIG_CONTROL = 200,              // SUB_CONFIG_CONTROL
        S_STRING = 201,                          // "constant string"
        S_INTEGER = 202,                         // "integer"
        S_FLOAT = 203,                           // "floating point"
        S_BOOLEAN = 204,                         // "boolean"
        S_YYACCEPT = 205,                        // $accept
        S_start = 206,                           // start
        S_207_1 = 207,                           // $@1
        S_208_2 = 208,                           // $@2
        S_209_3 = 209,                           // $@3
        S_210_4 = 210,                           // $@4
        S_211_5 = 211,                           // $@5
        S_212_6 = 212,                           // $@6
        S_213_7 = 213,                           // $@7
        S_214_8 = 214,                           // $@8
        S_215_9 = 215,                           // $@9
        S_216_10 = 216,                          // $@10
        S_217_11 = 217,                          // $@11
        S_218_12 = 218,                          // $@12
        S_219_13 = 219,                          // $@13
        S_220_14 = 220,                          // $@14
        S_value = 221,                           // value
        S_sub_json = 222,                        // sub_json
        S_map2 = 223,                            // map2
        S_224_15 = 224,                          // $@15
        S_map_value = 225,                       // map_value
        S_map_content = 226,                     // map_content
        S_not_empty_map = 227,                   // not_empty_map
        S_list_generic = 228,                    // list_generic
        S_229_16 = 229,                          // $@16
        S_list_content = 230,                    // list_content
        S_not_empty_list = 231,                  // not_empty_list
        S_list_strings = 232,                    // list_strings
        S_233_17 = 233,                          // $@17
        S_list_strings_content = 234,            // list_strings_content
        S_not_empty_list_strings = 235,          // not_empty_list_strings
        S_unknown_map_entry = 236,               // unknown_map_entry
        S_syntax_map = 237,                      // syntax_map
        S_238_18 = 238,                          // $@18
        S_global_object = 239,                   // global_object
        S_240_19 = 240,                          // $@19
        S_sub_dhcp6 = 241,                       // sub_dhcp6
        S_242_20 = 242,                          // $@20
        S_global_params = 243,                   // global_params
        S_global_param = 244,                    // global_param
        S_data_directory = 245,                  // data_directory
        S_246_21 = 246,                          // $@21
        S_preferred_lifetime = 247,              // preferred_lifetime
        S_min_preferred_lifetime = 248,          // min_preferred_lifetime
        S_max_preferred_lifetime = 249,          // max_preferred_lifetime
        S_valid_lifetime = 250,                  // valid_lifetime
        S_min_valid_lifetime = 251,              // min_valid_lifetime
        S_max_valid_lifetime = 252,              // max_valid_lifetime
        S_renew_timer = 253,                     // renew_timer
        S_rebind_timer = 254,                    // rebind_timer
        S_calculate_tee_times = 255,             // calculate_tee_times
        S_t1_percent = 256,                      // t1_percent
        S_t2_percent = 257,                      // t2_percent
        S_cache_threshold = 258,                 // cache_threshold
        S_cache_max_age = 259,                   // cache_max_age
        S_decline_probation_period = 260,        // decline_probation_period
        S_ddns_send_updates = 261,               // ddns_send_updates
        S_ddns_override_no_update = 262,         // ddns_override_no_update
        S_ddns_override_client_update = 263,     // ddns_override_client_update
        S_ddns_replace_client_name = 264,        // ddns_replace_client_name
        S_265_22 = 265,                          // $@22
        S_ddns_replace_client_name_value = 266,  // ddns_replace_client_name_value
        S_ddns_generated_prefix = 267,           // ddns_generated_prefix
        S_268_23 = 268,                          // $@23
        S_ddns_qualifying_suffix = 269,          // ddns_qualifying_suffix
        S_270_24 = 270,                          // $@24
        S_ddns_update_on_renew = 271,            // ddns_update_on_renew
        S_hostname_char_set = 272,               // hostname_char_set
        S_273_25 = 273,                          // $@25
        S_hostname_char_replacement = 274,       // hostname_char_replacement
        S_275_26 = 275,                          // $@26
        S_store_extended_info = 276,             // store_extended_info
        S_statistic_default_sample_count = 277,  // statistic_default_sample_count
        S_statistic_default_sample_age = 278,    // statistic_default_sample_age
        S_server_tag = 279,                      // server_tag
        S_280_27 = 280,                          // $@27
        S_ip_reservations_unique = 281,          // ip_reservations_unique
        S_interfaces_config = 282,               // interfaces_config
        S_283_28 = 283,                          // $@28
        S_sub_interfaces6 = 284,                 // sub_interfaces6
        S_285_29 = 285,                          // $@29
        S_interfaces_config_params = 286,        // interfaces_config_params
        S_interfaces_config_param = 287,         // interfaces_config_param
        S_interfaces_list = 288,                 // interfaces_list
        S_289_30 = 289,                          // $@30
        S_re_detect = 290,                       // re_detect
        S_lease_database = 291,                  // lease_database
        S_292_31 = 292,                          // $@31
        S_hosts_database = 293,                  // hosts_database
        S_294_32 = 294,                          // $@32
        S_hosts_databases = 295,                 // hosts_databases
        S_296_33 = 296,                          // $@33
        S_database_list = 297,                   // database_list
        S_not_empty_database_list = 298,         // not_empty_database_list
        S_database = 299,                        // database
        S_300_34 = 300,                          // $@34
        S_database_map_params = 301,             // database_map_params
        S_database_map_param = 302,              // database_map_param
        S_database_type = 303,                   // database_type
        S_304_35 = 304,                          // $@35
        S_db_type = 305,                         // db_type
        S_user = 306,                            // user
        S_307_36 = 307,                          // $@36
        S_password = 308,                        // password
        S_309_37 = 309,                          // $@37
        S_host = 310,                            // host
        S_311_38 = 311,                          // $@38
        S_port = 312,                            // port
        S_name = 313,                            // name
        S_314_39 = 314,                          // $@39
        S_persist = 315,                         // persist
        S_lfc_interval = 316,                    // lfc_interval
        S_readonly = 317,                        // readonly
        S_connect_timeout = 318,                 // connect_timeout
        S_reconnect_wait_time = 319,             // reconnect_wait_time
        S_max_row_errors = 320,                  // max_row_errors
        S_request_timeout = 321,                 // request_timeout
        S_tcp_keepalive = 322,                   // tcp_keepalive
        S_tcp_nodelay = 323,                     // tcp_nodelay
        S_contact_points = 324,                  // contact_points
        S_325_40 = 325,                          // $@40
        S_max_reconnect_tries = 326,             // max_reconnect_tries
        S_keyspace = 327,                        // keyspace
        S_328_41 = 328,                          // $@41
        S_consistency = 329,                     // consistency
        S_330_42 = 330,                          // $@42
        S_serial_consistency = 331,              // serial_consistency
        S_332_43 = 332,                          // $@43
        S_sanity_checks = 333,                   // sanity_checks
        S_334_44 = 334,                          // $@44
        S_sanity_checks_params = 335,            // sanity_checks_params
        S_sanity_checks_param = 336,             // sanity_checks_param
        S_lease_checks = 337,                    // lease_checks
        S_338_45 = 338,                          // $@45
        S_mac_sources = 339,                     // mac_sources
        S_340_46 = 340,                          // $@46
        S_mac_sources_list = 341,                // mac_sources_list
        S_mac_sources_value = 342,               // mac_sources_value
        S_duid_id = 343,                         // duid_id
        S_string_id = 344,                       // string_id
        S_host_reservation_identifiers = 345,    // host_reservation_identifiers
        S_346_47 = 346,                          // $@47
        S_host_reservation_identifiers_list = 347, // host_reservation_identifiers_list
        S_host_reservation_identifier = 348,     // host_reservation_identifier
        S_hw_address_id = 349,                   // hw_address_id
        S_flex_id = 350,                         // flex_id
        S_relay_supplied_options = 351,          // relay_supplied_options
        S_352_48 = 352,                          // $@48
        S_dhcp_multi_threading = 353,            // dhcp_multi_threading
        S_354_49 = 354,                          // $@49
        S_multi_threading_params = 355,          // multi_threading_params
        S_multi_threading_param = 356,           // multi_threading_param
        S_enable_multi_threading = 357,          // enable_multi_threading
        S_thread_pool_size = 358,                // thread_pool_size
        S_packet_queue_size = 359,               // packet_queue_size
        S_hooks_libraries = 360,                 // hooks_libraries
        S_361_50 = 361,                          // $@50
        S_hooks_libraries_list = 362,            // hooks_libraries_list
        S_not_empty_hooks_libraries_list = 363,  // not_empty_hooks_libraries_list
        S_hooks_library = 364,                   // hooks_library
        S_365_51 = 365,                          // $@51
        S_sub_hooks_library = 366,               // sub_hooks_library
        S_367_52 = 367,                          // $@52
        S_hooks_params = 368,                    // hooks_params
        S_hooks_param = 369,                     // hooks_param
        S_library = 370,                         // library
        S_371_53 = 371,                          // $@53
        S_parameters = 372,                      // parameters
        S_373_54 = 373,                          // $@54
        S_expired_leases_processing = 374,       // expired_leases_processing
        S_375_55 = 375,                          // $@55
        S_expired_leases_params = 376,           // expired_leases_params
        S_expired_leases_param = 377,            // expired_leases_param
        S_reclaim_timer_wait_time = 378,         // reclaim_timer_wait_time
        S_flush_reclaimed_timer_wait_time = 379, // flush_reclaimed_timer_wait_time
        S_hold_reclaimed_time = 380,             // hold_reclaimed_time
        S_max_reclaim_leases = 381,              // max_reclaim_leases
        S_max_reclaim_time = 382,                // max_reclaim_time
        S_unwarned_reclaim_cycles = 383,         // unwarned_reclaim_cycles
        S_subnet6_list = 384,                    // subnet6_list
        S_385_56 = 385,                          // $@56
        S_subnet6_list_content = 386,            // subnet6_list_content
        S_not_empty_subnet6_list = 387,          // not_empty_subnet6_list
        S_subnet6 = 388,                         // subnet6
        S_389_57 = 389,                          // $@57
        S_sub_subnet6 = 390,                     // sub_subnet6
        S_391_58 = 391,                          // $@58
        S_subnet6_params = 392,                  // subnet6_params
        S_subnet6_param = 393,                   // subnet6_param
        S_subnet = 394,                          // subnet
        S_395_59 = 395,                          // $@59
        S_interface = 396,                       // interface
        S_397_60 = 397,                          // $@60
        S_interface_id = 398,                    // interface_id
        S_399_61 = 399,                          // $@61
        S_client_class = 400,                    // client_class
        S_401_62 = 401,                          // $@62
        S_require_client_classes = 402,          // require_client_classes
        S_403_63 = 403,                          // $@63
        S_reservations_out_of_pool = 404,        // reservations_out_of_pool
        S_reservations_in_subnet = 405,          // reservations_in_subnet
        S_reservations_global = 406,             // reservations_global
        S_reservation_mode = 407,                // reservation_mode
        S_408_64 = 408,                          // $@64
        S_hr_mode = 409,                         // hr_mode
        S_id = 410,                              // id
        S_rapid_commit = 411,                    // rapid_commit
        S_shared_networks = 412,                 // shared_networks
        S_413_65 = 413,                          // $@65
        S_shared_networks_content = 414,         // shared_networks_content
        S_shared_networks_list = 415,            // shared_networks_list
        S_shared_network = 416,                  // shared_network
        S_417_66 = 417,                          // $@66
        S_shared_network_params = 418,           // shared_network_params
        S_shared_network_param = 419,            // shared_network_param
        S_option_def_list = 420,                 // option_def_list
        S_421_67 = 421,                          // $@67
        S_sub_option_def_list = 422,             // sub_option_def_list
        S_423_68 = 423,                          // $@68
        S_option_def_list_content = 424,         // option_def_list_content
        S_not_empty_option_def_list = 425,       // not_empty_option_def_list
        S_option_def_entry = 426,                // option_def_entry
        S_427_69 = 427,                          // $@69
        S_sub_option_def = 428,                  // sub_option_def
        S_429_70 = 429,                          // $@70
        S_option_def_params = 430,               // option_def_params
        S_not_empty_option_def_params = 431,     // not_empty_option_def_params
        S_option_def_param = 432,                // option_def_param
        S_option_def_name = 433,                 // option_def_name
        S_code = 434,                            // code
        S_option_def_code = 435,                 // option_def_code
        S_option_def_type = 436,                 // option_def_type
        S_437_71 = 437,                          // $@71
        S_option_def_record_types = 438,         // option_def_record_types
        S_439_72 = 439,                          // $@72
        S_space = 440,                           // space
        S_441_73 = 441,                          // $@73
        S_option_def_space = 442,                // option_def_space
        S_option_def_encapsulate = 443,          // option_def_encapsulate
        S_444_74 = 444,                          // $@74
        S_option_def_array = 445,                // option_def_array
        S_option_data_list = 446,                // option_data_list
        S_447_75 = 447,                          // $@75
        S_option_data_list_content = 448,        // option_data_list_content
        S_not_empty_option_data_list = 449,      // not_empty_option_data_list
        S_option_data_entry = 450,               // option_data_entry
        S_451_76 = 451,                          // $@76
        S_sub_option_data = 452,                 // sub_option_data
        S_453_77 = 453,                          // $@77
        S_option_data_params = 454,              // option_data_params
        S_not_empty_option_data_params = 455,    // not_empty_option_data_params
        S_option_data_param = 456,               // option_data_param
        S_option_data_name = 457,                // option_data_name
        S_option_data_data = 458,                // option_data_data
        S_459_78 = 459,                          // $@78
        S_option_data_code = 460,                // option_data_code
        S_option_data_space = 461,               // option_data_space
        S_option_data_csv_format = 462,          // option_data_csv_format
        S_option_data_always_send = 463,         // option_data_always_send
        S_pools_list = 464,                      // pools_list
        S_465_79 = 465,                          // $@79
        S_pools_list_content = 466,              // pools_list_content
        S_not_empty_pools_list = 467,            // not_empty_pools_list
        S_pool_list_entry = 468,                 // pool_list_entry
        S_469_80 = 469,                          // $@80
        S_sub_pool6 = 470,                       // sub_pool6
        S_471_81 = 471,                          // $@81
        S_pool_params = 472,                     // pool_params
        S_pool_param = 473,                      // pool_param
        S_pool_entry = 474,                      // pool_entry
        S_475_82 = 475,                          // $@82
        S_user_context = 476,                    // user_context
        S_477_83 = 477,                          // $@83
        S_comment = 478,                         // comment
        S_479_84 = 479,                          // $@84
        S_pd_pools_list = 480,                   // pd_pools_list
        S_481_85 = 481,                          // $@85
        S_pd_pools_list_content = 482,           // pd_pools_list_content
        S_not_empty_pd_pools_list = 483,         // not_empty_pd_pools_list
        S_pd_pool_entry = 484,                   // pd_pool_entry
        S_485_86 = 485,                          // $@86
        S_sub_pd_pool = 486,                     // sub_pd_pool
        S_487_87 = 487,                          // $@87
        S_pd_pool_params = 488,                  // pd_pool_params
        S_pd_pool_param = 489,                   // pd_pool_param
        S_pd_prefix = 490,                       // pd_prefix
        S_491_88 = 491,                          // $@88
        S_pd_prefix_len = 492,                   // pd_prefix_len
        S_excluded_prefix = 493,                 // excluded_prefix
        S_494_89 = 494,                          // $@89
        S_excluded_prefix_len = 495,             // excluded_prefix_len
        S_pd_delegated_len = 496,                // pd_delegated_len
        S_reservations = 497,                    // reservations
        S_498_90 = 498,                          // $@90
        S_reservations_list = 499,               // reservations_list
        S_not_empty_reservations_list = 500,     // not_empty_reservations_list
        S_reservation = 501,                     // reservation
        S_502_91 = 502,                          // $@91
        S_sub_reservation = 503,                 // sub_reservation
        S_504_92 = 504,                          // $@92
        S_reservation_params = 505,              // reservation_params
        S_not_empty_reservation_params = 506,    // not_empty_reservation_params
        S_reservation_param = 507,               // reservation_param
        S_ip_addresses = 508,                    // ip_addresses
        S_509_93 = 509,                          // $@93
        S_prefixes = 510,                        // prefixes
        S_511_94 = 511,                          // $@94
        S_duid = 512,                            // duid
        S_513_95 = 513,                          // $@95
        S_hw_address = 514,                      // hw_address
        S_515_96 = 515,                          // $@96
        S_hostname = 516,                        // hostname
        S_517_97 = 517,                          // $@97
        S_flex_id_value = 518,                   // flex_id_value
        S_519_98 = 519,                          // $@98
        S_reservation_client_classes = 520,      // reservation_client_classes
        S_521_99 = 521,                          // $@99
        S_relay = 522,                           // relay
        S_523_100 = 523,                         // $@100
        S_relay_map = 524,                       // relay_map
        S_ip_address = 525,                      // ip_address
        S_526_101 = 526,                         // $@101
        S_client_classes = 527,                  // client_classes
        S_528_102 = 528,                         // $@102
        S_client_classes_list = 529,             // client_classes_list
        S_client_class_entry = 530,              // client_class_entry
        S_531_103 = 531,                         // $@103
        S_client_class_params = 532,             // client_class_params
        S_not_empty_client_class_params = 533,   // not_empty_client_class_params
        S_client_class_param = 534,              // client_class_param
        S_client_class_name = 535,               // client_class_name
        S_client_class_test = 536,               // client_class_test
        S_537_104 = 537,                         // $@104
        S_only_if_required = 538,                // only_if_required
        S_server_id = 539,                       // server_id
        S_540_105 = 540,                         // $@105
        S_server_id_params = 541,                // server_id_params
        S_server_id_param = 542,                 // server_id_param
        S_server_id_type = 543,                  // server_id_type
        S_544_106 = 544,                         // $@106
        S_duid_type = 545,                       // duid_type
        S_htype = 546,                           // htype
        S_identifier = 547,                      // identifier
        S_548_107 = 548,                         // $@107
        S_time = 549,                            // time
        S_enterprise_id = 550,                   // enterprise_id
        S_dhcp4o6_port = 551,                    // dhcp4o6_port
        S_control_socket = 552,                  // control_socket
        S_553_108 = 553,                         // $@108
        S_control_socket_params = 554,           // control_socket_params
        S_control_socket_param = 555,            // control_socket_param
        S_socket_type = 556,                     // socket_type
        S_557_109 = 557,                         // $@109
        S_socket_name = 558,                     // socket_name
        S_559_110 = 559,                         // $@110
        S_dhcp_queue_control = 560,              // dhcp_queue_control
        S_561_111 = 561,                         // $@111
        S_queue_control_params = 562,            // queue_control_params
        S_queue_control_param = 563,             // queue_control_param
        S_enable_queue = 564,                    // enable_queue
        S_queue_type = 565,                      // queue_type
        S_566_112 = 566,                         // $@112
        S_capacity = 567,                        // capacity
        S_arbitrary_map_entry = 568,             // arbitrary_map_entry
        S_569_113 = 569,                         // $@113
        S_dhcp_ddns = 570,                       // dhcp_ddns
        S_571_114 = 571,                         // $@114
        S_sub_dhcp_ddns = 572,                   // sub_dhcp_ddns
        S_573_115 = 573,                         // $@115
        S_dhcp_ddns_params = 574,                // dhcp_ddns_params
        S_dhcp_ddns_param = 575,                 // dhcp_ddns_param
        S_enable_updates = 576,                  // enable_updates
        S_dep_qualifying_suffix = 577,           // dep_qualifying_suffix
        S_578_116 = 578,                         // $@116
        S_server_ip = 579,                       // server_ip
        S_580_117 = 580,                         // $@117
        S_server_port = 581,                     // server_port
        S_sender_ip = 582,                       // sender_ip
        S_583_118 = 583,                         // $@118
        S_sender_port = 584,                     // sender_port
        S_max_queue_size = 585,                  // max_queue_size
        S_ncr_protocol = 586,                    // ncr_protocol
        S_587_119 = 587,                         // $@119
        S_ncr_protocol_value = 588,              // ncr_protocol_value
        S_ncr_format = 589,                      // ncr_format
        S_590_120 = 590,                         // $@120
        S_dep_override_no_update = 591,          // dep_override_no_update
        S_dep_override_client_update = 592,      // dep_override_client_update
        S_dep_replace_client_name = 593,         // dep_replace_client_name
        S_594_121 = 594,                         // $@121
        S_dep_generated_prefix = 595,            // dep_generated_prefix
        S_596_122 = 596,                         // $@122
        S_dep_hostname_char_set = 597,           // dep_hostname_char_set
        S_598_123 = 598,                         // $@123
        S_dep_hostname_char_replacement = 599,   // dep_hostname_char_replacement
        S_600_124 = 600,                         // $@124
        S_config_control = 601,                  // config_control
        S_602_125 = 602,                         // $@125
        S_sub_config_control = 603,              // sub_config_control
        S_604_126 = 604,                         // $@126
        S_config_control_params = 605,           // config_control_params
        S_config_control_param = 606,            // config_control_param
        S_config_databases = 607,                // config_databases
        S_608_127 = 608,                         // $@127
        S_config_fetch_wait_time = 609,          // config_fetch_wait_time
        S_loggers = 610,                         // loggers
        S_611_128 = 611,                         // $@128
        S_loggers_entries = 612,                 // loggers_entries
        S_logger_entry = 613,                    // logger_entry
        S_614_129 = 614,                         // $@129
        S_logger_params = 615,                   // logger_params
        S_logger_param = 616,                    // logger_param
        S_debuglevel = 617,                      // debuglevel
        S_severity = 618,                        // severity
        S_619_130 = 619,                         // $@130
        S_output_options_list = 620,             // output_options_list
        S_621_131 = 621,                         // $@131
        S_output_options_list_content = 622,     // output_options_list_content
        S_output_entry = 623,                    // output_entry
        S_624_132 = 624,                         // $@132
        S_output_params_list = 625,              // output_params_list
        S_output_params = 626,                   // output_params
        S_output = 627,                          // output
        S_628_133 = 628,                         // $@133
        S_flush = 629,                           // flush
        S_maxsize = 630,                         // maxsize
        S_maxver = 631,                          // maxver
        S_pattern = 632,                         // pattern
        S_633_134 = 633                          // $@134
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
      basic_symbol ()
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
      case symbol_kind::S_ddns_replace_client_name_value: // ddns_replace_client_name_value
      case symbol_kind::S_db_type: // db_type
      case symbol_kind::S_hr_mode: // hr_mode
      case symbol_kind::S_duid_type: // duid_type
      case symbol_kind::S_ncr_protocol_value: // ncr_protocol_value
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
      void clear ()
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
      case symbol_kind::S_ddns_replace_client_name_value: // ddns_replace_client_name_value
      case symbol_kind::S_db_type: // db_type
      case symbol_kind::S_hr_mode: // hr_mode
      case symbol_kind::S_duid_type: // duid_type
      case symbol_kind::S_ncr_protocol_value: // ncr_protocol_value
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
        return Dhcp6Parser::symbol_name (this->kind ());
      }

      /// Backward compatibility (Bison 3.6).
      symbol_kind_type type_get () const YY_NOEXCEPT;

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
    struct by_kind
    {
      /// Default constructor.
      by_kind ();

#if 201103L <= YY_CPLUSPLUS
      /// Move constructor.
      by_kind (by_kind&& that);
#endif

      /// Copy constructor.
      by_kind (const by_kind& that);

      /// The symbol kind as needed by the constructor.
      typedef token_kind_type kind_type;

      /// Constructor from (external) token numbers.
      by_kind (kind_type t);

      /// Record that this symbol is empty.
      void clear ();

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
      symbol_type () {}

      /// Constructor for valueless symbols, and symbols from each type.
#if 201103L <= YY_CPLUSPLUS
      symbol_type (int tok, location_type l)
        : super_type(token_type (tok), std::move (l))
      {
        YY_ASSERT (tok == token::TOKEN_END || tok == token::TOKEN_PARSER6_error || tok == token::TOKEN_PARSER6_UNDEF || tok == token::TOKEN_COMMA || tok == token::TOKEN_COLON || tok == token::TOKEN_LSQUARE_BRACKET || tok == token::TOKEN_RSQUARE_BRACKET || tok == token::TOKEN_LCURLY_BRACKET || tok == token::TOKEN_RCURLY_BRACKET || tok == token::TOKEN_NULL_TYPE || tok == token::TOKEN_DHCP6 || tok == token::TOKEN_DATA_DIRECTORY || tok == token::TOKEN_CONFIG_CONTROL || tok == token::TOKEN_CONFIG_DATABASES || tok == token::TOKEN_CONFIG_FETCH_WAIT_TIME || tok == token::TOKEN_INTERFACES_CONFIG || tok == token::TOKEN_INTERFACES || tok == token::TOKEN_RE_DETECT || tok == token::TOKEN_LEASE_DATABASE || tok == token::TOKEN_HOSTS_DATABASE || tok == token::TOKEN_HOSTS_DATABASES || tok == token::TOKEN_TYPE || tok == token::TOKEN_MEMFILE || tok == token::TOKEN_MYSQL || tok == token::TOKEN_POSTGRESQL || tok == token::TOKEN_CQL || tok == token::TOKEN_USER || tok == token::TOKEN_PASSWORD || tok == token::TOKEN_HOST || tok == token::TOKEN_PORT || tok == token::TOKEN_PERSIST || tok == token::TOKEN_LFC_INTERVAL || tok == token::TOKEN_READONLY || tok == token::TOKEN_CONNECT_TIMEOUT || tok == token::TOKEN_CONTACT_POINTS || tok == token::TOKEN_MAX_RECONNECT_TRIES || tok == token::TOKEN_RECONNECT_WAIT_TIME || tok == token::TOKEN_KEYSPACE || tok == token::TOKEN_CONSISTENCY || tok == token::TOKEN_SERIAL_CONSISTENCY || tok == token::TOKEN_REQUEST_TIMEOUT || tok == token::TOKEN_TCP_KEEPALIVE || tok == token::TOKEN_TCP_NODELAY || tok == token::TOKEN_MAX_ROW_ERRORS || tok == token::TOKEN_PREFERRED_LIFETIME || tok == token::TOKEN_MIN_PREFERRED_LIFETIME || tok == token::TOKEN_MAX_PREFERRED_LIFETIME || tok == token::TOKEN_VALID_LIFETIME || tok == token::TOKEN_MIN_VALID_LIFETIME || tok == token::TOKEN_MAX_VALID_LIFETIME || tok == token::TOKEN_RENEW_TIMER || tok == token::TOKEN_REBIND_TIMER || tok == token::TOKEN_CALCULATE_TEE_TIMES || tok == token::TOKEN_T1_PERCENT || tok == token::TOKEN_T2_PERCENT || tok == token::TOKEN_CACHE_THRESHOLD || tok == token::TOKEN_CACHE_MAX_AGE || tok == token::TOKEN_DECLINE_PROBATION_PERIOD || tok == token::TOKEN_SERVER_TAG || tok == token::TOKEN_STATISTIC_DEFAULT_SAMPLE_COUNT || tok == token::TOKEN_STATISTIC_DEFAULT_SAMPLE_AGE || tok == token::TOKEN_DDNS_SEND_UPDATES || tok == token::TOKEN_DDNS_OVERRIDE_NO_UPDATE || tok == token::TOKEN_DDNS_OVERRIDE_CLIENT_UPDATE || tok == token::TOKEN_DDNS_REPLACE_CLIENT_NAME || tok == token::TOKEN_DDNS_GENERATED_PREFIX || tok == token::TOKEN_DDNS_QUALIFYING_SUFFIX || tok == token::TOKEN_DDNS_UPDATE_ON_RENEW || tok == token::TOKEN_STORE_EXTENDED_INFO || tok == token::TOKEN_SUBNET6 || tok == token::TOKEN_OPTION_DEF || tok == token::TOKEN_OPTION_DATA || tok == token::TOKEN_NAME || tok == token::TOKEN_DATA || tok == token::TOKEN_CODE || tok == token::TOKEN_SPACE || tok == token::TOKEN_CSV_FORMAT || tok == token::TOKEN_ALWAYS_SEND || tok == token::TOKEN_RECORD_TYPES || tok == token::TOKEN_ENCAPSULATE || tok == token::TOKEN_ARRAY || tok == token::TOKEN_SHARED_NETWORKS || tok == token::TOKEN_POOLS || tok == token::TOKEN_POOL || tok == token::TOKEN_PD_POOLS || tok == token::TOKEN_PREFIX || tok == token::TOKEN_PREFIX_LEN || tok == token::TOKEN_EXCLUDED_PREFIX || tok == token::TOKEN_EXCLUDED_PREFIX_LEN || tok == token::TOKEN_DELEGATED_LEN || tok == token::TOKEN_USER_CONTEXT || tok == token::TOKEN_COMMENT || tok == token::TOKEN_SUBNET || tok == token::TOKEN_INTERFACE || tok == token::TOKEN_INTERFACE_ID || tok == token::TOKEN_ID || tok == token::TOKEN_RAPID_COMMIT || tok == token::TOKEN_RESERVATION_MODE || tok == token::TOKEN_RESERVATIONS_OUT_OF_POOL || tok == token::TOKEN_RESERVATIONS_IN_SUBNET || tok == token::TOKEN_RESERVATIONS_GLOBAL || tok == token::TOKEN_DISABLED || tok == token::TOKEN_OUT_OF_POOL || tok == token::TOKEN_GLOBAL || tok == token::TOKEN_ALL || tok == token::TOKEN_MAC_SOURCES || tok == token::TOKEN_RELAY_SUPPLIED_OPTIONS || tok == token::TOKEN_HOST_RESERVATION_IDENTIFIERS || tok == token::TOKEN_SANITY_CHECKS || tok == token::TOKEN_LEASE_CHECKS || tok == token::TOKEN_CLIENT_CLASSES || tok == token::TOKEN_REQUIRE_CLIENT_CLASSES || tok == token::TOKEN_TEST || tok == token::TOKEN_ONLY_IF_REQUIRED || tok == token::TOKEN_CLIENT_CLASS || tok == token::TOKEN_RESERVATIONS || tok == token::TOKEN_IP_ADDRESSES || tok == token::TOKEN_PREFIXES || tok == token::TOKEN_DUID || tok == token::TOKEN_HW_ADDRESS || tok == token::TOKEN_HOSTNAME || tok == token::TOKEN_FLEX_ID || tok == token::TOKEN_RELAY || tok == token::TOKEN_IP_ADDRESS || tok == token::TOKEN_HOOKS_LIBRARIES || tok == token::TOKEN_LIBRARY || tok == token::TOKEN_PARAMETERS || tok == token::TOKEN_EXPIRED_LEASES_PROCESSING || tok == token::TOKEN_RECLAIM_TIMER_WAIT_TIME || tok == token::TOKEN_FLUSH_RECLAIMED_TIMER_WAIT_TIME || tok == token::TOKEN_HOLD_RECLAIMED_TIME || tok == token::TOKEN_MAX_RECLAIM_LEASES || tok == token::TOKEN_MAX_RECLAIM_TIME || tok == token::TOKEN_UNWARNED_RECLAIM_CYCLES || tok == token::TOKEN_SERVER_ID || tok == token::TOKEN_LLT || tok == token::TOKEN_EN || tok == token::TOKEN_LL || tok == token::TOKEN_IDENTIFIER || tok == token::TOKEN_HTYPE || tok == token::TOKEN_TIME || tok == token::TOKEN_ENTERPRISE_ID || tok == token::TOKEN_DHCP4O6_PORT || tok == token::TOKEN_DHCP_MULTI_THREADING || tok == token::TOKEN_ENABLE_MULTI_THREADING || tok == token::TOKEN_THREAD_POOL_SIZE || tok == token::TOKEN_PACKET_QUEUE_SIZE || tok == token::TOKEN_CONTROL_SOCKET || tok == token::TOKEN_SOCKET_TYPE || tok == token::TOKEN_SOCKET_NAME || tok == token::TOKEN_DHCP_QUEUE_CONTROL || tok == token::TOKEN_ENABLE_QUEUE || tok == token::TOKEN_QUEUE_TYPE || tok == token::TOKEN_CAPACITY || tok == token::TOKEN_DHCP_DDNS || tok == token::TOKEN_ENABLE_UPDATES || tok == token::TOKEN_QUALIFYING_SUFFIX || tok == token::TOKEN_SERVER_IP || tok == token::TOKEN_SERVER_PORT || tok == token::TOKEN_SENDER_IP || tok == token::TOKEN_SENDER_PORT || tok == token::TOKEN_MAX_QUEUE_SIZE || tok == token::TOKEN_NCR_PROTOCOL || tok == token::TOKEN_NCR_FORMAT || tok == token::TOKEN_OVERRIDE_NO_UPDATE || tok == token::TOKEN_OVERRIDE_CLIENT_UPDATE || tok == token::TOKEN_REPLACE_CLIENT_NAME || tok == token::TOKEN_GENERATED_PREFIX || tok == token::TOKEN_UDP || tok == token::TOKEN_TCP || tok == token::TOKEN_JSON || tok == token::TOKEN_WHEN_PRESENT || tok == token::TOKEN_NEVER || tok == token::TOKEN_ALWAYS || tok == token::TOKEN_WHEN_NOT_PRESENT || tok == token::TOKEN_HOSTNAME_CHAR_SET || tok == token::TOKEN_HOSTNAME_CHAR_REPLACEMENT || tok == token::TOKEN_IP_RESERVATIONS_UNIQUE || tok == token::TOKEN_LOGGERS || tok == token::TOKEN_OUTPUT_OPTIONS || tok == token::TOKEN_OUTPUT || tok == token::TOKEN_DEBUGLEVEL || tok == token::TOKEN_SEVERITY || tok == token::TOKEN_FLUSH || tok == token::TOKEN_MAXSIZE || tok == token::TOKEN_MAXVER || tok == token::TOKEN_PATTERN || tok == token::TOKEN_TOPLEVEL_JSON || tok == token::TOKEN_TOPLEVEL_DHCP6 || tok == token::TOKEN_SUB_DHCP6 || tok == token::TOKEN_SUB_INTERFACES6 || tok == token::TOKEN_SUB_SUBNET6 || tok == token::TOKEN_SUB_POOL6 || tok == token::TOKEN_SUB_PD_POOL || tok == token::TOKEN_SUB_RESERVATION || tok == token::TOKEN_SUB_OPTION_DEFS || tok == token::TOKEN_SUB_OPTION_DEF || tok == token::TOKEN_SUB_OPTION_DATA || tok == token::TOKEN_SUB_HOOKS_LIBRARY || tok == token::TOKEN_SUB_DHCP_DDNS || tok == token::TOKEN_SUB_CONFIG_CONTROL);
      }
#else
      symbol_type (int tok, const location_type& l)
        : super_type(token_type (tok), l)
      {
        YY_ASSERT (tok == token::TOKEN_END || tok == token::TOKEN_PARSER6_error || tok == token::TOKEN_PARSER6_UNDEF || tok == token::TOKEN_COMMA || tok == token::TOKEN_COLON || tok == token::TOKEN_LSQUARE_BRACKET || tok == token::TOKEN_RSQUARE_BRACKET || tok == token::TOKEN_LCURLY_BRACKET || tok == token::TOKEN_RCURLY_BRACKET || tok == token::TOKEN_NULL_TYPE || tok == token::TOKEN_DHCP6 || tok == token::TOKEN_DATA_DIRECTORY || tok == token::TOKEN_CONFIG_CONTROL || tok == token::TOKEN_CONFIG_DATABASES || tok == token::TOKEN_CONFIG_FETCH_WAIT_TIME || tok == token::TOKEN_INTERFACES_CONFIG || tok == token::TOKEN_INTERFACES || tok == token::TOKEN_RE_DETECT || tok == token::TOKEN_LEASE_DATABASE || tok == token::TOKEN_HOSTS_DATABASE || tok == token::TOKEN_HOSTS_DATABASES || tok == token::TOKEN_TYPE || tok == token::TOKEN_MEMFILE || tok == token::TOKEN_MYSQL || tok == token::TOKEN_POSTGRESQL || tok == token::TOKEN_CQL || tok == token::TOKEN_USER || tok == token::TOKEN_PASSWORD || tok == token::TOKEN_HOST || tok == token::TOKEN_PORT || tok == token::TOKEN_PERSIST || tok == token::TOKEN_LFC_INTERVAL || tok == token::TOKEN_READONLY || tok == token::TOKEN_CONNECT_TIMEOUT || tok == token::TOKEN_CONTACT_POINTS || tok == token::TOKEN_MAX_RECONNECT_TRIES || tok == token::TOKEN_RECONNECT_WAIT_TIME || tok == token::TOKEN_KEYSPACE || tok == token::TOKEN_CONSISTENCY || tok == token::TOKEN_SERIAL_CONSISTENCY || tok == token::TOKEN_REQUEST_TIMEOUT || tok == token::TOKEN_TCP_KEEPALIVE || tok == token::TOKEN_TCP_NODELAY || tok == token::TOKEN_MAX_ROW_ERRORS || tok == token::TOKEN_PREFERRED_LIFETIME || tok == token::TOKEN_MIN_PREFERRED_LIFETIME || tok == token::TOKEN_MAX_PREFERRED_LIFETIME || tok == token::TOKEN_VALID_LIFETIME || tok == token::TOKEN_MIN_VALID_LIFETIME || tok == token::TOKEN_MAX_VALID_LIFETIME || tok == token::TOKEN_RENEW_TIMER || tok == token::TOKEN_REBIND_TIMER || tok == token::TOKEN_CALCULATE_TEE_TIMES || tok == token::TOKEN_T1_PERCENT || tok == token::TOKEN_T2_PERCENT || tok == token::TOKEN_CACHE_THRESHOLD || tok == token::TOKEN_CACHE_MAX_AGE || tok == token::TOKEN_DECLINE_PROBATION_PERIOD || tok == token::TOKEN_SERVER_TAG || tok == token::TOKEN_STATISTIC_DEFAULT_SAMPLE_COUNT || tok == token::TOKEN_STATISTIC_DEFAULT_SAMPLE_AGE || tok == token::TOKEN_DDNS_SEND_UPDATES || tok == token::TOKEN_DDNS_OVERRIDE_NO_UPDATE || tok == token::TOKEN_DDNS_OVERRIDE_CLIENT_UPDATE || tok == token::TOKEN_DDNS_REPLACE_CLIENT_NAME || tok == token::TOKEN_DDNS_GENERATED_PREFIX || tok == token::TOKEN_DDNS_QUALIFYING_SUFFIX || tok == token::TOKEN_DDNS_UPDATE_ON_RENEW || tok == token::TOKEN_STORE_EXTENDED_INFO || tok == token::TOKEN_SUBNET6 || tok == token::TOKEN_OPTION_DEF || tok == token::TOKEN_OPTION_DATA || tok == token::TOKEN_NAME || tok == token::TOKEN_DATA || tok == token::TOKEN_CODE || tok == token::TOKEN_SPACE || tok == token::TOKEN_CSV_FORMAT || tok == token::TOKEN_ALWAYS_SEND || tok == token::TOKEN_RECORD_TYPES || tok == token::TOKEN_ENCAPSULATE || tok == token::TOKEN_ARRAY || tok == token::TOKEN_SHARED_NETWORKS || tok == token::TOKEN_POOLS || tok == token::TOKEN_POOL || tok == token::TOKEN_PD_POOLS || tok == token::TOKEN_PREFIX || tok == token::TOKEN_PREFIX_LEN || tok == token::TOKEN_EXCLUDED_PREFIX || tok == token::TOKEN_EXCLUDED_PREFIX_LEN || tok == token::TOKEN_DELEGATED_LEN || tok == token::TOKEN_USER_CONTEXT || tok == token::TOKEN_COMMENT || tok == token::TOKEN_SUBNET || tok == token::TOKEN_INTERFACE || tok == token::TOKEN_INTERFACE_ID || tok == token::TOKEN_ID || tok == token::TOKEN_RAPID_COMMIT || tok == token::TOKEN_RESERVATION_MODE || tok == token::TOKEN_RESERVATIONS_OUT_OF_POOL || tok == token::TOKEN_RESERVATIONS_IN_SUBNET || tok == token::TOKEN_RESERVATIONS_GLOBAL || tok == token::TOKEN_DISABLED || tok == token::TOKEN_OUT_OF_POOL || tok == token::TOKEN_GLOBAL || tok == token::TOKEN_ALL || tok == token::TOKEN_MAC_SOURCES || tok == token::TOKEN_RELAY_SUPPLIED_OPTIONS || tok == token::TOKEN_HOST_RESERVATION_IDENTIFIERS || tok == token::TOKEN_SANITY_CHECKS || tok == token::TOKEN_LEASE_CHECKS || tok == token::TOKEN_CLIENT_CLASSES || tok == token::TOKEN_REQUIRE_CLIENT_CLASSES || tok == token::TOKEN_TEST || tok == token::TOKEN_ONLY_IF_REQUIRED || tok == token::TOKEN_CLIENT_CLASS || tok == token::TOKEN_RESERVATIONS || tok == token::TOKEN_IP_ADDRESSES || tok == token::TOKEN_PREFIXES || tok == token::TOKEN_DUID || tok == token::TOKEN_HW_ADDRESS || tok == token::TOKEN_HOSTNAME || tok == token::TOKEN_FLEX_ID || tok == token::TOKEN_RELAY || tok == token::TOKEN_IP_ADDRESS || tok == token::TOKEN_HOOKS_LIBRARIES || tok == token::TOKEN_LIBRARY || tok == token::TOKEN_PARAMETERS || tok == token::TOKEN_EXPIRED_LEASES_PROCESSING || tok == token::TOKEN_RECLAIM_TIMER_WAIT_TIME || tok == token::TOKEN_FLUSH_RECLAIMED_TIMER_WAIT_TIME || tok == token::TOKEN_HOLD_RECLAIMED_TIME || tok == token::TOKEN_MAX_RECLAIM_LEASES || tok == token::TOKEN_MAX_RECLAIM_TIME || tok == token::TOKEN_UNWARNED_RECLAIM_CYCLES || tok == token::TOKEN_SERVER_ID || tok == token::TOKEN_LLT || tok == token::TOKEN_EN || tok == token::TOKEN_LL || tok == token::TOKEN_IDENTIFIER || tok == token::TOKEN_HTYPE || tok == token::TOKEN_TIME || tok == token::TOKEN_ENTERPRISE_ID || tok == token::TOKEN_DHCP4O6_PORT || tok == token::TOKEN_DHCP_MULTI_THREADING || tok == token::TOKEN_ENABLE_MULTI_THREADING || tok == token::TOKEN_THREAD_POOL_SIZE || tok == token::TOKEN_PACKET_QUEUE_SIZE || tok == token::TOKEN_CONTROL_SOCKET || tok == token::TOKEN_SOCKET_TYPE || tok == token::TOKEN_SOCKET_NAME || tok == token::TOKEN_DHCP_QUEUE_CONTROL || tok == token::TOKEN_ENABLE_QUEUE || tok == token::TOKEN_QUEUE_TYPE || tok == token::TOKEN_CAPACITY || tok == token::TOKEN_DHCP_DDNS || tok == token::TOKEN_ENABLE_UPDATES || tok == token::TOKEN_QUALIFYING_SUFFIX || tok == token::TOKEN_SERVER_IP || tok == token::TOKEN_SERVER_PORT || tok == token::TOKEN_SENDER_IP || tok == token::TOKEN_SENDER_PORT || tok == token::TOKEN_MAX_QUEUE_SIZE || tok == token::TOKEN_NCR_PROTOCOL || tok == token::TOKEN_NCR_FORMAT || tok == token::TOKEN_OVERRIDE_NO_UPDATE || tok == token::TOKEN_OVERRIDE_CLIENT_UPDATE || tok == token::TOKEN_REPLACE_CLIENT_NAME || tok == token::TOKEN_GENERATED_PREFIX || tok == token::TOKEN_UDP || tok == token::TOKEN_TCP || tok == token::TOKEN_JSON || tok == token::TOKEN_WHEN_PRESENT || tok == token::TOKEN_NEVER || tok == token::TOKEN_ALWAYS || tok == token::TOKEN_WHEN_NOT_PRESENT || tok == token::TOKEN_HOSTNAME_CHAR_SET || tok == token::TOKEN_HOSTNAME_CHAR_REPLACEMENT || tok == token::TOKEN_IP_RESERVATIONS_UNIQUE || tok == token::TOKEN_LOGGERS || tok == token::TOKEN_OUTPUT_OPTIONS || tok == token::TOKEN_OUTPUT || tok == token::TOKEN_DEBUGLEVEL || tok == token::TOKEN_SEVERITY || tok == token::TOKEN_FLUSH || tok == token::TOKEN_MAXSIZE || tok == token::TOKEN_MAXVER || tok == token::TOKEN_PATTERN || tok == token::TOKEN_TOPLEVEL_JSON || tok == token::TOKEN_TOPLEVEL_DHCP6 || tok == token::TOKEN_SUB_DHCP6 || tok == token::TOKEN_SUB_INTERFACES6 || tok == token::TOKEN_SUB_SUBNET6 || tok == token::TOKEN_SUB_POOL6 || tok == token::TOKEN_SUB_PD_POOL || tok == token::TOKEN_SUB_RESERVATION || tok == token::TOKEN_SUB_OPTION_DEFS || tok == token::TOKEN_SUB_OPTION_DEF || tok == token::TOKEN_SUB_OPTION_DATA || tok == token::TOKEN_SUB_HOOKS_LIBRARY || tok == token::TOKEN_SUB_DHCP_DDNS || tok == token::TOKEN_SUB_CONFIG_CONTROL);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      symbol_type (int tok, bool v, location_type l)
        : super_type(token_type (tok), std::move (v), std::move (l))
      {
        YY_ASSERT (tok == token::TOKEN_BOOLEAN);
      }
#else
      symbol_type (int tok, const bool& v, const location_type& l)
        : super_type(token_type (tok), v, l)
      {
        YY_ASSERT (tok == token::TOKEN_BOOLEAN);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      symbol_type (int tok, double v, location_type l)
        : super_type(token_type (tok), std::move (v), std::move (l))
      {
        YY_ASSERT (tok == token::TOKEN_FLOAT);
      }
#else
      symbol_type (int tok, const double& v, const location_type& l)
        : super_type(token_type (tok), v, l)
      {
        YY_ASSERT (tok == token::TOKEN_FLOAT);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      symbol_type (int tok, int64_t v, location_type l)
        : super_type(token_type (tok), std::move (v), std::move (l))
      {
        YY_ASSERT (tok == token::TOKEN_INTEGER);
      }
#else
      symbol_type (int tok, const int64_t& v, const location_type& l)
        : super_type(token_type (tok), v, l)
      {
        YY_ASSERT (tok == token::TOKEN_INTEGER);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      symbol_type (int tok, std::string v, location_type l)
        : super_type(token_type (tok), std::move (v), std::move (l))
      {
        YY_ASSERT (tok == token::TOKEN_STRING);
      }
#else
      symbol_type (int tok, const std::string& v, const location_type& l)
        : super_type(token_type (tok), v, l)
      {
        YY_ASSERT (tok == token::TOKEN_STRING);
      }
#endif
    };

    /// Build a parser object.
    Dhcp6Parser (isc::dhcp::Parser6Context& ctx_yyarg);
    virtual ~Dhcp6Parser ();

#if 201103L <= YY_CPLUSPLUS
    /// Non copyable.
    Dhcp6Parser (const Dhcp6Parser&) = delete;
    /// Non copyable.
    Dhcp6Parser& operator= (const Dhcp6Parser&) = delete;
#endif

    /// Parse.  An alias for parse ().
    /// \returns  0 iff parsing succeeded.
    int operator() ();

    /// Parse.
    /// \returns  0 iff parsing succeeded.
    virtual int parse ();

#if PARSER6_DEBUG
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
      make_PARSER6_error (location_type l)
      {
        return symbol_type (token::TOKEN_PARSER6_error, std::move (l));
      }
#else
      static
      symbol_type
      make_PARSER6_error (const location_type& l)
      {
        return symbol_type (token::TOKEN_PARSER6_error, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_PARSER6_UNDEF (location_type l)
      {
        return symbol_type (token::TOKEN_PARSER6_UNDEF, std::move (l));
      }
#else
      static
      symbol_type
      make_PARSER6_UNDEF (const location_type& l)
      {
        return symbol_type (token::TOKEN_PARSER6_UNDEF, l);
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
      make_DHCP6 (location_type l)
      {
        return symbol_type (token::TOKEN_DHCP6, std::move (l));
      }
#else
      static
      symbol_type
      make_DHCP6 (const location_type& l)
      {
        return symbol_type (token::TOKEN_DHCP6, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_DATA_DIRECTORY (location_type l)
      {
        return symbol_type (token::TOKEN_DATA_DIRECTORY, std::move (l));
      }
#else
      static
      symbol_type
      make_DATA_DIRECTORY (const location_type& l)
      {
        return symbol_type (token::TOKEN_DATA_DIRECTORY, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_CONFIG_CONTROL (location_type l)
      {
        return symbol_type (token::TOKEN_CONFIG_CONTROL, std::move (l));
      }
#else
      static
      symbol_type
      make_CONFIG_CONTROL (const location_type& l)
      {
        return symbol_type (token::TOKEN_CONFIG_CONTROL, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_CONFIG_DATABASES (location_type l)
      {
        return symbol_type (token::TOKEN_CONFIG_DATABASES, std::move (l));
      }
#else
      static
      symbol_type
      make_CONFIG_DATABASES (const location_type& l)
      {
        return symbol_type (token::TOKEN_CONFIG_DATABASES, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_CONFIG_FETCH_WAIT_TIME (location_type l)
      {
        return symbol_type (token::TOKEN_CONFIG_FETCH_WAIT_TIME, std::move (l));
      }
#else
      static
      symbol_type
      make_CONFIG_FETCH_WAIT_TIME (const location_type& l)
      {
        return symbol_type (token::TOKEN_CONFIG_FETCH_WAIT_TIME, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_INTERFACES_CONFIG (location_type l)
      {
        return symbol_type (token::TOKEN_INTERFACES_CONFIG, std::move (l));
      }
#else
      static
      symbol_type
      make_INTERFACES_CONFIG (const location_type& l)
      {
        return symbol_type (token::TOKEN_INTERFACES_CONFIG, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_INTERFACES (location_type l)
      {
        return symbol_type (token::TOKEN_INTERFACES, std::move (l));
      }
#else
      static
      symbol_type
      make_INTERFACES (const location_type& l)
      {
        return symbol_type (token::TOKEN_INTERFACES, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_RE_DETECT (location_type l)
      {
        return symbol_type (token::TOKEN_RE_DETECT, std::move (l));
      }
#else
      static
      symbol_type
      make_RE_DETECT (const location_type& l)
      {
        return symbol_type (token::TOKEN_RE_DETECT, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_LEASE_DATABASE (location_type l)
      {
        return symbol_type (token::TOKEN_LEASE_DATABASE, std::move (l));
      }
#else
      static
      symbol_type
      make_LEASE_DATABASE (const location_type& l)
      {
        return symbol_type (token::TOKEN_LEASE_DATABASE, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_HOSTS_DATABASE (location_type l)
      {
        return symbol_type (token::TOKEN_HOSTS_DATABASE, std::move (l));
      }
#else
      static
      symbol_type
      make_HOSTS_DATABASE (const location_type& l)
      {
        return symbol_type (token::TOKEN_HOSTS_DATABASE, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_HOSTS_DATABASES (location_type l)
      {
        return symbol_type (token::TOKEN_HOSTS_DATABASES, std::move (l));
      }
#else
      static
      symbol_type
      make_HOSTS_DATABASES (const location_type& l)
      {
        return symbol_type (token::TOKEN_HOSTS_DATABASES, l);
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
      make_MEMFILE (location_type l)
      {
        return symbol_type (token::TOKEN_MEMFILE, std::move (l));
      }
#else
      static
      symbol_type
      make_MEMFILE (const location_type& l)
      {
        return symbol_type (token::TOKEN_MEMFILE, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_MYSQL (location_type l)
      {
        return symbol_type (token::TOKEN_MYSQL, std::move (l));
      }
#else
      static
      symbol_type
      make_MYSQL (const location_type& l)
      {
        return symbol_type (token::TOKEN_MYSQL, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_POSTGRESQL (location_type l)
      {
        return symbol_type (token::TOKEN_POSTGRESQL, std::move (l));
      }
#else
      static
      symbol_type
      make_POSTGRESQL (const location_type& l)
      {
        return symbol_type (token::TOKEN_POSTGRESQL, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_CQL (location_type l)
      {
        return symbol_type (token::TOKEN_CQL, std::move (l));
      }
#else
      static
      symbol_type
      make_CQL (const location_type& l)
      {
        return symbol_type (token::TOKEN_CQL, l);
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
      make_HOST (location_type l)
      {
        return symbol_type (token::TOKEN_HOST, std::move (l));
      }
#else
      static
      symbol_type
      make_HOST (const location_type& l)
      {
        return symbol_type (token::TOKEN_HOST, l);
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
      make_PERSIST (location_type l)
      {
        return symbol_type (token::TOKEN_PERSIST, std::move (l));
      }
#else
      static
      symbol_type
      make_PERSIST (const location_type& l)
      {
        return symbol_type (token::TOKEN_PERSIST, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_LFC_INTERVAL (location_type l)
      {
        return symbol_type (token::TOKEN_LFC_INTERVAL, std::move (l));
      }
#else
      static
      symbol_type
      make_LFC_INTERVAL (const location_type& l)
      {
        return symbol_type (token::TOKEN_LFC_INTERVAL, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_READONLY (location_type l)
      {
        return symbol_type (token::TOKEN_READONLY, std::move (l));
      }
#else
      static
      symbol_type
      make_READONLY (const location_type& l)
      {
        return symbol_type (token::TOKEN_READONLY, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_CONNECT_TIMEOUT (location_type l)
      {
        return symbol_type (token::TOKEN_CONNECT_TIMEOUT, std::move (l));
      }
#else
      static
      symbol_type
      make_CONNECT_TIMEOUT (const location_type& l)
      {
        return symbol_type (token::TOKEN_CONNECT_TIMEOUT, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_CONTACT_POINTS (location_type l)
      {
        return symbol_type (token::TOKEN_CONTACT_POINTS, std::move (l));
      }
#else
      static
      symbol_type
      make_CONTACT_POINTS (const location_type& l)
      {
        return symbol_type (token::TOKEN_CONTACT_POINTS, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_MAX_RECONNECT_TRIES (location_type l)
      {
        return symbol_type (token::TOKEN_MAX_RECONNECT_TRIES, std::move (l));
      }
#else
      static
      symbol_type
      make_MAX_RECONNECT_TRIES (const location_type& l)
      {
        return symbol_type (token::TOKEN_MAX_RECONNECT_TRIES, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_RECONNECT_WAIT_TIME (location_type l)
      {
        return symbol_type (token::TOKEN_RECONNECT_WAIT_TIME, std::move (l));
      }
#else
      static
      symbol_type
      make_RECONNECT_WAIT_TIME (const location_type& l)
      {
        return symbol_type (token::TOKEN_RECONNECT_WAIT_TIME, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_KEYSPACE (location_type l)
      {
        return symbol_type (token::TOKEN_KEYSPACE, std::move (l));
      }
#else
      static
      symbol_type
      make_KEYSPACE (const location_type& l)
      {
        return symbol_type (token::TOKEN_KEYSPACE, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_CONSISTENCY (location_type l)
      {
        return symbol_type (token::TOKEN_CONSISTENCY, std::move (l));
      }
#else
      static
      symbol_type
      make_CONSISTENCY (const location_type& l)
      {
        return symbol_type (token::TOKEN_CONSISTENCY, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_SERIAL_CONSISTENCY (location_type l)
      {
        return symbol_type (token::TOKEN_SERIAL_CONSISTENCY, std::move (l));
      }
#else
      static
      symbol_type
      make_SERIAL_CONSISTENCY (const location_type& l)
      {
        return symbol_type (token::TOKEN_SERIAL_CONSISTENCY, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_REQUEST_TIMEOUT (location_type l)
      {
        return symbol_type (token::TOKEN_REQUEST_TIMEOUT, std::move (l));
      }
#else
      static
      symbol_type
      make_REQUEST_TIMEOUT (const location_type& l)
      {
        return symbol_type (token::TOKEN_REQUEST_TIMEOUT, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TCP_KEEPALIVE (location_type l)
      {
        return symbol_type (token::TOKEN_TCP_KEEPALIVE, std::move (l));
      }
#else
      static
      symbol_type
      make_TCP_KEEPALIVE (const location_type& l)
      {
        return symbol_type (token::TOKEN_TCP_KEEPALIVE, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TCP_NODELAY (location_type l)
      {
        return symbol_type (token::TOKEN_TCP_NODELAY, std::move (l));
      }
#else
      static
      symbol_type
      make_TCP_NODELAY (const location_type& l)
      {
        return symbol_type (token::TOKEN_TCP_NODELAY, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_MAX_ROW_ERRORS (location_type l)
      {
        return symbol_type (token::TOKEN_MAX_ROW_ERRORS, std::move (l));
      }
#else
      static
      symbol_type
      make_MAX_ROW_ERRORS (const location_type& l)
      {
        return symbol_type (token::TOKEN_MAX_ROW_ERRORS, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_PREFERRED_LIFETIME (location_type l)
      {
        return symbol_type (token::TOKEN_PREFERRED_LIFETIME, std::move (l));
      }
#else
      static
      symbol_type
      make_PREFERRED_LIFETIME (const location_type& l)
      {
        return symbol_type (token::TOKEN_PREFERRED_LIFETIME, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_MIN_PREFERRED_LIFETIME (location_type l)
      {
        return symbol_type (token::TOKEN_MIN_PREFERRED_LIFETIME, std::move (l));
      }
#else
      static
      symbol_type
      make_MIN_PREFERRED_LIFETIME (const location_type& l)
      {
        return symbol_type (token::TOKEN_MIN_PREFERRED_LIFETIME, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_MAX_PREFERRED_LIFETIME (location_type l)
      {
        return symbol_type (token::TOKEN_MAX_PREFERRED_LIFETIME, std::move (l));
      }
#else
      static
      symbol_type
      make_MAX_PREFERRED_LIFETIME (const location_type& l)
      {
        return symbol_type (token::TOKEN_MAX_PREFERRED_LIFETIME, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_VALID_LIFETIME (location_type l)
      {
        return symbol_type (token::TOKEN_VALID_LIFETIME, std::move (l));
      }
#else
      static
      symbol_type
      make_VALID_LIFETIME (const location_type& l)
      {
        return symbol_type (token::TOKEN_VALID_LIFETIME, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_MIN_VALID_LIFETIME (location_type l)
      {
        return symbol_type (token::TOKEN_MIN_VALID_LIFETIME, std::move (l));
      }
#else
      static
      symbol_type
      make_MIN_VALID_LIFETIME (const location_type& l)
      {
        return symbol_type (token::TOKEN_MIN_VALID_LIFETIME, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_MAX_VALID_LIFETIME (location_type l)
      {
        return symbol_type (token::TOKEN_MAX_VALID_LIFETIME, std::move (l));
      }
#else
      static
      symbol_type
      make_MAX_VALID_LIFETIME (const location_type& l)
      {
        return symbol_type (token::TOKEN_MAX_VALID_LIFETIME, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_RENEW_TIMER (location_type l)
      {
        return symbol_type (token::TOKEN_RENEW_TIMER, std::move (l));
      }
#else
      static
      symbol_type
      make_RENEW_TIMER (const location_type& l)
      {
        return symbol_type (token::TOKEN_RENEW_TIMER, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_REBIND_TIMER (location_type l)
      {
        return symbol_type (token::TOKEN_REBIND_TIMER, std::move (l));
      }
#else
      static
      symbol_type
      make_REBIND_TIMER (const location_type& l)
      {
        return symbol_type (token::TOKEN_REBIND_TIMER, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_CALCULATE_TEE_TIMES (location_type l)
      {
        return symbol_type (token::TOKEN_CALCULATE_TEE_TIMES, std::move (l));
      }
#else
      static
      symbol_type
      make_CALCULATE_TEE_TIMES (const location_type& l)
      {
        return symbol_type (token::TOKEN_CALCULATE_TEE_TIMES, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_T1_PERCENT (location_type l)
      {
        return symbol_type (token::TOKEN_T1_PERCENT, std::move (l));
      }
#else
      static
      symbol_type
      make_T1_PERCENT (const location_type& l)
      {
        return symbol_type (token::TOKEN_T1_PERCENT, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_T2_PERCENT (location_type l)
      {
        return symbol_type (token::TOKEN_T2_PERCENT, std::move (l));
      }
#else
      static
      symbol_type
      make_T2_PERCENT (const location_type& l)
      {
        return symbol_type (token::TOKEN_T2_PERCENT, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_CACHE_THRESHOLD (location_type l)
      {
        return symbol_type (token::TOKEN_CACHE_THRESHOLD, std::move (l));
      }
#else
      static
      symbol_type
      make_CACHE_THRESHOLD (const location_type& l)
      {
        return symbol_type (token::TOKEN_CACHE_THRESHOLD, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_CACHE_MAX_AGE (location_type l)
      {
        return symbol_type (token::TOKEN_CACHE_MAX_AGE, std::move (l));
      }
#else
      static
      symbol_type
      make_CACHE_MAX_AGE (const location_type& l)
      {
        return symbol_type (token::TOKEN_CACHE_MAX_AGE, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_DECLINE_PROBATION_PERIOD (location_type l)
      {
        return symbol_type (token::TOKEN_DECLINE_PROBATION_PERIOD, std::move (l));
      }
#else
      static
      symbol_type
      make_DECLINE_PROBATION_PERIOD (const location_type& l)
      {
        return symbol_type (token::TOKEN_DECLINE_PROBATION_PERIOD, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_SERVER_TAG (location_type l)
      {
        return symbol_type (token::TOKEN_SERVER_TAG, std::move (l));
      }
#else
      static
      symbol_type
      make_SERVER_TAG (const location_type& l)
      {
        return symbol_type (token::TOKEN_SERVER_TAG, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_STATISTIC_DEFAULT_SAMPLE_COUNT (location_type l)
      {
        return symbol_type (token::TOKEN_STATISTIC_DEFAULT_SAMPLE_COUNT, std::move (l));
      }
#else
      static
      symbol_type
      make_STATISTIC_DEFAULT_SAMPLE_COUNT (const location_type& l)
      {
        return symbol_type (token::TOKEN_STATISTIC_DEFAULT_SAMPLE_COUNT, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_STATISTIC_DEFAULT_SAMPLE_AGE (location_type l)
      {
        return symbol_type (token::TOKEN_STATISTIC_DEFAULT_SAMPLE_AGE, std::move (l));
      }
#else
      static
      symbol_type
      make_STATISTIC_DEFAULT_SAMPLE_AGE (const location_type& l)
      {
        return symbol_type (token::TOKEN_STATISTIC_DEFAULT_SAMPLE_AGE, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_DDNS_SEND_UPDATES (location_type l)
      {
        return symbol_type (token::TOKEN_DDNS_SEND_UPDATES, std::move (l));
      }
#else
      static
      symbol_type
      make_DDNS_SEND_UPDATES (const location_type& l)
      {
        return symbol_type (token::TOKEN_DDNS_SEND_UPDATES, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_DDNS_OVERRIDE_NO_UPDATE (location_type l)
      {
        return symbol_type (token::TOKEN_DDNS_OVERRIDE_NO_UPDATE, std::move (l));
      }
#else
      static
      symbol_type
      make_DDNS_OVERRIDE_NO_UPDATE (const location_type& l)
      {
        return symbol_type (token::TOKEN_DDNS_OVERRIDE_NO_UPDATE, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_DDNS_OVERRIDE_CLIENT_UPDATE (location_type l)
      {
        return symbol_type (token::TOKEN_DDNS_OVERRIDE_CLIENT_UPDATE, std::move (l));
      }
#else
      static
      symbol_type
      make_DDNS_OVERRIDE_CLIENT_UPDATE (const location_type& l)
      {
        return symbol_type (token::TOKEN_DDNS_OVERRIDE_CLIENT_UPDATE, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_DDNS_REPLACE_CLIENT_NAME (location_type l)
      {
        return symbol_type (token::TOKEN_DDNS_REPLACE_CLIENT_NAME, std::move (l));
      }
#else
      static
      symbol_type
      make_DDNS_REPLACE_CLIENT_NAME (const location_type& l)
      {
        return symbol_type (token::TOKEN_DDNS_REPLACE_CLIENT_NAME, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_DDNS_GENERATED_PREFIX (location_type l)
      {
        return symbol_type (token::TOKEN_DDNS_GENERATED_PREFIX, std::move (l));
      }
#else
      static
      symbol_type
      make_DDNS_GENERATED_PREFIX (const location_type& l)
      {
        return symbol_type (token::TOKEN_DDNS_GENERATED_PREFIX, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_DDNS_QUALIFYING_SUFFIX (location_type l)
      {
        return symbol_type (token::TOKEN_DDNS_QUALIFYING_SUFFIX, std::move (l));
      }
#else
      static
      symbol_type
      make_DDNS_QUALIFYING_SUFFIX (const location_type& l)
      {
        return symbol_type (token::TOKEN_DDNS_QUALIFYING_SUFFIX, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_DDNS_UPDATE_ON_RENEW (location_type l)
      {
        return symbol_type (token::TOKEN_DDNS_UPDATE_ON_RENEW, std::move (l));
      }
#else
      static
      symbol_type
      make_DDNS_UPDATE_ON_RENEW (const location_type& l)
      {
        return symbol_type (token::TOKEN_DDNS_UPDATE_ON_RENEW, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_STORE_EXTENDED_INFO (location_type l)
      {
        return symbol_type (token::TOKEN_STORE_EXTENDED_INFO, std::move (l));
      }
#else
      static
      symbol_type
      make_STORE_EXTENDED_INFO (const location_type& l)
      {
        return symbol_type (token::TOKEN_STORE_EXTENDED_INFO, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_SUBNET6 (location_type l)
      {
        return symbol_type (token::TOKEN_SUBNET6, std::move (l));
      }
#else
      static
      symbol_type
      make_SUBNET6 (const location_type& l)
      {
        return symbol_type (token::TOKEN_SUBNET6, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_OPTION_DEF (location_type l)
      {
        return symbol_type (token::TOKEN_OPTION_DEF, std::move (l));
      }
#else
      static
      symbol_type
      make_OPTION_DEF (const location_type& l)
      {
        return symbol_type (token::TOKEN_OPTION_DEF, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_OPTION_DATA (location_type l)
      {
        return symbol_type (token::TOKEN_OPTION_DATA, std::move (l));
      }
#else
      static
      symbol_type
      make_OPTION_DATA (const location_type& l)
      {
        return symbol_type (token::TOKEN_OPTION_DATA, l);
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
      make_CODE (location_type l)
      {
        return symbol_type (token::TOKEN_CODE, std::move (l));
      }
#else
      static
      symbol_type
      make_CODE (const location_type& l)
      {
        return symbol_type (token::TOKEN_CODE, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_SPACE (location_type l)
      {
        return symbol_type (token::TOKEN_SPACE, std::move (l));
      }
#else
      static
      symbol_type
      make_SPACE (const location_type& l)
      {
        return symbol_type (token::TOKEN_SPACE, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_CSV_FORMAT (location_type l)
      {
        return symbol_type (token::TOKEN_CSV_FORMAT, std::move (l));
      }
#else
      static
      symbol_type
      make_CSV_FORMAT (const location_type& l)
      {
        return symbol_type (token::TOKEN_CSV_FORMAT, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ALWAYS_SEND (location_type l)
      {
        return symbol_type (token::TOKEN_ALWAYS_SEND, std::move (l));
      }
#else
      static
      symbol_type
      make_ALWAYS_SEND (const location_type& l)
      {
        return symbol_type (token::TOKEN_ALWAYS_SEND, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_RECORD_TYPES (location_type l)
      {
        return symbol_type (token::TOKEN_RECORD_TYPES, std::move (l));
      }
#else
      static
      symbol_type
      make_RECORD_TYPES (const location_type& l)
      {
        return symbol_type (token::TOKEN_RECORD_TYPES, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ENCAPSULATE (location_type l)
      {
        return symbol_type (token::TOKEN_ENCAPSULATE, std::move (l));
      }
#else
      static
      symbol_type
      make_ENCAPSULATE (const location_type& l)
      {
        return symbol_type (token::TOKEN_ENCAPSULATE, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ARRAY (location_type l)
      {
        return symbol_type (token::TOKEN_ARRAY, std::move (l));
      }
#else
      static
      symbol_type
      make_ARRAY (const location_type& l)
      {
        return symbol_type (token::TOKEN_ARRAY, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_SHARED_NETWORKS (location_type l)
      {
        return symbol_type (token::TOKEN_SHARED_NETWORKS, std::move (l));
      }
#else
      static
      symbol_type
      make_SHARED_NETWORKS (const location_type& l)
      {
        return symbol_type (token::TOKEN_SHARED_NETWORKS, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_POOLS (location_type l)
      {
        return symbol_type (token::TOKEN_POOLS, std::move (l));
      }
#else
      static
      symbol_type
      make_POOLS (const location_type& l)
      {
        return symbol_type (token::TOKEN_POOLS, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_POOL (location_type l)
      {
        return symbol_type (token::TOKEN_POOL, std::move (l));
      }
#else
      static
      symbol_type
      make_POOL (const location_type& l)
      {
        return symbol_type (token::TOKEN_POOL, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_PD_POOLS (location_type l)
      {
        return symbol_type (token::TOKEN_PD_POOLS, std::move (l));
      }
#else
      static
      symbol_type
      make_PD_POOLS (const location_type& l)
      {
        return symbol_type (token::TOKEN_PD_POOLS, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_PREFIX (location_type l)
      {
        return symbol_type (token::TOKEN_PREFIX, std::move (l));
      }
#else
      static
      symbol_type
      make_PREFIX (const location_type& l)
      {
        return symbol_type (token::TOKEN_PREFIX, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_PREFIX_LEN (location_type l)
      {
        return symbol_type (token::TOKEN_PREFIX_LEN, std::move (l));
      }
#else
      static
      symbol_type
      make_PREFIX_LEN (const location_type& l)
      {
        return symbol_type (token::TOKEN_PREFIX_LEN, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_EXCLUDED_PREFIX (location_type l)
      {
        return symbol_type (token::TOKEN_EXCLUDED_PREFIX, std::move (l));
      }
#else
      static
      symbol_type
      make_EXCLUDED_PREFIX (const location_type& l)
      {
        return symbol_type (token::TOKEN_EXCLUDED_PREFIX, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_EXCLUDED_PREFIX_LEN (location_type l)
      {
        return symbol_type (token::TOKEN_EXCLUDED_PREFIX_LEN, std::move (l));
      }
#else
      static
      symbol_type
      make_EXCLUDED_PREFIX_LEN (const location_type& l)
      {
        return symbol_type (token::TOKEN_EXCLUDED_PREFIX_LEN, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_DELEGATED_LEN (location_type l)
      {
        return symbol_type (token::TOKEN_DELEGATED_LEN, std::move (l));
      }
#else
      static
      symbol_type
      make_DELEGATED_LEN (const location_type& l)
      {
        return symbol_type (token::TOKEN_DELEGATED_LEN, l);
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
      make_SUBNET (location_type l)
      {
        return symbol_type (token::TOKEN_SUBNET, std::move (l));
      }
#else
      static
      symbol_type
      make_SUBNET (const location_type& l)
      {
        return symbol_type (token::TOKEN_SUBNET, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_INTERFACE (location_type l)
      {
        return symbol_type (token::TOKEN_INTERFACE, std::move (l));
      }
#else
      static
      symbol_type
      make_INTERFACE (const location_type& l)
      {
        return symbol_type (token::TOKEN_INTERFACE, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_INTERFACE_ID (location_type l)
      {
        return symbol_type (token::TOKEN_INTERFACE_ID, std::move (l));
      }
#else
      static
      symbol_type
      make_INTERFACE_ID (const location_type& l)
      {
        return symbol_type (token::TOKEN_INTERFACE_ID, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ID (location_type l)
      {
        return symbol_type (token::TOKEN_ID, std::move (l));
      }
#else
      static
      symbol_type
      make_ID (const location_type& l)
      {
        return symbol_type (token::TOKEN_ID, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_RAPID_COMMIT (location_type l)
      {
        return symbol_type (token::TOKEN_RAPID_COMMIT, std::move (l));
      }
#else
      static
      symbol_type
      make_RAPID_COMMIT (const location_type& l)
      {
        return symbol_type (token::TOKEN_RAPID_COMMIT, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_RESERVATION_MODE (location_type l)
      {
        return symbol_type (token::TOKEN_RESERVATION_MODE, std::move (l));
      }
#else
      static
      symbol_type
      make_RESERVATION_MODE (const location_type& l)
      {
        return symbol_type (token::TOKEN_RESERVATION_MODE, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_RESERVATIONS_OUT_OF_POOL (location_type l)
      {
        return symbol_type (token::TOKEN_RESERVATIONS_OUT_OF_POOL, std::move (l));
      }
#else
      static
      symbol_type
      make_RESERVATIONS_OUT_OF_POOL (const location_type& l)
      {
        return symbol_type (token::TOKEN_RESERVATIONS_OUT_OF_POOL, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_RESERVATIONS_IN_SUBNET (location_type l)
      {
        return symbol_type (token::TOKEN_RESERVATIONS_IN_SUBNET, std::move (l));
      }
#else
      static
      symbol_type
      make_RESERVATIONS_IN_SUBNET (const location_type& l)
      {
        return symbol_type (token::TOKEN_RESERVATIONS_IN_SUBNET, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_RESERVATIONS_GLOBAL (location_type l)
      {
        return symbol_type (token::TOKEN_RESERVATIONS_GLOBAL, std::move (l));
      }
#else
      static
      symbol_type
      make_RESERVATIONS_GLOBAL (const location_type& l)
      {
        return symbol_type (token::TOKEN_RESERVATIONS_GLOBAL, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_DISABLED (location_type l)
      {
        return symbol_type (token::TOKEN_DISABLED, std::move (l));
      }
#else
      static
      symbol_type
      make_DISABLED (const location_type& l)
      {
        return symbol_type (token::TOKEN_DISABLED, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_OUT_OF_POOL (location_type l)
      {
        return symbol_type (token::TOKEN_OUT_OF_POOL, std::move (l));
      }
#else
      static
      symbol_type
      make_OUT_OF_POOL (const location_type& l)
      {
        return symbol_type (token::TOKEN_OUT_OF_POOL, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_GLOBAL (location_type l)
      {
        return symbol_type (token::TOKEN_GLOBAL, std::move (l));
      }
#else
      static
      symbol_type
      make_GLOBAL (const location_type& l)
      {
        return symbol_type (token::TOKEN_GLOBAL, l);
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
      make_MAC_SOURCES (location_type l)
      {
        return symbol_type (token::TOKEN_MAC_SOURCES, std::move (l));
      }
#else
      static
      symbol_type
      make_MAC_SOURCES (const location_type& l)
      {
        return symbol_type (token::TOKEN_MAC_SOURCES, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_RELAY_SUPPLIED_OPTIONS (location_type l)
      {
        return symbol_type (token::TOKEN_RELAY_SUPPLIED_OPTIONS, std::move (l));
      }
#else
      static
      symbol_type
      make_RELAY_SUPPLIED_OPTIONS (const location_type& l)
      {
        return symbol_type (token::TOKEN_RELAY_SUPPLIED_OPTIONS, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_HOST_RESERVATION_IDENTIFIERS (location_type l)
      {
        return symbol_type (token::TOKEN_HOST_RESERVATION_IDENTIFIERS, std::move (l));
      }
#else
      static
      symbol_type
      make_HOST_RESERVATION_IDENTIFIERS (const location_type& l)
      {
        return symbol_type (token::TOKEN_HOST_RESERVATION_IDENTIFIERS, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_SANITY_CHECKS (location_type l)
      {
        return symbol_type (token::TOKEN_SANITY_CHECKS, std::move (l));
      }
#else
      static
      symbol_type
      make_SANITY_CHECKS (const location_type& l)
      {
        return symbol_type (token::TOKEN_SANITY_CHECKS, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_LEASE_CHECKS (location_type l)
      {
        return symbol_type (token::TOKEN_LEASE_CHECKS, std::move (l));
      }
#else
      static
      symbol_type
      make_LEASE_CHECKS (const location_type& l)
      {
        return symbol_type (token::TOKEN_LEASE_CHECKS, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_CLIENT_CLASSES (location_type l)
      {
        return symbol_type (token::TOKEN_CLIENT_CLASSES, std::move (l));
      }
#else
      static
      symbol_type
      make_CLIENT_CLASSES (const location_type& l)
      {
        return symbol_type (token::TOKEN_CLIENT_CLASSES, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_REQUIRE_CLIENT_CLASSES (location_type l)
      {
        return symbol_type (token::TOKEN_REQUIRE_CLIENT_CLASSES, std::move (l));
      }
#else
      static
      symbol_type
      make_REQUIRE_CLIENT_CLASSES (const location_type& l)
      {
        return symbol_type (token::TOKEN_REQUIRE_CLIENT_CLASSES, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TEST (location_type l)
      {
        return symbol_type (token::TOKEN_TEST, std::move (l));
      }
#else
      static
      symbol_type
      make_TEST (const location_type& l)
      {
        return symbol_type (token::TOKEN_TEST, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ONLY_IF_REQUIRED (location_type l)
      {
        return symbol_type (token::TOKEN_ONLY_IF_REQUIRED, std::move (l));
      }
#else
      static
      symbol_type
      make_ONLY_IF_REQUIRED (const location_type& l)
      {
        return symbol_type (token::TOKEN_ONLY_IF_REQUIRED, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_CLIENT_CLASS (location_type l)
      {
        return symbol_type (token::TOKEN_CLIENT_CLASS, std::move (l));
      }
#else
      static
      symbol_type
      make_CLIENT_CLASS (const location_type& l)
      {
        return symbol_type (token::TOKEN_CLIENT_CLASS, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_RESERVATIONS (location_type l)
      {
        return symbol_type (token::TOKEN_RESERVATIONS, std::move (l));
      }
#else
      static
      symbol_type
      make_RESERVATIONS (const location_type& l)
      {
        return symbol_type (token::TOKEN_RESERVATIONS, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_IP_ADDRESSES (location_type l)
      {
        return symbol_type (token::TOKEN_IP_ADDRESSES, std::move (l));
      }
#else
      static
      symbol_type
      make_IP_ADDRESSES (const location_type& l)
      {
        return symbol_type (token::TOKEN_IP_ADDRESSES, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_PREFIXES (location_type l)
      {
        return symbol_type (token::TOKEN_PREFIXES, std::move (l));
      }
#else
      static
      symbol_type
      make_PREFIXES (const location_type& l)
      {
        return symbol_type (token::TOKEN_PREFIXES, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_DUID (location_type l)
      {
        return symbol_type (token::TOKEN_DUID, std::move (l));
      }
#else
      static
      symbol_type
      make_DUID (const location_type& l)
      {
        return symbol_type (token::TOKEN_DUID, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_HW_ADDRESS (location_type l)
      {
        return symbol_type (token::TOKEN_HW_ADDRESS, std::move (l));
      }
#else
      static
      symbol_type
      make_HW_ADDRESS (const location_type& l)
      {
        return symbol_type (token::TOKEN_HW_ADDRESS, l);
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
      make_FLEX_ID (location_type l)
      {
        return symbol_type (token::TOKEN_FLEX_ID, std::move (l));
      }
#else
      static
      symbol_type
      make_FLEX_ID (const location_type& l)
      {
        return symbol_type (token::TOKEN_FLEX_ID, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_RELAY (location_type l)
      {
        return symbol_type (token::TOKEN_RELAY, std::move (l));
      }
#else
      static
      symbol_type
      make_RELAY (const location_type& l)
      {
        return symbol_type (token::TOKEN_RELAY, l);
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
      make_EXPIRED_LEASES_PROCESSING (location_type l)
      {
        return symbol_type (token::TOKEN_EXPIRED_LEASES_PROCESSING, std::move (l));
      }
#else
      static
      symbol_type
      make_EXPIRED_LEASES_PROCESSING (const location_type& l)
      {
        return symbol_type (token::TOKEN_EXPIRED_LEASES_PROCESSING, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_RECLAIM_TIMER_WAIT_TIME (location_type l)
      {
        return symbol_type (token::TOKEN_RECLAIM_TIMER_WAIT_TIME, std::move (l));
      }
#else
      static
      symbol_type
      make_RECLAIM_TIMER_WAIT_TIME (const location_type& l)
      {
        return symbol_type (token::TOKEN_RECLAIM_TIMER_WAIT_TIME, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_FLUSH_RECLAIMED_TIMER_WAIT_TIME (location_type l)
      {
        return symbol_type (token::TOKEN_FLUSH_RECLAIMED_TIMER_WAIT_TIME, std::move (l));
      }
#else
      static
      symbol_type
      make_FLUSH_RECLAIMED_TIMER_WAIT_TIME (const location_type& l)
      {
        return symbol_type (token::TOKEN_FLUSH_RECLAIMED_TIMER_WAIT_TIME, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_HOLD_RECLAIMED_TIME (location_type l)
      {
        return symbol_type (token::TOKEN_HOLD_RECLAIMED_TIME, std::move (l));
      }
#else
      static
      symbol_type
      make_HOLD_RECLAIMED_TIME (const location_type& l)
      {
        return symbol_type (token::TOKEN_HOLD_RECLAIMED_TIME, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_MAX_RECLAIM_LEASES (location_type l)
      {
        return symbol_type (token::TOKEN_MAX_RECLAIM_LEASES, std::move (l));
      }
#else
      static
      symbol_type
      make_MAX_RECLAIM_LEASES (const location_type& l)
      {
        return symbol_type (token::TOKEN_MAX_RECLAIM_LEASES, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_MAX_RECLAIM_TIME (location_type l)
      {
        return symbol_type (token::TOKEN_MAX_RECLAIM_TIME, std::move (l));
      }
#else
      static
      symbol_type
      make_MAX_RECLAIM_TIME (const location_type& l)
      {
        return symbol_type (token::TOKEN_MAX_RECLAIM_TIME, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_UNWARNED_RECLAIM_CYCLES (location_type l)
      {
        return symbol_type (token::TOKEN_UNWARNED_RECLAIM_CYCLES, std::move (l));
      }
#else
      static
      symbol_type
      make_UNWARNED_RECLAIM_CYCLES (const location_type& l)
      {
        return symbol_type (token::TOKEN_UNWARNED_RECLAIM_CYCLES, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_SERVER_ID (location_type l)
      {
        return symbol_type (token::TOKEN_SERVER_ID, std::move (l));
      }
#else
      static
      symbol_type
      make_SERVER_ID (const location_type& l)
      {
        return symbol_type (token::TOKEN_SERVER_ID, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_LLT (location_type l)
      {
        return symbol_type (token::TOKEN_LLT, std::move (l));
      }
#else
      static
      symbol_type
      make_LLT (const location_type& l)
      {
        return symbol_type (token::TOKEN_LLT, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_EN (location_type l)
      {
        return symbol_type (token::TOKEN_EN, std::move (l));
      }
#else
      static
      symbol_type
      make_EN (const location_type& l)
      {
        return symbol_type (token::TOKEN_EN, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_LL (location_type l)
      {
        return symbol_type (token::TOKEN_LL, std::move (l));
      }
#else
      static
      symbol_type
      make_LL (const location_type& l)
      {
        return symbol_type (token::TOKEN_LL, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_IDENTIFIER (location_type l)
      {
        return symbol_type (token::TOKEN_IDENTIFIER, std::move (l));
      }
#else
      static
      symbol_type
      make_IDENTIFIER (const location_type& l)
      {
        return symbol_type (token::TOKEN_IDENTIFIER, l);
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
      make_TIME (location_type l)
      {
        return symbol_type (token::TOKEN_TIME, std::move (l));
      }
#else
      static
      symbol_type
      make_TIME (const location_type& l)
      {
        return symbol_type (token::TOKEN_TIME, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ENTERPRISE_ID (location_type l)
      {
        return symbol_type (token::TOKEN_ENTERPRISE_ID, std::move (l));
      }
#else
      static
      symbol_type
      make_ENTERPRISE_ID (const location_type& l)
      {
        return symbol_type (token::TOKEN_ENTERPRISE_ID, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_DHCP4O6_PORT (location_type l)
      {
        return symbol_type (token::TOKEN_DHCP4O6_PORT, std::move (l));
      }
#else
      static
      symbol_type
      make_DHCP4O6_PORT (const location_type& l)
      {
        return symbol_type (token::TOKEN_DHCP4O6_PORT, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_DHCP_MULTI_THREADING (location_type l)
      {
        return symbol_type (token::TOKEN_DHCP_MULTI_THREADING, std::move (l));
      }
#else
      static
      symbol_type
      make_DHCP_MULTI_THREADING (const location_type& l)
      {
        return symbol_type (token::TOKEN_DHCP_MULTI_THREADING, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ENABLE_MULTI_THREADING (location_type l)
      {
        return symbol_type (token::TOKEN_ENABLE_MULTI_THREADING, std::move (l));
      }
#else
      static
      symbol_type
      make_ENABLE_MULTI_THREADING (const location_type& l)
      {
        return symbol_type (token::TOKEN_ENABLE_MULTI_THREADING, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_THREAD_POOL_SIZE (location_type l)
      {
        return symbol_type (token::TOKEN_THREAD_POOL_SIZE, std::move (l));
      }
#else
      static
      symbol_type
      make_THREAD_POOL_SIZE (const location_type& l)
      {
        return symbol_type (token::TOKEN_THREAD_POOL_SIZE, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_PACKET_QUEUE_SIZE (location_type l)
      {
        return symbol_type (token::TOKEN_PACKET_QUEUE_SIZE, std::move (l));
      }
#else
      static
      symbol_type
      make_PACKET_QUEUE_SIZE (const location_type& l)
      {
        return symbol_type (token::TOKEN_PACKET_QUEUE_SIZE, l);
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
      make_DHCP_QUEUE_CONTROL (location_type l)
      {
        return symbol_type (token::TOKEN_DHCP_QUEUE_CONTROL, std::move (l));
      }
#else
      static
      symbol_type
      make_DHCP_QUEUE_CONTROL (const location_type& l)
      {
        return symbol_type (token::TOKEN_DHCP_QUEUE_CONTROL, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ENABLE_QUEUE (location_type l)
      {
        return symbol_type (token::TOKEN_ENABLE_QUEUE, std::move (l));
      }
#else
      static
      symbol_type
      make_ENABLE_QUEUE (const location_type& l)
      {
        return symbol_type (token::TOKEN_ENABLE_QUEUE, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_QUEUE_TYPE (location_type l)
      {
        return symbol_type (token::TOKEN_QUEUE_TYPE, std::move (l));
      }
#else
      static
      symbol_type
      make_QUEUE_TYPE (const location_type& l)
      {
        return symbol_type (token::TOKEN_QUEUE_TYPE, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_CAPACITY (location_type l)
      {
        return symbol_type (token::TOKEN_CAPACITY, std::move (l));
      }
#else
      static
      symbol_type
      make_CAPACITY (const location_type& l)
      {
        return symbol_type (token::TOKEN_CAPACITY, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_DHCP_DDNS (location_type l)
      {
        return symbol_type (token::TOKEN_DHCP_DDNS, std::move (l));
      }
#else
      static
      symbol_type
      make_DHCP_DDNS (const location_type& l)
      {
        return symbol_type (token::TOKEN_DHCP_DDNS, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ENABLE_UPDATES (location_type l)
      {
        return symbol_type (token::TOKEN_ENABLE_UPDATES, std::move (l));
      }
#else
      static
      symbol_type
      make_ENABLE_UPDATES (const location_type& l)
      {
        return symbol_type (token::TOKEN_ENABLE_UPDATES, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_QUALIFYING_SUFFIX (location_type l)
      {
        return symbol_type (token::TOKEN_QUALIFYING_SUFFIX, std::move (l));
      }
#else
      static
      symbol_type
      make_QUALIFYING_SUFFIX (const location_type& l)
      {
        return symbol_type (token::TOKEN_QUALIFYING_SUFFIX, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_SERVER_IP (location_type l)
      {
        return symbol_type (token::TOKEN_SERVER_IP, std::move (l));
      }
#else
      static
      symbol_type
      make_SERVER_IP (const location_type& l)
      {
        return symbol_type (token::TOKEN_SERVER_IP, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_SERVER_PORT (location_type l)
      {
        return symbol_type (token::TOKEN_SERVER_PORT, std::move (l));
      }
#else
      static
      symbol_type
      make_SERVER_PORT (const location_type& l)
      {
        return symbol_type (token::TOKEN_SERVER_PORT, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_SENDER_IP (location_type l)
      {
        return symbol_type (token::TOKEN_SENDER_IP, std::move (l));
      }
#else
      static
      symbol_type
      make_SENDER_IP (const location_type& l)
      {
        return symbol_type (token::TOKEN_SENDER_IP, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_SENDER_PORT (location_type l)
      {
        return symbol_type (token::TOKEN_SENDER_PORT, std::move (l));
      }
#else
      static
      symbol_type
      make_SENDER_PORT (const location_type& l)
      {
        return symbol_type (token::TOKEN_SENDER_PORT, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_MAX_QUEUE_SIZE (location_type l)
      {
        return symbol_type (token::TOKEN_MAX_QUEUE_SIZE, std::move (l));
      }
#else
      static
      symbol_type
      make_MAX_QUEUE_SIZE (const location_type& l)
      {
        return symbol_type (token::TOKEN_MAX_QUEUE_SIZE, l);
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
      make_OVERRIDE_NO_UPDATE (location_type l)
      {
        return symbol_type (token::TOKEN_OVERRIDE_NO_UPDATE, std::move (l));
      }
#else
      static
      symbol_type
      make_OVERRIDE_NO_UPDATE (const location_type& l)
      {
        return symbol_type (token::TOKEN_OVERRIDE_NO_UPDATE, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_OVERRIDE_CLIENT_UPDATE (location_type l)
      {
        return symbol_type (token::TOKEN_OVERRIDE_CLIENT_UPDATE, std::move (l));
      }
#else
      static
      symbol_type
      make_OVERRIDE_CLIENT_UPDATE (const location_type& l)
      {
        return symbol_type (token::TOKEN_OVERRIDE_CLIENT_UPDATE, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_REPLACE_CLIENT_NAME (location_type l)
      {
        return symbol_type (token::TOKEN_REPLACE_CLIENT_NAME, std::move (l));
      }
#else
      static
      symbol_type
      make_REPLACE_CLIENT_NAME (const location_type& l)
      {
        return symbol_type (token::TOKEN_REPLACE_CLIENT_NAME, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_GENERATED_PREFIX (location_type l)
      {
        return symbol_type (token::TOKEN_GENERATED_PREFIX, std::move (l));
      }
#else
      static
      symbol_type
      make_GENERATED_PREFIX (const location_type& l)
      {
        return symbol_type (token::TOKEN_GENERATED_PREFIX, l);
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
      make_WHEN_PRESENT (location_type l)
      {
        return symbol_type (token::TOKEN_WHEN_PRESENT, std::move (l));
      }
#else
      static
      symbol_type
      make_WHEN_PRESENT (const location_type& l)
      {
        return symbol_type (token::TOKEN_WHEN_PRESENT, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_NEVER (location_type l)
      {
        return symbol_type (token::TOKEN_NEVER, std::move (l));
      }
#else
      static
      symbol_type
      make_NEVER (const location_type& l)
      {
        return symbol_type (token::TOKEN_NEVER, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ALWAYS (location_type l)
      {
        return symbol_type (token::TOKEN_ALWAYS, std::move (l));
      }
#else
      static
      symbol_type
      make_ALWAYS (const location_type& l)
      {
        return symbol_type (token::TOKEN_ALWAYS, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_WHEN_NOT_PRESENT (location_type l)
      {
        return symbol_type (token::TOKEN_WHEN_NOT_PRESENT, std::move (l));
      }
#else
      static
      symbol_type
      make_WHEN_NOT_PRESENT (const location_type& l)
      {
        return symbol_type (token::TOKEN_WHEN_NOT_PRESENT, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_HOSTNAME_CHAR_SET (location_type l)
      {
        return symbol_type (token::TOKEN_HOSTNAME_CHAR_SET, std::move (l));
      }
#else
      static
      symbol_type
      make_HOSTNAME_CHAR_SET (const location_type& l)
      {
        return symbol_type (token::TOKEN_HOSTNAME_CHAR_SET, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_HOSTNAME_CHAR_REPLACEMENT (location_type l)
      {
        return symbol_type (token::TOKEN_HOSTNAME_CHAR_REPLACEMENT, std::move (l));
      }
#else
      static
      symbol_type
      make_HOSTNAME_CHAR_REPLACEMENT (const location_type& l)
      {
        return symbol_type (token::TOKEN_HOSTNAME_CHAR_REPLACEMENT, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_IP_RESERVATIONS_UNIQUE (location_type l)
      {
        return symbol_type (token::TOKEN_IP_RESERVATIONS_UNIQUE, std::move (l));
      }
#else
      static
      symbol_type
      make_IP_RESERVATIONS_UNIQUE (const location_type& l)
      {
        return symbol_type (token::TOKEN_IP_RESERVATIONS_UNIQUE, l);
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
      make_TOPLEVEL_DHCP6 (location_type l)
      {
        return symbol_type (token::TOKEN_TOPLEVEL_DHCP6, std::move (l));
      }
#else
      static
      symbol_type
      make_TOPLEVEL_DHCP6 (const location_type& l)
      {
        return symbol_type (token::TOKEN_TOPLEVEL_DHCP6, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_SUB_DHCP6 (location_type l)
      {
        return symbol_type (token::TOKEN_SUB_DHCP6, std::move (l));
      }
#else
      static
      symbol_type
      make_SUB_DHCP6 (const location_type& l)
      {
        return symbol_type (token::TOKEN_SUB_DHCP6, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_SUB_INTERFACES6 (location_type l)
      {
        return symbol_type (token::TOKEN_SUB_INTERFACES6, std::move (l));
      }
#else
      static
      symbol_type
      make_SUB_INTERFACES6 (const location_type& l)
      {
        return symbol_type (token::TOKEN_SUB_INTERFACES6, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_SUB_SUBNET6 (location_type l)
      {
        return symbol_type (token::TOKEN_SUB_SUBNET6, std::move (l));
      }
#else
      static
      symbol_type
      make_SUB_SUBNET6 (const location_type& l)
      {
        return symbol_type (token::TOKEN_SUB_SUBNET6, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_SUB_POOL6 (location_type l)
      {
        return symbol_type (token::TOKEN_SUB_POOL6, std::move (l));
      }
#else
      static
      symbol_type
      make_SUB_POOL6 (const location_type& l)
      {
        return symbol_type (token::TOKEN_SUB_POOL6, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_SUB_PD_POOL (location_type l)
      {
        return symbol_type (token::TOKEN_SUB_PD_POOL, std::move (l));
      }
#else
      static
      symbol_type
      make_SUB_PD_POOL (const location_type& l)
      {
        return symbol_type (token::TOKEN_SUB_PD_POOL, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_SUB_RESERVATION (location_type l)
      {
        return symbol_type (token::TOKEN_SUB_RESERVATION, std::move (l));
      }
#else
      static
      symbol_type
      make_SUB_RESERVATION (const location_type& l)
      {
        return symbol_type (token::TOKEN_SUB_RESERVATION, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_SUB_OPTION_DEFS (location_type l)
      {
        return symbol_type (token::TOKEN_SUB_OPTION_DEFS, std::move (l));
      }
#else
      static
      symbol_type
      make_SUB_OPTION_DEFS (const location_type& l)
      {
        return symbol_type (token::TOKEN_SUB_OPTION_DEFS, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_SUB_OPTION_DEF (location_type l)
      {
        return symbol_type (token::TOKEN_SUB_OPTION_DEF, std::move (l));
      }
#else
      static
      symbol_type
      make_SUB_OPTION_DEF (const location_type& l)
      {
        return symbol_type (token::TOKEN_SUB_OPTION_DEF, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_SUB_OPTION_DATA (location_type l)
      {
        return symbol_type (token::TOKEN_SUB_OPTION_DATA, std::move (l));
      }
#else
      static
      symbol_type
      make_SUB_OPTION_DATA (const location_type& l)
      {
        return symbol_type (token::TOKEN_SUB_OPTION_DATA, l);
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
      make_SUB_DHCP_DDNS (location_type l)
      {
        return symbol_type (token::TOKEN_SUB_DHCP_DDNS, std::move (l));
      }
#else
      static
      symbol_type
      make_SUB_DHCP_DDNS (const location_type& l)
      {
        return symbol_type (token::TOKEN_SUB_DHCP_DDNS, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_SUB_CONFIG_CONTROL (location_type l)
      {
        return symbol_type (token::TOKEN_SUB_CONFIG_CONTROL, std::move (l));
      }
#else
      static
      symbol_type
      make_SUB_CONFIG_CONTROL (const location_type& l)
      {
        return symbol_type (token::TOKEN_SUB_CONFIG_CONTROL, l);
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
      context (const Dhcp6Parser& yyparser, const symbol_type& yyla);
      const symbol_type& lookahead () const { return yyla_; }
      symbol_kind_type token () const { return yyla_.kind (); }
      const location_type& location () const { return yyla_.location; }

      /// Put in YYARG at most YYARGN of the expected tokens, and return the
      /// number of tokens stored in YYARG.  If YYARG is null, return the
      /// number of expected tokens (guaranteed to be less than YYNTOKENS).
      int expected_tokens (symbol_kind_type yyarg[], int yyargn) const;

    private:
      const Dhcp6Parser& yyparser_;
      const symbol_type& yyla_;
    };

  private:
#if YY_CPLUSPLUS < 201103L
    /// Non copyable.
    Dhcp6Parser (const Dhcp6Parser&);
    /// Non copyable.
    Dhcp6Parser& operator= (const Dhcp6Parser&);
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
    static bool yy_pact_value_is_default_ (int yyvalue);

    /// Whether the given \c yytable_ value indicates a syntax error.
    /// \param yyvalue   the value to check
    static bool yy_table_value_is_error_ (int yyvalue);

    static const short yypact_ninf_;
    static const signed char yytable_ninf_;

    /// Convert a scanner token kind \a t to a symbol kind.
    /// In theory \a t should be a token_kind_type, but character literals
    /// are valid, yet not members of the token_type enum.
    static symbol_kind_type yytranslate_ (int t);

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

    // YYSTOS[STATE-NUM] -- The (internal number of the) accessing
    // symbol of state STATE-NUM.
    static const short yystos_[];

    // YYR1[YYN] -- Symbol number of symbol that rule YYN derives.
    static const short yyr1_[];

    // YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.
    static const signed char yyr2_[];


#if PARSER6_DEBUG
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

      stack (size_type n = 200)
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
        slice (const stack& stack, index_type range)
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
    void yypop_ (int n = 1);

    /// Constants.
    enum
    {
      yylast_ = 1255,     ///< Last index in yytable_.
      yynnts_ = 429,  ///< Number of nonterminal symbols.
      yyfinal_ = 30 ///< Termination state number.
    };


    // User arguments.
    isc::dhcp::Parser6Context& ctx;

  };

  inline
  Dhcp6Parser::symbol_kind_type
  Dhcp6Parser::yytranslate_ (int t)
  {
    // YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to
    // TOKEN-NUM as returned by yylex.
    static
    const unsigned char
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
     155,   156,   157,   158,   159,   160,   161,   162,   163,   164,
     165,   166,   167,   168,   169,   170,   171,   172,   173,   174,
     175,   176,   177,   178,   179,   180,   181,   182,   183,   184,
     185,   186,   187,   188,   189,   190,   191,   192,   193,   194,
     195,   196,   197,   198,   199,   200,   201,   202,   203,   204
    };
    // Last valid token kind.
    const int code_max = 459;

    if (t <= 0)
      return symbol_kind::S_YYEOF;
    else if (t <= code_max)
      return YY_CAST (symbol_kind_type, translate_table[t]);
    else
      return symbol_kind::S_YYUNDEF;
  }

  // basic_symbol.
  template <typename Base>
  Dhcp6Parser::basic_symbol<Base>::basic_symbol (const basic_symbol& that)
    : Base (that)
    , value ()
    , location (that.location)
  {
    switch (this->kind ())
    {
      case symbol_kind::S_value: // value
      case symbol_kind::S_map_value: // map_value
      case symbol_kind::S_ddns_replace_client_name_value: // ddns_replace_client_name_value
      case symbol_kind::S_db_type: // db_type
      case symbol_kind::S_hr_mode: // hr_mode
      case symbol_kind::S_duid_type: // duid_type
      case symbol_kind::S_ncr_protocol_value: // ncr_protocol_value
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
  Dhcp6Parser::symbol_kind_type
  Dhcp6Parser::basic_symbol<Base>::type_get () const YY_NOEXCEPT
  {
    return this->kind ();
  }

  template <typename Base>
  bool
  Dhcp6Parser::basic_symbol<Base>::empty () const YY_NOEXCEPT
  {
    return this->kind () == symbol_kind::S_YYEMPTY;
  }

  template <typename Base>
  void
  Dhcp6Parser::basic_symbol<Base>::move (basic_symbol& s)
  {
    super_type::move (s);
    switch (this->kind ())
    {
      case symbol_kind::S_value: // value
      case symbol_kind::S_map_value: // map_value
      case symbol_kind::S_ddns_replace_client_name_value: // ddns_replace_client_name_value
      case symbol_kind::S_db_type: // db_type
      case symbol_kind::S_hr_mode: // hr_mode
      case symbol_kind::S_duid_type: // duid_type
      case symbol_kind::S_ncr_protocol_value: // ncr_protocol_value
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
  Dhcp6Parser::by_kind::by_kind ()
    : kind_ (symbol_kind::S_YYEMPTY)
  {}

#if 201103L <= YY_CPLUSPLUS
  inline
  Dhcp6Parser::by_kind::by_kind (by_kind&& that)
    : kind_ (that.kind_)
  {
    that.clear ();
  }
#endif

  inline
  Dhcp6Parser::by_kind::by_kind (const by_kind& that)
    : kind_ (that.kind_)
  {}

  inline
  Dhcp6Parser::by_kind::by_kind (token_kind_type t)
    : kind_ (yytranslate_ (t))
  {}

  inline
  void
  Dhcp6Parser::by_kind::clear ()
  {
    kind_ = symbol_kind::S_YYEMPTY;
  }

  inline
  void
  Dhcp6Parser::by_kind::move (by_kind& that)
  {
    kind_ = that.kind_;
    that.clear ();
  }

  inline
  Dhcp6Parser::symbol_kind_type
  Dhcp6Parser::by_kind::kind () const YY_NOEXCEPT
  {
    return kind_;
  }

  inline
  Dhcp6Parser::symbol_kind_type
  Dhcp6Parser::by_kind::type_get () const YY_NOEXCEPT
  {
    return this->kind ();
  }

#line 14 "dhcp6_parser.yy"
} } // isc::dhcp
#line 5377 "dhcp6_parser.h"




#endif // !YY_PARSER6_DHCP6_PARSER_H_INCLUDED
