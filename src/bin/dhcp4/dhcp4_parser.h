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
 ** \file dhcp4_parser.h
 ** Define the isc::dhcp::parser class.
 */

// C++ LALR(1) parser skeleton written by Akim Demaille.

// DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
// especially those whose name start with YY_ or yy_.  They are
// private implementation details that can be changed or removed.

#ifndef YY_PARSER4_DHCP4_PARSER_H_INCLUDED
# define YY_PARSER4_DHCP4_PARSER_H_INCLUDED
// "%code requires" blocks.
#line 17 "dhcp4_parser.yy"

#include <string>
#include <cc/data.h>
#include <dhcp/option.h>
#include <boost/lexical_cast.hpp>
#include <dhcp4/parser_context_decl.h>

using namespace isc::dhcp;
using namespace isc::data;
using namespace std;

#line 61 "dhcp4_parser.h"

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
#ifndef PARSER4__ASSERT
# include <cassert>
# define PARSER4__ASSERT assert
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

#line 14 "dhcp4_parser.yy"
namespace isc { namespace dhcp {
#line 210 "dhcp4_parser.h"




  /// A Bison parser.
  class Dhcp4Parser
  {
  public:
#ifdef PARSER4_STYPE
# ifdef __GNUC__
#  pragma GCC message "bison: do not #define PARSER4_STYPE in C++, use %define api.value.type"
# endif
    typedef PARSER4_STYPE value_type;
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
      PARSER4__ASSERT (sizeof (T) <= size);
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
      PARSER4__ASSERT (!yytypeid_);
    }

# if 201103L <= YY_CPLUSPLUS
    /// Instantiate a \a T in here from \a t.
    template <typename T, typename... U>
    T&
    emplace (U&&... u)
    {
      PARSER4__ASSERT (!yytypeid_);
      PARSER4__ASSERT (sizeof (T) <= size);
      yytypeid_ = & typeid (T);
      return *new (yyas_<T> ()) T (std::forward <U>(u)...);
    }
# else
    /// Instantiate an empty \a T in here.
    template <typename T>
    T&
    emplace ()
    {
      PARSER4__ASSERT (!yytypeid_);
      PARSER4__ASSERT (sizeof (T) <= size);
      yytypeid_ = & typeid (T);
      return *new (yyas_<T> ()) T ();
    }

    /// Instantiate a \a T in here from \a t.
    template <typename T>
    T&
    emplace (const T& t)
    {
      PARSER4__ASSERT (!yytypeid_);
      PARSER4__ASSERT (sizeof (T) <= size);
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
      PARSER4__ASSERT (yytypeid_);
      PARSER4__ASSERT (*yytypeid_ == typeid (T));
      PARSER4__ASSERT (sizeof (T) <= size);
      return *yyas_<T> ();
    }

