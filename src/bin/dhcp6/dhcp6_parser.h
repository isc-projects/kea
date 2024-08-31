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
#ifndef PARSER6__ASSERT
# include <cassert>
# define PARSER6__ASSERT assert
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
#line 210 "dhcp6_parser.h"




  /// A Bison parser.
  class Dhcp6Parser
  {
  public:
#ifdef PARSER6_STYPE
# ifdef __GNUC__
#  pragma GCC message "bison: do not #define PARSER6_STYPE in C++, use %define api.value.type"
# endif
    typedef PARSER6_STYPE value_type;
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
      PARSER6__ASSERT (sizeof (T) <= size);
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
      PARSER6__ASSERT (!yytypeid_);
    }

# if 201103L <= YY_CPLUSPLUS
    /// Instantiate a \a T in here from \a t.
    template <typename T, typename... U>
    T&
    emplace (U&&... u)
    {
      PARSER6__ASSERT (!yytypeid_);
      PARSER6__ASSERT (sizeof (T) <= size);
      yytypeid_ = & typeid (T);
      return *new (yyas_<T> ()) T (std::forward <U>(u)...);
    }
# else
    /// Instantiate an empty \a T in here.
    template <typename T>
    T&
    emplace ()
    {
      PARSER6__ASSERT (!yytypeid_);
      PARSER6__ASSERT (sizeof (T) <= size);
      yytypeid_ = & typeid (T);
      return *new (yyas_<T> ()) T ();
    }

    /// Instantiate a \a T in here from \a t.
    template <typename T>
    T&
    emplace (const T& t)
    {
      PARSER6__ASSERT (!yytypeid_);
      PARSER6__ASSERT (sizeof (T) <= size);
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
      PARSER6__ASSERT (yytypeid_);
      PARSER6__ASSERT (*yytypeid_ == typeid (T));
      PARSER6__ASSERT (sizeof (T) <= size);
      return *yyas_<T> ();
    }

    /// Const accessor to a built \a T (for %printer).
    template <typename T>
    const T&
    as () const YY_NOEXCEPT
    {
      PARSER6__ASSERT (yytypeid_);
      PARSER6__ASSERT (*yytypeid_ == typeid (T));
      PARSER6__ASSERT (sizeof (T) <= size);
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
      PARSER6__ASSERT (yytypeid_);
      PARSER6__ASSERT (*yytypeid_ == *that.yytypeid_);
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
      // ddns_replace_client_name_value
      // ddns_conflict_resolution_mode_value
      // db_type
      // on_fail_mode
      // duid_type
      // control_socket_type_value
      // auth_type_value
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
    TOKEN_SERVICE_SOCKETS_REQUIRE_ALL = 273, // "service-sockets-require-all"
    TOKEN_SERVICE_SOCKETS_RETRY_WAIT_TIME = 274, // "service-sockets-retry-wait-time"
    TOKEN_SERVICE_SOCKETS_MAX_RETRIES = 275, // "service-sockets-max-retries"
    TOKEN_LEASE_DATABASE = 276,    // "lease-database"
    TOKEN_HOSTS_DATABASE = 277,    // "hosts-database"
    TOKEN_HOSTS_DATABASES = 278,   // "hosts-databases"
    TOKEN_TYPE = 279,              // "type"
    TOKEN_MEMFILE = 280,           // "memfile"
    TOKEN_MYSQL = 281,             // "mysql"
    TOKEN_POSTGRESQL = 282,        // "postgresql"
    TOKEN_USER = 283,              // "user"
    TOKEN_PASSWORD = 284,          // "password"
    TOKEN_HOST = 285,              // "host"
    TOKEN_PORT = 286,              // "port"
    TOKEN_PERSIST = 287,           // "persist"
    TOKEN_LFC_INTERVAL = 288,      // "lfc-interval"
    TOKEN_READONLY = 289,          // "readonly"
    TOKEN_CONNECT_TIMEOUT = 290,   // "connect-timeout"
    TOKEN_READ_TIMEOUT = 291,      // "read-timeout"
    TOKEN_WRITE_TIMEOUT = 292,     // "write-timeout"
    TOKEN_TCP_USER_TIMEOUT = 293,  // "tcp-user-timeout"
    TOKEN_MAX_RECONNECT_TRIES = 294, // "max-reconnect-tries"
    TOKEN_RECONNECT_WAIT_TIME = 295, // "reconnect-wait-time"
    TOKEN_ON_FAIL = 296,           // "on-fail"
    TOKEN_STOP_RETRY_EXIT = 297,   // "stop-retry-exit"
    TOKEN_SERVE_RETRY_EXIT = 298,  // "serve-retry-exit"
    TOKEN_SERVE_RETRY_CONTINUE = 299, // "serve-retry-continue"
    TOKEN_RETRY_ON_STARTUP = 300,  // "retry-on-startup"
    TOKEN_MAX_ROW_ERRORS = 301,    // "max-row-errors"
    TOKEN_TRUST_ANCHOR = 302,      // "trust-anchor"
    TOKEN_CERT_FILE = 303,         // "cert-file"
    TOKEN_KEY_FILE = 304,          // "key-file"
    TOKEN_CIPHER_LIST = 305,       // "cipher-list"
    TOKEN_PREFERRED_LIFETIME = 306, // "preferred-lifetime"
    TOKEN_MIN_PREFERRED_LIFETIME = 307, // "min-preferred-lifetime"
    TOKEN_MAX_PREFERRED_LIFETIME = 308, // "max-preferred-lifetime"
    TOKEN_VALID_LIFETIME = 309,    // "valid-lifetime"
    TOKEN_MIN_VALID_LIFETIME = 310, // "min-valid-lifetime"
    TOKEN_MAX_VALID_LIFETIME = 311, // "max-valid-lifetime"
    TOKEN_RENEW_TIMER = 312,       // "renew-timer"
    TOKEN_REBIND_TIMER = 313,      // "rebind-timer"
    TOKEN_CALCULATE_TEE_TIMES = 314, // "calculate-tee-times"
    TOKEN_T1_PERCENT = 315,        // "t1-percent"
    TOKEN_T2_PERCENT = 316,        // "t2-percent"
    TOKEN_CACHE_THRESHOLD = 317,   // "cache-threshold"
    TOKEN_CACHE_MAX_AGE = 318,     // "cache-max-age"
    TOKEN_DECLINE_PROBATION_PERIOD = 319, // "decline-probation-period"
    TOKEN_SERVER_TAG = 320,        // "server-tag"
    TOKEN_STATISTIC_DEFAULT_SAMPLE_COUNT = 321, // "statistic-default-sample-count"
    TOKEN_STATISTIC_DEFAULT_SAMPLE_AGE = 322, // "statistic-default-sample-age"
    TOKEN_DDNS_SEND_UPDATES = 323, // "ddns-send-updates"
    TOKEN_DDNS_OVERRIDE_NO_UPDATE = 324, // "ddns-override-no-update"
    TOKEN_DDNS_OVERRIDE_CLIENT_UPDATE = 325, // "ddns-override-client-update"
    TOKEN_DDNS_REPLACE_CLIENT_NAME = 326, // "ddns-replace-client-name"
    TOKEN_DDNS_GENERATED_PREFIX = 327, // "ddns-generated-prefix"
    TOKEN_DDNS_QUALIFYING_SUFFIX = 328, // "ddns-qualifying-suffix"
    TOKEN_DDNS_UPDATE_ON_RENEW = 329, // "ddns-update-on-renew"
    TOKEN_DDNS_USE_CONFLICT_RESOLUTION = 330, // "ddns-use-conflict-resolution"
    TOKEN_DDNS_TTL_PERCENT = 331,  // "ddns-ttl-percent"
    TOKEN_STORE_EXTENDED_INFO = 332, // "store-extended-info"
    TOKEN_SUBNET6 = 333,           // "subnet6"
    TOKEN_OPTION_DEF = 334,        // "option-def"
    TOKEN_OPTION_DATA = 335,       // "option-data"
    TOKEN_NAME = 336,              // "name"
    TOKEN_DATA = 337,              // "data"
    TOKEN_CODE = 338,              // "code"
    TOKEN_SPACE = 339,             // "space"
    TOKEN_CSV_FORMAT = 340,        // "csv-format"
    TOKEN_ALWAYS_SEND = 341,       // "always-send"
    TOKEN_NEVER_SEND = 342,        // "never-send"
    TOKEN_RECORD_TYPES = 343,      // "record-types"
    TOKEN_ENCAPSULATE = 344,       // "encapsulate"
    TOKEN_ARRAY = 345,             // "array"
    TOKEN_PARKED_PACKET_LIMIT = 346, // "parked-packet-limit"
    TOKEN_ALLOCATOR = 347,         // "allocator"
    TOKEN_PD_ALLOCATOR = 348,      // "pd-allocator"
    TOKEN_DDNS_CONFLICT_RESOLUTION_MODE = 349, // "ddns-conflict-resolution-mode"
    TOKEN_CHECK_WITH_DHCID = 350,  // "check-with-dhcid"
    TOKEN_NO_CHECK_WITH_DHCID = 351, // "no-check-with-dhcid"
    TOKEN_CHECK_EXISTS_WITH_DHCID = 352, // "check-exists-with-dhcid"
    TOKEN_NO_CHECK_WITHOUT_DHCID = 353, // "no-check-without-dhcid"
    TOKEN_SHARED_NETWORKS = 354,   // "shared-networks"
    TOKEN_POOLS = 355,             // "pools"
    TOKEN_POOL = 356,              // "pool"
    TOKEN_PD_POOLS = 357,          // "pd-pools"
    TOKEN_PREFIX = 358,            // "prefix"
    TOKEN_PREFIX_LEN = 359,        // "prefix-len"
    TOKEN_EXCLUDED_PREFIX = 360,   // "excluded-prefix"
    TOKEN_EXCLUDED_PREFIX_LEN = 361, // "excluded-prefix-len"
    TOKEN_DELEGATED_LEN = 362,     // "delegated-len"
    TOKEN_USER_CONTEXT = 363,      // "user-context"
    TOKEN_COMMENT = 364,           // "comment"
    TOKEN_SUBNET = 365,            // "subnet"
    TOKEN_INTERFACE = 366,         // "interface"
    TOKEN_INTERFACE_ID = 367,      // "interface-id"
    TOKEN_ID = 368,                // "id"
    TOKEN_RAPID_COMMIT = 369,      // "rapid-commit"
    TOKEN_RESERVATIONS_GLOBAL = 370, // "reservations-global"
    TOKEN_RESERVATIONS_IN_SUBNET = 371, // "reservations-in-subnet"
    TOKEN_RESERVATIONS_OUT_OF_POOL = 372, // "reservations-out-of-pool"
    TOKEN_MAC_SOURCES = 373,       // "mac-sources"
    TOKEN_RELAY_SUPPLIED_OPTIONS = 374, // "relay-supplied-options"
    TOKEN_HOST_RESERVATION_IDENTIFIERS = 375, // "host-reservation-identifiers"
    TOKEN_SANITY_CHECKS = 376,     // "sanity-checks"
    TOKEN_LEASE_CHECKS = 377,      // "lease-checks"
    TOKEN_EXTENDED_INFO_CHECKS = 378, // "extended-info-checks"
    TOKEN_CLIENT_CLASSES = 379,    // "client-classes"
    TOKEN_REQUIRE_CLIENT_CLASSES = 380, // "require-client-classes"
    TOKEN_TEST = 381,              // "test"
    TOKEN_TEMPLATE_TEST = 382,     // "template-test"
    TOKEN_ONLY_IF_REQUIRED = 383,  // "only-if-required"
    TOKEN_CLIENT_CLASS = 384,      // "client-class"
    TOKEN_POOL_ID = 385,           // "pool-id"
    TOKEN_RESERVATIONS = 386,      // "reservations"
    TOKEN_IP_ADDRESSES = 387,      // "ip-addresses"
    TOKEN_PREFIXES = 388,          // "prefixes"
    TOKEN_DUID = 389,              // "duid"
    TOKEN_HW_ADDRESS = 390,        // "hw-address"
    TOKEN_HOSTNAME = 391,          // "hostname"
    TOKEN_FLEX_ID = 392,           // "flex-id"
    TOKEN_RELAY = 393,             // "relay"
    TOKEN_HOOKS_LIBRARIES = 394,   // "hooks-libraries"
    TOKEN_LIBRARY = 395,           // "library"
    TOKEN_PARAMETERS = 396,        // "parameters"
    TOKEN_EXPIRED_LEASES_PROCESSING = 397, // "expired-leases-processing"
    TOKEN_RECLAIM_TIMER_WAIT_TIME = 398, // "reclaim-timer-wait-time"
    TOKEN_FLUSH_RECLAIMED_TIMER_WAIT_TIME = 399, // "flush-reclaimed-timer-wait-time"
    TOKEN_HOLD_RECLAIMED_TIME = 400, // "hold-reclaimed-time"
    TOKEN_MAX_RECLAIM_LEASES = 401, // "max-reclaim-leases"
    TOKEN_MAX_RECLAIM_TIME = 402,  // "max-reclaim-time"
    TOKEN_UNWARNED_RECLAIM_CYCLES = 403, // "unwarned-reclaim-cycles"
    TOKEN_SERVER_ID = 404,         // "server-id"
    TOKEN_LLT = 405,               // "LLT"
    TOKEN_EN = 406,                // "EN"
    TOKEN_LL = 407,                // "LL"
    TOKEN_IDENTIFIER = 408,        // "identifier"
    TOKEN_HTYPE = 409,             // "htype"
    TOKEN_TIME = 410,              // "time"
    TOKEN_ENTERPRISE_ID = 411,     // "enterprise-id"
    TOKEN_DHCP4O6_PORT = 412,      // "dhcp4o6-port"
    TOKEN_DHCP_MULTI_THREADING = 413, // "multi-threading"
    TOKEN_ENABLE_MULTI_THREADING = 414, // "enable-multi-threading"
    TOKEN_THREAD_POOL_SIZE = 415,  // "thread-pool-size"
    TOKEN_PACKET_QUEUE_SIZE = 416, // "packet-queue-size"
    TOKEN_CONTROL_SOCKET = 417,    // "control-socket"
    TOKEN_CONTROL_SOCKETS = 418,   // "control-sockets"
    TOKEN_SOCKET_TYPE = 419,       // "socket-type"
    TOKEN_UNIX = 420,              // "unix"
    TOKEN_HTTP = 421,              // "http"
    TOKEN_HTTPS = 422,             // "https"
    TOKEN_SOCKET_NAME = 423,       // "socket-name"
    TOKEN_SOCKET_ADDRESS = 424,    // "socket-address"
    TOKEN_SOCKET_PORT = 425,       // "socket-port"
    TOKEN_AUTHENTICATION = 426,    // "authentication"
    TOKEN_BASIC = 427,             // "basic"
    TOKEN_REALM = 428,             // "realm"
    TOKEN_DIRECTORY = 429,         // "directory"
    TOKEN_CLIENTS = 430,           // "clients"
    TOKEN_USER_FILE = 431,         // "user-file"
    TOKEN_PASSWORD_FILE = 432,     // "password-file"
    TOKEN_CERT_REQUIRED = 433,     // "cert-required"
    TOKEN_DHCP_QUEUE_CONTROL = 434, // "dhcp-queue-control"
    TOKEN_ENABLE_QUEUE = 435,      // "enable-queue"
    TOKEN_QUEUE_TYPE = 436,        // "queue-type"
    TOKEN_CAPACITY = 437,          // "capacity"
    TOKEN_DHCP_DDNS = 438,         // "dhcp-ddns"
    TOKEN_ENABLE_UPDATES = 439,    // "enable-updates"
    TOKEN_SERVER_IP = 440,         // "server-ip"
    TOKEN_SERVER_PORT = 441,       // "server-port"
    TOKEN_SENDER_IP = 442,         // "sender-ip"
    TOKEN_SENDER_PORT = 443,       // "sender-port"
    TOKEN_MAX_QUEUE_SIZE = 444,    // "max-queue-size"
    TOKEN_NCR_PROTOCOL = 445,      // "ncr-protocol"
    TOKEN_NCR_FORMAT = 446,        // "ncr-format"
    TOKEN_UDP = 447,               // "UDP"
    TOKEN_TCP = 448,               // "TCP"
    TOKEN_JSON = 449,              // "JSON"
    TOKEN_WHEN_PRESENT = 450,      // "when-present"
    TOKEN_NEVER = 451,             // "never"
    TOKEN_ALWAYS = 452,            // "always"
    TOKEN_WHEN_NOT_PRESENT = 453,  // "when-not-present"
    TOKEN_HOSTNAME_CHAR_SET = 454, // "hostname-char-set"
    TOKEN_HOSTNAME_CHAR_REPLACEMENT = 455, // "hostname-char-replacement"
    TOKEN_EARLY_GLOBAL_RESERVATIONS_LOOKUP = 456, // "early-global-reservations-lookup"
    TOKEN_IP_RESERVATIONS_UNIQUE = 457, // "ip-reservations-unique"
    TOKEN_RESERVATIONS_LOOKUP_FIRST = 458, // "reservations-lookup-first"
    TOKEN_LOGGERS = 459,           // "loggers"
    TOKEN_OUTPUT_OPTIONS = 460,    // "output-options"
    TOKEN_OUTPUT = 461,            // "output"
    TOKEN_DEBUGLEVEL = 462,        // "debuglevel"
    TOKEN_SEVERITY = 463,          // "severity"
    TOKEN_FLUSH = 464,             // "flush"
    TOKEN_MAXSIZE = 465,           // "maxsize"
    TOKEN_MAXVER = 466,            // "maxver"
    TOKEN_PATTERN = 467,           // "pattern"
    TOKEN_COMPATIBILITY = 468,     // "compatibility"
    TOKEN_LENIENT_OPTION_PARSING = 469, // "lenient-option-parsing"
    TOKEN_TOPLEVEL_JSON = 470,     // TOPLEVEL_JSON
    TOKEN_TOPLEVEL_DHCP6 = 471,    // TOPLEVEL_DHCP6
    TOKEN_SUB_DHCP6 = 472,         // SUB_DHCP6
    TOKEN_SUB_INTERFACES6 = 473,   // SUB_INTERFACES6
    TOKEN_SUB_SUBNET6 = 474,       // SUB_SUBNET6
    TOKEN_SUB_POOL6 = 475,         // SUB_POOL6
    TOKEN_SUB_PD_POOL = 476,       // SUB_PD_POOL
    TOKEN_SUB_RESERVATION = 477,   // SUB_RESERVATION
    TOKEN_SUB_OPTION_DEFS = 478,   // SUB_OPTION_DEFS
    TOKEN_SUB_OPTION_DEF = 479,    // SUB_OPTION_DEF
    TOKEN_SUB_OPTION_DATA = 480,   // SUB_OPTION_DATA
    TOKEN_SUB_HOOKS_LIBRARY = 481, // SUB_HOOKS_LIBRARY
    TOKEN_SUB_DHCP_DDNS = 482,     // SUB_DHCP_DDNS
    TOKEN_SUB_CONFIG_CONTROL = 483, // SUB_CONFIG_CONTROL
    TOKEN_STRING = 484,            // "constant string"
    TOKEN_INTEGER = 485,           // "integer"
    TOKEN_FLOAT = 486,             // "floating point"
    TOKEN_BOOLEAN = 487            // "boolean"
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
        YYNTOKENS = 233, ///< Number of tokens.
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
        S_SERVICE_SOCKETS_REQUIRE_ALL = 18,      // "service-sockets-require-all"
        S_SERVICE_SOCKETS_RETRY_WAIT_TIME = 19,  // "service-sockets-retry-wait-time"
        S_SERVICE_SOCKETS_MAX_RETRIES = 20,      // "service-sockets-max-retries"
        S_LEASE_DATABASE = 21,                   // "lease-database"
        S_HOSTS_DATABASE = 22,                   // "hosts-database"
        S_HOSTS_DATABASES = 23,                  // "hosts-databases"
        S_TYPE = 24,                             // "type"
        S_MEMFILE = 25,                          // "memfile"
        S_MYSQL = 26,                            // "mysql"
        S_POSTGRESQL = 27,                       // "postgresql"
        S_USER = 28,                             // "user"
        S_PASSWORD = 29,                         // "password"
        S_HOST = 30,                             // "host"
        S_PORT = 31,                             // "port"
        S_PERSIST = 32,                          // "persist"
        S_LFC_INTERVAL = 33,                     // "lfc-interval"
        S_READONLY = 34,                         // "readonly"
        S_CONNECT_TIMEOUT = 35,                  // "connect-timeout"
        S_READ_TIMEOUT = 36,                     // "read-timeout"
        S_WRITE_TIMEOUT = 37,                    // "write-timeout"
        S_TCP_USER_TIMEOUT = 38,                 // "tcp-user-timeout"
        S_MAX_RECONNECT_TRIES = 39,              // "max-reconnect-tries"
        S_RECONNECT_WAIT_TIME = 40,              // "reconnect-wait-time"
        S_ON_FAIL = 41,                          // "on-fail"
        S_STOP_RETRY_EXIT = 42,                  // "stop-retry-exit"
        S_SERVE_RETRY_EXIT = 43,                 // "serve-retry-exit"
        S_SERVE_RETRY_CONTINUE = 44,             // "serve-retry-continue"
        S_RETRY_ON_STARTUP = 45,                 // "retry-on-startup"
        S_MAX_ROW_ERRORS = 46,                   // "max-row-errors"
        S_TRUST_ANCHOR = 47,                     // "trust-anchor"
        S_CERT_FILE = 48,                        // "cert-file"
        S_KEY_FILE = 49,                         // "key-file"
        S_CIPHER_LIST = 50,                      // "cipher-list"
        S_PREFERRED_LIFETIME = 51,               // "preferred-lifetime"
        S_MIN_PREFERRED_LIFETIME = 52,           // "min-preferred-lifetime"
        S_MAX_PREFERRED_LIFETIME = 53,           // "max-preferred-lifetime"
        S_VALID_LIFETIME = 54,                   // "valid-lifetime"
        S_MIN_VALID_LIFETIME = 55,               // "min-valid-lifetime"
        S_MAX_VALID_LIFETIME = 56,               // "max-valid-lifetime"
        S_RENEW_TIMER = 57,                      // "renew-timer"
        S_REBIND_TIMER = 58,                     // "rebind-timer"
        S_CALCULATE_TEE_TIMES = 59,              // "calculate-tee-times"
        S_T1_PERCENT = 60,                       // "t1-percent"
        S_T2_PERCENT = 61,                       // "t2-percent"
        S_CACHE_THRESHOLD = 62,                  // "cache-threshold"
        S_CACHE_MAX_AGE = 63,                    // "cache-max-age"
        S_DECLINE_PROBATION_PERIOD = 64,         // "decline-probation-period"
        S_SERVER_TAG = 65,                       // "server-tag"
        S_STATISTIC_DEFAULT_SAMPLE_COUNT = 66,   // "statistic-default-sample-count"
        S_STATISTIC_DEFAULT_SAMPLE_AGE = 67,     // "statistic-default-sample-age"
        S_DDNS_SEND_UPDATES = 68,                // "ddns-send-updates"
        S_DDNS_OVERRIDE_NO_UPDATE = 69,          // "ddns-override-no-update"
        S_DDNS_OVERRIDE_CLIENT_UPDATE = 70,      // "ddns-override-client-update"
        S_DDNS_REPLACE_CLIENT_NAME = 71,         // "ddns-replace-client-name"
        S_DDNS_GENERATED_PREFIX = 72,            // "ddns-generated-prefix"
        S_DDNS_QUALIFYING_SUFFIX = 73,           // "ddns-qualifying-suffix"
        S_DDNS_UPDATE_ON_RENEW = 74,             // "ddns-update-on-renew"
        S_DDNS_USE_CONFLICT_RESOLUTION = 75,     // "ddns-use-conflict-resolution"
        S_DDNS_TTL_PERCENT = 76,                 // "ddns-ttl-percent"
        S_STORE_EXTENDED_INFO = 77,              // "store-extended-info"
        S_SUBNET6 = 78,                          // "subnet6"
        S_OPTION_DEF = 79,                       // "option-def"
        S_OPTION_DATA = 80,                      // "option-data"
        S_NAME = 81,                             // "name"
        S_DATA = 82,                             // "data"
        S_CODE = 83,                             // "code"
        S_SPACE = 84,                            // "space"
        S_CSV_FORMAT = 85,                       // "csv-format"
        S_ALWAYS_SEND = 86,                      // "always-send"
        S_NEVER_SEND = 87,                       // "never-send"
        S_RECORD_TYPES = 88,                     // "record-types"
        S_ENCAPSULATE = 89,                      // "encapsulate"
        S_ARRAY = 90,                            // "array"
        S_PARKED_PACKET_LIMIT = 91,              // "parked-packet-limit"
        S_ALLOCATOR = 92,                        // "allocator"
        S_PD_ALLOCATOR = 93,                     // "pd-allocator"
        S_DDNS_CONFLICT_RESOLUTION_MODE = 94,    // "ddns-conflict-resolution-mode"
        S_CHECK_WITH_DHCID = 95,                 // "check-with-dhcid"
        S_NO_CHECK_WITH_DHCID = 96,              // "no-check-with-dhcid"
        S_CHECK_EXISTS_WITH_DHCID = 97,          // "check-exists-with-dhcid"
        S_NO_CHECK_WITHOUT_DHCID = 98,           // "no-check-without-dhcid"
        S_SHARED_NETWORKS = 99,                  // "shared-networks"
        S_POOLS = 100,                           // "pools"
        S_POOL = 101,                            // "pool"
        S_PD_POOLS = 102,                        // "pd-pools"
        S_PREFIX = 103,                          // "prefix"
        S_PREFIX_LEN = 104,                      // "prefix-len"
        S_EXCLUDED_PREFIX = 105,                 // "excluded-prefix"
        S_EXCLUDED_PREFIX_LEN = 106,             // "excluded-prefix-len"
        S_DELEGATED_LEN = 107,                   // "delegated-len"
        S_USER_CONTEXT = 108,                    // "user-context"
        S_COMMENT = 109,                         // "comment"
        S_SUBNET = 110,                          // "subnet"
        S_INTERFACE = 111,                       // "interface"
        S_INTERFACE_ID = 112,                    // "interface-id"
        S_ID = 113,                              // "id"
        S_RAPID_COMMIT = 114,                    // "rapid-commit"
        S_RESERVATIONS_GLOBAL = 115,             // "reservations-global"
        S_RESERVATIONS_IN_SUBNET = 116,          // "reservations-in-subnet"
        S_RESERVATIONS_OUT_OF_POOL = 117,        // "reservations-out-of-pool"
        S_MAC_SOURCES = 118,                     // "mac-sources"
        S_RELAY_SUPPLIED_OPTIONS = 119,          // "relay-supplied-options"
        S_HOST_RESERVATION_IDENTIFIERS = 120,    // "host-reservation-identifiers"
        S_SANITY_CHECKS = 121,                   // "sanity-checks"
        S_LEASE_CHECKS = 122,                    // "lease-checks"
        S_EXTENDED_INFO_CHECKS = 123,            // "extended-info-checks"
        S_CLIENT_CLASSES = 124,                  // "client-classes"
        S_REQUIRE_CLIENT_CLASSES = 125,          // "require-client-classes"
        S_TEST = 126,                            // "test"
        S_TEMPLATE_TEST = 127,                   // "template-test"
        S_ONLY_IF_REQUIRED = 128,                // "only-if-required"
        S_CLIENT_CLASS = 129,                    // "client-class"
        S_POOL_ID = 130,                         // "pool-id"
        S_RESERVATIONS = 131,                    // "reservations"
        S_IP_ADDRESSES = 132,                    // "ip-addresses"
        S_PREFIXES = 133,                        // "prefixes"
        S_DUID = 134,                            // "duid"
        S_HW_ADDRESS = 135,                      // "hw-address"
        S_HOSTNAME = 136,                        // "hostname"
        S_FLEX_ID = 137,                         // "flex-id"
        S_RELAY = 138,                           // "relay"
        S_HOOKS_LIBRARIES = 139,                 // "hooks-libraries"
        S_LIBRARY = 140,                         // "library"
        S_PARAMETERS = 141,                      // "parameters"
        S_EXPIRED_LEASES_PROCESSING = 142,       // "expired-leases-processing"
        S_RECLAIM_TIMER_WAIT_TIME = 143,         // "reclaim-timer-wait-time"
        S_FLUSH_RECLAIMED_TIMER_WAIT_TIME = 144, // "flush-reclaimed-timer-wait-time"
        S_HOLD_RECLAIMED_TIME = 145,             // "hold-reclaimed-time"
        S_MAX_RECLAIM_LEASES = 146,              // "max-reclaim-leases"
        S_MAX_RECLAIM_TIME = 147,                // "max-reclaim-time"
        S_UNWARNED_RECLAIM_CYCLES = 148,         // "unwarned-reclaim-cycles"
        S_SERVER_ID = 149,                       // "server-id"
        S_LLT = 150,                             // "LLT"
        S_EN = 151,                              // "EN"
        S_LL = 152,                              // "LL"
        S_IDENTIFIER = 153,                      // "identifier"
        S_HTYPE = 154,                           // "htype"
        S_TIME = 155,                            // "time"
        S_ENTERPRISE_ID = 156,                   // "enterprise-id"
        S_DHCP4O6_PORT = 157,                    // "dhcp4o6-port"
        S_DHCP_MULTI_THREADING = 158,            // "multi-threading"
        S_ENABLE_MULTI_THREADING = 159,          // "enable-multi-threading"
        S_THREAD_POOL_SIZE = 160,                // "thread-pool-size"
        S_PACKET_QUEUE_SIZE = 161,               // "packet-queue-size"
        S_CONTROL_SOCKET = 162,                  // "control-socket"
        S_CONTROL_SOCKETS = 163,                 // "control-sockets"
        S_SOCKET_TYPE = 164,                     // "socket-type"
        S_UNIX = 165,                            // "unix"
        S_HTTP = 166,                            // "http"
        S_HTTPS = 167,                           // "https"
        S_SOCKET_NAME = 168,                     // "socket-name"
        S_SOCKET_ADDRESS = 169,                  // "socket-address"
        S_SOCKET_PORT = 170,                     // "socket-port"
        S_AUTHENTICATION = 171,                  // "authentication"
        S_BASIC = 172,                           // "basic"
        S_REALM = 173,                           // "realm"
        S_DIRECTORY = 174,                       // "directory"
        S_CLIENTS = 175,                         // "clients"
        S_USER_FILE = 176,                       // "user-file"
        S_PASSWORD_FILE = 177,                   // "password-file"
        S_CERT_REQUIRED = 178,                   // "cert-required"
        S_DHCP_QUEUE_CONTROL = 179,              // "dhcp-queue-control"
        S_ENABLE_QUEUE = 180,                    // "enable-queue"
        S_QUEUE_TYPE = 181,                      // "queue-type"
        S_CAPACITY = 182,                        // "capacity"
        S_DHCP_DDNS = 183,                       // "dhcp-ddns"
        S_ENABLE_UPDATES = 184,                  // "enable-updates"
        S_SERVER_IP = 185,                       // "server-ip"
        S_SERVER_PORT = 186,                     // "server-port"
        S_SENDER_IP = 187,                       // "sender-ip"
        S_SENDER_PORT = 188,                     // "sender-port"
        S_MAX_QUEUE_SIZE = 189,                  // "max-queue-size"
        S_NCR_PROTOCOL = 190,                    // "ncr-protocol"
        S_NCR_FORMAT = 191,                      // "ncr-format"
        S_UDP = 192,                             // "UDP"
        S_TCP = 193,                             // "TCP"
        S_JSON = 194,                            // "JSON"
        S_WHEN_PRESENT = 195,                    // "when-present"
        S_NEVER = 196,                           // "never"
        S_ALWAYS = 197,                          // "always"
        S_WHEN_NOT_PRESENT = 198,                // "when-not-present"
        S_HOSTNAME_CHAR_SET = 199,               // "hostname-char-set"
        S_HOSTNAME_CHAR_REPLACEMENT = 200,       // "hostname-char-replacement"
        S_EARLY_GLOBAL_RESERVATIONS_LOOKUP = 201, // "early-global-reservations-lookup"
        S_IP_RESERVATIONS_UNIQUE = 202,          // "ip-reservations-unique"
        S_RESERVATIONS_LOOKUP_FIRST = 203,       // "reservations-lookup-first"
        S_LOGGERS = 204,                         // "loggers"
        S_OUTPUT_OPTIONS = 205,                  // "output-options"
        S_OUTPUT = 206,                          // "output"
        S_DEBUGLEVEL = 207,                      // "debuglevel"
        S_SEVERITY = 208,                        // "severity"
        S_FLUSH = 209,                           // "flush"
        S_MAXSIZE = 210,                         // "maxsize"
        S_MAXVER = 211,                          // "maxver"
        S_PATTERN = 212,                         // "pattern"
        S_COMPATIBILITY = 213,                   // "compatibility"
        S_LENIENT_OPTION_PARSING = 214,          // "lenient-option-parsing"
        S_TOPLEVEL_JSON = 215,                   // TOPLEVEL_JSON
        S_TOPLEVEL_DHCP6 = 216,                  // TOPLEVEL_DHCP6
        S_SUB_DHCP6 = 217,                       // SUB_DHCP6
        S_SUB_INTERFACES6 = 218,                 // SUB_INTERFACES6
        S_SUB_SUBNET6 = 219,                     // SUB_SUBNET6
        S_SUB_POOL6 = 220,                       // SUB_POOL6
        S_SUB_PD_POOL = 221,                     // SUB_PD_POOL
        S_SUB_RESERVATION = 222,                 // SUB_RESERVATION
        S_SUB_OPTION_DEFS = 223,                 // SUB_OPTION_DEFS
        S_SUB_OPTION_DEF = 224,                  // SUB_OPTION_DEF
        S_SUB_OPTION_DATA = 225,                 // SUB_OPTION_DATA
        S_SUB_HOOKS_LIBRARY = 226,               // SUB_HOOKS_LIBRARY
        S_SUB_DHCP_DDNS = 227,                   // SUB_DHCP_DDNS
        S_SUB_CONFIG_CONTROL = 228,              // SUB_CONFIG_CONTROL
        S_STRING = 229,                          // "constant string"
        S_INTEGER = 230,                         // "integer"
        S_FLOAT = 231,                           // "floating point"
        S_BOOLEAN = 232,                         // "boolean"
        S_YYACCEPT = 233,                        // $accept
        S_start = 234,                           // start
        S_235_1 = 235,                           // $@1
        S_236_2 = 236,                           // $@2
        S_237_3 = 237,                           // $@3
        S_238_4 = 238,                           // $@4
        S_239_5 = 239,                           // $@5
        S_240_6 = 240,                           // $@6
        S_241_7 = 241,                           // $@7
        S_242_8 = 242,                           // $@8
        S_243_9 = 243,                           // $@9
        S_244_10 = 244,                          // $@10
        S_245_11 = 245,                          // $@11
        S_246_12 = 246,                          // $@12
        S_247_13 = 247,                          // $@13
        S_248_14 = 248,                          // $@14
        S_value = 249,                           // value
        S_sub_json = 250,                        // sub_json
        S_map2 = 251,                            // map2
        S_252_15 = 252,                          // $@15
        S_map_value = 253,                       // map_value
        S_map_content = 254,                     // map_content
        S_not_empty_map = 255,                   // not_empty_map
        S_list_generic = 256,                    // list_generic
        S_257_16 = 257,                          // $@16
        S_list_content = 258,                    // list_content
        S_not_empty_list = 259,                  // not_empty_list
        S_list_strings = 260,                    // list_strings
        S_261_17 = 261,                          // $@17
        S_list_strings_content = 262,            // list_strings_content
        S_not_empty_list_strings = 263,          // not_empty_list_strings
        S_unknown_map_entry = 264,               // unknown_map_entry
        S_syntax_map = 265,                      // syntax_map
        S_266_18 = 266,                          // $@18
        S_global_object = 267,                   // global_object
        S_268_19 = 268,                          // $@19
        S_global_object_comma = 269,             // global_object_comma
        S_sub_dhcp6 = 270,                       // sub_dhcp6
        S_271_20 = 271,                          // $@20
        S_global_params = 272,                   // global_params
        S_global_param = 273,                    // global_param
        S_data_directory = 274,                  // data_directory
        S_275_21 = 275,                          // $@21
        S_preferred_lifetime = 276,              // preferred_lifetime
        S_min_preferred_lifetime = 277,          // min_preferred_lifetime
        S_max_preferred_lifetime = 278,          // max_preferred_lifetime
        S_valid_lifetime = 279,                  // valid_lifetime
        S_min_valid_lifetime = 280,              // min_valid_lifetime
        S_max_valid_lifetime = 281,              // max_valid_lifetime
        S_renew_timer = 282,                     // renew_timer
        S_rebind_timer = 283,                    // rebind_timer
        S_calculate_tee_times = 284,             // calculate_tee_times
        S_t1_percent = 285,                      // t1_percent
        S_t2_percent = 286,                      // t2_percent
        S_cache_threshold = 287,                 // cache_threshold
        S_cache_max_age = 288,                   // cache_max_age
        S_decline_probation_period = 289,        // decline_probation_period
        S_ddns_send_updates = 290,               // ddns_send_updates
        S_ddns_override_no_update = 291,         // ddns_override_no_update
        S_ddns_override_client_update = 292,     // ddns_override_client_update
        S_ddns_replace_client_name = 293,        // ddns_replace_client_name
        S_294_22 = 294,                          // $@22
        S_ddns_replace_client_name_value = 295,  // ddns_replace_client_name_value
        S_ddns_generated_prefix = 296,           // ddns_generated_prefix
        S_297_23 = 297,                          // $@23
        S_ddns_qualifying_suffix = 298,          // ddns_qualifying_suffix
        S_299_24 = 299,                          // $@24
        S_ddns_update_on_renew = 300,            // ddns_update_on_renew
        S_ddns_use_conflict_resolution = 301,    // ddns_use_conflict_resolution
        S_ddns_conflict_resolution_mode = 302,   // ddns_conflict_resolution_mode
        S_303_25 = 303,                          // $@25
        S_ddns_conflict_resolution_mode_value = 304, // ddns_conflict_resolution_mode_value
        S_ddns_ttl_percent = 305,                // ddns_ttl_percent
        S_hostname_char_set = 306,               // hostname_char_set
        S_307_26 = 307,                          // $@26
        S_hostname_char_replacement = 308,       // hostname_char_replacement
        S_309_27 = 309,                          // $@27
        S_store_extended_info = 310,             // store_extended_info
        S_statistic_default_sample_count = 311,  // statistic_default_sample_count
        S_statistic_default_sample_age = 312,    // statistic_default_sample_age
        S_server_tag = 313,                      // server_tag
        S_314_28 = 314,                          // $@28
        S_parked_packet_limit = 315,             // parked_packet_limit
        S_allocator = 316,                       // allocator
        S_317_29 = 317,                          // $@29
        S_pd_allocator = 318,                    // pd_allocator
        S_319_30 = 319,                          // $@30
        S_early_global_reservations_lookup = 320, // early_global_reservations_lookup
        S_ip_reservations_unique = 321,          // ip_reservations_unique
        S_reservations_lookup_first = 322,       // reservations_lookup_first
        S_interfaces_config = 323,               // interfaces_config
        S_324_31 = 324,                          // $@31
        S_sub_interfaces6 = 325,                 // sub_interfaces6
        S_326_32 = 326,                          // $@32
        S_interfaces_config_params = 327,        // interfaces_config_params
        S_interfaces_config_param = 328,         // interfaces_config_param
        S_interfaces_list = 329,                 // interfaces_list
        S_330_33 = 330,                          // $@33
        S_re_detect = 331,                       // re_detect
        S_service_sockets_require_all = 332,     // service_sockets_require_all
        S_service_sockets_retry_wait_time = 333, // service_sockets_retry_wait_time
        S_service_sockets_max_retries = 334,     // service_sockets_max_retries
        S_lease_database = 335,                  // lease_database
        S_336_34 = 336,                          // $@34
        S_hosts_database = 337,                  // hosts_database
        S_338_35 = 338,                          // $@35
        S_hosts_databases = 339,                 // hosts_databases
        S_340_36 = 340,                          // $@36
        S_database_list = 341,                   // database_list
        S_not_empty_database_list = 342,         // not_empty_database_list
        S_database = 343,                        // database
        S_344_37 = 344,                          // $@37
        S_database_map_params = 345,             // database_map_params
        S_database_map_param = 346,              // database_map_param
        S_database_type = 347,                   // database_type
        S_348_38 = 348,                          // $@38
        S_db_type = 349,                         // db_type
        S_user = 350,                            // user
        S_351_39 = 351,                          // $@39
        S_password = 352,                        // password
        S_353_40 = 353,                          // $@40
        S_host = 354,                            // host
        S_355_41 = 355,                          // $@41
        S_port = 356,                            // port
        S_name = 357,                            // name
        S_358_42 = 358,                          // $@42
        S_persist = 359,                         // persist
        S_lfc_interval = 360,                    // lfc_interval
        S_readonly = 361,                        // readonly
        S_connect_timeout = 362,                 // connect_timeout
        S_read_timeout = 363,                    // read_timeout
        S_write_timeout = 364,                   // write_timeout
        S_tcp_user_timeout = 365,                // tcp_user_timeout
        S_reconnect_wait_time = 366,             // reconnect_wait_time
        S_on_fail = 367,                         // on_fail
        S_368_43 = 368,                          // $@43
        S_on_fail_mode = 369,                    // on_fail_mode
        S_retry_on_startup = 370,                // retry_on_startup
        S_max_row_errors = 371,                  // max_row_errors
        S_max_reconnect_tries = 372,             // max_reconnect_tries
        S_trust_anchor = 373,                    // trust_anchor
        S_374_44 = 374,                          // $@44
        S_cert_file = 375,                       // cert_file
        S_376_45 = 376,                          // $@45
        S_key_file = 377,                        // key_file
        S_378_46 = 378,                          // $@46
        S_cipher_list = 379,                     // cipher_list
        S_380_47 = 380,                          // $@47
        S_sanity_checks = 381,                   // sanity_checks
        S_382_48 = 382,                          // $@48
        S_sanity_checks_params = 383,            // sanity_checks_params
        S_sanity_checks_param = 384,             // sanity_checks_param
        S_lease_checks = 385,                    // lease_checks
        S_386_49 = 386,                          // $@49
        S_extended_info_checks = 387,            // extended_info_checks
        S_388_50 = 388,                          // $@50
        S_mac_sources = 389,                     // mac_sources
        S_390_51 = 390,                          // $@51
        S_mac_sources_list = 391,                // mac_sources_list
        S_mac_sources_value = 392,               // mac_sources_value
        S_duid_id = 393,                         // duid_id
        S_string_id = 394,                       // string_id
        S_host_reservation_identifiers = 395,    // host_reservation_identifiers
        S_396_52 = 396,                          // $@52
        S_host_reservation_identifiers_list = 397, // host_reservation_identifiers_list
        S_host_reservation_identifier = 398,     // host_reservation_identifier
        S_hw_address_id = 399,                   // hw_address_id
        S_flex_id = 400,                         // flex_id
        S_relay_supplied_options = 401,          // relay_supplied_options
        S_402_53 = 402,                          // $@53
        S_dhcp_multi_threading = 403,            // dhcp_multi_threading
        S_404_54 = 404,                          // $@54
        S_multi_threading_params = 405,          // multi_threading_params
        S_multi_threading_param = 406,           // multi_threading_param
        S_enable_multi_threading = 407,          // enable_multi_threading
        S_thread_pool_size = 408,                // thread_pool_size
        S_packet_queue_size = 409,               // packet_queue_size
        S_hooks_libraries = 410,                 // hooks_libraries
        S_411_55 = 411,                          // $@55
        S_hooks_libraries_list = 412,            // hooks_libraries_list
        S_not_empty_hooks_libraries_list = 413,  // not_empty_hooks_libraries_list
        S_hooks_library = 414,                   // hooks_library
        S_415_56 = 415,                          // $@56
        S_sub_hooks_library = 416,               // sub_hooks_library
        S_417_57 = 417,                          // $@57
        S_hooks_params = 418,                    // hooks_params
        S_hooks_param = 419,                     // hooks_param
        S_library = 420,                         // library
        S_421_58 = 421,                          // $@58
        S_parameters = 422,                      // parameters
        S_423_59 = 423,                          // $@59
        S_expired_leases_processing = 424,       // expired_leases_processing
        S_425_60 = 425,                          // $@60
        S_expired_leases_params = 426,           // expired_leases_params
        S_expired_leases_param = 427,            // expired_leases_param
        S_reclaim_timer_wait_time = 428,         // reclaim_timer_wait_time
        S_flush_reclaimed_timer_wait_time = 429, // flush_reclaimed_timer_wait_time
        S_hold_reclaimed_time = 430,             // hold_reclaimed_time
        S_max_reclaim_leases = 431,              // max_reclaim_leases
        S_max_reclaim_time = 432,                // max_reclaim_time
        S_unwarned_reclaim_cycles = 433,         // unwarned_reclaim_cycles
        S_subnet6_list = 434,                    // subnet6_list
        S_435_61 = 435,                          // $@61
        S_subnet6_list_content = 436,            // subnet6_list_content
        S_not_empty_subnet6_list = 437,          // not_empty_subnet6_list
        S_subnet6 = 438,                         // subnet6
        S_439_62 = 439,                          // $@62
        S_sub_subnet6 = 440,                     // sub_subnet6
        S_441_63 = 441,                          // $@63
        S_subnet6_params = 442,                  // subnet6_params
        S_subnet6_param = 443,                   // subnet6_param
        S_subnet = 444,                          // subnet
        S_445_64 = 445,                          // $@64
        S_interface = 446,                       // interface
        S_447_65 = 447,                          // $@65
        S_interface_id = 448,                    // interface_id
        S_449_66 = 449,                          // $@66
        S_client_class = 450,                    // client_class
        S_451_67 = 451,                          // $@67
        S_require_client_classes = 452,          // require_client_classes
        S_453_68 = 453,                          // $@68
        S_reservations_global = 454,             // reservations_global
        S_reservations_in_subnet = 455,          // reservations_in_subnet
        S_reservations_out_of_pool = 456,        // reservations_out_of_pool
        S_id = 457,                              // id
        S_rapid_commit = 458,                    // rapid_commit
        S_shared_networks = 459,                 // shared_networks
        S_460_69 = 460,                          // $@69
        S_shared_networks_content = 461,         // shared_networks_content
        S_shared_networks_list = 462,            // shared_networks_list
        S_shared_network = 463,                  // shared_network
        S_464_70 = 464,                          // $@70
        S_shared_network_params = 465,           // shared_network_params
        S_shared_network_param = 466,            // shared_network_param
        S_option_def_list = 467,                 // option_def_list
        S_468_71 = 468,                          // $@71
        S_sub_option_def_list = 469,             // sub_option_def_list
        S_470_72 = 470,                          // $@72
        S_option_def_list_content = 471,         // option_def_list_content
        S_not_empty_option_def_list = 472,       // not_empty_option_def_list
        S_option_def_entry = 473,                // option_def_entry
        S_474_73 = 474,                          // $@73
        S_sub_option_def = 475,                  // sub_option_def
        S_476_74 = 476,                          // $@74
        S_option_def_params = 477,               // option_def_params
        S_not_empty_option_def_params = 478,     // not_empty_option_def_params
        S_option_def_param = 479,                // option_def_param
        S_option_def_name = 480,                 // option_def_name
        S_code = 481,                            // code
        S_option_def_code = 482,                 // option_def_code
        S_option_def_type = 483,                 // option_def_type
        S_484_75 = 484,                          // $@75
        S_option_def_record_types = 485,         // option_def_record_types
        S_486_76 = 486,                          // $@76
        S_space = 487,                           // space
        S_488_77 = 488,                          // $@77
        S_option_def_space = 489,                // option_def_space
        S_option_def_encapsulate = 490,          // option_def_encapsulate
        S_491_78 = 491,                          // $@78
        S_option_def_array = 492,                // option_def_array
        S_option_data_list = 493,                // option_data_list
        S_494_79 = 494,                          // $@79
        S_option_data_list_content = 495,        // option_data_list_content
        S_not_empty_option_data_list = 496,      // not_empty_option_data_list
        S_option_data_entry = 497,               // option_data_entry
        S_498_80 = 498,                          // $@80
        S_sub_option_data = 499,                 // sub_option_data
        S_500_81 = 500,                          // $@81
        S_option_data_params = 501,              // option_data_params
        S_not_empty_option_data_params = 502,    // not_empty_option_data_params
        S_option_data_param = 503,               // option_data_param
        S_option_data_name = 504,                // option_data_name
        S_option_data_data = 505,                // option_data_data
        S_506_82 = 506,                          // $@82
        S_option_data_code = 507,                // option_data_code
        S_option_data_space = 508,               // option_data_space
        S_option_data_csv_format = 509,          // option_data_csv_format
        S_option_data_always_send = 510,         // option_data_always_send
        S_option_data_never_send = 511,          // option_data_never_send
        S_pools_list = 512,                      // pools_list
        S_513_83 = 513,                          // $@83
        S_pools_list_content = 514,              // pools_list_content
        S_not_empty_pools_list = 515,            // not_empty_pools_list
        S_pool_list_entry = 516,                 // pool_list_entry
        S_517_84 = 517,                          // $@84
        S_sub_pool6 = 518,                       // sub_pool6
        S_519_85 = 519,                          // $@85
        S_pool_params = 520,                     // pool_params
        S_pool_param = 521,                      // pool_param
        S_pool_entry = 522,                      // pool_entry
        S_523_86 = 523,                          // $@86
        S_pool_id = 524,                         // pool_id
        S_user_context = 525,                    // user_context
        S_526_87 = 526,                          // $@87
        S_comment = 527,                         // comment
        S_528_88 = 528,                          // $@88
        S_pd_pools_list = 529,                   // pd_pools_list
        S_530_89 = 530,                          // $@89
        S_pd_pools_list_content = 531,           // pd_pools_list_content
        S_not_empty_pd_pools_list = 532,         // not_empty_pd_pools_list
        S_pd_pool_entry = 533,                   // pd_pool_entry
        S_534_90 = 534,                          // $@90
        S_sub_pd_pool = 535,                     // sub_pd_pool
        S_536_91 = 536,                          // $@91
        S_pd_pool_params = 537,                  // pd_pool_params
        S_pd_pool_param = 538,                   // pd_pool_param
        S_pd_prefix = 539,                       // pd_prefix
        S_540_92 = 540,                          // $@92
        S_pd_prefix_len = 541,                   // pd_prefix_len
        S_excluded_prefix = 542,                 // excluded_prefix
        S_543_93 = 543,                          // $@93
        S_excluded_prefix_len = 544,             // excluded_prefix_len
        S_pd_delegated_len = 545,                // pd_delegated_len
        S_reservations = 546,                    // reservations
        S_547_94 = 547,                          // $@94
        S_reservations_list = 548,               // reservations_list
        S_not_empty_reservations_list = 549,     // not_empty_reservations_list
        S_reservation = 550,                     // reservation
        S_551_95 = 551,                          // $@95
        S_sub_reservation = 552,                 // sub_reservation
        S_553_96 = 553,                          // $@96
        S_reservation_params = 554,              // reservation_params
        S_not_empty_reservation_params = 555,    // not_empty_reservation_params
        S_reservation_param = 556,               // reservation_param
        S_ip_addresses = 557,                    // ip_addresses
        S_558_97 = 558,                          // $@97
        S_prefixes = 559,                        // prefixes
        S_560_98 = 560,                          // $@98
        S_duid = 561,                            // duid
        S_562_99 = 562,                          // $@99
        S_hw_address = 563,                      // hw_address
        S_564_100 = 564,                         // $@100
        S_hostname = 565,                        // hostname
        S_566_101 = 566,                         // $@101
        S_flex_id_value = 567,                   // flex_id_value
        S_568_102 = 568,                         // $@102
        S_reservation_client_classes = 569,      // reservation_client_classes
        S_570_103 = 570,                         // $@103
        S_relay = 571,                           // relay
        S_572_104 = 572,                         // $@104
        S_relay_map = 573,                       // relay_map
        S_client_classes = 574,                  // client_classes
        S_575_105 = 575,                         // $@105
        S_client_classes_list = 576,             // client_classes_list
        S_client_class_entry = 577,              // client_class_entry
        S_578_106 = 578,                         // $@106
        S_client_class_params = 579,             // client_class_params
        S_not_empty_client_class_params = 580,   // not_empty_client_class_params
        S_client_class_param = 581,              // client_class_param
        S_client_class_name = 582,               // client_class_name
        S_client_class_test = 583,               // client_class_test
        S_584_107 = 584,                         // $@107
        S_client_class_template_test = 585,      // client_class_template_test
        S_586_108 = 586,                         // $@108
        S_only_if_required = 587,                // only_if_required
        S_server_id = 588,                       // server_id
        S_589_109 = 589,                         // $@109
        S_server_id_params = 590,                // server_id_params
        S_server_id_param = 591,                 // server_id_param
        S_server_id_type = 592,                  // server_id_type
        S_593_110 = 593,                         // $@110
        S_duid_type = 594,                       // duid_type
        S_htype = 595,                           // htype
        S_identifier = 596,                      // identifier
        S_597_111 = 597,                         // $@111
        S_time = 598,                            // time
        S_enterprise_id = 599,                   // enterprise_id
        S_dhcp4o6_port = 600,                    // dhcp4o6_port
        S_control_socket = 601,                  // control_socket
        S_602_112 = 602,                         // $@112
        S_control_sockets = 603,                 // control_sockets
        S_604_113 = 604,                         // $@113
        S_control_socket_list = 605,             // control_socket_list
        S_not_empty_control_socket_list = 606,   // not_empty_control_socket_list
        S_control_socket_entry = 607,            // control_socket_entry
        S_608_114 = 608,                         // $@114
        S_control_socket_params = 609,           // control_socket_params
        S_control_socket_param = 610,            // control_socket_param
        S_control_socket_type = 611,             // control_socket_type
        S_612_115 = 612,                         // $@115
        S_control_socket_type_value = 613,       // control_socket_type_value
        S_control_socket_name = 614,             // control_socket_name
        S_615_116 = 615,                         // $@116
        S_control_socket_address = 616,          // control_socket_address
        S_617_117 = 617,                         // $@117
        S_control_socket_port = 618,             // control_socket_port
        S_cert_required = 619,                   // cert_required
        S_authentication = 620,                  // authentication
        S_621_118 = 621,                         // $@118
        S_auth_params = 622,                     // auth_params
        S_auth_param = 623,                      // auth_param
        S_auth_type = 624,                       // auth_type
        S_625_119 = 625,                         // $@119
        S_auth_type_value = 626,                 // auth_type_value
        S_realm = 627,                           // realm
        S_628_120 = 628,                         // $@120
        S_directory = 629,                       // directory
        S_630_121 = 630,                         // $@121
        S_clients = 631,                         // clients
        S_632_122 = 632,                         // $@122
        S_clients_list = 633,                    // clients_list
        S_not_empty_clients_list = 634,          // not_empty_clients_list
        S_basic_auth = 635,                      // basic_auth
        S_636_123 = 636,                         // $@123
        S_clients_params = 637,                  // clients_params
        S_clients_param = 638,                   // clients_param
        S_user_file = 639,                       // user_file
        S_640_124 = 640,                         // $@124
        S_password_file = 641,                   // password_file
        S_642_125 = 642,                         // $@125
        S_dhcp_queue_control = 643,              // dhcp_queue_control
        S_644_126 = 644,                         // $@126
        S_queue_control_params = 645,            // queue_control_params
        S_queue_control_param = 646,             // queue_control_param
        S_enable_queue = 647,                    // enable_queue
        S_queue_type = 648,                      // queue_type
        S_649_127 = 649,                         // $@127
        S_capacity = 650,                        // capacity
        S_arbitrary_map_entry = 651,             // arbitrary_map_entry
        S_652_128 = 652,                         // $@128
        S_dhcp_ddns = 653,                       // dhcp_ddns
        S_654_129 = 654,                         // $@129
        S_sub_dhcp_ddns = 655,                   // sub_dhcp_ddns
        S_656_130 = 656,                         // $@130
        S_dhcp_ddns_params = 657,                // dhcp_ddns_params
        S_dhcp_ddns_param = 658,                 // dhcp_ddns_param
        S_enable_updates = 659,                  // enable_updates
        S_server_ip = 660,                       // server_ip
        S_661_131 = 661,                         // $@131
        S_server_port = 662,                     // server_port
        S_sender_ip = 663,                       // sender_ip
        S_664_132 = 664,                         // $@132
        S_sender_port = 665,                     // sender_port
        S_max_queue_size = 666,                  // max_queue_size
        S_ncr_protocol = 667,                    // ncr_protocol
        S_668_133 = 668,                         // $@133
        S_ncr_protocol_value = 669,              // ncr_protocol_value
        S_ncr_format = 670,                      // ncr_format
        S_671_134 = 671,                         // $@134
        S_config_control = 672,                  // config_control
        S_673_135 = 673,                         // $@135
        S_sub_config_control = 674,              // sub_config_control
        S_675_136 = 675,                         // $@136
        S_config_control_params = 676,           // config_control_params
        S_config_control_param = 677,            // config_control_param
        S_config_databases = 678,                // config_databases
        S_679_137 = 679,                         // $@137
        S_config_fetch_wait_time = 680,          // config_fetch_wait_time
        S_loggers = 681,                         // loggers
        S_682_138 = 682,                         // $@138
        S_loggers_entries = 683,                 // loggers_entries
        S_logger_entry = 684,                    // logger_entry
        S_685_139 = 685,                         // $@139
        S_logger_params = 686,                   // logger_params
        S_logger_param = 687,                    // logger_param
        S_debuglevel = 688,                      // debuglevel
        S_severity = 689,                        // severity
        S_690_140 = 690,                         // $@140
        S_output_options_list = 691,             // output_options_list
        S_692_141 = 692,                         // $@141
        S_output_options_list_content = 693,     // output_options_list_content
        S_output_entry = 694,                    // output_entry
        S_695_142 = 695,                         // $@142
        S_output_params_list = 696,              // output_params_list
        S_output_params = 697,                   // output_params
        S_output = 698,                          // output
        S_699_143 = 699,                         // $@143
        S_flush = 700,                           // flush
        S_maxsize = 701,                         // maxsize
        S_maxver = 702,                          // maxver
        S_pattern = 703,                         // pattern
        S_704_144 = 704,                         // $@144
        S_compatibility = 705,                   // compatibility
        S_706_145 = 706,                         // $@145
        S_compatibility_params = 707,            // compatibility_params
        S_compatibility_param = 708,             // compatibility_param
        S_lenient_option_parsing = 709           // lenient_option_parsing
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
      case symbol_kind::S_ddns_replace_client_name_value: // ddns_replace_client_name_value
      case symbol_kind::S_ddns_conflict_resolution_mode_value: // ddns_conflict_resolution_mode_value
      case symbol_kind::S_db_type: // db_type
      case symbol_kind::S_on_fail_mode: // on_fail_mode
      case symbol_kind::S_duid_type: // duid_type
      case symbol_kind::S_control_socket_type_value: // control_socket_type_value
      case symbol_kind::S_auth_type_value: // auth_type_value
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
      case symbol_kind::S_ddns_replace_client_name_value: // ddns_replace_client_name_value
      case symbol_kind::S_ddns_conflict_resolution_mode_value: // ddns_conflict_resolution_mode_value
      case symbol_kind::S_db_type: // db_type
      case symbol_kind::S_on_fail_mode: // on_fail_mode
      case symbol_kind::S_duid_type: // duid_type
      case symbol_kind::S_control_socket_type_value: // control_socket_type_value
      case symbol_kind::S_auth_type_value: // auth_type_value
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
        PARSER6__ASSERT (tok == token::TOKEN_END
                   || (token::TOKEN_PARSER6_error <= tok && tok <= token::TOKEN_SUB_CONFIG_CONTROL));
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
        PARSER6__ASSERT (tok == token::TOKEN_BOOLEAN);
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
        PARSER6__ASSERT (tok == token::TOKEN_FLOAT);
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
        PARSER6__ASSERT (tok == token::TOKEN_INTEGER);
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
        PARSER6__ASSERT (tok == token::TOKEN_STRING);
#endif
      }
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
      make_SERVICE_SOCKETS_REQUIRE_ALL (location_type l)
      {
        return symbol_type (token::TOKEN_SERVICE_SOCKETS_REQUIRE_ALL, std::move (l));
      }