    /// Const accessor to a built \a T (for %printer).
    template <typename T>
    const T&
    as () const YY_NOEXCEPT
    {
      PARSER4__ASSERT (yytypeid_);
      PARSER4__ASSERT (*yytypeid_ == typeid (T));
      PARSER4__ASSERT (sizeof (T) <= size);
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
      PARSER4__ASSERT (yytypeid_);
      PARSER4__ASSERT (*yytypeid_ == *that.yytypeid_);
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
      // socket_type
      // outbound_interface_value
      // db_type
      // on_fail_mode
      // hr_mode
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
        TOKEN_PARSER4_EMPTY = -2,
    TOKEN_END = 0,                 // "end of file"
    TOKEN_PARSER4_error = 256,     // error
    TOKEN_PARSER4_UNDEF = 257,     // "invalid token"
    TOKEN_COMMA = 258,             // ","
    TOKEN_COLON = 259,             // ":"
    TOKEN_LSQUARE_BRACKET = 260,   // "["
    TOKEN_RSQUARE_BRACKET = 261,   // "]"
    TOKEN_LCURLY_BRACKET = 262,    // "{"
    TOKEN_RCURLY_BRACKET = 263,    // "}"
    TOKEN_NULL_TYPE = 264,         // "null"
    TOKEN_DHCP4 = 265,             // "Dhcp4"
    TOKEN_CONFIG_CONTROL = 266,    // "config-control"
    TOKEN_CONFIG_DATABASES = 267,  // "config-databases"
    TOKEN_CONFIG_FETCH_WAIT_TIME = 268, // "config-fetch-wait-time"
    TOKEN_INTERFACES_CONFIG = 269, // "interfaces-config"
    TOKEN_INTERFACES = 270,        // "interfaces"
    TOKEN_DHCP_SOCKET_TYPE = 271,  // "dhcp-socket-type"
    TOKEN_RAW = 272,               // "raw"
    TOKEN_UDP = 273,               // "udp"
    TOKEN_OUTBOUND_INTERFACE = 274, // "outbound-interface"
    TOKEN_SAME_AS_INBOUND = 275,   // "same-as-inbound"
    TOKEN_USE_ROUTING = 276,       // "use-routing"
    TOKEN_RE_DETECT = 277,         // "re-detect"
    TOKEN_SERVICE_SOCKETS_REQUIRE_ALL = 278, // "service-sockets-require-all"
    TOKEN_SERVICE_SOCKETS_RETRY_WAIT_TIME = 279, // "service-sockets-retry-wait-time"
    TOKEN_SERVICE_SOCKETS_MAX_RETRIES = 280, // "service-sockets-max-retries"
    TOKEN_SANITY_CHECKS = 281,     // "sanity-checks"
    TOKEN_LEASE_CHECKS = 282,      // "lease-checks"
    TOKEN_ECHO_CLIENT_ID = 283,    // "echo-client-id"
    TOKEN_MATCH_CLIENT_ID = 284,   // "match-client-id"
    TOKEN_AUTHORITATIVE = 285,     // "authoritative"
    TOKEN_NEXT_SERVER = 286,       // "next-server"
    TOKEN_SERVER_HOSTNAME = 287,   // "server-hostname"
    TOKEN_BOOT_FILE_NAME = 288,    // "boot-file-name"
    TOKEN_LEASE_DATABASE = 289,    // "lease-database"
    TOKEN_HOSTS_DATABASE = 290,    // "hosts-database"
    TOKEN_HOSTS_DATABASES = 291,   // "hosts-databases"
    TOKEN_TYPE = 292,              // "type"
    TOKEN_MEMFILE = 293,           // "memfile"
    TOKEN_MYSQL = 294,             // "mysql"
    TOKEN_POSTGRESQL = 295,        // "postgresql"
    TOKEN_USER = 296,              // "user"
    TOKEN_PASSWORD = 297,          // "password"
    TOKEN_HOST = 298,              // "host"
    TOKEN_PORT = 299,              // "port"
    TOKEN_PERSIST = 300,           // "persist"
    TOKEN_LFC_INTERVAL = 301,      // "lfc-interval"
    TOKEN_READONLY = 302,          // "readonly"
    TOKEN_CONNECT_TIMEOUT = 303,   // "connect-timeout"
    TOKEN_READ_TIMEOUT = 304,      // "read-timeout"
    TOKEN_WRITE_TIMEOUT = 305,     // "write-timeout"
    TOKEN_TCP_USER_TIMEOUT = 306,  // "tcp-user-timeout"
    TOKEN_MAX_RECONNECT_TRIES = 307, // "max-reconnect-tries"
    TOKEN_RECONNECT_WAIT_TIME = 308, // "reconnect-wait-time"
    TOKEN_ON_FAIL = 309,           // "on-fail"
    TOKEN_STOP_RETRY_EXIT = 310,   // "stop-retry-exit"
    TOKEN_SERVE_RETRY_EXIT = 311,  // "serve-retry-exit"
    TOKEN_SERVE_RETRY_CONTINUE = 312, // "serve-retry-continue"
    TOKEN_MAX_ROW_ERRORS = 313,    // "max-row-errors"
    TOKEN_TRUST_ANCHOR = 314,      // "trust-anchor"
    TOKEN_CERT_FILE = 315,         // "cert-file"
    TOKEN_KEY_FILE = 316,          // "key-file"
    TOKEN_CIPHER_LIST = 317,       // "cipher-list"
    TOKEN_VALID_LIFETIME = 318,    // "valid-lifetime"
    TOKEN_MIN_VALID_LIFETIME = 319, // "min-valid-lifetime"
    TOKEN_MAX_VALID_LIFETIME = 320, // "max-valid-lifetime"
    TOKEN_RENEW_TIMER = 321,       // "renew-timer"
    TOKEN_REBIND_TIMER = 322,      // "rebind-timer"
    TOKEN_CALCULATE_TEE_TIMES = 323, // "calculate-tee-times"
    TOKEN_T1_PERCENT = 324,        // "t1-percent"
    TOKEN_T2_PERCENT = 325,        // "t2-percent"
    TOKEN_CACHE_THRESHOLD = 326,   // "cache-threshold"
    TOKEN_CACHE_MAX_AGE = 327,     // "cache-max-age"
    TOKEN_DECLINE_PROBATION_PERIOD = 328, // "decline-probation-period"
    TOKEN_SERVER_TAG = 329,        // "server-tag"
    TOKEN_STATISTIC_DEFAULT_SAMPLE_COUNT = 330, // "statistic-default-sample-count"
    TOKEN_STATISTIC_DEFAULT_SAMPLE_AGE = 331, // "statistic-default-sample-age"
    TOKEN_DDNS_SEND_UPDATES = 332, // "ddns-send-updates"
    TOKEN_DDNS_OVERRIDE_NO_UPDATE = 333, // "ddns-override-no-update"
    TOKEN_DDNS_OVERRIDE_CLIENT_UPDATE = 334, // "ddns-override-client-update"
    TOKEN_DDNS_REPLACE_CLIENT_NAME = 335, // "ddns-replace-client-name"
    TOKEN_DDNS_GENERATED_PREFIX = 336, // "ddns-generated-prefix"
    TOKEN_DDNS_QUALIFYING_SUFFIX = 337, // "ddns-qualifying-suffix"
    TOKEN_DDNS_UPDATE_ON_RENEW = 338, // "ddns-update-on-renew"
    TOKEN_DDNS_USE_CONFLICT_RESOLUTION = 339, // "ddns-use-conflict-resolution"
    TOKEN_STORE_EXTENDED_INFO = 340, // "store-extended-info"
    TOKEN_SUBNET4 = 341,           // "subnet4"
    TOKEN_SUBNET_4O6_INTERFACE = 342, // "4o6-interface"
    TOKEN_SUBNET_4O6_INTERFACE_ID = 343, // "4o6-interface-id"
    TOKEN_SUBNET_4O6_SUBNET = 344, // "4o6-subnet"
    TOKEN_OPTION_DEF = 345,        // "option-def"
    TOKEN_OPTION_DATA = 346,       // "option-data"
    TOKEN_NAME = 347,              // "name"
    TOKEN_DATA = 348,              // "data"
    TOKEN_CODE = 349,              // "code"
    TOKEN_SPACE = 350,             // "space"
    TOKEN_CSV_FORMAT = 351,        // "csv-format"
    TOKEN_ALWAYS_SEND = 352,       // "always-send"
    TOKEN_RECORD_TYPES = 353,      // "record-types"
    TOKEN_ENCAPSULATE = 354,       // "encapsulate"
    TOKEN_ARRAY = 355,             // "array"
    TOKEN_PARKED_PACKET_LIMIT = 356, // "parked-packet-limit"
    TOKEN_SHARED_NETWORKS = 357,   // "shared-networks"
    TOKEN_POOLS = 358,             // "pools"
    TOKEN_POOL = 359,              // "pool"
    TOKEN_USER_CONTEXT = 360,      // "user-context"
    TOKEN_COMMENT = 361,           // "comment"
    TOKEN_SUBNET = 362,            // "subnet"
    TOKEN_INTERFACE = 363,         // "interface"
    TOKEN_ID = 364,                // "id"
    TOKEN_RESERVATION_MODE = 365,  // "reservation-mode"
    TOKEN_DISABLED = 366,          // "disabled"
    TOKEN_OUT_OF_POOL = 367,       // "out-of-pool"
    TOKEN_GLOBAL = 368,            // "global"
    TOKEN_ALL = 369,               // "all"
    TOKEN_RESERVATIONS_GLOBAL = 370, // "reservations-global"
    TOKEN_RESERVATIONS_IN_SUBNET = 371, // "reservations-in-subnet"
    TOKEN_RESERVATIONS_OUT_OF_POOL = 372, // "reservations-out-of-pool"
    TOKEN_HOST_RESERVATION_IDENTIFIERS = 373, // "host-reservation-identifiers"
    TOKEN_CLIENT_CLASSES = 374,    // "client-classes"
    TOKEN_REQUIRE_CLIENT_CLASSES = 375, // "require-client-classes"
    TOKEN_TEST = 376,              // "test"
    TOKEN_ONLY_IF_REQUIRED = 377,  // "only-if-required"
    TOKEN_CLIENT_CLASS = 378,      // "client-class"
    TOKEN_RESERVATIONS = 379,      // "reservations"
    TOKEN_DUID = 380,              // "duid"
    TOKEN_HW_ADDRESS = 381,        // "hw-address"
    TOKEN_CIRCUIT_ID = 382,        // "circuit-id"
    TOKEN_CLIENT_ID = 383,         // "client-id"
    TOKEN_HOSTNAME = 384,          // "hostname"
    TOKEN_FLEX_ID = 385,           // "flex-id"
    TOKEN_RELAY = 386,             // "relay"
    TOKEN_IP_ADDRESS = 387,        // "ip-address"
    TOKEN_IP_ADDRESSES = 388,      // "ip-addresses"
    TOKEN_HOOKS_LIBRARIES = 389,   // "hooks-libraries"
    TOKEN_LIBRARY = 390,           // "library"
    TOKEN_PARAMETERS = 391,        // "parameters"
    TOKEN_EXPIRED_LEASES_PROCESSING = 392, // "expired-leases-processing"
    TOKEN_RECLAIM_TIMER_WAIT_TIME = 393, // "reclaim-timer-wait-time"
    TOKEN_FLUSH_RECLAIMED_TIMER_WAIT_TIME = 394, // "flush-reclaimed-timer-wait-time"
    TOKEN_HOLD_RECLAIMED_TIME = 395, // "hold-reclaimed-time"
    TOKEN_MAX_RECLAIM_LEASES = 396, // "max-reclaim-leases"
    TOKEN_MAX_RECLAIM_TIME = 397,  // "max-reclaim-time"
    TOKEN_UNWARNED_RECLAIM_CYCLES = 398, // "unwarned-reclaim-cycles"
    TOKEN_DHCP4O6_PORT = 399,      // "dhcp4o6-port"
    TOKEN_DHCP_MULTI_THREADING = 400, // "multi-threading"
    TOKEN_ENABLE_MULTI_THREADING = 401, // "enable-multi-threading"
    TOKEN_THREAD_POOL_SIZE = 402,  // "thread-pool-size"
    TOKEN_PACKET_QUEUE_SIZE = 403, // "packet-queue-size"
    TOKEN_CONTROL_SOCKET = 404,    // "control-socket"
    TOKEN_SOCKET_TYPE = 405,       // "socket-type"
    TOKEN_SOCKET_NAME = 406,       // "socket-name"
    TOKEN_DHCP_QUEUE_CONTROL = 407, // "dhcp-queue-control"
    TOKEN_ENABLE_QUEUE = 408,      // "enable-queue"
    TOKEN_QUEUE_TYPE = 409,        // "queue-type"
    TOKEN_CAPACITY = 410,          // "capacity"
    TOKEN_DHCP_DDNS = 411,         // "dhcp-ddns"
    TOKEN_ENABLE_UPDATES = 412,    // "enable-updates"
    TOKEN_QUALIFYING_SUFFIX = 413, // "qualifying-suffix"
    TOKEN_SERVER_IP = 414,         // "server-ip"
    TOKEN_SERVER_PORT = 415,       // "server-port"
    TOKEN_SENDER_IP = 416,         // "sender-ip"
    TOKEN_SENDER_PORT = 417,       // "sender-port"
    TOKEN_MAX_QUEUE_SIZE = 418,    // "max-queue-size"
    TOKEN_NCR_PROTOCOL = 419,      // "ncr-protocol"
    TOKEN_NCR_FORMAT = 420,        // "ncr-format"
    TOKEN_OVERRIDE_NO_UPDATE = 421, // "override-no-update"
    TOKEN_OVERRIDE_CLIENT_UPDATE = 422, // "override-client-update"
    TOKEN_REPLACE_CLIENT_NAME = 423, // "replace-client-name"
    TOKEN_GENERATED_PREFIX = 424,  // "generated-prefix"
    TOKEN_TCP = 425,               // "tcp"
    TOKEN_JSON = 426,              // "JSON"
    TOKEN_WHEN_PRESENT = 427,      // "when-present"
    TOKEN_NEVER = 428,             // "never"
    TOKEN_ALWAYS = 429,            // "always"
    TOKEN_WHEN_NOT_PRESENT = 430,  // "when-not-present"
    TOKEN_HOSTNAME_CHAR_SET = 431, // "hostname-char-set"
    TOKEN_HOSTNAME_CHAR_REPLACEMENT = 432, // "hostname-char-replacement"
    TOKEN_EARLY_GLOBAL_RESERVATIONS_LOOKUP = 433, // "early-global-reservations-lookup"
    TOKEN_IP_RESERVATIONS_UNIQUE = 434, // "ip-reservations-unique"
    TOKEN_RESERVATIONS_LOOKUP_FIRST = 435, // "reservations-lookup-first"
    TOKEN_LOGGERS = 436,           // "loggers"
    TOKEN_OUTPUT_OPTIONS = 437,    // "output_options"
    TOKEN_OUTPUT = 438,            // "output"
    TOKEN_DEBUGLEVEL = 439,        // "debuglevel"
    TOKEN_SEVERITY = 440,          // "severity"
    TOKEN_FLUSH = 441,             // "flush"
    TOKEN_MAXSIZE = 442,           // "maxsize"
    TOKEN_MAXVER = 443,            // "maxver"
    TOKEN_PATTERN = 444,           // "pattern"
    TOKEN_COMPATIBILITY = 445,     // "compatibility"
    TOKEN_LENIENT_OPTION_PARSING = 446, // "lenient-option-parsing"
    TOKEN_TOPLEVEL_JSON = 447,     // TOPLEVEL_JSON
    TOKEN_TOPLEVEL_DHCP4 = 448,    // TOPLEVEL_DHCP4
    TOKEN_SUB_DHCP4 = 449,         // SUB_DHCP4
    TOKEN_SUB_INTERFACES4 = 450,   // SUB_INTERFACES4
    TOKEN_SUB_SUBNET4 = 451,       // SUB_SUBNET4
    TOKEN_SUB_POOL4 = 452,         // SUB_POOL4
    TOKEN_SUB_RESERVATION = 453,   // SUB_RESERVATION
    TOKEN_SUB_OPTION_DEFS = 454,   // SUB_OPTION_DEFS
    TOKEN_SUB_OPTION_DEF = 455,    // SUB_OPTION_DEF
    TOKEN_SUB_OPTION_DATA = 456,   // SUB_OPTION_DATA
    TOKEN_SUB_HOOKS_LIBRARY = 457, // SUB_HOOKS_LIBRARY
    TOKEN_SUB_DHCP_DDNS = 458,     // SUB_DHCP_DDNS
    TOKEN_SUB_CONFIG_CONTROL = 459, // SUB_CONFIG_CONTROL
    TOKEN_STRING = 460,            // "constant string"
    TOKEN_INTEGER = 461,           // "integer"
    TOKEN_FLOAT = 462,             // "floating point"
    TOKEN_BOOLEAN = 463            // "boolean"
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
        YYNTOKENS = 209, ///< Number of tokens.
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
        S_DHCP4 = 10,                            // "Dhcp4"
        S_CONFIG_CONTROL = 11,                   // "config-control"
        S_CONFIG_DATABASES = 12,                 // "config-databases"
        S_CONFIG_FETCH_WAIT_TIME = 13,           // "config-fetch-wait-time"
        S_INTERFACES_CONFIG = 14,                // "interfaces-config"
        S_INTERFACES = 15,                       // "interfaces"
        S_DHCP_SOCKET_TYPE = 16,                 // "dhcp-socket-type"
        S_RAW = 17,                              // "raw"
        S_UDP = 18,                              // "udp"
        S_OUTBOUND_INTERFACE = 19,               // "outbound-interface"
        S_SAME_AS_INBOUND = 20,                  // "same-as-inbound"
        S_USE_ROUTING = 21,                      // "use-routing"
        S_RE_DETECT = 22,                        // "re-detect"
        S_SERVICE_SOCKETS_REQUIRE_ALL = 23,      // "service-sockets-require-all"
        S_SERVICE_SOCKETS_RETRY_WAIT_TIME = 24,  // "service-sockets-retry-wait-time"
        S_SERVICE_SOCKETS_MAX_RETRIES = 25,      // "service-sockets-max-retries"
        S_SANITY_CHECKS = 26,                    // "sanity-checks"
        S_LEASE_CHECKS = 27,                     // "lease-checks"
        S_ECHO_CLIENT_ID = 28,                   // "echo-client-id"
        S_MATCH_CLIENT_ID = 29,                  // "match-client-id"
        S_AUTHORITATIVE = 30,                    // "authoritative"
        S_NEXT_SERVER = 31,                      // "next-server"
        S_SERVER_HOSTNAME = 32,                  // "server-hostname"
        S_BOOT_FILE_NAME = 33,                   // "boot-file-name"
        S_LEASE_DATABASE = 34,                   // "lease-database"
        S_HOSTS_DATABASE = 35,                   // "hosts-database"
        S_HOSTS_DATABASES = 36,                  // "hosts-databases"
        S_TYPE = 37,                             // "type"
        S_MEMFILE = 38,                          // "memfile"
        S_MYSQL = 39,                            // "mysql"
        S_POSTGRESQL = 40,                       // "postgresql"
        S_USER = 41,                             // "user"
        S_PASSWORD = 42,                         // "password"
        S_HOST = 43,                             // "host"
        S_PORT = 44,                             // "port"
        S_PERSIST = 45,                          // "persist"
        S_LFC_INTERVAL = 46,                     // "lfc-interval"
        S_READONLY = 47,                         // "readonly"
        S_CONNECT_TIMEOUT = 48,                  // "connect-timeout"
        S_READ_TIMEOUT = 49,                     // "read-timeout"
        S_WRITE_TIMEOUT = 50,                    // "write-timeout"
        S_TCP_USER_TIMEOUT = 51,                 // "tcp-user-timeout"
        S_MAX_RECONNECT_TRIES = 52,              // "max-reconnect-tries"
        S_RECONNECT_WAIT_TIME = 53,              // "reconnect-wait-time"
        S_ON_FAIL = 54,                          // "on-fail"
        S_STOP_RETRY_EXIT = 55,                  // "stop-retry-exit"
        S_SERVE_RETRY_EXIT = 56,                 // "serve-retry-exit"
        S_SERVE_RETRY_CONTINUE = 57,             // "serve-retry-continue"
        S_MAX_ROW_ERRORS = 58,                   // "max-row-errors"
        S_TRUST_ANCHOR = 59,                     // "trust-anchor"
        S_CERT_FILE = 60,                        // "cert-file"
        S_KEY_FILE = 61,                         // "key-file"
        S_CIPHER_LIST = 62,                      // "cipher-list"
        S_VALID_LIFETIME = 63,                   // "valid-lifetime"
        S_MIN_VALID_LIFETIME = 64,               // "min-valid-lifetime"
        S_MAX_VALID_LIFETIME = 65,               // "max-valid-lifetime"
        S_RENEW_TIMER = 66,                      // "renew-timer"
        S_REBIND_TIMER = 67,                     // "rebind-timer"
        S_CALCULATE_TEE_TIMES = 68,              // "calculate-tee-times"
        S_T1_PERCENT = 69,                       // "t1-percent"
        S_T2_PERCENT = 70,                       // "t2-percent"
        S_CACHE_THRESHOLD = 71,                  // "cache-threshold"
        S_CACHE_MAX_AGE = 72,                    // "cache-max-age"
        S_DECLINE_PROBATION_PERIOD = 73,         // "decline-probation-period"
        S_SERVER_TAG = 74,                       // "server-tag"
        S_STATISTIC_DEFAULT_SAMPLE_COUNT = 75,   // "statistic-default-sample-count"
        S_STATISTIC_DEFAULT_SAMPLE_AGE = 76,     // "statistic-default-sample-age"
        S_DDNS_SEND_UPDATES = 77,                // "ddns-send-updates"
        S_DDNS_OVERRIDE_NO_UPDATE = 78,          // "ddns-override-no-update"
        S_DDNS_OVERRIDE_CLIENT_UPDATE = 79,      // "ddns-override-client-update"
        S_DDNS_REPLACE_CLIENT_NAME = 80,         // "ddns-replace-client-name"
        S_DDNS_GENERATED_PREFIX = 81,            // "ddns-generated-prefix"
        S_DDNS_QUALIFYING_SUFFIX = 82,           // "ddns-qualifying-suffix"
        S_DDNS_UPDATE_ON_RENEW = 83,             // "ddns-update-on-renew"
        S_DDNS_USE_CONFLICT_RESOLUTION = 84,     // "ddns-use-conflict-resolution"
        S_STORE_EXTENDED_INFO = 85,              // "store-extended-info"
        S_SUBNET4 = 86,                          // "subnet4"
        S_SUBNET_4O6_INTERFACE = 87,             // "4o6-interface"
        S_SUBNET_4O6_INTERFACE_ID = 88,          // "4o6-interface-id"
        S_SUBNET_4O6_SUBNET = 89,                // "4o6-subnet"
        S_OPTION_DEF = 90,                       // "option-def"
        S_OPTION_DATA = 91,                      // "option-data"
        S_NAME = 92,                             // "name"
        S_DATA = 93,                             // "data"
        S_CODE = 94,                             // "code"
        S_SPACE = 95,                            // "space"
        S_CSV_FORMAT = 96,                       // "csv-format"
        S_ALWAYS_SEND = 97,                      // "always-send"
        S_RECORD_TYPES = 98,                     // "record-types"
        S_ENCAPSULATE = 99,                      // "encapsulate"
        S_ARRAY = 100,                           // "array"
        S_PARKED_PACKET_LIMIT = 101,             // "parked-packet-limit"
        S_SHARED_NETWORKS = 102,                 // "shared-networks"
        S_POOLS = 103,                           // "pools"
        S_POOL = 104,                            // "pool"
        S_USER_CONTEXT = 105,                    // "user-context"
        S_COMMENT = 106,                         // "comment"
        S_SUBNET = 107,                          // "subnet"
        S_INTERFACE = 108,                       // "interface"
        S_ID = 109,                              // "id"
        S_RESERVATION_MODE = 110,                // "reservation-mode"
        S_DISABLED = 111,                        // "disabled"
        S_OUT_OF_POOL = 112,                     // "out-of-pool"
        S_GLOBAL = 113,                          // "global"
        S_ALL = 114,                             // "all"
        S_RESERVATIONS_GLOBAL = 115,             // "reservations-global"
        S_RESERVATIONS_IN_SUBNET = 116,          // "reservations-in-subnet"
        S_RESERVATIONS_OUT_OF_POOL = 117,        // "reservations-out-of-pool"
        S_HOST_RESERVATION_IDENTIFIERS = 118,    // "host-reservation-identifiers"
        S_CLIENT_CLASSES = 119,                  // "client-classes"
        S_REQUIRE_CLIENT_CLASSES = 120,          // "require-client-classes"
        S_TEST = 121,                            // "test"
        S_ONLY_IF_REQUIRED = 122,                // "only-if-required"
        S_CLIENT_CLASS = 123,                    // "client-class"
        S_RESERVATIONS = 124,                    // "reservations"
        S_DUID = 125,                            // "duid"
        S_HW_ADDRESS = 126,                      // "hw-address"
        S_CIRCUIT_ID = 127,                      // "circuit-id"
        S_CLIENT_ID = 128,                       // "client-id"
        S_HOSTNAME = 129,                        // "hostname"
        S_FLEX_ID = 130,                         // "flex-id"
        S_RELAY = 131,                           // "relay"
        S_IP_ADDRESS = 132,                      // "ip-address"
        S_IP_ADDRESSES = 133,                    // "ip-addresses"
        S_HOOKS_LIBRARIES = 134,                 // "hooks-libraries"
        S_LIBRARY = 135,                         // "library"
        S_PARAMETERS = 136,                      // "parameters"
        S_EXPIRED_LEASES_PROCESSING = 137,       // "expired-leases-processing"
        S_RECLAIM_TIMER_WAIT_TIME = 138,         // "reclaim-timer-wait-time"
        S_FLUSH_RECLAIMED_TIMER_WAIT_TIME = 139, // "flush-reclaimed-timer-wait-time"
        S_HOLD_RECLAIMED_TIME = 140,             // "hold-reclaimed-time"
        S_MAX_RECLAIM_LEASES = 141,              // "max-reclaim-leases"
        S_MAX_RECLAIM_TIME = 142,                // "max-reclaim-time"
        S_UNWARNED_RECLAIM_CYCLES = 143,         // "unwarned-reclaim-cycles"
        S_DHCP4O6_PORT = 144,                    // "dhcp4o6-port"
        S_DHCP_MULTI_THREADING = 145,            // "multi-threading"
        S_ENABLE_MULTI_THREADING = 146,          // "enable-multi-threading"
        S_THREAD_POOL_SIZE = 147,                // "thread-pool-size"
        S_PACKET_QUEUE_SIZE = 148,               // "packet-queue-size"
        S_CONTROL_SOCKET = 149,                  // "control-socket"
        S_SOCKET_TYPE = 150,                     // "socket-type"
        S_SOCKET_NAME = 151,                     // "socket-name"
        S_DHCP_QUEUE_CONTROL = 152,              // "dhcp-queue-control"
        S_ENABLE_QUEUE = 153,                    // "enable-queue"
        S_QUEUE_TYPE = 154,                      // "queue-type"
        S_CAPACITY = 155,                        // "capacity"
        S_DHCP_DDNS = 156,                       // "dhcp-ddns"
        S_ENABLE_UPDATES = 157,                  // "enable-updates"
        S_QUALIFYING_SUFFIX = 158,               // "qualifying-suffix"
        S_SERVER_IP = 159,                       // "server-ip"
        S_SERVER_PORT = 160,                     // "server-port"
        S_SENDER_IP = 161,                       // "sender-ip"
        S_SENDER_PORT = 162,                     // "sender-port"
        S_MAX_QUEUE_SIZE = 163,                  // "max-queue-size"
        S_NCR_PROTOCOL = 164,                    // "ncr-protocol"
        S_NCR_FORMAT = 165,                      // "ncr-format"
        S_OVERRIDE_NO_UPDATE = 166,              // "override-no-update"
        S_OVERRIDE_CLIENT_UPDATE = 167,          // "override-client-update"
        S_REPLACE_CLIENT_NAME = 168,             // "replace-client-name"
        S_GENERATED_PREFIX = 169,                // "generated-prefix"
        S_TCP = 170,                             // "tcp"
        S_JSON = 171,                            // "JSON"
        S_WHEN_PRESENT = 172,                    // "when-present"
        S_NEVER = 173,                           // "never"
        S_ALWAYS = 174,                          // "always"
        S_WHEN_NOT_PRESENT = 175,                // "when-not-present"
        S_HOSTNAME_CHAR_SET = 176,               // "hostname-char-set"
        S_HOSTNAME_CHAR_REPLACEMENT = 177,       // "hostname-char-replacement"
        S_EARLY_GLOBAL_RESERVATIONS_LOOKUP = 178, // "early-global-reservations-lookup"
        S_IP_RESERVATIONS_UNIQUE = 179,          // "ip-reservations-unique"
        S_RESERVATIONS_LOOKUP_FIRST = 180,       // "reservations-lookup-first"
        S_LOGGERS = 181,                         // "loggers"
        S_OUTPUT_OPTIONS = 182,                  // "output_options"
        S_OUTPUT = 183,                          // "output"
        S_DEBUGLEVEL = 184,                      // "debuglevel"
        S_SEVERITY = 185,                        // "severity"
        S_FLUSH = 186,                           // "flush"
        S_MAXSIZE = 187,                         // "maxsize"
        S_MAXVER = 188,                          // "maxver"
        S_PATTERN = 189,                         // "pattern"
        S_COMPATIBILITY = 190,                   // "compatibility"
        S_LENIENT_OPTION_PARSING = 191,          // "lenient-option-parsing"
        S_TOPLEVEL_JSON = 192,                   // TOPLEVEL_JSON
        S_TOPLEVEL_DHCP4 = 193,                  // TOPLEVEL_DHCP4
        S_SUB_DHCP4 = 194,                       // SUB_DHCP4
        S_SUB_INTERFACES4 = 195,                 // SUB_INTERFACES4
        S_SUB_SUBNET4 = 196,                     // SUB_SUBNET4
        S_SUB_POOL4 = 197,                       // SUB_POOL4
        S_SUB_RESERVATION = 198,                 // SUB_RESERVATION
        S_SUB_OPTION_DEFS = 199,                 // SUB_OPTION_DEFS
        S_SUB_OPTION_DEF = 200,                  // SUB_OPTION_DEF
        S_SUB_OPTION_DATA = 201,                 // SUB_OPTION_DATA
        S_SUB_HOOKS_LIBRARY = 202,               // SUB_HOOKS_LIBRARY
        S_SUB_DHCP_DDNS = 203,                   // SUB_DHCP_DDNS
        S_SUB_CONFIG_CONTROL = 204,              // SUB_CONFIG_CONTROL
        S_STRING = 205,                          // "constant string"
        S_INTEGER = 206,                         // "integer"
        S_FLOAT = 207,                           // "floating point"
        S_BOOLEAN = 208,                         // "boolean"
        S_YYACCEPT = 209,                        // $accept
        S_start = 210,                           // start
        S_211_1 = 211,                           // $@1
        S_212_2 = 212,                           // $@2
        S_213_3 = 213,                           // $@3
        S_214_4 = 214,                           // $@4
        S_215_5 = 215,                           // $@5
        S_216_6 = 216,                           // $@6
        S_217_7 = 217,                           // $@7
        S_218_8 = 218,                           // $@8
        S_219_9 = 219,                           // $@9
        S_220_10 = 220,                          // $@10
        S_221_11 = 221,                          // $@11
        S_222_12 = 222,                          // $@12
        S_223_13 = 223,                          // $@13
        S_value = 224,                           // value
        S_sub_json = 225,                        // sub_json
        S_map2 = 226,                            // map2
        S_227_14 = 227,                          // $@14
        S_map_value = 228,                       // map_value
        S_map_content = 229,                     // map_content
        S_not_empty_map = 230,                   // not_empty_map
        S_list_generic = 231,                    // list_generic
        S_232_15 = 232,                          // $@15
        S_list_content = 233,                    // list_content
        S_not_empty_list = 234,                  // not_empty_list
        S_list_strings = 235,                    // list_strings
        S_236_16 = 236,                          // $@16
        S_list_strings_content = 237,            // list_strings_content
        S_not_empty_list_strings = 238,          // not_empty_list_strings
        S_unknown_map_entry = 239,               // unknown_map_entry
        S_syntax_map = 240,                      // syntax_map
        S_241_17 = 241,                          // $@17
        S_global_object = 242,                   // global_object
        S_243_18 = 243,                          // $@18
        S_global_object_comma = 244,             // global_object_comma
        S_sub_dhcp4 = 245,                       // sub_dhcp4
        S_246_19 = 246,                          // $@19
        S_global_params = 247,                   // global_params
        S_global_param = 248,                    // global_param
        S_valid_lifetime = 249,                  // valid_lifetime
        S_min_valid_lifetime = 250,              // min_valid_lifetime
        S_max_valid_lifetime = 251,              // max_valid_lifetime
        S_renew_timer = 252,                     // renew_timer
        S_rebind_timer = 253,                    // rebind_timer
        S_calculate_tee_times = 254,             // calculate_tee_times
        S_t1_percent = 255,                      // t1_percent
        S_t2_percent = 256,                      // t2_percent
        S_cache_threshold = 257,                 // cache_threshold
        S_cache_max_age = 258,                   // cache_max_age
        S_decline_probation_period = 259,        // decline_probation_period
        S_server_tag = 260,                      // server_tag
        S_261_20 = 261,                          // $@20
        S_parked_packet_limit = 262,             // parked_packet_limit
        S_echo_client_id = 263,                  // echo_client_id
        S_match_client_id = 264,                 // match_client_id
        S_authoritative = 265,                   // authoritative
        S_ddns_send_updates = 266,               // ddns_send_updates
        S_ddns_override_no_update = 267,         // ddns_override_no_update
        S_ddns_override_client_update = 268,     // ddns_override_client_update
        S_ddns_replace_client_name = 269,        // ddns_replace_client_name
        S_270_21 = 270,                          // $@21
        S_ddns_replace_client_name_value = 271,  // ddns_replace_client_name_value
        S_ddns_generated_prefix = 272,           // ddns_generated_prefix
        S_273_22 = 273,                          // $@22
        S_ddns_qualifying_suffix = 274,          // ddns_qualifying_suffix
        S_275_23 = 275,                          // $@23
        S_ddns_update_on_renew = 276,            // ddns_update_on_renew
        S_ddns_use_conflict_resolution = 277,    // ddns_use_conflict_resolution
        S_hostname_char_set = 278,               // hostname_char_set
        S_279_24 = 279,                          // $@24
        S_hostname_char_replacement = 280,       // hostname_char_replacement
        S_281_25 = 281,                          // $@25
        S_store_extended_info = 282,             // store_extended_info
        S_statistic_default_sample_count = 283,  // statistic_default_sample_count
        S_statistic_default_sample_age = 284,    // statistic_default_sample_age
        S_early_global_reservations_lookup = 285, // early_global_reservations_lookup
        S_ip_reservations_unique = 286,          // ip_reservations_unique
        S_reservations_lookup_first = 287,       // reservations_lookup_first
        S_interfaces_config = 288,               // interfaces_config
        S_289_26 = 289,                          // $@26
        S_interfaces_config_params = 290,        // interfaces_config_params
        S_interfaces_config_param = 291,         // interfaces_config_param
        S_sub_interfaces4 = 292,                 // sub_interfaces4
        S_293_27 = 293,                          // $@27
        S_interfaces_list = 294,                 // interfaces_list
        S_295_28 = 295,                          // $@28
        S_dhcp_socket_type = 296,                // dhcp_socket_type
        S_297_29 = 297,                          // $@29
        S_socket_type = 298,                     // socket_type
        S_outbound_interface = 299,              // outbound_interface
        S_300_30 = 300,                          // $@30
        S_outbound_interface_value = 301,        // outbound_interface_value
        S_re_detect = 302,                       // re_detect
        S_service_sockets_require_all = 303,     // service_sockets_require_all
        S_service_sockets_retry_wait_time = 304, // service_sockets_retry_wait_time
        S_service_sockets_max_retries = 305,     // service_sockets_max_retries
        S_lease_database = 306,                  // lease_database
        S_307_31 = 307,                          // $@31
        S_sanity_checks = 308,                   // sanity_checks
        S_309_32 = 309,                          // $@32
        S_sanity_checks_params = 310,            // sanity_checks_params
        S_sanity_checks_param = 311,             // sanity_checks_param
        S_lease_checks = 312,                    // lease_checks
        S_313_33 = 313,                          // $@33
        S_hosts_database = 314,                  // hosts_database
        S_315_34 = 315,                          // $@34
        S_hosts_databases = 316,                 // hosts_databases
        S_317_35 = 317,                          // $@35
        S_database_list = 318,                   // database_list
        S_not_empty_database_list = 319,         // not_empty_database_list
        S_database = 320,                        // database
        S_321_36 = 321,                          // $@36
        S_database_map_params = 322,             // database_map_params
        S_database_map_param = 323,              // database_map_param
        S_database_type = 324,                   // database_type
        S_325_37 = 325,                          // $@37
        S_db_type = 326,                         // db_type
        S_user = 327,                            // user
        S_328_38 = 328,                          // $@38
        S_password = 329,                        // password
        S_330_39 = 330,                          // $@39
        S_host = 331,                            // host
        S_332_40 = 332,                          // $@40
        S_port = 333,                            // port
        S_name = 334,                            // name
        S_335_41 = 335,                          // $@41
        S_persist = 336,                         // persist
        S_lfc_interval = 337,                    // lfc_interval
        S_readonly = 338,                        // readonly
        S_connect_timeout = 339,                 // connect_timeout
        S_read_timeout = 340,                    // read_timeout
        S_write_timeout = 341,                   // write_timeout
        S_tcp_user_timeout = 342,                // tcp_user_timeout
        S_max_reconnect_tries = 343,             // max_reconnect_tries
        S_reconnect_wait_time = 344,             // reconnect_wait_time
        S_on_fail = 345,                         // on_fail
        S_346_42 = 346,                          // $@42
        S_on_fail_mode = 347,                    // on_fail_mode
        S_max_row_errors = 348,                  // max_row_errors
        S_trust_anchor = 349,                    // trust_anchor
        S_350_43 = 350,                          // $@43
        S_cert_file = 351,                       // cert_file
        S_352_44 = 352,                          // $@44
        S_key_file = 353,                        // key_file
        S_354_45 = 354,                          // $@45
        S_cipher_list = 355,                     // cipher_list
        S_356_46 = 356,                          // $@46
        S_host_reservation_identifiers = 357,    // host_reservation_identifiers
        S_358_47 = 358,                          // $@47
        S_host_reservation_identifiers_list = 359, // host_reservation_identifiers_list
        S_host_reservation_identifier = 360,     // host_reservation_identifier
        S_duid_id = 361,                         // duid_id
        S_hw_address_id = 362,                   // hw_address_id
        S_circuit_id = 363,                      // circuit_id
        S_client_id = 364,                       // client_id
        S_flex_id = 365,                         // flex_id
        S_dhcp_multi_threading = 366,            // dhcp_multi_threading
        S_367_48 = 367,                          // $@48
        S_multi_threading_params = 368,          // multi_threading_params
        S_multi_threading_param = 369,           // multi_threading_param
        S_enable_multi_threading = 370,          // enable_multi_threading
        S_thread_pool_size = 371,                // thread_pool_size
        S_packet_queue_size = 372,               // packet_queue_size
        S_hooks_libraries = 373,                 // hooks_libraries
        S_374_49 = 374,                          // $@49
        S_hooks_libraries_list = 375,            // hooks_libraries_list
        S_not_empty_hooks_libraries_list = 376,  // not_empty_hooks_libraries_list
        S_hooks_library = 377,                   // hooks_library
        S_378_50 = 378,                          // $@50
        S_sub_hooks_library = 379,               // sub_hooks_library
        S_380_51 = 380,                          // $@51
        S_hooks_params = 381,                    // hooks_params
        S_hooks_param = 382,                     // hooks_param
        S_library = 383,                         // library
        S_384_52 = 384,                          // $@52
        S_parameters = 385,                      // parameters
        S_386_53 = 386,                          // $@53
        S_expired_leases_processing = 387,       // expired_leases_processing
        S_388_54 = 388,                          // $@54
        S_expired_leases_params = 389,           // expired_leases_params
        S_expired_leases_param = 390,            // expired_leases_param
        S_reclaim_timer_wait_time = 391,         // reclaim_timer_wait_time
        S_flush_reclaimed_timer_wait_time = 392, // flush_reclaimed_timer_wait_time
        S_hold_reclaimed_time = 393,             // hold_reclaimed_time
        S_max_reclaim_leases = 394,              // max_reclaim_leases
        S_max_reclaim_time = 395,                // max_reclaim_time
        S_unwarned_reclaim_cycles = 396,         // unwarned_reclaim_cycles
        S_subnet4_list = 397,                    // subnet4_list
        S_398_55 = 398,                          // $@55
        S_subnet4_list_content = 399,            // subnet4_list_content
        S_not_empty_subnet4_list = 400,          // not_empty_subnet4_list
        S_subnet4 = 401,                         // subnet4
        S_402_56 = 402,                          // $@56
        S_sub_subnet4 = 403,                     // sub_subnet4
        S_404_57 = 404,                          // $@57
        S_subnet4_params = 405,                  // subnet4_params
        S_subnet4_param = 406,                   // subnet4_param
        S_subnet = 407,                          // subnet
        S_408_58 = 408,                          // $@58
        S_subnet_4o6_interface = 409,            // subnet_4o6_interface
        S_410_59 = 410,                          // $@59
        S_subnet_4o6_interface_id = 411,         // subnet_4o6_interface_id
        S_412_60 = 412,                          // $@60
        S_subnet_4o6_subnet = 413,               // subnet_4o6_subnet
        S_414_61 = 414,                          // $@61
        S_interface = 415,                       // interface
        S_416_62 = 416,                          // $@62
        S_client_class = 417,                    // client_class
        S_418_63 = 418,                          // $@63
        S_require_client_classes = 419,          // require_client_classes
        S_420_64 = 420,                          // $@64
        S_reservations_global = 421,             // reservations_global
        S_reservations_in_subnet = 422,          // reservations_in_subnet
        S_reservations_out_of_pool = 423,        // reservations_out_of_pool
        S_reservation_mode = 424,                // reservation_mode
        S_425_65 = 425,                          // $@65
        S_hr_mode = 426,                         // hr_mode
        S_id = 427,                              // id
        S_shared_networks = 428,                 // shared_networks
        S_429_66 = 429,                          // $@66
        S_shared_networks_content = 430,         // shared_networks_content
        S_shared_networks_list = 431,            // shared_networks_list
        S_shared_network = 432,                  // shared_network
        S_433_67 = 433,                          // $@67
        S_shared_network_params = 434,           // shared_network_params
        S_shared_network_param = 435,            // shared_network_param
        S_option_def_list = 436,                 // option_def_list
        S_437_68 = 437,                          // $@68
        S_sub_option_def_list = 438,             // sub_option_def_list
        S_439_69 = 439,                          // $@69
        S_option_def_list_content = 440,         // option_def_list_content
        S_not_empty_option_def_list = 441,       // not_empty_option_def_list
        S_option_def_entry = 442,                // option_def_entry
        S_443_70 = 443,                          // $@70
        S_sub_option_def = 444,                  // sub_option_def
        S_445_71 = 445,                          // $@71
        S_option_def_params = 446,               // option_def_params
        S_not_empty_option_def_params = 447,     // not_empty_option_def_params
        S_option_def_param = 448,                // option_def_param
        S_option_def_name = 449,                 // option_def_name
        S_code = 450,                            // code
        S_option_def_code = 451,                 // option_def_code
        S_option_def_type = 452,                 // option_def_type
        S_453_72 = 453,                          // $@72
        S_option_def_record_types = 454,         // option_def_record_types
        S_455_73 = 455,                          // $@73
        S_space = 456,                           // space
        S_457_74 = 457,                          // $@74
        S_option_def_space = 458,                // option_def_space
        S_option_def_encapsulate = 459,          // option_def_encapsulate
        S_460_75 = 460,                          // $@75
        S_option_def_array = 461,                // option_def_array
        S_option_data_list = 462,                // option_data_list
        S_463_76 = 463,                          // $@76
        S_option_data_list_content = 464,        // option_data_list_content
        S_not_empty_option_data_list = 465,      // not_empty_option_data_list
        S_option_data_entry = 466,               // option_data_entry
        S_467_77 = 467,                          // $@77
        S_sub_option_data = 468,                 // sub_option_data
        S_469_78 = 469,                          // $@78
        S_option_data_params = 470,              // option_data_params
        S_not_empty_option_data_params = 471,    // not_empty_option_data_params
        S_option_data_param = 472,               // option_data_param
        S_option_data_name = 473,                // option_data_name
        S_option_data_data = 474,                // option_data_data
        S_475_79 = 475,                          // $@79
        S_option_data_code = 476,                // option_data_code
        S_option_data_space = 477,               // option_data_space
        S_option_data_csv_format = 478,          // option_data_csv_format
        S_option_data_always_send = 479,         // option_data_always_send
        S_pools_list = 480,                      // pools_list
        S_481_80 = 481,                          // $@80
        S_pools_list_content = 482,              // pools_list_content
        S_not_empty_pools_list = 483,            // not_empty_pools_list
        S_pool_list_entry = 484,                 // pool_list_entry
        S_485_81 = 485,                          // $@81
        S_sub_pool4 = 486,                       // sub_pool4
        S_487_82 = 487,                          // $@82
        S_pool_params = 488,                     // pool_params
        S_pool_param = 489,                      // pool_param
        S_pool_entry = 490,                      // pool_entry
        S_491_83 = 491,                          // $@83
        S_user_context = 492,                    // user_context
        S_493_84 = 493,                          // $@84
        S_comment = 494,                         // comment
        S_495_85 = 495,                          // $@85
        S_reservations = 496,                    // reservations
        S_497_86 = 497,                          // $@86
        S_reservations_list = 498,               // reservations_list
        S_not_empty_reservations_list = 499,     // not_empty_reservations_list
        S_reservation = 500,                     // reservation
        S_501_87 = 501,                          // $@87
        S_sub_reservation = 502,                 // sub_reservation
        S_503_88 = 503,                          // $@88
        S_reservation_params = 504,              // reservation_params
        S_not_empty_reservation_params = 505,    // not_empty_reservation_params
        S_reservation_param = 506,               // reservation_param
        S_next_server = 507,                     // next_server
        S_508_89 = 508,                          // $@89
        S_server_hostname = 509,                 // server_hostname
        S_510_90 = 510,                          // $@90
        S_boot_file_name = 511,                  // boot_file_name
        S_512_91 = 512,                          // $@91
        S_ip_address = 513,                      // ip_address
        S_514_92 = 514,                          // $@92
        S_ip_addresses = 515,                    // ip_addresses
        S_516_93 = 516,                          // $@93
        S_duid = 517,                            // duid
        S_518_94 = 518,                          // $@94
        S_hw_address = 519,                      // hw_address
        S_520_95 = 520,                          // $@95
        S_client_id_value = 521,                 // client_id_value
        S_522_96 = 522,                          // $@96
        S_circuit_id_value = 523,                // circuit_id_value
        S_524_97 = 524,                          // $@97
        S_flex_id_value = 525,                   // flex_id_value
        S_526_98 = 526,                          // $@98
        S_hostname = 527,                        // hostname
        S_528_99 = 528,                          // $@99
        S_reservation_client_classes = 529,      // reservation_client_classes
        S_530_100 = 530,                         // $@100
        S_relay = 531,                           // relay
        S_532_101 = 532,                         // $@101
        S_relay_map = 533,                       // relay_map
        S_client_classes = 534,                  // client_classes
        S_535_102 = 535,                         // $@102
        S_client_classes_list = 536,             // client_classes_list
        S_client_class_entry = 537,              // client_class_entry
        S_538_103 = 538,                         // $@103
        S_client_class_params = 539,             // client_class_params
        S_not_empty_client_class_params = 540,   // not_empty_client_class_params
        S_client_class_param = 541,              // client_class_param
        S_client_class_name = 542,               // client_class_name
        S_client_class_test = 543,               // client_class_test
        S_544_104 = 544,                         // $@104
        S_only_if_required = 545,                // only_if_required
        S_dhcp4o6_port = 546,                    // dhcp4o6_port
        S_control_socket = 547,                  // control_socket
        S_548_105 = 548,                         // $@105
        S_control_socket_params = 549,           // control_socket_params
        S_control_socket_param = 550,            // control_socket_param
        S_control_socket_type = 551,             // control_socket_type
        S_552_106 = 552,                         // $@106
        S_control_socket_name = 553,             // control_socket_name
        S_554_107 = 554,                         // $@107
        S_dhcp_queue_control = 555,              // dhcp_queue_control
        S_556_108 = 556,                         // $@108
        S_queue_control_params = 557,            // queue_control_params
        S_queue_control_param = 558,             // queue_control_param
        S_enable_queue = 559,                    // enable_queue
        S_queue_type = 560,                      // queue_type
        S_561_109 = 561,                         // $@109
        S_capacity = 562,                        // capacity
        S_arbitrary_map_entry = 563,             // arbitrary_map_entry
        S_564_110 = 564,                         // $@110
        S_dhcp_ddns = 565,                       // dhcp_ddns
        S_566_111 = 566,                         // $@111
        S_sub_dhcp_ddns = 567,                   // sub_dhcp_ddns
        S_568_112 = 568,                         // $@112
        S_dhcp_ddns_params = 569,                // dhcp_ddns_params
        S_dhcp_ddns_param = 570,                 // dhcp_ddns_param
        S_enable_updates = 571,                  // enable_updates
        S_server_ip = 572,                       // server_ip
        S_573_113 = 573,                         // $@113
        S_server_port = 574,                     // server_port
        S_sender_ip = 575,                       // sender_ip
        S_576_114 = 576,                         // $@114
        S_sender_port = 577,                     // sender_port
        S_max_queue_size = 578,                  // max_queue_size
        S_ncr_protocol = 579,                    // ncr_protocol
        S_580_115 = 580,                         // $@115
        S_ncr_protocol_value = 581,              // ncr_protocol_value
        S_ncr_format = 582,                      // ncr_format
        S_583_116 = 583,                         // $@116
        S_dep_qualifying_suffix = 584,           // dep_qualifying_suffix
        S_585_117 = 585,                         // $@117
        S_dep_override_no_update = 586,          // dep_override_no_update
        S_dep_override_client_update = 587,      // dep_override_client_update
        S_dep_replace_client_name = 588,         // dep_replace_client_name
        S_589_118 = 589,                         // $@118
        S_dep_generated_prefix = 590,            // dep_generated_prefix
        S_591_119 = 591,                         // $@119
        S_dep_hostname_char_set = 592,           // dep_hostname_char_set
        S_593_120 = 593,                         // $@120
        S_dep_hostname_char_replacement = 594,   // dep_hostname_char_replacement
        S_595_121 = 595,                         // $@121
        S_config_control = 596,                  // config_control
        S_597_122 = 597,                         // $@122
        S_sub_config_control = 598,              // sub_config_control
        S_599_123 = 599,                         // $@123
        S_config_control_params = 600,           // config_control_params
        S_config_control_param = 601,            // config_control_param
        S_config_databases = 602,                // config_databases
        S_603_124 = 603,                         // $@124
        S_config_fetch_wait_time = 604,          // config_fetch_wait_time
        S_loggers = 605,                         // loggers
        S_606_125 = 606,                         // $@125
        S_loggers_entries = 607,                 // loggers_entries
        S_logger_entry = 608,                    // logger_entry
        S_609_126 = 609,                         // $@126
        S_logger_params = 610,                   // logger_params
        S_logger_param = 611,                    // logger_param
        S_debuglevel = 612,                      // debuglevel
        S_severity = 613,                        // severity
        S_614_127 = 614,                         // $@127
        S_output_options_list = 615,             // output_options_list
        S_616_128 = 616,                         // $@128
        S_output_options_list_content = 617,     // output_options_list_content
        S_output_entry = 618,                    // output_entry
        S_619_129 = 619,                         // $@129
        S_output_params_list = 620,              // output_params_list
        S_output_params = 621,                   // output_params
        S_output = 622,                          // output
        S_623_130 = 623,                         // $@130
        S_flush = 624,                           // flush
        S_maxsize = 625,                         // maxsize
        S_maxver = 626,                          // maxver
        S_pattern = 627,                         // pattern
        S_628_131 = 628,                         // $@131
        S_compatibility = 629,                   // compatibility
        S_630_132 = 630,                         // $@132
        S_compatibility_params = 631,            // compatibility_params
        S_compatibility_param = 632,             // compatibility_param
        S_lenient_option_parsing = 633           // lenient_option_parsing
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
      case symbol_kind::S_socket_type: // socket_type
      case symbol_kind::S_outbound_interface_value: // outbound_interface_value
      case symbol_kind::S_db_type: // db_type
      case symbol_kind::S_on_fail_mode: // on_fail_mode
      case symbol_kind::S_hr_mode: // hr_mode
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
      case symbol_kind::S_socket_type: // socket_type
      case symbol_kind::S_outbound_interface_value: // outbound_interface_value
      case symbol_kind::S_db_type: // db_type
      case symbol_kind::S_on_fail_mode: // on_fail_mode
      case symbol_kind::S_hr_mode: // hr_mode
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
        return Dhcp4Parser::symbol_name (this->kind ());
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
        PARSER4__ASSERT (tok == token::TOKEN_END
                   || (token::TOKEN_PARSER4_error <= tok && tok <= token::TOKEN_SUB_CONFIG_CONTROL));
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
        PARSER4__ASSERT (tok == token::TOKEN_BOOLEAN);
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
        PARSER4__ASSERT (tok == token::TOKEN_FLOAT);
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
        PARSER4__ASSERT (tok == token::TOKEN_INTEGER);
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
        PARSER4__ASSERT (tok == token::TOKEN_STRING);
#endif
      }
    };

    /// Build a parser object.
    Dhcp4Parser (isc::dhcp::Parser4Context& ctx_yyarg);
    virtual ~Dhcp4Parser ();

#if 201103L <= YY_CPLUSPLUS
    /// Non copyable.
    Dhcp4Parser (const Dhcp4Parser&) = delete;
    /// Non copyable.
    Dhcp4Parser& operator= (const Dhcp4Parser&) = delete;
#endif

    /// Parse.  An alias for parse ().
    /// \returns  0 iff parsing succeeded.
    int operator() ();

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
      make_PARSER4_error (location_type l)
      {
        return symbol_type (token::TOKEN_PARSER4_error, std::move (l));
      }
#else
      static
      symbol_type
      make_PARSER4_error (const location_type& l)
      {
        return symbol_type (token::TOKEN_PARSER4_error, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_PARSER4_UNDEF (location_type l)
      {
        return symbol_type (token::TOKEN_PARSER4_UNDEF, std::move (l));
      }
#else
      static
      symbol_type
      make_PARSER4_UNDEF (const location_type& l)
      {
        return symbol_type (token::TOKEN_PARSER4_UNDEF, l);
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
      make_DHCP4 (location_type l)
      {
        return symbol_type (token::TOKEN_DHCP4, std::move (l));
      }
#else
      static
      symbol_type
      make_DHCP4 (const location_type& l)
      {
        return symbol_type (token::TOKEN_DHCP4, l);
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
      make_DHCP_SOCKET_TYPE (location_type l)
      {
        return symbol_type (token::TOKEN_DHCP_SOCKET_TYPE, std::move (l));
      }
#else
      static
      symbol_type
      make_DHCP_SOCKET_TYPE (const location_type& l)
      {
        return symbol_type (token::TOKEN_DHCP_SOCKET_TYPE, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_RAW (location_type l)
      {
        return symbol_type (token::TOKEN_RAW, std::move (l));
      }
#else
      static
      symbol_type
      make_RAW (const location_type& l)
      {
        return symbol_type (token::TOKEN_RAW, l);
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
      make_OUTBOUND_INTERFACE (location_type l)
      {
        return symbol_type (token::TOKEN_OUTBOUND_INTERFACE, std::move (l));
      }
#else
      static
      symbol_type
      make_OUTBOUND_INTERFACE (const location_type& l)
      {
        return symbol_type (token::TOKEN_OUTBOUND_INTERFACE, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_SAME_AS_INBOUND (location_type l)
      {
        return symbol_type (token::TOKEN_SAME_AS_INBOUND, std::move (l));
      }
#else
      static
      symbol_type
      make_SAME_AS_INBOUND (const location_type& l)
      {
        return symbol_type (token::TOKEN_SAME_AS_INBOUND, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_USE_ROUTING (location_type l)
      {
        return symbol_type (token::TOKEN_USE_ROUTING, std::move (l));
      }
#else
      static
      symbol_type
      make_USE_ROUTING (const location_type& l)
      {
        return symbol_type (token::TOKEN_USE_ROUTING, l);
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
      make_ECHO_CLIENT_ID (location_type l)
      {
        return symbol_type (token::TOKEN_ECHO_CLIENT_ID, std::move (l));
      }
#else
      static
      symbol_type
      make_ECHO_CLIENT_ID (const location_type& l)
      {
        return symbol_type (token::TOKEN_ECHO_CLIENT_ID, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_MATCH_CLIENT_ID (location_type l)
      {
        return symbol_type (token::TOKEN_MATCH_CLIENT_ID, std::move (l));
      }
#else
      static
      symbol_type
      make_MATCH_CLIENT_ID (const location_type& l)
      {
        return symbol_type (token::TOKEN_MATCH_CLIENT_ID, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_AUTHORITATIVE (location_type l)
      {
        return symbol_type (token::TOKEN_AUTHORITATIVE, std::move (l));
      }
#else
      static
      symbol_type
      make_AUTHORITATIVE (const location_type& l)
      {
        return symbol_type (token::TOKEN_AUTHORITATIVE, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_NEXT_SERVER (location_type l)
      {
        return symbol_type (token::TOKEN_NEXT_SERVER, std::move (l));
      }
#else
      static
      symbol_type
      make_NEXT_SERVER (const location_type& l)
      {
        return symbol_type (token::TOKEN_NEXT_SERVER, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_SERVER_HOSTNAME (location_type l)
      {
        return symbol_type (token::TOKEN_SERVER_HOSTNAME, std::move (l));
      }
#else
      static
      symbol_type
      make_SERVER_HOSTNAME (const location_type& l)
      {
        return symbol_type (token::TOKEN_SERVER_HOSTNAME, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_BOOT_FILE_NAME (location_type l)
      {
        return symbol_type (token::TOKEN_BOOT_FILE_NAME, std::move (l));
      }
#else
      static
      symbol_type
      make_BOOT_FILE_NAME (const location_type& l)
      {
        return symbol_type (token::TOKEN_BOOT_FILE_NAME, l);
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
      make_SUBNET4 (location_type l)
      {
        return symbol_type (token::TOKEN_SUBNET4, std::move (l));
      }
#else
      static
      symbol_type
      make_SUBNET4 (const location_type& l)
      {
        return symbol_type (token::TOKEN_SUBNET4, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_SUBNET_4O6_INTERFACE (location_type l)
      {
        return symbol_type (token::TOKEN_SUBNET_4O6_INTERFACE, std::move (l));
      }
#else
      static
      symbol_type
      make_SUBNET_4O6_INTERFACE (const location_type& l)
      {
        return symbol_type (token::TOKEN_SUBNET_4O6_INTERFACE, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_SUBNET_4O6_INTERFACE_ID (location_type l)
      {
        return symbol_type (token::TOKEN_SUBNET_4O6_INTERFACE_ID, std::move (l));
      }
#else
      static
      symbol_type
      make_SUBNET_4O6_INTERFACE_ID (const location_type& l)
      {
        return symbol_type (token::TOKEN_SUBNET_4O6_INTERFACE_ID, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_SUBNET_4O6_SUBNET (location_type l)
      {
        return symbol_type (token::TOKEN_SUBNET_4O6_SUBNET, std::move (l));
      }
#else
      static
      symbol_type
      make_SUBNET_4O6_SUBNET (const location_type& l)
      {
        return symbol_type (token::TOKEN_SUBNET_4O6_SUBNET, l);
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
      make_CIRCUIT_ID (location_type l)
      {
        return symbol_type (token::TOKEN_CIRCUIT_ID, std::move (l));
      }
#else
      static
      symbol_type
      make_CIRCUIT_ID (const location_type& l)
      {
        return symbol_type (token::TOKEN_CIRCUIT_ID, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_CLIENT_ID (location_type l)
      {
        return symbol_type (token::TOKEN_CLIENT_ID, std::move (l));
      }
#else
      static
      symbol_type
      make_CLIENT_ID (const location_type& l)
      {
        return symbol_type (token::TOKEN_CLIENT_ID, l);
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
      make_TOPLEVEL_DHCP4 (location_type l)
      {
        return symbol_type (token::TOKEN_TOPLEVEL_DHCP4, std::move (l));
      }
#else
      static
      symbol_type
      make_TOPLEVEL_DHCP4 (const location_type& l)
      {
        return symbol_type (token::TOKEN_TOPLEVEL_DHCP4, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_SUB_DHCP4 (location_type l)
      {
        return symbol_type (token::TOKEN_SUB_DHCP4, std::move (l));
      }
#else
      static
      symbol_type
      make_SUB_DHCP4 (const location_type& l)
      {
        return symbol_type (token::TOKEN_SUB_DHCP4, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_SUB_INTERFACES4 (location_type l)
      {
        return symbol_type (token::TOKEN_SUB_INTERFACES4, std::move (l));
      }
#else
      static
      symbol_type
      make_SUB_INTERFACES4 (const location_type& l)
      {
        return symbol_type (token::TOKEN_SUB_INTERFACES4, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_SUB_SUBNET4 (location_type l)
      {
        return symbol_type (token::TOKEN_SUB_SUBNET4, std::move (l));
      }
#else
      static
      symbol_type
      make_SUB_SUBNET4 (const location_type& l)
      {
        return symbol_type (token::TOKEN_SUB_SUBNET4, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_SUB_POOL4 (location_type l)
      {
        return symbol_type (token::TOKEN_SUB_POOL4, std::move (l));
      }
#else
      static
      symbol_type
      make_SUB_POOL4 (const location_type& l)
      {
        return symbol_type (token::TOKEN_SUB_POOL4, l);
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
      context (const Dhcp4Parser& yyparser, const symbol_type& yyla);
      const symbol_type& lookahead () const YY_NOEXCEPT { return yyla_; }
      symbol_kind_type token () const YY_NOEXCEPT { return yyla_.kind (); }
      const location_type& location () const YY_NOEXCEPT { return yyla_.location; }

      /// Put in YYARG at most YYARGN of the expected tokens, and return the
      /// number of tokens stored in YYARG.  If YYARG is null, return the
      /// number of expected tokens (guaranteed to be less than YYNTOKENS).
      int expected_tokens (symbol_kind_type yyarg[], int yyargn) const;

    private:
      const Dhcp4Parser& yyparser_;
      const symbol_type& yyla_;
    };

  private:
#if YY_CPLUSPLUS < 201103L
    /// Non copyable.
    Dhcp4Parser (const Dhcp4Parser&);
    /// Non copyable.
    Dhcp4Parser& operator= (const Dhcp4Parser&);
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


#if PARSER4_DEBUG
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
      yylast_ = 1274,     ///< Last index in yytable_.
      yynnts_ = 425,  ///< Number of nonterminal symbols.
      yyfinal_ = 28 ///< Termination state number.
    };


    // User arguments.
    isc::dhcp::Parser4Context& ctx;

  };

  inline
  Dhcp4Parser::symbol_kind_type
  Dhcp4Parser::yytranslate_ (int t) YY_NOEXCEPT
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
     205,   206,   207,   208
    };
    // Last valid token kind.
    const int code_max = 463;

    if (t <= 0)
      return symbol_kind::S_YYEOF;
    else if (t <= code_max)
      return static_cast <symbol_kind_type> (translate_table[t]);
    else
      return symbol_kind::S_YYUNDEF;
  }

  // basic_symbol.
  template <typename Base>
  Dhcp4Parser::basic_symbol<Base>::basic_symbol (const basic_symbol& that)
    : Base (that)
    , value ()
    , location (that.location)
  {
    switch (this->kind ())
    {
      case symbol_kind::S_value: // value
      case symbol_kind::S_map_value: // map_value
      case symbol_kind::S_ddns_replace_client_name_value: // ddns_replace_client_name_value
      case symbol_kind::S_socket_type: // socket_type
      case symbol_kind::S_outbound_interface_value: // outbound_interface_value
      case symbol_kind::S_db_type: // db_type
      case symbol_kind::S_on_fail_mode: // on_fail_mode
      case symbol_kind::S_hr_mode: // hr_mode
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
  Dhcp4Parser::symbol_kind_type
  Dhcp4Parser::basic_symbol<Base>::type_get () const YY_NOEXCEPT
  {
    return this->kind ();
  }


  template <typename Base>
  bool
  Dhcp4Parser::basic_symbol<Base>::empty () const YY_NOEXCEPT
  {
    return this->kind () == symbol_kind::S_YYEMPTY;
  }

  template <typename Base>
  void
  Dhcp4Parser::basic_symbol<Base>::move (basic_symbol& s)
  {
    super_type::move (s);
    switch (this->kind ())
    {
      case symbol_kind::S_value: // value
      case symbol_kind::S_map_value: // map_value
      case symbol_kind::S_ddns_replace_client_name_value: // ddns_replace_client_name_value
      case symbol_kind::S_socket_type: // socket_type
      case symbol_kind::S_outbound_interface_value: // outbound_interface_value
      case symbol_kind::S_db_type: // db_type
      case symbol_kind::S_on_fail_mode: // on_fail_mode
      case symbol_kind::S_hr_mode: // hr_mode
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
  Dhcp4Parser::by_kind::by_kind () YY_NOEXCEPT
    : kind_ (symbol_kind::S_YYEMPTY)
  {}

#if 201103L <= YY_CPLUSPLUS
  inline
  Dhcp4Parser::by_kind::by_kind (by_kind&& that) YY_NOEXCEPT
    : kind_ (that.kind_)
  {
    that.clear ();
  }
#endif

  inline
  Dhcp4Parser::by_kind::by_kind (const by_kind& that) YY_NOEXCEPT
    : kind_ (that.kind_)
  {}

  inline
  Dhcp4Parser::by_kind::by_kind (token_kind_type t) YY_NOEXCEPT
    : kind_ (yytranslate_ (t))
  {}



  inline
  void
  Dhcp4Parser::by_kind::clear () YY_NOEXCEPT
  {
    kind_ = symbol_kind::S_YYEMPTY;
  }

  inline
  void
  Dhcp4Parser::by_kind::move (by_kind& that)
  {
    kind_ = that.kind_;
    that.clear ();
  }

  inline
  Dhcp4Parser::symbol_kind_type
  Dhcp4Parser::by_kind::kind () const YY_NOEXCEPT
  {
    return kind_;
  }


  inline
  Dhcp4Parser::symbol_kind_type
  Dhcp4Parser::by_kind::type_get () const YY_NOEXCEPT
  {
    return this->kind ();
  }


#line 14 "dhcp4_parser.yy"
} } // isc::dhcp
#line 5475 "dhcp4_parser.h"




#endif // !YY_PARSER4_DHCP4_PARSER_H_INCLUDED