#else
      static
      symbol_type
      make_SERVICE_SOCKETS_REQUIRE_ALL (const location_type& l)
      {
        return symbol_type (token::TOKEN_SERVICE_SOCKETS_REQUIRE_ALL, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_SERVICE_SOCKETS_RETRY_WAIT_TIME (location_type l)
      {
        return symbol_type (token::TOKEN_SERVICE_SOCKETS_RETRY_WAIT_TIME, std::move (l));
      }
#else
      static
      symbol_type
      make_SERVICE_SOCKETS_RETRY_WAIT_TIME (const location_type& l)
      {
        return symbol_type (token::TOKEN_SERVICE_SOCKETS_RETRY_WAIT_TIME, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_SERVICE_SOCKETS_MAX_RETRIES (location_type l)
      {
        return symbol_type (token::TOKEN_SERVICE_SOCKETS_MAX_RETRIES, std::move (l));
      }
#else
      static
      symbol_type
      make_SERVICE_SOCKETS_MAX_RETRIES (const location_type& l)
      {
        return symbol_type (token::TOKEN_SERVICE_SOCKETS_MAX_RETRIES, l);
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
      make_READ_TIMEOUT (location_type l)
      {
        return symbol_type (token::TOKEN_READ_TIMEOUT, std::move (l));
      }
#else
      static
      symbol_type
      make_READ_TIMEOUT (const location_type& l)
      {
        return symbol_type (token::TOKEN_READ_TIMEOUT, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_WRITE_TIMEOUT (location_type l)
      {
        return symbol_type (token::TOKEN_WRITE_TIMEOUT, std::move (l));
      }
#else
      static
      symbol_type
      make_WRITE_TIMEOUT (const location_type& l)
      {
        return symbol_type (token::TOKEN_WRITE_TIMEOUT, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TCP_USER_TIMEOUT (location_type l)
      {
        return symbol_type (token::TOKEN_TCP_USER_TIMEOUT, std::move (l));
      }
#else
      static
      symbol_type
      make_TCP_USER_TIMEOUT (const location_type& l)
      {
        return symbol_type (token::TOKEN_TCP_USER_TIMEOUT, l);
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
      make_ON_FAIL (location_type l)
      {
        return symbol_type (token::TOKEN_ON_FAIL, std::move (l));
      }
#else
      static
      symbol_type
      make_ON_FAIL (const location_type& l)
      {
        return symbol_type (token::TOKEN_ON_FAIL, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_STOP_RETRY_EXIT (location_type l)
      {
        return symbol_type (token::TOKEN_STOP_RETRY_EXIT, std::move (l));
      }
#else
      static
      symbol_type
      make_STOP_RETRY_EXIT (const location_type& l)
      {
        return symbol_type (token::TOKEN_STOP_RETRY_EXIT, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_SERVE_RETRY_EXIT (location_type l)
      {
        return symbol_type (token::TOKEN_SERVE_RETRY_EXIT, std::move (l));
      }
#else
      static
      symbol_type
      make_SERVE_RETRY_EXIT (const location_type& l)
      {
        return symbol_type (token::TOKEN_SERVE_RETRY_EXIT, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_SERVE_RETRY_CONTINUE (location_type l)
      {
        return symbol_type (token::TOKEN_SERVE_RETRY_CONTINUE, std::move (l));
      }
#else
      static
      symbol_type
      make_SERVE_RETRY_CONTINUE (const location_type& l)
      {
        return symbol_type (token::TOKEN_SERVE_RETRY_CONTINUE, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_RETRY_ON_STARTUP (location_type l)
      {
        return symbol_type (token::TOKEN_RETRY_ON_STARTUP, std::move (l));
      }
#else
      static
      symbol_type
      make_RETRY_ON_STARTUP (const location_type& l)
      {
        return symbol_type (token::TOKEN_RETRY_ON_STARTUP, l);
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
      make_CIPHER_LIST (location_type l)
      {
        return symbol_type (token::TOKEN_CIPHER_LIST, std::move (l));
      }
#else
      static
      symbol_type
      make_CIPHER_LIST (const location_type& l)
      {
        return symbol_type (token::TOKEN_CIPHER_LIST, l);
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
      make_DDNS_USE_CONFLICT_RESOLUTION (location_type l)
      {
        return symbol_type (token::TOKEN_DDNS_USE_CONFLICT_RESOLUTION, std::move (l));
      }
#else
      static
      symbol_type
      make_DDNS_USE_CONFLICT_RESOLUTION (const location_type& l)
      {
        return symbol_type (token::TOKEN_DDNS_USE_CONFLICT_RESOLUTION, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_DDNS_TTL_PERCENT (location_type l)
      {
        return symbol_type (token::TOKEN_DDNS_TTL_PERCENT, std::move (l));
      }
#else
      static
      symbol_type
      make_DDNS_TTL_PERCENT (const location_type& l)
      {
        return symbol_type (token::TOKEN_DDNS_TTL_PERCENT, l);
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
      make_NEVER_SEND (location_type l)
      {
        return symbol_type (token::TOKEN_NEVER_SEND, std::move (l));
      }
#else
      static
      symbol_type
      make_NEVER_SEND (const location_type& l)
      {
        return symbol_type (token::TOKEN_NEVER_SEND, l);
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
      make_PARKED_PACKET_LIMIT (location_type l)
      {
        return symbol_type (token::TOKEN_PARKED_PACKET_LIMIT, std::move (l));
      }
#else
      static
      symbol_type
      make_PARKED_PACKET_LIMIT (const location_type& l)
      {
        return symbol_type (token::TOKEN_PARKED_PACKET_LIMIT, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ALLOCATOR (location_type l)
      {
        return symbol_type (token::TOKEN_ALLOCATOR, std::move (l));
      }
#else
      static
      symbol_type
      make_ALLOCATOR (const location_type& l)
      {
        return symbol_type (token::TOKEN_ALLOCATOR, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_PD_ALLOCATOR (location_type l)
      {
        return symbol_type (token::TOKEN_PD_ALLOCATOR, std::move (l));
      }
#else
      static
      symbol_type
      make_PD_ALLOCATOR (const location_type& l)
      {
        return symbol_type (token::TOKEN_PD_ALLOCATOR, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_DDNS_CONFLICT_RESOLUTION_MODE (location_type l)
      {
        return symbol_type (token::TOKEN_DDNS_CONFLICT_RESOLUTION_MODE, std::move (l));
      }
#else
      static
      symbol_type
      make_DDNS_CONFLICT_RESOLUTION_MODE (const location_type& l)
      {
        return symbol_type (token::TOKEN_DDNS_CONFLICT_RESOLUTION_MODE, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_CHECK_WITH_DHCID (location_type l)
      {
        return symbol_type (token::TOKEN_CHECK_WITH_DHCID, std::move (l));
      }
#else
      static
      symbol_type
      make_CHECK_WITH_DHCID (const location_type& l)
      {
        return symbol_type (token::TOKEN_CHECK_WITH_DHCID, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_NO_CHECK_WITH_DHCID (location_type l)
      {
        return symbol_type (token::TOKEN_NO_CHECK_WITH_DHCID, std::move (l));
      }
#else
      static
      symbol_type
      make_NO_CHECK_WITH_DHCID (const location_type& l)
      {
        return symbol_type (token::TOKEN_NO_CHECK_WITH_DHCID, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_CHECK_EXISTS_WITH_DHCID (location_type l)
      {
        return symbol_type (token::TOKEN_CHECK_EXISTS_WITH_DHCID, std::move (l));
      }
#else
      static
      symbol_type
      make_CHECK_EXISTS_WITH_DHCID (const location_type& l)
      {
        return symbol_type (token::TOKEN_CHECK_EXISTS_WITH_DHCID, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_NO_CHECK_WITHOUT_DHCID (location_type l)
      {
        return symbol_type (token::TOKEN_NO_CHECK_WITHOUT_DHCID, std::move (l));
      }
#else
      static
      symbol_type
      make_NO_CHECK_WITHOUT_DHCID (const location_type& l)
      {
        return symbol_type (token::TOKEN_NO_CHECK_WITHOUT_DHCID, l);
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
      make_EXTENDED_INFO_CHECKS (location_type l)
      {
        return symbol_type (token::TOKEN_EXTENDED_INFO_CHECKS, std::move (l));
      }
#else
      static
      symbol_type
      make_EXTENDED_INFO_CHECKS (const location_type& l)
      {
        return symbol_type (token::TOKEN_EXTENDED_INFO_CHECKS, l);
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
      make_TEMPLATE_TEST (location_type l)
      {
        return symbol_type (token::TOKEN_TEMPLATE_TEST, std::move (l));
      }
#else
      static
      symbol_type
      make_TEMPLATE_TEST (const location_type& l)
      {
        return symbol_type (token::TOKEN_TEMPLATE_TEST, l);
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
      make_POOL_ID (location_type l)
      {
        return symbol_type (token::TOKEN_POOL_ID, std::move (l));
      }
#else
      static
      symbol_type
      make_POOL_ID (const location_type& l)
      {
        return symbol_type (token::TOKEN_POOL_ID, l);
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
      make_EARLY_GLOBAL_RESERVATIONS_LOOKUP (location_type l)
      {
        return symbol_type (token::TOKEN_EARLY_GLOBAL_RESERVATIONS_LOOKUP, std::move (l));
      }
#else
      static
      symbol_type
      make_EARLY_GLOBAL_RESERVATIONS_LOOKUP (const location_type& l)
      {
        return symbol_type (token::TOKEN_EARLY_GLOBAL_RESERVATIONS_LOOKUP, l);
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
      make_RESERVATIONS_LOOKUP_FIRST (location_type l)
      {
        return symbol_type (token::TOKEN_RESERVATIONS_LOOKUP_FIRST, std::move (l));
      }
#else
      static
      symbol_type
      make_RESERVATIONS_LOOKUP_FIRST (const location_type& l)
      {
        return symbol_type (token::TOKEN_RESERVATIONS_LOOKUP_FIRST, l);
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
      make_COMPATIBILITY (location_type l)
      {
        return symbol_type (token::TOKEN_COMPATIBILITY, std::move (l));
      }
#else
      static
      symbol_type
      make_COMPATIBILITY (const location_type& l)
      {
        return symbol_type (token::TOKEN_COMPATIBILITY, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_LENIENT_OPTION_PARSING (location_type l)
      {
        return symbol_type (token::TOKEN_LENIENT_OPTION_PARSING, std::move (l));
      }
#else
      static
      symbol_type
      make_LENIENT_OPTION_PARSING (const location_type& l)
      {
        return symbol_type (token::TOKEN_LENIENT_OPTION_PARSING, l);
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
      const symbol_type& lookahead () const YY_NOEXCEPT { return yyla_; }
      symbol_kind_type token () const YY_NOEXCEPT { return yyla_.kind (); }
      const location_type& location () const YY_NOEXCEPT { return yyla_.location; }

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
      yylast_ = 1436,     ///< Last index in yytable_.
      yynnts_ = 477,  ///< Number of nonterminal symbols.
      yyfinal_ = 30 ///< Termination state number.
    };


    // User arguments.
    isc::dhcp::Parser6Context& ctx;

  };

  inline
  Dhcp6Parser::symbol_kind_type
  Dhcp6Parser::yytranslate_ (int t) YY_NOEXCEPT
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
     195,   196,   197,   198,   199,   200,   201,   202,   203,   204,
     205,   206,   207,   208,   209,   210,   211,   212,   213,   214,
     215,   216,   217,   218,   219,   220,   221,   222,   223,   224,
     225,   226,   227,   228,   229,   230,   231,   232
    };
    // Last valid token kind.
    const int code_max = 487;

    if (t <= 0)
      return symbol_kind::S_YYEOF;
    else if (t <= code_max)
      return static_cast <symbol_kind_type> (translate_table[t]);
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
      case symbol_kind::S_ddns_conflict_resolution_mode_value: // ddns_conflict_resolution_mode_value
      case symbol_kind::S_db_type: // db_type
      case symbol_kind::S_on_fail_mode: // on_fail_mode
      case symbol_kind::S_duid_type: // duid_type
      case symbol_kind::S_control_socket_type_value: // control_socket_type_value
      case symbol_kind::S_auth_type_value: // auth_type_value
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
      case symbol_kind::S_ddns_conflict_resolution_mode_value: // ddns_conflict_resolution_mode_value
      case symbol_kind::S_db_type: // db_type
      case symbol_kind::S_on_fail_mode: // on_fail_mode
      case symbol_kind::S_duid_type: // duid_type
      case symbol_kind::S_control_socket_type_value: // control_socket_type_value
      case symbol_kind::S_auth_type_value: // auth_type_value
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
  Dhcp6Parser::by_kind::by_kind () YY_NOEXCEPT
    : kind_ (symbol_kind::S_YYEMPTY)
  {}

#if 201103L <= YY_CPLUSPLUS
  inline
  Dhcp6Parser::by_kind::by_kind (by_kind&& that) YY_NOEXCEPT
    : kind_ (that.kind_)
  {
    that.clear ();
  }
#endif

  inline
  Dhcp6Parser::by_kind::by_kind (const by_kind& that) YY_NOEXCEPT
    : kind_ (that.kind_)
  {}

  inline
  Dhcp6Parser::by_kind::by_kind (token_kind_type t) YY_NOEXCEPT
    : kind_ (yytranslate_ (t))
  {}



  inline
  void
  Dhcp6Parser::by_kind::clear () YY_NOEXCEPT
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
#line 5942 "dhcp6_parser.h"




#endif // !YY_PARSER6_DHCP6_PARSER_H_INCLUDED
